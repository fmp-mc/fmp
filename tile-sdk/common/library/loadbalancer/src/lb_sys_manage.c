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
 *  @(#) $Id: sample1.c 374 2008-03-22 01:32:57Z honda $
 */

#include "kernel/kernel_impl.h"
#include "kernel/task.h"
#include "kernel/check.h"
#include "kernel/mp.h"

#include "loadbalancer.h"

/* マイグレーションカウント用 */
/* ロードバランスモジュール内でカウント */
uint16_t mig_count[TNUM_PRCID]={0,0,0,0};//mig_tsk発行回数

/*
 *  特定優先度のタスク数の参照
 */
ER
get_rtsk(ID prcid, PRI tskpri, uint_t *p_rtsk)
{
	PCB *mp_p_pcb;
	ER		ercd;
	uint_t	i;

	CHECK_TSKCTX_UNL();
	CHECK_TPRI(tskpri);

	t_lock_cpu();
	if (prcid == 0) {
		mp_p_pcb = get_my_p_pcb();
	} else {
		mp_p_pcb = get_mp_p_pcb(prcid);
	}

	if (tskpri == 0){
		*p_rtsk = 0;
		for (i = 0; i < TNUM_TPRI; i++) {
			*p_rtsk += mp_p_pcb->tsk_num[i];
		}
	}else{
		*p_rtsk = mp_p_pcb->tsk_num[tskpri - 1];
	}

	t_unlock_cpu();
    ercd =  E_OK;

  error_exit:
	return(ercd);
}

/*
 *  特定優先度のタスク数の参照
 */
ER
iget_rtsk(ID prcid, PRI tskpri, uint_t *p_rtsk)
{
	PCB *mp_p_pcb;
	ER		ercd;
	uint_t	i;

	CHECK_INTCTX_UNL();
	CHECK_TPRI(tskpri);

	i_lock_cpu();
	if (prcid == 0) {
		mp_p_pcb = get_my_p_pcb();
	} else {
		mp_p_pcb = get_mp_p_pcb(prcid);
    }

	if (tskpri == 0){
		*p_rtsk = 0;
		for (i = 0; i < TNUM_TPRI; i++) {
			*p_rtsk += mp_p_pcb->tsk_num[i];
		}
	}else{
		*p_rtsk = mp_p_pcb->tsk_num[tskpri - 1];
	}

	i_unlock_cpu();
	ercd =  E_OK;

  error_exit:
	return(ercd);
}
/*
 *  特定優先順位のタスクIDの参照
 */
ER
get_prd(PRI tskpri, uint_t prd, ID *p_tskid)
{
	TCB		*p_tcb;
	QUEUE	*p_queue;
	QUEUE	*p_entry;
	int_t	i;
	ER		ercd;
	PCB		*my_p_pcb;

	CHECK_TSKCTX_UNL();
	CHECK_TPRI(tskpri);

	t_lock_cpu();
	my_p_pcb = t_acquire_tsk_lock_self();
	p_queue = &((my_p_pcb->ready_queue)[tskpri - 1]);
	if (prd == TPRD_LOWEST) {
		/*
		 *  最低優先順位のタスクを指定
		 */
		p_tcb = (TCB *)(p_queue->p_prev);
	} else {
		/*
		 *  特定優先順位のタスクを指定
		 */
		p_entry = p_queue->p_next;
		for (i = 1; i < prd; i++) {
			p_entry = p_entry->p_next;
			if (p_entry == p_queue) {
				//ercd = TSK_NONE;
				ercd = E_NOEXS;
				release_tsk_lock(my_p_pcb);
				t_unlock_cpu();
				goto error_exit;
			}
		}
		p_tcb = (TCB *)(p_entry);
	}
	*p_tskid = TSKID(p_tcb);
	ercd =  E_OK;
	release_tsk_lock(my_p_pcb);
	t_unlock_cpu();

  error_exit:
	return(ercd);
}

/*
 *  特定優先順位のタスクIDの参照
 */
ER
iget_prd(PRI tskpri, uint_t prd, ID *p_tskid)
{
	TCB		*p_tcb;
	QUEUE	*p_queue;
	QUEUE	*p_entry;
	int_t	i;
	ER		ercd;
	PCB		*my_p_pcb;

	CHECK_INTCTX_UNL();
	CHECK_TPRI(tskpri);

	i_lock_cpu();
	my_p_pcb = i_acquire_tsk_lock_self();
	p_queue = &((my_p_pcb->ready_queue)[tskpri - 1]);
	if (prd == TPRD_LOWEST) {
		/*
		 *  最低優先順位のタスクを指定
		 */
		p_tcb = (TCB *)(p_queue->p_prev);
	} else {
		/*
		 *  特定優先順位のタスクを指定
		 */
		p_entry = p_queue->p_next;
		for (i = 1; i < prd; i++) {
			p_entry = p_entry->p_next;
			if (p_entry == p_queue) {
				ercd = TSK_NONE;
				release_tsk_lock(my_p_pcb);
				t_unlock_cpu();
				goto error_exit;
			}
		}
		p_tcb = (TCB *)(p_entry);
	}
	*p_tskid = TSKID(p_tcb);
	ercd =  E_OK;
	release_tsk_lock(my_p_pcb);
	i_unlock_cpu();

  error_exit:
	return(ercd);
}
