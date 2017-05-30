$ 
$		�ѥ�2�Υ������ƥ������¸�ƥ�ץ졼�ȡ�SH2A-DUAL�ѡ�
$ 

$ 
$  ATT_ISR�ǻ��ѤǤ��������ֹ�Ȥ�����б��������ߥϥ�ɥ��ֹ�
$ 
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$ 
$  DEF_INT��DEF_EXC�ǻ��ѤǤ������ߥϥ�ɥ��ֹ桿CPU�㳰�ϥ�ɥ��ֹ�
$ 
$INHNO_DEFINH_VALID = INHNO_VALID$
$EXCNO_DEFEXC_VALID = EXCNO_VALID$

$ 
$  CFG_INT�ǻ��ѤǤ��������ֹ�ȳ����ͥ����
$ 
$INTNO_CFGINT_VALID = INTNO_VALID$
$INTPRI_CFGINT_VALID = { -1,-2,...,-15 }$

$ 
$  TSKINICTXB�ν�������������
$ 
$FUNCTION GENERATE_TSKINICTXB$
	$SPC${$TSK.TINIB_STKSZ[tskid]$, 
	((void *)((char_t *)($TSK.TINIB_STK[tskid]$)
	          + ($TSK.TINIB_STKSZ[tskid]$)))
	},
$END$


$ 
$  ɸ��ƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ 
$INCLUDE "kernel/kernel.tf"$


$ 
$  ������ֹ桤����ߥϥ�ɥ��ֹ桤CPU�㳰�ϥ�ɥ��ֹ���ϰ�
$  �����ֹ椬Ϣ³���Ƥ��ʤ���硢������ֹ��ޤࡣ

$ ���ʲ��ξ����������Ƥ��뤫�Υ��顼�����å�
$  ������0��3�ϥ������ȥ��åץ롼�����Ѥ�ͽ��
$  �������٥����ơ��֥�����������Թ�ǡ�EXCNO_RANGE��INTNO_RANGE��
$  ������Ϣ³���Ƥ��ʤ���С��ʤ�ʤ���
$ 
$IF TMIN_EXCNO != 4$
	$ERROR$ TMIN_EXCNO($+TMIN_EXCNO$) != 4 $END$
$END$
$IF (TMAX_EXCNO + 1) != TMIN_INTNO$
	$ERROR$ (TMAX_EXCNO($+TMAX_EXCNO$) + 1) != TMIN_INTNO($+TMIN_INTNO$) $END$
$END$

$EXCNO_RANGE = RANGE(4, TMIN_INTNO - 1)$
$INTNO_RANGE = RANGE(TMIN_INTNO, TMAX_INTNO)$
$INHNO_RANGE = INTNO_RANGE$


/*												$NL$$SPC$
 *  Target-dependent Definitions (SH2A-DUAL)	$NL$$SPC$
 */												$NL$$NL$

$ 
$  CFG_INT�Υ������ƥ������¸�Υ��顼�����å�
$ 
$ �����������ͥ���٤Υ��顼�����å�
$ 		��Ʊ�������ͥ���٤ˤʤ�٤�������ֹ���Ф��ơ��ۤʤ�����
$ 		��ͥ���٤���ꤷ�Ƥ��ʤ���������å����롣
$ 		��same_intpri_list�ϥ��åװ�¸����������롣
$ 		����-1�򥻥ѥ졼���Ȥ��롣��
$ 		��same_intpri_list����ϡ���ŪAPI�ΰ����Ȥ���Ϳ����줿ʸ�����
$ 		�����Ф��ʤ��Τǡ�����ʸ����ɬ�פʾ��ϡ�INT.INTNO[intno1]
$ 		���Τ褦�ʵ��Ҥ��Ѥ��ơ����Ф���
$ 

$intno_list = {}$
$FOREACH intno (same_intpri_list)$
	$IF (intno != -1)$
$       ���ѥ졼���ʳ��ΤȤ��ν���
		$IF (LENGTH(INT.INTPRI[intno]) != 0)$
			$intno_list = APPEND(intno_list, intno)$
		$END$

$       ���ѥ졼���ޤ���ã�����Ȥ��ν���
	$ELSE$
