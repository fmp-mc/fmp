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
 * Save and set current context.
 */

#include "ucontext_asm.h"

/* int swapcontext (ucontext_t *oucp, const ucontext_t *ucp) */

	.section .text.swapcontext, "ax"
	.global swapcontext
	.type swapcontext,@function
swapcontext:
	/* Set up a frame and save r0 and r1.  */
	{
	 ST sp, lr
	 ADDI_PTR r11, sp, -(3 * REGSIZE)
	 move r10, sp
	}
	{
	 ST r11, r10
	 ADDI_PTR r10, sp, -(2 * REGSIZE)
	}
	{
	 ST r10, r0
	 ADDI_PTR r10, sp, -REGSIZE
	 ADDI_PTR sp, sp, -(4 * REGSIZE)
	}
	ST r10, r1

	/* Save the current context.  */
	jal getcontext
	
	/* Tear down the frame and restore r0, r1, and lr. */
	{
	 BNEZ r0, .Lerror
	 ADDI_PTR r1, sp, 3 * REGSIZE
	}
	{
	 LD r1, r1
	 ADDI_PTR r0, sp, 2 * REGSIZE
	}
	{
	 LD r0, r0
	 ADDI_PTR sp, sp, 4 * REGSIZE
	}
	{
	 LD lr, sp
	 ADDLI_PTR r10, r0, UC_REG(54)
	}

	/* Update the stored sp and lr.  */
	{
	 ST r10, sp
	 ADDLI_PTR r10, r0, UC_REG(55)
	}
	ST r10, lr

	/* Tail-call setcontext to finish up.  */
	{
	 move r0, r1
	 j setcontext
	}

.Lerror:
	jrp lr
	.size swapcontext,.-swapcontext
