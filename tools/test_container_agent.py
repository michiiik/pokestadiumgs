#!/usr/bin/env python3
"""Unit tests for tools/container_agent.py.

Every subprocess-shelling function is stubbed: ``invoke_generator``,
``invoke_probe``, ``invoke_permuter``/``poll_permuter``/``run_permuter``,
``file_brief_text``, ``owner_asm_text``, ``discover_owners``'s
``pragma_targets.py`` call, and the ``git diff`` inside ``capture_accepted``
(patched via ``container_agent.subprocess.run``, which none of the stubbed
wrapper functions touch once they are replaced outright). Nothing here
shells out to a real generator, probe, permuter, or git.
"""

from __future__ import annotations

import json
import os
import shlex
import signal
import subprocess
import sys
import tempfile
import threading
import time
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import container_agent  # noqa: E402


# ---------------------------------------------------------------------------
# Shared stub helpers
# ---------------------------------------------------------------------------

def _extract_path_arg(command: str, flag: str) -> Path:
    """Pull the path following ``flag`` out of a rendered generator command."""
    tokens = shlex.split(command)
    return Path(tokens[tokens.index(flag) + 1])


def make_invoke_generator(batch_for_iteration):
    """Fake ``invoke_generator`` that writes ``batch_for_iteration(n)`` (a
    dict, or ``None`` to simulate invalid JSON) to the command's ``--batch``
    path and returns a successful CompletedProcess-alike."""
    calls = {"n": 0}

    def _stub(command, *, cwd, timeout):
        batch_path = _extract_path_arg(command, "--batch")
        batch = batch_for_iteration(calls["n"])
        calls["n"] += 1
        batch_path.parent.mkdir(parents=True, exist_ok=True)
        if batch is not None:
            container_agent.save_json(batch_path, batch)
        else:
            batch_path.write_text("not valid json", encoding="utf-8")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    return _stub


def make_invoke_probe(result_for_call):
    """Fake ``invoke_probe`` that writes ``result_for_call(n, batch)`` (a
    dict, or ``None`` to simulate a missing result file) to ``result_path``."""
    calls = {"n": 0}

    def _stub(repo_dir, batch_path, result_path, *, timeout):
        batch = container_agent.load_json(batch_path)
        result = result_for_call(calls["n"], batch)
        calls["n"] += 1
        if result is not None:
            container_agent.save_json(result_path, result)
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    return _stub


def _git_diff_stub():
    return mock.patch.object(
        container_agent.subprocess, "run",
        return_value=SimpleNamespace(returncode=0, stdout="diff --git a/x b/x\n", stderr=""),
    )


# ---------------------------------------------------------------------------
# render_generator_command
# ---------------------------------------------------------------------------

class RenderGeneratorCommandTests(unittest.TestCase):
    def test_substitutes_prompt_and_batch_with_quoted_paths(self) -> None:
        template = "mytool --prompt {prompt} --batch {batch} --flag"
        prompt_path = Path("/tmp/some dir/prompt.txt")
        batch_path = Path("/tmp/out dir/batch.json")

        command = container_agent.render_generator_command(template, prompt_path, batch_path)

        self.assertIn(shlex.quote(str(prompt_path)), command)
        self.assertIn(shlex.quote(str(batch_path)), command)
        self.assertNotIn("{prompt}", command)
        self.assertNotIn("{batch}", command)


# ---------------------------------------------------------------------------
# discover_owners / discover_owners_fallback
# ---------------------------------------------------------------------------

class DiscoverOwnersFallbackTests(unittest.TestCase):
    def test_regex_scan_finds_both_pragmas_in_order(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp)
            source_rel = "disasm/src/X.c"
            source_path = repo_dir / source_rel
            source_path.parent.mkdir(parents=True)
            source_path.write_text(
                '#pragma GLOBAL_ASM("asm/nonmatchings/X/func_a.s")\n'
                "void func_a(void);\n\n"
                '#pragma GLOBAL_ASM("asm/nonmatchings/X/func_b.s")\n'
                "void func_b(void);\n",
                encoding="utf-8",
            )
            owners = container_agent.discover_owners_fallback(repo_dir, source_rel)
        self.assertEqual(owners, ["func_a", "func_b"])

    def test_missing_source_returns_empty_list(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            owners = container_agent.discover_owners_fallback(Path(tmp), "disasm/src/missing.c")
        self.assertEqual(owners, [])


class DiscoverOwnersTests(unittest.TestCase):
    def test_uses_pragma_targets_json_when_available(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp)
            fake_stdout = json.dumps({"targets": [{"function": "func_a"}, {"function": "func_b"}]})
            with mock.patch.object(
                container_agent.subprocess, "run",
                return_value=SimpleNamespace(returncode=0, stdout=fake_stdout, stderr=""),
            ):
                owners = container_agent.discover_owners(repo_dir, "disasm/src/X.c")
        self.assertEqual(owners, ["func_a", "func_b"])

    def test_falls_back_to_regex_scan_when_pragma_targets_fails(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp)
            source_rel = "disasm/src/X.c"
            source_path = repo_dir / source_rel
            source_path.parent.mkdir(parents=True)
            source_path.write_text(
                '#pragma GLOBAL_ASM("asm/nonmatchings/X/func_a.s")\nvoid func_a(void);\n',
                encoding="utf-8",
            )
            with mock.patch.object(
                container_agent.subprocess, "run",
                return_value=SimpleNamespace(returncode=1, stdout="", stderr="boom"),
            ):
                owners = container_agent.discover_owners(repo_dir, source_rel)
        self.assertEqual(owners, ["func_a"])

    def test_command_never_passes_the_nonexistent_json_flag(self) -> None:
        # `pragma_targets.py targets` has no `--json` flag (see its own
        # --help): passing one is an argparse error (exit 2) that used to
        # make this function silently fall back to the regex scan on every
        # single call, permanently losing size ordering/--max-instructions.
        # The command already prints JSON unconditionally.
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp)
            fake_stdout = json.dumps({"targets": [{"function": "func_a"}]})
            with mock.patch.object(
                container_agent.subprocess, "run",
                return_value=SimpleNamespace(returncode=0, stdout=fake_stdout, stderr=""),
            ) as run_mock:
                container_agent.discover_owners(repo_dir, "disasm/src/X.c")
            command = run_mock.call_args[0][0]
        self.assertNotIn("--json", command)

    def test_parses_a_real_shaped_targets_payload(self) -> None:
        # The exact shape `list_targets()`/`main()` in tools/pragma_targets.py
        # print for `targets` (trimmed to two rows) -- captured from a real
        # `python3 tools/pragma_targets.py targets --source disasm/src/14640.c
        # --limit 5` invocation, not a hand-simplified fixture.
        real_shaped_stdout = json.dumps({
            "matched": 60,
            "family_counts": {"state_field_access": 9, "call_sequence": 36},
            "targets": [
                {
                    "function": "func_8001644C",
                    "source": "disasm/src/14640.c",
                    "asm": "disasm/asm/us/nonmatchings/14640/func_8001644C.s",
                    "family": "state_field_access",
                    "confidence": 0.78,
                    "instructions": 12,
                    "branches": 1,
                    "loops": False,
                    "calls": [],
                    "globals": ["D_8011BE90", "D_8011C990"],
                    "jump_tables": [],
                    "notes": ["global field access with explicit stores"],
                    "jump_table_ready": False,
                    "jump_table_unready": False,
                    "jump_table_status": "not_applicable",
                    "prior_attempts": 0,
                    "best_similarity": None,
                    "best_mismatch_kind": None,
                    "best_raw_similarity": None,
                    "last_attempt": None,
                    "hardness": "fresh",
                },
                {
                    "function": "func_8001874C",
                    "source": "disasm/src/14640.c",
                    "instructions": 12,
                    "family": "call_sequence",
                },
            ],
            "truncated": False,
        })
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp)
            with mock.patch.object(
                container_agent.subprocess, "run",
                return_value=SimpleNamespace(returncode=0, stdout=real_shaped_stdout, stderr=""),
            ):
                owners = container_agent.discover_owners(repo_dir, "disasm/src/14640.c")
        self.assertEqual(owners, ["func_8001644C", "func_8001874C"])

    def test_logs_loudly_on_nonzero_exit(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp)
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")
            with mock.patch.object(
                container_agent.subprocess, "run",
                return_value=SimpleNamespace(returncode=2, stdout="", stderr="unrecognized arguments: --json"),
            ):
                container_agent.discover_owners(repo_dir, "disasm/src/X.c", logger=logger)
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
        self.assertIn("falling back to a regex scan", log_text)
        self.assertIn("exited 2", log_text)

    def test_logs_loudly_on_no_rows(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp)
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")
            fake_stdout = json.dumps({"targets": []})
            with mock.patch.object(
                container_agent.subprocess, "run",
                return_value=SimpleNamespace(returncode=0, stdout=fake_stdout, stderr=""),
            ):
                container_agent.discover_owners(repo_dir, "disasm/src/X.c", logger=logger)
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
        self.assertIn("falling back to a regex scan", log_text)
        self.assertIn("no remaining owners", log_text)


# ---------------------------------------------------------------------------
# extract_installed_function
# ---------------------------------------------------------------------------

class ExtractInstalledFunctionTests(unittest.TestCase):
    def test_finds_body_with_nested_braces(self) -> None:
        source = (
            "int helper(void) { return 0; }\n\n"
            "void func_1(void) {\n"
            "    if (helper()) {\n"
            "        do_thing();\n"
            "    }\n"
            "    return;\n"
            "}\n\n"
            "void other(void) {}\n"
        )
        body = container_agent.extract_installed_function(source, "func_1")
        self.assertIsNotNone(body)
        self.assertTrue(body.startswith("void func_1(void) {"))
        self.assertIn("do_thing();", body)
        self.assertTrue(body.rstrip("\n").endswith("}"))
        self.assertNotIn("other", body)

    def test_returns_none_when_function_absent(self) -> None:
        source = "void other(void) {}\n"
        self.assertIsNone(container_agent.extract_installed_function(source, "func_missing"))


# ---------------------------------------------------------------------------
# capture_accepted
# ---------------------------------------------------------------------------

