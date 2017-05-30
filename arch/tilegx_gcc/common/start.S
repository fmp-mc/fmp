/*
 * TILEGx startup module for TOPPERS/FMP kernel.
 * This file is modified from 'head_64.S' of TILE linux kernel 3.12.
 * (C) 2014 by Li Yixiao (liyixiao@ertl.jp)
 *
 * Copyright 2011 Tilera Corporation. All Rights Reserved.
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation, version 2.
 *
 *   This program is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 *   NON INFRINGEMENT.  See the GNU General Public License for
 *   more details.
 *
 * TILE startup code.
 */

#define TOPPERS_MACRO_ONLY
#include <hv/hypervisor.h>
#include "tilegx.h"

/**
 * TODO: following macros are from linux, remove them
 */
//#include <linux/linkage.h>
//#include <linux/init.h>
#define __HEAD      .section    ".head.text","ax"
#define ENTRY(name) \
  .globl name; \
  ALIGN; \
  name:
#define ALIGN __ALIGN
#define __ALIGN .align 8

/* Extract two 32-bit bit values that were read into one register. */
#ifdef __BIG_ENDIAN__
#define GET_FIRST_INT(rd, rs) shrsi rd, rs, 32
#define GET_SECOND_INT(rd, rs) addxi rd, rs, 0
#else
#define GET_FIRST_INT(rd, rs) addxi rd, rs, 0
#define GET_SECOND_INT(rd, rs) shrsi rd, rs, 32
#endif

#include "arch_asm_inc.S"
#include "target_kernel.h"

/**
 * Return core index.
 * TODO: handle when there is a hole (unavailable CPU core); check r2,r3 for strach
 * Result:  re_reg
 * Scratch: rx, ry, r0, r1
 */
.macro my_core_index re_reg sc_reg1 sc_reg2
    jal _hv_inquire_topology
    {
      //GET_FIRST_INT(\sc_reg1, r1)           /* sc_reg1 = width */ // TODO: THIS IS NOT WHAT WE WANT
      moveli \sc_reg1, TILEGX_CLIENT_WD
      GET_SECOND_INT(\re_reg, r0)           /* re_reg = y */
    }
    {
      GET_FIRST_INT(\sc_reg2, r0)           /* sc_reg2 = x */
      mul_lu_lu \re_reg, \re_reg, \sc_reg1
    }
    {
      add \re_reg, \re_reg, \sc_reg2        /* re_reg == cpu == y*width + x */
    }
.endm

/**
 * Return ISTKPT of a specified core.
 * Input:  core_id_reg
 * Result: re_reg
 */
.macro core_istkpt re_reg core_id_reg
    load_symbol \re_reg, _kernel_istkpt_table /* TODO: check sizeof(STK_T*) == 8 to use shl3add */
    shl3add \re_reg, \core_id_reg, \re_reg    /* re_reg = &((STK_T **)_kernel_istkpt_table)[core_id_reg] */
    ld \re_reg, \re_reg                       /* re_reg = *((STK_T **)re_reg) */
.endm

/*
 * This module contains the entry code for kernel images. It performs the
 * minimal setup needed to call the generic C routines.
 */

	__HEAD
ENTRY(_start)
	/* Notify the hypervisor of what version of the API we want */
	{
#if CONFIG_KERNEL_PL == 1 && _HV_VERSION == 13 && !defined(CONFIG_KVM_GUEST)
	  /* Support older hypervisors by asking for API version 12. */
	  movei r0, _HV_VERSION_OLD_HV_INIT
#else
	  movei r0, _HV_VERSION
#endif
	  movei r1, __tile_chip__
	}
	{
	  movei r2, __tile_chip_rev__
	  movei r3, CONFIG_KERNEL_PL
	}
	jal _hv_init

    /* Install the interrupt base. */
    moveli r0, hw2_last(intrpt_start)
    shl16insli r0, r0, hw1(intrpt_start)
    shl16insli r0, r0, hw0(intrpt_start)
    mtspr SPR_INTERRUPT_VECTOR_BASE_K, r0

    /* Install page table for slave cores */
    my_core_index r2, r3, r4 /* r2 <- core index */
    beqz r2, skip_install_context


#if 0
//  Flush L2?
/*            hv_flush_remote(NULL, HV_FLUSH_ALL,
                    -1,
                    NULL, 0,
                    0, NULL,
                    NULL, 0);*/
    move   r0, zero
    moveli r1, -1
    moveli r2, -1
    moveli r3, 0
    moveli r4, 0
    moveli r5, 0
    moveli r6, 0
    moveli r7, 0
    moveli r8, 0
    jal hv_flush_remote
#endif

    move r0, zero
    jal _hv_inquire_asid
    GET_FIRST_INT(r2, r0)    /* r2 <- asid */

#define LOCAL_ACCESS_PTE (HV_PTE_READABLE | HV_PTE_WRITABLE | HV_PTE_PRESENT | (HV_PTE_MODE_CACHE_NO_L3 << HV_PTE_INDEX_MODE))
    moveli r1, hw2_last(LOCAL_ACCESS_PTE)
    shl16insli r1, r1, hw1(LOCAL_ACCESS_PTE)
    shl16insli r1, r1, hw0(LOCAL_ACCESS_PTE) /* r1 <- LOCAL_ACCESS_PTE */

#define CTX_PAGE_FLAG HV_CTX_DIRECTIO
    moveli r3, CTX_PAGE_FLAG /* r3 <- CTX_PAGE_FLAG */

    moveli r0, hw2_last(_kernel_page_table)
    shl16insli r0, r0, hw1(_kernel_page_table)
    shl16insli r0, r0, hw0(_kernel_page_table) /* r0 <- _kernel_page_table */

    jal _hv_install_context /* install page table */

skip_install_context:

    /* Initialize ISTKPT */
	my_core_index r2, r3, r4
	mtspr SPR_SYSTEM_SAVE_K_0, r2  /* save core index to SPR_SYSTEM_SAVE_1_0 */
	core_istkpt r0, r2
	move sp, r0

	/* Initialize my_pcb() */
	init_my_pcb r2, r3

    cpu_lock r0 // IMPORTANT: MUST lock cpu before enter sta_ker()
    local_irq enable r0 // TODO: should enable interrupts with x_config_int

    // stop backtrace here, TODO: check this
	push zero
	push zero

    jal boot_pc

    jal _start

    .global _cpu_idle_nap
_cpu_idle_nap:
    nap
    nop       /* avoid provoking the icache prefetch with a jump */
    jrp lr
