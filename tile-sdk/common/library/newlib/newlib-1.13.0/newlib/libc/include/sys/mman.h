#ifndef SYS_MMAN_H
#define SYS_MMAN_H

/* mmap() protection modes */
#define PROT_READ    (0x1)
#define PROT_WRITE   (0x2)
#define PROT_EXEC    (0x4)
#define PROT_NONE    (0x0)

/* Sharing types (must choose one and only one of these).  */
#define MAP_SHARED	0x01		/* Share changes.  */
#define MAP_PRIVATE	0x02		/* Changes are private.  */
#define MAP_TYPE	0x03		/* Mask for type of mapping.  */

/* Other flags.  */
#define MAP_FIXED	0x10		/* Interpret addr exactly.  */
#define MAP_FILE	0
#define MAP_ANONYMOUS	0x20		/* Don't use a file.  */
#define MAP_ANON	MAP_ANONYMOUS

/* These are Linux-specific.  */
#define MAP_POPULATE	0x0040		/* populate (prefault) pagetables */
#define MAP_NONBLOCK	0x0080		/* do not block on IO */
#define MAP_GROWSDOWN	0x0100		/* Stack-like segment.  */
#define MAP_LOCKED	0x0200		/* Lock the mapping.  */
#define MAP_NORESERVE	0x0400		/* Don't check for reservations.  */
#define MAP_DENYWRITE	0x0800		/* ETXTBSY */
#define MAP_EXECUTABLE	0x1000		/* Mark it as an executable.  */
#define MAP_HUGETLB	0x4000		/* Create huge page mapping.  */

/* Flags for mremap. */
#define MREMAP_MAYMOVE	1
#define MREMAP_FIXED	2

/*
 * Specify the "home cache" for the page explicitly.  The home cache is
 * the cache of one particular "home" cpu, which is used as a coherence
 * point for normal cached operations.  Normally the kernel chooses for
 * you, but you can use the MAP_CACHE_HOME_xxx flags to override.
 *
 * User code should not use any symbols with a leading "_" as they are
 * implementation specific and may change from release to release
 * without warning.
 *
 * See the Tilera mmap(2) man page for more details (e.g. "tile-man mmap").
 */

/* Implementation details; do not use directly. */
#define _MAP_CACHE_INCOHERENT   0x40000
#define _MAP_CACHE_HOME         0x80000
#define _MAP_CACHE_HOME_SHIFT   20
#define _MAP_CACHE_HOME_MASK    0x3ff
#define _MAP_CACHE_MKHOME(n) \
  (_MAP_CACHE_HOME | (((n) & _MAP_CACHE_HOME_MASK) << _MAP_CACHE_HOME_SHIFT))

/* Set the home cache to the specified cpu. */
#define MAP_CACHE_HOME(n)       _MAP_CACHE_MKHOME(n)

/* Set the home cache to the current cpu. */
#define _MAP_CACHE_HOME_HERE    (_MAP_CACHE_HOME_MASK - 0)
#define MAP_CACHE_HOME_HERE     _MAP_CACHE_MKHOME(_MAP_CACHE_HOME_HERE)

/* Request no on-chip home, i.e. read from memory.  Invalid with PROT_WRITE. */
#define _MAP_CACHE_HOME_NONE    (_MAP_CACHE_HOME_MASK - 1)
#define MAP_CACHE_HOME_NONE     _MAP_CACHE_MKHOME(_MAP_CACHE_HOME_NONE)

/* Request no on-chip home, and allow incoherent PROT_WRITE mappings. */
#define MAP_CACHE_INCOHERENT    (_MAP_CACHE_INCOHERENT | MAP_CACHE_HOME_NONE)

/* Force the system to choose a single home cache, on a cpu of its choice. */
#define _MAP_CACHE_HOME_SINGLE  (_MAP_CACHE_HOME_MASK - 2)
#define MAP_CACHE_HOME_SINGLE   _MAP_CACHE_MKHOME(_MAP_CACHE_HOME_SINGLE)

/* Create a mapping that follows the task when it migrates. */
#define _MAP_CACHE_HOME_TASK    (_MAP_CACHE_HOME_MASK - 3)
#define MAP_CACHE_HOME_TASK     _MAP_CACHE_MKHOME(_MAP_CACHE_HOME_TASK)

/* Create a hash-for-home mapping. */
#define _MAP_CACHE_HOME_HASH    (_MAP_CACHE_HOME_MASK - 4)
#define MAP_CACHE_HOME_HASH     _MAP_CACHE_MKHOME(_MAP_CACHE_HOME_HASH)

/*
 * Specify local caching attributes for the mapping.  Normally the kernel
 * chooses whether to use the local cache, but these flags can be used
 * to override the kernel.
 */

/* Disable use of local L2 (on tile64, true for any writable mapping). */
#define MAP_CACHE_NO_L2         0x20000

/* Disable use of local L1 (on tile64, ignored; L1 is disabled with L2). */
#define MAP_CACHE_NO_L1         0x08000

/* Convenience alias that should be used for forward compatibility. */
#define MAP_CACHE_NO_LOCAL      (MAP_CACHE_NO_L1 | MAP_CACHE_NO_L2)

/* Convenience alias for direct-to-RAM mappings. */
#define MAP_CACHE_NONE          (MAP_CACHE_HOME_NONE | MAP_CACHE_NO_LOCAL)

/* Arrange for this mapping to take priority in the cache. */
#define MAP_CACHE_PRIORITY      0x02000

/*
 * Environment variable that controls hash-for-home in user programs.
 */
#define MAP_CACHE_HASH_ENV_VAR "LD_CACHE_HASH"

#ifndef __ASSEMBLER__

/** A the error value returned by a bad mmap. */
#define MAP_FAILED ((void*)-1)

#include <sys/types.h>

void *
mmap(void *start, size_t length, int protection, int flags,
     int fd, off_t offset);

void *
mmap64(void *start, size_t length, int protection, int flags,
       int fd, loff_t offset);

int
munmap(void *start, size_t length);

void *
mremap(void *old_address, size_t old_size, size_t new_size, int flags, ...);

int
mprotect(void *start, size_t length, int protection);

#ifdef _COMPILING_NEWLIB
/* 
 * When building newlib, provide additional definitions that
 * user programs don't need to see.
 */
struct _reent;
void *
_mmap_r(struct _reent *, void *start, size_t length, int protection, int flags,
     int fd, off_t offset, ...);
void *
_munmap_r(struct _reent *, void *start, size_t length);
void *
_mremap_r(struct _reent *, void *old_address, size_t old_size,
          size_t new_size, int flags);
int
_mprotect_r(struct _reent *, void *start, size_t length, int protection);
#endif

#endif /* __ASSEMBLER__ */

#endif /* SYS_MMAN_H */
