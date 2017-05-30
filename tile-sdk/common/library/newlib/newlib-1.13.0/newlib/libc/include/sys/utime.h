#ifndef _SYS_UTIME_H
#define _SYS_UTIME_H

/* This is a dummy <sys/utime.h> file, not customized for any
   particular system.  If there is a utime.h in libc/sys/SYSDIR/sys,
   it will override this one.  */

#ifdef __cplusplus
extern "C" {
#endif

#include <machine/types.h>

#ifndef __time_t_defined
typedef _TIME_T_ time_t;
#define __time_t_defined
#endif

struct utimbuf 
{
  time_t actime;
  time_t modtime; 
};

#ifdef __cplusplus
};
#endif

#endif /* _SYS_UTIME_H */
