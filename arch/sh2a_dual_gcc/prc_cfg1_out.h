/*
 *  $Id: prc_cfg1_out.h 809 2011-06-03 08:19:09Z mit-kimai $
 */

/*
 *		cfg1_out.cをリンクするために必要なスタブの定義
 */

void sta_ker(void){}
void _kernel_target_mprc_initialize(void){}

/*  スタックポインタの初期値  */
STK_T *const	_kernel_istkpt_table[TNUM_PRCID];

/*
 *  オフセットファイルを生成するための定義
 */
const uint8_t	MAGIC_1 = 0x12;
const uint16_t	MAGIC_2 = 0x1234;
const uint32_t	MAGIC_4 = 0x12345678;

const TCB	TCB_enatex = {
	{ NULL, NULL },			/* task_queue */
	NULL,					/* p_tinib */
	0U,						/* tstat */
	0U,						/* priority */
	false,					/* acqeue */
	false,					/* wupque */
	true,					/* enatex */
	0U,						/* texptn */
	NULL,					/* p_pcb */
	{ NULL, NULL },			/* tskctxb {sp, pc} */
	0U,						/* actprc */
#if TTYPE_KLOCK != G_KLOCK
	false,					/* pend_relwai */
	false,					/* pend_chgpri */
	0U,						/* pend_newpri */
#endif /* TTYPE_KLOCK != G_KLOCK */
	0,						/* wercd */
	{0U, NULL, NULL},		/* tmevtb */
	NULL,					/* p_wobjcb */
	{{0U, 0U, 0U}}			/* winfo_obj */
};
