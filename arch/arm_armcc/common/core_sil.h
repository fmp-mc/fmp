/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: core_sil.h 789 2011-03-03 07:20:01Z ertl-honda $
 */

/*
 *  sil.hのコア依存部（ARM_ARMCC用）
 */

#ifndef TOPPERS_CORE_SIL_H
#define TOPPERS_CORE_SIL_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  メモリが変更されることをコンパイラに伝えるためのマクロ
 */
#define ARM_MEMORY_CHANGED __memory_changed()

#ifdef __thumb__
/*
 *  制御レジスタの操作関数
 */

/*
 *  ステータスレジスタ（CPSR）の現在値の読出し
 */
extern uint32_t current_sr(void);

/*
 *  ステータスレジスタ（CPSR）の現在値の変更
 */
extern void set_sr(uint32_t sr);
#endif /* __thumb__ */

/*
 *  すべての割込み（FIQとIRQ）の禁止
 */
Inline uint32_t
TOPPERS_disint(void)
{
	uint32_t  irq_fiq_mask;

#ifndef __thumb__
	register uint32_t cpsr __asm("cpsr");

	irq_fiq_mask = cpsr & (0x40|0x80);
	cpsr |= (0x40|0x80);
#else /* !__thumb__ */
	uint32_t  cpsr;

	cpsr = current_sr();
	irq_fiq_mask = cpsr & (0x40|0x80);
	cpsr |= (0x40|0x80);
	set_sr(cpsr);
#endif /* __thumb__ */

	return(irq_fiq_mask);
}

/*
 *  FIQ,IRQの設定
 */
Inline void
TOPPERS_set_fiq_irq(uint32_t TOPPERS_irq_fiq_mask)
{
#ifndef __thumb__
	register uint32_t cpsr __asm("cpsr");
	uint32_t tmp_cpsr;
    
	tmp_cpsr = cpsr & ~(0x40|0x80); 
	cpsr = tmp_cpsr | (TOPPERS_irq_fiq_mask & (0x40|0x80));
#else /* __thumb__ */
	uint32_t  cpsr;

	cpsr = current_sr();
	cpsr = cpsr &  ~(0x40|0x80);
	cpsr = cpsr | (TOPPERS_irq_fiq_mask &  (0x40|0x80));
	set_sr(cpsr);
#endif /* __thumb__ */
}

/*
 *  全割込みロック状態の制御
 */
#define SIL_PRE_LOC   uint32_t TOPPERS_irq_fiq_mask
#define SIL_LOC_INT() ((void)(TOPPERS_irq_fiq_mask = TOPPERS_disint()))
#define SIL_UNL_INT() (TOPPERS_set_fiq_irq(TOPPERS_irq_fiq_mask))

/*
 *  微少時間待ち
 */
Inline void
sil_dly_nse(ulong_t dlytim)
{
	extern _sil_dly_nse(ulong_t dlytim);
	_sil_dly_nse(dlytim);
}

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_CORE_SIL_H */
