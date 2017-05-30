/* Provide the appropriate flavor of mmap syscall.  */

#include <unistd.h>
#include <sys/mman.h>
#include <sys/syscall.h>

#define MMAP_PAGE_SHIFT 12

void* mmap64(void* addr, size_t len, int prot, int flags, int fd, loff_t offset)
{
#ifdef __LP64__
  return (void*) syscall(SYS_mmap, addr, len, prot, flags, fd, offset);
#else
  return (void*) syscall(SYS_mmap2, addr, len, prot, flags, fd,
                         (unsigned long)(offset >> MMAP_PAGE_SHIFT));
#endif
}
