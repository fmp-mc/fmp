/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel  
 * 
 *  Copyright (C) 2006-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: marzen.h 943 2012-10-19 07:50:40Z ertl-honda $
 */

/*
 *  Marzen用ドライバ定義
 */

#ifndef TOPPERS_MARZEN_H
#define TOPPERS_MARZEN_H

#include <sil.h>
#include "r_car_h1.h"

/*
 * コアクロック（1000MHz）
 */
#define MARZEN_CORE_CLK  1000

/*
 *  MPCore内蔵のプライベートタイマを1MSで動作させるためのプリスケーラー
 *  の設定値．1Mhzに設定コアクロックの1/4のPERIPHCLKで駆動される．
 */
#define MPCORE_TM_PS_1MS    (MARZEN_CORE_CLK/4)

/*
 *  MPCore内蔵のタイマを1MSで動作させるためのカウンタ値
 */
#define MPCORE_TM_LOAD_1MS    1000

/*
 *  TMUのタイマ値の内部表現とミリ秒単位との変換
 */
#define TMU_TIMER_CLOCK  (62500 / 4)

/*
 *  グローバルタイマのクロック周波数
 */
#define MPCORE_GTC_CLOCK_FREQ_MHZ     (MARZEN_CORE_CLK/4)

#ifndef TOPPERS_MACRO_ONLY
/*
 *  UARTからのポーリング出力
 */
extern void marzen_uart_putc(char_t c);

/*
 * ポーリング出力のためのUARTの初期化
 */
extern void marzen_uart_init(void);

/*
 *  ボード依存の初期化
 */
extern void marzen_init(void);

/*
 *  timer_rate_hz
 */
uint32_t timer_rate_hz;

/*
 *  開発環境依存の処理(T.B.D)
 */
Inline void
marzen_exit(void)
{
	while(1);
}

/*
 *  トレースログに関する定義
 */
//#define TRACE_HW_INIT()   scu_counter_init()
//#define TRACE_GET_TIM()   ((scu_counter_get_current() * 1000) / NAVIENGINE_CORE_CLK)

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_MARZEN_H */
