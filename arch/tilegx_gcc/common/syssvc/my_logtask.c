/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: logtask.c 569 2010-04-15 02:23:27Z ertl-honda $
 */

/*
 *		システムログタスク
 */

#include <kernel.h>
#include <t_syslog.h>
#include <log_output.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "syssvc/logtask.h"

/*
 *  システムログタスクの変数配置のディフォルト定義
 */
#ifndef SEC_LOGTASK
#define SEC_LOGTASK(type, variable) type variable
#endif /* SEC_PREC1_SYSLOG */

#ifndef SEC_LOGTASK_BEGIN
#define SEC_LOGTASK_BEGIN
#endif /* SEC_LOGTASK_BEGIN */

#ifndef SEC_LOGTASK_END
#define SEC_LOGTASK_END
#endif /* SEC_LOGTASK_END */

#ifndef SEC_PRC1_LOGTASK
#define SEC_PRC1_LOGTASK(type, variable) type variable
#endif /* SEC_PREC1_SYSLOG */

#ifndef SEC_PRC1_LOGTASK_BEGIN
#define SEC_PRC1_LOGTASK_BEGIN
#endif /* SEC_PRC1_LOGTASK_BEGIN */

#ifndef SEC_PRC1_LOGTASK_END
#define SEC_PRC1_LOGTASK_END
#endif /* SEC_PREC1_LOGTASK_END */

#ifndef SEC_PRC2_LOGTASK
#define SEC_PRC2_LOGTASK(type, variable) type variable
#endif /* SEC_PREC2_SYSLOG */

#ifndef SEC_PRC2_LOGTASK_BEGIN
#define SEC_PRC2_LOGTASK_BEGIN
#endif /* SEC_PRC2_LOGTASK_BEGIN */

#ifndef SEC_PRC2_LOGTASK_END
#define SEC_PRC2_LOGTASK_END
#endif /* SEC_PREC2_LOGTASK_END */

#ifndef SEC_PRC3_LOGTASK
#define SEC_PRC3_LOGTASK(type, variable) type variable
#endif /* SEC_PREC3_SYSLOG */

#ifndef SEC_PRC3_LOGTASK_BEGIN
#define SEC_PRC3_LOGTASK_BEGIN
#endif /* SEC_PRC3_LOGTASK_BEGIN */

#ifndef SEC_PRC3_LOGTASK_END
#define SEC_PRC3_LOGTASK_END
#endif /* SEC_PREC3_LOGTASK_END */

#ifndef SEC_PRC4_LOGTASK
#define SEC_PRC4_LOGTASK(type, variable) type variable
#endif /* SEC_PREC4_SYSLOG */

#ifndef SEC_PRC4_LOGTASK_BEGIN
#define SEC_PRC4_LOGTASK_BEGIN
#endif /* SEC_PRC4_LOGTASK_BEGIN */

#ifndef SEC_PRC4_LOGTASK_END
#define SEC_PRC4_LOGTASK_END
#endif /* SEC_PREC4_LOGTASK_END */

/*
 *  システムログタスクの出力先のポートIDのテーブル
 */
#ifdef G_SYSLOG

SEC_LOGTASK_BEGIN
SEC_LOGTASK(static ID, logtask_portid);
SEC_LOGTASK_END

#else  /* G_SYSLOG */

#if TNUM_PRCID >= 1
SEC_PRC1_LOGTASK_BEGIN
SEC_PRC1_LOGTASK(static ID, logtask_portid_prc1);
SEC_PRC1_LOGTASK_END
#endif /* TNUM_PRCID >= 1 */

#if TNUM_PRCID >= 2
SEC_PRC2_LOGTASK_BEGIN
SEC_PRC2_LOGTASK(static ID, logtask_portid_prc2);
SEC_PRC2_LOGTASK_END
#endif /* TNUM_PRCID >= 2 */

#if TNUM_PRCID >= 3
SEC_PRC3_LOGTASK_BEGIN
SEC_PRC3_LOGTASK(static ID, logtask_portid_prc3);
SEC_PRC3_LOGTASK_END
#endif /* TNUM_PRCID >= 3 */

#if TNUM_PRCID >= 4
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc4);
SEC_PRC4_LOGTASK_END
#endif /* TNUM_PRCID >= 4 */

#if 1 // Support up to 36 cores. -- ertl-liyixiao

/* TODO: Generated from following Python script.
for i in range(1, 37):
	print("""
#if TNUM_PRCID >= %(prc)s
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc%(prc)s);
SEC_PRC4_LOGTASK_END
#endif""" % {'prc':i})
*/

