# Generated automatically from Makefile.in by configure.
# Makefile.in generated automatically by automake 1.4-p6 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999, 2001 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


SHELL = /bin/sh

srcdir = /home/liyixiao/manycore/fmp-tilegx/fmp/tile-sdk/common/library/newlib/newlib-1.13.0/build/obj/../../newlib/libc/sys/tilegx
top_srcdir = /home/liyixiao/manycore/fmp-tilegx/fmp/tile-sdk/common/library/newlib/newlib-1.13.0/build/obj/../../newlib/libc/sys/tilegx
VPATH = /home/liyixiao/manycore/fmp-tilegx/fmp/tile-sdk/common/library/newlib/newlib-1.13.0/build/obj/../../newlib/libc/sys/tilegx
prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/newlib
pkglibdir = $(libdir)/newlib
pkgincludedir = $(includedir)/newlib

top_builddir = .

ACLOCAL = /home/liyixiao/manycore/fmp-tilegx/fmp/tile-sdk/common/library/newlib/newlib-1.13.0/missing aclocal-1.4
AUTOCONF = autoconf
AUTOMAKE = /home/liyixiao/manycore/fmp-tilegx/fmp/tile-sdk/common/library/newlib/newlib-1.13.0/missing automake-1.4
AUTOHEADER = autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL_PROGRAM}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_alias = tilegx-elf64
build_triplet = tilegx-unknown-linux-gnu
host_alias = tilegx-elf64
host_triplet = tilegx-unknown-linux-gnu
target_alias = tilegx-elf64
target_triplet = tilegx-unknown-linux-gnu
AR = ar
AS = as
CC = /opt/tilera/TileraMDE-4.3.4.193953/tilegx/bin/tile-gcc
CPP = @CPP@
EXEEXT = 
LDFLAGS = 
MAINT = #
MAKEINFO = makeinfo
NEWLIB_CFLAGS =  -Os -DREENTRANT_SYSCALLS_PROVIDED -D__DYNAMIC_REENT__ -D_COMPILING_NEWLIB -DHAVE_GETTIMEOFDAY -DHAVE_FCNTL -DSIGNAL_PROVIDED -fno-builtin
OBJEXT = o
PACKAGE = newlib
RANLIB = ranlib
VERSION = 1.13.0
aext = a
libm_machine_dir = 
machine_dir = tilegx
newlib_basedir = /home/liyixiao/manycore/fmp-tilegx/fmp/tile-sdk/common/library/newlib/newlib-1.13.0/build/obj/../../newlib/libc/sys/tilegx/../../..
oext = o
sys_dir = tilegx

AUTOMAKE_OPTIONS = cygnus

INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

noinst_LIBRARIES = lib.a

# Generate assembler files for each syscall wrapper
# The numeric suffix is the number of arguments, which ultimately drives
# which flavor of SYSCALL1(), SYSCALL2(), etc. to use in the .S file.
TRAPS = \
  _exit.1 \
  accept.3 \
  access.2 \
  bind.3 \
  chdir.1 \
  chmod.2 \
  chown.3 \
  chroot.1 \
  close.1 \
  connect.3 \
  dup.1 \
  dup2.2 \
  execve.3 \
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
  mbind.6 \
  mprotect.3 \
  mremap.5 \
  msync.3 \
  munmap.6 \
  nanosleep.2 \
  open.3 \
  pipe.1 \
  ptrace.4 \
  read.3 \
  readlink.3 \
  recv.4 \
  recvfrom.6 \
  recvmsg.3 \
  rmdir.1 \
  sched_setaffinity.3 \
  sched_yield.0 \
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
  sigaltstack.2 \
  socket.3 \
  socketpair.4 \
  stat.3 \
  symlink.2 \
  times.1 \
  truncate.2 \
  unlink.1 \
  vfork.0 \
  vhangup.0 \
  waitpid.3 \
  write.3 \

TRAP_OBJECTS = $(addsuffix _r.o,$(basename $(TRAPS)))

