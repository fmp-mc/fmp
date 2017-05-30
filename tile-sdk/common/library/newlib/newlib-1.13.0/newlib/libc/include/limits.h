#ifndef _LIBC_LIMITS_H_
# define _LIBC_LIMITS_H_	1

/* The libc environment provides a couple of values, then we defer 
   to the compiler limits.h for the rest. */
#define MB_LEN_MAX 16

/* This one is provided in <linux/limits.h> normally */
#define PATH_MAX 4096

#endif

#ifndef _GCC_LIMITS_H_
#include_next <limits.h>
#endif
