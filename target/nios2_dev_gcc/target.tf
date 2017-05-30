$ 
$     �ѥ�2�Υ������åȰ�¸�ƥ�ץ졼�ȡ�Nios2_Dev_1s40�ѡ�
$ 

$ 
$ �ץ����å����Ф������
$ 

$ 
$ ͭ����CPU�㳰�ϥ�ɥ��ֹ�
$ 
$EXCNO_VALID = { 
	0x10000,0x10001,0x10002,0x10003,0x10004,0x10005,0x10009,0x1000a,0x100c,0x100d,0x10010,0x10011; 
	0x20000,0x20001,0x20002,0x20003,0x20004,0x20005,0x20009,0x2000a,0x200c,0x200d,0x20010,0x20011; 
	0x30000,0x30001,0x30002,0x30003,0x30004,0x30005,0x30009,0x3000a,0x300c,0x300d,0x30010,0x30011; 
	0x40000,0x40001,0x40002,0x40003,0x40004,0x40005,0x40009,0x4000a,0x400c,0x400d,0x40010,0x40011
}$

$ 
$  ͭ���ʳ�����ֹ桤����ߥϥ�ɥ��ֹ�
$ 
$INTNO_VALID = { 
	0x10000,0x10001,...,0x1001f;
	0x20000,0x20001,...,0x2001f;
	0x30000,0x30001,...,0x3001f;
	0x40000,0x40001,...,0x4001f
}$

$INHNO_VALID = INTNO_VALID$

$ �������Х륿���޻��Υ����।�٥���ѥǡ����Υ�����������
$PRC_SECTION_TEVT[0] = ""$

$ 
$ �ץ����å�1�˴ؤ������
$ 
$ PCB�Υ�����������
$PRC_SECTION_PCB[1]  = "__attribute__((section(\"._kernel_prc1s_pcb\"),nocommon))"$
$ �󥿥�������ƥ������ѥ����å��Υ�����������
$PRC_SECTION_ISTACK[1]  = "__attribute__((section(\"._kernel_prc1p_istack\"),nocommon))"$
$ �����।�٥�ȴ�Ϣ�ǡ����Υ�����������
$PRC_SECTION_TEVT[1] = "__attribute__((section(\"._kernel_prc1s_tevt\"),nocommon))"$

$ �������åȰ�¸�����
$PRC_SECTION_NCCB[1] = "__attribute__((section(\"._kernel_prc1p_nccb\"),nocommon))"$


$ 
$ �ץ����å�2�˴ؤ������
$ 
$PRC_SECTION_PCB[2] = "__attribute__((section(\"._kernel_prc2s_pcb\"),nocommon))"$
$PRC_SECTION_ISTACK[2]  = "__attribute__((section(\"._kernel_prc2p_istack\"),nocommon))"$
$PRC_SECTION_TEVT[2] = "__attribute__((section(\"._kernel_prc2s_tevt\"),nocommon))"$
$PRC_SECTION_NCCB[2] = "__attribute__((section(\"._kernel_prc2p_nccb\"),nocommon))"$

$ 
$ �ץ����å�3�˴ؤ������
$ 
$PRC_SECTION_PCB[3] = "__attribute__((section(\"._kernel_prc3s_pcb\"),nocommon))"$
$PRC_SECTION_ISTACK[3]  = "__attribute__((section(\"._kernel_prc3p_istack\"),nocommon))"$
$PRC_SECTION_TEVT[3] = "__attribute__((section(\"._kernel_prc3s_tevt\"),nocommon))"$
$PRC_SECTION_NCCB[3] = "__attribute__((section(\"._kernel_prc3p_nccb\"),nocommon))"$

$ 
$ �ץ����å�4�˴ؤ������
$ 
$PRC_SECTION_PCB[4] = "__attribute__((section(\"._kernel_prc4s_pcb\"),nocommon))"$
$PRC_SECTION_ISTACK[4]  = "__attribute__((section(\"._kernel_prc4p_istack\"),nocommon))"$
$PRC_SECTION_TEVT[4] = "__attribute__((section(\"._kernel_prc4s_tevt\"),nocommon))"$
$PRC_SECTION_NCCB[4] = "__attribute__((section(\"._kernel_prc4p_nccb\"),nocommon))"$

$ 
$  ���֥������ȴ�Ϣ�Υ�������������ʥץ����å���
$ 