define apps_lib_newlib__trap

$(basename $(1))_r.o: ../tilepro/trap.S
	$(CC) -c -o $$@ -DSYSCALL=$(basename $(1)) -DL_$(basename $(1)) \
	  -DNARGS=$(patsubst .%,%,$(suffix $(1))) $$<

endef

$(foreach trap,$(TRAPS),$(eval $(call apps_lib_newlib__trap, $(trap))))

SHARED_TILE_SOURCES := __syscall_error.S \
  brk.c creat.c ctermid.c fork.c getcontext.S getlogin.c \
  getpagesize.c getreent.S lseek.c makecontext.c mmap.c mmap64.c prdwr.c \
  sched_getaffinity.c select.c setcontext.S sigaction.c signal.c \
  sigpending.c sigprocmask.c sigsuspend.c sleep.c swapcontext.S syscall.S \
  sysconf.c tcpgrp.c wait.c

SHARED_TILE_OBJECTS := $(addsuffix .o, $(basename $(SHARED_TILE_SOURCES)))
SHARED_TILE_SOURCES := $(addprefix ../tilepro/, $(SHARED_TILE_SOURCES))

lib_a_SOURCES = $(SHARED_TILE_SOURCES) $(TRAP_SOURCES)

ACLOCAL_AMFLAGS = -I ../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
mkinstalldirs = $(SHELL) $(top_srcdir)/../../../../mkinstalldirs
CONFIG_CLEAN_FILES = 
LIBRARIES =  $(noinst_LIBRARIES)

DEFS =  -DPACKAGE=\"newlib\" -DVERSION=\"1.13.0\"  -I. -I$(srcdir) 
CPPFLAGS = 
LIBS = 
lib_a_OBJECTS = $(SHARED_TILE_OBJECTS) $(TRAP_OBJECTS) $(ATOMIC_OBJECTS)
CFLAGS = -mnewlib -g -ffunction-sections -fno-strict-aliasing -std=gnu99 -Wall -Werror -Wno-uninitialized -Wno-parentheses -I/opt/tilera/TileraMDE-4.3.4.193953/tilegx/lib/gcc/bin/../lib/gcc/tilegx-redhat-linux/4.4.7/include
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(LDFLAGS) -o $@
DIST_COMMON =  Makefile.am Makefile.in aclocal.m4 configure configure.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = gtar
GZIP_ENV = --best
SOURCES = $(lib_a_SOURCES)
OBJECTS = $(lib_a_OBJECTS)

all: all-redirect
.SUFFIXES:
.SUFFIXES: .S .c .o .s
$(srcdir)/Makefile.in: # Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --cygnus Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$@ CONFIG_HEADERS= $(SHELL) ./config.status

$(ACLOCAL_M4): # configure.in  \
		../../../acinclude.m4 ../../../aclocal.m4 \
		../../../libtool.m4
	cd $(srcdir) && $(ACLOCAL) $(ACLOCAL_AMFLAGS)

config.status: $(srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	$(SHELL) ./config.status --recheck
$(srcdir)/configure: #$(srcdir)/configure.in $(ACLOCAL_M4) $(CONFIGURE_DEPENDENCIES)
	cd $(srcdir) && $(AUTOCONF)

mostlyclean-noinstLIBRARIES:

clean-noinstLIBRARIES:
	-test -z "$(noinst_LIBRARIES)" || rm -f $(noinst_LIBRARIES)

distclean-noinstLIBRARIES:

maintainer-clean-noinstLIBRARIES:

.c.o:
	$(COMPILE) -c $<

.s.o:
	$(COMPILE) -c $<

.S.o:
	$(COMPILE) -c $<

mostlyclean-compile:
	-rm -f *.o core *.core

clean-compile:

distclean-compile:
	-rm -f *.tab.c

maintainer-clean-compile:

lib.a: $(lib_a_OBJECTS) $(lib_a_DEPENDENCIES)
	-rm -f lib.a
	$(AR) cru lib.a $(lib_a_OBJECTS) $(lib_a_LIBADD)
	$(RANLIB) lib.a

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP)
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	here=`pwd` && cd $(srcdir) \
	  && mkid -f$$here/ID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || (cd $(srcdir) && etags $(ETAGS_ARGS) $$tags  $$unique $(LISP) -o $$here/TAGS)

