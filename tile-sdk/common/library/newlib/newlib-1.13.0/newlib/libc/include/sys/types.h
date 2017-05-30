/* unified sys/types.h: 
   start with sef's sysvi386 version.
   merge go32 version -- a few ifdefs.
   h8300hms, h8300xray, and sysvnecv70 disagree on the following types:

   typedef int gid_t;
   typedef int uid_t;
   typedef int dev_t;
   typedef int ino_t;
   typedef int mode_t;
   typedef int caddr_t;

   however, these aren't "reasonable" values, the sysvi386 ones make far 
   more sense, and should work sufficiently well (in particular, h8300 
   doesn't have a stat, and the necv70 doesn't matter.) -- eichin
 */

#ifndef _SYS_TYPES_H

#include <features.h>
#include <_ansi.h>

#ifndef __INTTYPES_DEFINED__
#define __INTTYPES_DEFINED__
typedef short int __int16_t;
typedef unsigned short int __uint16_t;

typedef signed char __int8_t;
typedef unsigned char __uint8_t;

#if __INT_MAX__ == 32767
typedef long int __int32_t;
typedef unsigned long int __uint32_t;
#else
typedef int __int32_t;
typedef unsigned int __uint32_t;
#endif

#if __LONG_MAX__ > 2147483647
typedef long int __int64_t;
typedef unsigned long int __uint64_t;
#else
#ifdef __GNUC__
__extension__ typedef long long __int64_t;
__extension__ typedef unsigned long long __uint64_t;
#else
typedef long long __int64_t;
typedef unsigned long long __uint64_t;
#endif
#endif
#endif /* ! __INTTYPES_DEFINED */

#ifndef __need_inttypes

#define _SYS_TYPES_H
#include <sys/_types.h>

#ifdef __i386__
#if defined (GO32) || defined (__MSDOS__)
#define __MS_types__
#endif
#endif

# include <stddef.h>
# include <machine/types.h>

/* To ensure the stat struct's layout doesn't change when sizeof(int), etc.
   changes, we assume sizeof short and long never change and have all types
   used to define struct stat use them and not int where possible.
   Where not possible, _ST_INTxx are used.  It would be preferable to not have
   such assumptions, but until the extra fluff is necessary, it's avoided.
   No 64 bit targets use stat yet.  What to do about them is postponed
   until necessary.  */
#ifdef __GNUC__
#define _ST_INT32 __attribute__ ((__mode__ (__SI__)))
#else
#define _ST_INT32
#endif

# ifndef	_POSIX_SOURCE

#  define	physadr		physadr_t
#  define	quad		quad_t

#ifndef _BSDTYPES_DEFINED
/* also defined in mingw/gmon.h and in w32api/winsock[2].h */
typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;
#define _BSDTYPES_DEFINED
#endif

typedef	unsigned short	ushort;		/* System V compatibility */
typedef	unsigned int	uint;		/* System V compatibility */
# endif	/*!_POSIX_SOURCE */

#ifndef __clock_t_defined
typedef _CLOCK_T_ clock_t;
#define __clock_t_defined
#endif

#ifndef __time_t_defined
typedef _TIME_T_ time_t;
#define __time_t_defined

/* Time Value Specification Structures, P1003.1b-1993, p. 261 */

struct timespec {
  time_t  tv_sec;   /* Seconds */
  long    tv_nsec;  /* Nanoseconds */
};

struct itimerspec {
  struct timespec  it_interval;  /* Timer period */
  struct timespec  it_value;     /* Timer expiration */
};
#endif

typedef	int	daddr_t;
typedef	char *	caddr_t;

typedef	unsigned long	ino_t;

#ifdef __MS_types__
typedef unsigned long vm_offset_t;
typedef unsigned long vm_size_t;

#define __BIT_TYPES_DEFINED__

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef int32_t register_t;
#endif /* __MS_types__ */

#if defined(__linux__) || defined(__MS_types__)
/* Provide additional types defined in Linux's <sys/types.h> */
typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;
#endif

/*
 * All these should be machine specific - right now they are all broken.
 * However, for all of Cygnus' embedded targets, we want them to all be
 * the same.  Otherwise things like sizeof (struct stat) might depend on
 * how the file was compiled (e.g. -mint16 vs -mint32, etc.).
 */

#ifdef __tile__  /* this is the standard Linux definition, actually */
typedef unsigned long   dev_t;
#else
typedef unsigned int    dev_t;
#endif

#ifndef __CYGWIN__	/* which defines these types in it's own types.h. */
typedef long		off_t;
typedef long long	loff_t;

typedef	unsigned int	uid_t;
typedef	unsigned int	gid_t;
#endif

