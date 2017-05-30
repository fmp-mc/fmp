/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel  
 * 
 *  Copyright (C) 2006-2012 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: naviengine.h 942 2012-10-19 07:49:03Z ertl-honda $
 */

/*
 *  NaviEngine�ѥɥ饤�����
 */

#ifndef TOPPERS_NAVIENGINE_H
#define TOPPERS_NAVIENGINE_H

#include <sil.h>

/*
 * ��������å���400MHz��
 */
#define NAVIENGINE_CORE_CLK  400

/*
 *  MPCore Private Memory Regin Base Address
 */
#define MPCORE_PMR_BASE  0xc0000000

/*
 *  MPCore Status
 */
#define NAVIENGINE_MPCORE_STATUS  0x18037D08

/*
 *  MPCore��¢�Υץ饤�١��ȥ����ޤ�1MS��ư����뤿��Υץꥹ�����顼
 *  �������͡�1Mhz�����ꡥ
 */
#define MPCORE_TM_PS_1MS    199   /* ��������å�399Mhz */

/*
 *  MPCore��¢�Υ����ޤ�1MS��ư����뤿��Υ�������
 */
#define MPCORE_TM_LOAD_1MS    1000

/*
 *  UART�Υ쥸����
 */
#define UART0_BASE		0x18034000
#define UART1_BASE		0x18034400
#define UART2_BASE		0x18034800
#define UART3_BASE		0x18034C80
#define UART4_BASE		0x180350c0

#define	UART_RBR_REG		(0x0 )
#define	UART_THR_REG		(0x0 )
#define	UART_DLL_REG		(0x00)
#define	UART_IER_REG		(0x04)
#define	UART_DLM_REG		(0x04)
#define	UART_IIR_REG		(0x08)
#define	UART_LCR_REG		(0x0c)
#define	UART_MCR_REG		(0x10)
#define	UART_LSR_REG		(0x14)
#define	UART_MSR_REG		(0x18)
#define	UART_SCR_REG		(0x1c)
#define	UART_FCR_REG		(0x20)

/*
 * ������ֹ�
 */
#define DIC_IRQNO_UART0   86
#define DIC_IRQNO_UART1   87
#define DIC_IRQNO_UART2   88
#define DIC_IRQNO_UART3   89

/*
 *  ��������
 */
#define UART0_LCR_VAL 0x03
#define UART0_DLM_VAL 0x00
#define UART0_DLL_VAL 0xd8

#define UART1_LCR_VAL 0x03
#define UART1_DLM_VAL 0x00
#define UART1_DLL_VAL 0xd8

#define UART2_LCR_VAL 0x03
#define UART2_DLM_VAL 0x00
#define UART2_DLL_VAL 0xd8

#define UART3_LCR_VAL 0x03
#define UART3_DLM_VAL 0x00
#define UART3_DLL_VAL 0xd8

#ifndef TOPPERS_MACRO_ONLY
/*
 *  UART����Υݡ���󥰽���
 */
extern void naviengine_uart_putc(char_t c);

/*
 * �ݡ���󥰽��ϤΤ���ν����
 */
extern void naviengine_uart_init(void);
#endif /* TOPPERS_MACRO_ONLY */

#define DIC_TMIN_INTNO    0U
#define DIC_TMAX_INTNO  127U
#define DIC_TNUM_INT    128U

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ��ȯ�Ķ���¸�ν���(T.B.D)
 */
Inline void
naviengine_exit(void)
{
	while(1);
}

/*
 *  �ȥ졼�����˴ؤ������
 *  SCU���Ѥ��롥 
 */
#define TRACE_HW_INIT()   scu_counter_init()
#define TRACE_GET_TIM()   ((scu_counter_get_current() * 1000) / NAVIENGINE_CORE_CLK)

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_NAVIENGINE_H */
