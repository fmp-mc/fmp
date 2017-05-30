/*
 * Copyright 2014 Tilera Corporation. All Rights Reserved.
 *
 *   The source code contained or described herein and all documents
 *   related to the source code ("Material") are owned by Tilera
 *   Corporation or its suppliers or licensors.  Title to the Material
 *   remains with Tilera Corporation or its suppliers and licensors.
 *   The software is licensed under the Tilera MDE License.
 *
 *   However, Licensee may elect to use this file under the terms of the
 *   GNU Lesser General Public License version 2.1 as published by the
 *   Free Software Foundation and appearing in the file src/COPYING.LIB
 *   in the MDE distribution.  Please review the following information to
 *   ensure the GNU Lesser General Public License version 2.1 requirements
 *   will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 */

#ifndef __ARCH_DIAG_H__
#define __ARCH_DIAG_H__


#ifdef __ASSEMBLER__
#define _64bit(x) x
#else /* __ASSEMBLER__ */
#ifdef __tile__
#define _64bit(x) x ## UL
#else /* __tile__ */
#define _64bit(x) x ## ULL
#endif /* __tile__ */
#endif /* __ASSEMBLER */



/* Always zero - no event ever happens */
#define DIAG_TOP_EVENT_ZERO 0

/* Always one - an event occurs every cycle */
#define DIAG_TOP_EVENT_ONE 1

/* The event indicates that the PASS SPR was written */
#define DIAG_TOP_EVENT_PASS_WRITTEN 2

/* The event indicates that the FAIL SPR was written */
#define DIAG_TOP_EVENT_FAIL_WRITTEN 3

/* The event indicates that the DONE SPR was written */
#define DIAG_TOP_EVENT_DONE_WRITTEN 4

/* An event occurs every cycle that the tile is in the instruction issue
   quiesced state */
#define DIAG_TOP_EVENT_SBOX_QUIESCED 5

/* An event occurs every cycle that a tile is in the coherence traffic
   quiesced state */
#define DIAG_TOP_EVENT_CBOX_QUIESCED 6

/* An event occurs every time a diagnostic trace sample is triggered. */
#define DIAG_TOP_EVENT_TRACE_SAMPLE 7


/* The event occurs when bit 12 of the cycle_counter SPR is asserted.  The
   transition of this event can be used to generate periodic triggers every 4
   k cycles. */
#define DIAG_SBOX_EVENT_CYCLE_12 0

/* The event occurs when bit 8 of the cycle_counter SPR is asserted.  The
   transition of this event can be used to generate periodic triggers every
   256 cycles. */
#define DIAG_SBOX_EVENT_CYCLE_8 1

/* The event occurs when bit 4 of the cycle_counter SPR is asserted.  The
   transition of this event can be used to generate periodic triggers every 16
   cycles. */
#define DIAG_SBOX_EVENT_CYCLE_4 2

/* The event occurs when an icoh instruction completes. */
#define DIAG_SBOX_EVENT_ICOH 3

/* The event occurs when a memory operation stalls due to L1 DCache being busy
   doing a fill. */
#define DIAG_SBOX_EVENT_L1D_FILL_STALL 4

/* The event occurs when a memory operation stalls due to Cbox queue being
   full. */
#define DIAG_SBOX_EVENT_CBOX_FULL_STALL 5

/* The event occurs when an instruction 2 cycles after a load stalls due to a
   source operand being the destination.  The L1 DCache hit latency is two
   cycles, so the instruction would stall on a miss but not on a hit. */
#define DIAG_SBOX_EVENT_LOAD_HIT_STALL 6

/* The event occurs when an instruction stalls due to a source operand being
   the destination of a load instruction.  This event happens on all cycles
   that stall except for the one 2 cycles after the load, which is counted by
   LOAD_HIT_STALL event. */
#define DIAG_SBOX_EVENT_LOAD_STALL 7

/* The event occurs when an instruction stalls due to a source operand being
   the destination of an ALU instruction. */
#define DIAG_SBOX_EVENT_ALU_SRC_STALL 8

/* The event occurs when an instruction stalls due to IDN source register not
   available. */
#define DIAG_SBOX_EVENT_IDN_SRC_STALL 9

/* The event occurs when an instruction stalls due to UDN source register not
   available. */
#define DIAG_SBOX_EVENT_UDN_SRC_STALL 10

/* The event during stalls for the Memory Fence instruction. */
#define DIAG_SBOX_EVENT_MF_STALL 11

/* The event occurs during stalls to slow SPR access. */
#define DIAG_SBOX_EVENT_SLOW_SPR_STALL 12

/* The event occurs when a valid instruction in pipeline Decode stage stalls
   due to network destination full. */
#define DIAG_SBOX_EVENT_NETWORK_DEST_STALL 13

/* The event occurs when a valid instruction in pipeline Decode stage stalls
   for any reason. */
#define DIAG_SBOX_EVENT_INSTRUCTION_STALL 14
#define DIAG_SBOX_EVENT_STALL 14

/* The event occurs when an instruction lookup hits in prefetch buffer,
   already in PFB. */
#define DIAG_SBOX_EVENT_PFB_HIT_IN_PFB 15

/* The event occurs when an instruction lookup hits in prefetch buffer, either
   in the PFB or in-flight. */
#define DIAG_SBOX_EVENT_PFB_HIT 16

/* The event occurs when Cbox responds with fill data, either demand or
   prefetch. */
#define DIAG_SBOX_EVENT_CBOX_RESP 17

/* The event occurs when a memory operation is sent to Mbox. */
#define DIAG_SBOX_EVENT_MEM_OP 18

/* The event occurs when an instruction request is sent to Cbox, either demand
   or prefetch. */
#define DIAG_SBOX_EVENT_CBOX_REQ 19

/* The event occurs when an ITLB_MISS interrupt is taken. */
#define DIAG_SBOX_EVENT_ITLB_MISS_INTERRUPT 20
#define DIAG_SBOX_EVENT_ITLB_MISS_INT 20

/* The event occurs when any interrupt is taken. */
#define DIAG_SBOX_EVENT_INTERRUPT 21
#define DIAG_SBOX_EVENT_INT 21

/* The event occurs each cycle and Icache fill is pending. */
#define DIAG_SBOX_EVENT_ICACHE_FILL_PEND 22

/* The event occurs each time a line in Icache is filled. */
#define DIAG_SBOX_EVENT_ICACHE_FILL 23

/* The event occurs when the Icache has to correct the way prediction due to a
   mispredict. */
#define DIAG_SBOX_EVENT_WAY_MISPREDICT 24

/* The event occurs when a correctly predicted branch instruction is
   committed. */
#define DIAG_SBOX_EVENT_COND_BRANCH_PRED_CORRECT 25

/* The event occurs when an incorrectly predicted branch instruction is
   committed. */
#define DIAG_SBOX_EVENT_COND_BRANCH_PRED_INCORRECT 26

/* The event occurs when there is a valid instruction in pipeline WB stage
   (e.g. when an instruction is committed). */
#define DIAG_SBOX_EVENT_INSTRUCTION_BUNDLE 27
#define DIAG_SBOX_EVENT_VALID_WB 27

/* The event occurs when the instruction pipeline is restarted. */
#define DIAG_SBOX_EVENT_RESTART 28

/* The event occurs when the Return Address Stack is used for jump
   instruction. */
#define DIAG_SBOX_EVENT_USED_RAS 29

/* The event occurs when the value from Return Address Stack was correct. */
#define DIAG_SBOX_EVENT_RAS_CORRECT 30

/* The event occurs when a predicted taken branch that did not do a prediction
   due to bypassing branch predict pipeline is committed. */
#define DIAG_SBOX_EVENT_COND_BRANCH_NO_PREDICT 31


/* The event occurs when a data memory operation is issued and the data
   translation lookaside buffer (DTLB) is used to translate the virtual
   address into the physical address. */
#define DIAG_MBOX_EVENT_TLB 0
#define DIAG_MBOX_EVENT_TLB_CNT 0

/* The event occurs when a load is issued. */
#define DIAG_MBOX_EVENT_READ 1
#define DIAG_MBOX_EVENT_RD_CNT 1

/* The event occurs when a store is issued. */
#define DIAG_MBOX_EVENT_WRITE 2
#define DIAG_MBOX_EVENT_WR_CNT 2

/* The event occurs when the address of a data stream memory operation causes
   a Data TLB Exception including TLB Misses and protection violations. */
#define DIAG_MBOX_EVENT_TLB_EXCEPTION 3

/* The event occurs when a load is issued and data is not returned from the
   level 1 data cache. */
#define DIAG_MBOX_EVENT_READ_MISS 4
#define DIAG_MBOX_EVENT_RD_MISS 4

/* The event occurs when a store is issued and the 16-byte aligned block
   (level 1 data cache line size) containing the address is not present at the
   level 1 data cache. */
#define DIAG_MBOX_EVENT_WRITE_MISS 5
#define DIAG_MBOX_EVENT_WR_MISS 5

/* The event occurs when the L1 data cache system processes a request. */
#define DIAG_MBOX_EVENT_L1_OPCODE_VALID 6
#define DIAG_MBOX_EVENT_OPCODE_VALID 6

/* The event occurs when the L1 data cache system processes a request with the
   opcode LD. */
#define DIAG_MBOX_EVENT_L1_OPCODE_LD_VALID 7
#define DIAG_MBOX_EVENT_OPCODE_LD_VALID 7

/* The event occurs when the L1 data cache system processes a request with the
   opcode ST. */
#define DIAG_MBOX_EVENT_L1_OPCODE_ST_VALID 8
#define DIAG_MBOX_EVENT_OPCODE_ST_VALID 8

/* The event occurs when the L1 data cache system processes a request with the
   opcode ATOMIC. */
#define DIAG_MBOX_EVENT_L1_OPCODE_ATOMIC_VALID 9
#define DIAG_MBOX_EVENT_OPCODE_ATOMIC_VALID 9

/* The event occurs when the L1 data cache system processes a request with the
   opcode FLUSH. */
#define DIAG_MBOX_EVENT_L1_OPCODE_FLUSH_VALID 10
#define DIAG_MBOX_EVENT_OPCODE_FLUSH_VALID 10

/* The event occurs when the L1 data cache system processes a request with the
   opcode INV. */
#define DIAG_MBOX_EVENT_L1_OPCODE_INV_VALID 11
#define DIAG_MBOX_EVENT_OPCODE_INV_VALID 11

/* The event occurs when the L1 data cache system processes a request with the
   opcode FINV. */
#define DIAG_MBOX_EVENT_L1_OPCODE_FINV_VALID 12
#define DIAG_MBOX_EVENT_OPCODE_FINV_VALID 12

/* The event occurs when the L1 data cache system processes a request with the
   opcode MF. */
#define DIAG_MBOX_EVENT_L1_OPCODE_MF_VALID 13
#define DIAG_MBOX_EVENT_OPCODE_MF_VALID 13

/* The event occurs when the L1 data cache system processes a request with the
   opcode PFETCH. */
#define DIAG_MBOX_EVENT_L1_OPCODE_PFETCH_VALID 14
#define DIAG_MBOX_EVENT_OPCODE_PFETCH_VALID 14

/* The event occurs when the L1 data cache system processes a request with the
   opcode WH64. */
#define DIAG_MBOX_EVENT_L1_OPCODE_WH64_VALID 15
#define DIAG_MBOX_EVENT_OPCODE_WH64_VALID 15

/* The event occurs when the L1 data cache system processes a request with the
   opcode DTLBPR. */
#define DIAG_MBOX_EVENT_L1_OPCODE_DTLBPR_VALID 16
#define DIAG_MBOX_EVENT_OPCODE_DTLBPR_VALID 16

/* The event occurs when the L1 data cache system processes a request with the
   opcode FWB. */
#define DIAG_MBOX_EVENT_L1_OPCODE_FWB_VALID 17
#define DIAG_MBOX_EVENT_OPCODE_FWB_VALID 17

/* The event occurs when the L1 data cache system processes a request with the
   opcode LD_NON_TEMPORAL. */
#define DIAG_MBOX_EVENT_L1_OPCODE_LD_NON_TEMPORAL_VALID 18
#define DIAG_MBOX_EVENT_OPCODE_LD_NON_TEMPORAL_VALID 18

/* The event occurs when the L1 data cache system processes a request with the
   opcode ST_NON_TEMPORAL. */
#define DIAG_MBOX_EVENT_L1_OPCODE_ST_NON_TEMPORAL_VALID 19
#define DIAG_MBOX_EVENT_OPCODE_ST_NON_TEMPORAL_VALID 19


/* The event occurs when a read request is received from another tile off the
   SDN and the Level 3 cache will track the share state. */
#define DIAG_CBOX_EVENT_SNOOP_INCREMENT_READ 0
#define DIAG_CBOX_EVENT_SNP_INC_RD_CNT 0

/* The event occurs when a read request is received from another tile off the
   SDN and the Level 3 cache will not track the share state. */
#define DIAG_CBOX_EVENT_SNOOP_NON_INCREMENT_READ 1
#define DIAG_CBOX_EVENT_SNP_NINC_RD_CNT 1

/* The event occurs when a write request is received from another tile off the
   SDN. */
#define DIAG_CBOX_EVENT_SNOOP_WRITE 2
#define DIAG_CBOX_EVENT_SNP_WR_CNT 2

