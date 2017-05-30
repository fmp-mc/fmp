/**
 * TILEGx Architecture Support Package for TOPPERS/FMP Kernel
 *
 * Copyright (C) 2016 by Yixiao Li (liyixiao@ertl.jp)
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

// TODO: Move this file to somewhere else other than 'posix/include'

#pragma once

/**
 * Rectangle of tiles controlled by supervisor (client)
 */
/** [[[cog
import cog, pass0
cog.outl('''\
#define TILEGX_CLIENT_WD ({client_width})
#define TILEGX_CLIENT_HT ({client_height})\
'''.format(**vars(pass0)))
]]] */
#define TILEGX_CLIENT_WD (8)
#define TILEGX_CLIENT_HT (9)
/* [[[end]]] */

/**
 * Number of processors
 */
#define TNUM_PRCID ((TILEGX_CLIENT_WD) * (TILEGX_CLIENT_HT))

/**
 * Only CLASS IDs for each processor are supported currently
 */
/** [[[cog
import cog, pass0
for i in range(1, pass0.core_number + 1):
	cog.outl('#define TCL_%(i)s\t(%(i)s)' % {'i':i})
]]] */
#define TCL_1	(1)
#define TCL_2	(2)
#define TCL_3	(3)
#define TCL_4	(4)
#define TCL_5	(5)
#define TCL_6	(6)
#define TCL_7	(7)
#define TCL_8	(8)
#define TCL_9	(9)
#define TCL_10	(10)
#define TCL_11	(11)
#define TCL_12	(12)
#define TCL_13	(13)
#define TCL_14	(14)
#define TCL_15	(15)
#define TCL_16	(16)
#define TCL_17	(17)
#define TCL_18	(18)
#define TCL_19	(19)
#define TCL_20	(20)
#define TCL_21	(21)
#define TCL_22	(22)
#define TCL_23	(23)
#define TCL_24	(24)
#define TCL_25	(25)
#define TCL_26	(26)
#define TCL_27	(27)
#define TCL_28	(28)
#define TCL_29	(29)
#define TCL_30	(30)
#define TCL_31	(31)
#define TCL_32	(32)
#define TCL_33	(33)
#define TCL_34	(34)
#define TCL_35	(35)
#define TCL_36	(36)
#define TCL_37	(37)
#define TCL_38	(38)
#define TCL_39	(39)
#define TCL_40	(40)
#define TCL_41	(41)
#define TCL_42	(42)
#define TCL_43	(43)
#define TCL_44	(44)
#define TCL_45	(45)
#define TCL_46	(46)
#define TCL_47	(47)
#define TCL_48	(48)
#define TCL_49	(49)
#define TCL_50	(50)
#define TCL_51	(51)
#define TCL_52	(52)
#define TCL_53	(53)
#define TCL_54	(54)
#define TCL_55	(55)
#define TCL_56	(56)
#define TCL_57	(57)
#define TCL_58	(58)
#define TCL_59	(59)
#define TCL_60	(60)
#define TCL_61	(61)
#define TCL_62	(62)
#define TCL_63	(63)
#define TCL_64	(64)
#define TCL_65	(65)
#define TCL_66	(66)
#define TCL_67	(67)
#define TCL_68	(68)
#define TCL_69	(69)
#define TCL_70	(70)
#define TCL_71	(71)
#define TCL_72	(72)
/* [[[end]]] */

/**
 * Default CLASS IDs for each processor
 */
/** [[[cog
import cog, pass0
for i in range(1, pass0.core_number + 1):
	cog.outl('#define DEFAULT_PRC%(i)s_ISTKSZ \t(DEFAULT_ISTKSZ)' % {'i':i})
]]] */
#define DEFAULT_PRC1_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC2_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC3_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC4_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC5_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC6_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC7_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC8_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC9_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC10_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC11_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC12_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC13_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC14_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC15_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC16_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC17_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC18_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC19_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC20_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC21_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC22_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC23_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC24_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC25_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC26_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC27_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC28_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC29_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC30_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC31_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC32_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC33_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC34_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC35_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC36_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC37_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC38_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC39_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC40_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC41_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC42_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC43_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC44_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC45_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC46_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC47_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC48_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC49_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC50_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC51_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC52_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC53_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC54_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC55_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC56_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC57_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC58_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC59_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC60_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC61_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC62_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC63_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC64_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC65_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC66_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC67_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC68_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC69_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC70_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC71_ISTKSZ 	(DEFAULT_ISTKSZ)
#define DEFAULT_PRC72_ISTKSZ 	(DEFAULT_ISTKSZ)
/* [[[end]]] */

/**
 * Macros for global timer
 */
#define TOPPERS_SYSTIM_PRCID (1) // Master processor's timer as the global timer
#if defined(TOPPERS_SYSTIM_GLOBAL)
#define TCL_SYSTIM_PRC TCL_1     // TODO: use a dedicate class for global timer?
#endif
