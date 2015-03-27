
###############################################################################
# Environment Setup
# Section 1
###############################################################################
THISMAK= makefile
COMPILER= dcc
ASSEMBLER= das
DDUMP = ddump
SUBPROJECT_MAK= submake
PTP = ptp


OUTFILE= mt22p3_chery_4cyl
PROG_NAME = mt22p3_chery_4cyl
CHERY_HLS_LIB_NAME = chery_hls_lib
DELPHI_HWIO_LIB_NAME = mt22p3_chery_4cyl
ifeq ($(TARGET),HWIO)
LINKFILE= mt22p3_chery_4cyl
else
LINKFILE= mt22p3_chery_4cyl
endif



export HOME_DIR = $(CURDIR)/..
export BUILD_DIR = $(CURDIR)

TOOLS_DIR    = $(HOME_DIR)/tools/utility
DIABLIBS_DIR    = $(HOME_DIR)/tools/diab/lib
COMPILER_DIR = $(HOME_DIR)/tools/diab/WIN32/bin
COMP_DIR     = $(subst /,\,$(COMPILER_DIR))
TOOLS_PATH   = $(subst /,\,$(TOOLS_DIR))
PROJECT_ROOT = $(HOME_DIR)
# ifeq ($(TARGET), INTEGRATION)
CHERY_LIB_DIR = $(HOME_DIR)/tools/cherylib
# else
DELPHI_LIB_DIR = $(HOME_DIR)/tools/delphilib/outputlib
# endif

VERSION = 1.1
LAST_UPDATE = April 2013

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

export MAP2SYM=\
				$(subst \,/,$(TOOLS_PATH)\MAP2SYM.exe)

export PERL=\
				$(subst \,/,$(TOOLS_PATH)\perl5.6.1)


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
ifeq ($(TARGET),HWIO_Test)
INSTRUMT_DIR = $(HOME_DIR)/Function_test/Instrumentation
else
ifeq ($(TARGET),HWIO_HLS_INTEGRATION_TEST)
INSTRUMT_DIR = $(HOME_DIR)/Function_test/Instrumentation
else
INSTRUMT_DIR = $(HOME_DIR)/Instrumentation
endif
endif

###############################################################################
# Include sub-project directories here
# Section 3
###############################################################################
ifneq ($(TARGET),HWIO_HLS_INTEGRATION)
ifneq ($(TARGET),HWIO_HLS_INTEGRATION_TEST)
ifneq ($(TARGET),HWIO_LIB)
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
SUBDIRS += LLD/DeviceDriver/STM
SUBDIRS += LLD/DeviceDriver/DFILTER
SUBDIRS += LLD/DeviceDriver/SCI
SUBDIRS += LLD/VSEP
SUBDIRS += LLD/VSEP/DeviceDriver
SUBDIRS += LLD/VSEP/SPI_Scheduler
SUBDIRS += LLD/VSEP/Interface
SUBDIRS += LLD/VSEP/Configuration
SUBDIRS += LLD/L9958
SUBDIRS += LLD/TLE4471
SUBDIRS += LLD/TPU/MCD5408
SUBDIRS += LLD/TPU/MCD5412
SUBDIRS += LLD/TPU/MCD5417
SUBDIRS += LLD/TPU/MCD5411
SUBDIRS += LLD/TPU/MCD5401
SUBDIRS += LLD/TPU/MCD5402
SUBDIRS += LLD/TPU/MCD5406
SUBDIRS += LLD/TPU/uCode
SUBDIRS += LLD/Complex_IO/Crank
SUBDIRS += LLD/Complex_IO/Spark
SUBDIRS += LLD/Complex_IO/PFI
SUBDIRS += LLD/Complex_IO/CXIO
SUBDIRS += LLD/Complex_IO/CAM
SUBDIRS += LLD/Complex_IO/IGN
SUBDIRS += LLD/Complex_IO/KNOCK
SUBDIRS += LLD/Complex_IO/Power
SUBDIRS += LLD/Complex_IO/ID_Cald
SUBDIRS += LLD/OS
SUBDIRS += LLD/SOH
SUBDIRS += LLD/Inst
SUBDIRS += LLD/EEPROM
SUBDIRS += LLD/Communications/CCP
SUBDIRS += LLD/Communications/OBD/KW2OBD/KWTRANSP
SUBDIRS += LLD/Communications/OBD/KW2OBD/KW2KSERV
SUBDIRS += LLD/Communications/OBD/OBDLIB
SUBDIRS += LLD/Communications/OBD/CANOBD/DCANSERV
SUBDIRS += LLD/Communications/OBD/CANOBD/DGTRANSP
SUBDIRS += LLD/Communications/OBD/CANIO
SUBDIRS += LLD/HAL
SUBDIRS += LLD/IO_Interface
SUBDIRS += LLD/Type_Incl
SUBDIRS += LLD/HWDiag/Common
SUBDIRS += LLD/HWDiag/EMSD
SUBDIRS += LLD/HWDiag/INJD
SUBDIRS += LLD/HWDiag/ESTD
SUBDIRS += LLD/HWDiag/EOSD
SUBDIRS += LLD/HWDiag/PRGD
SUBDIRS += LLD/HWDiag/VVTD
SUBDIRS += LLD/HWDiag/ETCD
SUBDIRS += LLD/HWDiag/EPSD
SUBDIRS += LLD/HWDiag/COND
SUBDIRS += LLD/HWDiag/CAND
SUBDIRS += LLD/HWDiag/KNOD
SUBDIRS += knock
SUBDIRS += LLD/EMS
SUBDIRS += LLD/Immo
SUBDIRS += LLD/File

