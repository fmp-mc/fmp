/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  @(#) $Id: serial.c 898 2012-02-24 05:15:21Z ertl-honda $
 */

/*
 *		シリアルインタフェースドライバ
 */

#include <kernel.h>
#include <t_syslog.h>
#include "target_syssvc.h"
#include "target_serial.h"
#include "syssvc/serial.h"
#include "kernel_cfg.h"

/*
 *  シリアルインタフェースドライバの変数配置のディフォルト定義
 */
#ifndef SEC_SERIAL1
#define SEC_SERIAL1(type, variable) type variable
#endif /* SEC_SERIAL1 */

#ifndef SEC_SERIAL1_BEGIN
#define SEC_SERIAL1_BEGIN
#endif /* SEC_SERIAL1_BEGIN */

#ifndef SEC_SERIAL1_END
#define SEC_SERIAL1_END
#endif /* SEC_SERIAL1_END */

#ifndef SEC_SERIAL2
#define SEC_SERIAL2(type, variable) type variable
#endif /* SEC_SERIAL2 */

#ifndef SEC_SERIAL2_BEGIN
#define SEC_SERIAL2_BEGIN
#endif /* SEC_SERIAL2_BEGIN */

#ifndef SEC_SERIAL2_END
#define SEC_SERIAL2_END
#endif /* SEC_SERIAL2_END */

#ifndef SEC_SERIAL3
#define SEC_SERIAL3(type, variable) type variable
#endif /* SEC_SERIAL3 */

#ifndef SEC_SERIAL3_BEGIN
#define SEC_SERIAL3_BEGIN
#endif /* SEC_SERIAL3_BEGIN */

#ifndef SEC_SERIAL3_END
#define SEC_SERIAL3_END
#endif /* SEC_SERIAL3_END */

#ifndef SEC_SERIAL4
#define SEC_SERIAL4(type, variable) type variable
#endif /* SEC_SERIAL4 */

#ifndef SEC_SERIAL4_BEGIN
#define SEC_SERIAL4_BEGIN
#endif /* SEC_SERIAL4_BEGIN */

#ifndef SEC_SERIAL4_END
#define SEC_SERIAL4_END
#endif /* SEC_SERIAL4_END */

/*
 *  バッファサイズのデフォルト値とバッファの定義
 */
#ifndef SERIAL_RCV_BUFSZ1
#define	SERIAL_RCV_BUFSZ1	256			/* ポート1の受信バッファサイズ */
#endif /* SERIAL_RCV_BUFSZ1 */

#ifndef SERIAL_SND_BUFSZ1
#define	SERIAL_SND_BUFSZ1	256			/* ポート1の送信バッファサイズ */
#endif /* SERIAL_SND_BUFSZ1 */

SEC_SERIAL1_BEGIN
SEC_SERIAL1(static char_t, rcv_buffer1[SERIAL_RCV_BUFSZ1]);
SEC_SERIAL1(static char_t, snd_buffer1[SERIAL_SND_BUFSZ1]);
SEC_SERIAL1_END

#if TNUM_PORT >= 2						/* ポート2に関する定義 */

#ifndef SERIAL_RCV_BUFSZ2
#define	SERIAL_RCV_BUFSZ2	256			/* ポート2の受信バッファサイズ */
#endif /* SERIAL_RCV_BUFSZ2 */

#ifndef SERIAL_SND_BUFSZ2
#define	SERIAL_SND_BUFSZ2	256			/* ポート2の送信バッファサイズ */
#endif /* SERIAL_SND_BUFSZ2 */

SEC_SERIAL2_BEGIN
SEC_SERIAL2(static char_t, rcv_buffer2[SERIAL_RCV_BUFSZ2]);
SEC_SERIAL2(static char_t, snd_buffer2[SERIAL_SND_BUFSZ2]);
SEC_SERIAL2_END

#endif /* TNUM_PORT >= 2 */

#if TNUM_PORT >= 3						/* ポート3に関する定義 */

#ifndef SERIAL_RCV_BUFSZ3
#define	SERIAL_RCV_BUFSZ3	256			/* ポート3の受信バッファサイズ */
#endif /* SERIAL_RCV_BUFSZ3 */

#ifndef SERIAL_SND_BUFSZ3
#define	SERIAL_SND_BUFSZ3	256			/* ポート3の送信バッファサイズ */
#endif /* SERIAL_SND_BUFSZ3 */

SEC_SERIAL3_BEGIN
SEC_SERIAL3(static char_t, rcv_buffer3[SERIAL_RCV_BUFSZ3]);
SEC_SERIAL3(static char_t, snd_buffer3[SERIAL_SND_BUFSZ3]);
SEC_SERIAL3_END

#endif /* TNUM_PORT >= 3 */

#if TNUM_PORT >= 4						/* ポート4に関する定義 */

#ifndef SERIAL_RCV_BUFSZ4
#define	SERIAL_RCV_BUFSZ4	256			/* ポート4の受信バッファサイズ */
#endif /* SERIAL_RCV_BUFSZ4 */

#ifndef SERIAL_SND_BUFSZ4
#define	SERIAL_SND_BUFSZ4	256			/* ポート4の送信バッファサイズ */
#endif /* SERIAL_SND_BUFSZ4 */

SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer4[SERIAL_RCV_BUFSZ4]);
SEC_SERIAL4(static char_t, snd_buffer4[SERIAL_SND_BUFSZ4]);
SEC_SERIAL4_END

#endif /* TNUM_PORT >= 4 */

#if 1 // Support up to 36 cores. -- ertl-liyixiao

/* TODO: Generated from following Python script.
for i in range(1, 37):
	print("""
#if TNUM_PORT >= %(prc)s
#define	SERIAL_RCV_BUFSZ%(prc)s 256
#define	SERIAL_SND_BUFSZ%(prc)s 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer%(prc)s[SERIAL_RCV_BUFSZ%(prc)s]);
SEC_SERIAL4(static char_t, snd_buffer%(prc)s[SERIAL_SND_BUFSZ%(prc)s]);
SEC_SERIAL4_END
#endif""" % {'prc':i})
*/

