/*
 *	TOPPERS/FMP Kernel
 *		Toyohashi Open Platform for Embedded Real-Time Systems/
 *		Advanced Standard Profile Kernel
 *	
 *	Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *								Toyohashi Univ. of Technology, JAPAN
 *	Copyright (C) 2007		by Embedded and Real-Time Systems Laboratory
 *				Graduate School of Information Science, Nagoya Univ., JAPAN
 *	Copyright (C) 2007-2011 by Industrial Technology Institute,
 *								Miyagi Prefectural Government, JAPAN
 *	
 *	�嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *	�����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *	�ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *	(1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *		��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *		����������˴ޤޤ�Ƥ��뤳�ȡ�
 *	(2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *		�ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *		�ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *		��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *	(3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *		�ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *		�ȡ�
 *	  (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *		  �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *	  (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
 *		  ��𤹤뤳�ȡ�
 *	(4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *		������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 *		�ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *		ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ�
 *		���դ��뤳�ȡ�
 *	
 *	�ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *	���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *	���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *	�������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *	����Ǥ�����ʤ���
 * 
 *  $Id: prc_support.S 867 2011-08-09 05:53:10Z mit-kimai $
 */

/*
 *	�ץ����å���¸�⥸�塼�� ������֥��������SH2A-DUAL�ѡ�
 *		�����ǥ��󥰥롼��
 *	 ��		����ǥ�Ȥ��ٱ䥹���åȤ�ɽ����
 *	 ��		��������̿�ᡧjmp��jsr��bra��bsr��rts��rte��bf/s��bt/s��bsrf��braf
 */

#define TOPPERS_MACRO_ONLY
#define UINT_C(val) 	(val)		 /* uint_t�����������ޥ��� */
#define ULONG_C(val)	(val)		 /* ulong_t�����������ޥ��� */
#define CAST(type, val) (val)		 /* �����㥹�Ȥ�Ԥ��ޥ��� */

/*
 *	������֥��ѤΥޥ�����ͭ���ˤ���
 */
#define TOPPERS_ASM_MACRO
#include "kernel_impl.h"
#include "offset.h"

/*
 *	����
 *	  �������0x80�ʾ�ˤʤ������ĥ���졢
 *	  ���Ԥ���ư��ˤʤ�ʤ���
 */
#if !(TCB_p_tinib < 0x80)
#error	Range error!  Check (TCB_p_tinib < 0x80)
#endif

#if !(TCB_texptn < 0x80)
#error	Range error!  Check (TCB_texptn < 0x80)
#endif

#if !(TCB_sp < 0x80)
#error	Range error!  Check (TCB_sp < 0x80)
#endif

#if !(TCB_pc < 0x80)
#error	Range error!  Check (TCB_pc < 0x80)
#endif

#if !(TCB_enatex < 0x80)
#error	Range error!  Check (TCB_enatex < 0x80)
#endif

#if !(TCB_enatex_bit < 8)
#error	Range error!  Check (TCB_enatex_bit < 8)
#endif


/*
 *	�����ͥ���Ǥ�������߶ػ߻���IPM����
 *
 *	kernel_cfg.c ��Υ�����֥�ǻ���
 */
	.global _iipm_disall
_iipm_disall = IIPM_DISALL

/*
 *	�������ǥ����ѥå���
 *
 *	���Υ롼����ϡ�
 *	 ������������ƥ�����(excnest_count = 0)
 *	 ��CPU���å�����
 *	 ���ǥ����ѥå����ľ���
 *	 ���ʥ�ǥ��Ρ˳����ͥ���٥ޥ������������
 *	�ǸƤӽФ���롥
 */

	.text
	.align 2
	.global _dispatch
_dispatch:
	/*
	 *	������å��쥸������������٤ƤΥ쥸��������¸
	 *	��pr,r8��r14�򥹥��å�����¸
	 *	��r0��r7�ϸƤӽФ�������¸���Ƥ��뤿����¸����ɬ�פ�̵��
	 */
	movmu.l r8,@-r15
	stc gbr, r7						/*  r7��my_p_pcb  */
	mov.l @(PCB_p_runtsk,r7),r0		/*  r0��my_p_pcb->p_runtsk 	*/
	mov.l _dispatch_r_dis,r1		/*  r1���¹ԺƳ�����   		*/
	mov.l r15,@(TCB_sp,r0)  /* �����������å���TCB����¸ 60�ʲ��ʤ�OK */
	bra   _dispatcher
	 mov.l	r1,@(TCB_pc,r0)   /* �¹ԺƳ����Ϥ�TCB����¸  60�ʲ��ʤ�OK	*/

_dispatch_r:
	/*
	 *	������å��쥸�����ν������٤ƤΥ쥸����������
	 *	��pr,r8��r14�򥹥��å���������
	 */
	movmu.l @r15+,r8
	/*
	 *	�������㳰�����롼����ε�ư
	 *	dispatch_r��dispatcher����ƤӽФ���뤿�ᡤ
	 *	tcb�Υ��ɥ쥹��r0�����äƤ��롥
	 */
	bld.b  #TCB_enatex_bit, @(TCB_enatex,r0)
	bt     _dispatch_r_check_texptn	/* enatex��true�ʤ�texptn�Υ����å��� */
	rts/n		/*  dispatch()�θƤӽФ����إ꥿����  */

	/* texptn��0�Ǥʤ���ipmflg��true�ʤ�С��������㳰�����롼����θƤӽФ� */
_dispatch_r_check_texptn:
	mov.l  @(TCB_texptn,r0),r1		/* texptn������� */
	tst    r1,r1
	bf	   _dispatch_r_check_ipmflg
	rts/n		/*  dispatch()�θƤӽФ����إ꥿����  */

_dispatch_r_check_ipmflg:
	stc gbr, r7						/*  r7��my_p_pcb  */
	mov.l @(PCB_ipmflg,r7),r1		/* ipmflg������� */
	tst    r1,r1
	bf	   _dispatch_r_call_texrtn
	rts/n		/*  dispatch()�θƤӽФ����إ꥿����  */


	/*
	 * �������㳰�����롼����θƤӽФ�
	 * ��_call_texrtn�����dispatch()�θƤӽФ����إ꥿���󤹤뤿�ᡢ
	 * ��jmp̿���ʬ�����롣
	 *����pr�쥸�����ˤϡ�dispatch()�θƤӽФ��������Ϥ���Ǽ����Ƥ��ꡢ
	 *���������ǤϽ񤭴����ʤ�����
	 */
_dispatch_r_call_texrtn:
	mov.l  _dispatch_call_texrtn_dis,r2
	jmp    @r2
	 nop

/*
 * �ǥ����ѥå����ư��ϡ�prc_support.S��
 */
	.global _start_dispatch
_start_dispatch:
	/*
	 *	���Υ롼����ϡ������ͥ뵯ư���ˡ�
	 *	�������٤Ƥγ���ߤ�ػߤ������֡�������ߥ��å����֤�Ʊ����
	 *	����sp���󥿥�������ƥ������ѥ����å��ݥ���
	 *	�ξ��֤ǸƤӽФ���뤳�Ȥ����ꤷ�Ƥ��롥
	 *
	 *	prc_initialize�ǡ�
	 *	����lock_flag��true
	 *	����saved_iipm��IIPM_ENAALL
	 *	�˽�������Ƥ��뤿�ᡤ�����ͥ�������γ���ߤ���Ĥ��뤳�Ȥǡ�
	 *	����CPU���å�����
	 *	�����ʥ�ǥ��Ρ˳����ͥ���٥ޥ������������
	 *	�ˤʤ롥
	 *	�ޤ���initialize_task��disdsp��false�˽�������Ƥ��뤿�ᡤ�ǥ�
	 *	���ѥå����ľ��֤ˤʤäƤ��롥
	 *
	 *	��äơ�����������ƥ����Ȥ��ڤ��ؤ�������Ǥ褤��
	 */
	mov   #0,r0
	bra   _dispatcher_0
	 mov.l r0, @(PCB_excnest_count,gbr)	/* excnest_count��0  	*/

