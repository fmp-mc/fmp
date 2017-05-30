/*
FUNCTION
	<<isatty>>---report whether a given file descriptor is attached to a terminal

INDEX
	isatty

ANSI_SYNOPSIS
        #include <unistd.h>
	int isatty(int <[fd]>);

DESCRIPTION
<<isatty>> returns 1 if the given file descriptor references a
terminal, or 0 otherwise.  Within tile-sim's "magic-supervisor" mode,
we always assume that the initial file descriptors assigned to stdin,
stdout, and stderr reference a terminal.

PORTABILITY
<<isatty>> conforms to SVID and X/OPEN.

No supporting OS subroutines are required.  */

#include <sys/stat.h>

int
isatty(int fd)
{
  struct stat buf;

  if (fstat (fd, &buf) < 0)
    return 0;
  if (S_ISCHR (buf.st_mode))
    return 1;
  return 0;
}