/* The event occurs when a read request is received from an IO device off the
   SDN. */
#define DIAG_CBOX_EVENT_SNOOP_IO_READ 3
#define DIAG_CBOX_EVENT_SNP_IO_RD_CNT 3

/* The event occurs when a write request is received from an IO device off the
   SDN. */
#define DIAG_CBOX_EVENT_SNOOP_IO_WRITE 4
#define DIAG_CBOX_EVENT_SNP_IO_WR_CNT 4

/* The event occurs when a data read request is received from the main
   processor and the Level 3 cache resides in the tile. */
#define DIAG_CBOX_EVENT_LOCAL_DATA_READ 5
#define DIAG_CBOX_EVENT_LOCAL_DRD_CNT 5

/* The event occurs when a write request is received from the main processor
   and the Level 3 cache resides in the tile. */
#define DIAG_CBOX_EVENT_LOCAL_WRITE 6
#define DIAG_CBOX_EVENT_LOCAL_WR_CNT 6

/* The event occurs when an instruction read request is received from the main
   processor and the Level 3 cache resides in the tile. */
#define DIAG_CBOX_EVENT_LOCAL_INSTRUCTION_READ 7
#define DIAG_CBOX_EVENT_LOCAL_IRD_CNT 7

/* The event occurs when a data read request is received from the main
   processor and the Level 3 cache resides in another tile. */
#define DIAG_CBOX_EVENT_REMOTE_DATA_READ 8
#define DIAG_CBOX_EVENT_REMOTE_DRD_CNT 8

/* The event occurs when a write request is received from the main processor
   and the Level 3 cache resides in another tile. */
#define DIAG_CBOX_EVENT_REMOTE_WRITE 9
#define DIAG_CBOX_EVENT_REMOTE_WR_CNT 9

/* The event occurs when an instruction read request is received from the main
   processor and the Level 3 cache resides in another tile. */
#define DIAG_CBOX_EVENT_REMOTE_INSTRUCTION_READ 10
#define DIAG_CBOX_EVENT_REMOTE_IRD_CNT 10

/* The event occurs when a coherence invalidation is received from another
   tile off the QDN. */
#define DIAG_CBOX_EVENT_COHERENCE_INVALIDATION 11
#define DIAG_CBOX_EVENT_COH_INV_CNT 11

/* The event occurs when a read request is received from another tile off the
   SDN and misses the Level 3 cache. The level 3 cache will track the share
   state. */
#define DIAG_CBOX_EVENT_SNOOP_INCREMENT_READ_MISS 12
#define DIAG_CBOX_EVENT_SNP_INC_RD_MISS 12

/* The event occurs when a read request is received from another tile off the
   SDN and misses the Level 3 cache. The Level 3 cache will not track the
   share state. */
#define DIAG_CBOX_EVENT_SNOOP_NON_INCREMENT_READ_MISS 13
#define DIAG_CBOX_EVENT_SNP_NINC_RD_MISS 13

/* The event occurs when a write request is received from another tile off the
   SDN and misses the Level 3 cache. */
#define DIAG_CBOX_EVENT_SNOOP_WRITE_MISS 14
#define DIAG_CBOX_EVENT_SNP_WR_MISS 14

/* The event occurs when a read request is received from an IO device off the
   SDN and misses the Level 3 cache. */
#define DIAG_CBOX_EVENT_SNOOP_IO_READ_MISS 15
#define DIAG_CBOX_EVENT_SNP_IO_RD_MISS 15

/* The event occurs when a write request is received from an IO device off the
   SDN and misses the Level 3 cache. */
#define DIAG_CBOX_EVENT_SNOOP_IO_WRITE_MISS 16
#define DIAG_CBOX_EVENT_SNP_IO_WR_MISS 16

/* The event occurs when a data read request is received from the main
   processor and misses the Level 3 cache resided in the tile. */
#define DIAG_CBOX_EVENT_LOCAL_DATA_READ_MISS 17
#define DIAG_CBOX_EVENT_LOCAL_DRD_MISS 17

/* The event occurs when a write request is received from the main processor
   and misses the Level 3 cache resided in the tile. */
#define DIAG_CBOX_EVENT_LOCAL_WRITE_MISS 18
#define DIAG_CBOX_EVENT_LOCAL_WR_MISS 18

/* The event occurs when an instruction read request is received from the main
   processor and misses the Level 3 cache resided in the tile. */
#define DIAG_CBOX_EVENT_LOCAL_INSTRUCTION_READ_MISS 19
#define DIAG_CBOX_EVENT_LOCAL_IRD_MISS 19

/* The event occurs when a data read request is received from the main
   processor and misses the Level 2 cache. The Level 3 cache resides in
   another tile. */
#define DIAG_CBOX_EVENT_REMOTE_DATA_READ_MISS 20
#define DIAG_CBOX_EVENT_REMOTE_DRD_MISS 20

/* The event occurs when a write request is received from the main processor
   and misses the Level 2 cache. The Level 3 cache resides in another tile. */
#define DIAG_CBOX_EVENT_REMOTE_WRITE_MISS 21
#define DIAG_CBOX_EVENT_REMOTE_WR_MISS 21

/* The event occurs when an instruction read request is received from the main
   processor and misses the Level 2 cache. The Level 3 cache resides in
   another tile. */
#define DIAG_CBOX_EVENT_REMOTE_INSTRUCTION_READ_MISS 22
#define DIAG_CBOX_EVENT_REMOTE_IRD_MISS 22

/* The event occurs when a coherence invalidation is received from another
   tile off the QDN and hits the level 2 cache. */
#define DIAG_CBOX_EVENT_COHERENCE_INVALIDATION_HIT 23
#define DIAG_CBOX_EVENT_COH_INV_HIT 23

/* The event occurs when a cache writeback to main memory, including victim
   writes or explicit flushes, leaves the tile. */
#define DIAG_CBOX_EVENT_CACHE_WRITEBACK 24
#define DIAG_CBOX_EVENT_VIC_WB_CNT 24

/* The event occurs when a snoop is received and the controller enters the SDN
   starved condition. */
#define DIAG_CBOX_EVENT_SDN_STARVED 25

/* The event occurs when the controller enters the RDN starved condition. */
#define DIAG_CBOX_EVENT_RDN_STARVED 26

/* The event occurs when the controller enters the QDN starved condition. */
#define DIAG_CBOX_EVENT_QDN_STARVED 27

/* The event occurs when the controller enters the skid FIFO starved
   condition. */
#define DIAG_CBOX_EVENT_SKF_STARVED 28

/* The event occurs when the controller enters the re-try FIFO starved
   condition. */
#define DIAG_CBOX_EVENT_RTF_STARVED 29

/* The event occurs when the controller enters the instruction stream starved
   condition. */
#define DIAG_CBOX_EVENT_IREQ_STARVED 30

/* The event occurs when an instruction read request associated with the ITLB
   entry specified by ITLB_PERF is received from the main processor and misses
   the Level 2 cache. The Level 3 cache resides in another tile. */
#define DIAG_CBOX_EVENT_ITLB_OLOC_CACHE_MISS 31

/* The event occurs when a data read or write (load or store) request
   associated with the DTLB entry specified by DTLB_PERF is received from the
   main processor and misses the Level 2 cache. The Level 3 cache resides in
   another tile. */
#define DIAG_CBOX_EVENT_DTLB_OLOC_CACHE_MISS 32

/* The event occurs when a write request is received from the main processor
   and allocates a write buffer in the Level 3 cache resided in the tile. */
#define DIAG_CBOX_EVENT_LOCAL_WRITE_BUFFER_ALLOC 33
#define DIAG_CBOX_EVENT_LOCAL_WR_BUFFER_CNT 33

/* The event occurs when a write request is received from the main processor
   and allocates a write buffer in the Level 2 cache resided in the tile. The
   Level 3 cache resides in another tile */
#define DIAG_CBOX_EVENT_REMOTE_WRITE_BUFFER_ALLOC 34
#define DIAG_CBOX_EVENT_REMOTE_WR_BUFFER_CNT 34

/* The event occurs when a request is processed in the L2 pipeline. */
#define DIAG_CBOX_EVENT_ARB_VALID 35

/* The event occurs when a request generates a MDF write. */
#define DIAG_CBOX_EVENT_MDF_WRITE 36

/* The event occurs when a request generates a Load Buffer read. */
#define DIAG_CBOX_EVENT_LDB_READ 37

/* The event occurs when the L2 cache system processes a request with the
   opcode LD. */
#define DIAG_CBOX_EVENT_L2_OPCODE_LD_VALID 38
#define DIAG_CBOX_EVENT_OPCODE_LD_VALID 38

/* The event occurs when the L2 cache system processes a request with the
   opcode ST. */
#define DIAG_CBOX_EVENT_L2_OPCODE_ST_VALID 39
#define DIAG_CBOX_EVENT_OPCODE_ST_VALID 39

/* The event occurs when the L2 cache system processes a request with the
   opcode ATOMIC. */
#define DIAG_CBOX_EVENT_L2_OPCODE_ATOMIC_VALID 40
#define DIAG_CBOX_EVENT_OPCODE_ATOMIC_VALID 40

/* The event occurs when the L2 cache system processes a request with the
   opcode FLUSH. */
#define DIAG_CBOX_EVENT_L2_OPCODE_FLUSH_VALID 41
#define DIAG_CBOX_EVENT_OPCODE_FLUSH_VALID 41

/* The event occurs when the L2 cache system processes a request with the
   opcode INV. */
#define DIAG_CBOX_EVENT_L2_OPCODE_INV_VALID 42
#define DIAG_CBOX_EVENT_OPCODE_INV_VALID 42

/* The event occurs when the L2 cache system processes a request with the
   opcode FINV. */
#define DIAG_CBOX_EVENT_L2_OPCODE_FINV_VALID 43
#define DIAG_CBOX_EVENT_OPCODE_FINV_VALID 43

/* The event occurs when the L2 cache system processes a request with the
   opcode MF. */
#define DIAG_CBOX_EVENT_L2_OPCODE_MF_VALID 44
#define DIAG_CBOX_EVENT_OPCODE_MF_VALID 44

/* The event occurs when the L2 cache system processes a request with the
   opcode PFETCH. */
#define DIAG_CBOX_EVENT_L2_OPCODE_PFETCH_VALID 45
#define DIAG_CBOX_EVENT_OPCODE_PFETCH_VALID 45

/* The event occurs when the L2 cache system processes a request with the
   opcode WH64. */
#define DIAG_CBOX_EVENT_L2_OPCODE_WH64_VALID 46
#define DIAG_CBOX_EVENT_OPCODE_WH64_VALID 46

/* The event occurs when the L2 cache system processes a request with the
   opcode FWB. */
#define DIAG_CBOX_EVENT_L2_OPCODE_FWB_VALID 47
#define DIAG_CBOX_EVENT_OPCODE_FWB_VALID 47

/* The event occurs when the L2 cache system processes a request with the
   opcode LD_NON_TEMPORAL. */
#define DIAG_CBOX_EVENT_L2_OPCODE_LD_NON_TEMPORAL_VALID 48
#define DIAG_CBOX_EVENT_OPCODE_LD_NON_TEMPORAL_VALID 48

/* The event occurs when the L2 cache system processes a request with the
   opcode ST_NON_TEMPORAL. */
#define DIAG_CBOX_EVENT_L2_OPCODE_ST_NON_TEMPORAL_VALID 49
#define DIAG_CBOX_EVENT_OPCODE_ST_NON_TEMPORAL_VALID 49

/* The event occurs when the L2 cache system processes a request with the
   opcode LD_NOFIL. */
#define DIAG_CBOX_EVENT_L2_OPCODE_LD_NOFIL_VALID 50
#define DIAG_CBOX_EVENT_OPCODE_LD_NOFIL_VALID 50

/* The event occurs when the L2 cache system processes a request with the
   opcode LD_NOFIL_NON_TEMPORAL. */
#define DIAG_CBOX_EVENT_L2_OPCODE_LD_NOFIL_NON_TEMPORAL_VALID 51
#define DIAG_CBOX_EVENT_OPCODE_LD_NOFIL_NON_TEMPORAL_VALID 51

/* The event occurs when the L2 cache system processes a request from RDN
   network. */
#define DIAG_CBOX_EVENT_L2_OPCODE_RDN_VALID 52
#define DIAG_CBOX_EVENT_OPCODE_RDN_VALID 52

/* The event occurs when the L2 cache system processes a request from QDN
   network. */
#define DIAG_CBOX_EVENT_L2_OPCODE_QDN_VALID 53
#define DIAG_CBOX_EVENT_OPCODE_QDN_VALID 53

/* The event occurs when the L2 cache system processes an IO read request. */
#define DIAG_CBOX_EVENT_L2_OPCODE_IO_READ_VALID 54
#define DIAG_CBOX_EVENT_OPCODE_IO_READ_VALID 54

/* The event occurs when the L2 cache system processes an IO write request. */
#define DIAG_CBOX_EVENT_L2_OPCODE_IO_WRITE_VALID 55
#define DIAG_CBOX_EVENT_OPCODE_IO_WRITE_VALID 55

/* The event occurs when the L2 cache system processes an I-stream request. */
#define DIAG_CBOX_EVENT_L2_OPCODE_I_STREAM_VALID 56
#define DIAG_CBOX_EVENT_OPCODE_I_STREAM_VALID 56