/*
 *	���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå�
 */
	.global _exit_and_dispatch
_exit_and_dispatch:
	/* �ǥ����ѥå������Ρ�dispatcher�ˤ� */

/*
 * �ǥ����ѥå�������
 */
_dispatcher:
#ifdef LOG_DSP_ENTER
	mov.l _log_dsp_enter_dis, r1	/* �������ϴؿ� */
	stc gbr, r8						/* r8��my_p_pcb */
	jsr   @r1
	 mov.l @(PCB_p_runtsk,r8),r4
							/* ������r4��my_p_pcb->p_runtsk */
#endif /* LOG_DSP_ENTER */
_dispatcher_0:
   /*
	*  �����ˤ�ä����Τϡ��嵭��_dispatcher��¾�ˡ�
	*  ������2�ս꤫����ή���Ƥ��롣
	*	   ��_start_dispatch
	*	   ��_dispatcher_2�ʼ¹Ԥ��٤����������ʤ�������Ԥ��ξ���
	*
	*  ���Υ롼����ϡ�
	*	   ������������ƥ�����
	*	   ��CPU���å�����
	*	   ���ǥ����ѥå����ľ���
	*	   ���ʥ�ǥ��Ρ˳����ͥ���٥ޥ������������
	*  �ǸƤӽФ���롥
	*
	*  ���ʤ����
	*	   ��excnest_count=0
	*	   ��lock_flag=true
	*	   ��disdsp=false
	*	   ��dspflg=true
	*	   ��saved_iipm=IIPM_ENAALL
	*���ȤʤäƤ��롥�¹ԺƳ����Ϥؤ⤳�ξ��֤Τޤ�ʬ�����롥
	*/
	stc gbr, r7						/* r7��my_p_pcb  */
	mov.l @(PCB_p_schedtsk,r7),r8	/* r8 <- my_p_schedtsk 			*/
	tst    r8,r8					/* my_p_schedtsk �����뤫��		*/
	bt/s  _dispatcher_1				/* my_p_schedtsk��̵����Х����� 	*/
	 mov.l r8, @(PCB_p_runtsk,r7)	/* my_p_runtsk��my_p_schedtsk	*/
	mov.l @(TCB_sp,r8),r15 			/* TCB���饿���������å�������	*/
#ifdef LOG_DSP_LEAVE
	mov.l _log_dsp_leave_dis, r1 	/* �������ϴؿ� */
	jsr   @r1
	 mov   r8, r4					/* ����	  */
#endif /* LOG_DSP_LEAVE */
	mov.l  @(TCB_pc,r8),r1		/* TCB����¹ԺƳ����Ϥ�����		*/
	jmp    @r1
	 mov   r8, r0
		/*
		 *  ʬ����ʼ¹ԺƳ����ϡˤǤϡ�r0��my_p_schedtsk��
		 *  ��Ǽ���줿���֤����ꤷ�Ƥ��롣
		 */

	/* 
	 * �¹Ԥ��٤����������ʤ����γ�����Ԥ�
	 */
_dispatcher_1:
	/* 
	 * ���ߥǥ��������ͤ�����ɤ߹���Τϸ�Ψ�������Τǻ������Ѱդ���
	 * ���׸�Ƥ���쥸����������Ƥθ�ľ����ASP��changeset/1658��
	 * 
	 * r0  : 0x00�ʳ���ߤ���Ĥ���Ȥ��ˤϤ����ͤ�SR�����ꤹ���
	 * r1  : 0x01
	 * r2  : ����߶ػߤΤ����SR����
	 * r8  : my_p_pcb
	 * r12 : ����_sleep_end
	 */
	mov    #0,r0
	mov    #1,r1
	mov.l  _iipm_disall_dis,r2		/* ����߶ػ߻���SR���� */
	stc    gbr, r8					/* r8��my_p_pcb */
#ifndef OMIT_POWER_CONTROL
	mov.l _sleep_end_dis, r12
#endif /* OMIT_POWER_CONTROL */
	/*
	 *  ����ߤ���Ĥ����顢CPU���å�������֤ˤʤ�褦��������
	 *  ����my_p_tacb->lock_flag��false
	 */
	mov.l r0, @(PCB_lock_flag,gbr)
	/*
	 *	�󥿥�������ƥ����Ȥ��ڤ��ؤ�
	 *	
	 *	�������󥿥�������ƥ����Ȥ��ڤ괹����Τϡ�������ȯ��������
	 *	�߽����ˤɤΥ����å���Ȥ����Ȥ�������β��ȡ�����ߥϥ�ɥ�
	 *	��ǤΥ������ǥ����ѥå����ɻߤȤ�����Ĥΰ�̣�����롥
	 */
	mov.l r1, @(PCB_excnest_count,r8)	/* excnest_count��1  	*/
	mov.l @(PCB_istkpt,r8),r15			/* �����å����ؤ�		*/
_dispatcher_2:
	/*
	 *��������Ԥ�
	 *
	 *���ǥ����ѥå���νи��Ǽ¹Ԥ��٤����������ʤ�(schedtsk==
	 *��NULL�˾��ϡ�sleep̿��ˤ�äƥץ����å�������ϥ⡼�ɤ���
	 *�����ؤ��Ƴ�����Ԥ��򤷤Ƥ��롣
	 *��
	 *������ߵ��ĸ��sleep̿���¹Ԥ��Ƥ��뤿�ᡢ����ߵ���̿���
	 *���¹����˳�����׵᤬���äƤ�����ʤ��뤤�ϳ���ߵ���ľ�塢
	 *��sleep̿��¹����˳�����׵᤬���ä����ˡ�����ߵ���̿���
	 *���¹Ԥȶ��˳���ߤ������դ���졢�����������sleep�����ޤޤ�
	 *���ʤꡢreqflg�Υ����å��˿ʤޤʤ���
	 *����1msec����˥����޳���ߤ����뤿�ᡢ�ºݤˤ�sleep�����ޤޤ�
	 *���������ȤϤʤ�����
	 *��
	 *����������ϡ�����ߤε��Ĥ�sleep���֤ؤΰܹԤ����ȥߥå��˼�
	 *���ԤǤ��ʤ����Ȥ˵������롣
	 *
	 *	����������褹�뤿�ᡤrte̿��Ρ�PC,SR�������ٱ䥹���åȤ�
	 *	̿��򡢳���ߤȤ��Բ�ʬ�˼¹Ԥ���פȤ������ͤ����Ѥ������
	 *	�ߤε��ĤȾ����ϥ⡼�ɤؤΰܹԤ��Բ�ʬ�˹Ԥ���
	 */
#ifdef OMIT_POWER_CONTROL
	ldc    r0,sr				/*  ����ߵ��� 				  */
	ENAINT_NOP					/*  CPU����INTC����ã�����ޤǤ��ٱ�  */
	
#else /* OMIT_POWER_CONTROL */
	mov.l r0, @-r15				/*	SR�����ꤹ���ͤ򥹥��å����Ѥ�	*/
	mov.l r12, @-r15			/*	������Ϥ򥹥��å����Ѥ�  */
	/*
	 *������ߵ��Ĥ���ʥ����å������ɤ߽Ф����ͤ�SR�����ꤹ���
	 *����Ʊ���˾����ϥ⡼�ɤذܹԤ��롣
	 *��
	 *���׸�Ƥ
	 *�������եȥ�����������Х��⡼�ɤ˰ܹԤ�������
	 *�����Х����ơ��ȥ���ȥ�����Υ饤�ȥХåե�����
	 *��������RAM�ؤν񤭹��ߤ���λ�������Ȥ��ǧ���롣
	 *�����ʳ���RAM�ؤΥ��ߡ��꡼�ɤ�Ԥ�����
	 */
	rte
	 sleep						/*	���ٱ䥹���åȡ�  */

