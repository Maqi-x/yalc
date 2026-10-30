import subprocess
import typing
import sys
import os
import re
import shlex

from pathlib import Path

from .models  import *
from .console import *
from .defs    import *

def get_expectation(test: TestCase) -> TestExpectation:
    path = test.path
    try:
        content = path.read_text(encoding='utf-8')
    except Exception as err:
        error(f"failed to read test file {path}: {err}")

    stripped = content.lstrip()
    if not stripped.startswith('/*'):
        return TestExpectation(exitcode=0, stdout="", stderr="")

    end_idx = stripped.find('*/')
    if end_idx == -1:
        error(f"ill-formed test header in {path}: unterminated /* comment")

    comment = stripped[2:end_idx]

    fields: dict[str, list[str]] = {}
    current_key: str | None = None

    for line in comment.splitlines():
        trimmed = line.strip()
        if not trimmed:
            continue

        m = re.match(r'^([a-zA-Z0-9_-]+):\s*(.*)$', trimmed)
        if m:
            current_key = m.group(1).lower()
            assert current_key is not None

            fields[current_key] = []
            inline_val = m.group(2).strip()
            if inline_val:
                fields[current_key].append(inline_val)

        elif current_key is not None:
            fields[current_key].append(trimmed)

    raw_exitcode = fields.get('exit-code') or fields.get('exitcode')
    exitcode = 0
    if raw_exitcode is not None:
        val_str = ' '.join(raw_exitcode).strip()
        try:
            exitcode = int(val_str)
        except ValueError:
            error(f"ill-formed test header in {path}: exit-code '{val_str}' is not a valid integer")

    stdout = '\n'.join(fields.get('stdout', [])).strip()
    stderr = '\n'.join(fields.get('stderr', [])).strip()

    return TestExpectation(exitcode=exitcode, stdout=stdout, stderr=stderr)

def _run_stage(cmd: list[str], stage: TestStage, timeout: float, cwd: Path | None = None) -> TestResult:
    try:
        res = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            timeout=timeout,
            cwd=cwd,
        )
        return FinishedResult(
            exitcode=res.returncode,
            stdout=res.stdout.strip(),
            stderr=res.stderr.strip(),
            stage=stage,
        )
    except subprocess.TimeoutExpired:
        return TimedOutResult(stage=stage)

def run_test_case(
    case: TestCase,
    work_dir: Path,
    timeouts: Timeouts,
    cc: str,
    lib_path: Path | None,
    include_dir: Path,
    verify: bool
) -> TestResult:
    test_dir = work_dir / case.category / case.path.stem
    test_dir.mkdir(parents=True, exist_ok=True)

    obj_file = test_dir / f"{case.path.stem}.o"
    exe_name = f"{case.path.stem}.exe" if sys.platform == 'win32' else case.path.stem
    exe_file = test_dir / exe_name

    cc_cmd = shlex.split(cc)

    # Compilation
    if verify:
        compile_cmd = [
            *cc_cmd,
            '-c', str(case.path),
            '-I', str(include_dir),
            '-o', str(obj_file)
        ]
    else:
        compile_cmd = [
            *cc_cmd,
            '-c', str(case.path),
            '-nostdlib',
            '-I', str(include_dir),
            '-I', str(include_dir / 'yalc' / 'api'),
            '-D__YALC_INC_BASE=yalc/',
            '-o', str(obj_file)
        ]

    comp_res = _run_stage(compile_cmd, stage='compilation', timeout=timeouts.compile, cwd=project_dir)
    if isinstance(comp_res, TimedOutResult) or comp_res.exitcode != 0:
        return comp_res

    # Linking
    if verify:
        link_cmd = [
            *cc_cmd,
            str(obj_file),
            '-o', str(exe_file)
        ]
    else:
        if lib_path is None or not lib_path.is_file():
            error(f"static library not found at {lib_path}")
        link_cmd = [
            *cc_cmd,
            '-nostdlib',
            str(obj_file),
            str(lib_path),
            '-o', str(exe_file)
        ]

    link_res = _run_stage(link_cmd, stage='linking', timeout=timeouts.link, cwd=project_dir)
    if isinstance(link_res, TimedOutResult) or link_res.exitcode != 0:
        return link_res

    # Runtime
    run_res = _run_stage([str(exe_file)], stage='runtime', timeout=timeouts.runtime, cwd=project_dir)
    return run_res
