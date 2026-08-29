#!/usr/bin/env python3
"""Focused tests for the opt-in per-source candidate-yield report."""

from __future__ import annotations

import contextlib
import io
import json
import sys
import tempfile
import unittest
from pathlib import Path

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import report_candidate_yield as report  # noqa: E402


def _write_stats(path: Path) -> None:
    batches = [
        {
            "schema_version": 2,
            "source": "/Users/michaegg/projects/pokemonStadiumGSRecomp/disasm/src/fragments/1/fragment1_code.c",
            "attempts": [
                {
                    "function": "func_accept",
                    "label": "manual:accepted",
                    "status": "accepted",
                    "link_verified": True,
                },
                {
                    "function": "func_probe",
                    "label": "manual:probe",
                    "status": "probe_match",
                    "link_verified": True,
                    "mismatch_kind": "immediate_drift",
                },
                {
                    "function": "func_compile",
                    "label": "m2c:compile",
                    "status": "compile_failed",
                    "mismatch_kind": "register_allocation_only",
                },
                {
                    "function": "func_unavailable",
                    "label": "manual:unavailable",
                    "status": "probe_unavailable",
                    "probe_reason": "probe_error",
                },
            ],
        },
        {
            "schema_version": 2,
            "source": "/tmp/other-project/disasm/other_source.c",
            "attempts": [
                {
                    "function": "func_other",
                    "label": "manual:other",
                    "status": "probe_match",
                    "link_verified": True,
                },
            ],
        },
        {
            "schema_version": 2,
            "source": "disasm/src/fragments/2/fragment2_code.c",
            "attempts": [
                {
                    "function": "func_runner",
                    "label": "manual:runner",
                    "status": "runner_error",
                    "mismatch_kind": "runner_failure",
                },
                {
                    "function": "func_internal",
                    "label": "manual:internal",
                    "status": "internal_error",
                    "mismatch_kind": "internal_failure",
                },
                {
                    "function": "func_unavailable",
                    "label": "manual:unavailable",
                    "status": "unavailable",
                    "mismatch_kind": "missing_function_bytes",
                },
                {
                    "function": "func_compile",
                    "label": "manual:compile",
                    "status": "combined_compile_failed",
                    "mismatch_kind": "section_layout_drift",
                },
            ],
        },
        {
            "schema_version": 2,
            "source": "disasm/src/fragments/1/fragment1_code.c",
            "attempts": [
                {
                    "function": "func_accept",
                    "label": "manual:accepted-again",
                    "status": "accepted",
                    "link_verified": True,
                },
            ],
        },
    ]
    with path.open("w", encoding="utf-8") as handle:
        for batch in batches:
            handle.write(json.dumps(batch) + "\n")


class SourceReportTests(unittest.TestCase):
    def setUp(self) -> None:
        self.tempdir = tempfile.TemporaryDirectory()
        self.addCleanup(self.tempdir.cleanup)
        self.stats = Path(self.tempdir.name) / "probe-stats.jsonl"
        _write_stats(self.stats)

    def test_source_tallies_include_accept_and_zero_accept_sources(self) -> None:
        rows = report.collect_by_source((self.stats,))

        accepted = rows["disasm/src/fragments/1/fragment1_code.c"]
        self.assertEqual(accepted.batches, 2)
        self.assertEqual(accepted.attempts, 5)
        self.assertEqual(accepted.accepted_attempts, 2)
        self.assertEqual(accepted.accepted_owners, 1)
        self.assertEqual(accepted.probe_matches, 1)
        self.assertEqual(accepted.compile_failed, 1)
        self.assertEqual(accepted.runner_errors, 1)
        self.assertEqual(accepted.internal_errors, 0)
        self.assertEqual(accepted.unavailable, 1)
        self.assertEqual(accepted.link_verified_accepted, 2)
        self.assertEqual(accepted.link_verified_probe_matches, 1)
        self.assertEqual(
            accepted.mismatch_kinds,
            {"immediate_drift": 1, "register_allocation_only": 1},
        )

        unrelated = rows["/tmp/other-project/disasm/other_source.c"]
        self.assertEqual(unrelated.batches, 1)
        self.assertEqual(unrelated.attempts, 1)
        self.assertEqual(unrelated.probe_matches, 1)

        zero_accept = rows["disasm/src/fragments/2/fragment2_code.c"]
        self.assertEqual(zero_accept.batches, 1)
        self.assertEqual(zero_accept.attempts, 4)
        self.assertEqual(zero_accept.accepted_attempts, 0)
        self.assertEqual(zero_accept.accepted_owners, 0)
        self.assertEqual(zero_accept.probe_matches, 0)
        self.assertEqual(zero_accept.compile_failed, 1)
        self.assertEqual(zero_accept.runner_errors, 1)
        self.assertEqual(zero_accept.internal_errors, 1)
        self.assertEqual(zero_accept.unavailable, 1)
        self.assertEqual(zero_accept.link_verified_accepted, 0)
        self.assertEqual(zero_accept.link_verified_probe_matches, 0)
        self.assertEqual(
            zero_accept.mismatch_kinds,
            {
                "internal_failure": 1,
                "missing_function_bytes": 1,
                "runner_failure": 1,
                "section_layout_drift": 1,
            },
        )

    def test_cli_opt_in_prints_and_serializes_source_data(self) -> None:
        output_json = Path(self.tempdir.name) / "report.json"
        stdout = io.StringIO()
        with contextlib.redirect_stdout(stdout):
            result = report.main([
                "--stats", str(self.stats), "--by-source", "--json", str(output_json),
            ])

        self.assertEqual(result, 0)
        text = stdout.getvalue()
        self.assertIn("By source", text)
        self.assertIn("fragment1_code.c", text)
        self.assertIn("fragment2_code.c", text)
        self.assertIn("mismatch_kinds:", text)

        payload = json.loads(output_json.read_text(encoding="utf-8"))
        self.assertEqual(payload["by_source"]["disasm/src/fragments/1/fragment1_code.c"]["accepted_attempts"], 2)
        self.assertEqual(payload["by_source"]["disasm/src/fragments/2/fragment2_code.c"]["accepted_attempts"], 0)
        self.assertEqual(payload["by_source"]["disasm/src/fragments/2/fragment2_code.c"]["runner_errors"], 1)

    def test_default_output_and_json_have_no_source_section(self) -> None:
        output_json = Path(self.tempdir.name) / "default.json"
        stdout = io.StringIO()
        with contextlib.redirect_stdout(stdout):
            result = report.main(["--stats", str(self.stats), "--json", str(output_json)])

        self.assertEqual(result, 0)
        self.assertNotIn("By source", stdout.getvalue())
        payload = json.loads(output_json.read_text(encoding="utf-8"))
        self.assertEqual(set(payload), {"by_prefix", "by_variant"})


if __name__ == "__main__":
    unittest.main()
