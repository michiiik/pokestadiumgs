#!/usr/bin/env python3
"""Tests for tools/probe_stats.py and tools/check_decomp_provenance.py."""

from __future__ import annotations

import json
import os
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import probe_stats  # noqa: E402
import check_decomp_provenance as provenance  # noqa: E402


class StatsPathTests(unittest.TestCase):
    def test_unset_env_resolves_to_new_default_location(self) -> None:
        with mock.patch.dict(os.environ, {}, clear=False):
            os.environ.pop("PRAGMA_PROBE_STATS", None)
            self.assertEqual(probe_stats.stats_path(), probe_stats.DEFAULT_STATS_PATH)

    def test_default_location_is_outside_build_dir(self) -> None:
        parts = probe_stats.DEFAULT_STATS_PATH.parts
        self.assertNotIn("build", parts)
        self.assertIn("probe-stats", parts)

    def test_empty_string_disables(self) -> None:
        with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": ""}):
            self.assertIsNone(probe_stats.stats_path())

    def test_explicit_override(self) -> None:
        with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": "/tmp/custom-stats.jsonl"}):
            self.assertEqual(probe_stats.stats_path(), Path("/tmp/custom-stats.jsonl"))

    def test_legacy_stats_paths_points_at_old_build_location(self) -> None:
        legacy = probe_stats.legacy_stats_paths()
        self.assertEqual(len(legacy), 1)
        self.assertTrue(str(legacy[0]).endswith("disasm/build/probe-stats.jsonl"))


