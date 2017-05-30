/* This file is generated from target_rename.def by genrename. */

#ifndef TOPPERS_TARGET_RENAME_H
#define TOPPERS_TARGET_RENAME_H

/*
 *  target_config.c
 */
#define target_mprc_initialize		_kernel_target_mprc_initialize
#define target_mmu_init				_kernel_target_mmu_init
#define target_initialize			_kernel_target_initialize
#define target_exit					_kernel_target_exit
#define perf_timer_initialize		_kernel_perf_timer_initialize
#define perf_timer_get				_kernel_perf_timer_get
#define perf_timer_conv_tim			_kernel_perf_timer_conv_tim

/*
 *  naviengine.c
 */
#define naviengine_uart_init		_kernel_naviengine_uart_init
#define naviengine_uart_putc		_kernel_naviengine_uart_putc


#ifdef TOPPERS_LABEL_ASM

/*
 *  target_config.c
 */
#define _target_mprc_initialize		__kernel_target_mprc_initialize
#define _target_mmu_init			__kernel_target_mmu_init
#define _target_initialize			__kernel_target_initialize
#define _target_exit				__kernel_target_exit
#define _perf_timer_initialize		__kernel_perf_timer_initialize
#define _perf_timer_get				__kernel_perf_timer_get
#define _perf_timer_conv_tim		__kernel_perf_timer_conv_tim

/*
 *  naviengine.c
 */
#define _naviengine_uart_init		__kernel_naviengine_uart_init
#define _naviengine_uart_putc		__kernel_naviengine_uart_putc


#endif /* TOPPERS_LABEL_ASM */

#include "arm_gcc/mpcore/chip_rename.h"

#endif /* TOPPERS_TARGET_RENAME_H */
