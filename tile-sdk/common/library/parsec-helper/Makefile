THIS_LIB_NAME := parsec-helper
THIS_LIB_OBJS := parsec-helper.o
THIS_LIB_CXXOBJS := 

include $(EV3RT_SDK_LIB_DIR)/../Makefile.slib

# TODO: this is a workaround to import 'main' symbol from PARSEC app
APPL_LIBS := $(THIS_LIB_ARC_FILE) $(APPL_LIBS)

#
# Common libraries for PARSEC applications
#
include $(ARCHDIR)/pass0.makefile

