/* Trivial "sys/ioctl.h". */

#ifndef SYS_IOCTL_H
#define SYS_IOCTL_H 1

#ifdef __cplusplus
extern "C" {
#endif

extern int ioctl(int fd, unsigned long request, ...);

#ifdef __cplusplus
}
#endif

#endif /* SYS_IOCTL_H */
