/* Call Linux's rt_sigsuspend() syscall.   */

#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>

int sigsuspend(const sigset_t *set)
{
  return syscall(SYS_rt_sigsuspend, set, sizeof(sigset_t));
}
