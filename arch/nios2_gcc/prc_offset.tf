$ 
$       オフセットファイル生成用テンプレートファイル（NIOS2用）
$ 

$ 
$  標準テンプレートファイルのインクルード
$ 
$INCLUDE "kernel/genoffset.tf"$

$ 
$  オフセット値のマクロ定義の生成
$ 
$DEFINE("TCB_p_tinib", offsetof_TCB_p_tinib)$
$DEFINE("TCB_texptn", offsetof_TCB_texptn)$
$DEFINE("TCB_sp", offsetof_TCB_sp)$
$DEFINE("TCB_pc", offsetof_TCB_pc)$

$DEFINE("TINIB_exinf", offsetof_TINIB_exinf)$
$DEFINE("TINIB_task", offsetof_TINIB_task)$

$DEFINE("PCB_p_runtsk", offsetof_PCB_p_runtsk)$
$DEFINE("PCB_p_schedtsk", offsetof_PCB_p_schedtsk)$
$DEFINE("PCB_reqflg", offsetof_PCB_reqflg)$
$DEFINE("PCB_ipmflg", offsetof_PCB_ipmflg)$
$DEFINE("PCB_disdsp", offsetof_PCB_disdsp)$
$DEFINE("PCB_dspflg", offsetof_PCB_dspflg)$

$DEFINE("PCB_p_firstlock", offsetof_PCB_p_firstlock)$
$DEFINE("PCB_p_secondlock", offsetof_PCB_p_secondlock)$
$DEFINE("PCB_locspnid", offsetof_PCB_locspnid)$

$DEFINE("PCB_except_nest_count", offsetof_PCB_except_nest_count)$
$DEFINE("PCB_idf", offsetof_PCB_idf)$
$DEFINE("PCB_iipm", offsetof_PCB_iipm)$
$DEFINE("PCB_istkpt", offsetof_PCB_istkpt)$
$DEFINE("PCB_p_iipm_mask_tbl", offsetof_PCB_p_iipm_mask_tbl)$
$DEFINE("PCB_p_inh_tbl", offsetof_PCB_p_inh_tbl)$
$DEFINE("PCB_p_inh_iipm_tbl", offsetof_PCB_p_inh_iipm_tbl)$
$DEFINE("PCB_p_exch_tbl", offsetof_PCB_p_exch_tbl)$
$DEFINE("PCB_prc_int_base", offsetof_PCB_prc_int_base)$

$ 
$  ビットオフセット値等のマクロ定義の生成
$ 
$DEFINE_BIT("TCB_enatex", sizeof_TCB, "B")$