SUBDIRS += Testability/MCAMOS
SUBDIRS += Testability/Testability_Application
SUBDIRS += Testability/Testability_HAL
SUBDIRS += Testability/Testability_OS
endif

ifneq ($(TARGET),INTEGRATION)

ifneq ($(TARGET),HWIO_Test)
SUBDIRS += HLS
else
SUBDIRS += Function_test/HLS
endif

endif


endif
endif


###############################################################################
# Directories included for compiling.
# Section 4
###############################################################################
ifneq ($(TARGET),HWIO_HLS_INTEGRATION)
ifneq ($(TARGET),HWIO_HLS_INTEGRATION_TEST)
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
INCDIRS += LLD/DeviceDriver/STM
INCDIRS += LLD/DeviceDriver/DFILTER
INCDIRS += LLD/DeviceDriver/SCI
INCDIRS += LLD/DeviceDriver/KP254/10.DeviceDriver
INCDIRS += LLD/VSEP/SPI_Scheduler
INCDIRS += LLD/VSEP/DeviceDriver
INCDIRS += LLD/VSEP/Configuration
INCDIRS += LLD/VSEP/Interface
INCDIRS += LLD/L9958
INCDIRS += LLD/TLE4471
INCDIRS += LLD/TPU/MCD5408
INCDIRS += LLD/TPU/MCD5412
INCDIRS += LLD/TPU/MCD5417
INCDIRS += LLD/TPU/MCD5411
INCDIRS += LLD/TPU/MCD5401
INCDIRS += LLD/TPU/MCD5402
INCDIRS += LLD/TPU/MCD5406
INCDIRS += LLD/TPU/uCode
INCDIRS += LLD/Complex_IO/Crank
INCDIRS += LLD/Complex_IO/Spark
INCDIRS += LLD/Complex_IO/PFI
INCDIRS += LLD/Complex_IO/CXIO
INCDIRS += LLD/Complex_IO/CAM
INCDIRS += LLD/Complex_IO/IGN
INCDIRS += LLD/Complex_IO/KNOCK
INCDIRS += LLD/Complex_IO/Power
INCDIRS += LLD/Complex_IO/ID_Cald
INCDIRS += LLD/OS
INCDIRS += LLD/HAL
INCDIRS += LLD/SOH
INCDIRS += LLD/Inst
INCDIRS += LLD/EEPROM
INCDIRS += LLD/Communications/CCP
INCDIRS += LLD/Communications/OBD/KW2OBD/KWTRANSP
INCDIRS += LLD/Communications/OBD/KW2OBD/KW2KSERV
INCDIRS += LLD/Communications/OBD/Interface
INCDIRS += LLD/Communications/OBD/OBDLIB
INCDIRS += LLD/Communications/OBD/CANOBD/DCANSERV
INCDIRS += LLD/Communications/OBD/CANOBD/DGTRANSP
INCDIRS += LLD/Communications/OBD/CANIO
INCDIRS += LLD/IO_Interface
INCDIRS += LLD/Type_Incl
INCDIRS += LLD/HWDiag/Common
INCDIRS += LLD/HWDiag/EMSD
INCDIRS += LLD/HWDiag/INJD
INCDIRS += LLD/HWDiag/ESTD
INCDIRS += LLD/HWDiag/EOSD
INCDIRS += LLD/HWDiag/PRGD
INCDIRS += LLD/HWDiag/VVTD
INCDIRS += LLD/HWDiag/ETCD
INCDIRS += LLD/HWDiag/EPSD
INCDIRS += LLD/HWDiag/COND
INCDIRS += LLD/HWDiag/CAND
INCDIRS += LLD/HWDiag/KNOD
INCDIRS += LLD/EMS
INCDIRS += LLD/LUX_Library
INCDIRS += knock
INCDIRS += LLD/Immo
INCDIRS += LLD/File