$       ����index���ϰ�0��10���ä˰�̣�Ϥʤ���
$       ����Ʊ�������ͥ���٤����ꤹ�٤�������ֹ���򥫥С��Ǥ���Ф褤��
		$FOREACH index ({ 0,1,...,10 })$
			$IF (LENGTH(intno_list) >= index + 2)$
				$intno1 = AT(intno_list, index)$
				$intno2 = AT(intno_list, index + 1)$
				$IF (INT.INTPRI[intno1] != INT.INTPRI[intno2])$
					$ERROR INT.TEXT_LINE[intno1]$:E_PAR:
						$FORMAT("CFG_INT:These intno's intpri must be same.\n")$
						$FORMAT("\t configuration file %s:(%d)\n",
							INT.TEXT_LINE[intno1], +INT.TEXT_LINE[intno1])$
						$FORMAT("\t\t intno:%s(%d), intpri:%s(%d)\n",
							INT.INTNO[intno1], +intno1,
							INT.INTPRI[intno1], +INT.INTPRI[intno1])$
						$FORMAT("\t configuration file %s:(%d)\n",
							INT.TEXT_LINE[intno2], +INT.TEXT_LINE[intno2])$
						$FORMAT("\t\t intno:%s(%d), intpri:%s(%d)\n",
							INT.INTNO[intno2], +intno2,
							INT.INTPRI[intno2], +INT.INTPRI[intno2])$
					$END$
				$END$
			$END$
		$END$

		$intno_list = {}$
	$END$
$END$


$ 
$  CFG_INT�Υ������ƥ������¸�Υ��顼�����å�
$ 
$ �����������°���Υ��顼�����å�
$ ��������������¸���ޤ��ϥ��åװ�¸���ǰʲ����ѿ����ꥹ�Ȥ�������롣
$ ������������TINTNO_NMI��NMI�γ�����ֹ�
$ ������������valid_irq_intatr_list��IRQ����ߤǻ��ѤǤ�������°��
$ ������������valid_nmi_intatr_list��NMI�ǻ��ѤǤ�������°��
$ 
$ 	�����°��������Ǥ����ͤϳ�����װ���˰ۤʤ�Τǡ�
$ 	���줾������å����Ƥ��롣�����¸���ǤޤȤ�ƥ����å��Ǥ��ʤ�����
$ 	���Τ��ᡢ���ĤΥ��顼�ǡ�ʣ���ĤΥ��顼��å�������ɽ������뤬
$ 	�ߤ�����ʤ���
$ 

$FOREACH intno (INT.ORDER_LIST)$
	$intno0 = INT.INTNO[intno]$
$ 		intno��Ʊ�ͤ�intno0����Ƥ���Τϡ�ʸ����°������Ф�����
	$intno_local = intno & 0x0000ffff$
	$intatr0 = INT.INTATR[intno]$
	
	$IF (TMIN_INTNO_IRQ <= intno_local) && (intno_local <= TMAX_INTNO_IRQ)$
$ 											IRQ����ߤξ��
$ 			TA_ENAINT�λ����̵�뤹�롣
		$intatr1 = intatr0 & ~TA_ENAINT$
		$IF LENGTH(FIND(valid_irq_intatr_list, intatr1)) == 0$
			$ERROR INT.TEXT_LINE[intno]$E_RSATR:
				$FORMAT(_("illegal %1% `%2%\' of intno `%3%\' in %4%"),
					"intatr", intatr0, intno0, "CFG_INT")$
			$END$
		$END$
	$ELSE$
		$IF (intno_local == TINTNO_NMI)$
$ 											NMI�ξ��
$ 		����
$ 			NMI��虜�虜����ߵ��Ĥ��Ƥ���Τϴְ㤤�β�ǽ����
$ 			�⤤�Τǡ�TA_ENAINT�����ꤵ��Ƥ�����⥨�顼�����ˤ��롣
			$IF LENGTH(FIND(valid_nmi_intatr_list, intatr0)) == 0$
				$ERROR INT.TEXT_LINE[intno]$E_RSATR:
					$FORMAT(_("illegal %1% `%2%\' of intno `%3%\' in %4%"),
						"intatr", intatr0, intno0, "CFG_INT")$
				$END$
			$END$
		$ELSE$
$ 											IRQ, NMI�ʳ��γ���ߤξ��
			$IF (intatr0 & ~TA_ENAINT) != 0$
				$ERROR INT.TEXT_LINE[intno]$E_RSATR:
					$FORMAT(_("illegal %1% `%2%\' of intno `%3%\' in %4%"),
						"intatr", intatr0, intno0, "CFG_INT")$
				$END$
			$END$
		$END$
	$END$
$END$


