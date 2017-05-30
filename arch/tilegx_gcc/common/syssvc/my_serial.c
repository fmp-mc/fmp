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
 *  @(#) $Id: serial.c 898 2012-02-24 05:15:21Z ertl-honda $
 */

/*
 *		���ꥢ�륤�󥿥ե������ɥ饤��
 */

#include <kernel.h>
#include <t_syslog.h>
#include "target_syssvc.h"
#include "target_serial.h"
#include "syssvc/serial.h"
#include "kernel_cfg.h"

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Ф��ѿ����֤Υǥ��ե�������
 */
#ifndef SEC_SERIAL1
#define SEC_SERIAL1(type, variable) type variable
#endif /* SEC_SERIAL1 */

#ifndef SEC_SERIAL1_BEGIN
#define SEC_SERIAL1_BEGIN
#endif /* SEC_SERIAL1_BEGIN */

#ifndef SEC_SERIAL1_END
#define SEC_SERIAL1_END
#endif /* SEC_SERIAL1_END */

#ifndef SEC_SERIAL2
#define SEC_SERIAL2(type, variable) type variable
#endif /* SEC_SERIAL2 */

#ifndef SEC_SERIAL2_BEGIN
#define SEC_SERIAL2_BEGIN
#endif /* SEC_SERIAL2_BEGIN */

#ifndef SEC_SERIAL2_END
#define SEC_SERIAL2_END
#endif /* SEC_SERIAL2_END */

#ifndef SEC_SERIAL3
#define SEC_SERIAL3(type, variable) type variable
#endif /* SEC_SERIAL3 */

#ifndef SEC_SERIAL3_BEGIN
#define SEC_SERIAL3_BEGIN
#endif /* SEC_SERIAL3_BEGIN */

#ifndef SEC_SERIAL3_END
#define SEC_SERIAL3_END
#endif /* SEC_SERIAL3_END */

#ifndef SEC_SERIAL4
#define SEC_SERIAL4(type, variable) type variable
#endif /* SEC_SERIAL4 */

#ifndef SEC_SERIAL4_BEGIN
#define SEC_SERIAL4_BEGIN
#endif /* SEC_SERIAL4_BEGIN */

#ifndef SEC_SERIAL4_END
#define SEC_SERIAL4_END
#endif /* SEC_SERIAL4_END */

/*
 *  �Хåե��������Υǥե�����ͤȥХåե������
 */
#ifndef SERIAL_RCV_BUFSZ1
#define	SERIAL_RCV_BUFSZ1	256			/* �ݡ���1�μ����Хåե������� */
#endif /* SERIAL_RCV_BUFSZ1 */

#ifndef SERIAL_SND_BUFSZ1
#define	SERIAL_SND_BUFSZ1	256			/* �ݡ���1�������Хåե������� */
#endif /* SERIAL_SND_BUFSZ1 */

SEC_SERIAL1_BEGIN
SEC_SERIAL1(static char_t, rcv_buffer1[SERIAL_RCV_BUFSZ1]);
SEC_SERIAL1(static char_t, snd_buffer1[SERIAL_SND_BUFSZ1]);
SEC_SERIAL1_END

#if TNUM_PORT >= 2						/* �ݡ���2�˴ؤ������ */

#ifndef SERIAL_RCV_BUFSZ2
#define	SERIAL_RCV_BUFSZ2	256			/* �ݡ���2�μ����Хåե������� */
#endif /* SERIAL_RCV_BUFSZ2 */

#ifndef SERIAL_SND_BUFSZ2
#define	SERIAL_SND_BUFSZ2	256			/* �ݡ���2�������Хåե������� */
#endif /* SERIAL_SND_BUFSZ2 */

SEC_SERIAL2_BEGIN
SEC_SERIAL2(static char_t, rcv_buffer2[SERIAL_RCV_BUFSZ2]);
SEC_SERIAL2(static char_t, snd_buffer2[SERIAL_SND_BUFSZ2]);
SEC_SERIAL2_END

#endif /* TNUM_PORT >= 2 */

#if TNUM_PORT >= 3						/* �ݡ���3�˴ؤ������ */

#ifndef SERIAL_RCV_BUFSZ3
#define	SERIAL_RCV_BUFSZ3	256			/* �ݡ���3�μ����Хåե������� */
#endif /* SERIAL_RCV_BUFSZ3 */

#ifndef SERIAL_SND_BUFSZ3
#define	SERIAL_SND_BUFSZ3	256			/* �ݡ���3�������Хåե������� */
#endif /* SERIAL_SND_BUFSZ3 */

SEC_SERIAL3_BEGIN
SEC_SERIAL3(static char_t, rcv_buffer3[SERIAL_RCV_BUFSZ3]);
SEC_SERIAL3(static char_t, snd_buffer3[SERIAL_SND_BUFSZ3]);
SEC_SERIAL3_END

#endif /* TNUM_PORT >= 3 */

#if TNUM_PORT >= 4						/* �ݡ���4�˴ؤ������ */

#ifndef SERIAL_RCV_BUFSZ4
#define	SERIAL_RCV_BUFSZ4	256			/* �ݡ���4�μ����Хåե������� */
#endif /* SERIAL_RCV_BUFSZ4 */

#ifndef SERIAL_SND_BUFSZ4
#define	SERIAL_SND_BUFSZ4	256			/* �ݡ���4�������Хåե������� */
#endif /* SERIAL_SND_BUFSZ4 */

SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer4[SERIAL_RCV_BUFSZ4]);
SEC_SERIAL4(static char_t, snd_buffer4[SERIAL_SND_BUFSZ4]);
SEC_SERIAL4_END

#endif /* TNUM_PORT >= 4 */

#if 1 // Support up to 36 cores. -- ertl-liyixiao

/* TODO: Generated from following Python script.
for i in range(1, 37):
	print("""
#if TNUM_PORT >= %(prc)s
#define	SERIAL_RCV_BUFSZ%(prc)s 256
#define	SERIAL_SND_BUFSZ%(prc)s 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer%(prc)s[SERIAL_RCV_BUFSZ%(prc)s]);
SEC_SERIAL4(static char_t, snd_buffer%(prc)s[SERIAL_SND_BUFSZ%(prc)s]);
SEC_SERIAL4_END
#endif""" % {'prc':i})
*/