#if TNUM_PORT >= 5
#define	SERIAL_RCV_BUFSZ5 256
#define	SERIAL_SND_BUFSZ5 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer5[SERIAL_RCV_BUFSZ5]);
SEC_SERIAL4(static char_t, snd_buffer5[SERIAL_SND_BUFSZ5]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 6
#define	SERIAL_RCV_BUFSZ6 256
#define	SERIAL_SND_BUFSZ6 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer6[SERIAL_RCV_BUFSZ6]);
SEC_SERIAL4(static char_t, snd_buffer6[SERIAL_SND_BUFSZ6]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 7
#define	SERIAL_RCV_BUFSZ7 256
#define	SERIAL_SND_BUFSZ7 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer7[SERIAL_RCV_BUFSZ7]);
SEC_SERIAL4(static char_t, snd_buffer7[SERIAL_SND_BUFSZ7]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 8
#define	SERIAL_RCV_BUFSZ8 256
#define	SERIAL_SND_BUFSZ8 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer8[SERIAL_RCV_BUFSZ8]);
SEC_SERIAL4(static char_t, snd_buffer8[SERIAL_SND_BUFSZ8]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 9
#define	SERIAL_RCV_BUFSZ9 256
#define	SERIAL_SND_BUFSZ9 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer9[SERIAL_RCV_BUFSZ9]);
SEC_SERIAL4(static char_t, snd_buffer9[SERIAL_SND_BUFSZ9]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 10
#define	SERIAL_RCV_BUFSZ10 256
#define	SERIAL_SND_BUFSZ10 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer10[SERIAL_RCV_BUFSZ10]);
SEC_SERIAL4(static char_t, snd_buffer10[SERIAL_SND_BUFSZ10]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 11
#define	SERIAL_RCV_BUFSZ11 256
#define	SERIAL_SND_BUFSZ11 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer11[SERIAL_RCV_BUFSZ11]);
SEC_SERIAL4(static char_t, snd_buffer11[SERIAL_SND_BUFSZ11]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 12
#define	SERIAL_RCV_BUFSZ12 256
#define	SERIAL_SND_BUFSZ12 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer12[SERIAL_RCV_BUFSZ12]);
SEC_SERIAL4(static char_t, snd_buffer12[SERIAL_SND_BUFSZ12]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 13
#define	SERIAL_RCV_BUFSZ13 256
#define	SERIAL_SND_BUFSZ13 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer13[SERIAL_RCV_BUFSZ13]);
SEC_SERIAL4(static char_t, snd_buffer13[SERIAL_SND_BUFSZ13]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 14
#define	SERIAL_RCV_BUFSZ14 256
#define	SERIAL_SND_BUFSZ14 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer14[SERIAL_RCV_BUFSZ14]);
SEC_SERIAL4(static char_t, snd_buffer14[SERIAL_SND_BUFSZ14]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 15
#define	SERIAL_RCV_BUFSZ15 256
#define	SERIAL_SND_BUFSZ15 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer15[SERIAL_RCV_BUFSZ15]);
SEC_SERIAL4(static char_t, snd_buffer15[SERIAL_SND_BUFSZ15]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 16
#define	SERIAL_RCV_BUFSZ16 256
#define	SERIAL_SND_BUFSZ16 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer16[SERIAL_RCV_BUFSZ16]);
SEC_SERIAL4(static char_t, snd_buffer16[SERIAL_SND_BUFSZ16]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 17
#define	SERIAL_RCV_BUFSZ17 256
#define	SERIAL_SND_BUFSZ17 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer17[SERIAL_RCV_BUFSZ17]);
SEC_SERIAL4(static char_t, snd_buffer17[SERIAL_SND_BUFSZ17]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 18
#define	SERIAL_RCV_BUFSZ18 256
#define	SERIAL_SND_BUFSZ18 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer18[SERIAL_RCV_BUFSZ18]);
SEC_SERIAL4(static char_t, snd_buffer18[SERIAL_SND_BUFSZ18]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 19
#define	SERIAL_RCV_BUFSZ19 256
#define	SERIAL_SND_BUFSZ19 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer19[SERIAL_RCV_BUFSZ19]);
SEC_SERIAL4(static char_t, snd_buffer19[SERIAL_SND_BUFSZ19]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 20
#define	SERIAL_RCV_BUFSZ20 256
#define	SERIAL_SND_BUFSZ20 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer20[SERIAL_RCV_BUFSZ20]);
SEC_SERIAL4(static char_t, snd_buffer20[SERIAL_SND_BUFSZ20]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 21
#define	SERIAL_RCV_BUFSZ21 256
#define	SERIAL_SND_BUFSZ21 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer21[SERIAL_RCV_BUFSZ21]);
SEC_SERIAL4(static char_t, snd_buffer21[SERIAL_SND_BUFSZ21]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 22
#define	SERIAL_RCV_BUFSZ22 256
#define	SERIAL_SND_BUFSZ22 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer22[SERIAL_RCV_BUFSZ22]);
SEC_SERIAL4(static char_t, snd_buffer22[SERIAL_SND_BUFSZ22]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 23
#define	SERIAL_RCV_BUFSZ23 256
#define	SERIAL_SND_BUFSZ23 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer23[SERIAL_RCV_BUFSZ23]);
SEC_SERIAL4(static char_t, snd_buffer23[SERIAL_SND_BUFSZ23]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 24
#define	SERIAL_RCV_BUFSZ24 256
#define	SERIAL_SND_BUFSZ24 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer24[SERIAL_RCV_BUFSZ24]);
SEC_SERIAL4(static char_t, snd_buffer24[SERIAL_SND_BUFSZ24]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 25
#define	SERIAL_RCV_BUFSZ25 256
#define	SERIAL_SND_BUFSZ25 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer25[SERIAL_RCV_BUFSZ25]);
SEC_SERIAL4(static char_t, snd_buffer25[SERIAL_SND_BUFSZ25]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 26
#define	SERIAL_RCV_BUFSZ26 256
#define	SERIAL_SND_BUFSZ26 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer26[SERIAL_RCV_BUFSZ26]);
SEC_SERIAL4(static char_t, snd_buffer26[SERIAL_SND_BUFSZ26]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 27
#define	SERIAL_RCV_BUFSZ27 256
#define	SERIAL_SND_BUFSZ27 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer27[SERIAL_RCV_BUFSZ27]);
SEC_SERIAL4(static char_t, snd_buffer27[SERIAL_SND_BUFSZ27]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 28
#define	SERIAL_RCV_BUFSZ28 256
#define	SERIAL_SND_BUFSZ28 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer28[SERIAL_RCV_BUFSZ28]);
SEC_SERIAL4(static char_t, snd_buffer28[SERIAL_SND_BUFSZ28]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 29
#define	SERIAL_RCV_BUFSZ29 256
#define	SERIAL_SND_BUFSZ29 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer29[SERIAL_RCV_BUFSZ29]);
SEC_SERIAL4(static char_t, snd_buffer29[SERIAL_SND_BUFSZ29]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 30
#define	SERIAL_RCV_BUFSZ30 256
#define	SERIAL_SND_BUFSZ30 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer30[SERIAL_RCV_BUFSZ30]);
SEC_SERIAL4(static char_t, snd_buffer30[SERIAL_SND_BUFSZ30]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 31
#define	SERIAL_RCV_BUFSZ31 256
#define	SERIAL_SND_BUFSZ31 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer31[SERIAL_RCV_BUFSZ31]);
SEC_SERIAL4(static char_t, snd_buffer31[SERIAL_SND_BUFSZ31]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 32
#define	SERIAL_RCV_BUFSZ32 256
#define	SERIAL_SND_BUFSZ32 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer32[SERIAL_RCV_BUFSZ32]);
SEC_SERIAL4(static char_t, snd_buffer32[SERIAL_SND_BUFSZ32]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 33
#define	SERIAL_RCV_BUFSZ33 256
#define	SERIAL_SND_BUFSZ33 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer33[SERIAL_RCV_BUFSZ33]);
SEC_SERIAL4(static char_t, snd_buffer33[SERIAL_SND_BUFSZ33]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 34
#define	SERIAL_RCV_BUFSZ34 256
#define	SERIAL_SND_BUFSZ34 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer34[SERIAL_RCV_BUFSZ34]);
SEC_SERIAL4(static char_t, snd_buffer34[SERIAL_SND_BUFSZ34]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 35
#define	SERIAL_RCV_BUFSZ35 256
#define	SERIAL_SND_BUFSZ35 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer35[SERIAL_RCV_BUFSZ35]);
SEC_SERIAL4(static char_t, snd_buffer35[SERIAL_SND_BUFSZ35]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 36
#define	SERIAL_RCV_BUFSZ36 256
#define	SERIAL_SND_BUFSZ36 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer36[SERIAL_RCV_BUFSZ36]);
SEC_SERIAL4(static char_t, snd_buffer36[SERIAL_SND_BUFSZ36]);
SEC_SERIAL4_END
#endif

#if !defined(G_SYSLOG) && TNUM_PRCID > 36
#error Number of processor cores exceeds limit (36).
#endif

#else

#if TNUM_PRCID >= 5
#error Serial driver Not Support more than 5 processor!
#endif /* TNUM_PRCID >= 5 */

#endif

/*
 *  終了処理の際に送信を待つ最大時間（msec単位）
 */
#ifndef SERIAL_MAX_FLUSH_WAIT
#define SERIAL_MAX_FLUSH_WAIT	1000
#endif /* SERIAL_MAX_FLUSH_WAIT */

/*
 *  フロー制御に関連する定数とマクロ
 */
#define	FC_STOP			'\023'		/* コントロール-S */
#define	FC_START		'\021'		/* コントロール-Q */

#define BUFCNT_STOP(bufsz)		((bufsz) * 3 / 4)	/* STOPを送る基準文字数 */
#define BUFCNT_START(bufsz)		((bufsz) / 2)		/* STARTを送る基準文字数 */

/*
 *  シリアルポート初期化ブロック
 */
typedef struct serial_port_initialization_block {
	ID		rcv_semid;		/* 受信バッファ管理用セマフォのID */
	ID		snd_semid;		/* 送信バッファ管理用セマフォのID */
	uint_t	rcv_bufsz;		/* 受信バッファサイズ */
	char_t	*rcv_buffer;	/* 受信バッファ */
	uint_t	snd_bufsz;		/* 送信バッファサイズ */
	char_t	*snd_buffer;	/* 送信バッファ */
} SPINIB;

static const SPINIB spinib_table[TNUM_PORT] = {
	{ SERIAL_RCV_SEM1, SERIAL_SND_SEM1,
	  SERIAL_RCV_BUFSZ1, rcv_buffer1,
	  SERIAL_SND_BUFSZ1, snd_buffer1 },
#if TNUM_PORT >= 2
	{ SERIAL_RCV_SEM2, SERIAL_SND_SEM2,
	  SERIAL_RCV_BUFSZ2, rcv_buffer2,
	  SERIAL_SND_BUFSZ2, snd_buffer2 },
#endif /* TNUM_PORT >= 2 */
#if TNUM_PORT >= 3
	{ SERIAL_RCV_SEM3, SERIAL_SND_SEM3,
	  SERIAL_RCV_BUFSZ3, rcv_buffer3,
	  SERIAL_SND_BUFSZ3, snd_buffer3 },
#endif /* TNUM_PORT >= 3 */
#if TNUM_PORT >= 4
	{ SERIAL_RCV_SEM4, SERIAL_SND_SEM4,
	  SERIAL_RCV_BUFSZ4, rcv_buffer4,
	  SERIAL_SND_BUFSZ4, snd_buffer4 },
#endif /* TNUM_PORT >= 4 */
#if 1 // Support up to 36 cores. -- ertl-liyixiao
/* TODO: Generated from following Python script.
for i in range(1, 37):
	print("""#if TNUM_PORT >= %(prc)s
	{ SERIAL_RCV_SEM%(prc)s, SERIAL_SND_SEM%(prc)s,
	  SERIAL_RCV_BUFSZ%(prc)s, rcv_buffer%(prc)s,
	  SERIAL_SND_BUFSZ%(prc)s, snd_buffer%(prc)s },
#endif""" % {'prc':i})
*/
#if TNUM_PORT >= 5
	{ SERIAL_RCV_SEM5, SERIAL_SND_SEM5,
	  SERIAL_RCV_BUFSZ5, rcv_buffer5,
	  SERIAL_SND_BUFSZ5, snd_buffer5 },
#endif
#if TNUM_PORT >= 6
	{ SERIAL_RCV_SEM6, SERIAL_SND_SEM6,
	  SERIAL_RCV_BUFSZ6, rcv_buffer6,
	  SERIAL_SND_BUFSZ6, snd_buffer6 },
#endif
#if TNUM_PORT >= 7
	{ SERIAL_RCV_SEM7, SERIAL_SND_SEM7,
	  SERIAL_RCV_BUFSZ7, rcv_buffer7,
	  SERIAL_SND_BUFSZ7, snd_buffer7 },
#endif
#if TNUM_PORT >= 8
	{ SERIAL_RCV_SEM8, SERIAL_SND_SEM8,
	  SERIAL_RCV_BUFSZ8, rcv_buffer8,
	  SERIAL_SND_BUFSZ8, snd_buffer8 },
#endif
#if TNUM_PORT >= 9
	{ SERIAL_RCV_SEM9, SERIAL_SND_SEM9,
	  SERIAL_RCV_BUFSZ9, rcv_buffer9,
	  SERIAL_SND_BUFSZ9, snd_buffer9 },
#endif
#if TNUM_PORT >= 10
	{ SERIAL_RCV_SEM10, SERIAL_SND_SEM10,
	  SERIAL_RCV_BUFSZ10, rcv_buffer10,
	  SERIAL_SND_BUFSZ10, snd_buffer10 },
#endif
#if TNUM_PORT >= 11
	{ SERIAL_RCV_SEM11, SERIAL_SND_SEM11,
	  SERIAL_RCV_BUFSZ11, rcv_buffer11,
	  SERIAL_SND_BUFSZ11, snd_buffer11 },
#endif
#if TNUM_PORT >= 12
	{ SERIAL_RCV_SEM12, SERIAL_SND_SEM12,
	  SERIAL_RCV_BUFSZ12, rcv_buffer12,
	  SERIAL_SND_BUFSZ12, snd_buffer12 },
#endif
#if TNUM_PORT >= 13
	{ SERIAL_RCV_SEM13, SERIAL_SND_SEM13,
	  SERIAL_RCV_BUFSZ13, rcv_buffer13,
	  SERIAL_SND_BUFSZ13, snd_buffer13 },
#endif
#if TNUM_PORT >= 14
	{ SERIAL_RCV_SEM14, SERIAL_SND_SEM14,
	  SERIAL_RCV_BUFSZ14, rcv_buffer14,
	  SERIAL_SND_BUFSZ14, snd_buffer14 },
#endif
#if TNUM_PORT >= 15
	{ SERIAL_RCV_SEM15, SERIAL_SND_SEM15,
	  SERIAL_RCV_BUFSZ15, rcv_buffer15,
	  SERIAL_SND_BUFSZ15, snd_buffer15 },
#endif
#if TNUM_PORT >= 16
	{ SERIAL_RCV_SEM16, SERIAL_SND_SEM16,
	  SERIAL_RCV_BUFSZ16, rcv_buffer16,
	  SERIAL_SND_BUFSZ16, snd_buffer16 },
#endif
#if TNUM_PORT >= 17
	{ SERIAL_RCV_SEM17, SERIAL_SND_SEM17,
	  SERIAL_RCV_BUFSZ17, rcv_buffer17,
	  SERIAL_SND_BUFSZ17, snd_buffer17 },
#endif
#if TNUM_PORT >= 18
	{ SERIAL_RCV_SEM18, SERIAL_SND_SEM18,
	  SERIAL_RCV_BUFSZ18, rcv_buffer18,
	  SERIAL_SND_BUFSZ18, snd_buffer18 },
#endif
#if TNUM_PORT >= 19
	{ SERIAL_RCV_SEM19, SERIAL_SND_SEM19,
	  SERIAL_RCV_BUFSZ19, rcv_buffer19,
	  SERIAL_SND_BUFSZ19, snd_buffer19 },
#endif
#if TNUM_PORT >= 20
	{ SERIAL_RCV_SEM20, SERIAL_SND_SEM20,
	  SERIAL_RCV_BUFSZ20, rcv_buffer20,
	  SERIAL_SND_BUFSZ20, snd_buffer20 },
#endif
#if TNUM_PORT >= 21
	{ SERIAL_RCV_SEM21, SERIAL_SND_SEM21,
	  SERIAL_RCV_BUFSZ21, rcv_buffer21,
	  SERIAL_SND_BUFSZ21, snd_buffer21 },
#endif
#if TNUM_PORT >= 22
	{ SERIAL_RCV_SEM22, SERIAL_SND_SEM22,
	  SERIAL_RCV_BUFSZ22, rcv_buffer22,
	  SERIAL_SND_BUFSZ22, snd_buffer22 },
#endif
#if TNUM_PORT >= 23
	{ SERIAL_RCV_SEM23, SERIAL_SND_SEM23,
	  SERIAL_RCV_BUFSZ23, rcv_buffer23,
	  SERIAL_SND_BUFSZ23, snd_buffer23 },
#endif
#if TNUM_PORT >= 24
	{ SERIAL_RCV_SEM24, SERIAL_SND_SEM24,
	  SERIAL_RCV_BUFSZ24, rcv_buffer24,
	  SERIAL_SND_BUFSZ24, snd_buffer24 },
#endif
#if TNUM_PORT >= 25
	{ SERIAL_RCV_SEM25, SERIAL_SND_SEM25,
	  SERIAL_RCV_BUFSZ25, rcv_buffer25,
	  SERIAL_SND_BUFSZ25, snd_buffer25 },
#endif
#if TNUM_PORT >= 26
	{ SERIAL_RCV_SEM26, SERIAL_SND_SEM26,
	  SERIAL_RCV_BUFSZ26, rcv_buffer26,
	  SERIAL_SND_BUFSZ26, snd_buffer26 },
#endif
#if TNUM_PORT >= 27
	{ SERIAL_RCV_SEM27, SERIAL_SND_SEM27,
	  SERIAL_RCV_BUFSZ27, rcv_buffer27,
	  SERIAL_SND_BUFSZ27, snd_buffer27 },
#endif
#if TNUM_PORT >= 28
	{ SERIAL_RCV_SEM28, SERIAL_SND_SEM28,
	  SERIAL_RCV_BUFSZ28, rcv_buffer28,
	  SERIAL_SND_BUFSZ28, snd_buffer28 },
#endif
#if TNUM_PORT >= 29
	{ SERIAL_RCV_SEM29, SERIAL_SND_SEM29,
	  SERIAL_RCV_BUFSZ29, rcv_buffer29,
	  SERIAL_SND_BUFSZ29, snd_buffer29 },
#endif
#if TNUM_PORT >= 30
	{ SERIAL_RCV_SEM30, SERIAL_SND_SEM30,
	  SERIAL_RCV_BUFSZ30, rcv_buffer30,
	  SERIAL_SND_BUFSZ30, snd_buffer30 },
#endif
#if TNUM_PORT >= 31
	{ SERIAL_RCV_SEM31, SERIAL_SND_SEM31,
	  SERIAL_RCV_BUFSZ31, rcv_buffer31,
	  SERIAL_SND_BUFSZ31, snd_buffer31 },
#endif
#if TNUM_PORT >= 32
	{ SERIAL_RCV_SEM32, SERIAL_SND_SEM32,
	  SERIAL_RCV_BUFSZ32, rcv_buffer32,
	  SERIAL_SND_BUFSZ32, snd_buffer32 },
#endif
#if TNUM_PORT >= 33
	{ SERIAL_RCV_SEM33, SERIAL_SND_SEM33,
	  SERIAL_RCV_BUFSZ33, rcv_buffer33,
	  SERIAL_SND_BUFSZ33, snd_buffer33 },
#endif
#if TNUM_PORT >= 34
	{ SERIAL_RCV_SEM34, SERIAL_SND_SEM34,
	  SERIAL_RCV_BUFSZ34, rcv_buffer34,
	  SERIAL_SND_BUFSZ34, snd_buffer34 },
#endif
#if TNUM_PORT >= 35
	{ SERIAL_RCV_SEM35, SERIAL_SND_SEM35,
	  SERIAL_RCV_BUFSZ35, rcv_buffer35,
	  SERIAL_SND_BUFSZ35, snd_buffer35 },
#endif
#if TNUM_PORT >= 36
	{ SERIAL_RCV_SEM36, SERIAL_SND_SEM36,
	  SERIAL_RCV_BUFSZ36, rcv_buffer36,
	  SERIAL_SND_BUFSZ36, snd_buffer36 },
#endif
#endif
};

/*
 *  シリアルポート管理ブロック
 */
typedef struct serial_port_control_block {
	const SPINIB *p_spinib;		/* シリアルポート初期化ブロック */
	SIOPCB	*p_siopcb;			/* シリアルI/Oポート管理ブロック */
	bool_t	openflag;			/* オープン済みフラグ */
	bool_t	errorflag;			/* エラーフラグ */
	uint_t	ioctl;				/* 動作制御の設定値 */

	uint_t	rcv_read_ptr;		/* 受信バッファ読出しポインタ */
	uint_t	rcv_write_ptr;		/* 受信バッファ書込みポインタ */
	uint_t	rcv_count;			/* 受信バッファ中の文字数 */
	char_t	rcv_fc_chr;			/* 送るべきSTART/STOP */
	bool_t	rcv_stopped;		/* STOPを送った状態か？ */

	uint_t	snd_read_ptr;		/* 送信バッファ読出しポインタ */
	uint_t	snd_write_ptr;		/* 送信バッファ書込みポインタ */
	uint_t	snd_count;			/* 送信バッファ中の文字数 */
	bool_t	snd_stopped;		/* STOPを受け取った状態か？ */
} SPCB;

SEC_SERIAL1_BEGIN
SEC_SERIAL1(static SPCB, spcb1);
SEC_SERIAL1_END

#if TNUM_PORT >= 2
SEC_SERIAL2_BEGIN
SEC_SERIAL2(static SPCB, spcb2);
SEC_SERIAL2_END
#endif /* TNUM_PORT >= 2 */

#if TNUM_PORT >= 3
SEC_SERIAL3_BEGIN
SEC_SERIAL3(static SPCB, spcb3);
SEC_SERIAL3_END
#endif /* TNUM_PORT >= 3 */

#if TNUM_PORT >= 4
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb4);
SEC_SERIAL4_END
#endif /* TNUM_PORT >= 4 */

#if 1 // Support up to 36 cores. -- ertl-liyixiao
/* TODO: Generated from following Python script.
for i in range(1, 37):
	print("""#if TNUM_PORT >= %(prc)s
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb%(prc)s);
SEC_SERIAL4_END
#endif""" % {'prc':i})
*/
#if TNUM_PORT >= 5
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb5);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 6
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb6);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 7
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb7);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 8
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb8);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 9
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb9);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 10
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb10);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 11
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb11);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 12
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb12);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 13
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb13);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 14
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb14);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 15
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb15);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 16
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb16);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 17
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb17);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 18
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb18);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 19
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb19);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 20
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb20);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 21
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb21);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 22
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb22);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 23
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb23);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 24
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb24);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 25
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb25);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 26
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb26);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 27
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb27);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 28
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb28);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 29
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb29);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 30
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb30);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 31
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb31);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 32
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb32);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 33
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb33);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 34
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb34);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 35
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb35);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 36
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb36);
SEC_SERIAL4_END
#endif
#endif