_sleep_end:
#endif /* OMIT_POWER_CONTROL */
	ldc    r2,sr				/* �����ͥ�����γ���ߤ�ػ�	   */
	/*
	 *��LDC Rm,SR̿��λ���
	 *����ľ���̿��¹Ի��˳�����׵᤬���ä����ο�����
	 *��
	 *������SH-2E����
	 *��������ľ���̿�᤬����߶ػߤǼ¹Ԥ���롣
	 *��������
	 *������SH-2A�ʹ�
	 *��������LDC Rm,SR̿������ꤷ������ߥޥ�����SR��I�ӥåȡˤ�ȿ�Ǥ���
	 *��������ľ���̿��¹Ի��˳���ߤ�����դ��뤫�ݤ�����ޤ롣
	 *��
	 *����äơ��ʲ��Υ������󥹤Ǥϡ��ɤ���ξ���̿�ᣱ��
	 *������߶ػߤǼ¹Ԥ����Τǡ�nop̿�����������ɬ�פϤʤ���
	 *��
	 *��  mov  #f0, r0
	 *��  ldc  r0, sr
	 *����̿�ᣱ
	 */
	mov.l @(PCB_reqflg,r8),r6	/* r6 <- my_p_pbc->reqflg		   */
	tst   r6,r6					/* reqflg �� false�ʤ�			   */
	bt	  _dispatcher_2			/* ��dispatcher_2 ��			   */
	mov.l r0, @(PCB_reqflg,gbr)	/* reqflg��false				   */
	/*
	 *	����������ƥ����Ȥ��ڤ��ؤ�
	 *	�������å��ڤ��ؤ��ϡ�ʬ�����_dispatcher_0�ǹԤ���
	 */
	mov.l r0, @(PCB_excnest_count,gbr)	/* excnest_count �򥯥ꥢ	*/
	
	/*
	 *	CPU���å����֤��᤹��������Ԥ��δ֤˼¹Ԥ�������ߥϥ�ɥ�ˤ�
	 *	�ꡤsaved_iipm���񤭴��������ǽ�������뤿�ᡤ�����ͤ��᤹ɬ
	 *	�פ����롥dispatcher���¹Ԥ������ϡ�saved_iipm��IIPM_ENAALL
	 *	�ȤʤäƤ��뤿�ᡤ�����Ǥ�saved_iipm��IIPM_ENAALL�ʡ�0�ˤ��᤻
	 *	�Ф褤��
	 */
	mov.l r1, @(PCB_lock_flag,r8)		/* lock_flag��true */
	bra    _dispatcher_0
	 mov.l r0, @(PCB_saved_iipm,gbr)	/* saved_iipm��0 */


    /*
     *  ���������Υޥ����졼�����
     *  ���ѥ�᡼���Ȥ���r4�˥ޥ����졼�������Υץ����å�ID��
     *  ����Ǽ����Ƥ���Τǡ�migrate_self��ƤӽФ��ޤǡ�
     *  ���˲����ƤϤ����ʤ���
     */
    .text
    .align 2
    .global _dispatch_and_migrate
_dispatch_and_migrate:
	/*
	 *	������å��쥸������������٤ƤΥ쥸��������¸
	 *	��pr,r8��r14�򥹥��å�����¸
	 *	��r0��r7�ϸƤӽФ�������¸���Ƥ��뤿����¸����ɬ�פ�̵��
	 */
	movmu.l r8,@-r15
	mov.l @(PCB_p_runtsk,gbr),r0	/*  r0��my_p_pcb->p_runtsk 	*/
	mov.l _dispatch_r_dis,r1		/*  r1���¹ԺƳ�����   		*/
	mov.l r15,@(TCB_sp,r0)  /* �����������å���TCB����¸ 60�ʲ��ʤ�OK */
	mov.l r1,@(TCB_pc,r0)   /* �¹ԺƳ����Ϥ�TCB����¸  60�ʲ��ʤ�OK	*/
    mov.l p_migrate_self, r2
	stc   gbr, r8			/* r8��my_p_pcb */
    jsr   @r2		/*  �ѥ�᡼��r4���ޥ����졼�������Υץ����å�ID  */
	 mov.l @(PCB_istkpt,r8),r15
							/* �󥿥�������ƥ������ѥ����å����ڤ��ؤ� */

    .align 2
_iipm_disall_dis:
	.long _iipm_disall

    /*
     *  ���ߤΥ���ƥ����Ȥ�Τƥޥ����졼�����
     */
    .text
    .align 2
    .global _exit_and_migrate
_exit_and_migrate:
    mov.l p_exit_and_migrate_self, r2
	stc   gbr, r8	/* r8��my_p_pcb */
    jsr   @r2		/* ����������exit�ȥޥ����졼�����롼����� */
    				/*  �ѥ�᡼��r4���ޥ����졼�������Υץ����å�ID  */
	 mov.l @(PCB_istkpt,r8),r15
					/* �󥿥�������ƥ������ѥ����å����ڤ��ؤ� */

	.align 2
_dispatch_r_dis:
	.long _dispatch_r
_dispatch_call_texrtn_dis:
	.long _dispatch_call_texrtn
#ifndef OMIT_POWER_CONTROL
_sleep_end_dis:
	.long _sleep_end
#endif /* OMIT_POWER_CONTROL */
#ifdef LOG_DSP_ENTER
_log_dsp_enter_dis:
	.long _log_dsp_enter
#endif /* LOG_DSP_ENTER */
#ifdef LOG_DSP_LEAVE
_log_dsp_leave_dis:
	.long _log_dsp_leave
#endif /* LOG_DSP_LEAVE */

p_migrate_self:
    .long _migrate_self
p_exit_and_migrate_self:
    .long _exit_and_migrate_self


/*
 *	�����ͥ�ν�λ�����θƽФ�
 *
 *	�����å����󥿥�������ƥ������Ѥ��ڤ��ؤ���
 *	exit_kernel��ʬ�����롣
 *	���δؿ��ϡ�������ߥ��å����֤ǸƤФ��
 */
	.global _call_exit_kernel
_call_exit_kernel:
	mov.l _exit_kernel_exit,r0
	stc   gbr, r7					/* r7��my_p_pcb */
	jmp   @r0
	 mov.l @(PCB_istkpt,r7),r15	/* �����å��ڤ��ؤ�		   */

	.align 2
_exit_kernel_exit:
	.long _exit_kernel


/*
 *	��������ư����
 *
 *	�ǥ����ѥå��㤫�顢�ʲ��ξ��֤Ǥ����ˤ��롣
 *  ��������������ƥ�����
 *  ����CPU���å�����
 *  ���������ͥ���٥ޥ������������
 *  �����ǥ����ѥå����ľ���
 *  ����r0��my_p_runtsk
 */
	.text
	.global _start_r
_start_r:
	/*
	 *  ����ߤ���Ĥ����顢CPU���å�������֤ˤʤ�褦��������
	 *  ����my_p_tacb->lock_flag��false
	 */
	mov    #0,r2
	stc    gbr, r7				 /* r7��my_p_pcb */
	mov.l  r2, @(PCB_lock_flag, r7)
	ldc    r2,sr				 /* ����ߵ��� */
	mov.l  @(TCB_p_tinib,r0),r3  /* r3��my_p_runtsk->p_tinib  */
	mov.l  _ext_tsk_start,r5
	mov.l  @(TINIB_task,r3),r1	 /* r1����������ư����	 */
	lds    r5,pr				 /* ������Ϥ����� */
	jmp    @r1
	 mov.l @(TINIB_exinf,r3),r4  /* exinf������쥸����r4��  */

	.align 2
_ext_tsk_start:
	.long _ext_tsk


