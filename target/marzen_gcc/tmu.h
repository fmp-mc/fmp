/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007-2008 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: tmu.h 943 2012-10-19 07:50:40Z ertl-honda $
 */

/*
 *  タイマドライバ（TMU用）
 */

#ifndef TOPPERS_TMU_H
#define TOPPERS_TMU_H

#include <sil.h>

/*
 *  各コアが使用するタイマの番号と割込み番号
 */
#define PRC1_TMU_NO  3
#define PRC2_TMU_NO  4
#define PRC3_TMU_NO  5
#define PRC4_TMU_NO  6

#define INTNO_TIMER_PRC1 IRQNO_TMU3
#define INTNO_TIMER_PRC2 IRQNO_TMU4
#define INTNO_TIMER_PRC3 IRQNO_TMU5
#define INTNO_TIMER_PRC4 IRQNO_TMU6

/*
 *  タイマ割込みハンドラ登録のための定数
 */
#define INHNO_TIMER_PRC1 (0x10000 | INTNO_TIMER_PRC1)
#define INHNO_TIMER_PRC2 (0x20000 | INTNO_TIMER_PRC2)
#define INHNO_TIMER_PRC3 (0x30000 | INTNO_TIMER_PRC3)
#define INHNO_TIMER_PRC4 (0x40000 | INTNO_TIMER_PRC4)


//#define INTPRI_TIMER   (-6)          /* 割込み優先度 */
#define INTATR_TIMER    0U           /* 割込み属性 */

/*
 *  グローバルタイマーの場合の定義
 */
#define INHNO_TIMER_SYSTIM (0x10000 | IRQNO_TMU3)
#define INTNO_TIMER_SYSTIM (0x10000 | IRQNO_TMU3)

/*
 *  レジスタのビット定義
 */
#define TCR_UNF    UINT_C(0x0100)
#define TCR_UNIE   UINT_C(0x0020)

#ifndef TOPPERS_MACRO_ONLY

/*
 *  TMU初期化ブロック
 */
typedef struct tmu_initialization_block {
	uint8_t *tstr_b;    /* タイマスタートレジスタ */
	uint32_t *tcor_w;    /* タイマコンスタントレジスタ */
	uint32_t *tcnt_w;    /* タイマカウンタ */
	uint16_t *tcr_h;     /* タイマコントロールレジスタ */
	uint8_t   tstr_bit;  /* スタートビット */
} TMUINIB;

/*
 *  TMU初期化ブロック
 */
extern const TMUINIB tmuinib_table[];

/*
 *  カーネルタイマのID取得テーブル
 */
extern const uint32_t target_sys_clk_timer_id_table[];

/*
 *  カーネルタイマの割込み番号の取得テーブル
 */
extern const uint32_t target_sys_clk_timer_intno_table[];

/*
 *  タイマ値の内部表現の型
 */
typedef uint32_t    CLOCK;

/*
 *  タイマ値の内部表現とミリ秒・μ秒単位との変換
 */
#define TIMER_CLOCK             TMU_TIMER_CLOCK
#define TO_CLOCK(nume, deno)    ((CLOCK)(TIMER_CLOCK * (nume) / (deno)))
#define TO_USEC(clock)          (((SYSUTM) clock) * 1000U / TIMER_CLOCK)

/*
 *  設定できる最大のタイマ周期（単位は内部表現）
 */
#define MAX_CLOCK    ((CLOCK) 0xffffffffU)

/*
 *  タイマの起動処理
 *
 *  タイマを初期化し，周期的なタイマ割込み要求を発生させる．
 */
extern void target_timer_initialize(intptr_t exinf);

/*
 *  タイマの停止処理
 *
 *  タイマの動作を停止させる．
 */
extern void target_timer_terminate(intptr_t exinf);

/*
 *  タイマの現在値の読出し
 */
Inline CLOCK
target_timer_get_current(void)
{
	const TMUINIB *p_tmuinib = &tmuinib_table[target_sys_clk_timer_id_table[x_prc_index()]];
	return(TO_CLOCK(TIC_NUME, TIC_DENO) - sil_rew_mem((void*)(p_tmuinib->tcnt_w)));
}

/*
 *  タイマ割込み要求のチェック
 */
Inline bool_t
target_timer_probe_int(void)
{
	const TMUINIB *p_tmuinib = &tmuinib_table[target_sys_clk_timer_id_table[x_prc_index()]];
	return(sil_reh_mem((void*)(p_tmuinib->tcr_h)) & TCR_UNF);
}

/*
 *  タイマ割込みハンドラ
 */
extern void target_timer_handler(void);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_TIMER_H */
