/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007-2008 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: tmu.h 943 2012-10-19 07:50:40Z ertl-honda $
 */

/*
 *  �����ޥɥ饤�С�TMU�ѡ�
 */

#ifndef TOPPERS_TMU_H
#define TOPPERS_TMU_H

#include <sil.h>

/*
 *  �ƥ��������Ѥ��륿���ޤ��ֹ�ȳ�����ֹ�
 */
#define PRC1_TMU_NO  3
#define PRC2_TMU_NO  4
#define PRC3_TMU_NO  5
#define PRC4_TMU_NO  6

#define INTNO_TIMER_PRC1 IRQNO_TMU3
#define INTNO_TIMER_PRC2 IRQNO_TMU4
#define INTNO_TIMER_PRC3 IRQNO_TMU5
#define INTNO_TIMER_PRC4 IRQNO_TMU6

/*
 *  �����޳���ߥϥ�ɥ���Ͽ�Τ�������
 */
#define INHNO_TIMER_PRC1 (0x10000 | INTNO_TIMER_PRC1)
#define INHNO_TIMER_PRC2 (0x20000 | INTNO_TIMER_PRC2)
#define INHNO_TIMER_PRC3 (0x30000 | INTNO_TIMER_PRC3)
#define INHNO_TIMER_PRC4 (0x40000 | INTNO_TIMER_PRC4)


//#define INTPRI_TIMER   (-6)          /* �����ͥ���� */
#define INTATR_TIMER    0U           /* �����°�� */

/*
 *  �����Х륿���ޡ��ξ������
 */
#define INHNO_TIMER_SYSTIM (0x10000 | IRQNO_TMU3)
#define INTNO_TIMER_SYSTIM (0x10000 | IRQNO_TMU3)

/*
 *  �쥸�����Υӥå����
 */
#define TCR_UNF    UINT_C(0x0100)
#define TCR_UNIE   UINT_C(0x0020)

#ifndef TOPPERS_MACRO_ONLY

/*
 *  TMU������֥�å�
 */
typedef struct tmu_initialization_block {
	uint8_t *tstr_b;    /* �����ޥ������ȥ쥸���� */
	uint32_t *tcor_w;    /* �����ޥ��󥹥���ȥ쥸���� */
	uint32_t *tcnt_w;    /* �����ޥ����� */
	uint16_t *tcr_h;     /* �����ޥ���ȥ���쥸���� */
	uint8_t   tstr_bit;  /* �������ȥӥå� */
} TMUINIB;

/*
 *  TMU������֥�å�
 */
extern const TMUINIB tmuinib_table[];

/*
 *  �����ͥ륿���ޤ�ID�����ơ��֥�
 */
extern const uint32_t target_sys_clk_timer_id_table[];

/*
 *  �����ͥ륿���ޤγ�����ֹ�μ����ơ��֥�
 */
extern const uint32_t target_sys_clk_timer_intno_table[];

/*
 *  �������ͤ�����ɽ���η�
 */
typedef uint32_t    CLOCK;

/*
 *  �������ͤ�����ɽ���ȥߥ��á�����ñ�̤Ȥ��Ѵ�
 */
#define TIMER_CLOCK             TMU_TIMER_CLOCK
#define TO_CLOCK(nume, deno)    ((CLOCK)(TIMER_CLOCK * (nume) / (deno)))
#define TO_USEC(clock)          (((SYSUTM) clock) * 1000U / TIMER_CLOCK)

/*
 *  ����Ǥ������Υ����޼�����ñ�̤�����ɽ����
 */
#define MAX_CLOCK    ((CLOCK) 0xffffffffU)

/*
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 */
extern void target_timer_initialize(intptr_t exinf);

/*
 *  �����ޤ���߽���
 *
 *  �����ޤ�ư�����ߤ����롥
 */
extern void target_timer_terminate(intptr_t exinf);

/*
 *  �����ޤθ����ͤ��ɽФ�
 */
Inline CLOCK
target_timer_get_current(void)
{
	const TMUINIB *p_tmuinib = &tmuinib_table[target_sys_clk_timer_id_table[x_prc_index()]];
	return(TO_CLOCK(TIC_NUME, TIC_DENO) - sil_rew_mem((void*)(p_tmuinib->tcnt_w)));
}

/*
 *  �����޳�����׵�Υ����å�
 */
Inline bool_t
target_timer_probe_int(void)
{
	const TMUINIB *p_tmuinib = &tmuinib_table[target_sys_clk_timer_id_table[x_prc_index()]];
	return(sil_reh_mem((void*)(p_tmuinib->tcr_h)) & TCR_UNF);
}

/*
 *  �����޳���ߥϥ�ɥ�
 */
extern void target_timer_handler(void);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_TIMER_H */
