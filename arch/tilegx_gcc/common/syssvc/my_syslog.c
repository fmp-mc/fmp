/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: syslog.c 900 2012-02-24 05:25:12Z ertl-honda $
 */

/*
 *		�����ƥ����ǽ
 */

#include <kernel.h>
#include <sil.h>
#undef TOPPERS_OMIT_SYSLOG
#include <t_syslog.h>
#include <log_output.h>
#include "target_syssvc.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_SYSLOG_WRI_LOG_ENTER
#define LOG_SYSLOG_WRI_LOG_ENTER(prio, p_syslog)
#endif /* LOG_SYSLOG_WRI_LOG_ENTER */

#ifndef LOG_SYSLOG_WRI_LOG_LEAVE
#define LOG_SYSLOG_WRI_LOG_LEAVE(ercd)
#endif /* LOG_SYSLOG_WRI_LOG_LEAVE */

#ifndef LOG_SYSLOG_REA_LOG_ENTER
#define LOG_SYSLOG_REA_LOG_ENTER(p_syslog)
#endif /* LOG_SYSLOG_REA_LOG_ENTER */

#ifndef LOG_SYSLOG_REA_LOG_LEAVE
#define LOG_SYSLOG_REA_LOG_LEAVE(ercd, p_syslog)
#endif /* LOG_SYSLOG_REA_LOG_LEAVE */

#ifndef LOG_SYSLOG_MSK_LOG_ENTER
#define LOG_SYSLOG_MSK_LOG_ENTER(logmask, lowmask)
#endif /* LOG_SYSLOG_MSK_LOG_ENTER */

#ifndef LOG_SYSLOG_MSK_LOG_LEAVE
#define LOG_SYSLOG_MSK_LOG_LEAVE(ercd)
#endif /* LOG_SYSLOG_MSK_LOG_LEAVE */

#ifndef LOG_SYSLOG_REF_LOG_ENTER
#define LOG_SYSLOG_REF_LOG_ENTER(pk_rlog)
#endif /* LOG_SYSLOG_REF_LOG_ENTER */

#ifndef LOG_SYSLOG_REF_LOG_LEAVE
#define LOG_SYSLOG_REF_LOG_LEAVE(pk_rlog)
#endif /* LOG_SYSLOG_REF_LOG_LEAVE */

/*
 *  �����ƥ����ǽ���ѿ����֤Υǥ��ե�������
 */
#ifndef SEC_SYSLOG
#define SEC_SYSLOG(type, variable) type variable
#endif /* SEC_SYSLOG */

#ifndef SEC_SYSLOG_BEGIN
#define SEC_SYSLOG_BEGIN
#endif /* SEC_SYSLOG_BEGIN */

#ifndef SEC_SYSLOG_END
#define SEC_SYSLOG_END
#endif /* SEC_SYSLOG_END */

#ifndef SEC_PRC1_SYSLOG
#define SEC_PRC1_SYSLOG(type, variable) type variable
#endif /* SEC_PRC1_SYSLOG */

#ifndef SEC_PRC1_SYSLOG_BEGIN
#define SEC_PRC1_SYSLOG_BEGIN
#endif /* SEC_PRC1_SYSLOG_BEGIN */

#ifndef SEC_PRC1_SYSLOG_END
#define SEC_PRC1_SYSLOG_END
#endif /* SEC_PRC1_SYSLOG_END */

#ifndef SEC_PRC2_SYSLOG
#define SEC_PRC2_SYSLOG(type, variable) type variable
#endif /* SEC_PRC2_SYSLOG */

#ifndef SEC_PRC2_SYSLOG_BEGIN
#define SEC_PRC2_SYSLOG_BEGIN
#endif /* SEC_PRC2_SYSLOG_BEGIN */

#ifndef SEC_PRC2_SYSLOG_END
#define SEC_PRC2_SYSLOG_END
#endif /* SEC_PRC2_SYSLOG_END */

#ifndef SEC_PRC3_SYSLOG
#define SEC_PRC3_SYSLOG(type, variable) type variable
#endif /* SEC_PRC3_SYSLOG */

