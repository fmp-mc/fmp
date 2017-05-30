/*
FUNCTION
<<flockfile>>, <<funlockfile>>, <<ftrylockfile>>---lock and unlock a stream

INDEX
	flockfile
INDEX
	funlockfile
INDEX
	ftrylockfile

ANSI_SYNOPSIS
	#include <stdio.h>
        void flockfile(FILE *);
        int ftrylockfile(FILE *);
        void funlockfile(FILE *);

DESCRIPTION
<<flockfile>> locks a stream so that only one thread can write to it.
<<funlockfile>> unlocks a locked stream.  <<ftrylockfile>> attempts
to lock a stream and returns zero for success and non-zero for failure.
Most stdio routines lock the file descriptor internally; these routines
are provided so that users can group together a sequence of I/O operations 
so that another thread can't interleave with it, or to increase efficiency,
in which case the user can use <<getc_unlocked>> or <<putc_unlocked>> 
instead of the usual locking <<getc>> and <<putc>> routines.

PORTABILITY
<<flockfile>> et al conform to POSIX.1.
*/

#include <stdio.h>

// These functions appear to be missing from the normal libc,
// although <stdio.h> claims they are ANSI.  

void
flockfile(FILE* f)
{
  _flockfile(f);
}

void
funlockfile(FILE* f)
{
  _funlockfile(f);
}

int
ftrylockfile(FILE* f)
{
  return _ftrylockfile(f);
}
