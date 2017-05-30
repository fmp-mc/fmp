/*
FUNCTION
	<<strtoul>>---string to unsigned long

INDEX
	strtoul
INDEX
	_strtoul_r

ANSI_SYNOPSIS
	#include <stdlib.h>
        unsigned long strtoul(const char *<[s]>, char **<[ptr]>,
                              int <[base]>);

        unsigned long _strtoul_r(void *<[reent]>, const char *<[s]>,
                              char **<[ptr]>, int <[base]>);

TRAD_SYNOPSIS
	#include <stdlib.h>
        unsigned long strtoul(<[s]>, <[ptr]>, <[base]>)
        char *<[s]>;
        char **<[ptr]>;
        int <[base]>;

        unsigned long _strtoul_r(<[reent]>, <[s]>, <[ptr]>, <[base]>)
	char *<[reent]>;
        char *<[s]>;
        char **<[ptr]>;
        int <[base]>;

DESCRIPTION
The function <<strtoul>> converts the string <<*<[s]>>> to
an <<unsigned long>>. First, it breaks down the string into three parts:
leading whitespace, which is ignored; a subject string consisting
of the digits meaningful in the radix specified by <[base]>
(for example, <<0>> through <<7>> if the value of <[base]> is 8);
and a trailing portion consisting of one or more unparseable characters,
which always includes the terminating null character. Then, it attempts
to convert the subject string into an unsigned long integer, and returns the
result.

If the value of <[base]> is zero, the subject string is expected to look
like a normal C integer constant (save that no optional sign is permitted):
a possible <<0x>> indicating hexadecimal radix, and a number.
If <[base]> is between 2 and 36, the expected form of the subject is a
sequence of digits (which may include letters, depending on the
base) representing an integer in the radix specified by <[base]>.
The letters <<a>>--<<z>> (or <<A>>--<<Z>>) are used as digits valued from
10 to 35. If <[base]> is 16, a leading <<0x>> is permitted.

The subject sequence is the longest initial sequence of the input
string that has the expected form, starting with the first
non-whitespace character.  If the string is empty or consists entirely
of whitespace, or if the first non-whitespace character is not a
permissible digit, the subject string is empty.

If the subject string is acceptable, and the value of <[base]> is zero,
<<strtoul>> attempts to determine the radix from the input string. A
string with a leading <<0x>> is treated as a hexadecimal value; a string with
a leading <<0>> and no <<x>> is treated as octal; all other strings are
treated as decimal. If <[base]> is between 2 and 36, it is used as the
conversion radix, as described above. Finally, a pointer to the first
character past the converted subject string is stored in <[ptr]>, if
<[ptr]> is not <<NULL>>.

If the subject string is empty (that is, if <<*>><[s]> does not start
with a substring in acceptable form), no conversion
is performed and the value of <[s]> is stored in <[ptr]> (if <[ptr]> is
not <<NULL>>).

The alternate function <<_strtoul_r>> is a reentrant version.  The
extra argument <[reent]> is a pointer to a reentrancy structure.


RETURNS
<<strtoul>> returns the converted value, if any. If no conversion was
made, <<0>> is returned.

<<strtoul>> returns <<ULONG_MAX>> if the magnitude of the converted
value is too large, and sets <<errno>> to <<ERANGE>>.

PORTABILITY
<<strtoul>> is ANSI.

<<strtoul>> requires no supporting OS subroutines.
*/

/*
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <_ansi.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <reent.h>

/*
 * Convert a string to an unsigned long integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
unsigned long
_DEFUN (_strtoul_r, (rptr, nptr, endptr, base),
	struct _reent *rptr _AND
	_CONST char *nptr _AND
	char **endptr _AND
	int base)
{
	register const char *s = nptr;
	register unsigned long acc;
	register int c;
	register unsigned long cutoff;
	register int neg = 0, any, cutlim;

	/*
	 * See strtol for comments as to the logic used.
	 */
	do {
		c = *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else if (c == '+')
		c = *s++;
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;

        /*
         * Avoid painfully slow calls to __umodsi3 and __udivsi3
         * on TILE by letting the compiler generate inline code.
         */
        switch (base)
        {
        case 8:
                cutoff = ULONG_MAX / 8;
                cutlim = ULONG_MAX % 8;
                break;
        case 10:
                cutoff = ULONG_MAX / 10;
                cutlim = ULONG_MAX % 10;
                break;
        case 16:
                cutoff = ULONG_MAX / 16;
                cutlim = ULONG_MAX % 16;
                break;
        default:
                cutoff = ULONG_MAX / base;
                cutlim = ULONG_MAX % base;
                break;
        }

	for (acc = 0, any = 0;; c = *s++) {
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
               if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0) {
		acc = ULONG_MAX;
		rptr->_errno = ERANGE;
	} else if (neg)
		acc = -acc;
	if (endptr != 0)
		*endptr = (char *) (any ? s - 1 : nptr);
	return (acc);
}

#ifndef _REENT_ONLY

unsigned long
_DEFUN (strtoul, (s, ptr, base),
	_CONST char *s _AND
	char **ptr _AND
	int base)
{
	return _strtoul_r (_REENT, s, ptr, base);
}

#endif