#ifndef _NEWLIB_STDIO_H
#define _NEWLIB_STDIO_H

#include <sys/lock.h>
#include <sys/reent.h>

/* Internal locking macros, used to protect stdio functions.  In the
   general case, expand to nothing. Use __SSTR flag in FILE _flags to
   detect if FILE is private to sprintf/sscanf class of functions; if
   set then do nothing as lock is not initialised. */
#if !defined(_flockfile)
#ifndef __SINGLE_THREAD__
#  define _flockfile(fp) do { if (!((fp)->_flags & __SSTR)) __lock_acquire_recursive((fp)->_lock); } while(0)
#else
#  define _flockfile(fp)
#endif
#endif

#if !defined(_ftrylockfile)
#ifndef __SINGLE_THREAD__
#  define _ftrylockfile(fp) ((!((fp)->_flags & __SSTR)) ? __lock_try_acquire_recursive((fp)->_lock) : 1)
#else
#  define _ftrylockfile(fp) 1
#endif
#endif

#if !defined(_funlockfile)
#ifndef __SINGLE_THREAD__
#  define _funlockfile(fp) do { if (!((fp)->_flags & __SSTR)) __lock_release_recursive((fp)->_lock); } while(0)
#else
#  define _funlockfile(fp)
#endif
#endif

#endif /* _NEWLIB_STDIO_H */
