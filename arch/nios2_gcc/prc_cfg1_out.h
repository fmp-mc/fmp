/*
 *  @(#) $Id: prc_cfg1_out.h 808 2011-05-20 13:50:58Z ertl-honda $
 */

/*
 *		cfg1_out.cをリンクするために必要なスタブの定義
 */

void sta_ker(void){}
void _kernel_target_mprc_initialize(void){}
uint_t _kernel_start_sync;
STK_T *const	_kernel_istkpt_table[TNUM_PRCID];

/*  
 *  オフセットファイルを生成するための定義  
 */  
const uint8_t   MAGIC_1 = 0x12;  
const uint16_t  MAGIC_2 = 0x1234;  
const uint32_t  MAGIC_4 = 0x12345678; 
 
const TCB TCB_enatex = { 
    { NULL, NULL }, NULL, 0U, 0U, 
    false, false, true, 
    0U, NULL, { NULL, NULL }, 0U, 
#if TTYPE_KLOCK != G_KLOCK 
    false, /* pend_relwai */ 
    false, /* pend_chgpri */ 
    0U,    /* pend_newpri */ 
#endif /* TTYPE_KLOCK != G_KLOCK */ 
    0U, {0U, NULL, NULL}, NULL, {{0U, 0U, 0U}} 
};
