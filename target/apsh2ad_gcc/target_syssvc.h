/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *	Copyright (C) 2010 by Industrial Technology Institute,
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
 *  $Id: target_syssvc.h 760 2010-12-21 02:30:48Z mit-kimai $
 */

/*
 *  �����ƥॵ���ӥ��Υ������åȰ�¸����APSH2AD�ѡ�
 *
 *  �����ƥॵ���ӥ��Υ������åȰ�¸���Υ��󥯥롼�ɥե����롥���Υե�
 *  ��������Ƥϡ�����ݡ��ͥ�ȵ��ҥե�����˵��Ҥ��졤���Υե������
 *  ̵���ʤ븫���ߡ�
 */

#ifndef TOPPERS_TARGET_SYSSVC_H
#define TOPPERS_TARGET_SYSSVC_H

/*
 *  �������åȥ����ƥ�Υϡ��ɥ������񸻤����
 */
#include "apsh2ad.h"

/*
 *  �ץ��å���¸�����
 */
#include "sh2a_dual_gcc/prc_syssvc.h"

/*
 *  �ȥ졼�����˴ؤ�������
 */
#ifdef TOPPERS_TRACE_ENABLE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_TRACE_ENABLE */

/*
 *  ��ư��å������Υ������åȥ����ƥ�̾
 */
#define TARGET_NAME    "APSH2AD(SH7205)"

/*
 *  ��ư��å������˥������åȰ�¸�������ɽ����
 *  �ɲä��뤿��Υޥ���
 */
#ifdef PRC_COPYRIGHT
#define TARGET_COPYRIGHT	PRC_COPYRIGHT
#endif /* PRC_COPYRIGHT */

/*
 *  �����ƥ�������٥���ϤΤ����ʸ������
 *
 *  �������åȰ�¸����ˡ�ǡ�ʸ��c��ɽ��/����/��¸���롥
 */
extern void	target_fput_log(char_t c);

/*
 *  ���ꥢ��ݡ��ȿ������
 */
#define TNUM_PORT        1        /* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */
#define TNUM_SIOP        TNUM_PORT


/*
 *  �ܡ��졼��
 */
#define BPS_SETTING 		38400
#define SCIF0_BPS_SETTING  (((PCLOCK / 32) / BPS_SETTING) - 1)
#define SCIF1_BPS_SETTING  (((PCLOCK / 32) / BPS_SETTING) - 1)

/*
 *  ����å�������
 */
/*  ��������å���SCK ü�Ҥ�����ü�ҡ����Ͽ����̵���  */
#define SCIF0_CKE_SETTING	0x00U
#define SCIF1_CKE_SETTING	0x00U


#define SIO_INIT_DLY		1000000	/* ��ư�����Ԥ�����(1�ӥå�ʬ) */

/*
 *  �����ƥ����������Ϣ����������
 *
 *  �ǥե�����ͤ��̤ꡥ
 */

/*
 *  �����ƥ�������Ѥ���ݡ��ȿ��ȼºݤΥݡ��ȿ���������������å�
 *  
 *  ���������åȥܡ��ɤ˥��ꥢ��ݡ��ȤΥ��ͥ��������Ĥ����ʤ����ᡢ
 *  ���������åȰ�¸���Υǥե���ȤǤϥ����ƥ����ǽ�򥰥��Х�����
 *  ���ǻ��Ѥ��뤳�Ȥ�����Ȥ��Ƥ��롣
 *  ���ʥ��եȥ��������Τ�TNUM_PORT�������2���ѹ�����С�2�ݡ��Ȼ���
 *  ���Ǥ��뤬���ϡ��ɥ�����¦�⥳�ͥ������ɲä���ɬ�פ����롣��
 *  �������Х���������ꤹ��G_SYSLOG�ޥ��������ϡ����ץꥱ�������
 *  ��¦��Makefile�ǹԤ�������ץ�ץ����Ǥϡ�G_SYSLOG�ޥ������
 *  ������Ƥ��ʤ����ᡢ�ǥե���ȤΤޤޥӥ�ɤ����make depend����
 *  ���ʲ��Υ��顼��å�������ɽ������뤬��G_SYSLOG�ޥ����������ɲ�
 *  �����뤳�Ȥˤ�ꡢ�������ӥ�ɤǤ���褦�ˤʤ롣
 *  ��
 *  ��G_SYSLOG�������ˡ��
 *  ������ˡ��
 *  ������configure������ץȤ�-s���ץ������դ��Ƽ¹Ԥ��롣
 *  ���������㡧configure -s -T apsh2ad_gcc
 *  �������ܤ����ϡ�fmp/doc/user.txt��
 *  ���������֣�������ե�����졼����󥹥���ץȤλȤ����פ򻲾�
 *  ������ˡ��
 *  ������Makefile����ѿ�ENABLE_G_SYSLOG��true�����ꤹ�뤳�Ȥˤ�ꡤ
 *  �����������Х�������ͭ���Ȥʤ롣
 *  �������ܤ����ϡ��桼�������ޥ˥奢��fmp/user.txt��
 *  ��������6.1 Makefile���ѿ������
 *  ������������(M) �����ƥ����ǽ�Υ����Х������λ���פ򻲾�
 */
#if !defined(G_SYSLOG) && (TNUM_PORT < TNUM_PRCID)
#error !defined(G_SYSLOG) && (TNUM_PORT < TNUM_PRCID) : check G_SYSLOG and TNUM_PORT !
#endif /* defined(G_SYSLOG) && (TNUM_PORT == 1) */

#endif /* TOPPERS_TARGET_SYSSVC_H */
