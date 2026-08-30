#!/usr/bin/env python3
"""Unit tests for tools/fleet_probe.py.

These tests never touch the real runner: ``try_pragma_compare.try_candidates_detailed``
is monkeypatched with a fake that records its arguments and returns a
synthetic ``attempts[]`` payload shaped like the real one.  Nothing here
compiles anything or reads the main checkout's disasm tree.
"""

from __future__ import annotations

import io
import json
import sys
import unittest
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import fleet_probe  # noqa: E402
import try_pragma_compare  # noqa: E402


_FLEET_SOURCE = (
    'void func_2(void) {}\n'
    '#pragma GLOBAL_ASM("asm/us/nonmatchings/s/func_1.s")\n'
)


def _fake_attempt(function: str, label: str, **overrides: object) -> dict[str, object]:
    row = {
        "function": function,
        "label": label,
        "status": "probe_rejected",
        "mismatch_kind": "immediate_drift",
        "similarity_score": 0.9,
        "raw_similarity_score": 0.8,
        "first_diff_offset": 12,
        "expected_instruction_text": "addiu a1, a1, IMM",
        "actual_instruction_text": "addiu a1, a1, IMM",
        "expected_size": 64,
        "actual_size": 64,
        "expected_tail_kind": "jr_nop",
        "link_verified": None,
        "diagnostic": None,
    }
    row.update(overrides)
    return row