#if TNUM_PORT >= 5
#define	SERIAL_RCV_BUFSZ5 256
#define	SERIAL_SND_BUFSZ5 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer5[SERIAL_RCV_BUFSZ5]);
SEC_SERIAL4(static char_t, snd_buffer5[SERIAL_SND_BUFSZ5]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 6
#define	SERIAL_RCV_BUFSZ6 256
#define	SERIAL_SND_BUFSZ6 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer6[SERIAL_RCV_BUFSZ6]);
SEC_SERIAL4(static char_t, snd_buffer6[SERIAL_SND_BUFSZ6]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 7
#define	SERIAL_RCV_BUFSZ7 256
#define	SERIAL_SND_BUFSZ7 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer7[SERIAL_RCV_BUFSZ7]);
SEC_SERIAL4(static char_t, snd_buffer7[SERIAL_SND_BUFSZ7]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 8
#define	SERIAL_RCV_BUFSZ8 256
#define	SERIAL_SND_BUFSZ8 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer8[SERIAL_RCV_BUFSZ8]);
SEC_SERIAL4(static char_t, snd_buffer8[SERIAL_SND_BUFSZ8]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 9
#define	SERIAL_RCV_BUFSZ9 256
#define	SERIAL_SND_BUFSZ9 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer9[SERIAL_RCV_BUFSZ9]);
SEC_SERIAL4(static char_t, snd_buffer9[SERIAL_SND_BUFSZ9]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 10
#define	SERIAL_RCV_BUFSZ10 256
#define	SERIAL_SND_BUFSZ10 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer10[SERIAL_RCV_BUFSZ10]);
SEC_SERIAL4(static char_t, snd_buffer10[SERIAL_SND_BUFSZ10]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 11
#define	SERIAL_RCV_BUFSZ11 256
#define	SERIAL_SND_BUFSZ11 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer11[SERIAL_RCV_BUFSZ11]);
SEC_SERIAL4(static char_t, snd_buffer11[SERIAL_SND_BUFSZ11]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 12
#define	SERIAL_RCV_BUFSZ12 256
#define	SERIAL_SND_BUFSZ12 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer12[SERIAL_RCV_BUFSZ12]);
SEC_SERIAL4(static char_t, snd_buffer12[SERIAL_SND_BUFSZ12]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 13
#define	SERIAL_RCV_BUFSZ13 256
#define	SERIAL_SND_BUFSZ13 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer13[SERIAL_RCV_BUFSZ13]);
SEC_SERIAL4(static char_t, snd_buffer13[SERIAL_SND_BUFSZ13]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 14
#define	SERIAL_RCV_BUFSZ14 256
#define	SERIAL_SND_BUFSZ14 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer14[SERIAL_RCV_BUFSZ14]);
SEC_SERIAL4(static char_t, snd_buffer14[SERIAL_SND_BUFSZ14]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 15
#define	SERIAL_RCV_BUFSZ15 256
#define	SERIAL_SND_BUFSZ15 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer15[SERIAL_RCV_BUFSZ15]);
SEC_SERIAL4(static char_t, snd_buffer15[SERIAL_SND_BUFSZ15]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 16
#define	SERIAL_RCV_BUFSZ16 256
#define	SERIAL_SND_BUFSZ16 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer16[SERIAL_RCV_BUFSZ16]);
SEC_SERIAL4(static char_t, snd_buffer16[SERIAL_SND_BUFSZ16]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 17
#define	SERIAL_RCV_BUFSZ17 256
#define	SERIAL_SND_BUFSZ17 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer17[SERIAL_RCV_BUFSZ17]);
SEC_SERIAL4(static char_t, snd_buffer17[SERIAL_SND_BUFSZ17]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 18
#define	SERIAL_RCV_BUFSZ18 256
#define	SERIAL_SND_BUFSZ18 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer18[SERIAL_RCV_BUFSZ18]);
SEC_SERIAL4(static char_t, snd_buffer18[SERIAL_SND_BUFSZ18]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 19
#define	SERIAL_RCV_BUFSZ19 256
#define	SERIAL_SND_BUFSZ19 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer19[SERIAL_RCV_BUFSZ19]);
SEC_SERIAL4(static char_t, snd_buffer19[SERIAL_SND_BUFSZ19]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 20
#define	SERIAL_RCV_BUFSZ20 256
#define	SERIAL_SND_BUFSZ20 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer20[SERIAL_RCV_BUFSZ20]);
SEC_SERIAL4(static char_t, snd_buffer20[SERIAL_SND_BUFSZ20]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 21
#define	SERIAL_RCV_BUFSZ21 256
#define	SERIAL_SND_BUFSZ21 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer21[SERIAL_RCV_BUFSZ21]);
SEC_SERIAL4(static char_t, snd_buffer21[SERIAL_SND_BUFSZ21]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 22
#define	SERIAL_RCV_BUFSZ22 256
#define	SERIAL_SND_BUFSZ22 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer22[SERIAL_RCV_BUFSZ22]);
SEC_SERIAL4(static char_t, snd_buffer22[SERIAL_SND_BUFSZ22]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 23
#define	SERIAL_RCV_BUFSZ23 256
#define	SERIAL_SND_BUFSZ23 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer23[SERIAL_RCV_BUFSZ23]);
SEC_SERIAL4(static char_t, snd_buffer23[SERIAL_SND_BUFSZ23]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 24
#define	SERIAL_RCV_BUFSZ24 256
#define	SERIAL_SND_BUFSZ24 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer24[SERIAL_RCV_BUFSZ24]);
SEC_SERIAL4(static char_t, snd_buffer24[SERIAL_SND_BUFSZ24]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 25
#define	SERIAL_RCV_BUFSZ25 256
#define	SERIAL_SND_BUFSZ25 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer25[SERIAL_RCV_BUFSZ25]);
SEC_SERIAL4(static char_t, snd_buffer25[SERIAL_SND_BUFSZ25]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 26
#define	SERIAL_RCV_BUFSZ26 256
#define	SERIAL_SND_BUFSZ26 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer26[SERIAL_RCV_BUFSZ26]);
SEC_SERIAL4(static char_t, snd_buffer26[SERIAL_SND_BUFSZ26]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 27
#define	SERIAL_RCV_BUFSZ27 256
#define	SERIAL_SND_BUFSZ27 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer27[SERIAL_RCV_BUFSZ27]);
SEC_SERIAL4(static char_t, snd_buffer27[SERIAL_SND_BUFSZ27]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 28
#define	SERIAL_RCV_BUFSZ28 256
#define	SERIAL_SND_BUFSZ28 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer28[SERIAL_RCV_BUFSZ28]);
SEC_SERIAL4(static char_t, snd_buffer28[SERIAL_SND_BUFSZ28]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 29
#define	SERIAL_RCV_BUFSZ29 256
#define	SERIAL_SND_BUFSZ29 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer29[SERIAL_RCV_BUFSZ29]);
SEC_SERIAL4(static char_t, snd_buffer29[SERIAL_SND_BUFSZ29]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 30
#define	SERIAL_RCV_BUFSZ30 256
#define	SERIAL_SND_BUFSZ30 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer30[SERIAL_RCV_BUFSZ30]);
SEC_SERIAL4(static char_t, snd_buffer30[SERIAL_SND_BUFSZ30]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 31
#define	SERIAL_RCV_BUFSZ31 256
#define	SERIAL_SND_BUFSZ31 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer31[SERIAL_RCV_BUFSZ31]);
SEC_SERIAL4(static char_t, snd_buffer31[SERIAL_SND_BUFSZ31]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 32
#define	SERIAL_RCV_BUFSZ32 256
#define	SERIAL_SND_BUFSZ32 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer32[SERIAL_RCV_BUFSZ32]);
SEC_SERIAL4(static char_t, snd_buffer32[SERIAL_SND_BUFSZ32]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 33
#define	SERIAL_RCV_BUFSZ33 256
#define	SERIAL_SND_BUFSZ33 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer33[SERIAL_RCV_BUFSZ33]);
SEC_SERIAL4(static char_t, snd_buffer33[SERIAL_SND_BUFSZ33]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 34
#define	SERIAL_RCV_BUFSZ34 256
#define	SERIAL_SND_BUFSZ34 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer34[SERIAL_RCV_BUFSZ34]);
SEC_SERIAL4(static char_t, snd_buffer34[SERIAL_SND_BUFSZ34]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 35
#define	SERIAL_RCV_BUFSZ35 256
#define	SERIAL_SND_BUFSZ35 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer35[SERIAL_RCV_BUFSZ35]);
SEC_SERIAL4(static char_t, snd_buffer35[SERIAL_SND_BUFSZ35]);
SEC_SERIAL4_END
#endif

#if TNUM_PORT >= 36
#define	SERIAL_RCV_BUFSZ36 256
#define	SERIAL_SND_BUFSZ36 256
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static char_t, rcv_buffer36[SERIAL_RCV_BUFSZ36]);
SEC_SERIAL4(static char_t, snd_buffer36[SERIAL_SND_BUFSZ36]);
SEC_SERIAL4_END
#endif

#if !defined(G_SYSLOG) && TNUM_PRCID > 36
#error Number of processor cores exceeds limit (36).
#endif

#else

#if TNUM_PRCID >= 5
#error Serial driver Not Support more than 5 processor!
#endif /* TNUM_PRCID >= 5 */

#endif

/*
 *  ��λ�����κݤ��������Ԥĺ�����֡�msecñ�̡�
 */
#ifndef SERIAL_MAX_FLUSH_WAIT
#define SERIAL_MAX_FLUSH_WAIT	1000
#endif /* SERIAL_MAX_FLUSH_WAIT */

/*
 *  �ե�����˴�Ϣ��������ȥޥ���
 */
#define	FC_STOP			'\023'		/* ����ȥ���-S */
#define	FC_START		'\021'		/* ����ȥ���-Q */

#define BUFCNT_STOP(bufsz)		((bufsz) * 3 / 4)	/* STOP��������ʸ���� */
#define BUFCNT_START(bufsz)		((bufsz) / 2)		/* START��������ʸ���� */

/*
 *  ���ꥢ��ݡ��Ƚ�����֥�å�
 */
typedef struct serial_port_initialization_block {
	ID		rcv_semid;		/* �����Хåե������ѥ��ޥե���ID */
	ID		snd_semid;		/* �����Хåե������ѥ��ޥե���ID */
	uint_t	rcv_bufsz;		/* �����Хåե������� */
	char_t	*rcv_buffer;	/* �����Хåե� */
	uint_t	snd_bufsz;		/* �����Хåե������� */
	char_t	*snd_buffer;	/* �����Хåե� */
} SPINIB;

static const SPINIB spinib_table[TNUM_PORT] = {
	{ SERIAL_RCV_SEM1, SERIAL_SND_SEM1,
	  SERIAL_RCV_BUFSZ1, rcv_buffer1,
	  SERIAL_SND_BUFSZ1, snd_buffer1 },
#if TNUM_PORT >= 2
	{ SERIAL_RCV_SEM2, SERIAL_SND_SEM2,
	  SERIAL_RCV_BUFSZ2, rcv_buffer2,
	  SERIAL_SND_BUFSZ2, snd_buffer2 },
#endif /* TNUM_PORT >= 2 */
#if TNUM_PORT >= 3
	{ SERIAL_RCV_SEM3, SERIAL_SND_SEM3,
	  SERIAL_RCV_BUFSZ3, rcv_buffer3,
	  SERIAL_SND_BUFSZ3, snd_buffer3 },
#endif /* TNUM_PORT >= 3 */
#if TNUM_PORT >= 4
	{ SERIAL_RCV_SEM4, SERIAL_SND_SEM4,
	  SERIAL_RCV_BUFSZ4, rcv_buffer4,
	  SERIAL_SND_BUFSZ4, snd_buffer4 },
#endif /* TNUM_PORT >= 4 */
#if 1 // Support up to 36 cores. -- ertl-liyixiao
/* TODO: Generated from following Python script.
for i in range(1, 37):
	print("""#if TNUM_PORT >= %(prc)s
	{ SERIAL_RCV_SEM%(prc)s, SERIAL_SND_SEM%(prc)s,
	  SERIAL_RCV_BUFSZ%(prc)s, rcv_buffer%(prc)s,
	  SERIAL_SND_BUFSZ%(prc)s, snd_buffer%(prc)s },
#endif""" % {'prc':i})
*/
#if TNUM_PORT >= 5
	{ SERIAL_RCV_SEM5, SERIAL_SND_SEM5,
	  SERIAL_RCV_BUFSZ5, rcv_buffer5,
	  SERIAL_SND_BUFSZ5, snd_buffer5 },
#endif
#if TNUM_PORT >= 6
	{ SERIAL_RCV_SEM6, SERIAL_SND_SEM6,
	  SERIAL_RCV_BUFSZ6, rcv_buffer6,
	  SERIAL_SND_BUFSZ6, snd_buffer6 },
#endif
#if TNUM_PORT >= 7
	{ SERIAL_RCV_SEM7, SERIAL_SND_SEM7,
	  SERIAL_RCV_BUFSZ7, rcv_buffer7,
	  SERIAL_SND_BUFSZ7, snd_buffer7 },
#endif
#if TNUM_PORT >= 8
	{ SERIAL_RCV_SEM8, SERIAL_SND_SEM8,
	  SERIAL_RCV_BUFSZ8, rcv_buffer8,
	  SERIAL_SND_BUFSZ8, snd_buffer8 },
#endif
#if TNUM_PORT >= 9
	{ SERIAL_RCV_SEM9, SERIAL_SND_SEM9,
	  SERIAL_RCV_BUFSZ9, rcv_buffer9,
	  SERIAL_SND_BUFSZ9, snd_buffer9 },
#endif
#if TNUM_PORT >= 10
	{ SERIAL_RCV_SEM10, SERIAL_SND_SEM10,
	  SERIAL_RCV_BUFSZ10, rcv_buffer10,
	  SERIAL_SND_BUFSZ10, snd_buffer10 },
#endif
#if TNUM_PORT >= 11
	{ SERIAL_RCV_SEM11, SERIAL_SND_SEM11,
	  SERIAL_RCV_BUFSZ11, rcv_buffer11,
	  SERIAL_SND_BUFSZ11, snd_buffer11 },
#endif
#if TNUM_PORT >= 12
	{ SERIAL_RCV_SEM12, SERIAL_SND_SEM12,
	  SERIAL_RCV_BUFSZ12, rcv_buffer12,
	  SERIAL_SND_BUFSZ12, snd_buffer12 },
#endif
#if TNUM_PORT >= 13
	{ SERIAL_RCV_SEM13, SERIAL_SND_SEM13,
	  SERIAL_RCV_BUFSZ13, rcv_buffer13,
	  SERIAL_SND_BUFSZ13, snd_buffer13 },
#endif
#if TNUM_PORT >= 14
	{ SERIAL_RCV_SEM14, SERIAL_SND_SEM14,
	  SERIAL_RCV_BUFSZ14, rcv_buffer14,
	  SERIAL_SND_BUFSZ14, snd_buffer14 },
#endif
#if TNUM_PORT >= 15
	{ SERIAL_RCV_SEM15, SERIAL_SND_SEM15,
	  SERIAL_RCV_BUFSZ15, rcv_buffer15,
	  SERIAL_SND_BUFSZ15, snd_buffer15 },
#endif
#if TNUM_PORT >= 16
	{ SERIAL_RCV_SEM16, SERIAL_SND_SEM16,
	  SERIAL_RCV_BUFSZ16, rcv_buffer16,
	  SERIAL_SND_BUFSZ16, snd_buffer16 },
#endif
#if TNUM_PORT >= 17
	{ SERIAL_RCV_SEM17, SERIAL_SND_SEM17,
	  SERIAL_RCV_BUFSZ17, rcv_buffer17,
	  SERIAL_SND_BUFSZ17, snd_buffer17 },
#endif
#if TNUM_PORT >= 18
	{ SERIAL_RCV_SEM18, SERIAL_SND_SEM18,
	  SERIAL_RCV_BUFSZ18, rcv_buffer18,
	  SERIAL_SND_BUFSZ18, snd_buffer18 },
#endif
#if TNUM_PORT >= 19
	{ SERIAL_RCV_SEM19, SERIAL_SND_SEM19,
	  SERIAL_RCV_BUFSZ19, rcv_buffer19,
	  SERIAL_SND_BUFSZ19, snd_buffer19 },
#endif
#if TNUM_PORT >= 20
	{ SERIAL_RCV_SEM20, SERIAL_SND_SEM20,
	  SERIAL_RCV_BUFSZ20, rcv_buffer20,
	  SERIAL_SND_BUFSZ20, snd_buffer20 },
#endif
#if TNUM_PORT >= 21
	{ SERIAL_RCV_SEM21, SERIAL_SND_SEM21,
	  SERIAL_RCV_BUFSZ21, rcv_buffer21,
	  SERIAL_SND_BUFSZ21, snd_buffer21 },
#endif
#if TNUM_PORT >= 22
	{ SERIAL_RCV_SEM22, SERIAL_SND_SEM22,
	  SERIAL_RCV_BUFSZ22, rcv_buffer22,
	  SERIAL_SND_BUFSZ22, snd_buffer22 },
#endif
#if TNUM_PORT >= 23
	{ SERIAL_RCV_SEM23, SERIAL_SND_SEM23,
	  SERIAL_RCV_BUFSZ23, rcv_buffer23,
	  SERIAL_SND_BUFSZ23, snd_buffer23 },
#endif
#if TNUM_PORT >= 24
	{ SERIAL_RCV_SEM24, SERIAL_SND_SEM24,
	  SERIAL_RCV_BUFSZ24, rcv_buffer24,
	  SERIAL_SND_BUFSZ24, snd_buffer24 },
#endif
#if TNUM_PORT >= 25
	{ SERIAL_RCV_SEM25, SERIAL_SND_SEM25,
	  SERIAL_RCV_BUFSZ25, rcv_buffer25,
	  SERIAL_SND_BUFSZ25, snd_buffer25 },
#endif
#if TNUM_PORT >= 26
	{ SERIAL_RCV_SEM26, SERIAL_SND_SEM26,
	  SERIAL_RCV_BUFSZ26, rcv_buffer26,
	  SERIAL_SND_BUFSZ26, snd_buffer26 },
#endif
#if TNUM_PORT >= 27
	{ SERIAL_RCV_SEM27, SERIAL_SND_SEM27,
	  SERIAL_RCV_BUFSZ27, rcv_buffer27,
	  SERIAL_SND_BUFSZ27, snd_buffer27 },
#endif
#if TNUM_PORT >= 28
	{ SERIAL_RCV_SEM28, SERIAL_SND_SEM28,
	  SERIAL_RCV_BUFSZ28, rcv_buffer28,
	  SERIAL_SND_BUFSZ28, snd_buffer28 },
#endif
#if TNUM_PORT >= 29
	{ SERIAL_RCV_SEM29, SERIAL_SND_SEM29,
	  SERIAL_RCV_BUFSZ29, rcv_buffer29,
	  SERIAL_SND_BUFSZ29, snd_buffer29 },
#endif
#if TNUM_PORT >= 30
	{ SERIAL_RCV_SEM30, SERIAL_SND_SEM30,
	  SERIAL_RCV_BUFSZ30, rcv_buffer30,
	  SERIAL_SND_BUFSZ30, snd_buffer30 },
#endif
#if TNUM_PORT >= 31
	{ SERIAL_RCV_SEM31, SERIAL_SND_SEM31,
	  SERIAL_RCV_BUFSZ31, rcv_buffer31,
	  SERIAL_SND_BUFSZ31, snd_buffer31 },
#endif
#if TNUM_PORT >= 32
	{ SERIAL_RCV_SEM32, SERIAL_SND_SEM32,
	  SERIAL_RCV_BUFSZ32, rcv_buffer32,
	  SERIAL_SND_BUFSZ32, snd_buffer32 },
#endif
#if TNUM_PORT >= 33
	{ SERIAL_RCV_SEM33, SERIAL_SND_SEM33,
	  SERIAL_RCV_BUFSZ33, rcv_buffer33,
	  SERIAL_SND_BUFSZ33, snd_buffer33 },
#endif
#if TNUM_PORT >= 34
	{ SERIAL_RCV_SEM34, SERIAL_SND_SEM34,
	  SERIAL_RCV_BUFSZ34, rcv_buffer34,
	  SERIAL_SND_BUFSZ34, snd_buffer34 },
#endif
#if TNUM_PORT >= 35
	{ SERIAL_RCV_SEM35, SERIAL_SND_SEM35,
	  SERIAL_RCV_BUFSZ35, rcv_buffer35,
	  SERIAL_SND_BUFSZ35, snd_buffer35 },
#endif
#if TNUM_PORT >= 36
	{ SERIAL_RCV_SEM36, SERIAL_SND_SEM36,
	  SERIAL_RCV_BUFSZ36, rcv_buffer36,
	  SERIAL_SND_BUFSZ36, snd_buffer36 },
#endif
#endif
};

/*
 *  ���ꥢ��ݡ��ȴ����֥�å�
 */
typedef struct serial_port_control_block {
	const SPINIB *p_spinib;		/* ���ꥢ��ݡ��Ƚ�����֥�å� */
	SIOPCB	*p_siopcb;			/* ���ꥢ��I/O�ݡ��ȴ����֥�å� */
	bool_t	openflag;			/* �����ץ�Ѥߥե饰 */
	bool_t	errorflag;			/* ���顼�ե饰 */
	uint_t	ioctl;				/* ư������������� */

	uint_t	rcv_read_ptr;		/* �����Хåե��ɽФ��ݥ��� */
	uint_t	rcv_write_ptr;		/* �����Хåե�����ߥݥ��� */
	uint_t	rcv_count;			/* �����Хåե����ʸ���� */
	char_t	rcv_fc_chr;			/* ����٤�START/STOP */
	bool_t	rcv_stopped;		/* STOP�����ä����֤��� */

	uint_t	snd_read_ptr;		/* �����Хåե��ɽФ��ݥ��� */
	uint_t	snd_write_ptr;		/* �����Хåե�����ߥݥ��� */
	uint_t	snd_count;			/* �����Хåե����ʸ���� */
	bool_t	snd_stopped;		/* STOP�������ä����֤��� */
} SPCB;

SEC_SERIAL1_BEGIN
SEC_SERIAL1(static SPCB, spcb1);
SEC_SERIAL1_END

#if TNUM_PORT >= 2
SEC_SERIAL2_BEGIN
SEC_SERIAL2(static SPCB, spcb2);
SEC_SERIAL2_END
#endif /* TNUM_PORT >= 2 */

#if TNUM_PORT >= 3
SEC_SERIAL3_BEGIN
SEC_SERIAL3(static SPCB, spcb3);
SEC_SERIAL3_END
#endif /* TNUM_PORT >= 3 */

#if TNUM_PORT >= 4
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb4);
SEC_SERIAL4_END
#endif /* TNUM_PORT >= 4 */

#if 1 // Support up to 36 cores. -- ertl-liyixiao
/* TODO: Generated from following Python script.
for i in range(1, 37):
	print("""#if TNUM_PORT >= %(prc)s
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb%(prc)s);
SEC_SERIAL4_END
#endif""" % {'prc':i})
*/
#if TNUM_PORT >= 5
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb5);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 6
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb6);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 7
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb7);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 8
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb8);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 9
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb9);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 10
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb10);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 11
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb11);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 12
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb12);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 13
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb13);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 14
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb14);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 15
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb15);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 16
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb16);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 17
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb17);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 18
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb18);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 19
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb19);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 20
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb20);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 21
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb21);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 22
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb22);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 23
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb23);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 24
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb24);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 25
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb25);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 26
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb26);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 27
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb27);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 28
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb28);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 29
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb29);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 30
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb30);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 31
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb31);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 32
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb32);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 33
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb33);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 34
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb34);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 35
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb35);
SEC_SERIAL4_END
#endif
#if TNUM_PORT >= 36
SEC_SERIAL4_BEGIN
SEC_SERIAL4(static SPCB, spcb36);
SEC_SERIAL4_END
#endif
#endif

