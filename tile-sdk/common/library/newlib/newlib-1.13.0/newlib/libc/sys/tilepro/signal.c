/* Provide BSD-style signal() implementation.   */

#include <signal.h>

_sig_func_ptr signal(int sig, _sig_func_ptr func)
{
  struct sigaction oact, act = { .sa_handler = func };
  return (sigaction(sig, &act, &oact) < 0) ? SIG_ERR : oact.sa_handler;
}