INCDIRS += Testability/MCAMOS
INCDIRS += Testability/Testability_Application
INCDIRS += Testability/Testability_HAL
INCDIRS += Testability/Testability_OS
# ifneq ($(TARGET),INTEGRATION)
ifneq ($(TARGET),HWIO_Test)
INCDIRS += HLS
else
INCDIRS += Function_test/HLS
endif
# endif

endif
endif

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
                      -ei1025\
                      -ei1241\
                      -ei1583\
                      -ei1789\
                      -Xclib-optim-off\
                      -Xstmw-fast\
                      -Xsize-opt\
                      -Xlicense-wait\
                      -Xinline=0\
                      -Xnested-interrupts\
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

ifeq ($(ETCSOH),ENABLE)
    PPC_DIAB_OPTS += -DENABLE_ETC_SOH_MODULE
endif

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
                      -Xnested-interrupts\
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
    export ASM_OPT= -g $(PPC_DIAB_TARGET)
export ASM= $(COMP_DIR)\$(ASSEMBLER)

###############################################################################
# Linker option
# Section 5.4
###############################################################################

DIAB_PPC_ELF_FILE = $(OUTPUT_DIR)/$(PROG_NAME).elf

DIAB_PPC_MAPFILE  = $(OUTPUT_DIR)/$(PROG_NAME).map

DIAB_PPC_LINKER_FLAGS +=\
                     -m6
ifeq ($(TARGET),HWIO)
DIAB_PPC_LINKER_LIB +=\
                     -L$(OBJ_DIR)\
                     -L$(DIABLIBS_DIR)\
                     -lc
endif
ifeq ($(TARGET),HWIO_Test)
DIAB_PPC_LINKER_LIB +=\
                     -L$(OBJ_DIR)\
                     -L$(DIABLIBS_DIR)\
                     -lc
endif
ifeq ($(TARGET),HWIO_LIB)
DIAB_PPC_LINKER_LIB +=\
                     -L$(OBJ_DIR)\
                     -L$(DIABLIBS_DIR)\
                     -lc\
                     -A $(DELPHI_LIB_DIR)/$(PROG_NAME).a
endif
ifeq ($(TARGET),INTEGRATION)
DIAB_PPC_LINKER_LIB +=\
                     -L$(OBJ_DIR)\
                     -L$(DIABLIBS_DIR)\
                     -lc\
                     -A $(CHERY_LIB_DIR)/$(CHERY_HLS_LIB_NAME).a
endif
ifeq ($(TARGET),HWIO_HLS_INTEGRATION)
DIAB_PPC_LINKER_LIB +=\
                     -L$(DIABLIBS_DIR)\
                     -lc\
                     -A $(DELPHI_LIB_DIR)/$(DELPHI_HWIO_LIB_NAME).a\
                     -A $(CHERY_LIB_DIR)/$(CHERY_HLS_LIB_NAME).a
endif
ifeq ($(TARGET),HWIO_HLS_INTEGRATION_TEST)
DIAB_PPC_LINKER_LIB +=\
                     -L$(DIABLIBS_DIR)\
                     -lc\
                     -A $(DELPHI_LIB_DIR)/$(DELPHI_HWIO_LIB_NAME).a\
                     -A $(CHERY_LIB_DIR)/$(CHERY_HLS_LIB_NAME).a
endif
DIAB_PPC_LINKER_COMMANDLINE =\
		$(PPC_DIAB_TARGET) \
		$(DIAB_PPC_LINKER_FLAGS)\
      -o$(DIAB_PPC_ELF_FILE)\
		$(DIAB_PPC_LINKER_LIB_FLAGS)\
		$(DIAB_PPC_LINKER_LIB)\
		> $(DIAB_PPC_MAPFILE)

ifeq ($(TARGET),HWIO_HLS_INTEGRATION)
LINK = $(COMP_DIR)\dld $(DIAB_PPC_LINKER_COMMANDLINE)
else
ifeq ($(TARGET),HWIO_HLS_INTEGRATION_TEST)
LINK = $(COMP_DIR)\dld $(DIAB_PPC_LINKER_COMMANDLINE)
else
LINK = $(COMP_DIR)\dld $(DIAB_PPC_LINKER_COMMANDLINE) $(BUILD_DIR)/obj_list.txt 
endif
endif

