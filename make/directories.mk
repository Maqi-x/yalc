include make/config.mk

SRC_DIR     := src
TEST_DIR    := tests
INCLUDE_DIR := include
SCRIPTS_DIR := scripts

OBJ_ROOT_DIR := build/$(BUILD)/obj
DEP_ROOT_DIR := build/$(BUILD)/dep

OUT_DIR := out/$(BUILD)
LIB_DIR := $(OUT_DIR)/lib

EXE_EXT :=
ifeq ($(PLATFORM),windows)
	EXE_EXT    := .exe
	SHARED_EXT := .dll
	STATIC_EXT := .a
else ifeq ($(PLATFORM),posix)
	EXE_EXT    :=
	SHARED_EXT := .so
	STATIC_EXT := .a
endif

LIBYALC_NAME   := yalc
LIBYALC_STATIC := $(LIB_DIR)/lib$(LIBYALC_NAME)$(STATIC_EXT)
LIBYALC_SHARED := $(LIB_DIR)/lib$(LIBYALC_NAME)$(SHARED_EXT)

DIST_NAME := $(OUT_DIR)/yalc-$(VERSION)-$(DIST_OS)-$(DIST_ARCH)-$(BUILD)