class LoadBatchTests(unittest.TestCase):
    def test_json_batch_basic_fields(self) -> None:
        with mock.patch.object(fleet_probe, "REPO_ROOT", Path("/repo")):
            with _tmp_json({
                "source": "disasm/src/X.c",
                "declarations": "extern s32 D_X;\n",
                "candidates": [
                    {"function": "func_1", "label": "a:b:c", "body": "void func_1(void) {}"},
                ],
            }) as path:
                source, declarations, blocks, labels, companion_edits = fleet_probe.load_batch(
                    path, source_override=None, declarations_override=None
                )
        self.assertEqual(source, Path("/repo/disasm/src/X.c"))
        self.assertEqual(declarations, "extern s32 D_X;\n")
        self.assertEqual(blocks, [("func_1", "void func_1(void) {}")])
        self.assertEqual(labels, ["a:b:c"])
        self.assertIsNone(companion_edits)

    def test_json_batch_parses_companion_edits(self) -> None:
        edits = [{"function": "func_2", "old": "old", "new": "new"}]
        with _tmp_json({
            "source": "disasm/src/X.c",
            "companion_edits": edits,
            "candidates": [{"function": "func_1", "body": "void func_1(void) {}"}],
        }) as path:
            _source, _declarations, _blocks, _labels, companion_edits = fleet_probe.load_batch(
                path, source_override=None, declarations_override=None
            )
        self.assertEqual(companion_edits, edits)

    def test_json_batch_validates_companion_edits(self) -> None:
        invalid_payloads = [
            {"function": "func_2", "old": "old"},
            "not an object",
        ]
        for edit in invalid_payloads:
            with self.subTest(edit=edit):
                with _tmp_json({
                    "source": "disasm/src/X.c",
                    "companion_edits": [edit],
                    "candidates": [{"function": "func_1", "body": "x"}],
                }) as path:
                    with self.assertRaises(fleet_probe.InputError):
                        fleet_probe.load_batch(
                            path, source_override=None, declarations_override=None
                        )

    def test_directory_batch_keeps_declarations_and_has_no_companion_edits(self) -> None:
        with _tmp_dir() as directory:
            (directory / "candidate.c").write_text(
                "# function: func_1\nvoid func_1(void) {}\n"
            )
            _source, declarations, _blocks, _labels, companion_edits = fleet_probe.load_batch(
                directory,
                source_override="disasm/src/X.c",
                declarations_override="extern s32 D_X;\n",
            )
        self.assertEqual(declarations, "extern s32 D_X;\n")
        self.assertIsNone(companion_edits)

    def test_json_batch_requires_source_somewhere(self) -> None:
        with _tmp_json({"candidates": [{"function": "func_1", "body": "x"}]}) as path:
            with self.assertRaises(fleet_probe.InputError):
                fleet_probe.load_batch(path, source_override=None, declarations_override=None)

    def test_cli_source_override_wins(self) -> None:
        with mock.patch.object(fleet_probe, "REPO_ROOT", Path("/repo")):
            with _tmp_json({
                "source": "disasm/src/orig.c",
                "candidates": [{"function": "func_1", "body": "x"}],
            }) as path:
                source, _decl, _blocks, _labels, _companion_edits = fleet_probe.load_batch(
                    path, source_override="disasm/src/override.c", declarations_override=None
                )
        self.assertEqual(source, Path("/repo/disasm/src/override.c"))

    def test_missing_candidates_is_input_error(self) -> None:
        with _tmp_json({"source": "disasm/src/X.c"}) as path:
            with self.assertRaises(fleet_probe.InputError):
                fleet_probe.load_batch(path, source_override=None, declarations_override=None)

    def test_directory_batch_with_header(self) -> None:
        with _tmp_dir() as directory:
            (directory / "guard-return.c").write_text(
                "# function: func_8004A010\nvoid func_8004A010(s32 a) { return; }\n"
            )
            (directory / "assign-then-return.c").write_text(
                "# function: func_8004A010\ns32 func_8004A010(s32 a) { return a; }\n"
            )
            source, declarations, blocks, labels, companion_edits = fleet_probe.load_batch(
                directory, source_override="disasm/src/X.c", declarations_override=None
            )
        self.assertEqual(declarations, None)
        self.assertIsNone(companion_edits)
        self.assertEqual(labels, ["assign-then-return", "guard-return"])
        self.assertEqual({function for function, _ in blocks}, {"func_8004A010"})
        self.assertTrue(all("return" in body for _, body in blocks))

    def test_directory_batch_guesses_function_without_header(self) -> None:
        with _tmp_dir() as directory:
            (directory / "guess.c").write_text("void func_8004A010(s32 a) { return; }\n")
            _source, _decl, blocks, labels, _companion_edits = fleet_probe.load_batch(
                directory, source_override="disasm/src/X.c", declarations_override=None
            )
        self.assertEqual(blocks, [("func_8004A010", "void func_8004A010(s32 a) { return; }\n")])
        self.assertEqual(labels, ["guess"])

    def test_directory_batch_requires_source(self) -> None:
        with _tmp_dir() as directory:
            (directory / "a.c").write_text("# function: func_1\nvoid func_1(void) {}\n")
            with self.assertRaises(fleet_probe.InputError):
                fleet_probe.load_batch(directory, source_override=None, declarations_override=None)

    def test_directory_batch_ungessable_function_errors(self) -> None:
        with _tmp_dir() as directory:
            (directory / "a.c").write_text("this is not a function body\n")
            with self.assertRaises(fleet_probe.InputError):
                fleet_probe.load_batch(directory, source_override="disasm/src/X.c", declarations_override=None)


