/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2009 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN  
 *	Copyright (C) 2009-2010 by Industrial Technology Institute,
 *								Miyagi Prefectural Government, JAPAN
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
 *  $Id: prc_pcb.h 765 2011-01-13 07:18:55Z mit-kimai $
 */

/*
 *  �ץ��å���¸�ץ��å�����ȥ���֥�å��⥸�塼���SH2A-DUAL�ѡ�
 */
#ifndef TOPPERS_PRC_PCB_H
#define TOPPERS_PRC_PCB_H

/*
 *  �����ͥ��å�������
 */
#define TTYPE_KLOCK 	G_KLOCK

#ifndef TOPPERS_MACRO_ONLY

#include "prc_insn.h"	/*  current_gbr()  */
#include <sil.h>

/*
 *  ��å��η�
 */
typedef uint8_t *LOCK;		/*  SEMR1�ؤΥݥ���  */

/*
 *  ��������
 */
typedef struct processor_control_block PCB;

/*
 *  SH2A-DUAL��¸�ץ��å�����ȥ���֥�å�
 */
typedef struct target_processor_control_block{
	/*
	 *  ����ƥ����Ȥδ���
	 */
	uint32_t excnest_count;	/*  ����ߡ�CPU�㳰�Υͥ��Ȳ��  */
	STK_T* istkpt;			/*  �󥿥�������ƥ������ѤΥ����å��ν����  */
	
	/*
	 *  CPU��å���ǽ
	 */
	bool_t lock_flag;		/*  CPU��å��ե饰  */
	uint32_t saved_iipm;	/*  CPU��å����IPM���ͤ��ݻ������ѿ�������ɽ����*/

	/*
	 *  �٥����ơ��֥�ؤΥݥ��󥿡��׸�Ƥ��ɬ�פʤ�����
	 */
	const FP* p_vector_table;
}TPCB;

/*  ���¸����get_my_p_pcb()����Ѥ��ʤ�  */
#define OMIT_GET_MY_P_PCB

/*
 *  my_p_pcb�μ���
 *  ��gcc�Ǥϡ�gbr����Ѥ��ʤ��Τǡ�my_p_pcb��gbr�˳�����ơ�
 *  ��CPUIDR��my_p_pcb_table�ؤ�̵�̤ʥ��������򸺤餹��
 *  �����׸�Ƥ��
 */
Inline PCB*
get_my_p_pcb(void)
{
	PCB* my_p_pcb;
	
	my_p_pcb = current_gbr();
	return my_p_pcb;
}

/*
 *	�ץ��å�INDEX��0���ꥸ��ˤμ���
 *	�������
 *	����CPU0��0
 *	����CPU1��1
 */
Inline uint_t
x_prc_index(void)
{
	uint32_t cpuidr, index;
	
	cpuidr = sil_rew_reg((uint32_t *)CPUIDR_w);
	if ((cpuidr & CPUIDR_ID_BIT) == 0) {
		index = 0U;
	} else {
		index = 1U;
	}
	return index;
}


#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_PCB_H */