/* The event occurs when the L2 cache system processes an MDF request. */
#define DIAG_CBOX_EVENT_L2_OPCODE_MDF_VALID 57
#define DIAG_CBOX_EVENT_OPCODE_MDF_VALID 57

/* The event occurs when the L2 cache system processes a request with the
   opcode IREQ_IV. */
#define DIAG_CBOX_EVENT_L2_OPCODE_IREQ_IV_VALID 58
#define DIAG_CBOX_EVENT_OPCODE_IREQ_IV_VALID 58


/* Main processor finished sending a packet to the UDN. */
#define DIAG_XDN_EVENT_UDN_PACKET_SENT 0
#define DIAG_XDN_EVENT_UDN_PKT_SNT 0

/* UDN word sent to an output port.  Participating ports are selected with the
   UDN_EVT_PORT_SEL field. */
#define DIAG_XDN_EVENT_UDN_WORD_SENT 1
#define DIAG_XDN_EVENT_UDN_SNT 1

/* Bubble detected on an output port.  A bubble is defined as a cycle in which
   no data is being sent, but the first word of a packet has already traversed
   the switch.  Participating ports are selected with the UDN_EVT_PORT_SEL
   field. */
#define DIAG_XDN_EVENT_UDN_BUBBLE 2

/* Out of credit on an output port.  Participating ports are selected with the
   UDN_EVT_PORT_SEL field. */
#define DIAG_XDN_EVENT_UDN_CONGESTION 3

/* Main processor finished sending a packet to the IDN. */
#define DIAG_XDN_EVENT_IDN_PACKET_SENT 4
#define DIAG_XDN_EVENT_IDN_PKT_SNT 4

/* IDN word sent to an output port.  Participating ports are selected with the
   IDN_EVT_PORT_SEL field. */
#define DIAG_XDN_EVENT_IDN_WORD_SENT 5
#define DIAG_XDN_EVENT_IDN_SNT 5

/* Bubble detected on an output port.  A bubble is defined as a cycle in which
   no data is being sent, but the first word of a packet has already traversed
   the switch.  Participating ports are selected with the IDN_EVT_PORT_SEL
   field. */
#define DIAG_XDN_EVENT_IDN_BUBBLE 6

/* Out of credit on an output port.  Participating ports are selected with the
   IDN_EVT_PORT_SEL field. */
#define DIAG_XDN_EVENT_IDN_CONGESTION 7

/* Main processor finished sending a packet to the RDN. */
#define DIAG_XDN_EVENT_RDN_PACKET_SENT 8
#define DIAG_XDN_EVENT_RDN_PKT_SNT 8

/* RDN word sent to an output port.  Participating ports are selected with the
   RDN_EVT_PORT_SEL field. */
#define DIAG_XDN_EVENT_RDN_WORD_SENT 9
#define DIAG_XDN_EVENT_RDN_SNT 9

/* Bubble detected on an output port.  A bubble is defined as a cycle in which
   no data is being sent, but the first word of a packet has already traversed
   the switch.  Participating ports are selected with the RDN_EVT_PORT_SEL
   field. */
#define DIAG_XDN_EVENT_RDN_BUBBLE 10

/* Out of credit on an output port.  Participating ports are selected with the
   RDN_EVT_PORT_SEL field. */
#define DIAG_XDN_EVENT_RDN_CONGESTION 11

/* Main processor finished sending a packet to the SDN. */
#define DIAG_XDN_EVENT_SDN_PACKET_SENT 12
#define DIAG_XDN_EVENT_SDN_PKT_SNT 12

/* SDN word sent to an output port.  Participating ports are selected with the
   SDN_EVT_PORT_SEL field. */
#define DIAG_XDN_EVENT_SDN_WORD_SENT 13
#define DIAG_XDN_EVENT_SDN_SNT 13

/* Bubble detected on an output port.  A bubble is defined as a cycle in which
   no data is being sent, but the first word of a packet has already traversed
   the switch.  Participating ports are selected with the SDN_EVT_PORT_SEL
   field. */
#define DIAG_XDN_EVENT_SDN_BUBBLE 14

/* Out of credit on an output port.  Participating ports are selected with the
   SDN_EVT_PORT_SEL field. */
#define DIAG_XDN_EVENT_SDN_CONGESTION 15

/* Main processor finished sending a packet to the QDN. */
#define DIAG_XDN_EVENT_QDN_PACKET_SENT 16
#define DIAG_XDN_EVENT_QDN_PKT_SNT 16

/* QDN word sent to an output port.  Participating ports are selected with the
   QDN_EVT_PORT_SEL field. */
#define DIAG_XDN_EVENT_QDN_WORD_SENT 17
#define DIAG_XDN_EVENT_QDN_SNT 17

/* Bubble detected on an output port.  A bubble is defined as a cycle in which
   no data is being sent, but the first word of a packet has already traversed
   the switch.  Participating ports are selected with the QDN_EVT_PORT_SEL
   field. */
#define DIAG_XDN_EVENT_QDN_BUBBLE 18

/* Out of credit on an output port.  Participating ports are selected with the
   QDN_EVT_PORT_SEL field. */
#define DIAG_XDN_EVENT_QDN_CONGESTION 19

/* UDN Demux stalled due to buffer full */
#define DIAG_XDN_EVENT_UDN_DEMUX_STALL 20
#define DIAG_XDN_EVENT_UDN_DMUX_STALL 20

/* IDN Demux stalled due to buffer full */
#define DIAG_XDN_EVENT_IDN_DEMUX_STALL 21
#define DIAG_XDN_EVENT_IDN_DMUX_STALL 21


/* The event occurs when the Watch SPR detects a address or address range. */
#define DIAG_SPCL_EVENT_WATCH 0

/* The event occurs whenever broadcast wire-0 asserts. */
#define DIAG_SPCL_EVENT_BCST0 1

/* The event occurs whenever broadcast wire-1 asserts. */
#define DIAG_SPCL_EVENT_BCST1 2

/* The event occurs whenever broadcast wire-2 asserts. */
#define DIAG_SPCL_EVENT_BCST2 3

/* The event occurs whenever broadcast wire-3 asserts. */
#define DIAG_SPCL_EVENT_BCST3 4

/* The event occurs when Performance counter-0 overflows. */
#define DIAG_SPCL_EVENT_PCNT0 5

/* The event occurs when Performance counter-1 overflows. */
#define DIAG_SPCL_EVENT_PCNT1 6

/* The event occurs when Auxiliary Performance counter-0 overflows. */
#define DIAG_SPCL_EVENT_AUX_PCNT0 7

/* The event occurs when Auxiliary Performance counter-1 overflows. */
#define DIAG_SPCL_EVENT_AUX_PCNT1 8


/* Constants for TOP diags */

#define DIAG_TOP_MODE0_MBOX_SHIFT 0
#define DIAG_TOP_MODE0_MBOX_WIDTH 64
#define DIAG_TOP_MODE0_MBOX_RMASK _64bit(0xffffffffffffffff)
#define DIAG_TOP_MODE0_MBOX_MASK _64bit(0xffffffffffffffff)
#define DIAG_TOP_MODE0_MBOX_FIELD 63,0


#define DIAG_TOP_MODE1_CBOX_SHIFT 0
#define DIAG_TOP_MODE1_CBOX_WIDTH 64
#define DIAG_TOP_MODE1_CBOX_RMASK _64bit(0xffffffffffffffff)
#define DIAG_TOP_MODE1_CBOX_MASK _64bit(0xffffffffffffffff)
#define DIAG_TOP_MODE1_CBOX_FIELD 63,0


#define DIAG_TOP_MODE2_SBOX_SHIFT 0
#define DIAG_TOP_MODE2_SBOX_WIDTH 64
#define DIAG_TOP_MODE2_SBOX_RMASK _64bit(0xffffffffffffffff)
#define DIAG_TOP_MODE2_SBOX_MASK _64bit(0xffffffffffffffff)
#define DIAG_TOP_MODE2_SBOX_FIELD 63,0


#define DIAG_TOP_MODE3_XDN_SHIFT 0
#define DIAG_TOP_MODE3_XDN_WIDTH 64
#define DIAG_TOP_MODE3_XDN_RMASK _64bit(0xffffffffffffffff)
#define DIAG_TOP_MODE3_XDN_MASK _64bit(0xffffffffffffffff)
#define DIAG_TOP_MODE3_XDN_FIELD 63,0


#define DIAG_TOP_MODE4_PASS_SHIFT 0
#define DIAG_TOP_MODE4_PASS_WIDTH 64
#define DIAG_TOP_MODE4_PASS_RMASK _64bit(0xffffffffffffffff)
#define DIAG_TOP_MODE4_PASS_MASK _64bit(0xffffffffffffffff)
#define DIAG_TOP_MODE4_PASS_FIELD 63,0


#define DIAG_TOP_MODE5_FAIL_WRITTEN_SHIFT 0
#define DIAG_TOP_MODE5_FAIL_WRITTEN_WIDTH 1
#define DIAG_TOP_MODE5_FAIL_WRITTEN_RMASK 0x1
#define DIAG_TOP_MODE5_FAIL_WRITTEN_MASK 0x1
#define DIAG_TOP_MODE5_FAIL_WRITTEN_FIELD 0,0

#define DIAG_TOP_MODE5_DONE_WRITTEN_SHIFT 1
#define DIAG_TOP_MODE5_DONE_WRITTEN_WIDTH 1
#define DIAG_TOP_MODE5_DONE_WRITTEN_RMASK 0x1
#define DIAG_TOP_MODE5_DONE_WRITTEN_MASK 0x2
#define DIAG_TOP_MODE5_DONE_WRITTEN_FIELD 1,1

#define DIAG_TOP_MODE5_QUIESCED_SHIFT 2
#define DIAG_TOP_MODE5_QUIESCED_WIDTH 1
#define DIAG_TOP_MODE5_QUIESCED_RMASK 0x1
#define DIAG_TOP_MODE5_QUIESCED_MASK 0x4
#define DIAG_TOP_MODE5_QUIESCED_FIELD 2,2

#define DIAG_TOP_MODE5_ONE_SHIFT 3
#define DIAG_TOP_MODE5_ONE_WIDTH 1
#define DIAG_TOP_MODE5_ONE_RMASK 0x1
#define DIAG_TOP_MODE5_ONE_MASK 0x8
#define DIAG_TOP_MODE5_ONE_FIELD 3,3

#define DIAG_TOP_MODE5_PASS_SHIFT 4
#define DIAG_TOP_MODE5_PASS_WIDTH 4
#define DIAG_TOP_MODE5_PASS_RMASK 0xf
#define DIAG_TOP_MODE5_PASS_MASK 0xf0
#define DIAG_TOP_MODE5_PASS_FIELD 7,4




/* Constants for SBOX diags */

#define DIAG_SBOX_MODE1_FETCH_STATE_SHIFT 0
#define DIAG_SBOX_MODE1_FETCH_STATE_WIDTH 4
#define DIAG_SBOX_MODE1_FETCH_STATE_RMASK 0xf
#define DIAG_SBOX_MODE1_FETCH_STATE_MASK 0xf
#define DIAG_SBOX_MODE1_FETCH_STATE_FIELD 3,0

#define DIAG_SBOX_MODE1_PF_STATE_SHIFT 4
#define DIAG_SBOX_MODE1_PF_STATE_WIDTH 3
#define DIAG_SBOX_MODE1_PF_STATE_RMASK 0x7
#define DIAG_SBOX_MODE1_PF_STATE_MASK 0x70
#define DIAG_SBOX_MODE1_PF_STATE_FIELD 6,4

#define DIAG_SBOX_MODE1_STALL_DC_SHIFT 7
#define DIAG_SBOX_MODE1_STALL_DC_WIDTH 1
#define DIAG_SBOX_MODE1_STALL_DC_RMASK 0x1
#define DIAG_SBOX_MODE1_STALL_DC_MASK 0x80
#define DIAG_SBOX_MODE1_STALL_DC_FIELD 7,7

#define DIAG_SBOX_MODE1_RESTART_D1_SHIFT 8
#define DIAG_SBOX_MODE1_RESTART_D1_WIDTH 1
#define DIAG_SBOX_MODE1_RESTART_D1_RMASK 0x1
#define DIAG_SBOX_MODE1_RESTART_D1_MASK 0x100
#define DIAG_SBOX_MODE1_RESTART_D1_FIELD 8,8

#define DIAG_SBOX_MODE1_RESTART_DC_D1_SHIFT 9
#define DIAG_SBOX_MODE1_RESTART_DC_D1_WIDTH 1
#define DIAG_SBOX_MODE1_RESTART_DC_D1_RMASK 0x1
#define DIAG_SBOX_MODE1_RESTART_DC_D1_MASK 0x200
#define DIAG_SBOX_MODE1_RESTART_DC_D1_FIELD 9,9

#define DIAG_SBOX_MODE1_RESTART_EX0_D1_SHIFT 10
#define DIAG_SBOX_MODE1_RESTART_EX0_D1_WIDTH 1
#define DIAG_SBOX_MODE1_RESTART_EX0_D1_RMASK 0x1
#define DIAG_SBOX_MODE1_RESTART_EX0_D1_MASK 0x400
#define DIAG_SBOX_MODE1_RESTART_EX0_D1_FIELD 10,10