static SPCB* const	p_spcb_table[TNUM_PORT] = {
	&spcb1
#if TNUM_PORT >= 2
	,&spcb2
#endif /* TNUM_PORT >= 2 */
#if TNUM_PORT >= 3
	,&spcb3
#endif /* TNUM_PORT >= 3 */
#if TNUM_PORT >= 4
	,&spcb4
#endif /* TNUM_PORT >= 4 */
#if 1 // Support up to 36 cores. -- ertl-liyixiao
/* TODO: Generated from following Python script.
for i in range(1, 37):
	print("""#if TNUM_PORT >= %(prc)s
	,&spcb%(prc)s
#endif""" % {'prc':i})
*/
#if TNUM_PORT >= 5
	,&spcb5
#endif
#if TNUM_PORT >= 6
	,&spcb6
#endif
#if TNUM_PORT >= 7
	,&spcb7
#endif
#if TNUM_PORT >= 8
	,&spcb8
#endif
#if TNUM_PORT >= 9
	,&spcb9
#endif
#if TNUM_PORT >= 10
	,&spcb10
#endif
#if TNUM_PORT >= 11
	,&spcb11
#endif
#if TNUM_PORT >= 12
	,&spcb12
#endif
#if TNUM_PORT >= 13
	,&spcb13
#endif
#if TNUM_PORT >= 14
	,&spcb14
#endif
#if TNUM_PORT >= 15
	,&spcb15
#endif
#if TNUM_PORT >= 16
	,&spcb16
#endif
#if TNUM_PORT >= 17
	,&spcb17
#endif
#if TNUM_PORT >= 18
	,&spcb18
#endif
#if TNUM_PORT >= 19
	,&spcb19
#endif
#if TNUM_PORT >= 20
	,&spcb20
#endif
#if TNUM_PORT >= 21
	,&spcb21
#endif
#if TNUM_PORT >= 22
	,&spcb22
#endif
#if TNUM_PORT >= 23
	,&spcb23
#endif
#if TNUM_PORT >= 24
	,&spcb24
#endif
#if TNUM_PORT >= 25
	,&spcb25
#endif
#if TNUM_PORT >= 26
	,&spcb26
#endif
#if TNUM_PORT >= 27
	,&spcb27
#endif
#if TNUM_PORT >= 28
	,&spcb28
#endif
#if TNUM_PORT >= 29
	,&spcb29
#endif
#if TNUM_PORT >= 30
	,&spcb30
#endif
#if TNUM_PORT >= 31
	,&spcb31
#endif
#if TNUM_PORT >= 32
	,&spcb32
#endif
#if TNUM_PORT >= 33
	,&spcb33
#endif
#if TNUM_PORT >= 34
	,&spcb34
#endif
#if TNUM_PORT >= 35
	,&spcb35
#endif
#if TNUM_PORT >= 36
	,&spcb36
#endif
#endif
};

