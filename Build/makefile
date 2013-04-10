
###############################################################################
# Environment Setup
# Section 1
###############################################################################
THISMAK= makefile
COMPILER= dcc
ASSEMBLER= das
DDUMP = ddump
SUBPROJECT_MAK= submake


OUTFILE= test
PROG_NAME = test
LINKFILE= test



export HOME_DIR = $(CURDIR)/..
export BUILD_DIR = $(CURDIR)

TOOLS_DIR    = $(HOME_DIR)/tools/utility
DIABLIBS_DIR    = $(HOME_DIR)/tools/diab/lib
COMPILER_DIR = $(HOME_DIR)/tools/diab/WIN32/bin
COMP_DIR     = $(subst /,\,$(COMPILER_DIR))
TOOLS_PATH   = $(subst /,\,$(TOOLS_DIR))
PROJECT_ROOT = $(HOME_DIR)

VERSION = 1.0
LAST_UPDATE = July 2011

export TOOLS_PATH
export ROOT_DIR = $(PROJECT_ROOT)
export COMP_DIR
export OUT_DIR

###############################################################################
# Setup All Directories
# Section 2
###############################################################################
###############################################################################
# Make Tools
# Section 2.1
###############################################################################

export BASH=\
				$(subst \,/,$(TOOLS_PATH)\bash)

export CAT=\
				$(subst \,/,$(TOOLS_PATH)\cat.exe)

export PERL=\
				$(subst \,/,$(TOOLS_PATH)\perl)


export SED =\
				$(subst /,\,$(TOOLS_PATH)\sed.exe)

export RM=\
				$(subst /,\,$(TOOLS_PATH)\rm.exe)

export RMDIR=\
				$(subst /,\,$(TOOLS_PATH)\rmdir.exe)

export COPY=\
				copy

export MOVE=\
				move

export ECHO=\
				@echo

export TYPE=\
				@type

export DEL= \
				@del

#export SED= \
				@sed


###############################################################################
# where the root begins
# Section 2.2
###############################################################################

###############################################################################
# The intermediate directory for .o and .ls files
# Section 2.3
###############################################################################
export OBJ_DIR       = $(HOME_DIR)/objs

###############################################################################
# .ptp, .i6l, .sym, .695, .out, .map files are placed here.
# Section 2.4
###############################################################################
export OUTPUT_DIR    = $(HOME_DIR)/bin

###############################################################################
# .lx listing files are placed here
# Section 2.5
###############################################################################
export LISTING_DIR  = $(HOME_DIR)/Listing

###############################################################################
# makefile, submake, linker file are placed here
# Section 2.6
###############################################################################
BUILD_DIR = $(HOME_DIR)/Build



###############################################################################
# Include sub-project directories here
# Section 3
###############################################################################
SUBDIRS += LLD/IO_Config
SUBDIRS += LLD/DeviceDriver/SWT
SUBDIRS += LLD/DeviceDriver/FMPLL
SUBDIRS += LLD/DeviceDriver/MMU
SUBDIRS += LLD/DeviceDriver/FLASH
SUBDIRS += LLD/DeviceDriver/INTC
SUBDIRS += LLD/DeviceDriver/PIT
SUBDIRS += LLD/DeviceDriver/SIU
SUBDIRS += LLD/DeviceDriver/XBAR
SUBDIRS += LLD/DeviceDriver/ECSM
SUBDIRS += LLD/DeviceDriver/EDMA
SUBDIRS += LLD/DeviceDriver/QADC
SUBDIRS += LLD/DeviceDriver/MIOS
SUBDIRS += LLD/DeviceDriver/DSPI
SUBDIRS += LLD/DeviceDriver/CAN
SUBDIRS += LLD/DeviceDriver/TPU
SUBDIRS += LLD/VSEP
SUBDIRS += LLD/VSEP/DeviceDriver
SUBDIRS += LLD/VSEP/SPI_Scheduler
SUBDIRS += LLD/VSEP/Interface
SUBDIRS += LLD/VSEP/Configuration
SUBDIRS += LLD/L9958
SUBDIRS += LLD/L9958/DeviceDriver
SUBDIRS += LLD/L9958/Initialization
SUBDIRS += LLD/L9958/Interface
SUBDIRS += LLD/L9958/message_configuration
SUBDIRS += LLD/TPU/MCD5408
SUBDIRS += LLD/TPU/MCD5412
SUBDIRS += LLD/TPU/MCD5417
SUBDIRS += LLD/TPU/MCD5411
SUBDIRS += LLD/TPU/MCD5401
SUBDIRS += LLD/TPU/uCode
SUBDIRS += LLD/Complex_IO/Crank
SUBDIRS += LLD/Complex_IO/Spark
SUBDIRS += LLD/Complex_IO/PFI
SUBDIRS += LLD/Complex_IO/CXIO
SUBDIRS += LLD/Complex_IO/CAM
SUBDIRS += LLD/OS
SUBDIRS += LLD/SOH
SUBDIRS += LLD/HAL
SUBDIRS += LLD/IO_Interface
SUBDIRS += LLD/Type_Incl
SUBDIRS += HLS


