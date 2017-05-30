/* Implement nice() via setpriority().  */

#include <sys/resource.h>
#include <unistd.h>

int nice(int inc)
{
	int prio = getpriority(PRIO_PROCESS, 0);
	return setpriority(PRIO_PROCESS, 0, prio + inc);
}