/*
 *  ���ꥢ��ݡ���ID���饷�ꥢ��ݡ��ȴ����֥�å�����Ф�����Υޥ���
 */
#define INDEX_PORT(portid)	((uint_t)((portid) - 1))
#define get_spcb(portid)	(p_spcb_table[INDEX_PORT(portid)])

/*
 *  �ݥ��󥿤Υ��󥯥����
 */
#define INC_PTR(ptr, bufsz)		do {					\
	if (++(ptr) == (bufsz)) { (ptr) = 0; }				\
} while(false)

/*
 *  �����ӥ�������ƽФ��ޥ���
 *
 *  �����ӥ�������ƽФ���ޤ༰exp��ɾ���������ͤ����顼������͡ˤξ�
 *  ��ˤϡ�erc��ercd_exp��ɾ�������ͤ���������error_exit��goto���롥
 */
#define SVC(exp, ercd_exp) \
				{ if ((exp) < 0) { ercd = (ercd_exp); goto error_exit; }}

/*
 *  E_SYS���顼������
 */
static ER
gen_ercd_sys(SPCB *p_spcb)
{
	p_spcb->errorflag = true;
	return(E_SYS);
}

/*
 *  �Ԥ������륵���ӥ������뤫��Υ��顼���Ѵ�
 */
