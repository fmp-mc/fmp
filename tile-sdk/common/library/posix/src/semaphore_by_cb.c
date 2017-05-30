/**
 * POSIX Library for TOPPERS/FMP Kernel
 *
 * Copyright (C) 2016 by Yixiao Li
 *
 *  The above copyright holders grant permission gratis to use,
 *  duplicate, modify, or redistribute (hereafter called use) this
 *  software (including the one made by modifying this software),
 *  provided that the following four conditions (1) through (4) are
 *  satisfied.
 *
 *  (1) When this software is used in the form of source code, the above
 *      copyright notice, this use conditions, and the disclaimer shown
 *      below must be retained in the source code without modification.
 *
 *  (2) When this software is redistributed in the forms usable for the
 *      development of other software, such as in library form, the above
 *      copyright notice, this use conditions, and the disclaimer shown
 *      below must be shown without modification in the document provided
 *      with the redistributed software, such as the user manual.
 *
 *  (3) When this software is redistributed in the forms unusable for the
 *      development of other software, such as the case when the software
 *      is embedded in a piece of equipment, either of the following two
 *      conditions must be satisfied:
 *
 *    (a) The above copyright notice, this use conditions, and the
 *        disclaimer shown below must be shown without modification in
 *        the document provided with the redistributed software, such as
 *        the user manual.
 *
 *    (b) How the software is to be redistributed must be reported to the
 *        TOPPERS Project according to the procedure described
 *        separately.
 *
 *  (4) The above copyright holders and the TOPPERS Project are exempt
 *      from responsibility for any type of damage directly or indirectly
 *      caused from the use of this software and are indemnified by any
 *      users or end users of this software from any and all causes of
 *      action whatsoever.
 *
 *  THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
 *  THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
 *  PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
 *  TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
 *  INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
 */

#include "kernel/kernel_impl.h"
#include "kernel/check.h"
#include "kernel/task.h"
#include "kernel/wait.h"
#include "kernel/semaphore.h"
#include "kernel/mp.h"

#include "kernel_cfg.h"
#include "posix_cfg.h"
#include "semaphore_by_cb.h"

ER
sig_sem_by_cb(SEMCB *p_semcb)
{
	TCB		*p_tcb;
	ER		ercd;
	bool_t	dspreq = false;
	PCB		*p_pcb;

//	LOG_SIG_SEM_ENTER(semid);
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_semcb));
	if (!queue_empty(&(p_semcb->wait_queue))) {
		p_tcb = (TCB *) (p_semcb->wait_queue.p_next);
		/* この間は繰り返し実行されるため，非破壊コードでなければならない．*/
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_semcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		ercd = E_OK;
	}
	else if (p_semcb->semcnt < p_semcb->p_seminib->maxsem) {
		p_semcb->semcnt += 1;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	release_obj_lock(&GET_OBJLOCK(p_semcb));
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
//	LOG_SIG_SEM_LEAVE(ercd);
	return(ercd);
}

ER
wai_sem_by_cb(SEMCB *p_semcb)
{
	ER		ercd;
	PCB		*my_p_pcb;
	TCB		*p_runtsk;

//	LOG_WAI_SEM_ENTER(semid);
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_semcb));
	if (p_semcb->semcnt >= 1) {
		p_semcb->semcnt -= 1;
		release_obj_lock(&GET_OBJLOCK(p_semcb));
		ercd = E_OK;
	}
	else {
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_semcb))) == NULL){
			goto retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SEM);
		wobj_make_wait((WOBJCB *) p_semcb, p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_semcb));
		dispatch();
		ercd = p_runtsk->wercd;
	}
	t_unlock_cpu();

  error_exit:
//	LOG_WAI_SEM_LEAVE(ercd);
	return(ercd);
}

ER
pol_sem_by_cb(SEMCB *p_semcb)
{
	ER		ercd;

//	LOG_POL_SEM_ENTER(semid);
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	t_acquire_obj_lock(&GET_OBJLOCK(p_semcb));
	if (p_semcb->semcnt >= 1) {
		p_semcb->semcnt -= 1;
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	release_obj_lock(&GET_OBJLOCK(p_semcb));
	t_unlock_cpu();

  error_exit:
//	LOG_POL_SEM_LEAVE(ercd);
	return(ercd);
}

ER
twai_sem_by_cb(SEMCB *p_semcb, TMO tmout)
{
//	SEMCB	*p_semcb;
	ER		ercd;
	PCB		*my_p_pcb;
	TCB		*p_runtsk;

//	LOG_TWAI_SEM_ENTER(semid, tmout);
	CHECK_TSKCTX_UNL();
//	CHECK_SEMID(semid);
	CHECK_TMOUT(tmout);
//	p_semcb = get_semcb(semid);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_semcb));
	if (p_semcb->semcnt >= 1) {
		p_semcb->semcnt -= 1;
		release_obj_lock(&GET_OBJLOCK(p_semcb));
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		release_obj_lock(&GET_OBJLOCK(p_semcb));
		ercd = E_TMOUT;
	}
	else {
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_semcb))) == NULL){
			goto retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SEM);
		wobj_make_wait_tmout((WOBJCB *) p_semcb, tmout, p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_semcb));
		dispatch();
		ercd = p_runtsk->wercd;
	}
	t_unlock_cpu();

  error_exit:
//	LOG_TWAI_SEM_LEAVE(ercd);
	return(ercd);
}

ER
ini_sem_by_cb(SEMCB	*p_semcb)
{
	ER		ercd;
	bool_t	dspreq;

//	LOG_INI_SEM_ENTER(semid);
	CHECK_TSKCTX_UNL();
//	CHECK_SEMID(semid);
//	p_semcb = get_semcb(semid);

	t_lock_cpu();
	t_acquire_obj_lock(&GET_OBJLOCK(p_semcb));
	dspreq = init_wait_queue(&(p_semcb->wait_queue));
	p_semcb->semcnt = p_semcb->p_seminib->isemcnt;
	ercd = E_OK;
	release_obj_lock(&GET_OBJLOCK(p_semcb));
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
//	LOG_INI_SEM_LEAVE(ercd);
	return(ercd);
}

#if defined(DYNAMIC_SEMCB_ALLOCATION)

SEMCB *cre_sem_cb(ATR sematr, uint_t isemcnt, uint_t maxsem) {
	assert(sematr == TA_NULL);

	SEMCB   *p_semcb;
	SEMINIB *p_seminib;

	ER ercd = pget_mpf(SEMCB_MPF, &(p_semcb));
	assert(ercd == E_OK);
	ercd = pget_mpf(SEMINIB_MPF, &(p_seminib));
	assert(ercd == E_OK);

	p_seminib->isemcnt = isemcnt;
	p_seminib->maxsem = maxsem;
	p_seminib->sematr = sematr;
#if TTYPE_KLOCK == F_KLOCK
	x_initialize_obj_lock(&(p_semcb->obj_lock));
#endif /* TTYPE_KLOCK == F_KLOCK */

	// Ref: initialize_semaphore()
	queue_initialize(&(p_semcb->wait_queue));
	p_semcb->p_seminib = p_seminib;
	p_semcb->semcnt = p_semcb->p_seminib->isemcnt;

	return p_semcb;
}

#if 0 // Unused?
void del_sem_cb(SEMCB *p_semcb) {
	assert(queue_empty(&(p_semcb->wait_queue)));
	ER ercd = rel_mpf(SEMINIB_MPF, p_semcb->p_seminib);
	assert(ercd == E_OK);
	ercd = rel_mpf(SEMCB_MPF, p_semcb);
	assert(ercd == E_OK);
}
#endif

#endif