/***************************************************************$NL$$SPC$
 *																$NL$$SPC$
 *  �������åȰ�¸���ĥ��ץꥱ��������¸�ν�����SH2A-DUAL��	$NL$$SPC$
 *																$NL$$SPC$
 *	���Υե�����ϥ���ե�����졼���ˤ�꼫ư��������Ƥ��롣	$NL$$SPC$
 *	����������ϥƥ�ץ졼�ȥե�����������뤳�ȡ�			$NL$$SPC$
 **************************************************************/$NL$

$ 
$  �����ͥ���٥ơ��֥�
$ 
const uint8_t _kernel_int_iipm_tbl[TNUM_PRCID][TNUM_INT] = {	$NL$
$JOINEACH prcid {1,TNUM_PRCID} ", \n"$
	$TAB${														$NL$
	$upper_word = prcid << 16$
	$JOINEACH local_intno INTNO_RANGE ", \n"$
		$intno = upper_word | local_intno$
		$IF LENGTH(INT.INTNO[intno])$
			$intmask = (-INT.INTPRI[intno])$
		$ELSE$
$			NOT_CFG_INT_BIT�ϡ������ͥ���٤����ꤵ��Ƥ��ʤ����Ȥ򼨤���
			$intmask = NOT_CFG_INT_BIT$
		$END$
		$TAB$$FORMAT("UINT8_C(0x%02x) /* 0x%08x */", +intmask, +intno)$
	$END$														$NL$
	$TAB$}														$NL$
$END$
};																$NL$$NL$

$ 
$  �٥����ơ��֥롦���������ơ��֥�
$ 

$JOINEACH prcid RANGE(1, TNUM_PRCID) "\n"$
	extern const FP _kernel_vectors$prcid$[];
$END$
$NL$$NL$


const FP* const _kernel_p_vectors_table[TNUM_PRCID] = {$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
	$TAB$_kernel_vectors$prcid$
$END$
$NL$};$NL$


$ 
$  ������֥顦�ե�����
$ 
$FILE "kernel_cfg_asm.S"$

#define _start		__kernel_start		$NL$

/***************************************************************$NL$$SPC$
 *																$NL$$SPC$
 *  �������åȰ�¸���ĥ��ץꥱ��������¸�ν�����SH2A-DUAL��	$NL$$SPC$
 *																$NL$$SPC$
 *	���Υե�����ϥ���ե�����졼���ˤ�꼫ư��������Ƥ��롣	$NL$$SPC$
 *	����������ϥƥ�ץ졼�ȥե�����������뤳�ȡ�			$NL$$SPC$
 **************************************************************/$NL$

$ 
$  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ�ν���������������
$ 
/*															$NL$$SPC$
 *  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ����������				$NL$$SPC$
 *															$NL$$SPC$
 *�����쥸��������											$NL$$SPC$
 *��������r7������߼���ľ�塿CPU�㳰ȯ������SR�Υ��ԡ�		$NL$$SPC$
 *��������r6������ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ����Ƭ���ɥ쥹	$NL$$SPC$
 *��������r5������ߡ�CPU�㳰�ϥ�ɥ��ֹ�					$NL$$SPC$
 *��������r4��_kernel_interrupt_entry��_kernel_exception_entry	$NL$$SPC$
 *			��prc_support.S��Ǥ�ʬ�����					$NL$$SPC$
 *															$NL$$SPC$
 *	����ߤ�CPU�㳰�������									$NL$$SPC$
 *	������CPU�㳰�ϥ�ɥ�˰�����Ϳ����						$NL$$SPC$
 *	������CPU�㳰�Ǥϡ��㳰ȯ������IPM��Ʊ���ͤ�
 										����ߤ���Ĥ���	$NL$$SPC$
 *		��CPU�㳰�ˤ�ꡢIPM���Ѳ������ʤ���				$NL$$SPC$
 *															$NL$$SPC$
 *	����������ߥϥ�ɥ�ξ��								$NL$$SPC$
 *	����  	����߼��ջ��˥ϡ��ɥ�������IPM�����ꤹ��		$NL$$SPC$
 *	����  	����ߵ��ĤˤϤ���IPM���ͤ��Ѥ���				$NL$$SPC$
 *	������CPU�㳰�ϥ�ɥ�ξ��								$NL$$SPC$
 *	����  	CPU�㳰���ջ���IPM���ͤ��Ѳ����ʤ�				$NL$$SPC$
 *	����  	����ߵ��Ĥˤ�CPU�㳰ȯ������IPM���ͤ��Ѥ���	$NL$$SPC$
 */															$NL$

