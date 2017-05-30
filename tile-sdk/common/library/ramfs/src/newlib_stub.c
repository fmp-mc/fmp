#include <stdio.h>
#include <errno.h>
#include <hv/hypervisor.h>
#include <t_stddef.h>
#include <t_syslog.h>
#include <sys/stat.h> // Use struct stat in Newlib
#include <fcntl.h>

#include <kernel.h>
#include "syssvc/logtask.h"
#include "target_config.h"

#include "dfs_fs.h"
#include "dfs_ramfs.h"

#undef errno
//extern int errno;
int errno;

#define FD_TAB_SZ (256)
static struct dfs_filesystem fs;
static struct dfs_ramfs* ramfs;
static struct dfs_fd fd_tab[FD_TAB_SZ];
static int fd_used = 0;

#define NORMAL_FD_OFFSET (10)

int openat(int fd, const char *path, int oflag, ...) {
	ER ercd;

    if (fd_used < FD_TAB_SZ) {
        struct dfs_fd *tmp_fd = fd_tab + fd_used;
        tmp_fd->fs = &fs;

        /* initialize the fd item */
        tmp_fd->type  = FT_REGULAR;
        tmp_fd->flags = 0;
#define O_WRONLY 0x1
#define O_TRUNC 0x200
        if (oflag & O_WRONLY) { tmp_fd->flags |= DFS_O_WRONLY; oflag &= ~O_WRONLY; }
        if (oflag & O_TRUNC) { tmp_fd->flags |= DFS_O_TRUNC; oflag &= ~O_TRUNC; }
        if (oflag != 0) printf("Unhandled oflag 0x%x\n", oflag);
        tmp_fd->size  = 0;
        tmp_fd->pos   = 0;

        // TODO: check this
        tmp_fd->path = path;
        if ((ercd = dfs_ramfs_open(tmp_fd)) == DFS_STATUS_OK)
            return NORMAL_FD_OFFSET + fd_used++;
    }
    return -1; // TODO: check this
}

int open(const char *name, int flags, ...) {
	// TODO: mode is ignored currently
	return openat(0/*should use AT_FDCWD*/, name, flags, 0);
}

int _open_r(struct _reent *reent, const char *name, int flags, int mode) {
	// TODO: thread-safe
	return open(name, flags, mode);
}

int write(int fd, const void *buf, size_t count) {
	if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {

#define PRINTF_BUFFER_SIZE (1024 * 1024)
#if !defined(G_SYSLOG)
#error Only G_SYSLOG is supported!
#endif
		static char printf_buffer[PRINTF_BUFFER_SIZE];
		static uint32_t printf_buffer_head = 0, printf_buffer_tail = 0;
		static mcs_lock lock = NULL;

		bool_t add_log = false;

		mcs_lock_t me;
		lock_mcs(&lock, &me, false);
		char *head = printf_buffer + printf_buffer_head;
		assert(printf_buffer_tail + count <= sizeof(printf_buffer));
		memcpy(printf_buffer + printf_buffer_tail, buf, count);
		printf_buffer_tail += count;
		char *tail = printf_buffer + printf_buffer_tail - 1;
		for (int i = 0; i < count; ++i) if (*(tail - i) == '\n') { // TODO: optimize by search first before memcpy()?
			add_log = true;
			*(tail - i) = '\0';
			printf_buffer_head = printf_buffer_tail - i;
			break;
		}
		unlock_mcs(&lock, &me);

		if (add_log) {
			SYSLOG syslog;
			syslog.logtype = LOG_TYPE_COMMENT;
			syslog.loginfo[0] = (intptr_t) "%s";
			syslog.loginfo[1] = (intptr_t) head;
			syslog_wri_log(LOG_NOTICE, &syslog);
		}
		return count;
	} else if (fd < NORMAL_FD_OFFSET) {
        assert(false);
        return 0;
    }
    assert(fd >= NORMAL_FD_OFFSET);
    assert(fd < NORMAL_FD_OFFSET + fd_used);
    struct dfs_fd *tmp_fd = fd_tab + fd - NORMAL_FD_OFFSET;
    return dfs_ramfs_write(tmp_fd, buf, count);
}

int _write_r(struct _reent *reent, int fd, const void *buf, size_t count) {
	return write(fd, buf, count);
}

int read(int fd, void *buf, size_t count) {
    assert(fd >= NORMAL_FD_OFFSET);
    assert(fd < NORMAL_FD_OFFSET + fd_used);
    struct dfs_fd *tmp_fd = fd_tab + fd - NORMAL_FD_OFFSET;
    return dfs_ramfs_read(tmp_fd, buf, count);
}

