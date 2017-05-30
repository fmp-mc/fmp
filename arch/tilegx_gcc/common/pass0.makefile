# [[[cog
# import cog, pass0
# if pass0.kernel_spin_lock == 'tas':
#     cog.outl('CDEFS += -DKERNEL_SPIN_LOCK_TAS')
# elif pass0.kernel_spin_lock == 'tatas':
#     cog.outl('CDEFS += -DKERNEL_SPIN_LOCK_TATAS')
# elif pass0.kernel_spin_lock == 'backoff':
#     cog.outl('CDEFS += -DKERNEL_SPIN_LOCK_BACKOFF')
# elif pass0.kernel_spin_lock == 'k42':
#     cog.outl('CDEFS += -DKERNEL_SPIN_LOCK_K42')
# else:
#     raise
#
# if pass0.load_balancer == 'ishida':
#     cog.outl('include $(EV3RT_SDK_LIB_DIR)/loadbalancer/Makefile')
#     cog.outl('COPTS += -DENABLE_LOAD_BALANCE')
# elif pass0.load_balancer != None:
#     raise
#
# if pass0.memory_allocator == 'newlib':
#     cog.outl('include $(EV3RT_SDK_LIB_DIR)/tlsf/Makefile')
# elif pass0.memory_allocator == 'tlsf':
#     cog.outl('include $(EV3RT_SDK_LIB_DIR)/tlsf/Makefile')
#     cog.outl('CDEFS += -DUSE_TLSF_ALLOCATOR')
# elif pass0.memory_allocator == 'hoard':
#     cog.outl('include $(EV3RT_SDK_LIB_DIR)/hoard/Makefile')
# elif pass0.memory_allocator != None:
#     raise
#
# if pass0.opt_page_table == None:
#     cog.outl('CDEFS += -DOPTIMIZE_PAGE_TABLE=0')
# elif pass0.opt_page_table == 'page':
#     cog.outl('CDEFS += -DOPTIMIZE_PAGE_TABLE=1')
# elif pass0.opt_page_table == 'section':
#     cog.outl('CDEFS += -DOPTIMIZE_PAGE_TABLE=2')
# else:
#     raise
#
# if pass0.opt_my_p_runtsk == 'fast':
#     cog.outl('CDEFS += -DSUPPORT_GET_P_RUNTSK_FAST')
# elif pass0.opt_my_p_runtsk == 'spr':
#     cog.outl('CDEFS += -DSUPPORT_GET_P_RUNTSK_SPR')
# elif pass0.opt_my_p_runtsk != None:
#     raise
#
# if pass0.math_library == 'glibc':
#     cog.outl('USE_GLIBC_LIBM=1')
# else:
#     raise
# ]]]
CDEFS += -DKERNEL_SPIN_LOCK_BACKOFF
include $(EV3RT_SDK_LIB_DIR)/hoard/Makefile
CDEFS += -DOPTIMIZE_PAGE_TABLE=2
CDEFS += -DSUPPORT_GET_P_RUNTSK_SPR
USE_GLIBC_LIBM=1
# [[[end]]]