$ 
$  PCB�����������
$ 
$FUNCTION GENERATE_PCB$
	PCB _kernel_prc$ARGV[1]$_pcb $PRC_SECTION_PCB[ARGV[1]]$;$NL$
$END$

$ 
$  ISTACK�����������
$ 
$FUNCTION GENERATE_ISTACK$
	static STK_T					_kernel_prc$ARGV[1]$_istack[COUNT_STK_T(DEFAULT_PRC$ARGV[1]$_ISTKSZ)] $PRC_SECTION_ISTACK[ARGV[1]]$;$NL$
$END$

$ 
$  ISTACK_ICS�����������
$ 
$FUNCTION GENERATE_ISTACK_ICS$
	static STK_T				_kernel_prc$ARGV[1]$_istack[COUNT_STK_T($ICS.ISTKSZ[ARGV[2]]$)] $PRC_SECTION_ISTACK[ARGV[1]]$;$NL$
$END$

$ 
$  TMEVTN_HEAP�����������
$ 
$FUNCTION GENERATE_TMEVT_HEAP$
	TMEVTN   _kernel_prc$ARGV[1]$_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID] $PRC_SECTION_TEVT[ARGV[1]]$;$NL$
$END$

$ 
$  �������Х륿���������ǤΥ����।�٥�ȥҡ��פ����������
$ 
$FUNCTION GENERATE_TMEVT_HEAP_SYSTIM_GLOBAL$
	TMEVTN   _kernel_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID] $PRC_SECTION_TEVT[0]$;$NL$
$END$

$ 
$  TEVTCB�����������
$ 
$FUNCTION GENERATE_TEVTCB$
	TEVTCB   _kernel_prc$ARGV[1]$_tevtcb $PRC_SECTION_TEVT[ARGV[1]]$;$NL$
$END$

$ 
$  �������Х륿���������ǤΥ����।�٥�ȥ���ȥ�����֥��å������������
$ 
$FUNCTION GENERATE_TEVTCB_SYSTIM_GLOBAL$
	TEVTCB   _kernel_tevtcb $PRC_SECTION_TEVT[0]$;$NL$
$END$


$ 
$  ���饹���Ф������
$ 

$ 
$  ���饹��
$ 
$NUM_CLASS = 9$

$ 
$ ���饹1�˴ؤ������
$ 

$  ������դ��ץ����å�(ID����)
$CLASS_AFFINITY_INI[1] = 1$

$  �ޥ����졼������ǽ�ʥץ����å��Υޥ�������
$CLASS_AFFINITY_MASK[1] = 0x0000000f$

$  ���֥������ȥ��å�
& P_LOCK�ξ��˻��Ѥ��륪�֥������ȥ��å�����ĥץ����å���ID�����
$CLASS_OBJ_LOCK[1] = 1$

$  �����������å��Υ�����������
$CLASS_SECTION_TSKSTK[1] = "__attribute__((section(\"._kernel_prc1s_tstack\"),nocommon))"$

$  ����������ȥ�����֥��å��Υ�����������
$CLASS_SECTION_TSKCB[1] = "__attribute__((section(\"._kernel_prc1s_tskcb\"),nocommon))"$

$  ���֥������ȥ���ȥ�����֥��å��Υ�����������
$CLASS_SECTION_OBJCB[1] = "__attribute__((section(\"._kernel_prc1s_objcb\"),nocommon))"$

$ 
$ ���饹2�˴ؤ������
$ 
$CLASS_AFFINITY_INI[2] = 2$
$CLASS_AFFINITY_MASK[2] = 0x0000000f$
$CLASS_OBJ_LOCK[2] = 2$

$CLASS_SECTION_TSKSTK[2] = "__attribute__((section(\"._kernel_prc2s_tstack\"),nocommon))"$
$CLASS_SECTION_TSKCB[2] = "__attribute__((section(\"._kernel_prc2s_tskcb\"),nocommon))"$
$CLASS_SECTION_OBJCB[2] = "__attribute__((section(\"._kernel_prc2s_objcb\"),nocommon))"$

$ 
$ ���饹3�˴ؤ������
$ 
$CLASS_AFFINITY_INI[3] = 3$
$CLASS_AFFINITY_MASK[3] = 0x0000000f$
$CLASS_OBJ_LOCK[3] = 3$

