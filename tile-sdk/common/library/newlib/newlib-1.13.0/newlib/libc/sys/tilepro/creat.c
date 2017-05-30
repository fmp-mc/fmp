/* creat() "system call"  */

#include <fcntl.h>

int
_DEFUN(creat, (path, mode), 
       const char *path _AND 
       mode_t mode)
{
  return open (path, O_WRONLY | O_CREAT | O_TRUNC, mode);
}