typedef int pid_t;
#ifndef __CYGWIN__
typedef	long key_t;
#endif
typedef _ssize_t ssize_t;

typedef	char *	addr_t;
typedef int mode_t;

typedef unsigned int nlink_t;

#undef __MS_types__
#undef _ST_INT32

/* The following are actually standard POSIX 1003.1b-1993 threads, mutexes,
   condition variables, and keys.  But since RTEMS is currently the only
   newlib user of these, the ifdef is just on RTEMS. */

#if defined(__rtems__) || defined(__CYGWIN__)

#ifndef __clockid_t_defined
typedef _CLOCKID_T_ clockid_t;
#define __clockid_t_defined
#endif

#ifndef __timer_t_defined
typedef _TIMER_T_ timer_t;
#define __timer_t_defined
#endif

#if defined(__CYGWIN__) || defined(__rtems__)
typedef long useconds_t;
#endif

#include <sys/features.h>


/* Cygwin will probably never have full posix compliance due to little things
 * like an inability to set the stackaddress. Cygwin is also using void *  
 * pointers rather than structs to ensure maximum binary compatability with
 * previous releases.
 * This means that we don't use the types defined here, but rather in
 * <cygwin/types.h>
 */
#if defined(_POSIX_THREADS) && !defined(__CYGWIN__)

#include <sys/sched.h>

/*
 *  2.5 Primitive System Data Types,  P1003.1c/D10, p. 19.
 */

typedef __uint32_t pthread_t;            /* identify a thread */

/* P1003.1c/D10, p. 118-119 */
#define PTHREAD_SCOPE_PROCESS 0
#define PTHREAD_SCOPE_SYSTEM  1

/* P1003.1c/D10, p. 111 */
#define PTHREAD_INHERIT_SCHED  1      /* scheduling policy and associated */
                                      /*   attributes are inherited from */
                                      /*   the calling thread. */
#define PTHREAD_EXPLICIT_SCHED 2      /* set from provided attribute object */

/* P1003.1c/D10, p. 141 */
#define PTHREAD_CREATE_DETACHED 0
#define PTHREAD_CREATE_JOINABLE  1

typedef struct {
  int is_initialized;
  void *stackaddr;
  int stacksize;
  int contentionscope;
  int inheritsched;
  int schedpolicy;
  struct sched_param schedparam;

  /* P1003.4b/D8, p. 54 adds cputime_clock_allowed attribute.  */
#if defined(_POSIX_THREAD_CPUTIME)
  int  cputime_clock_allowed;  /* see time.h */
#endif
  int  detachstate;

} pthread_attr_t;

#if defined(_POSIX_THREAD_PROCESS_SHARED)
/* NOTE: P1003.1c/D10, p. 81 defines following values for process_shared.  */

#define PTHREAD_PROCESS_PRIVATE 0 /* visible within only the creating process */
#define PTHREAD_PROCESS_SHARED  1 /* visible too all processes with access to */
                                  /*   the memory where the resource is */
                                  /*   located */
#endif

#if defined(_POSIX_THREAD_PRIO_PROTECT)
/* Mutexes */

/* Values for blocking protocol. */

#define PTHREAD_PRIO_NONE    0
#define PTHREAD_PRIO_INHERIT 1
#define PTHREAD_PRIO_PROTECT 2
#endif

typedef __uint32_t pthread_mutex_t;      /* identify a mutex */

typedef struct {
  int   is_initialized;
#if defined(_POSIX_THREAD_PROCESS_SHARED)
  int   process_shared;  /* allow mutex to be shared amongst processes */
#endif
#if defined(_POSIX_THREAD_PRIO_PROTECT)
  int   prio_ceiling;
  int   protocol;
#endif
  int   recursive;
} pthread_mutexattr_t;

/* Condition Variables */

typedef __uint32_t pthread_cond_t;       /* identify a condition variable */

typedef struct {
  int   is_initialized;
#if defined(_POSIX_THREAD_PROCESS_SHARED)
  int   process_shared;       /* allow this to be shared amongst processes */
#endif
} pthread_condattr_t;         /* a condition attribute object */

/* Keys */

typedef __uint32_t pthread_key_t;        /* thread-specific data keys */

typedef struct {
  int   is_initialized;  /* is this structure initialized? */
  int   init_executed;   /* has the initialization routine been run? */
} pthread_once_t;       /* dynamic package initialization */
#else
#if defined (__CYGWIN__)
#include <cygwin/types.h>
#endif
#endif /* defined(_POSIX_THREADS) */

#endif  /* defined(__rtems__) */

#if defined(__toppers__)
#include <t_pthreadtypes.h>
#endif

#endif  /* !__need_inttypes */

#undef __need_inttypes

#endif	/* _SYS_TYPES_H */
