/*
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
/* No user fns here.  Pesch 15apr92. */

#include <_ansi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include "local.h"

/* See if "fd" has dev/ino equal to the values in the STDIO_LBF_DEV_INO
   environment variable. */
static int is_lbf_fd(int fd)
{
  const char* env = getenv("STDIO_LBF_DEV_INO");
  if (env == NULL)
    return 0;

  char* end;
  unsigned long dev = strtoul(env, &end, 0);
  if (end == env || *end != ':')
    return 0;
  env = end + 1;
  unsigned long ino = strtoul(env, &end, 0);
  if (end == env || *end != '\0')
    return 0;
  struct stat s;
  if (fstat(fd, &s) != 0)
    return 0;
  return (ino == (unsigned long) s.st_ino &&
          dev == (unsigned long) s.st_dev);
}

/*
 * Allocate a file buffer, or switch to unbuffered I/O.
 * Per the ANSI C standard, ALL tty devices default to line buffered.
 *
 * As a side effect, we set __SOPT or __SNPT (en/dis-able fseek
 * optimization) right after the _fstat() that finds the buffer size.
 */

_VOID
_DEFUN(__smakebuf, (fp),
       register FILE *fp)
{
  register size_t size, couldbetty;
  register _PTR p;
  struct stat st;

  if (fp->_flags & __SNBF)
    {
      fp->_bf._base = fp->_p = fp->_nbuf;
      fp->_bf._size = 1;
      return;
    }
#ifdef __USE_INTERNAL_STAT64
  if (fp->_file < 0 || _fstat64_r (_REENT, fp->_file, &st) < 0)
#else
  if (fp->_file < 0 || _fstat_r (_REENT, fp->_file, &st) < 0)
#endif
    {
      couldbetty = 0;
      size = BUFSIZ;
      /* do not try to optimise fseek() */
      fp->_flags |= __SNPT;
    }
  else
    {
      couldbetty = (st.st_mode & S_IFMT) == S_IFCHR;
#ifdef HAVE_BLKSIZE
      size = st.st_blksize <= 0 ? BUFSIZ : st.st_blksize;
#else
      size = BUFSIZ;
#endif
      /*
       * Optimize fseek() only if it is a regular file.
       * (The test for __sseek is mainly paranoia.)
       */
      if ((st.st_mode & S_IFMT) == S_IFREG && fp->_seek == __sseek)
	{
	  fp->_flags |= __SOPT;
#ifdef HAVE_BLKSIZE
	  fp->_blksize = st.st_blksize;
#else
	  fp->_blksize = 1024;
#endif
	}
      else
	fp->_flags |= __SNPT;
    }
  if ((p = _malloc_r (_REENT, size)) == NULL)
    {
      fp->_flags |= __SNBF;
      fp->_bf._base = fp->_p = fp->_nbuf;
      fp->_bf._size = 1;
    }
  else
    {
      _REENT->__cleanup = _cleanup_r;
      fp->_flags |= __SMBF;
      fp->_bf._base = fp->_p = (unsigned char *) p;
      fp->_bf._size = size;
      if ((couldbetty && isatty (fp->_file)) || is_lbf_fd(fp->_file))
        fp->_flags |= __SLBF;
    }
}
