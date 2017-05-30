/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_config.c 512 2010-02-01 05:33:27Z ertl-honda $
 */

/*
 *		�ץ��å���¸�⥸�塼���SH4A�ѡ�
 */
#include "kernel_impl.h"
#include "check.h"
#include "task.h"

/*
 *  SIL�Υ��ԥ��å����ѿ�
 */
uint32_t TOPPERS_spn_var;

/*
 *  ��å��������˻��Ѥ�����ߡ��ѿ�
 */
uint32_t dangling_dummy;

/*
 *  �Ƴ�����ֹ����IPR�ξ�������ơ��֥�
 *  ���Ƥ�����ϡ��ץ��å�������˰ۤʤ�Τ��ᡤ
 *  �ץ��å������������ե�������������
 */
const IPR_INFO ipr_info_tbl[TNUM_INH] = {
    IPR_INFO_TBL_DATA 
};

/*
 *  �Ƴ�����ֹ����MSKCLR�ξ�������ơ��֥�
 *  ���Ƥ�����ϡ��ץ��å�������˰ۤʤ�Τ��ᡤ
 *  �ץ��å������������ե�������������
 */
const MSK_INFO mskclr_info_tbl[TNUM_INH] = {
    MSKCLR_INFO_TBL_DATA
};

/*
 *  �����ͥ�Υ٥������١���
 */
extern void base_vec(void);

/*
 *  start.S �Ǥ�Ʊ����
 */
volatile uint_t   start_sync;

/*
 *  sta_ker ��ǤΥХꥢƱ�����ѿ�
 */
static volatile bool_t   prc_init[TNUM_PRCID];
static volatile uint_t   sys_start;

/*
 *  Ʊ���Τ���Υޥ���
 */
#define MAGIC_START 0x87654321U

/*
 *  sta_ker ��ǤΥХꥢƱ��
 */
void
sta_ker_barrier_sync(void){
	volatile uint_t i, j;
	volatile uint_t flag;

	prc_init[x_prc_index()] = true;

	if (x_sense_mprc()) {
		do{
			flag = 0;
			for(i = 0; i < TNUM_PRCID; i++){
				if(prc_init[i] == true){
					flag++;
				}
			}
			for(j = 0; j < 100; j++);
		}while (flag < TNUM_PRCID);
		sys_start = MAGIC_START;
		start_sync = 0;

      
	}
	else {
		while(sys_start != MAGIC_START){
			for(j = 0; j < 100; j++);
		}
	}
}

/*
 *  str_ker()�����ǥޥ����ץ��å��ǹԤ������
 */
void
prc_mprc_initialize(void)
{
	/*
	 *  SIL�Υ��ԥ��å����ѿ��ν����
	 */
	TOPPERS_spn_var = 0U;

	/*
	 * �����ͥ���٥쥸�����ν����
	 */
	init_int2pri();

	/*
	 *  ����ߥ���ȥ���ν����
	 */
	init_irc();
}


/*
 *  �ץ��å���¸�ν����
 */
void
prc_initialize(void)
{
	TPCB *p_tpcb = get_my_p_tpcb();

	/*
	 *  CPU��å��ե饰�¸��Τ�����ѿ��ν����
	 */
	p_tpcb->lock_flag = true;
	p_tpcb->saved_iipm = IIPM_ENAALL;

	set_vbr(base_vec);
}

/*
 *  �ץ��å���¸�ν�λ����
 */
void
prc_terminate(void)
{

}

/*
 *  ������׵�饤��°��������
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri, uint_t affinity_mask)
{
	assert(VALID_INTNO_CFGINT(intno));
	assert(-15 <= intpri && intpri <= TMAX_INTPRI);

	/* 
	 *  ��ö����ߤ�ػߤ���
	 */    
	(void)x_disable_int(intno) ;

	/*
	 *  ��٥�ȥꥬ/���å��ȥꥬ������
	 *  IRQ�Τߥ��ݡ��Ȥ���
	 */
	if(INTNO_IRQ(INTNO_MASK(intno)) != 0U){
		uint16_t icr1_val = sil_rew_mem((void*)ICR1);
		uint16_t offset   = INTNO_IRQ_OFFSET(INTNO_MASK(intno)) * 2U;

		icr1_val &=  ~(0x03U << offset);
        
		if((intatr & TA_POSEDGE) != 0U) {
		/*
		 *  �ݥ��ƥ��֥��å�
		 */
			icr1_val |= IRQ_POSEDGE << offset;            
        }else if((intatr & TA_NEGEDGE) != 0U) {
		 /*
		  *  �ͥ��ƥ��֥��å�
		 */
			icr1_val |= IRQ_NEGEDGE << offset;                        
        }else {
		/*
		 *  ����٥�ȥꥬ
		 */
			icr1_val |= IRQ_LOWLEVEL << offset;
		}
        
		sil_wrw_mem((void*)ICR1, icr1_val);
	}

	/*
	 *  ������׵�ޥ������(ɬ�פʾ��)
	 *  Ʊ���˳����ͥ���٤⥻�åȤ����
	 */

	if ((intatr & TA_ENAINT) != 0U) {
		(void) x_enable_int(intno);
	}

	/*
	 *������ߥޥ������ꥢ�쥸�������å�
	 */
	set_target_irc(intno,x_prc_index());

}


#ifndef OMIT_DEFAULT_EXC_HANDLER
/*
 *  Trapa�ʳ����㳰����Ͽ����Ƥ��ʤ��㳰��ȯ������ȸƤӽФ����
 */
void
default_exc_handler(void *p_excinf)
{
	uint32_t expevt = *(((uint32_t*)p_excinf) + P_EXCINF_OFFSET_EXPEVT);
	uint32_t spc    = *(((uint32_t*)p_excinf) + P_EXCINF_OFFSET_SPC);
	uint32_t ssr    = *(((uint32_t*)p_excinf) + P_EXCINF_OFFSET_SSR);
	uint32_t pr     = *(((uint32_t*)p_excinf) + P_EXCINF_OFFSET_PR);
    
	syslog(LOG_EMERG, "Unregistered Expevt error occurs.");
	syslog(LOG_EMERG, "Expevt = %08x SPC = %08x SR = %08x PR=%08X",
           expevt, spc, ssr, pr);
	target_exit();
}
#endif /* OMIT_DEFAULT_EXC_HANDLER */

#ifndef OMIT_DEFAULT_INT_HANDLER
/*
 *  ̤��Ͽ�γ���ߤ�ȯ���������˸ƤӽФ����
 */
void
default_int_handler(void *p_excinf)
{
	uint32_t spc     = *(((uint32_t*)p_excinf) + 13U);
	uint32_t ssr     = *(((uint32_t*)p_excinf) + 11U);
	uint32_t pr      = *(((uint32_t*)p_excinf) + 12U);
	uint32_t intevt  = sil_rew_mem((void*)INTEVT);
#ifdef USE_INTEVT2    
	uint32_t intevt2 = sil_rew_mem((void*)INTEVT2);
#endif /* USE_INTEVT2 */      
	syslog(LOG_EMERG, "Unregistered Interrupt occurs.");
#ifdef USE_INTEVT2    
	syslog(LOG_EMERG, "INTEVT = %08x INTEVT2 = %08x SPC = %08x SR = %08x PR = %08x ",
           intevt, intevt2, spc, ssr, pr);
#else
	syslog(LOG_EMERG, "INTEVT = %08x SPC = %08x SR = %08x PR = %08x ",
           intevt, spc, ssr, pr);    
#endif /* USE_INTEVT2 */      
	target_exit();
}
#endif /* OMIT_DEFAULT_INT_HANDLER */