$CLASS_SECTION_TSKSTK[3] = "__attribute__((section(\"._kernel_prc3s_tstack\"),nocommon))"$
$CLASS_SECTION_TSKCB[3] = "__attribute__((section(\"._kernel_prc3s_tskcb\"),nocommon))"$
$CLASS_SECTION_OBJCB[3] = "__attribute__((section(\"._kernel_prc3s_objcb\"),nocommon))"$

$ 
$ ���饹4�˴ؤ������
$ 
$CLASS_AFFINITY_INI[4] = 4$
$CLASS_AFFINITY_MASK[4] = 0x0000000f$
$CLASS_OBJ_LOCK[4] = 4$

$CLASS_SECTION_TSKSTK[4] = "__attribute__((section(\"._kernel_prc4s_tstack\"),nocommon))"$
$CLASS_SECTION_TSKCB[4] = "__attribute__((section(\"._kernel_prc4s_tskcb\"),nocommon))"$
$CLASS_SECTION_OBJCB[4] = "__attribute__((section(\"._kernel_prc4s_objcb\"),nocommon))"$

$ 
$ ���饹 TCL_1_ONLY�ʥ��饹ID 5�ˤ˴ؤ������
$ 
$CLASS_AFFINITY_INI[5] = 1$
$CLASS_AFFINITY_MASK[5] = 0x00000001$
$CLASS_OBJ_LOCK[5] = 1$

$CLASS_SECTION_TSKSTK[5] = "__attribute__((section(\"._kernel_prc1s_tstack\"),nocommon))"$
$CLASS_SECTION_TSKCB[5] = "__attribute__((section(\"._kernel_prc1s_tskcb\"),nocommon))"$
$CLASS_SECTION_OBJCB[5] = "__attribute__((section(\"._kernel_prc1s_objcb\"),nocommon))"$

$ 
$ ���饹 TCL_2_ONLY�ʥ��饹ID 6�ˤ˴ؤ������
$ 
$CLASS_AFFINITY_INI[6] = 2$
$CLASS_AFFINITY_MASK[6] = 0x00000002$
$CLASS_OBJ_LOCK[6] = 2$

$CLASS_SECTION_TSKSTK[6] = "__attribute__((section(\"._kernel_prc2s_tstack\"),nocommon))"$
$CLASS_SECTION_TSKCB[6] = "__attribute__((section(\"._kernel_prc2s_tskcb\"),nocommon))"$
$CLASS_SECTION_OBJCB[6] = "__attribute__((section(\"._kernel_prc2s_objcb\"),nocommon))"$

$ 
$ ���饹 TCL_3_ONLY�ʥ��饹ID 7�� �˴ؤ������
$ 
$CLASS_AFFINITY_INI[7] = 3$
$CLASS_AFFINITY_MASK[7] = 0x00000004$
$CLASS_OBJ_LOCK[7] = 3$

$CLASS_SECTION_TSKSTK[7] = "__attribute__((section(\"._kernel_prc3s_tstack\"),nocommon))"$
$CLASS_SECTION_TSKCB[7] = "__attribute__((section(\"._kernel_prc3s_tskcb\"),nocommon))"$
$CLASS_SECTION_OBJCB[7] = "__attribute__((section(\"._kernel_prc3s_objcb\"),nocommon))"$

$ 
$ ���饹 TCL_4_ONLY�ʥ��饹ID 8�� �˴ؤ������
$ 
$CLASS_AFFINITY_INI[8] = 4$
$CLASS_AFFINITY_MASK[8] = 0x00000008$
$CLASS_OBJ_LOCK[8] = 4$

$CLASS_SECTION_TSKSTK[8] = "__attribute__((section(\"._kernel_prc4s_tstack\"),nocommon))"$
$CLASS_SECTION_TSKCB[8] = "__attribute__((section(\"._kernel_prc4s_tskcb\"),nocommon))"$
$CLASS_SECTION_OBJCB[8] = "__attribute__((section(\"._kernel_prc4s_objcb\"),nocommon))"$

$ 
$ ���饹 TCL_SYSTIM_PRC�ʥ��饹ID 9�� �˴ؤ������
$ 
$CLASS_AFFINITY_INI[9] = TOPPERS_SYSTIM_PRCID$
$CLASS_AFFINITY_MASK[9] = 0x1 << (TOPPERS_SYSTIM_PRCID - 1) $
$CLASS_OBJ_LOCK[9] = TOPPERS_SYSTIM_PRCID$

