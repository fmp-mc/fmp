/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2007-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: test_mact_tsk1.c 16 2008-12-08 06:15:08Z ertl-honda $
 */

/* 
 *		���ԥ��å������ӥ�������Υƥ���
 *  �ڥƥ��Ȥ���Ū��
 *    ���ԥ��å������ӥ������뤬ư��Ƥ��뤫�����å����롥
 *
 *  �ڥƥ��ȹ��ܡ�
 *    API�μ���ˤ����ʬ����Ԥ���
 *
 *    (1) loc_spn�ˤ�륿�����֤���¾����
 *    (2) try_spn�ˤ�륿�����֤���¾����
 *    (3) iloc_spn�ˤ�륢�顼��ϥ�ɥ�֤���¾����
 *    (4) itry_spn�ˤ�륢�顼��ϥ�ɥ�֤���¾����
 *    (5) loc_spn��iloc_spn�ˤ�륿�����ȥ��顼��ϥ�ɥ�֤���¾����
 *    (6) try_spn��itry_spn�ˤ�륿�����ȥ��顼��ϥ�ɥ�֤���¾����  
 */


#include <kernel.h>
#include <t_syslog.h>
#include <test_lib.h>
#include <sil.h>
#include "kernel_cfg.h"

#define LOOP_REF 10000
#define BUSY_LOOP_REF 1000

volatile int32_t global_data;

/*
 *  ���16bit�Υ��󥯥����
 */
int32_t
inc_data_upper(int32_t data)
{
	uint_t i;

	for (i = 0; i < BUSY_LOOP_REF; i++);
	return data + 0x10000;
}

/*
 *  ����6bit�Υ��󥯥����
 */
int32_t
inc_data_lower(int32_t data)
{
	uint_t i;

	for (i = 0; i < BUSY_LOOP_REF; i++);
	return data + 0x0001;
}

/*
 *  PE1��ư���ƥ��ȤΥᥤ�󥿥���
 */
void
task1_1(intptr_t exinf)
{
	ER	ercd;
	uint_t  i;

	check_point(1);

	/*
	 * (1) loc_spn�ˤ�륿�����֤���¾����
	 */
	global_data = 0;
	ercd = act_tsk(TASK2_1);
	check_ercd(ercd, E_OK);

	barrier_sync(1);

	for(i = 0; i < LOOP_REF; i++) {
		ercd = loc_spn(SPN1);
		check_ercd(ercd, E_OK);
		global_data = inc_data_upper(global_data);
		ercd = unl_spn(SPN1);
		check_ercd(ercd, E_OK);
	}

	check_assert((global_data & 0xffff0000) == (LOOP_REF << 16));

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(2);

	/*
	 * (2) try_spn�ˤ�륿�����֤���¾����
	 */
	global_data = 0;
	ercd = act_tsk(TASK2_2);
	check_ercd(ercd, E_OK);

	barrier_sync(2);

	for(i = 0; i < LOOP_REF; i++) {
		do {
			ercd = try_spn(SPN1);
		}while(ercd == E_OBJ);
		check_ercd(ercd, E_OK);
		global_data = inc_data_upper(global_data);
		ercd = unl_spn(SPN1);
		check_ercd(ercd, E_OK);
	}

	check_assert((global_data & 0xffff0000) == (LOOP_REF << 16));

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(3);

	/*
	 * (3) iloc_spn�ˤ�륢�顼��ϥ�ɥ�֤���¾����
	 */
	global_data = 0;
	ercd = sta_alm(ALMHDR2_1, 1);
	check_ercd(ercd, E_OK);

	check_point(4);
	ercd = sta_alm(ALMHDR1_1, 1);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(7);

	/*
	 * (4) itry_spn�ˤ�륢�顼��ϥ�ɥ�֤���¾����
	 */
	global_data = 0;
	ercd = sta_alm(ALMHDR2_2, 1);
	check_ercd(ercd, E_OK);

	check_point(8);
	ercd = sta_alm(ALMHDR1_2, 1);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(11);

	/*
	 * (5) loc_spn��iloc_spn�ˤ�륿�����ȥ��顼��ϥ�ɥ�֤���¾����
	 */
	global_data = 0;
	ercd = sta_alm(ALMHDR2_3, 1);
	check_ercd(ercd, E_OK);

	barrier_sync(5);

	for(i = 0; i < LOOP_REF; i++) {
		ercd = loc_spn(SPN1);
		check_ercd(ercd, E_OK);
		global_data = inc_data_upper(global_data);
		ercd = unl_spn(SPN1);
		check_ercd(ercd, E_OK);
	}

	check_assert((global_data & 0xffff0000) == (LOOP_REF << 16));

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(12);

	/*
	 * (6) try_spn��itry_spn�ˤ�륿�����ȥ��顼��ϥ�ɥ�֤���¾����
	 */
	global_data = 0;
	ercd = sta_alm(ALMHDR2_4, 11);
	check_ercd(ercd, E_OK);

	barrier_sync(6);

	for(i = 0; i < LOOP_REF; i++) {
		do {
			ercd = try_spn(SPN2);
		} while(ercd == E_OBJ);
		check_ercd(ercd, E_OK);
		global_data = inc_data_upper(global_data);
		ercd = unl_spn(SPN2);
		check_ercd(ercd, E_OK);
	}

	check_assert((global_data & 0xffff0000) == (LOOP_REF << 16));

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_finish(13);
}

/*
 * (1) loc_spn�ˤ�륿�����֤���¾�����ѤΥ�����
 */
