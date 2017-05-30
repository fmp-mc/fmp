/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_syssvc.h 559 2010-04-05 10:04:44Z ertl-honda $
 */

/*
 *  �����ƥॵ���ӥ��Υ������åȰ�¸����SH7786_DEV�ѡ�
 *
 *  �����ƥॵ���ӥ��Υ������åȰ�¸���Υ��󥯥롼�ɥե����롥���Υե�
 *  ��������Ƥϡ�����ݡ��ͥ�ȵ��ҥե�����˵��Ҥ��졤���Υե������
 *  ̵���ʤ븫���ߡ�
 */

#ifndef TOPPERS_TARGET_SYSSVC_H
#define TOPPERS_TARGET_SYSSVC_H

#include "sh7786_dev.h"

/*
 *  �ȥ졼�����˴ؤ�������
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  ���ꥢ��ݡ��ȿ������
 */
#define TNUM_PORT    TNUM_PRCID        /* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */
#define TNUM_SIOP        2

/*
 *  ��ư��å������Υ������åȥ����ƥ�̾
 */
#define TARGET_NAME    "Renesas Prototype 1(SH4A)"

/*
 *  �����ƥ�������٥���ϤΤ����ʸ������
 *
 *  �������åȰ�¸����ˡ�ǡ�ʸ��c��ɽ��/����/��¸���롥
 */
extern void	target_fput_log(char_t c);


/*
 *  �ܡ��졼��
 */

#define BPS_SETTING 38400

#define SCIF0_BPS_SETTING  (((PCLOCK / 32) / BPS_SETTING) - 1)
#define SCIF1_BPS_SETTING  (((PCLOCK / 32) / BPS_SETTING) - 1)
#define SCIF2_BPS_SETTING  (((PCLOCK / 32) / BPS_SETTING) - 1)
#define SCIF3_BPS_SETTING  (((PCLOCK / 32) / BPS_SETTING) - 1)

/*
 *  ����å�������
 */
#define SCIF0_CKE_SETTING  0x03
#define SCIF1_CKE_SETTING  0x03
#define SCIF2_CKE_SETTING  0x03
#define SCIF3_CKE_SETTING  0x03

#define SIO_INIT_DLY     1000000          /* ��ư�����Ԥ�����(1�ӥå�ʬ) */

#endif /* TOPPERS_TARGET_SYSSVC_H */
