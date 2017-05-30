/*
 * sig_and_wai_sem.c
 *
 *  Created on: Nov 27, 2015
 *      Author: liyixiao
 */

#include "kernel/kernel_impl.h"
#include "kernel/check.h"
#include "kernel/task.h"
#include "kernel/semaphore.h"
#include "kernel/mp.h"
#include "kernel/wait.h"

// From 'kernel/semaphore.c'
#define INDEX_SEM(semid)	((uint_t)((semid) - TMIN_SEMID))
#define get_semcb(semid)	(p_semcb_table[INDEX_SEM(semid)])

//#define DEBUG_SIG_AND_WAI_SEM

#if 1

#if TTYPE_KLOCK != G_KLOCK && TTYPE_KLOCK != F_KLOCK
#error "TODO: TTYPE_KLOCK is not supported!"
#endif

ER sig_and_wai_sem_by_cb(SEMCB *p_sig_semcb, SEMCB *p_wai_semcb) {
	ER		ercd;
	bool_t	dspreq = false;
	bool_t  waireq = false;
#if TTYPE_KLOCK != G_KLOCK // Do this for G_KLOCK will cause dead lock
	bool_t  unlock_sig_pcb = false;
#endif
//	SEMCB	*p_sig_semcb;
//	SEMCB	*p_wai_semcb;

//	LOG_SIG_SEM_ENTER(semid); // TODO: log is omitted currently
//	LOG_WAI_SEM_ENTER(semid);
	CHECK_TSKCTX_UNL();
//	CHECK_SEMID(sig_semid);
//	CHECK_SEMID(wai_semid);
//	p_sig_semcb = get_semcb(sig_semid);
//	p_wai_semcb = get_semcb(wai_semid);

	t_lock_cpu();

	// Signal phase
	TCB		*p_sig_tcb;
	PCB		*p_sig_pcb = get_my_p_pcb(); // TODO: get_my_p_pcb is for debug
  sig_retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_sig_semcb));
	if (!queue_empty(&(p_sig_semcb->wait_queue))) {
 		p_sig_tcb = (TCB *) (p_sig_semcb->wait_queue.p_next);
#if defined(DEBUG_SIG_AND_WAI_SEM)
		syslog(LOG_NOTICE, "tid %d call %s(semid=%d) unlock %d", TSKID(get_my_p_pcb()->p_runtsk), __FUNCTION__, sig_semid, TSKID(p_sig_tcb));
#endif
		/* この間は繰り返し実行されるため，非破壊コードでなければならない．*/
		if ((p_sig_pcb = t_acquire_nested_tsk_lock(p_sig_tcb, &GET_OBJLOCK(p_sig_semcb))) == NULL){
			goto sig_retry;
		}
		queue_delete((QUEUE *) p_sig_tcb);
		if (wait_complete(p_sig_tcb)) {
			dspreq = dispatch_request(p_sig_pcb);
		}
#if TTYPE_KLOCK != G_KLOCK // Do this for G_KLOCK will cause dead lock
		unlock_sig_pcb = true; // release_nested_tsk_lock(p_sig_pcb);
#endif
		ercd = E_OK;
	}
	else if (p_sig_semcb->semcnt < p_sig_semcb->p_seminib->maxsem) {
#if defined(DEBUG_SIG_AND_WAI_SEM)
		syslog(LOG_NOTICE, "tid %d call %s(semid=%d) cnt++", TSKID(get_my_p_pcb()->p_runtsk), __FUNCTION__, sig_semid);
#endif
		p_sig_semcb->semcnt += 1;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
		syslog(LOG_EMERG, "!!!!!!!!!!!!!!!!!!!!!!!tid %d %s(): signal phase queue overflow!!!!!!!!!!!!!!!!!!!!!!!!!!!", TSKID(get_my_p_pcb()->p_runtsk), __FUNCTION__);
		//extern void debug_loop();debug_loop(); // This should not happen
		release_obj_lock(&GET_OBJLOCK(p_sig_semcb));
		t_unlock_cpu();
		while (1) tslp_tsk(1000); // loop to dump messages
		goto error_exit;
	}
	// release_obj_lock(&GET_OBJLOCK(p_sig_semcb));

	// Wait phase
	PCB		*my_p_pcb;
	TCB		*p_runtsk;
	assert(ercd == E_OK); // Precondition
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);
  wai_retry:
#if TTYPE_KLOCK != G_KLOCK // Do this for G_KLOCK will cause dead lock
    t_acquire_obj_lock(&GET_OBJLOCK(p_wai_semcb));
#endif
	if (p_wai_semcb->semcnt >= 1) {
		p_wai_semcb->semcnt -= 1;
		// release_obj_lock(&GET_OBJLOCK(p_wai_semcb));
		ercd = E_OK;
	}
	else {
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_wai_semcb))) == NULL){
			goto wai_retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
//		if (dspreq) make_non_wait(p_runtsk); TODO: check this
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SEM);
		wobj_make_wait((WOBJCB *) p_wai_semcb, p_runtsk);