/*
 *  ����ߤκݤΥ����å��ݥ��󥿤��ؤ��������֤���SR,PC�Υ��ԡ�������
 *  ���ޤǤΥ��ե��å�
 *����
 *����SP_PC_OFFSET_INT��_ret_int_2�λ����ǤΡ������å����Ѥޤ줿
 *����������������������PC�ؤΥ��ե��å�
 *����SP_SR_OFFSET_INT��_ret_int_3�λ����ǤΡ������å����Ѥޤ줿
 *����������������������SR�ؤΥ��ե��å�
 *����
 *����
 * �����å��ڤ��ؤ����Υ����å�
 * �ʳ���߼��ջ��Υ���ƥ������ѥ����å���
 *
 * (1) �쥸�����Х󥯤���Ѥ��ʤ����
 *        ----------------------
 *  0    |         PR           |   <-- _ret_int_2 / _ret_int_3 �λ���
 *        ----------------------
 *  1    |        MACH          |
 *        ----------------------
 *  2    |        MACL          |
 *        ----------------------
 *  3    |         R0           |
 *        ----------------------
 *  4    |         R1           |
 *        ----------------------
 *  5    |         R2           |
 *        ----------------------
 *  6    |         R3           |
 *        ----------------------
 *  7    |         R4           |
 *        ----------------------
 *  8    |         R5           |
 *        ----------------------
 *  9    |         R6           |
 *        ----------------------
 * 10    |         R7           |
 *        ----------------------
 * 11    |         PC           |
 *        ----------------------
 * 12    |         SR           |
 *        ----------------------
 *
 * (2) �쥸�����Х󥯤���Ѥ�����
 *        ----------------------
 *  0    |         PR           |   <-- _ret_int_3 �λ���
 *        ----------------------
 *  1    |        MACH          |
 *        ----------------------
 *  2    |        MACL          |
 *        ----------------------
 *  3    |         R0           |
 *        ----------------------
 *  4    |         R1           |
 *        ----------------------
 *  5    |         R2           |
 *        ----------------------
 *  6    |         R3           |
 *        ----------------------
 *  7    |         R4           |
 *        ----------------------
 *  8    |         R5           |
 *        ----------------------
 *  9    |         R6           |
 *        ----------------------
 * 10    |         R7           |
 *        ----------------------
 * 11    |         PC           |   <-- _ret_int_2 �λ���
 *        ----------------------
 * 12    |         SR           |
 *        ----------------------
 */
#ifdef USE_BANKED_REG
#define    SP_PC_OFFSET_INT    0
#else /* USE_BANKED_REG  */
#define    SP_PC_OFFSET_INT    (11*4)
#endif /* USE_BANKED_REG */

#define    SP_SR_OFFSET_INT    (12*4)


/*
 *	���̳���ߤ���������
 *����������װ��˰ͤ餺�����̤���ʬ
 *�����ʥ���ե�����졼����������������������kernel_cfg_asm.S�ˤ����
 *������³����
 *	
 *	������װ����Ÿ�������롼�����r4,r5,r6,r7����¸����
 *����r5��������ֹ�
 *����r6������ߥϥ�ɥ����Ƭ���ɥ쥹
 *����r7������߼���ľ���SR�Υ��ԡ�
 *	�ξ��֤Ǥ�������롣
 *	��r4�˳�����Ƥʤ��Τϡ�CPU�㳰�ϥ�ɥ�ν����Ȥʤ�٤����̤ˤ��뤿���
 */
	.text
	.global _interrupt_entry
_interrupt_entry:
#ifndef  USE_BANKED_REG
    movml.l r3, @-r15	/*  �Ĥ�Υ�����å��쥸�����򥹥��å����Ѥ�  */
    sts.l  mach,@-r15
    sts.l  macl,@-r15
    sts.l  pr,@-r15
#endif /* USE_BANKED_REG */
							/* �����/CPU�㳰�ͥ��ȥ����󥿤Υ����å� */
	stc    gbr, r3				/* r3��my_p_pcb */
	mov.l  @(PCB_excnest_count, r3),r1
	tst    r1,r1				/* �����ȯ�����Υ���ƥ����Ȥ�Ƚ��  */
	add    #0x1,r1				/* ����ߥͥ��ȥ����󥿤򥤥󥯥���� */
    bf/s   _interrupt_entry_1   /* ¿�ų���ߤʤ饸����  */
	 mov.l  r1, @(PCB_excnest_count, r3)
	mov    r15,r2				/* �����å��ڤ��ؤ���*/
	mov.l  @(PCB_istkpt, r3),r15
	mov.l  r2,@-r15 			 /* �����������å�����¸ */
_interrupt_entry_1:
	ldc    r7,sr				 /* ����ߵ���	*/
	/*
	 * ������ֹ����¸
	 * ����������¸����������ֹ�ˤϡ����Ĥΰ�̣�����롣
	 * ������default_int_handler�ΰ���
	 * ������log_inh_leave_int�ΰ���
	 */
	mov.l  r5,@-r15

#ifdef LOG_INH_ENTER
	mov.l _log_inh_enter_int, r1 /* �������ϴؿ� */
	mov.l  r6,@-r15 	  /* r6�ʳ���ߥϥ�ɥ����Ƭ���ɥ쥹����¸ */
	jsr   @r1
	 mov  r5, r4				 /* ����		  */
	mov.l @r15+, r6 			 /* r6����		  */
#endif /* LOG_INH_ENTER */

	jsr    @r6					 /* ����ߥϥ�ɥ�ƤӽФ�  */
#ifndef LOG_INH_LEAVE
	  mov.l @r15+,r4			 /* default_int_handler�Ѥΰ��� */
	  							 /*  �ʳ�����ֹ��  */
#else  /* LOG_INH_LEAVE */
	  mov.l  @r15, r4			 /* default_int_handler�Ѥΰ��� */
	  							 /*  �ʥ����å��Ϥ��Τޤޡ�  �� */
	mov.l _log_inh_leave_int, r1 /* �������ϴؿ�				*/
	jsr  @r1
	 mov.l @r15+,r4 			 /* ������ֹ������			*/
#endif /* LOG_INH_LEAVE */

	/*
	 * ����ߥϥ�ɥ�и�����
	 *
	 *	�����/CPU�㳰�ͥ��ȥ����󥿤�ǥ�����Ȥ��������Υ���ƥ�
	 *	���Ȥ�Ƚ�ꤷ�ƥ����å��������ؤ��롥
	 *	�����ͥ�������γ���ߤ򥵥ݡ��Ȥ�����ϡ�ξ�Ԥδ֤˥����ͥ�
	 *	�������γ���ߤ������礬���롥�����ͥ�������γ���ߤ������ϡ�
	 *	�����ͥ�����γ���ߤ�Ʊ�ͤǤ��뤿�ᡤ�����/CPU�㳰�ͥ��ȥ���
	 *	�󥿤򻲾Ȥ��ơ������å��������ؤ��롥���Τ��ᡤ�����/CPU�㳰
	 *	�ͥ��ȥ����󥿤ȥ����å��������ؤ��ϥ����ͥ�������γ���ߤ���
	 *	���Ƥ⡤�Բ�ʬ�˹Ԥ�ɬ�פ����롥
	 */
_ret_int:
	movi20 #IIPM_DISALL,r2	/*  ������ߡʥ����ͥ��������ޤ�˶ػ�  */
	ldc    r2,sr
    /*
     *�������/CPU�㳰�ͥ��ȥ����󥿤�ǥ�����Ȥ���
     *������褬�󥿥�������ƥ����Ȥʤ餹���˥꥿����
     */
	stc    gbr, r7				 /* r7��my_p_pcb */
	mov.l  @(PCB_excnest_count, r7),r1
	dt     r1
	mov.l r1,@(PCB_excnest_count, r7)
	bf    _ret_int_1			 /* 32�ӥå�̿��ʤΤǡ��ٱ䥹���åȤ����֤Ǥ��ʤ� */

	mov.l  @r15,r15 			 /* ����褬�������ʤΤǥ����å����᤹	   */
	mov.l  @(PCB_reqflg, r7),r1	 /* reqflg�Υ����å� */
	tst    r1,r1				 /* 	reqflg��false�ʤ�ret_int_1��	   */
	bt	   _ret_int_1
	/*
	 * ����褬��������reqflg�����åȤ���Ƥ�����ν�����ʬ��
	 * ��ret_int_2��ʬ�����ƥǥ����ѥå����ʤ���礬����Τ�reqflg�ϥ��ꥢ���ʤ�
	 */
	movi20 #IIPM_LOCK,r0