$INHNO_VALID_LOCAL = INTNO_VALID_LOCAL$
$FOREACH prcid RANGE(1, TNUM_PRCID)$
	$upper_word = prcid << 16$
/*															$NL$$SPC$
 *  �ץ��å�$prcid$�γ���ߥϥ�ɥ����������				$NL$$SPC$
 */															$NL$

$ �׸�Ƥ����������������
$TAB$	.section .vector_entry,"xa"							$NL$
$FOREACH local_inhno INHNO_VALID_LOCAL$
	$inhno = upper_word | local_inhno$
	$IF LENGTH(INH.INHNO[inhno])$
$ 
$ ����ߥϥ�ɥ����Ͽ��������
$ 
$NL$$TAB$
$ 	kernel_cfg.c���const INHINIB __kernel_inhinib_table[TNUM_INHNO]��
$ 	���Υ�٥�򻲾Ȥ��뤿�ᡢ�����Х륹�����פˤ���ɬ�פ����롣

	$label1 = CONCAT("__kernel_", INH.INTHDR[inhno])$
	$label2 = CONCAT("_", INH.INHNO[inhno])$
	$label  = CONCAT(label1, label2)$

	.global $label$  										$NL$$TAB$
	.align 2                       							$NL$
$label$:													$NL$
#ifndef USE_BANKED_REG    									$NL$$TAB$
	$TAB$ /*  ɬ�׺Ǿ��¤Υ쥸�����򥹥��å�������  */ 		$NL$$TAB$
	mov.l r7,@-r15 											$NL$$TAB$
	mov.l r6,@-r15											$NL$$TAB$
	mov.l r5,@-r15											$NL$$TAB$
	mov.l r4,@-r15											$NL$
#endif /* USE_BANKED_REG */   								$NL$$TAB$
	stc   sr,r7							/* SR����¸ */		$NL$$TAB$
	mov.l _iipm_disall_$label$,r6							$NL$$TAB$
	ldc	  r6,sr     					/* ����߶ػ� */	$NL$
					$TAB$$TAB$ /* ��ͭ������������� */    	$NL$$TAB$
	mov.l _common_routine_$label$,r4						$NL$
					$TAB$$TAB$ /* ����ߥϥ�ɥ����Ƭ���ɥ쥹 */ $NL$$TAB$
	mov.l _c_routine_$label$,r6     						$NL$$TAB$
	mov.l _inhno_$label$,r5				/* ������ֹ� */ 	$NL$$TAB$
	jmp	  @r4												$NL$$TAB$$SPC$
	 nop													$NL$$NL$$TAB$

	.align 2												$NL$
			$TAB$$TAB$ /* ����߶ػ��ѥޥ��� */ 			$NL$
_iipm_disall_$label$:										$NL$
			$TAB$$TAB$ /* ipm�ʳ��ΥӥåȤϥ�����ɤ� */ 	$NL$$TAB$
	.long  __kernel_iipm_disall								$NL$
_c_routine_$label$:
			/* ����ߥϥ�ɥ����Ƭ���ɥ쥹 */				$NL$$TAB$
	.long  _$INH.INTHDR[inhno]$         					$NL$$TAB$
		$TAB$ /* cpu_support.S���ʬ���襢�ɥ쥹 */			$NL$
_common_routine_$label$: 									$NL$$TAB$
	.long  __kernel_interrupt_entry							$NL$
_inhno_$label$:     					/* ������ֹ�	*/	$NL$$TAB$
	.long  $inhno$ 											$NL$$NL$
	$ELSE$
$ 
$ 	����ߥϥ�ɥ����Ͽ���ʤ����
$      r6�˳�����ֹ���Ǽ���ơ�cpu_support.S���
$      _default_int_handler_entry��ʬ�����롣

	$label  = CONCAT("__kernel_default_int_handler_entry_", inhno)$
															$NL$$TAB$
	.align 2                       							$NL$
$label$:													$NL$
#ifndef USE_BANKED_REG    									$NL$$TAB$
	$TAB$ /*  ɬ�׺Ǿ��¤Υ쥸�����򥹥��å�������  */ 		$NL$$TAB$
	mov.l r7,@-r15 											$NL$$TAB$
	mov.l r6,@-r15											$NL$