#if TTYPE_KLOCK != G_KLOCK // Do this for G_KLOCK will cause dead lock
		release_nested_tsk_lock(my_p_pcb);                  // ==> Unlock phase start here
#endif
		// release_obj_lock(&GET_OBJLOCK(p_wai_semcb));
		waireq = true;
	}
#if TTYPE_KLOCK != G_KLOCK // Do this for G_KLOCK will cause dead lock
															// ==> Unlock phase continue  TODO: check can we unlock some lock(s) earlier
	if (unlock_sig_pcb) release_nested_tsk_lock(p_sig_pcb);
	release_obj_lock(&GET_OBJLOCK(p_wai_semcb));
#endif
	release_obj_lock(&GET_OBJLOCK(p_sig_semcb));

	// Dispatch phase
	if (dspreq || waireq) {
		dispatch();
		if (waireq)
			ercd = p_runtsk->wercd;
	}

	t_unlock_cpu();

	return(ercd);

  error_exit:
  assert(false);
  // FIXME: should unlock here, but we assume this never happen
//	LOG_SIG_SEM_LEAVE(ercd);  // TODO: log is omitted currently
//	LOG_WAI_SEM_LEAVE(ercd);
	return(ercd);
}

#else // This version works but only for G_KLOCK
#if TTYPE_KLOCK != G_KLOCK
#error "TODO: only giant lock is supported!"
#endif

ER sig_and_wai_sem_by_cb(SEMCB *p_sig_semcb, SEMCB *p_wai_semcb) {
	ER		ercd;
	bool_t	dspreq = false;
	bool_t  waireq = false;
//	SEMCB	*p_sig_semcb;
//	SEMCB	*p_wai_semcb;

//	LOG_SIG_SEM_ENTER(semid); // TODO: log is omitted currently
//	LOG_WAI_SEM_ENTER(semid);
	CHECK_TSKCTX_UNL();
//	CHECK_SEMID(sig_semid);
//	CHECK_SEMID(wai_semid);
//	p_sig_semcb = get_semcb(sig_semid);
//	p_wai_semcb = get_semcb(wai_semid);

	t_lock_cpu();

	// Signal phase
	TCB		*p_sig_tcb;
	PCB		*p_sig_pcb = get_my_p_pcb(); // TODO: get_my_p_pcb is for debug
  sig_retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_sig_semcb));
	if (!queue_empty(&(p_sig_semcb->wait_queue))) {
 		p_sig_tcb = (TCB *) (p_sig_semcb->wait_queue.p_next);
#if defined(DEBUG_SIG_AND_WAI_SEM)
		syslog(LOG_NOTICE, "tid %d call %s(semid=%d) unlock %d", TSKID(get_my_p_pcb()->p_runtsk), __FUNCTION__, sig_semid, TSKID(p_sig_tcb));
#endif
		/* この間は繰り返し実行されるため，非破壊コードでなければならない．*/
		if ((p_sig_pcb = t_acquire_nested_tsk_lock(p_sig_tcb, &GET_OBJLOCK(p_sig_semcb))) == NULL){
			goto sig_retry;
		}
		queue_delete((QUEUE *) p_sig_tcb);
		if (wait_complete(p_sig_tcb)) {
			dspreq = dispatch_request(p_sig_pcb);
		}
		release_nested_tsk_lock(p_sig_pcb);
		ercd = E_OK;
	}
	else if (p_sig_semcb->semcnt < p_sig_semcb->p_seminib->maxsem) {
#if defined(DEBUG_SIG_AND_WAI_SEM)
		syslog(LOG_NOTICE, "tid %d call %s(semid=%d) cnt++", TSKID(get_my_p_pcb()->p_runtsk), __FUNCTION__, sig_semid);
#endif
		p_sig_semcb->semcnt += 1;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
		syslog(LOG_EMERG, "!!!!!!!!!!!!!!!!!!!!!!!tid %d %s(): signal phase queue overflow!!!!!!!!!!!!!!!!!!!!!!!!!!!", TSKID(get_my_p_pcb()->p_runtsk), __FUNCTION__);
		//extern void debug_loop();debug_loop(); // This should not happen
		release_obj_lock(&GET_OBJLOCK(p_wai_semcb));
		t_unlock_cpu();
		while (1) tslp_tsk(1000); // loop to dump messages
		goto error_exit;
	}
	// release_obj_lock(&GET_OBJLOCK(p_sig_semcb));

	// Wait phase
	PCB		*my_p_pcb;
	TCB		*p_runtsk;
	assert(ercd == E_OK); // Precondition
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);
  wai_retry:
	// t_acquire_obj_lock(&GET_OBJLOCK(p_wai_semcb));
	if (p_wai_semcb->semcnt >= 1) {
		p_wai_semcb->semcnt -= 1;
		// release_obj_lock(&GET_OBJLOCK(p_wai_semcb));
		ercd = E_OK;
	}
	else {
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_wai_semcb))) == NULL){
			goto wai_retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
//		if (dspreq) make_non_wait(p_runtsk); TODO: check this
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SEM);
		wobj_make_wait((WOBJCB *) p_wai_semcb, p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		// release_obj_lock(&GET_OBJLOCK(p_wai_semcb));
		waireq = true;
	}

	release_obj_lock(&GET_OBJLOCK(p_wai_semcb));

	// Dispatch phase
	if (dspreq || waireq) {
		dispatch();
		if (waireq)
			ercd = p_runtsk->wercd;
	}

	t_unlock_cpu();

	return(ercd);

  error_exit:
  assert(false);
