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
 */

#include "sysdep.h"

/* Definitions of offsets within the ucontext_t structure.  Note
   that for convenience we use __SIZEOF_POINTER__ for "long" and
   "ssize_t" fields (and their unsigned counterparts) as well.  */

#define UC_FLAGS_OFFSET 0
#define UC_LINK_OFFSET (UC_FLAGS_OFFSET + __SIZEOF_POINTER__)
#define UC_STACK_SP_OFFSET (UC_LINK_OFFSET + __SIZEOF_POINTER__)
#define UC_STACK_FLAGS_OFFSET (UC_STACK_SP_OFFSET + __SIZEOF_POINTER__)
#define UC_STACK_SIZE_OFFSET (UC_STACK_FLAGS_OFFSET + __SIZEOF_POINTER__)
#define UC_STACK_MCONTEXT_OFFSET (UC_STACK_SIZE_OFFSET + __SIZEOF_POINTER__)
#define UC_REG(i) (UC_STACK_MCONTEXT_OFFSET + ((i) * REGSIZE))
#define UC_NREGS 64
#define UC_SIGMASK_OFFSET UC_REG(UC_NREGS)
#define UC_SIZE (UC_SIGMASK_OFFSET + (_NSIG / 8))

/* From <asm/siginfo.h> */
#define SI_MAX_SIZE	128

/* From <asm/signal.h> */
#define _NSIG		64
#define SIG_BLOCK          0	/* for blocking signals */
#define SIG_UNBLOCK        1	/* for unblocking signals */
#define SIG_SETMASK        2	/* for setting the signal mask */