#ifdef TOPPERS_LDC_IS_SLOT_ILLEGAL_INSTRUCTION
	ldc    r0,sr				 /* �����ͥ�������γ���ߤ����			  */
	bra   _ret_int_2
	 nop
#else	/* TOPPERS_LDC_IS_SLOT_ILLEGAL_INSTRUCTION */
	bra   _ret_int_2
	 ldc	r0,sr				  /* �����ͥ�������γ���ߤ����			  */
#endif	/* TOPPERS_LDC_IS_SLOT_ILLEGAL_INSTRUCTION */


	/*
	 *	����߽�������Υ꥿����
	 *	�����ǥ����ѥå���䥿�����㳰�����롼�����ƤӽФ�����
	 *	����ľ�ܡ�����߸��إ꥿���󤹤롣
	 *	�����������٤��쥸�������쥸�����Х󥯤˳�Ǽ����Ƥ�������
	 *	����_ret_int_r_return�Ȱۤʤ롣
	 */
_ret_int_1:
	/*
	 *	����߽�������Υ꥿����ˤ�ꡤCPU���å�������֤˰ܹԤ���褦
	 *	�������롥�����ͥ���٥ޥ����ϡ�RTE̿��ˤ�긵���ͤ���뤿�ᡤ
	 *	lock_flag��false�ˤ��Ƥ����Ф褤��lock_flag��false�ˤ���Τϡ�
	 *	CPU���å����֤Τޤ޳���ߥϥ�ɥ餫����ä������к��ˡ�
	 */
	mov    #0x0, r1
	stc    gbr, r7						/* r7��my_p_pcb */
	mov.l  r1,@(PCB_lock_flag,r7)

#ifdef USE_BANKED_REG
	resbank
#else	/*  USE_BANKED_REG  */
	lds.l  @r15+,pr
	lds.l  @r15+,macl
	lds.l  @r15+,mach
	movml.l @r15+,r7
#endif	/* USE_BANKED_REG */
	rte
	 nop

	.align 2
#ifdef LOG_INH_ENTER
_log_inh_enter_int:
	.long  _log_inh_enter
#endif /* LOG_INH_ENTER */
#ifdef LOG_INH_LEAVE
_log_inh_leave_int:
	.long  _log_inh_leave
#endif /* LOG_INH_LEAVE */

	/*
	 *	�����ؤϳ���ߥϥ�ɥ�νи���������ʬ�����Ƥ���
	 *	
	 *	����褬��������reqflg�����åȤ���Ƥ�����Τߤ����ˤ��롣
	 */
_ret_int_2:
	/*
	 *��CPU�㳰/����߼���ľ��˳���߶ػߤˤʤäƤ��ʤ����Ȥؤ��к�
	 *��������褬����ߡ�CPU�㳰�������������ݤ���Ƚ�̡�
	 *��
	 *��SH2A-DUAL�Ǥ�CPU�㳰/����߼���ľ��˳���߶ػߤˤʤäƤ��ʤ����ᡢ
	 *	�����A��������������̤γ����B�������ǽ�������롣
	 * �ʤ���ϥϡ��ɥ������Υ������ƥ�������򤱤褦���ʤ�����
	 *	����ߥϥ�ɥ�B��ǥ������ڤ��ؤ��򵯤����褦�ʥ����ӥ�������
	 *	��Ƥ֤ȳ����B�νи��������̤Υ������˥ǥ����ѥå����Ƥ��ޤ���
	 *	������2���鸵�Υ���������äƤ���ޤǡ������A�ν������٤�Ƥ�
	 *	�ޤ���
	 *	������ɤ����ᡢ�����/�㳰������������ޤȤ��vector_entry��
	 *	���������֤��������Υ��ɥ쥹�������ϰ���ʤ�ǥ����ѥå�
	 *	�����˥꥿���󤹤롥
	 */
	mov.l  @(SP_PC_OFFSET_INT,r15),r0	/* r0 <-�����å����Ѥޤ줿pc */
	mov.l  _vector_entry_start_ret, r1
	mov.l  _vector_entry_end_ret, r2
	cmp/hs r1, r0
	bf	   _ret_int_2_1
	cmp/hi r0, r2
	bt	   _ret_int_1

	/*
	 *	�ǥ����ѥå���⤷���ϥ������㳰�����θƤӽФ�
	 */
_ret_int_2_1:
	/*
	 *	�쥸�����Х󥯤���Ѥ�����ϥ�����å��쥸������
	 *	�����å��˳�Ǽ����
	 */
#ifdef USE_BANKED_REG
	resbank
	movml.l  r7, @-r15
	sts.l	 mach,@-r15
	sts.l	 macl,@-r15
	sts.l	 pr,@-r15
#endif /* USE_BANKED_REG */

	/*
	 *	�ǥ����ѥå���θƤӽФ�
	 *
	 *	�����ؤϡ�CPU�㳰�ϥ�ɥ�νи����������ʬ�����Ƥ��롥
	 *
	 *	�����Ǥϡ�����褬�������Ǥ��ꡤ�����å��ϡ������������å���
	 *	������å��쥸�����Τߤ���¸���줿���֤ˤʤäƤ��롥�ޤ���
	 *	�����ͥ�����γ���ߤ�ػߤ������֤ȤʤäƤ��롥
	 */
_ret_int_3:
	/*
	 *��reqflg�Υ��ꥢ
	 *��
	 *����������ã��������reqflg�򥯥ꥢ���Ƥ��ޤ��ȡ��嵭�γ����A
	 *���νи������ǥǥ����ѥå���ƤӽФ���ɬ�פʥ������Ǥ�ǥ���
	 *���ѥå��㤬�ƤӽФ���ʤ���
	 *���ʳ����B��reqflg�򥻥åȤ��ơ������A��reqflg���Ѳ����ʤ���
	 *�������
	 */
	mov    #0x0, r0
	stc    gbr, r7					/*  r7��my_p_pcb */
	mov.l  r0, @(PCB_reqflg, r7)	/*  reqflg��false  */

	/*
	 *	CPU���å����֤˰ܹԤ��롥�����ͥ�����γ���ߤϴ��˶ػߤ���
	 *	����Τǡ�lock_flag��saved_iipm�򹹿����롥saved_iipm�ϡ����
	 *	��γ����ͥ���٥ޥ����ʤ�����ɽ���ˤ����ꤹ�롥
	 *
	 *	���λ�����CPU���å����֤Ȥ���Τϡ�dispatcher��ʬ��������ȡ�
	 *	dispatch_call_texrtn��ƤӽФ����ˡ�CPU���å����֤ˤʤäƤ���
	 *	ɬ�פ����뤿��Ǥ��롥
	 */
	mov    #0x01,r1
	mov.l  r1,@(PCB_lock_flag,r7)	/* lock_flag��true */

	/*
	 * �����å������¸����Ƥ�����������IPM����Ф��ơ�saved_iipm��
	 *
	 *��������������ƥ����Ȥ����Τˡ�ñ��saved_iipm��0�Ȥ��ʤ�
	 *�����ʥ����å������¸����Ƥ���SR����虜�虜IPM����Ф��ˤΤϡ�
	 *���������ȯ�����Υ���������ƥ����Ȥ�chg_ipm��¹Ԥ���
	 *���������ͥ���٥ޥ�����������֤Ǥʤ����֤ǡ������/CPU�㳰��
	 *����ȯ��������������ã���������б����뤿��Ǥ��롣
	 */
	mov.l  @(SP_SR_OFFSET_INT,r15),r0
	and    #0xf0,r0		/* and #imm,r0̿���r0�Τ߻����ǽ  */
	mov.l  r0,@(PCB_saved_iipm,gbr)
			/* saved_iimp�������å�����Ѥޤ�Ƥ���SR��IPM  */

	/*
	 *	dspflg��false�Ǥ�����ȡ�p_runtsk��p_schedtsk��Ʊ�����ˤϡ�
	 *	�ǥ����ѥå���Ԥ�ʤ������Υ����å���ɬ�פʤΤϡ��������㳰��
	 *	���롼����θƽФ���ɬ�פʾ��ˡ��ǥ����ѥå���ɬ�פʤ��Ƥ⡤
	 *	reqflg��true�ˤ��뤿��Ǥ��롥
	 */
	mov.l  @(PCB_dspflg,r7),r3	  /* r3 <- dspflg					*/
	mov.l  @(PCB_p_runtsk,gbr),r0 /* r0 <- p_runtsk					*/
	tst    r3,r3
	bt	   _ret_int_r_1			/* dspflg��false�ʤ�ret_int_r_1�� 	*/
	mov.l  @(PCB_p_schedtsk,r7),r5 /* r5 <- p_schedtsk				*/
	cmp/eq r0,r5				/* runtsk �� schedtsk �����	 	*/
	bt	   _ret_int_r_1 		/* Ʊ���ʤ�ret_int_r_1��		 	*/
	/*
	 *	����
	 *	��r8-r14�˲ä��ơ�pr����ʣ���ƥ����å�����¸����뤬
	 *	��_ret_int_r¦���ɤ߽Ф��Ȥ��ˤ⡢���礵���Ƥ���Τ�����ʤ���
	 */
	movmu.l r8, @-r15			/*  r8-r14,pr�򥹥��å�����¸  	*/
	mov.l  r15,@(TCB_sp, r0)	/* �����������å���TCB����¸	  */
	mov.l  _ret_int_r_ret,r3
	bra    _dispatcher
	 mov.l	r3,@(TCB_pc, r0)	/* �¹ԺƳ����Ϥ�TCB����¸		  */

