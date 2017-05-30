/* This file is generated from target_rename.def by genrename. */

#ifndef TOPPERS_TARGET_RENAME_H
#define TOPPERS_TARGET_RENAME_H


/*
 *  target_config.c
 */
#define target_bsc_pfc_initialize	_kernel_target_bsc_pfc_initialize
#define target_mprc_initialize		_kernel_target_mprc_initialize
#define target_initialize			_kernel_target_initialize
#define target_exit					_kernel_target_exit

#ifdef TOPPERS_LABEL_ASM


/*
 *  target_config.c
 */
#define _target_bsc_pfc_initialize	__kernel_target_bsc_pfc_initialize
#define _target_mprc_initialize		__kernel_target_mprc_initialize
#define _target_initialize			__kernel_target_initialize
#define _target_exit				__kernel_target_exit

#endif /* TOPPERS_LABEL_ASM */

#include "sh2a_dual_gcc/prc_rename.h"

#endif /* TOPPERS_TARGET_RENAME_H */
