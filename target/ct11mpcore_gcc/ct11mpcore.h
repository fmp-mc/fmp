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
 *  @(#) $Id: ct11mpcore.h 942 2012-10-19 07:49:03Z ertl-honda $
 */

/*
 * ARM CT11MPCore with the RealView Emulation Board�ѥɥ饤�����
 */

#ifndef TOPPERS_CT11MPCORE_EB_H
#define TOPPERS_CT11MPCORE_EB_H

#include <sil.h>

/*
 * �ץ��å���
 */
#ifndef TNUM_PRCID
#define TNUM_PRCID  2
#endif /* TNUM_PRCID */

/*
 * ��������å���200MHz��
 */
#define CT11MPCORE_CORE_CLK  200

/*
 *  ����ߤο�
 */
#define DIC_TMAX_INTNO    63U
#define DIC_TNUM_INT      64U

/*
 *  MPCore Private Memory Regin Base Address
 */
#define MPCORE_PMR_BASE  0x1f000000

/*
 *  MPCore��¢�Υץ饤�١��ȥ����ޤ�1MS��ư����뤿��Υץꥹ�����顼
 *  �������͡�1Mhz�����ꡥ
 */
#define MPCORE_TM_PS_1MS    99   /* ��������å�200Mhz */

/*
 *  MPCore��¢�Υ����ޤ�1MS��ư����뤿��Υ�������
 */
#define MPCORE_TM_LOAD_1MS    1000

/*
 * �١������ɥ쥹
 */
#define EB_BASE   0x10000000

/*
 * EB�ܡ��ɤΥ꥽����
 */
#define EB_LED            (EB_BASE + 0x0008)

#define EB_SYS_LOCK       (EB_BASE + 0x0020)
#define EB_SYS_PLD_CTRL1  (EB_BASE + 0x0074)
#define EB_SYS_PLD_CTRL2  (EB_BASE + 0x0078)

#define EB_SYS_LOCK_LOCK   0x0000
#define EB_SYS_LOCK_UNLOCK 0xA05F

#define EB_SYS_PLD_CTRL1_INTMODE_MASK       0x01C00000
#define EB_SYS_PLD_CTRL1_INTMODE_LEGACY     0x00000000
#define EB_SYS_PLD_CTRL1_INTMODE_NEW_DCC    0x00400000
#define EB_SYS_PLD_CTRL1_INTMODE_NEW_NODCC  0x00800000
#define EB_SYS_PLD_CTRL1_INTMODE_EN_FIQ     0x01000000

/*
 * ������ֹ�
 */
#define DIC_IRQNO_UART0   36
#define DIC_IRQNO_UART1   37
#define DIC_IRQNO_UART2   44  /* DIC��ľ�� */
#define DIC_IRQNO_UART3   45  /* DIC��ľ�� */

#ifndef TOPPERS_MACRO_ONLY
/*
 * ����ߥ⡼�ɤν����
 */
Inline void
eb_init_int_mode(void)
{
	/* �����å� */
	sil_wrw_mem((void *)EB_SYS_LOCK, EB_SYS_LOCK_UNLOCK);
	sil_wrw_mem((void *)EB_SYS_PLD_CTRL1,
				(sil_rew_mem((void *)EB_SYS_PLD_CTRL1)
				 & (~EB_SYS_PLD_CTRL1_INTMODE_MASK))
				| (EB_SYS_PLD_CTRL1_INTMODE_NEW_NODCC));
	/* ��å� */
	sil_wrw_mem((void *)EB_SYS_LOCK, EB_SYS_LOCK_LOCK);
}
#endif /* TOPPERS_MACRO_ONLY */

/*
 * EB��¢�����޴�Ϣ
 */
#define TIMER01_BASE       (EB_BASE + 0x11000)

#define TIMER01_0_LOAD     (TIMER01_BASE + 0x00)
#define TIMER01_0_VALUE    (TIMER01_BASE + 0x04)
#define TIMER01_0_CTRL     (TIMER01_BASE + 0x08)
#define TIMER01_0_CLR      (TIMER01_BASE + 0x0C)

#define TIMER_CTRL_TIMER_EN     0x00000080
#define TIMER_CTRL_PERIODIC     0x00000040
#define TIMER_CTRL_INT_EN       0x00000020
#define TIMER_CTRL_PRESCALE_1   0x00000000
#define TIMER_CTRL_PRESCALE_16  0x00000004
#define TIMER_CTRL_PRESCALE_256 0x00000008
#define TIMER_CTRL_TIMESIZE_16  0x00000000
#define TIMER_CTRL_TIMESIZE_32  0x00000002
#define TIMER_CTRL_ONE_SHOT     0x00000001

/*
 * �����ƥॳ��ȥ���
 */
#define SYSTEM_CONTROLER (EB_BASE + 0x1000)
#define SYSTEM_CONTROLER_TIMER01_1MHZ   0x00008000 /* 1MHz�ǥ������ */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  EB��¢�����ޤν����
 */
extern void ebtimer_init(void);

/*
 *  EB��¢�����ޤθ����ͤ��ɽФ�
 */
Inline uint32_t
ebtimer_get_current(void)
{
	return (0xffffffff - sil_rew_mem((void *)TIMER01_0_VALUE));
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 * UART��Ϣ�����
 * �쥸����������� arm_primecell_uart.h �ǹԤäƤ���
 */
/* 
 * �١������ɥ쥹
 */
#define UART0_BASE  (EB_BASE + 0x9000)
#define UART1_BASE  (EB_BASE + 0xA000)
#define UART2_BASE  (EB_BASE + 0xB000)
#define UART3_BASE  (EB_BASE + 0xC000)

/*
 *  BPS����(38400bps)
 */ 
#define UART_IBRD_38400   0x27
#define UART_FBRD_38400   0x04

#ifndef TOPPERS_MACRO_ONLY
/*
 *  UART����Υݡ���󥰽���
 */
extern void ct11mpcore_putc(char_t c);

/*
 * �ݡ���󥰽��ϤΤ���ν����
 */
extern void ct11mpcore_uart_init(void);
#endif /* TOPPERS_MACRO_ONLY */

/*
 *  GIC������
 */
#define GIC1_BASE (EB_BASE + 0x40000)
#define GIC2_BASE (EB_BASE + 0x50000)

/*
 * CORE0 �� FIQ�ؤ�GIC2����³����Ƥ���
 */
#define GIC_BASE  GIC2_BASE

#define GIC_CPUIF_CCR   0x0000 /* CPU����ȥ���쥸����    */
#define GIC_CPUIF_PR    0x0004 /* ͥ���٥쥸����             */
#define GIC_CPUIF_BPR   0x0008 /* �Х��ʥ�ݥ���ȥ쥸����   */
#define GIC_CPUIF_ACK   0x000C /* �����Υ�å��쥸����       */
#define GIC_CPUIF_EOI   0x0010 /* End of Interrupt �쥸����  */
#define GIC_CPUIF_RPR   0x0014 /* Runnning priority �쥸���� */
#define GIC_CPUIF_PER   0x0016 /* Pending�쥸���� */

#define GIC_DIS_CR      0x1000 /* ����ȥ���쥸����   */
#define GIC_DIS_ESR     0x1100 /* ����ߥ��͡��֥륻�å� */
#define GIC_DIS_ECR     0x1180 /* ����ߥ��͡��֥륯�ꥢ */
#define GIC_DIS_PSR     0x1200 /* �ڥ�ǥ��󥰥��å�     */
#define GIC_DIS_PCR     0x1280 /* �ڥ�ǥ��󥰥��ꥢ     */
#define GIC_DIS_ACR     0x1300 /* �����ƥ��֥쥸����     */
#define GIC_DIS_PR      0x1400 /* ͥ���٥쥸����         */
#define GIC_DIS_TAR     0x1800 /* �������åȥ쥸����     */
#define GIC_DIS_CFGR    0x1C00 /* ����ե�����졼�����쥸���� */
#define GIC_DIS_SFT     0x1F00 /* ���եȥ��������󥿥�ץȥ쥸���� */

#define GIC_CPUIF_CCR_EN      0x0001 /* ͭ��     */
#define GIC_DIS_CFGR_EDGE     0x03   /* ���å������ */
#define GIC_DIS_CFGR_LEVEL    0x01   /* ��٥����� */

#define GIC_TMIN_INTNO   0U
#define GIC_TMAX_INTNO  95U
#define GIC_TNUM_INT    96U

#define GIC_IRQNO_TIMER01   36
#define GIC_IRQNO_UART0     44
#define GIC_IRQNO_UART1     45
#define GIC_IRQNO_UART2     46
#define GIC_IRQNO_UART3     47

#ifndef TOPPERS_MACRO_ONLY

/*
 * GIC CPU���󥿥ե�������Ϣ�Υɥ饤��
 */
/*
 * CPU�γ����ͥ���٥ޥ���������
 */ 
Inline void
gic_cpu_set_priority(int pri)
{
	sil_wrw_mem((void *)(GIC_BASE + GIC_CPUIF_PR), pri << 4);
}

/*
 * CPU�γ����ͥ���٥ޥ��������
 */ 
Inline int
gic_cpu_current_priority(void)
{
	return (sil_rew_mem((void *)(GIC_BASE + GIC_CPUIF_PR)) >> 4);    
}

/*
 * ����ߥϥ�ɥ�νи���ɬ�פ�IRC���
 */
Inline void
gic_cpu_end_int(uint8_t id)
{
	sil_wrw_mem((void *)(GIC_BASE + GIC_CPUIF_EOI), id);
}

/*
 * CPU���󥿥ե������ν����
 */
extern void gic_cpu_init(void);

/*
 * CPU���󥿥ե������ν�λ
 */
extern void gic_cpu_stop(void);


/*
 * GIC DIS���󥿥ե�������Ϣ�Υɥ饤��
 */

/*
 * ����߶ػ�
 */
extern void gic_dis_disable_int(uint8_t id);

/*
 * ����ߵ���
 */
extern void gic_dis_enable_int(uint8_t id);

/*
 * ����ߥڥ�ǥ��󥰥��ꥢ
 */
extern void gic_dis_clear_pending(uint8_t id);

/*
 * ����ߥڥ�ǥ��󥰥��å�
 */
extern void gic_dis_set_pending(uint8_t id);

/*
 * ������׵�Υ����å�
 */
extern bool_t gic_dis_probe_int(uint8_t id);

/*
 * ���������Υ��å�
 */
extern void gic_dis_config(uint8_t id, uint8_t config);

/*
 * �����ͥ���٤Υ��å�
 * ����ɽ�����Ϥ��� 
 */
extern void gic_dis_set_priority(uint8_t id, int pri);

/*
 * GIC���󥿥ե������ν����
 */
extern void gic_dis_init(void);

/*
 * GIC���󥿥ե������ν�λ
 */
extern void gic_dis_stop(void);


/*
 *  ��ȯ�Ķ���¸�ν���(T.B.D)
 */
Inline void
ct11mpcore_exit(void){
	while(1);
}

/*
 *  �ȥ졼�����˴ؤ������
 *  SCU���Ѥ��롥 
 */
#define TRACE_HW_INIT()   scu_counter_init()
#define TRACE_GET_TIM()   ((scu_counter_get_current() * 1000) / CT11MPCORE_CORE_CLK)

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  Character LCD ������
 */
#define CHARLCD_BASE    (EB_BASE + 0x8000)

#define CHARLCD_COM        (CHARLCD_BASE + 0x000)
#define CHARLCD_DAT        (CHARLCD_BASE + 0x004)
#define CHARLCD_RD         (CHARLCD_BASE + 0x008)
#define CHARLCD_RAW        (CHARLCD_BASE + 0x00C)
#define CHARLCD_MASK       (CHARLCD_BASE + 0x010)
#define CHARLCD_STAT       (CHARLCD_BASE + 0x014)


#define CHAR_LCDRS      1<<7
#define CHAR_LCDRnW     1<<6
#define CHAR_LCDE       1<<5
#define CHAR_LCDD4      1<<4
#define CHAR_LCDD5      1<<3
#define CHAR_LCDD6      1<<2
#define CHAR_LCDD7      1<<1

#define RAMSELECT       1
#define COMMAND         0

#define CLR_DISPLAY     1
#define    HOME            2
#define    ENTRY_MODE_SET  4
#define DISP_CTRL       8
#define    CUR_DIS_SHIFT   16
#define FUNC_SET        32
#define CGRAM_ADDR      64
#define DDRAM_ADDR      128

#define INC             2
#define DEC             0
#define COM_DIS_SHIFT   1
#define DISP_ON         4
#define CURS_ON         2
#define BLINK_ON        1
#define DISP_OFF        0
#define CURS_OFF        0
#define BLINK_OFF       0
#define DISP_SHIFT      8
#define CURS_SHIFT      0
#define SHIFT_RIGHT     4
#define SHIFT_LEFT      0
#define IF4BIT          0
#define IF8BIT          0x10
#define NUMLINES2       8
#define NUMLINES1       0
#define FONT5X10        4
#define FONT5X8         0
#define BUSYFLAG        0x80

#define CHAR_WRTIMEOUT  10          // Write time of 1mS max
#define CHAR_BSYTIMEOUT 50          // Busy time of 50mS max

#ifndef TOPPERS_MACRO_ONLY

/*
 * Character LCD �ν����
 */
extern void charlcd_init(void);

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_CT11MPCORE_EB_H */