###############################################################################
# Directories included for compiling.
# Section 4
###############################################################################

INCDIRS += LLD/IO_Config
INCDIRS += LLD/DeviceDriver/SWT
INCDIRS += LLD/DeviceDriver/FMPLL
INCDIRS += LLD/DeviceDriver/MMU
INCDIRS += LLD/DeviceDriver/FLASH
INCDIRS += LLD/DeviceDriver/INTC
INCDIRS += LLD/DeviceDriver/PIT
INCDIRS += LLD/DeviceDriver/SIU
INCDIRS += LLD/DeviceDriver/XBAR
INCDIRS += LLD/DeviceDriver/ECSM
INCDIRS += LLD/DeviceDriver/EDMA
INCDIRS += LLD/DeviceDriver/QADC
INCDIRS += LLD/DeviceDriver/MIOS
INCDIRS += LLD/DeviceDriver/DSPI
INCDIRS += LLD/DeviceDriver/CAN
INCDIRS += LLD/DeviceDriver/TPU
INCDIRS += LLD/VSEP/Include
INCDIRS += LLD/VSEP/DeviceDriver
INCDIRS += LLD/VSEP/Configuration
INCDIRS += LLD/VSEP/Interface
INCDIRS += LLD/L9958/Include
INCDIRS += LLD/TPU/MCD5408
INCDIRS += LLD/TPU/MCD5412
INCDIRS += LLD/TPU/MCD5417
INCDIRS += LLD/TPU/MCD5411
INCDIRS += LLD/TPU/MCD5401
INCDIRS += LLD/TPU/uCode
INCDIRS += LLD/Complex_IO/Crank
INCDIRS += LLD/Complex_IO/Spark
INCDIRS += LLD/Complex_IO/PFI
INCDIRS += LLD/Complex_IO/CXIO
INCDIRS += LLD/Complex_IO/CAM
INCDIRS += LLD/OS
INCDIRS += LLD/HAL
INCDIRS += LLD/SOH
INCDIRS += LLD/IO_Interface
INCDIRS += LLD/Type_Incl
INCDIRS += HLS

export INCLUDE_DIR += $(patsubst %,-I$(HOME_DIR)/%,$(INCDIRS))
###############################################################################
# Project Build option
# Section 5
###############################################################################

OUT_DIR = $(subst /,\,$(OUTPUT_DIR))

###############################################################################
# Compiler Option
# Section 5.1                       # -Xnested-interrupts\
###############################################################################
PPC_DIAB_TARGET = -tPPCE200Z3VEN:simple

PPC_DIAB_OPTS   =     -g2 -XO\
                      -Xclib-optim-off\
                      -Xstmw-fast\
                      -Xsize-opt\
                      -Xlicense-wait\
                      -Xinline=0\
                      -Xinline-explicit-force\
                      -Xbss-common-off\
                      -Xenum-is-best\
                      -Xpass-source\
                      -Xsmall-data=0\
                      -Xsmall-const=0\
                      -Xsemi-is-comment\
                      -Wa,-l

CDEBUG= -Xpass-source
CX_OUTPUT= -ce$(subst /,\,$(OBJ_DIR)) -co$(subst /,\,$(OBJ_DIR)) -cl$(subst /,\,$(OBJ_DIR))


export CC= $(COMP_DIR)\$(COMPILER) $(PPC_DIAB_OPTS) $(CDEBUG) $(PPC_DIAB_TARGET) $(INCLUDE_DIR) 

