APPL_COBJS +=

APPL_CXXOBJS +=

APPL_LIBS += $(APPLDIR)/swaptions.a

SRCLANG := c++

COPTS +=

ifdef CONFIG_EV3RT_APPLICATION

APPL_LIBS += -Wl,--start-group

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/parsec-helper/Makefile
include $(EV3RT_SDK_LIB_DIR)/posix/Makefile
include $(EV3RT_SDK_LIB_DIR)/ramfs/Makefile
include $(EV3RT_SDK_LIB_DIR)/newlib/Makefile

APPL_LIBS += -Wl,--end-group

endif

REAL_PWD := $(dir $(lastword $(MAKEFILE_LIST)))
