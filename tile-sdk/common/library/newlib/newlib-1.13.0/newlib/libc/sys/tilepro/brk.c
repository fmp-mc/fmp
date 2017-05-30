/* Provide the standard brk/sbrk API calls via the brk syscall.  */

#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/syscall.h>

#if 0
static void *current_brk;

int brk(void *new_brk)
{
  current_brk = (void *)syscall(SYS_brk, new_brk);
  if (current_brk < new_brk)
  {
    errno = -ENOMEM;
    return -1;
  }
  return 0;
}

void *sbrk(intptr_t increment)
{
  if (current_brk == NULL)
    brk(0);
  void *orig = current_brk;
  if (brk(current_brk + increment) != 0)
    return NULL;
  return orig;
}

/* The reent ptr is a myth on tile. */
void *_sbrk_r(struct _reent *reent_ptr, intptr_t increment)
{
  return sbrk(increment);
}
#endif

