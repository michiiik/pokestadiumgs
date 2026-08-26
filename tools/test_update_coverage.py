#!/usr/bin/env python3
"""Regression tests for the COVERAGE.md generator."""

from __future__ import annotations

import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import update_coverage as cov  # noqa: E402


def _run_git(repo: Path, *args: str) -> str:
    result = subprocess.run(
        ["git", "-C", str(repo), *args],
        check=True,
        capture_output=True,
        text=True,
    )
    return result.stdout


def _pragma(owner: str) -> str:
    return f'#pragma GLOBAL_ASM("asm/us/nonmatchings/x/{owner}.s")\n'


class _GitFixture:
    """A tiny git repo with disasm/src/*.c pragma owners across three states:

    baseline commit -> HEAD commit -> staged (index, uncommitted).
    """

    def __init__(self, repo: Path) -> None:
        self.repo = repo
        src = repo / "disasm" / "src"
        src.mkdir(parents=True)

        _run_git(repo, "init", "-q", "-b", "main")
        _run_git(repo, "config", "user.email", "test@example.com")
        _run_git(repo, "config", "user.name", "Test")

        # Baseline: AAA.c has 3 owners, BBB.c has 2 owners (5 total).
        (src / "AAA.c").write_text(_pragma("func_1") + _pragma("func_2") + _pragma("func_3"))
        (src / "BBB.c").write_text(_pragma("func_4") + _pragma("func_5"))
        _run_git(repo, "add", "-A")
        _run_git(repo, "commit", "-q", "-m", "baseline")
        self.baseline_sha = _run_git(repo, "rev-parse", "HEAD").strip()

        # HEAD: func_2 decompiled out of AAA.c (2 remaining there; 4 total).
        (src / "AAA.c").write_text(_pragma("func_1") + _pragma("func_3"))
        _run_git(repo, "add", "-A")
        _run_git(repo, "commit", "-q", "-m", "decompile func_2")
        self.head_sha = _run_git(repo, "rev-parse", "HEAD").strip()

        # Staged (uncommitted): func_4 also decompiled out of BBB.c.
        (src / "BBB.c").write_text(_pragma("func_5"))
        _run_git(repo, "add", "-A")


class CoverageSnapshotTests(unittest.TestCase):
    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.repo = Path(self._tmp.name)
        self.fixture = _GitFixture(self.repo)

    def tearDown(self) -> None:
        self._tmp.cleanup()

    def _patched_baseline(self):
        return mock.patch.multiple(
            cov, BASELINE_COMMIT=self.fixture.baseline_sha, BASELINE_TOTAL=5
        )

    def test_baseline_revision_has_no_coverage_yet(self) -> None:
        with self._patched_baseline():
            snapshot = cov.coverage_snapshot(self.repo, revision=self.fixture.baseline_sha)
        self.assertEqual(snapshot.covered, 0)
        self.assertEqual(snapshot.total, 5)
        self.assertEqual(snapshot.remaining_by_file, {"disasm/src/AAA.c": 3, "disasm/src/BBB.c": 2})

    def test_head_revision_reflects_committed_decompilation(self) -> None:
        with self._patched_baseline():
            snapshot = cov.coverage_snapshot(self.repo, revision="HEAD")
        self.assertEqual(snapshot.covered, 1)
        self.assertEqual(snapshot.total, 5)
        self.assertAlmostEqual(snapshot.percentage, 20.0)
        self.assertEqual(snapshot.remaining_by_file, {"disasm/src/AAA.c": 2, "disasm/src/BBB.c": 2})

    def test_staged_reflects_index_not_head(self) -> None:
        with self._patched_baseline():
            head_snapshot = cov.coverage_snapshot(self.repo, revision="HEAD")
            staged_snapshot = cov.coverage_snapshot(self.repo, staged=True)
        # HEAD is unaffected by the staged-but-uncommitted func_4 removal.
        self.assertEqual(head_snapshot.remaining_by_file["disasm/src/BBB.c"], 2)
        self.assertEqual(staged_snapshot.covered, 2)
        self.assertEqual(staged_snapshot.remaining_by_file, {"disasm/src/AAA.c": 2, "disasm/src/BBB.c": 1})

    def test_specific_older_revision_selectable(self) -> None:
        with self._patched_baseline():
            snapshot = cov.coverage_snapshot(self.repo, revision=self.fixture.baseline_sha[:7])
        self.assertEqual(snapshot.covered, 0)
        self.assertEqual(snapshot.remaining_by_file, {"disasm/src/AAA.c": 3, "disasm/src/BBB.c": 2})

    def test_baseline_remaining_by_file(self) -> None:
        with self._patched_baseline():
            baseline = cov.baseline_remaining_by_file(self.repo)
        self.assertEqual(baseline, {"disasm/src/AAA.c": 3, "disasm/src/BBB.c": 2})

    def test_baseline_remaining_by_file_unavailable_returns_none(self) -> None:
        # The real module-level BASELINE_COMMIT does not exist in this
        # throwaway repo, so git grep fails to resolve it (shallow-clone-like
        # fallback).
        baseline = cov.baseline_remaining_by_file(self.repo)
        self.assertIsNone(baseline)


