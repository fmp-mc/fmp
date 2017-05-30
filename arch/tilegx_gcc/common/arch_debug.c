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
#include "arch_debug.h"
#include "target_syssvc.h"
#include "kernel_cfg.h"
#include "arch_debug_perf.h"

#include <string.h>

void debug_loop() {
	call_backtracer();
	register long tp asm ("tp");
	register long lr asm ("lr");
	register long r0 asm ("r0");
	syslog(LOG_EMERG, "tp = %x, lr = %x, r0=%x", tp, lr, r0);
	syslog(LOG_EMERG, "pid=%d, nest count = %d", x_prc_index(), ((PCB*)(tp))->target_pcb.excpt_nest_count);
	// syslog(LOG_EMERG, "_kernel_p_tcb_table[0].pc %x", _kernel_p_tcb_table[0]->tskctxb.pc);
	syslog(LOG_EMERG, "p_runtsk ID %d", ((PCB*)(tp))->p_runtsk == NULL ? -1 : TSKID(((PCB*)(tp))->p_runtsk));
	syslog(LOG_EMERG, "p_schedtsk ID %d", ((PCB*)(tp))->p_schedtsk == NULL ? -1 : TSKID(((PCB*)(tp))->p_schedtsk));
	syslog(LOG_EMERG, "EX_CONTEXT_K_0 %x", __insn_mfspr(SPR_EX_CONTEXT_K_0));
	const char *str = "debug_loop!\n";
    hv_console_write(str, strlen(str));
    ext_ker();
    hv_power_off();
}

void ill_handler(void) {
	syslog(LOG_EMERG, "Illegal instruction interrupt occurs.");
	syslog(LOG_EMERG, "Illegal Virtual Address PC: 0x%x.", __insn_mfspr(SPR_ILL_VA_PC));
	syslog(LOG_EMERG, "Illegal Translation Reason: 0x%x.", __insn_mfspr(SPR_ILL_TRANS_REASON));
	syslog(LOG_EMERG, "PC in EX_CONTEXT_K_0: 0x%x.", __insn_mfspr(SPR_EX_CONTEXT_K_0));
	debug_loop();
}

void ill_trans_handler(void) {
	syslog(LOG_EMERG, "Illegal instruction translation interrupt occurs.");
	syslog(LOG_EMERG, "Illegal Virtual Address PC: 0x%x.", __insn_mfspr(SPR_ILL_VA_PC));
	syslog(LOG_EMERG, "Illegal Translation Reason: 0x%x.", __insn_mfspr(SPR_ILL_TRANS_REASON));
	syslog(LOG_EMERG, "PC in EX_CONTEXT_K_0: 0x%x.", __insn_mfspr(SPR_EX_CONTEXT_K_0));
	debug_loop();
}

void unalign_data_handler(void) {
	syslog(LOG_EMERG, "Unaligned data interrupt occurs.");
	syslog(LOG_EMERG, "PC in EX_CONTEXT_K_0: 0x%x.", __insn_mfspr(SPR_EX_CONTEXT_K_0));
	debug_loop();
}

void itlb_miss_handler() {
	syslog(LOG_EMERG, "prcid %d: ITLB_MISS, fatal", x_prc_index());
	debug_loop();
}

void dump_stack_frame(uint64_t *frame_pointer) {
	if (frame_pointer) {
		syslog(LOG_EMERG, "BT>> lr=%p, sp=%p", frame_pointer[0], frame_pointer[1]);
		dump_stack_frame(frame_pointer[1]);
	}
}

/** All registers from the thread of execution that incurred an interrupt.
 */
struct fmp_int_entry_saved_regs_full
{
//  uint64_t intmask_1;           /**< Previous interrupt mask word 1 */
//  uint64_t intmask_0;           /**< Previous interrupt mask word 0 */
  uint64_t int_num;                  /**< Saved link (return address) register */
  uint64_t dummy[30];       /**< Saved registers (array index 0 is r53,*/
  uint64_t ex_context_0;        /**< EX_CONTEXT_BME_0 after interrupt */
  uint64_t ex_context_1;        /**< EX_CONTEXT_BME_1 after interrupt */
  uint64_t r29_to_r0[30];       /**< Saved registers (array index 0 is r53,
                                 *   array index 1 is r52, and so forth) */
  uint64_t lr;                  /**< Saved link (return address) register */
//  uint64_t sp;                  /**< Saved stack pointer */
};

extern STK_T *const _kernel_istk_table[TNUM_PRCID];

