/* Call Linux's rt_sigaction() syscall.   */

#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>

int sigaction(int sig, const struct sigaction* act, struct sigaction* oact)
{
  return syscall(SYS_rt_sigaction, sig, act, oact, sizeof(sigset_t));
}
