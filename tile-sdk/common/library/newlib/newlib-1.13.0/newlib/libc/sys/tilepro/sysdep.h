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
 * Provide definitions to simplify sharing code between TILEPro,
 * TILE-Gx, and TILE-Gx -m32.
 */

#ifndef _TILE_SYSDEP_H
#define _TILE_SYSDEP_H

/* Specify the size in bytes of a machine register.  */
#ifdef __tilegx__
#define REGSIZE		8
#else
#define REGSIZE		4
#endif

/* The presumption is that LD/ST are used for manipulating registers.
   Since opcode parsing is case-insensitive, we don't need to provide
   definitions for these on tilegx.  */
#ifndef __tilegx__
#define LD		lw
#define LD4U		lw
#define ST		sw
#define ST4		sw
#define BNEZ		bnz
#define BEQZ		bz
#define BEQZT		bzt
#define CMPEQI		seqi
#define CMPEQ		seq
#define CMOVEQZ		mvz
#define CMOVNEZ		mvnz
#endif

/* Provide "pointer-oriented" instruction variants.  These differ not
   just for tilepro vs tilegx, but also for tilegx -m64 vs -m32.  */
#if defined(__tilegx__) && !defined(__LP64__)
#define ADD_PTR		addx
#define ADDI_PTR	addxi
#define ADDLI_PTR	addxli
#define LD_PTR		ld4s
#else
#define ADD_PTR		add
#define ADDI_PTR	addi
#define ADDLI_PTR	addli
#define LD_PTR		LD
#endif

#endif /* _TILE_SYSDEP_H */