#ifndef SEC_PRC3_SYSLOG_BEGIN
#define SEC_PRC3_SYSLOG_BEGIN
#endif /* SEC_PRC3_SYSLOG_BEGIN */

#ifndef SEC_PRC3_SYSLOG_END
#define SEC_PRC3_SYSLOG_END
#endif /* SEC_PRC3_SYSLOG_END */

#ifndef SEC_PRC4_SYSLOG
#define SEC_PRC4_SYSLOG(type, variable) type variable
#endif /* SEC_PRC4_SYSLOG */

#ifndef SEC_PRC4_SYSLOG_BEGIN
#define SEC_PRC4_SYSLOG_BEGIN
#endif /* SEC_PRC4_SYSLOG_BEGIN */

#ifndef SEC_PRC4_SYSLOG_END
#define SEC_PRC4_SYSLOG_END
#endif /* SEC_PRC4_SYSLOG_END */

/*
 *  �ݡ��ȿ��Υ����å�
 */
#if !defined(G_SYSLOG) && (TNUM_PORT < TNUM_PRCID)
#error !defined(G_SYSLOG) && (TNUM_PORT < TNUM_PRCID) : check G_SYSLOG and TNUM_PORT !
#endif /* defined(G_SYSLOG) && (TNUM_PORT == 1) */

/*
 *  �����ƥ������ȥ���֥�å�
 */
typedef struct syslog_control_block{
	SYSLOG	syslog_buffer[TCNT_SYSLOG_BUFFER];	/* ���Хåե� */
	uint_t	syslog_count;		/* ���Хåե���Υ��ο� */
	uint_t	syslog_head;		/* ��Ƭ�Υ��γ�Ǽ���� */
	uint_t	syslog_tail;		/* ���Υ��γ�Ǽ���� */
	uint_t	syslog_lost;		/* ����줿���ο� */
	uint_t	syslog_logmask;		/* ���Хåե��˵�Ͽ���٤������� */
	uint_t	syslog_lowmask_not;	/* ���٥���Ϥ��٤������١�ȿž��*/
}SYSLOGCB;

#ifdef G_SYSLOG

SEC_SYSLOG_BEGIN
SEC_SYSLOG(SYSLOGCB, syslogcb);
SEC_SYSLOG_END

#else /* G_SYSLOG */

#if TNUM_PRCID >= 1
SEC_PRC1_SYSLOG_BEGIN
SEC_PRC1_SYSLOG(SYSLOGCB, prc1_syslogcb);
SEC_PRC1_SYSLOG_END
#endif /* TNUM_PRCID >= 1 */

#if TNUM_PRCID >= 2
SEC_PRC2_SYSLOG_BEGIN
SEC_PRC2_SYSLOG(SYSLOGCB, prc2_syslogcb);
SEC_PRC2_SYSLOG_END
#endif /* TNUM_PRCID >= 2 */

#if TNUM_PRCID >= 3
SEC_PRC3_SYSLOG_BEGIN
SEC_PRC3_SYSLOG(SYSLOGCB, prc3_syslogcb);
SEC_PRC3_SYSLOG_END
#endif /* TNUM_PRCID >= 3 */

#if TNUM_PRCID >= 4
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc4_syslogcb);
SEC_PRC4_SYSLOG_END
#endif /* TNUM_PRCID >= 4 */

#if 1 // Support up to 36 cores. -- ertl-liyixiao

/* TODO: Generated from following Python script.
for i in range(1, 37):
	print("""
#if TNUM_PRCID >= %(prc)s
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc%(prc)s_syslogcb);
SEC_PRC4_SYSLOG_END
#endif""" % {'prc':i})
*/

#if TNUM_PRCID >= 5
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc5_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 6
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc6_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 7
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc7_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 8
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc8_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 9
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc9_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 10
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc10_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 11
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc11_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 12
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc12_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 13
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc13_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 14
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc14_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 15
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc15_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 16
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc16_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 17
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc17_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 18
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc18_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 19
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc19_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 20
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc20_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 21
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc21_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 22
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc22_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 23
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc23_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 24
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc24_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 25
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc25_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 26
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc26_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 27
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc27_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 28
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc28_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 29
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc29_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 30
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc30_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 31
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc31_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 32
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc32_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 33
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc33_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 34
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc34_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 35
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc35_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#if TNUM_PRCID >= 36
SEC_PRC4_SYSLOG_BEGIN
SEC_PRC4_SYSLOG(SYSLOGCB, prc36_syslogcb);
SEC_PRC4_SYSLOG_END
#endif

