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
 * Set current context.
 */

#include <asm/errno.h>
#include <asm/unistd.h>
#include <arch/spr_def.h>
#include <arch/abi.h>

#include "ucontext_asm.h"

/* PL to return to via iret in setcontext */
#define RETURN_PL 0

/* int setcontext (const ucontext_t *ucp) */

	.section .text.setcontext, "ax"
	.global setcontext
	.type setcontext,@function
setcontext:

	/* See if this is a true signal context (flags == 0).
	   If so, restore by invoking rt_sigreturn().  */
#if UC_FLAGS_OFFSET != 0
#error Add offset to r0 prior to load
#endif
	LD r10, r0
	{
	 BEQZ r10, .Lsigreturn
	 addi r10, r10, -1  /* Confirm that it has value "1".  */
	}
	BNEZ r10, .Lbadcontext

	/* Save lr and r0 briefly on the stack and set the signal mask:
	   rt_sigprocmask (SIG_SETMASK, &ucp->uc_sigmask, NULL, _NSIG / 8).  */
	{
	 ST sp, lr
	 ADDI_PTR r11, sp, -(2 * REGSIZE)
	 move r10, sp
	}
	{
	 ST r11, r10
	 ADDI_PTR r10, sp, -REGSIZE
	 ADDI_PTR sp, sp, -(3 * REGSIZE)
	}
	{
	 ST r10, r0
	 ADDLI_PTR r1, r0, UC_SIGMASK_OFFSET
	}
	{
	 movei r3, _NSIG / 8
	 movei r2, 0
	}
	{
	 movei r0, SIG_SETMASK
	 moveli TREG_SYSCALL_NR_NAME, __NR_rt_sigprocmask
	}
	swint1
	{
	 ADDI_PTR sp, sp, 3 * REGSIZE
	 ADDI_PTR r11, sp, 2 * REGSIZE  /* Restore uc_context to r11. */
	}
	LD lr, sp
	LD r11, r11
	{
	 ADDI_PTR r10, r11, UC_REG(0)
	 BNEZ r1, .Lsyscall_error
	}

	/* Restore the argument registers; note they will be random
	   unless makecontext() has been called.  */
	{ LD r0, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r1, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r2, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r3, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r4, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r5, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r6, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r7, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r8, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r9, r10; ADDLI_PTR r10, r10, UC_REG(30) - UC_REG(9) }

	/* Restore the callee-saved GPRs.  */
	{ LD r30, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r31, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r32, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r33, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r34, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r35, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r36, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r37, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r38, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r39, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r40, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r41, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r42, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r43, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r44, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r45, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r46, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r47, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r48, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r49, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r50, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r51, r10; ADDI_PTR r10, r10, REGSIZE }
	{ LD r52, r10; ADDI_PTR r10, r10, REGSIZE * 2 }
	/* Skip tp since it must not change for a given thread.  */
	{ LD sp, r10;  ADDI_PTR r10, r10, REGSIZE }
	{ LD lr, r10;  ADDI_PTR r10, r10, REGSIZE }
	{ LD r11, r10; ADDI_PTR r10, r10, REGSIZE }

	/* Construct an iret context; we set ICS so we can validly load
	   EX_CONTEXT for iret without being interrupted halfway through.  */
	{
	 LD r12, r10
	 movei r13, 1
	}
	{
	 mtspr INTERRUPT_CRITICAL_SECTION, r13
	 shli r12, r12, SPR_EX_CONTEXT_0_1__ICS_SHIFT
	}
	{
	 mtspr EX_CONTEXT_0_0, r11
	 ori r12, r12, RETURN_PL
	}
	mtspr EX_CONTEXT_0_1, r12
	iret
	jrp lr    /* keep the backtracer happy */
	
.Lsigreturn:
	/* This is a context obtained from a signal handler.
	   Perform a full restore by pushing the context
	   passed onto a simulated signal frame on the stack
	   and call the signal return syscall as if a signal
	   handler exited normally.  */
	{
	 ADDLI_PTR sp, sp, -(C_ABI_SAVE_AREA_SIZE + SI_MAX_SIZE + UC_SIZE)
	 ADDLI_PTR r1, sp, -UC_SIZE
	}
	moveli r2, UC_SIZE / REGSIZE
0:      {
	 LD r10, r0
	 ADDI_PTR r0, r0, REGSIZE
	}
	{
	 ST r1, r10
	 ADDI_PTR r1, r1, REGSIZE
	 addi r2, r2, -1
	}
	BNEZ r2, 0b
	moveli TREG_SYSCALL_NR_NAME, __NR_rt_sigreturn
	swint1

	/* Restore the stack and fall through to the error
	   path.  Successful rt_sigreturn never returns to
	   its calling place.  */
	ADDLI_PTR sp, sp, (C_ABI_SAVE_AREA_SIZE + SI_MAX_SIZE + UC_SIZE)

.Lsyscall_error:
	j __syscall_error

.Lbadcontext:
	{
	 movei r1, EINVAL
	 j __syscall_error
	}
	.size setcontext,.-setcontext

	.section .text.__startcontext, "ax"
	.global __startcontext
	.type __startcontext,@function
__startcontext:
	BEQZ r30, 1f
	{
	 move r0, r30
	 jal setcontext
	}
1:	j plt(exit)
	.size __startcontext,.-__startcontext
