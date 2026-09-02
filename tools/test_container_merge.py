#!/usr/bin/env python3
"""Unit tests for tools/container_merge.py.

Nothing here touches a real git repo or runs the real runner: both
subprocess-shelling functions (``run_fleet_probe_gate``, ``git_commit_only``)
are monkeypatched with fakes that record their arguments and return a
synthetic payload shaped like the real one.
"""

from __future__ import annotations

import contextlib
import io
import json
import os
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import container_merge  # noqa: E402


def _write_batch(
    directory: Path, owner: str, *, source: str = "disasm/src/X.c", write_source: bool = True
) -> Path:
    """Write ``<directory>/<owner>.json``. By default this also writes (or
    appends to -- several owners commonly share one ``source`` file) the
    ``source`` file itself (relative to ``directory.parent``, which is the
    ``repo_root`` every test in this module passes -- ``out_dir``) with a
    ``#pragma GLOBAL_ASM`` line naming ``owner``, so ``process_owner``'s
    "already landed" pragma-presence check (``source_still_has_pragma``)
    sees the un-landed state most tests assume. Pass ``write_source=False``
    to simulate an owner whose source has already had the pragma removed
    (the "skip via missing pragma" idempotency case).
    """
    path = directory / f"{owner}.json"
    path.write_text(
        json.dumps(
            {
                "source": source,
                "declarations": "",
                "candidates": [
                    {"function": owner, "label": "container:accepted", "body": "void f(void) {}"}
                ],
            }
        ),
        encoding="utf-8",
    )
    if write_source and source:
        src_path = directory.parent / source
        src_path.parent.mkdir(parents=True, exist_ok=True)
        pragma_line = f'#pragma GLOBAL_ASM("asm/nonmatchings/x/{owner}.s")\n'
        existing = src_path.read_text(encoding="utf-8") if src_path.is_file() else ""
        if pragma_line not in existing:
            with src_path.open("a", encoding="utf-8") as handle:
                handle.write(pragma_line)
    return path


def _accepted_result(function: str) -> dict[str, object]:
    return {
        "returncode": 0,
        "result": {
            "status": 0,
            "accepted": [function],
            "batch_status": "accepted",
            "attempts": [{"function": function, "status": "accepted"}],
        },
        "stdout": "",
        "stderr": "",
    }


def _rejected_result() -> dict[str, object]:
    return {
        "returncode": 0,
        "result": {
            "status": 1,
            "accepted": [],
            "batch_status": "no_candidate_accepted",
            "attempts": [{"status": "probe_rejected"}],
        },
        "stdout": "",
        "stderr": "gate: no candidate matched\n",
    }


class _FakeGateProc:
    """Stand-in for ``subprocess.CompletedProcess`` in fake ``subprocess.run``s."""

    def __init__(self, returncode: int = 0, stdout: str = "", stderr: str = "") -> None:
        self.returncode = returncode
        self.stdout = stdout
        self.stderr = stderr


def _fake_gate_subprocess_run(result_payload: dict[str, object], calls: list[dict[str, object]]):
    """A ``subprocess.run`` replacement for ``run_fleet_probe_gate``'s own call:
    records ``{"cmd", "cwd", "env"}`` for each invocation and writes
    ``result_payload`` to the ``--json <path>`` argument, exactly like the
    real ``fleet_probe.py --gate`` would.
    """

    def fake_run(cmd, *, cwd, capture_output, text, timeout, env):
        calls.append({"cmd": list(cmd), "cwd": cwd, "env": env})
        result_path = Path(cmd[cmd.index("--json") + 1])
        result_path.write_text(json.dumps(result_payload), encoding="utf-8")
        return _FakeGateProc(0)

    return fake_run


@contextlib.contextmanager
def _tmp_out_dir():
    with tempfile.TemporaryDirectory() as tmp:
        out_dir = Path(tmp)
        (out_dir / "accepted").mkdir()
        yield out_dir


class LoadBatchTests(unittest.TestCase):
    def test_load_accepted_batch_parses_object(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1")
            payload = container_merge.load_accepted_batch(path)
        self.assertEqual(payload["source"], "disasm/src/X.c")

    def test_load_accepted_batch_rejects_non_object(self) -> None:
        with tempfile.NamedTemporaryFile("w", suffix=".json", delete=False) as handle:
            handle.write("[1, 2, 3]")
            path = Path(handle.name)
        try:
            with self.assertRaises(ValueError):
                container_merge.load_accepted_batch(path)
        finally:
            path.unlink(missing_ok=True)

    def test_owner_function_name_falls_back_to_stem(self) -> None:
        self.assertEqual(container_merge.owner_function_name("func_9", {}), "func_9")

    def test_owner_function_name_reads_first_candidate(self) -> None:
        payload = {"candidates": [{"function": "func_real"}]}
        self.assertEqual(container_merge.owner_function_name("func_stub", payload), "func_real")

    def test_batch_source_missing_is_none(self) -> None:
        self.assertIsNone(container_merge.batch_source({}))


class ProcessOwnerTests(unittest.TestCase):
    def test_invalid_json_becomes_error_row(self) -> None:
        with _tmp_out_dir() as out_dir:
            bad = out_dir / "accepted" / "func_bad.json"
            bad.write_text("not json", encoding="utf-8")
            row = container_merge.process_owner(
                bad, repo_root=out_dir, commit=False, dry_run=False
            )
        self.assertEqual(row.status, "error")

    def test_host_regate_accepts(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ):
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=False, dry_run=False
                )
        self.assertEqual(row.status, "accepted")
        self.assertFalse(row.committed)

    def test_host_regate_rejects(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_rejected_result()
            ):
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=False, dry_run=False
                )
        self.assertEqual(row.status, "rejected")
        self.assertIn("no_candidate_accepted", row.detail)

    def test_commit_invoked_with_only_and_source(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ) as commit_mock:
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False
                )
        self.assertTrue(row.committed)
        commit_mock.assert_called_once()
        args, kwargs = commit_mock.call_args
        self.assertEqual(args[0], "disasm/src/Y.c")
        self.assertEqual(args[1], "Land container match for func_1")
        self.assertEqual(kwargs.get("repo_root"), out_dir)

    def test_dry_run_never_commits(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(container_merge, "git_commit_only") as commit_mock:
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=True
                )
        self.assertFalse(row.committed)
        commit_mock.assert_not_called()

    def test_rejected_owner_never_commits(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_rejected_result()
            ), mock.patch.object(container_merge, "git_commit_only") as commit_mock:
                container_merge.process_owner(path, repo_root=out_dir, commit=True, dry_run=False)
        commit_mock.assert_not_called()

    def test_missing_source_skips_commit_but_stays_accepted(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = out_dir / "accepted" / "func_1.json"
            path.write_text(
                json.dumps({"candidates": [{"function": "func_1", "body": "void f(void) {}"}]}),
                encoding="utf-8",
            )
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(container_merge, "git_commit_only") as commit_mock:
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False
                )
        self.assertEqual(row.status, "accepted")
        self.assertFalse(row.committed)
        commit_mock.assert_not_called()

    # -- --fresh-history import ordering relative to commit ----------------

    def test_fresh_history_imports_before_commit_for_that_owner(self) -> None:
        """The bug this fixes: a prior run imported the accepted evidence
        only after every owner's commit had already been attempted, so
        tools/check_decomp_provenance.py's pre-commit hook never saw it in
        time and silently refused the commit. Assert call order directly."""
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            order: list[str] = []

            def fake_import(out, *, repo_root):
                order.append("import")
                return "imported"

            def fake_commit(source, message, *, repo_root):
                order.append("commit")
                return True, "committed"

            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "import_fresh_history_after_accept", side_effect=fake_import
            ) as import_mock, mock.patch.object(
                container_merge, "git_commit_only", side_effect=fake_commit
            ):
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False,
                    out_dir=out_dir, fresh_history=True,
                )
        self.assertEqual(order, ["import", "commit"])
        import_mock.assert_called_once_with(out_dir, repo_root=out_dir)
        self.assertTrue(row.committed)

    def test_fresh_history_not_imported_when_commit_never_attempted(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "import_fresh_history_after_accept"
            ) as import_mock:
                container_merge.process_owner(
                    path, repo_root=out_dir, commit=False, dry_run=False,
                    out_dir=out_dir, fresh_history=True,
                )
        import_mock.assert_not_called()

    def test_fresh_history_not_imported_on_dry_run(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "import_fresh_history_after_accept"
            ) as import_mock:
                container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=True,
                    out_dir=out_dir, fresh_history=True,
                )
        import_mock.assert_not_called()

    # -- commit failure diagnostics -----------------------------------------

    def test_commit_failure_captures_tail_and_writes_log(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            lines = [f"line {i}" for i in range(1, 21)]  # 20 lines, > 15
            output = "\n".join(lines)
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(False, output)
            ):
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False, out_dir=out_dir,
                )
            self.assertFalse(row.committed)
            self.assertEqual(row.status, "accepted")
            tail_lines = row.commit_error_tail.splitlines()
            self.assertEqual(tail_lines, lines[-15:])
            self.assertNotIn("line 5", tail_lines)  # earliest lines dropped, tail keeps line 6..20
            self.assertIn("commit failed (see merge-results/func_1.commit.log)", row.commit_detail)

            log_path = out_dir / "merge-results" / "func_1.commit.log"
            self.assertTrue(log_path.is_file())
            self.assertEqual(log_path.read_text(encoding="utf-8").strip(), output)

    def test_commit_failure_without_out_dir_skips_log_but_keeps_tail(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(False, "boom")
            ):
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False, out_dir=None,
                )
        self.assertFalse(row.committed)
        self.assertEqual(row.commit_error_tail, "boom")
        self.assertEqual(row.commit_detail, "commit failed")

    def test_commit_success_does_not_set_error_tail(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ):
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False, out_dir=out_dir,
                )
        self.assertTrue(row.committed)
        self.assertEqual(row.commit_error_tail, "")
        self.assertFalse((out_dir / "merge-results" / "func_1.commit.log").exists())

    def test_commit_success_records_commit_sha(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ), mock.patch.object(
                container_merge, "git_rev_parse_head", return_value="deadbeef"
            ) as rev_parse_mock:
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False,
                )
        self.assertTrue(row.committed)
        self.assertEqual(row.commit_sha, "deadbeef")
        rev_parse_mock.assert_called_once_with(out_dir)

    def test_commit_success_without_readable_sha_leaves_commit_sha_empty(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ), mock.patch.object(
                container_merge, "git_rev_parse_head", return_value=None
            ):
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False,
                )
        self.assertTrue(row.committed)
        self.assertEqual(row.commit_sha, "")

    def test_rejected_owner_never_calls_rev_parse(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_rejected_result()
            ), mock.patch.object(
                container_merge, "git_rev_parse_head"
            ) as rev_parse_mock:
                container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False,
                )
        rev_parse_mock.assert_not_called()