#else

#if TNUM_PRCID >= 5
#error Syslog Not Support more than 5 processor!
#endif /* TNUM_PRCID >= 5 */

#endif

static SYSLOGCB* const p_syslogcb_table[TNUM_PRCID] = {
#if TNUM_PRCID >= 1
	&prc1_syslogcb,
#endif /* TNUM_PRCID >= 1 */

#if TNUM_PRCID >= 2
	&prc2_syslogcb,
#endif /* TNUM_PRCID >= 2 */

#if TNUM_PRCID >= 3
	&prc3_syslogcb,
#endif /* TNUM_PRCID >= 3 */

#if TNUM_PRCID >= 4
	&prc4_syslogcb,
#endif /* TNUM_PRCID >= 4 */

#if 1 // Support up to 36 cores. -- ertl-liyixiao
/* TODO: Generated from following Python script.
for i in range(1, 37):
	print("""#if TNUM_PRCID >= %(prc)s
	&prc%(prc)s_syslogcb,
#endif""" % {'prc':i})
*/
#if TNUM_PRCID >= 5
	&prc5_syslogcb,
#endif
#if TNUM_PRCID >= 6
	&prc6_syslogcb,
#endif
#if TNUM_PRCID >= 7
	&prc7_syslogcb,
#endif
#if TNUM_PRCID >= 8
	&prc8_syslogcb,
#endif
#if TNUM_PRCID >= 9
	&prc9_syslogcb,
#endif
#if TNUM_PRCID >= 10
	&prc10_syslogcb,
#endif
#if TNUM_PRCID >= 11
	&prc11_syslogcb,
#endif
#if TNUM_PRCID >= 12
	&prc12_syslogcb,
#endif
#if TNUM_PRCID >= 13
	&prc13_syslogcb,
#endif
#if TNUM_PRCID >= 14
	&prc14_syslogcb,
#endif
#if TNUM_PRCID >= 15
	&prc15_syslogcb,
#endif
#if TNUM_PRCID >= 16
	&prc16_syslogcb,
#endif
#if TNUM_PRCID >= 17
	&prc17_syslogcb,
#endif
#if TNUM_PRCID >= 18
	&prc18_syslogcb,
#endif
#if TNUM_PRCID >= 19
	&prc19_syslogcb,
#endif
#if TNUM_PRCID >= 20
	&prc20_syslogcb,
#endif
#if TNUM_PRCID >= 21
	&prc21_syslogcb,
#endif
#if TNUM_PRCID >= 22
	&prc22_syslogcb,
#endif
#if TNUM_PRCID >= 23
	&prc23_syslogcb,
#endif
#if TNUM_PRCID >= 24
	&prc24_syslogcb,
#endif
#if TNUM_PRCID >= 25
	&prc25_syslogcb,
#endif
#if TNUM_PRCID >= 26
	&prc26_syslogcb,
#endif
#if TNUM_PRCID >= 27
	&prc27_syslogcb,
#endif
#if TNUM_PRCID >= 28
	&prc28_syslogcb,
#endif
#if TNUM_PRCID >= 29
	&prc29_syslogcb,
#endif
#if TNUM_PRCID >= 30
	&prc30_syslogcb,
#endif
#if TNUM_PRCID >= 31
	&prc31_syslogcb,
#endif
#if TNUM_PRCID >= 32
	&prc32_syslogcb,
#endif
#if TNUM_PRCID >= 33
	&prc33_syslogcb,
#endif
#if TNUM_PRCID >= 34
	&prc34_syslogcb,
#endif
#if TNUM_PRCID >= 35
	&prc35_syslogcb,
#endif
#if TNUM_PRCID >= 36
	&prc36_syslogcb,
#endif
#endif
};

#endif /* G_SYSLOG */


#ifdef G_SYSLOG

/*
 *  �����ƥ������ȥ���֥�å��ؤΥ�������
 */

