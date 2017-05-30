/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2008 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: marzen.c 943 2012-10-19 07:50:40Z ertl-honda $
 */

#include "kernel_impl.h"
#include "marzen.h"
#include "sh_scif.h"

#ifndef G_SYSLOG
#error Must use G_SYSLOG!!
#endif /* !G_SYSLOG */


/*
 *  UARTからのポーリング出力
 */
void
marzen_uart_putc(char_t c)
{
	sh_scif_pol_putc(c, 1);
}


/*
 *  ポーリング出力のための初期化
 */
void
marzen_uart_init(void)
{
	/* 初期化 */
	sh_scif_init(1);
}

static void
pin_init(void)
{
	set_guard_reg(MOD_SEL, 0x01c00000, 0x00800000);
	set_guard_reg(MOD_SEL2, 0x0c000000, 0x04000000);
	set_guard_reg(GPSR0, 0x80000000, 0x00000000);
	set_guard_reg(IPSR3, 0xe0000000, 0x60000000);
	set_guard_reg(GPSR0, 0x00000000, 0x80000000);
	set_guard_reg(GPSR1, 0x00000002, 0x00000000);
	set_guard_reg(IPSR4, 0x0000001c, 0x0000000c);
	set_guard_reg(GPSR1, 0x00000000, 0x00000002);
	set_guard_reg(GPSR3, 0x0c000000, 0x00000000);
	set_guard_reg(IPSR1, 0x01e00000, 0x01400000);
	set_guard_reg(GPSR3, 0x00000000, 0x0c000000);
	set_guard_reg(GPSR4, 0x00000020, 0x00000000);
	set_guard_reg(IPSR6, 0x00038000, 0x00028000);
	set_guard_reg(GPSR4, 0x00000000, 0x00000020);
}


/*
 *  ボード依存の初期化
 */
void
marzen_init(void)
{
	/* ピンの初期化 */
	pin_init();

	if ((sil_rew_mem((void*)MODEMR) & MD1) == MD1) {
		timer_rate_hz = 62500000 / 4;
	}
	else {
		timer_rate_hz = 46875000/ 4;
	}
}
