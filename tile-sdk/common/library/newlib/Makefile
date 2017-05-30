THIS_LIB_NAME := newlib
THIS_LIB_OBJS := syscall.o
THIS_LIB_CXXOBJS := cxxrt.o

CFLAGS += -D__DYNAMIC_REENT__
CFLAGS += -D__toppers__ # enable POSIX thread support in Newlib

#USE_GLIBC_LIBM = 1
#USE_OPEN_LIBM = 1

include $(EV3RT_SDK_LIB_DIR)/../Makefile.slib

INCLUDES := -I$(CURRENT_DIR)/newlib-1.13.0/newlib/libc/include -I$(CURRENT_DIR)/newlib-1.13.0/build/obj/targ-include $(INCLUDES)
INCLUDES += -I$(TILERA_ROOT)/lib/gcc/tilegx-redhat-linux/include/c++/4.4.7 -I$(TILERA_ROOT)/lib/gcc/tilegx-redhat-linux/include/c++/4.4.7/tilegx-redhat-linux
#I$(TILERA_ROOT)/tile/usr/lib/newlib/usr/include
# /home/liyixiao/manycore/fmp-tilegx/uClibc++/src/libuClibc++.a 
#APPL_LIBS := $(APPL_LIBS) -Wl,--start-group $(CURRENT_DIR)/newlib-1.13.0/build/obj/libm/libm.a $(CURRENT_DIR)/newlib-1.13.0/build/obj/libc/libc.a -Wl,--end-group $(THIS_LIB_ARC_FILE)

APPL_LIBS := $(APPL_LIBS) $(CURRENT_DIR)/newlib-libc.a

ifdef USE_GLIBC_LIBM
CFLAGS += -DUSE_GLIBC_LIBM
APPL_LIBS := $(APPL_LIBS) $(CURRENT_DIR)/glibc-2.12-libm.a
else

ifdef USE_OPEN_LIBM
CFLAGS += -DUSE_OPEN_LIBM
APPL_LIBS := $(APPL_LIBS) $(CURRENT_DIR)/libopenlibm.a
else
APPL_LIBS := $(APPL_LIBS) $(CURRENT_DIR)/newlib-libm.a
endif

endif

# glibc libm
#APPL_LIBS := $(APPL_LIBS) -Wl,--start-group $(TILERA_ROOT)/tile/usr/lib/libm.a $(CURRENT_DIR)/newlib-1.13.0/build/obj/libc/libc.a -Wl,--end-group $(THIS_LIB_ARC_FILE)

# fdlibm
#APPL_LIBS := $(APPL_LIBS) /home/liyixiao/manycore/fdlibm/libm.a $(CURRENT_DIR)/newlib-1.13.0/build/obj/libm/libm.a $(CURRENT_DIR)/newlib-1.13.0/build/obj/libc/libc.a $(THIS_LIB_ARC_FILE)