#define DIAG_SBOX_MODE1_RESTART_EX1_D1_SHIFT 11
#define DIAG_SBOX_MODE1_RESTART_EX1_D1_WIDTH 1
#define DIAG_SBOX_MODE1_RESTART_EX1_D1_RMASK 0x1
#define DIAG_SBOX_MODE1_RESTART_EX1_D1_MASK 0x800
#define DIAG_SBOX_MODE1_RESTART_EX1_D1_FIELD 11,11

#define DIAG_SBOX_MODE1_RESTART_D1_2_SHIFT 12
#define DIAG_SBOX_MODE1_RESTART_D1_2_WIDTH 1
#define DIAG_SBOX_MODE1_RESTART_D1_2_RMASK 0x1
#define DIAG_SBOX_MODE1_RESTART_D1_2_MASK 0x1000
#define DIAG_SBOX_MODE1_RESTART_D1_2_FIELD 12,12

#define DIAG_SBOX_MODE1_VALID_BP_SHIFT 13
#define DIAG_SBOX_MODE1_VALID_BP_WIDTH 1
#define DIAG_SBOX_MODE1_VALID_BP_RMASK 0x1
#define DIAG_SBOX_MODE1_VALID_BP_MASK 0x2000
#define DIAG_SBOX_MODE1_VALID_BP_FIELD 13,13

#define DIAG_SBOX_MODE1_VALID_DC_SHIFT 14
#define DIAG_SBOX_MODE1_VALID_DC_WIDTH 1
#define DIAG_SBOX_MODE1_VALID_DC_RMASK 0x1
#define DIAG_SBOX_MODE1_VALID_DC_MASK 0x4000
#define DIAG_SBOX_MODE1_VALID_DC_FIELD 14,14

#define DIAG_SBOX_MODE1_VALID_EX0_SHIFT 15
#define DIAG_SBOX_MODE1_VALID_EX0_WIDTH 1
#define DIAG_SBOX_MODE1_VALID_EX0_RMASK 0x1
#define DIAG_SBOX_MODE1_VALID_EX0_MASK 0x8000
#define DIAG_SBOX_MODE1_VALID_EX0_FIELD 15,15

#define DIAG_SBOX_MODE1_VALID_EX1_SHIFT 16
#define DIAG_SBOX_MODE1_VALID_EX1_WIDTH 1
#define DIAG_SBOX_MODE1_VALID_EX1_RMASK 0x1
#define DIAG_SBOX_MODE1_VALID_EX1_MASK 0x10000
#define DIAG_SBOX_MODE1_VALID_EX1_FIELD 16,16

#define DIAG_SBOX_MODE1_VALID_WB_SHIFT 17
#define DIAG_SBOX_MODE1_VALID_WB_WIDTH 1
#define DIAG_SBOX_MODE1_VALID_WB_RMASK 0x1
#define DIAG_SBOX_MODE1_VALID_WB_MASK 0x20000
#define DIAG_SBOX_MODE1_VALID_WB_FIELD 17,17

#define DIAG_SBOX_MODE1_PFB_VALID_0_SHIFT 18
#define DIAG_SBOX_MODE1_PFB_VALID_0_WIDTH 1
#define DIAG_SBOX_MODE1_PFB_VALID_0_RMASK 0x1
#define DIAG_SBOX_MODE1_PFB_VALID_0_MASK 0x40000
#define DIAG_SBOX_MODE1_PFB_VALID_0_FIELD 18,18

#define DIAG_SBOX_MODE1_PFB_VALID_1_SHIFT 19
#define DIAG_SBOX_MODE1_PFB_VALID_1_WIDTH 1
#define DIAG_SBOX_MODE1_PFB_VALID_1_RMASK 0x1
#define DIAG_SBOX_MODE1_PFB_VALID_1_MASK 0x80000
#define DIAG_SBOX_MODE1_PFB_VALID_1_FIELD 19,19

#define DIAG_SBOX_MODE1_PFB_VALID_2_SHIFT 20
#define DIAG_SBOX_MODE1_PFB_VALID_2_WIDTH 1
#define DIAG_SBOX_MODE1_PFB_VALID_2_RMASK 0x1
#define DIAG_SBOX_MODE1_PFB_VALID_2_MASK 0x100000
#define DIAG_SBOX_MODE1_PFB_VALID_2_FIELD 20,20

#define DIAG_SBOX_MODE1_PFB_VALID_3_SHIFT 21
#define DIAG_SBOX_MODE1_PFB_VALID_3_WIDTH 1
#define DIAG_SBOX_MODE1_PFB_VALID_3_RMASK 0x1
#define DIAG_SBOX_MODE1_PFB_VALID_3_MASK 0x200000
#define DIAG_SBOX_MODE1_PFB_VALID_3_FIELD 21,21

#define DIAG_SBOX_MODE1_PC_EX1_SHIFT 22
#define DIAG_SBOX_MODE1_PC_EX1_WIDTH 39
#define DIAG_SBOX_MODE1_PC_EX1_RMASK _64bit(0x7fffffffff)
#define DIAG_SBOX_MODE1_PC_EX1_MASK _64bit(0x1fffffffffc00000)
#define DIAG_SBOX_MODE1_PC_EX1_FIELD 60,22

#define DIAG_SBOX_MODE1_CPL_EX1_SHIFT 61
#define DIAG_SBOX_MODE1_CPL_EX1_WIDTH 2
#define DIAG_SBOX_MODE1_CPL_EX1_RMASK 0x3
#define DIAG_SBOX_MODE1_CPL_EX1_MASK _64bit(0x6000000000000000)
#define DIAG_SBOX_MODE1_CPL_EX1_FIELD 62,61


#define DIAG_SBOX_MODE2_FETCH_STATE_SHIFT 0
#define DIAG_SBOX_MODE2_FETCH_STATE_WIDTH 4
#define DIAG_SBOX_MODE2_FETCH_STATE_RMASK 0xf
#define DIAG_SBOX_MODE2_FETCH_STATE_MASK 0xf
#define DIAG_SBOX_MODE2_FETCH_STATE_FIELD 3,0

#define DIAG_SBOX_MODE2_PF_STATE_SHIFT 4
#define DIAG_SBOX_MODE2_PF_STATE_WIDTH 3
#define DIAG_SBOX_MODE2_PF_STATE_RMASK 0x7
#define DIAG_SBOX_MODE2_PF_STATE_MASK 0x70
#define DIAG_SBOX_MODE2_PF_STATE_FIELD 6,4

#define DIAG_SBOX_MODE2_STALL_DC_SHIFT 7
#define DIAG_SBOX_MODE2_STALL_DC_WIDTH 1
#define DIAG_SBOX_MODE2_STALL_DC_RMASK 0x1
#define DIAG_SBOX_MODE2_STALL_DC_MASK 0x80
#define DIAG_SBOX_MODE2_STALL_DC_FIELD 7,7

#define DIAG_SBOX_MODE2_RESTART_D1_SHIFT 8
#define DIAG_SBOX_MODE2_RESTART_D1_WIDTH 1
#define DIAG_SBOX_MODE2_RESTART_D1_RMASK 0x1
#define DIAG_SBOX_MODE2_RESTART_D1_MASK 0x100
#define DIAG_SBOX_MODE2_RESTART_D1_FIELD 8,8

#define DIAG_SBOX_MODE2_PC_FT_E1_SHIFT 9
#define DIAG_SBOX_MODE2_PC_FT_E1_WIDTH 11
#define DIAG_SBOX_MODE2_PC_FT_E1_RMASK 0x7ff
#define DIAG_SBOX_MODE2_PC_FT_E1_MASK 0xffe00
#define DIAG_SBOX_MODE2_PC_FT_E1_FIELD 19,9

#define DIAG_SBOX_MODE2_IC_ALLOC_WAY_DC_SHIFT 20
#define DIAG_SBOX_MODE2_IC_ALLOC_WAY_DC_WIDTH 1
#define DIAG_SBOX_MODE2_IC_ALLOC_WAY_DC_RMASK 0x1
#define DIAG_SBOX_MODE2_IC_ALLOC_WAY_DC_MASK 0x100000
#define DIAG_SBOX_MODE2_IC_ALLOC_WAY_DC_FIELD 20,20

#define DIAG_SBOX_MODE2_IC_PRED_WAY_DC_SHIFT 21
#define DIAG_SBOX_MODE2_IC_PRED_WAY_DC_WIDTH 1
#define DIAG_SBOX_MODE2_IC_PRED_WAY_DC_RMASK 0x1
#define DIAG_SBOX_MODE2_IC_PRED_WAY_DC_MASK 0x200000
#define DIAG_SBOX_MODE2_IC_PRED_WAY_DC_FIELD 21,21

#define DIAG_SBOX_MODE2_IC_HIT_OTHER_WAY_DC_SHIFT 22
#define DIAG_SBOX_MODE2_IC_HIT_OTHER_WAY_DC_WIDTH 1
#define DIAG_SBOX_MODE2_IC_HIT_OTHER_WAY_DC_RMASK 0x1
#define DIAG_SBOX_MODE2_IC_HIT_OTHER_WAY_DC_MASK 0x400000
#define DIAG_SBOX_MODE2_IC_HIT_OTHER_WAY_DC_FIELD 22,22

#define DIAG_SBOX_MODE2_IC_HIT_DC_SHIFT 23
#define DIAG_SBOX_MODE2_IC_HIT_DC_WIDTH 1
#define DIAG_SBOX_MODE2_IC_HIT_DC_RMASK 0x1
#define DIAG_SBOX_MODE2_IC_HIT_DC_MASK 0x800000
#define DIAG_SBOX_MODE2_IC_HIT_DC_FIELD 23,23

#define DIAG_SBOX_MODE2_VALID_DC_SHIFT 24
#define DIAG_SBOX_MODE2_VALID_DC_WIDTH 1
#define DIAG_SBOX_MODE2_VALID_DC_RMASK 0x1
#define DIAG_SBOX_MODE2_VALID_DC_MASK 0x1000000
#define DIAG_SBOX_MODE2_VALID_DC_FIELD 24,24

#define DIAG_SBOX_MODE2_VALID_EX0_SHIFT 25
#define DIAG_SBOX_MODE2_VALID_EX0_WIDTH 1
#define DIAG_SBOX_MODE2_VALID_EX0_RMASK 0x1
#define DIAG_SBOX_MODE2_VALID_EX0_MASK 0x2000000
#define DIAG_SBOX_MODE2_VALID_EX0_FIELD 25,25

#define DIAG_SBOX_MODE2_VALID_EX1_SHIFT 26
#define DIAG_SBOX_MODE2_VALID_EX1_WIDTH 1
#define DIAG_SBOX_MODE2_VALID_EX1_RMASK 0x1
#define DIAG_SBOX_MODE2_VALID_EX1_MASK 0x4000000
#define DIAG_SBOX_MODE2_VALID_EX1_FIELD 26,26

#define DIAG_SBOX_MODE2_VALID_WB_SHIFT 27
#define DIAG_SBOX_MODE2_VALID_WB_WIDTH 1
#define DIAG_SBOX_MODE2_VALID_WB_RMASK 0x1
#define DIAG_SBOX_MODE2_VALID_WB_MASK 0x8000000
#define DIAG_SBOX_MODE2_VALID_WB_FIELD 27,27

#define DIAG_SBOX_MODE2_PC_DC_SHIFT 28
#define DIAG_SBOX_MODE2_PC_DC_WIDTH 36
#define DIAG_SBOX_MODE2_PC_DC_RMASK _64bit(0xfffffffff)
#define DIAG_SBOX_MODE2_PC_DC_MASK _64bit(0xfffffffff0000000)
#define DIAG_SBOX_MODE2_PC_DC_FIELD 63,28


#define DIAG_SBOX_MODE3_FETCH_STATE_SHIFT 0
#define DIAG_SBOX_MODE3_FETCH_STATE_WIDTH 4
#define DIAG_SBOX_MODE3_FETCH_STATE_RMASK 0xf
#define DIAG_SBOX_MODE3_FETCH_STATE_MASK 0xf
#define DIAG_SBOX_MODE3_FETCH_STATE_FIELD 3,0

#define DIAG_SBOX_MODE3_PF_STATE_SHIFT 4
#define DIAG_SBOX_MODE3_PF_STATE_WIDTH 3
#define DIAG_SBOX_MODE3_PF_STATE_RMASK 0x7
#define DIAG_SBOX_MODE3_PF_STATE_MASK 0x70
#define DIAG_SBOX_MODE3_PF_STATE_FIELD 6,4

#define DIAG_SBOX_MODE3_STALL_DC_SHIFT 7
#define DIAG_SBOX_MODE3_STALL_DC_WIDTH 1
#define DIAG_SBOX_MODE3_STALL_DC_RMASK 0x1
#define DIAG_SBOX_MODE3_STALL_DC_MASK 0x80
#define DIAG_SBOX_MODE3_STALL_DC_FIELD 7,7

#define DIAG_SBOX_MODE3_RESTART_D1_SHIFT 8
#define DIAG_SBOX_MODE3_RESTART_D1_WIDTH 1
#define DIAG_SBOX_MODE3_RESTART_D1_RMASK 0x1
#define DIAG_SBOX_MODE3_RESTART_D1_MASK 0x100
#define DIAG_SBOX_MODE3_RESTART_D1_FIELD 8,8

