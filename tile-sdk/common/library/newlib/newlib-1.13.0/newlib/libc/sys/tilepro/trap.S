/*
 * Copyright 2014 Tilera Corporation. All Rights Reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *   PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 *   DAMAGE. TILERA FURTHER DISCLAIMS ANY LIABILITY WHATSOEVER FOR
 *   INFRINGEMENT OF ANY INTELLECTUAL PROPERTY RIGHTS OF ANY THIRD PARTY.
 *
 * This provides an interface for the newlib system calls.  By
 * convention, we assume that we want to support an API where we pass
 * arguments to the kernel the same way they are passed to the libc
 * wrapper, namely starting in r0, and update errno via tp.
 *
 * However, newlib wants to pass a struct _reent* as the first
 * argument to its reentrant syscall wrappers, and it uses those
 * reentrant syscall wrappers from all over its source code, so to
 * match that we have to shift the arguments down one
 * (r1 -> r0, r2 -> r1, etc.).  We can do this
 * two at a time, and only for the arguments that are being passed, so
 * the cost isn't too high, and it keeps things uniform at the kernel
 * API level.  We just ignore the passed struct _reent anyway, since
 * it should always be referencing the "tp" register.
 */

#if 0 // don't use Linux syscall in TOPPERS/FMP kernel -- ertl-liyixiao

#define __ASSEMBLY__
#include <sys/syscall.h>
#include <sys/errno.h>
#include <arch/abi.h>
#include <fcntl.h>
#include <linux/sched.h>
#include <asm/signal.h>
#include "sysdep.h"

#ifdef __tilegx__
#define shri shrsi
#endif

#ifdef L__exit
#define SYS__exit SYS_exit
#endif

#ifdef L_access
#define SYSCALL_SETUP(x) \
	{ move r3, r2; move r2, r1 }; \
	{ move r1, r0; moveli r0, AT_FDCWD }; \
	moveli TREG_SYSCALL_NR_NAME, SYS_faccessat
#endif

#ifdef L_chmod
#define SYSCALL_SETUP(x) \
	{ move r2, r1; move r1, r0 }; \
	{ moveli r0, AT_FDCWD; moveli TREG_SYSCALL_NR_NAME, SYS_fchmodat }
#endif

#ifdef L_chown
#define SYSCALL_SETUP(x) \
        { move r4, zero; move r3, r2 }; \
	{ move r2, r1; move r1, r0 }; \
	{ moveli r0, AT_FDCWD; moveli TREG_SYSCALL_NR_NAME, SYS_fchownat }
#endif

#ifdef L_dup2
#define SYSCALL_SETUP(x) \
	{ move r2, zero; moveli TREG_SYSCALL_NR_NAME, SYS_dup3 }
#endif

#ifdef L_fcntl
#ifndef SYS_fcntl
/* Note: this will not work as expected with the locking-related fcntls. */
#define SYS_fcntl SYS_fcntl64
#endif
#endif

#ifdef L_fstat
#ifndef SYS_fstat
#define SYS_fstat SYS_fstat64
#endif
#endif

#ifdef L_ftruncate
#ifndef __LP64__
#ifndef SYS_ftruncate
#define SYS_ftruncate SYS_ftruncate64
#endif
#define SYSCALL_SETUP(x) \
	{ move r2, r1; move r3, r1 }; \
	{ shri r3, r3, 31; moveli TREG_SYSCALL_NR_NAME, SYS_ftruncate }
#endif
#endif

#ifdef L_getpgrp
#define SYSCALL_SETUP(x) \
	{ move r0, zero; moveli TREG_SYSCALL_NR_NAME, SYS_getpgid }
#endif

#ifdef L_lchown
#define SYSCALL_SETUP(x) \
        { moveli r4, AT_SYMLINK_NOFOLLOW; move r3, r2 }; \
        { move r2, r1; move r1, r0 }; \
	{ moveli r0, AT_FDCWD; moveli TREG_SYSCALL_NR_NAME, SYS_fchownat }
#endif

#ifdef L_link
#define SYSCALL_SETUP(x) \
        { move r4, zero; move r3, r1 }; \
        { moveli r2, AT_FDCWD; move r1, r0 }; \
        { moveli r0, AT_FDCWD; moveli TREG_SYSCALL_NR_NAME, SYS_linkat }
#endif

#ifdef L_open
#define SYSCALL_SETUP(x) \
	{ move r3, r2; move r2, r1 }; \
	{ move r1, r0; moveli r0, AT_FDCWD }; \
	moveli TREG_SYSCALL_NR_NAME, SYS_openat
#endif

#ifdef L_pipe
#define SYSCALL_SETUP(x) \
	{ move r1, zero; moveli TREG_SYSCALL_NR_NAME, SYS_pipe2 }
#endif

#ifdef L_readlink
#define SYSCALL_SETUP(x) \
	{ move r3, r2; move r2, r1 }; \
	{ move r1, r0; moveli r0, AT_FDCWD }; \
	moveli TREG_SYSCALL_NR_NAME, SYS_readlinkat
#endif

