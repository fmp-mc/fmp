#
#  @(#) $Id: Makefile.prc 512 2010-02-01 05:33:27Z ertl-honda $
# 

#
#		Makefile �Υץ��å���¸����SH4A�ѡ�
#

#
#  ����ѥ��륪�ץ����
#
COPTS := $(COPTS)
LDFLAGS := -nostdlib $(LDFLAGS) 
CDEFS := $(CDEFS) -DTOPPERS_LABEL_ASM
LIBS := $(LIBS)  -lgcc -lgcc-Os-4-200

#
#  �ץ��å��μ���˱���������ѥ��륪�ץ����
#
ifeq ($(PRC_ARCH), SH4A)
	ifeq ($(FPU_ENABLE),TRUE)
		ifeq ($(FPU_MODE),SINGLE)
			COPTS := $(COPTS) -m4a-single
		else
		ifeq ($(FPU_MODE),SINGLE_ONLY)
			COPTS := $(COPTS) -m4a-single-only
		else
		ifeq ($(FPU_MODE),DOUBLE)
			COPTS := $(COPTS) -m4a
		endif
		endif
		endif
	else
		COPTS := $(COPTS) -m4a-nofpu
	endif
endif

#
#  FPU����Ѥ�����
#
ifeq ($(FPU_ENABLE),TRUE)
CDEFS := $(CDEFS) -DFPU_ENABLE
endif

ifeq ($(FPU_MODE),SINGLE)
CDEFS := $(CDEFS) -DFPU_SINGLE
endif

ifeq ($(FPU_MODE),SINGLE_ONLY)
CDEFS := $(CDEFS) -DFPU_SINGLE_ONLY
endif

ifeq ($(FPU_MODE),DOUBLE)
CDEFS := $(CDEFS) -DFPU_DOUBLE
endif

#
#  �����ͥ�˴ؤ������
#
KERNEL_DIR := $(KERNEL_DIR) $(SRCDIR)/arch/$(PRC)_$(TOOL)
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS) prc_support.o
KERNEL_COBJS := $(KERNEL_COBJS) prc_config.o prc_timer.o
