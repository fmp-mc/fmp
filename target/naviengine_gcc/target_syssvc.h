/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2008-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_syssvc.h 606 2010-05-10 06:16:33Z ertl-honda $
 */

/*
 *  �����ƥॵ���ӥ��Υ������åȰ�¸����NaviEngine�ѡ�
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
#include "naviengine.h"
#include "arm_gcc/mpcore/mpcore.h"

/*
 *  �ȥ졼�����˴ؤ�������
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  ��ư��å������Υ������åȥ����ƥ�̾
 */
#define TARGET_NAME    "ARM NaviEngine(11MPCore)"

/*
 *  �����ƥ�������٥���ϤΤ����ʸ������
 *
 *  �������åȰ�¸����ˡ�ǡ�ʸ��c��ɽ��/����/��¸���롥
 */
extern void	target_fput_log(char_t c);

/*
 *  ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο�
 */
#ifdef G_SYSLOG
#define TNUM_PORT       1
#else
#ifndef TNUM_PORT
#define TNUM_PORT       2
#endif  /* TNUM_PORT */
#endif /* G_SYSLOG */

#define INHNO_SIO0   DIC_IRQNO_UART0   /* UART0����ߥϥ�ɥ��ֹ� */
#define INTNO_SIO0   DIC_IRQNO_UART0   /* UART0������ֹ� */
#define INHNO_SIO1   DIC_IRQNO_UART1   /* UART1����ߥϥ�ɥ��ֹ� */
#define INTNO_SIO1   DIC_IRQNO_UART1   /* UART1������ֹ� */
#define INHNO_SIO2   DIC_IRQNO_UART2   /* UART2����ߥϥ�ɥ��ֹ� */
#define INTNO_SIO2   DIC_IRQNO_UART2   /* UART2������ֹ� */
#define INHNO_SIO3   DIC_IRQNO_UART3   /* UART3����ߥϥ�ɥ��ֹ� */
#define INTNO_SIO3   DIC_IRQNO_UART3   /* UART3������ֹ� */

#define INTPRI_SIO0       -2              /* UART�����ͥ���� */
#define INTATR_SIO0       0U              /* UART�����°�� */
#define INTPRI_SIO1       -2              /* UART�����ͥ���� */
#define INTATR_SIO1       0U              /* UART�����°�� */
#define INTPRI_SIO2       -2              /* UART�����ͥ���� */
#define INTATR_SIO2       0U              /* UART�����°�� */
#define INTPRI_SIO3       -2              /* UART�����ͥ���� */
#define INTATR_SIO3       0U              /* UART�����°�� */

/*
 *  �����ƥ����������Ϣ����������
 *
 *  �ǥե�����ͤ��̤ꡥ
 */

#endif /* TOPPERS_TARGET_SYSSVC_H */
