/* This file is generated from prc_rename.def by genrename. */

/* This file is included only when prc_rename.h has been included. */
#ifdef TOPPERS_PRC_RENAME_H
#undef TOPPERS_PRC_RENAME_H

/*
 *  prc_config.c
 */
#undef x_config_int
#undef int_bitmap_search_table
#undef prc_initialize
#undef prc_terminate
#undef start_sync
#undef default_exc_handler
#undef default_int_handler

/*
 *  prc_support.S
 */
#undef exception_entry
#undef ret_int
#undef ret_exc
#undef start_r
#undef dispatch
#undef start_dispatch
#undef exit_and_dispatch
#undef call_exit_kernel
#undef exit_and_migrate
#undef dispatch_and_migrate

/*
 * kernel_cfg.c
 */
#undef p_npcb_table
#undef p_inh_table
#undef p_iipm_mask_table
#undef p_inh_iipm_table
#undef p_exch_table

#ifdef TOPPERS_LABEL_ASM

/*
 *  prc_config.c
 */
#undef _x_config_int
#undef _int_bitmap_search_table
#undef _prc_initialize
#undef _prc_terminate
#undef _start_sync
#undef _default_exc_handler
#undef _default_int_handler

/*
 *  prc_support.S
 */
#undef _exception_entry
#undef _ret_int
#undef _ret_exc
#undef _start_r
#undef _dispatch
#undef _start_dispatch
#undef _exit_and_dispatch
#undef _call_exit_kernel
#undef _exit_and_migrate
#undef _dispatch_and_migrate

/*
 * kernel_cfg.c
 */
#undef _p_npcb_table
#undef _p_inh_table
#undef _p_iipm_mask_table
#undef _p_inh_iipm_table
#undef _p_exch_table

#endif /* TOPPERS_LABEL_ASM */


#endif /* TOPPERS_PRC_RENAME_H */