class CaptureAcceptedTests(unittest.TestCase):
    def test_multi_function_body_stored_verbatim_from_batch(self) -> None:
        # The bug this guards against: extract_installed_function only
        # returns the FIRST function definition in the installed source, so
        # a candidate body carrying padding helpers after the main function
        # (a real accepted shape) would be silently truncated if
        # capture_accepted re-derived the body from source instead of using
        # the batch's own text verbatim.
        multi_body = (
            "f32 func_860004C8(void *arg0, void *arg1) {\n"
            "    u8 value[0x18];\n"
            "    func_87C00160(value, arg1, arg0);\n"
            "    return (f32)func_87C00D14(*(f64 *)value, *(f64 *)(value + 0x10));\n"
            "}\n"
            "void func_860004C8_padding(void) {}\n"
            "void func_860004C8_padding2(void) {}\n"
        )
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            source_rel = "disasm/src/X.c"
            source_path = repo_dir / source_rel
            source_path.parent.mkdir(parents=True)
            # The installed source only shows the first definition -- a
            # correct capture must NOT rely on re-extracting from this text.
            source_path.write_text(multi_body, encoding="utf-8")
            out_dir = Path(tmp) / "out"
            owner = "func_860004C8"
            function = "func_860004C8"
            batch = {
                "source": source_rel,
                "declarations": "",
                "companion_edits": [],
                "candidates": [{"function": function, "label": "cast:padding:h", "body": multi_body}],
            }
            accepted_attempt = {
                "label": "cast:padding:h", "status": "accepted",
                "similarity_score": 1.0, "raw_similarity_score": 0.98, "link_verified": True,
            }
            logger = container_agent.Logger(out_dir / "log.txt")

            with _git_diff_stub():
                container_agent.capture_accepted(
                    repo_dir, out_dir, owner, function, batch, accepted_attempt,
                    source_rel_fallback=source_rel, logger=logger,
                )

            data = json.loads((out_dir / "accepted" / f"{function}.json").read_text(encoding="utf-8"))
            self.assertEqual(data["candidates"][0]["body"], multi_body)
            self.assertIn("func_860004C8_padding2", data["candidates"][0]["body"])
            self.assertEqual(data["captured_from"], "batch")
            self.assertEqual(data["label"], "cast:padding:h")
            self.assertEqual(
                data["probe_result"],
                {"similarity": 1.0, "raw": 0.98, "link_verified": True},
            )
            log_path = out_dir / "log.txt"
            log_text = log_path.read_text(encoding="utf-8") if log_path.exists() else ""
            self.assertNotIn("WARNING", log_text)

    def test_falls_back_to_source_extraction_when_label_missing(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            source_rel = "disasm/src/X.c"
            source_path = repo_dir / source_rel
            source_path.parent.mkdir(parents=True)
            source_path.write_text("void func_1(void) {\n    return;\n}\n", encoding="utf-8")
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            function = "func_1"
            batch = {
                "source": source_rel,
                "declarations": "",
                "companion_edits": [],
                # No candidate carries the accepted label -- forces fallback.
                "candidates": [{"function": function, "label": "other:label", "body": "void func_1(void) { return; }"}],
            }
            accepted_attempt = {
                "label": "label:not:in:batch", "status": "accepted",
                "similarity_score": 1.0, "raw_similarity_score": 1.0, "link_verified": True,
            }
            logger = container_agent.Logger(out_dir / "log.txt")

            with _git_diff_stub():
                container_agent.capture_accepted(
                    repo_dir, out_dir, owner, function, batch, accepted_attempt,
                    source_rel_fallback=source_rel, logger=logger,
                )

            data = json.loads((out_dir / "accepted" / f"{function}.json").read_text(encoding="utf-8"))
            self.assertEqual(data["candidates"][0]["body"], "void func_1(void) {\n    return;\n}\n")
            self.assertEqual(data["captured_from"], "source")
            self.assertEqual(data["label"], "label:not:in:batch")
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
            self.assertIn("WARNING", log_text)
            self.assertIn("label:not:in:batch", log_text)


# ---------------------------------------------------------------------------
# run_permuter (invoke_permuter / poll_permuter stubbed directly)
# ---------------------------------------------------------------------------

class RunPermuterTests(unittest.TestCase):
    def test_writes_inputs_launches_and_polls(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")
            fake_process = mock.Mock()
            poll_result = {
                "timed_out": False,
                "outputs": [{"score": 0, "code": "void func_1(void) {}"}],
                "best": {"score": 0, "code": "void func_1(void) {}"},
            }
            with mock.patch.object(
                container_agent, "invoke_permuter", return_value=fake_process
            ) as invoke_mock, mock.patch.object(
                container_agent, "poll_permuter", return_value=poll_result
            ) as poll_mock:
                result = container_agent.run_permuter(
                    repo_dir, out_dir, "func_1", 0, "void func_1(void) {}", "extern int g;",
                    permuter_seconds=30.0, logger=logger,
                )
            invoke_mock.assert_called_once()
            poll_mock.assert_called_once()
            self.assertEqual(result["best"]["score"], 0)
            candidate_path = out_dir / "tmp" / "permuter" / "func_1_iter0_candidate.c"
            declarations_path = out_dir / "tmp" / "permuter" / "func_1_iter0_declarations.h"
            self.assertEqual(candidate_path.read_text(encoding="utf-8"), "void func_1(void) {}")
            self.assertEqual(declarations_path.read_text(encoding="utf-8"), "extern int g;")

    def test_quick_zero_output_finish_logs_warning_with_log_tail(self) -> None:
        # Real-run repro: base.c fails to compile (a redeclaration, here),
        # the permuter process exits almost immediately with zero outputs,
        # and the one-line summary alone ("outputs=0") gives no hint why.
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")
            work_dir = Path(tmp) / "disasm" / "build" / "permuter" / "func_1-abc123"
            work_dir.mkdir(parents=True)
            (work_dir / "permuter.log").write_text(
                "irrelevant setup line 1\nirrelevant setup line 2\n"
                "line 1\nline 2\nline 3\n"
                "cfe: Error: line 2130: redeclaration of 'func_1'\n"
                "Unable to compile base.c\n",
                encoding="utf-8",
            )
            fake_process = mock.Mock()
            poll_result = {"timed_out": False, "outputs": [], "best": None, "work_dir": str(work_dir)}
            with mock.patch.object(
                container_agent, "invoke_permuter", return_value=fake_process
            ), mock.patch.object(
                container_agent, "poll_permuter", return_value=poll_result
            ):
                container_agent.run_permuter(
                    repo_dir, out_dir, "func_1", 0, "void func_1(void) {}", "extern int g;",
                    permuter_seconds=30.0, logger=logger,
                )
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
            self.assertIn("WARNING", log_text)
            self.assertIn("zero outputs", log_text)
            self.assertIn("cfe: Error: line 2130: redeclaration of 'func_1'", log_text)
            self.assertIn("Unable to compile base.c", log_text)
            self.assertNotIn("irrelevant setup line", log_text)  # only the last 5 lines are included

    def test_slow_zero_output_finish_does_not_warn(self) -> None:
        # A run that actually used its whole budget searching (rather than
        # dying immediately in the compile step) is not a failure signal.
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")
            fake_process = mock.Mock()
            poll_result = {"timed_out": True, "outputs": [], "best": None, "work_dir": None}
            with mock.patch.object(
                container_agent, "invoke_permuter", return_value=fake_process
            ), mock.patch.object(
                container_agent, "poll_permuter", return_value=poll_result
            ):
                container_agent.run_permuter(
                    repo_dir, out_dir, "func_1", 0, "void func_1(void) {}", None,
                    permuter_seconds=30.0, logger=logger,
                )
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
            self.assertNotIn("WARNING", log_text)


# ---------------------------------------------------------------------------
# run_iteration
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# _build_feedback: distilling fleet_probe's rich per-attempt assembly_diff
# (see a real result at
# gs-container-runs/fragment47-codex-luna-run3/results/func_86000020_iter1.json)
# into a compact, prompt-ready dict.
# ---------------------------------------------------------------------------

class BuildFeedbackTests(unittest.TestCase):
    def _diff_entry(self, offset, expected, actual, *, exact_match=False):
        return {
            "expected_instruction": offset // 4,
            "actual_instruction": offset // 4,
            "expected_offset": offset,
            "actual_offset": offset,
            "expected": expected,
            "actual": actual,
            "expected_normalized": expected,
            "actual_normalized": actual,
            "normalized_match": exact_match,
            "exact_match": exact_match,
        }

    def test_passthrough_fields_and_diff_excerpt_with_context_line(self) -> None:
        attempt = {
            "expected_size": 336,
            "actual_size": 340,
            "expected_instruction_count": 84,
            "actual_instruction_count": 85,
            "first_diff_offset": 3,
            "expected_instruction_text": "addiu $sp, $sp, -144",
            "actual_instruction_text": "addiu $sp, $sp, -152",
            "mismatch_kind": "operand_or_scheduling_drift",
            "futility": None,
            "register_only_similarity_score": 0.5059,
            "repeated_drift": None,
            "expected_tail_kind": "normal_return",
            "actual_tail_kind": "normal_return",
            "assembly_diff": [
                self._diff_entry(0, "addiu\tsp,sp,-144", "addiu\tsp,sp,-144", exact_match=True),
                self._diff_entry(4, "sw\tra,20(sp)", "sdc1\t$f20,24(sp)"),
                self._diff_entry(8, "sw\ta0,144(sp)", "sw\ts0,32(sp)"),
            ],
        }

        feedback = container_agent._build_feedback(attempt)

        self.assertEqual(feedback["expected_size"], 336)
        self.assertEqual(feedback["actual_size"], 340)
        self.assertEqual(feedback["expected_instruction_count"], 84)
        self.assertEqual(feedback["actual_instruction_count"], 85)
        self.assertEqual(feedback["first_diff_offset"], 3)
        self.assertEqual(feedback["expected_instruction_text"], "addiu $sp, $sp, -144")
        self.assertEqual(feedback["actual_instruction_text"], "addiu $sp, $sp, -152")
        self.assertEqual(feedback["mismatch_kind"], "operand_or_scheduling_drift")
        self.assertEqual(feedback["register_only_similarity_score"], 0.5059)
        self.assertEqual(feedback["expected_tail_kind"], "normal_return")
        self.assertEqual(feedback["actual_tail_kind"], "normal_return")

        excerpt = feedback["diff_excerpt"]
        lines = excerpt.splitlines()
        # One line of exact-match context precedes the first mismatch.
        self.assertIn("@0: addiu\tsp,sp,-144  (match)", lines[0])
        self.assertIn("@4: expected `sw\tra,20(sp)`  actual `sdc1\t$f20,24(sp)`", lines[1])
        self.assertIn("@8: expected `sw\ta0,144(sp)`  actual `sw\ts0,32(sp)`", lines[2])
        self.assertFalse(feedback["diff_excerpt_truncated"])

    def test_no_assembly_diff_omits_excerpt(self) -> None:
        feedback = container_agent._build_feedback({"mismatch_kind": "immediate_drift"})
        self.assertNotIn("diff_excerpt", feedback)
        self.assertEqual(feedback["mismatch_kind"], "immediate_drift")

    def test_none_fields_are_not_copied(self) -> None:
        feedback = container_agent._build_feedback({"expected_size": 100, "actual_size": None})
        self.assertEqual(feedback["expected_size"], 100)
        self.assertNotIn("actual_size", feedback)

    def test_entry_count_cap_marks_truncated(self) -> None:
        diff = [self._diff_entry(i * 4, f"exp{i}", f"act{i}") for i in range(60)]
        feedback = container_agent._build_feedback({"assembly_diff": diff})

        excerpt = feedback["diff_excerpt"]
        self.assertTrue(feedback["diff_excerpt_truncated"])
        self.assertIn("truncated", excerpt)
        shown = [ln for ln in excerpt.splitlines() if ln.strip().startswith("@")]
        self.assertEqual(len(shown), container_agent.DIFF_EXCERPT_MAX_ENTRIES)

    def test_byte_cap_marks_truncated_before_entry_cap(self) -> None:
        # Ten entries whose lines are individually large enough that the
        # ~3 KB budget runs out well before the 40-entry cap does.
        diff = [
            self._diff_entry(i * 4, "x" * 500, "y" * 500)
            for i in range(10)
        ]
        feedback = container_agent._build_feedback({"assembly_diff": diff})

        self.assertTrue(feedback["diff_excerpt_truncated"])
        self.assertLessEqual(len(feedback["diff_excerpt"].encode("utf-8")), container_agent.DIFF_EXCERPT_MAX_BYTES + 200)

    def test_source_truncated_flag_propagates(self) -> None:
        feedback = container_agent._build_feedback({
            "assembly_diff": [self._diff_entry(0, "a", "b")],
            "assembly_diff_truncated": True,
        })
        self.assertTrue(feedback["diff_excerpt_truncated"])


class RunIterationTests(unittest.TestCase):
    def _run(
        self, out_dir, repo_dir, owner, batch, result, owner_state, *,
        iteration=0, permuter_seconds=0.0, permuter_jobs=None,
    ):
        logger = container_agent.Logger(out_dir / "log.txt")
        batch_path = out_dir / "batches" / f"{owner}_iter{iteration}.json"
        container_agent.save_json(batch_path, batch)
        if permuter_jobs is None:
            permuter_jobs = []

        def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
            if result is not None:
                container_agent.save_json(result_path, result)
            return SimpleNamespace(returncode=0, stdout="", stderr="")

        try:
            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe):
                return container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=iteration, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=permuter_seconds, logger=logger,
                    permuter_jobs=permuter_jobs,
                )
        finally:
            # A triggered permuter job runs in a background thread (Part D);
            # join it before the caller's tempdir goes away, or a real,
            # unmocked run_permuter/invoke_permuter can still be reading/
            # writing under it when rmtree runs.
            for job in permuter_jobs:
                job.thread.join(timeout=5.0)

    def test_accepted_result_captures_declarations_and_companion_edits(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            source_path = repo_dir / "disasm" / "src" / "X.c"
            source_path.parent.mkdir(parents=True)
            source_path.write_text("void func_1(void) {\n    return;\n}\n", encoding="utf-8")
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            batch = {
                "source": "disasm/src/X.c",
                "declarations": "extern int g;",
                "companion_edits": [{"function": "func_2", "old": "a", "new": "b"}],
                "candidates": [{"function": owner, "label": "fam:shape:h", "body": "void func_1(void) { return; }"}],
            }
            result = {
                "batch_status": "accepted",
                "accepted": [owner],
                "attempts": [{"function": owner, "label": "fam:shape:h", "status": "accepted", "similarity_score": 1.0}],
            }
            with _git_diff_stub():
                status = self._run(out_dir, repo_dir, owner, batch, result, owner_state)

            self.assertEqual(status, "accepted")
            accepted_path = out_dir / "accepted" / f"{owner}.json"
            self.assertTrue(accepted_path.exists())
            data = json.loads(accepted_path.read_text(encoding="utf-8"))
            self.assertEqual(data["declarations"], "extern int g;")
            self.assertEqual(data["companion_edits"], [{"function": "func_2", "old": "a", "new": "b"}])
            self.assertEqual(data["candidates"][0]["function"], owner)
            self.assertEqual(data["candidates"][0]["body"], "void func_1(void) { return; }")
            self.assertEqual(data["captured_from"], "batch")
            self.assertEqual(data["label"], "fam:shape:h")
            self.assertEqual(data["probe_result"]["similarity"], 1.0)
            self.assertEqual(owner_state["best_similarity"], 1.0)
            self.assertEqual(owner_state["plateau_count"], 0)

    def test_improvement_resets_plateau_no_improvement_increments(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            owner_state["plateau_count"] = 3
            owner_state["best_similarity"] = 0.5
            owner_state["best_effective_similarity"] = 0.5

            batch = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "a", "body": "body_a"}]}
            low_result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{"function": owner, "label": "a", "status": "rejected", "similarity_score": 0.3}],
            }
            self._run(out_dir, repo_dir, owner, batch, low_result, owner_state, iteration=0)
            self.assertEqual(owner_state["plateau_count"], 4)
            self.assertEqual(owner_state["best_similarity"], 0.5)

            # A distinct body/label: with tried-body dedup filtering (issue:
            # dropped-batches-preflight-rejection), resending the same body
            # from iteration 0 would be dropped before ever reaching the
            # probe, which would defeat this test's actual point (that a
            # *result* improvement resets the plateau counter).
            batch2 = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "a2", "body": "body_a2"}]}
            high_result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{"function": owner, "label": "a2", "status": "rejected", "similarity_score": 0.9}],
            }
            self._run(out_dir, repo_dir, owner, batch2, high_result, owner_state, iteration=1)
            self.assertEqual(owner_state["best_similarity"], 0.9)
            self.assertEqual(owner_state["plateau_count"], 0)

    def test_best_candidates_deduped_by_label_and_capped(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()

            batch0 = {
                "source": "disasm/src/X.c",
                "candidates": [{"function": owner, "label": f"label{i}", "body": f"body{i}"} for i in range(4)],
            }
            result0 = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [
                    {"function": owner, "label": f"label{i}", "status": "rejected", "similarity_score": 0.1 * i}
                    for i in range(4)
                ],
            }
            self._run(out_dir, repo_dir, owner, batch0, result0, owner_state, iteration=0)

            batch1 = {
                "source": "disasm/src/X.c",
                "candidates": [
                    {"function": owner, "label": "label0", "body": "body0-v2"},
                    {"function": owner, "label": "label4", "body": "body4"},
                    {"function": owner, "label": "label5", "body": "body5"},
                    {"function": owner, "label": "label6", "body": "body6"},
                ],
            }
            result1 = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [
                    {"function": owner, "label": "label0", "status": "rejected", "similarity_score": 0.99},
                    {"function": owner, "label": "label4", "status": "rejected", "similarity_score": 0.2},
                    {"function": owner, "label": "label5", "status": "rejected", "similarity_score": 0.25},
                    {"function": owner, "label": "label6", "status": "rejected", "similarity_score": 0.05},
                ],
            }
            self._run(out_dir, repo_dir, owner, batch1, result1, owner_state, iteration=1)

            labels = [c["label"] for c in owner_state["best_candidates"]]
            self.assertEqual(len(labels), len(set(labels)))
            self.assertLessEqual(len(owner_state["best_candidates"]), container_agent.BEST_CANDIDATES_KEPT)
            self.assertEqual(owner_state["best_candidates"][0]["label"], "label0")
            self.assertEqual(owner_state["best_candidates"][0]["similarity_score"], 0.99)
            self.assertEqual(owner_state["best_candidates"][0]["body"], "body0-v2")

    def test_best_candidates_entries_carry_feedback_from_assembly_diff(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            batch = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "a", "body": "body_a"}]}
            result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{
                    "function": owner, "label": "a", "status": "probe_rejected",
                    "similarity_score": 0.83, "raw_similarity_score": 0.27,
                    "mismatch_kind": "operand_or_scheduling_drift",
                    "expected_size": 336, "actual_size": 340,
                    "expected_instruction_count": 84, "actual_instruction_count": 85,
                    "first_diff_offset": 3,
                    "expected_instruction_text": "addiu $sp, $sp, -144",
                    "actual_instruction_text": "addiu $sp, $sp, -152",
                    "assembly_diff": [
                        {
                            "expected_offset": 0, "expected": "addiu\tsp,sp,-144",
                            "actual": "addiu\tsp,sp,-144", "exact_match": True,
                        },
                        {
                            "expected_offset": 4, "expected": "sw\tra,20(sp)",
                            "actual": "sdc1\t$f20,24(sp)", "exact_match": False,
                        },
                    ],
                }],
            }
            self._run(out_dir, repo_dir, owner, batch, result, owner_state)

            feedback = owner_state["best_candidates"][0]["feedback"]
            self.assertEqual(feedback["expected_size"], 336)
            self.assertEqual(feedback["actual_size"], 340)
            self.assertEqual(feedback["first_diff_offset"], 3)
            self.assertIn("sw\tra,20(sp)", feedback["diff_excerpt"])

            # Persisted through state.json as-is (small, JSON-serializable) so
            # --resume inherits it.
            state = {owner: owner_state}
            state_path = out_dir / "state.json"
            container_agent.save_json(state_path, state)
            reloaded = container_agent.load_json(state_path)
            self.assertEqual(
                reloaded[owner]["best_candidates"][0]["feedback"]["first_diff_offset"], 3,
            )

    # Part D: the permuter is triggered from run_iteration as a background
    # job (a started thread appended to the caller's `permuter_jobs` list)
    # rather than blocking inline; `run_permuter` (reused unchanged by the
    # job's worker thread) is stubbed so no real subprocess runs, the
    # thread is joined so the job has actually finished, and
    # `poll_permuter_jobs` is what folds its result into `owner_state` --
    # exactly the two call sites `process_owner` uses in production.

    def test_permuter_triggered_by_high_similarity(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            batch = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "a", "body": "body_a"}]}
            result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{
                    "function": owner, "label": "a", "status": "near_miss",
                    "similarity_score": 0.97, "futility": None,
                }],
            }
            permuter_result = {"timed_out": False, "outputs": [], "best": {"score": 0, "code": "void func_1(void) {}"}}
            logger = container_agent.Logger(out_dir / "log.txt")
            batch_path = out_dir / "batches" / "func_1_iter0.json"
            container_agent.save_json(batch_path, batch)
            jobs: list = []

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe), \
                 mock.patch.object(container_agent, "run_permuter", return_value=permuter_result) as run_permuter_mock:
                container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=30.0, logger=logger,
                    permuter_jobs=jobs,
                )
                self.assertEqual(len(jobs), 1)
                jobs[0].thread.join(timeout=5.0)
                self.assertFalse(jobs[0].thread.is_alive())
            container_agent.poll_permuter_jobs(jobs, owner_state, logger=logger)
        run_permuter_mock.assert_called_once()
        self.assertEqual(owner_state["permuter_seed"]["score"], 0)
        self.assertEqual(jobs, [])

    def test_permuter_triggered_by_register_tie_below_threshold(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            batch = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "a", "body": "body_a"}]}
            result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{
                    "function": owner, "label": "a", "status": "near_miss",
                    "similarity_score": 0.5, "futility": "register-tie: a0 vs a1",
                }],
            }
            permuter_result = {"timed_out": False, "outputs": [], "best": {"score": 5, "code": "void func_1(void) {}"}}
            logger = container_agent.Logger(out_dir / "log.txt")
            batch_path = out_dir / "batches" / "func_1_iter0.json"
            container_agent.save_json(batch_path, batch)
            jobs: list = []

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe), \
                 mock.patch.object(container_agent, "run_permuter", return_value=permuter_result) as run_permuter_mock:
                container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=30.0, logger=logger,
                    permuter_jobs=jobs,
                )
                jobs[0].thread.join(timeout=5.0)
            container_agent.poll_permuter_jobs(jobs, owner_state, logger=logger)
        run_permuter_mock.assert_called_once()
        self.assertEqual(owner_state["permuter_seed"]["score"], 5)

    def test_permuter_lowered_threshold_on_operand_or_scheduling_drift(self) -> None:
        # Part D.2: 0.90 (not 0.95) is enough to trigger when mismatch_kind
        # is operand_or_scheduling_drift.
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            batch = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "a", "body": "body_a"}]}
            result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{
                    "function": owner, "label": "a", "status": "near_miss",
                    "similarity_score": 0.91, "raw_similarity_score": 0.91,
                    "mismatch_kind": "operand_or_scheduling_drift", "futility": None,
                }],
            }
            permuter_result = {"timed_out": False, "outputs": [], "best": {"score": 1, "code": "void func_1(void) {}"}}
            logger = container_agent.Logger(out_dir / "log.txt")
            batch_path = out_dir / "batches" / "func_1_iter0.json"
            container_agent.save_json(batch_path, batch)
            jobs: list = []

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe), \
                 mock.patch.object(container_agent, "run_permuter", return_value=permuter_result) as run_permuter_mock:
                container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=30.0, logger=logger,
                    permuter_jobs=jobs,
                )
                jobs[0].thread.join(timeout=5.0)
            container_agent.poll_permuter_jobs(jobs, owner_state, logger=logger)
        run_permuter_mock.assert_called_once()
        self.assertEqual(owner_state["permuter_seed"]["score"], 1)

    def test_permuter_lowered_threshold_on_register_only_tie_gap(self) -> None:
        # register_allocation_only with raw well below effective/normalized
        # also gets the 0.90 bar, even without a runner-reported
        # "register-tie" futility string.
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            batch = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "a", "body": "body_a"}]}
            result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{
                    "function": owner, "label": "a", "status": "near_miss",
                    "similarity_score": 0.92, "raw_similarity_score": 0.80,
                    "mismatch_kind": "register_allocation_only", "futility": None,
                }],
            }
            permuter_result = {"timed_out": False, "outputs": [], "best": {"score": 2, "code": "void func_1(void) {}"}}
            logger = container_agent.Logger(out_dir / "log.txt")
            batch_path = out_dir / "batches" / "func_1_iter0.json"
            container_agent.save_json(batch_path, batch)
            jobs: list = []

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe), \
                 mock.patch.object(container_agent, "run_permuter", return_value=permuter_result) as run_permuter_mock:
                container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=30.0, logger=logger,
                    permuter_jobs=jobs,
                )
                jobs[0].thread.join(timeout=5.0)
            container_agent.poll_permuter_jobs(jobs, owner_state, logger=logger)
        run_permuter_mock.assert_called_once()
        self.assertEqual(owner_state["permuter_seed"]["score"], 2)

    def test_permuter_not_triggered_below_threshold(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            batch = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "a", "body": "body_a"}]}
            result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{
                    "function": owner, "label": "a", "status": "near_miss",
                    "similarity_score": 0.5, "futility": None,
                }],
            }
            logger = container_agent.Logger(out_dir / "log.txt")
            batch_path = out_dir / "batches" / "func_1_iter0.json"
            container_agent.save_json(batch_path, batch)
            jobs: list = []

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe), \
                 mock.patch.object(container_agent, "run_permuter") as run_permuter_mock:
                container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=30.0, logger=logger,
                    permuter_jobs=jobs,
                )
        run_permuter_mock.assert_not_called()
        self.assertEqual(jobs, [])
        self.assertNotIn("permuter_seed", owner_state)

    def test_missing_result_json_increments_plateau_and_continues(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            batch = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "a", "body": "body_a"}]}
            status = self._run(out_dir, repo_dir, owner, batch, None, owner_state)
        self.assertEqual(status, "continue")
        self.assertEqual(owner_state["plateau_count"], 1)

    def test_normalized_only_match_does_not_win_or_trigger_permuter(self) -> None:
        # Reproduces the observed real-run attempt: similarity_score=1.0,
        # raw_similarity_score=0.6667, mismatch_kind=immediate_drift, a
        # diagnostic flagging it as normalized-only, and status
        # "probe_rejected" (never "accepted"). It must not be allowed to
        # look like a perfect (or even near-95%) match to the driver.
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            batch = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "a", "body": "body_a"}]}
            result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{
                    "function": owner, "label": "a", "status": "probe_rejected",
                    "similarity_score": 1.0, "raw_similarity_score": 0.6667,
                    "mismatch_kind": "immediate_drift",
                    "diagnostic": (
                        "normalized_only_match: the normalised similarity score is hiding "
                        "register/field differences"
                    ),
                }],
            }
            logger = container_agent.Logger(out_dir / "log.txt")
            batch_path = out_dir / "batches" / "func_1_iter0.json"
            container_agent.save_json(batch_path, batch)

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe), \
                 mock.patch.object(container_agent, "run_permuter") as run_permuter_mock:
                status = container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=30.0, logger=logger,
                )
        self.assertEqual(status, "continue")
        run_permuter_mock.assert_not_called()
        self.assertNotIn("permuter_seed", owner_state)
        # No improvement is recorded -- plateau increments, not resets.
        self.assertEqual(owner_state["plateau_count"], 1)
        self.assertEqual(owner_state["best_similarity"], 0.0)
        self.assertEqual(owner_state["best_effective_similarity"], 0.0)
        self.assertTrue(owner_state["best_candidates"][0]["normalized_only"])

    def test_later_genuine_improvement_counts_over_normalized_only_match(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()

            batch0 = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "a", "body": "body_a"}]}
            normalized_only_result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{
                    "function": owner, "label": "a", "status": "probe_rejected",
                    "similarity_score": 1.0, "raw_similarity_score": 0.6667,
                    "mismatch_kind": "immediate_drift",
                    "diagnostic": "normalized_only_match: hiding register/field differences",
                }],
            }
            # run_permuter is stubbed (not just joined) so the trigger below
            # never spawns a real subprocess: plateau/best-similarity
            # tracking is the point of this test, not the permuter itself.
            no_permuter_result = {"timed_out": False, "outputs": [], "best": None}
            with mock.patch.object(container_agent, "run_permuter", return_value=no_permuter_result):
                self._run(
                    out_dir, repo_dir, owner, batch0, normalized_only_result, owner_state,
                    iteration=0, permuter_seconds=30.0,
                )
                self.assertEqual(owner_state["plateau_count"], 1)
                self.assertEqual(owner_state["best_similarity"], 0.0)

                batch1 = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "b", "body": "body_b"}]}
                genuine_result = {
                    "batch_status": "no_candidate_accepted", "accepted": [],
                    "attempts": [{
                        "function": owner, "label": "b", "status": "near_miss",
                        "similarity_score": 0.96, "raw_similarity_score": 0.95,
                    }],
                }
                self._run(
                    out_dir, repo_dir, owner, batch1, genuine_result, owner_state,
                    iteration=1, permuter_seconds=30.0,
                )

        self.assertEqual(owner_state["best_similarity"], 0.96)
        self.assertEqual(owner_state["best_effective_similarity"], 0.96)
        self.assertEqual(owner_state["plateau_count"], 0)

    def test_raw_only_improvement_at_equal_normalized_similarity_counts(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()

            batch0 = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "a", "body": "body_a"}]}
            result0 = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{
                    "function": owner, "label": "a", "status": "rejected",
                    "similarity_score": 0.8, "raw_similarity_score": 0.70,
                }],
            }
            self._run(out_dir, repo_dir, owner, batch0, result0, owner_state, iteration=0)
            self.assertEqual(owner_state["best_similarity"], 0.8)
            self.assertEqual(owner_state["best_raw_similarity"], 0.70)
            self.assertEqual(owner_state["plateau_count"], 0)

            batch1 = {"source": "disasm/src/X.c", "candidates": [{"function": owner, "label": "b", "body": "body_b"}]}
            result1 = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{
                    "function": owner, "label": "b", "status": "rejected",
                    "similarity_score": 0.8, "raw_similarity_score": 0.75,
                }],
            }
            self._run(out_dir, repo_dir, owner, batch1, result1, owner_state, iteration=1)

        self.assertEqual(owner_state["best_similarity"], 0.8)
        self.assertEqual(owner_state["best_raw_similarity"], 0.75)
        self.assertEqual(owner_state["plateau_count"], 0)


