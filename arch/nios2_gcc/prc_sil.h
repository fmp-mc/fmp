/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2008-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_sil.h 843 2011-07-15 03:17:19Z ertl-honda $
 */

/*
 *  sil.h�Υץ��å���¸����Nios2�ѡ�
 */

#ifndef TOPPERS_PRC_SIL_H
#define TOPPERS_PRC_SIL_H

/*
 *  �ץ��å��Υ���ǥ�����
 */
#define SIL_ENDIAN_LITTLE

#ifndef TOPPERS_MACRO_ONLY

/*
 *  NMI��������٤Ƥγ���ߤζػ�
 */
Inline uint8_t
TOPPERS_disint(void)
{
	uint32_t  TOPPERS_status;

	Asm("rdctl %0, status" : "=r" (TOPPERS_status));
	Asm("wrctl status, %0" :: "r" (TOPPERS_status & ~(0x0001)) : "memory");
    return((uint8_t)(TOPPERS_status & (0x0001)));
}

/*
 *  �����ͥ���٥ޥ���������ɽ���ˤθ����ͤ�����
 */
Inline void
TOPPERS_set_pie(uint8_t TOPPERS_pie_bit)
{
	uint32_t  TOPPERS_status;

	Asm("rdctl %0, status" : "=r" (TOPPERS_status));
	TOPPERS_status = TOPPERS_status & ~(0x0001);
	TOPPERS_status = TOPPERS_status | (TOPPERS_pie_bit & (0x0001));
	Asm("wrctl status, %0" :: "r" (TOPPERS_status) : "memory");
}

/*
 *  ������ߥ�å����֤�����
 */
#define SIL_PRE_LOC      uint8_t TOPPERS_pie_bit
#define SIL_LOC_INT()    ((void)(TOPPERS_pie_bit = TOPPERS_disint()))
#define SIL_UNL_INT()    (TOPPERS_set_pie(TOPPERS_pie_bit))

/*
 *  ���������Ԥ���prc_support.S��
 */
extern void sil_dly_nse(ulong_t dlytim);


/*
 *  I/O���֥��������ؿ���
 *  Nios2��I/O���֤ȥ�����֤϶��̤��ʤ���������å����̵���ˤ��뤿�ᡤ
 *  I/O�����������Ϥ����δؿ����Ѥ��뤳�ȤȤ��롥
 */

/*
 *  8�ӥå�ñ�̤��ɽФ��������
 */
Inline uint8_t
sil_reb_iop(void *mem)
{
	return(__builtin_ldbuio(mem));
}

Inline void
sil_wrb_iop(void *mem, uint8_t data)
{
	__builtin_stbio(mem, data);
}

/*
 *  16�ӥå�ñ�̤��ɽФ��������
 */
Inline uint16_t
sil_reh_iop(void *mem)
{
	return(__builtin_ldhuio(mem));
}

Inline void
sil_wrh_iop(void *mem, uint16_t data)
{
	__builtin_sthio(mem, data);
}

/*
 *  32�ӥå�ñ�̤��ɽФ��������
 */
Inline uint32_t
sil_rew_iop(void *mem)
{
	return(__builtin_ldwio(mem));
}

Inline void
sil_wrw_iop(void *mem, uint32_t data)
{
	__builtin_stwio(mem, data);
}

/*
 *  �ץ��å�ID�μ���
 */
Inline void
sil_get_pid(ID *p_prcid)
{
	uint32_t index;

	Asm("rdctl %0, cpuid" : "=r" (index));
	*p_prcid = index + 1;
}

#define TOPPERS_MUTEX_MUTEX_OFFSET 0x00
#define TOPPERS_MUTEX_RESET_OFFSET 0x04

#define TOPPERS_MUTEX_MUTEX_OWNER_MASK   0xffff0000
#define TOPPERS_MUTEX_MUTEX_VALUE_MASK   0x0000ffff
#define TOPPERS_MUTEX_MUTEX_OWNER_OFFSET (16U)

#define TOPPERS_MUTEX_RESET_RESET_MASK   0x01
#define TOPPERS_MUTEX_VALUE_DATA         0x1234

/*
 *  ���ԥ��å��μ�����sil�����ѤǤ��ʤ��Τ�ľ�ܥ���������
 */
Inline uint8_t
TOPPERS_sil_loc_spn(void)
{
	uint8_t pie_bit;
	uint32_t data;
	uint32_t check;
	ID       id;

  retry:
	/* ������ߥ�å����֤�*/
	pie_bit = TOPPERS_disint();

	/* ���ԥ��å��μ��� */
	sil_get_pid(&id);

	data = (id << TOPPERS_MUTEX_MUTEX_OWNER_OFFSET) | TOPPERS_MUTEX_VALUE_DATA;
	sil_wrw_iop((void *)(TOPPERS_SIL_MUTEX_BASE + TOPPERS_MUTEX_MUTEX_OFFSET), data);
	check = sil_rew_iop((void *)(TOPPERS_SIL_MUTEX_BASE + TOPPERS_MUTEX_MUTEX_OFFSET));

	if (data != check) {
		/* ���ԥ��å��������Ǥ��ʤ��ä���� */
		/* ����ߥ�å����֤����ξ��֤� */
		TOPPERS_set_pie(pie_bit);
		goto retry;
	}

	Asm("":::"memory");

	return pie_bit;
}

/*
 *  ���ԥ��å����ֵ�
 */
Inline void
TOPPERS_sil_unl_spn(uint8_t pie_bit)
{
	ID  id;

	sil_get_pid(&id);

	sil_wrw_iop((void *)(TOPPERS_SIL_MUTEX_BASE + TOPPERS_MUTEX_MUTEX_OFFSET),
				(id << TOPPERS_MUTEX_MUTEX_OWNER_OFFSET));

	/* ���ԥ��å��μ������ξ��֤� */
	TOPPERS_set_pie(pie_bit);
}
/*
 *  ���ԥ��å��ζ�������
 *  ���ץ��å������ԥ��å���������Ƥ�����˲������롥 
 */
Inline void
TOPPERS_sil_force_unl_spn(void)
{
	ID       id;
	uint32_t mutex_val;

	sil_get_pid(&id);
	mutex_val = sil_rew_iop((void *)(TOPPERS_SIL_MUTEX_BASE + TOPPERS_MUTEX_MUTEX_OFFSET));

	if (mutex_val == ((id << TOPPERS_MUTEX_MUTEX_OWNER_OFFSET) | TOPPERS_MUTEX_VALUE_DATA)) {
		sil_wrw_iop((void *)(TOPPERS_SIL_MUTEX_BASE + TOPPERS_MUTEX_MUTEX_OFFSET),
					(id << TOPPERS_MUTEX_MUTEX_OWNER_OFFSET));
	}
}


/*
 *  ���ԥ��å�
 */
#define SIL_LOC_SPN() ((void)(TOPPERS_pie_bit = TOPPERS_sil_loc_spn()))
#define SIL_UNL_SPN() (TOPPERS_sil_unl_spn(TOPPERS_pie_bit))

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_PRC_SIL_H */
