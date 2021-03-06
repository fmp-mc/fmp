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
 *  @(#) $Id: sh7786_dev.h 513 2010-02-01 05:42:13Z ertl-honda $
 */


/*
 *  ハードウェア資源の定義（SH7786_DEV用）
 */

#ifndef TOPPERS_SH7786_DEV_H
#define TOPPERS_SH7786_DEV_H

#include <sil.h>

/*
 *  プロセッサのハードウェア資源の定義のインクルード
 */
#include "sh4a_gcc/sh7786.h"

/*
 *  内蔵周辺クロック P = 600MHz
 */
#define PCLOCK   600000000 

/*
 *  Serial Port Control A Register
 */
#define SPCAR  UINT_C(0xA7FFF920)

#ifndef TOPPERS_MACRO_ONLY

/*
 *  開発環境依存の処理
 */
Inline void
sh7786_dev_exit(void)
{
	uint32_t sr = 0x10000000U;
    
	/*
	 * 強制的にリセットを発生させる
	 */

	/*
	 * BLビットを立てる
	 */
	Asm("ldc %0, sr" : : "r"(sr));
    
	/*
	 * 書込み例外
	 */
	*((volatile int *) 0xFFFFFEC1U) = 0U;
}

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_SH7786_DEV_H */