ifeq ($(TARGET),HWIO_HLS_INTEGRATION)
LINK_COMMAND = $(LINK) $(HOME_DIR)/Build/$(LINKFILE).dld
else
ifeq ($(TARGET),HWIO_Test)
LINK_COMMAND = cd ../objs && $(LINK) $(HOME_DIR)/Function_test/$(LINKFILE).dld
else
ifeq ($(TARGET),HWIO_HLS_INTEGRATION_TEST)
LINK_COMMAND = $(LINK) $(HOME_DIR)/Function_test/$(LINKFILE).dld
else
LINK_COMMAND = cd ../objs && $(LINK) $(HOME_DIR)/Build/$(LINKFILE).dld
endif
endif
endif

###############################################################################
# Command to generate listing file
# Section 5.5
###############################################################################
DDUMP = $(COMP_DIR)\ddump -R -m3 -w16 -v -o $(OUTPUT_DIR)\$(OUTFILE).s19  $(OUTPUT_DIR)\$(OUTFILE).elf
PTP_FILL  = $(subst /,\,$(TOOLS_DIR))\$(PTP) cut -fill_byte=00 -InputType=s19 -replace -output=$(subst /,\,$(OUTPUT_DIR))\$(OUTFILE).s19 $(subst /,\,$(OUTPUT_DIR))\$(OUTFILE).s19 00020000:0003ffff,00020000 00040000:0017ffff,00040000
PTP_CONV  = $(subst /,\,$(TOOLS_DIR))\$(PTP) convert -ValuesPerLine=16 -InputType=s19 -replace -recordtype=3 -output= $(subst /,\,$(OUTPUT_DIR))\$(OUTFILE).s19  $(subst /,\,$(OUTPUT_DIR))\$(OUTFILE).s19
PTP_CKSUM = $(subst /,\,$(TOOLS_DIR))\tool_cksum $(subst /,\,$(OUTPUT_DIR))\$(OUTFILE).s19 $(subst /,\,$(OUTPUT_DIR))\$(OUTFILE).s19 kksum

###############################################################################
# Command to generate i6l file
# Section 5.9
###############################################################################
I695 = $(TOOLS_PATH)\i695x.exe
ANCILLARY_TEMPLATES = $(subst /,\,$(INSTRUMT_DIR)/anc_files/V10)
EANCILLARY_FILES  = $(subst /,\,$(OUTPUT_DIR)/$(PROG_NAME).anc)



export I6L_FLAGS=\
            -expl\
            -nomisc \
            -nt\
            -ds2u\
            -noancval\
            -movanon \
            -noqualif\
            -local\
            -ku\
            -exit0\
            -dev\
            -textsec .vector_table .calibration .app_sec .bss\
            -elfdwarf20\
            -relaxed1\
            -D FORCE_MSB_FIRST_DAQ_PROCESSING=1\
            -anc $(ANCILLARY_TEMPLATES)\
            -eanc $(EANCILLARY_FILES)\
            -s\
            $(subst /,\,$(OUTPUT_DIR)/$(OUTFILE).elf)



I6LGEN = $(TOOLS_PATH)/i6lgen
I6L_DEPENDS += $(OUTPUT_DIR)\$(OUTFILE).anc
I6L= $(I6LGEN) -c $(OUTPUT_DIR)\$(PROG_NAME).cmd 


export ASAP2_FILE =\
				$(I695)\
				ASAP2\
				-UNITS\
				-NOMOD\
				-ETAS\
				-OUTPUT_FILE="$(subst \,/,$(OUTPUT_DIR)\$(PROG_NAME)_org.a2l)"\
				"$(subst \,/,$(OUTPUT_DIR)\$(OUTFILE).i6l)"

export CORR_ETC_ARRAYS_ASAP2_FILE =\
				"$(BASH)"\
				-c\
				"$(PERL) $(subst \,/,$(INSTRUMT_DIR)\perl_scripts\a2l_hand_edit.pl)\
				$(subst \,/,$(OUTPUT_DIR)\$(PROG_NAME)_org.a2l)\
				> $(subst \,/,$(OUTPUT_DIR)\mod_$(PROG_NAME).a2l)"

export CORR_ASAP2_FILE =\
				"$(BASH)"\
				-c\
				"$(PERL) $(subst \,/,$(INSTRUMT_DIR)\perl_scripts\a2lcorr.pl)\
				$(subst \,/,$(OUTPUT_DIR)\$(PROG_NAME)_org.a2l)\
				$(subst \,/,$(INSTRUMT_DIR)\perl_scripts\patch.a2l)\
				0xFDFF \
				> $(subst \,/,$(OUTPUT_DIR)\Engine.$(PROG_NAME).a2l)"

