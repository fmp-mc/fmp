/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2008-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_timer.h 722 2010-10-14 04:43:29Z ertl-honda $
 */

/*
 *  タイマドライバ
 */

#ifndef TOPPERS_TARGET_TIMER_H
#define TOPPERS_TARGET_TIMER_H

#include "nios2_system.h"

/*
 *  タイマ割込みハンドラ登録のための定数
 */
/*
 *  ローカルタイマ方式用の定義
 */
#define INHNO_TIMER1     (0x10000 | SYS_CLK_TIMER_1_INT)  /* 割込みハンドラ番号 */
#define INTNO_TIMER1     (0x10000 | SYS_CLK_TIMER_1_INT)  /* 割込み番号 */
#define INTPRI_TIMER1    (-6)            /* 割込み優先度 */
#define INTATR_TIMER1    0U              /* 割込み属性 */

#define INHNO_TIMER2     (0x20000 | SYS_CLK_TIMER_2_INT)  /* 割込みハンドラ番号 */
#define INTNO_TIMER2     (0x20000 | SYS_CLK_TIMER_2_INT)  /* 割込み番号 */
#define INTPRI_TIMER2    (-6)            /* 割込み優先度 */
#define INTATR_TIMER2    0U              /* 割込み属性 */

#define INHNO_TIMER3     (0x30000 | SYS_CLK_TIMER_3_INT)  /* 割込みハンドラ番号 */
#define INTNO_TIMER3     (0x30000 | SYS_CLK_TIMER_3_INT)  /* 割込み番号 */
#define INTPRI_TIMER3    (-6)            /* 割込み優先度 */
#define INTATR_TIMER3    0U              /* 割込み属性 */

#define INHNO_TIMER4     (0x40000 | SYS_CLK_TIMER_4_INT)  /* 割込みハンドラ番号 */
#define INTNO_TIMER4     (0x40000 | SYS_CLK_TIMER_4_INT)  /* 割込み番号 */
#define INTPRI_TIMER4    (-6)            /* 割込み優先度 */
#define INTATR_TIMER4    0U              /* 割込み属性 */

/*
 *  グローバルタイマ方式用の定義
 */
#if TOPPERS_SYSTIM_PRCID == 1
#define INHNO_TIMER_SYSTIM    (0x10000|SYS_CLK_TIMER_1_INT)  /* 割込みハンドラ番号 */
#define INTNO_TIMER_SYSTIM    (0x10000|SYS_CLK_TIMER_1_INT)  /* 割込み番号 */
#elif TOPPERS_SYSTIM_PRCID == 2
#define INHNO_TIMER_SYSTIM    (0x20000|SYS_CLK_TIMER_2_INT)  /* 割込みハンドラ番号 */
#define INTNO_TIMER_SYSTIM    (0x20000|SYS_CLK_TIMER_2_INT)  /* 割込み番号 */
#elif TOPPERS_SYSTIM_PRCID == 3
#define INHNO_TIMER_SYSTIM    (0x30000|SYS_CLK_TIMER_3_INT)  /* 割込みハンドラ番号 */
#define INTNO_TIMER_SYSTIM    (0x30000|SYS_CLK_TIMER_3_INT)  /* 割込み番号 */
#elif TOPPERS_SYSTIM_PRCID == 4
#define INHNO_TIMER_SYSTIM    (0x40000|SYS_CLK_TIMER_4_INT)  /* 割込みハンドラ番号 */
#define INTNO_TIMER_SYSTIM    (0x40000|SYS_CLK_TIMER_4_INT)  /* 割込み番号 */
#endif /* TOPPERS_SYSTIM_PRCID == 1 */

#define INTPRI_TIMER_SYSTIM   -6    /* 割込み優先度 */
#define INTATR_TIMER_SYSTIM    0U   /* 割込み属性 */

/*
 * プロセッサ依存部で定義する
 */ 
#include "nios2_gcc/avalon_timer.h"

#endif /* TOPPERS_TARGET_TIMER_H */
