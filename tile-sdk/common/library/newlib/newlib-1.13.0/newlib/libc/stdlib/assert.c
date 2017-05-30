/*
FUNCTION
<<assert>>---Macro for Debugging Diagnostics

INDEX
	assert

ANSI_SYNOPSIS
	#include <assert.h>
	void assert(int <[expression]>);

TRAD_SYNOPSIS
	#include <assert.h>
	assert(<[expression]>)
	int <[expression]>;

DESCRIPTION
	Use this macro to embed debuggging diagnostic statements in
	your programs.  The argument <[expression]> should be an
	expression which evaluates to true (nonzero) when your program
	is working as you intended.

	When <[expression]> evaluates to false (zero), <<assert>>
	calls <<abort>>, after first printing a message showing what
	failed and where:

. Assertion failed: <[expression]>, file <[filename]>, line <[lineno]>

	The macro is defined to permit you to turn off all uses of
	<<assert>> at compile time by defining <<NDEBUG>> as a
	preprocessor variable.   If you do this, the <<assert>> macro
	expands to

. (void(0))

RETURNS
	<<assert>> does not return a value.

PORTABILITY
	The <<assert>> macro is required by ANSI, as is the behavior
	when <<NDEBUG>> is defined.

Supporting OS subroutines required (only if enabled): <<close>>, <<fstat>>,
<<getpid>>, <<isatty>>, <<kill>>, <<lseek>>, <<read>>, <<sbrk>>, <<write>>.
*/

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void
_DEFUN (__assert, (msg_str),
	const char *msg_str)
{
  /* To save code size our input arguments are packed together as
   * one string:
   *
   * "failed_expr\0file\0line"
   */
  const char *failed_expr = msg_str;
  size_t failed_expr_len = strlen(failed_expr);
  const char *file = failed_expr + failed_expr_len + 1;
  size_t file_len = strlen(file);
  const char *line = file + file_len + 1;
  size_t line_len = strlen(line);

  /* use write() to make it safe to call assert() from inside malloc, */
  /* whereas if we use fputs() we might circle back into malloc. */
  const int stderr_fd = 2;
#define write_constant(fd, str) write(fd, str, sizeof(str)-1)
  write_constant(stderr_fd, "assertion \"");
  write(stderr_fd, failed_expr, failed_expr_len);
  write_constant(stderr_fd, "\" failed: file \"");
  write(stderr_fd, file, file_len);
  write_constant(stderr_fd, "\", line ");
  write(stderr_fd, line, line_len);
  write_constant(stderr_fd, "\n");

  abort();
  /* NOTREACHED */
}
