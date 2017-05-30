## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = cygnus

INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

noinst_LIBRARIES = lib.a

# Generate assembler files for each syscall wrapper
# The numeric suffix is the number of arguments, which ultimately drives
# which flavor of SYSCALL1(), SYSCALL2(), etc. to use in the .S file.
TRAPS = \
  _exit.1 \
  access.2 \
  accept.3 \
  alarm.1 \
  bind.3 \
  brk.1 \
  chdir.1 \
  chmod.2 \
  chown.3 \
  chroot.1 \
  close.1 \
  connect.3 \
  dup.1 \
  dup2.2 \
  fchmod.2 \
  fchown.3 \
  fcntl.3 \
  fdatasync.1 \
  fstat.2 \
  fsync.1 \
  ftruncate.2 \
  get_mempolicy.5 \
  getcwd.2 \
  getegid.0 \
  geteuid.0 \
  getgid.0 \
  getgroups.2 \
  getitimer.2 \
  getpeername.3 \
  getpgid.0 \
  getpgrp.0 \
  getpid.0 \
  getppid.0 \
  getsid.0 \
  getsockname.3 \
  getsockopt.5 \
  gettimeofday.2 \
  getuid.0 \
  ioctl.3 \
  kill.2 \
  lchown.3 \
  link.2 \
  listen.2 \
  lseek.3 \
  mbind.6 \
  mprotect.3 \
  mremap.5 \
  msync.3 \
  munmap.6 \
  nanosleep.2 \
  nice.1 \
  open.3 \
  pause.0 \
  pipe.1 \
  poll.3 \
  ptrace.4 \
  read.3 \
  readlink.3 \
  recv.4 \
  recvfrom.6 \
  recvmsg.3 \
  rmdir.1 \
  sched_setaffinity.3 \
  sched_yield.0 \
  select.5 \
  send.4 \
  sendmsg.3 \
  sendto.6 \
  set_mempolicy.3 \
  setegid.1 \
  seteuid.1 \
  setgid.1 \
  setgroups.2 \
  setitimer.3 \
  setpgid.2 \
  setpgrp.0 \
  setregid.2 \
  setreuid.2 \
  setsid.0 \
  setsockopt.5 \
  settimeofday.2 \
  setuid.1 \
  shutdown.2 \
  socket.3 \
  socketpair.4 \
  stat.3 \
  symlink.2 \
  times.1 \
  truncate.2 \
  ulimit.2 \
  unlink.1 \
  utimes.2 \
  vfork.0 \
  vhangup.0 \
  waitpid.3 \
  write.3 \

TRAPS_OBJ = $(addsuffix _r.o,$(basename $(TRAPS)))
TRAPS_SRC = $(addsuffix _r.S,$(basename $(TRAPS)))

define apps_lib_newlib__trap

$(basename $(1))_r.o: $(basename $(1))_r.S trap.S
$(basename $(1))_r.S:
	echo '#include "trap.S"' > $$@.tmp && \
	echo 'SYSCALL$(patsubst .%,%,$(suffix $(1)))('$(basename $(1))')' >> $$@.tmp && \
	mv $$@.tmp $$@

endef

$(foreach trap,$(TRAPS),$(eval $(call apps_lib_newlib__trap, $(trap))))

sched_getcpu.o: ../tilepro/trap.S
	$(CC) -c -o $@ -DSYSCALL=getcpu -DL_getcpu -DNARGS=0 $<

TRAP_OBJECTS += sched_getcpu.o

lib_a_SOURCES = __syscall_error.S \
  brk.c creat.c ctermid.c fork.c getcontext.S getlogin.c \
  getpagesize.c getreent.S lseek.c makecontext.c mmap.c mmap64.c prdwr.c \
  sched_getaffinity.c select.c setcontext.S sigaction.c signal.c \
  sigpending.c sigprocmask.c sigsuspend.c sleep.c swapcontext.S syscall.S \
  sysconf.c tcpgrp.c wait.c $(TRAPS_SRC)

all: crt0.o crti.o crtn.o

ACLOCAL_AMFLAGS = -I ../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
