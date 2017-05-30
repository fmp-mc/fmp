THIS_LIB_NAME := hoard-wrapper
THIS_LIB_OBJS := allocator.o
THIS_LIB_CXXOBJS := 
CFLAGS += -DMALLOC_USE_HOARD

include $(EV3RT_SDK_LIB_DIR)/../Makefile.slib

APPL_LIBS := $(APPL_LIBS) $(CURRENT_DIR)/libhoard.a
#APPL_LIBS := $(APPL_LIBS) $(CURRENT_DIR)/libhoard-mod-constants.a