#ifdef L_recv
#define SYSCALL_SETUP(x) \
        { move r4, zero; move r5, zero }; \
	moveli TREG_SYSCALL_NR_NAME, SYS_recvfrom
#endif

#ifdef L_rmdir
#define SYSCALL_SETUP(x) \
        { moveli r2, AT_REMOVEDIR; move r1, r0 }; \
        { moveli r0, AT_FDCWD; moveli TREG_SYSCALL_NR_NAME, SYS_unlinkat }
#endif

#ifdef L_send
#define SYSCALL_SETUP(x) \
        { move r4, zero; move r5, zero }; \
	moveli TREG_SYSCALL_NR_NAME, SYS_sendto
#endif

#ifdef L_setegid
#define SYSCALL_SETUP(x) \
        { movei r2, -1; move r1, r0 }; \
        { movei r0, -1; moveli TREG_SYSCALL_NR_NAME, SYS_setresgid }
#endif

#ifdef L_seteuid
#define SYSCALL_SETUP(x) \
        { movei r2, -1; move r1, r0 }; \
        { movei r0, -1; moveli TREG_SYSCALL_NR_NAME, SYS_setresuid }
#endif

#ifdef L_setpgrp
#define SYSCALL_SETUP(x) \
        { movei r0, 0; movei r1, 0 }; \
	moveli TREG_SYSCALL_NR_NAME, SYS_setpgid
#endif

#ifdef L_stat
#ifndef SYS_newfstatat
#define SYS_newfstatat SYS_fstatat64
#endif
#define SYSCALL_SETUP(x) \
        { move r3, zero; move r2, r1 }; \
        { move r1, r0; moveli r0, AT_FDCWD }; \
	moveli TREG_SYSCALL_NR_NAME, SYS_newfstatat
#endif

#ifdef L_symlink
#define SYSCALL_SETUP(x) \
        { move r2, r1; moveli r1, AT_FDCWD }; \
	moveli TREG_SYSCALL_NR_NAME, SYS_symlinkat
#endif

#ifdef L_truncate
#ifndef __LP64__
#ifndef SYS_truncate
#define SYS_truncate SYS_truncate64
#endif
#define SYSCALL_SETUP(x) \
	{ move r2, r1; move r3, r1 }; \
	{ shri r3, r3, 31; moveli TREG_SYSCALL_NR_NAME, SYS_truncate }
#endif
#endif

#ifdef L_unlink
#define SYSCALL_SETUP(x) \
        { moveli r2, 0; move r1, r0 }; \
        { moveli r0, AT_FDCWD; moveli TREG_SYSCALL_NR_NAME, SYS_unlinkat }
#endif

#ifdef L_vfork
#define SYSCALL_SETUP(x) \
        { moveli r0, CLONE_VFORK | CLONE_VM | SIGCHLD; move r1, zero }; \
        { move r2, zero; move r3, zero }; \
	moveli TREG_SYSCALL_NR_NAME, SYS_clone
#endif

#ifdef L_waitpid
#define SYSCALL_SETUP(x) \
	{ move r3, zero; moveli TREG_SYSCALL_NR_NAME, SYS_wait4 }
#endif

/* The offset of _errno in struct _reent; see <sys/reent.h> */
/* Note that we are using the SECOND version, with !REENT_SMALL */
#define REENT_ERRNO_OFFSET 0

/* For now the code assumes REENT_ERRNO_OFFSET == 0 for efficiency */
#if REENT_ERRNO_OFFSET != 0
# error "Adjust _##name code not to store directly to tp"
#endif        

#ifndef SYSCALL_SETUP
#define SYSCALL_NR(x) SYS_##x
#define SYSCALL_SETUP(x) moveli TREG_SYSCALL_NR_NAME, SYSCALL_NR(x)
#endif

#define MOVE0 
#define MOVE1 { move r0,r1 };
#define MOVE2 { move r0,r1; move r1,r2 };
#define MOVE3 MOVE2 { move r2,r3 };
#define MOVE4 MOVE2 { move r2,r3; move r3,r4 };
#define MOVE5 MOVE4 { move r4,r5 };
#define MOVE6 MOVE4 { move r4,r5; move r5,r6 };
#define __MOVES(n) n
#define _MOVES(x) __MOVES(MOVE ## x)
#define MOVES(x) _MOVES(x)

#define _NAME(x) _##x
#define NAME(x) _NAME(x)
#define _NAME_R(x) _##x##_r
#define NAME_R(x) _NAME_R(x)

	.section .text.NAME(SYSCALL), "ax"
	.global NAME_R(SYSCALL)
	.type NAME_R(SYSCALL),@function
NAME_R(SYSCALL):
	MOVES(NARGS)
	.size NAME_R(SYSCALL),.-NAME_R(SYSCALL)

	.global NAME(SYSCALL)
	.type NAME(SYSCALL),@function
NAME(SYSCALL):
        SYSCALL_SETUP(SYSCALL)
        swint1
        BNEZ r1, 1f
        jrp lr
1:      j __syscall_error
	.size NAME(SYSCALL),.-NAME(SYSCALL)

        .weak SYSCALL
SYSCALL = NAME(SYSCALL)

#endif