class FormatTableTests(unittest.TestCase):
    def test_table_has_header_and_one_row_per_attempt(self) -> None:
        attempts = [
            _fake_attempt("func_1", "family:shape:a"),
            _fake_attempt("func_1", "family:shape:b", status="accepted", mismatch_kind=None),
        ]
        table = fleet_probe.format_table(attempts)
        lines = table.splitlines()
        self.assertEqual(len(lines), 4)  # header, separator, 2 rows
        self.assertIn("FUNCTION", lines[0])
        self.assertIn("SIM", lines[0])
        self.assertIn("family:shape:a", lines[2])
        self.assertIn("accepted", lines[3])

    def test_table_handles_missing_fields(self) -> None:
        table = fleet_probe.format_table([{"function": "func_1", "status": "compile_failed"}])
        self.assertIn("func_1", table)
        self.assertIn("compile_failed", table)

    def test_table_exposes_link_futility_and_compact_diagnostic(self) -> None:
        table = fleet_probe.format_table(
            [
                _fake_attempt(
                    "func_1",
                    "compile",
                    prior_attempts=7,
                    link_verified=False,
                    link_mismatch="section_layout_drift",
                    futility="stuck: 15 attempts, best 0.81",
                    diagnostic="compiler error: bad type\nnext line",
                )
            ]
        )
        self.assertIn("PRIOR", table)
        self.assertIn("LINK", table)
        self.assertIn("FUTILITY", table)
        self.assertIn("DIAGNOSTIC", table)
        self.assertIn("7", table)
        self.assertIn("no:section_layout_drift", table)
        self.assertIn("stuck: 15 attempts, best 0.81", table)
        self.assertIn("compiler error: bad type next line", table)


class SummarizeTests(unittest.TestCase):
    def test_accepted_wins_over_everything(self) -> None:
        attempts = [
            _fake_attempt("func_1", "a", status="probe_rejected", similarity_score=0.5),
            _fake_attempt("func_1", "b", status="accepted"),
        ]
        summary = fleet_probe.summarize(attempts)
        self.assertIn("func_1: ACCEPTED via b", summary)

    def test_probe_match_without_gate(self) -> None:
        attempts = [_fake_attempt("func_1", "a", status="probe_match", link_verified=None)]
        summary = fleet_probe.summarize(attempts)
        self.assertIn("PROBE MATCH via a", summary)
        self.assertIn("--gate", summary)

    def test_register_tie_without_futility_is_advisory(self) -> None:
        attempts = [
            _fake_attempt(
                "func_1", "a",
                status="probe_rejected",
                mismatch_kind="register_allocation_only",
                similarity_score=0.995,
            )
        ]
        summary = fleet_probe.summarize(attempts)
        self.assertIn("possible register tie", summary)
        self.assertIn("advisory", summary)
        self.assertNotIn("register tie — stop", summary)

    def test_register_tie_stop_requires_runner_futility(self) -> None:
        attempts = [
            _fake_attempt(
                "func_1", "a",
                mismatch_kind="register_allocation_only",
                similarity_score=0.995,
                futility="register-tie: 6 prior attempts at >=0.99",
            )
        ]
        summary = fleet_probe.summarize(attempts)
        self.assertIn("register tie — stop", summary)
        self.assertNotIn("possible register tie", summary)

    def test_register_tie_futility_is_authoritative_for_best_other_than_tie(self) -> None:
        attempts = [
            _fake_attempt(
                "func_1", "tie-history",
                mismatch_kind="register_allocation_only",
                similarity_score=0.995,
                futility="register-tie: 6 prior attempts at >=0.99",
            ),
            _fake_attempt(
                "func_1", "best-current",
                mismatch_kind="immediate_drift",
                similarity_score=0.999,
                futility="register-tie: 6 prior attempts at >=0.99",
            ),
        ]
        summary = fleet_probe.summarize(attempts)
        self.assertIn("register tie — stop", summary)

    def test_no_register_tie_below_threshold(self) -> None:
        attempts = [
            _fake_attempt(
                "func_1", "a",
                status="probe_rejected",
                mismatch_kind="register_allocation_only",
                similarity_score=0.9,
            )
        ]
        summary = fleet_probe.summarize(attempts)
        self.assertNotIn("register tie", summary)

    def test_best_of_multiple_by_similarity(self) -> None:
        attempts = [
            _fake_attempt("func_1", "low", status="probe_rejected", similarity_score=0.5),
            _fake_attempt("func_1", "high", status="probe_rejected", similarity_score=0.97),
        ]
        summary = fleet_probe.summarize(attempts)
        self.assertIn("best=high", summary)

    def test_multiple_functions_each_get_a_line(self) -> None:
        attempts = [
            _fake_attempt("func_1", "a", status="accepted"),
            _fake_attempt("func_2", "b", status="probe_rejected", similarity_score=0.6),
        ]
        summary = fleet_probe.summarize(attempts)
        lines = summary.splitlines()
        self.assertEqual(len(lines), 2)
        self.assertTrue(lines[0].startswith("func_1:"))
        self.assertTrue(lines[1].startswith("func_2:"))

    def test_no_scored_attempts(self) -> None:
        attempts = [{"function": "func_1", "status": "compile_failed"}]
        summary = fleet_probe.summarize(attempts)
        self.assertIn("no scored attempts", summary)

    def test_summary_exposes_futility(self) -> None:
        attempts = [_fake_attempt("func_1", "a", futility="register-tie: six prior attempts")]
        summary = fleet_probe.summarize(attempts)
        self.assertIn("futility=register-tie: six prior attempts", summary)