class AlreadyLandedTests(unittest.TestCase):
    """Idempotency: a second ``merge --commit`` over the same ``<out>``
    must not re-gate (and try to re-install/re-commit) an owner that has
    already landed -- the bug this fixes (see this module's own module
    docstring reference and tools/container_merge.py's module docstring):
    a repeat run re-installed an already-merged body into an
    already-matched source and then ``git commit --only`` failed with
    nothing to commit."""

    # -- skip via missing pragma --------------------------------------------

    def test_missing_pragma_is_already_landed_and_never_regated(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(
                out_dir / "accepted", "func_1", source="disasm/src/Y.c", write_source=False,
            )
            # The source file exists (as it would in a real checkout after a
            # prior merge landed this owner) but no longer carries the
            # pragma for func_1 -- some other function's, say.
            src_path = out_dir / "disasm" / "src" / "Y.c"
            src_path.parent.mkdir(parents=True, exist_ok=True)
            src_path.write_text("void already_landed_body(void) {}\n", encoding="utf-8")

            with mock.patch.object(container_merge, "run_fleet_probe_gate") as gate_mock:
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False,
                )
        self.assertEqual(row.status, "already_landed")
        self.assertFalse(row.committed)
        gate_mock.assert_not_called()

    def test_missing_source_file_entirely_is_already_landed(self) -> None:
        """A source file that no longer exists at all (e.g. removed as part
        of the same landing) is also read as "no longer has the pragma"."""
        with _tmp_out_dir() as out_dir:
            path = _write_batch(
                out_dir / "accepted", "func_1", source="disasm/src/gone.c", write_source=False,
            )
            with mock.patch.object(container_merge, "run_fleet_probe_gate") as gate_mock:
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False,
                )
        self.assertEqual(row.status, "already_landed")
        gate_mock.assert_not_called()

    def test_pragma_still_present_is_regated_normally(self) -> None:
        """Sanity check for the fixture itself: with the pragma still
        present (the default from _write_batch), an owner is regated as
        before -- not short-circuited to already_landed."""
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ) as gate_mock:
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=False, dry_run=False,
                )
        self.assertEqual(row.status, "accepted")
        gate_mock.assert_called_once()

    # -- skip via prior merge-report.json ------------------------------------

    def test_prior_report_bare_accepted_string_is_already_landed(self) -> None:
        """Reports written before this fix recorded a bare "accepted"
        string for a committed owner -- reading one back must still treat
        it as already landed."""
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            with mock.patch.object(container_merge, "run_fleet_probe_gate") as gate_mock:
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False,
                    previous_report={"func_1": "accepted"},
                )
        self.assertEqual(row.status, "already_landed")
        gate_mock.assert_not_called()

    def test_prior_report_object_committed_true_is_already_landed(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            with mock.patch.object(container_merge, "run_fleet_probe_gate") as gate_mock:
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=True, dry_run=False,
                    previous_report={
                        "func_1": {"status": "accepted", "committed": True, "commit": "abc123"}
                    },
                )
        self.assertEqual(row.status, "already_landed")
        gate_mock.assert_not_called()

    def test_prior_report_committed_false_object_is_not_already_landed(self) -> None:
        """A previously *failed* commit (committed: false) must still be
        re-gated -- only committed: true means already landed."""
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ) as gate_mock:
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=False, dry_run=False,
                    previous_report={
                        "func_1": {
                            "status": "accepted", "committed": False, "commit_error": "boom",
                        }
                    },
                )
        self.assertEqual(row.status, "accepted")
        gate_mock.assert_called_once()

    def test_prior_report_rejected_is_not_already_landed(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ) as gate_mock:
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=False, dry_run=False,
                    previous_report={"func_1": "rejected"},
                )
        self.assertEqual(row.status, "accepted")
        gate_mock.assert_called_once()

    def test_no_previous_report_is_not_already_landed(self) -> None:
        with _tmp_out_dir() as out_dir:
            path = _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ) as gate_mock:
                row = container_merge.process_owner(
                    path, repo_root=out_dir, commit=False, dry_run=False, previous_report=None,
                )
        self.assertEqual(row.status, "accepted")
        gate_mock.assert_called_once()

    # -- owner_pragma_pattern / source_still_has_pragma / helpers -----------

    def test_owner_pragma_pattern_matches_real_pragma_line(self) -> None:
        pattern = container_merge.owner_pragma_pattern("func_1")
        self.assertTrue(
            pattern.search('#pragma GLOBAL_ASM("asm/nonmatchings/x/func_1.s")')
        )
        self.assertFalse(
            pattern.search('#pragma GLOBAL_ASM("asm/nonmatchings/x/func_1_helper.s")')
        )

    def test_source_still_has_pragma_true_when_present(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            src = repo_root / "disasm" / "src" / "X.c"
            src.parent.mkdir(parents=True)
            src.write_text('#pragma GLOBAL_ASM("asm/nonmatchings/x/func_1.s")\n', encoding="utf-8")
            self.assertTrue(
                container_merge.source_still_has_pragma(repo_root, "disasm/src/X.c", "func_1")
            )

    def test_source_still_has_pragma_false_when_missing_file(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            self.assertFalse(
                container_merge.source_still_has_pragma(repo_root, "disasm/src/gone.c", "func_1")
            )

    def test_previous_entry_marks_committed(self) -> None:
        marks = container_merge.previous_entry_marks_committed
        self.assertTrue(marks("accepted"))
        self.assertTrue(marks("already_landed"))
        self.assertTrue(marks({"status": "accepted", "committed": True}))
        self.assertFalse(marks({"status": "accepted", "committed": False}))
        self.assertFalse(marks("rejected"))
        self.assertFalse(marks("error"))


class RunFleetProbeGateTests(unittest.TestCase):
    """``run_fleet_probe_gate``'s own subprocess call: env handling and
    whether the ``--json`` result file survives the call. These stub
    ``subprocess.run`` directly (rather than ``run_fleet_probe_gate``
    itself) so the env actually reaching the subprocess is observable."""

    def test_extra_env_overlaid_on_cleaned_environment(self) -> None:
        calls: list[dict[str, object]] = []
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            batch_path = repo_root / "batch.json"
            batch_path.write_text("{}", encoding="utf-8")
            with mock.patch.object(
                container_merge.subprocess, "run",
                side_effect=_fake_gate_subprocess_run(_accepted_result("func_1")["result"], calls),
            ), mock.patch.dict(
                os.environ, {"SOME_HOST_VAR": "keep-me", "GIT_DIR": "poison"}
            ):
                container_merge.run_fleet_probe_gate(
                    batch_path, repo_root=repo_root,
                    extra_env={"PRAGMA_GATE_CC_CHECK": "0"},
                )
        self.assertEqual(len(calls), 1)
        env = calls[0]["env"]
        self.assertEqual(env.get("PRAGMA_GATE_CC_CHECK"), "0")
        self.assertEqual(env.get("SOME_HOST_VAR"), "keep-me")
        self.assertNotIn("GIT_DIR", env)

    def test_fresh_history_env_reaches_subprocess(self) -> None:
        calls: list[dict[str, object]] = []
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            batch_path = repo_root / "batch.json"
            batch_path.write_text("{}", encoding="utf-8")
            history_path = repo_root / "out" / "merge-history.jsonl"
            with mock.patch.object(
                container_merge.subprocess, "run",
                side_effect=_fake_gate_subprocess_run(_accepted_result("func_1")["result"], calls),
            ):
                container_merge.run_fleet_probe_gate(
                    batch_path, repo_root=repo_root,
                    extra_env={"PRAGMA_PROBE_STATS": str(history_path)},
                )
        self.assertEqual(calls[0]["env"].get("PRAGMA_PROBE_STATS"), str(history_path))

    def test_no_extra_env_still_runs_with_cleaned_environment(self) -> None:
        calls: list[dict[str, object]] = []
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            batch_path = repo_root / "batch.json"
            batch_path.write_text("{}", encoding="utf-8")
            with mock.patch.object(
                container_merge.subprocess, "run",
                side_effect=_fake_gate_subprocess_run(_accepted_result("func_1")["result"], calls),
            ):
                container_merge.run_fleet_probe_gate(batch_path, repo_root=repo_root)
        self.assertNotIn("PRAGMA_GATE_CC_CHECK", calls[0]["env"])

    def test_result_path_is_written_and_kept(self) -> None:
        calls: list[dict[str, object]] = []
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            batch_path = repo_root / "batch.json"
            batch_path.write_text("{}", encoding="utf-8")
            result_path = repo_root / "out" / "merge-results" / "func_1.json"
            with mock.patch.object(
                container_merge.subprocess, "run",
                side_effect=_fake_gate_subprocess_run(_rejected_result()["result"], calls),
            ):
                gate = container_merge.run_fleet_probe_gate(
                    batch_path, repo_root=repo_root, result_path=result_path,
                )
            self.assertTrue(result_path.is_file())
            self.assertEqual(gate["result"]["batch_status"], "no_candidate_accepted")

    def test_default_temp_result_path_is_deleted(self) -> None:
        written: dict[str, Path] = {}

        def fake_run(cmd, *, cwd, capture_output, text, timeout, env):
            result_path = Path(cmd[cmd.index("--json") + 1])
            written["path"] = result_path
            result_path.write_text(
                json.dumps({"batch_status": "accepted", "accepted": []}), encoding="utf-8"
            )
            return _FakeGateProc(0)

        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            batch_path = repo_root / "batch.json"
            batch_path.write_text("{}", encoding="utf-8")
            with mock.patch.object(container_merge.subprocess, "run", side_effect=fake_run):
                container_merge.run_fleet_probe_gate(batch_path, repo_root=repo_root)
        self.assertFalse(written["path"].exists())


class BuildGateEnvTests(unittest.TestCase):
    def test_no_flags_returns_empty_env(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            env = container_merge.build_gate_env(
                Path(tmp), no_cc_check=False, fresh_history=False
            )
        self.assertEqual(env, {})

    def test_no_cc_check_sets_env_var(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            env = container_merge.build_gate_env(
                Path(tmp), no_cc_check=True, fresh_history=False
            )
        self.assertEqual(env.get("PRAGMA_GATE_CC_CHECK"), "0")

    def test_fresh_history_points_at_out_dir_and_creates_file(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp) / "out"
            out_dir.mkdir()
            env = container_merge.build_gate_env(
                out_dir, no_cc_check=False, fresh_history=True
            )
            expected = out_dir / "merge-history.jsonl"
            self.assertEqual(env.get("PRAGMA_PROBE_STATS"), str(expected))
            self.assertTrue(expected.is_file())

    def test_fresh_history_leaves_existing_file_untouched(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp)
            history_path = out_dir / "merge-history.jsonl"
            history_path.write_text('{"already": "here"}\n', encoding="utf-8")
            container_merge.build_gate_env(out_dir, no_cc_check=False, fresh_history=True)
            self.assertEqual(
                history_path.read_text(encoding="utf-8"), '{"already": "here"}\n'
            )

    def test_both_flags_together(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp)
            env = container_merge.build_gate_env(out_dir, no_cc_check=True, fresh_history=True)
        self.assertEqual(env.get("PRAGMA_GATE_CC_CHECK"), "0")
        self.assertEqual(
            env.get("PRAGMA_PROBE_STATS"), str(out_dir / "merge-history.jsonl")
        )


class MergeTests(unittest.TestCase):
    def setUp(self) -> None:
        # Notes/naming (below) are new merge() features, on by default.
        # Neither has anything to do in any of these existing tests (no
        # out_dir/region-notes -- apply_region_notes() no-ops on its own --
        # and no tools/name_decompiled.py under these tests' throwaway
        # repo_root tempdirs), but naming's own subprocess seam would still
        # get invoked once per committed row unless stubbed, so keep it
        # inert here; NotesTests / NamingTests below cover the real seams.
        patcher = mock.patch.object(
            container_merge, "name_after_commit", return_value=(None, "")
        )
        patcher.start()
        self.addCleanup(patcher.stop)

    def _run_merge(self, out_dir: Path, **kwargs) -> tuple[int, str]:
        buffer = io.StringIO()
        with contextlib.redirect_stdout(buffer):
            code = container_merge.merge(out_dir, repo_root=out_dir, **kwargs)
        return code, buffer.getvalue()

    def test_no_accepted_directory_is_a_clean_noop(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            code, _out = self._run_merge(Path(tmp), commit=False, dry_run=False)
        self.assertEqual(code, 0)

    def test_all_accepted_exits_zero(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            _write_batch(out_dir / "accepted", "func_2")

            def fake_gate(path, *, repo_root, **_kw):
                owner = path.stem
                return _accepted_result(owner)

            with mock.patch.object(container_merge, "run_fleet_probe_gate", side_effect=fake_gate):
                code, out = self._run_merge(out_dir, commit=False, dry_run=False)
        self.assertEqual(code, 0)
        self.assertIn("accepted 2/2", out)

    def test_one_rejected_exits_nonzero(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            _write_batch(out_dir / "accepted", "func_2")

            def fake_gate(path, *, repo_root, **_kw):
                if path.stem == "func_1":
                    return _accepted_result("func_1")
                return _rejected_result()

            with mock.patch.object(container_merge, "run_fleet_probe_gate", side_effect=fake_gate):
                code, out = self._run_merge(out_dir, commit=False, dry_run=False)
        self.assertEqual(code, 1)
        self.assertIn("accepted 1/2", out)

    def test_merge_prints_import_stats_reminder(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ):
                _code, out = self._run_merge(out_dir, commit=False, dry_run=False)
        self.assertIn("import-stats", out)
        self.assertIn(str(out_dir), out)

    def test_commit_runs_git_commit_only_per_accepted_owner(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/A.c")
            _write_batch(out_dir / "accepted", "func_2", source="disasm/src/B.c")

            def fake_gate(path, *, repo_root, **_kw):
                return _accepted_result(path.stem)

            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", side_effect=fake_gate
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ) as commit_mock:
                code, out = self._run_merge(out_dir, commit=True, dry_run=False)

        self.assertEqual(code, 0)
        self.assertEqual(commit_mock.call_count, 2)
        called_sources = sorted(call.args[0] for call in commit_mock.call_args_list)
        self.assertEqual(called_sources, ["disasm/src/A.c", "disasm/src/B.c"])
        for call in commit_mock.call_args_list:
            self.assertTrue(call.args[1].startswith("Land container match for "))
        self.assertIn("committed 2/2", out)

    def test_commit_failure_makes_merge_exit_nonzero(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")

            with mock.patch.object(
                container_merge, "run_fleet_probe_gate",
                return_value=_accepted_result("func_1"),
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(False, "nothing to commit")
            ):
                code, _out = self._run_merge(out_dir, commit=True, dry_run=False)
        self.assertEqual(code, 1)

    def test_commit_failure_table_mentions_log_file(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate",
                return_value=_accepted_result("func_1"),
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(False, "nothing to commit")
            ):
                _code, out = self._run_merge(out_dir, commit=True, dry_run=False)
        self.assertIn("commit failed (see merge-results/func_1.commit.log)", out)

    def test_commit_failure_prints_last_15_lines_in_merge_output(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            lines = [f"line {i}" for i in range(1, 21)]
            output = "\n".join(lines)
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate",
                return_value=_accepted_result("func_1"),
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(False, output)
            ):
                _code, out = self._run_merge(out_dir, commit=True, dry_run=False)
        self.assertIn("line 20", out)
        self.assertIn("line 6", out)
        self.assertNotIn("line 5", out)

    def test_commit_failure_writes_full_log_under_merge_results(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            output = "boom: something went wrong\nsecond line"
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate",
                return_value=_accepted_result("func_1"),
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(False, output)
            ):
                self._run_merge(out_dir, commit=True, dry_run=False)
            log_path = out_dir / "merge-results" / "func_1.commit.log"
            self.assertTrue(log_path.is_file())
            self.assertEqual(log_path.read_text(encoding="utf-8").strip(), output)

    def test_commit_failure_recorded_in_report_as_object(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            output = "boom: something went wrong"
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate",
                return_value=_accepted_result("func_1"),
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(False, output)
            ):
                self._run_merge(out_dir, commit=True, dry_run=False)
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
            self.assertEqual(
                report["owners"]["func_1"],
                {"status": "accepted", "committed": False, "commit_error": output},
            )

    def test_commit_success_report_entry_records_committed_and_sha(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate",
                return_value=_accepted_result("func_1"),
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ), mock.patch.object(
                container_merge, "git_rev_parse_head", return_value="abc123"
            ):
                self._run_merge(out_dir, commit=True, dry_run=False)
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
            self.assertEqual(
                report["owners"]["func_1"],
                {"status": "accepted", "committed": True, "commit": "abc123"},
            )

    def test_commit_success_never_committed_stays_a_plain_string(self) -> None:
        """An owner whose host re-gate accepted but where --commit was never
        passed (no commit attempted at all) keeps the pre-existing plain
        "accepted" string -- only an owner that was actually committed gets
        the new object form."""
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate",
                return_value=_accepted_result("func_1"),
            ):
                self._run_merge(out_dir, commit=False, dry_run=False)
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
            self.assertEqual(report["owners"]["func_1"], "accepted")

    def test_commit_success_without_readable_sha_omits_commit_field(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate",
                return_value=_accepted_result("func_1"),
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ), mock.patch.object(
                container_merge, "git_rev_parse_head", return_value=None
            ):
                self._run_merge(out_dir, commit=True, dry_run=False)
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
            self.assertEqual(report["owners"]["func_1"], {"status": "accepted", "committed": True})

    def test_fresh_history_import_happens_before_commit_within_merge(self) -> None:
        """End-to-end (merge(), not just process_owner()) version of the
        ordering fix: with --fresh-history --commit, the accepted line must
        land in the host's real history before that owner's commit is
        attempted -- otherwise check_decomp_provenance.py's pre-commit hook
        refuses the commit even though the re-gate accepted it."""
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")
            order: list[str] = []

            def fake_import(out, *, repo_root):
                order.append("import")
                return "imported"

            def fake_commit(source, message, *, repo_root):
                order.append("commit")
                return True, "committed"

            with mock.patch.object(
                container_merge, "run_fleet_probe_gate",
                return_value=_accepted_result("func_1"),
            ), mock.patch.object(
                container_merge, "import_fresh_history_after_accept", side_effect=fake_import
            ), mock.patch.object(
                container_merge, "git_commit_only", side_effect=fake_commit
            ):
                code, _out = self._run_merge(
                    out_dir, commit=True, dry_run=False, fresh_history=True
                )
        self.assertEqual(code, 0)
        self.assertEqual(order[0], "import")
        self.assertIn("commit", order)
        self.assertLess(order.index("import"), order.index("commit"))

    def test_rejected_batch_is_never_committed_in_a_merge_run(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")

            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_rejected_result()
            ), mock.patch.object(container_merge, "git_commit_only") as commit_mock:
                self._run_merge(out_dir, commit=True, dry_run=False)
        commit_mock.assert_not_called()

    # -- --no-cc-check ----------------------------------------------------

    def test_no_cc_check_passes_env_to_gate_and_result_path(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            captured: dict[str, object] = {}

            def fake_gate(path, *, repo_root, extra_env=None, result_path=None, **_kw):
                captured["extra_env"] = extra_env
                captured["result_path"] = result_path
                return _accepted_result("func_1")

            with mock.patch.object(container_merge, "run_fleet_probe_gate", side_effect=fake_gate):
                self._run_merge(out_dir, commit=False, dry_run=False, no_cc_check=True)
        self.assertEqual(captured["extra_env"], {"PRAGMA_GATE_CC_CHECK": "0"})
        self.assertEqual(captured["result_path"], out_dir / "merge-results" / "func_1.json")

    def test_no_cc_check_prints_loud_warning(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ):
                _code, out = self._run_merge(out_dir, commit=False, dry_run=False, no_cc_check=True)
        self.assertIn("WARNING", out)
        self.assertIn("--no-cc-check", out)
        self.assertIn("PRAGMA_GATE_CC_CHECK=0", out)

    def test_no_warning_without_no_cc_check(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ):
                _code, out = self._run_merge(out_dir, commit=False, dry_run=False)
        self.assertNotIn("WARNING", out)

    # -- merge-report.json --------------------------------------------------

    def test_merge_report_records_cc_check_bypassed_true(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ):
                self._run_merge(out_dir, commit=False, dry_run=False, no_cc_check=True)
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
            self.assertTrue(report["cc_check_bypassed"])
            self.assertEqual(report["owners"], {"func_1": "accepted"})

    def test_merge_report_default_is_not_bypassed(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_rejected_result()
            ):
                self._run_merge(out_dir, commit=False, dry_run=False)
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
            self.assertFalse(report["cc_check_bypassed"])
            self.assertFalse(report["fresh_history"])
            self.assertEqual(report["owners"], {"func_1": "rejected"})

    # -- --fresh-history ------------------------------------------------

    def test_fresh_history_passes_env_to_gate(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            captured: dict[str, object] = {}

            def fake_gate(path, *, repo_root, extra_env=None, result_path=None, **_kw):
                captured["extra_env"] = extra_env
                return _accepted_result("func_1")

            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", side_effect=fake_gate
            ), mock.patch.object(container_merge, "import_fresh_history_after_accept", return_value=None):
                self._run_merge(out_dir, commit=False, dry_run=False, fresh_history=True)
            self.assertEqual(
                captured["extra_env"], {"PRAGMA_PROBE_STATS": str(out_dir / "merge-history.jsonl")}
            )
            self.assertTrue((out_dir / "merge-history.jsonl").is_file())

    def test_fresh_history_imports_after_a_successful_accept(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "import_fresh_history_after_accept",
                return_value="container_merge: --fresh-history: imported 1 accepted line",
            ) as import_mock:
                _code, out = self._run_merge(out_dir, commit=False, dry_run=False, fresh_history=True)
            import_mock.assert_called_once_with(out_dir, repo_root=out_dir)
            self.assertIn("imported 1 accepted line", out)

    def test_fresh_history_not_imported_when_nothing_accepted(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_rejected_result()
            ), mock.patch.object(
                container_merge, "import_fresh_history_after_accept"
            ) as import_mock:
                self._run_merge(out_dir, commit=False, dry_run=False, fresh_history=True)
            import_mock.assert_not_called()

    def test_fresh_history_flag_off_never_imports(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "import_fresh_history_after_accept"
            ) as import_mock:
                self._run_merge(out_dir, commit=False, dry_run=False)
            import_mock.assert_not_called()

    # -- merge-results/<owner>.json kept ---------------------------------

    def test_merge_results_json_kept_for_inspection(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            calls: list[dict[str, object]] = []
            with mock.patch.object(
                container_merge.subprocess, "run",
                side_effect=_fake_gate_subprocess_run(_rejected_result()["result"], calls),
            ):
                self._run_merge(out_dir, commit=False, dry_run=False)
            result_path = out_dir / "merge-results" / "func_1.json"
            self.assertTrue(result_path.is_file())
            payload = json.loads(result_path.read_text(encoding="utf-8"))
            self.assertEqual(payload["batch_status"], "no_candidate_accepted")

    def test_merge_results_json_kept_for_multiple_owners(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")
            _write_batch(out_dir / "accepted", "func_2")
            calls: list[dict[str, object]] = []
            with mock.patch.object(
                container_merge.subprocess, "run",
                side_effect=_fake_gate_subprocess_run(_accepted_result("func_1")["result"], calls),
            ):
                self._run_merge(out_dir, commit=False, dry_run=False)
            self.assertTrue((out_dir / "merge-results" / "func_1.json").is_file())
            self.assertTrue((out_dir / "merge-results" / "func_2.json").is_file())

    # -- idempotency: a second merge over the same <out> -------------------

    def test_second_run_skips_already_committed_owner_without_regating(self) -> None:
        """The bug this fixes: running merge --fresh-history --commit a
        second time on an out dir whose accepted/func_A.json had already
        landed used to re-gate it again (re-installing the same body into
        an already-matched source) and then fail to commit. A second
        merge() call must instead skip it as already_landed and never call
        the gate at all."""
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/Y.c")

            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1"),
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed"),
            ), mock.patch.object(
                container_merge, "git_rev_parse_head", return_value="sha1",
            ):
                first_code, _out = self._run_merge(out_dir, commit=True, dry_run=False)
            self.assertEqual(first_code, 0)

            with mock.patch.object(container_merge, "run_fleet_probe_gate") as gate_mock, \
                 mock.patch.object(container_merge, "git_commit_only") as commit_mock:
                second_code, second_out = self._run_merge(out_dir, commit=True, dry_run=False)

            self.assertEqual(second_code, 0)
            self.assertIn("already_landed 1/1", second_out)
            gate_mock.assert_not_called()
            commit_mock.assert_not_called()
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
        # This run's own status ("already_landed") wins for a touched
        # owner, per write_merge_report -- a prior run's entry is only
        # ever carried forward untouched for an owner NOT in this run's
        # rows at all (see test_report_is_cumulative_across_owners_filter_touch).
        self.assertEqual(report["owners"]["func_1"], "already_landed")

    def test_already_landed_does_not_affect_exit_code(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/A.c")

            def fake_gate(path, *, repo_root, **_kw):
                return _accepted_result(path.stem)

            with mock.patch.object(container_merge, "run_fleet_probe_gate", side_effect=fake_gate):
                code, _out = self._run_merge(out_dir, commit=False, dry_run=False)
            self.assertEqual(code, 0)

            with mock.patch.object(container_merge, "run_fleet_probe_gate") as gate_mock:
                code, out = self._run_merge(out_dir, commit=False, dry_run=False)
        self.assertEqual(code, 0)
        self.assertIn("already_landed", out)
        gate_mock.assert_not_called()

    # -- cumulative merge-report.json ---------------------------------------

    def test_report_is_cumulative_across_owners_filter_touch(self) -> None:
        """An owner not touched this run (filtered out via --owners) keeps
        its prior report entry rather than disappearing, and a touched
        owner is still re-gated fresh regardless of what the untouched
        owner's entry looks like."""
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/A.c")
            _write_batch(out_dir / "accepted", "func_2", source="disasm/src/B.c")

            # Simulate a prior run's report for both owners.
            (out_dir / "merge-report.json").write_text(
                json.dumps(
                    {
                        "cc_check_bypassed": False,
                        "fresh_history": False,
                        "owners": {
                            "func_1": {
                                "status": "accepted", "committed": True, "commit": "sha0",
                            },
                            "func_2": "rejected",
                        },
                    }
                ),
                encoding="utf-8",
            )

            # A run limited to func_2 only via --owners must leave func_1's
            # entry untouched (process_owner is never even called for it --
            # its accepted/func_1.json is filtered out before the loop) and
            # must re-gate func_2 fresh (its prior status was "rejected",
            # not landed).
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_2"),
            ) as gate_mock:
                code, _out = self._run_merge(
                    out_dir, commit=False, dry_run=False, owners={"func_2"}
                )
            self.assertEqual(code, 0)
            gate_mock.assert_called_once()
            report2 = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
        self.assertEqual(
            report2["owners"]["func_1"],
            {"status": "accepted", "committed": True, "commit": "sha0"},
        )
        self.assertEqual(report2["owners"]["func_2"], "accepted")

    def test_report_preserves_prior_commit_object_entry_untouched(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/A.c")
            _write_batch(out_dir / "accepted", "func_2", source="disasm/src/B.c")

            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1"),
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed"),
            ), mock.patch.object(
                container_merge, "git_rev_parse_head", return_value="cafef00d",
            ):
                self._run_merge(out_dir, commit=True, dry_run=False, owners={"func_1"})

            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_rejected_result(),
            ):
                self._run_merge(out_dir, commit=True, dry_run=False, owners={"func_2"})

            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
        self.assertEqual(
            report["owners"]["func_1"],
            {"status": "accepted", "committed": True, "commit": "cafef00d"},
        )
        self.assertEqual(report["owners"]["func_2"], "rejected")

    # -- --owners -------------------------------------------------------

    def test_owners_filter_limits_which_batches_are_processed(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/A.c")
            _write_batch(out_dir / "accepted", "func_2", source="disasm/src/B.c")

            def fake_gate(path, *, repo_root, **_kw):
                return _accepted_result(path.stem)

            with mock.patch.object(container_merge, "run_fleet_probe_gate", side_effect=fake_gate):
                code, out = self._run_merge(
                    out_dir, commit=False, dry_run=False, owners={"func_1"}
                )
        self.assertEqual(code, 0)
        self.assertIn("func_1", out)
        self.assertNotIn("func_2", out)
        self.assertIn("accepted 1/1", out)

    def test_owners_filter_matching_nothing_is_a_clean_noop(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/A.c")
            with mock.patch.object(container_merge, "run_fleet_probe_gate") as gate_mock:
                code, out = self._run_merge(
                    out_dir, commit=False, dry_run=False, owners={"no_such_owner"}
                )
        self.assertEqual(code, 0)
        self.assertIn("--owners", out)
        gate_mock.assert_not_called()

    def test_cli_parses_owners_flag_into_a_set(self) -> None:
        captured: dict[str, object] = {}

        def fake_merge(out_dir, **kwargs):
            captured.update(kwargs)
            return 0

        with mock.patch.object(container_merge, "merge", side_effect=fake_merge):
            code = container_merge.main(
                ["merge", "/abs/out", "--owners", "func_1, func_2,func_3"]
            )
        self.assertEqual(code, 0)
        self.assertEqual(captured["owners"], {"func_1", "func_2", "func_3"})

    def test_cli_omits_owners_filter_when_flag_absent(self) -> None:
        captured: dict[str, object] = {}

        def fake_merge(out_dir, **kwargs):
            captured.update(kwargs)
            return 0

        with mock.patch.object(container_merge, "merge", side_effect=fake_merge):
            container_merge.main(["merge", "/abs/out"])
        self.assertIsNone(captured["owners"])

    def test_cli_no_notes_and_no_naming_default_false(self) -> None:
        captured: dict[str, object] = {}

        def fake_merge(out_dir, **kwargs):
            captured.update(kwargs)
            return 0

        with mock.patch.object(container_merge, "merge", side_effect=fake_merge):
            container_merge.main(["merge", "/abs/out"])
        self.assertFalse(captured["no_notes"])
        self.assertFalse(captured["no_naming"])

    def test_cli_parses_no_notes_and_no_naming_flags(self) -> None:
        captured: dict[str, object] = {}

        def fake_merge(out_dir, **kwargs):
            captured.update(kwargs)
            return 0

        with mock.patch.object(container_merge, "merge", side_effect=fake_merge):
            container_merge.main(["merge", "/abs/out", "--no-notes", "--no-naming"])
        self.assertTrue(captured["no_notes"])
        self.assertTrue(captured["no_naming"])


class ImportStatsTests(unittest.TestCase):
    """tools/container_merge.py import-stats: fold <out>/probe-stats/probe-stats.jsonl
    into the host's probe-stats history (see tools/probe_stats.py's
    PRAGMA_PROBE_STATS contract). No fleet_probe/git subprocess involved --
    this command only ever reads/writes JSONL files."""

    def _run(self, out_dir: Path, *, repo_root: Path, dry_run: bool = False) -> tuple[int, str]:
        buffer = io.StringIO()
        with contextlib.redirect_stdout(buffer):
            code = container_merge.import_stats(out_dir, repo_root=repo_root, dry_run=dry_run)
        return code, buffer.getvalue()

    def test_missing_source_file_is_a_clean_noop(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp) / "out"
            out_dir.mkdir()
            repo_root = Path(tmp) / "repo"
            repo_root.mkdir()
            code, out = self._run(out_dir, repo_root=repo_root)
        self.assertEqual(code, 0)
        self.assertIn("nothing to import", out)

    def test_appends_new_lines_and_skips_exact_duplicates(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp) / "out"
            (out_dir / "probe-stats").mkdir(parents=True)
            source = out_dir / "probe-stats" / "probe-stats.jsonl"
            row_shared = json.dumps({"batch_id": "shared", "source": "disasm/src/X.c"}, sort_keys=True)
            row_new_1 = json.dumps({"batch_id": "new1", "source": "disasm/src/X.c"}, sort_keys=True)
            row_new_2 = json.dumps({"batch_id": "new2", "source": "disasm/src/Y.c"}, sort_keys=True)
            source.write_text(f"{row_shared}\n{row_new_1}\n{row_new_2}\n", encoding="utf-8")

            target = Path(tmp) / "host-stats.jsonl"
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text(f"{row_shared}\n", encoding="utf-8")

            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": str(target)}):
                code, out = self._run(out_dir, repo_root=Path(tmp))

            self.assertEqual(code, 0)
            self.assertIn("3 line(s), 2 new, 1 already present", out)
            target_lines = target.read_text(encoding="utf-8").splitlines()
        self.assertEqual(len(target_lines), 3)
        self.assertEqual(target_lines.count(row_shared), 1)
        self.assertIn(row_new_1, target_lines)
        self.assertIn(row_new_2, target_lines)

    def test_dry_run_counts_but_never_writes(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp) / "out"
            (out_dir / "probe-stats").mkdir(parents=True)
            source = out_dir / "probe-stats" / "probe-stats.jsonl"
            row = json.dumps({"batch_id": "only"}, sort_keys=True)
            source.write_text(f"{row}\n", encoding="utf-8")

            target = Path(tmp) / "host-stats.jsonl"

            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": str(target)}):
                code, out = self._run(out_dir, repo_root=Path(tmp), dry_run=True)

        self.assertEqual(code, 0)
        self.assertIn("1 new", out)
        self.assertIn("--dry-run", out)
        self.assertFalse(target.exists())

    def test_disabled_via_empty_pragma_probe_stats_is_a_noop(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp) / "out"
            (out_dir / "probe-stats").mkdir(parents=True)
            source = out_dir / "probe-stats" / "probe-stats.jsonl"
            source.write_text(json.dumps({"batch_id": "x"}) + "\n", encoding="utf-8")

            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": ""}):
                code, out = self._run(out_dir, repo_root=Path(tmp))

        self.assertEqual(code, 0)
        self.assertIn("disabled", out)

    def test_default_target_is_under_repo_disasm_probe_stats(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp) / "out"
            (out_dir / "probe-stats").mkdir(parents=True)
            source = out_dir / "probe-stats" / "probe-stats.jsonl"
            row = json.dumps({"batch_id": "x"}, sort_keys=True)
            source.write_text(row + "\n", encoding="utf-8")

            repo_root = Path(tmp) / "repo"
            repo_root.mkdir()
            env = dict(os.environ)
            env.pop("PRAGMA_PROBE_STATS", None)
            with mock.patch.dict(os.environ, env, clear=True):
                code, _out = self._run(out_dir, repo_root=repo_root)

            expected_target = repo_root / "disasm" / "probe-stats" / "probe-stats.jsonl"
            self.assertEqual(code, 0)
            self.assertTrue(expected_target.is_file())
            self.assertEqual(expected_target.read_text(encoding="utf-8").strip(), row)


class AppendHistoryLinesTests(unittest.TestCase):
    """``append_history_lines``: the dedup-append core ``import_stats`` was
    refactored onto, and that ``import_fresh_history_after_accept`` reuses
    with ``only_accepted=True``."""

    def test_only_accepted_filters_out_non_accepted_lines(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source = Path(tmp) / "source.jsonl"
            accepted_row = json.dumps(
                {"attempts": [{"function": "func_1", "status": "accepted"}]}, sort_keys=True
            )
            rejected_row = json.dumps(
                {"attempts": [{"function": "func_2", "status": "rejected"}]}, sort_keys=True
            )
            source.write_text(f"{accepted_row}\n{rejected_row}\n", encoding="utf-8")
            target = Path(tmp) / "target.jsonl"

            considered, new_count, duplicates = container_merge.append_history_lines(
                source, target, only_accepted=True
            )
            self.assertEqual((considered, new_count, duplicates), (1, 1, 0))
            self.assertEqual(target.read_text(encoding="utf-8").strip(), accepted_row)

    def test_only_accepted_false_keeps_every_line(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source = Path(tmp) / "source.jsonl"
            row = json.dumps({"batch_id": "x"}, sort_keys=True)
            source.write_text(row + "\n", encoding="utf-8")
            target = Path(tmp) / "target.jsonl"
            considered, new_count, _duplicates = container_merge.append_history_lines(source, target)
        self.assertEqual((considered, new_count), (1, 1))

    def test_dry_run_reports_without_writing(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source = Path(tmp) / "source.jsonl"
            row = json.dumps({"batch_id": "x"}, sort_keys=True)
            source.write_text(row + "\n", encoding="utf-8")
            target = Path(tmp) / "target.jsonl"
            considered, new_count, _duplicates = container_merge.append_history_lines(
                source, target, dry_run=True
            )
        self.assertEqual((considered, new_count), (1, 1))
        self.assertFalse(target.exists())

    def test_duplicate_against_target_is_skipped(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source = Path(tmp) / "source.jsonl"
            row = json.dumps({"batch_id": "x"}, sort_keys=True)
            source.write_text(row + "\n", encoding="utf-8")
            target = Path(tmp) / "target.jsonl"
            target.write_text(row + "\n", encoding="utf-8")
            considered, new_count, duplicates = container_merge.append_history_lines(source, target)
        self.assertEqual((considered, new_count, duplicates), (1, 0, 1))


class ImportFreshHistoryAfterAcceptTests(unittest.TestCase):
    """``import_fresh_history_after_accept``: folds a ``--fresh-history``
    run's ``<out>/merge-history.jsonl`` accepted line(s) into the host's
    real probe-stats history so ``tools/check_decomp_provenance.py``'s
    pre-commit hook still finds an accepted attempt on record."""

    def test_no_fresh_history_file_returns_none(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp) / "out"
            out_dir.mkdir()
            repo_root = Path(tmp) / "repo"
            repo_root.mkdir()
            result = container_merge.import_fresh_history_after_accept(
                out_dir, repo_root=repo_root
            )
        self.assertIsNone(result)

    def test_imports_only_accepted_lines_into_host_history(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp) / "out"
            out_dir.mkdir()
            accepted_row = json.dumps(
                {"attempts": [{"function": "func_1", "status": "accepted"}]}, sort_keys=True
            )
            rejected_row = json.dumps(
                {"attempts": [{"function": "func_2", "status": "rejected"}]}, sort_keys=True
            )
            (out_dir / "merge-history.jsonl").write_text(
                f"{accepted_row}\n{rejected_row}\n", encoding="utf-8"
            )
            target = Path(tmp) / "host-stats.jsonl"
            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": str(target)}):
                status_line = container_merge.import_fresh_history_after_accept(
                    out_dir, repo_root=Path(tmp)
                )
            self.assertIsNotNone(status_line)
            self.assertIn("1 accepted line", status_line)
            self.assertEqual(target.read_text(encoding="utf-8").strip(), accepted_row)

    def test_already_present_line_is_not_double_counted(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp) / "out"
            out_dir.mkdir()
            accepted_row = json.dumps(
                {"attempts": [{"function": "func_1", "status": "accepted"}]}, sort_keys=True
            )
            (out_dir / "merge-history.jsonl").write_text(accepted_row + "\n", encoding="utf-8")
            target = Path(tmp) / "host-stats.jsonl"
            target.write_text(accepted_row + "\n", encoding="utf-8")
            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": str(target)}):
                container_merge.import_fresh_history_after_accept(out_dir, repo_root=Path(tmp))
            self.assertEqual(target.read_text(encoding="utf-8").count(accepted_row), 1)

    def test_disabled_host_history_returns_status_without_writing(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp) / "out"
            out_dir.mkdir()
            (out_dir / "merge-history.jsonl").write_text(
                json.dumps({"attempts": [{"status": "accepted"}]}) + "\n", encoding="utf-8"
            )
            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": ""}):
                status_line = container_merge.import_fresh_history_after_accept(
                    out_dir, repo_root=Path(tmp)
                )
        self.assertIsNotNone(status_line)
        self.assertIn("disabled", status_line)


class GitCommitOnlyPathsTests(unittest.TestCase):
    """``git_commit_only_paths``: the multi-path generalisation of
    ``git_commit_only`` (which is now just its single-path case)."""

    def test_git_commit_only_delegates_to_paths_form(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(
                container_merge, "git_commit_only_paths", return_value=(True, "ok")
            ) as paths_mock:
                ok, output = container_merge.git_commit_only(
                    "disasm/src/X.c", "msg", repo_root=repo_root
                )
            self.assertTrue(ok)
            self.assertEqual(output, "ok")
            paths_mock.assert_called_once_with(
                ["disasm/src/X.c"], "msg", repo_root=repo_root
            )

    def test_git_commit_only_paths_builds_multi_path_cmd(self) -> None:
        calls: list[list[str]] = []

        def fake_run(cmd, *, cwd, capture_output, text, env):
            calls.append(list(cmd))
            return _FakeGateProc(0, "committed", "")

        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(container_merge.subprocess, "run", side_effect=fake_run):
                ok, output = container_merge.git_commit_only_paths(
                    ["disasm/src/X.c", "docs/regions/X.md"], "msg", repo_root=repo_root
                )
        self.assertTrue(ok)
        self.assertEqual(output, "committed")
        self.assertEqual(
            calls[0],
            ["git", "commit", "--only", "disasm/src/X.c", "docs/regions/X.md", "-m", "msg"],
        )


class RegionNotesHelperTests(unittest.TestCase):
    """Pure helpers used by ``apply_region_notes``: filename<->source
    mapping, note-line extraction, and the docs/regions/<source>.md path
    computation (mirroring tools/region_notes.py's own path_for(), but
    parameterised on a throwaway repo_root)."""

    def test_source_from_filename_round_trips_slashes(self) -> None:
        self.assertEqual(
            container_merge.region_notes_source_from_filename(
                Path("disasm__src__4AC10.c.md")
            ),
            "disasm/src/4AC10.c",
        )

    def test_source_from_filename_top_level_source(self) -> None:
        self.assertEqual(
            container_merge.region_notes_source_from_filename(Path("X.c.md")), "X.c"
        )

    def test_region_notes_lines_skips_headers_and_blank_lines(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "notes.md"
            path.write_text(
                "# Region notes -- disasm/src/X.c\n\n"
                "Some intro.\n\n"
                "## 2026-09-02\n\n"
                "skip permuter on this one; offset math\n\n"
                "## 2026-09-02\n\n"
                "second note here\n",
                encoding="utf-8",
            )
            lines = container_merge.region_notes_lines(path)
        self.assertEqual(
            lines,
            ["Some intro.", "skip permuter on this one; offset math", "second note here"],
        )

    def test_region_notes_lines_missing_file_is_empty(self) -> None:
        self.assertEqual(
            container_merge.region_notes_lines(Path("/no/such/notes.md")), []
        )

    def test_target_path_relative_to_disasm_src(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp).resolve()
            target = container_merge.region_notes_target_path(repo_root, "disasm/src/4AC10.c")
        self.assertEqual(target, (repo_root / "docs" / "regions" / "4AC10.c").with_suffix(".md"))

    def test_target_path_falls_back_to_repo_relative(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp).resolve()
            target = container_merge.region_notes_target_path(repo_root, "other/place/X.c")
        self.assertEqual(
            target, (repo_root / "docs" / "regions" / "other" / "place" / "X.c").with_suffix(".md")
        )

    def test_target_relpath_is_repo_relative_string(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            rel = container_merge.region_notes_target_relpath(repo_root, "disasm/src/4AC10.c")
        self.assertEqual(rel, "docs/regions/4AC10.md")

    def test_existing_region_notes_text_missing_file_is_empty_string(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            self.assertEqual(
                container_merge.existing_region_notes_text(repo_root, "disasm/src/X.c"), ""
            )

    def test_existing_region_notes_text_reads_current_content(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            target = repo_root / "docs" / "regions" / "X.md"
            target.parent.mkdir(parents=True)
            target.write_text("existing note\n", encoding="utf-8")
            self.assertEqual(
                container_merge.existing_region_notes_text(repo_root, "disasm/src/X.c"),
                "existing note\n",
            )


class RunRegionNotesAppendTests(unittest.TestCase):
    """``run_region_notes_append``'s own subprocess call shape."""

    def test_builds_expected_command(self) -> None:
        calls: list[list[str]] = []

        def fake_run(cmd, *, cwd, capture_output, text, timeout, env):
            calls.append(list(cmd))
            return _FakeGateProc(0, "appended to docs/regions/X.md", "")

        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(container_merge.subprocess, "run", side_effect=fake_run):
                ok, output = container_merge.run_region_notes_append(
                    "disasm/src/X.c", "note text", repo_root=repo_root
                )
        self.assertTrue(ok)
        self.assertIn("appended", output)
        self.assertEqual(
            calls[0],
            [
                sys.executable,
                str(repo_root / "tools" / "region_notes.py"),
                "append",
                "disasm/src/X.c",
                "--text",
                "note text",
            ],
        )

    def test_nonzero_exit_is_reported_as_failure(self) -> None:
        def fake_run(cmd, *, cwd, capture_output, text, timeout, env):
            return _FakeGateProc(1, "", "boom")

        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(container_merge.subprocess, "run", side_effect=fake_run):
                ok, output = container_merge.run_region_notes_append(
                    "disasm/src/X.c", "note text", repo_root=repo_root
                )
        self.assertFalse(ok)
        self.assertIn("boom", output)


class ApplyRegionNotesTests(unittest.TestCase):
    """``apply_region_notes``: dedupe against docs/regions/<source>.md,
    commit grouping (folded into an owner's land commit vs. its own
    "Record container run notes" commit), --no-notes / dry-run behaviour.
    ``run_region_notes_append`` / ``git_commit_only_paths`` are stubbed
    throughout -- this never runs the real tools or touches real git.
    """

    def _write_notes(self, out_dir: Path, source: str, lines: list[str]) -> Path:
        notes_dir = out_dir / "region-notes"
        notes_dir.mkdir(parents=True, exist_ok=True)
        filename = source.replace("/", "__") + ".md"
        path = notes_dir / filename
        body = "\n\n".join(f"## 2026-09-02\n\n{line}" for line in lines)
        path.write_text(f"# Region notes -- {source}\n\n{body}\n", encoding="utf-8")
        return path

    def test_no_region_notes_dir_is_a_clean_noop(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp) / "out"
            out_dir.mkdir()
            results = container_merge.apply_region_notes(
                out_dir, repo_root=Path(tmp), commit=False, dry_run=False,
            )
        self.assertEqual(results, [])

    def test_appends_new_lines_and_skips_already_present(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            repo_root.mkdir()
            out_dir.mkdir()
            target = repo_root / "docs" / "regions" / "X.md"
            target.parent.mkdir(parents=True)
            target.write_text("already known note\n", encoding="utf-8")

            self._write_notes(
                out_dir, "disasm/src/X.c", ["already known note", "brand new note"]
            )

            appended_calls: list[tuple[str, str]] = []

            def fake_append(source, text, *, repo_root):
                appended_calls.append((source, text))
                return True, "appended"

            with mock.patch.object(
                container_merge, "run_region_notes_append", side_effect=fake_append
            ):
                results = container_merge.apply_region_notes(
                    out_dir, repo_root=repo_root, commit=False, dry_run=False,
                )
        self.assertEqual(len(results), 1)
        self.assertEqual(results[0].source, "disasm/src/X.c")
        self.assertEqual(results[0].appended, ["brand new note"])
        self.assertEqual(appended_calls, [("disasm/src/X.c", "brand new note")])

    def test_duplicate_line_within_notes_file_appended_once(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            repo_root.mkdir()
            out_dir.mkdir()
            self._write_notes(out_dir, "disasm/src/X.c", ["same note", "same note"])

            with mock.patch.object(
                container_merge, "run_region_notes_append", return_value=(True, "appended")
            ) as append_mock:
                results = container_merge.apply_region_notes(
                    out_dir, repo_root=repo_root, commit=False, dry_run=False,
                )
        self.assertEqual(results[0].appended, ["same note"])
        append_mock.assert_called_once()

    def test_append_failure_is_logged_and_skipped(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            repo_root.mkdir()
            out_dir.mkdir()
            self._write_notes(out_dir, "disasm/src/X.c", ["a note"])

            with mock.patch.object(
                container_merge, "run_region_notes_append", return_value=(False, "boom")
            ):
                buffer = io.StringIO()
                with contextlib.redirect_stderr(buffer):
                    results = container_merge.apply_region_notes(
                        out_dir, repo_root=repo_root, commit=False, dry_run=False,
                    )
        self.assertEqual(results[0].appended, [])
        self.assertIn("boom", buffer.getvalue())

    def test_dry_run_never_calls_append_or_commit(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            repo_root.mkdir()
            out_dir.mkdir()
            self._write_notes(out_dir, "disasm/src/X.c", ["a note"])

            with mock.patch.object(
                container_merge, "run_region_notes_append"
            ) as append_mock, mock.patch.object(
                container_merge, "git_commit_only_paths"
            ) as commit_mock:
                results = container_merge.apply_region_notes(
                    out_dir, repo_root=repo_root, commit=True, dry_run=True,
                )
        append_mock.assert_not_called()
        commit_mock.assert_not_called()
        self.assertEqual(results[0].appended, ["a note"])
        self.assertFalse(results[0].committed)

    def test_notes_folded_into_owners_land_commit_when_source_was_committed(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            repo_root.mkdir()
            out_dir.mkdir()
            self._write_notes(out_dir, "disasm/src/X.c", ["a note"])
            rows = [
                container_merge.MergeRow(
                    owner="func_1", source="disasm/src/X.c", function="func_1",
                    status="accepted", detail="", committed=True, commit_detail="committed",
                )
            ]

            with mock.patch.object(
                container_merge, "run_region_notes_append", return_value=(True, "appended")
            ), mock.patch.object(
                container_merge, "git_commit_only_paths", return_value=(True, "committed")
            ) as commit_mock:
                results = container_merge.apply_region_notes(
                    out_dir, repo_root=repo_root, commit=True, dry_run=False, rows=rows,
                )
        self.assertTrue(results[0].committed)
        commit_mock.assert_called_once_with(
            ["disasm/src/X.c", "docs/regions/X.md"],
            "Land container match for func_1",
            repo_root=repo_root,
        )

    def test_notes_get_own_commit_when_no_accept_for_source_this_run(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            repo_root.mkdir()
            out_dir.mkdir()
            self._write_notes(out_dir, "disasm/src/X.c", ["a note"])

            with mock.patch.object(
                container_merge, "run_region_notes_append", return_value=(True, "appended")
            ), mock.patch.object(
                container_merge, "git_commit_only_paths", return_value=(True, "committed")
            ) as commit_mock:
                results = container_merge.apply_region_notes(
                    out_dir, repo_root=repo_root, commit=True, dry_run=False, rows=[],
                )
        self.assertTrue(results[0].committed)
        commit_mock.assert_called_once_with(
            ["docs/regions/X.md"],
            "Record container run notes for disasm/src/X.c",
            repo_root=repo_root,
        )

    def test_no_commit_flag_appends_but_never_commits(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            repo_root.mkdir()
            out_dir.mkdir()
            self._write_notes(out_dir, "disasm/src/X.c", ["a note"])

            with mock.patch.object(
                container_merge, "run_region_notes_append", return_value=(True, "appended")
            ), mock.patch.object(container_merge, "git_commit_only_paths") as commit_mock:
                results = container_merge.apply_region_notes(
                    out_dir, repo_root=repo_root, commit=False, dry_run=False,
                )
        self.assertFalse(results[0].committed)
        commit_mock.assert_not_called()

    def test_no_new_lines_never_commits(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp) / "repo"
            out_dir = Path(tmp) / "out"
            repo_root.mkdir()
            out_dir.mkdir()
            target = repo_root / "docs" / "regions" / "X.md"
            target.parent.mkdir(parents=True)
            target.write_text("already known\n", encoding="utf-8")
            self._write_notes(out_dir, "disasm/src/X.c", ["already known"])

            with mock.patch.object(
                container_merge, "run_region_notes_append"
            ) as append_mock, mock.patch.object(
                container_merge, "git_commit_only_paths"
            ) as commit_mock:
                results = container_merge.apply_region_notes(
                    out_dir, repo_root=repo_root, commit=True, dry_run=False,
                )
        self.assertEqual(results[0].appended, [])
        append_mock.assert_not_called()
        commit_mock.assert_not_called()

    def test_merge_no_notes_flag_skips_region_notes_entirely(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/X.c")
            self._write_notes(out_dir, "disasm/src/X.c", ["a note"])
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "apply_region_notes"
            ) as apply_mock, mock.patch.object(
                container_merge, "name_after_commit", return_value=(None, "")
            ):
                buffer = io.StringIO()
                with contextlib.redirect_stdout(buffer):
                    container_merge.merge(
                        out_dir, repo_root=out_dir, commit=False, dry_run=False, no_notes=True,
                    )
        apply_mock.assert_not_called()

    def test_merge_records_notes_applied_in_report(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/X.c")
            self._write_notes(out_dir, "disasm/src/X.c", ["a note"])
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "run_region_notes_append", return_value=(True, "appended")
            ), mock.patch.object(
                container_merge, "name_after_commit", return_value=(None, "")
            ):
                buffer = io.StringIO()
                with contextlib.redirect_stdout(buffer):
                    container_merge.merge(
                        out_dir, repo_root=out_dir, commit=False, dry_run=False,
                    )
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
        self.assertEqual(report["notes_applied"], {"disasm/src/X.c": ["a note"]})


class NameDecompiledSubprocessTests(unittest.TestCase):
    """``run_name_decompiled_plan`` / ``run_name_decompiled_apply``'s own
    subprocess call shape, and the stdout parsers layered on top of them."""

    def test_plan_builds_expected_command(self) -> None:
        calls: list[list[str]] = []

        def fake_run(cmd, *, cwd, capture_output, text, timeout, env):
            calls.append(list(cmd))
            return _FakeGateProc(0, "function ...\n", "")

        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(container_merge.subprocess, "run", side_effect=fake_run):
                result = container_merge.run_name_decompiled_plan(
                    "func_80012345", repo_root=repo_root
                )
        self.assertEqual(result["returncode"], 0)
        self.assertEqual(
            calls[0],
            [
                sys.executable,
                str(repo_root / "tools" / "name_decompiled.py"),
                "plan",
                "--only",
                "func_80012345",
                "--repo-root",
                str(repo_root),
            ],
        )

    def test_apply_builds_expected_command(self) -> None:
        calls: list[list[str]] = []

        def fake_run(cmd, *, cwd, capture_output, text, timeout, env):
            calls.append(list(cmd))
            return _FakeGateProc(0, "renamed 1 function(s)\n  func_1 -> Real\n", "")

        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(container_merge.subprocess, "run", side_effect=fake_run):
                result = container_merge.run_name_decompiled_apply(
                    "func_1", repo_root=repo_root
                )
        self.assertEqual(result["returncode"], 0)
        self.assertEqual(
            calls[0],
            [
                sys.executable,
                str(repo_root / "tools" / "name_decompiled.py"),
                "apply",
                "--only",
                "func_1",
                "--repo-root",
                str(repo_root),
            ],
        )

    def test_parse_planned_name_finds_matching_row(self) -> None:
        stdout = (
            f"{'function':<16} {'new name':<40} {'source':<18} def file\n"
            f"{'func_80012345':<16} {'Audio_DoThing':<40} {'gs_names.json':<18} disasm/src/foo.c\n"
            "\n1 function(s) ready to rename (evidence-backed, decompiled, still func_-named)\n"
        )
        self.assertEqual(
            container_merge.parse_planned_name("func_80012345", stdout), "Audio_DoThing"
        )

    def test_parse_planned_name_no_row_returns_none(self) -> None:
        stdout = (
            f"{'function':<16} {'new name':<40} {'source':<18} def file\n"
            "\n0 function(s) ready to rename (evidence-backed, decompiled, still func_-named)\n"
        )
        self.assertIsNone(container_merge.parse_planned_name("func_80012345", stdout))

    def test_parse_planned_name_header_alone_is_not_mistaken_for_a_row(self) -> None:
        """The header line's first column is the literal string "function"
        -- never a real ``func_...`` name -- so querying for a real function
        name against header-only output (no matching data row) is None,
        exactly like the "not proposed at all" case."""
        stdout = f"{'function':<16} {'new name':<40} {'source':<18} def file\n"
        self.assertIsNone(container_merge.parse_planned_name("func_80099999", stdout))

    def test_parse_applied_name_finds_matching_row(self) -> None:
        stdout = "renamed 1 function(s)\n  func_1 -> Audio_DoThing\n"
        self.assertEqual(
            container_merge.parse_applied_name("func_1", stdout), "Audio_DoThing"
        )

    def test_parse_applied_name_refused_row_returns_none(self) -> None:
        stdout = (
            "would rename 0 function(s)\n"
            "refused 1 collision(s):\n"
            "  func_1 -> Audio_DoThing: 'Audio_DoThing' already exists\n"
        )
        self.assertIsNone(container_merge.parse_applied_name("func_1", stdout))

    def test_parse_applied_name_no_match_returns_none(self) -> None:
        self.assertIsNone(container_merge.parse_applied_name("func_1", "renamed 0 function(s)\n"))


class NameAfterCommitTests(unittest.TestCase):
    """``name_after_commit``: plan-then-apply, never fatal on failure."""

    def test_no_evidence_backed_name_returns_none(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(
                container_merge, "run_name_decompiled_plan",
                return_value={"returncode": 0, "stdout": "function ...\n", "stderr": ""},
            ), mock.patch.object(
                container_merge, "run_name_decompiled_apply"
            ) as apply_mock:
                new_name, detail = container_merge.name_after_commit(
                    "func_1", repo_root=repo_root
                )
        self.assertIsNone(new_name)
        self.assertEqual(detail, "no evidence-backed name proposed")
        apply_mock.assert_not_called()

    def test_proposed_name_applied_successfully(self) -> None:
        plan_stdout = (
            f"{'function':<16} {'new name':<40} {'source':<18} def file\n"
            f"{'func_1':<16} {'Real_Name':<40} {'gs_names.json':<18} disasm/src/foo.c\n"
        )
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(
                container_merge, "run_name_decompiled_plan",
                return_value={"returncode": 0, "stdout": plan_stdout, "stderr": ""},
            ), mock.patch.object(
                container_merge, "run_name_decompiled_apply",
                return_value={
                    "returncode": 0, "stdout": "renamed 1 function(s)\n  func_1 -> Real_Name\n",
                    "stderr": "",
                },
            ):
                new_name, detail = container_merge.name_after_commit(
                    "func_1", repo_root=repo_root
                )
        self.assertEqual(new_name, "Real_Name")
        self.assertIn("Real_Name", detail)

    def test_proposed_name_refused_by_apply_returns_none(self) -> None:
        plan_stdout = (
            f"{'function':<16} {'new name':<40} {'source':<18} def file\n"
            f"{'func_1':<16} {'Real_Name':<40} {'gs_names.json':<18} disasm/src/foo.c\n"
        )
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(
                container_merge, "run_name_decompiled_plan",
                return_value={"returncode": 0, "stdout": plan_stdout, "stderr": ""},
            ), mock.patch.object(
                container_merge, "run_name_decompiled_apply",
                return_value={
                    "returncode": 1,
                    "stdout": (
                        "would rename 0 function(s)\nrefused 1 collision(s):\n"
                        "  func_1 -> Real_Name: 'Real_Name' already exists\n"
                    ),
                    "stderr": "",
                },
            ):
                new_name, detail = container_merge.name_after_commit(
                    "func_1", repo_root=repo_root
                )
        self.assertIsNone(new_name)
        self.assertIn("func_1", detail)

    def test_plan_subprocess_failure_is_never_fatal(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(
                container_merge, "run_name_decompiled_plan",
                side_effect=OSError("no such file"),
            ):
                new_name, detail = container_merge.name_after_commit(
                    "func_1", repo_root=repo_root
                )
        self.assertIsNone(new_name)
        self.assertIn("failed to run", detail)

    def test_apply_subprocess_failure_is_never_fatal(self) -> None:
        plan_stdout = (
            f"{'function':<16} {'new name':<40} {'source':<18} def file\n"
            f"{'func_1':<16} {'Real_Name':<40} {'gs_names.json':<18} disasm/src/foo.c\n"
        )
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(
                container_merge, "run_name_decompiled_plan",
                return_value={"returncode": 0, "stdout": plan_stdout, "stderr": ""},
            ), mock.patch.object(
                container_merge, "run_name_decompiled_apply",
                side_effect=OSError("no such file"),
            ):
                new_name, detail = container_merge.name_after_commit(
                    "func_1", repo_root=repo_root
                )
        self.assertIsNone(new_name)
        self.assertIn("failed to run", detail)


class GitStatusPathsTests(unittest.TestCase):
    def test_filters_to_given_prefixes(self) -> None:
        porcelain = (
            " M disasm/src/X.c\n"
            "?? disasm/include/Y.h\n"
            " M disasm/linker_scripts/us/symbol_addrs_code.txt\n"
            " M docs/regions/X.md\n"
        )

        def fake_run(cmd, *, cwd, capture_output, text, env):
            return _FakeGateProc(0, porcelain, "")

        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(container_merge.subprocess, "run", side_effect=fake_run):
                paths = container_merge.git_status_paths(
                    repo_root, prefixes=("disasm/src", "disasm/include")
                )
        self.assertEqual(paths, ["disasm/include/Y.h", "disasm/src/X.c"])

    def test_handles_rename_lines(self) -> None:
        porcelain = "R  disasm/src/Old.c -> disasm/src/New.c\n"

        def fake_run(cmd, *, cwd, capture_output, text, env):
            return _FakeGateProc(0, porcelain, "")

        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(container_merge.subprocess, "run", side_effect=fake_run):
                paths = container_merge.git_status_paths(repo_root, prefixes=("disasm/src",))
        self.assertEqual(paths, ["disasm/src/New.c"])

    def test_nonzero_exit_returns_empty_list(self) -> None:
        def fake_run(cmd, *, cwd, capture_output, text, env):
            return _FakeGateProc(1, "", "fatal: not a git repo")

        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(container_merge.subprocess, "run", side_effect=fake_run):
                paths = container_merge.git_status_paths(repo_root, prefixes=("disasm/src",))
        self.assertEqual(paths, [])


class MergeNamingIntegrationTests(unittest.TestCase):
    """``merge()``'s naming-on-accept step end to end: only committed
    accepts are offered, the follow-up commit uses the file list
    ``git_status_paths`` reports, --no-naming disables it, and a naming
    failure never affects merge()'s own exit code."""

    def _run_merge(self, out_dir: Path, **kwargs) -> tuple[int, str]:
        buffer = io.StringIO()
        with contextlib.redirect_stdout(buffer):
            code = container_merge.merge(out_dir, repo_root=out_dir, **kwargs)
        return code, buffer.getvalue()

    @staticmethod
    def _status_side_effect(src_paths):
        """A `git_status_paths` side_effect: `[]` for the
        disasm/linker_scripts-only query (the symtab-revert check), else
        `src_paths` (the disasm/src|include|aliases.ld naming-commit query)
        -- distinguishing the two calls `merge()`'s naming step now makes,
        since a plain `return_value=` would (wrongly) return the same list
        for both.
        """

        def fn(repo_root, *, prefixes):
            if prefixes == ("disasm/linker_scripts",):
                return []
            return src_paths

        return fn

    def test_committed_accept_gets_named_and_committed(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/X.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ), mock.patch.object(
                container_merge, "name_after_commit", return_value=("Real_Name", "renamed")
            ), mock.patch.object(
                container_merge, "git_status_paths",
                side_effect=self._status_side_effect(["disasm/src/X.c"]),
            ), mock.patch.object(
                container_merge, "append_name_alias", return_value=True
            ), mock.patch.object(
                container_merge, "git_commit_only_paths", return_value=(True, "committed")
            ) as naming_commit_mock:
                code, out = self._run_merge(out_dir, commit=True, dry_run=False)
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
        self.assertEqual(code, 0)
        naming_commit_mock.assert_called_once_with(
            ["disasm/src/X.c"], "Name func_1 -> Real_Name", repo_root=out_dir
        )
        self.assertEqual(report["names"], {"func_1": "Real_Name"})
        self.assertIn("named func_1 -> Real_Name", out)

    def test_uncommitted_accept_is_never_offered_for_naming(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/X.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "name_after_commit"
            ) as name_mock:
                # commit=False: row.committed is always False.
                self._run_merge(out_dir, commit=False, dry_run=False)
        name_mock.assert_not_called()

    def test_rejected_owner_is_never_offered_for_naming(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/X.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_rejected_result()
            ), mock.patch.object(
                container_merge, "name_after_commit"
            ) as name_mock:
                self._run_merge(out_dir, commit=True, dry_run=False)
        name_mock.assert_not_called()

    def test_no_naming_flag_skips_naming_entirely(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/X.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ), mock.patch.object(
                container_merge, "name_after_commit"
            ) as name_mock:
                self._run_merge(out_dir, commit=True, dry_run=False, no_naming=True)
        name_mock.assert_not_called()

    def test_naming_failure_is_logged_but_never_fatal(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/X.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ), mock.patch.object(
                container_merge, "name_after_commit",
                return_value=(None, "name_decompiled plan failed to run: boom"),
            ):
                buffer_err = io.StringIO()
                with contextlib.redirect_stderr(buffer_err):
                    code, _out = self._run_merge(out_dir, commit=True, dry_run=False)
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
        self.assertEqual(code, 0)
        self.assertIn("boom", buffer_err.getvalue())
        self.assertEqual(report["names"], {})

    def test_naming_commit_failure_leaves_names_empty_but_not_fatal(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/X.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ), mock.patch.object(
                container_merge, "name_after_commit", return_value=("Real_Name", "renamed")
            ), mock.patch.object(
                container_merge, "git_status_paths",
                side_effect=self._status_side_effect(["disasm/src/X.c"]),
            ), mock.patch.object(
                container_merge, "append_name_alias", return_value=True
            ), mock.patch.object(
                container_merge, "git_commit_only_paths", return_value=(False, "nothing staged")
            ):
                buffer_err = io.StringIO()
                with contextlib.redirect_stderr(buffer_err):
                    code, _out = self._run_merge(out_dir, commit=True, dry_run=False)
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
        self.assertEqual(code, 0)
        self.assertEqual(report["names"], {})
        self.assertIn("nothing staged", buffer_err.getvalue())

    def test_naming_with_no_changed_files_is_logged_but_not_fatal(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/X.c")
            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ), mock.patch.object(
                container_merge, "name_after_commit", return_value=("Real_Name", "renamed")
            ), mock.patch.object(
                container_merge, "git_status_paths", side_effect=self._status_side_effect([])
            ), mock.patch.object(
                container_merge, "append_name_alias", return_value=True
            ), mock.patch.object(
                container_merge, "git_commit_only_paths"
            ) as commit_mock:
                buffer_err = io.StringIO()
                with contextlib.redirect_stderr(buffer_err):
                    code, _out = self._run_merge(out_dir, commit=True, dry_run=False)
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
        self.assertEqual(code, 0)
        commit_mock.assert_not_called()
        self.assertEqual(report["names"], {})
        self.assertIn("no changed files", buffer_err.getvalue())

    def test_rename_reverts_symtab_but_extends_and_commits_aliases_ld(self) -> None:
        """The 2026-09-02 incident: `tools/name_decompiled.py apply` renamed
        a matched owner's entry in symbol_addrs_code.txt, but `merge()` only
        ever committed disasm/src/disasm/include -- the symtab rename was
        left dirty in the merge repo, and a container's pre-extracted asm
        tree (which still calls the function by its old name) failed to
        link. The fix: revert the symtab (and anything else under
        disasm/linker_scripts except aliases.ld), append an `old = new;`
        alias to aliases.ld instead, and commit aliases.ld alongside
        disasm/src -- mirroring PR #58's hand-applied fix.
        """
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1", source="disasm/src/X.c")
            aliases_path = out_dir / container_merge._ALIASES_LD_PATH
            aliases_path.parent.mkdir(parents=True, exist_ok=True)
            aliases_path.write_text(
                "/* header */\nAudio_ThreadEntry = func_80035174;\n", encoding="utf-8"
            )

            def status_side_effect(repo_root, *, prefixes):
                if prefixes == ("disasm/linker_scripts",):
                    return [
                        "disasm/linker_scripts/us/symbol_addrs_code.txt",
                        container_merge._ALIASES_LD_PATH,
                    ]
                return ["disasm/src/X.c", container_merge._ALIASES_LD_PATH]

            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_accepted_result("func_1")
            ), mock.patch.object(
                container_merge, "git_commit_only", return_value=(True, "committed")
            ), mock.patch.object(
                container_merge, "name_after_commit", return_value=("Real_Name", "renamed")
            ), mock.patch.object(
                container_merge, "git_status_paths", side_effect=status_side_effect
            ), mock.patch.object(
                container_merge, "git_checkout_paths", return_value=True
            ) as checkout_mock, mock.patch.object(
                container_merge, "git_commit_only_paths", return_value=(True, "committed")
            ) as naming_commit_mock:
                code, out = self._run_merge(out_dir, commit=True, dry_run=False)
            report = json.loads((out_dir / "merge-report.json").read_text(encoding="utf-8"))
            # Read back before the tmp dir is torn down (_tmp_out_dir's own
            # scope, not this test's).
            alias_lines = aliases_path.read_text(encoding="utf-8").splitlines()

        self.assertEqual(code, 0)
        # symbol_addrs_code.txt is checked out (reverted) -- aliases.ld is
        # deliberately excluded from that revert.
        checkout_mock.assert_called_once_with(
            ["disasm/linker_scripts/us/symbol_addrs_code.txt"], repo_root=out_dir
        )
        # The alias line was actually appended (append_name_alias itself is
        # not mocked in this test).
        self.assertIn("func_1 = Real_Name;", alias_lines)
        self.assertIn("Audio_ThreadEntry = func_80035174;", alias_lines)  # untouched
        # aliases.ld rides along in the same naming commit as disasm/src.
        naming_commit_mock.assert_called_once_with(
            ["disasm/src/X.c", container_merge._ALIASES_LD_PATH],
            "Name func_1 -> Real_Name",
            repo_root=out_dir,
        )
        self.assertEqual(report["names"], {"func_1": "Real_Name"})
        self.assertIn("aliased func_1 -> Real_Name", out)


class GitCheckoutPathsTests(unittest.TestCase):
    def test_builds_checkout_cmd_and_returns_true_on_success(self) -> None:
        calls: list[list[str]] = []

        def fake_run(cmd, *, cwd, capture_output, text, env):
            calls.append(list(cmd))
            return _FakeGateProc(0)

        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(container_merge.subprocess, "run", side_effect=fake_run):
                ok = container_merge.git_checkout_paths(
                    ["disasm/linker_scripts/us/symbol_addrs_code.txt"], repo_root=repo_root
                )
        self.assertTrue(ok)
        self.assertEqual(
            calls[0],
            ["git", "checkout", "--", "disasm/linker_scripts/us/symbol_addrs_code.txt"],
        )

    def test_empty_paths_is_a_noop_success(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(container_merge.subprocess, "run") as run_mock:
                ok = container_merge.git_checkout_paths([], repo_root=repo_root)
        self.assertTrue(ok)
        run_mock.assert_not_called()

    def test_nonzero_exit_returns_false(self) -> None:
        def fake_run(cmd, *, cwd, capture_output, text, env):
            return _FakeGateProc(1, "", "error: pathspec did not match")

        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(container_merge.subprocess, "run", side_effect=fake_run):
                ok = container_merge.git_checkout_paths(["disasm/src/X.c"], repo_root=repo_root)
        self.assertFalse(ok)

    def test_oserror_returns_false(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            with mock.patch.object(container_merge.subprocess, "run", side_effect=OSError("no git")):
                ok = container_merge.git_checkout_paths(["disasm/src/X.c"], repo_root=repo_root)
        self.assertFalse(ok)


class AppendNameAliasTests(unittest.TestCase):
    def test_appends_line_to_existing_file(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            path = repo_root / container_merge._ALIASES_LD_PATH
            path.parent.mkdir(parents=True)
            path.write_text("/* header */\nAudio_ThreadEntry = func_80035174;\n", encoding="utf-8")

            appended = container_merge.append_name_alias(
                "func_8005805C", "GbSave_IdentifyFormat", repo_root=repo_root
            )
            lines = path.read_text(encoding="utf-8").splitlines()
        self.assertTrue(appended)
        self.assertEqual(lines[-1], "func_8005805C = GbSave_IdentifyFormat;")
        self.assertIn("Audio_ThreadEntry = func_80035174;", lines)

    def test_creates_missing_trailing_newline_before_appending(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            path = repo_root / container_merge._ALIASES_LD_PATH
            path.parent.mkdir(parents=True)
            path.write_text("Audio_ThreadEntry = func_80035174;", encoding="utf-8")  # no trailing \n

            container_merge.append_name_alias("old_fn", "New_Fn", repo_root=repo_root)
            text = path.read_text(encoding="utf-8")
        self.assertEqual(
            text, "Audio_ThreadEntry = func_80035174;\nold_fn = New_Fn;\n"
        )

    def test_skips_identical_existing_line(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            path = repo_root / container_merge._ALIASES_LD_PATH
            path.parent.mkdir(parents=True)
            path.write_text("func_8005805C = GbSave_IdentifyFormat;\n", encoding="utf-8")

            appended = container_merge.append_name_alias(
                "func_8005805C", "GbSave_IdentifyFormat", repo_root=repo_root
            )
            count = path.read_text(encoding="utf-8").count("func_8005805C = GbSave_IdentifyFormat;")
        self.assertFalse(appended)
        self.assertEqual(count, 1)

    def test_missing_parent_directory_returns_false(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)  # disasm/linker_scripts/us doesn't exist
            appended = container_merge.append_name_alias("old_fn", "New_Fn", repo_root=repo_root)
        self.assertFalse(appended)


class SummaryTests(unittest.TestCase):
    def test_missing_files_report_and_return_nonzero(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            buffer = io.StringIO()
            with contextlib.redirect_stdout(buffer):
                code = container_merge.summary_command(Path(tmp))
        self.assertEqual(code, 1)

    def test_state_table_lists_each_owner(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            out_dir = Path(tmp)
            (out_dir / "state.json").write_text(
                json.dumps(
                    {
                        "func_1": {
                            "best_similarity": 0.97,
                            "iterations": 12,
                            "history": [0.5, 0.9, 0.97],
                            "status": "requeue",
                        }
                    }
                ),
                encoding="utf-8",
            )
            buffer = io.StringIO()
            with contextlib.redirect_stdout(buffer):
                code = container_merge.summary_command(out_dir)
        self.assertEqual(code, 0)
        out = buffer.getvalue()
        self.assertIn("func_1", out)
        self.assertIn("0.9700", out)
        self.assertIn("requeue", out)

    def test_summary_table_renders_scalars_and_nested_owner_map(self) -> None:
        summary = {
            "owners_attempted": 3,
            "owners_matched": 1,
            "wall_time_seconds": 1800,
            "best_per_owner": {"func_1": 0.97, "func_2": 1.0},
        }
        text = container_merge.format_summary(summary)
        self.assertIn("owners_attempted:", text)
        self.assertIn("best_per_owner:", text)
        self.assertIn("func_2:", text)

    def test_format_summary_empty(self) -> None:
        self.assertEqual(container_merge.format_summary({}), "(empty)")

    def test_format_state_empty(self) -> None:
        self.assertEqual(container_merge.format_state({}), "(empty)")


if __name__ == "__main__":
    unittest.main()
