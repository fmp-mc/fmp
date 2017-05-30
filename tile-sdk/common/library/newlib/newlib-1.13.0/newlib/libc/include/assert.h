/*
	assert.h
*/

#ifdef __cplusplus
extern "C" {
#endif

#include "_ansi.h"

#undef assert

#ifdef NDEBUG           /* required by ANSI standard */
#define assert(p)  	((void)0)
#else

/* Use preprocessor magic turn error message, file and line number
 * into a single string constant separated by \0 to save space.
 */
#define __assert2(e, e_str, file, line) \
  (__builtin_expect((e) != 0, 1) \
   ? (void)0 \
   : __assert(e_str "\0" file "\0" #line))
#define __assert1(e, e_str, file, line) __assert2(e, e_str, file, line)

#define assert(e) __assert1(e, #e, __FILE__, __LINE__)

#endif /* NDEBUG */

void _EXFUN(__assert,(const char *) _ATTRIBUTE((noreturn)));

#ifdef __cplusplus
}
#endif
