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
 * The ELF standard tells us that the stack is set up like this on
 * entry (the left side is the offset from "sp", in "long"-size words):
 *
 *              +0              argc
 *              +1              argv[0]
 *              ...
 *              +(argc+1)       NULL
 *              +(argc+2)       envp[0]
 *              ...
 *                              NULL
 *              ...             ElfInfo
 *
 * The ElfInfo is pairs of key/value words following the envp
 * pointers and terminated by a zero-valued key.
 *
 * Although not mandated by the standard, it happens to be the case
 * that we store the actual argv and envp strings immediately after
 * the ElfInfo data on the stack.
 *
 * As required by the ABI, a 16-byte caller state save area is allocated
 * at the base of the stack frame.
 *
 * In crt0 we just need to set up r0, r1, r2 to the right values
 * so that main() can take them like normal function arguments.
 */

#include <sys/syscall.h>
#include <arch/abi.h>

#if __SIZEOF_POINTER__ == 4
#define ADD_PTR addx
#define ADDI_PTR addxi
#define LD_PTR ld4s
#define ST_PTR st4
#define SHLADD_PTR shl2add
#else
#define ADD_PTR add
#define ADDI_PTR addi
#define LD_PTR ld
#define ST_PTR st
#define SHLADD_PTR shl3add
#endif

/* System page size enumeration value not provided in newlib headers. */
#define AT_PAGESZ 6

        .section .text._start, "ax"

        .global _start
        .type _start,@function
        .align 8
_start:
        /* Linux starts us with sp pointing at the conventional Elf layout,
         * but we need to allow two "caller" words for our ABI convention.
         * See the TILE uClibc crt1.S for more info.
         */
        { move r0,sp; ADDI_PTR sp,sp,-16 }

        /* Save zero for caller lr in the "caller" save area. */
        { st sp,zero; ADDI_PTR r12,sp,-8 }

        /* Allocate caller state save area for our callee. And save
         * our caller's sp in it.
         */
        { st r12,sp; ADDI_PTR sp,sp,-16 }

        /* Initialize the first thread to use the struct _reent impure_data.
         * Subsequent threads will need to allocate their own.
         */
        moveli tp,hw2_last(_impure_ptr)
        shl16insli tp,tp,hw1(_impure_ptr)
        shl16insli tp,tp,hw0(_impure_ptr)
        LD_PTR tp,tp

        /* Save the environment to the "environ" pointer. */
        { LD_PTR r0,r0; ADDI_PTR r1,r0,__SIZEOF_POINTER__ }
        { addi r2,r0,1; moveli r12,hw2_last(environ) }
        { SHLADD_PTR r2,r2,r1 ; shl16insli r12,r12,hw1(environ) }
        shl16insli r12,r12,hw0(environ)
        ST_PTR r12,r2

        /* Skip ahead to the Elf attributes (after environ). */
1:      { LD_PTR r1,r2; ADDI_PTR r2,r2,__SIZEOF_POINTER__ }
        bnezt r1,1b

        /* Read the Elf attributes; for now we just grab AT_PAGESZ. */
1:      {
         LD_PTR r1,r2
         ADDI_PTR r2,r2,__SIZEOF_POINTER__*2
         ADDI_PTR r0,r2,__SIZEOF_POINTER__
        }
        { beqz r1,2f; addi r1,r1,-AT_PAGESZ }
        bnezt r1,1b
        { LD_PTR r0,r0; moveli r2,hw2_last(__pagesize) }
        shl16insli r2,r2,hw1(__pagesize)
        shl16insli r2,r2,hw0(__pagesize)
        st4 r2,r0
2:      
        
        /* See if we have an _init section, and if so call it. */
        .weak _init
        moveli r12,hw2_last(_init)
        shl16insli r12,r12,hw1(_init)
        shl16insli r12,r12,hw0(_init)
        beqz r12,1f
        jalr r12

1:      /* Load the function arguments as appropriate from the stack. */
        ADDI_PTR r0,sp,32
        { LD_PTR r0,r0; ADDI_PTR r1,r0,__SIZEOF_POINTER__ }
        addi r2,r0,1
        SHLADD_PTR r2,r2,r1

        /* Call main and exit with the return code. */
        jal main
        jal exit       /* try normal C-style exit */
        jal _exit      /* try to call our libc wrapper for the syscall */

        ADDI_PTR sp,sp,16  /* deallocate caller state save area */

        movei TREG_SYSCALL_NR_NAME,SYS_exit    /* do a direct syscall */
        swint1
        mtspr DONE,r0       /* try the "DONE" spr */
        ill            /* give up and issue an illegal instruction */
        .size _start,.-_start

        .section ".data","wa"
        .global __pagesize
__pagesize:
        .int 0         /* no default value */