export CONCAT_ANC_FILE =\
				"$(BASH)"\
				-c\
				"$(CAT) $(subst \,/,$(INSTRUMT_DIR)\anc_files\chery_hwio*.anc)\
				> $(subst \,/,$(OUTPUT_DIR)\pre.$(PROG_NAME).anc)"

export ANC_FILE =\
				"$(BASH)"\
				-c\
				"$(PERL) $(subst \,/,$(INSTRUMT_DIR)\perl_scripts\ancupdate.pl)\
				$(subst \,/,$(OUTPUT_DIR)\$(OUTFILE).exmap)\
				$(subst \,/,$(OUTPUT_DIR)\pre.$(PROG_NAME).anc)\
				> $(subst \,/,$(OUTPUT_DIR)\$(PROG_NAME).anc)"

ifeq ($(TARGET),HWIO_Test)
export I6L_CMD_PREPROCESSOR_FILE ?=\
            $(subst /,\,$(HOME_DIR)/Function_test/$(PROG_NAME).cmd)
else
export I6L_CMD_PREPROCESSOR_FILE ?=\
            $(subst /,\,$(HOME_DIR)/build/$(PROG_NAME).cmd)
endif
            	
export	EXMAP_FILE =\
   $(MAP2SYM) $(OUTPUT_DIR)/$(PROG_NAME).map $(OUTPUT_DIR)/$(PROG_NAME).exmap 40000000 400177FF

export	SECTION_FILE =\
   $(COMP_DIR)\ddump -h $(OUTPUT_DIR)/$(OUTFILE).elf >>  $(OUTPUT_DIR)/$(PROG_NAME).map




###############################################################################
# Build Targets
# Section 7
###############################################################################

BUILD_TARGET += $(OUTPUT_DIR)/$(OUTFILE).elf
BUILD_TARGET += $(OUTPUT_DIR)/$(OUTFILE).s19
BUILD_TARGET += $(OUTPUT_DIR)/$(OUTFILE).i6l


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
	@$(LINK_COMMAND)

###############################################################################
# Generating *.ptp
###############################################################################
	@$(ECHO) Generating PTP file, And do necessary adjustment
	@cd ..\bin && $(DDUMP) && $(PTP_FILL) && $(PTP_CONV) && $(PTP_CKSUM)
ifneq ($(TARGET),HWIO_HLS_INTEGRATION)
ifneq ($(TARGET),HWIO_HLS_INTEGRATION_TEST)
	@cd ..\objs && @if exist *.lst $(COPY) *.lst	$(subst /,\,$(LISTING_DIR))\. >nul
	@cd ..\objs && @if exist *.lst $(DEL) *.lst
endif
endif
###############################################################################
# Build EXMAP file from elf file target
###############################################################################
	@$(ECHO) Generating XMAP Output
	-@$(EXMAP_FILE)

###############################################################################
# Add Section Summary Info to the end of map file
###############################################################################
	@$(ECHO) Generating Section Info Output
	-@$(SECTION_FILE)

###############################################################################
# Build ANC file from EXMAP file target
###############################################################################
	@if not exist $(subst \,/,$(TOOLS_PATH)\cygintl-1.dll) copy $(TOOLS_PATH)\cygintl_1.dll $(TOOLS_PATH)\cygintl-1.dll
	-@$(CONCAT_ANC_FILE)
	-@$(ANC_FILE)

###############################################################################
# Generating *.i6l
###############################################################################
	@$(ECHO) Generating I6L Output
	@$(ECHO) $(I6L_FLAGS) > $(subst /,\,$(OUTPUT_DIR)/$(PROG_NAME).cmd)
	$(TYPE) $(I6L_CMD_PREPROCESSOR_FILE) >> $(subst /,\,$(OUTPUT_DIR)/$(PROG_NAME).cmd)
	-@cd ..\bin && $(I6L)


###############################################################################
# Build A2L from I6L file target
###############################################################################
	@$(ECHO) Generating A2L Output
	-@cd ..\bin && $(ASAP2_FILE)
#	-@$(CORR_ETC_ARRAYS_ASAP2_FILE)
	-@$(CORR_ASAP2_FILE)

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
	@$(ECHO) Compile for mt22p3_chery_4cyl software version: $(VERSION) date: $(LAST_UPDATE)
	