_ret_int_r:
	/*
	 *	����
	 *	��������ʬ�����Ƥ���Τ�_ret_int_3����ΤߤǤ��롣
	 *	��_ret_int_3¦��r8-r14�˲ä��ơ�pr�⥹���å�����¸���Ƥ��롣
	 */
	movmu.l @r15+,r8			/*  r8-r14,pr�򥹥��å���������  */
_ret_int_r_1:
	/*
	 *	�������㳰�����롼����ε�ư
	 *	ret_int_r �� dispatcher ����ƤӽФ���뤿�ᡤtcb�Υ��ɥ쥹��r0��
	 *	���äƤ��롥
	 *	�ʤ�������ߤνи��ǥ����������å���ȯ�����ʤ����ϥǥ����ѥå���
	 *	���̤餺�� ret_int ����ľ�� ret_int_1 ������
	 */
	/*  enatex�Υ����å�  */
	bld.b  #TCB_enatex_bit, @(TCB_enatex,r0)
	bf     _ret_int_r_return	/* enatex��false�ʤ�����ȯ�����إ꥿���� */

	/* texptn��0��̵����ipmflg��true�ʤ�С��������㳰�����롼����θƤӽФ� */
	mov.l  @(TCB_texptn,r0),r1	/* texptn������� */
	tst    r1,r1
	bt	   _ret_int_r_return	/* texptn��0�ʤ�����ȯ�����إ꥿����  */

_ret_int_r_check_ipmflg:
	stc gbr, r7						/*  r7��my_p_pcb  */
	mov.l @(PCB_ipmflg,r7),r1		/* ipmflg������� */
	tst    r1,r1
	bt	   _ret_int_r_return	/* ipmflg��false�ʤ�����ȯ�����إ꥿����  */

	mov.l  _dispatch_call_texrtn_ret,r2
	jsr/n  @r2					/* �������㳰�����롼����θƤӽФ� */

	/*  �����ȯ�����إ꥿����  */
_ret_int_r_return:
	mov    #0x0,r0					/* lock_flag��false�� */
	lds.l  @r15+,pr
	mov.l  r0, @(PCB_lock_flag,gbr)
	lds.l  @r15+,macl
	lds.l  @r15+,mach
	movml.l @r15+,r7
	rte
	 nop

	.align 2
_ret_int_r_ret:
	.long _ret_int_r
_dispatch_call_texrtn_ret:
	.long _dispatch_call_texrtn
_vector_entry_start_ret:
	.long __vector_entry_start
_vector_entry_end_ret:
	.long __vector_entry_end

/*
 *	����CPU�㳰��������
 *
 *  CPU�㳰�ϥ�ɥ�ϡ��󥿥�������ƥ����ȤǼ¹Ԥ��롥���Τ��ᡤCPU��
 *  ���ϥ�ɥ��ƤӽФ������󥿥�������ƥ����Ȥ����ؤ����꥿���󤷤�
 *  ������˸��Υ���ƥ����Ȥ��᤹�����Υ���ƥ����Ȥ��᤹����ˡ���
 *  ���å����ؤ��������Υ����������å��Υ����å��ݥ��󥿤��󥿥�������
 *  �ƥ������ѥ����å������¸���롥
 *  CPU�㳰������������ƥ����Ȥ�ȯ������reqflg �� true �ˤʤä����ˡ�
 *  _ret_exc_2 ��ʬ�����롥
 *	reqflg ������å��������˳���ߤ�ػߤ��ʤ��ȡ�reqflg ������å���
 *	�˵�ư���줿����ߥϥ�ɥ���ǥǥ����ѥå����׵ᤵ�줿���ˡ��ǥ�
 *	���ѥå�����ʤ���
 *	��
 *	��������̿��ξ���������Ϥ�2�Х��ȿʤ��ɬ�פ����뤬
 *	�б����Ƥ��ʤ�
 *	��
 *	CPU�㳰�װ����Ÿ�������롼�����r4,r5,r6,r7����¸����
 *	 r5 �� CPU�㳰�ϥ�ɥ��ֹ�
 *	 r6 �� CPU�㳰�ϥ�ɥ����Ƭ���ɥ쥹
 *	 r7 �� CPU�㳰ȯ������SR�Υ��ԡ�
 *	�ξ��֤Ǥ�������롣
 *	
 * (1) CPU�㳰ȯ�����Υ���ƥ������ѥ����å�
 *		  ----------------------
 *	0	 | CPU�㳰�ϥ�ɥ��ֹ�	|	<-- p_excinf��CPU�㳰�ϥ�ɥ�ΰ����ˡ�
 *		  ----------------------		_ret_exc_non_task�λ�����CPU�㳰ȯ�������󥿥�������ƥ����Ȥξ���
 *	1	 |		   PR			|	<-- _ret_exc_1/_ret_exc_2�λ���
 *		  ----------------------
 *	2	 |		  MACH			|
 *		  ----------------------
 *	3	 |		  MACL			|
 *		  ----------------------
 *	4	 |		   R0			|
 *		  ----------------------
 *	5	 |		   R1			|
 *		  ----------------------
 *	6	 |		   R2			|
 *		  ----------------------
 *	7	 |		   R3			|
 *		  ----------------------
 *	8	 |		   R4			|  <-- sp��_exception_entry�λ�����
 *		  ----------------------
 *	9	 |		   R5			|
 *		  ----------------------
 * 10	 |		   R6			|
 *		  ----------------------
 * 11	 |		   R7			|
 *		  ----------------------
 * 12	 |		   PC			|	<-- sp��CPU�㳰����ľ��λ�����
 *		  ----------------------
 * 13	 |		   SR			|
 *		  ----------------------
 *	
 * (2) ����ƥ������ڤ��ؤ�����󥿥�������ƥ������ѥ����å�
 *		  ----------------------
 *		 |	 CPU�㳰�ϥ�ɥ��	|��log_exc_enter��ƤӽФ�����
 *		 |	 ��Ƭ���ɥ쥹(r6)	|
 *		  ----------------------
 *		 |	   p_excinf(r4) 	|��log_exc_enter��ƤӽФ�����
 *		  ----------------------
 *		 | CPU�㳰�ϥ�ɥ��ֹ�	|��log_exc_leave��ƤӽФ�����
 *		  ----------------------
 *		 |	   saved_iipm		|  <-- sp��_ret_exc�λ�����
 *		  ----------------------
 *		 |	   lock_flag		|
 *		  ----------------------
 *		 |	   locspinid		|
 *		  ----------------------
 *		 | �����������å���sp	|�ʥ����å����ؤ򤷤�����
 *		  ----------------------
 */

