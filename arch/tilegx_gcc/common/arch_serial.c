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

/**
 * Serial I/O driver.
 * This driver is used for Hypervisor Virtual Console (HVC).
 * Physical serial I/O ports are not supported.
 *
 * Note:
 * SIO port of HVC is associated with PCB so 'siopcb' is not used.
 */

#include "kernel/kernel_impl.h"
#include "kernel/task.h"
#include <t_syslog.h>
#include <log_output.h>
#include "spr_def.h"
#include "hv/hypervisor.h"
#include "arch_serial.h"
#include "target_syssvc.h"
#include "kernel_cfg.h"

#include <string.h>

void arch_hvc_ipi_handler() {
    PCB *my_p_pcb = get_my_p_pcb();
	intptr_t exinf = my_p_pcb->target_pcb.siopcb.exinf;

	// Handle incoming data
	int *read_buf = &(my_p_pcb->target_pcb.siopcb.recv_buffer);
	while((*read_buf = hv_console_read_if_ready()) >= 0) {
		sio_irdy_rcv(exinf);

		// For debug
		if (*read_buf == 'q') { // Quit kernel
			ext_ker();
#if 0
			trace_dump_reverse(target_fput_log);
			hv_power_off();
#endif
		} else if (*read_buf == 'p') { // Print debug info
            //syslog(LOG_NOTICE, "p_runtsk ID: %d", TSKID(my_p_pcb->p_schedtsk));
            syslog(LOG_NOTICE, "my_p_pcb: 0x%p", my_p_pcb->p_schedtsk);
        }
	}
}

SIOPCB *sio_opn_por(ID siopid, intptr_t exinf) {
	// TODO: assert(siopid == my_prc_id)
	get_my_p_pcb()->target_pcb.siopcb.exinf = exinf;
    return &(get_my_p_pcb()->target_pcb.siopcb);
}

/**
 * This function will and can ONLY be called from interrupt context or CPU locked state.
 */
bool_t sio_snd_chr(SIOPCB *siopcb, char c) {
#if 1 // G_SYSLOG
	hv_console_putc(c);
#else
    if (siopcb->send_request) {
//		syslog(LOG_EMERG, "%s(): send_request busy!.", __FUNCTION__);
		return false;
	}

	assert(siopcb->send_buffer_len < SIO_WRITE_BUFFER_SIZE);

	siopcb->send_buffer[siopcb->send_buffer_len++] = c;

	if (c == '\n' || siopcb->send_buffer_len == SIO_WRITE_BUFFER_SIZE) {
		siopcb->send_request = true;
	}
#endif

    return true;
}

int_t sio_rcv_chr(SIOPCB *unused) {
    return get_my_p_pcb()->target_pcb.siopcb.recv_buffer;
}

void sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn) {
	siopcb->cbrtn |= cbrtn;
}

void sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn) {
	siopcb->cbrtn &= ~cbrtn;
}

static bool_t write_with_retry(const char *src, int len) {
	int retry_times;
	for (retry_times = 5; retry_times > 0; retry_times--) {
		int bytes_write = hv_console_write((HV_VirtAddr)src, len);
		if (bytes_write == len) return true;
		if (bytes_write < 0)	return false;
		src += bytes_write;
		len -= bytes_write;
		tslp_tsk(10);
	}
	return false;
}

void hvc_write_task(intptr_t unused) {
	// Generate prefix
	intptr_t core = x_prc_index();
	assert(core <= 81);
	char prefix[] = "<0,0> ";
	prefix[1] += core % TILEGX_CLIENT_WD;
	prefix[3] += core / TILEGX_CLIENT_WD;

	SIOPCB *my_siopcb = &(get_my_p_pcb()->target_pcb.siopcb);

	for (;;) {
//		wai_sem(HVC_WRITE_SEM);

//		sig_sem(HVC_WRITE_SEM);
		if (!my_siopcb->send_request) {
			if (my_siopcb->cbrtn & SIO_RDY_SND) sio_rdy_snd(my_siopcb->exinf);
			tslp_tsk(5);
			continue;
		}
		wai_sem(HVC_WRITE_SEM);

		bool_t res;
		res = write_with_retry(prefix, strlen(prefix));
		assert(res);
		res = write_with_retry(my_siopcb->send_buffer, my_siopcb->send_buffer_len);
		assert(res);

			if (my_siopcb->send_buffer[my_siopcb->send_buffer_len - 1] != '\n') hv_console_putc('\n');
			my_siopcb->send_buffer_len = 0;
			my_siopcb->send_request = false;

//		}
//		if ((my_siopcb->cbrtn & SIO_RDY_SND) && !my_siopcb->send_request)
		sig_sem(HVC_WRITE_SEM);
	}
}

// DUMMY BELOW THIS LINE


void sio_cls_por(SIOPCB *siopcb) {
	syslog(LOG_EMERG, "%s(): not supported yet.", __FUNCTION__);
}