static ER
gen_ercd_wait(ER rercd, SPCB *p_spcb)
{
	switch (MERCD(rercd)) {
	case E_RLWAI:
	case E_DLT:
		return(rercd);
	default:
		p_spcb->errorflag = true;
		return(E_SYS);
	}
}

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фν�����롼����
 */
void
serial_initialize(intptr_t exinf)
{
	uint_t	i = (uint_t)exinf;

	(p_spcb_table[i])->p_spinib = &(spinib_table[i]);
	(p_spcb_table[i])->openflag = false;
}

/*
 *  ���ꥢ��ݡ��ȤΥ����ץ�ʥ����ӥ��������
 */
ER
serial_opn_por(ID portid)
{
	SPCB	*p_spcb;
	ER		ercd;

	if (sns_dpn()) {				/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �ݡ����ֹ�Υ����å� */
	}
	p_spcb = get_spcb(portid);

	SVC(dis_dsp(), gen_ercd_sys(p_spcb));
	if (p_spcb->openflag) {			/* �����ץ�Ѥߤ��Υ����å� */
		ercd = E_OBJ;
	}
	else {
		/*
		 *  �ѿ��ν����
		 */
		p_spcb->ioctl = (IOCTL_ECHO | IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV);

		p_spcb->rcv_read_ptr = p_spcb->rcv_write_ptr = 0U;
		p_spcb->rcv_count = 0U;
		p_spcb->rcv_fc_chr = '\0';
		p_spcb->rcv_stopped = false;

		p_spcb->snd_read_ptr = p_spcb->snd_write_ptr = 0U;
		p_spcb->snd_count = 0U;
		p_spcb->snd_stopped = false;

		/*
		 *  ����ʹߡ�����ߤ�ػߤ��롥
		 */
		if (loc_cpu() < 0) {
			ercd = E_SYS;
			goto error_exit_enadsp;
		}

		/*
		 *  �ϡ��ɥ�������¸�Υ����ץ����
		 */
		p_spcb->p_siopcb = sio_opn_por(portid, (intptr_t) p_spcb);

		/*
		 *  �������Υ�����Хå�����Ĥ��롥
		 */
		sio_ena_cbr(p_spcb->p_siopcb, SIO_RDY_RCV);
		p_spcb->openflag = true;
		p_spcb->errorflag = false;

		if (unl_cpu() < 0) {
			p_spcb->errorflag = true;
			ercd = E_SYS;
			goto error_exit_enadsp;
		}
		ercd = E_OK;
	}

  error_exit_enadsp:
	SVC(ena_dsp(), gen_ercd_sys(p_spcb));

  error_exit:
	return(ercd);
}

