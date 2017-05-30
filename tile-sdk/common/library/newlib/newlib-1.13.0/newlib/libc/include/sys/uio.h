#ifndef _SYS_UIO_H
#define _SYS_UIO_H

#include <sys/types.h>

struct iovec
{
  void   *iov_base;
  size_t  iov_len;
};

/*
 * Newlib does not currently support readv and writev, so their prototypes
 * are not included here.
 */

#endif /* _SYS_UIO_H */
