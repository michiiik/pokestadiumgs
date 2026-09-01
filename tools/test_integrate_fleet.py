"""Tests for the unattended fleet integrator.

The point of this tool is that no human reads the diff, so the refusals it
makes are the only thing standing between an agent and a weakened oracle.
These tests pin exactly those refusals.
"""

import unittest
from unittest import mock

import integrate_fleet as fleet


class TrustAnchorTests(unittest.TestCase):
    def test_checksum_is_an_anchor(self) -> None:
        self.assertTrue(fleet.touched_anchors(["disasm/baseroms/us/checksum.md5"]))

    def test_makefile_is_an_anchor(self) -> None:
        self.assertTrue(fleet.touched_anchors(["disasm/Makefile"]))

    def test_hooks_are_anchors(self) -> None:
        self.assertTrue(fleet.touched_anchors([".githooks/pre-commit.d/15-provenance.sh"]))

    def test_provenance_script_is_an_anchor(self) -> None:
        self.assertTrue(fleet.touched_anchors(["tools/check_decomp_provenance.py"]))

    def test_the_integrator_cannot_edit_itself(self) -> None:
        self.assertTrue(fleet.touched_anchors(["tools/integrate_fleet.py"]))

    def test_ordinary_decomp_work_is_not_an_anchor(self) -> None:
        self.assertEqual(
            fleet.touched_anchors([
                "disasm/src/fragments/61/fragment61_code.c",
                "docs/regions/57C0.md",
                "COVERAGE.md",
                "tools/try_pragma_compare.py",
            ]),
            [],
        )

    def test_rom_yaml_is_allowed_because_the_hash_still_proves_it(self) -> None:
        self.assertEqual(fleet.touched_anchors(["disasm/yamls/us/rom.yaml"]), [])


class BypassDetectionTests(unittest.TestCase):
    def _diff(self, *lines: str) -> str:
        return "\n".join(["diff --git a/x b/x", "+++ b/x", *lines])

    def _hits(self, diff: str) -> list[str]:
        with mock.patch.object(fleet, "git", return_value=diff):
            return fleet.introduced_bypasses("master", "b")

    def test_detects_provenance_skip(self) -> None:
        self.assertTrue(self._hits(self._diff("+DECOMP_PROVENANCE_SKIP=1 git commit")))

    def test_detects_disabled_cc_check(self) -> None:
        self.assertTrue(self._hits(self._diff("+PRAGMA_GATE_CC_CHECK=0 make")))

    def test_detects_disabled_probe_stats(self) -> None:
        self.assertTrue(self._hits(self._diff("+PRAGMA_PROBE_STATS=")))

    def test_detects_skipped_tool_tests(self) -> None:
        self.assertTrue(self._hits(self._diff("+SKIP_TOOL_TESTS=1 git commit")))

    def test_removed_lines_do_not_count(self) -> None:
        diff = "\n".join([
            "diff --git a/x b/x", "--- a/x", "+++ b/x",
            "-DECOMP_PROVENANCE_SKIP=1 git commit",
        ])
        self.assertEqual(self._hits(diff), [])

    def test_clean_diff_passes(self) -> None:
        self.assertEqual(self._hits(self._diff("+    return 0;")), [])

    def test_enabling_the_cc_check_is_not_a_bypass(self) -> None:
        self.assertEqual(self._hits(self._diff("+PRAGMA_GATE_CC_CHECK=1 make")), [])


class ScreenTests(unittest.TestCase):
    def test_empty_branch_is_refused(self) -> None:
        with mock.patch.object(fleet, "changed_paths", return_value=[]), \
             mock.patch.object(fleet, "introduced_bypasses", return_value=[]):
            reasons = fleet.screen("master", "b")
        self.assertEqual(len(reasons), 1)
        self.assertIn("no changes", reasons[0])

    def test_clean_decomp_branch_passes(self) -> None:
        with mock.patch.object(
            fleet, "changed_paths",
            return_value=["disasm/src/1A360.c", "COVERAGE.md"],
        ), mock.patch.object(fleet, "introduced_bypasses", return_value=[]):
            self.assertEqual(fleet.screen("master", "b"), [])

    def test_anchor_and_bypass_are_both_reported(self) -> None:
        with mock.patch.object(
            fleet, "changed_paths", return_value=["disasm/Makefile"],
        ), mock.patch.object(
            fleet, "introduced_bypasses", return_value=["SKIP_TOOL_TESTS -> +x"],
        ):
            reasons = fleet.screen("master", "b")
        self.assertEqual(len(reasons), 2)
        self.assertTrue(any("trust anchor" in r for r in reasons))
        self.assertTrue(any("gate bypass" in r for r in reasons))


class ProveTests(unittest.TestCase):
    def test_rom_gate_must_report_ok(self) -> None:
        """A zero exit without the md5 'OK' line is still a failure."""
        with mock.patch.object(fleet, "run", return_value=(True, "Building ROM...")):
            failures = fleet.prove(60)
        self.assertTrue(any("ROM gate failed" in f for f in failures))

    def test_all_green_proves(self) -> None:
        with mock.patch.object(
            fleet, "run", return_value=(True, "build/pokestadiumgs-us.z64: OK"),
        ):
            self.assertEqual(fleet.prove(60), [])


if __name__ == "__main__":
    unittest.main()
