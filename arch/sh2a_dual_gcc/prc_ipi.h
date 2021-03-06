/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2009 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *	Copyright (C) 2010 by Industrial Technology Institute,
 *								Miyagi Prefectural Government, JAPAN
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
 *  $Id: prc_ipi.h 816 2011-06-30 02:46:57Z mit-kimai $
 */

/*
 *  プロセッサ間割込みドライバ（SH2A-DUAL用）
 */

#ifndef TOPPERS_PRC_IPI_H
#define TOPPERS_PRC_IPI_H

/*
 *  make depend時にcfg1_out.cでシンボルirc_reg_tblが
 *  見つけられなくなるため、追加
 *  （要検討：本来はいらないはず）
 */
#include "prc_rename.h"		/*  irc_reg_tblのリネーム  */
#include "prc_config.h"

/*
 *  割込み番号と割込みハンドラ番号
 */
#define INTNO_IPI_PRC1  (0x10000|IPI08_VECTOR)  /* 割込み番号 */
#define INHNO_IPI_PRC1  INTNO_IPI_PRC1  		/* 割込みハンドラ番号 */
#define INTPRI_IPI_PRC1 (-8)					/* 割込み優先度 */

#define INTNO_IPI_PRC2  (0x20000|IPI08_VECTOR)  /* 割込み番号 */
#define INHNO_IPI_PRC2  INTNO_IPI_PRC2  		/* 割込みハンドラ番号 */
#define INTPRI_IPI_PRC2 (-8)					/* 割込み優先度 */

/*
 *  プロセッサ間割込みの発行
 */
Inline void
target_ipi_raise(uint_t procid)
{
	uint16_t *p_ipcr8_h = irc_reg_tbl[procid - 1].ipcr8_h;
	
	sil_wrh_mem((uint16_t *)p_ipcr8_h, IPCR_CI);
}

/*
 *  プロセッサ間割込みのクリア
 */
Inline void
target_ipi_clear(void)
{

}

#endif /* TOPPERS_PRC_IPI_H */