###############################################################################
# Compiler option for building dependency file
# Section 5.2
###############################################################################
    DEPENDS_OPTION =    -g2 -XO\
                      -Xclib-optim-off\
                      -Xstmw-fast\
                      -Xsize-opt\
                      -Xlicense-wait\
                      -Xinline=0\
                      -Xinline-explicit-force\
                      -Xbss-common-off\
                      -Xlist-file\
                      -Xenum-is-best\
                      -Xpass-source\
                      -Xsmall-data=0\
                      -Xsmall-const=0\
                      -Xsemi-is-comment\
                      -Wa,-l
                      
export CC_DEPENDS = $(COMPILER) $(INCLUDE_DIR) $(DEPENDS_OPTION)

###############################################################################
# Assembler option
# Section 5.3
###############################################################################
ASMDEBUG=
    export ASM_OPT= -g
export ASM= $(COMP_DIR)\$(ASSEMBLER)

###############################################################################
# Linker option
# Section 5.4
###############################################################################

DIAB_PPC_ELF_FILE = $(OUTPUT_DIR)/$(PROG_NAME).elf

DIAB_PPC_MAPFILE  = $(OUTPUT_DIR)/$(PROG_NAME).map

DIAB_PPC_LINKER_FLAGS +=\
                     -m6
                     
DIAB_PPC_LINKER_LIB	+=\
		     -L$(OBJ_DIR)\
                     -L$(DIABLIBS_DIR)\
                     -lc

DIAB_PPC_LINKER_COMMANDLINE =\
		$(PPC_DIAB_TARGET) \
		$(DIAB_PPC_LINKER_FLAGS)\
      -o$(DIAB_PPC_ELF_FILE)\
		$(DIAB_PPC_LINKER_LIB_FLAGS)\
		$(DIAB_PPC_LINKER_LIB)\
		> $(DIAB_PPC_MAPFILE)
		
LINK= $(COMP_DIR)\dld $(DIAB_PPC_LINKER_COMMANDLINE) $(BUILD_DIR)/obj_list.txt 


###############################################################################
# Command to generate listing file
# Section 5.5
###############################################################################
DDUMP= $(COMP_DIR)\ddump -R -m3 -w16 -v -o $(OUTPUT_DIR)\$(OUTFILE).s19  $(OUTPUT_DIR)\$(OUTFILE).elf


###############################################################################
# Build Targets
# Section 7
###############################################################################

BUILD_TARGET += $(OUTPUT_DIR)/$(OUTFILE).elf
BUILD_TARGET += $(OUTPUT_DIR)/$(OUTFILE).s19


###############################################################################
# Build all targets
# Section 7.1
###############################################################################
.PHONY: all
 all:   display subproject $(BUILD_TARGET)

###############################################################################
# Build Output Directories
# Section 7.2
###############################################################################
###############################################################################
# Make sure we have a output directory
###############################################################################
.PHONY: bldoutputdir
bldoutputdir: $(OUTPUT_DIR)

$(OUTPUT_DIR):
	md $(subst /,\,$(OUTPUT_DIR))

###############################################################################
# Build object file depository directory
# Section 7.3
###############################################################################
SUBOBJDIR = $(HOME_DIR)/objs

.PHONY: bldsubobjdir
bldsubobjdir: $(SUBOBJDIR)

$(SUBOBJDIR):
	md $(subst /,\,$@)

###############################################################################
# Build file listing depository directory
# Section 7.4
###############################################################################
SUBLSTDIR = $(LISTING_DIR)

.PHONY: bldsublstdir
bldsublstdir: $(SUBLSTDIR)

$(SUBLSTDIR):
	md $(subst /,\,$@)

###############################################################################
# Copy master subproject.mak file if it is new than the one in subdirectories
# Section 8
###############################################################################
SUBMAKS = $(patsubst %,$(HOME_DIR)/%/$(SUBPROJECT_MAK).mak,$(SUBDIRS))
MASTERSUBMAK = $(CURDIR)/$(SUBPROJECT_MAK).mak

$(SUBMAKS) : $(MASTERSUBMAK)
	$(ECHO) $(MASTERSUBMAK)
	$(COPY) $(subst /,\,$(MASTERSUBMAK)) $(subst /,\,$(patsubst %/$(SUBPROJECT_MAK).mak,%,$@))

###############################################################################
# Subproject Build Process
# Section 9
###############################################################################

###############################################################################
# 				BUILD SUB PROJECTS
###############################################################################
# Build all source code here
###############################################################################
SUBMAKALLS = $(patsubst %,%/subproject.makall,$(SUBDIRS))

.PHONY: subproject $(SUBMAKALLS)
subproject: $(SUBMAKALLS)

