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
 *  @(#) $Id: target_serial.h 540 2010-02-17 10:48:07Z ertl-honda $
 */


/*
 *  ���ꥢ��I/O�ǥХ�����SIO�˥ɥ饤�С�SH7786_DEV�ѡ�
 */
#ifndef TOPPERS_TARGET_SERIAL_H
#define TOPPERS_TARGET_SERIAL_H

#include "sh7786_dev.h"
#include "pdic/sh/sh_scif.h"

/*
 *  SIO�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SIO_TX0     (0x00010000 | SCIF0_TXI_INTEVT)	/* ����ߥϥ�ɥ��ֹ� */
#define INTNO_SIO_TX0     (0x00000000 | SCIF0_TXI_INTEVT)	/* ������ֹ� */
#define INHNO_SIO_RX0     (0x00010000 | SCIF0_RXI_INTEVT)	/* ����ߥϥ�ɥ��ֹ� */
#define INTNO_SIO_RX0     (0x00000000 | SCIF0_RXI_INTEVT)	/* ������ֹ� */

#define INHNO_SIO_TX1     (0x00020000 | SCIF1_TXI_INTEVT)	/* ����ߥϥ�ɥ��ֹ� */
#define INTNO_SIO_TX1     (0x00000000 | SCIF1_TXI_INTEVT)	/* ������ֹ� */
#define INHNO_SIO_RX1     (0x00020000 | SCIF1_RXI_INTEVT)	/* ����ߥϥ�ɥ��ֹ� */
#define INTNO_SIO_RX1     (0x00000000 | SCIF1_RXI_INTEVT)	/* ������ֹ� */

#define INTPRI_SIO       (-4)             /* �����ͥ���� */
#define INTATR_SIO       0U               /* �����°�� */

#ifndef TOPPERS_MACRO_ONLY

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
extern void sio_tx_isr(intptr_t siopid);
extern void sio_rx_isr(intptr_t siopid);
extern void sio_scif1_isr(intptr_t siopid);

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
#endif /* TOPPERS_TARGET_SERIAL_H */
