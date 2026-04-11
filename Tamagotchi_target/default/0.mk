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
	Input$(OBJ_EXT)\
	MainGame$(OBJ_EXT)\
	StatusProt$(OBJ_EXT)\
	Top$(OBJ_EXT)\
	UnitName$(OBJ_EXT)
0_OBJS_LIST = $(0_OBJS)
0_OBJS_LISTFILE = .olist
0_DEPFILES = \
	Input$(DEP_EXT)\
	MainGame$(DEP_EXT)\
	StatusProt$(DEP_EXT)\
	Top$(DEP_EXT)\
	UnitName$(DEP_EXT)

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

Input$(OBJ_EXT) : ../Input.cpp ../UnitName.h ../Input.h ../StatusProt.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:Input
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../Input.cpp $(CC_TAIL)

MainGame$(OBJ_EXT) : ../MainGame.cpp ../UnitName.h ../MainGame.h ../StatusProt.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:MainGame
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../MainGame.cpp $(CC_TAIL)

StatusProt$(OBJ_EXT) : ../StatusProt.cpp ../UnitName.h ../StatusProt.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:StatusProt
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../StatusProt.cpp $(CC_TAIL)

Top$(OBJ_EXT) : ../Top.cpp ../UnitName.h ../Top.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:Top
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../Top.cpp $(CC_TAIL)

UnitName$(OBJ_EXT) : ../UnitName.cpp ../UnitName.h .cc.dat
	@$(FEEDBACK) Compiling Tamagotchi_target:UnitName
	$(0_CC) $(CC_HEAD) $(0_CCFLAGS) $(0_INCPATHS) ../UnitName.cpp $(CC_TAIL)

0_clean :
	@$(ECHO) Cleaning Tamagotchi_target
	$(RMF) executable$(EXEC_EXT)
	$(RMF) Input$(OBJ_EXT) MainGame$(OBJ_EXT) StatusProt$(OBJ_EXT) Top$(OBJ_EXT) UnitName$(OBJ_EXT)
	$(RMF) Input$(DEP_EXT) MainGame$(DEP_EXT) StatusProt$(DEP_EXT) Top$(DEP_EXT) UnitName$(DEP_EXT)
	$(RMF) $(PURECOV_TARGET)
	$(RMF) $(PURIFY_TARGET)
	$(RMF) $(PURIFY_COV_TARGET)
	$(RMF) $(QUANTIFY_TARGET)
