APPL_COBJS +=

APPL_CXXOBJS +=

APPL_LIBS += $(APPLDIR)/dedup.a $(APPLDIR)/libz.a
CFLAGS += -DBUILD_PARSEC_DEDUP

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/parsec-helper/Makefile
include $(EV3RT_SDK_LIB_DIR)/posix/Makefile
include $(EV3RT_SDK_LIB_DIR)/ramfs/Makefile
include $(EV3RT_SDK_LIB_DIR)/newlib/Makefile

endif

REAL_PWD := $(dir $(lastword $(MAKEFILE_LIST)))

