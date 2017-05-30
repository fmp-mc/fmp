/* Map select() to pselect6().   */

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <errno.h>

int select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
           struct timeval *timeout)
{
	struct timespec ts;
	if (timeout) {
		ts.tv_sec = timeout->tv_sec;
		ts.tv_nsec = timeout->tv_usec * 1000;
	}
	return syscall(SYS_pselect6, 6, n, readfds, writefds, exceptfds,
                       timeout ? &ts : NULL, NULL);
}