#define DIAG_SBOX_MODE3_CBOX_RID_D1_SHIFT 9
#define DIAG_SBOX_MODE3_CBOX_RID_D1_WIDTH 4
#define DIAG_SBOX_MODE3_CBOX_RID_D1_RMASK 0xf
#define DIAG_SBOX_MODE3_CBOX_RID_D1_MASK 0x1e00
#define DIAG_SBOX_MODE3_CBOX_RID_D1_FIELD 12,9

#define DIAG_SBOX_MODE3_S_REQ_TYPE_SHIFT 13
#define DIAG_SBOX_MODE3_S_REQ_TYPE_WIDTH 2
#define DIAG_SBOX_MODE3_S_REQ_TYPE_RMASK 0x3
#define DIAG_SBOX_MODE3_S_REQ_TYPE_MASK 0x6000
#define DIAG_SBOX_MODE3_S_REQ_TYPE_FIELD 14,13

#define DIAG_SBOX_MODE3_S_LOTAR_SHIFT 15
#define DIAG_SBOX_MODE3_S_LOTAR_WIDTH 8
#define DIAG_SBOX_MODE3_S_LOTAR_RMASK 0xff
#define DIAG_SBOX_MODE3_S_LOTAR_MASK 0x7f8000
#define DIAG_SBOX_MODE3_S_LOTAR_FIELD 22,15

#define DIAG_SBOX_MODE3_S_RID_SHIFT 23
#define DIAG_SBOX_MODE3_S_RID_WIDTH 4
#define DIAG_SBOX_MODE3_S_RID_RMASK 0xf
#define DIAG_SBOX_MODE3_S_RID_MASK 0x7800000
#define DIAG_SBOX_MODE3_S_RID_FIELD 26,23

#define DIAG_SBOX_MODE3_S_PA_SHIFT 27
#define DIAG_SBOX_MODE3_S_PA_WIDTH 34
#define DIAG_SBOX_MODE3_S_PA_RMASK _64bit(0x3ffffffff)
#define DIAG_SBOX_MODE3_S_PA_MASK _64bit(0x1ffffffff8000000)
#define DIAG_SBOX_MODE3_S_PA_FIELD 60,27

#define DIAG_SBOX_MODE3_C_NONFATAL_ERR_SHIFT 61
#define DIAG_SBOX_MODE3_C_NONFATAL_ERR_WIDTH 1
#define DIAG_SBOX_MODE3_C_NONFATAL_ERR_RMASK 0x1
#define DIAG_SBOX_MODE3_C_NONFATAL_ERR_MASK _64bit(0x2000000000000000)
#define DIAG_SBOX_MODE3_C_NONFATAL_ERR_FIELD 61,61

#define DIAG_SBOX_MODE3_C_FATAL_ERR_SHIFT 62
#define DIAG_SBOX_MODE3_C_FATAL_ERR_WIDTH 1
#define DIAG_SBOX_MODE3_C_FATAL_ERR_RMASK 0x1
#define DIAG_SBOX_MODE3_C_FATAL_ERR_MASK _64bit(0x4000000000000000)
#define DIAG_SBOX_MODE3_C_FATAL_ERR_FIELD 62,62

#define DIAG_SBOX_MODE3_C_RETURN_VALID_SHIFT 63
#define DIAG_SBOX_MODE3_C_RETURN_VALID_WIDTH 1
#define DIAG_SBOX_MODE3_C_RETURN_VALID_RMASK 0x1
#define DIAG_SBOX_MODE3_C_RETURN_VALID_MASK _64bit(0x8000000000000000)
#define DIAG_SBOX_MODE3_C_RETURN_VALID_FIELD 63,63

#define DIAG_SBOX_MODE3_S_REQUEST_VALID_SHIFT 64
#define DIAG_SBOX_MODE3_S_REQUEST_VALID_WIDTH 1
#define DIAG_SBOX_MODE3_S_REQUEST_VALID_RMASK 0x1
#define DIAG_SBOX_MODE3_S_REQUEST_VALID_MASK _64bit(0x10000000000000000)
#define DIAG_SBOX_MODE3_S_REQUEST_VALID_FIELD 64,64


#define DIAG_SBOX_MODE5_FETCH_STATE_SHIFT 0
#define DIAG_SBOX_MODE5_FETCH_STATE_WIDTH 4
#define DIAG_SBOX_MODE5_FETCH_STATE_RMASK 0xf
#define DIAG_SBOX_MODE5_FETCH_STATE_MASK 0xf
#define DIAG_SBOX_MODE5_FETCH_STATE_FIELD 3,0

#define DIAG_SBOX_MODE5_PF_STATE_SHIFT 4
#define DIAG_SBOX_MODE5_PF_STATE_WIDTH 3
#define DIAG_SBOX_MODE5_PF_STATE_RMASK 0x7
#define DIAG_SBOX_MODE5_PF_STATE_MASK 0x70
#define DIAG_SBOX_MODE5_PF_STATE_FIELD 6,4

#define DIAG_SBOX_MODE5_STALL_DC_SHIFT 7
#define DIAG_SBOX_MODE5_STALL_DC_WIDTH 1
#define DIAG_SBOX_MODE5_STALL_DC_RMASK 0x1
#define DIAG_SBOX_MODE5_STALL_DC_MASK 0x80
#define DIAG_SBOX_MODE5_STALL_DC_FIELD 7,7

#define DIAG_SBOX_MODE5_RESTART_D1_SHIFT 8
#define DIAG_SBOX_MODE5_RESTART_D1_WIDTH 1
#define DIAG_SBOX_MODE5_RESTART_D1_RMASK 0x1
#define DIAG_SBOX_MODE5_RESTART_D1_MASK 0x100
#define DIAG_SBOX_MODE5_RESTART_D1_FIELD 8,8

#define DIAG_SBOX_MODE5_RESTART_DC_D1_SHIFT 9
#define DIAG_SBOX_MODE5_RESTART_DC_D1_WIDTH 1
#define DIAG_SBOX_MODE5_RESTART_DC_D1_RMASK 0x1
#define DIAG_SBOX_MODE5_RESTART_DC_D1_MASK 0x200
#define DIAG_SBOX_MODE5_RESTART_DC_D1_FIELD 9,9

#define DIAG_SBOX_MODE5_RESTART_EX0_D1_SHIFT 10
#define DIAG_SBOX_MODE5_RESTART_EX0_D1_WIDTH 1
#define DIAG_SBOX_MODE5_RESTART_EX0_D1_RMASK 0x1
#define DIAG_SBOX_MODE5_RESTART_EX0_D1_MASK 0x400
#define DIAG_SBOX_MODE5_RESTART_EX0_D1_FIELD 10,10

#define DIAG_SBOX_MODE5_RESTART_EX1_D1_SHIFT 11
#define DIAG_SBOX_MODE5_RESTART_EX1_D1_WIDTH 1
#define DIAG_SBOX_MODE5_RESTART_EX1_D1_RMASK 0x1
#define DIAG_SBOX_MODE5_RESTART_EX1_D1_MASK 0x800
#define DIAG_SBOX_MODE5_RESTART_EX1_D1_FIELD 11,11

#define DIAG_SBOX_MODE5_RESTART_D1_2_SHIFT 12
#define DIAG_SBOX_MODE5_RESTART_D1_2_WIDTH 1
#define DIAG_SBOX_MODE5_RESTART_D1_2_RMASK 0x1
#define DIAG_SBOX_MODE5_RESTART_D1_2_MASK 0x1000
#define DIAG_SBOX_MODE5_RESTART_D1_2_FIELD 12,12

#define DIAG_SBOX_MODE5_VALID_BP_SHIFT 13
#define DIAG_SBOX_MODE5_VALID_BP_WIDTH 1
#define DIAG_SBOX_MODE5_VALID_BP_RMASK 0x1
#define DIAG_SBOX_MODE5_VALID_BP_MASK 0x2000
#define DIAG_SBOX_MODE5_VALID_BP_FIELD 13,13

#define DIAG_SBOX_MODE5_VALID_DC_SHIFT 14
#define DIAG_SBOX_MODE5_VALID_DC_WIDTH 1
#define DIAG_SBOX_MODE5_VALID_DC_RMASK 0x1
#define DIAG_SBOX_MODE5_VALID_DC_MASK 0x4000
#define DIAG_SBOX_MODE5_VALID_DC_FIELD 14,14

#define DIAG_SBOX_MODE5_VALID_EX0_SHIFT 15
#define DIAG_SBOX_MODE5_VALID_EX0_WIDTH 1
#define DIAG_SBOX_MODE5_VALID_EX0_RMASK 0x1
#define DIAG_SBOX_MODE5_VALID_EX0_MASK 0x8000
#define DIAG_SBOX_MODE5_VALID_EX0_FIELD 15,15

#define DIAG_SBOX_MODE5_VALID_EX1_SHIFT 16
#define DIAG_SBOX_MODE5_VALID_EX1_WIDTH 1
#define DIAG_SBOX_MODE5_VALID_EX1_RMASK 0x1
#define DIAG_SBOX_MODE5_VALID_EX1_MASK 0x10000
#define DIAG_SBOX_MODE5_VALID_EX1_FIELD 16,16

#define DIAG_SBOX_MODE5_VALID_WB_SHIFT 17
#define DIAG_SBOX_MODE5_VALID_WB_WIDTH 1
#define DIAG_SBOX_MODE5_VALID_WB_RMASK 0x1
#define DIAG_SBOX_MODE5_VALID_WB_MASK 0x20000
#define DIAG_SBOX_MODE5_VALID_WB_FIELD 17,17

#define DIAG_SBOX_MODE5_PFB_VALID_0_SHIFT 18
#define DIAG_SBOX_MODE5_PFB_VALID_0_WIDTH 1
#define DIAG_SBOX_MODE5_PFB_VALID_0_RMASK 0x1
#define DIAG_SBOX_MODE5_PFB_VALID_0_MASK 0x40000
#define DIAG_SBOX_MODE5_PFB_VALID_0_FIELD 18,18

#define DIAG_SBOX_MODE5_PFB_VALID_1_SHIFT 19
#define DIAG_SBOX_MODE5_PFB_VALID_1_WIDTH 1
#define DIAG_SBOX_MODE5_PFB_VALID_1_RMASK 0x1
#define DIAG_SBOX_MODE5_PFB_VALID_1_MASK 0x80000
#define DIAG_SBOX_MODE5_PFB_VALID_1_FIELD 19,19

#define DIAG_SBOX_MODE5_PFB_VALID_2_SHIFT 20
#define DIAG_SBOX_MODE5_PFB_VALID_2_WIDTH 1
#define DIAG_SBOX_MODE5_PFB_VALID_2_RMASK 0x1
#define DIAG_SBOX_MODE5_PFB_VALID_2_MASK 0x100000
#define DIAG_SBOX_MODE5_PFB_VALID_2_FIELD 20,20

#define DIAG_SBOX_MODE5_PFB_VALID_3_SHIFT 21
#define DIAG_SBOX_MODE5_PFB_VALID_3_WIDTH 1
#define DIAG_SBOX_MODE5_PFB_VALID_3_RMASK 0x1
#define DIAG_SBOX_MODE5_PFB_VALID_3_MASK 0x200000
#define DIAG_SBOX_MODE5_PFB_VALID_3_FIELD 21,21

#define DIAG_SBOX_MODE5_PC_WB_SHIFT 22
#define DIAG_SBOX_MODE5_PC_WB_WIDTH 39
#define DIAG_SBOX_MODE5_PC_WB_RMASK _64bit(0x7fffffffff)
#define DIAG_SBOX_MODE5_PC_WB_MASK _64bit(0x1fffffffffc00000)
#define DIAG_SBOX_MODE5_PC_WB_FIELD 60,22

#define DIAG_SBOX_MODE5_CPL_EX1_SHIFT 61
#define DIAG_SBOX_MODE5_CPL_EX1_WIDTH 2
#define DIAG_SBOX_MODE5_CPL_EX1_RMASK 0x3
#define DIAG_SBOX_MODE5_CPL_EX1_MASK _64bit(0x6000000000000000)
#define DIAG_SBOX_MODE5_CPL_EX1_FIELD 62,61




/* Constants for MBOX diags */

#define DIAG_MBOX_MODE1_OP_SRC_A_SHIFT 0
#define DIAG_MBOX_MODE1_OP_SRC_A_WIDTH 42
#define DIAG_MBOX_MODE1_OP_SRC_A_RMASK _64bit(0x3ffffffffff)
#define DIAG_MBOX_MODE1_OP_SRC_A_MASK _64bit(0x3ffffffffff)
#define DIAG_MBOX_MODE1_OP_SRC_A_FIELD 41,0

#define DIAG_MBOX_MODE1_MEM_OPCODE_SHIFT 42
#define DIAG_MBOX_MODE1_MEM_OPCODE_WIDTH 4
#define DIAG_MBOX_MODE1_MEM_OPCODE_RMASK 0xf
#define DIAG_MBOX_MODE1_MEM_OPCODE_MASK _64bit(0x3c0000000000)
#define DIAG_MBOX_MODE1_MEM_OPCODE_FIELD 45,42

#define DIAG_MBOX_MODE1_TLB_HIT_SHIFT 46
#define DIAG_MBOX_MODE1_TLB_HIT_WIDTH 1
#define DIAG_MBOX_MODE1_TLB_HIT_RMASK 0x1
#define DIAG_MBOX_MODE1_TLB_HIT_MASK _64bit(0x400000000000)
#define DIAG_MBOX_MODE1_TLB_HIT_FIELD 46,46

