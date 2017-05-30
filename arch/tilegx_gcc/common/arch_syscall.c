/**
 * TILEGx Architecture Support Package for TOPPERS/FMP Kernel
 *
 * Copyright (C) 2015 by Yixiao Li (liyixiao@ertl.jp)
 *
 *  The above copyright holders grant permission gratis to use,
 *  duplicate, modify, or redistribute (hereafter called use) this
 *  software (including the one made by modifying this software),
 *  provided that the following four conditions (1) through (4) are
 *  satisfied.
 *
 *  (1) When this software is used in the form of source code, the above
 *      copyright notice, this use conditions, and the disclaimer shown
 *      below must be retained in the source code without modification.
 *
 *  (2) When this software is redistributed in the forms usable for the
 *      development of other software, such as in library form, the above
 *      copyright notice, this use conditions, and the disclaimer shown
 *      below must be shown without modification in the document provided
 *      with the redistributed software, such as the user manual.
 *
 *  (3) When this software is redistributed in the forms unusable for the
 *      development of other software, such as the case when the software
 *      is embedded in a piece of equipment, either of the following two
 *      conditions must be satisfied:
 *
 *    (a) The above copyright notice, this use conditions, and the
 *        disclaimer shown below must be shown without modification in
 *        the document provided with the redistributed software, such as
 *        the user manual.
 *
 *    (b) How the software is to be redistributed must be reported to the
 *        TOPPERS Project according to the procedure described
 *        separately.
 *
 *  (4) The above copyright holders and the TOPPERS Project are exempt
 *      from responsibility for any type of damage directly or indirectly
 *      caused from the use of this software and are indemnified by any
 *      users or end users of this software from any and all causes of
 *      action whatsoever.
 *
 *  THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
 *  THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
 *  PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
 *  TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
 *  INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
 */

#include <kernel.h>
#include <t_syslog.h>
#include "spr_def.h"
#include "hv/hypervisor.h"
#include "hv/pagesize.h"
#include "arch_syscall.h"
#include <sys/syscall.h>

void arch_syscall_handler(intptr_t par1, intptr_t par2, intptr_t par3, intptr_t par4) {
    register int r10 asm ("r10");
    int svc_num = r10; // NOTE: This is IMPORTANT! Snapshot r10.
    int ret;
    switch(svc_num) {
    case SYS_exit:
        syslog(LOG_EMERG, "exit() called!");
        extern void debug_loop();
        debug_loop();
        break;
#if 0
    case SYS_openat:
        assert(par1 == -100/*AT_FDCWD*/);
        ret = openat(par1, par2, par3);
        break;

    case SYS_read:
        ret = read(par1, par2, par3);
        break;

    case SYS_write:
        ret = write(par1, par2, par3);
        break;
#endif
#if 0
    case SYS_lseek:
        ret = sys_lseek(par1, par2, par3);
        break;

    case SYS_close:
        assert(par1 >= 2/*NORMAL_FD_OFFSET*/);
        ret = close(par1);
        break;

    case SYS_newfstatat/*SYS3264_fstatat*/:
    	assert(par1 == -100/*AT_FDCWD*/);
    	assert(par4 == 0/*flag is not supported yet*/);
    	syslog(LOG_NOTICE, "SYS_newfstatat path=%s, buf=%p", par2, par3);
    	ret = openat(par1, par2, par4); // TODO: par4 is not really oflag
    	ret = fstat(ret, par3);
    	close(ret);
    	break;

    case SYS_fstat:
        ret = fstat(par1, par2);
        break;
#endif

    default:
        syslog(LOG_EMERG, "Unsupported system call!", __FUNCTION__);
	    syslog(LOG_EMERG, "No. %d", svc_num);
	    syslog(LOG_EMERG, "r0: 0x%p", par1);
	    syslog(LOG_EMERG, "r1: 0x%p", par2);
	    syslog(LOG_EMERG, "r2: 0x%p", par3);
	    syslog(LOG_EMERG, "r3: 0x%p", par4);
        debug_loop();
    }
    // TODO: SHOULD write r0 register HERE!!!!
}