static SPCB* const	p_spcb_table[TNUM_PORT] = {
	&spcb1
#if TNUM_PORT >= 2
	,&spcb2
#endif /* TNUM_PORT >= 2 */
#if TNUM_PORT >= 3
	,&spcb3
#endif /* TNUM_PORT >= 3 */
#if TNUM_PORT >= 4
	,&spcb4
#endif /* TNUM_PORT >= 4 */
#if 1 // Support up to 36 cores. -- ertl-liyixiao
/* TODO: Generated from following Python script.
for i in range(1, 37):
	print("""#if TNUM_PORT >= %(prc)s
	,&spcb%(prc)s
#endif""" % {'prc':i})
*/
#if TNUM_PORT >= 5
	,&spcb5
#endif
#if TNUM_PORT >= 6
	,&spcb6
#endif
#if TNUM_PORT >= 7
	,&spcb7
#endif
#if TNUM_PORT >= 8
	,&spcb8
#endif
#if TNUM_PORT >= 9
	,&spcb9
#endif
#if TNUM_PORT >= 10
	,&spcb10
#endif
#if TNUM_PORT >= 11
	,&spcb11
#endif
#if TNUM_PORT >= 12
	,&spcb12
#endif
#if TNUM_PORT >= 13
	,&spcb13
#endif
#if TNUM_PORT >= 14
	,&spcb14
#endif
#if TNUM_PORT >= 15
	,&spcb15
#endif
#if TNUM_PORT >= 16
	,&spcb16
#endif
#if TNUM_PORT >= 17
	,&spcb17
#endif
#if TNUM_PORT >= 18
	,&spcb18
#endif
#if TNUM_PORT >= 19
	,&spcb19
#endif
#if TNUM_PORT >= 20
	,&spcb20
#endif
#if TNUM_PORT >= 21
	,&spcb21
#endif
#if TNUM_PORT >= 22
	,&spcb22
#endif
#if TNUM_PORT >= 23
	,&spcb23
#endif
#if TNUM_PORT >= 24
	,&spcb24
#endif
#if TNUM_PORT >= 25
	,&spcb25
#endif
#if TNUM_PORT >= 26
	,&spcb26
#endif
#if TNUM_PORT >= 27
	,&spcb27
#endif
#if TNUM_PORT >= 28
	,&spcb28
#endif
#if TNUM_PORT >= 29
	,&spcb29
#endif
#if TNUM_PORT >= 30
	,&spcb30
#endif
#if TNUM_PORT >= 31
	,&spcb31
#endif
#if TNUM_PORT >= 32
	,&spcb32
#endif
#if TNUM_PORT >= 33
	,&spcb33
#endif
#if TNUM_PORT >= 34
	,&spcb34
#endif
#if TNUM_PORT >= 35
	,&spcb35
#endif
#if TNUM_PORT >= 36
	,&spcb36
#endif
#endif
};