# ---------------------------------------------------------------------------
# filter_batch / tried-body dedup (a generator resending an already-probed
# body -- or two identical candidates in one batch -- makes fleet_probe's
# own preflight reject the WHOLE batch; this driver must catch it first)
# ---------------------------------------------------------------------------

class FilterBatchTests(unittest.TestCase):
    def test_drops_previously_tried_body_and_in_batch_duplicate(self) -> None:
        owner_state = container_agent._new_owner_state()
        owner_state["tried_bodies"] = [
            container_agent._tried_body_key("void func_1(void) { return; }", "")
        ]
        batch = {
            "declarations": "",
            "candidates": [
                {"function": "func_1", "label": "already-tried", "body": "void func_1(void) { return; }"},
                {"function": "func_1", "label": "dup-a", "body": "void func_1(void) { return 1; }"},
                # Same body as dup-a modulo whitespace -- an in-batch duplicate.
                {"function": "func_1", "label": "dup-b", "body": "void   func_1(void)   {   return 1;   }"},
                {"function": "func_1", "label": "new", "body": "void func_1(void) { return 2; }"},
            ],
        }

        filtered, dropped = container_agent.filter_batch(batch, owner_state)

        self.assertEqual([c["label"] for c in filtered["candidates"]], ["dup-a", "new"])
        self.assertEqual([d["label"] for d in dropped], ["already-tried", "dup-b"])
        self.assertEqual(dropped[0]["reason"], "already tried this run")
        self.assertEqual(dropped[1]["reason"], "duplicate within this batch")

    def test_empty_batch_after_filtering_counts_as_plateau_without_probing(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            body = "void func_1(void) { return; }"
            owner_state["tried_bodies"] = [container_agent._tried_body_key(body, "")]
            batch = {
                "source": "disasm/src/X.c", "declarations": "",
                "candidates": [{"function": owner, "label": "a", "body": body}],
            }
            batch_path = out_dir / "batches" / "func_1_iter0.json"
            container_agent.save_json(batch_path, batch)
            logger = container_agent.Logger(out_dir / "log.txt")

            with mock.patch.object(container_agent, "invoke_probe") as probe_mock:
                status = container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=0.0, logger=logger,
                )

        self.assertEqual(status, "continue")
        probe_mock.assert_not_called()
        self.assertEqual(owner_state["plateau_count"], 1)

    def test_preflight_retry_drops_indexed_candidates_and_probes_once_more(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            batch = {
                "source": "disasm/src/X.c",
                "declarations": "",
                "candidates": [
                    {"function": owner, "label": "a", "body": "body_a"},
                    {"function": owner, "label": "b", "body": "body_b"},
                    {"function": owner, "label": "c", "body": "body_c"},
                ],
            }
            batch_path = out_dir / "batches" / "func_1_iter0.json"
            container_agent.save_json(batch_path, batch)
            calls = {"n": 0}

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                calls["n"] += 1
                current = container_agent.load_json(batch_path_arg)
                if calls["n"] == 1:
                    self.assertEqual([c["label"] for c in current["candidates"]], ["a", "b", "c"])
                    return SimpleNamespace(
                        returncode=2, stdout="",
                        stderr=(
                            "fleet_probe: batch preflight failed:\n"
                            "- candidates[1] for func_1 is a body already rejected as 'b' "
                            "(probe_rejected, similarity 0.4) at an earlier batch with these "
                            "same declarations; re-sending it cannot produce a new result"
                        ),
                    )
                self.assertEqual(calls["n"], 2)
                self.assertEqual([c["label"] for c in current["candidates"]], ["a", "c"])
                result = {
                    "batch_status": "no_candidate_accepted", "accepted": [],
                    "attempts": [
                        {"function": owner, "label": "a", "status": "rejected", "similarity_score": 0.2},
                        {"function": owner, "label": "c", "status": "rejected", "similarity_score": 0.3},
                    ],
                }
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            logger = container_agent.Logger(out_dir / "log.txt")
            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe):
                status = container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=0.0, logger=logger,
                )

        self.assertEqual(status, "continue")
        self.assertEqual(calls["n"], 2)
        self.assertEqual(len(owner_state["tried_bodies"]), 2)
        self.assertIn("a", owner_state["tried_labels"])
        self.assertIn("c", owner_state["tried_labels"])
        self.assertNotIn("b", owner_state["tried_labels"])


class TriedBodiesPersistenceTests(unittest.TestCase):
    def test_tried_bodies_round_trips_through_state_json_and_still_dedups(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            state_path = Path(tmp) / "state.json"
            owner_state = container_agent._new_owner_state()
            batch = {
                "declarations": "extern int g;",
                "candidates": [{"function": "func_1", "label": "a", "body": "void func_1(void) {}"}],
            }
            container_agent._record_tried_bodies(batch, owner_state)
            container_agent.save_json(state_path, {"func_1": owner_state})

            loaded_state = container_agent.load_json(state_path)
            reloaded_owner_state = loaded_state["func_1"]
            self.assertEqual(reloaded_owner_state["tried_bodies"], owner_state["tried_bodies"])
            self.assertEqual(reloaded_owner_state["tried_labels"], ["a"])

            # --resume passes the reloaded owner_state straight into
            # filter_batch, so a re-send of the exact same body/declarations
            # must still be dropped after the JSON round trip.
            filtered, dropped = container_agent.filter_batch(batch, reloaded_owner_state)
            self.assertEqual(filtered["candidates"], [])
            self.assertEqual(len(dropped), 1)


# ---------------------------------------------------------------------------
# build_prompt
# ---------------------------------------------------------------------------

class BuildPromptTests(unittest.TestCase):
    def test_normalized_only_candidate_gets_flagged_in_prompt(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1",
            source_rel="disasm/src/X.c",
            file_brief="brief",
            asm_text="asm",
            best_candidates=[{
                "label": "a", "similarity_score": 1.0, "raw_similarity_score": 0.6667,
                "mismatch_kind": "immediate_drift", "futility": None,
                "diagnostic": "normalized_only_match: hiding register/field differences",
                "body": "void func_1(void) {}",
                "normalized_only": True,
            }],
            permuter_seed=None,
            batch_path=Path("/tmp/batch.json"),
        )
        self.assertIn("NORMALIZED-ONLY MATCH", prompt)
        self.assertIn("raw=0.6667", prompt)

    def test_non_normalized_only_candidate_has_no_flag_line(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1",
            source_rel="disasm/src/X.c",
            file_brief="brief",
            asm_text="asm",
            best_candidates=[{
                "label": "a", "similarity_score": 0.8, "raw_similarity_score": 0.75,
                "mismatch_kind": None, "futility": None, "diagnostic": None,
                "body": "void func_1(void) {}",
                "normalized_only": False,
            }],
            permuter_seed=None,
            batch_path=Path("/tmp/batch.json"),
        )
        self.assertNotIn("NORMALIZED-ONLY MATCH", prompt)

    def test_tried_labels_shown_and_capped(self) -> None:
        labels = [f"label{i}" for i in range(40)]
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[], permuter_seed=None, batch_path=Path("/tmp/batch.json"),
            tried_labels=labels,
        )
        self.assertIn("labels already tried this run", prompt)
        self.assertIn("label39", prompt)
        self.assertNotIn("label0,", prompt)
        self.assertNotIn("label0 ", prompt)

    def test_no_tried_labels_section_when_empty(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[], permuter_seed=None, batch_path=Path("/tmp/batch.json"),
            tried_labels=[],
        )
        self.assertNotIn("labels already tried this run", prompt)

    def test_time_budget_sentence_reflects_generator_timeout_minutes(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[], permuter_seed=None, batch_path=Path("/tmp/batch.json"),
            generator_timeout_minutes=25,
        )
        self.assertIn("Time budget: about 25 minutes.", prompt)
        self.assertIn("Write a first batch file to", prompt)
        self.assertIn("/tmp/batch.json", prompt)
        self.assertIn("within the first few minutes", prompt)
        self.assertIn("whatever is in the file is what gets probed", prompt)

    def test_time_budget_sentence_defaults_to_generator_timeout_default(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[], permuter_seed=None, batch_path=Path("/tmp/batch.json"),
        )
        self.assertIn(
            f"Time budget: about {round(container_agent.DEFAULT_GENERATOR_TIMEOUT / 60)} minutes.",
            prompt,
        )

    def _candidate_with_feedback(self, label, **feedback_overrides):
        feedback = {
            "expected_size": 336, "actual_size": 340,
            "expected_instruction_count": 84, "actual_instruction_count": 85,
            "first_diff_offset": 3,
            "expected_instruction_text": "addiu $sp, $sp, -144",
            "actual_instruction_text": "addiu $sp, $sp, -152",
            "diff_excerpt": (
                "  @0: addiu\tsp,sp,-144  (match)\n"
                "  @4: expected `sw\tra,20(sp)`  actual `sdc1\t$f20,24(sp)`"
            ),
            "diff_excerpt_truncated": False,
        }
        feedback.update(feedback_overrides)
        return {
            "label": label, "similarity_score": 0.83, "raw_similarity_score": 0.27,
            "mismatch_kind": "operand_or_scheduling_drift", "futility": None,
            "diagnostic": "similarity_score=0.83 raw=0.27 mismatch_kind=operand_or_scheduling_drift",
            "body": f"void {label}(void) {{}}",
            "normalized_only": False,
            "feedback": feedback,
        }

    def test_frame_instructions_and_first_mismatch_lines_rendered(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_86000020", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[self._candidate_with_feedback("a")],
            permuter_seed=None, batch_path=Path("/tmp/batch.json"),
        )
        self.assertIn("frame: expected 336 bytes, actual 340", prompt)
        self.assertIn("instructions: expected 84, actual 85", prompt)
        self.assertIn(
            "first mismatch at offset 3: expected `addiu $sp, $sp, -144` "
            "actual `addiu $sp, $sp, -152`",
            prompt,
        )
        self.assertIn("sdc1\t$f20,24(sp)", prompt)
        self.assertIn("== how to read the diff ==", prompt)

    def test_frame_line_omitted_when_sizes_match(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[self._candidate_with_feedback("a", expected_size=100, actual_size=100)],
            permuter_seed=None, batch_path=Path("/tmp/batch.json"),
        )
        self.assertNotIn("frame: expected", prompt)

    def test_diff_excerpt_truncation_note_surfaces_in_prompt(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[self._candidate_with_feedback(
                "a",
                diff_excerpt=(
                    "  @4: expected `sw\tra,20(sp)`  actual `sdc1\t$f20,24(sp)`\n"
                    "  ... (diff truncated)"
                ),
                diff_excerpt_truncated=True,
            )],
            permuter_seed=None, batch_path=Path("/tmp/batch.json"),
        )
        self.assertIn("(diff truncated)", prompt)

    def test_size_guard_drops_diffs_beyond_top_two(self) -> None:
        # A large diff_excerpt (near the 3 KB per-candidate cap) on each of
        # BEST_CANDIDATES_KEPT candidates, plus a large file brief/assembly,
        # pushes the fully-rendered prompt well past PROMPT_SIZE_CAP.
        big_excerpt = "\n".join(
            f"  @{i * 4}: expected `sw\ta0,{i}(sp)`  actual `sw\ta1,{i}(sp)`" for i in range(40)
        )
        candidates = [
            self._candidate_with_feedback(f"label{i}", diff_excerpt=big_excerpt)
            for i in range(container_agent.BEST_CANDIDATES_KEPT)
        ]
        # A large file brief/assembly on top of a full diff excerpt for
        # every candidate is what actually pushes a real owner's prompt
        # over the cap (the diffs alone rarely do).
        unguarded = container_agent._render_best_candidates(candidates, full_diff_count=len(candidates))
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c",
            file_brief="brief line\n" * 1500, asm_text="asm line\n" * 4000,
            best_candidates=candidates, permuter_seed=None,
            batch_path=Path("/tmp/batch.json"),
        )
        # Confirms the fixture actually exercises the guard (an "unguarded"
        # rendering of the section alone would already be sizeable) rather
        # than passing trivially because nothing was ever close to the cap.
        self.assertGreater(len("\n".join(unguarded)), 5_000)

        full_diff_count = container_agent.FULL_DIFF_CANDIDATES
        self.assertGreater(len(candidates), full_diff_count)
        for entry in candidates[:full_diff_count]:
            self.assertIn(f"first mismatch at offset {entry['feedback']['first_diff_offset']}", prompt)
        for entry in candidates[full_diff_count:]:
            label = entry["label"]
            label_pos = prompt.index(f"label={label}")
            # No diff excerpt (its distinctive "sw\ta0," lines) was rendered
            # for this candidate -- just the header-only fallback.
            omitted_marker = "(diff omitted"
            self.assertIn(omitted_marker, prompt[label_pos:label_pos + 4000])
            next_label_pos = prompt.find("-- label=", label_pos + 1)
            end = next_label_pos if next_label_pos != -1 else len(prompt)
            self.assertNotIn("sw\ta0,", prompt[label_pos:end])

    def test_small_prompt_keeps_full_diff_for_all_candidates(self) -> None:
        candidates = [self._candidate_with_feedback(f"label{i}") for i in range(3)]
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=candidates, permuter_seed=None, batch_path=Path("/tmp/batch.json"),
        )
        for entry in candidates:
            self.assertIn(f"first mismatch at offset {entry['feedback']['first_diff_offset']}", prompt)
        self.assertNotIn("(diff omitted", prompt)

    def test_probe_tool_on_by_default_mentions_probe_one(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[], permuter_seed=None, batch_path=Path("/tmp/batch.json"),
        )
        self.assertIn("tools/probe_one.py", prompt)
        self.assertIn(
            "--source disasm/src/X.c --function func_1", prompt,
        )
        self.assertIn("MAY and SHOULD iterate", prompt)
        self.assertNotIn(
            "Do NOT compile, assemble, run make, probes or the permuter yourself", prompt,
        )

    def test_probe_tool_off_restores_do_not_compile_rule(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[], permuter_seed=None, batch_path=Path("/tmp/batch.json"),
            probe_tool=False,
        )
        self.assertNotIn("tools/probe_one.py", prompt)
        self.assertIn(
            "Do NOT compile, assemble, run make, probes or the permuter yourself", prompt,
        )


# ---------------------------------------------------------------------------
# process_owner
# ---------------------------------------------------------------------------

