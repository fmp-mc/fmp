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
 *  @(#) $Id: nios2.h 89 2009-01-25 16:02:00Z ertl-honda $
 */

/*
 *  Nios2�Υϡ��ɥ������񸻤����
 */

#ifndef TOPPERS_NIOS2_H
#define TOPPERS_NIOS2_H

#include <sil.h>

/*
 *  ����ߥӥå�
 */
#define STATUS_U   0x02
#define STATUS_PIE 0x01

/*
 * ����ߤο�
 */
#define MAX_INT_NUM 32

/*
 * �㳰�θĿ�
 */
#define MAX_EXC_NUM 32

/*
 * ����ߥϥ�ɥ��ֹ椫�顤IRC���Τ���Υӥåȥѥ���������ޥ���
 */
#define INTNO_BITPAT(intno) (1U << intno)

/*
 * Mutex
 */ 
#define MUTEX_MUTEX_OFFSET 0x00
#define MUTEX_RESET_OFFSET 0x04

#define MUTEX_MUTEX_OWNER_MASK   0xffff0000
#define MUTEX_MUTEX_VALUE_MASK   0x0000ffff
#define MUTEX_MUTEX_OWNER_OFFSET (16U)

#define MUTEX_RESET_RESET_MASK   0x01
#define MUTEX_VALUE_DATA         0x1234

#ifndef TOPPERS_MACRO_ONLY
#include "prc_insn.h"

/*
 *  �ץ��å�INDEX��0���ꥸ��ˤμ���
 *  �������˳ƥץ��å���0����Ϣ³�����ͤ����ꤷ�Ƥ����� 
 */
Inline uint32_t
x_prc_index(void)
{
	return(current_cpuid());
}

/*
 *  Mutex��Ϣ
 */

/*
 *  Mutex�μ���
 *  �����Ǥ����true������Ǥ��ʤ����false���֤� 
 */ 
Inline int
mutex_try_lock(uint32_t addr, uint32_t id)
{
	uint32_t data;
	uint32_t check;
    
	data = (id << MUTEX_MUTEX_OWNER_OFFSET) | MUTEX_VALUE_DATA;

	sil_wrw_mem((void *)(addr + MUTEX_MUTEX_OFFSET), data);
	check = sil_rew_mem((void *)(addr + MUTEX_MUTEX_OFFSET));

	return (data == check)? true : false;
}

/*
 *  Mutex�β��� 
 */ 
Inline void
mutex_unlock(uint32_t addr, uint32_t id)
{
	sil_wrw_mem((void *)(addr + MUTEX_MUTEX_OFFSET), (id << MUTEX_MUTEX_OWNER_OFFSET));
}

/*
 *  Mutex�ν����
 */
Inline void
mutex_init(uint32_t addr)
{
	uint32_t data;
	uint32_t check;

	check = sil_rew_mem((void *)(addr + MUTEX_RESET_OFFSET));

	if ( check == MUTEX_RESET_RESET_MASK ){
		sil_wrw_mem((void *)(addr + MUTEX_RESET_OFFSET), MUTEX_RESET_RESET_MASK);
	}
	else {
		data = sil_rew_mem((void *)(addr + MUTEX_MUTEX_OFFSET));
		sil_wrw_mem((void *)(addr + MUTEX_MUTEX_OFFSET), (data & MUTEX_MUTEX_OWNER_MASK));
	}
}
#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_MICROBLAZE_H */
