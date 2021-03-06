/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2009 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *	Copyright (C) 2009 by Industrial Technology Institute,
 *								Miyagi Prefectural Government, JAPAN
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
 *  $Id: prc_asm.inc 765 2011-01-13 07:18:55Z mit-kimai $
 */

#ifndef TOPPERS_PRC_ASM_INC
#define TOPPERS_PRC_ASM_INC

.macro my_prc_index index_reg work_reg labal_skip label_cpuidr_id
	movi20 #CPUIDR_w, \work_reg
	mov.l \label_cpuidr_id, \index_reg	/*  index_reg←CPUIDR_ID  */
	mov.l @\work_reg, \work_reg			/*  work_reg←CPUIDR  */
	tst	\index_reg, \work_reg			/*  CPUIDRのIDビット==0 ? */
	mov #0, \index_reg					/*  index_reg←0  */
	bt \labal_skip
	mov #1, \index_reg					/*  index_reg←1  */
\labal_skip:
.endm

.macro my_pcb re_reg sc_reg1
	rdctl \sc_reg1, cpuid
	slli  \sc_reg1, \sc_reg1, 2
	movhi \re_reg, %hiadj(p_pcb_table)
	addi  \re_reg, \re_reg, %lo(p_pcb_table)
	add   \sc_reg1, \sc_reg1, \re_reg
	ldw   \re_reg, 0(\sc_reg1)
.endm

.macro my_istkpt re_reg sc_reg1
	rdctl \sc_reg1, cpuid
	slli  \sc_reg1, \sc_reg1, 2
	movhi \re_reg, %hiadj(_kernel_istkpt_table)
	addi  \re_reg, \re_reg, %lo(_kernel_istkpt_table)
	add   \sc_reg1, \sc_reg1, \re_reg
	ldw   \re_reg, 0(\sc_reg1)
.endm

#endif /* TOPPERS_PRC_ASM_INC */

