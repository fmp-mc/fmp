#include <kernel.h>
#include "kernel_impl.h"
#include "target_pcb.h"
#include "target_serial.h"
#include "arch_debug.h"

/**
 * Lock CPU
 */

void TOPPERS_sil_force_unl_spn() {
}

/**
 * Sense context
 */




bool_t exc_sense_intmask(void *p_excinf) {
    return false;
}

/**
 * Interrupts
 */

PRI t_get_ipm(void) {
    return 0;
}

PRI i_get_ipm(void) {
    return 0;
}

void t_set_ipm(PRI intpri) {
}

void i_set_ipm(PRI intpri) {
}

void x_define_inh(INHNO inhno, FP int_entry) {
}

void x_config_int(INTNO intno, ATR intatr, PRI intpri) {
}

void x_define_exc(EXCNO excno, FP exc_entry) {
}


/**
 * Dispatch
 */

void dispatch_and_migrate(ID prcid) {
	assert(false);
	debug_loop();
}

void exit_and_migrate(ID prcid) {
	assert(false);
	debug_loop();
}

/**
 * Kernel
 */

void target_initialize(void) {
	arch_initialize();
}

void call_exit_kernel(void) {
	// TODO: switch context and stack
	exit_kernel();
}

void target_exit(void) {
	hv_power_off();
}

void sil_get_pid(ID *p_prcid) {
	*p_prcid = x_prc_index() + 1;
}

/**
 * Serial & log
 */





/**
 * Assert
 */

void TOPPERS_assert_abort(void) {
}

#if 0 // Legacy code
uint_t x_prc_index(void) {
//    printf("%s(): Dummy.", __FUNCTION__);
    return 0;
}

bool_t x_sense_mprc(void) {
    return false;
}
void target_fput_log(char c) {
}


void start_dispatch() {
}

void dispatch() {
}


void i_lock_cpu() {
}

void t_lock_cpu() {
}

void i_unlock_cpu() {
}

void t_unlock_cpu() {
}

bool_t sense_context(void) {
    return false;
}

void exit_and_dispatch(void) {
}

#endif
