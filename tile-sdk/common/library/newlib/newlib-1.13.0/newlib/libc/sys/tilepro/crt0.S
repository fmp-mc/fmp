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
 * As required by the ABI, an 8-byte caller state save area is allocated
 * at the base of the stack frame.
 *
 * In crt0 we just need to set up r0, r1, r2 to the right values
 * so that main() can take them like normal function arguments.
 */

#include <sys/syscall.h>
#include <arch/abi.h>

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
        { move r0,sp; addi sp,sp,-8 }

        /* Save zero for caller lr in the "caller" save area. */
        { sw sp,zero; addi r12,sp,-4 }

        /* Allocate caller state save area for our callee. And save
         * our caller's sp in it.
         */
        { sw r12,sp; addi sp,sp,-8 }

        /* Initialize the first thread to use the struct _reent impure_data.
         * Subsequent threads will need to allocate their own.
         */
        moveli tp,lo16(_impure_ptr)
        auli tp,tp,ha16(_impure_ptr)
        lw tp,tp

        /* Save the environment to the "environ" pointer. */
        { lw r0,r0; addi r1,sp,20 }
        addi r2,r0,1
        s2a r2,r2,r1
        moveli r12,lo16(environ)
        auli r12,r12,ha16(environ)
        sw r12,r2

        /* Skip ahead to the Elf attributes (after environ). */
1:      { lw r1,r2; addi r2,r2,4 }
        bnzt r1,1b

        /* Read the Elf attributes; for now we just grab AT_PAGESZ. */
1:      { lw r1,r2; addi r2,r2,8; addi r0,r2,4 }
        { bz r1,2f; addi r1,r1,-AT_PAGESZ }
        bnzt r1,1b
        { lw r0,r0; moveli r2,lo16(__pagesize) }
        auli r2,r2,ha16(__pagesize)
        sw r2,r0
2:      
        
        /* See if we have an _init section, and if so call it. */
        .weak _init
        moveli r12,lo16(_init)
        auli r12,r12,ha16(_init)
        bz r12,1f
        jalr r12

1:      /* Load the function arguments as appropriate from the stack. */
        addi r0,sp,16
        { lw r0,r0; addi r1,sp,20 }
        addi r2,r0,1
        s2a r2,r2,r1

        /* Call main and exit with the return code. */
        jal main
        jal exit       /* try normal C-style exit */
        jal _exit      /* try to call our libc wrapper for the syscall */

        addi sp,sp,8   /* deallocate caller state save area */

        movei TREG_SYSCALL_NR_NAME,SYS_exit    /* do a direct syscall */
        swint1
        mtspr DONE,r0       /* try the "DONE" spr */
        ill            /* give up and issue an illegal instruction */
        .size _start,.-_start

        .section ".data","wa"
        .global __pagesize
__pagesize:
        .int 0         /* no default value */