//	LOG_SIG_SEM_LEAVE(ercd);  // TODO: log is omitted currently
//	LOG_WAI_SEM_LEAVE(ercd);
	return(ercd);
}
#endif

#if 0 // Legacy code
ER sig_and_wai_sem(ID sig_semid, ID wai_semid) {
	ER		ercd;
	bool_t	dspreq = false;
	bool_t  waireq = false;
	SEMCB	*p_sig_semcb;
	SEMCB	*p_wai_semcb;

//	LOG_SIG_SEM_ENTER(semid); // TODO: log is omitted currently
//	LOG_WAI_SEM_ENTER(semid);
	CHECK_TSKCTX_UNL();
	CHECK_SEMID(sig_semid);
	CHECK_SEMID(wai_semid);
	p_sig_semcb = get_semcb(sig_semid);
	p_wai_semcb = get_semcb(wai_semid);

	t_lock_cpu();

	// Signal phase
	TCB		*p_sig_tcb;
	PCB		*p_sig_pcb;
  sig_retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_sig_semcb));
	if (!queue_empty(&(p_sig_semcb->wait_queue))) {
		p_sig_tcb = (TCB *) (p_sig_semcb->wait_queue.p_next);
		/* この間は繰り返し実行されるため，非破壊コードでなければならない．*/
		if ((p_sig_pcb = t_acquire_nested_tsk_lock(p_sig_tcb, &GET_OBJLOCK(p_sig_semcb))) == NULL){
			goto sig_retry;
		}
		queue_delete((QUEUE *) p_sig_tcb);
		if (wait_complete(p_sig_tcb)) {
			dspreq = dispatch_request(p_sig_pcb);
		}
		release_nested_tsk_lock(p_sig_pcb);
		ercd = E_OK;
	}
	else if (p_sig_semcb->semcnt < p_sig_semcb->p_seminib->maxsem) {
		p_sig_semcb->semcnt += 1;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
		extern void debug_loop();debug_loop(); // This should not happen
		t_unlock_cpu();
		goto error_exit;
	}
#if TTYPE_KLOCK != G_KLOCK
#error "Giant lock is required, can't be released!"
	release_obj_lock(&GET_OBJLOCK(p_sig_semcb));
#endif

	// Wait phase
	PCB		*my_p_pcb;
	TCB		*p_runtsk;
	assert(ercd == E_OK); // Precondition
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);
  wai_retry:
#if TTYPE_KLOCK != G_KLOCK
#error "Giant lock is required, don't acquire it again!"
	t_acquire_obj_lock(&GET_OBJLOCK(p_wai_semcb));
#endif
	if (p_wai_semcb->semcnt >= 1) {
		p_wai_semcb->semcnt -= 1;
#if TTYPE_KLOCK != G_KLOCK
#error "Giant lock is required"
		release_obj_lock(&GET_OBJLOCK(p_wai_semcb));
#endif
		ercd = E_OK;
	}
	else {
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_wai_semcb))) == NULL){
			goto wai_retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		if (dspreq) make_non_wait(p_runtsk);
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SEM);
		wobj_make_wait((WOBJCB *) p_wai_semcb, p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
#if TTYPE_KLOCK != G_KLOCK
#error "Giant lock is required"
		release_obj_lock(&GET_OBJLOCK(p_wai_semcb));
#endif
		waireq = true;
	}

	release_obj_lock(&GET_OBJLOCK(p_wai_semcb));

	// Dispatch phase
	if (dspreq || waireq) {
		dispatch();
		if (waireq)
			ercd = p_runtsk->wercd;
	}

	t_unlock_cpu();

  error_exit:
//	LOG_SIG_SEM_LEAVE(ercd);  // TODO: log is omitted currently
//	LOG_WAI_SEM_LEAVE(ercd);
	return(ercd);
}
#endif
