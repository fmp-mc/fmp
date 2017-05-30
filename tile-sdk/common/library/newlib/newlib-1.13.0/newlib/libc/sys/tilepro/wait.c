/* Express wait in terms of waitpid().  */

#include <sys/types.h>
#include <sys/wait.h>
#include <reent.h>

extern pid_t _waitpid_r (struct _reent*, pid_t, int *, int);
extern pid_t _waitpid (pid_t, int *, int);

pid_t _wait_r(struct _reent* r, int *status)
{
  return _waitpid_r(r, -1, status, 0);
}

pid_t _wait(int *status)
{
  return _waitpid(-1, status, 0);
}

extern __typeof(_wait) wait __attribute__ ((weak, alias("_wait")));