class RenderingTests(unittest.TestCase):
    def test_render_block_formats_counts_and_percentage(self) -> None:
        block = cov.render_block(covered=3142, total=10532, percentage=29.83745)
        self.assertIn(cov.START_MARKER, block)
        self.assertIn(cov.END_MARKER, block)
        self.assertIn("**3,142 / 10,532 (29.8%)**", block)
        self.assertIn("Remaining `GLOBAL_ASM` owners: **7,390**", block)
        self.assertIn(f"Baseline: `{cov.BASELINE_COMMIT}`", block)

    def test_render_file_table_uses_baseline_totals(self) -> None:
        remaining_by_file = {"disasm/src/AAA.c": 2, "disasm/src/BBB.c": 2}
        baseline_by_file = {"disasm/src/AAA.c": 3, "disasm/src/BBB.c": 2}
        table = cov.render_file_table(remaining_by_file, baseline_by_file)
        lines = table.splitlines()
        self.assertEqual(lines[0], "| File | Remaining | Baseline total | Percent complete |")
        self.assertIn("| `disasm/src/AAA.c` | 2 | 3 | 33.3% |", lines)
        self.assertIn("| `disasm/src/BBB.c` | 2 | 2 | 0.0% |", lines)

    def test_render_file_table_falls_back_without_baseline(self) -> None:
        remaining_by_file = {"disasm/src/AAA.c": 2}
        table = cov.render_file_table(remaining_by_file, None)
        self.assertIn("| `disasm/src/AAA.c` | 2 | 2 | 0.0% |", table.splitlines())

    def test_render_file_table_empty(self) -> None:
        table = cov.render_file_table({}, {"disasm/src/AAA.c": 3})
        self.assertIn("No source files", table)

    def test_render_coverage_md_includes_generated_header_and_sections(self) -> None:
        snapshot = cov.CoverageSnapshot(
            covered=1, total=5, percentage=20.0, remaining_by_file={"disasm/src/AAA.c": 4}
        )
        content = cov.render_coverage_md(snapshot, {"disasm/src/AAA.c": 5})
        self.assertTrue(content.startswith(cov.GENERATED_HEADER))
        self.assertIn("do not edit", cov.GENERATED_HEADER.lower())
        self.assertIn(cov.START_MARKER, content)
        self.assertIn("## Remaining owners by source file", content)
        self.assertIn("| `disasm/src/AAA.c` | 4 | 5 | 20.0% |", content)


class WriteIfChangedTests(unittest.TestCase):
    def test_writes_only_on_change(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "COVERAGE.md"
            self.assertTrue(cov.write_if_changed(path, "one"))
            self.assertEqual(path.read_text(encoding="utf-8"), "one")
            self.assertFalse(cov.write_if_changed(path, "one"))
            self.assertTrue(cov.write_if_changed(path, "two"))
            self.assertEqual(path.read_text(encoding="utf-8"), "two")


class CommandLineTests(unittest.TestCase):
    def test_staged_cli_writes_coverage_md(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            repo = Path(directory)
            fixture = _GitFixture(repo)
            output = repo / "COVERAGE.md"
            subprocess.run(
                [
                    sys.executable,
                    str(TOOLS / "update_coverage.py"),
                    "--repo-root",
                    str(repo),
                    "--output",
                    str(output),
                    "--staged",
                ],
                check=True,
                capture_output=True,
                text=True,
            )
            content = output.read_text(encoding="utf-8")
            self.assertTrue(content.startswith(cov.GENERATED_HEADER))
            self.assertIn("| `disasm/src/AAA.c` | 2 |", content)
            self.assertIn("| `disasm/src/BBB.c` | 1 |", content)
            del fixture  # fixture only needed for its side effects

    def test_revision_cli_selects_baseline_commit(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            repo = Path(directory)
            fixture = _GitFixture(repo)
            output = repo / "COVERAGE.md"
            subprocess.run(
                [
                    sys.executable,
                    str(TOOLS / "update_coverage.py"),
                    "--repo-root",
                    str(repo),
                    "--output",
                    str(output),
                    "--revision",
                    fixture.baseline_sha,
                ],
                check=True,
                capture_output=True,
                text=True,
            )
            content = output.read_text(encoding="utf-8")
            self.assertIn("| `disasm/src/AAA.c` | 3 |", content)
            self.assertIn("| `disasm/src/BBB.c` | 2 |", content)


if __name__ == "__main__":
    unittest.main()
