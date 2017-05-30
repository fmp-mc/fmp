$ 
$ 		オフセットファイル生成用テンプレートファイル（SH12A用）
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

$DEFINE("TINIB_TSKINICTXB_stksz", offsetof_TINIB_TSKINICTXB_stksz)$
$DEFINE("TINIB_TSKINICTXB_stk_bottom", offsetof_TINIB_TSKINICTXB_stk_bottom)$

$DEFINE("PCB_p_runtsk", offsetof_PCB_p_runtsk)$
$DEFINE("PCB_p_schedtsk", offsetof_PCB_p_schedtsk)$
$DEFINE("PCB_reqflg", offsetof_PCB_reqflg)$
$DEFINE("PCB_ipmflg", offsetof_PCB_ipmflg)$
$DEFINE("PCB_disdsp", offsetof_PCB_disdsp)$
$DEFINE("PCB_dspflg", offsetof_PCB_dspflg)$
$DEFINE("PCB_locspnid", offsetof_PCB_locspnid)$

$DEFINE("PCB_excnest_count", offsetof_PCB_excnest_count)$
$DEFINE("PCB_istkpt", offsetof_PCB_istkpt)$
$DEFINE("PCB_lock_flag", offsetof_PCB_lock_flag)$
$DEFINE("PCB_saved_iipm", offsetof_PCB_saved_iipm)$
$DEFINE("PCB_p_vector_table", offsetof_PCB_p_vector_table)$


$ 
$  ビットオフセット値等のマクロ定義の生成
$ 
$DEFINE_BIT("TCB_enatex", sizeof_TCB, "B")$