Inline SYSLOGCB*
get_p_syslogcb(void){
	return (&syslogcb);
}

#else /* G_SYSLOG */

Inline SYSLOGCB*
get_p_syslogcb(void){
	ID prcid;

	sil_get_pid(&prcid);

	return p_syslogcb_table[prcid - 1];
}

#endif /* G_SYSLOG */

/*
 *  �����ƥ����ǽ�ν����
 */
void
syslog_initialize(intptr_t exinf)
{
	SYSLOGCB *p_syslogcb = get_p_syslogcb();

	p_syslogcb->syslog_count = 0U;
	p_syslogcb->syslog_head = p_syslogcb->syslog_tail = 0U;
	p_syslogcb->syslog_lost = 0U;
    
	p_syslogcb->syslog_logmask = 0U;
	p_syslogcb->syslog_lowmask_not = 0U;
}     

/*
 *  ���ߤΥ����ƥ����
 *
 *  ���������Ф�����ˡ����ʤ��������ͥ�������ѿ��򻲾Ȥ��Ƥ�
 *  �롥
 */
extern ulong_t _kernel_get_my_current_time(void);

/* 
 *  ������ν���
 *
 *  CPU��å����֤�¹ԥ���ƥ����Ȥˤ�餺ư��Ǥ���褦�˼������Ƥ��롥
 *  �������������Х������ξ��ϡ�SIL�Υ��ԥ��å�������˸ƤӽФ���
 *  ����ư����ݾڤ��ʤ���
 */
ER
syslog_wri_log(uint_t prio, const SYSLOG *p_syslog)
{
	SYSLOGCB *p_syslogcb;

	SIL_PRE_LOC;

	LOG_SYSLOG_WRI_LOG_ENTER(prio, p_syslog);

#ifdef G_SYSLOG
	SIL_LOC_SPN();
#else
	SIL_LOC_INT();
#endif /* G_SYSLOG */

	/*
	 * �ޥ����졼������б��Τ��ᡤ��å���˼���
	 */
	p_syslogcb = get_p_syslogcb();

	/*
	 *  �����������
	 */
	((SYSLOG *) p_syslog)->logtim = _kernel_get_my_current_time();

	/*
	 *  �ץ��å�ID������
	 */
	sil_get_pid(&(((SYSLOG *) p_syslog)->prcid));

	/*
	 *  ���Хåե��˵�Ͽ
	 */
	if ((p_syslogcb->syslog_logmask & LOG_MASK(prio)) != 0U) {
		p_syslogcb->syslog_buffer[p_syslogcb->syslog_tail] = *p_syslog;
		(p_syslogcb->syslog_tail)++;
		if (p_syslogcb->syslog_tail >= TCNT_SYSLOG_BUFFER) {
			p_syslogcb->syslog_tail = 0U;
		}
		if (p_syslogcb->syslog_count < TCNT_SYSLOG_BUFFER) {
			p_syslogcb->syslog_count++;
		}
		else {
			p_syslogcb->syslog_head = p_syslogcb->syslog_tail;
			(p_syslogcb->syslog_lost)++;
		}
	}

	/*
	 *  ���٥����
	 */
	if (((~(p_syslogcb->syslog_lowmask_not)) & LOG_MASK(prio)) != 0U) {
		syslog_print(p_syslog, target_fput_log);
		(*target_fput_log)('\n');
	}

#ifdef G_SYSLOG
	SIL_UNL_SPN();
#else
	SIL_UNL_INT();
#endif /* G_SYSLOG */

	LOG_SYSLOG_WRI_LOG_LEAVE(E_OK);
	return(E_OK);
}

/*
 *  ���Хåե�������ɽФ�
 *
 *  CPU��å����֤�¹ԥ���ƥ����Ȥˤ�餺ư��Ǥ���褦�˼������Ƥ��롥
 *  �������������Х������ξ��ϡ�SIL�Υ��ԥ��å�������˸ƤӽФ���
 *  ����ư����ݾڤ��ʤ���
 */
