#!/usr/bin/env python3
"""Unit tests for tools/probe_one.py.

The ``tools/fleet_probe.py`` subprocess call is stubbed via
``probe_one.run_probe_subprocess`` -- nothing here shells out, compiles
anything, or reads the real disasm tree.
"""

from __future__ import annotations

import io
import json
import subprocess
import sys
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import probe_one  # noqa: E402


def _completed(returncode: int, stdout: str = "", stderr: str = "") -> subprocess.CompletedProcess:
    return subprocess.CompletedProcess(args=["fleet_probe.py"], returncode=returncode, stdout=stdout, stderr=stderr)


def _stub_writes_result(result: dict, *, returncode: int = 0, stdout: str = "", stderr: str = ""):
    """Build a fake ``run_probe_subprocess`` that writes ``result`` as the
    JSON fleet_probe.py would have written, and records the batch it saw.
    """
    calls: list[dict] = []

    def _fake(batch_path: Path, result_path: Path, *, repo_root: Path, timeout: float):
        calls.append({
            "batch": json.loads(batch_path.read_text(encoding="utf-8")),
            "repo_root": repo_root,
            "timeout": timeout,
        })
        result_path.write_text(json.dumps(result), encoding="utf-8")
        return _completed(returncode, stdout, stderr)

    _fake.calls = calls  # type: ignore[attr-defined]
    return _fake


def _attempt(status: str = "probe_rejected", **overrides: object) -> dict:
    row = {
        "function": "func_X",
        "label": "probe",
        "status": status,
        "similarity_score": 0.9,
        "raw_similarity_score": 0.8,
        "mismatch_kind": "operand_or_scheduling_drift",
        "futility": None,
        "expected_size": 64,
        "actual_size": 64,
        "expected_instruction_count": 16,
        "actual_instruction_count": 16,
        "first_diff_offset": 12,
        "expected_instruction_text": "addiu a1, a1, 4",
        "actual_instruction_text": "addiu a1, a1, 8",
        "diagnostic": "similarity_score=0.9 raw_similarity_score=0.8 mismatch_kind=operand_or_scheduling_drift",
        "assembly_diff": [
            {
                "expected_offset": 8, "actual_offset": 8,
                "expected": "addiu a0, a0, 4", "actual": "addiu a0, a0, 4",
                "exact_match": True,
            },
            {
                "expected_offset": 12, "actual_offset": 12,
                "expected": "addiu a1, a1, 4", "actual": "addiu a1, a1, 8",
                "exact_match": False,
            },
        ],
        "normalized_only_match": False,
    }
    row.update(overrides)
    return row


VALID_BODY = "void func_X(s32 arg0) {\n    return;\n}\n"


class BodyShapeTests(unittest.TestCase):
    def test_valid_body_passes(self) -> None:
        self.assertIsNone(probe_one.check_body_shape(VALID_BODY, "func_X"))

    def test_bare_block_rejected(self) -> None:
        error = probe_one.check_body_shape("{ return; }", "func_X")
        self.assertIsNotNone(error)
        self.assertIn("func_X(", error)

    def test_missing_brace_rejected(self) -> None:
        error = probe_one.check_body_shape("void func_X(s32 arg0)", "func_X")
        self.assertIsNotNone(error)
        self.assertIn("no '{'", error)

    def test_empty_body_rejected(self) -> None:
        error = probe_one.check_body_shape("   \n  ", "func_X")
        self.assertIsNotNone(error)
        self.assertIn("empty", error)

    def test_wrong_function_name_rejected(self) -> None:
        error = probe_one.check_body_shape("void func_OTHER(void) { return; }", "func_X")
        self.assertIsNotNone(error)


