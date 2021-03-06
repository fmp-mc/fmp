/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2012 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: chip_sil.h 843 2011-07-15 03:17:19Z ertl-honda $
 */

/*
 *   sil.hのチップ依存部（MPCORE用）
 *
 *  このインクルードファイルは，sil.hの先頭でインクルードされる．他のファ
 *  イルからは直接インクルードすることはない．このファイルをインクルー
 *  ドする前に，t_stddef.hがインクルードされるので，それらに依存しても
 *  よい．
 */

#ifndef TOPPERS_CHIP_SIL_H
#define TOPPERS_CHIP_SIL_H

/*
 *  ARMで共通な定義
 */
#include "arm_armcc/common/core_sil.h"

#ifndef TOPPERS_MACRO_ONLY

/*
 *  プロセッサIDの取得
 */
Inline void
sil_get_pid(ID *p_prcid)
{
	register uint32_t cp15_cpuid __asm("cp15:0:c0:c0:5");

	*p_prcid = (cp15_cpuid & 0x0f) + 1;
}

/*
 *  スピンロック変数（chip_config.c）
 */
extern uint32_t TOPPERS_spn_var;

/*
 *  スピンロックの取得
 */
Inline uint32_t
TOPPERS_sil_loc_spn(void)
{
	uint32_t irq_fiq_mask; 
	register uint32_t locked;
	uint32_t pre_cpsr_c;
	uint32_t dis_cpsr_c;
	ID       prcid;
	register uint32_t cpsr __asm("cpsr");

	sil_get_pid(&prcid);

	/* 呼び出し時のcpsrのbit0〜7の状態 */
	pre_cpsr_c = cpsr;

	/* 全割込みロック状態へ */
	irq_fiq_mask = TOPPERS_disint();

	/* 全割込みロック状態移行後のcpsrのbit0〜7の状態 */
	dis_cpsr_c = cpsr;

	while(true) {
		locked = __ldrex(&TOPPERS_spn_var);
		if (locked != 0) {
			cpsr = pre_cpsr_c;  /* 呼び出し時の状態へ（割込み許可） */
			__wfe();
			cpsr = dis_cpsr_c;  /* 全割込みロック状態へ */
		} else {
			locked = __strex(prcid, &TOPPERS_spn_var);
		}

		if (locked == 0) {
			/* スピンロックが取得成功 */
			/* Data meory barrier */
#if __TARGET_ARCH_ARM == 6
			{
				register uint32_t cp15_dmb __asm("cp15:0:c7:c10:5");
				cp15_dmb = 0;
			}
#elif __TARGET_ARCH_ARM == 7
			__dmb(0xf)
#endif /* __TARGET_ARCH_ARM == 7 */
			__memory_changed();
			return irq_fiq_mask;
		}
	}
}

/*
 *  スピンロックの返却
 */
Inline void
TOPPERS_sil_unl_spn(uint32_t irq_fiq_mask)
{
	/* メモリの内容が書き換わる可能性がある */
	__memory_changed();
	/* Data meory barrier */
#if __TARGET_ARCH_ARM == 6
	{
		register uint32_t cp15_dmb __asm("cp15:0:c7:c10:5");
		cp15_dmb = 0;
	}
#elif __TARGET_ARCH_ARM == 7
	__dmb(0xf)
#endif /* __TARGET_ARCH_ARM == 7 */
	TOPPERS_spn_var = 0U;
	/* Data Sync Barrier */
#if __TARGET_ARCH_ARM == 6
	{
		register uint32_t cp15_dsb __asm("cp15:0:c7:c10:5");
		cp15_dsb = 0;
	}
#elif __TARGET_ARCH_ARM == 7
	__dsb(0xf)
#endif /* __TARGET_ARCH_ARM == 7 */
	/* スピンロック待ちのタスクへイベントを送る */
	__sev();

	/* スピンロックの取得前の状態へ */
	TOPPERS_set_fiq_irq(irq_fiq_mask);
}

/*
 *  スピンロックの強制解放
 *  自プロセッサがスピンロックを取得している場合に解放する． 
 */
Inline void
TOPPERS_sil_force_unl_spn(void)
{
	ID prcid;

	sil_get_pid(&prcid);

	if (TOPPERS_spn_var == prcid) {
		TOPPERS_spn_var = 0U;
		/* スピンロック待ちのタスクへイベントを送る */
		__sev();
	}
}

/*
 *  スピンロック
 */
#define SIL_LOC_SPN() ((void)(TOPPERS_irq_fiq_mask = TOPPERS_sil_loc_spn()))
#define SIL_UNL_SPN() (TOPPERS_sil_unl_spn(TOPPERS_irq_fiq_mask))

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_CHIP_SIL_H */
