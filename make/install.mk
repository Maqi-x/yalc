.PHONY: install uninstall

PREFIX     ?= /usr/local
DESTDIR    ?=
LIBDIR     ?= $(PREFIX)/lib
INCLUDEDIR ?= $(PREFIX)/include

install: all
ifneq ($(PLATFORM),posix)
	$(error install unsupported on non-posix platforms)
else
	@$(call CMD_MKDIR_P,$(DESTDIR)$(LIBDIR))
	@$(call CMD_MKDIR_P,$(DESTDIR)$(INCLUDEDIR))

	$(ECHO) "INSTALL $(DESTDIR)$(LIBDIR)/$(notdir $(LIBYALC_STATIC))"
	$(Q)install -m644 $(LIBYALC_STATIC) $(DESTDIR)$(LIBDIR)/

	$(ECHO) "INSTALL $(DESTDIR)$(LIBDIR)/$(notdir $(LIBYALC_SHARED))"
	$(Q)install -m755 $(LIBYALC_SHARED) $(DESTDIR)$(LIBDIR)/

	$(ECHO) "INSTALL $(DESTDIR)$(INCLUDEDIR)"
	$(Q)cp -R $(INCLUDE_DIR)/. $(DESTDIR)$(INCLUDEDIR)/
endif

uninstall:
ifneq ($(PLATFORM),posix)
	$(error install unsupported on non-posix platforms)
else
	$(ECHO) "RM $(DESTDIR)$(LIBDIR)/$(notdir $(LIBYALC_STATIC))"
	@$(call CMD_RM_F,$(DESTDIR)$(LIBDIR)/$(notdir $(LIBYALC_STATIC)))

	$(ECHO) "RM $(DESTDIR)$(LIBDIR)/$(notdir $(LIBYALC_SHARED))"
	@$(call CMD_RM_F,$(DESTDIR)$(LIBDIR)/$(notdir $(LIBYALC_SHARED)))

	$(ECHO) "RM $(DESTDIR)$(INCLUDEDIR)/yalc"
	@$(call CMD_RM_RF,$(DESTDIR)$(INCLUDEDIR)/yalc)
endif
