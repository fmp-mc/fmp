#ifndef _NUMAIF_H_
#define	_NUMAIF_H_

/* These values should match <linux/mempolicy.h>. */

#define MPOL_DEFAULT	0
#define MPOL_PREFERRED	1
#define MPOL_BIND	2
#define MPOL_INTERLEAVE	3
#define MPOL_MAX	4

#define MPOL_MF_STRICT	1
#define MPOL_MF_MOVE	2
#define MPOL_MF_MOVE_ALL 4

long mbind(void *start, unsigned long len, int mode,
           const unsigned long *nmask, unsigned long maxnode, unsigned flags);
long get_mempolicy(int *mode, const unsigned long *nmask,
                   unsigned long maxnode, void *addr, int flags);
long set_mempolicy(int mode, const unsigned long *nmask,
                   unsigned long maxnode);

#endif
