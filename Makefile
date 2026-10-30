include make/directories.mk
include make/config.mk

LIBYALC_C_SRCS := $(call rwildcard,$(SRC_DIR),*.c)
ALL_C_SRCS     := $(LIBYALC_C_SRCS)

LIBYALC_OBJ_STATIC := $(patsubst %.c,$(OBJ_ROOT_DIR)/%.o,$(LIBYALC_C_SRCS))
LIBYALC_OBJ_SHARED := $(patsubst %.c,$(OBJ_ROOT_DIR)/shared/%.o,$(LIBYALC_C_SRCS))

DEPS := $(patsubst %.c,$(DEP_ROOT_DIR)/%.d,$(ALL_C_SRCS)) \
        $(patsubst %.c,$(DEP_ROOT_DIR)/shared/%.d,$(LIBYALC_C_SRCS))

.PHONY: all dirs lint clean inspect
.PHONY: libyalc libyalc-shared libyalc-static
.PHONY: archive

all: dirs compile-commands libyalc

archive: $(DIST_FILE)
$(DIST_FILE): all
ifeq ($(filter %.zip,$(DIST_FILE)),$(DIST_FILE))
	$(ECHO) "ZIP $@"
else
	$(ECHO) "TAR $@"
endif
	$(Q)$(call CMD_ARCHIVE)

libyalc-static: $(LIBYALC_STATIC)
libyalc-shared: $(LIBYALC_SHARED)
libyalc: libyalc-static libyalc-shared

dirs:
	@$(call CMD_MKDIR_P,$(LIB_DIR))
	@$(call CMD_MKDIR_P,$(OBJ_ROOT_DIR))
	@$(call CMD_MKDIR_P,$(DEP_ROOT_DIR))
	@$(call CMD_MKDIR_P,$(OBJ_ROOT_DIR)/shared)
	@$(call CMD_MKDIR_P,$(DEP_ROOT_DIR)/shared)

lint:
	clang-tidy $(ALL_C_SRCS) -- $(CFLAGS)

inspect:
	$(MAKE) clean
	$(MAKE) libyalc >/dev/null

$(LIBYALC_STATIC): $(LIBYALC_OBJ_STATIC)
	@$(call CMD_MKDIR_P,$(dir $@))
	$(ECHO) "AR $@"
	$(Q)$(AR) rcs $@ $^

$(LIBYALC_SHARED): $(LIBYALC_OBJ_SHARED)
	@$(call CMD_MKDIR_P,$(dir $@))
	$(ECHO) "CC $@"
	$(Q)$(CC) -shared $^ $(LDFLAGS) -o $@

$(OBJ_ROOT_DIR)/%.o: %.c
	@$(call CMD_MKDIR_P,$(dir $@))
	@$(call CMD_MKDIR_P,$(DEP_ROOT_DIR)/$(dir $<))
	$(ECHO) "CC $@"
	$(Q)$(CC) $(CFLAGS) -MMD -MP -MF $(DEP_ROOT_DIR)/$*.d -c $< -o $@

$(OBJ_ROOT_DIR)/shared/%.o: %.c
	@$(call CMD_MKDIR_P,$(dir $@))
	@$(call CMD_MKDIR_P,$(DEP_ROOT_DIR)/shared/$(dir $<))
	$(ECHO) "CC $@"
	$(Q)$(CC) $(CFLAGS) $(PIC_CFLAGS) -MMD -MP -MF $(DEP_ROOT_DIR)/shared/$*.d -c $< -o $@

-include $(DEPS)

include tests/build.mk

include make/compcmds.mk
include make/install.mk

clean:
	@$(call CMD_RM_RF,build)
	@$(call CMD_RM_RF,out)
