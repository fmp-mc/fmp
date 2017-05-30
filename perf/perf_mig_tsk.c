/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2008-2010 by Embedded and Real-Time Systems Laboratory
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
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 *
 *  @(#) $Id: perf_mig_tsk.c 661 2010-07-29 10:10:12Z ertl-honda $
 */

/*
 *  mig_tsk ��ǽ¬��ץ����
 */

#include <kernel.h>
#include <t_syslog.h>
#include <test_lib.h>
#include <sil.h>
#include <histogram.h>
#include "kernel_cfg.h"
#include "perf_mig_tsk.h"
#include "target_test.h"

/*
 *  ��¬����ȼ¹Ի���ʬ�ۤ�Ͽ����������
 */
#define NO_MEASURE	20000U			/* ��¬��� */
#define MAX_TIME	400000U			/* �¹Ի���ʬ�ۤ�Ͽ���������� */

/*
 *  �¹Ի���ʬ�ۤ�Ͽ��������ΰ�
 */
static uint_t	histarea1[MAX_TIME + 1];

/*
 *  ��¬������ǤΥեå��롼����
 */
#ifndef CPU1_PERF_PRE_HOOK
#define CPU1_PERF_PRE_HOOK
#endif  /* CPU1_PERF_PRE_HOOK */
#ifndef CPU1_PERF_POST_HOOK
#define CPU1_PERF_POST_HOOK
#endif  /* CPU1_PERF_POST_HOOK */
#ifndef CPU2_PERF_PRE_HOOK
#define CPU2_PERF_PRE_HOOK
#endif  /* CPU2_PERF_PRE_HOOK */
#ifndef CPU2_PERF_POST_HOOK
#define CPU2_PERF_POST_HOOK
#endif  /* CPU2_PERF_POST_HOOK */

void task1_3(intptr_t exinf)
{
	T_RTSK	rtsk;

	ref_tsk(TASK1_3,&rtsk);
	assert(rtsk.prcid == 1);
	begin_measure(1);
	mig_tsk(TASK1_3,2);
	end_measure(1);
	ref_tsk(TASK1_3,&rtsk);
	assert(rtsk.prcid == 2);
	ext_tsk();
}

void task1_5(intptr_t exinf)
{
	;
}

void task1_7(intptr_t exinf)
{
	T_RTSK   rtsk;

	end_measure(1);
	ref_tsk(TASK1_7,&rtsk);
	assert(rtsk.prcid == 2);
	ext_tsk();
}

void task2_1(intptr_t exinf)
{
	T_RTSK   rtsk;
	uint_t   i;

	for(i=0;i<NO_MEASURE;i++){
		PRCID_WAIT(TASK1_5,2); //TASK1_5���ץ��å�2�ˤ���ޤ��Ԥ�
		ref_tsk(TASK1_5,&rtsk);
		assert(rtsk.prcid == 2);
		mig_tsk(TASK1_5,1);
	}
}

/*
 * ��¬�롼����
 */
void perf_eval(uint_t n)
{
	uint_t	 i;
	T_RTSK   rtsk;

	init_hist(1, MAX_TIME, histarea1);
	syslog_flush();
	dly_tsk(1000);
	CPU1_PERF_PRE_HOOK;

	for ( i = 0; i < NO_MEASURE; i++ ) {
		switch (n) {
			//�����С��إåɤ�¬��
		case 0:
			begin_measure(1);
			end_measure(1);
			break;

			//��1���оݥ��������ٻ߾���
		case 1:
			PRCID_WAIT(TASK1_5,1); //TASK1_5���ץ��å����ˤ���ޤ��Ԥ�
			ref_tsk(TASK1_5,&rtsk);
			assert(rtsk.prcid == 1);
			begin_measure(1);
			mig_tsk(TASK1_5,2);
			end_measure(1);
			break;

			//��2���оݥ��������¹Բ�ǽ����
		case 2:
			STAT_WAIT(TASK1_7,TTS_DMT);
			mact_tsk(TASK1_7,1);
			ref_tsk(TASK1_7,&rtsk);
			assert(rtsk.prcid == 1);
			begin_measure(1);
			mig_tsk(TASK1_7,2);
			break;

			//��3���оݥ��������¹Ծ���
		case 3:
			mact_tsk(TASK1_3,1);
			STAT_WAIT(TASK1_3,TTS_DMT);
			break;
		}
	}

	CPU1_PERF_POST_HOOK;

	syslog(LOG_NOTICE, "==================================");
	syslog(LOG_NOTICE, "(%d)", n);
	syslog(LOG_NOTICE, "----------------------------------");
	print_hist(1);
	test_finish();
}

/*
 *  PE1 �ᥤ�󥿥�������ͥ����
 */
void main_task1(intptr_t exinf)
{
	slp_tsk();

	perf_eval(0);
	perf_eval(1);
	perf_eval(2);
	perf_eval(3);

	wup_tsk(MAIN_TASK2);
}

/*
 *  PE2 �ᥤ�󥿥�������ͥ����
 */
void main_task2(intptr_t exinf)
{
#ifndef G_SYSLOG
	sus_tsk(LOGTASK2);
#endif /* G_SYSLOG */
	CPU2_PERF_PRE_HOOK;
	wup_tsk(MAIN_TASK1);
	slp_tsk();
	CPU2_PERF_POST_HOOK;
#ifndef G_SYSLOG
	rsm_tsk(LOGTASK2);
#endif /* G_SYSLOG */
}
