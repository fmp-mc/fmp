/*
FUNCTION
<<strsignal>>---return string describing a signal

INDEX
	strsignal

ANSI_SYNOPSIS
	#include <string.h>
	const char * strsignal(int <[sig]>);

DESCRIPTION
<<strsignal>> returns a string describing a particular signal.

RETURNS
For signals whose value is defined in <<<signal.h>>>, a pointer to
a constant string is returned.  Otherwise, a pointer to a static buffer
is returned, holding the string "Unknown signal <<n>>"; this pointer
is therefore not thread-safe, and should also not be held across
subsequent calls to <<strsignal>>.

PORTABILITY
This function is found on Linux, Solaris, and some other systems.

No supporting OS subroutines are required to link with <<strsignal>>.
*/

// We define a short list of normal signal names here.
// See <sys/signal.h> for the corresponding #defines.

#include <string.h>
#include <stdio.h>
#include <signal.h>

static const char* const signames[] = {
  "Signal 0",
  "Hangup",
  "Interrupt",
  "Quit",
  "Illegal instruction",
  "Trace/breakpoint trap",
  "Abort",
  "EMT trap",
  "Floating point exception",
  "Killed",
  "Bus error",
  "Segmentation fault",
  "Bad system call",
  "Broken pipe",
  "Alarm clock",
  "Terminated",
  "Urgent I/O condition",
  "Stopped (signal)",
  "Stopped",
  "Continued",
  "Child exited",
  "Stopped (tty input)",
  "Stopped (tty output)",
  "I/O possible",
  "CPU time limit exceeded",
  "File size limit exceeded",
  "Virtual timer expired",
  "Profiling timer expired",
  "Window changed",
  "Resource lost",
  "User defined signal 1",
  "User defined signal 2"
};

char* strsignal(int signo)
{
  if (signo >= 0 && signo <= SIGTERM)
    return (char*) signames[signo];
  static char buf[30];
  snprintf(buf, sizeof(buf), "Unknown signal %d", signo);
  return buf;
}
