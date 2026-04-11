# ##############################################################
# Automatically-generated file. Do not edit!
# Generated from C:\Users\rebec\eclipse-workspace\tamagotchi-model\Tamagotchi\defaultTC.tcjs
0_TCONFIG_NAME = defaultTC

0_CC = $(CC)
0_CCFLAGS =
0_INCPATHS = \
	$(INCLUDE_TAG)..

0_MK_DIR = .
0_IN_MK_DIR = @$(IN) $(0_MK_DIR)

0_LD = $(LD)
0_LDFLAGS =
0_LIBS = 
0_LIBS_DEPS = 
0_USER_LIBS = 
0_USER_OBJS = 
0_USER_OBJS_LIST = $(0_USER_OBJS)

0_OBJS = \
	Feed$(OBJ_EXT)\
	FeedProt$(OBJ_EXT)\
	InputLoop$(OBJ_EXT)\
	InputProt$(OBJ_EXT)\
	StatusProt$(OBJ_EXT)\
	TranslateInput$(OBJ_EXT)\
	UnitName$(OBJ_EXT)\
	Update$(OBJ_EXT)\
	UpdateValProt$(OBJ_EXT)
0_OBJS_LIST = $(0_OBJS)
0_OBJS_LISTFILE = .olist
0_DEPFILES = \
	Feed$(DEP_EXT)\
	FeedProt$(DEP_EXT)\
	InputLoop$(DEP_EXT)\
	InputProt$(DEP_EXT)\
	StatusProt$(DEP_EXT)\
	TranslateInput$(DEP_EXT)\
	UnitName$(DEP_EXT)\
	Update$(DEP_EXT)\
	UpdateValProt$(DEP_EXT)

-include $(0_DEPFILES)

PURECOV = purecov $(PURECOV_OPTIONS)
PURECOV_OPTIONS = "-log-file=$(PURECOV_TARGET).txt" -windows=no
PURECOV_TARGET = PureCov_executable$(EXEC_EXT)

PURIFY = purify $(PURIFY_OPTIONS)
PURIFY_OPTIONS = "-log-file=$(PURIFY_TARGET).txt" -windows=no
PURIFY_TARGET = Purify_executable$(EXEC_EXT)

PURIFY_COV = purify $(PURIFY_OPTIONS) purecov $(PURECOV_OPTIONS)
PURIFY_COV_TARGET = PurifyCov_executable$(EXEC_EXT)

QUANTIFY = quantify $(QUANTIFY_OPTIONS)
QUANTIFY_OPTIONS = "-log-file=$(QUANTIFY_TARGET).txt" -filename-prefix=%v -windows=no
QUANTIFY_TARGET = Quantify_executable$(EXEC_EXT)

local_build : executable$(EXEC_EXT)

local_compile : $(0_OBJS)

RTpurecov : $(PURECOV_TARGET)

RTpurify : $(PURIFY_TARGET)

RTpurify_cov : $(PURIFY_COV_TARGET)

RTquantify : $(QUANTIFY_TARGET)

executable$(EXEC_EXT) : $(0_OBJS) $(0_USER_OBJS) $(0_LIBS_DEPS) $(0_OBJS_LISTFILE) .ld.dat
	@$(FEEDBACK) Linking Tamagotchi_target:$@
	$(0_LD) $(LD_HEAD) $(0_LDFLAGS) $(0_OBJS_LIST) $(0_USER_OBJS_LIST) $(0_LIBS) $(0_USER_LIBS) $(LD_TAIL)
	@$(FEEDBACK) Finished building $@

$(PURECOV_TARGET) : $(0_OBJS) $(0_USER_OBJS) $(0_LIBS_DEPS) $(0_OBJS_LISTFILE) .ld.dat
	@$(FEEDBACK) Linking Tamagotchi_target:$@
	$(PURECOV) $(0_LD) $(LD_HEAD) $(0_LDFLAGS) $(0_OBJS_LIST) $(0_USER_OBJS_LIST) $(0_LIBS) $(0_USER_LIBS) $(LD_TAIL)
	@$(FEEDBACK) Finished building $@

$(PURIFY_TARGET) : $(0_OBJS) $(0_USER_OBJS) $(0_LIBS_DEPS) $(0_OBJS_LISTFILE) .ld.dat
	@$(FEEDBACK) Linking Tamagotchi_target:$@
	$(PURIFY) $(0_LD) $(LD_HEAD) $(0_LDFLAGS) $(0_OBJS_LIST) $(0_USER_OBJS_LIST) $(0_LIBS) $(0_USER_LIBS) $(LD_TAIL)
	@$(FEEDBACK) Finished building $@

$(PURIFY_COV_TARGET) : $(0_OBJS) $(0_USER_OBJS) $(0_LIBS_DEPS) $(0_OBJS_LISTFILE) .ld.dat
	@$(FEEDBACK) Linking Tamagotchi_target:$@
	$(PURIFY_COV) $(0_LD) $(LD_HEAD) $(0_LDFLAGS) $(0_OBJS_LIST) $(0_USER_OBJS_LIST) $(0_LIBS) $(0_USER_LIBS) $(LD_TAIL)
	@$(FEEDBACK) Finished building $@

$(QUANTIFY_TARGET) : $(0_OBJS) $(0_USER_OBJS) $(0_LIBS_DEPS) $(0_OBJS_LISTFILE) .ld.dat
	@$(FEEDBACK) Linking Tamagotchi_target:$@
	$(QUANTIFY) $(0_LD) $(LD_HEAD) $(0_LDFLAGS) $(0_OBJS_LIST) $(0_USER_OBJS_LIST) $(0_LIBS) $(0_USER_LIBS) $(LD_TAIL)
	@$(FEEDBACK) Finished building $@

Feed$(OBJ_EXT) : ../Feed.cpp ../UnitName.h ../Feed.h ../FeedProt.h ../UpdateValProt.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:Feed
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../Feed.cpp $(CC_TAIL)

FeedProt$(OBJ_EXT) : ../FeedProt.cpp ../UnitName.h ../FeedProt.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:FeedProt
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../FeedProt.cpp $(CC_TAIL)

InputLoop$(OBJ_EXT) : ../InputLoop.cpp ../UnitName.h ../InputLoop.h ../InputProt.h ../StatusProt.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:InputLoop
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../InputLoop.cpp $(CC_TAIL)

InputProt$(OBJ_EXT) : ../InputProt.cpp ../UnitName.h ../InputProt.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:InputProt
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../InputProt.cpp $(CC_TAIL)

StatusProt$(OBJ_EXT) : ../StatusProt.cpp ../UnitName.h ../StatusProt.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:StatusProt
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../StatusProt.cpp $(CC_TAIL)

TranslateInput$(OBJ_EXT) : ../TranslateInput.cpp ../UnitName.h ../TranslateInput.h ../FeedProt.h ../InputProt.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:TranslateInput
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../TranslateInput.cpp $(CC_TAIL)

UnitName$(OBJ_EXT) : ../UnitName.cpp ../UnitName.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:UnitName
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../UnitName.cpp $(CC_TAIL)

Update$(OBJ_EXT) : ../Update.cpp ../UnitName.h ../Update.h ../StatusProt.h ../UpdateValProt.h ../FeedProt.h ../InputProt.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:Update
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../Update.cpp $(CC_TAIL)

UpdateValProt$(OBJ_EXT) : ../UpdateValProt.cpp ../UnitName.h ../UpdateValProt.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:UpdateValProt
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../UpdateValProt.cpp $(CC_TAIL)

0_clean :
	@$(ECHO) Cleaning Tamagotchi_target
	$(RMF) executable$(EXEC_EXT)
	$(RMF) Feed$(OBJ_EXT) FeedProt$(OBJ_EXT) InputLoop$(OBJ_EXT) InputProt$(OBJ_EXT) StatusProt$(OBJ_EXT)
	$(RMF) TranslateInput$(OBJ_EXT) UnitName$(OBJ_EXT) Update$(OBJ_EXT) UpdateValProt$(OBJ_EXT)
	$(RMF) Feed$(DEP_EXT) FeedProt$(DEP_EXT) InputLoop$(DEP_EXT) InputProt$(DEP_EXT) StatusProt$(DEP_EXT)
	$(RMF) TranslateInput$(DEP_EXT) UnitName$(DEP_EXT) Update$(DEP_EXT) UpdateValProt$(DEP_EXT)
	$(RMF) $(PURECOV_TARGET)
	$(RMF) $(PURIFY_TARGET)
	$(RMF) $(PURIFY_COV_TARGET)
	$(RMF) $(QUANTIFY_TARGET)
