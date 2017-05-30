OUTPUT_ARCH(tile)
ENTRY(_start)

/*
PROVIDE(hardware_init_hook = 0);
PROVIDE(software_init_hook = 0);
PROVIDE(software_term_hook = 0);
*/

PHDRS
{
  text PT_LOAD;
  data PT_LOAD;
}

SECTIONS
{  
    /* Hypervisor call vectors */
  .hvglue (0x10000/*HV_GLUE_START_CPA*/): {
    *(.hvglue)
  } :NONE

    . = 0x20000;
    .text :
    {
        __text = . ;
        *(.intrpt)
        *(.head.text)
        *(.text)
        *(.text.*)
        *(.glue_7t)
        *(.glue_7)
    } : text
    _etext = .	;
    PROVIDE (etext = .)	;
    .rodata : {
		*(.rodata)
		*(.rodata.*)
	} : text

    . = ALIGN(4);
    __idata_start = . ;
    .data   :  AT(__idata_start)
    {
        __data_start = . ;
        *(.init.data)
        *(.data)
        *(.data.*)
    } : data
    __idata_end = __idata_start + SIZEOF(.data);
    _edata  =  . ;
    PROVIDE (edata = .);

    . = ALIGN(4);
    __bss_start = .	;
    .bss (NOLOAD)      :
    {
. = ALIGN(0x1000000);
      *(.bss)
      *(.bss.*)
      *(COMMON)
/* [[[cog
import cog, pass0
for i in range(1, pass0.core_number + 1):
#    cog.outl('. = ALIGN(0x10000);') # small page size aligned
    cog.outl('. = ALIGN(0x1000000);') # large page size aligned
    cog.outl('''\
    _local_cached_prc{0}_bss_start = .;
    *(.local_cached_prc{0}.bss)
    *(.local_cached_prc{0}.stack)'''.format(i))
    cog.outl('. = ALIGN(0x1000000);') # large page size aligned
    cog.outl('''_local_cached_prc{0}_bss_end = .;'''.format(i))
"""
    cog.outl('''\
.local_cached_prc{0}.bss : {{
    _local_cached_prc{0}_bss_start = .;
    *(.local_cached_prc{0}.bss)
    _local_cached_prc{0}_bss_end = .;
}} : data'''.format(i))
"""
]]] */
. = ALIGN(0x1000000);
    _local_cached_prc1_bss_start = .;
    *(.local_cached_prc1.bss)
    *(.local_cached_prc1.stack)
. = ALIGN(0x1000000);
_local_cached_prc1_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc2_bss_start = .;
    *(.local_cached_prc2.bss)
    *(.local_cached_prc2.stack)
. = ALIGN(0x1000000);
_local_cached_prc2_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc3_bss_start = .;
    *(.local_cached_prc3.bss)
    *(.local_cached_prc3.stack)
. = ALIGN(0x1000000);
_local_cached_prc3_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc4_bss_start = .;
    *(.local_cached_prc4.bss)
    *(.local_cached_prc4.stack)
. = ALIGN(0x1000000);
_local_cached_prc4_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc5_bss_start = .;
    *(.local_cached_prc5.bss)
    *(.local_cached_prc5.stack)
. = ALIGN(0x1000000);
_local_cached_prc5_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc6_bss_start = .;
    *(.local_cached_prc6.bss)
    *(.local_cached_prc6.stack)
. = ALIGN(0x1000000);
_local_cached_prc6_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc7_bss_start = .;
    *(.local_cached_prc7.bss)
    *(.local_cached_prc7.stack)
. = ALIGN(0x1000000);
_local_cached_prc7_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc8_bss_start = .;
    *(.local_cached_prc8.bss)
    *(.local_cached_prc8.stack)
. = ALIGN(0x1000000);
_local_cached_prc8_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc9_bss_start = .;
    *(.local_cached_prc9.bss)
    *(.local_cached_prc9.stack)
. = ALIGN(0x1000000);
_local_cached_prc9_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc10_bss_start = .;
    *(.local_cached_prc10.bss)
    *(.local_cached_prc10.stack)
. = ALIGN(0x1000000);
_local_cached_prc10_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc11_bss_start = .;
    *(.local_cached_prc11.bss)
    *(.local_cached_prc11.stack)
. = ALIGN(0x1000000);
_local_cached_prc11_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc12_bss_start = .;
    *(.local_cached_prc12.bss)
    *(.local_cached_prc12.stack)
. = ALIGN(0x1000000);
_local_cached_prc12_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc13_bss_start = .;
    *(.local_cached_prc13.bss)
    *(.local_cached_prc13.stack)
. = ALIGN(0x1000000);
_local_cached_prc13_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc14_bss_start = .;
    *(.local_cached_prc14.bss)
    *(.local_cached_prc14.stack)
. = ALIGN(0x1000000);
_local_cached_prc14_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc15_bss_start = .;
    *(.local_cached_prc15.bss)
    *(.local_cached_prc15.stack)
. = ALIGN(0x1000000);
_local_cached_prc15_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc16_bss_start = .;
    *(.local_cached_prc16.bss)
    *(.local_cached_prc16.stack)
. = ALIGN(0x1000000);
_local_cached_prc16_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc17_bss_start = .;
    *(.local_cached_prc17.bss)
    *(.local_cached_prc17.stack)
. = ALIGN(0x1000000);
_local_cached_prc17_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc18_bss_start = .;
    *(.local_cached_prc18.bss)
    *(.local_cached_prc18.stack)
. = ALIGN(0x1000000);
_local_cached_prc18_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc19_bss_start = .;
    *(.local_cached_prc19.bss)
    *(.local_cached_prc19.stack)
. = ALIGN(0x1000000);
_local_cached_prc19_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc20_bss_start = .;
    *(.local_cached_prc20.bss)
    *(.local_cached_prc20.stack)
. = ALIGN(0x1000000);
_local_cached_prc20_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc21_bss_start = .;
    *(.local_cached_prc21.bss)
    *(.local_cached_prc21.stack)
. = ALIGN(0x1000000);
_local_cached_prc21_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc22_bss_start = .;
    *(.local_cached_prc22.bss)
    *(.local_cached_prc22.stack)
. = ALIGN(0x1000000);
_local_cached_prc22_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc23_bss_start = .;
    *(.local_cached_prc23.bss)
    *(.local_cached_prc23.stack)
. = ALIGN(0x1000000);
_local_cached_prc23_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc24_bss_start = .;
    *(.local_cached_prc24.bss)
    *(.local_cached_prc24.stack)
. = ALIGN(0x1000000);
_local_cached_prc24_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc25_bss_start = .;
    *(.local_cached_prc25.bss)
    *(.local_cached_prc25.stack)
. = ALIGN(0x1000000);
_local_cached_prc25_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc26_bss_start = .;
    *(.local_cached_prc26.bss)
    *(.local_cached_prc26.stack)
. = ALIGN(0x1000000);
_local_cached_prc26_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc27_bss_start = .;
    *(.local_cached_prc27.bss)
    *(.local_cached_prc27.stack)
. = ALIGN(0x1000000);
_local_cached_prc27_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc28_bss_start = .;
    *(.local_cached_prc28.bss)
    *(.local_cached_prc28.stack)
. = ALIGN(0x1000000);
_local_cached_prc28_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc29_bss_start = .;
    *(.local_cached_prc29.bss)
    *(.local_cached_prc29.stack)
. = ALIGN(0x1000000);
_local_cached_prc29_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc30_bss_start = .;
    *(.local_cached_prc30.bss)
    *(.local_cached_prc30.stack)
. = ALIGN(0x1000000);
_local_cached_prc30_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc31_bss_start = .;
    *(.local_cached_prc31.bss)
    *(.local_cached_prc31.stack)
. = ALIGN(0x1000000);
_local_cached_prc31_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc32_bss_start = .;
    *(.local_cached_prc32.bss)
    *(.local_cached_prc32.stack)
. = ALIGN(0x1000000);
_local_cached_prc32_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc33_bss_start = .;
    *(.local_cached_prc33.bss)
    *(.local_cached_prc33.stack)
. = ALIGN(0x1000000);
_local_cached_prc33_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc34_bss_start = .;
    *(.local_cached_prc34.bss)
    *(.local_cached_prc34.stack)
. = ALIGN(0x1000000);
_local_cached_prc34_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc35_bss_start = .;
    *(.local_cached_prc35.bss)
    *(.local_cached_prc35.stack)
. = ALIGN(0x1000000);
_local_cached_prc35_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc36_bss_start = .;
    *(.local_cached_prc36.bss)
    *(.local_cached_prc36.stack)
. = ALIGN(0x1000000);
_local_cached_prc36_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc37_bss_start = .;
    *(.local_cached_prc37.bss)
    *(.local_cached_prc37.stack)
. = ALIGN(0x1000000);
_local_cached_prc37_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc38_bss_start = .;
    *(.local_cached_prc38.bss)
    *(.local_cached_prc38.stack)
. = ALIGN(0x1000000);
_local_cached_prc38_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc39_bss_start = .;
    *(.local_cached_prc39.bss)
    *(.local_cached_prc39.stack)
. = ALIGN(0x1000000);
_local_cached_prc39_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc40_bss_start = .;
    *(.local_cached_prc40.bss)
    *(.local_cached_prc40.stack)
. = ALIGN(0x1000000);
_local_cached_prc40_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc41_bss_start = .;
    *(.local_cached_prc41.bss)
    *(.local_cached_prc41.stack)
. = ALIGN(0x1000000);
_local_cached_prc41_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc42_bss_start = .;
    *(.local_cached_prc42.bss)
    *(.local_cached_prc42.stack)
. = ALIGN(0x1000000);
_local_cached_prc42_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc43_bss_start = .;
    *(.local_cached_prc43.bss)
    *(.local_cached_prc43.stack)
. = ALIGN(0x1000000);
_local_cached_prc43_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc44_bss_start = .;
    *(.local_cached_prc44.bss)
    *(.local_cached_prc44.stack)
. = ALIGN(0x1000000);
_local_cached_prc44_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc45_bss_start = .;
    *(.local_cached_prc45.bss)
    *(.local_cached_prc45.stack)
. = ALIGN(0x1000000);
_local_cached_prc45_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc46_bss_start = .;
    *(.local_cached_prc46.bss)
    *(.local_cached_prc46.stack)
. = ALIGN(0x1000000);
_local_cached_prc46_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc47_bss_start = .;
    *(.local_cached_prc47.bss)
    *(.local_cached_prc47.stack)
. = ALIGN(0x1000000);
_local_cached_prc47_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc48_bss_start = .;
    *(.local_cached_prc48.bss)
    *(.local_cached_prc48.stack)
. = ALIGN(0x1000000);
_local_cached_prc48_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc49_bss_start = .;
    *(.local_cached_prc49.bss)
    *(.local_cached_prc49.stack)
. = ALIGN(0x1000000);
_local_cached_prc49_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc50_bss_start = .;
    *(.local_cached_prc50.bss)
    *(.local_cached_prc50.stack)
. = ALIGN(0x1000000);
_local_cached_prc50_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc51_bss_start = .;
    *(.local_cached_prc51.bss)
    *(.local_cached_prc51.stack)
. = ALIGN(0x1000000);
_local_cached_prc51_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc52_bss_start = .;
    *(.local_cached_prc52.bss)
    *(.local_cached_prc52.stack)
. = ALIGN(0x1000000);
_local_cached_prc52_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc53_bss_start = .;
    *(.local_cached_prc53.bss)
    *(.local_cached_prc53.stack)
. = ALIGN(0x1000000);
_local_cached_prc53_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc54_bss_start = .;
    *(.local_cached_prc54.bss)
    *(.local_cached_prc54.stack)
. = ALIGN(0x1000000);
_local_cached_prc54_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc55_bss_start = .;
    *(.local_cached_prc55.bss)
    *(.local_cached_prc55.stack)
. = ALIGN(0x1000000);
_local_cached_prc55_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc56_bss_start = .;
    *(.local_cached_prc56.bss)
    *(.local_cached_prc56.stack)
. = ALIGN(0x1000000);
_local_cached_prc56_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc57_bss_start = .;
    *(.local_cached_prc57.bss)
    *(.local_cached_prc57.stack)
. = ALIGN(0x1000000);
_local_cached_prc57_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc58_bss_start = .;
    *(.local_cached_prc58.bss)
    *(.local_cached_prc58.stack)
. = ALIGN(0x1000000);
_local_cached_prc58_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc59_bss_start = .;
    *(.local_cached_prc59.bss)
    *(.local_cached_prc59.stack)
. = ALIGN(0x1000000);
_local_cached_prc59_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc60_bss_start = .;
    *(.local_cached_prc60.bss)
    *(.local_cached_prc60.stack)
. = ALIGN(0x1000000);
_local_cached_prc60_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc61_bss_start = .;
    *(.local_cached_prc61.bss)
    *(.local_cached_prc61.stack)
. = ALIGN(0x1000000);
_local_cached_prc61_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc62_bss_start = .;
    *(.local_cached_prc62.bss)
    *(.local_cached_prc62.stack)
. = ALIGN(0x1000000);
_local_cached_prc62_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc63_bss_start = .;
    *(.local_cached_prc63.bss)
    *(.local_cached_prc63.stack)
. = ALIGN(0x1000000);
_local_cached_prc63_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc64_bss_start = .;
    *(.local_cached_prc64.bss)
    *(.local_cached_prc64.stack)
. = ALIGN(0x1000000);
_local_cached_prc64_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc65_bss_start = .;
    *(.local_cached_prc65.bss)
    *(.local_cached_prc65.stack)
. = ALIGN(0x1000000);
_local_cached_prc65_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc66_bss_start = .;
    *(.local_cached_prc66.bss)
    *(.local_cached_prc66.stack)
. = ALIGN(0x1000000);
_local_cached_prc66_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc67_bss_start = .;
    *(.local_cached_prc67.bss)
    *(.local_cached_prc67.stack)
. = ALIGN(0x1000000);
_local_cached_prc67_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc68_bss_start = .;
    *(.local_cached_prc68.bss)
    *(.local_cached_prc68.stack)
. = ALIGN(0x1000000);
_local_cached_prc68_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc69_bss_start = .;
    *(.local_cached_prc69.bss)
    *(.local_cached_prc69.stack)
. = ALIGN(0x1000000);
_local_cached_prc69_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc70_bss_start = .;
    *(.local_cached_prc70.bss)
    *(.local_cached_prc70.stack)
. = ALIGN(0x1000000);
_local_cached_prc70_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc71_bss_start = .;
    *(.local_cached_prc71.bss)
    *(.local_cached_prc71.stack)
. = ALIGN(0x1000000);
_local_cached_prc71_bss_end = .;
. = ALIGN(0x1000000);
    _local_cached_prc72_bss_start = .;
    *(.local_cached_prc72.bss)
    *(.local_cached_prc72.stack)
. = ALIGN(0x1000000);
_local_cached_prc72_bss_end = .;
/* [[[end]]] */
   . = ALIGN(32 / 8);
    } : data
    __bss_end = .;
     _end = .		;

    PROVIDE (end = .)	;
    .comment 0 : { *(.comment) }

  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to
     the beginning of the section so we begin them at 0.  */

  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }

  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }

  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }

  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }

  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }

  /DISCARD/ : { *(*) }
}
