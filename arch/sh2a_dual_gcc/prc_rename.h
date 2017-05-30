/* This file is generated from prc_rename.def by genrename. */

#ifndef TOPPERS_PRC_RENAME_H
#define TOPPERS_PRC_RENAME_H

/*
 *  start.S
 */
#define start						_kernel_start

/*
 *  prc_support.S
 */
#define dispatch					_kernel_dispatch
#define start_dispatch				_kernel_start_dispatch
#define exit_and_dispatch			_kernel_exit_and_dispatch
#define call_exit_kernel			_kernel_call_exit_kernel
#define start_r						_kernel_start_r
#define interrupt_entry				_kernel_interrupt_entry
#define exception_entry				_kernel_exception_entry
#define default_int_handler_entry	_kernel_default_int_handler_entry
#define default_exc_handler_entry	_kernel_default_exc_handler_entry

#define iipm_disall					_kernel_iipm_disall

/*
 *  prc_config.c
 */
#define prc_initialize				_kernel_prc_initialize
#define prc_exit					_kernel_prc_exit
#define x_config_int				_kernel_x_config_int
#define default_int_handler			_kernel_default_int_handler
#define default_exc_handler			_kernel_default_exc_handler

#define ipr_info_tbl				_kernel_ipr_info_tbl

/*
 *  sh2a_dual_config.c
 */
#define prc_mprc_initialize			_kernel_prc_mprc_initialize
#define x_config_int				_kernel_x_config_int

#define irc_reg_tbl					_kernel_irc_reg_tbl
#define idcnt_tbl_h					_kernel_idcnt_tbl_h
#define semr_tbl_b					_kernel_semr_tbl_b

/*
 *  kernel_cfg.c
 */
#define p_pcb_table					_kernel_p_pcb_table
#define p_vectors_table				_kernel_p_vectors_table
#define int_iipm_tbl				_kernel_int_iipm_tbl

/*
 *  trace_config.c
 */
#define trace_sta_log				_kernel_trace_sta_log
#define trace_wri_log				_kernel_trace_wri_log
#define trace_rea_log				_kernel_trace_rea_log
#define trace_write_0				_kernel_trace_write_0
#define trace_write_1				_kernel_trace_write_1
#define trace_write_2				_kernel_trace_write_2
#define trace_write_3				_kernel_trace_write_3

#define trace_buffer				_kernel_trace_buffer
#define trace_count					_kernel_trace_count
#define trace_head					_kernel_trace_head
#define trace_tail					_kernel_trace_tail
#define trace_lost					_kernel_trace_lost

#ifdef TOPPERS_LABEL_ASM

/*
 *  start.S
 */
#define _start						__kernel_start

/*
 *  prc_support.S
 */
#define _dispatch					__kernel_dispatch
#define _start_dispatch				__kernel_start_dispatch
#define _exit_and_dispatch			__kernel_exit_and_dispatch
#define _call_exit_kernel			__kernel_call_exit_kernel
#define _start_r					__kernel_start_r
#define _interrupt_entry			__kernel_interrupt_entry
#define _exception_entry			__kernel_exception_entry
#define _default_int_handler_entry	__kernel_default_int_handler_entry
#define _default_exc_handler_entry	__kernel_default_exc_handler_entry

#define _iipm_disall				__kernel_iipm_disall

/*
 *  prc_config.c
 */
#define _prc_initialize				__kernel_prc_initialize
#define _prc_exit					__kernel_prc_exit
#define _x_config_int				__kernel_x_config_int
#define _default_int_handler		__kernel_default_int_handler
#define _default_exc_handler		__kernel_default_exc_handler

#define _ipr_info_tbl				__kernel_ipr_info_tbl

/*
 *  sh2a_dual_config.c
 */
#define _prc_mprc_initialize		__kernel_prc_mprc_initialize
#define _x_config_int				__kernel_x_config_int

#define _irc_reg_tbl				__kernel_irc_reg_tbl
#define _idcnt_tbl_h				__kernel_idcnt_tbl_h
#define _semr_tbl_b					__kernel_semr_tbl_b

/*
 *  kernel_cfg.c
 */
#define _p_pcb_table				__kernel_p_pcb_table
#define _p_vectors_table			__kernel_p_vectors_table
#define _int_iipm_tbl				__kernel_int_iipm_tbl

/*
 *  trace_config.c
 */
#define _trace_sta_log				__kernel_trace_sta_log
#define _trace_wri_log				__kernel_trace_wri_log
#define _trace_rea_log				__kernel_trace_rea_log
#define _trace_write_0				__kernel_trace_write_0
#define _trace_write_1				__kernel_trace_write_1
#define _trace_write_2				__kernel_trace_write_2
#define _trace_write_3				__kernel_trace_write_3

#define _trace_buffer				__kernel_trace_buffer
#define _trace_count				__kernel_trace_count
#define _trace_head					__kernel_trace_head
#define _trace_tail					__kernel_trace_tail
#define _trace_lost					__kernel_trace_lost

#endif /* TOPPERS_LABEL_ASM */


#endif /* TOPPERS_PRC_RENAME_H */