/*
 *	_ret_exc_2�λ����ǡ������å��ݥ��󥿤��ͤ���
 *  �֥����å����Ѥޤ�Ƥ���CPU�㳰�����������ϡפޤǤΥ��ե��å�
 */
#define    SP_PC_OFFSET_EXC     (11 * 4)

	.text
	.global _exception_entry
_exception_entry:
	movml.l r3,@-r15 	/*	�Ĥ�Υ�����å��쥸�����򥹥��å����Ѥ�  */
	sts.l  mach,@-r15
	sts.l  macl,@-r15
	sts.l  pr,@-r15
	mov.l  r5,@-r15 			/* CPU�㳰�ϥ�ɥ��ֹ����¸  */
								/* �����/CPU�㳰�ͥ��ȥ����󥿤Υ����å� */
	stc    gbr, r3				/* r3��my_p_pcb */
	mov.l  @(PCB_excnest_count,r3), r1
	mov    r15, r4				 /* CPU�㳰�ϥ�ɥ�ؤΰ��� */
	tst    r1,r1				 /* �����ȯ�����Υ���ƥ����Ȥ�Ƚ��	 */
	add    #0x1,r1				 /* �����/CPU�㳰�ͥ��ȥ����󥿤򥤥󥯥���� */
    bf/s   _exception_entry_1    /* CPU�㳰ȯ�������󥿥�������ƥ����Ȥʤ饸���� */
	 mov.l r1, @(PCB_excnest_count,r3)
	mov.l @(PCB_istkpt,r3),r15	 /* �󥿥��������å����ڤ��ؤ�			 */
	mov.l  r4,@-r15 			 /* �����������å��ݥ��󥿤���¸ */
_exception_entry_1:
    /*
     * ���Υ��ԥ���å��������֡�CPU���å����֡�������֤򥹥��å�����¸
     */
	mov.l  @(PCB_locspnid, gbr), r0
	mov.l  @(PCB_lock_flag, r3), r1
	mov.l  @(PCB_saved_iipm,r3), r2
	mov.l  r0,@-r15
	mov.l  r1,@-r15
	mov.l  r2,@-r15

#ifdef LOG_EXC_LEAVE
	mov.l  r5,@-r15 			 /* CPU�㳰�ϥ�ɥ��ֹ����¸ */
#endif /* LOG_EXC_LEAVE */

#ifdef LOG_EXC_ENTER
	ldc    r7,sr				 /* ����ߵ���	*/
	mov.l _log_exc_enter_exc, r1 /* �������ϴؿ�  */
	mov.l  r4,@-r15 			 /* r4��¸��CPU�㳰�ϥ�ɥ�ΰ����� */
	mov    r5, r4				 /* ������CPU�㳰�ϥ�ɥ��ֹ��*/
	jsr   @r1
	 mov.l  r6,@-r15 			 /* r6��¸��CPU�㳰�ϥ�ɥ����Ƭ���ɥ쥹��*/

	mov.l @r15+, r6 			 /* r6����		  */
	jsr    @r6					 /* CPU�㳰�ϥ�ɥ�ƤӽФ�  */
	 mov.l @r15+, r4			 /* r4����		  */
#else /* LOG_EXC_ENTER */

#ifdef TOPPERS_LDC_IS_SLOT_ILLEGAL_INSTRUCTION
	ldc    r7,sr				 /* ����ߵ���	*/
	jsr    @r6					 /* CPU�㳰�ϥ�ɥ�ƤӽФ�  */
	 nop
#else	/* TOPPERS_LDC_IS_SLOT_ILLEGAL_INSTRUCTION */
	jsr    @r6					 /* CPU�㳰�ϥ�ɥ�ƤӽФ�  */
	 ldc	r7,sr				 /* ����ߵ���	*/
#endif	/* TOPPERS_LDC_IS_SLOT_ILLEGAL_INSTRUCTION */

#endif /* LOG_EXC_ENTER */

#ifdef LOG_EXC_LEAVE
	mov.l _log_exc_leave_exc, r1 /* �������ϴؿ�						*/
	jsr  @r1
	 mov.l @r15+, r4             /* ������CPU�㳰�ϥ�ɥ��ֹ�           */
#endif /* LOG_EXC_LEAVE */

	/*
	 * CPU�㳰�ϥ�ɥ�и�����
	 */
_ret_exc:
	/*
	 * �׸�Ƥ
	 * ��excnest�ι����ȥ����å��ڤ��ؤ����Բ�ʬ�˹Ԥ��ˤϡ�
	 * �������ͥ�������γ���ߤ�ػߤ���ɬ�פ����롣
	 * �����������ͥ�������γ���ߤ�̵ͭ�ǽ������Ѥ�롣
	 */
	movi20 #IIPM_DISALL, r0				/* ������߶ػ�	 */
	ldc    r0,sr
    /*
     * ���ԥ���å��������֡�CPU���å����֡�������֤򸵤ξ��֤��᤹
     */
	stc    gbr, r7						/* r7��my_p_pcb */
    mov.l  @r15+,r0						/* saved_iipm */
    mov.l  @r15+,r1						/* lock_flag  */
    mov.l  @r15+,r2						/* locspinid  */
	mov.l  r0, @(PCB_saved_iipm,gbr)
	mov.l  r1, @(PCB_lock_flag, r7)
	tst    r2,r2
	mov.l  r2, @(PCB_locspnid, r7)
	
	/*  locspinid=0�ʤ�С�force_unlock_spin(my_p_pdb)��ƤӽФ�  */
	bf     _ret_exc_after_force_unlock_spin
	mov.l  _force_unlock_spin_exc, r3
	jsr    @r3
	 stc   gbr, r4					/*  ������my_p_pdb  */
_ret_exc_after_force_unlock_spin:

    /*
     * ����ƥ������ڤ��ؤ�
	 * ���֥����å����Ѥޤ줿CPU�㳰�ϥ�ɥ��ֹ���ɤ����Ф��׽����ʥ�
	 * �����å��ݥ��󥿤Υ��󥯥���ȡˤϥ����å��ڤ��ؤ���Ǥʤ���
	 * ���Ǥ��ʤ����ᡢ�����Υ���ƥ�����Ƚ��塢2�ս�ǹԤäƤ��롣
	 * ���ʥ����å��ڤ��ؤ�ľ���_ret_exc_non_task��
     */
	/*
	 *	�׸�Ƥ
	 *	��������ȯ�����������ͥ�������γ���ߤ��˲����ʤ��褦������
	 */
    /*  ���׸�Ƥ���������顢�Բ�ʬ  */
	mov    r15,r2
    /*
     *�������/CPU�㳰�ͥ��ȥ����󥿤�ǥ�����Ȥ���
     *������褬�󥿥�������ƥ����Ȥʤ餹���˥꥿����
     */
	stc    gbr, r7					/* r7��my_p_pcb */
	mov.l  @(PCB_excnest_count,r7), r1
    dt     r1
    bf/s   _ret_exc_non_task
	 mov.l r1, @(PCB_excnest_count,r7)

	mov.l  @r2,r15			/* ����褬�������ʤΤǥ����å����᤹	  */
    /*  �׸�Ƥ�������ޤǡ��Բ�ʬ  */

	mov.l  @(PCB_reqflg,r7), r1	/* reqflg�Υ����å� */
	add    #4, r15
		/* �����å����Ѥޤ줿CPU�㳰�ϥ�ɥ��ֹ���ɤ����Ф� */
	
	/*
	 *��reqflg��true�ʤ�ret_exc_2��
	 *����ret_exc_2��ʬ�����ƥǥ����ѥå����ʤ���礬����Τ�reqflg��
	 *�������ꥢ���ʤ�
	 */
	tst    r1,r1
	bf	  _ret_exc_2


    /*
	 *���ǥ����ѥå����ƤФ��˥꥿���󤹤���
     */
