#
# Makefile for TILE-Gx8036 processor
#

#
# Processor, architecture and toolchain
#
PRC  = tilegx8036
ARCH = tilegx
TOOL = gcc

PRCDIR = $(SRCDIR)/arch/$(ARCH)_$(TOOL)/$(PRC)

#
# Compiler options
#
INCLUDES += -I$(PRCDIR)

#
# Include architecture support package
#
include $(SRCDIR)/arch/$(ARCH)_$(TOOL)/common/Makefile.arch