#if TNUM_PRCID >= 5
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc5);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 6
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc6);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 7
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc7);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 8
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc8);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 9
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc9);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 10
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc10);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 11
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc11);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 12
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc12);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 13
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc13);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 14
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc14);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 15
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc15);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 16
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc16);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 17
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc17);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 18
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc18);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 19
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc19);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 20
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc20);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 21
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc21);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 22
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc22);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 23
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc23);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 24
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc24);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 25
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc25);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 26
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc26);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 27
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc27);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 28
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc28);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 29
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc29);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 30
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc30);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 31
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc31);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 32
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc32);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 33
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc33);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 34
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc34);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 35
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc35);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID >= 36
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc36);
SEC_PRC4_LOGTASK_END
#endif

#if TNUM_PRCID > 36
#error Number of processor cores exceeds limit (36).
#endif

#else

#if TNUM_PRCID >= 5
#error Logtask Not Support more than 5 processor!
#endif /* TNUM_PRCID >= 5 */

#endif

static ID* const	p_logtask_portid_table[] = {
#if TNUM_PRCID >= 1
	&logtask_portid_prc1,
#endif /* TNUM_PRCID >= 1 */
#if TNUM_PRCID >= 2
	&logtask_portid_prc2,
#endif /* TNUM_PRCID >= 2 */
#if TNUM_PRCID >= 3
	&logtask_portid_prc3,
#endif /* TNUM_PRCID >= 3 */
#if TNUM_PRCID >= 4
	&logtask_portid_prc4,
#endif /* TNUM_PRCID >= 4 */
#if 1 // Support up to 36 cores. -- ertl-liyixiao
/* TODO: Generated from following Python script.
for i in range(1, 37):
	print("""#if TNUM_PRCID >= %(prc)s
	&logtask_portid_prc%(prc)s,
#endif""" % {'prc':i})
*/
#if TNUM_PRCID >= 5
	&logtask_portid_prc5,
#endif
#if TNUM_PRCID >= 6
	&logtask_portid_prc6,
#endif
#if TNUM_PRCID >= 7
	&logtask_portid_prc7,
#endif
#if TNUM_PRCID >= 8
	&logtask_portid_prc8,
#endif
#if TNUM_PRCID >= 9
	&logtask_portid_prc9,
#endif
#if TNUM_PRCID >= 10
	&logtask_portid_prc10,
#endif
#if TNUM_PRCID >= 11
	&logtask_portid_prc11,
#endif
#if TNUM_PRCID >= 12
	&logtask_portid_prc12,
#endif
#if TNUM_PRCID >= 13
	&logtask_portid_prc13,
#endif
#if TNUM_PRCID >= 14
	&logtask_portid_prc14,
#endif
#if TNUM_PRCID >= 15
	&logtask_portid_prc15,
#endif
#if TNUM_PRCID >= 16
	&logtask_portid_prc16,
#endif
#if TNUM_PRCID >= 17
	&logtask_portid_prc17,
#endif
#if TNUM_PRCID >= 18
	&logtask_portid_prc18,
#endif
#if TNUM_PRCID >= 19
	&logtask_portid_prc19,
#endif
#if TNUM_PRCID >= 20
	&logtask_portid_prc20,
#endif
#if TNUM_PRCID >= 21
	&logtask_portid_prc21,
#endif
#if TNUM_PRCID >= 22
	&logtask_portid_prc22,
#endif
#if TNUM_PRCID >= 23
	&logtask_portid_prc23,
#endif
#if TNUM_PRCID >= 24
	&logtask_portid_prc24,
#endif
#if TNUM_PRCID >= 25
	&logtask_portid_prc25,
#endif
#if TNUM_PRCID >= 26
	&logtask_portid_prc26,
#endif
#if TNUM_PRCID >= 27
	&logtask_portid_prc27,
#endif
#if TNUM_PRCID >= 28
	&logtask_portid_prc28,
#endif
#if TNUM_PRCID >= 29
	&logtask_portid_prc29,
#endif
#if TNUM_PRCID >= 30
	&logtask_portid_prc30,
#endif
#if TNUM_PRCID >= 31
	&logtask_portid_prc31,
#endif
#if TNUM_PRCID >= 32
	&logtask_portid_prc32,
#endif
#if TNUM_PRCID >= 33
	&logtask_portid_prc33,
#endif
#if TNUM_PRCID >= 34
	&logtask_portid_prc34,
#endif
#if TNUM_PRCID >= 35
	&logtask_portid_prc35,
#endif
#if TNUM_PRCID >= 36
	&logtask_portid_prc36,
#endif
#endif
};
#endif /* G_SYSLOG */

/*
 *  自コアのポートIDへのアクセスマクロ
 */
#ifdef G_SYSLOG

Inline ID
get_my_logtask_portid(void)
{
	return logtask_portid;
}

Inline void
set_my_logtask_portid(ID id)
{
	logtask_portid = id;
}

#else  /* G_SYSLOG */

Inline ID
get_my_logtask_portid(void)
{
	ID prcid;
	sil_get_pid(&prcid);

	return *(p_logtask_portid_table[prcid - 1]);
}

