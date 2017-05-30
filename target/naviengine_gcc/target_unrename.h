/* This file is generated from target_rename.def by genrename. */

/* This file is included only when target_rename.h has been included. */
#ifdef TOPPERS_TARGET_RENAME_H
#undef TOPPERS_TARGET_RENAME_H

/*
 *  target_config.c
 */
#undef target_mprc_initialize
#undef target_mmu_init
#undef target_initialize
#undef target_exit
#undef perf_timer_initialize
#undef perf_timer_get
#undef perf_timer_conv_tim

/*
 *  naviengine.c
 */
#undef naviengine_uart_init
#undef naviengine_uart_putc


#ifdef TOPPERS_LABEL_ASM

/*
 *  target_config.c
 */
#undef _target_mprc_initialize
#undef _target_mmu_init
#undef _target_initialize
#undef _target_exit
#undef _perf_timer_initialize
#undef _perf_timer_get
#undef _perf_timer_conv_tim

/*
 *  naviengine.c
 */
#undef _naviengine_uart_init
#undef _naviengine_uart_putc


#endif /* TOPPERS_LABEL_ASM */

#include "arm_gcc/mpcore/chip_unrename.h"

#endif /* TOPPERS_TARGET_RENAME_H */