/*
 *  ���ꥢ��ݡ��ȤΥ������ʥ����ӥ��������
 */
ER
serial_cls_por(ID portid)
{
	SPCB	*p_spcb;
	ER		ercd;
	bool_t	eflag = false;

	if (sns_dpn()) {				/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �ݡ����ֹ�Υ����å� */
	}
	p_spcb = get_spcb(portid);

	SVC(dis_dsp(), gen_ercd_sys(p_spcb));
	if (!(p_spcb->openflag)) {		/* �����ץ�Ѥߤ��Υ����å� */
		ercd = E_OBJ;
	}
	else {
		/*
		 *  �ϡ��ɥ�������¸�Υ���������
		 */
		if (loc_cpu() < 0) {
			eflag = true;
		}
		sio_cls_por(p_spcb->p_siopcb);
		p_spcb->openflag = false;
		if (unl_cpu() < 0) {
			eflag = true;
		}

		/*
		 *  ���ޥե��ν����
		 */
		if (ini_sem(p_spcb->p_spinib->snd_semid) < 0) {
			eflag = true;
		}
		if (ini_sem(p_spcb->p_spinib->rcv_semid) < 0) {
			eflag = true;
		}

		/*
		 *  ���顼�����ɤ�����
		 */
		if (eflag) {
			ercd = gen_ercd_sys(p_spcb);
		}
		else {
			ercd = E_OK;
		}
	}
	SVC(ena_dsp(), gen_ercd_sys(p_spcb));

  error_exit:
	return(ercd);
}

