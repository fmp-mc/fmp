#include <reent.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int
wctob (wint_t c)
{
  mbstate_t mbs;
  int retval = 0;
  char pwc;

  /* Put mbs in initial state. */
  memset (&mbs, '\0', sizeof (mbs));

  _REENT_CHECK_MISC(_REENT);

  retval = _wctomb_r (_REENT, &pwc, c, &mbs);

  if (c == EOF || retval != 1)
    return WEOF;
  else
    return (int)(unsigned char)pwc;
}