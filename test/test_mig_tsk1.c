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
 *  @(#) $Id: test_mig_tsk1.c 661 2010-07-29 10:10:12Z ertl-honda $
 */

/* 
 *		mig_tsk�����ӥ�������Υƥ���(1)
 *  �ڥƥ��Ȥ���Ū��
 *    �оݥ����������ٻ߾��֡��¹Բ�ǽ���֤Υ��������Ф��ơ�mig_tsk��ȯ�Ԥ��롥
 *
 *  �ڥƥ��ȹ��ܡ�
 *    (1-A)�оݥ����������ٻ߾���
 *    �¹Բ�ǽ���֤Υ������Ϥ���ˡ���ư��CPU�Υ�ǥ����塼�Ǥΰ��֤ˤ����ʬ����Ԥ���
 *
 *    (1-B) �ǹ�ͥ����
 *    (1-C) �¹Ծ��֤Υ�������Ʊͥ����
 *    (1-D) �¹Ծ��֤Υ����������ͥ����
 *    (1-E) ��ǥ����塼�����ΤȤ���ذ�ư
 */

#include <kernel.h>
#include <t_syslog.h>
#include <test_lib.h>
#include <sil.h>
#include "kernel_cfg.h"

void
task1_1(intptr_t exinf)
{
	ER		ercd;
	FLGPTN  flgptn;

	check_point(1);
	ercd = mig_tsk(TASK1_5,2);
	check_ercd(ercd, E_OK);

	check_point(2);
	ercd = mig_tsk(TASK1_3,2);
	check_ercd(ercd, E_OK);

	//1-3run�Ԥ�
	do{
		ercd = pol_flg(FLG1,8,TWF_ANDW,&flgptn);
	} while(ercd != E_OK);

	check_point(3);
	ercd = mig_tsk(TASK1_4,2);
	check_ercd(ercd, E_OK);
  
	check_point(4);
	ercd = mig_tsk(TASK1_7,2);
	check_ercd(ercd, E_OK);

	//Ʊ���ե饰���å� 1_3�˰�ư��λ������
	check_point(5);
	ercd = set_flg(FLG1,1);
	check_ercd(ercd, E_OK);

	//Ʊ���ե饰���å��Ԥ� 1_7�ε�ư�Ԥ�
	do{
		ercd = pol_flg(FLG1,2,TWF_ANDW,&flgptn);
	} while(ercd != E_OK);

	check_point(6);
	ercd = mig_tsk(TASK1_6,2);
	check_ercd(ercd, E_OK);

	check_point(7);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task1_3(intptr_t exinf)
{
	ER		ercd;
	FLGPTN flgptn;

	check_point(1);

	//1-1�˰�ư������
	ercd = set_flg(FLG1,8);
	check_ercd(ercd, E_OK);

	do{
		ercd = pol_flg(FLG1,1,TWF_ANDW,&flgptn);
	}while(ercd != E_OK);
  
	check_point(2);
	ercd = act_tsk(TASK1_5);
	check_ercd(ercd, E_OK);

	check_point(3);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task1_4(intptr_t exinf)
{
	ER		ercd;

	check_point(4);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task1_5(intptr_t exinf)
{
	ER		ercd;

	check_point(5);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task1_6(intptr_t exinf)
{
	ER		ercd;

	check_point(7);
	ercd = set_flg(FLG1,4);
	check_ercd(ercd, E_OK);

	check_point(8);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task1_7(intptr_t exinf)
{
	ER		ercd;
	FLGPTN  flgptn;

	check_point(6);
	//Ʊ���ե饰���å� 1_1�˵�ư����
	ercd = set_flg(FLG1,2);
	check_ercd(ercd, E_OK);

	//Ʊ���ե饰���å��Ԥ� 1_6�ε�ư�Ԥ�
	do{
		ercd = pol_flg(FLG1,4,TWF_ANDW,&flgptn);
	}while(ercd != E_OK);
  
	check_point(9);
	//Ʊ���ե饰���å�
	ercd = set_flg(FLG1,0x10);
	check_ercd(ercd, E_OK);

	check_point(10);
	//Ʊ���ե饰���å�
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);
    
	check_point(0);
}

void
task1_8(intptr_t exinf)
{
	ER		ercd;
	FLGPTN flgptn;
  
	check_point(8);
  
	do{
		ercd = pol_flg(FLG1,0x10,TWF_ANDW,&flgptn);
	}while(ercd != E_OK);

	check_point(9);
	ercd = mig_tsk(TASK1_9,2);
	check_ercd(ercd, E_OK);

	/*
	 *  �ƥ��Ƚ�λ
	 */

	check_finish(10);//CPU1

}

void
task1_9(intptr_t exinf)
{
	/*
	 *  �ƥ��Ƚ�λ
	 */
    check_finish(11);//CPU2
}