_ret_exc_1:
	lds.l  @r15+,pr
	lds.l  @r15+,macl
	lds.l  @r15+,mach
	movml.l @r15+,r7
	rte
	 nop

	/*
	 *������褬�󥿥�������ƥ�����
	 *���������å����Ѥޤ�Ƥ���CPU�㳰�ϥ�ɥ��ֹ���ɤ����Ф���
	 *����_ret_exc_1��ʬ��
	 */
_ret_exc_non_task:
	bra    _ret_exc_1
	 add   #4, r15
	 	/* �����å����Ѥޤ줿CPU�㳰�ϥ�ɥ��ֹ���ɤ����Ф� */

	/*
	 *������褬����������ƥ����Ȥǡ�reqflg=true�ξ��
	 *���ʥǥ����ѥå���ޤ��ϥ������㳰�����롼����θƤӽФ���
	 *��
	 *������ߤξ���_ret_int_2�ˤȶ��̤ˤǤ��ʤ��Τϡ�
	 *���쥸�����Х󥯤����ꡢ�쥸��������Υ����ߥ󥰤��ۤʤ뤿�ᡣ
	 */
_ret_exc_2:
	/*
	 *������褬����ߡ�CPU�㳰�������������ݤ���Ƚ��
	 *	�ܤ�����ret_int_2�򻲾ȤΤ���
	 */
	mov.l  @(SP_PC_OFFSET_EXC,r15),r0	/* r0 <-�����å����Ѥޤ줿PC */
	mov.l  _vector_entry_start_exc, r1
	mov.l  _vector_entry_end_exc, r2
	cmp/hs r1, r0
	bf	   _ret_exc_2_1			/*  �ǥ����ѥå����ƤӽФ����  */
	cmp/hi r0, r2
	bt	   _ret_exc_1			/*  �ǥ����ѥå����ƤФ��˥꥿����  */

_ret_exc_2_1:
	bra    _ret_int_3			/*  ����ߤξ��ȶ��̤ν���  */
	 nop
	
	.align 2
_force_unlock_spin_exc:
	.long  _force_unlock_spin
_vector_entry_start_exc:
	.long __vector_entry_start
_vector_entry_end_exc:
	.long __vector_entry_end
#ifdef LOG_EXC_ENTER
_log_exc_enter_exc:
	.long _log_exc_enter
#endif /* LOG_EXC_ENTER */
#ifdef LOG_EXC_LEAVE
_log_exc_leave_exc:
	.long _log_exc_leave
#endif /* LOG_EXC_LEAVE */

/*
 *	̤��Ͽ�γ���ߥϥ�ɥ����������
 *	��������װ��������������r7,r6����¸����
 *	��r6�˳�����ֹ���Ǽ���ơ���������롣
 *�����ʲ��Υ쥸���������ǡ�_interrupt_entry��ʬ�����롣
 *����
 *�����쥸��������
 *��������r7������߼���ľ���SR�Υ��ԡ�
 *��������r6������ߥϥ�ɥ����Ƭ���ɥ쥹(_default_int_handler)
 *��������r5��������ֹ�
 *��������r4��_interrupt_entry
 *�����������ʳ���ߥϥ�ɥ餬��Ͽ����Ƥ�����ȶ��̤ν�����
 */
	.section .vector_entry,"xa"
	.align 2
	.global  _default_int_handler_entry
_default_int_handler_entry:
#ifndef USE_BANKED_REG
	mov.l r5,@-r15				   /*  ɬ�׺Ǿ��¤Υ쥸�����򥹥��å�������  */
	mov.l r4,@-r15
#endif /* USE_BANKED_REG */
	mov   r6,r5						/* ������ֹ� */
	movi20 #IIPM_DISALL,r6
	stc   sr,r7						/* SR����¸ */
	ldc   r6,sr						/* ����߶ػ� */
									/* ��ͭ������������� */
	mov.l _common_routine_default_int_handler,r4
									/* ����ߥϥ�ɥ����Ƭ���ɥ쥹 */
	mov.l _c_routine_default_int_handler,r6
	/*	��PC���Х��ɥ쥹�����ʤΤǡ��ٱ䥹���åȤˤ�������ʤ�����  */
	jmp   @r4
	 nop

	.align 2
_c_routine_default_int_handler:
	.long _default_int_handler
_common_routine_default_int_handler:
	.long  _interrupt_entry

/*
 *	̤��Ͽ��CPU�㳰�ϥ�ɥ����������
 *	��CPU�㳰�װ��������������r7,r6����¸����
 *	��r6�˥٥����ֹ���Ǽ���ơ���������롣
 *�����ʲ��Υ쥸���������ǡ�_exception_entry��ʬ�����롣
 *����
 *�����쥸��������
 *��������r7��CPU�㳰ȯ������SR�Υ��ԡ�
 *��������r6��CPU�㳰�ϥ�ɥ����Ƭ���ɥ쥹(_default_exc_handler)
 *��������r5���٥����ֹ�
 *��������r4��_exception_entry
 *������������CPU�㳰�ϥ�ɥ餬��Ͽ����Ƥ�����ȶ��̤ν�����
 */
	.section .vector_entry,"xa"
	.align 2
	.global  _default_exc_handler_entry
_default_exc_handler_entry:
		 /*  ɬ�׺Ǿ��¤Υ쥸�����򥹥��å�������  */
	mov.l r5,@-r15
	mov.l r4,@-r15
	mov   r6,r5							/* �٥����ֹ�򥳥ԡ�	*/
	movi20 #IIPM_DISALL,r6
	stc   sr,r7							/* SR����¸   */
	ldc	  r6,sr							/* ������߶ػ� */
										/* ��ͭCPU�㳰�������� */ 
	mov.l _common_routine_exc_default_exc_handler,r4
										/* CPU�㳰�ϥ�ɥ����Ƭ���ɥ쥹 */
	mov.l _c_routine_exc_default_exc_handler,r6
	/*	��PC���Х��ɥ쥹�����ʤΤǡ��ٱ䥹���åȤˤ�������ʤ�����  */
	jmp	  @r4
	 nop
		/*
		 *	ldc̿����ٱ䥹���åȤ����֤��ʤ��Τϡ�
		 *	�����Ƥ���쥸�������ʤ�����
		 */

	.align 2
_common_routine_exc_default_exc_handler: /* CPU�㳰���̤��������� */
	.long  _exception_entry
_c_routine_exc_default_exc_handler:		/* CPU�㳰�ϥ�ɥ����Ƭ���ɥ쥹 */
	.long  _default_exc_handler


/*
 *	���������Ԥ�
 */
	.text
	.align 2
	.global _sil_dly_nse
_sil_dly_nse:
	mov.l  _sil_dly_tim1, r1
	add    r1, r4
	cmp/pl r4
	bt	   _sil_dly_nse1
	rts/n
_sil_dly_nse1:
	mov.l  _sil_dly_tim2, r1
	add    r1, r4
	cmp/pl r4
	bt	   _sil_dly_nse1
	rts/n

	.align 2
_sil_dly_tim1:
	.long  -SIL_DLY_TIM1
_sil_dly_tim2:
	.long  -SIL_DLY_TIM2