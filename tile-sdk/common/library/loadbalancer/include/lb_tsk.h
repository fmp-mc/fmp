/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2009-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: logtask.h 4 2008-05-09 18:17:43Z ertl-honda $
 */

/*
 *		タスク数によるロードバランス
 */

#ifndef LOADBALANCE_TSK_H
#define LOADBALANCE_TSK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "target_syssvc.h"

/*
 *  システムログタスク関連の定数のデフォルト値の定義
 */ 
#ifndef LOADTASK_PRIORITY
#define LOADTASK_PRIORITY	3		/* 初期優先度 */
#endif /* LOADTASK_PRIORITY */

#ifndef LOADTASK_STACK_SIZE
#define LOADTASK_STACK_SIZE	1024	/* スタック領域のサイズ */
#endif /* LOADTASK_STACK_SIZE */

/*
 *  ロードバランス対象タスク優先度
 */
#ifndef LOAD_PRI
//#define LOAD_PRI 10
#include "posix_cfg.h" // for PTHREAD_TASK_PRIORITY
#define LOAD_PRI PTHREAD_TASK_PRIORITY
#endif /* LOAD_PRI */

/*
 *  ロードサーバータスクの本体
 */
extern void	loadserver_main(intptr_t exinf) throw();
extern void cyclic_loadserver(intptr_t exinf) throw();
extern void	cyclic_rr(intptr_t exinf) throw();
extern void cyclic_rebalance(intptr_t exinf) throw();

void load_balancer_initialize(intptr_t unused);

#ifdef __cplusplus
}
#endif

#endif /* LOADBALANCE_TSK_H */
