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
 *  ポインタのインクリメント
 */
#define INC_PTR(ptr, bufsz)		do {					\
	if (++(ptr) == (bufsz)) { (ptr) = 0; }				\
} while(false)

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

/*
 *  シリアルポートからの送信可能コールバック (Task context version)
 */
void
sio_rdy_snd(intptr_t exinf)
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
			if (sig_sem(p_spcb->p_spinib->snd_semid) < 0) {
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
