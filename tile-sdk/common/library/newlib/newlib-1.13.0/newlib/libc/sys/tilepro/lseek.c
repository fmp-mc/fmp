/* Provide the appropriate flavor of lseek().  */

#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#if 0 // don't use Linux syscall in TOPPERS/FMP kernel -- ertl-liyixiao
off_t lseek(int fd, off_t offset, int whence)
{
#ifdef __LP64__
	return syscall(SYS_lseek, fd, offset, whence);
#else
	long long result;
	int rc = syscall(SYS_llseek, fd, offset >> 31, 
                         offset & 0xffffffff, &result, whence);
        return rc < 0 ? rc : (off_t)result;
#endif
}

/* Support newlib's internal syscall calling convention. */
off_t _lseek_r(void *tp, int fd, off_t offset, int whence)
{
	return lseek(fd, offset, whence);
}
#endif