#define DIAG_MBOX_MODE1_TLB_EXC_SHIFT 47
#define DIAG_MBOX_MODE1_TLB_EXC_WIDTH 1
#define DIAG_MBOX_MODE1_TLB_EXC_RMASK 0x1
#define DIAG_MBOX_MODE1_TLB_EXC_MASK _64bit(0x800000000000)
#define DIAG_MBOX_MODE1_TLB_EXC_FIELD 47,47

#define DIAG_MBOX_MODE1_TLB_WRITEABLE_SHIFT 48
#define DIAG_MBOX_MODE1_TLB_WRITEABLE_WIDTH 1
#define DIAG_MBOX_MODE1_TLB_WRITEABLE_RMASK 0x1
#define DIAG_MBOX_MODE1_TLB_WRITEABLE_MASK _64bit(0x1000000000000)
#define DIAG_MBOX_MODE1_TLB_WRITEABLE_FIELD 48,48

#define DIAG_MBOX_MODE1_HIT_SHIFT 49
#define DIAG_MBOX_MODE1_HIT_WIDTH 1
#define DIAG_MBOX_MODE1_HIT_RMASK 0x1
#define DIAG_MBOX_MODE1_HIT_MASK _64bit(0x2000000000000)
#define DIAG_MBOX_MODE1_HIT_FIELD 49,49

#define DIAG_MBOX_MODE1_OPCODE_FIN_SHIFT 50
#define DIAG_MBOX_MODE1_OPCODE_FIN_WIDTH 4
#define DIAG_MBOX_MODE1_OPCODE_FIN_RMASK 0xf
#define DIAG_MBOX_MODE1_OPCODE_FIN_MASK _64bit(0x3c000000000000)
#define DIAG_MBOX_MODE1_OPCODE_FIN_FIELD 53,50

#define DIAG_MBOX_MODE1_PREHIT1_SHIFT 54
#define DIAG_MBOX_MODE1_PREHIT1_WIDTH 1
#define DIAG_MBOX_MODE1_PREHIT1_RMASK 0x1
#define DIAG_MBOX_MODE1_PREHIT1_MASK _64bit(0x40000000000000)
#define DIAG_MBOX_MODE1_PREHIT1_FIELD 54,54

#define DIAG_MBOX_MODE1_PREHIT0_SHIFT 55
#define DIAG_MBOX_MODE1_PREHIT0_WIDTH 1
#define DIAG_MBOX_MODE1_PREHIT0_RMASK 0x1
#define DIAG_MBOX_MODE1_PREHIT0_MASK _64bit(0x80000000000000)
#define DIAG_MBOX_MODE1_PREHIT0_FIELD 55,55

#define DIAG_MBOX_MODE1_SET_OVLD_SHIFT 56
#define DIAG_MBOX_MODE1_SET_OVLD_WIDTH 1
#define DIAG_MBOX_MODE1_SET_OVLD_RMASK 0x1
#define DIAG_MBOX_MODE1_SET_OVLD_MASK _64bit(0x100000000000000)
#define DIAG_MBOX_MODE1_SET_OVLD_FIELD 56,56

#define DIAG_MBOX_MODE1_WAY0_STATE_SHIFT 57
#define DIAG_MBOX_MODE1_WAY0_STATE_WIDTH 2
#define DIAG_MBOX_MODE1_WAY0_STATE_RMASK 0x3
#define DIAG_MBOX_MODE1_WAY0_STATE_MASK _64bit(0x600000000000000)
#define DIAG_MBOX_MODE1_WAY0_STATE_FIELD 58,57

#define DIAG_MBOX_MODE1_WAY1_STATE_SHIFT 59
#define DIAG_MBOX_MODE1_WAY1_STATE_WIDTH 2
#define DIAG_MBOX_MODE1_WAY1_STATE_RMASK 0x3
#define DIAG_MBOX_MODE1_WAY1_STATE_MASK _64bit(0x1800000000000000)
#define DIAG_MBOX_MODE1_WAY1_STATE_FIELD 60,59

#define DIAG_MBOX_MODE1_MRU_SHIFT 61
#define DIAG_MBOX_MODE1_MRU_WIDTH 1
#define DIAG_MBOX_MODE1_MRU_RMASK 0x1
#define DIAG_MBOX_MODE1_MRU_MASK _64bit(0x2000000000000000)
#define DIAG_MBOX_MODE1_MRU_FIELD 61,61

#define DIAG_MBOX_MODE1_FILL_WAY_SHIFT 62
#define DIAG_MBOX_MODE1_FILL_WAY_WIDTH 1
#define DIAG_MBOX_MODE1_FILL_WAY_RMASK 0x1
#define DIAG_MBOX_MODE1_FILL_WAY_MASK _64bit(0x4000000000000000)
#define DIAG_MBOX_MODE1_FILL_WAY_FIELD 62,62


#define DIAG_MBOX_MODE2_TLB_PA_SHIFT 0
#define DIAG_MBOX_MODE2_TLB_PA_WIDTH 40
#define DIAG_MBOX_MODE2_TLB_PA_RMASK _64bit(0xffffffffff)
#define DIAG_MBOX_MODE2_TLB_PA_MASK _64bit(0xffffffffff)
#define DIAG_MBOX_MODE2_TLB_PA_FIELD 39,0

#define DIAG_MBOX_MODE2_MEM_OPCODE_SHIFT 40
#define DIAG_MBOX_MODE2_MEM_OPCODE_WIDTH 4
#define DIAG_MBOX_MODE2_MEM_OPCODE_RMASK 0xf
#define DIAG_MBOX_MODE2_MEM_OPCODE_MASK _64bit(0xf0000000000)
#define DIAG_MBOX_MODE2_MEM_OPCODE_FIELD 43,40

#define DIAG_MBOX_MODE2_TLB_HIT_SHIFT 44
#define DIAG_MBOX_MODE2_TLB_HIT_WIDTH 1
#define DIAG_MBOX_MODE2_TLB_HIT_RMASK 0x1
#define DIAG_MBOX_MODE2_TLB_HIT_MASK _64bit(0x100000000000)
#define DIAG_MBOX_MODE2_TLB_HIT_FIELD 44,44

#define DIAG_MBOX_MODE2_TLB_EXC_SHIFT 45
#define DIAG_MBOX_MODE2_TLB_EXC_WIDTH 1
#define DIAG_MBOX_MODE2_TLB_EXC_RMASK 0x1
#define DIAG_MBOX_MODE2_TLB_EXC_MASK _64bit(0x200000000000)
#define DIAG_MBOX_MODE2_TLB_EXC_FIELD 45,45

#define DIAG_MBOX_MODE2_TLB_WRITEABLE_SHIFT 46
#define DIAG_MBOX_MODE2_TLB_WRITEABLE_WIDTH 1
#define DIAG_MBOX_MODE2_TLB_WRITEABLE_RMASK 0x1
#define DIAG_MBOX_MODE2_TLB_WRITEABLE_MASK _64bit(0x400000000000)
#define DIAG_MBOX_MODE2_TLB_WRITEABLE_FIELD 46,46

#define DIAG_MBOX_MODE2_HIT_SHIFT 47
#define DIAG_MBOX_MODE2_HIT_WIDTH 1
#define DIAG_MBOX_MODE2_HIT_RMASK 0x1
#define DIAG_MBOX_MODE2_HIT_MASK _64bit(0x800000000000)
#define DIAG_MBOX_MODE2_HIT_FIELD 47,47

#define DIAG_MBOX_MODE2_OPCODE_FIN_SHIFT 48
#define DIAG_MBOX_MODE2_OPCODE_FIN_WIDTH 4
#define DIAG_MBOX_MODE2_OPCODE_FIN_RMASK 0xf
#define DIAG_MBOX_MODE2_OPCODE_FIN_MASK _64bit(0xf000000000000)
#define DIAG_MBOX_MODE2_OPCODE_FIN_FIELD 51,48

#define DIAG_MBOX_MODE2_PREHIT1_SHIFT 52
#define DIAG_MBOX_MODE2_PREHIT1_WIDTH 1
#define DIAG_MBOX_MODE2_PREHIT1_RMASK 0x1
#define DIAG_MBOX_MODE2_PREHIT1_MASK _64bit(0x10000000000000)
#define DIAG_MBOX_MODE2_PREHIT1_FIELD 52,52

#define DIAG_MBOX_MODE2_PREHIT0_SHIFT 53
#define DIAG_MBOX_MODE2_PREHIT0_WIDTH 1
#define DIAG_MBOX_MODE2_PREHIT0_RMASK 0x1
#define DIAG_MBOX_MODE2_PREHIT0_MASK _64bit(0x20000000000000)
#define DIAG_MBOX_MODE2_PREHIT0_FIELD 53,53

#define DIAG_MBOX_MODE2_SET_OVLD_SHIFT 54
#define DIAG_MBOX_MODE2_SET_OVLD_WIDTH 1
#define DIAG_MBOX_MODE2_SET_OVLD_RMASK 0x1
#define DIAG_MBOX_MODE2_SET_OVLD_MASK _64bit(0x40000000000000)
#define DIAG_MBOX_MODE2_SET_OVLD_FIELD 54,54

#define DIAG_MBOX_MODE2_WAY0_STATE_SHIFT 55
#define DIAG_MBOX_MODE2_WAY0_STATE_WIDTH 2
#define DIAG_MBOX_MODE2_WAY0_STATE_RMASK 0x3
#define DIAG_MBOX_MODE2_WAY0_STATE_MASK _64bit(0x180000000000000)
#define DIAG_MBOX_MODE2_WAY0_STATE_FIELD 56,55

#define DIAG_MBOX_MODE2_WAY1_STATE_SHIFT 57
#define DIAG_MBOX_MODE2_WAY1_STATE_WIDTH 2
#define DIAG_MBOX_MODE2_WAY1_STATE_RMASK 0x3
#define DIAG_MBOX_MODE2_WAY1_STATE_MASK _64bit(0x600000000000000)
#define DIAG_MBOX_MODE2_WAY1_STATE_FIELD 58,57

#define DIAG_MBOX_MODE2_MRU_SHIFT 59
#define DIAG_MBOX_MODE2_MRU_WIDTH 1
#define DIAG_MBOX_MODE2_MRU_RMASK 0x1
#define DIAG_MBOX_MODE2_MRU_MASK _64bit(0x800000000000000)
#define DIAG_MBOX_MODE2_MRU_FIELD 59,59

#define DIAG_MBOX_MODE2_FILL_WAY_SHIFT 60
#define DIAG_MBOX_MODE2_FILL_WAY_WIDTH 1
#define DIAG_MBOX_MODE2_FILL_WAY_RMASK 0x1
#define DIAG_MBOX_MODE2_FILL_WAY_MASK _64bit(0x1000000000000000)
#define DIAG_MBOX_MODE2_FILL_WAY_FIELD 60,60


#define DIAG_MBOX_MODE3_OP_SRC_B_SHIFT 0
#define DIAG_MBOX_MODE3_OP_SRC_B_WIDTH 64
#define DIAG_MBOX_MODE3_OP_SRC_B_RMASK _64bit(0xffffffffffffffff)
#define DIAG_MBOX_MODE3_OP_SRC_B_MASK _64bit(0xffffffffffffffff)
#define DIAG_MBOX_MODE3_OP_SRC_B_FIELD 63,0




/* Constants for CBOX diags */

#define DIAG_CBOX_MODE1_C2_PA_SHIFT 0
#define DIAG_CBOX_MODE1_C2_PA_WIDTH 40
#define DIAG_CBOX_MODE1_C2_PA_RMASK _64bit(0xffffffffff)
#define DIAG_CBOX_MODE1_C2_PA_MASK _64bit(0xffffffffff)
#define DIAG_CBOX_MODE1_C2_PA_FIELD 39,0

#define DIAG_CBOX_MODE1_ARB_CMD_SHIFT 40
#define DIAG_CBOX_MODE1_ARB_CMD_WIDTH 5
#define DIAG_CBOX_MODE1_ARB_CMD_RMASK 0x1f
#define DIAG_CBOX_MODE1_ARB_CMD_MASK _64bit(0x1f0000000000)
#define DIAG_CBOX_MODE1_ARB_CMD_FIELD 44,40

#define DIAG_CBOX_MODE1_ARB_CMD_IS_SNOOP_SHIFT 45
#define DIAG_CBOX_MODE1_ARB_CMD_IS_SNOOP_WIDTH 1
#define DIAG_CBOX_MODE1_ARB_CMD_IS_SNOOP_RMASK 0x1
#define DIAG_CBOX_MODE1_ARB_CMD_IS_SNOOP_MASK _64bit(0x200000000000)
#define DIAG_CBOX_MODE1_ARB_CMD_IS_SNOOP_FIELD 45,45

#define DIAG_CBOX_MODE1_REJECT_SHIFT 46
#define DIAG_CBOX_MODE1_REJECT_WIDTH 1
#define DIAG_CBOX_MODE1_REJECT_RMASK 0x1
#define DIAG_CBOX_MODE1_REJECT_MASK _64bit(0x400000000000)
#define DIAG_CBOX_MODE1_REJECT_FIELD 46,46