#endif /* USE_BANKED_REG */   								$NL$$TAB$
	$TAB$			/* cpu_support.S���ʬ���襢�ɥ쥹	*/ 	$NL$$TAB$
	mov.l _default_int_handler_entry_asm_$label$,r7 		$NL$$TAB$
	mov.l _inhno_$label$,r6				/* ������ֹ� */	$NL$$TAB$
	jmp	  @r7                        						$NL$$TAB$$SPC$
	 nop						 	 						$NL$$NL$$TAB$

	.align 2						 						$NL$$TAB$$TAB$
					/* cpu_support.S���ʬ���襢�ɥ쥹	*/ 	$NL$
_default_int_handler_entry_asm_$label$:						$NL$$TAB$
	.long  __kernel_default_int_handler_entry				$NL$
_inhno_$label$:                     /* ������ֹ� */ 		$NL$$TAB$
	.long  $inhno$ 											$NL$
	$END$
$END$

/*															$NL$$SPC$
 *  �ץ��å�$prcid$��CPU�㳰�ϥ�ɥ�ν���������			$NL$$SPC$
 */															$NL$$NL$
	.section .vector_entry,"xa"  							$NL$
$ �׸�Ƥ����������������
$FOREACH local_excno EXCNO_VALID_LOCAL$
	$excno = upper_word | local_excno$
	$IF LENGTH(EXC.EXCNO[excno])$
$ 
$ CPU�㳰�ϥ�ɥ����Ͽ��������
$ 
	$label1 = CONCAT("__kernel_", EXC.EXCHDR[excno])$
	$label2 = CONCAT("_", EXC.EXCNO[excno])$
	$label  = CONCAT(label1, label2)$
															$NL$$TAB$
	.align 2                       							$NL$
$label$:													$NL$$TAB$
	$TAB$ /*  ɬ�׺Ǿ��¤Υ쥸�����򥹥��å�������  */ 		$NL$$TAB$
	mov.l r7,@-r15 											$NL$$TAB$
	mov.l r6,@-r15											$NL$$TAB$
	mov.l r5,@-r15											$NL$$TAB$
	mov.l r4,@-r15											$NL$$TAB$
	stc   sr,r7								/* SR����¸ */	$NL$$TAB$
	mov.l _iipm_disall_$label$,r6							$NL$$TAB$
	ldc	  r6,sr								/* ������߶ػ� */ $NL$
			$TAB$$TAB$ /* ��ͭCPU�㳰�������� */ 			$NL$$TAB$
	mov.l _common_routine_$label$,r4 						$NL$
			$TAB$$TAB$ /* �٥����ֹ� */    					$NL$$TAB$
	mov.l _vectorno_$label$,r5								$NL$
			$TAB$$TAB$ /* CPU�㳰�ϥ�ɥ����Ƭ���ɥ쥹 */ 	$NL$$TAB$
	mov.l _c_routine_$label$,r6								$NL$$TAB$
	jmp	  @r4												$NL$$TAB$$SPC$
	 nop													$NL$$TAB$

	.align 2												$NL$
_iipm_disall_$label$:	/* ����߶ػ��ѥޥ��� */ 			$NL$
			$TAB$$TAB$ /* ipm�ʳ��ΥӥåȤϥ�����ɤ� */ 	$NL$$TAB$
	.long  __kernel_iipm_disall								$NL$
			$TAB$$TAB$ /* CPU�㳰�ϥ�ɥ����Ƭ���ɥ쥹 */ 	$NL$
_c_routine_$label$:											$NL$$TAB$
	.long  _$EXC.EXCHDR[excno]$         					$NL$
_vectorno_$label$:		/* �٥����ֹ� */ 					$NL$$TAB$
	.long  $excno$                      					$NL$
			$TAB$$TAB$ /* cpu_support.S���ʬ���襢�ɥ쥹 */ $NL$
_common_routine_$label$:									$NL$$TAB$
	.long  __kernel_exception_entry        					$NL$$NL$
	$ELSE$
$ 
$ CPU�㳰�ϥ�ɥ����Ͽ���ʤ����
$      r6�˥٥����ֹ���Ǽ���ơ�cpu_support.S���
$      _default_exception_handler_entry��ʬ�����롣
$ 

	$label  = CONCAT("__kernel_exc_entry_", excno)$
															$NL$$TAB$
	.align 2                           						$NL$