class RenderReportTests(unittest.TestCase):
    def test_rejected_report_has_core_fields(self) -> None:
        lines = probe_one.render_report(_attempt(), max_diff=60)
        text = "\n".join(lines)
        self.assertIn("status: probe_rejected", text)
        self.assertIn("similarity: 0.9000", text)
        self.assertIn("raw: 0.8000", text)
        self.assertIn("mismatch_kind: operand_or_scheduling_drift", text)
        self.assertIn("instructions: expected 16, actual 16", text)
        self.assertIn("first mismatch at offset 12", text)
        self.assertIn("expected `addiu a1, a1, 4`", text)
        self.assertIn("actual `addiu a1, a1, 8`", text)
        self.assertIn("diff:", text)
        self.assertIn("(match)", text)  # exact-match context line
        self.assertNotIn("NORMALIZED-ONLY", text)

    def test_frame_size_mismatch_shown_only_when_different(self) -> None:
        same = probe_one.render_report(_attempt(expected_size=64, actual_size=64), max_diff=60)
        self.assertFalse(any("frame:" in line for line in same))
        diff = probe_one.render_report(_attempt(expected_size=64, actual_size=72), max_diff=60)
        self.assertTrue(any("frame: expected 64 bytes, actual 72" in line for line in diff))

    def test_futility_shown_when_present(self) -> None:
        lines = probe_one.render_report(_attempt(futility="register-tie"), max_diff=60)
        self.assertTrue(any("futility: register-tie" in line for line in lines))

    def test_compile_failed_report_shows_compiler_error(self) -> None:
        diag = "\n".join(f"error line {i}" for i in range(50))
        attempt = _attempt(
            status="compile_failed",
            similarity_score=None,
            raw_similarity_score=None,
            mismatch_kind=None,
            assembly_diff=None,
            diagnostic=diag,
        )
        lines = probe_one.render_report(attempt, max_diff=60)
        text = "\n".join(lines)
        self.assertIn("status: compile_failed", text)
        self.assertIn("compiler error (first 30 lines):", text)
        self.assertIn("error line 0", text)
        self.assertIn("error line 29", text)
        self.assertNotIn("error line 30", text)
        self.assertIn("... (truncated)", text)

    def test_normalized_only_match_warning(self) -> None:
        attempt = _attempt(
            normalized_only_match=True,
            similarity_score=0.9997,
            raw_similarity_score=0.4,
        )
        lines = probe_one.render_report(attempt, max_diff=60)
        text = "\n".join(lines)
        self.assertIn("NORMALIZED-ONLY MATCH", text)

    def test_normalized_only_match_inferred_from_scores(self) -> None:
        # No explicit flag, but the score-shape heuristic should still catch it.
        attempt = _attempt(
            normalized_only_match=False,
            similarity_score=0.9995,
            raw_similarity_score=0.3,
            status="probe_rejected",
        )
        self.assertTrue(probe_one.is_normalized_only_match(attempt))

    def test_diff_excerpt_truncation(self) -> None:
        diff = [
            {"expected_offset": 0, "actual_offset": 0, "expected": "nop", "actual": "nop", "exact_match": True},
        ]
        for i in range(5):
            diff.append({
                "expected_offset": 4 + i * 4, "actual_offset": 4 + i * 4,
                "expected": f"addiu a{i}, a{i}, 1", "actual": f"addiu a{i}, a{i}, 2",
                "exact_match": False,
            })
        lines = probe_one.render_diff_excerpt(diff, max_entries=2, already_truncated=False)
        shown = [line for line in lines if "expected `" in line]
        self.assertEqual(len(shown), 2)
        self.assertIn("... (diff truncated)", lines[-1])


class ExitCodeTests(unittest.TestCase):
    def test_probe_rejected_is_zero(self) -> None:
        self.assertEqual(probe_one.exit_code_for_attempt(_attempt(status="probe_rejected")), 0)

    def test_probe_match_is_zero(self) -> None:
        self.assertEqual(probe_one.exit_code_for_attempt(_attempt(status="probe_match")), 0)

    def test_accepted_is_zero(self) -> None:
        self.assertEqual(probe_one.exit_code_for_attempt(_attempt(status="accepted")), 0)

    def test_compile_failed_is_one(self) -> None:
        self.assertEqual(probe_one.exit_code_for_attempt(_attempt(status="compile_failed")), 1)

    def test_unknown_status_is_two(self) -> None:
        self.assertEqual(probe_one.exit_code_for_attempt(_attempt(status="probe_unavailable")), 2)


