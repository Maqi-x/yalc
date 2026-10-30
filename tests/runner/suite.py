import threading
import typing
import os
import sys

from concurrent.futures import ThreadPoolExecutor, as_completed
from signal import Signals
from pathlib import Path

from .models  import *
from .console import *
from .defs    import *
from .test    import run_test_case, get_expectation

def report_compilation_failure(actual: FinishedResult):
    print_info(f'  Error during {CLR_BOLD}{actual.stage}{CLR_RESET} stage (exitcode {actual.exitcode})')
    if actual.stdout:
        print_info(f'  stdout:')
        for line in actual.stdout.splitlines():
            print_info(f'    {line}')
    if actual.stderr:
        print_info(f'  stderr:')
        for line in actual.stderr.splitlines():
            print_info(f'    {line}')

def report_failure(case: TestCase, expected: TestExpectation, actual: TestResult, cc: str, lib_path: Path | None, verify: bool):
    if isinstance(actual, TimedOutResult):
        print_timeout(case.name)
        print_info(f'  Timed out during {CLR_BOLD}{actual.stage}{CLR_RESET} stage')
    else:
        print_fail(case.name)

    print_info(f'  reproduce:')
    if verify:
        print_info(f'    {cc} -Iinclude {case.path}')
    else:
        lib_str = str(lib_path) if lib_path else '<libyalc.a>'
        print_info(f'    {cc} -nostdlib -Iinclude -Iinclude/yalc/api -D__YALC_INC_BASE=yalc/ {case.path} {lib_str}')

    if not isinstance(actual, FinishedResult):
        return

    if actual.stage != 'runtime':
        report_compilation_failure(actual)
        return

    if actual.exitcode != expected.exitcode:
        print_info(f'  exitcode: expected {expected.exitcode}, actual {actual.exitcode}')

    if expected.stdout != actual.stdout:
        print_diff(expected.stdout, actual.stdout, 'stdout')
    if expected.stderr != actual.stderr:
        print_diff(expected.stderr, actual.stderr, 'stderr')

def collect_test_cases() -> list[TestCase]:
    cases: list[TestCase] = []
    if not tests_dir.is_dir():
        error(f"tests directory not found at {tests_dir}")

    for category_dir in tests_dir.iterdir():
        if not category_dir.is_dir():
            continue

        if category_dir.name in ('runner', '__pycache__'):
            continue

        for item in category_dir.iterdir():
            if item.is_file() and item.suffix == '.c':
                name = f"{category_dir.name}/{item.stem}"
                cases.append(TestCase(name=name, path=item, category=category_dir.name))

    return sorted(cases)

def _is_success(expected: TestExpectation, actual: TestResult) -> bool:
    if isinstance(actual, TimedOutResult):
        return False

    if actual.stage != 'runtime':
        return False
    if actual.exitcode != expected.exitcode:
        return False
    if actual.stdout != expected.stdout:
        return False
    if actual.stderr != expected.stderr:
        return False

    return True

def run_suite(
    *, # see https://www.youtube.com/watch?v=R8-oAqCgHag
    work_dir: Path,
    jobs: int | None,
    timeouts: Timeouts,
    verbose: bool,
    cc: str,
    lib_path: Path | None,
    include_dir: Path,
    verify: bool
) -> bool:
    passed_count  = 0
    failed_count  = 0
    crashed_count = 0
    skipped_count = 0

    test_cases = collect_test_cases()

    tasks = []
    for case in test_cases:
        tasks.append((case, get_expectation(case)))

    def handle_result(case: TestCase, expected: TestExpectation, actual: TestResult | None):
        nonlocal passed_count, failed_count, crashed_count, skipped_count
        if actual is None:
            print_skip(case.name)
            skipped_count += 1
        elif isinstance(actual, FinishedResult) and actual.exitcode < 0:
            print_fail(case.name)
            try:
                signame = Signals(-actual.exitcode).name
            except ValueError:
                signame = f"signal {-actual.exitcode}"
            print_info(f'  crash: {signame}')
            crashed_count += 1
        elif _is_success(expected, actual):
            if verbose:
                print_pass(case.name)
            passed_count += 1
        else:
            report_failure(case, expected, actual, cc, lib_path, verify)
            failed_count += 1

    if jobs is None or jobs > 1:
        with ThreadPoolExecutor(max_workers=jobs) as executor:
            future_to_test = {}
            for case, expected in tasks:
                future = executor.submit(
                    run_test_case, case, work_dir, timeouts, cc, lib_path, include_dir, verify
                )
                future_to_test[future] = (case, expected)

            for future in as_completed(future_to_test):
                case, expected = future_to_test[future]
                handle_result(case, expected, future.result())
    else:
        for case, expected in tasks:
            result = run_test_case(case, work_dir, timeouts, cc, lib_path, include_dir, verify)
            handle_result(case, expected, result)

    tested_count = passed_count + failed_count + crashed_count + skipped_count
    print(f'[{CLR_BLUE}===={CLR_RESET}] {CLR_BOLD}Synthesis: ', end='')
    print(f'Tested: {CLR_BLUE}{tested_count}{CLR_RESET}{CLR_BOLD} ', end='')
    print(f'| Passing: {stat(passed_count, CLR_GREEN)}{CLR_BOLD} ', end='')
    print(f'| Failing: {stat(failed_count, CLR_RED)}{CLR_BOLD} ', end='')
    print(f'| Crashing: {stat(crashed_count, CLR_ORANGE)}{CLR_BOLD} ', end='')
    if skipped_count != 0:
        print(f'| Skipped: {CLR_BLUE}{skipped_count}{CLR_RESET}', end='')
    print(CLR_RESET)

    return (failed_count + crashed_count) == 0
