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
 *  @(#) $Id: test_mact_tsk3.c 661 2010-07-29 10:10:12Z ertl-honda $
 */

/* 
 *		mact_tsk�����ӥ�������Υƥ���(3)
 *  �ڥƥ��Ȥ���Ū��
 *    �оݥ��������������Ԥ��Υ��������Ф��ơ�mact_tsk��ȯ�Ԥ��롥
 *
 *  �ڥƥ��ȹ��ܡ�
 *
 *    (2-H) ���ץ��å��˳���դ���줿��������¾�ץ��å���
 *    (2-I) ¾�ץ��å��˳���դ���줿�������򼫥ץ��å���
 */

#include <kernel.h>
#include <t_syslog.h>
#include <test_lib.h>
#include <sil.h>
#include "kernel_cfg.h"

void
task1_4(intptr_t exinf)
{
	ER		ercd;
	FLGPTN flgptn;
  
	check_point(1);
	ercd = mact_tsk(TASK1_5,2);
	check_ercd(ercd, E_OK);

	check_point(2);
	ercd = mact_tsk(TASK1_5,2);
	check_ercd(ercd, E_OK);

	//Ʊ���ե饰�Ԥ� 1���ܵ�ư�Ԥ�
	do{
		ercd = pol_flg(FLG1,1,TWF_ANDW,&flgptn);
	}while(ercd != E_OK);

	check_point(3);
	ercd = wup_tsk(TASK1_5);
	check_ercd(ercd, E_OK);

	//Ʊ���ե饰�Ԥ� 2���ܵ�ư�Ԥ�
	do{
		ercd = pol_flg(FLG1,2,TWF_ANDW,&flgptn);
		}while(ercd != E_OK);

	check_point(4);
	ercd = wup_tsk(TASK1_5);
	check_ercd(ercd, E_OK);

//��������¾�ץ��å��˳���դ���줿�������򼫥ץ��å���
	check_point(5);
	ercd = mact_tsk(TASK2_1,1);
	check_ercd(ercd, E_OK);

	check_point(7);
	ercd = mact_tsk(TASK2_1,1);
	check_ercd(ercd, E_OK);

	check_point(8);
	ercd = wup_tsk(TASK2_1);
	check_ercd(ercd, E_OK);

	check_point(11);
	ercd = wup_tsk(TASK2_1);
	check_ercd(ercd, E_OK);

	/*
	 * �ƥ��Ƚ�λ
	 */
  
	check_finish(13);//CPU1
}

void
task1_5(intptr_t exinf)
{
	ER		ercd;
	static uint_t actno=0;

	actno++;
	if(actno==1){
		check_point(1);
		ercd = set_flg(FLG1,1);
		check_ercd(ercd, E_OK);    
	}else if(actno ==2){
		check_point(3);
		ercd = set_flg(FLG1,2);
		check_ercd(ercd, E_OK);    
	}

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	if(actno==1){
		check_point(2);
	}else if(actno ==2){
		check_point(4);

	/*
	 * �ƥ��Ƚ�λ
	 */
		check_finish(5);
	}
  
}

void
task2_1(intptr_t exinf)
{
	ER		ercd;
	static uint_t actno=0;

	actno++;
	if(actno==1){
		check_point(6);
	}else if(actno ==2){
		check_point(10);
	}

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	if(actno==1){
		check_point(9);
	}else if(actno ==2){
		check_point(12);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);
	}
  
}
