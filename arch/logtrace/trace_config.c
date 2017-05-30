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
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: trace_config.c 419 2009-10-04 15:02:07Z ertl-honda $
 */

/*
 *		�ȥ졼��������ǽ
 */

#include "kernel_impl.h"
#include "task.h"
#include "time_event.h"
#include "mp.h"
#include <sil.h>

/*
 *  �ȥ졼�������Хåե��Ȥ���˥����������뤿��Υݥ���
 */
TRACE	trace_buffer[TCNT_TRACE_BUFFER];	/* �ȥ졼�������Хåե� */
uint_t	trace_count;				/* �ȥ졼�������Хåե���Υ����ο� */
uint_t	trace_head;					/* ��Ƭ�Υȥ졼�������γ�Ǽ���� */
uint_t	trace_tail;					/* ���Υȥ졼�������γ�Ǽ���� */
MODE	trace_mode;					/* �ȥ졼���⡼�� */

/*
 *  �ȥ졼��������ǽ�ν����
 */
void
trace_initialize(intptr_t exinf)
{
	MODE	mode = ((MODE) exinf);

	trace_count = 0U;
	trace_head = trace_tail = 0U;
	trace_mode = mode;

	TRACE_HW_INIT();
}     

/*
 *  �ȥ졼�������γ���
 */
ER
trace_sta_log(MODE mode)
{
	if ((mode & TRACE_CLEAR) != 0U) {
		trace_count = 0U;
		trace_head = trace_tail = 0U;
	}
	trace_mode = mode;
	return(E_OK);
}     

/* 
 *  �ȥ졼�������ν����
 */
ER
trace_wri_log(TRACE *p_trace)
{
	SIL_PRE_LOC;

	if (trace_mode != TRACE_STOP) {
		SIL_LOC_SPN();

		/*
		 *  �ȥ졼�����������
		 *
		 *  LOG_WRI_LOG_ENTER����ƤФ줿����p_trace->logtim��񤭴�
		 *  ���Ƥ��ޤ��Τϵ���������������wri_log�����Ǿ�񤭤��뤿����
		 *  ��Ϥʤ���
		 */
		p_trace->logtim = TRACE_GET_TIM();

		/*
		 *  �ץ����å�ID������
		 */
		p_trace->prcid = ID_PRC(x_prc_index());

		/*
		 *  �ȥ졼���Хåե��˵�Ͽ
		 */
		trace_buffer[trace_tail] = *p_trace;
		trace_tail++;
		if (trace_tail >= TCNT_TRACE_BUFFER) {
			trace_tail = 0U;
		}
		if (trace_count < TCNT_TRACE_BUFFER) {
			trace_count++;
			if (trace_count >= TCNT_TRACE_BUFFER
						&& (trace_mode & TRACE_AUTOSTOP) != 0U) {
				trace_mode = TRACE_STOP;
			}
		}
		else {
			trace_head = trace_tail;
		}

		SIL_UNL_SPN();
	}
	return(E_OK);
}

/*
 *  �ȥ졼���������ɽФ�
 */
ER
trace_rea_log(TRACE *p_trace)
{
	ER_UINT	ercd;
	SIL_PRE_LOC;

	SIL_LOC_SPN();

	/*
	 *  �ȥ졼�������Хåե�����μ�Ф�
	 */
	if (trace_count > 0U) {
		*p_trace = trace_buffer[trace_head];
		trace_count--;
		trace_head++;
		if (trace_head >= TCNT_TRACE_BUFFER) {
			trace_head = 0U;
		}
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;
	}

	SIL_UNL_SPN();
	return(ercd);
}