class RunAndMainTests(unittest.TestCase):
    def test_run_calls_try_candidates_detailed_with_expected_args(self) -> None:
        captured: dict[str, object] = {}

        def fake_try_candidates_detailed(
            source_path,
            blocks,
            *,
            probe_workers=None,
            labels=None,
            gate=True,
            declarations=None,
            families=None,
            companion_edits=None,
        ):
            captured.update(
                source_path=source_path, blocks=blocks, probe_workers=probe_workers,
                labels=labels, gate=gate, declarations=declarations,
                companion_edits=companion_edits,
            )
            return {"status": 0, "accepted": [], "attempts": [], "batch_status": "probe_only", "gate": gate}

        with _tmp_json({
            "source": "x.c",
            "candidates": [{"function": "func_1", "label": "l", "body": "void func_1(void) {}"}],
        }) as path:
            fake_source = path.parent / "x.c"
            fake_source.write_text(_FLEET_SOURCE)
            with mock.patch.object(try_pragma_compare, "try_candidates_detailed", fake_try_candidates_detailed):
                with mock.patch.object(fleet_probe, "REPO_ROOT", path.parent):
                    result = fleet_probe.run(
                        path, source_override=None, declarations_override=None, gate=False, probe_workers=3
                    )

        self.assertEqual(result["batch_status"], "probe_only")
        self.assertEqual(captured["blocks"], [("func_1", "void func_1(void) {}")])
        self.assertEqual(captured["labels"], ["l"])
        self.assertEqual(captured["probe_workers"], 3)
        self.assertFalse(captured["gate"])
        self.assertIsNone(captured["companion_edits"])

    def test_run_forwards_companion_edits(self) -> None:
        captured: dict[str, object] = {}

        def fake_try_candidates_detailed(source_path, blocks, **kwargs):
            captured.update(kwargs)
            return {"status": 1, "accepted": [], "attempts": [], "batch_status": "probe_only", "gate": False}

        edits = [{
            "function": "func_2",
            "old": "void func_2(void) {}",
            "new": "void func_2(void) { (void)0; }",
        }]
        with _tmp_json({
            "source": "x.c",
            "companion_edits": edits,
            "candidates": [{"function": "func_1", "body": "void func_1(void) {}"}],
        }) as path:
            (path.parent / "x.c").write_text(_FLEET_SOURCE)
            with mock.patch.object(try_pragma_compare, "try_candidates_detailed", fake_try_candidates_detailed):
                with mock.patch.object(fleet_probe, "REPO_ROOT", path.parent):
                    fleet_probe.run(
                        path, source_override=None, declarations_override=None, gate=False, probe_workers=None
                    )
        self.assertEqual(captured["companion_edits"], edits)

    def test_run_rejects_missing_source_file(self) -> None:
        with _tmp_json({
            "source": "does/not/exist.c",
            "candidates": [{"function": "func_1", "body": "x"}],
        }) as path:
            with self.assertRaises(fleet_probe.InputError):
                fleet_probe.run(path, source_override=None, declarations_override=None, gate=False, probe_workers=None)

    def test_main_prints_table_and_verdict(self) -> None:
        def fake_try_candidates_detailed(source_path, blocks, **kwargs):
            return {
                "status": 1,
                "accepted": [],
                "attempts": [
                    _fake_attempt(
                        "func_1",
                        "a",
                        status="probe_rejected",
                        similarity_score=0.4,
                        link_verified=False,
                        futility="stuck: 15 attempts, best 0.81",
                        diagnostic="compiler error: bad type\nnext line",
                    )
                ],
                "batch_status": "probe_only",
                "gate": False,
                "futility_summary": {"func_1": "stuck: 15 attempts, best 0.81"},
            }

        with _tmp_json({
            "source": "x.c",
            "candidates": [{"function": "func_1", "label": "a", "body": "void func_1(void) {}"}],
        }) as path:
            (path.parent / "x.c").write_text(_FLEET_SOURCE)
            with mock.patch.object(try_pragma_compare, "try_candidates_detailed", fake_try_candidates_detailed):
                with mock.patch.object(fleet_probe, "REPO_ROOT", path.parent):
                    output = io.StringIO()
                    with mock.patch("sys.stdout", output):
                        exit_code = fleet_probe.main([str(path)])
        self.assertEqual(exit_code, 0)
        rendered = output.getvalue()
        self.assertIn("LINK", rendered)
        self.assertIn("no", rendered)
        self.assertIn("compiler error: bad type next line", rendered)
        self.assertIn("futility_summary:", rendered)

    def test_main_reports_input_errors_on_stderr(self) -> None:
        with _tmp_json({"source": "x.c"}) as path:
            with mock.patch("sys.stderr"):
                exit_code = fleet_probe.main([str(path)])
        self.assertEqual(exit_code, 2)

    def test_main_keeps_probe_only_rejections_nonfatal(self) -> None:
        def fake_try_candidates_detailed(source_path, blocks, **kwargs):
            return {
                "status": 1,
                "accepted": [],
                "attempts": [_fake_attempt("func_1", "a", similarity_score=0.4)],
                "batch_status": "probe_only",
                "gate": False,
            }

        with _tmp_json({
            "source": "x.c",
            "candidates": [{"function": "func_1", "body": "void func_1(void) {}"}],
        }) as path:
            (path.parent / "x.c").write_text(_FLEET_SOURCE)
            with mock.patch.object(try_pragma_compare, "try_candidates_detailed", fake_try_candidates_detailed):
                with mock.patch.object(fleet_probe, "REPO_ROOT", path.parent):
                    exit_code = fleet_probe.main([str(path)])
        self.assertEqual(exit_code, 0)

    def test_main_fails_on_runner_internal_error(self) -> None:
        def fake_try_candidates_detailed(source_path, blocks, **kwargs):
            return {
                "status": 2,
                "accepted": [],
                "attempts": [],
                "batch_status": "runner_internal_error",
                "gate": False,
            }

        with _tmp_json({
            "source": "x.c",
            "candidates": [{"function": "func_1", "body": "void func_1(void) {}"}],
        }) as path:
            (path.parent / "x.c").write_text(_FLEET_SOURCE)
            with mock.patch.object(try_pragma_compare, "try_candidates_detailed", fake_try_candidates_detailed):
                with mock.patch.object(fleet_probe, "REPO_ROOT", path.parent):
                    exit_code = fleet_probe.main([str(path)])
        self.assertEqual(exit_code, 1)


import contextlib
import tempfile


@contextlib.contextmanager
def _tmp_json(payload: dict[str, object]):
    with tempfile.TemporaryDirectory() as tmp:
        path = Path(tmp) / "batch.json"
        path.write_text(json.dumps(payload))
        yield path


@contextlib.contextmanager
def _tmp_dir():
    with tempfile.TemporaryDirectory() as tmp:
        yield Path(tmp)


if __name__ == "__main__":
    unittest.main()