void dump_fmp_int_entry_saved_regs_full(struct fmp_int_entry_saved_regs_full *sr) {

#if 0
	if(x_prc_index()==0) {
	syslog(LOG_EMERG, "lr=%d> sp: %016x, ex_context_0: %016x, excpt_nest_count: %d", sr->lr/*x_prc_index()*/, sr, (uint32_t)sr->ex_context_0, get_my_p_tpcb()->excpt_nest_count);
	if (get_my_p_tpcb()->excpt_nest_count == 0) syslog(LOG_EMERG, "p_tinib %016x", get_my_p_pcb()->p_runtsk->p_tinib);
	//for (int i = 0; i <100000; ++i); // delay?
	}
#endif
	if (get_my_p_pcb()->kerflg) {
		syslog(LOG_NOTICE, "prc %d int_num=%d, lr=%x in dump_fmp_int_entry_saved_regs_full!", x_prc_index(), sr->int_num, sr->lr);
		return;
	} else return;
	if (get_my_p_tpcb()->excpt_nest_count != 0) { // interrupt context
		if ((uint64_t)sr <= (uint64_t)_kernel_istk_table[x_prc_index()]) {
			syslog(LOG_EMERG, "prc %d interrupt stack overflow!", x_prc_index());
			debug_loop();
		}
	} else { // task context
		if ((uint64_t)sr <= (uint64_t)get_my_p_pcb()->p_runtsk->p_tinib->stk) {
			syslog(LOG_EMERG, "prc %d task stack overflow!", x_prc_index());
			debug_loop();
		}
	}
#if 0

#endif
}

#if defined(DEBUG_CPU_USAGE)

typedef struct {
	uint64_t busy;
	uint64_t start;
	uint32_t usage;
	bool_t   idle;
} t_cpu_usage;

static t_cpu_usage cpu_usage[TNUM_PRCID];

void debug_dsp_enter() {
	PCB* pcb = get_my_p_pcb();
	//if (pcb->prcid != 1) return;
	if (pcb->p_runtsk == NULL) { // From idle to busy
		assert(pcb->p_schedtsk != NULL);
		cpu_usage[pcb->prcid - 1].start = __insn_mfspr(SPR_CYCLE);
		//syslog(LOG_NOTICE, "idle, start=%lu", cpu_usage[pcb->prcid - 1].start);
	} else if (pcb->p_schedtsk == NULL) { // From busy to idle
		assert(pcb->p_runtsk != NULL);
		cpu_usage[pcb->prcid - 1].busy += __insn_mfspr(SPR_CYCLE) - cpu_usage[pcb->prcid - 1].start;
		cpu_usage[pcb->prcid - 1].idle = true;
		//syslog(LOG_NOTICE, "busy=%lu, start=%lu", cpu_usage[pcb->prcid - 1].busy, cpu_usage[pcb->prcid - 1].start);
	}
}

void debug_dsp_leave() {
	PCB* pcb = get_my_p_pcb();
	//if (pcb->prcid != 1) return;
	if (cpu_usage[pcb->prcid - 1].idle) { // From idle to busy
		assert(pcb->p_schedtsk != NULL);
		cpu_usage[pcb->prcid - 1].start = __insn_mfspr(SPR_CYCLE);
		cpu_usage[pcb->prcid - 1].idle = false;
		//syslog(LOG_NOTICE, "end idle, start=%lu", cpu_usage[pcb->prcid - 1].start);
	} else if (pcb->p_schedtsk == NULL) { // From busy to idle
		assert(pcb->p_runtsk != NULL);
		cpu_usage[pcb->prcid - 1].busy += __insn_mfspr(SPR_CYCLE) - cpu_usage[pcb->prcid - 1].start;
		//syslog(LOG_NOTICE, "busy=%lu, start=%lu", cpu_usage[pcb->prcid - 1].busy, cpu_usage[pcb->prcid - 1].start);
	}
}

void calculate_cpu_usage(intptr_t unused) {
	uint64_t now = __insn_mfspr(SPR_CYCLE);

	PCB* pcb = get_my_p_pcb();
	if (pcb->p_runtsk != NULL) { // update busy
		cpu_usage[pcb->prcid - 1].busy += now - cpu_usage[pcb->prcid - 1].start;
		//syslog(LOG_NOTICE, "busy=%lu", cpu_usage[pcb->prcid - 1].busy);
	}

	cpu_usage[pcb->prcid - 1].usage = cpu_usage[pcb->prcid - 1].busy * 100 / ((cpu_hz() / 1000) * CALC_CPU_USAGE_PRD);
	cpu_usage[pcb->prcid - 1].busy  = 0;
	cpu_usage[pcb->prcid - 1].start = now;
	syslog(LOG_NOTICE, "CPU %d usage: %d%%", pcb->prcid, (int32_t)cpu_usage[pcb->prcid - 1].usage);
	//syslog(LOG_NOTICE, "busy=%lu, now=%lu", cpu_usage[pcb->prcid - 1].busy, now);
}

#endif

#if defined(DEBUG_PERF)

struct perf_event_pair {
    const char *name;
    int         event;
};