#define DIAG_CBOX_MODE1_MAF_MATCH_SHIFT 47
#define DIAG_CBOX_MODE1_MAF_MATCH_WIDTH 1
#define DIAG_CBOX_MODE1_MAF_MATCH_RMASK 0x1
#define DIAG_CBOX_MODE1_MAF_MATCH_MASK _64bit(0x800000000000)
#define DIAG_CBOX_MODE1_MAF_MATCH_FIELD 47,47

#define DIAG_CBOX_MODE1_MDF_WRITE_SHIFT 48
#define DIAG_CBOX_MODE1_MDF_WRITE_WIDTH 1
#define DIAG_CBOX_MODE1_MDF_WRITE_RMASK 0x1
#define DIAG_CBOX_MODE1_MDF_WRITE_MASK _64bit(0x1000000000000)
#define DIAG_CBOX_MODE1_MDF_WRITE_FIELD 48,48

#define DIAG_CBOX_MODE1_LDB_READ_SHIFT 49
#define DIAG_CBOX_MODE1_LDB_READ_WIDTH 1
#define DIAG_CBOX_MODE1_LDB_READ_RMASK 0x1
#define DIAG_CBOX_MODE1_LDB_READ_MASK _64bit(0x2000000000000)
#define DIAG_CBOX_MODE1_LDB_READ_FIELD 49,49

#define DIAG_CBOX_MODE1_RTF_WRITE_SHIFT 50
#define DIAG_CBOX_MODE1_RTF_WRITE_WIDTH 1
#define DIAG_CBOX_MODE1_RTF_WRITE_RMASK 0x1
#define DIAG_CBOX_MODE1_RTF_WRITE_MASK _64bit(0x4000000000000)
#define DIAG_CBOX_MODE1_RTF_WRITE_FIELD 50,50

#define DIAG_CBOX_MODE1_EG_CMD_VLD_SHIFT 51
#define DIAG_CBOX_MODE1_EG_CMD_VLD_WIDTH 4
#define DIAG_CBOX_MODE1_EG_CMD_VLD_RMASK 0xf
#define DIAG_CBOX_MODE1_EG_CMD_VLD_MASK _64bit(0x78000000000000)
#define DIAG_CBOX_MODE1_EG_CMD_VLD_FIELD 54,51

#define DIAG_CBOX_MODE1_RAM_ENABLES_SHIFT 55
#define DIAG_CBOX_MODE1_RAM_ENABLES_WIDTH 4
#define DIAG_CBOX_MODE1_RAM_ENABLES_RMASK 0xf
#define DIAG_CBOX_MODE1_RAM_ENABLES_MASK _64bit(0x780000000000000)
#define DIAG_CBOX_MODE1_RAM_ENABLES_FIELD 58,55

#define DIAG_CBOX_MODE1_RAM_WRITES_SHIFT 59
#define DIAG_CBOX_MODE1_RAM_WRITES_WIDTH 4
#define DIAG_CBOX_MODE1_RAM_WRITES_RMASK 0xf
#define DIAG_CBOX_MODE1_RAM_WRITES_MASK _64bit(0x7800000000000000)
#define DIAG_CBOX_MODE1_RAM_WRITES_FIELD 62,59


#define DIAG_CBOX_MODE2_C2_PA_30_SHIFT 0
#define DIAG_CBOX_MODE2_C2_PA_30_WIDTH 30
#define DIAG_CBOX_MODE2_C2_PA_30_RMASK 0x3fffffff
#define DIAG_CBOX_MODE2_C2_PA_30_MASK 0x3fffffff
#define DIAG_CBOX_MODE2_C2_PA_30_FIELD 29,0

#define DIAG_CBOX_MODE2_ARB_CMD_SHIFT 30
#define DIAG_CBOX_MODE2_ARB_CMD_WIDTH 5
#define DIAG_CBOX_MODE2_ARB_CMD_RMASK 0x1f
#define DIAG_CBOX_MODE2_ARB_CMD_MASK _64bit(0x7c0000000)
#define DIAG_CBOX_MODE2_ARB_CMD_FIELD 34,30

#define DIAG_CBOX_MODE2_ARB_CMD_IS_SNOOP_SHIFT 35
#define DIAG_CBOX_MODE2_ARB_CMD_IS_SNOOP_WIDTH 1
#define DIAG_CBOX_MODE2_ARB_CMD_IS_SNOOP_RMASK 0x1
#define DIAG_CBOX_MODE2_ARB_CMD_IS_SNOOP_MASK _64bit(0x800000000)
#define DIAG_CBOX_MODE2_ARB_CMD_IS_SNOOP_FIELD 35,35

#define DIAG_CBOX_MODE2_ARB_SEL_SHIFT 36
#define DIAG_CBOX_MODE2_ARB_SEL_WIDTH 7
#define DIAG_CBOX_MODE2_ARB_SEL_RMASK 0x7f
#define DIAG_CBOX_MODE2_ARB_SEL_MASK _64bit(0x7f000000000)
#define DIAG_CBOX_MODE2_ARB_SEL_FIELD 42,36

#define DIAG_CBOX_MODE2_ARB_REQ_SHIFT 43
#define DIAG_CBOX_MODE2_ARB_REQ_WIDTH 7
#define DIAG_CBOX_MODE2_ARB_REQ_RMASK 0x7f
#define DIAG_CBOX_MODE2_ARB_REQ_MASK _64bit(0x3f80000000000)
#define DIAG_CBOX_MODE2_ARB_REQ_FIELD 49,43

#define DIAG_CBOX_MODE2_REJECT_VEC_SHIFT 50
#define DIAG_CBOX_MODE2_REJECT_VEC_WIDTH 4
#define DIAG_CBOX_MODE2_REJECT_VEC_RMASK 0xf
#define DIAG_CBOX_MODE2_REJECT_VEC_MASK _64bit(0x3c000000000000)
#define DIAG_CBOX_MODE2_REJECT_VEC_FIELD 53,50

#define DIAG_CBOX_MODE2_MF_STATE_SHIFT 54
#define DIAG_CBOX_MODE2_MF_STATE_WIDTH 3
#define DIAG_CBOX_MODE2_MF_STATE_RMASK 0x7
#define DIAG_CBOX_MODE2_MF_STATE_MASK _64bit(0x1c0000000000000)
#define DIAG_CBOX_MODE2_MF_STATE_FIELD 56,54

#define DIAG_CBOX_MODE2_STARVATION_STATUS_SHIFT 57
#define DIAG_CBOX_MODE2_STARVATION_STATUS_WIDTH 7
#define DIAG_CBOX_MODE2_STARVATION_STATUS_RMASK 0x7f
#define DIAG_CBOX_MODE2_STARVATION_STATUS_MASK _64bit(0xfe00000000000000)
#define DIAG_CBOX_MODE2_STARVATION_STATUS_FIELD 63,57


#define DIAG_CBOX_MODE3_C2_PA_30_SHIFT 0
#define DIAG_CBOX_MODE3_C2_PA_30_WIDTH 30
#define DIAG_CBOX_MODE3_C2_PA_30_RMASK 0x3fffffff
#define DIAG_CBOX_MODE3_C2_PA_30_MASK 0x3fffffff
#define DIAG_CBOX_MODE3_C2_PA_30_FIELD 29,0

#define DIAG_CBOX_MODE3_ARB_CMD_SHIFT 30
#define DIAG_CBOX_MODE3_ARB_CMD_WIDTH 5
#define DIAG_CBOX_MODE3_ARB_CMD_RMASK 0x1f
#define DIAG_CBOX_MODE3_ARB_CMD_MASK _64bit(0x7c0000000)
#define DIAG_CBOX_MODE3_ARB_CMD_FIELD 34,30

#define DIAG_CBOX_MODE3_ARB_CMD_IS_SNOOP_SHIFT 35
#define DIAG_CBOX_MODE3_ARB_CMD_IS_SNOOP_WIDTH 1
#define DIAG_CBOX_MODE3_ARB_CMD_IS_SNOOP_RMASK 0x1
#define DIAG_CBOX_MODE3_ARB_CMD_IS_SNOOP_MASK _64bit(0x800000000)
#define DIAG_CBOX_MODE3_ARB_CMD_IS_SNOOP_FIELD 35,35

#define DIAG_CBOX_MODE3_TAG_HIT_VEC_SHIFT 36
#define DIAG_CBOX_MODE3_TAG_HIT_VEC_WIDTH 8
#define DIAG_CBOX_MODE3_TAG_HIT_VEC_RMASK 0xff
#define DIAG_CBOX_MODE3_TAG_HIT_VEC_MASK _64bit(0xff000000000)
#define DIAG_CBOX_MODE3_TAG_HIT_VEC_FIELD 43,36

#define DIAG_CBOX_MODE3_WAY_STATE_SHIFT 44
#define DIAG_CBOX_MODE3_WAY_STATE_WIDTH 8
#define DIAG_CBOX_MODE3_WAY_STATE_RMASK 0xff
#define DIAG_CBOX_MODE3_WAY_STATE_MASK _64bit(0xff00000000000)
#define DIAG_CBOX_MODE3_WAY_STATE_FIELD 51,44

#define DIAG_CBOX_MODE3_WAY_SHR_STATE_SHIFT 52
#define DIAG_CBOX_MODE3_WAY_SHR_STATE_WIDTH 3
#define DIAG_CBOX_MODE3_WAY_SHR_STATE_RMASK 0x7
#define DIAG_CBOX_MODE3_WAY_SHR_STATE_MASK _64bit(0x70000000000000)
#define DIAG_CBOX_MODE3_WAY_SHR_STATE_FIELD 54,52

#define DIAG_CBOX_MODE3_IFILL_RTN_SHIFT 55
#define DIAG_CBOX_MODE3_IFILL_RTN_WIDTH 1
#define DIAG_CBOX_MODE3_IFILL_RTN_RMASK 0x1
#define DIAG_CBOX_MODE3_IFILL_RTN_MASK _64bit(0x80000000000000)
#define DIAG_CBOX_MODE3_IFILL_RTN_FIELD 55,55

#define DIAG_CBOX_MODE3_MP_RTN_SHIFT 56
#define DIAG_CBOX_MODE3_MP_RTN_WIDTH 1
#define DIAG_CBOX_MODE3_MP_RTN_RMASK 0x1
#define DIAG_CBOX_MODE3_MP_RTN_MASK _64bit(0x100000000000000)
#define DIAG_CBOX_MODE3_MP_RTN_FIELD 56,56

#define DIAG_CBOX_MODE3_FILL_CMD_SHIFT 57
#define DIAG_CBOX_MODE3_FILL_CMD_WIDTH 2
#define DIAG_CBOX_MODE3_FILL_CMD_RMASK 0x3
#define DIAG_CBOX_MODE3_FILL_CMD_MASK _64bit(0x600000000000000)
#define DIAG_CBOX_MODE3_FILL_CMD_FIELD 58,57

#define DIAG_CBOX_MODE3_STALL_MP_ISSUE_SHIFT 59
#define DIAG_CBOX_MODE3_STALL_MP_ISSUE_WIDTH 1
#define DIAG_CBOX_MODE3_STALL_MP_ISSUE_RMASK 0x1
#define DIAG_CBOX_MODE3_STALL_MP_ISSUE_MASK _64bit(0x800000000000000)
#define DIAG_CBOX_MODE3_STALL_MP_ISSUE_FIELD 59,59

#define DIAG_CBOX_MODE3_STALL_SKF_ISSUE_SHIFT 60
#define DIAG_CBOX_MODE3_STALL_SKF_ISSUE_WIDTH 1
#define DIAG_CBOX_MODE3_STALL_SKF_ISSUE_RMASK 0x1
#define DIAG_CBOX_MODE3_STALL_SKF_ISSUE_MASK _64bit(0x1000000000000000)
#define DIAG_CBOX_MODE3_STALL_SKF_ISSUE_FIELD 60,60


#define DIAG_CBOX_MODE4_C2_PA_30_SHIFT 0
#define DIAG_CBOX_MODE4_C2_PA_30_WIDTH 30
#define DIAG_CBOX_MODE4_C2_PA_30_RMASK 0x3fffffff
#define DIAG_CBOX_MODE4_C2_PA_30_MASK 0x3fffffff
#define DIAG_CBOX_MODE4_C2_PA_30_FIELD 29,0

#define DIAG_CBOX_MODE4_ARB_CMD_SHIFT 30
#define DIAG_CBOX_MODE4_ARB_CMD_WIDTH 5
#define DIAG_CBOX_MODE4_ARB_CMD_RMASK 0x1f
#define DIAG_CBOX_MODE4_ARB_CMD_MASK _64bit(0x7c0000000)
#define DIAG_CBOX_MODE4_ARB_CMD_FIELD 34,30

#define DIAG_CBOX_MODE4_ARB_CMD_IS_SNOOP_SHIFT 35
#define DIAG_CBOX_MODE4_ARB_CMD_IS_SNOOP_WIDTH 1
#define DIAG_CBOX_MODE4_ARB_CMD_IS_SNOOP_RMASK 0x1
#define DIAG_CBOX_MODE4_ARB_CMD_IS_SNOOP_MASK _64bit(0x800000000)
#define DIAG_CBOX_MODE4_ARB_CMD_IS_SNOOP_FIELD 35,35

