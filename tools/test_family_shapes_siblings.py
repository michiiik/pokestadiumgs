#!/usr/bin/env python3
"""Tests for the ``siblings``/``unlock`` family-unlock hunting modes.

These exercise ``tools/analyze_family_shapes.py``'s opcode-shape clustering
(see its module docstring section on "siblings"/"unlock" for the rationale:
a fleet wave on 2026-08-28 found by accident that six of twelve accepts in
``4AC10.c`` shared one spelling because they were siblings -- this tool is
meant to surface that on purpose). Fixtures are small synthetic ``.s`` files
in a tempdir; nothing here touches the real ``disasm/`` tree.
"""

from __future__ import annotations

import io
import json
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path
from unittest import mock

import analyze_family_shapes as shapes
import pragma_targets

# A three-instruction body with a saved-register prologue/epilogue, used as
# the common tail for every synthetic sibling below.
_TAIL = """
            /* 000020 80000020 */ jr $ra
            /* 000024 80000024 */ nop
"""


def _caller_asm(label: str, target: str, immediate: str) -> str:
    """A short wrapper calling ``target`` once, differing only by an immediate.

    Two owners built from this template are the same shape once immediates
    are abstracted; a real sibling family (see ``4AC10.c``'s
    ``func_8004A174``/``A2E0``/``A44C``) differs the same way -- same
    instructions, different literal operands.
    """
    return f"""
        glabel {label}
            /* 000000 80000000 */ addiu $sp, $sp, -0x18
            /* 000004 80000004 */ or $a1, $a0, $zero
            /* 000008 80000008 */ addiu $a0, $zero, {immediate}
            /* 00000C 8000000C */ jal {target}
            /* 000010 80000010 */ nop
{_TAIL}
    """


def _unrelated_asm(label: str) -> str:
    """A shape with no calls at all -- must not cluster with the callers."""
    return f"""
        glabel {label}
            /* 000000 80000000 */ lbu $v0, 0x0($a0)
            /* 000004 80000004 */ andi $v0, $v0, 0xff
            /* 000008 80000008 */ jr $ra
            /* 00000C 8000000C */ nop
    """


def _gbi_macro_asm(label: str) -> str:
    """The display-list append shape: stores through D_800D0510 with a
    G_ENDDL-family constant (0xDE000000), per AGENTS.md's "Display-list
    append" row.
    """
    return f"""
        glabel {label}
            /* 000000 80000000 */ lui $v1, %hi(D_800D0510)
            /* 000004 80000004 */ addiu $v1, $v1, %lo(D_800D0510)
            /* 000008 80000008 */ lw $v0, 0x0($v1)
            /* 00000C 8000000C */ lui $t7, (0xDE000000 >> 16)
            /* 000010 80000010 */ sw $t7, 0x0($v0)
            /* 000014 80000014 */ jr $ra
            /* 000018 80000018 */ addiu $v0, $v0, 0x8
    """


def _write_owner(source_root: Path, asm_root: Path, source_name: str, subdir: str, function: str, asm_text: str) -> None:
    """Append a pragma for ``function`` to ``source_name`` and write its ``.s``."""
    source_path = source_root / source_name
    asm_dir = asm_root / subdir
    asm_dir.mkdir(parents=True, exist_ok=True)
    (asm_dir / f"{function}.s").write_text(asm_text, encoding="utf-8")
    pragma = f'#pragma GLOBAL_ASM("asm/us/nonmatchings/{subdir}/{function}.s")\n'
    if source_path.exists():
        with source_path.open("a", encoding="utf-8") as handle:
            handle.write(pragma)
    else:
        source_path.write_text(pragma, encoding="utf-8")


class _NoStatsFixture:
    """Point the solved-shape lookup at a stats file that never exists.

    ``analyze_family_shapes.build_solved_index`` reuses
    ``pragma_targets.solved_shapes``, whose default target is
    ``pragma_targets.STATS_PATH`` (a module-level constant, not re-derived
    from ``PRAGMA_PROBE_STATS`` at call time). Patching it directly is the
    only way to guarantee a test never reads the real checkout's probe-stats
    history, regardless of whether one happens to exist on this machine.
    """

    def __enter__(self):
        self._directory = tempfile.TemporaryDirectory()
        missing = Path(self._directory.name) / "does-not-exist.jsonl"
        self._patches = [
            mock.patch.object(pragma_targets, "STATS_PATH", missing),
            mock.patch.object(pragma_targets.probe_stats, "DEFAULT_STATS_PATH", missing),
        ]
        for patch in self._patches:
            patch.start()
        return missing

    def __exit__(self, *exc_info):
        for patch in self._patches:
            patch.stop()
        self._directory.cleanup()