class MainTests(unittest.TestCase):
    def _run_main(self, argv: list[str], fake_subprocess) -> tuple[int, str, str]:
        out, err = io.StringIO(), io.StringIO()
        with mock.patch.object(probe_one, "run_probe_subprocess", fake_subprocess):
            with redirect_stdout(out), redirect_stderr(err):
                code = probe_one.main(argv)
        return code, out.getvalue(), err.getvalue()

    def _write_body(self, tmp: Path, text: str = VALID_BODY) -> Path:
        path = tmp / "body.c"
        path.write_text(text, encoding="utf-8")
        return path

    def test_body_shape_guard_short_circuits_without_probing(self) -> None:
        fake = mock.Mock(side_effect=AssertionError("should not be called"))
        with tempfile.TemporaryDirectory() as tmp_dir:
            tmp = Path(tmp_dir)
            body_path = self._write_body(tmp, "{ return; }")
            code, _out, err = self._run_main(
                ["--source", "disasm/src/X.c", "--function", "func_X", "--body", str(body_path)],
                fake,
            )
        self.assertEqual(code, 2)
        self.assertIn("func_X(", err)
        fake.assert_not_called()

    def test_rejected_probe_exits_zero_and_prints_report(self) -> None:
        result = {"attempts": [_attempt(status="probe_rejected", label="probe")]}
        fake = _stub_writes_result(result)
        with tempfile.TemporaryDirectory() as tmp_dir:
            tmp = Path(tmp_dir)
            body_path = self._write_body(tmp)
            code, out, _err = self._run_main(
                ["--source", "disasm/src/X.c", "--function", "func_X", "--body", str(body_path)],
                fake,
            )
        self.assertEqual(code, 0)
        self.assertIn("status: probe_rejected", out)
        self.assertEqual(len(fake.calls), 1)
        batch = fake.calls[0]["batch"]
        self.assertEqual(batch["source"], "disasm/src/X.c")
        self.assertEqual(batch["candidates"][0]["function"], "func_X")
        self.assertEqual(batch["candidates"][0]["label"], "probe")
        self.assertNotIn("declarations", batch)

    def test_compile_failed_exits_one(self) -> None:
        result = {"attempts": [_attempt(status="compile_failed", diagnostic="cfe: Error: bad")]}
        fake = _stub_writes_result(result)
        with tempfile.TemporaryDirectory() as tmp_dir:
            tmp = Path(tmp_dir)
            body_path = self._write_body(tmp)
            code, out, _err = self._run_main(
                ["--source", "disasm/src/X.c", "--function", "func_X", "--body", str(body_path)],
                fake,
            )
        self.assertEqual(code, 1)
        self.assertIn("compiler error", out)

    def test_normalized_only_match_flagged_loudly(self) -> None:
        result = {
            "attempts": [
                _attempt(
                    status="probe_rejected",
                    normalized_only_match=True,
                    similarity_score=0.9999,
                    raw_similarity_score=0.4,
                )
            ]
        }
        fake = _stub_writes_result(result)
        with tempfile.TemporaryDirectory() as tmp_dir:
            tmp = Path(tmp_dir)
            body_path = self._write_body(tmp)
            code, out, _err = self._run_main(
                ["--source", "disasm/src/X.c", "--function", "func_X", "--body", str(body_path)],
                fake,
            )
        self.assertEqual(code, 0)
        self.assertIn("NORMALIZED-ONLY MATCH", out)

    def test_preflight_failure_exits_two(self) -> None:
        fake = _stub_writes_result({}, returncode=2, stderr="fleet_probe: batch preflight failed:\n- bad")
        with tempfile.TemporaryDirectory() as tmp_dir:
            tmp = Path(tmp_dir)
            body_path = self._write_body(tmp)
            code, _out, err = self._run_main(
                ["--source", "disasm/src/X.c", "--function", "func_X", "--body", str(body_path)],
                fake,
            )
        self.assertEqual(code, 2)
        self.assertIn("preflight failed", err)

    def test_runner_internal_error_exits_two(self) -> None:
        fake = _stub_writes_result({"batch_status": "runner_internal_error"}, returncode=1)
        with tempfile.TemporaryDirectory() as tmp_dir:
            tmp = Path(tmp_dir)
            body_path = self._write_body(tmp)
            code, _out, err = self._run_main(
                ["--source", "disasm/src/X.c", "--function", "func_X", "--body", str(body_path)],
                fake,
            )
        self.assertEqual(code, 2)
        self.assertIn("runner internal error", err)

    def test_timeout_exits_two(self) -> None:
        def _fake(batch_path, result_path, *, repo_root, timeout):
            raise subprocess.TimeoutExpired(cmd="fleet_probe.py", timeout=timeout)

        with tempfile.TemporaryDirectory() as tmp_dir:
            tmp = Path(tmp_dir)
            body_path = self._write_body(tmp)
            code, _out, err = self._run_main(
                ["--source", "disasm/src/X.c", "--function", "func_X", "--body", str(body_path)],
                _fake,
            )
        self.assertEqual(code, 2)
        self.assertIn("timed out", err)

    def test_no_attempts_exits_two(self) -> None:
        fake = _stub_writes_result({"attempts": []})
        with tempfile.TemporaryDirectory() as tmp_dir:
            tmp = Path(tmp_dir)
            body_path = self._write_body(tmp)
            code, _out, err = self._run_main(
                ["--source", "disasm/src/X.c", "--function", "func_X", "--body", str(body_path)],
                fake,
            )
        self.assertEqual(code, 2)
        self.assertIn("no attempts", err)

    def test_stdin_body(self) -> None:
        result = {"attempts": [_attempt(status="probe_rejected")]}
        fake = _stub_writes_result(result)
        with mock.patch.object(probe_one, "run_probe_subprocess", fake):
            out, err = io.StringIO(), io.StringIO()
            with mock.patch.object(sys, "stdin", io.StringIO(VALID_BODY)):
                with redirect_stdout(out), redirect_stderr(err):
                    code = probe_one.main(
                        ["--source", "disasm/src/X.c", "--function", "func_X", "--body", "-"]
                    )
        self.assertEqual(code, 0)

    def test_declarations_file_merged_into_batch(self) -> None:
        result = {"attempts": [_attempt(status="probe_rejected")]}
        fake = _stub_writes_result(result)
        with tempfile.TemporaryDirectory() as tmp_dir:
            tmp = Path(tmp_dir)
            body_path = self._write_body(tmp)
            decl_path = tmp / "decls.h"
            decl_path.write_text("extern s32 D_X;\n", encoding="utf-8")
            code, _out, _err = self._run_main(
                [
                    "--source", "disasm/src/X.c", "--function", "func_X",
                    "--body", str(body_path), "--declarations", str(decl_path),
                    "--label", "custom-label",
                ],
                fake,
            )
        self.assertEqual(code, 0)
        batch = fake.calls[0]["batch"]
        self.assertEqual(batch["declarations"], "extern s32 D_X;\n")
        self.assertEqual(batch["candidates"][0]["label"], "custom-label")

    def test_json_output_written(self) -> None:
        result = {"attempts": [_attempt(status="probe_rejected")]}
        fake = _stub_writes_result(result)
        with tempfile.TemporaryDirectory() as tmp_dir:
            tmp = Path(tmp_dir)
            body_path = self._write_body(tmp)
            json_path = tmp / "out.json"
            code, out, _err = self._run_main(
                [
                    "--source", "disasm/src/X.c", "--function", "func_X",
                    "--body", str(body_path), "--json", str(json_path),
                ],
                fake,
            )
            self.assertEqual(code, 0)
            self.assertTrue(json_path.exists())
            written = json.loads(json_path.read_text(encoding="utf-8"))
            self.assertEqual(written["status"], "probe_rejected")
            self.assertIn(str(json_path), out)


if __name__ == "__main__":
    unittest.main()