/*
 *  ���ꥢ��ݡ��Ȥؤ�ʸ������
 *
 *  p_spcb�ǻ��ꤵ��륷�ꥢ��I/O�ݡ��Ȥ��Ф��ơ�ʸ��c���������롥ʸ��
 *  �������쥸�����ˤ��줿���ˤ�true���֤��������Ǥʤ����ˤϡ�����
 *  �쥸���������������Ȥ����Τ��륳����Хå��ؿ�����Ĥ���false���֤���
 *  ���δؿ��ϡ�CPU��å����֤ǸƤӽФ���롥
 */
Inline bool_t
serial_snd_chr(SPCB *p_spcb, char_t c)
{
	if (sio_snd_chr(p_spcb->p_siopcb, c)) {
		return(true);
	}
	else {
		sio_ena_cbr(p_spcb->p_siopcb, SIO_RDY_SND);
		return(false);
	}
}

/*
 *  ���ꥢ��ݡ��Ȥؤ�1ʸ������
 */
static ER_BOOL
serial_wri_chr(SPCB *p_spcb, char_t c)
{
	bool_t	buffer_full;
	ER		ercd, rercd;

	/*
	 *  LF������CR���������롥
	 */
	if (c == '\n' && (p_spcb->ioctl & IOCTL_CRLF) != 0U) {
		SVC(rercd = serial_wri_chr(p_spcb, '\r'), rercd);
		if ((bool_t) rercd) {
			SVC(rercd = wai_sem(p_spcb->p_spinib->snd_semid),
										gen_ercd_wait(rercd, p_spcb));
		}
	}

	SVC(loc_cpu(), gen_ercd_sys(p_spcb));
	if (p_spcb->snd_count == 0U && !(p_spcb->snd_stopped)
								&& serial_snd_chr(p_spcb, c)) {
		/*
		 *  ���ꥢ��I/O�ǥХ����������쥸������ʸ��������뤳�Ȥ�������
		 *  ����硥
		 */
		buffer_full = false;
	}
	else {
		/*
		 *  �����Хåե���ʸ��������롥
		 */
		p_spcb->p_spinib->snd_buffer[p_spcb->snd_write_ptr] = c;
		INC_PTR(p_spcb->snd_write_ptr, p_spcb->p_spinib->snd_bufsz);
		p_spcb->snd_count++;
		buffer_full = (p_spcb->snd_count == p_spcb->p_spinib->snd_bufsz);
	}

	SVC(unl_cpu(), gen_ercd_sys(p_spcb));
	ercd = (ER_BOOL) buffer_full;

  error_exit:
	return(ercd);
}

/*
 *  ���ꥢ��ݡ��Ȥؤ�ʸ���������ʥ����ӥ��������
 */
ER_UINT
serial_wri_dat(ID portid, const char_t *buf, uint_t len)
{
	SPCB	*p_spcb;
	bool_t	buffer_full;
	uint_t	wricnt = 0U;
	ER		ercd, rercd;

	if (sns_dpn()) {				/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �ݡ����ֹ�Υ����å� */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* �����ץ�Ѥߤ��Υ����å� */
		return(E_OBJ);
	}
    if (p_spcb->errorflag) {		/* ���顼���֤��Υ����å� */
		return(E_SYS);
	}

	buffer_full = true;				/* �롼�פ�1����wai_sem���� */
	while (wricnt < len) {
		if (buffer_full) {
			SVC(rercd = wai_sem(p_spcb->p_spinib->snd_semid),
										gen_ercd_wait(rercd, p_spcb));
		}
		SVC(rercd = serial_wri_chr(p_spcb, *buf++), rercd);
		wricnt++;
		buffer_full = (bool_t) rercd;
	}
	if (!buffer_full) {
		SVC(sig_sem(p_spcb->p_spinib->snd_semid), gen_ercd_sys(p_spcb));
	}
	ercd = E_OK;

  error_exit:
	return(wricnt > 0U ? (ER_UINT) wricnt : ercd);
}

/*
 *  ���ꥢ��ݡ��Ȥ����1ʸ������
 */
static bool_t
serial_rea_chr(SPCB *p_spcb, char_t *p_c)
{
	bool_t	buffer_empty;
	ER		ercd;

	SVC(loc_cpu(), gen_ercd_sys(p_spcb));

	/*
	 *  �����Хåե�����ʸ������Ф���
	 */
	*p_c = p_spcb->p_spinib->rcv_buffer[p_spcb->rcv_read_ptr];
	INC_PTR(p_spcb->rcv_read_ptr, p_spcb->p_spinib->rcv_bufsz);
	p_spcb->rcv_count--;
	buffer_empty = (p_spcb->rcv_count == 0U);

	/*
	 *  START���������롥
	 */
	if (p_spcb->rcv_stopped && p_spcb->rcv_count
								<= BUFCNT_START(p_spcb->p_spinib->rcv_bufsz)) {
		if (!serial_snd_chr(p_spcb, FC_START)) {
			p_spcb->rcv_fc_chr = FC_START;
		}
		p_spcb->rcv_stopped = false;
	}

	SVC(unl_cpu(), gen_ercd_sys(p_spcb));
	ercd = (ER_BOOL) buffer_empty;

  error_exit:
	return(ercd);
}

/*
 *  ���ꥢ��ݡ��Ȥ����ʸ��������ʥ����ӥ��������
 */
ER_UINT
serial_rea_dat(ID portid, char_t *buf, uint_t len)
{
	SPCB	*p_spcb;
	bool_t	buffer_empty;
	uint_t	reacnt = 0U;
	char_t	c = '\0';		/* ����ѥ���ηٹ���޻ߤ��뤿��˽�������� */
	ER		ercd, rercd;

	if (sns_dpn()) {				/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �ݡ����ֹ�Υ����å� */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* �����ץ�Ѥߤ��Υ����å� */
		return(E_OBJ);
	}
	if (p_spcb->errorflag) {		/* ���顼���֤��Υ����å� */
		return(E_SYS);
	}

	buffer_empty = true;			/* �롼�פ�1����wai_sem���� */
	while (reacnt < len) {
		if (buffer_empty) {
			SVC(rercd = wai_sem(p_spcb->p_spinib->rcv_semid),
										gen_ercd_wait(rercd, p_spcb));
		}
		SVC(rercd = serial_rea_chr(p_spcb, &c), rercd);
		*buf++ = c;
		reacnt++;
		buffer_empty = (bool_t) rercd;

		/*
		 *  �������Хå�������
		 */
		if ((p_spcb->ioctl & IOCTL_ECHO) != 0U) {
			SVC(rercd = wai_sem(p_spcb->p_spinib->snd_semid),
										gen_ercd_wait(rercd, p_spcb));
			SVC(rercd = serial_wri_chr(p_spcb, c), rercd);
			if (!((bool_t) rercd)) {
				SVC(sig_sem(p_spcb->p_spinib->snd_semid),
										gen_ercd_sys(p_spcb));
			}
		}
	}
	if (!buffer_empty) {
		SVC(sig_sem(p_spcb->p_spinib->rcv_semid), gen_ercd_sys(p_spcb));
	}
	ercd = E_OK;

  error_exit:
	return(reacnt > 0U ? (ER_UINT) reacnt : ercd);
}