/*
 *  シリアルポートIDからシリアルポート管理ブロックを取り出すためのマクロ
 */
#define INDEX_PORT(portid)	((uint_t)((portid) - 1))
#define get_spcb(portid)	(p_spcb_table[INDEX_PORT(portid)])

/*
 *  ポインタのインクリメント
 */
#define INC_PTR(ptr, bufsz)		do {					\
	if (++(ptr) == (bufsz)) { (ptr) = 0; }				\
} while(false)

/*
 *  サービスコール呼出しマクロ
 *
 *  サービスコール呼出しを含む式expを評価し，返値がエラー（負の値）の場
 *  合には，ercにercd_expを評価した値を代入し，error_exitにgotoする．
 */
#define SVC(exp, ercd_exp) \
				{ if ((exp) < 0) { ercd = (ercd_exp); goto error_exit; }}

/*
 *  E_SYSエラーの生成
 */
static ER
gen_ercd_sys(SPCB *p_spcb)
{
	p_spcb->errorflag = true;
	return(E_SYS);
}

/*
 *  待ちに入るサービスコールからのエラーの変換
 */
static ER
gen_ercd_wait(ER rercd, SPCB *p_spcb)
{
	switch (MERCD(rercd)) {
	case E_RLWAI:
	case E_DLT:
		return(rercd);
	default:
		p_spcb->errorflag = true;
		return(E_SYS);
	}
}

