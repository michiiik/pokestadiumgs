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
import shlex
import sys
import tempfile
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


# ---------------------------------------------------------------------------
# run_iteration
# ---------------------------------------------------------------------------

class RunIterationTests(unittest.TestCase):
    def _run(self, out_dir, repo_dir, owner, batch, result, owner_state, *, iteration=0, permuter_seconds=0.0):
        logger = container_agent.Logger(out_dir / "log.txt")
        batch_path = out_dir / "batches" / f"{owner}_iter{iteration}.json"
        container_agent.save_json(batch_path, batch)

        def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
            if result is not None:
                container_agent.save_json(result_path, result)
            return SimpleNamespace(returncode=0, stdout="", stderr="")

        with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe):
            return container_agent.run_iteration(
                repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                iteration=iteration, batch=batch, batch_path=batch_path, owner_state=owner_state,
                deadline=time.monotonic() + 60.0, permuter_seconds=permuter_seconds, logger=logger,
            )

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

            high_result = {
                "batch_status": "no_candidate_accepted", "accepted": [],
                "attempts": [{"function": owner, "label": "a", "status": "rejected", "similarity_score": 0.9}],
            }
            self._run(out_dir, repo_dir, owner, batch, high_result, owner_state, iteration=1)
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

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe), \
                 mock.patch.object(container_agent, "run_permuter", return_value=permuter_result) as run_permuter_mock:
                container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=30.0, logger=logger,
                )
        run_permuter_mock.assert_called_once()
        self.assertEqual(owner_state["permuter_seed"]["score"], 0)

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

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe), \
                 mock.patch.object(container_agent, "run_permuter", return_value=permuter_result) as run_permuter_mock:
                container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=30.0, logger=logger,
                )
        run_permuter_mock.assert_called_once()
        self.assertEqual(owner_state["permuter_seed"]["score"], 5)

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

            def fake_probe(repo_dir_arg, batch_path_arg, result_path, *, timeout):
                container_agent.save_json(result_path, result)
                return SimpleNamespace(returncode=0, stdout="", stderr="")

            with mock.patch.object(container_agent, "invoke_probe", side_effect=fake_probe), \
                 mock.patch.object(container_agent, "run_permuter") as run_permuter_mock:
                container_agent.run_iteration(
                    repo_dir=repo_dir, out_dir=out_dir, source_rel="disasm/src/X.c", owner=owner,
                    iteration=0, batch=batch, batch_path=batch_path, owner_state=owner_state,
                    deadline=time.monotonic() + 60.0, permuter_seconds=30.0, logger=logger,
                )
        run_permuter_mock.assert_not_called()
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
            self._run(out_dir, repo_dir, owner, batch0, normalized_only_result, owner_state, iteration=0, permuter_seconds=30.0)
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
            self._run(out_dir, repo_dir, owner, batch1, genuine_result, owner_state, iteration=1, permuter_seconds=30.0)

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


if __name__ == "__main__":
    unittest.main()