ER_UINT
syslog_rea_log(SYSLOG *p_syslog)
{
	ER_UINT	ercd;
	SYSLOGCB *p_syslogcb;

	SIL_PRE_LOC;

	LOG_SYSLOG_REA_LOG_ENTER(p_syslog);

#ifdef G_SYSLOG
	SIL_LOC_SPN();
#else
	SIL_LOC_INT();
#endif /* G_SYSLOG */

	/*
	 * �ޥ����졼������б��Τ��ᡤ��å���˼���
	 */
	p_syslogcb = get_p_syslogcb();

	/*
	 *  ���Хåե�����μ�Ф�
	 */
	if (p_syslogcb->syslog_count > 0U) {
		*p_syslog = p_syslogcb->syslog_buffer[p_syslogcb->syslog_head];
		(p_syslogcb->syslog_count)--;
		(p_syslogcb->syslog_head)++;
		if (p_syslogcb->syslog_head >= TCNT_SYSLOG_BUFFER) {
			p_syslogcb->syslog_head = 0U;
		}
		ercd = (ER_UINT) (p_syslogcb->syslog_lost);
		p_syslogcb->syslog_lost = 0U;
	}
	else {
		ercd = E_OBJ;
	}

#ifdef G_SYSLOG
	SIL_UNL_SPN();
#else
	SIL_UNL_INT();
#endif /* G_SYSLOG */

	LOG_SYSLOG_REA_LOG_LEAVE(ercd, p_syslog);
	return(ercd);
}

/* 
 *  ���Ϥ��٤�������ν����٤�����
 *
 *  CPU��å����֤�¹ԥ���ƥ����Ȥˤ�餺ư��Ǥ���褦�˼������Ƥ��롥
 *  �������������Х������ξ��ϡ�SIL�Υ��ԥ��å�������˸ƤӽФ���
 *  ����ư����ݾڤ��ʤ���
 */
ER
syslog_msk_log(uint_t logmask, uint_t lowmask)
{
	SYSLOGCB *p_syslogcb;

	SIL_PRE_LOC;

	LOG_SYSLOG_MSK_LOG_ENTER(logmask, lowmask);

#ifdef G_SYSLOG
	SIL_LOC_SPN();
#else
	SIL_LOC_INT();
#endif /* G_SYSLOG */

	/*
	 * �ޥ����졼������б��Τ��ᡤ��å���˼���
	 */
	p_syslogcb = get_p_syslogcb();

	p_syslogcb->syslog_logmask = logmask;
	p_syslogcb->syslog_lowmask_not = ~lowmask;

#ifdef G_SYSLOG
	SIL_UNL_SPN();
#else
	SIL_UNL_INT();
#endif /* G_SYSLOG */

	LOG_SYSLOG_MSK_LOG_LEAVE(E_OK);

	return(E_OK);
}

/*
 *  ���Хåե��ξ��ֻ���
 *
 *  CPU��å����֤�¹ԥ���ƥ����Ȥˤ�餺ư��Ǥ���褦�˼������Ƥ��롥
 *  �������������Х������ξ��ϡ�SIL�Υ��ԥ��å�������˸ƤӽФ���
 *  ����ư����ݾڤ��ʤ���
 */
ER_UINT
syslog_ref_log(T_SYSLOG_RLOG *pk_rlog)
{
	SYSLOGCB *p_syslogcb;

	SIL_PRE_LOC;

	LOG_SYSLOG_REF_LOG_ENTER(pk_rlog);

#ifdef G_SYSLOG
	SIL_LOC_SPN();
#else
	SIL_LOC_INT();
#endif /* G_SYSLOG */

	/*
	 * �ޥ����졼������б��Τ��ᡤ��å���˼���
	 */
	p_syslogcb = get_p_syslogcb();

	pk_rlog->count = p_syslogcb->syslog_count;
	pk_rlog->lost = p_syslogcb->syslog_lost;
	pk_rlog->logmask = p_syslogcb->syslog_logmask;
	pk_rlog->lowmask = ~(p_syslogcb->syslog_lowmask_not);

#ifdef G_SYSLOG
	SIL_UNL_SPN();
#else
	SIL_UNL_INT();
#endif /* G_SYSLOG */

	LOG_SYSLOG_REF_LOG_LEAVE(pk_rlog);
	return(E_OK);
}
