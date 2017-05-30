/* Implement pause() via sigsuspend().  */

#include <signal.h>
#include <unistd.h>

int pause(void)
{
  sigset_t oset;
  if (sigprocmask(SIG_BLOCK, NULL, &oset) < 0)
    return -1;
  return sigsuspend(&oset);
}