/*
 *  シリアルインタフェースドライバの初期化ルーチン
 */
void
serial_initialize(intptr_t exinf)
{
	uint_t	i = (uint_t)exinf;

	(p_spcb_table[i])->p_spinib = &(spinib_table[i]);
	(p_spcb_table[i])->openflag = false;
}

/*
 *  シリアルポートのオープン（サービスコール）
 */
ER
serial_opn_por(ID portid)
{
	SPCB	*p_spcb;
	ER		ercd;

	if (sns_dpn()) {				/* コンテキストのチェック */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* ポート番号のチェック */
	}
	p_spcb = get_spcb(portid);

	SVC(dis_dsp(), gen_ercd_sys(p_spcb));
	if (p_spcb->openflag) {			/* オープン済みかのチェック */
		ercd = E_OBJ;
	}
	else {
		/*
		 *  変数の初期化
		 */
		p_spcb->ioctl = (IOCTL_ECHO | IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV);

		p_spcb->rcv_read_ptr = p_spcb->rcv_write_ptr = 0U;
		p_spcb->rcv_count = 0U;
		p_spcb->rcv_fc_chr = '\0';
		p_spcb->rcv_stopped = false;

		p_spcb->snd_read_ptr = p_spcb->snd_write_ptr = 0U;
		p_spcb->snd_count = 0U;
		p_spcb->snd_stopped = false;

		/*
		 *  これ以降，割込みを禁止する．
		 */
		if (loc_cpu() < 0) {
			ercd = E_SYS;
			goto error_exit_enadsp;
		}

		/*
		 *  ハードウェア依存のオープン処理
		 */
		p_spcb->p_siopcb = sio_opn_por(portid, (intptr_t) p_spcb);

		/*
		 *  受信通知コールバックを許可する．
		 */
		sio_ena_cbr(p_spcb->p_siopcb, SIO_RDY_RCV);
		p_spcb->openflag = true;
		p_spcb->errorflag = false;

		if (unl_cpu() < 0) {
			p_spcb->errorflag = true;
			ercd = E_SYS;
			goto error_exit_enadsp;
		}
		ercd = E_OK;
	}

  error_exit_enadsp:
	SVC(ena_dsp(), gen_ercd_sys(p_spcb));

  error_exit:
	return(ercd);
}

