/* This file is generated from prc_rename.def by genrename. */

/* This file is included only when prc_rename.h has been included. */
#ifdef TOPPERS_PRC_RENAME_H
#undef TOPPERS_PRC_RENAME_H

/*
 *  start.S
 */
#undef start

/*
 *  prc_support.S
 */
#undef dispatch
#undef start_dispatch
#undef exit_and_dispatch
#undef call_exit_kernel
#undef start_r
#undef interrupt_entry
#undef exception_entry
#undef default_int_handler_entry
#undef default_exc_handler_entry

#undef iipm_disall

/*
 *  prc_config.c
 */
#undef prc_initialize
#undef prc_exit
#undef x_config_int
#undef default_int_handler
#undef default_exc_handler

#undef ipr_info_tbl

/*
 *  sh2a_dual_config.c
 */
#undef prc_mprc_initialize
#undef x_config_int

#undef irc_reg_tbl
#undef idcnt_tbl_h
#undef semr_tbl_b

/*
 *  kernel_cfg.c
 */
#undef p_pcb_table
#undef p_vectors_table
#undef int_iipm_tbl

/*
 *  trace_config.c
 */
#undef trace_sta_log
#undef trace_wri_log
#undef trace_rea_log
#undef trace_write_0
#undef trace_write_1
#undef trace_write_2
#undef trace_write_3

#undef trace_buffer
#undef trace_count
#undef trace_head
#undef trace_tail
#undef trace_lost

#ifdef TOPPERS_LABEL_ASM

/*
 *  start.S
 */
#undef _start

/*
 *  prc_support.S
 */
#undef _dispatch
#undef _start_dispatch
#undef _exit_and_dispatch
#undef _call_exit_kernel
#undef _start_r
#undef _interrupt_entry
#undef _exception_entry
#undef _default_int_handler_entry
#undef _default_exc_handler_entry

#undef _iipm_disall

/*
 *  prc_config.c
 */
#undef _prc_initialize
#undef _prc_exit
#undef _x_config_int
#undef _default_int_handler
#undef _default_exc_handler

#undef _ipr_info_tbl

/*
 *  sh2a_dual_config.c
 */
#undef _prc_mprc_initialize
#undef _x_config_int

#undef _irc_reg_tbl
#undef _idcnt_tbl_h
#undef _semr_tbl_b

/*
 *  kernel_cfg.c
 */
#undef _p_pcb_table
#undef _p_vectors_table
#undef _int_iipm_tbl

/*
 *  trace_config.c
 */
#undef _trace_sta_log
#undef _trace_wri_log
#undef _trace_rea_log
#undef _trace_write_0
#undef _trace_write_1
#undef _trace_write_2
#undef _trace_write_3

#undef _trace_buffer
#undef _trace_count
#undef _trace_head
#undef _trace_tail
#undef _trace_lost

#endif /* TOPPERS_LABEL_ASM */


#endif /* TOPPERS_PRC_RENAME_H */
