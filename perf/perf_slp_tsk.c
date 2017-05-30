/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: perf_act_tsk.c 170 2009-02-25 08:27:36Z ertl-kikuchi $
 */

/*
 *  sig_sem ��ǽ¬��ץ����
 */

#include <kernel.h>
#include <t_syslog.h>
#include <sil.h>
#include <histogram.h>
#include "kernel_cfg.h"
#include "perf_slp_tsk.h"
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
static uint_t	histarea2[MAX_TIME + 1];

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

void task1_1(intptr_t exinf)
{
	end_measure(1);
	begin_measure(2);
	wup_tsk(MAIN_TASK1);
}

/*
 * ��¬�롼����
 */
void perf_eval(uint_t n)
{
	uint_t	i;

	init_hist(1, MAX_TIME, histarea1);
	init_hist(2, MAX_TIME, histarea2);

	sus_tsk(LOGTASK1);
	dly_tsk(1000);
	CPU1_PERF_PRE_HOOK;

	for ( i = 0; i < NO_MEASURE; i++ ) {
		switch (n) {
			//�����С��إåɤ�¬��
		case 0:
			begin_measure(1);
			end_measure(1);
			break;
			//��1��slp_tsk()������ͥ���٤Υ��������ڤ��ؤ��ޤǤλ���
			//��2��wup_tsk()�����ͥ���٤Υ��������ڤ��ؤ��ޤǤλ���
		case 1:
			act_tsk(TASK1_1);
			begin_measure(1);
			slp_tsk();
			end_measure(2);
			chg_pri(0, LOW_PRIORITY);
			chg_pri(0, MAIN_PRIORITY);
			break;
		}
	}

	CPU1_PERF_POST_HOOK;
	rsm_tsk(LOGTASK1);


	syslog(LOG_NOTICE, "==================================");
	syslog(LOG_NOTICE, "(%d)", n);
	syslog(LOG_NOTICE, "----------------------------------");
	print_hist(1);
	
	if (n == 1) {
		syslog(LOG_NOTICE, "==================================");
		syslog(LOG_NOTICE, "(%d)", 2);
		syslog(LOG_NOTICE, "----------------------------------");
		print_hist(2);
	}
}

/*
 *  PE1 �ᥤ�󥿥�������ͥ����
 */
void main_task1(intptr_t exinf)
{
	perf_eval(0);
	perf_eval(1);
}