_ssize_t _read_r(struct _reent *reent, int fd, void *buf, size_t count) {
	return read(fd, buf, count);
}

int close(int fd) {
	struct dfs_fd *tmp_fd = fd_tab + fd - NORMAL_FD_OFFSET;
	dfs_ramfs_close(tmp_fd);
	return 0;
}

int _close_r(struct _reent *reent, int fd) {
	return close(fd);
}

// TODO: support by dfs_ramfs_stat
int stat(const char *path, struct stat *st) {
	int fd = open(path, O_RDONLY);
	int rv = fstat(fd, st);
	close(fd);
	return rv;
}

// TODO: support by dfs_ramfs_stat
int fstat(int fd, struct stat *st) {
    assert(fd >= NORMAL_FD_OFFSET);
    assert(fd < NORMAL_FD_OFFSET + fd_used);
    struct dfs_fd *tmp_fd = fd_tab + fd - NORMAL_FD_OFFSET;
#define _IFREG  0100000 /* regular */
    st->st_mode = _IFREG;
    st->st_size = tmp_fd->size;
    return 0;
}

int _fstat_r(struct _reent *reent, int fd, struct stat *st) {
	return fstat(fd, st);
}

off_t lseek(int fd, off_t ptr, int dir) {
    assert(fd >= NORMAL_FD_OFFSET);
    assert(fd < NORMAL_FD_OFFSET + fd_used);
	struct dfs_fd *tmp_fd = fd_tab + fd - NORMAL_FD_OFFSET;
    assert(dir == SEEK_SET);
	return dfs_ramfs_lseek(tmp_fd, ptr);
}

_off_t _lseek_r(struct _reent *reent, int fd, _off_t ptr, int dir) {
	return lseek(fd, ptr, dir);
}

static void load_hv_file(const char *filename) {
	int inode = hv_fs_findfile(filename);
	assert(inode != HV_ENOENT);
	assert(inode != HV_EFAULT);

	HV_FS_StatInfo stat = hv_fs_fstat(inode);

	int fd = open(filename, DFS_O_CREAT|DFS_O_WRONLY/*O_CREAT*/, 0);

#if 1 // write directly into dfs_fd to save memory
    extern void  *uma_heap;
	int bytes_write = write(fd, uma_heap, stat.size);
    struct dfs_fd *tmp_fd = fd_tab + fd - NORMAL_FD_OFFSET;
	int bytes_read  = hv_fs_pread(inode, ((struct ramfs_dirent*)tmp_fd->data)->data, stat.size, 0);
	assert(bytes_write == bytes_read);
#endif
#if 0 // use malloc instead of buffer
	char *buf = malloc(stat.size);
	int bytes_read = hv_fs_pread(inode, buf, stat.size, 0);
	assert(bytes_read == stat.size);
	int bytes_write = write(fd, buf, bytes_read);
	assert(bytes_write == bytes_read);
	free(buf);
#endif
#if 0 // use buffer
    extern void  *uma_heap;
	write(fd, uma_heap, stat.size);
    lseek(fd, 0, SEEK_SET);
	static char buf[1024 * 1024];
	int bytes_read;
	for (int offset = 0/*, bytes_read*/; (bytes_read = hv_fs_pread(inode, buf, sizeof(buf), offset)) != 0; offset += bytes_read) {
		assert(bytes_read != HV_EBADF);
		assert(bytes_read != HV_EFAULT);
		//int bytes_write = fwrite(buf, 1, bytes_read, file);
		int bytes_write = write(fd, buf, bytes_read);
		assert(bytes_write == bytes_read);
	}
#endif

	close(fd);

    syslog(LOG_NOTICE, "in.txt (%lu bytes) loaded", stat.size);
}

void my_ramfs_init() {
	syslog(LOG_EMERG, "%s() start", __FUNCTION__);
    static unsigned char pool[sizeof(struct dfs_ramfs) * 2];
    ramfs = dfs_ramfs_create(pool, sizeof(pool));
    syslog(LOG_EMERG, "%s() here", __FUNCTION__);
    fs.data = ramfs;
    load_hv_file("in.txt"); // TODO: pesudo
	//debug_loop();
}

// Legacy code
#if 0
SIL_PRE_LOC; // TODO: check dead lock
SIL_LOC_SPN();
int bytes_written = 0;
for (int cnt; count > 0 && (cnt = hv_console_write(buf, count)) >= 0; ) {
    bytes_written += cnt;
    buf           += cnt;
    count         -= cnt;
}
SIL_UNL_SPN();
assert(count == 0);
return bytes_written;
#endif