static struct perf_event_pair perf_events[] = {
    {"TMC_PERF_INVALID", TMC_PERF_INVALID},
    {"TMC_PERF_ZERO", TMC_PERF_ZERO},
    {"TMC_PERF_ONE", TMC_PERF_ONE},
    {"TMC_PERF_PASS_WRITTEN", TMC_PERF_PASS_WRITTEN},
    {"TMC_PERF_FAIL_WRITTEN", TMC_PERF_FAIL_WRITTEN},
    {"TMC_PERF_DONE_WRITTEN", TMC_PERF_DONE_WRITTEN},
    {"TMC_PERF_SBOX_QUIESCED", TMC_PERF_SBOX_QUIESCED},
    {"TMC_PERF_CBOX_QUIESCED", TMC_PERF_CBOX_QUIESCED},
    {"TMC_PERF_TRACE_SAMPLE", TMC_PERF_TRACE_SAMPLE},
    {"TMC_PERF_CYCLE_12", TMC_PERF_CYCLE_12},
    {"TMC_PERF_CYCLE_8", TMC_PERF_CYCLE_8},
    {"TMC_PERF_CYCLE_4", TMC_PERF_CYCLE_4},
    {"TMC_PERF_ICOH", TMC_PERF_ICOH},
    {"TMC_PERF_L1D_FILL_STALL", TMC_PERF_L1D_FILL_STALL},
    {"TMC_PERF_CBOX_FULL_STALL", TMC_PERF_CBOX_FULL_STALL},
    {"TMC_PERF_LOAD_HIT_STALL", TMC_PERF_LOAD_HIT_STALL},
    {"TMC_PERF_LOAD_STALL", TMC_PERF_LOAD_STALL},
    {"TMC_PERF_ALU_SRC_STALL", TMC_PERF_ALU_SRC_STALL},
    {"TMC_PERF_IDN_SRC_STALL", TMC_PERF_IDN_SRC_STALL},
    {"TMC_PERF_UDN_SRC_STALL", TMC_PERF_UDN_SRC_STALL},
    {"TMC_PERF_MF_STALL", TMC_PERF_MF_STALL},
    {"TMC_PERF_SLOW_SPR_STALL", TMC_PERF_SLOW_SPR_STALL},
    {"TMC_PERF_NETWORK_DEST_STALL", TMC_PERF_NETWORK_DEST_STALL},
    {"TMC_PERF_INSTRUCTION_STALL", TMC_PERF_INSTRUCTION_STALL},
    {"TMC_PERF_PFB_HIT_IN_PFB", TMC_PERF_PFB_HIT_IN_PFB},
    {"TMC_PERF_PFB_HIT", TMC_PERF_PFB_HIT},
    {"TMC_PERF_CBOX_RESP", TMC_PERF_CBOX_RESP},
    {"TMC_PERF_MEM_OP", TMC_PERF_MEM_OP},
    {"TMC_PERF_CBOX_REQ", TMC_PERF_CBOX_REQ},
    {"TMC_PERF_ITLB_MISS_INTERRUPT", TMC_PERF_ITLB_MISS_INTERRUPT},
    {"TMC_PERF_INTERRUPT", TMC_PERF_INTERRUPT},
    {"TMC_PERF_ICACHE_FILL_PEND", TMC_PERF_ICACHE_FILL_PEND},
    {"TMC_PERF_ICACHE_FILL", TMC_PERF_ICACHE_FILL},
    {"TMC_PERF_WAY_MISPREDICT", TMC_PERF_WAY_MISPREDICT},
    {"TMC_PERF_COND_BRANCH_PRED_CORRECT", TMC_PERF_COND_BRANCH_PRED_CORRECT},
    {"TMC_PERF_COND_BRANCH_PRED_INCORRECT", TMC_PERF_COND_BRANCH_PRED_INCORRECT},
    {"TMC_PERF_INSTRUCTION_BUNDLE", TMC_PERF_INSTRUCTION_BUNDLE},
    {"TMC_PERF_RESTART", TMC_PERF_RESTART},
    {"TMC_PERF_USED_RAS", TMC_PERF_USED_RAS},
    {"TMC_PERF_RAS_CORRECT", TMC_PERF_RAS_CORRECT},
    {"TMC_PERF_COND_BRANCH_NO_PREDICT", TMC_PERF_COND_BRANCH_NO_PREDICT},
    {"TMC_PERF_TLB", TMC_PERF_TLB},
    {"TMC_PERF_READ", TMC_PERF_READ},
    {"TMC_PERF_WRITE", TMC_PERF_WRITE},
    {"TMC_PERF_TLB_EXCEPTION", TMC_PERF_TLB_EXCEPTION},
    {"TMC_PERF_READ_MISS", TMC_PERF_READ_MISS},
    {"TMC_PERF_WRITE_MISS", TMC_PERF_WRITE_MISS},
    {"TMC_PERF_L1_OPCODE_VALID", TMC_PERF_L1_OPCODE_VALID},
    {"TMC_PERF_L1_OPCODE_LD_VALID", TMC_PERF_L1_OPCODE_LD_VALID},
    {"TMC_PERF_L1_OPCODE_ST_VALID", TMC_PERF_L1_OPCODE_ST_VALID},
    {"TMC_PERF_L1_OPCODE_ATOMIC_VALID", TMC_PERF_L1_OPCODE_ATOMIC_VALID},
    {"TMC_PERF_L1_OPCODE_FLUSH_VALID", TMC_PERF_L1_OPCODE_FLUSH_VALID},
    {"TMC_PERF_L1_OPCODE_INV_VALID", TMC_PERF_L1_OPCODE_INV_VALID},
    {"TMC_PERF_L1_OPCODE_FINV_VALID", TMC_PERF_L1_OPCODE_FINV_VALID},
    {"TMC_PERF_L1_OPCODE_MF_VALID", TMC_PERF_L1_OPCODE_MF_VALID},
    {"TMC_PERF_L1_OPCODE_PFETCH_VALID", TMC_PERF_L1_OPCODE_PFETCH_VALID},
    {"TMC_PERF_L1_OPCODE_WH64_VALID", TMC_PERF_L1_OPCODE_WH64_VALID},
    {"TMC_PERF_L1_OPCODE_DTLBPR_VALID", TMC_PERF_L1_OPCODE_DTLBPR_VALID},
    {"TMC_PERF_L1_OPCODE_FWB_VALID", TMC_PERF_L1_OPCODE_FWB_VALID},
    {"TMC_PERF_L1_OPCODE_LD_NON_TEMPORAL_VALID", TMC_PERF_L1_OPCODE_LD_NON_TEMPORAL_VALID},
    {"TMC_PERF_L1_OPCODE_ST_NON_TEMPORAL_VALID", TMC_PERF_L1_OPCODE_ST_NON_TEMPORAL_VALID},
    {"TMC_PERF_SNOOP_INCREMENT_READ", TMC_PERF_SNOOP_INCREMENT_READ},
    {"TMC_PERF_SNOOP_NON_INCREMENT_READ", TMC_PERF_SNOOP_NON_INCREMENT_READ},
    {"TMC_PERF_SNOOP_WRITE", TMC_PERF_SNOOP_WRITE},
    {"TMC_PERF_SNOOP_IO_READ", TMC_PERF_SNOOP_IO_READ},
    {"TMC_PERF_SNOOP_IO_WRITE", TMC_PERF_SNOOP_IO_WRITE},
    {"TMC_PERF_LOCAL_DATA_READ", TMC_PERF_LOCAL_DATA_READ},
    {"TMC_PERF_LOCAL_WRITE", TMC_PERF_LOCAL_WRITE},
    {"TMC_PERF_LOCAL_INSTRUCTION_READ", TMC_PERF_LOCAL_INSTRUCTION_READ},
    {"TMC_PERF_REMOTE_DATA_READ", TMC_PERF_REMOTE_DATA_READ},
    {"TMC_PERF_REMOTE_WRITE", TMC_PERF_REMOTE_WRITE},
    {"TMC_PERF_REMOTE_INSTRUCTION_READ", TMC_PERF_REMOTE_INSTRUCTION_READ},
    {"TMC_PERF_COHERENCE_INVALIDATION", TMC_PERF_COHERENCE_INVALIDATION},
    {"TMC_PERF_SNOOP_INCREMENT_READ_MISS", TMC_PERF_SNOOP_INCREMENT_READ_MISS},
    {"TMC_PERF_SNOOP_NON_INCREMENT_READ_MISS", TMC_PERF_SNOOP_NON_INCREMENT_READ_MISS},
    {"TMC_PERF_SNOOP_WRITE_MISS", TMC_PERF_SNOOP_WRITE_MISS},
    {"TMC_PERF_SNOOP_IO_READ_MISS", TMC_PERF_SNOOP_IO_READ_MISS},
    {"TMC_PERF_SNOOP_IO_WRITE_MISS", TMC_PERF_SNOOP_IO_WRITE_MISS},
    {"TMC_PERF_LOCAL_DATA_READ_MISS", TMC_PERF_LOCAL_DATA_READ_MISS},
    {"TMC_PERF_LOCAL_WRITE_MISS", TMC_PERF_LOCAL_WRITE_MISS},
    {"TMC_PERF_LOCAL_INSTRUCTION_READ_MISS", TMC_PERF_LOCAL_INSTRUCTION_READ_MISS},
    {"TMC_PERF_REMOTE_DATA_READ_MISS", TMC_PERF_REMOTE_DATA_READ_MISS},
    {"TMC_PERF_REMOTE_WRITE_MISS", TMC_PERF_REMOTE_WRITE_MISS},
    {"TMC_PERF_REMOTE_INSTRUCTION_READ_MISS", TMC_PERF_REMOTE_INSTRUCTION_READ_MISS},
    {"TMC_PERF_COHERENCE_INVALIDATION_HIT", TMC_PERF_COHERENCE_INVALIDATION_HIT},
    {"TMC_PERF_CACHE_WRITEBACK", TMC_PERF_CACHE_WRITEBACK},
    {"TMC_PERF_SDN_STARVED", TMC_PERF_SDN_STARVED},
    {"TMC_PERF_RDN_STARVED", TMC_PERF_RDN_STARVED},
    {"TMC_PERF_QDN_STARVED", TMC_PERF_QDN_STARVED},
    {"TMC_PERF_SKF_STARVED", TMC_PERF_SKF_STARVED},
    {"TMC_PERF_RTF_STARVED", TMC_PERF_RTF_STARVED},
    {"TMC_PERF_IREQ_STARVED", TMC_PERF_IREQ_STARVED},
    {"TMC_PERF_ITLB_OLOC_CACHE_MISS", TMC_PERF_ITLB_OLOC_CACHE_MISS},
    {"TMC_PERF_DTLB_OLOC_CACHE_MISS", TMC_PERF_DTLB_OLOC_CACHE_MISS},
    {"TMC_PERF_LOCAL_WRITE_BUFFER_ALLOC", TMC_PERF_LOCAL_WRITE_BUFFER_ALLOC},
    {"TMC_PERF_REMOTE_WRITE_BUFFER_ALLOC", TMC_PERF_REMOTE_WRITE_BUFFER_ALLOC},
    {"TMC_PERF_ARB_VALID", TMC_PERF_ARB_VALID},
    {"TMC_PERF_MDF_WRITE", TMC_PERF_MDF_WRITE},
    {"TMC_PERF_LDB_READ", TMC_PERF_LDB_READ},
    {"TMC_PERF_L2_OPCODE_LD_VALID", TMC_PERF_L2_OPCODE_LD_VALID},
    {"TMC_PERF_L2_OPCODE_ST_VALID", TMC_PERF_L2_OPCODE_ST_VALID},
    {"TMC_PERF_L2_OPCODE_ATOMIC_VALID", TMC_PERF_L2_OPCODE_ATOMIC_VALID},
    {"TMC_PERF_L2_OPCODE_FLUSH_VALID", TMC_PERF_L2_OPCODE_FLUSH_VALID},
    {"TMC_PERF_L2_OPCODE_INV_VALID", TMC_PERF_L2_OPCODE_INV_VALID},
    {"TMC_PERF_L2_OPCODE_FINV_VALID", TMC_PERF_L2_OPCODE_FINV_VALID},
    {"TMC_PERF_L2_OPCODE_MF_VALID", TMC_PERF_L2_OPCODE_MF_VALID},
    {"TMC_PERF_L2_OPCODE_PFETCH_VALID", TMC_PERF_L2_OPCODE_PFETCH_VALID},
    {"TMC_PERF_L2_OPCODE_WH64_VALID", TMC_PERF_L2_OPCODE_WH64_VALID},
    {"TMC_PERF_L2_OPCODE_FWB_VALID", TMC_PERF_L2_OPCODE_FWB_VALID},
    {"TMC_PERF_L2_OPCODE_LD_NON_TEMPORAL_VALID", TMC_PERF_L2_OPCODE_LD_NON_TEMPORAL_VALID},
    {"TMC_PERF_L2_OPCODE_ST_NON_TEMPORAL_VALID", TMC_PERF_L2_OPCODE_ST_NON_TEMPORAL_VALID},
    {"TMC_PERF_L2_OPCODE_LD_NOFIL_VALID", TMC_PERF_L2_OPCODE_LD_NOFIL_VALID},
    {"TMC_PERF_L2_OPCODE_LD_NOFIL_NON_TEMPORAL_VALID", TMC_PERF_L2_OPCODE_LD_NOFIL_NON_TEMPORAL_VALID},
    {"TMC_PERF_L2_OPCODE_RDN_VALID", TMC_PERF_L2_OPCODE_RDN_VALID},
    {"TMC_PERF_L2_OPCODE_QDN_VALID", TMC_PERF_L2_OPCODE_QDN_VALID},
    {"TMC_PERF_L2_OPCODE_IO_READ_VALID", TMC_PERF_L2_OPCODE_IO_READ_VALID},
    {"TMC_PERF_L2_OPCODE_IO_WRITE_VALID", TMC_PERF_L2_OPCODE_IO_WRITE_VALID},
    {"TMC_PERF_L2_OPCODE_I_STREAM_VALID", TMC_PERF_L2_OPCODE_I_STREAM_VALID},
    {"TMC_PERF_L2_OPCODE_MDF_VALID", TMC_PERF_L2_OPCODE_MDF_VALID},
    {"TMC_PERF_L2_OPCODE_IREQ_IV_VALID", TMC_PERF_L2_OPCODE_IREQ_IV_VALID},
    {"TMC_PERF_UDN_PACKET_SENT", TMC_PERF_UDN_PACKET_SENT},
    {"TMC_PERF_UDN_WORD_SENT", TMC_PERF_UDN_WORD_SENT},
    {"TMC_PERF_UDN_BUBBLE", TMC_PERF_UDN_BUBBLE},
    {"TMC_PERF_UDN_CONGESTION", TMC_PERF_UDN_CONGESTION},
    {"TMC_PERF_IDN_PACKET_SENT", TMC_PERF_IDN_PACKET_SENT},
    {"TMC_PERF_IDN_WORD_SENT", TMC_PERF_IDN_WORD_SENT},
    {"TMC_PERF_IDN_BUBBLE", TMC_PERF_IDN_BUBBLE},
    {"TMC_PERF_IDN_CONGESTION", TMC_PERF_IDN_CONGESTION},
    {"TMC_PERF_RDN_PACKET_SENT", TMC_PERF_RDN_PACKET_SENT},
    {"TMC_PERF_RDN_WORD_SENT", TMC_PERF_RDN_WORD_SENT},
    {"TMC_PERF_RDN_BUBBLE", TMC_PERF_RDN_BUBBLE},
    {"TMC_PERF_RDN_CONGESTION", TMC_PERF_RDN_CONGESTION},
    {"TMC_PERF_SDN_PACKET_SENT", TMC_PERF_SDN_PACKET_SENT},
    {"TMC_PERF_SDN_WORD_SENT", TMC_PERF_SDN_WORD_SENT},
    {"TMC_PERF_SDN_BUBBLE", TMC_PERF_SDN_BUBBLE},
    {"TMC_PERF_SDN_CONGESTION", TMC_PERF_SDN_CONGESTION},
    {"TMC_PERF_QDN_PACKET_SENT", TMC_PERF_QDN_PACKET_SENT},
    {"TMC_PERF_QDN_WORD_SENT", TMC_PERF_QDN_WORD_SENT},
    {"TMC_PERF_QDN_BUBBLE", TMC_PERF_QDN_BUBBLE},
    {"TMC_PERF_QDN_CONGESTION", TMC_PERF_QDN_CONGESTION},
    {"TMC_PERF_UDN_DEMUX_STALL", TMC_PERF_UDN_DEMUX_STALL},
    {"TMC_PERF_IDN_DEMUX_STALL", TMC_PERF_IDN_DEMUX_STALL},
    {"TMC_PERF_WATCH", TMC_PERF_WATCH},
    {"TMC_PERF_BCST0", TMC_PERF_BCST0},
    {"TMC_PERF_BCST1", TMC_PERF_BCST1},
    {"TMC_PERF_BCST2", TMC_PERF_BCST2},
    {"TMC_PERF_BCST3", TMC_PERF_BCST3},
    {"TMC_PERF_PCNT0", TMC_PERF_PCNT0},
    {"TMC_PERF_PCNT1", TMC_PERF_PCNT1},
    {"TMC_PERF_AUX_PCNT0", TMC_PERF_AUX_PCNT0},
    {"TMC_PERF_AUX_PCNT1", TMC_PERF_AUX_PCNT1},
};