/*
 *  シリアルポートのクローズ（サービスコール）
 */
ER
serial_cls_por(ID portid)
{
	SPCB	*p_spcb;
	ER		ercd;
	bool_t	eflag = false;

	if (sns_dpn()) {				/* コンテキストのチェック */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* ポート番号のチェック */
	}
	p_spcb = get_spcb(portid);

	SVC(dis_dsp(), gen_ercd_sys(p_spcb));
	if (!(p_spcb->openflag)) {		/* オープン済みかのチェック */
		ercd = E_OBJ;
	}
	else {
		/*
		 *  ハードウェア依存のクローズ処理
		 */
		if (loc_cpu() < 0) {
			eflag = true;
		}
		sio_cls_por(p_spcb->p_siopcb);
		p_spcb->openflag = false;
		if (unl_cpu() < 0) {
			eflag = true;
		}

		/*
		 *  セマフォの初期化
		 */
		if (ini_sem(p_spcb->p_spinib->snd_semid) < 0) {
			eflag = true;
		}
		if (ini_sem(p_spcb->p_spinib->rcv_semid) < 0) {
			eflag = true;
		}

		/*
		 *  エラーコードの設定
		 */
		if (eflag) {
			ercd = gen_ercd_sys(p_spcb);
		}
		else {
			ercd = E_OK;
		}
	}
	SVC(ena_dsp(), gen_ercd_sys(p_spcb));

  error_exit:
	return(ercd);
}