class ResolvePathsTests(unittest.TestCase):
    def test_explicit_path_does_not_pull_in_legacy(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            explicit = root / "explicit.jsonl"
            explicit.write_text('{"attempts": []}\n')
            legacy = root / "legacy.jsonl"
            legacy.write_text('{"attempts": []}\n')
            with mock.patch.object(probe_stats, "LEGACY_STATS_PATH", legacy):
                resolved = probe_stats.resolve_paths([explicit])
            self.assertEqual(resolved, [explicit])

    def test_default_merges_active_and_legacy(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            active = root / "active" / "probe-stats.jsonl"
            active.parent.mkdir(parents=True)
            active.write_text('{"attempts": []}\n')
            legacy = root / "legacy" / "probe-stats.jsonl"
            legacy.parent.mkdir(parents=True)
            legacy.write_text('{"attempts": []}\n')
            with mock.patch.object(probe_stats, "DEFAULT_STATS_PATH", active), mock.patch.object(
                probe_stats, "LEGACY_STATS_PATH", legacy
            ), mock.patch.dict(os.environ, {}, clear=False):
                os.environ.pop("PRAGMA_PROBE_STATS", None)
                resolved = probe_stats.resolve_paths(None)
            self.assertEqual(set(resolved), {active, legacy})

    def test_default_skips_legacy_when_disabled(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            legacy = root / "legacy" / "probe-stats.jsonl"
            legacy.parent.mkdir(parents=True)
            legacy.write_text('{"attempts": []}\n')
            with mock.patch.object(probe_stats, "LEGACY_STATS_PATH", legacy), mock.patch.dict(
                os.environ, {"PRAGMA_PROBE_STATS": ""}
            ):
                resolved = probe_stats.resolve_paths(None)
            # The active file is disabled, but a legacy file that exists is
            # still surfaced so old history is never silently dropped.
            self.assertEqual(resolved, [legacy])

    def test_missing_paths_are_not_returned(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            missing = Path(directory) / "nope.jsonl"
            self.assertEqual(probe_stats.resolve_paths([missing]), [])

    def test_includes_rotated_siblings_oldest_first(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            base = root / "probe-stats.jsonl"
            base.write_text('{"n": 0}\n')
            (root / "probe-stats.2.jsonl").write_text('{"n": 2}\n')
            (root / "probe-stats.1.jsonl").write_text('{"n": 1}\n')
            resolved = probe_stats.resolve_paths([base])
            self.assertEqual(
                [path.name for path in resolved],
                ["probe-stats.jsonl", "probe-stats.1.jsonl", "probe-stats.2.jsonl"],
            )


class IterBatchesTests(unittest.TestCase):
    def test_iter_batches_tolerates_corrupt_lines(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "stats.jsonl"
            path.write_text(
                '{"source": "a.c", "attempts": [{"function": "func_a"}]}\n'
                "not json at all\n"
                '{"truncated line missing brace"\n'
                '{"source": "b.c", "attempts": [{"function": "func_b"}]}\n'
            )
            batches = list(probe_stats.iter_batches([path]))
            self.assertEqual([batch["source"] for batch in batches], ["a.c", "b.c"])

    def test_iter_batches_skips_blank_lines(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "stats.jsonl"
            path.write_text('{"source": "a.c"}\n\n   \n{"source": "b.c"}\n')
            batches = list(probe_stats.iter_batches([path]))
            self.assertEqual(len(batches), 2)

    def test_iter_batches_reads_across_rotated_files(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            base = root / "probe-stats.jsonl"
            base.write_text('{"source": "new.c"}\n')
            (root / "probe-stats.1.jsonl").write_text('{"source": "old.c"}\n')
            batches = list(probe_stats.iter_batches([base]))
            self.assertEqual({batch["source"] for batch in batches}, {"new.c", "old.c"})

    def test_iter_attempts_flattens_every_batch(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "stats.jsonl"
            path.write_text(
                '{"attempts": [{"function": "func_a"}, {"function": "func_b"}]}\n'
                '{"attempts": [{"function": "func_c"}]}\n'
            )
            functions = [attempt["function"] for attempt in probe_stats.iter_attempts([path])]
            self.assertEqual(functions, ["func_a", "func_b", "func_c"])

    def test_old_schema_1_rows_without_new_fields_still_load(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "stats.jsonl"
            # No schema_version/timestamp/batch_id -- a pre-migration row.
            path.write_text(
                json.dumps({
                    "source": "disasm/src/x.c",
                    "counts": {"m2c:u8-void:accepted": 1},
                    "attempts": [{"function": "func_old", "status": "accepted", "candidate": "void func_old(void) {}"}],
                }) + "\n"
            )
            batches = list(probe_stats.iter_batches([path]))
            self.assertEqual(len(batches), 1)
            self.assertNotIn("schema_version", batches[0])
            attempts = list(probe_stats.iter_attempts([path]))
            self.assertEqual(attempts[0]["function"], "func_old")


class ShapeAttemptRowTests(unittest.TestCase):
    def test_drops_assembly_diff_fields(self) -> None:
        row = probe_stats.shape_attempt_row({
            "function": "func_a",
            "status": "compare_rejected",
            "assembly_diff": [{"expected": "x", "actual": "y"}],
            "assembly_diff_truncated": False,
        })
        self.assertNotIn("assembly_diff", row)
        self.assertNotIn("assembly_diff_truncated", row)
        self.assertEqual(row["function"], "func_a")

    def test_truncates_long_diagnostic(self) -> None:
        row = probe_stats.shape_attempt_row(
            {"function": "func_a", "diagnostic": "x" * 5000}, diagnostic_max_chars=2000
        )
        self.assertEqual(len(row["diagnostic"]), 2000)

    def test_short_diagnostic_untouched(self) -> None:
        row = probe_stats.shape_attempt_row({"function": "func_a", "diagnostic": "short"})
        self.assertEqual(row["diagnostic"], "short")

    def test_keeps_candidate(self) -> None:
        row = probe_stats.shape_attempt_row({"function": "func_a", "candidate": "void func_a(void) {}"})
        self.assertEqual(row["candidate"], "void func_a(void) {}")

    def test_default_diagnostic_max_chars_is_2000(self) -> None:
        self.assertEqual(probe_stats.DIAGNOSTIC_MAX_CHARS, 2000)


class RotateIfNeededTests(unittest.TestCase):
    def test_noop_under_limit(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "probe-stats.jsonl"
            path.write_text("small\n")
            self.assertIsNone(probe_stats.rotate_if_needed(path, max_bytes=1024))
            self.assertTrue(path.exists())

    def test_rotates_when_over_limit(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "probe-stats.jsonl"
            path.write_text("x" * 100)
            rotated = probe_stats.rotate_if_needed(path, max_bytes=10)
            self.assertEqual(rotated, path.with_name("probe-stats.1.jsonl"))
            self.assertFalse(path.exists())
            self.assertTrue(rotated.exists())

    def test_picks_next_free_index(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "probe-stats.jsonl"
            path.write_text("x" * 100)
            (path.with_name("probe-stats.1.jsonl")).write_text("already used")
            rotated = probe_stats.rotate_if_needed(path, max_bytes=10)
            self.assertEqual(rotated, path.with_name("probe-stats.2.jsonl"))

    def test_missing_file_is_a_noop(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "does-not-exist.jsonl"
            self.assertIsNone(probe_stats.rotate_if_needed(path))


class NewBatchRowTests(unittest.TestCase):
    def test_schema_fields(self) -> None:
        batch = probe_stats.new_batch_row("disasm/src/x.c", [])
        self.assertEqual(batch["schema_version"], 2)
        self.assertIn("timestamp", batch)
        self.assertTrue(batch["timestamp"].endswith("Z"))
        self.assertIn("batch_id", batch)
        self.assertEqual(len(batch["batch_id"]), 32)
        self.assertIn("worktree", batch)

    def test_attempt_family_takes_precedence_over_families_dict(self) -> None:
        batch = probe_stats.new_batch_row(
            "x.c",
            [{"function": "func_a", "family": "already_known"}],
            families={"func_a": "from_dict"},
        )
        self.assertEqual(batch["attempts"][0]["family"], "already_known")

    def test_family_from_families_dict(self) -> None:
        batch = probe_stats.new_batch_row(
            "x.c", [{"function": "func_a"}], families={"func_a": "bounded_lookup"}
        )
        self.assertEqual(batch["attempts"][0]["family"], "bounded_lookup")

    def test_family_from_family_lookup_fallback(self) -> None:
        batch = probe_stats.new_batch_row(
            "x.c", [{"function": "func_a"}], family_lookup=lambda f: "call_sequence"
        )
        self.assertEqual(batch["attempts"][0]["family"], "call_sequence")

    def test_family_lookup_exception_is_swallowed(self) -> None:
        def boom(function: str) -> str:
            raise RuntimeError("nope")

        batch = probe_stats.new_batch_row("x.c", [{"function": "func_a"}], family_lookup=boom)
        self.assertIsNone(batch["attempts"][0].get("family"))

    def test_shapes_every_attempt(self) -> None:
        batch = probe_stats.new_batch_row(
            "x.c", [{"function": "func_a", "assembly_diff": [1, 2, 3]}]
        )
        self.assertNotIn("assembly_diff", batch["attempts"][0])


class AppendBatchTests(unittest.TestCase):
    def test_disabled_returns_none_and_writes_nothing(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            target = Path(directory) / "should-not-exist.jsonl"
            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": ""}):
                result = probe_stats.append_batch({"a": 1}, path=None)
            self.assertIsNone(result)
            self.assertFalse(target.exists())

    def test_append_writes_one_json_line(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "stats.jsonl"
            written = probe_stats.append_batch({"source": "x.c"}, path=path)
            self.assertEqual(written, path)
            self.assertEqual(json.loads(path.read_text().strip())["source"], "x.c")

    def test_append_rotates_before_writing(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "stats.jsonl"
            path.write_text("x" * 100)
            probe_stats.append_batch({"source": "new.c"}, path=path, max_bytes=10)
            self.assertTrue(path.with_name("stats.1.jsonl").exists())
            self.assertEqual(json.loads(path.read_text().strip())["source"], "new.c")

    def test_append_creates_parent_directory(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "nested" / "stats.jsonl"
            probe_stats.append_batch({"source": "x.c"}, path=path)
            self.assertTrue(path.exists())


class MigrateLegacyTests(unittest.TestCase):
    def test_migrates_and_shapes_rows(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            legacy = root / "build" / "probe-stats.jsonl"
            legacy.parent.mkdir(parents=True)
            legacy.write_text(json.dumps({
                "source": "x.c",
                "attempts": [{
                    "function": "func_a",
                    "status": "accepted",
                    "candidate": "void func_a(void) {}",
                    "assembly_diff": [{"expected": "a", "actual": "b"}],
                }],
            }) + "\n")
            target = root / "probe-stats" / "probe-stats.jsonl"
            result = probe_stats.migrate_legacy(legacy_path=legacy, target_path=target)
            self.assertTrue(result["migrated"])
            self.assertEqual(result["batches"], 1)
            self.assertEqual(result["attempts"], 1)
            written = json.loads(target.read_text().strip())
            self.assertNotIn("assembly_diff", written["attempts"][0])
            self.assertEqual(written["attempts"][0]["candidate"], "void func_a(void) {}")

    def test_idempotent_second_call_is_a_noop(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            legacy = root / "build" / "probe-stats.jsonl"
            legacy.parent.mkdir(parents=True)
            legacy.write_text(json.dumps({"source": "x.c", "attempts": [{"function": "func_a", "status": "accepted", "candidate": "c"}]}) + "\n")
            target = root / "probe-stats" / "probe-stats.jsonl"
            first = probe_stats.migrate_legacy(legacy_path=legacy, target_path=target)
            self.assertTrue(first["migrated"])
            second = probe_stats.migrate_legacy(legacy_path=legacy, target_path=target)
            self.assertFalse(second["migrated"])
            # Only one copy of the batch made it into the target file.
            lines = [line for line in target.read_text().splitlines() if line.strip()]
            self.assertEqual(len(lines), 1)

    def test_no_legacy_file_still_writes_marker(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            legacy = root / "build" / "probe-stats.jsonl"
            target = root / "probe-stats" / "probe-stats.jsonl"
            result = probe_stats.migrate_legacy(legacy_path=legacy, target_path=target)
            self.assertFalse(result["migrated"])
            self.assertEqual(result["reason"], "no legacy file")
            marker = target.parent / probe_stats.MIGRATION_MARKER_NAME
            self.assertTrue(marker.exists())
            self.assertFalse(target.exists())

    def test_cli_migrate_runs(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            legacy = root / "build" / "probe-stats.jsonl"
            legacy.parent.mkdir(parents=True)
            legacy.write_text(json.dumps({"source": "x.c", "attempts": []}) + "\n")
            target = root / "probe-stats" / "probe-stats.jsonl"
            marker = target.parent / probe_stats.MIGRATION_MARKER_NAME
            with mock.patch.object(probe_stats, "LEGACY_STATS_PATH", legacy), mock.patch.object(
                probe_stats, "DEFAULT_STATS_PATH", target
            ):
                exit_code = probe_stats._cli(["migrate"])
            self.assertEqual(exit_code, 0)
            self.assertTrue(marker.exists())


class ProvenanceRemovedPragmaTests(unittest.TestCase):
    def test_finds_removed_pragma_under_disasm_src(self) -> None:
        diff = (
            "diff --git a/disasm/src/x.c b/disasm/src/x.c\n"
            "--- a/disasm/src/x.c\n"
            "+++ b/disasm/src/x.c\n"
            "@@ -1,1 +1,3 @@\n"
            '-#pragma GLOBAL_ASM("asm/us/nonmatchings/x/func_8000ABCD.s")\n'
            "+void func_8000ABCD(void) {\n"
            "+}\n"
        )
        self.assertEqual(provenance.removed_pragma_functions(diff), ["func_8000ABCD"])

    def test_ignores_files_outside_disasm_src(self) -> None:
        diff = (
            "diff --git a/tools/foo.py b/tools/foo.py\n"
            "--- a/tools/foo.py\n"
            "+++ b/tools/foo.py\n"
            "@@ -1,1 +0,0 @@\n"
            '-#pragma GLOBAL_ASM("asm/us/nonmatchings/x/func_8000ABCD.s")\n'
        )
        self.assertEqual(provenance.removed_pragma_functions(diff), [])

    def test_ignores_added_pragma_lines(self) -> None:
        diff = (
            "diff --git a/disasm/src/x.c b/disasm/src/x.c\n"
            "--- a/disasm/src/x.c\n"
            "+++ b/disasm/src/x.c\n"
            "@@ -0,0 +1,1 @@\n"
            '+#pragma GLOBAL_ASM("asm/us/nonmatchings/x/func_8000ABCD.s")\n'
        )
        self.assertEqual(provenance.removed_pragma_functions(diff), [])

    def test_deduplicates_and_preserves_order(self) -> None:
        diff = (
            "diff --git a/disasm/src/x.c b/disasm/src/x.c\n"
            "--- a/disasm/src/x.c\n"
            "+++ b/disasm/src/x.c\n"
            '-#pragma GLOBAL_ASM("asm/us/nonmatchings/x/func_b.s")\n'
            "diff --git a/disasm/src/y.c b/disasm/src/y.c\n"
            "--- a/disasm/src/y.c\n"
            "+++ b/disasm/src/y.c\n"
            '-#pragma GLOBAL_ASM("asm/us/nonmatchings/y/func_a.s")\n'
            '-#pragma GLOBAL_ASM("asm/us/nonmatchings/y/func_b.s")\n'
        )
        self.assertEqual(provenance.removed_pragma_functions(diff), ["func_b", "func_a"])


class ProvenanceAcceptedFunctionsTests(unittest.TestCase):
    def test_scans_and_collects_accepted_functions(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "stats.jsonl"
            path.write_text(
                json.dumps({"attempts": [
                    {"function": "func_a", "status": "accepted"},
                    {"function": "func_b", "status": "probe_rejected"},
                ]}) + "\n"
                + json.dumps({"attempts": [{"function": "func_c", "status": "accepted"}]}) + "\n"
                + "not json, and no accepted mention either\n"
            )
            accepted = provenance.accepted_functions([path])
            self.assertEqual(accepted, {"func_a", "func_c"})

    def test_line_without_accepted_substring_is_never_parsed(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "stats.jsonl"
            path.write_text('{"attempts": [{"function": "func_a", "status": "probe_rejected"}]}\n')
            self.assertEqual(provenance.accepted_functions([path]), set())


class ProvenanceStagedIntegrationTests(unittest.TestCase):
    """End-to-end check against a real throwaway git repo."""

    def _init_repo(self, root: Path) -> None:
        subprocess.run(["git", "init", "-q"], cwd=root, check=True)
        subprocess.run(["git", "config", "user.email", "test@example.com"], cwd=root, check=True)
        subprocess.run(["git", "config", "user.name", "Test"], cwd=root, check=True)

    def test_missing_accepted_attempt_blocks(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self._init_repo(root)
            src_dir = root / "disasm" / "src"
            src_dir.mkdir(parents=True)
            source = src_dir / "x.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/x/func_8000ABCD.s")\n')
            subprocess.run(["git", "add", "disasm/src/x.c"], cwd=root, check=True)
            subprocess.run(["git", "commit", "-q", "-m", "add pragma"], cwd=root, check=True)

            source.write_text("void func_8000ABCD(void) {\n}\n")
            subprocess.run(["git", "add", "disasm/src/x.c"], cwd=root, check=True)

            with mock.patch.object(probe_stats, "DEFAULT_STATS_PATH", root / "probe-stats" / "probe-stats.jsonl"), \
                 mock.patch.object(probe_stats, "LEGACY_STATS_PATH", root / "build" / "probe-stats.jsonl"):
                missing = provenance.check_staged(root)
            self.assertEqual(missing, ["func_8000ABCD"])

    def test_accepted_attempt_on_file_unblocks(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self._init_repo(root)
            src_dir = root / "disasm" / "src"
            src_dir.mkdir(parents=True)
            source = src_dir / "x.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/x/func_8000ABCD.s")\n')
            subprocess.run(["git", "add", "disasm/src/x.c"], cwd=root, check=True)
            subprocess.run(["git", "commit", "-q", "-m", "add pragma"], cwd=root, check=True)

            source.write_text("void func_8000ABCD(void) {\n}\n")
            subprocess.run(["git", "add", "disasm/src/x.c"], cwd=root, check=True)

            stats_path = root / "probe-stats" / "probe-stats.jsonl"
            stats_path.parent.mkdir(parents=True)
            stats_path.write_text(json.dumps({"attempts": [
                {"function": "func_8000ABCD", "status": "accepted", "candidate": "void func_8000ABCD(void) {}"},
            ]}) + "\n")

            with mock.patch.object(probe_stats, "DEFAULT_STATS_PATH", stats_path), mock.patch.object(
                probe_stats, "LEGACY_STATS_PATH", root / "build" / "probe-stats.jsonl"
            ):
                missing = provenance.check_staged(root)
            self.assertEqual(missing, [])

    def test_no_pragma_removed_is_a_noop(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self._init_repo(root)
            src_dir = root / "disasm" / "src"
            src_dir.mkdir(parents=True)
            source = src_dir / "x.c"
            source.write_text("void func_unrelated(void) {}\n")
            subprocess.run(["git", "add", "disasm/src/x.c"], cwd=root, check=True)
            subprocess.run(["git", "commit", "-q", "-m", "initial"], cwd=root, check=True)

            source.write_text("void func_unrelated(void) { return; }\n")
            subprocess.run(["git", "add", "disasm/src/x.c"], cwd=root, check=True)

            missing = provenance.check_staged(root)
            self.assertEqual(missing, [])

    def test_main_respects_skip_env_var(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self._init_repo(root)
            with mock.patch.dict(os.environ, {"DECOMP_PROVENANCE_SKIP": "1"}):
                exit_code = provenance.main(["--staged", "--repo-root", str(root)])
            self.assertEqual(exit_code, 0)

    def test_main_exits_nonzero_and_lists_missing_functions(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self._init_repo(root)
            src_dir = root / "disasm" / "src"
            src_dir.mkdir(parents=True)
            source = src_dir / "x.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/x/func_8000ABCD.s")\n')
            subprocess.run(["git", "add", "disasm/src/x.c"], cwd=root, check=True)
            subprocess.run(["git", "commit", "-q", "-m", "add pragma"], cwd=root, check=True)
            source.write_text("void func_8000ABCD(void) {\n}\n")
            subprocess.run(["git", "add", "disasm/src/x.c"], cwd=root, check=True)

            with mock.patch.object(probe_stats, "DEFAULT_STATS_PATH", root / "probe-stats" / "probe-stats.jsonl"), \
                 mock.patch.object(probe_stats, "LEGACY_STATS_PATH", root / "build" / "probe-stats.jsonl"), \
                 mock.patch.dict(os.environ, {}, clear=False):
                os.environ.pop("DECOMP_PROVENANCE_SKIP", None)
                exit_code = provenance.main(["--staged", "--repo-root", str(root)])
            self.assertEqual(exit_code, 1)


if __name__ == "__main__":
    unittest.main()
