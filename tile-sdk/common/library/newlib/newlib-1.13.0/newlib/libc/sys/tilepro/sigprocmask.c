/* Call Linux's rt_sigprocmask() syscall.   */

#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
  return syscall(SYS_rt_sigprocmask, how, set, oldset, sizeof(sigset_t));
}