$label$:													$NL$$TAB$
	$TAB$ /*  ɬ�׺Ǿ��¤Υ쥸�����򥹥��å�������  */ 		$NL$$TAB$
	mov.l r7,@-r15 			           						$NL$$TAB$
	mov.l r6,@-r15											$NL$$TAB$
	$TAB$	/* cpu_support.S���ʬ���襢�ɥ쥹 */			$NL$$TAB$
	mov.l _default_exc_handler_entry_asm_$label$,r7			$NL$
			$TAB$$TAB$ /* �٥����ֹ� */    					$NL$$TAB$
	mov.l _vectorno_$label$,r6       						$NL$$TAB$
	jmp	  @r7                        						$NL$$TAB$$SPC$
	 nop													$NL$$TAB$

	.align 2						 						$NL$$TAB$
		 /* cpu_support.S���ʬ���襢�ɥ쥹 */ 				$NL$
_default_exc_handler_entry_asm_$label$:    					$NL$$TAB$
	.long  __kernel_default_exc_handler_entry				$NL$
_vectorno_$label$:		/* �٥����ֹ� */ 					$NL$$TAB$
	.long  $excno$                      					$NL$$NL$

	$END$
$END$

$END$
$ �ץ��å��ֹ�Υ롼�ס������ޤ�
$  �ʳ���ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ�ν�����������������

$ 
$ �٥����ơ��֥������
$  ��������SH7205��SH7265��2����Τߤ��θ���Ƥ��롣
$  �����塢�٥����ơ��֥�ι�¤���ޤä����ۤʤ���åפ����줿����
$  ����������ʬ����åװ�¸���˰�ư���롣

$FOREACH prcid RANGE(1, TNUM_PRCID)$
	$upper_word = prcid << 16$

/*															$NL$$SPC$
 *  �ץ��å�$prcid$�Υ٥����ơ��֥�						$NL$$SPC$
 */															$NL$$NL$$TAB$
	.section .vector										$NL$$TAB$
	.global __kernel_vectors$prcid$							$NL$$NL$
	
__kernel_vectors$prcid$:									$NL$$TAB$
	.long	_start		/* 0���ѥ����ꥻ�å�(PC) */		$NL$$TAB$
	.long	0     		/* 1��������������������(SP) */		$NL$$TAB$
	.long	_start		/* 2���ޥ˥奢��ꥻ�å�(PC) */		$NL$$TAB$
	.long	0     		/* 3��������������������(SP) */		$NL$$NL$$TAB$
	/* CPU exception */										$NL$

$FOREACH local_vectorno RANGE(4, TMAX_INHNO)$
	$IF LENGTH(FIND(EXCNO_VALID_LOCAL, local_vectorno))$
$ 
$ CPU�㳰�ξ��
$ 
		$excno = upper_word | local_vectorno$
		$IF LENGTH(EXC.EXCNO[excno])$
$ 
$ CPU�㳰�ϥ�ɥ����Ͽ��������
$ 
			$TAB$.long __kernel_$EXC.EXCHDR[excno]$_$EXC.EXCNO[excno]$
		$ELSE$
$ 
$ CPU�㳰�ϥ�ɥ����Ͽ���ʤ����
$ 
			$TAB$.long __kernel_exc_entry_$excno$
		$END$
		$FORMAT(" /* 0x%x(%d) */\n", +excno, +excno)$
	$ELSE$

	$IF LENGTH(FIND(INHNO_VALID_LOCAL, local_vectorno))$
$ 
$ ����ߤξ��
$ 
		$inhno = upper_word | local_vectorno$
		$IF LENGTH(INH.INHNO[inhno])$
$ 
$ ����ߥϥ�ɥ����Ͽ��������
$ 
			$TAB$.long __kernel_$INH.INTHDR[inhno]$_$INH.INHNO[inhno]$
		$ELSE$
$ 
$ ����ߥϥ�ɥ����Ͽ���ʤ����
$ 
			$TAB$.long __kernel_default_int_handler_entry_$inhno$
		$END$
		$FORMAT(" /* 0x%x(%d) */\n", +inhno, +inhno)$
	$ELSE$
$ 
$ �����ƥ�ͽ����㳰�٥�����CPU�㳰�Ǥ����ߤǤ�ʤ���
$ 
		$vectorno = upper_word | local_vectorno$
		$FORMAT("\t .long _ext_ker /* 0x%x(%d) */\n", +vectorno, +vectorno)$

$ IF(�����)��END
	$END$
$ IF(CPU�㳰�ϥ�ɥ�)��END
	$END$

$ FOREACH local_vectorno��END
$END$

$END$
$ �ץ��å��ֹ�Υ롼�ס������ޤ�
$ ���ʥ٥����ơ��֥��������

