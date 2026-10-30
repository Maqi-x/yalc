TESTS_DIR     := tests
TESTS_OUT_DIR := $(OUT_DIR)/tests

TEST_RUNNER := $(TESTS_DIR)/runner.py

ifdef TEST_PARALLELISM
	TEST_PARALLEL_FLAG := -j$(TEST_PARALLELISM)
endif

.PHONY: test-dirs clean-tests clean-test
.PHONY: test test-verbose verify-tests verify-tests-verbose

test-dirs:
	@$(call CMD_MKDIR_P,$(TESTS_OUT_DIR))

clean-test: clean-tests
clean-tests:
	@$(call CMD_RM_RF,$(TESTS_OUT_DIR))

test: $(LIBYALC_STATIC) | test-dirs
	@echo "Running tests"
	@$(PY) $(TEST_RUNNER) --lib $(LIBYALC_STATIC) --work-dir $(TESTS_OUT_DIR) $(TEST_PARALLEL_FLAG)

test-verbose: $(LIBYALC_STATIC) | test-dirs
	@echo "Running tests"
	@$(PY) $(TEST_RUNNER) --lib $(LIBYALC_STATIC) --work-dir $(TESTS_OUT_DIR) $(TEST_PARALLEL_FLAG) --verbose

verify-tests: | test-dirs
	@echo "Verifying tests with default libc"
	@$(PY) $(TEST_RUNNER) --work-dir $(TESTS_OUT_DIR) $(TEST_PARALLEL_FLAG) --verify

verify-tests-verbose: | test-dirs
	@echo "Verifying tests with default libc"
	@$(PY) $(TEST_RUNNER) --work-dir $(TESTS_OUT_DIR) $(TEST_PARALLEL_FLAG) --verbose --verify