$CLASS_SECTION_TSKSTK[9] = "__attribute__((section(\"._kernel_systim_tstack\"),nocommon))"$
$CLASS_SECTION_TSKCB[9] = "__attribute__((section(\"._kernel_systim_tskcb\"),nocommon))"$
$CLASS_SECTION_OBJCB[9] = "__attribute__((section(\"._kernel_systim_objcb\"),nocommon))"$

$ 
$  ���֥������ȴ�Ϣ�Υ�������������ʥ��饹��
$ 

$ 
$  �����������å������������
$ 
$FUNCTION GENERATE_TSKSTK$
	static STK_T _kernel_stack_$ARGV[1]$[COUNT_STK_T($TSK.STKSZ[ARGV[1]]$)]  $CLASS_SECTION_TSKSTK[TSK.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  TCB�����������
$ 
$FUNCTION GENERATE_TCB$
	TCB _kernel_tcb_$ARGV[1]$$TAB$$CLASS_SECTION_TSKCB[TSK.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  SEMCB�����������
$ 
$FUNCTION GENERATE_SEMCB$
	SEMCB _kernel_semcb_$ARGV[1]$ $CLASS_SECTION_OBJCB[SEM.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  FLGCB�����������
$ 
$FUNCTION GENERATE_FLGCB$
	FLGCB _kernel_flgcb_$ARGV[1]$ $CLASS_SECTION_OBJCB[FLG.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  DTQMB�����������
$ 
$FUNCTION GENERATE_DTQMB$
	static DTQMB _kernel_dtqmb_$DTQ.DTQID[ARGV[1]]$[$DTQ.DTQCNT[ARGV[1]]$] $CLASS_SECTION_OBJCB[DTQ.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  DTQCB�����������
$ 
$FUNCTION GENERATE_DTQCB$
	DTQCB _kernel_dtqcb_$ARGV[1]$ $CLASS_SECTION_OBJCB[DTQ.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  PDQMB�����������
$ 
$FUNCTION GENERATE_PDQMB$
	static PDQMB _kernel_pdqmb_$PDQ.PDQID[ARGV[1]]$[$PDQ.PDQCNT[ARGV[1]]$]  $CLASS_SECTION_OBJCB[PDQ.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  PDQCB�����������
$ 
$FUNCTION GENERATE_PDQCB$
	PDQCB _kernel_pdqcb_$ARGV[1]$ $CLASS_SECTION_OBJCB[PDQ.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  MBXCB�����������
$ 
$FUNCTION GENERATE_MBXCB$
	MBXCB _kernel_mbxcb_$ARGV[1]$ $CLASS_SECTION_OBJCB[MBX.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  MPF_T�����������
$ 
$FUNCTION GENERATE_MPF_T$
	static MPF_T _kernel_mpf_$MPF.MPFID[ARGV[1]]$[($MPF.BLKCNT[ARGV[1]]$) * COUNT_MPF_T($MPF.BLKSZ[mpfid]$)]  $CLASS_SECTION_OBJCB[MPF.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  MPFMB�����������
$ 
$FUNCTION GENERATE_MPFMB$
	static MPFMB _kernel_mpfmb_$MPF.MPFID[ARGV[1]]$[$MPF.BLKCNT[ARGV[1]]$] $CLASS_SECTION_OBJCB[MPF.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  MPFCB�����������
$ 
$FUNCTION GENERATE_MPFCB$
	MPFCB _kernel_mpfcb_$ARGV[1]$ $CLASS_SECTION_OBJCB[MPF.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  CYCCB�����������
$ 
$FUNCTION GENERATE_CYCCB$
	CYCCB _kernel_cyccb_$ARGV[1]$$TAB$$CLASS_SECTION_OBJCB[CYC.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  ALMCB�����������
$ 
$FUNCTION GENERATE_ALMCB$
	ALMCB _kernel_almcb_$ARGV[1]$$TAB$$CLASS_SECTION_OBJCB[ALM.CLASS[ARGV[1]]]$;$NL$
$END$

$ 
$  SPNCB�����������
$ 
$FUNCTION GENERATE_SPNCB$
	SPNCB _kernel_spncb_$ARGV[1]$ $CLASS_SECTION_OBJCB[SPN.CLASS[ARGV[1]]]$;$NL$
$END$


$ 
$  �ץ����å���¸�ƥ�ץ졼�ȤΥ��󥯥롼��
$ 
$INCLUDE"../../arch/nios2_gcc/prc.tf"$