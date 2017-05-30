$ 
$		�������ƥ������¸�ƥ�ץ졼�ȡ�SH4A�ѡ�
$ 

$ 
$  �������å����¸���˴ޤޤ��ɸ��γ���ߴ�����ǽ�ν�����������Ѥ��ʤ�
$ 
$OMIT_INITIALIZE_EXCEPTION = 1$

$  ������ֹ桤�����ߥϥ�ɥ��ֹ�Υޥ���
$ 
$INTNO_MASK = 0x0000FFFF$
$INHNO_MASK = INTNO_MASK$

$EXCNO_RANGE = { 0,0x20,...,0x820 }$

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
$  ������
$ 
$TA_POSEDGE = TA_EDGE$
$TA_NEGEDGE = 0x04$

$ 
$  �����°����Υ������åȰ�¸���Ѥ���ӥå�
$ 
$  TARGET_INTATR = TA_NEGEDGE$
$ 
$  �������å�����γ����°���ʥץ��å��ֹ��
$ 
$TARGET_INTATR = 0xff0000$



$ 
$  ɸ��ƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ 
$INCLUDE "kernel/kernel.tf"$

/*$NL$
$SPC$*  Target-dependent Definitions (SH34)$NL$
$SPC$*/$NL$
$NL$


$ 
$  �����ͥ���٥ơ��֥������ɽ����
$ 
const uint32_t _kernel_int_iipm_tbl[TNUM_INT] = {$NL$
$FOREACH intno INTNO_RANGE$
	$IF LENGTH(INT.INTNO[intno])$
		$intmask = 0x40000000 | (-INT.INTPRI[intno] << 4)$
	$ELSE$
$		// LSB��1�ˤ��Ƥ���Τϡ������°�������ꤵ��Ƥ��ʤ����Ȥ�Ƚ
$		// �̤��뤿��Ǥ��롥
		$intmask = 0x400000F0 | 0x01 $
	$END$
	$TAB$$FORMAT("UINT32_C(0x%08x), /* 0x%03x */", intmask, +intno)$$NL$
$END$
$NL$};$NL$
$NL$

$ 
$  ����ߥϥ�ɥ�ơ��֥�
$ 
const FP _kernel_inh_tbl[TNUM_INH] = {$NL$
$FOREACH intno INTNO_RANGE$
	$IF LENGTH(INT.INTNO[intno])$
		$FOREACH inhno INHNO_RANGE$
			$IF (((inhno & 0x0000ffff) == intno) &&(LENGTH(INH.INHNO[inhno])))$
				$TAB$(FP)($INH.INTHDR[inhno]$),
			$END$
		$END$
	$ELSE$
		$TAB$(FP)(_kernel_default_int_handler),
	$END$
	$SPC$$FORMAT("/* 0x%03x */", +intno)$$NL$
$END$
$NL$};$NL$
$NL$

$ 
$  �㳰�ϥ�ɥ�ơ��֥�
$ 
$FOREACH prcid RANGE(1, TNUM_PRCID)$

const FP _kernel_prc$prcid$_exch_table[] = {$NL$
$FOREACH excno EXCNO_RANGE$
    $number = excno|(prcid<<16)$
	$IF LENGTH(EXC.EXCNO[number])$
		$TAB$(FP)($EXC.EXCHDR[number]$),
	$ELSE$
		$TAB$(FP)(_kernel_default_exc_handler),
	$END$
	$SPC$$FORMAT("/* 0x%03x */", +excno)$$NL$
$END$
$NL$};$NL$
$NL$

$END$

$ 
$  �㳰�ϥ�ɥ饢�������ơ��֥�
$ 
const FP* const _kernel_p_exch_table[TNUM_PRCID] = {$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
	$TAB$_kernel_prc$prcid$_exch_table
$END$
$NL$};$NL$
$NL$