/*
 *  シリアルポートへの文字送信
 *
 *  p_spcbで指定されるシリアルI/Oポートに対して，文字cを送信する．文字
 *  を送信レジスタにいれた場合にはtrueを返す．そうでない場合には，送信
 *  レジスタが空いたことを通知するコールバック関数を許可し，falseを返す．
 *  この関数は，CPUロック状態で呼び出される．
 */
Inline bool_t
serial_snd_chr(SPCB *p_spcb, char_t c)
{
	if (sio_snd_chr(p_spcb->p_siopcb, c)) {
		return(true);
	}
	else {
		sio_ena_cbr(p_spcb->p_siopcb, SIO_RDY_SND);
		return(false);
	}
}

/*
 *  シリアルポートへの1文字送信
 */
static ER_BOOL
serial_wri_chr(SPCB *p_spcb, char_t c)
{
	bool_t	buffer_full;
	ER		ercd, rercd;

	/*
	 *  LFの前にCRを送信する．
	 */
	if (c == '\n' && (p_spcb->ioctl & IOCTL_CRLF) != 0U) {
		SVC(rercd = serial_wri_chr(p_spcb, '\r'), rercd);
		if ((bool_t) rercd) {
			SVC(rercd = wai_sem(p_spcb->p_spinib->snd_semid),
										gen_ercd_wait(rercd, p_spcb));
		}
	}

	SVC(loc_cpu(), gen_ercd_sys(p_spcb));
	if (p_spcb->snd_count == 0U && !(p_spcb->snd_stopped)
								&& serial_snd_chr(p_spcb, c)) {
		/*
		 *  シリアルI/Oデバイスの送信レジスタに文字を入れることに成功し
		 *  た場合．
		 */
		buffer_full = false;
	}
	else {
		/*
		 *  送信バッファに文字を入れる．
		 */
		p_spcb->p_spinib->snd_buffer[p_spcb->snd_write_ptr] = c;
		INC_PTR(p_spcb->snd_write_ptr, p_spcb->p_spinib->snd_bufsz);
		p_spcb->snd_count++;
		buffer_full = (p_spcb->snd_count == p_spcb->p_spinib->snd_bufsz);
	}

	SVC(unl_cpu(), gen_ercd_sys(p_spcb));
	ercd = (ER_BOOL) buffer_full;

  error_exit:
	return(ercd);
}

/*
 *  シリアルポートへの文字列送信（サービスコール）
 */
ER_UINT
serial_wri_dat(ID portid, const char_t *buf, uint_t len)
{
	SPCB	*p_spcb;
	bool_t	buffer_full;
	uint_t	wricnt = 0U;
	ER		ercd, rercd;

	if (sns_dpn()) {				/* コンテキストのチェック */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* ポート番号のチェック */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* オープン済みかのチェック */
		return(E_OBJ);
	}
    if (p_spcb->errorflag) {		/* エラー状態かのチェック */
		return(E_SYS);
	}

	buffer_full = true;				/* ループの1回めはwai_semする */
	while (wricnt < len) {
		if (buffer_full) {
			SVC(rercd = wai_sem(p_spcb->p_spinib->snd_semid),
										gen_ercd_wait(rercd, p_spcb));
		}
		SVC(rercd = serial_wri_chr(p_spcb, *buf++), rercd);
		wricnt++;
		buffer_full = (bool_t) rercd;
	}
	if (!buffer_full) {
		SVC(sig_sem(p_spcb->p_spinib->snd_semid), gen_ercd_sys(p_spcb));
	}
	ercd = E_OK;

  error_exit:
	return(wricnt > 0U ? (ER_UINT) wricnt : ercd);
}

/*
 *  シリアルポートからの1文字受信
 */
static bool_t
serial_rea_chr(SPCB *p_spcb, char_t *p_c)
{
	bool_t	buffer_empty;
	ER		ercd;

	SVC(loc_cpu(), gen_ercd_sys(p_spcb));

	/*
	 *  受信バッファから文字を取り出す．
	 */
	*p_c = p_spcb->p_spinib->rcv_buffer[p_spcb->rcv_read_ptr];
	INC_PTR(p_spcb->rcv_read_ptr, p_spcb->p_spinib->rcv_bufsz);
	p_spcb->rcv_count--;
	buffer_empty = (p_spcb->rcv_count == 0U);

	/*
	 *  STARTを送信する．
	 */
	if (p_spcb->rcv_stopped && p_spcb->rcv_count
								<= BUFCNT_START(p_spcb->p_spinib->rcv_bufsz)) {
		if (!serial_snd_chr(p_spcb, FC_START)) {
			p_spcb->rcv_fc_chr = FC_START;
		}
		p_spcb->rcv_stopped = false;
	}

	SVC(unl_cpu(), gen_ercd_sys(p_spcb));
	ercd = (ER_BOOL) buffer_empty;

  error_exit:
	return(ercd);
}

/*
 *  シリアルポートからの文字列受信（サービスコール）
 */
ER_UINT
serial_rea_dat(ID portid, char_t *buf, uint_t len)
{
	SPCB	*p_spcb;
	bool_t	buffer_empty;
	uint_t	reacnt = 0U;
	char_t	c = '\0';		/* コンパイラの警告を抑止するために初期化する */
	ER		ercd, rercd;

	if (sns_dpn()) {				/* コンテキストのチェック */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* ポート番号のチェック */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* オープン済みかのチェック */
		return(E_OBJ);
	}
	if (p_spcb->errorflag) {		/* エラー状態かのチェック */
		return(E_SYS);
	}

	buffer_empty = true;			/* ループの1回めはwai_semする */
	while (reacnt < len) {
		if (buffer_empty) {
			SVC(rercd = wai_sem(p_spcb->p_spinib->rcv_semid),
										gen_ercd_wait(rercd, p_spcb));
		}
		SVC(rercd = serial_rea_chr(p_spcb, &c), rercd);
		*buf++ = c;
		reacnt++;
		buffer_empty = (bool_t) rercd;

		/*
		 *  エコーバック処理．
		 */
		if ((p_spcb->ioctl & IOCTL_ECHO) != 0U) {
			SVC(rercd = wai_sem(p_spcb->p_spinib->snd_semid),
										gen_ercd_wait(rercd, p_spcb));
			SVC(rercd = serial_wri_chr(p_spcb, c), rercd);
			if (!((bool_t) rercd)) {
				SVC(sig_sem(p_spcb->p_spinib->snd_semid),
										gen_ercd_sys(p_spcb));
			}
		}
	}
	if (!buffer_empty) {
		SVC(sig_sem(p_spcb->p_spinib->rcv_semid), gen_ercd_sys(p_spcb));
	}
	ercd = E_OK;

  error_exit:
	return(reacnt > 0U ? (ER_UINT) reacnt : ercd);
}

/*
 *  シリアルポートの制御（サービスコール）
 */
ER
serial_ctl_por(ID portid, uint_t ioctl)
{
	SPCB	*p_spcb;

	if (sns_dpn()) {				/* コンテキストのチェック */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* ポート番号のチェック */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* オープン済みかのチェック */
		return(E_OBJ);
	}
	if (p_spcb->errorflag) {		/* エラー状態かのチェック */
		return(E_SYS);
	}

	p_spcb->ioctl = ioctl;
	return(E_OK);
}

/*
 *  シリアルポート状態の参照（サービスコール）
 */
ER
serial_ref_por(ID portid, T_SERIAL_RPOR *pk_rpor)
{
	SPCB	*p_spcb;

	if (sns_dpn()) {				/* コンテキストのチェック */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* ポート番号のチェック */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* オープン済みかのチェック */
		return(E_OBJ);
	}
	if (p_spcb->errorflag) {		/* エラー状態かのチェック */
		return(E_SYS);
	}

	pk_rpor->reacnt = p_spcb->rcv_count;
	pk_rpor->wricnt = p_spcb->snd_count;
	return(E_OK);
}

/*
 *  シリアルポートからの送信可能コールバック
 */
void
sio_irdy_snd(intptr_t exinf)
{
	SPCB	*p_spcb;

	p_spcb = (SPCB *) exinf;
	if (p_spcb->rcv_fc_chr != '\0') {
		/*
		 *  START/STOP を送信する．
		 */
		(void) sio_snd_chr(p_spcb->p_siopcb, p_spcb->rcv_fc_chr);
		p_spcb->rcv_fc_chr = '\0';
	}
	else if (!(p_spcb->snd_stopped) && p_spcb->snd_count > 0U) {
		/*
		 *  送信バッファ中から文字を取り出して送信する．
		 */
		(void) sio_snd_chr(p_spcb->p_siopcb,
					p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr]);
		INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
		if (p_spcb->snd_count == p_spcb->p_spinib->snd_bufsz) {
			if (isig_sem(p_spcb->p_spinib->snd_semid) < 0) {
				p_spcb->errorflag = true;
			}
		}
		p_spcb->snd_count--;
	}
	else {
		/*
		 *  送信すべき文字がない場合は，送信可能コールバックを
		 *  禁止する．
		 */
		sio_dis_cbr(p_spcb->p_siopcb, SIO_RDY_SND);
	}
}

/*
 *  シリアルポートからの受信通知コールバック
 */
void
sio_irdy_rcv(intptr_t exinf)
{
	SPCB	*p_spcb;
	char_t	c;

	p_spcb = (SPCB *) exinf;
	c = (char_t) sio_rcv_chr(p_spcb->p_siopcb);
	if ((p_spcb->ioctl & IOCTL_FCSND) != 0U && c == FC_STOP) {
		/*
		 *  送信を一時停止する．送信中の文字はそのまま送信する．
		 */
		p_spcb->snd_stopped = true;
	}
	else if (p_spcb->snd_stopped && (c == FC_START
				|| (p_spcb->ioctl & IOCTL_FCANY) != 0U)) {
		/*
		 *  送信を再開する．
		 */
		p_spcb->snd_stopped = false;
		if (p_spcb->snd_count > 0U) {
			c = p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr];
			if (serial_snd_chr(p_spcb, c)) {
				INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
				if (p_spcb->snd_count == p_spcb->p_spinib->snd_bufsz) {
					if (isig_sem(p_spcb->p_spinib->snd_semid) < 0) {
						p_spcb->errorflag = true;
					}
				}
				p_spcb->snd_count--;
			}
		}
	}
	else if ((p_spcb->ioctl & IOCTL_FCSND) != 0U && c == FC_START) {
		/*
		 *  送信に対してフロー制御している場合，START は捨てる．
		 */
	}
	else if (p_spcb->rcv_count == p_spcb->p_spinib->rcv_bufsz) {
		/*
		 *  バッファフルの場合，受信した文字を捨てる．
		 */
	}
	else {
		/*
		 *  受信した文字を受信バッファに入れる．
		 */
		p_spcb->p_spinib->rcv_buffer[p_spcb->rcv_write_ptr] = c;
		INC_PTR(p_spcb->rcv_write_ptr, p_spcb->p_spinib->rcv_bufsz);
		if (p_spcb->rcv_count == 0U) {
			if (isig_sem(p_spcb->p_spinib->rcv_semid) < 0) {
				p_spcb->errorflag = true;
			}
		}
		p_spcb->rcv_count++;

		/*
		 *  STOPを送信する．
		 */
		if ((p_spcb->ioctl & IOCTL_FCRCV) != 0U && !(p_spcb->rcv_stopped)
						&& p_spcb->rcv_count
							>= BUFCNT_STOP(p_spcb->p_spinib->rcv_bufsz)) {
			if (!serial_snd_chr(p_spcb, FC_STOP)) {
				p_spcb->rcv_fc_chr = FC_STOP;
			}
			p_spcb->rcv_stopped = true;
		}
	}
}

/*
 *  シリアルインタフェースドライバからの未送信文字の取出し
 */
bool_t
serial_get_chr(ID portid, char_t *p_c)
{
	SPCB	*p_spcb;

	if (1 <= portid && portid <= TNUM_PORT) {	/* ポート番号のチェック */
		p_spcb = get_spcb(portid);
		if (p_spcb->openflag) {					/* オープン済みかのチェック */
			if (p_spcb->snd_count > 0U) {
				*p_c = p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr];
				INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
				p_spcb->snd_count--;
				return(true);
			}
		}
	}
	return(false);
}
