/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2008 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: jtag_uart.h 238 2009-04-28 08:26:25Z ertl-honda $
 */

/*
 * ���ꥢ��I/O�ǥХ�����SIO�˥ɥ饤�С�JTAG UART�ѡ�
 */

#ifndef TOPPERS_JTAG_UARTL_H
#define TOPPERS_JTAG_UARTL_H

#include <sil.h>

/*
 *  �ϡ��ɥ��������
 */
/*
 *  �쥸�������ե��å�
 */
#define JTAG_UART_DATA_OFFSET    0x00
#define JTAG_UART_CONTROL_OFFSET 0x04

/*
 *  �쥸�����ӥå����
 */
#define JTAG_UART_DATA_RVALID 0x8000
#define JTAG_UART_CONTROL_RIE 0x01
#define JTAG_UART_CONTROL_WIE 0x02
#define JTAG_UART_CONTROL_RIP 0x04
#define JTAG_UART_CONTROL_WIP 0x08
#define JTAG_UART_CONTROL_WSAPCE 0x0ffff0000

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �����ͥ�����٥�����Ѵؿ�(JTAG UART��)
 */
Inline void
jtag_uart_putc(uint32_t base, char_t c)
{
	while(!((sil_rew_iop((void*)(base + JTAG_UART_CONTROL_OFFSET)) & JTAG_UART_CONTROL_WSAPCE) > 0));
	sil_wrw_iop((void*)(base + JTAG_UART_DATA_OFFSET), c);
}

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
typedef struct sio_port_control_block SIOPCB;

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å������
 */
typedef struct sio_port_initialization_block 
{
	void*    ctrl;
	void*    data;
	uint32_t intno;
}SIOPINIB;

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å��Υ��ꥢ
 *  �������åȰ�¸�����  
 */
extern const SIOPINIB siopinib_table[];

/*
 *  ������Хå��롼����μ����ֹ�
 */
#define SIO_RDY_SND	1U		/* ������ǽ������Хå� */
#define SIO_RDY_RCV	2U		/* �������Υ�����Хå� */

/*
 *  SIO�ɥ饤�Фν����
 */
extern void sio_initialize(intptr_t exinf);

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
extern SIOPCB *sio_opn_por(ID siopid, intptr_t exinf);

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
extern void sio_cls_por(SIOPCB *p_siopcb);

/*
 *  SIO�γ���ߥϥ�ɥ�
 */
extern void sio_isr(intptr_t siopid);

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
extern bool_t sio_snd_chr(SIOPCB *siopcb, char_t c);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
extern int_t sio_rcv_chr(SIOPCB *siopcb);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
extern void sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
extern void sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����������ǽ������Хå�
 */
extern void sio_irdy_snd(intptr_t exinf);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���μ������Υ�����Хå�
 */
extern void sio_irdy_rcv(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_JTAG_UARTL_H */
