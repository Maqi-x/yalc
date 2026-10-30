from dataclasses import dataclass, field
from typing import Literal
from pathlib import Path

TestStage = Literal['compilation', 'linking', 'runtime']

@dataclass
class Timeouts:
    compile: float
    link:    float
    runtime: float

@dataclass(order=True)
class TestCase:
    name:     str
    path:     Path = field(compare=False)
    category: str  = field(compare=False)

@dataclass
class TestExpectation:
    exitcode: int = 0
    stdout:   str = ""
    stderr:   str = ""

@dataclass
class FinishedResult:
    exitcode: int
    stdout:   str
    stderr:   str
    stage:    TestStage

@dataclass
class TimedOutResult:
    stage: TestStage

TestResult = FinishedResult | TimedOutResult
