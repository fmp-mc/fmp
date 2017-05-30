/*
FUNCTION
	<<setjmp>>, <<longjmp>>---non-local jump support

INDEX
	setjmp
INDEX
	longjmp

ANSI_SYNOPSIS
	#include <setjmp.h>
        void longjmp(jmp_buf <[env]>, int <[val]>);
        int setjmp(jmp_buf <[env]>);

DESCRIPTION

<<setjmp>> sets up a location which can be returned to later.  The
specific location (including register and stack) is saved to the
specified jmp_buf <[env]>.

<<longjmp>> transfer control to the location described by the given
buffer, and provides a return <[val]> to use as the return value
from <<setjmp>>.  <<longjmp>> must pass a non-zero value to use
as the return value, or else 1 is returned.

RETURNS
<<setjmp>> returns zero if called directly, and non-zero if returning
from a <<longjmp>> that returned control to it.

PORTABILITY
<<longjmp>> and <<setjmp>> conform to POSIX.

No supporting OS subroutines are required.  */