$(SUBMAKALLS): bldsubobjdir bldsublstdir $(SUBMAKS)
	@$(ECHO) Compiling subproject: $(patsubst %/subproject.makall,%,$@)
	@$(MAKE) all -s -C $(patsubst %/subproject.makall,$(HOME_DIR)/%,$@) -f $(SUBPROJECT_MAK).mak

$(BUILD_TARGET): bldoutputdir build_target
.PHONY: build_target1

build_target:	;
###############################################################################
# Linking objects file and generating *.h12 
###############################################################################
	@$(ECHO) Linking...
	@cd ..\objs && $(LINK) $(HOME_DIR)\Build\$(LINKFILE).dld


###############################################################################
# Generating *.ptp
###############################################################################
	@$(ECHO) Generating PTP file
	-@cd ..\bin && $(DDUMP)



###############################################################################
# 				CLEANING PROCESS UTILITY TARGETS
# Section 10
###############################################################################
# Clean subproject mak files here
###############################################################################
CLEANSUBPROJECTMAKS = $(patsubst %,%.cleansubprojectmaks,$(SUBDIRS))

.PHONY: cleansubprojectmaks $(CLEANSUBPROJECTMAKS)
cleansubprojectmaks: $(CLEANSUBPROJECTMAKS)


$(CLEANSUBPROJECTMAKS):
	@$(RM) -f $(subst /,\,$(patsubst %.cleansubprojectmaks,$(HOME_DIR)/%/$(SUBPROJECT_MAK).mak,$@))
	@$(RM) -f $(subst /,\,$(patsubst %.cleansubprojectmaks,$(ROOT_DIR)/%/$(SUBPROJECT_MAK).mak,$@))

###############################################################################
# Clean all files here
###############################################################################
CLEANSUBALL = $(patsubst %,%.cleanall,$(SUBDIRS))

.PHONY: cleanall $(CLEANSUBALL)

cleanall: $(CLEANSUBALL) $(CLEANSUBPROJECTMAKS)
	-@$(RM) -r $(subst /,\,$(OUTPUT_DIR))
	-@$(RM) -r $(subst /,\,$(OBJ_DIR))
	-@$(RM) -r $(subst /,\,$(LISTING_DIR))

$(CLEANSUBALL): $(SUBMAKS)
	$(MAKE) -C $(patsubst %.cleanall,$(HOME_DIR)/%,$@) -f $(SUBPROJECT_MAK).mak cleanall

###############################################################################
# Clean object files here
###############################################################################
CLEANSUBOBJ = $(patsubst %,%.clean,$(SUBDIRS))

.PHONY: clean $(CLEANSUBOBJ)
clean: $(CLEANSUBOBJ)

$(CLEANSUBOBJ): $(SUBMAKS)
	@$(MAKE) -C $(patsubst %.clean,$(HOME_DIR)/%,$@) -f $(SUBPROJECT_MAK).mak cleanobjs

###############################################################################
# Clean dependency files here
###############################################################################
CLEANSUBDEPENDS = $(patsubst %,%.cleandepends,$(SUBDIRS))

.PHONY: cleandepends $(CLEANSUBDEPENDS)
cleandepends: $(CLEANSUBDEPENDS)

$(CLEANSUBDEPENDS): $(SUBMAKS)
#@$(MAKE) -C $(patsubst %.cleandepends,$(HOME_DIR)/%,$@) -f $(SUBPROJECT_MAK).mak cleandepends

###############################################################################
# Remove object list file
###############################################################################
CLEANOBJLIST = $(patsubst %,%.cleanobjectlist,$(SUBDIRS))

.PHONY: cleanobjectlist $(CLEANOBJLIST)
cleanobjectlist: $(CLEANOBJLIST)

$(CLEANOBJLIST): $(SUBMAKS)
	@$(MAKE) -C $(patsubst %.cleanobjectlist,$(HOME_DIR)/%,$@) -f $(SUBPROJECT_MAK).mak cleanobjectlist

###############################################################################
# Build dependency files here
###############################################################################

SUBMAKDEPS = $(patsubst %,%.builddepends,$(SUBDIRS))

.PHONY: builddepends
$(SUBMAKDEPS): $(SUBMAKS)
	@$(MAKE) depends -C $(patsubst %.builddepends,$(HOME_DIR)/%,$@) -f $(SUBPROJECT_MAK).mak


display:
	@$(ECHO) Compile for test software version: $(VERSION) date: $(LAST_UPDATE)
	