Inline void
set_my_logtask_portid(ID id)
{
	ID prcid;
	sil_get_pid(&prcid);

	*(p_logtask_portid_table[prcid - 1]) = id;
}

#endif /* G_SYSLOG */

/*
 *  シリアルインタフェースへの1文字出力
 */
static void
logtask_putc(char_t c)
{

	ID my_logtask_portid = get_my_logtask_portid();
#if defined(G_SYSLOG) // Buffer in G_SYSLOG mode, TODO: support buffer in !G_SYSLOG mode
	static char buffer[100];
	static uint32_t buffer_left = sizeof(buffer);
	buffer[sizeof(buffer) - buffer_left--] = c;
	if (buffer_left == 0) {
		buffer_left = sizeof(buffer);
		serial_wri_dat(my_logtask_portid, buffer, sizeof(buffer));
	}
#else
	serial_wri_dat(my_logtask_portid, &c, 1);
#endif
}

/*
 *  システムログ出力の待ち合わせ
 */
ER
logtask_flush(uint_t count)
{
	T_SYSLOG_RLOG	rlog;
	T_SERIAL_RPOR	rpor;
	ER				ercd, rercd;
	ID my_logtask_portid = get_my_logtask_portid();

	if (sns_dpn()) {
		ercd = E_CTX;
	}
	else {
		for (;;) {
			if (syslog_ref_log(&rlog) < 0) {
				ercd = E_SYS;
				goto error_exit;
			}
			if (rlog.count <= count) {
				if (count == 0U) {
					/*
					 *  countが0の場合には，シリアルバッファが空かを確
					 *  認する．
					 */
					if (serial_ref_por(my_logtask_portid, &rpor) < 0) {
						ercd = E_SYS;
						goto error_exit;
					}
					if (rpor.wricnt == 0U) {
						ercd = E_OK;
						goto error_exit;
					}
				}
				else {
					ercd = E_OK;
					goto error_exit;
				}
			}

			/*
			 *  LOGTASK_FLUSH_WAITミリ秒待つ．
			 */
			rercd = dly_tsk(LOGTASK_FLUSH_WAIT);
			if (rercd < 0) {
				ercd = (rercd == E_RLWAI) ? rercd : E_SYS;
				goto error_exit;
			}
		}
	}

  error_exit:
	return(ercd);
}

/*
 *  システムログタスクの本体
 */
void
logtask_main(intptr_t exinf)
{
	SYSLOG	syslog;
	uint_t	lost;
	ER_UINT	rercd;
	ID my_logtask_portid;

	my_logtask_portid = (ID) exinf;
	set_my_logtask_portid(my_logtask_portid);
	serial_opn_por(my_logtask_portid);
	syslog_msk_log(LOG_UPTO(LOG_NOTICE), LOG_UPTO(LOG_EMERG));
	syslog_1(LOG_NOTICE, "System logging task is started on port %d.",
													my_logtask_portid);
	for (;;) {
		lost = 0U;
		while ((rercd = syslog_rea_log(&syslog)) >= 0) {
			lost += (uint_t) rercd;
			if (syslog.logtype >= LOG_TYPE_COMMENT) {
				if (lost > 0U) {
					syslog_lostmsg(lost, logtask_putc);
					lost = 0U;
				}
				syslog_print(&syslog, logtask_putc);
				logtask_putc('\n');
			}
		}
		if (lost > 0U) {
			syslog_lostmsg(lost, logtask_putc);
		}
		if(E_OK != dly_tsk(LOGTASK_INTERVAL)){
			syslog_0(LOG_NOTICE, "syslog : Error dly_tsk() !");
		}
	}
}

/*
 *  システムログタスクの終了処理
 */
void
logtask_terminate(intptr_t exinf)
{
	char_t	c;
	SYSLOG	syslog;
	bool_t	msgflg = false;
	ER_UINT	rercd;
	ID my_logtask_portid = get_my_logtask_portid();

	/*
	 *  シリアルインタフェースドライバの送信バッファに蓄積されたデータ
	 *  を，低レベル出力機能を用いて出力する．
	 */
	while (serial_get_chr(my_logtask_portid, &c)) {
		target_fput_log(c);
	}

	/*
	 *  ログバッファに記録されたログ情報を，低レベル出力機能を用いて出
	 *  力する．
	 */
	while ((rercd = syslog_rea_log(&syslog)) >= 0) {
		if (!msgflg) {
			/*
			 *  ログバッファに残ったログ情報であることを示す文字列を出
			 *  力する．
			 */
			syslog_printf("-- buffered messages --\n", NULL, target_fput_log);
			msgflg = true;
		}
		if (rercd > 0) {
			syslog_lostmsg((uint_t) rercd, target_fput_log);
		}
		if (syslog.logtype >= LOG_TYPE_COMMENT) {
			syslog_print(&syslog, target_fput_log);
			target_fput_log('\n');
		}
	}
}
