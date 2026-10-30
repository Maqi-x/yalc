#!/usr/bin/env python3

from pathlib import Path
from typing import Optional

import argparse
import typing
import sys
import os

tests_root = Path(__file__).resolve().parent
if str(tests_root) not in sys.path:
    sys.path.insert(0, str(tests_root))

from runner.models import Timeouts
from runner.suite import run_suite
from runner.defs import project_dir

class CliArgs(argparse.Namespace):
    lib:             Optional[Path]
    work_dir:        Path
    parallel:        Optional[int]
    verbose:         bool
    timeout:         float
    compile_timeout: Optional[float]
    link_timeout:    Optional[float]
    runtime_timeout: Optional[float]
    verify:          bool
    cc:              str
    include_dir:     Path

def main():
    parser = argparse.ArgumentParser(description="yalc's test runner")
    parser.add_argument('--lib', type=Path, default=None, help='Path to libyalc.a binary')
    parser.add_argument('--work-dir', type=Path, default=project_dir / 'out' / 'release' / 'tests', help='Path to working directory')
    parser.add_argument(
        '-j', '--parallel', nargs='?',
        const=None, default=1, type=int,
        help='run in parallel with optional N workers limit'
    )

    parser.add_argument(
        '-t', '--timeout', type=float, default=1.0,
        help='base timeout multiplier'
    )
    parser.add_argument('--compile-timeout', type=float, help='compile stage timeout (default: 2.0s * timeout)')
    parser.add_argument('--link-timeout',    type=float, help='link stage timeout (default: 5.0s * timeout)')
    parser.add_argument('--runtime-timeout', type=float, help='runtime stage timeout (default: 3.0s * timeout)')

    parser.add_argument('-v', '--verbose', action='store_true', default=True,            help='verbose mode: print all passing test cases')
    parser.add_argument('--verify',        dest='verify', action='store_true',           help='verify tests using default libc instead of yalc')
    parser.add_argument('--cc',            type=str, default=os.environ.get('CC', 'cc'), help='c compiler to use (default: $CC or cc)')
    parser.add_argument('--include-dir',   type=Path, default=project_dir / 'include',   help='path to the include directory')

    args = typing.cast(CliArgs, parser.parse_args())

    timeouts = Timeouts(
        compile = (args.compile_timeout or 2.0) * args.timeout,
        runtime = (args.runtime_timeout or 3.0) * args.timeout,
        link    = (args.link_timeout    or 5.0) * args.timeout,
    )

    work_dir = args.work_dir.resolve()
    if not work_dir.exists():
        os.makedirs(str(work_dir), exist_ok=True)

    lib_path = args.lib.resolve() if args.lib else None
    include_dir = args.include_dir.resolve()

    if not args.verify:
        if lib_path is None:
            sys.stderr.write("error: --lib is required when not running with --verify\n")
            sys.exit(1)
        if not lib_path.is_file():
            sys.stderr.write(f"error: static library not found at {lib_path}\n")
            sys.exit(1)

    success = run_suite(
        work_dir=work_dir,
        jobs=args.parallel,
        timeouts=timeouts,
        verbose=args.verbose,
        cc=args.cc,
        lib_path=lib_path,
        include_dir=include_dir,
        verify=args.verify
    )

    if not success:
        sys.exit(1)

if __name__ == '__main__':
    main()
