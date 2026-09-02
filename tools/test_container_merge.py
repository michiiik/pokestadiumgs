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


def _write_batch(directory: Path, owner: str, *, source: str = "disasm/src/X.c") -> Path:
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


class MergeTests(unittest.TestCase):
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

    def test_rejected_batch_is_never_committed_in_a_merge_run(self) -> None:
        with _tmp_out_dir() as out_dir:
            _write_batch(out_dir / "accepted", "func_1")

            with mock.patch.object(
                container_merge, "run_fleet_probe_gate", return_value=_rejected_result()
            ), mock.patch.object(container_merge, "git_commit_only") as commit_mock:
                self._run_merge(out_dir, commit=True, dry_run=False)
        commit_mock.assert_not_called()


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
