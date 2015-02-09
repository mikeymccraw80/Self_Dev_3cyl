###############################################################################
# Define HWIO pathname
###############################################################################
TESTABILITY_DIR ?= $(ROSTER_NUMBER)_Testability

###############################################################################
# Testability
###############################################################################
SUBDIRS += $(TESTABILITY_DIR)
SUBDIRS += $(TESTABILITY_DIR)/MCAMOS
SUBDIRS += $(TESTABILITY_DIR)/Testability_Application
SUBDIRS += $(TESTABILITY_DIR)/Testability_HAL
SUBDIRS += $(TESTABILITY_DIR)/Testability_OS

###############################################################################
# END CTC HWIO
###############################################################################

###############################################################################
# Setup the make files which are included in the build
###############################################################################
MAKFILE_DEPENDS += $(HOME_DIR)/$(TESTABILITY_DIR)/06.Build/$(PROG_ROSTER)_Testability.mak
