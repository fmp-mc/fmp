/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel  
 * 
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
 *  @(#) $Id: marzen.h 943 2012-10-19 07:50:40Z ertl-honda $
 */

/*
 *  Marzen�ѥɥ饤�����
 */

#ifndef TOPPERS_MARZEN_H
#define TOPPERS_MARZEN_H

#include <sil.h>
#include "r_car_h1.h"

/*
 * ��������å���1000MHz��
 */
#define MARZEN_CORE_CLK  1000

/*
 *  MPCore��¢�Υץ饤�١��ȥ����ޤ�1MS��ư����뤿��Υץꥹ�����顼
 *  �������͡�1Mhz�����ꥳ������å���1/4��PERIPHCLK�Ƕ�ư����롥
 */
#define MPCORE_TM_PS_1MS    (MARZEN_CORE_CLK/4)

/*
 *  MPCore��¢�Υ����ޤ�1MS��ư����뤿��Υ�������
 */
#define MPCORE_TM_LOAD_1MS    1000

/*
 *  TMU�Υ������ͤ�����ɽ���ȥߥ���ñ�̤Ȥ��Ѵ�
 */
#define TMU_TIMER_CLOCK  (62500 / 4)

/*
 *  �����Х륿���ޤΥ���å����ȿ�
 */
#define MPCORE_GTC_CLOCK_FREQ_MHZ     (MARZEN_CORE_CLK/4)

#ifndef TOPPERS_MACRO_ONLY
/*
 *  UART����Υݡ���󥰽���
 */
extern void marzen_uart_putc(char_t c);

/*
 * �ݡ���󥰽��ϤΤ����UART�ν����
 */
extern void marzen_uart_init(void);

/*
 *  �ܡ��ɰ�¸�ν����
 */
extern void marzen_init(void);

/*
 *  timer_rate_hz
 */
uint32_t timer_rate_hz;

/*
 *  ��ȯ�Ķ���¸�ν���(T.B.D)
 */
Inline void
marzen_exit(void)
{
	while(1);
}

/*
 *  �ȥ졼�����˴ؤ������
 */
//#define TRACE_HW_INIT()   scu_counter_init()
//#define TRACE_GET_TIM()   ((scu_counter_get_current() * 1000) / NAVIENGINE_CORE_CLK)

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_MARZEN_H */
