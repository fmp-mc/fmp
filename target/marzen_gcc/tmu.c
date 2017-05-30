/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: tmu.c 943 2012-10-19 07:50:40Z ertl-honda $
 */

/*
 *  タイマドライバ（SH34用）
 */

#include "kernel_impl.h"
#include "time_event.h"
#include <sil.h>
#include "target_timer.h"
#ifdef TRACE_ENABLE
#endif /* TRACE_ENABLE */

/*
 *  TMU初期化ブロック
 */
const TMUINIB tmuinib_table[] = {
	{
		(uint8_t*)(TMU012_BASE + TMU_TSTR),
		(uint32_t*)(TMU0_BASE + TMU_TCOR),
		(uint32_t*)(TMU0_BASE + TMU_TCNT),
		(uint16_t*)(TMU0_BASE + TMU_TCR),
		(uint8_t)(0x01)  
	},
	{
		(uint8_t*)(TMU012_BASE + TMU_TSTR),
		(uint32_t*)(TMU1_BASE + TMU_TCOR),
		(uint32_t*)(TMU1_BASE + TMU_TCNT),
		(uint16_t*)(TMU1_BASE + TMU_TCR),
		(uint8_t)(0x02)  
	},
	{
		(uint8_t*)(TMU012_BASE + TMU_TSTR),
		(uint32_t*)(TMU2_BASE + TMU_TCOR),
		(uint32_t*)(TMU2_BASE + TMU_TCNT),
		(uint16_t*)(TMU2_BASE + TMU_TCR),
		(uint8_t)(0x04)  
	},
	{
		(uint8_t*)(TMU345_BASE + TMU_TSTR),
		(uint32_t*)(TMU3_BASE + TMU_TCOR),
		(uint32_t*)(TMU3_BASE + TMU_TCNT),
		(uint16_t*)(TMU3_BASE + TMU_TCR),
		(uint8_t)(0x01)  
	},
	{
		(uint8_t*)(TMU345_BASE + TMU_TSTR),
		(uint32_t*)(TMU4_BASE + TMU_TCOR),
		(uint32_t*)(TMU4_BASE + TMU_TCNT),
		(uint16_t*)(TMU4_BASE + TMU_TCR),
		(uint8_t)(0x02)  
	},
	{
		(uint8_t*)(TMU345_BASE + TMU_TSTR),
		(uint32_t*)(TMU5_BASE + TMU_TCOR),
		(uint32_t*)(TMU5_BASE + TMU_TCNT),
		(uint16_t*)(TMU5_BASE + TMU_TCR),
		(uint8_t)(0x04)  
	},
	{
		(uint8_t*)(TMU678_BASE + TMU_TSTR),
		(uint32_t*)(TMU6_BASE + TMU_TCOR),
		(uint32_t*)(TMU6_BASE + TMU_TCNT),
		(uint16_t*)(TMU6_BASE + TMU_TCR),
		(uint8_t)(0x01)  
	},
	{
		(uint8_t*)(TMU678_BASE + TMU_TSTR),
		(uint32_t*)(TMU7_BASE + TMU_TCOR),
		(uint32_t*)(TMU7_BASE + TMU_TCNT),
		(uint16_t*)(TMU7_BASE + TMU_TCR),
		(uint8_t)(0x02)  
	},
	{
		(uint8_t*)(TMU678_BASE + TMU_TSTR),
		(uint32_t*)(TMU8_BASE + TMU_TCOR),
		(uint32_t*)(TMU8_BASE + TMU_TCNT),
		(uint16_t*)(TMU8_BASE + TMU_TCR),
		(uint8_t)(0x03)  
	}
};


/*
 *  カーネルタイマのID取得テーブル
 */
const uint32_t
target_sys_clk_timer_id_table[] = {
	PRC1_TMU_NO,
	PRC2_TMU_NO,
	PRC3_TMU_NO,
	PRC4_TMU_NO,
};

/*
 *  カーネルタイマの割込み番号の取得テーブル
 */
const uint32_t
target_sys_clk_timer_intno_table[] = {
	INTNO_TIMER_PRC1,
	INTNO_TIMER_PRC2,
	INTNO_TIMER_PRC3,
	INTNO_TIMER_PRC4
};

/*
 * [タイマスタートレジスタの排他制御用ロック(タイマ3,4,5用)]
 * ローカルタイマ方式では，コア1,2,3がタイマ3,4,5を使用する．
 * タイマ3,4,5で使用するタイマスタートレジスタはtstr1で共通のため，
 * コア1,2,3の間で排他制御が必要．
 */
SPNLOCK tmu_tstr_lock;

/*
 *  タイマの起動処理
 */
void
target_timer_initialize(intptr_t exinf)
{
	CLOCK    cyc = TO_CLOCK(TIC_NUME, TIC_DENO);
	const TMUINIB *p_tmuinib = &tmuinib_table[target_sys_clk_timer_id_table[x_prc_index()]];

	/*
	 *  タイマ周期を設定し，タイマの動作を開始する．
	 */
	sil_wrb_mem((void*)(p_tmuinib->tstr_b),
				(sil_reb_mem((void*)(p_tmuinib->tstr_b)) & ~(p_tmuinib->tstr_bit)));  /* タイマ停止 */
	assert(cyc <= MAX_CLOCK);             /* タイマ上限値のチェック */

	/* 分周比設定、割り込み許可 */
	sil_wrh_mem((void*)(p_tmuinib->tcr_h), TCR_UNIE);
    
	sil_wrw_mem((void*)(p_tmuinib->tcor_w), cyc); /* timer constantレジスタをセット */
	sil_wrw_mem((void*)(p_tmuinib->tcnt_w), cyc); /* カウンターをセット */


	/* 割り込み要求をクリア */
	sil_wrh_mem((void*)(p_tmuinib->tcr_h),
				(sil_reh_mem((void*)(p_tmuinib->tcr_h)) & ~TCR_UNF));

	x_lock_spin(&tmu_tstr_lock);
	/* タイマスタート */
	sil_wrb_mem((void*)(p_tmuinib->tstr_b),
				(sil_reb_mem((void*)(p_tmuinib->tstr_b)) | (p_tmuinib->tstr_bit)));
	x_unlock_spin(&tmu_tstr_lock);
}

/*
 *  タイマの停止処理
 */
void
target_timer_terminate(intptr_t exinf)
{
	const TMUINIB *p_tmuinib = &tmuinib_table[target_sys_clk_timer_id_table[x_prc_index()]];

	sil_wrb_mem((void*)(p_tmuinib->tstr_b),
				(sil_reb_mem((void*)(p_tmuinib->tstr_b)) & ~(p_tmuinib->tstr_bit)));  /* タイマ停止 */
	/* 割り込み要求をクリア */
	sil_wrh_mem((void*)(p_tmuinib->tcr_h),
				(sil_reh_mem((void*)(p_tmuinib->tcr_h)) & ~TCR_UNF));
}

/*
 *  タイマ割込みハンドラ
 */
void
target_timer_handler(void)
{
	const TMUINIB *p_tmuinib = &tmuinib_table[target_sys_clk_timer_id_table[x_prc_index()]];
	uint32_t intno = target_sys_clk_timer_intno_table[x_prc_index()];

	/* 割り込み要求をクリア */
	sil_wrh_mem((void*)(p_tmuinib->tcr_h),
				(sil_reh_mem((void*)(p_tmuinib->tcr_h)) & ~TCR_UNF));
      
	i_begin_int(intno);
	signal_time();                    /* タイムティックの供給 */
	i_end_int(intno);
}
