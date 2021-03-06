/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2006-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_kernel.h 942 2012-10-19 07:49:03Z ertl-honda $
 */

/*
 *  kernel.hのチップ依存部（KZM_CA9用）
 *
 *  このインクルードファイルは，kernel.hでインクルードされる．他のファ
 *  イルから直接インクルードすることはない．このファイルをインクルード
 *  する前に，t_stddef.hがインクルードされるので，それらに依存してもよ
 *  い．
 */

#ifndef TOPPERS_TARGET_KERNEL_H
#define TOPPERS_TARGET_KERNEL_H

#include "kzm_ca9.h"

/*
 *  プロセッサ間割込みとして用いる割込みのDICの番号
 */
#define DIC_IRQNO_IPI  DIC_IRQNO_IPI0

/*
 *  システム時刻の管理方式
 */
#define TOPPERS_SYSTIM_LOCAL			/* ローカルタイマ方式のシステム時刻 */
//#define TOPPERS_SYSTIM_GLOBAL			/* グローバルタイマ方式のシステム時刻 */

/*
 *  グローバルタイマ方式時のシステム時刻管理プロセッサ（ID）
 */
#define TOPPERS_SYSTIM_PRCID  1

/*
 *  マスタプロセッサ（ID）
 */
#define TOPPERS_MASTER_PRCID  1

/*
 * プロセッサ数
 */
#ifndef TNUM_PRCID
#define TNUM_PRCID  2
#endif /* TNUM_PRCID */

/*
 *  クラスのID定義
 */
#define TCL_1   1
#define TCL_2   2
#define TCL_3   3
#define TCL_4   4
#define TCL_1_ONLY   5
#define TCL_2_ONLY   6 
#define TCL_3_ONLY   7
#define TCL_4_ONLY   8
#define TCL_SYSTIM_PRC   9

/*
 *  チップ依存で共通な定義
 */
#include "arm_gcc/mpcore/chip_kernel.h"

#endif /* TOPPERS_TARGET_KERNEL_H */