/*
 *  ���ꥢ��ݡ��Ȥ�����ʥ����ӥ��������
 */
ER
serial_ctl_por(ID portid, uint_t ioctl)
{
	SPCB	*p_spcb;

	if (sns_dpn()) {				/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �ݡ����ֹ�Υ����å� */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* �����ץ�Ѥߤ��Υ����å� */
		return(E_OBJ);
	}
	if (p_spcb->errorflag) {		/* ���顼���֤��Υ����å� */
		return(E_SYS);
	}

	p_spcb->ioctl = ioctl;
	return(E_OK);
}

/*
 *  ���ꥢ��ݡ��Ⱦ��֤λ��ȡʥ����ӥ��������
 */
ER
serial_ref_por(ID portid, T_SERIAL_RPOR *pk_rpor)
{
	SPCB	*p_spcb;

	if (sns_dpn()) {				/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �ݡ����ֹ�Υ����å� */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* �����ץ�Ѥߤ��Υ����å� */
		return(E_OBJ);
	}
	if (p_spcb->errorflag) {		/* ���顼���֤��Υ����å� */
		return(E_SYS);
	}

	pk_rpor->reacnt = p_spcb->rcv_count;
	pk_rpor->wricnt = p_spcb->snd_count;
	return(E_OK);
}

/*
 *  ���ꥢ��ݡ��Ȥ����������ǽ������Хå�
 */
void
sio_irdy_snd(intptr_t exinf)
{
	SPCB	*p_spcb;

	p_spcb = (SPCB *) exinf;
	if (p_spcb->rcv_fc_chr != '\0') {
		/*
		 *  START/STOP ���������롥
		 */
		(void) sio_snd_chr(p_spcb->p_siopcb, p_spcb->rcv_fc_chr);
		p_spcb->rcv_fc_chr = '\0';
	}
	else if (!(p_spcb->snd_stopped) && p_spcb->snd_count > 0U) {
		/*
		 *  �����Хåե��椫��ʸ������Ф����������롥
		 */
		(void) sio_snd_chr(p_spcb->p_siopcb,
					p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr]);
		INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
		if (p_spcb->snd_count == p_spcb->p_spinib->snd_bufsz) {
			if (isig_sem(p_spcb->p_spinib->snd_semid) < 0) {
				p_spcb->errorflag = true;
			}
		}
		p_spcb->snd_count--;
	}
	else {
		/*
		 *  �������٤�ʸ�����ʤ����ϡ�������ǽ������Хå���
		 *  �ػߤ��롥
		 */
		sio_dis_cbr(p_spcb->p_siopcb, SIO_RDY_SND);
	}
}

/*
 *  ���ꥢ��ݡ��Ȥ���μ������Υ�����Хå�
 */
void
sio_irdy_rcv(intptr_t exinf)
{
	SPCB	*p_spcb;
	char_t	c;

	p_spcb = (SPCB *) exinf;
	c = (char_t) sio_rcv_chr(p_spcb->p_siopcb);
	if ((p_spcb->ioctl & IOCTL_FCSND) != 0U && c == FC_STOP) {
		/*
		 *  ����������ߤ��롥�������ʸ���Ϥ��Τޤ��������롥
		 */
		p_spcb->snd_stopped = true;
	}
	else if (p_spcb->snd_stopped && (c == FC_START
				|| (p_spcb->ioctl & IOCTL_FCANY) != 0U)) {
		/*
		 *  ������Ƴ����롥
		 */
		p_spcb->snd_stopped = false;
		if (p_spcb->snd_count > 0U) {
			c = p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr];
			if (serial_snd_chr(p_spcb, c)) {
				INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
				if (p_spcb->snd_count == p_spcb->p_spinib->snd_bufsz) {
					if (isig_sem(p_spcb->p_spinib->snd_semid) < 0) {
						p_spcb->errorflag = true;
					}
				}
				p_spcb->snd_count--;
			}
		}
	}
	else if ((p_spcb->ioctl & IOCTL_FCSND) != 0U && c == FC_START) {
		/*
		 *  �������Ф��ƥե����椷�Ƥ����硤START �ϼΤƤ롥
		 */
	}
	else if (p_spcb->rcv_count == p_spcb->p_spinib->rcv_bufsz) {
		/*
		 *  �Хåե��ե�ξ�硤��������ʸ����ΤƤ롥
		 */
	}
	else {
		/*
		 *  ��������ʸ��������Хåե�������롥
		 */
		p_spcb->p_spinib->rcv_buffer[p_spcb->rcv_write_ptr] = c;
		INC_PTR(p_spcb->rcv_write_ptr, p_spcb->p_spinib->rcv_bufsz);
		if (p_spcb->rcv_count == 0U) {
			if (isig_sem(p_spcb->p_spinib->rcv_semid) < 0) {
				p_spcb->errorflag = true;
			}
		}
		p_spcb->rcv_count++;

		/*
		 *  STOP���������롥
		 */
		if ((p_spcb->ioctl & IOCTL_FCRCV) != 0U && !(p_spcb->rcv_stopped)
						&& p_spcb->rcv_count
							>= BUFCNT_STOP(p_spcb->p_spinib->rcv_bufsz)) {
			if (!serial_snd_chr(p_spcb, FC_STOP)) {
				p_spcb->rcv_fc_chr = FC_STOP;
			}
			p_spcb->rcv_stopped = true;
		}
	}
}

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Ф����̤����ʸ���μ�Ф�
 */
bool_t
serial_get_chr(ID portid, char_t *p_c)
{
	SPCB	*p_spcb;

	if (1 <= portid && portid <= TNUM_PORT) {	/* �ݡ����ֹ�Υ����å� */
		p_spcb = get_spcb(portid);
		if (p_spcb->openflag) {					/* �����ץ�Ѥߤ��Υ����å� */
			if (p_spcb->snd_count > 0U) {
				*p_c = p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr];
				INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
				p_spcb->snd_count--;
				return(true);
			}
		}
	}
	return(false);
}