mostlyclean-tags:

clean-tags:

distclean-tags:
	-rm -f TAGS ID

maintainer-clean-tags:

distdir = $(PACKAGE)-$(VERSION)
top_distdir = $(distdir)

# This target untars the dist file and tries a VPATH configuration.  Then
# it guarantees that the distribution is self-contained by making another
# tarfile.
distcheck: dist
	-rm -rf $(distdir)
	GZIP=$(GZIP_ENV) $(TAR) zxf $(distdir).tar.gz
	mkdir $(distdir)/=build
	mkdir $(distdir)/=inst
	dc_install_base=`cd $(distdir)/=inst && pwd`; \
	cd $(distdir)/=build \
	  && ../configure --srcdir=.. --prefix=$$dc_install_base \
	  && $(MAKE) $(AM_MAKEFLAGS) \
	  && $(MAKE) $(AM_MAKEFLAGS) dvi \
	  && $(MAKE) $(AM_MAKEFLAGS) check \
	  && $(MAKE) $(AM_MAKEFLAGS) install \
	  && $(MAKE) $(AM_MAKEFLAGS) installcheck \
	  && $(MAKE) $(AM_MAKEFLAGS) dist
	-rm -rf $(distdir)
	@banner="$(distdir).tar.gz is ready for distribution"; \
	dashes=`echo "$$banner" | sed s/./=/g`; \
	echo "$$dashes"; \
	echo "$$banner"; \
	echo "$$dashes"
dist: distdir
	-chmod -R a+r $(distdir)
	GZIP=$(GZIP_ENV) $(TAR) chozf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)
dist-all: distdir
	-chmod -R a+r $(distdir)
	GZIP=$(GZIP_ENV) $(TAR) chozf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)
distdir: $(DISTFILES)
	-rm -rf $(distdir)
	mkdir $(distdir)
	-chmod 777 $(distdir)
	@for file in $(DISTFILES); do \
	  if test -f $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    cp -pr $$d/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done
info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am:
check: check-am
installcheck-am:
installcheck: installcheck-am
install-info-am: 
install-info: install-info-am
install-exec-am:
install-exec: install-exec-am

install-data-am:
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am:
uninstall: uninstall-am
all-am: Makefile $(LIBRARIES)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-noinstLIBRARIES mostlyclean-compile \
		mostlyclean-tags mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-noinstLIBRARIES clean-compile clean-tags clean-generic \
		mostlyclean-am

clean: clean-am

distclean-am:  distclean-noinstLIBRARIES distclean-compile \
		distclean-tags distclean-generic clean-am

distclean: distclean-am
	-rm -f config.status

maintainer-clean-am:  maintainer-clean-noinstLIBRARIES \
		maintainer-clean-compile maintainer-clean-tags \
		maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am
	-rm -f config.status

.PHONY: mostlyclean-noinstLIBRARIES distclean-noinstLIBRARIES \
clean-noinstLIBRARIES maintainer-clean-noinstLIBRARIES \
mostlyclean-compile distclean-compile clean-compile \
maintainer-clean-compile tags mostlyclean-tags distclean-tags \
clean-tags maintainer-clean-tags distdir info-am info dvi-am dvi check \
check-am installcheck-am installcheck install-info-am install-info \
install-exec-am install-exec install-data-am install-data install-am \
install uninstall-am uninstall all-redirect all-am all installdirs \
mostlyclean-generic distclean-generic clean-generic \
maintainer-clean-generic clean mostlyclean distclean maintainer-clean


all: crt0.o crti.o crtn.o

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:

doc:
	cat $(srcdir)/sys.tex >> $(TARGETDOC)
