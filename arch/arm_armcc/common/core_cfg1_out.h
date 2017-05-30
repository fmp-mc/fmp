/*
 *  @(#) $Id: core_cfg1_out.h 801 2011-05-03 13:54:23Z ertl-honda $
 */

/*
 *		cfg1_out.c���󥯤��뤿���ɬ�פʥ����֤����
 */

void sta_ker(void){}
void _kernel_target_mprc_initialize(void){}
uint_t _kernel_start_sync;
STK_T *const	_kernel_istkpt_table[TNUM_PRCID];
/* .vector���������˲����ե�������֤��ʤ��ȥ��顼�Ȥʤ뤿�� */
__attribute__ ((section("vector")))
void dummy_vector(void){}

/*
 * �����㥿���Ǥϥ��������ǥ��ե��˥å���󤬻Ȥ��ʤ�����
 * start.s���黲�Ȥ��륷��ܥ�����
 */ 
void hardware_init_hook(void){}
void software_init_hook(void){}

/* 
 *  ���ե��åȥե�������������뤿������ 
 */ 
const uint8_t   MAGIC_1 = 0x12; 
const uint16_t  MAGIC_2 = 0x1234; 
const uint32_t  MAGIC_4 = 0x12345678;


const TCB	TCB_enatex = {
	{ NULL, NULL },			/* task_queue */
	NULL,					/* p_tinib */
	0U,						/* tstat */
#ifdef TOPPERS_SUPPORT_MUTEX
	0U,						/* bpriority */
#endif /* TOPPERS_SUPPORT_MUTEX */
	0U,						/* priority */
	false,					/* acqeue */
	false,					/* wupque */
	true,					/* enatex */
	0U,						/* texprn */
	NULL,					/* p_winifo */
#ifdef TOPPERS_SUPPORT_MUTEX
	{ NULL, NULL },			/* mutex_queue */
#endif /* TOPPERS_SUPPORT_MUTEX */
	{ NULL, NULL }			/* tskctxb */
};
