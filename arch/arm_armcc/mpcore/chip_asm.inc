/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2007-2012 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: chip_asm.inc 394 2009-09-15 07:08:25Z ertl-honda $
 */

#ifndef TOPPERS_CHIP_ASM_INC
#define TOPPERS_CHIP_ASM_INC

#include "arm_armcc/common/core_asm.inc"

	MACRO
$label my_core_index $re_reg
	mrc p15, 0, $re_reg, c0, c0, 5 /* プロセッサIDの取得 */
	and $re_reg, $re_reg, #0x0f    /* 下位4bitのみ有効   */
	MEND

#ifdef USE_THREAD_ID_PCB
	MACRO
$label my_pcb $re_reg, $sc_reg1
	mrc p15, 0, $re_reg, c13, c0, 4
	MEND
#else  /* USE_THREAD_ID_PCB */
	MACRO
$label my_pcb $re_reg, $sc_reg1
	mrc p15, 0, $re_reg, c0, c0, 5 /* プロセッサIDの取得 */
	and $sc_reg1, $re_reg, #0x0f   /* 下位4bitのみ有効   */
	ldr $re_reg, =p_pcb_table
	ldr $re_reg, [$re_reg, $sc_reg1, lsl #2]
	MEND
#endif /* USE_THREAD_ID_PCB */

	MACRO
$label my_istkpt $re_reg, $sc_reg1
	mrc p15, 0, $re_reg, c0, c0, 5 /* プロセッサIDの取得 */
	and $sc_reg1, $re_reg, #0x0f   /* 下位4bitのみ有効   */
	ldr $re_reg, =_kernel_istkpt_table
	ldr $re_reg, [$re_reg, $sc_reg1, lsl #2]
	MEND

	MACRO
$label toppers_asm_custom_idle
	wfi
	msr   cpsr_cxsf, #(CPSR_SVC :OR: CPSR_ALWAYS_SET) /* 割り込み許可(システムモード) */
	msr   cpsr_cxsf, #(CPSR_SVC :OR: CPSR_CPULOCK :OR: CPSR_ALWAYS_SET) /* CPUロック(システムモード) */
	MEND

#endif /* TOPPERS_CHIP_ASM_INC */
