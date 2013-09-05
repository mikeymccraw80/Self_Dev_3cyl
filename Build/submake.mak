
###############################################################################
# Define desired directories to place dependancy and assembly files
# Section 1
###############################################################################
LST_DIR		= $(LISTING_DIR)
###############################################################################
# Define targets to build based on known prerequisites
# Section 1.1
###############################################################################
OBJS_C		=$(patsubst %.c,$(OBJ_DIR)/%.o,$(wildcard *.c))
OBJS_ASM        =$(patsubst %.s,$(OBJ_DIR)/%.o,$(wildcard *.s))

###############################################################################
# Build All for this sub project
# Section 2
###############################################################################

###############################################################################
# Create macro containing all known required object files for the subproject
# Section 3
###############################################################################

ALLOBJECTS += $(OBJS_ASM)
ALLOBJECTS += $(OBJS_C)

DEPENDS_FILE  = deps.mak
DEPENDS_TEMP1 = deps1.mak
DEPENDS_TEMP2 = deps2.mak
find_deps = $(wildcard *deps.mak)



OBJECT_LIST = obj_list.txt

###############################################################################
# Build all targets
# Section 4
###############################################################################

.PHONY: all
all: $(ALLOBJECTS) echo_objects


###############################################################################
# Build list of all object files created to be streamed to the linker file
# Section 5
###############################################################################
OBJS_TO_LNK	= $(patsubst %.o,%.tolnk,$(ALLOBJECTS))

.PHONY: $(OBJS_TO_LNK) cleanobjectlist
$(OBJS_TO_LNK): cleanobjectlist
	@$(ECHO) $(subst /,\,$(patsubst %.tolnk,%.o,$@)) >> $(OBJECT_LIST)
	@$(ECHO) $(patsubst %.tolnk,%.o,$(@F)) >> $(BUILD_DIR)/$(OBJECT_LIST)
cleanobjectlist:
	-@$(RM) -f $(OBJECT_LIST) 	

###############################################################################
# echo_objects generate list of objects file to be included in linker file
###############################################################################
.PHONY: echo_objects 
echo_objects: $(OBJS_TO_LNK)

###############################################################################
# Clean up object files
# Section 6
###############################################################################
CLEAN_OBJS	= $(patsubst %.o,%.cleanobj,$(ALLOBJECTS))

.PHONY: $(CLEAN_OBJS)
$(CLEAN_OBJS):
	@$(RM) -f $(subst /,\,$(patsubst %.cleanobj,%.o,$@))

.PHONY: cleanobjs
cleanobjs: $(CLEAN_OBJS)

###############################################################################
# Clean up dependency files
# Section 6.2
###############################################################################
.PHONY: cleandepends cleantempdepends  
cleandepends: cleantempdepends
	-@$(RM) -f $(DEPENDS_FILE) 	
  
cleantempdepends:
	-@$(RM) -f $(DEPENDS_TEMP2)
	-@$(RM) -f $(DEPENDS_TEMP1)


###############################################################################
# Clean up listing directory assemble output files
# Section 6.3
###############################################################################
CLEAN_LST	= $(patsubst $(OBJ_DIR)/%.o,$(LST_DIR)/%.cleanlst,$(OBJS_C))

.PHONY: $(CLEAN_LST)
$(CLEAN_LST):
	$(RM) -f $(subst /,\,$(patsubst %.cleanlst,%.*,$@))

.PHONY: cleanlist
cleanlist: $(CLEAN_LST)

###############################################################################
# Clean up all output files
# Section 6.4
###############################################################################
CLEAN_OBJ	= $(patsubst %.o, %.cleanobj, $(ALLOBJECTS))

.PHONY: clean cleanall 
clean cleanall: cleanobjs cleandepends cleanobjectlist

###############################################################################
# Create dependency file in subproject
# Section 6.5
###############################################################################

OBJS_DEPENDS = $(patsubst %.c,%/subproject.depends,$(wildcard *.c))

.PHONY: depends 
depends: $(OBJS_DEPENDS) cleantempdepends 

.PHONY: $(OBJS_DEPENDS) 
$(OBJS_DEPENDS):  
	@$(ECHO) Creating C dependencies files...
	@$(CC_DEPENDS) $(patsubst %/subproject.depends,%.c,$@) >> $(DEPENDS_TEMP2) 
	$(TYPE) $(DEPENDS_TEMP2) | $(SED) -e "s/\([^ ]\)\\/\1\//g" > $(DEPENDS_TEMP1) 
	$(TYPE) $(DEPENDS_TEMP1) | $(SED) -e "s/\(.*\)\.o[: ]/$$(OBJ_DIR)\/\1.o :/g" > $(DEPENDS_FILE)


###############################################################################
# Implicit Rules
# Section 7
###############################################################################

###############################################################################
# Implicit rule to create an object file in $(OBJ_DIR) directory from 
# a C file in $(CURDIR) directory
# Section 7.1 	@$(ECHO) $(@F)>> $(BUILD_DIR)/$(OBJECT_LIST)
###############################################################################
$(OBJ_DIR)/%.o:$(CURDIR)/%.c
	@$(ECHO) Building $(CURDIR)/$(<F) to $(@F)
	@$(CC) -c -o $@ -c -o $@ -@E+$(BUILD_DIR)/ERROR.err $(subst /,\,$<) 
ifeq ($(find_deps),$(DEPENDS_FILE))
include $(DEPENDS_FILE) 
endif


###############################################################################
# Implicit rule to create an object file in $(OBJ_DIR) directory from 
# assembly file in $(CURDIR) directory
# Section 7.2
###############################################################################

$(OBJ_DIR)/%.o:$(CURDIR)/%.s
	$(ASM) -o $(subst /,\,$@) $(ASM_OPT) -@E+$(BUILD_DIR)/ERROR.err $(subst /,\,$<)


