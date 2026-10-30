export CC
export BUILD
export CFLAGS
export LIBYALC_C_SRCS

.PHONY: compile-commands clean-compile-commands

compile-commands: compile_commands.json

compile_commands.json:
	$(ECHO) "PY $@"
	$(Q)$(PY) scripts/gen-comp-cmds.py

clean-compile-commands:
	@$(call CMD_RM_F,compile_commands.json)
