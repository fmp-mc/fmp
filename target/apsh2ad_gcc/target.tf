$ 
$     �ѥ�2�Υ������åȰ�¸�ƥ�ץ졼�ȡ�APSH2AD�ѡ�
$ 

$ 
$ �ץ��å����Ф������
$ 

$ �����Х륿���޻��Υ����।�٥���ѥǡ����Υ�����������
$PRC_SECTION_TEVT[0] = ""$

$ 
$ �ͥ��ƥ��֥�å������ξ��Υ�å��κ��祵�ݡ��ȿ�
$ 
$MAX_NATIVE_SPIN_LOCK = 32 - 2$
$ 
$ �ץ��å�1�˴ؤ������
$ 
$ PCB�Υ�����������
$PRC_SECTION_PCB[1]  = ""$
$ �󥿥�������ƥ������ѥ����å��Υ�����������
$PRC_SECTION_ISTACK[1]  = ""$
$ �����।�٥�ȴ�Ϣ�ǡ����Υ�����������
$PRC_SECTION_TEVT[1] = ""$

$ �������åȰ�¸�����
$PRC_SECTION_TPCB[1] = ""$


$ 
$ �ץ��å�2�˴ؤ������
$ 
$PRC_SECTION_PCB[2] = ""$
$PRC_SECTION_ISTACK[2]  = ""$
$PRC_SECTION_TEVT[2] = ""$
$PRC_SECTION_TPCB[2] = ""$



$ 
$  ���饹���Ф������
$ 

$ 
$  ���饹��
$ 
$NUM_CLASS = 5$

$ 
$ ���饹 TCL_1�ʥ��饹ID 1�� �˴ؤ������
$ ���ץ��å�1��������դ��ץ��å��Υ��饹
$ 

$  �����°�ץ��å�(ID����)
$CLASS_AFFINITY_INI[1] = 1$

$  �ޥ����졼������ǽ�ʥץ��å��Υޥ�������
$CLASS_AFFINITY_MASK[1] = 0x00000003$

$  ����������ȥ���֥�å��Υ�����������
$CLASS_SECTION_TSKCB[1] = ""$

$  ���֥������ȥ���ȥ���֥�å��Υ�����������
$CLASS_SECTION_OBJCB[1] = ""$

$  �����������å��Υ�����������
$CLASS_SECTION_TSTACK[1] = ""$


$ 
$ ���饹 TCL_2�ʥ��饹ID 2�� �˴ؤ������
$ ���ץ��å�2��������դ��ץ��å��Υ��饹
$ 
$CLASS_AFFINITY_INI[2] = 2$
$CLASS_AFFINITY_MASK[2] = 0x00000003$

$CLASS_SECTION_TSKCB[2] = ""$
$CLASS_SECTION_OBJCB[2] = ""$
$CLASS_SECTION_TSTACK[2] = ""$

$ 
$ ���饹 TCL_1_ONLY�ʥ��饹ID 3�� �˴ؤ������
$ �����դ���ǽ�ץ��å��ϥץ��å�1�ΤߤΥ��饹
$ 
$CLASS_AFFINITY_INI[3] = 1$
$CLASS_AFFINITY_MASK[3] = 0x00000001$

$CLASS_SECTION_TSKCB[3] = ""$
$CLASS_SECTION_OBJCB[3] = ""$
$CLASS_SECTION_TSTACK[3] = ""$


$ 
$ ���饹 TCL_2_ONLY�ʥ��饹ID 4�� �˴ؤ������
$ �����դ���ǽ�ץ��å��ϥץ��å�1�ΤߤΥ��饹
$ 
$CLASS_AFFINITY_INI[4] = 2$
$CLASS_AFFINITY_MASK[4] = 0x00000002$

$CLASS_SECTION_TSKCB[4] = ""$
$CLASS_SECTION_OBJCB[4] = ""$
$CLASS_SECTION_TSTACK[4] = ""$

$ 
$ ���饹 TCL_SYSTIM_PRC�ʥ��饹ID 5�� �˴ؤ������
$ ���������Х륿���������ξ��Υ����।�٥�ȥϥ�ɥ����Ͽ���륯�饹
$ �����ʥ����ƥ��������ץ��å��ΤߤΥ��饹��
$ 
$CLASS_AFFINITY_INI[5] = TOPPERS_SYSTIM_PRCID$
$CLASS_AFFINITY_MASK[5] = 0x1 << (TOPPERS_SYSTIM_PRCID - 1)$

$CLASS_SECTION_TSKCB[5] = ""$
$CLASS_SECTION_OBJCB[5] = ""$
$CLASS_SECTION_TSTACK[5] = ""$


$ 
$ ATT_ISR�Υ������åȰ�¸�Υ����å�
$ �������»����
$ ���ϡ��ɥ�����Ū�����ץ��å��ˤ����դ���ǽ�ʳ���ߡʳ�����ֹ�ξ��
$ ��16�ӥåȤ�0�ˤ��Ф���ATT_ISR�ϡ�����դ���ǽ�ץ��å���������դ��ץ�
$ �����å��ΤߤΥ��饹�˳���դ���ǽ�Ǥ��롥
$ 
$FUNCTION TARGET_CHECK_ATT_ISR$
	$IF ((ISR.INTNO[ARGV[1]] & 0xffff0000) == 0) 
		&& ((1 << (CLASS_AFFINITY_INI[ISR.CLASS[ARGV[1]]] - 1)) != CLASS_AFFINITY_MASK[ISR.CLASS[ARGV[1]]])$
		$ERROR ISR.TEXT_LINE[order]$E_RSATR: $FORMAT(_("processor affinity of `0x%1$x\' in %2% is not match with class %3% processor affinity mask `0x%4$x\'."), +ISR.INTNO[ARGV[1]], "ATT_ISR", ISR.CLASS[ARGV[1]], +CLASS_AFFINITY_MASK[ISR.CLASS[ARGV[1]]])$$END$
	$END$
$END$


$ 
$  SH7205��¸�Υƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ 
$INCLUDE "sh2a_dual_gcc/sh7205.tf"$
