$ 
$     �ѥ�2�Υ������åȰ�¸�ƥ�ץ졼�ȡ�CT11MPCORE�ѡ�
$ 

$ 
$  ͭ���ʳ�����ֹ桤����ߥϥ�ɥ��ֹ桤CPU�㳰�ϥ�ɥ��ֹ�
$ 
$INTNO_VALID = { 
	0x10000,0x10001,...,0x1000f;0x1001d,0x1001e,0x1001f;
	0x20000,0x20001,...,0x2000f;0x2001d,0x2001e,0x2001f;
	0x30000,0x30001,...,0x3000f;0x3001d,0x3001e,0x3001f;
	0x40000,0x40001,...,0x4000f;0x4001d,0x4001e,0x4001f;
	0x00020,0x00021,...,0x0003f
}$

$INHNO_VALID = { 
	0x10000,0x10001,...,0x1000f;0x1001d,0x1001e,...,0x1003f;
	0x20000,0x20001,...,0x2000f;0x2001d,0x2001e,...,0x2003f;
	0x30000,0x30001,...,0x3000f;0x3001d,0x3001e,...,0x3003f;
	0x40000,0x40001,...,0x4000f;0x4001d,0x4001e,...,0x4003f
}$

$ 
$  ATT_ISR�ǻ��ѤǤ��������ֹ�Ȥ�����б��������ߥϥ�ɥ��ֹ�
$ 
$INTNO_ATTISR_VALID = { 
	0x10000,0x10001,...,0x1000f;0x1001d,0x1001e,0x1001f;
	0x20000,0x20001,...,0x2000f;0x2001d,0x2001e,0x2001f;
	0x30000,0x30001,...,0x3000f;0x3001d,0x3001e,0x3001f;
	0x40000,0x40001,...,0x4000f;0x4001d,0x4001e,0x4001f;
	0x00020,0x00021,...,0x0003f
}$

$INHNO_ATTISR_VALID = {
	0x10000,0x10001,...,0x1000f;0x1001d,0x1001e,0x1001f;
	0x20000,0x20001,...,0x2000f;0x2001d,0x2001e,0x2001f;
	0x30000,0x30001,...,0x3000f;0x3001d,0x3001e,0x3001f;
	0x40000,0x40001,...,0x4000f;0x4001d,0x4001e,0x4001f;
	0x00020,0x00021,...,0x0003f
}$

$ 
$ ������ֹ桤����ߥϥ�ɥ��ֹ��Ĺ��
$ 
$INTNO_RANGE = { 0x0000,0x0001,...,0x003f }$
$INHNO_RANGE = INTNO_RANGE$

$ 
$ �ץ��å����Ф������
$ 


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

$  ������դ��ץ��å�(ID����)
$CLASS_AFFINITY_INI[1] = 1$

$  �ޥ����졼������ǽ�ʥץ��å��Υޥ�������
$CLASS_AFFINITY_MASK[1] = 0x0000000f$

$  ���֥������ȥ�å�
& P_LOCK�ξ��˻��Ѥ��륪�֥������ȥ�å�����ĥץ��å���ID�����
$CLASS_OBJ_LOCK[1] = 1$

$ 
$ ���饹2�˴ؤ������
$ 
$CLASS_AFFINITY_INI[2] = 2$
$CLASS_AFFINITY_MASK[2] = 0x0000000f$
$CLASS_OBJ_LOCK[2] = 2$

$ 
$ ���饹3�˴ؤ������
$ 
$CLASS_AFFINITY_INI[3] = 3$
$CLASS_AFFINITY_MASK[3] = 0x0000000f$
$CLASS_OBJ_LOCK[3] = 3$

$ 
$ ���饹4�˴ؤ������
$ 
$CLASS_AFFINITY_INI[4] = 4$
$CLASS_AFFINITY_MASK[4] = 0x0000000f$
$CLASS_OBJ_LOCK[4] = 4$

$ 
$ ���饹 TCL_1_ONLY�ʥ��饹ID 5�ˤ˴ؤ������
$ 
$CLASS_AFFINITY_INI[5] = 1$
$CLASS_AFFINITY_MASK[5] = 0x00000001$
$CLASS_OBJ_LOCK[5] = 1$

$ 
$ ���饹 TCL_2_ONLY�ʥ��饹ID 6�ˤ˴ؤ������
$ 
$CLASS_AFFINITY_INI[6] = 2$
$CLASS_AFFINITY_MASK[6] = 0x00000002$
$CLASS_OBJ_LOCK[6] = 2$

$ 
$ ���饹 TCL_3_ONLY�ʥ��饹ID 7�� �˴ؤ������
$ 
$CLASS_AFFINITY_INI[7] = 3$
$CLASS_AFFINITY_MASK[7] = 0x00000004$
$CLASS_OBJ_LOCK[7] = 3$

$ 
$ ���饹 TCL_4_ONLY�ʥ��饹ID 8�� �˴ؤ������
$ 
$CLASS_AFFINITY_INI[8] = 4$
$CLASS_AFFINITY_MASK[8] = 0x00000008$
$CLASS_OBJ_LOCK[8] = 4$

$ 
$ ���饹 TCL_SYSTIM_PRC�ʥ��饹ID 9�� �˴ؤ������
$ 
$CLASS_AFFINITY_INI[9] = TOPPERS_SYSTIM_PRCID$
$CLASS_AFFINITY_MASK[9] = 0x1 << (TOPPERS_SYSTIM_PRCID - 1) $
$CLASS_OBJ_LOCK[9] = TOPPERS_SYSTIM_PRCID$

$ 
$  ���åװ�¸�ƥ�ץ졼�ȤΥ��󥯥롼��
$ 
$INCLUDE"../../arch/arm_gcc/mpcore/arm11.tf"$
