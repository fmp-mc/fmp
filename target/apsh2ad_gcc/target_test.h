/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *	Copyright (C) 2011 by Industrial Technology Institute,
 *								Miyagi Prefectural Government, JAPAN
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
 *  $Id: target_test.h 867 2011-08-09 05:53:10Z mit-kimai $
 */

/*
 *		�ƥ��ȥץ������Υ������åȰ�¸�����APSH2AD�ѡ�
 */

#ifndef TOPPERS_TARGET_TEST_H
#define TOPPERS_TARGET_TEST_H

#define CPUEXC1				0x10009		/* ���ɥ쥹���顼�㳰(CPU0) */
#define CPUEXC2				0x20009		/* ���ɥ쥹���顼�㳰(CPU1) */

/*
 *	���ɥ쥹���顼�㳰ȯ���ؿ�
 *	��
 *	���㳰ȯ�����˥����å������򤵤��PC���ͤϡֺǸ�˼¹Ԥ���̿���
 *	���μ�̿�����Ƭ���ɥ쥹��ؤ��Ƥ��롣
 *	�����ΡֺǸ�˼¹Ԥ���̿��פȤϼºݤ˥��ɥ쥹���顼�㳰��ȯ��
 *	������̿��ǤϤʤ����㳰ȯ�����˥ѥ��ץ饤���Ǽ¹Ԥ���Ƥ���
 *	����³��̿��Ǥ��롣
 *	�����㳰��ȯ������̿�᤬���ꥢ���������ơ����ǡ���³��̿�᤬
 *	�������˼¹ԥ��ơ����ˤ������
 *	��
 *	���ޤ�����³��̿���ʬ��̿�᤬�ޤޤ����ϡ����򤹤٤�PC���ͤ�
 *	���񤭴������Ƥ��륱���������롣
 *	��
 *	���ֺǸ�˼¹Ԥ���̿��פ��㳰ȯ���ս꤫�鲿̿��Υ��Ƥ��뤫
 *	���쳵�ˤϵ����ʤ����ᡢ�����Ǥ�nop̿����������Ƥ��롣
 */
Inline void 
toppers_raise_cpu_exception(void)
{
	uint32_t tmp;
	uint32_t adr = 0xfffffec1U;		/*  �������  */
	
	Asm(" mov.l @%1, %0 \n"			/*  ���ɥ쥹���顼�㳰��ȯ��  */
	    " nop           \n"
	    " nop           \n"
	    " nop           \n"			/*  �������å������򤵤�륢�ɥ쥹  */
	    " nop           " : "=r"(tmp): "r"(adr));
}

#define RAISE_CPU_EXCEPTION	toppers_raise_cpu_exception()

#define LOOP_REF		ULONG_C(500000)	/* ®�ٷ�¬�ѤΥ롼�ײ�� */

/*
 *  �������ǻ��Ѥ��륷�ꥢ��ݡ���ID
 */
#define TASK_PORTID_PRC1			1
#define TASK_PORTID_PRC2			2

/*
 *  ��ǽɾ���ѤΥޥ������
 */
/*  �ǥե���Ȥ�����򤽤Τޤ��Ѥ��롣  */


#endif /* TOPPERS_TARGET_TEST_H */