class ProcessOwnerTests(unittest.TestCase):
    def test_returns_plateau_after_non_improving_iterations(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            source_rel = "disasm/src/X.c"

            def batch_for_iteration(_n):
                return {"source": source_rel, "candidates": [{"function": owner, "label": "a", "body": "b"}]}

            def result_for_call(_n, _batch):
                return {
                    "batch_status": "no_candidate_accepted", "accepted": [],
                    "attempts": [{"function": owner, "label": "a", "status": "rejected", "similarity_score": 0.0}],
                }

            owner_state = container_agent._new_owner_state()
            state = {owner: owner_state}
            state_path = out_dir / "state.json"
            logger = container_agent.Logger(out_dir / "log.txt")

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator", side_effect=make_invoke_generator(batch_for_iteration)), \
                 mock.patch.object(container_agent, "invoke_probe", side_effect=make_invoke_probe(result_for_call)):
                status = container_agent.process_owner(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                    owner_state=owner_state, state=state, state_path=state_path,
                    deadline=time.monotonic() + 60.0, max_iterations=50, plateau=2,
                    permuter_seconds=0.0, generator_cmd="generator --prompt {prompt} --batch {batch}",
                    logger=logger,
                )
        self.assertEqual(status, "plateau")
        self.assertEqual(owner_state["iterations"], 2)

    def test_returns_max_iterations_at_cap(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            source_rel = "disasm/src/X.c"

            def batch_for_iteration(_n):
                return {"source": source_rel, "candidates": [{"function": owner, "label": "a", "body": "b"}]}

            def result_for_call(n, _batch):
                return {
                    "batch_status": "no_candidate_accepted", "accepted": [],
                    "attempts": [{"function": owner, "label": "a", "status": "rejected", "similarity_score": 0.1 * (n + 1)}],
                }

            owner_state = container_agent._new_owner_state()
            state = {owner: owner_state}
            state_path = out_dir / "state.json"
            logger = container_agent.Logger(out_dir / "log.txt")

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator", side_effect=make_invoke_generator(batch_for_iteration)), \
                 mock.patch.object(container_agent, "invoke_probe", side_effect=make_invoke_probe(result_for_call)):
                status = container_agent.process_owner(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                    owner_state=owner_state, state=state, state_path=state_path,
                    deadline=time.monotonic() + 60.0, max_iterations=2, plateau=100,
                    permuter_seconds=0.0, generator_cmd="generator --prompt {prompt} --batch {batch}",
                    logger=logger,
                )
        self.assertEqual(status, "max_iterations")
        self.assertEqual(owner_state["iterations"], 2)

    def test_returns_budget_expired_when_deadline_passed(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            source_rel = "disasm/src/X.c"
            owner_state = container_agent._new_owner_state()
            state = {owner: owner_state}
            state_path = out_dir / "state.json"
            logger = container_agent.Logger(out_dir / "log.txt")

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator") as gen_mock, \
                 mock.patch.object(container_agent, "invoke_probe") as probe_mock:
                status = container_agent.process_owner(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                    owner_state=owner_state, state=state, state_path=state_path,
                    deadline=time.monotonic() - 1.0, max_iterations=50, plateau=6,
                    permuter_seconds=0.0, generator_cmd="generator --prompt {prompt} --batch {batch}",
                    logger=logger,
                )
        self.assertEqual(status, "budget_expired")
        gen_mock.assert_not_called()
        probe_mock.assert_not_called()

    def test_returns_accepted_on_acceptance(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            source_rel = "disasm/src/X.c"
            source_path = repo_dir / source_rel
            source_path.parent.mkdir(parents=True)
            source_path.write_text("void func_1(void) {\n    return;\n}\n", encoding="utf-8")
            out_dir = Path(tmp) / "out"
            owner = "func_1"

            def batch_for_iteration(_n):
                return {"source": source_rel, "candidates": [{"function": owner, "label": "a", "body": "void func_1(void) { return; }"}]}

            def result_for_call(_n, _batch):
                return {
                    "batch_status": "accepted", "accepted": [owner],
                    "attempts": [{"function": owner, "label": "a", "status": "accepted", "similarity_score": 1.0}],
                }

            owner_state = container_agent._new_owner_state()
            state = {owner: owner_state}
            state_path = out_dir / "state.json"
            logger = container_agent.Logger(out_dir / "log.txt")

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator", side_effect=make_invoke_generator(batch_for_iteration)), \
                 mock.patch.object(container_agent, "invoke_probe", side_effect=make_invoke_probe(result_for_call)), \
                 _git_diff_stub():
                status = container_agent.process_owner(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                    owner_state=owner_state, state=state, state_path=state_path,
                    deadline=time.monotonic() + 60.0, max_iterations=50, plateau=6,
                    permuter_seconds=0.0, generator_cmd="generator --prompt {prompt} --batch {batch}",
                    logger=logger,
                )
            self.assertEqual(status, "accepted")
            self.assertTrue((out_dir / "accepted" / f"{owner}.json").exists())

    def test_invalid_batch_json_counts_toward_plateau(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            source_rel = "disasm/src/X.c"
            owner_state = container_agent._new_owner_state()
            state = {owner: owner_state}
            state_path = out_dir / "state.json"
            logger = container_agent.Logger(out_dir / "log.txt")

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator", side_effect=make_invoke_generator(lambda _n: None)), \
                 mock.patch.object(container_agent, "invoke_probe") as probe_mock:
                status = container_agent.process_owner(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                    owner_state=owner_state, state=state, state_path=state_path,
                    deadline=time.monotonic() + 60.0, max_iterations=50, plateau=1,
                    permuter_seconds=0.0, generator_cmd="generator --prompt {prompt} --batch {batch}",
                    logger=logger,
                )
        self.assertEqual(status, "plateau")
        self.assertEqual(owner_state["plateau_count"], 1)
        probe_mock.assert_not_called()


# ---------------------------------------------------------------------------
# main() end to end (--candidate-file / test mode)
# ---------------------------------------------------------------------------

class MainEndToEndTests(unittest.TestCase):
    def test_candidate_file_writes_state_summary_and_log(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            source_rel = "disasm/src/X.c"
            source_path = repo_dir / source_rel
            source_path.parent.mkdir(parents=True)
            source_path.write_text("void func_1(void) {\n    return;\n}\n", encoding="utf-8")

            out_dir = Path(tmp) / "out"
            candidate_file = Path(tmp) / "batch.json"
            candidate_file.write_text(
                json.dumps({
                    "source": source_rel,
                    "declarations": "",
                    "candidates": [{"function": "func_1", "label": "a", "body": "void func_1(void) { return; }"}],
                }),
                encoding="utf-8",
            )

            def result_for_call(_n, _batch):
                return {
                    "batch_status": "accepted", "accepted": ["func_1"],
                    "attempts": [{"function": "func_1", "label": "a", "status": "accepted", "similarity_score": 1.0}],
                }

            with mock.patch.object(container_agent, "invoke_probe", side_effect=make_invoke_probe(result_for_call)), \
                 _git_diff_stub():
                exit_code = container_agent.main([
                    "--source", source_rel,
                    "--out", str(out_dir),
                    "--repo", str(repo_dir),
                    "--candidate-file", str(candidate_file),
                ])

            self.assertEqual(exit_code, 0)
            self.assertTrue((out_dir / "state.json").exists())
            self.assertTrue((out_dir / "log.txt").exists())
            summary_path = out_dir / "summary.json"
            self.assertTrue(summary_path.exists())
            summary = json.loads(summary_path.read_text(encoding="utf-8"))
            self.assertEqual(summary["matched"], ["func_1"])
            self.assertEqual(summary["stopped_reason"], "test_mode_exit")
            self.assertTrue((out_dir / "accepted" / "func_1.json").exists())

            state = json.loads((out_dir / "state.json").read_text(encoding="utf-8"))
            self.assertEqual(state["func_1"]["status"], "accepted")


# ---------------------------------------------------------------------------
# Generator exhaustion (quota/rate-limit early stop)
# ---------------------------------------------------------------------------

class GeneratorExhaustionTests(unittest.TestCase):
    def test_consecutive_failures_stop_the_whole_run(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            source_rel = "disasm/src/X.c"

            def failing_generator(command, *, cwd, timeout):
                return SimpleNamespace(returncode=1, stdout="", stderr="boom, no output produced")

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator", side_effect=failing_generator), \
                 mock.patch.object(container_agent, "invoke_probe") as probe_mock:
                exit_code = container_agent.main([
                    "--source", source_rel,
                    "--out", str(out_dir),
                    "--repo", str(repo_dir),
                    "--owners", "func_1,func_2",
                    "--generator-cmd", "generator --prompt {prompt} --batch {batch}",
                    "--max-generator-failures", "2",
                    "--plateau", "100",
                    "--max-iterations", "100",
                ])

            self.assertEqual(exit_code, 3)
            probe_mock.assert_not_called()

            summary = json.loads((out_dir / "summary.json").read_text(encoding="utf-8"))
            self.assertEqual(summary["stopped_reason"], "generator_exhausted")
            self.assertEqual(summary["runs"][-1]["stop_reason"], "generator_exhausted")
            self.assertIsNotNone(summary["runs"][-1]["ended"])

            state = json.loads((out_dir / "state.json").read_text(encoding="utf-8"))
            self.assertEqual(state["func_1"]["status"], "generator_failed")
            # the run stopped before func_2 was ever reached
            self.assertNotIn("func_2", state)

    def test_quota_signature_counts_as_two_failures(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            source_rel = "disasm/src/X.c"

            def quota_generator(command, *, cwd, timeout):
                return SimpleNamespace(returncode=1, stdout="", stderr="Error: Rate limit exceeded, try later")

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator", side_effect=quota_generator), \
                 mock.patch.object(container_agent, "invoke_probe") as probe_mock:
                exit_code = container_agent.main([
                    "--source", source_rel,
                    "--out", str(out_dir),
                    "--repo", str(repo_dir),
                    "--owners", "func_1",
                    "--generator-cmd", "generator --prompt {prompt} --batch {batch}",
                    "--max-generator-failures", "2",
                    "--plateau", "100",
                    "--max-iterations", "100",
                ])

            self.assertEqual(exit_code, 3)
            probe_mock.assert_not_called()
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
            self.assertIn("quota", log_text.lower())

            state = json.loads((out_dir / "state.json").read_text(encoding="utf-8"))
            # a single quota-looking failure counts double, so it alone reaches the limit of 2
            self.assertEqual(state["func_1"]["iterations"], 1)

    def test_success_resets_the_failure_counter(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            source_rel = "disasm/src/X.c"

            # iteration 0: invalid batch (failure); iteration 1: valid batch (success,
            # resets the counter); iteration 2: invalid batch again (failure -> count 1,
            # not 2, proving the reset actually happened).
            def batch_for_iteration(n):
                if n in (0, 2):
                    return None
                return {"source": source_rel, "candidates": [{"function": owner, "label": "a", "body": "b"}]}

            def result_for_call(_n, _batch):
                return {
                    "batch_status": "no_candidate_accepted", "accepted": [],
                    "attempts": [{"function": owner, "label": "a", "status": "rejected", "similarity_score": 0.1}],
                }

            owner_state = container_agent._new_owner_state()
            state = {owner: owner_state}
            state_path = out_dir / "state.json"
            logger = container_agent.Logger(out_dir / "log.txt")
            gen_failures = {"consecutive": 0}

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator", side_effect=make_invoke_generator(batch_for_iteration)), \
                 mock.patch.object(container_agent, "invoke_probe", side_effect=make_invoke_probe(result_for_call)):
                status = container_agent.process_owner(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                    owner_state=owner_state, state=state, state_path=state_path,
                    deadline=time.monotonic() + 60.0, max_iterations=3, plateau=100,
                    permuter_seconds=0.0, generator_cmd="generator --prompt {prompt} --batch {batch}",
                    logger=logger, gen_failures=gen_failures, max_generator_failures=5,
                )

        self.assertEqual(status, "max_iterations")
        self.assertEqual(owner_state["iterations"], 3)
        self.assertEqual(gen_failures["consecutive"], 1)


# ---------------------------------------------------------------------------
# Generator timeout handling / quota classification scoping
# ---------------------------------------------------------------------------

class GeneratorTimeoutAndQuotaClassificationTests(unittest.TestCase):
    """A generator timeout must count as exactly one failure and must never
    be misread as a quota/rate-limit signal from the model's own partial
    reasoning text. Quota classification applies only to a non-zero exit,
    and only inspects stderr."""

    def _run_owner(
        self, tmp, *, invoke_generator_stub, max_generator_failures=10,
        generator_timeout=container_agent.DEFAULT_GENERATOR_TIMEOUT, deadline_seconds=60.0,
    ):
        repo_dir = Path(tmp) / "repo"
        repo_dir.mkdir()
        out_dir = Path(tmp) / "out"
        owner = "func_1"
        source_rel = "disasm/src/X.c"
        owner_state = container_agent._new_owner_state()
        state = {owner: owner_state}
        state_path = out_dir / "state.json"
        logger = container_agent.Logger(out_dir / "log.txt")
        gen_failures = {"consecutive": 0}

        with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
             mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
             mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
             mock.patch.object(container_agent, "invoke_generator", side_effect=invoke_generator_stub):
            status = container_agent.process_owner(
                repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                owner_state=owner_state, state=state, state_path=state_path,
                deadline=time.monotonic() + deadline_seconds, max_iterations=1, plateau=100,
                permuter_seconds=0.0, generator_cmd="generator --prompt {prompt} --batch {batch}",
                logger=logger, gen_failures=gen_failures, max_generator_failures=max_generator_failures,
                generator_timeout=generator_timeout,
            )
        log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
        return status, gen_failures, log_text

    def test_timeout_counts_one_failure_and_logs_no_quota_signal(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            def timeout_generator(command, *, cwd, timeout):
                # Partial reasoning text captured off a killed generator --
                # mentions an offset that happens to look like "429".
                text = "reasoning: computing offset 0x429 into the jump table"
                raise subprocess.TimeoutExpired(cmd=command, timeout=timeout, output=text, stderr=text)

            status, gen_failures, log_text = self._run_owner(tmp, invoke_generator_stub=timeout_generator)

        self.assertEqual(status, "max_iterations")
        self.assertEqual(gen_failures["consecutive"], 1)
        self.assertNotIn("quota", log_text.lower())
        # No batch file was ever written by the stub, so this must fall
        # through to the plain hard-failure path, not the soft-failure
        # (timed out but left a probeable batch) path.
        self.assertNotIn("probing it", log_text)

    def test_timeout_with_valid_batch_is_probed_as_soft_failure(self) -> None:
        """A generator that times out but still left a valid batch file (the
        fix for the Kimi K3 incident: probe_one.py iterations eating the
        whole budget without ever reaching the final batch write) must be
        probed like a normal iteration, and must reset -- not increment --
        the consecutive-failure counter, since it did produce output."""
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            source_rel = "disasm/src/X.c"
            owner_state = container_agent._new_owner_state()
            state = {owner: owner_state}
            state_path = out_dir / "state.json"
            logger = container_agent.Logger(out_dir / "log.txt")
            # Start with a nonzero counter to prove a soft failure resets it
            # rather than merely not incrementing it.
            gen_failures = {"consecutive": 3}

            def timeout_generator_with_batch(command, *, cwd, timeout):
                batch_path = _extract_path_arg(command, "--batch")
                batch_path.parent.mkdir(parents=True, exist_ok=True)
                container_agent.save_json(batch_path, {
                    "source": source_rel,
                    "candidates": [{"function": owner, "label": "a", "body": "void func_1(void) {}"}],
                })
                raise subprocess.TimeoutExpired(cmd=command, timeout=timeout, output="", stderr="")

            probe_calls = {"n": 0}

            def probe_stub(repo_dir_arg, batch_path, result_path, *, timeout):
                probe_calls["n"] += 1
                container_agent.save_json(result_path, {
                    "batch_status": "no_candidate_accepted", "accepted": [],
                    "attempts": [{
                        "function": owner, "label": "a", "status": "rejected", "similarity_score": 0.1,
                    }],
                })
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator", side_effect=timeout_generator_with_batch), \
                 mock.patch.object(container_agent, "invoke_probe", side_effect=probe_stub):
                status = container_agent.process_owner(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                    owner_state=owner_state, state=state, state_path=state_path,
                    deadline=time.monotonic() + 60.0, max_iterations=1, plateau=100,
                    permuter_seconds=0.0, generator_cmd="generator --prompt {prompt} --batch {batch}",
                    logger=logger, gen_failures=gen_failures, max_generator_failures=5,
                )
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")

        self.assertEqual(status, "max_iterations")
        self.assertEqual(probe_calls["n"], 1)
        self.assertEqual(gen_failures["consecutive"], 0)
        self.assertEqual(owner_state["iterations"], 1)
        self.assertIn(
            "generator timed out but left a batch with 1 candidate(s); probing it", log_text,
        )

    def test_nonzero_exit_with_rate_limit_stderr_counts_two_failures(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            def failing_generator(command, *, cwd, timeout):
                return SimpleNamespace(returncode=1, stdout="", stderr="Error: Rate limit exceeded, try later")

            status, gen_failures, log_text = self._run_owner(tmp, invoke_generator_stub=failing_generator)

        self.assertEqual(gen_failures["consecutive"], 2)
        self.assertIn("quota", log_text.lower())

    def test_nonzero_exit_with_hex_offset_in_stderr_is_not_quota(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            def failing_generator(command, *, cwd, timeout):
                return SimpleNamespace(
                    returncode=1, stdout="",
                    stderr="unexpected token near 0x429 in decoded instruction",
                )

            status, gen_failures, log_text = self._run_owner(tmp, invoke_generator_stub=failing_generator)

        self.assertEqual(gen_failures["consecutive"], 1)
        self.assertNotIn("quota", log_text.lower())

    def test_stdout_quota_word_with_exit_zero_and_missing_batch_is_not_quota(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            def missing_batch_generator(command, *, cwd, timeout):
                # Exit 0, but the batch file is never written -- stdout
                # happens to mention "quota" in the model's own reasoning.
                return SimpleNamespace(
                    returncode=0, stdout="checking my quota of remaining tool calls", stderr="",
                )

            status, gen_failures, log_text = self._run_owner(tmp, invoke_generator_stub=missing_batch_generator)

        self.assertEqual(gen_failures["consecutive"], 1)
        self.assertNotIn("quota", log_text.lower())

    def test_generator_timeout_flag_bounds_the_invocation_timeout(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            source_rel = "disasm/src/X.c"
            owner_state = container_agent._new_owner_state()
            state = {owner: owner_state}
            state_path = out_dir / "state.json"
            logger = container_agent.Logger(out_dir / "log.txt")

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator") as gen_mock:
                gen_mock.side_effect = subprocess.TimeoutExpired(cmd="x", timeout=1)
                container_agent.process_owner(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                    owner_state=owner_state, state=state, state_path=state_path,
                    deadline=time.monotonic() + 3600.0, max_iterations=1, plateau=100,
                    permuter_seconds=0.0, generator_cmd="generator --prompt {prompt} --batch {batch}",
                    logger=logger, gen_failures={"consecutive": 0}, max_generator_failures=10,
                    generator_timeout=45.0,
                )

            self.assertEqual(gen_mock.call_count, 1)
            _, kwargs = gen_mock.call_args
            # deadline is far away, so the flag itself (not the remaining
            # budget) bounds the invocation timeout.
            self.assertEqual(kwargs["timeout"], 45.0)

    def test_generator_timeout_flag_is_bounded_by_remaining_budget(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            source_rel = "disasm/src/X.c"
            owner_state = container_agent._new_owner_state()
            state = {owner: owner_state}
            state_path = out_dir / "state.json"
            logger = container_agent.Logger(out_dir / "log.txt")

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator") as gen_mock:
                gen_mock.side_effect = subprocess.TimeoutExpired(cmd="x", timeout=1)
                container_agent.process_owner(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                    owner_state=owner_state, state=state, state_path=state_path,
                    deadline=time.monotonic() + 20.0, max_iterations=1, plateau=100,
                    permuter_seconds=0.0, generator_cmd="generator --prompt {prompt} --batch {batch}",
                    logger=logger, gen_failures={"consecutive": 0}, max_generator_failures=10,
                    generator_timeout=600.0,
                )

            _, kwargs = gen_mock.call_args
            # the run's remaining budget (~20s) is tighter than the 600s
            # flag, so it -- not the flag -- bounds the invocation timeout.
            self.assertLessEqual(kwargs["timeout"], 20.0)
            self.assertGreater(kwargs["timeout"], 10.0)


# ---------------------------------------------------------------------------
# --resume / --skip-status / non-empty-state guard
# ---------------------------------------------------------------------------

class ResumeTests(unittest.TestCase):
    def test_nonempty_state_without_resume_is_an_error(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            out_dir.mkdir()
            container_agent.save_json(out_dir / "state.json", {"func_a": container_agent._new_owner_state()})

            with mock.patch.object(container_agent, "invoke_generator") as gen_mock:
                exit_code = container_agent.main([
                    "--source", "disasm/src/X.c",
                    "--out", str(out_dir),
                    "--repo", str(repo_dir),
                    "--generator-cmd", "generator --prompt {prompt} --batch {batch}",
                ])

            self.assertEqual(exit_code, 2)
            gen_mock.assert_not_called()
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
            self.assertIn("--resume", log_text)

    def test_resume_skips_accepted_and_continues_iteration_numbering(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            out_dir.mkdir()
            source_rel = "disasm/src/X.c"
            owner = "func_b"

            state = {
                "func_a": {
                    "status": "accepted", "best_similarity": 1.0, "best_raw_similarity": 1.0,
                    "best_label": "a", "iterations": 3, "plateau_count": 0,
                    "history": [], "best_candidates": [], "permuter_runs": [],
                },
                "func_b": {
                    "status": "plateau", "best_similarity": 0.4, "best_effective_similarity": 0.4,
                    "best_raw_similarity": 0.4,
                    "best_label": "x", "iterations": 2, "plateau_count": 6,
                    "history": [],
                    "best_candidates": [{
                        "label": "x", "similarity_score": 0.4, "raw_similarity_score": 0.4,
                        "mismatch_kind": None, "futility": None, "diagnostic": None, "body": "prev_body",
                    }],
                    "permuter_runs": [],
                },
            }
            container_agent.save_json(out_dir / "state.json", state)
            container_agent.save_json(out_dir / "summary.json", {"runs": [{
                "started": "2026-09-01T00:00:00Z", "ended": "2026-09-01T00:05:00Z",
                "generator_cmd": "old-generator", "stop_reason": "generator_exhausted",
            }]})

            batch_paths_seen: list[str] = []

            def gen_stub(command, *, cwd, timeout):
                batch_path = _extract_path_arg(command, "--batch")
                batch_paths_seen.append(batch_path.name)
                batch_path.parent.mkdir(parents=True, exist_ok=True)
                container_agent.save_json(batch_path, {
                    "source": source_rel,
                    "candidates": [{"function": owner, "label": "b2", "body": "body_b2"}],
                })
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            def result_for_call(_n, _batch):
                return {
                    "batch_status": "no_candidate_accepted", "accepted": [],
                    "attempts": [{"function": owner, "label": "b2", "status": "rejected", "similarity_score": 0.35}],
                }

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator", side_effect=gen_stub), \
                 mock.patch.object(container_agent, "invoke_probe", side_effect=make_invoke_probe(result_for_call)):
                exit_code = container_agent.main([
                    "--source", source_rel,
                    "--out", str(out_dir),
                    "--repo", str(repo_dir),
                    "--owners", "func_a,func_b",
                    "--generator-cmd", "generator --prompt {prompt} --batch {batch}",
                    "--resume", "--plateau", "1", "--max-iterations", "3",
                ])

            self.assertEqual(exit_code, 0)
            # func_a (already accepted) never triggers a new generator call
            self.assertEqual(batch_paths_seen, ["func_b_iter2.json"])

            summary = json.loads((out_dir / "summary.json").read_text(encoding="utf-8"))
            self.assertIn("func_a", summary["matched"])
            self.assertNotIn("func_a", summary["owners_attempted"])
            self.assertIn("func_b", summary["owners_attempted"])
            self.assertEqual(len(summary["runs"]), 2)
            self.assertEqual(summary["runs"][0]["generator_cmd"], "old-generator")
            self.assertEqual(summary["runs"][1]["generator_cmd"], "generator --prompt {prompt} --batch {batch}")

            state_after = json.loads((out_dir / "state.json").read_text(encoding="utf-8"))
            self.assertEqual(state_after["func_b"]["iterations"], 3)
            self.assertEqual(state_after["func_b"]["status"], "plateau")

    def test_skip_status_can_also_skip_plateaued_owners(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            out_dir.mkdir()
            state = {"func_a": {**container_agent._new_owner_state(), "status": "plateau", "iterations": 5}}
            container_agent.save_json(out_dir / "state.json", state)

            with mock.patch.object(container_agent, "invoke_generator") as gen_mock:
                exit_code = container_agent.main([
                    "--source", "disasm/src/X.c",
                    "--out", str(out_dir),
                    "--repo", str(repo_dir),
                    "--owners", "func_a",
                    "--generator-cmd", "generator --prompt {prompt} --batch {batch}",
                    "--resume", "--skip-status", "accepted,plateau",
                ])

            self.assertEqual(exit_code, 0)
            gen_mock.assert_not_called()
            summary = json.loads((out_dir / "summary.json").read_text(encoding="utf-8"))
            self.assertNotIn("func_a", summary["owners_attempted"])
            self.assertEqual(summary["stopped_reason"], "completed")


# ---------------------------------------------------------------------------
# Part A: m2c draft seed
# ---------------------------------------------------------------------------

class ParseM2cDraftOutputTests(unittest.TestCase):
    def test_extracts_body_after_label_comment(self) -> None:
        stdout = "/* m2c */\nf64 func_1(void) {\n    return 0;\n}\n"
        self.assertEqual(
            container_agent._parse_m2c_draft_output(stdout),
            "f64 func_1(void) {\n    return 0;\n}",
        )

    def test_returns_none_on_error_comment(self) -> None:
        stdout = "/* m2c */\n/* error: m2c crashed */\n"
        self.assertIsNone(container_agent._parse_m2c_draft_output(stdout))

    def test_returns_none_on_empty_stdout(self) -> None:
        self.assertIsNone(container_agent._parse_m2c_draft_output(""))


class GetM2cDraftTests(unittest.TestCase):
    def test_fetches_once_and_caches_in_owner_state(self) -> None:
        owner_state = container_agent._new_owner_state()
        logger = container_agent.Logger(Path(tempfile.mkdtemp()) / "log.txt")
        proc = SimpleNamespace(returncode=0, stdout="/* m2c */\nvoid func_1(void) {}\n", stderr="")
        with mock.patch.object(container_agent, "invoke_m2c_draft", return_value=proc) as draft_mock:
            draft1 = container_agent.get_m2c_draft(Path("/repo"), "func_1", owner_state, logger=logger)
            draft2 = container_agent.get_m2c_draft(Path("/repo"), "func_1", owner_state, logger=logger)
        draft_mock.assert_called_once()
        self.assertEqual(draft1, "void func_1(void) {}")
        self.assertEqual(draft2, "void func_1(void) {}")
        self.assertEqual(owner_state["m2c_draft"], "void func_1(void) {}")
        self.assertTrue(owner_state["m2c_draft_fetched"])

    def test_resume_reuses_cached_draft_without_refetching(self) -> None:
        owner_state = container_agent._new_owner_state()
        owner_state["m2c_draft"] = "cached body"
        owner_state["m2c_draft_fetched"] = True
        logger = container_agent.Logger(Path(tempfile.mkdtemp()) / "log.txt")
        with mock.patch.object(container_agent, "invoke_m2c_draft") as draft_mock:
            draft = container_agent.get_m2c_draft(Path("/repo"), "func_1", owner_state, logger=logger)
        draft_mock.assert_not_called()
        self.assertEqual(draft, "cached body")

    def test_timeout_is_logged_and_cached_as_no_draft(self) -> None:
        owner_state = container_agent._new_owner_state()
        logger = container_agent.Logger(Path(tempfile.mkdtemp()) / "log.txt")
        with mock.patch.object(
            container_agent, "invoke_m2c_draft",
            side_effect=subprocess.TimeoutExpired(cmd="x", timeout=120),
        ) as draft_mock:
            draft1 = container_agent.get_m2c_draft(Path("/repo"), "func_1", owner_state, logger=logger)
            draft2 = container_agent.get_m2c_draft(Path("/repo"), "func_1", owner_state, logger=logger)
        draft_mock.assert_called_once()
        self.assertIsNone(draft1)
        self.assertIsNone(draft2)
        self.assertIsNone(owner_state["m2c_draft"])

    def test_nonzero_exit_returns_none_without_raising(self) -> None:
        owner_state = container_agent._new_owner_state()
        logger = container_agent.Logger(Path(tempfile.mkdtemp()) / "log.txt")
        proc = SimpleNamespace(returncode=1, stdout="", stderr="m2c not installed")
        with mock.patch.object(container_agent, "invoke_m2c_draft", return_value=proc):
            draft = container_agent.get_m2c_draft(Path("/repo"), "func_1", owner_state, logger=logger)
        self.assertIsNone(draft)


class BuildPromptM2cDraftTests(unittest.TestCase):
    def test_m2c_draft_rendered_before_best_candidates_section(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[{"label": "a", "similarity_score": 0.5, "body": "body_a"}],
            permuter_seed=None, batch_path=Path("/tmp/batch.json"),
            m2c_draft="f64 func_1(void) { return 0; }",
        )
        marker = "== m2c draft (structure hint, not a match; retype/reshape freely) =="
        self.assertIn(marker, prompt)
        self.assertIn("f64 func_1(void) { return 0; }", prompt)
        self.assertLess(prompt.index(marker), prompt.index("== best candidates tried so far"))

    def test_no_m2c_section_when_draft_absent(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[], permuter_seed=None, batch_path=Path("/tmp/batch.json"),
        )
        self.assertNotIn("m2c draft", prompt)


# ---------------------------------------------------------------------------
# Part B: declaration hygiene
# ---------------------------------------------------------------------------

class DeclarationStatementParsingTests(unittest.TestCase):
    def test_splits_multiple_statements(self) -> None:
        statements = container_agent._split_declaration_statements(
            "extern s32 func_A(void *arg0);\nextern u8 D_80328E00;\n"
        )
        self.assertEqual(statements, ["extern s32 func_A(void *arg0);", "extern u8 D_80328E00;"])

    def test_empty_declarations_yields_no_statements(self) -> None:
        self.assertEqual(container_agent._split_declaration_statements(""), [])
        self.assertEqual(container_agent._split_declaration_statements(None), [])

    def test_declared_name_from_function_prototype(self) -> None:
        self.assertEqual(
            container_agent._declaration_statement_name("extern s32 func_A(void *arg0);"), "func_A",
        )

    def test_declared_name_from_plain_data_symbol(self) -> None:
        self.assertEqual(container_agent._declaration_statement_name("extern u8 D_80328E00;"), "D_80328E00")

    def test_declared_name_from_data_array(self) -> None:
        self.assertEqual(container_agent._declaration_statement_name("extern u8 D_80328E00[16];"), "D_80328E00")

    def test_declared_name_from_function_pointer(self) -> None:
        self.assertEqual(
            container_agent._declaration_statement_name("extern void (*callback)(s32);"), "callback",
        )


class NameDeclaredInSourceTests(unittest.TestCase):
    def test_function_definition_counts_as_declared(self) -> None:
        source = "void func_A(void) {\n    return;\n}\n"
        self.assertTrue(container_agent._name_declared_in_source("func_A", source))

    def test_extern_line_counts_as_declared(self) -> None:
        source = "extern s32 func_A(void *arg0);\n"
        self.assertTrue(container_agent._name_declared_in_source("func_A", source))

    def test_array_data_symbol_counts_as_declared(self) -> None:
        source = "u8 D_80328E00[16] = {0};\n"
        self.assertTrue(container_agent._name_declared_in_source("D_80328E00", source))

    def test_unrelated_name_is_not_declared(self) -> None:
        source = "void func_A(void) {\n    return;\n}\n"
        self.assertFalse(container_agent._name_declared_in_source("func_B", source))


class FilterDeclarationsTests(unittest.TestCase):
    def test_drops_statement_for_name_already_defined_in_source(self) -> None:
        source = "void func_A(void) {\n    return;\n}\n"
        batch = {
            "declarations": "extern void func_A(void);\nextern u8 D_80328E00;",
            "candidates": [],
        }
        filtered, dropped, conflicts = container_agent.filter_declarations(batch, source)
        self.assertEqual(dropped, ["extern void func_A(void);"])
        self.assertEqual(filtered["declarations"], "extern u8 D_80328E00;")
        self.assertEqual(conflicts, [])

    def test_keeps_declarations_for_names_not_in_source(self) -> None:
        source = "void func_A(void) {\n    return;\n}\n"
        batch = {"declarations": "extern u8 D_80328E00;", "candidates": []}
        filtered, dropped, conflicts = container_agent.filter_declarations(batch, source)
        self.assertEqual(dropped, [])
        self.assertEqual(conflicts, [])
        self.assertIs(filtered, batch)

    def test_no_declarations_field_is_a_noop(self) -> None:
        filtered, dropped, conflicts = container_agent.filter_declarations(
            {"candidates": []}, "void func_A(void) {}"
        )
        self.assertEqual(dropped, [])
        self.assertEqual(conflicts, [])

    # -----------------------------------------------------------------
    # Issue #38: a stale file declaration must not silently win over a
    # batch's differently-typed one -- see filter_declarations' docstring.
    # -----------------------------------------------------------------

    def test_identical_signature_is_dropped_silently(self) -> None:
        # Same type, only the parameter name differs -- not a conflict.
        source = "extern f64 func_87C0068C(void *arg0);\n"
        batch = {
            "declarations": "extern f64 func_87C0068C(void *);",
            "candidates": [],
        }
        filtered, dropped, conflicts = container_agent.filter_declarations(batch, source)
        self.assertEqual(dropped, ["extern f64 func_87C0068C(void *);"])
        self.assertEqual(conflicts, [])
        self.assertEqual(filtered["declarations"], "")
        self.assertNotIn("companion_edits", filtered)

    def test_differing_signature_becomes_companion_edit(self) -> None:
        # Reproduces the real-run bug: the file's stale "extern void" must
        # not silently override the batch's (correct) "extern f64" -- and
        # must not simply be redeclared either (that's the compile error).
        old_line = "extern void func_87C0068C(void *arg0);"
        source = f"{old_line}\n\nvoid func_1(void) {{ return; }}\n"
        new_line = "extern f64 func_87C0068C(void *);"
        batch = {"declarations": new_line, "candidates": []}
        filtered, dropped, conflicts = container_agent.filter_declarations(batch, source)

        self.assertEqual(dropped, [])
        self.assertEqual(filtered["declarations"], "")
        self.assertEqual(len(conflicts), 1)
        conflict = conflicts[0]
        self.assertEqual(conflict["name"], "func_87C0068C")
        self.assertTrue(conflict["companion_edit"])
        self.assertEqual(conflict["file_declaration"], old_line)
        self.assertEqual(conflict["batch_declaration"], new_line)
        self.assertEqual(
            filtered["companion_edits"],
            [{"function": "func_87C0068C", "old": old_line, "new": new_line}],
        )

    def test_companion_edits_are_deduped_against_existing(self) -> None:
        old_line = "extern void func_87C0068C(void *arg0);"
        source = f"{old_line}\n"
        new_line = "extern f64 func_87C0068C(void *);"
        existing_edit = {"function": "func_87C0068C", "old": old_line, "new": new_line}
        batch = {
            "declarations": new_line,
            "companion_edits": [existing_edit, {"function": "other", "old": "a", "new": "b"}],
            "candidates": [],
        }
        filtered, dropped, conflicts = container_agent.filter_declarations(batch, source)
        self.assertEqual(len(conflicts), 1)
        self.assertEqual(
            filtered["companion_edits"],
            [existing_edit, {"function": "other", "old": "a", "new": "b"}],
        )

    def test_pragma_owner_conflict_keeps_batch_line_without_companion_edit(self) -> None:
        old_line = "extern void func_87C0068C(void *arg0);"
        source = (
            f"{old_line}\n\n"
            '#pragma GLOBAL_ASM("asm/nonmatchings/X/func_87C0068C.s")\n'
            "void func_87C0068C(void *arg0);\n"
        )
        new_line = "extern f64 func_87C0068C(void *);"
        batch = {"declarations": new_line, "candidates": []}
        filtered, dropped, conflicts = container_agent.filter_declarations(batch, source)

        self.assertEqual(dropped, [])
        self.assertEqual(filtered["declarations"], new_line)
        self.assertNotIn("companion_edits", filtered)
        self.assertEqual(len(conflicts), 1)
        self.assertFalse(conflicts[0]["companion_edit"])
        self.assertEqual(conflicts[0]["name"], "func_87C0068C")

    def test_non_extern_source_declaration_falls_back_to_silent_drop(self) -> None:
        # A full definition (not a plain extern line) has no single
        # comparable signature to check against -- old silent-drop behavior.
        source = "f64 func_87C0068C(void *arg0) {\n    return 0.0;\n}\n"
        batch = {"declarations": "extern void func_87C0068C(void *);", "candidates": []}
        filtered, dropped, conflicts = container_agent.filter_declarations(batch, source)
        self.assertEqual(dropped, ["extern void func_87C0068C(void *);"])
        self.assertEqual(conflicts, [])


class NormalizeDeclarationSignatureTests(unittest.TestCase):
    def test_ignores_parameter_names(self) -> None:
        a = container_agent._normalize_declaration_signature("extern f64 func_A(void *arg0);")
        b = container_agent._normalize_declaration_signature("extern f64 func_A(void *);")
        self.assertEqual(a, b)

    def test_different_return_type_differs(self) -> None:
        a = container_agent._normalize_declaration_signature("extern void func_A(void *arg0);")
        b = container_agent._normalize_declaration_signature("extern f64 func_A(void *);")
        self.assertNotEqual(a, b)

    def test_ignores_whitespace_and_pointer_spacing(self) -> None:
        a = container_agent._normalize_declaration_signature("extern   f64   func_A( void  *arg0 );")
        b = container_agent._normalize_declaration_signature("extern f64 func_A(void*arg1);")
        self.assertEqual(a, b)

    def test_unnamed_multiword_type_param_is_not_mistaken_for_a_name(self) -> None:
        a = container_agent._normalize_declaration_signature(
            "extern s32 func_A(unsigned int arg0, void *arg1);"
        )
        b = container_agent._normalize_declaration_signature(
            "extern s32 func_A(unsigned int, void*);"
        )
        self.assertEqual(a, b)

    def test_data_symbol_type_differs(self) -> None:
        a = container_agent._normalize_declaration_signature("extern u8 D_X;")
        b = container_agent._normalize_declaration_signature("extern void *D_X;")
        self.assertNotEqual(a, b)


class ExternBlockSymbolNamesTests(unittest.TestCase):
    def test_extracts_names_in_first_seen_order(self) -> None:
        file_brief = (
            "== extern/prototype block (deduplicated) ==\n"
            "  extern s32 func_A(void *arg0);\n"
            "  extern u8 D_80328E00;\n"
            "\n"
            "== func_/D_ symbols referenced, by solved-body count ==\n"
            "  func_Z used in 3 solved bodies\n"
        )
        self.assertEqual(container_agent._extern_block_symbol_names(file_brief), ["func_A", "D_80328E00"])

    def test_none_found_when_section_absent(self) -> None:
        self.assertEqual(container_agent._extern_block_symbol_names("no sections here"), [])

    def test_none_found_section(self) -> None:
        file_brief = "== extern/prototype block (deduplicated) ==\n  (none found)\n"
        self.assertEqual(container_agent._extern_block_symbol_names(file_brief), [])


class BuildPromptDoNotRedeclareRuleTests(unittest.TestCase):
    def test_rule_line_lists_extern_block_names(self) -> None:
        file_brief = (
            "== extern/prototype block (deduplicated) ==\n"
            "  extern s32 func_A(void *arg0);\n"
        )
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief=file_brief, asm_text="asm",
            best_candidates=[], permuter_seed=None, batch_path=Path("/tmp/batch.json"),
        )
        self.assertIn("The file already declares these callees/data (do not redeclare): func_A", prompt)

    def test_no_rule_line_when_extern_block_empty(self) -> None:
        file_brief = "== extern/prototype block (deduplicated) ==\n  (none found)\n"
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief=file_brief, asm_text="asm",
            best_candidates=[], permuter_seed=None, batch_path=Path("/tmp/batch.json"),
        )
        self.assertNotIn("do not redeclare", prompt)

    def test_rule_line_mentions_companion_edit_type_conflicts(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[], permuter_seed=None, batch_path=Path("/tmp/batch.json"),
            type_conflicts=[{
                "name": "func_87C0068C",
                "file_declaration": "extern void func_87C0068C(void *arg0);",
                "companion_edit": True,
            }],
        )
        self.assertIn(
            "the file declares func_87C0068C as `extern void func_87C0068C(void *arg0);`; "
            "your batch retyped it via a companion edit.",
            prompt,
        )

    def test_rule_line_omits_non_companion_edit_conflicts(self) -> None:
        prompt = container_agent.build_prompt(
            owner="func_1", source_rel="disasm/src/X.c", file_brief="brief", asm_text="asm",
            best_candidates=[], permuter_seed=None, batch_path=Path("/tmp/batch.json"),
            type_conflicts=[{
                "name": "func_87C0068C",
                "file_declaration": "extern void func_87C0068C(void *arg0);",
                "companion_edit": False,
            }],
        )
        self.assertNotIn("retyped it via a companion edit", prompt)


class RunIterationDeclarationHygieneTests(unittest.TestCase):
    def test_drops_already_declared_statement_before_probing(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            source_path = repo_dir / "disasm" / "src" / "X.c"
            source_path.parent.mkdir(parents=True)
            source_path.write_text(
                "void func_A(void) {\n    return;\n}\n\nvoid func_1(void) {\n    return;\n}\n",
                encoding="utf-8",
            )
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            batch = {
                "source": "disasm/src/X.c",
                "declarations": "extern void func_A(void);\nextern u8 D_NEW;",
                "candidates": [{"function": owner, "label": "a", "body": "void func_1(void) { return; }"}],
            }
            result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{"function": owner, "label": "a", "status": "rejected", "similarity_score": 0.1}],
            }
            seen_batches: list[dict] = []
            logger = container_agent.Logger(out_dir / "log.txt")
            batch_path = out_dir / "batches" / "func_1_iter0.json"
            container_agent.save_json(batch_path, batch)

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                seen_batches.append(container_agent.load_json(batch_path_arg))
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe):
                container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=0.0, logger=logger,
                )

            self.assertEqual(len(seen_batches), 1)
            self.assertEqual(seen_batches[0]["declarations"], "extern u8 D_NEW;")
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
            self.assertIn("dropping already-declared statement", log_text)
            self.assertIn("extern void func_A(void);", log_text)

    def test_type_conflict_becomes_companion_edit_and_is_recorded(self) -> None:
        # Issue #38 / real-run repro: the file's stale "extern void" for
        # func_87C0068C must not silently win, nor be redeclared alongside
        # the batch's "extern f64" -- it must become a companion_edit and
        # drop out of "declarations" entirely.
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            source_path = repo_dir / "disasm" / "src" / "X.c"
            source_path.parent.mkdir(parents=True)
            old_line = "extern void func_87C0068C(void *arg0);"
            source_path.write_text(
                f"{old_line}\n\nvoid func_1(void) {{\n    return;\n}}\n", encoding="utf-8",
            )
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            new_line = "extern f64 func_87C0068C(void *);"
            batch = {
                "source": "disasm/src/X.c",
                "declarations": new_line,
                "candidates": [{"function": owner, "label": "a", "body": "void func_1(void) { return; }"}],
            }
            result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{"function": owner, "label": "a", "status": "rejected", "similarity_score": 0.1}],
            }
            seen_batches: list[dict] = []
            logger = container_agent.Logger(out_dir / "log.txt")
            batch_path = out_dir / "batches" / "func_1_iter0.json"
            container_agent.save_json(batch_path, batch)

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                seen_batches.append(container_agent.load_json(batch_path_arg))
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe):
                container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=0.0, logger=logger,
                )

            self.assertEqual(len(seen_batches), 1)
            self.assertEqual(seen_batches[0]["declarations"], "")
            self.assertEqual(
                seen_batches[0]["companion_edits"],
                [{"function": "func_87C0068C", "old": old_line, "new": new_line}],
            )
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
            self.assertIn("TYPE CONFLICT", log_text)
            self.assertIn("companion edit created", log_text)
            self.assertEqual(len(owner_state["type_conflicts"]), 1)
            self.assertEqual(owner_state["type_conflicts"][0]["name"], "func_87C0068C")
            self.assertTrue(owner_state["type_conflicts"][0]["companion_edit"])

    def test_pragma_owner_type_conflict_keeps_declaration_and_warns(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            source_path = repo_dir / "disasm" / "src" / "X.c"
            source_path.parent.mkdir(parents=True)
            old_line = "extern void func_87C0068C(void *arg0);"
            source_path.write_text(
                f"{old_line}\n\n"
                '#pragma GLOBAL_ASM("asm/nonmatchings/X/func_87C0068C.s")\n'
                "void func_87C0068C(void *arg0);\n\n"
                "void func_1(void) {\n    return;\n}\n",
                encoding="utf-8",
            )
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            new_line = "extern f64 func_87C0068C(void *);"
            batch = {
                "source": "disasm/src/X.c",
                "declarations": new_line,
                "candidates": [{"function": owner, "label": "a", "body": "void func_1(void) { return; }"}],
            }
            result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{"function": owner, "label": "a", "status": "rejected", "similarity_score": 0.1}],
            }
            seen_batches: list[dict] = []
            logger = container_agent.Logger(out_dir / "log.txt")
            batch_path = out_dir / "batches" / "func_1_iter0.json"
            container_agent.save_json(batch_path, batch)

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                seen_batches.append(container_agent.load_json(batch_path_arg))
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe):
                container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=0.0, logger=logger,
                )

            self.assertEqual(len(seen_batches), 1)
            self.assertEqual(seen_batches[0]["declarations"], new_line)
            self.assertNotIn("companion_edits", seen_batches[0])
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
            self.assertIn("WARNING TYPE CONFLICT", log_text)
            self.assertIn("no companion edit", log_text)
            self.assertEqual(len(owner_state["type_conflicts"]), 1)
            self.assertFalse(owner_state["type_conflicts"][0]["companion_edit"])


class RunIterationPermuterDeclarationsTests(unittest.TestCase):
    def test_permuter_receives_declarations_after_type_conflict_filtering(self) -> None:
        # Regression for the real-run bug: the permuter's base.c must never
        # see the file's already-conflicting declaration alongside the
        # batch's -- run_permuter must get exactly the post-filter string,
        # not the batch's original unfiltered "declarations".
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            source_path = repo_dir / "disasm" / "src" / "X.c"
            source_path.parent.mkdir(parents=True)
            source_path.write_text(
                "extern void func_87C0068C(void *arg0);\n\nvoid func_1(void) {\n    return;\n}\n",
                encoding="utf-8",
            )
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            owner_state = container_agent._new_owner_state()
            batch = {
                "source": "disasm/src/X.c",
                "declarations": "extern f64 func_87C0068C(void *);",
                "candidates": [{"function": owner, "label": "a", "body": "body_a"}],
            }
            result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{
                    "function": owner, "label": "a", "status": "near_miss",
                    "similarity_score": 0.97, "futility": None,
                }],
            }
            permuter_result = {"timed_out": False, "outputs": [], "best": None}
            logger = container_agent.Logger(out_dir / "log.txt")
            batch_path = out_dir / "batches" / "func_1_iter0.json"
            container_agent.save_json(batch_path, batch)
            jobs: list = []

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe), \
                 mock.patch.object(container_agent, "run_permuter", return_value=permuter_result) as run_permuter_mock:
                container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=30.0, logger=logger,
                    permuter_jobs=jobs,
                )
                jobs[0].thread.join(timeout=5.0)

        run_permuter_mock.assert_called_once()
        # The dropped/companion-edited statement must not reach the permuter.
        declarations_arg = run_permuter_mock.call_args[0][5]
        self.assertEqual(declarations_arg, "")


# ---------------------------------------------------------------------------
# Part C: owner ordering / --max-instructions
# ---------------------------------------------------------------------------

class OwnerOrderingTests(unittest.TestCase):
    def test_owner_order_file_reorders_by_source_appearance(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp)
            source_rel = "disasm/src/X.c"
            source_path = repo_dir / source_rel
            source_path.parent.mkdir(parents=True)
            source_path.write_text(
                '#pragma GLOBAL_ASM("asm/nonmatchings/X/func_b.s")\n'
                "void func_b(void);\n\n"
                '#pragma GLOBAL_ASM("asm/nonmatchings/X/func_a.s")\n'
                "void func_a(void);\n",
                encoding="utf-8",
            )
            # pragma_targets ranks func_a (10 instructions) before func_b (50)
            # by size; --owner-order file must instead follow the source,
            # where func_b appears first.
            fake_stdout = json.dumps({"targets": [
                {"function": "func_a", "instructions": 10},
                {"function": "func_b", "instructions": 50},
            ]})
            with mock.patch.object(
                container_agent.subprocess, "run",
                return_value=SimpleNamespace(returncode=0, stdout=fake_stdout, stderr=""),
            ):
                size_order = container_agent.discover_owners(repo_dir, source_rel, owner_order="size")
                file_order = container_agent.discover_owners(repo_dir, source_rel, owner_order="file")
        self.assertEqual(size_order, ["func_a", "func_b"])
        self.assertEqual(file_order, ["func_b", "func_a"])

    def test_max_instructions_forwarded_to_pragma_targets_command(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp)
            fake_stdout = json.dumps({"targets": [{"function": "func_a", "instructions": 10}]})
            with mock.patch.object(
                container_agent.subprocess, "run",
                return_value=SimpleNamespace(returncode=0, stdout=fake_stdout, stderr=""),
            ) as run_mock:
                container_agent.discover_owners(repo_dir, "disasm/src/X.c", max_instructions=64)
            command = run_mock.call_args[0][0]
        self.assertIn("--max-instructions", command)
        self.assertEqual(command[command.index("--max-instructions") + 1], "64")

    def test_logs_owner_order_with_instruction_counts(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp)
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")
            fake_stdout = json.dumps({"targets": [
                {"function": "func_a", "instructions": 10},
                {"function": "func_b", "instructions": 50},
            ]})
            with mock.patch.object(
                container_agent.subprocess, "run",
                return_value=SimpleNamespace(returncode=0, stdout=fake_stdout, stderr=""),
            ):
                container_agent.discover_owners(repo_dir, "disasm/src/X.c", logger=logger)
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
        self.assertIn("func_a(10)", log_text)
        self.assertIn("func_b(50)", log_text)

    def test_no_logging_when_logger_omitted(self) -> None:
        # Existing callers (and DiscoverOwnersTests) rely on the logger-less
        # default not raising and not requiring a Logger instance.
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp)
            fake_stdout = json.dumps({"targets": [{"function": "func_a", "instructions": 10}]})
            with mock.patch.object(
                container_agent.subprocess, "run",
                return_value=SimpleNamespace(returncode=0, stdout=fake_stdout, stderr=""),
            ):
                owners = container_agent.discover_owners(repo_dir, "disasm/src/X.c")
        self.assertEqual(owners, ["func_a"])


class ArgParsingTests(unittest.TestCase):
    def test_defaults(self) -> None:
        args = container_agent.parse_args([
            "--source", "disasm/src/X.c", "--out", "/tmp/out",
        ])
        self.assertEqual(args.owner_order, "size")
        self.assertIsNone(args.max_instructions)
        self.assertEqual(args.permuter_bodies, container_agent.DEFAULT_PERMUTER_BODIES)
        self.assertEqual(args.generator_timeout, container_agent.DEFAULT_GENERATOR_TIMEOUT)
        self.assertEqual(container_agent.DEFAULT_GENERATOR_TIMEOUT, 1800.0)
        # --probe-tool is unset by default (None) so main() can fall back to
        # the PROBE_TOOL env var -- see ProbeToolResolutionTests below.
        self.assertIsNone(args.probe_tool)

    def test_overrides(self) -> None:
        args = container_agent.parse_args([
            "--source", "disasm/src/X.c", "--out", "/tmp/out",
            "--owner-order", "file", "--max-instructions", "48", "--permuter-bodies", "5",
            "--probe-tool", "off",
        ])
        self.assertEqual(args.owner_order, "file")
        self.assertEqual(args.max_instructions, 48)
        self.assertEqual(args.permuter_bodies, 5)
        self.assertEqual(args.probe_tool, "off")


class ProbeToolResolutionTests(unittest.TestCase):
    """main()'s --probe-tool/PROBE_TOOL precedence: an explicit --probe-tool
    wins; otherwise fall back to the PROBE_TOOL env var; otherwise default to
    "on". Exercised directly against parse_args's contract plus main()'s
    resolution expression, without needing to run a whole owner loop."""

    def _resolve(self, argv, env):
        args = container_agent.parse_args(argv)
        with mock.patch.dict(container_agent.os.environ, env, clear=False):
            probe_tool_arg = args.probe_tool or container_agent.os.environ.get("PROBE_TOOL", "on")
        return probe_tool_arg != "off"

    def test_flag_wins_over_env(self) -> None:
        argv = ["--source", "disasm/src/X.c", "--out", "/tmp/out", "--probe-tool", "off"]
        self.assertFalse(self._resolve(argv, {"PROBE_TOOL": "on"}))

    def test_env_used_when_flag_absent(self) -> None:
        argv = ["--source", "disasm/src/X.c", "--out", "/tmp/out"]
        self.assertFalse(self._resolve(argv, {"PROBE_TOOL": "off"}))
        self.assertTrue(self._resolve(argv, {"PROBE_TOOL": "on"}))

    def test_defaults_on_when_neither_set(self) -> None:
        argv = ["--source", "disasm/src/X.c", "--out", "/tmp/out"]
        env = dict(container_agent.os.environ)
        env.pop("PROBE_TOOL", None)
        with mock.patch.dict(container_agent.os.environ, env, clear=True):
            args = container_agent.parse_args(argv)
            probe_tool_arg = args.probe_tool or container_agent.os.environ.get("PROBE_TOOL", "on")
        self.assertEqual(probe_tool_arg, "on")


# ---------------------------------------------------------------------------
# Part D: background permuter jobs
# ---------------------------------------------------------------------------

class SelectPermuterBodiesTests(unittest.TestCase):
    def test_ranks_best_first_dedupes_and_caps_at_limit(self) -> None:
        scored = [
            {"label": "a", "similarity_score": 0.90},
            {"label": "b", "similarity_score": 0.99},
            {"label": "c", "similarity_score": 0.95},
            # duplicate body of "b" (whitespace-different) must be skipped
            {"label": "d", "similarity_score": 0.97},
        ]
        candidate_bodies = {
            "a": "body_a", "b": "body_b", "c": "body_c", "d": "  body_b  ",
        }
        selected = container_agent._select_permuter_bodies(scored, candidate_bodies, limit=2)
        self.assertEqual([label for label, _ in selected], ["b", "c"])

    def test_excludes_normalized_only_matches(self) -> None:
        scored = [{
            "label": "a", "status": "probe_rejected",
            "similarity_score": 1.0, "raw_similarity_score": 0.5,
        }]
        candidate_bodies = {"a": "body_a"}
        selected = container_agent._select_permuter_bodies(scored, candidate_bodies, limit=3)
        self.assertEqual(selected, [])

    def test_skips_attempts_with_no_body(self) -> None:
        scored = [{"label": "missing", "similarity_score": 0.9}]
        selected = container_agent._select_permuter_bodies(scored, {}, limit=3)
        self.assertEqual(selected, [])


class PollPermuterJobsTests(unittest.TestCase):
    def _finished_job(self, owner, iteration, results) -> "container_agent.PermuterJob":
        job = container_agent.PermuterJob(thread=None, owner=owner, iteration=iteration, labels=[r["label"] for r in results])
        job.results = results
        job.thread = SimpleNamespace(is_alive=lambda: False)
        return job

    def test_folds_new_results_and_keeps_lowest_score_as_seed(self) -> None:
        owner_state = container_agent._new_owner_state()
        logger = container_agent.Logger(Path(tempfile.mkdtemp()) / "log.txt")
        job = self._finished_job("func_1", 0, [
            {"label": "a", "timed_out": False, "best": {"score": 5, "code": "body_a"}},
            {"label": "b", "timed_out": False, "best": {"score": 1, "code": "body_b"}},
        ])
        jobs = [job]
        container_agent.poll_permuter_jobs(jobs, owner_state, logger=logger)
        self.assertEqual(owner_state["permuter_seed"]["score"], 1)
        self.assertEqual(owner_state["permuter_seed"]["body"], "body_b")
        self.assertEqual(len(owner_state["permuter_runs"]), 2)
        self.assertEqual(jobs, [])  # thread not alive -> dropped

    def test_does_not_regress_seed_with_a_worse_score(self) -> None:
        owner_state = container_agent._new_owner_state()
        owner_state["permuter_seed"] = {"score": 0, "body": "best_body", "iteration": 0}
        logger = container_agent.Logger(Path(tempfile.mkdtemp()) / "log.txt")
        job = self._finished_job("func_1", 1, [
            {"label": "a", "timed_out": False, "best": {"score": 3, "code": "worse_body"}},
        ])
        container_agent.poll_permuter_jobs([job], owner_state, logger=logger)
        self.assertEqual(owner_state["permuter_seed"]["score"], 0)
        self.assertEqual(owner_state["permuter_seed"]["body"], "best_body")

    def test_already_consumed_results_are_not_reapplied(self) -> None:
        owner_state = container_agent._new_owner_state()
        logger = container_agent.Logger(Path(tempfile.mkdtemp()) / "log.txt")
        job = self._finished_job("func_1", 0, [
            {"label": "a", "timed_out": False, "best": {"score": 4, "code": "body_a"}},
        ])
        # still running -> kept in the jobs list across two polls
        job.thread = SimpleNamespace(is_alive=lambda: True)
        jobs = [job]
        container_agent.poll_permuter_jobs(jobs, owner_state, logger=logger)
        self.assertEqual(len(owner_state["permuter_runs"]), 1)
        container_agent.poll_permuter_jobs(jobs, owner_state, logger=logger)
        self.assertEqual(len(owner_state["permuter_runs"]), 1)  # not doubled
        self.assertEqual(jobs, [job])  # still tracked (thread still alive)

    def test_none_best_output_records_run_without_seed(self) -> None:
        owner_state = container_agent._new_owner_state()
        logger = container_agent.Logger(Path(tempfile.mkdtemp()) / "log.txt")
        job = self._finished_job("func_1", 0, [
            {"label": "a", "timed_out": True, "best": None},
        ])
        container_agent.poll_permuter_jobs([job], owner_state, logger=logger)
        self.assertNotIn("permuter_seed", owner_state)
        self.assertEqual(len(owner_state["permuter_runs"]), 1)


class StartPermuterJobTests(unittest.TestCase):
    def test_runs_bodies_sequentially_via_run_permuter(self) -> None:
        calls: list[str] = []

        def fake_run_permuter(repo_dir, out_dir, owner, iteration, body, declarations, *, permuter_seconds, logger, label_suffix=""):
            calls.append(body)
            return {"timed_out": False, "outputs": [], "best": {"score": 0, "code": body}}

        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")
            with mock.patch.object(container_agent, "run_permuter", side_effect=fake_run_permuter):
                job = container_agent.start_permuter_job(
                    repo_dir, out_dir, "func_1", 0,
                    [("a", "body_a"), ("b", "body_b")], None,
                    permuter_seconds=5.0, logger=logger,
                )
                job.thread.join(timeout=5.0)
        self.assertFalse(job.thread.is_alive())
        self.assertEqual(calls, ["body_a", "body_b"])
        self.assertEqual([entry["label"] for entry in job.results], ["a", "b"])


class TerminateAllPermutersTests(unittest.TestCase):
    def test_terminates_registered_running_processes(self) -> None:
        fake_process = mock.Mock()
        fake_process.poll.return_value = None
        container_agent._register_permuter_process(fake_process)
        try:
            with mock.patch.object(container_agent, "_terminate_process_group") as terminate_mock:
                container_agent.terminate_all_permuters()
            terminate_mock.assert_called_once_with(fake_process)
        finally:
            container_agent._unregister_permuter_process(fake_process)
        self.assertNotIn(fake_process, container_agent._ACTIVE_PERMUTER_PROCESSES)

    def test_skips_already_exited_processes(self) -> None:
        fake_process = mock.Mock()
        fake_process.poll.return_value = 0
        container_agent._register_permuter_process(fake_process)
        with mock.patch.object(container_agent, "_terminate_process_group") as terminate_mock:
            container_agent.terminate_all_permuters()
        terminate_mock.assert_not_called()
        self.assertNotIn(fake_process, container_agent._ACTIVE_PERMUTER_PROCESSES)

    def test_finalize_run_terminates_permuters(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp)
            summary = {"runs": []}
            with mock.patch.object(container_agent, "terminate_all_permuters") as terminate_mock:
                container_agent._finalize_run(summary, out_dir, "completed", time.monotonic())
            terminate_mock.assert_called_once()


# ---------------------------------------------------------------------------
# Graceful termination (SIGTERM/SIGINT): request_stop/_STOP_REQUESTED, the
# bounded-process registry _run_bounded uses, and the safe-point checks in
# process_owner/run_iteration/main() that route a termination request to the
# run's normal finalize path (stopped_reason "terminated", exit code 143)
# instead of letting the driver wait out a 30-minute generator cap.
# ---------------------------------------------------------------------------

class _StopFlagTestCase(unittest.TestCase):
    """Base class that resets the module-level termination flag/registry
    around every test, so one test's SIGTERM simulation can never bleed into
    another (mirrors how _ACTIVE_PERMUTER_PROCESSES tests clean up).

    Also saves/restores the process's real SIGTERM/SIGINT handlers: a test
    that calls container_agent.main() installs real handlers via
    signal.signal(), which -- unlike everything else here -- is genuine
    process-wide state that would otherwise leak into every test that runs
    afterwards in the same `unittest discover` process (including other
    test_*.py files' subprocess-using tests)."""

    def setUp(self) -> None:
        container_agent._STOP_REQUESTED.clear()
        container_agent._ACTIVE_BOUNDED_PROCESS = None
        self._prior_sigterm = signal.getsignal(signal.SIGTERM)
        self._prior_sigint = signal.getsignal(signal.SIGINT)

    def tearDown(self) -> None:
        container_agent._STOP_REQUESTED.clear()
        container_agent._ACTIVE_BOUNDED_PROCESS = None
        signal.signal(signal.SIGTERM, self._prior_sigterm)
        signal.signal(signal.SIGINT, self._prior_sigint)


class RequestStopTests(_StopFlagTestCase):
    def test_sets_stop_requested_flag(self) -> None:
        self.assertFalse(container_agent.stop_requested())
        container_agent.request_stop(signal.SIGTERM)
        self.assertTrue(container_agent.stop_requested())

    def test_terminates_registered_active_bounded_process(self) -> None:
        fake_process = mock.Mock()
        fake_process.poll.return_value = None
        container_agent._register_bounded_process(fake_process)
        with mock.patch.object(container_agent, "_terminate_process_group") as terminate_mock:
            container_agent.request_stop(signal.SIGTERM)
        terminate_mock.assert_called_once_with(fake_process)

    def test_skips_already_exited_active_bounded_process(self) -> None:
        fake_process = mock.Mock()
        fake_process.poll.return_value = 0
        container_agent._register_bounded_process(fake_process)
        with mock.patch.object(container_agent, "_terminate_process_group") as terminate_mock:
            container_agent.request_stop(signal.SIGTERM)
        terminate_mock.assert_not_called()

    def test_noop_when_nothing_registered(self) -> None:
        with mock.patch.object(container_agent, "_terminate_process_group") as terminate_mock:
            container_agent.request_stop(signal.SIGTERM)
        terminate_mock.assert_not_called()
        self.assertTrue(container_agent.stop_requested())

    def test_logs_once_via_logger_with_signal_name_and_message(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            logger = container_agent.Logger(Path(tmp) / "log.txt")
            container_agent.request_stop(signal.SIGTERM, logger=logger)
            container_agent.request_stop(signal.SIGTERM, logger=logger)
            log_text = (Path(tmp) / "log.txt").read_text(encoding="utf-8")
        self.assertEqual(log_text.count("termination requested"), 1)
        self.assertIn("SIGTERM", log_text)
        self.assertIn("finishing current step", log_text)


class RunBoundedTests(_StopFlagTestCase):
    def test_returns_completed_process_and_unregisters(self) -> None:
        result = container_agent._run_bounded(
            [sys.executable, "-c", "print('hi')"], cwd=Path.cwd(), timeout=10.0,
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), "hi")
        self.assertIsNone(container_agent._ACTIVE_BOUNDED_PROCESS)

    def test_active_process_is_killed_when_termination_requested_mid_call(self) -> None:
        """A Popen standing in for a running generator/probe call is
        terminated once the stop flag/registry-based termination fires --
        the driver must not wait out the child's full timeout."""
        with tempfile.TemporaryDirectory() as tmp:
            marker = Path(tmp) / "started"
            script = (
                "import pathlib, time; "
                f"pathlib.Path({str(marker)!r}).write_text('1'); time.sleep(30)"
            )

            def trigger_termination() -> None:
                deadline = time.monotonic() + 5.0
                while not marker.exists() and time.monotonic() < deadline:
                    time.sleep(0.02)
                container_agent.request_stop(signal.SIGTERM)

            trigger = threading.Thread(target=trigger_termination)
            trigger.start()
            started = time.monotonic()
            result = container_agent._run_bounded(
                [sys.executable, "-c", script], cwd=Path(tmp), timeout=25.0,
            )
            trigger.join(timeout=5.0)

        self.assertLess(time.monotonic() - started, 15.0)
        self.assertNotEqual(result.returncode, 0)
        self.assertIsNone(container_agent._ACTIVE_BOUNDED_PROCESS)


class SaveStateSummaryRewriteTests(_StopFlagTestCase):
    def test_save_state_writes_summary_json_when_given(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            state_path = out_dir / "state.json"
            summary = {"stopped_reason": None, "matched": ["func_1"]}
            container_agent._save_state(
                {"func_1": {}}, state_path, repo_dir=repo_dir, out_dir=out_dir, summary=summary,
            )
            written = json.loads((out_dir / "summary.json").read_text(encoding="utf-8"))
        self.assertEqual(written, summary)

    def test_save_state_does_not_write_summary_json_when_omitted(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            state_path = out_dir / "state.json"
            container_agent._save_state({"func_1": {}}, state_path, repo_dir=repo_dir, out_dir=out_dir)
            self.assertFalse((out_dir / "summary.json").exists())

    def test_process_owner_rewrites_summary_json_on_every_iteration_save(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            owner = "func_1"
            source_rel = "disasm/src/X.c"

            def batch_for_iteration(_n):
                return {"source": source_rel, "candidates": [{"function": owner, "label": "a", "body": "b"}]}

            def result_for_call(_n, _batch):
                return {
                    "batch_status": "no_candidate_accepted", "accepted": [],
                    "attempts": [{"function": owner, "label": "a", "status": "rejected", "similarity_score": 0.3}],
                }

            owner_state = container_agent._new_owner_state()
            state = {owner: owner_state}
            state_path = out_dir / "state.json"
            logger = container_agent.Logger(out_dir / "log.txt")
            summary = {"iteration_counts": {}, "best_per_owner": {}, "matched": [], "stopped_reason": None}

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator", side_effect=make_invoke_generator(batch_for_iteration)), \
                 mock.patch.object(container_agent, "invoke_probe", side_effect=make_invoke_probe(result_for_call)):
                status = container_agent.process_owner(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                    owner_state=owner_state, state=state, state_path=state_path,
                    deadline=time.monotonic() + 60.0, max_iterations=1, plateau=100,
                    permuter_seconds=0.0, generator_cmd="generator --prompt {prompt} --batch {batch}",
                    logger=logger, summary=summary,
                )

            self.assertEqual(status, "max_iterations")
            written = json.loads((out_dir / "summary.json").read_text(encoding="utf-8"))
            # Written mid-run (process_owner never calls _finalize_run
            # itself), so stopped_reason is still None here -- proof this
            # came from the in-loop _save_state rewrite, not the run's
            # final write.
            self.assertIsNone(written["stopped_reason"])
            self.assertEqual(written["iteration_counts"][owner], 1)


class ProcessOwnerTerminationTests(_StopFlagTestCase):
    def _base_kwargs(self, tmp, *, owner="func_1", source_rel="disasm/src/X.c"):
        repo_dir = Path(tmp) / "repo"
        repo_dir.mkdir()
        out_dir = Path(tmp) / "out"
        owner_state = container_agent._new_owner_state()
        state = {owner: owner_state}
        state_path = out_dir / "state.json"
        logger = container_agent.Logger(out_dir / "log.txt")
        return dict(
            repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
            owner_state=owner_state, state=state, state_path=state_path,
            deadline=time.monotonic() + 60.0, max_iterations=50, plateau=6,
            permuter_seconds=0.0, generator_cmd="generator --prompt {prompt} --batch {batch}",
            logger=logger,
        ), owner_state

    def test_stop_flag_set_before_loop_skips_generator_entirely(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            kwargs, owner_state = self._base_kwargs(tmp)
            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator") as gen_mock, \
                 mock.patch.object(container_agent, "invoke_probe") as probe_mock:
                container_agent._STOP_REQUESTED.set()
                status = container_agent.process_owner(**kwargs)
        self.assertEqual(status, "terminated")
        self.assertEqual(owner_state["status"], "terminated")
        gen_mock.assert_not_called()
        probe_mock.assert_not_called()

    def test_stop_flag_set_during_generator_call_stops_without_counting_a_failure(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            kwargs, owner_state = self._base_kwargs(tmp)

            def gen_stub(command, *, cwd, timeout):
                # Simulate the signal arriving while this call was "in
                # flight": by the time it returns, the flag is set.
                container_agent._STOP_REQUESTED.set()
                return SimpleNamespace(returncode=-15, stdout="", stderr="")

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator", side_effect=gen_stub), \
                 mock.patch.object(container_agent, "invoke_probe") as probe_mock:
                status = container_agent.process_owner(**kwargs)
        self.assertEqual(status, "terminated")
        self.assertEqual(owner_state["status"], "terminated")
        probe_mock.assert_not_called()

    def test_stop_flag_set_during_probe_call_stops_without_incrementing_plateau(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            kwargs, owner_state = self._base_kwargs(tmp)
            source_rel = kwargs["source_rel"]
            owner = kwargs["owner"]

            def gen_stub(command, *, cwd, timeout):
                batch_path = _extract_path_arg(command, "--batch")
                batch_path.parent.mkdir(parents=True, exist_ok=True)
                container_agent.save_json(batch_path, {
                    "source": source_rel,
                    "candidates": [{"function": owner, "label": "a", "body": "b"}],
                })
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            def probe_stub(repo_dir, batch_path, result_path, *, timeout):
                container_agent._STOP_REQUESTED.set()
                return SimpleNamespace(returncode=-15, stdout="", stderr="")

            with mock.patch.object(container_agent, "file_brief_text", return_value="brief"), \
                 mock.patch.object(container_agent, "owner_asm_text", return_value="asm"), \
                 mock.patch.object(container_agent, "get_m2c_draft", return_value=None), \
                 mock.patch.object(container_agent, "invoke_generator", side_effect=gen_stub), \
                 mock.patch.object(container_agent, "invoke_probe", side_effect=probe_stub):
                status = container_agent.process_owner(**kwargs)
        self.assertEqual(status, "terminated")
        self.assertEqual(owner_state["status"], "terminated")
        self.assertEqual(owner_state["plateau_count"], 0)


class MainTerminationTests(_StopFlagTestCase):
    def test_stop_flag_before_owner_loop_yields_terminated_summary_and_exit_143(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            source_rel = "disasm/src/X.c"

            with mock.patch.object(container_agent, "discover_owners", return_value=["func_1"]), \
                 mock.patch.object(container_agent, "invoke_generator") as gen_mock, \
                 mock.patch.object(container_agent, "invoke_probe") as probe_mock:
                container_agent._STOP_REQUESTED.set()
                exit_code = container_agent.main([
                    "--source", source_rel, "--out", str(out_dir), "--repo", str(repo_dir),
                    "--generator-cmd", "fake-gen --prompt {prompt} --batch {batch}",
                ])

            gen_mock.assert_not_called()
            probe_mock.assert_not_called()
            self.assertEqual(exit_code, 143)
            summary = json.loads((out_dir / "summary.json").read_text(encoding="utf-8"))
            self.assertEqual(summary["stopped_reason"], "terminated")
            self.assertEqual(summary["runs"][-1]["stop_reason"], "terminated")

    def test_summary_json_written_immediately_on_startup(self) -> None:
        """Even before any owner is processed (before _finalize_run ever
        runs), main() must leave a current summary.json with this run's
        fresh "runs" entry on disk -- the fix for the original bug: a run
        killed before _finalize_run used to leave no summary.json at all.
        Simulate a crash right after owner discovery (before the owner
        loop/_finalize_run) to observe that intermediate write."""
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            source_rel = "disasm/src/X.c"

            with mock.patch.object(
                container_agent, "discover_owners", side_effect=RuntimeError("simulated crash"),
            ):
                with self.assertRaises(RuntimeError):
                    container_agent.main([
                        "--source", source_rel, "--out", str(out_dir), "--repo", str(repo_dir),
                        "--generator-cmd", "fake-gen --prompt {prompt} --batch {batch}",
                    ])
            summary = json.loads((out_dir / "summary.json").read_text(encoding="utf-8"))
            self.assertEqual(len(summary["runs"]), 1)
            self.assertIsNone(summary["runs"][0]["stop_reason"])
            self.assertIsNone(summary["runs"][0]["ended"])


# ---------------------------------------------------------------------------
# Probe-stats export: <out>/probe-stats/probe-stats.jsonl, copied from the
# runner's own PRAGMA_PROBE_STATS-resolved file on every state save and at
# finalize.
# ---------------------------------------------------------------------------

class ProbeStatsExportTests(unittest.TestCase):
    def test_copies_default_repo_stats_file_into_out_dir(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            source = repo_dir / "disasm" / "probe-stats" / "probe-stats.jsonl"
            source.parent.mkdir(parents=True)
            source.write_text('{"batch_id": "a"}\n{"batch_id": "b"}\n', encoding="utf-8")

            with mock.patch.dict(os.environ, {}, clear=False):
                os.environ.pop("PRAGMA_PROBE_STATS", None)
                container_agent.export_probe_stats(repo_dir, out_dir)

            dest = out_dir / "probe-stats" / "probe-stats.jsonl"
            self.assertTrue(dest.is_file())
            self.assertEqual(dest.read_text(encoding="utf-8"), source.read_text(encoding="utf-8"))

    def test_honours_pragma_probe_stats_env_override(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            custom = Path(tmp) / "custom-stats.jsonl"
            custom.write_text('{"batch_id": "custom"}\n', encoding="utf-8")

            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": str(custom)}):
                container_agent.export_probe_stats(repo_dir, out_dir)

            dest = out_dir / "probe-stats" / "probe-stats.jsonl"
            self.assertTrue(dest.is_file())
            self.assertEqual(dest.read_text(encoding="utf-8"), '{"batch_id": "custom"}\n')

    def test_empty_env_var_disables_export(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            source = repo_dir / "disasm" / "probe-stats" / "probe-stats.jsonl"
            source.parent.mkdir(parents=True)
            source.write_text('{"batch_id": "a"}\n', encoding="utf-8")

            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": ""}):
                container_agent.export_probe_stats(repo_dir, out_dir)

            dest = out_dir / "probe-stats" / "probe-stats.jsonl"
            self.assertFalse(dest.exists())

    def test_missing_source_file_is_a_noop(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            with mock.patch.dict(os.environ, {}, clear=False):
                os.environ.pop("PRAGMA_PROBE_STATS", None)
                container_agent.export_probe_stats(repo_dir, out_dir)  # must not raise
            dest = out_dir / "probe-stats" / "probe-stats.jsonl"
            self.assertFalse(dest.exists())

    def test_save_state_exports_probe_stats(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            with mock.patch.object(container_agent, "export_probe_stats") as export_mock:
                container_agent._save_state({"a": 1}, out_dir / "state.json", repo_dir=repo_dir, out_dir=out_dir)
            export_mock.assert_called_once_with(repo_dir, out_dir)
            self.assertTrue((out_dir / "state.json").exists())

    def test_finalize_run_exports_probe_stats_when_repo_dir_given(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            summary = {"runs": []}
            with mock.patch.object(container_agent, "export_probe_stats") as export_mock:
                container_agent._finalize_run(
                    summary, out_dir, "completed", time.monotonic(), repo_dir=repo_dir,
                )
            export_mock.assert_called_once_with(repo_dir, out_dir)

    def test_finalize_run_skips_export_without_repo_dir(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp)
            summary = {"runs": []}
            with mock.patch.object(container_agent, "export_probe_stats") as export_mock:
                container_agent._finalize_run(summary, out_dir, "completed", time.monotonic())
            export_mock.assert_not_called()

    def test_end_to_end_candidate_file_run_copies_probe_stats(self) -> None:
        # A full --candidate-file run: the runner (invoke_probe, stubbed here)
        # never really writes disasm/probe-stats/probe-stats.jsonl, but the
        # export path only ever copies whatever is there -- simulate the
        # runner having already written it before the driver's own finalize
        # export snapshot runs.
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            source_rel = "disasm/src/X.c"
            source_path = repo_dir / source_rel
            source_path.parent.mkdir(parents=True)
            source_path.write_text("void func_1(void) {\n    return;\n}\n", encoding="utf-8")
            stats_source = repo_dir / "disasm" / "probe-stats" / "probe-stats.jsonl"
            stats_source.parent.mkdir(parents=True)
            stats_source.write_text('{"batch_id": "real-run"}\n', encoding="utf-8")

            out_dir = Path(tmp) / "out"
            candidate_file = Path(tmp) / "batch.json"
            candidate_file.write_text(
                json.dumps({
                    "source": source_rel,
                    "candidates": [{"function": "func_1", "label": "a", "body": "void func_1(void) { return; }"}],
                }),
                encoding="utf-8",
            )

            def result_for_call(_n, _batch):
                return {
                    "batch_status": "no_candidate_accepted", "accepted": [],
                    "attempts": [{"function": "func_1", "label": "a", "status": "rejected", "similarity_score": 0.5}],
                }

            with mock.patch.object(container_agent, "invoke_probe", side_effect=make_invoke_probe(result_for_call)), \
                 mock.patch.dict(os.environ, {}, clear=False):
                os.environ.pop("PRAGMA_PROBE_STATS", None)
                exit_code = container_agent.main([
                    "--source", source_rel, "--out", str(out_dir), "--repo", str(repo_dir),
                    "--candidate-file", str(candidate_file),
                ])

            self.assertEqual(exit_code, 0)
            dest = out_dir / "probe-stats" / "probe-stats.jsonl"
            self.assertTrue(dest.is_file())
            self.assertEqual(dest.read_text(encoding="utf-8"), '{"batch_id": "real-run"}\n')


# ---------------------------------------------------------------------------
# --seed-from: fresh-run seeding from earlier --out dirs
# ---------------------------------------------------------------------------

def _write_seed_state(seed_dir: Path, state: dict) -> None:
    container_agent.save_json(seed_dir / "state.json", state)


def _write_seed_accepted(seed_dir: Path, owner: str, body: str, *, label: str = "accepted") -> None:
    container_agent.save_json(
        seed_dir / "accepted" / f"{owner}.json",
        {
            "source": "disasm/src/X.c",
            "declarations": "",
            "candidates": [{"function": owner, "label": label, "body": body}],
        },
    )


def _candidate(label: str, similarity: float, *, raw: float | None = None, body: str = "") -> dict:
    return {
        "label": label,
        "similarity_score": similarity,
        "raw_similarity_score": raw if raw is not None else similarity,
        "mismatch_kind": None,
        "futility": None,
        "diagnostic": None,
        "body": body or f"body-for-{label}",
        "normalized_only": False,
        "feedback": {},
    }


class SeedOwnerStatesTests(unittest.TestCase):
    def test_new_schema_basic_import(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            seed_dir = Path(tmp) / "seed1"
            _write_seed_state(seed_dir, {
                "func_a": {
                    "status": "in_progress",
                    "iterations": 4,
                    "plateau_count": 2,
                    "history": [{"iteration": 0}],
                    "best_candidates": [
                        _candidate("hyp:one", 0.95, body="body_one"),
                        _candidate("hyp:two", 0.80, body="body_two"),
                    ],
                    "tried_bodies": ["hash1:decl1", "hash2:decl1"],
                    "tried_labels": ["hyp:one", "hyp:two"],
                    "m2c_draft": "f64 func_a(void) { return 0; }",
                    "permuter_seed": {"score": 3, "body": "permuted body", "iteration": 2, "label": "hyp:one"},
                },
            })
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")

            seeded = container_agent.seed_owner_states([seed_dir], logger=logger)
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")

        self.assertIn("func_a", seeded)
        owner_state = seeded["func_a"]
        # status/iterations/plateau/history are never imported.
        self.assertEqual(owner_state["status"], "in_progress")
        self.assertEqual(owner_state["iterations"], 0)
        self.assertEqual(owner_state["plateau_count"], 0)
        self.assertEqual(owner_state["history"], [])
        self.assertEqual(len(owner_state["best_candidates"]), 2)
        self.assertEqual(owner_state["best_candidates"][0]["label"], "hyp:one")
        self.assertEqual(owner_state["tried_bodies"], ["hash1:decl1", "hash2:decl1"])
        self.assertEqual(owner_state["tried_labels"], ["hyp:one", "hyp:two"])
        self.assertEqual(owner_state["m2c_draft"], "f64 func_a(void) { return 0; }")
        self.assertTrue(owner_state["m2c_draft_fetched"])
        self.assertEqual(owner_state["permuter_seed"]["score"], 3)
        self.assertEqual(owner_state["seeded_from"], [str(seed_dir)])
        self.assertEqual(owner_state["seed_best_similarity"], 0.95)
        self.assertIn("func_a: seeded 2 candidate(s), best 0.95", log_text)

    def test_old_schema_missing_tried_bodies_and_feedback(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            seed_dir = Path(tmp) / "seed_old"
            # Mirrors a real older out dir: best_candidates entries have no
            # "feedback"/"normalized_only" keys, and the owner has no
            # "tried_bodies"/"tried_labels" keys at all.
            _write_seed_state(seed_dir, {
                "func_b": {
                    "status": "plateau",
                    "best_similarity": 1.0,
                    "best_label": "x",
                    "iterations": 12,
                    "plateau_count": 6,
                    "history": [],
                    "best_candidates": [
                        {
                            "label": "x", "similarity_score": 0.93, "raw_similarity_score": 0.90,
                            "mismatch_kind": "register_allocation_only", "futility": None,
                            "diagnostic": None, "body": "old_body",
                        },
                    ],
                    "permuter_runs": [],
                },
            })
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")

            seeded = container_agent.seed_owner_states([seed_dir], logger=logger)

        self.assertIn("func_b", seeded)
        owner_state = seeded["func_b"]
        self.assertEqual(owner_state["tried_bodies"], [])
        self.assertEqual(owner_state["tried_labels"], [])
        self.assertIsNone(owner_state["m2c_draft"])
        self.assertNotIn("permuter_seed", owner_state)
        self.assertEqual(len(owner_state["best_candidates"]), 1)
        self.assertEqual(owner_state["best_candidates"][0]["body"], "old_body")
        self.assertEqual(owner_state["status"], "in_progress")
        self.assertEqual(owner_state["iterations"], 0)

    def test_merge_of_two_seeds_keeps_best_of_each(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            seed_a = Path(tmp) / "seed_a"
            seed_b = Path(tmp) / "seed_b"
            # seed_a alone fills the whole BEST_CANDIDATES_KEPT cap with
            # higher-scoring candidates than seed_b's single lower one.
            a_candidates = [
                _candidate(f"a:{i}", 0.9 - i * 0.01, body=f"a_body_{i}")
                for i in range(container_agent.BEST_CANDIDATES_KEPT)
            ]
            _write_seed_state(seed_a, {"func_c": {"status": "in_progress", "best_candidates": a_candidates}})
            _write_seed_state(seed_b, {
                "func_c": {
                    "status": "in_progress",
                    "best_candidates": [_candidate("b:only", 0.10, body="b_body_only")],
                },
            })
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")

            seeded = container_agent.seed_owner_states([seed_a, seed_b], logger=logger)

        owner_state = seeded["func_c"]
        bodies = {c["body"] for c in owner_state["best_candidates"]}
        # seed_b's one lead survives even though it ranks below every one of
        # seed_a's candidates and the cap alone would have dropped it.
        self.assertIn("b_body_only", bodies)
        for candidate in a_candidates:
            self.assertIn(candidate["body"], bodies)
        self.assertEqual(sorted(owner_state["seeded_from"]), sorted([str(seed_a), str(seed_b)]))
        # Ranked best-first overall.
        scores = [c["similarity_score"] for c in owner_state["best_candidates"]]
        self.assertEqual(scores, sorted(scores, reverse=True))

    def test_merge_dedupes_identical_bodies_across_sources(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            seed_a = Path(tmp) / "seed_a"
            seed_b = Path(tmp) / "seed_b"
            _write_seed_state(seed_a, {
                "func_d": {"status": "in_progress", "best_candidates": [_candidate("a:1", 0.7, body="  same body  ")]},
            })
            _write_seed_state(seed_b, {
                "func_d": {"status": "in_progress", "best_candidates": [_candidate("b:1", 0.6, body="same body")]},
            })
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")

            seeded = container_agent.seed_owner_states([seed_a, seed_b], logger=logger)

        owner_state = seeded["func_d"]
        self.assertEqual(len(owner_state["best_candidates"]), 1)
        # The higher-scoring source's copy wins the dedupe.
        self.assertEqual(owner_state["best_candidates"][0]["label"], "a:1")

    def test_accepted_owner_imports_body_as_candidate_and_logs_loudly(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            seed_dir = Path(tmp) / "seed_accepted"
            _write_seed_state(seed_dir, {
                "func_e": {"status": "accepted", "best_similarity": 1.0, "best_candidates": []},
            })
            _write_seed_accepted(seed_dir, "func_e", "f64 func_e(void) { return 1.0; }")
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")

            seeded = container_agent.seed_owner_states([seed_dir], logger=logger)
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")

        self.assertIn("func_e", seeded)
        owner_state = seeded["func_e"]
        self.assertEqual(owner_state["status"], "in_progress")  # not skipped/auto-accepted
        self.assertEqual(len(owner_state["best_candidates"]), 1)
        best = owner_state["best_candidates"][0]
        self.assertEqual(best["similarity_score"], 1.0)
        self.assertEqual(best["body"], "f64 func_e(void) { return 1.0; }")
        self.assertIn("ACCEPTED", log_text)
        self.assertIn("func_e", log_text)

    def test_accepted_owner_without_accepted_json_is_not_skipped(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            seed_dir = Path(tmp) / "seed_accepted_missing"
            _write_seed_state(seed_dir, {
                "func_f": {"status": "accepted", "best_similarity": 1.0, "best_candidates": []},
            })
            # No accepted/func_f.json written -- simulates a hand-built or
            # incomplete fixture.
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")

            seeded = container_agent.seed_owner_states([seed_dir], logger=logger)
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")

        # Still recorded (do not skip it; the host merge decides), just with
        # nothing to show for the accept itself.
        self.assertIn("func_f", seeded)
        owner_state = seeded["func_f"]
        self.assertEqual(owner_state["best_candidates"], [])
        self.assertEqual(owner_state["seeded_from"], [str(seed_dir)])
        self.assertIn("WARNING", log_text)
        self.assertIn("func_f", log_text)

    def test_owner_absent_from_every_seed_dir_is_not_returned(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            seed_dir = Path(tmp) / "seed"
            _write_seed_state(seed_dir, {"func_g": {"status": "in_progress", "best_candidates": []}})
            out_dir = Path(tmp) / "out"
            logger = container_agent.Logger(out_dir / "log.txt")

            seeded = container_agent.seed_owner_states([seed_dir], logger=logger)

        self.assertNotIn("func_nowhere", seeded)


class SeedFromCLITests(unittest.TestCase):
    def test_seed_from_wired_into_fresh_test_mode_run(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            source_rel = "disasm/src/X.c"
            source_path = repo_dir / source_rel
            source_path.parent.mkdir(parents=True)
            source_path.write_text("void func_1(void) {\n    return;\n}\n", encoding="utf-8")

            seed_dir = Path(tmp) / "seed"
            _write_seed_state(seed_dir, {
                "func_1": {
                    "status": "in_progress",
                    "best_candidates": [_candidate("seed:one", 0.77, body="seeded_body")],
                    "tried_labels": ["seed:one"],
                },
            })

            out_dir = Path(tmp) / "out"
            candidate_file = Path(tmp) / "batch.json"
            candidate_file.write_text(
                json.dumps({
                    "source": source_rel,
                    "candidates": [{"function": "func_1", "label": "a", "body": "void func_1(void) { return; }"}],
                }),
                encoding="utf-8",
            )

            def result_for_call(_n, _batch):
                return {
                    "batch_status": "no_candidate_accepted", "accepted": [],
                    "attempts": [{"function": "func_1", "label": "a", "status": "rejected", "similarity_score": 0.5}],
                }

            with mock.patch.object(container_agent, "invoke_probe", side_effect=make_invoke_probe(result_for_call)):
                exit_code = container_agent.main([
                    "--source", source_rel, "--out", str(out_dir), "--repo", str(repo_dir),
                    "--seed-from", str(seed_dir), "--candidate-file", str(candidate_file),
                ])

            self.assertEqual(exit_code, 0)
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
            state = json.loads((out_dir / "state.json").read_text(encoding="utf-8"))

        self.assertIn("func_1: seeded 1 candidate(s), best 0.77", log_text)
        self.assertEqual(state["func_1"]["seeded_from"], [str(seed_dir)])
        self.assertEqual(state["func_1"]["seed_best_similarity"], 0.77)
        # The seeded candidate survives into the merged/deduped pool
        # run_iteration built from this run's own attempt too.
        seeded_bodies = {c["body"] for c in state["func_1"]["best_candidates"]}
        self.assertIn("seeded_body", seeded_bodies)

    def test_seed_from_accepts_comma_separated_dirs(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            seed_a = Path(tmp) / "seed_a"
            seed_b = Path(tmp) / "seed_b"
            _write_seed_state(seed_a, {"func_x": {"status": "in_progress", "best_candidates": []}})
            _write_seed_state(seed_b, {"func_y": {"status": "in_progress", "best_candidates": []}})

            with mock.patch.object(
                container_agent, "seed_owner_states", wraps=container_agent.seed_owner_states
            ) as seed_mock:
                container_agent.main([
                    "--source", "disasm/src/X.c",
                    "--out", str(Path(tmp) / "out"),
                    "--repo", str(repo_dir),
                    "--seed-from", f"{seed_a}, {seed_b}",
                    "--generator-cmd", "generator --prompt {prompt} --batch {batch}",
                    "--owners", "func_none",
                ])
            called_dirs = seed_mock.call_args[0][0]
        self.assertEqual([str(d) for d in called_dirs], [str(seed_a), str(seed_b)])

    def test_seed_from_ignored_under_resume(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_dir = Path(tmp) / "repo"
            repo_dir.mkdir()
            out_dir = Path(tmp) / "out"
            out_dir.mkdir()
            container_agent.save_json(out_dir / "state.json", {
                "func_a": {**container_agent._new_owner_state(), "status": "plateau", "iterations": 5},
            })

            seed_dir = Path(tmp) / "seed"
            _write_seed_state(seed_dir, {
                "func_a": {"status": "in_progress", "best_candidates": [_candidate("seed:one", 0.9, body="x")]},
                "func_never_resumed": {"status": "in_progress", "best_candidates": []},
            })

            with mock.patch.object(container_agent, "invoke_generator") as gen_mock:
                exit_code = container_agent.main([
                    "--source", "disasm/src/X.c", "--out", str(out_dir), "--repo", str(repo_dir),
                    "--owners", "func_a", "--seed-from", str(seed_dir),
                    "--generator-cmd", "generator --prompt {prompt} --batch {batch}",
                    "--resume", "--skip-status", "accepted,plateau",
                ])

            self.assertEqual(exit_code, 0)
            gen_mock.assert_not_called()
            log_text = (out_dir / "log.txt").read_text(encoding="utf-8")
            state = json.loads((out_dir / "state.json").read_text(encoding="utf-8"))

        self.assertIn("--seed-from ignored", log_text)
        # The resumed owner's own real state is untouched by the seed dir.
        self.assertNotIn("seeded_from", state["func_a"])
        self.assertEqual(state["func_a"]["status"], "plateau")
        self.assertEqual(state["func_a"]["iterations"], 5)
        # An owner that only exists in the seed dir is never introduced
        # under --resume.
        self.assertNotIn("func_never_resumed", state)


if __name__ == "__main__":
    unittest.main()