ER
trace_rea_log_reverse(TRACE *p_trace)
{
	ER_UINT	ercd;
	SIL_PRE_LOC;

	SIL_LOC_SPN();

	/*
	 *  �ȥ졼�������Хåե�����μ�Ф�
	 */
	if (trace_count > 0U) {
		uint_t last = trace_head + trace_count - 1;
		if (last >= TCNT_TRACE_BUFFER) last -= TCNT_TRACE_BUFFER;
		*p_trace = trace_buffer[last];
		trace_count--;
#if 0
		trace_head++;
		if (trace_head >= TCNT_TRACE_BUFFER) {
			trace_head = 0U;
		}
#endif
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;
	}

	SIL_UNL_SPN();
	return(ercd);
}

/*
 *  �ȥ졼����������Ϥ��뤿��Υ饤�֥��ؿ�
 */

void
trace_write_0(uint_t type)
{
	TRACE	trace;

	trace.logtype = type;
	(void) trace_wri_log(&trace);
}

void
trace_write_1(uint_t type, intptr_t arg1)
{
	TRACE	trace;

	trace.logtype = type;
	trace.loginfo[0] = arg1;
	(void) trace_wri_log(&trace);
}

void
trace_write_2(uint_t type, intptr_t arg1, intptr_t arg2)
{
	TRACE	trace;

	trace.logtype = type;
	trace.loginfo[0] = arg1;
	trace.loginfo[1] = arg2;
	(void) trace_wri_log(&trace);
}

void
trace_write_3(uint_t type, intptr_t arg1, intptr_t arg2, intptr_t arg3)
{
	TRACE	trace;

	trace.logtype = type;
	trace.loginfo[0] = arg1;
	trace.loginfo[1] = arg2;
	trace.loginfo[2] = arg3;
	(void) trace_wri_log(&trace);
}

void
trace_write_4(uint_t type, intptr_t arg1, intptr_t arg2, intptr_t arg3,
			  intptr_t arg4)
{
	TRACE	trace;

	trace.logtype = type;
	trace.loginfo[0] = arg1;
	trace.loginfo[1] = arg2;
	trace.loginfo[2] = arg3;
	trace.loginfo[3] = arg4;
	(void) trace_wri_log(&trace);
}

void
trace_write_5(uint_t type, intptr_t arg1, intptr_t arg2, intptr_t arg3,
			  intptr_t arg4, intptr_t arg5)
{
	TRACE	trace;

	trace.logtype = type;
	trace.loginfo[0] = arg1;
	trace.loginfo[1] = arg2;
	trace.loginfo[2] = arg3;
	trace.loginfo[3] = arg4;
	trace.loginfo[4] = arg5;
	(void) trace_wri_log(&trace);
}

void
trace_write_6(uint_t type, intptr_t arg1, intptr_t arg2, intptr_t arg3,
			  intptr_t arg4, intptr_t arg5, intptr_t arg6)
{
	TRACE	trace;

	trace.logtype = type;
	trace.loginfo[0] = arg1;
	trace.loginfo[1] = arg2;
	trace.loginfo[2] = arg3;
	trace.loginfo[3] = arg4;
	trace.loginfo[4] = arg5;
	trace.loginfo[5] = arg6;
	(void) trace_wri_log(&trace);
}

/*
 *  ������֥����ǵ��Ҥ���륳���ɤ���ȥ졼����������Ϥ��뤿��δ�
 *  ��
 */

void
log_dsp_enter(TCB *p_tcb)
{
	trace_1(LOG_TYPE_DSP|LOG_ENTER, p_tcb);
}

void
log_dsp_leave(TCB *p_tcb)
{
	trace_1(LOG_TYPE_DSP|LOG_LEAVE, p_tcb);
}

void
log_inh_enter(INHNO inhno)
{
	trace_1(LOG_TYPE_INH|LOG_ENTER, inhno);
}

void
log_inh_leave(INHNO inhno)
{
	trace_1(LOG_TYPE_INH|LOG_LEAVE, inhno);
}

void
log_exc_enter(EXCNO excno)
{
	trace_1(LOG_TYPE_EXC|LOG_ENTER, excno);
}

void
log_exc_leave(EXCNO excno)
{
	trace_1(LOG_TYPE_EXC|LOG_LEAVE, excno);
}