#define DIAG_CBOX_MODE4_MAF_CNT_SHIFT 36
#define DIAG_CBOX_MODE4_MAF_CNT_WIDTH 4
#define DIAG_CBOX_MODE4_MAF_CNT_RMASK 0xf
#define DIAG_CBOX_MODE4_MAF_CNT_MASK _64bit(0xf000000000)
#define DIAG_CBOX_MODE4_MAF_CNT_FIELD 39,36

#define DIAG_CBOX_MODE4_LRTF_CNT_SHIFT 40
#define DIAG_CBOX_MODE4_LRTF_CNT_WIDTH 5
#define DIAG_CBOX_MODE4_LRTF_CNT_RMASK 0x1f
#define DIAG_CBOX_MODE4_LRTF_CNT_MASK _64bit(0x1f0000000000)
#define DIAG_CBOX_MODE4_LRTF_CNT_FIELD 44,40

#define DIAG_CBOX_MODE4_RRTF_CNT_SHIFT 45
#define DIAG_CBOX_MODE4_RRTF_CNT_WIDTH 5
#define DIAG_CBOX_MODE4_RRTF_CNT_RMASK 0x1f
#define DIAG_CBOX_MODE4_RRTF_CNT_MASK _64bit(0x3e00000000000)
#define DIAG_CBOX_MODE4_RRTF_CNT_FIELD 49,45

#define DIAG_CBOX_MODE4_MAF_CMD_SHIFT 50
#define DIAG_CBOX_MODE4_MAF_CMD_WIDTH 5
#define DIAG_CBOX_MODE4_MAF_CMD_RMASK 0x1f
#define DIAG_CBOX_MODE4_MAF_CMD_MASK _64bit(0x7c000000000000)
#define DIAG_CBOX_MODE4_MAF_CMD_FIELD 54,50

#define DIAG_CBOX_MODE4_MAF_CMD_IS_SNOOP_SHIFT 55
#define DIAG_CBOX_MODE4_MAF_CMD_IS_SNOOP_WIDTH 1
#define DIAG_CBOX_MODE4_MAF_CMD_IS_SNOOP_RMASK 0x1
#define DIAG_CBOX_MODE4_MAF_CMD_IS_SNOOP_MASK _64bit(0x80000000000000)
#define DIAG_CBOX_MODE4_MAF_CMD_IS_SNOOP_FIELD 55,55




/* Constants for XDN diags */

#define DIAG_XDN_MODE1_UDN_CORE_EGR_SHIFT 0
#define DIAG_XDN_MODE1_UDN_CORE_EGR_WIDTH 1
#define DIAG_XDN_MODE1_UDN_CORE_EGR_RMASK 0x1
#define DIAG_XDN_MODE1_UDN_CORE_EGR_MASK 0x1
#define DIAG_XDN_MODE1_UDN_CORE_EGR_FIELD 0,0

#define DIAG_XDN_MODE1_IDN_CORE_EGR_SHIFT 1
#define DIAG_XDN_MODE1_IDN_CORE_EGR_WIDTH 1
#define DIAG_XDN_MODE1_IDN_CORE_EGR_RMASK 0x1
#define DIAG_XDN_MODE1_IDN_CORE_EGR_MASK 0x2
#define DIAG_XDN_MODE1_IDN_CORE_EGR_FIELD 1,1

#define DIAG_XDN_MODE1_RDN_CORE_EGR_SHIFT 2
#define DIAG_XDN_MODE1_RDN_CORE_EGR_WIDTH 1
#define DIAG_XDN_MODE1_RDN_CORE_EGR_RMASK 0x1
#define DIAG_XDN_MODE1_RDN_CORE_EGR_MASK 0x4
#define DIAG_XDN_MODE1_RDN_CORE_EGR_FIELD 2,2

#define DIAG_XDN_MODE1_SDN_CORE_EGR_SHIFT 3
#define DIAG_XDN_MODE1_SDN_CORE_EGR_WIDTH 1
#define DIAG_XDN_MODE1_SDN_CORE_EGR_RMASK 0x1
#define DIAG_XDN_MODE1_SDN_CORE_EGR_MASK 0x8
#define DIAG_XDN_MODE1_SDN_CORE_EGR_FIELD 3,3

#define DIAG_XDN_MODE1_QDN_CORE_EGR_SHIFT 4
#define DIAG_XDN_MODE1_QDN_CORE_EGR_WIDTH 1
#define DIAG_XDN_MODE1_QDN_CORE_EGR_RMASK 0x1
#define DIAG_XDN_MODE1_QDN_CORE_EGR_MASK 0x10
#define DIAG_XDN_MODE1_QDN_CORE_EGR_FIELD 4,4

#define DIAG_XDN_MODE1_UDN_CORE_ING_SHIFT 5
#define DIAG_XDN_MODE1_UDN_CORE_ING_WIDTH 1
#define DIAG_XDN_MODE1_UDN_CORE_ING_RMASK 0x1
#define DIAG_XDN_MODE1_UDN_CORE_ING_MASK 0x20
#define DIAG_XDN_MODE1_UDN_CORE_ING_FIELD 5,5

#define DIAG_XDN_MODE1_IDN_CORE_ING_SHIFT 6
#define DIAG_XDN_MODE1_IDN_CORE_ING_WIDTH 1
#define DIAG_XDN_MODE1_IDN_CORE_ING_RMASK 0x1
#define DIAG_XDN_MODE1_IDN_CORE_ING_MASK 0x40
#define DIAG_XDN_MODE1_IDN_CORE_ING_FIELD 6,6

#define DIAG_XDN_MODE1_RDN_CORE_ING_SHIFT 7
#define DIAG_XDN_MODE1_RDN_CORE_ING_WIDTH 1
#define DIAG_XDN_MODE1_RDN_CORE_ING_RMASK 0x1
#define DIAG_XDN_MODE1_RDN_CORE_ING_MASK 0x80
#define DIAG_XDN_MODE1_RDN_CORE_ING_FIELD 7,7

#define DIAG_XDN_MODE1_SDN_CORE_ING_SHIFT 8
#define DIAG_XDN_MODE1_SDN_CORE_ING_WIDTH 1
#define DIAG_XDN_MODE1_SDN_CORE_ING_RMASK 0x1
#define DIAG_XDN_MODE1_SDN_CORE_ING_MASK 0x100
#define DIAG_XDN_MODE1_SDN_CORE_ING_FIELD 8,8

#define DIAG_XDN_MODE1_QDN_CORE_ING_SHIFT 9
#define DIAG_XDN_MODE1_QDN_CORE_ING_WIDTH 1
#define DIAG_XDN_MODE1_QDN_CORE_ING_RMASK 0x1
#define DIAG_XDN_MODE1_QDN_CORE_ING_MASK 0x200
#define DIAG_XDN_MODE1_QDN_CORE_ING_FIELD 9,9

#define DIAG_XDN_MODE1_UDN_COMP_EGR_SHIFT 10
#define DIAG_XDN_MODE1_UDN_COMP_EGR_WIDTH 4
#define DIAG_XDN_MODE1_UDN_COMP_EGR_RMASK 0xf
#define DIAG_XDN_MODE1_UDN_COMP_EGR_MASK 0x3c00
#define DIAG_XDN_MODE1_UDN_COMP_EGR_FIELD 13,10

#define DIAG_XDN_MODE1_IDN_COMP_EGR_SHIFT 14
#define DIAG_XDN_MODE1_IDN_COMP_EGR_WIDTH 4
#define DIAG_XDN_MODE1_IDN_COMP_EGR_RMASK 0xf
#define DIAG_XDN_MODE1_IDN_COMP_EGR_MASK 0x3c000
#define DIAG_XDN_MODE1_IDN_COMP_EGR_FIELD 17,14

#define DIAG_XDN_MODE1_RDN_COMP_EGR_SHIFT 18
#define DIAG_XDN_MODE1_RDN_COMP_EGR_WIDTH 4
#define DIAG_XDN_MODE1_RDN_COMP_EGR_RMASK 0xf
#define DIAG_XDN_MODE1_RDN_COMP_EGR_MASK 0x3c0000
#define DIAG_XDN_MODE1_RDN_COMP_EGR_FIELD 21,18

#define DIAG_XDN_MODE1_SDN_COMP_EGR_SHIFT 22
#define DIAG_XDN_MODE1_SDN_COMP_EGR_WIDTH 4
#define DIAG_XDN_MODE1_SDN_COMP_EGR_RMASK 0xf
#define DIAG_XDN_MODE1_SDN_COMP_EGR_MASK 0x3c00000
#define DIAG_XDN_MODE1_SDN_COMP_EGR_FIELD 25,22

#define DIAG_XDN_MODE1_QDN_COMP_EGR_SHIFT 26
#define DIAG_XDN_MODE1_QDN_COMP_EGR_WIDTH 4
#define DIAG_XDN_MODE1_QDN_COMP_EGR_RMASK 0xf
#define DIAG_XDN_MODE1_QDN_COMP_EGR_MASK 0x3c000000
#define DIAG_XDN_MODE1_QDN_COMP_EGR_FIELD 29,26

#define DIAG_XDN_MODE1_UDN_COMP_ING_SHIFT 30
#define DIAG_XDN_MODE1_UDN_COMP_ING_WIDTH 4
#define DIAG_XDN_MODE1_UDN_COMP_ING_RMASK 0xf
#define DIAG_XDN_MODE1_UDN_COMP_ING_MASK _64bit(0x3c0000000)
#define DIAG_XDN_MODE1_UDN_COMP_ING_FIELD 33,30

#define DIAG_XDN_MODE1_IDN_COMP_ING_SHIFT 34
#define DIAG_XDN_MODE1_IDN_COMP_ING_WIDTH 4
#define DIAG_XDN_MODE1_IDN_COMP_ING_RMASK 0xf
#define DIAG_XDN_MODE1_IDN_COMP_ING_MASK _64bit(0x3c00000000)
#define DIAG_XDN_MODE1_IDN_COMP_ING_FIELD 37,34

#define DIAG_XDN_MODE1_RDN_COMP_ING_SHIFT 38
#define DIAG_XDN_MODE1_RDN_COMP_ING_WIDTH 4
#define DIAG_XDN_MODE1_RDN_COMP_ING_RMASK 0xf
#define DIAG_XDN_MODE1_RDN_COMP_ING_MASK _64bit(0x3c000000000)
#define DIAG_XDN_MODE1_RDN_COMP_ING_FIELD 41,38

#define DIAG_XDN_MODE1_SDN_COMP_ING_SHIFT 42
#define DIAG_XDN_MODE1_SDN_COMP_ING_WIDTH 4
#define DIAG_XDN_MODE1_SDN_COMP_ING_RMASK 0xf
#define DIAG_XDN_MODE1_SDN_COMP_ING_MASK _64bit(0x3c0000000000)
#define DIAG_XDN_MODE1_SDN_COMP_ING_FIELD 45,42

#define DIAG_XDN_MODE1_QDN_COMP_ING_SHIFT 46
#define DIAG_XDN_MODE1_QDN_COMP_ING_WIDTH 4
#define DIAG_XDN_MODE1_QDN_COMP_ING_RMASK 0xf
#define DIAG_XDN_MODE1_QDN_COMP_ING_MASK _64bit(0x3c00000000000)
#define DIAG_XDN_MODE1_QDN_COMP_ING_FIELD 49,46

#define DIAG_XDN_MODE1_UDN_DMX_STALL_SHIFT 50
#define DIAG_XDN_MODE1_UDN_DMX_STALL_WIDTH 1
#define DIAG_XDN_MODE1_UDN_DMX_STALL_RMASK 0x1
#define DIAG_XDN_MODE1_UDN_DMX_STALL_MASK _64bit(0x4000000000000)
#define DIAG_XDN_MODE1_UDN_DMX_STALL_FIELD 50,50

#define DIAG_XDN_MODE1_IDN_DMX_STALL_SHIFT 51
#define DIAG_XDN_MODE1_IDN_DMX_STALL_WIDTH 1
#define DIAG_XDN_MODE1_IDN_DMX_STALL_RMASK 0x1
#define DIAG_XDN_MODE1_IDN_DMX_STALL_MASK _64bit(0x8000000000000)
#define DIAG_XDN_MODE1_IDN_DMX_STALL_FIELD 51,51

#define DIAG_XDN_MODE1_UDN_DMX_Q_AVAIL_SHIFT 52
#define DIAG_XDN_MODE1_UDN_DMX_Q_AVAIL_WIDTH 4
#define DIAG_XDN_MODE1_UDN_DMX_Q_AVAIL_RMASK 0xf
#define DIAG_XDN_MODE1_UDN_DMX_Q_AVAIL_MASK _64bit(0xf0000000000000)
#define DIAG_XDN_MODE1_UDN_DMX_Q_AVAIL_FIELD 55,52

#define DIAG_XDN_MODE1_IDN_DMX_Q_AVAIL_SHIFT 56
#define DIAG_XDN_MODE1_IDN_DMX_Q_AVAIL_WIDTH 2
#define DIAG_XDN_MODE1_IDN_DMX_Q_AVAIL_RMASK 0x3
#define DIAG_XDN_MODE1_IDN_DMX_Q_AVAIL_MASK _64bit(0x300000000000000)
#define DIAG_XDN_MODE1_IDN_DMX_Q_AVAIL_FIELD 57,56




/* Constants for SPCL diags */


#endif /* __ARCH_DIAG_H__ */