class ShapeSignatureTests(unittest.TestCase):
    def test_registers_and_immediates_are_abstracted(self) -> None:
        _, a, _ = shapes.scanner.parse_instructions(_caller_asm("func_a", "func_target", "8"))
        _, b, _ = shapes.scanner.parse_instructions(_caller_asm("func_b", "func_target", "0x10"))
        self.assertEqual(shapes.shape_signature(a), shapes.shape_signature(b))

    def test_jal_target_name_is_kept_as_part_of_the_token(self) -> None:
        _, same_target, _ = shapes.scanner.parse_instructions(_caller_asm("func_a", "func_target", "8"))
        _, other_target, _ = shapes.scanner.parse_instructions(_caller_asm("func_b", "func_other", "8"))
        sig_a = shapes.shape_signature(same_target)
        sig_b = shapes.shape_signature(other_target)
        self.assertIn("jal:func_target", sig_a)
        self.assertIn("jal:func_other", sig_b)
        self.assertNotEqual(sig_a, sig_b)

    def test_consecutive_sw_or_lw_runs_collapse_to_one_token(self) -> None:
        asm = """
        glabel func_stores
            /* 000000 80000000 */ sw $a0, 0x0($v0)
            /* 000004 80000004 */ sw $a1, 0x4($v0)
            /* 000008 80000008 */ sw $a2, 0x8($v0)
            /* 00000C 8000000C */ jr $ra
            /* 000010 80000010 */ nop
        """
        _, instructions, _ = shapes.scanner.parse_instructions(asm)
        tokens = shapes.shape_signature(instructions)
        self.assertEqual(tokens.count("sw"), 1)


class EditDistanceTests(unittest.TestCase):
    def test_identical_sequences_have_zero_distance(self) -> None:
        self.assertEqual(shapes.edit_distance(["a", "b", "c"], ["a", "b", "c"]), 0)
        self.assertEqual(shapes.normalized_distance(["a", "b", "c"], ["a", "b", "c"]), 0.0)

    def test_distance_counts_one_substitution(self) -> None:
        self.assertEqual(shapes.edit_distance(["a", "b", "c"], ["a", "x", "c"]), 1)

    def test_normalized_distance_divides_by_longer_length(self) -> None:
        distance = shapes.normalized_distance(["a"] * 8, ["a"] * 8 + ["b"])
        self.assertAlmostEqual(distance, 1 / 9)

    def test_empty_sequences_are_zero_distance(self) -> None:
        self.assertEqual(shapes.normalized_distance([], []), 0.0)


class GbiMacroDetectionTests(unittest.TestCase):
    def test_pointer_symbol_is_detected(self) -> None:
        self.assertTrue(shapes.is_gbi_macro_asm("sw $t7, 0x0($v0) ; D_800D0510"))

    def test_command_constant_prefixes_are_detected(self) -> None:
        for constant in ("0xDE000000", "0xE7000000", "0xFD100000", "0xF5100400", "0xF3000000"):
            with self.subTest(constant=constant):
                self.assertTrue(shapes.is_gbi_macro_asm(f"lui $t7, ({constant} >> 16)"))

    def test_unrelated_text_is_not_tagged(self) -> None:
        self.assertFalse(shapes.is_gbi_macro_asm("lbu $v0, 0x0($a0)\nandi $v0, $v0, 0xff"))


