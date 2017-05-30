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
 * Save current context.
 */

#include <asm/unistd.h>
#include <arch/abi.h>

#include "ucontext_asm.h"

/* int getcontext (ucontext_t *ucp) */

	.section .text.getcontext, "ax"
	.global getcontext
	.type getcontext,@function
getcontext:

	/* Save the callee-saved GPRs.  There's no need to save the
	   caller-saved GPRs since the eventual setcontext() or
	   swapcontext() will assume those registers are all dead.
	   Save value "1" to uc_flags to later recognize getcontext().  */
	{ movei r11, 1; ADDI_PTR r10, r0, UC_FLAGS_OFFSET }
	{ ST r10, r11; addli r10, r0, UC_REG(30) }
	{ ST r10, r30; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r31; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r32; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r33; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r34; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r35; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r36; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r37; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r38; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r39; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r40; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r41; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r42; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r43; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r44; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r45; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r46; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r47; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r48; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r49; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r50; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r51; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, r52; ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, tp;  ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, sp;  ADDI_PTR r10, r10, REGSIZE }
	{ ST r10, lr;  ADDI_PTR r10, r10, REGSIZE }
	lnk r11   /* Point PC at the "jrp lr" instruction.  */
	addli r11, r11, .Lreturn - .
	{ ST r10, r11; ADDI_PTR r10, r10, REGSIZE }
	mfspr r11, INTERRUPT_CRITICAL_SECTION
	{
	 ST r10, r11
	 movei r1, 0
	}

	/* rt_sigprocmask (SIG_BLOCK, NULL, &ucp->uc_sigmask, _NSIG / 8) */
	{
	 movei r3, _NSIG / 8
	 addli r2, r0, UC_SIGMASK_OFFSET
	}
	{
	 movei r0, SIG_BLOCK
	 moveli TREG_SYSCALL_NR_NAME, __NR_rt_sigprocmask
	}
	swint1
	BNEZ r1, .Lsyscall_error

.Lreturn:
	{
	 movei r0, 0
	 jrp lr
	}

.Lsyscall_error:
	j __syscall_error

	.size getcontext,.-getcontext