static int eventIndex[4];

void perf_initialize(const char *event1, const char *event2, const char *event3, const char *event4) {
    tmc_perf_clear_counters();
    const char *names[] = {event1, event2, event3, event4};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < sizeof(perf_events) / sizeof(perf_events[0]); j++) {
            if (strcmp(perf_events[j].name, names[i]) == 0) {
                eventIndex[i] = j;
                break;
            }
        }
    }
    tmc_perf_setup_counters(perf_events[eventIndex[0]].event, perf_events[eventIndex[1]].event, perf_events[eventIndex[2]].event, perf_events[eventIndex[3]].event);
#if 0
    // OMIT: TMC_PERF_INVALID, TMC_PERF_ZERO, TMC_PERF_ONE, TMC_PERF_PASS_WRITTEN, TMC_PERF_FAIL_WRITTEN, TMC_PERF_DONE_WRITTEN,
    // OMIT: TMC_PERF_TRACE_SAMPLE, TMC_PERF_CYCLE_12, TMC_PERF_CYCLE_8, TMC_PERF_CYCLE_4,
    tmc_perf_setup_counters(TMC_PERF_SBOX_QUIESCED, TMC_PERF_CBOX_QUIESCED, TMC_PERF_ICOH, TMC_PERF_L1D_FILL_STALL);
    tmc_perf_setup_counters(TMC_PERF_CBOX_FULL_STALL, TMC_PERF_LOAD_HIT_STALL, TMC_PERF_LOAD_STALL, TMC_PERF_ALU_SRC_STALL);
    tmc_perf_setup_counters(TMC_PERF_IDN_SRC_STALL, TMC_PERF_UDN_SRC_STALL, TMC_PERF_MF_STALL, TMC_PERF_SLOW_SPR_STALL);
    tmc_perf_setup_counters(TMC_PERF_NETWORK_DEST_STALL, TMC_PERF_INSTRUCTION_STALL, TMC_PERF_PFB_HIT_IN_PFB, TMC_PERF_PFB_HIT);
    tmc_perf_setup_counters(TMC_PERF_CBOX_RESP, TMC_PERF_MEM_OP, TMC_PERF_CBOX_REQ, TMC_PERF_ITLB_MISS_INTERRUPT);
    tmc_perf_setup_counters(TMC_PERF_INTERRUPT, TMC_PERF_ICACHE_FILL_PEND, TMC_PERF_ICACHE_FILL, TMC_PERF_WAY_MISPREDICT);
    tmc_perf_setup_counters(TMC_PERF_COND_BRANCH_PRED_CORRECT, TMC_PERF_COND_BRANCH_PRED_INCORRECT, TMC_PERF_INSTRUCTION_BUNDLE, TMC_PERF_RESTART);
    tmc_perf_setup_counters(TMC_PERF_USED_RAS, TMC_PERF_RAS_CORRECT, TMC_PERF_COND_BRANCH_NO_PREDICT, TMC_PERF_TLB);
    tmc_perf_setup_counters(TMC_PERF_READ, TMC_PERF_WRITE, TMC_PERF_TLB_EXCEPTION, TMC_PERF_READ_MISS);
    tmc_perf_setup_counters(TMC_PERF_WRITE_MISS, TMC_PERF_L1_OPCODE_VALID, TMC_PERF_L1_OPCODE_LD_VALID, TMC_PERF_L1_OPCODE_ST_VALID);
    tmc_perf_setup_counters(TMC_PERF_L1_OPCODE_ATOMIC_VALID, TMC_PERF_L1_OPCODE_FLUSH_VALID, TMC_PERF_L1_OPCODE_INV_VALID, TMC_PERF_L1_OPCODE_FINV_VALID);
    tmc_perf_setup_counters(TMC_PERF_L1_OPCODE_MF_VALID, TMC_PERF_L1_OPCODE_PFETCH_VALID, TMC_PERF_L1_OPCODE_DTLBPR_VALID, TMC_PERF_L1_OPCODE_FWB_VALID);
    tmc_perf_setup_counters(TMC_PERF_L1_OPCODE_LD_NON_TEMPORAL_VALID, TMC_PERF_L1_OPCODE_ST_NON_TEMPORAL_VALID, TMC_PERF_SNOOP_INCREMENT_READ, TMC_PERF_SNOOP_NON_INCREMENT_READ,);
    tmc_perf_setup_counters(TMC_PERF_SNOOP_WRITE, TMC_PERF_SNOOP_IO_READ, TMC_PERF_SNOOP_IO_WRITE, TMC_PERF_LOCAL_DATA_READ);
    tmc_perf_setup_counters(TMC_PERF_LOCAL_WRITE, TMC_PERF_LOCAL_INSTRUCTION_READ, TMC_PERF_REMOTE_DATA_READ, TMC_PERF_REMOTE_WRITE);
    tmc_perf_setup_counters(TMC_PERF_REMOTE_INSTRUCTION_READ, TMC_PERF_COHERENCE_INVALIDATION, TMC_PERF_SNOOP_INCREMENT_READ_MISS, TMC_PERF_SNOOP_NON_INCREMENT_READ_MISS);
    tmc_perf_setup_counters(TMC_PERF_SNOOP_WRITE_MISS, TMC_PERF_SNOOP_IO_READ_MISS, TMC_PERF_SNOOP_IO_WRITE_MISS, TMC_PERF_LOCAL_DATA_READ_MISS);
    tmc_perf_setup_counters(TMC_PERF_LOCAL_WRITE_MISS, TMC_PERF_LOCAL_INSTRUCTION_READ_MISS, TMC_PERF_REMOTE_WRITE_MISS, TMC_PERF_REMOTE_INSTRUCTION_READ_MISS);
    tmc_perf_setup_counters(TMC_PERF_COHERENCE_INVALIDATION_HIT, TMC_PERF_CACHE_WRITEBACK, TMC_PERF_SDN_STARVED, TMC_PERF_RDN_STARVED);
    tmc_perf_setup_counters(TMC_PERF_QDN_STARVED, TMC_PERF_SKF_STARVED, TMC_PERF_RTF_STARVED, TMC_PERF_IREQ_STARVED);
    tmc_perf_setup_counters(TMC_PERF_ITLB_OLOC_CACHE_MISS, TMC_PERF_DTLB_OLOC_CACHE_MISS, TMC_PERF_LOCAL_WRITE_BUFFER_ALLOC, TMC_PERF_REMOTE_WRITE_BUFFER_ALLOC);
    tmc_perf_setup_counters(TMC_PERF_ARB_VALID, TMC_PERF_MDF_WRITE, TMC_PERF_LDB_READ, TMC_PERF_L2_OPCODE_LD_VALID);
    tmc_perf_setup_counters(TMC_PERF_L2_OPCODE_ST_VALID, TMC_PERF_L2_OPCODE_ATOMIC_VALID, TMC_PERF_L2_OPCODE_FLUSH_VALID, TMC_PERF_L2_OPCODE_INV_VALID);
    tmc_perf_setup_counters(TMC_PERF_L2_OPCODE_FINV_VALID, TMC_PERF_L2_OPCODE_MF_VALID, TMC_PERF_L2_OPCODE_PFETCH_VALID, TMC_PERF_L2_OPCODE_WH64_VALID);
    tmc_perf_setup_counters(TMC_PERF_L2_OPCODE_FWB_VALID, TMC_PERF_L2_OPCODE_LD_NON_TEMPORAL_VALID, TMC_PERF_L2_OPCODE_ST_NON_TEMPORAL_VALID, TMC_PERF_L2_OPCODE_LD_NOFIL_VALID);
    tmc_perf_setup_counters(TMC_PERF_L2_OPCODE_LD_NOFIL_NON_TEMPORAL_VALID, TMC_PERF_L2_OPCODE_RDN_VALID, TMC_PERF_L2_OPCODE_QDN_VALID, TMC_PERF_L2_OPCODE_IO_READ_VALID);
    tmc_perf_setup_counters(TMC_PERF_L2_OPCODE_IO_WRITE_VALID, TMC_PERF_L2_OPCODE_I_STREAM_VALID, TMC_PERF_L2_OPCODE_MDF_VALID, TMC_PERF_L2_OPCODE_IREQ_IV_VALID);
    tmc_perf_setup_counters(TMC_PERF_UDN_PACKET_SENT, TMC_PERF_UDN_WORD_SENT, TMC_PERF_UDN_BUBBLE, TMC_PERF_UDN_CONGESTION);
    tmc_perf_setup_counters(TMC_PERF_IDN_PACKET_SENT, TMC_PERF_IDN_WORD_SENT, TMC_PERF_IDN_BUBBLE, TMC_PERF_IDN_CONGESTION);
    tmc_perf_setup_counters();

  //! Main processor finished sending a packet to the RDN.
  TMC_PERF_RDN_PACKET_SENT,

  //! RDN word sent to an output port.  Participating ports are selected with
  //! the RDN_EVT_PORT_SEL field.
  TMC_PERF_RDN_WORD_SENT,

  //! Bubble detected on an output port.  A bubble is defined as a cycle in
  //! which no data is being sent, but the first word of a packet has already
  //! traversed the switch.  Participating ports are selected with the
  //! RDN_EVT_PORT_SEL field.
  TMC_PERF_RDN_BUBBLE,

  //! Out of credit on an output port.  Participating ports are selected with
  //! the RDN_EVT_PORT_SEL field.
  TMC_PERF_RDN_CONGESTION,

  //! Main processor finished sending a packet to the SDN.
  TMC_PERF_SDN_PACKET_SENT,

  //! SDN word sent to an output port.  Participating ports are selected with
  //! the SDN_EVT_PORT_SEL field.
  TMC_PERF_SDN_WORD_SENT,

  //! Bubble detected on an output port.  A bubble is defined as a cycle in
  //! which no data is being sent, but the first word of a packet has already
  //! traversed the switch.  Participating ports are selected with the
  //! SDN_EVT_PORT_SEL field.
  TMC_PERF_SDN_BUBBLE,

  //! Out of credit on an output port.  Participating ports are selected with
  //! the SDN_EVT_PORT_SEL field.
  TMC_PERF_SDN_CONGESTION,

  //! Main processor finished sending a packet to the QDN.
  TMC_PERF_QDN_PACKET_SENT,

  //! QDN word sent to an output port.  Participating ports are selected with
  //! the QDN_EVT_PORT_SEL field.
  TMC_PERF_QDN_WORD_SENT,

  //! Bubble detected on an output port.  A bubble is defined as a cycle in
  //! which no data is being sent, but the first word of a packet has already
  //! traversed the switch.  Participating ports are selected with the
  //! QDN_EVT_PORT_SEL field.
  TMC_PERF_QDN_BUBBLE,

  //! Out of credit on an output port.  Participating ports are selected with
  //! the QDN_EVT_PORT_SEL field.
  TMC_PERF_QDN_CONGESTION,

  //! UDN Demux stalled due to buffer full.
  TMC_PERF_UDN_DEMUX_STALL,

  //! IDN Demux stalled due to buffer full.
  TMC_PERF_IDN_DEMUX_STALL,

  //! The event occurs when the Watch SPR detects a address or address range.
  TMC_PERF_WATCH,

  //! The event occurs whenever broadcast wire-0 asserts.
  TMC_PERF_BCST0,

  //! The event occurs whenever broadcast wire-1 asserts.
  TMC_PERF_BCST1,

  //! The event occurs whenever broadcast wire-2 asserts.
  TMC_PERF_BCST2,

  //! The event occurs whenever broadcast wire-3 asserts.
  TMC_PERF_BCST3,

  //! The event occurs when Performance counter-0 overflows.
  TMC_PERF_PCNT0,

  //! The event occurs when Performance counter-1 overflows.
  TMC_PERF_PCNT1,

  //! The event occurs when Auxiliary Performance counter-0 overflows.
  TMC_PERF_AUX_PCNT0,

  //! The event occurs when Auxiliary Performance counter-1 overflows.
  TMC_PERF_AUX_PCNT1,

    //tmc_perf_setup_counters(TMC_PERF_MEM_OP, TMC_PERF_SBOX_QUIESCED, TMC_PERF_CBOX_QUIESCED, TMC_PERF_NETWORK_DEST_STALL);
#endif
}

void perf_dump() {
    struct tmc_perf_counters counters;
    tmc_perf_read_counters(&counters);
    for (int i = 0; i < 4; i++)
    syslog(LOG_NOTICE, "%s: %ld", perf_events[eventIndex[i]].name, counters.val[i]);
}

#endif