class ClusterSiblingsTests(unittest.TestCase):
    def test_near_identical_callers_cluster_with_shared_jal_target(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            owners = [
                _write_and_build(root, "func_a", _caller_asm("func_a", "func_helper", "8")),
                _write_and_build(root, "func_b", _caller_asm("func_b", "func_helper", "0x10")),
                _write_and_build(root, "func_c", _caller_asm("func_c", "func_helper", "0x18")),
                _write_and_build(root, "func_unrelated", _unrelated_asm("func_unrelated")),
            ]
            groups = shapes.cluster_siblings(owners)
        sizes = sorted(group.size for group in groups)
        self.assertEqual(sizes, [1, 3])
        sibling_group = next(group for group in groups if group.size == 3)
        self.assertEqual(
            {member.function for member in sibling_group.members},
            {"func_a", "func_b", "func_c"},
        )
        self.assertEqual(sibling_group.shared_jal_targets, ["func_helper"])
        self.assertFalse(sibling_group.gbi_macro)

    def test_gbi_macro_tag_is_set_when_any_member_matches(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            owners = [_write_and_build(root, "func_gbi", _gbi_macro_asm("func_gbi"))]
            groups = shapes.cluster_siblings(owners)
        self.assertEqual(len(groups), 1)
        self.assertTrue(groups[0].gbi_macro)
        self.assertEqual(
            shapes.group_to_dict(groups[0])["suggested_spelling"], shapes.GBI_MACRO_HINT
        )


def _write_and_build(root: Path, function: str, asm_text: str) -> shapes.SiblingOwner:
    asm_path = root / f"{function}.s"
    asm_path.write_text(asm_text, encoding="utf-8")
    return shapes.build_sibling_owner(function, root / "synthetic.c", asm_path)


class _ResetsSolvedCaches(unittest.TestCase):
    """``build_solved_index``/``build_function_locations`` cache unconditionally
    for the process lifetime (by design: one CLI run always asks with the
    same roots). Tests must reset both between cases so one test's synthetic
    probe-stats/source tree cannot leak into the next.
    """

    def setUp(self) -> None:
        shapes._SOLVED_SIGNATURE_CACHE = None
        shapes._FUNCTION_LOCATION_CACHE = None

    def tearDown(self) -> None:
        shapes._SOLVED_SIGNATURE_CACHE = None
        shapes._FUNCTION_LOCATION_CACHE = None


class FileSiblingsReportTests(_ResetsSolvedCaches):
    def test_family_surfaces_and_gbi_macro_singleton_survives_min_group(self) -> None:
        with tempfile.TemporaryDirectory() as directory, _NoStatsFixture():
            root = Path(directory)
            source_root = root / "src"
            asm_root = root / "asm"
            source_root.mkdir()
            source_name = "4AC10ish.c"

            # Three siblings calling one still-unsolved helper (the shape the
            # 2026-08-28 wave found by accident in 4AC10.c: func_8004A174/
            # A2E0/A44C all call func_8004A010 the same way).
            _write_owner(source_root, asm_root, source_name, "4AC10ish", "func_caller_a",
                         _caller_asm("func_caller_a", "func_helper", "8"))
            _write_owner(source_root, asm_root, source_name, "4AC10ish", "func_caller_b",
                         _caller_asm("func_caller_b", "func_helper", "0x10"))
            _write_owner(source_root, asm_root, source_name, "4AC10ish", "func_caller_c",
                         _caller_asm("func_caller_c", "func_helper", "0x18"))
            # The helper itself: a lone gbi-macro owner, same shape family as
            # 4AC10.c's real func_8004A010.
            _write_owner(source_root, asm_root, source_name, "4AC10ish", "func_helper",
                         _gbi_macro_asm("func_helper"))
            # An unrelated owner that must not join either group.
            _write_owner(source_root, asm_root, source_name, "4AC10ish", "func_lonely",
                         _unrelated_asm("func_lonely"))

            report = shapes.build_file_siblings_report(
                source_root / source_name, asm_root, None, min_group=2, source_root=source_root
            )

        self.assertEqual(report["owners_remaining"], 5)
        # func_lonely's group (size 1, not gbi-macro) is filtered by
        # --min-group; the 3-caller family and the gbi-macro singleton
        # survive.
        self.assertEqual(report["groups_shown"], 2)
        sizes = sorted(group["size"] for group in report["groups"])
        self.assertEqual(sizes, [1, 3])

        family = next(group for group in report["groups"] if group["size"] == 3)
        self.assertEqual(
            set(family["members"]), {"func_caller_a", "func_caller_b", "func_caller_c"}
        )
        self.assertEqual(family["shared_jal_targets"], ["func_helper"])

        helper_group = next(group for group in report["groups"] if group["size"] == 1)
        self.assertEqual(helper_group["members"], ["func_helper"])
        self.assertTrue(helper_group["gbi_macro"])
        self.assertIsNone(helper_group["closest_solved"])  # no probe-stats history in this fixture

    def test_min_group_hides_small_non_gbi_groups_by_default(self) -> None:
        with tempfile.TemporaryDirectory() as directory, _NoStatsFixture():
            root = Path(directory)
            source_root = root / "src"
            asm_root = root / "asm"
            source_root.mkdir()
            _write_owner(source_root, asm_root, "solo.c", "solo", "func_solo",
                         _unrelated_asm("func_solo"))
            report = shapes.build_file_siblings_report(
                source_root / "solo.c", asm_root, None, min_group=2, source_root=source_root
            )
        self.assertEqual(report["groups_found"], 1)
        self.assertEqual(report["groups_shown"], 0)


class ClosestSolvedTests(_ResetsSolvedCaches):
    def test_closest_solved_finds_the_nearest_accepted_shape(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source_root = root / "src"
            asm_root = root / "asm"
            source_root.mkdir()

            # The remaining sibling family (unsolved).
            _write_owner(source_root, asm_root, "family.c", "family", "func_x",
                         _caller_asm("func_x", "func_helper", "8"))
            _write_owner(source_root, asm_root, "family.c", "family", "func_y",
                         _caller_asm("func_y", "func_helper", "0x10"))

            # An already-accepted winner elsewhere with the identical shape:
            # its .s stays on disk after decompilation (see AGENTS.md rule 8),
            # and its C definition lives in a separate, already-solved file.
            solved_dir = asm_root / "family"
            solved_dir.mkdir(parents=True, exist_ok=True)
            (solved_dir / "func_8000AB10.s").write_text(
                _caller_asm("func_8000AB10", "func_helper", "0x20"), encoding="utf-8"
            )
            solved_source = source_root / "solved.c"
            solved_source.write_text(
                "void func_8000AB10(s32 arg0) { func_helper(arg0, 0x20); }\n",
                encoding="utf-8",
            )

            stats_path = root / "probe-stats.jsonl"
            stats_path.write_text(
                json.dumps(
                    {
                        "attempts": [
                            {
                                "function": "func_8000AB10",
                                "status": "accepted",
                                "candidate": "void func_8000AB10(s32 arg0) { func_helper(arg0, 0x20); }",
                                "label": "wrapper",
                            }
                        ]
                    }
                )
                + "\n",
                encoding="utf-8",
            )

            # ``display_relpath`` (pre-existing helper) reports paths relative
            # to ``REPO_ROOT``; point it at this tempdir so the expected
            # "source" value is a short, readable relative path.
            with mock.patch.object(pragma_targets, "STATS_PATH", stats_path), mock.patch.object(
                pragma_targets.probe_stats, "DEFAULT_STATS_PATH", stats_path
            ), mock.patch.object(shapes, "REPO_ROOT", root.resolve()):
                report = shapes.build_file_siblings_report(
                    source_root / "family.c", asm_root, None, min_group=2, source_root=source_root
                )

        self.assertEqual(report["groups_shown"], 1)
        closest = report["groups"][0]["closest_solved"]
        self.assertIsNotNone(closest)
        self.assertEqual(closest["function"], "func_8000AB10")
        self.assertEqual(closest["source"], "src/solved.c")
        self.assertEqual(closest["distance"], 0.0)


class AllSiblingsReportTests(_ResetsSolvedCaches):
    def test_top_n_sorted_by_size_across_files(self) -> None:
        with tempfile.TemporaryDirectory() as directory, _NoStatsFixture():
            root = Path(directory)
            source_root = root / "src"
            asm_root = root / "asm"
            source_root.mkdir()

            # File A: a family of 3.
            for index, immediate in enumerate(("8", "0x10", "0x18")):
                name = f"func_a{index}"
                _write_owner(source_root, asm_root, "a.c", "a", name, _caller_asm(name, "func_helper_a", immediate))
            # File B: a family of 2 (still >= default min-group).
            for index, immediate in enumerate(("4", "0xc")):
                name = f"func_b{index}"
                _write_owner(source_root, asm_root, "b.c", "b", name, _caller_asm(name, "func_helper_b", immediate))
            # File C: a lone non-gbi owner, filtered out by min-group.
            _write_owner(source_root, asm_root, "c.c", "c", "func_c0", _unrelated_asm("func_c0"))

            report = shapes.build_all_siblings_report(source_root, asm_root, None, min_group=2, top=30)

        self.assertEqual(report["files_scanned"], 3)
        self.assertEqual(report["owners_remaining_total"], 6)
        self.assertEqual(len(report["groups"]), 2)
        self.assertEqual(report["groups"][0]["size"], 3)
        self.assertEqual(report["groups"][0]["rank"], 1)
        self.assertEqual(report["groups"][1]["size"], 2)

    def test_top_limits_how_many_groups_are_returned(self) -> None:
        with tempfile.TemporaryDirectory() as directory, _NoStatsFixture():
            root = Path(directory)
            source_root = root / "src"
            asm_root = root / "asm"
            source_root.mkdir()
            for file_index in range(3):
                for owner_index in range(2):
                    name = f"func_f{file_index}_{owner_index}"
                    _write_owner(
                        source_root,
                        asm_root,
                        f"f{file_index}.c",
                        f"f{file_index}",
                        name,
                        _caller_asm(name, f"func_helper_{file_index}", str(owner_index)),
                    )
            report = shapes.build_all_siblings_report(source_root, asm_root, None, min_group=2, top=1)
        self.assertEqual(len(report["groups"]), 1)
        self.assertEqual(report["groups_found_total"], 3)


class UnlockCallersTests(unittest.TestCase):
    def test_lists_only_remaining_owners_that_call_the_target(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source_root = root / "src"
            asm_root = root / "asm"
            source_root.mkdir()
            _write_owner(source_root, asm_root, "callers.c", "callers", "func_caller_1",
                         _caller_asm("func_caller_1", "func_target", "8"))
            # A double-caller (calls the target twice).
            double_asm = """
            glabel func_caller_2
                /* 000000 80000000 */ jal func_target
                /* 000004 80000004 */ nop
                /* 000008 80000008 */ jal func_target
                /* 00000C 8000000C */ nop
                /* 000010 80000010 */ jr $ra
                /* 000014 80000014 */ nop
            """
            _write_owner(source_root, asm_root, "callers.c", "callers", "func_caller_2", double_asm)
            _write_owner(source_root, asm_root, "callers.c", "callers", "func_bystander",
                         _unrelated_asm("func_bystander"))

            buffer = io.StringIO()
            with redirect_stdout(buffer):
                argv = [
                    "unlock",
                    "--function",
                    "func_target",
                    "--source-root",
                    str(source_root),
                    "--asm-root",
                    str(asm_root),
                    "--no-fallback",
                    "--json",
                ]
                with mock.patch.object(sys, "argv", ["analyze_family_shapes.py"] + argv):
                    exit_code = shapes.main()

        self.assertEqual(exit_code, 0)
        report = json.loads(buffer.getvalue())
        self.assertEqual(report["target"], "func_target")
        self.assertEqual(report["caller_count"], 2)
        by_function = {row["function"]: row for row in report["callers"]}
        self.assertEqual(by_function["func_caller_2"]["call_count"], 2)
        self.assertEqual(by_function["func_caller_1"]["call_count"], 1)
        self.assertNotIn("func_bystander", by_function)


class DispatchTests(unittest.TestCase):
    def test_main_still_routes_plain_flags_to_the_original_shape_report(self) -> None:
        """``siblings``/``unlock`` must not break the pre-existing ``--family`` CLI."""
        with tempfile.TemporaryDirectory() as directory:
            # Resolved up front (macOS: /var is a symlink to /private/var):
            # ``extract_features`` (pre-existing, unrelated to siblings/unlock)
            # compares an owner's un-resolved source path against a resolved
            # ``REPO_ROOT``, so every path built from ``root`` must already
            # agree with the resolved form patched in below.
            root = Path(directory).resolve()
            source_root = root / "src"
            asm_root = root / "asm"
            source_root.mkdir()
            _write_owner(source_root, asm_root, "plain.c", "plain", "func_plain",
                         _unrelated_asm("func_plain"))

            buffer = io.StringIO()
            argv = [
                "--source-root",
                str(source_root),
                "--asm-root",
                str(asm_root),
                "--no-fallback",
                "--family",
                "unclassified",
            ]
            with redirect_stdout(buffer), mock.patch.object(
                sys, "argv", ["analyze_family_shapes.py"] + argv
            ), mock.patch.object(shapes, "REPO_ROOT", root):
                exit_code = shapes.main()

        self.assertEqual(exit_code, 0)
        report = json.loads(buffer.getvalue())
        self.assertIn("shape_summary", report)


if __name__ == "__main__":
    unittest.main()