void
task2_1(intptr_t exinf)
{
	ER	ercd;
	uint_t i;

	check_point(1);
	barrier_sync(1);

	for(i = 0; i < LOOP_REF; i++) {
		ercd = loc_spn(SPN1);
		check_ercd(ercd, E_OK);
		global_data = inc_data_lower(global_data);
		ercd = unl_spn(SPN1);
		check_ercd(ercd, E_OK);
	}

	check_assert((global_data & 0xffff) == LOOP_REF);

	ercd = wup_tsk(TASK1_1);
	check_ercd(ercd, E_OK);

	check_point(2);
}

/*
 * (2) try_spn�ˤ�륿�����֤���¾�����ѤΥ�����
 */
void
task2_2(intptr_t exinf)
{
	ER	ercd;
	uint_t i;

	check_point(3);
	barrier_sync(2);

	for(i = 0; i < LOOP_REF; i++) {
		do {
			ercd = try_spn(SPN1);
		} while(ercd == E_OBJ);
		check_ercd(ercd, E_OK);
		global_data = inc_data_lower(global_data);
		ercd = unl_spn(SPN1);
		check_ercd(ercd, E_OK);
	}

	check_assert((global_data & 0xffff) == LOOP_REF);

	ercd = wup_tsk(TASK1_1);
	check_ercd(ercd, E_OK);

	check_point(4);
}

/*
 * (3) iloc_spn�ˤ�륢�顼��ϥ�ɥ�֤���¾����
 */
void
alarm_handler1_1(intptr_t exinf)
{
	ER	ercd;
	uint_t i;

	check_point(5);
	barrier_sync(3);

	for(i = 0; i < LOOP_REF; i++) {
		ercd = iloc_spn(SPN2);
		check_ercd(ercd, E_OK);
		global_data = inc_data_upper(global_data);
		ercd = iunl_spn(SPN2);
		check_ercd(ercd, E_OK);
	}

	check_assert((global_data & 0xffff0000) == (LOOP_REF << 16));

	ercd = iwup_tsk(TASK1_1);
	check_ercd(ercd, E_OK);

	check_point(6);
}

void
alarm_handler2_1(intptr_t exinf)
{
	ER	ercd;
	uint_t i;

	check_point(5);

	barrier_sync(3);

	for(i = 0; i < LOOP_REF; i++) {
		ercd = iloc_spn(SPN2);
		check_ercd(ercd, E_OK);
		global_data = inc_data_lower(global_data);
		ercd = iunl_spn(SPN2);
		check_ercd(ercd, E_OK);
	}

	check_assert((global_data & 0xffff) == LOOP_REF);

	ercd = iwup_tsk(TASK1_1);
	check_ercd(ercd, E_OK);

	check_point(6);
}

/*
 * (4) itry_spn�ˤ�륢�顼��ϥ�ɥ�֤���¾����
 */
void
alarm_handler1_2(intptr_t exinf)
{
	ER	ercd;
	uint_t i;

	check_point(9);
	barrier_sync(4);

	for(i = 0; i < LOOP_REF; i++) {
		do {
			ercd = itry_spn(SPN2);
		} while(ercd == E_OBJ);
		check_ercd(ercd, E_OK);
		global_data = inc_data_upper(global_data);
		ercd = iunl_spn(SPN2);
		check_ercd(ercd, E_OK);
	}

	check_assert((global_data & 0xffff0000) == (LOOP_REF << 16));

	ercd = iwup_tsk(TASK1_1);
	check_ercd(ercd, E_OK);

	check_point(10);
}

void
alarm_handler2_2(intptr_t exinf)
{
	ER	ercd;
	uint_t i;

	check_point(7);

	barrier_sync(4);

	for(i = 0; i < LOOP_REF; i++) {
		do {
			ercd = itry_spn(SPN2);
		} while(ercd == E_OBJ);
		check_ercd(ercd, E_OK);
		global_data = inc_data_lower(global_data);
		ercd = iunl_spn(SPN2);
		check_ercd(ercd, E_OK);
	}

	check_assert((global_data & 0xffff) == LOOP_REF);

	ercd = iwup_tsk(TASK1_1);
	check_ercd(ercd, E_OK);

	check_point(8);
}

/*
 * (5) loc_spn��iloc_spn�ˤ�륿�����ȥ��顼��ϥ�ɥ�֤���¾����
 */
void
alarm_handler2_3(intptr_t exinf)
{
	ER	ercd;
	uint_t i;

	check_point(9);
	barrier_sync(5);

	for(i = 0; i < LOOP_REF; i++) {
		ercd = iloc_spn(SPN1);
		check_ercd(ercd, E_OK);
		global_data = inc_data_lower(global_data);
		ercd = iunl_spn(SPN1);
		check_ercd(ercd, E_OK);
	}

	check_assert((global_data & 0xffff) == LOOP_REF);

	ercd = iwup_tsk(TASK1_1);
	check_ercd(ercd, E_OK);

	check_point(10);
}

/*
 * (6) try_spn��itry_spn�ˤ�륿�����ȥ��顼��ϥ�ɥ�֤���¾����
 */
void
alarm_handler2_4(intptr_t exinf)
{
	ER	ercd;
	uint_t i;

	check_point(11);
	barrier_sync(6);

	for(i = 0; i < LOOP_REF; i++) {
		do {
			ercd = itry_spn(SPN2);
		} while(ercd == E_OBJ);
		check_ercd(ercd, E_OK);
		global_data = inc_data_lower(global_data);
		ercd = iunl_spn(SPN2);
		check_ercd(ercd, E_OK);
	}

	check_assert((global_data & 0xffff) == LOOP_REF);

	ercd = iwup_tsk(TASK1_1);
	check_ercd(ercd, E_OK);

	check_finish(12);
}
