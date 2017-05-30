#ifndef _IEEE_FP_H_
#define _IEEE_FP_H_

#include "_ansi.h"

#include <machine/ieeefp.h>


int _EXFUN(isnan, (double));
int _EXFUN(isinf, (double));
int _EXFUN(finite, (double));



int _EXFUN(isnanf, (float));
int _EXFUN(isinff, (float));
int _EXFUN(finitef, (float));

#define __IEEE_DBL_EXPBIAS 1023
#define __IEEE_FLT_EXPBIAS 127

#define __IEEE_DBL_EXPLEN 11
#define __IEEE_FLT_EXPLEN 8


#define __IEEE_DBL_FRACLEN (64 - (__IEEE_DBL_EXPLEN + 1))
#define __IEEE_FLT_FRACLEN (32 - (__IEEE_FLT_EXPLEN + 1))

#define __IEEE_DBL_MAXPOWTWO	((double)(1L << 32 - 2) * (1L << (32-11) - 32 + 1))
#define __IEEE_FLT_MAXPOWTWO	((float)(1L << (32-8) - 1))

#define __IEEE_DBL_NAN_EXP 0x7ff
#define __IEEE_FLT_NAN_EXP 0xff


#define isnanf(x) (((*(long *)&(x) & 0x7f800000L)==0x7f800000L) && \
		   ((*(long *)&(x) & 0x007fffffL)!=0000000000L))

#define isinff(x) (((*(long *)&(x) & 0x7f800000L)==0x7f800000L) && \
		   ((*(long *)&(x) & 0x007fffffL)==0000000000L))

#define finitef(x) (((*(long *)&(x) & 0x7f800000L)!=0x7f800000L))

#endif /* _IEEE_FP_H_ */
