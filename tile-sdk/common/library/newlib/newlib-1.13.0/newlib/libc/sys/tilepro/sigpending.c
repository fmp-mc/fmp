/* Call Linux's rt_sigpending() syscall.   */

#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>

int sigpending(sigset_t *set)
{
  return syscall(SYS_rt_sigpending, set, sizeof(sigset_t));
}

