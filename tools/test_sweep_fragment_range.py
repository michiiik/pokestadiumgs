#!/usr/bin/env python3
"""Focused regression tests for fragment-band sweep selection and accounting."""

from __future__ import annotations

import os
import sys
import tempfile
import time
import unittest
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import sweep_targets  # noqa: E402
import try_pragma_compare as runner  # noqa: E402


class SweepBandTests(unittest.TestCase):
    def test_fragment_filter_happens_before_limit(self) -> None:
        rows = [
            {"function": "func_out_a", "source": "disasm/src/fragments/1/a.c"},
            {"function": "func_out_b", "source": "disasm/src/fragments/2/b.c"},
            {"function": "func_in_a", "source": "disasm/src/fragments/17/a.c"},
            {"function": "func_in_b", "source": "disasm/src/fragments/32/b.c"},
            {"function": "func_in_c", "source": "disasm/src/fragments/25/c.c"},
        ]
        with mock.patch.object(sweep_targets.targets, "owner_index", return_value={name: object() for name in range(5)}) as owners, mock.patch.object(
            sweep_targets.targets,
            "list_targets",
            return_value={"matched": 5, "targets": rows, "truncated": False},
        ) as listing:
            result = sweep_targets._sweep_listing(
                max_instructions=None,
                min_instructions=None,
                family=None,
                source=None,
                limit=2,
                fragment_range=(17, 32),
            )

        owners.assert_called_once()
        listing.assert_called_once()
        self.assertEqual(listing.call_args.kwargs["limit"], 5)
        self.assertEqual(result["matched"], 2)
        self.assertEqual(result["available_in_range"], 3)
        self.assertTrue(result["truncated"])
        self.assertEqual(
            [row["function"] for row in result["targets"]],
            ["func_in_a", "func_in_b"],
        )

    def test_stale_cleanup_only_removes_old_probe_directories(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            old = root / "disasm" / "probes" / ".pragma_probe_old"
            fresh = root / "disasm" / "build" / "probes" / ".pragma_probe_fresh"
            old.mkdir(parents=True)
            fresh.mkdir(parents=True)
            tracked = root / "disasm" / "src" / "keep.c"
            tracked.parent.mkdir(parents=True)
            tracked.write_text("keep\n")
            old_time = time.time() - 7200
            os.utime(old, (old_time, old_time))

            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STALE_SECONDS": "3600"}):
                runner._cleanup_stale_probe_dirs(root)

            self.assertFalse(old.exists())
            self.assertTrue(fresh.exists())
            self.assertEqual(tracked.read_text(), "keep\n")

    def test_dirty_accounting_distinguishes_sources_and_targets(self) -> None:
        dirty_source = "disasm/src/fragments/17/dirty.c"
        rows = [
            {"function": "func_dirty_a", "source": dirty_source, "family": "call_sequence"},
            {"function": "func_dirty_b", "source": dirty_source, "family": "call_sequence"},
            {"function": "func_clean", "source": "disasm/src/fragments/18/clean.c", "family": "call_sequence"},
        ]
        dirty_path = (sweep_targets.targets.REPO_ROOT / dirty_source).resolve()
        with mock.patch.object(
            sweep_targets.targets,
            "list_targets",
            return_value={"matched": len(rows), "targets": rows, "truncated": False},
        ), mock.patch.object(
            sweep_targets.dedupe_externs,
            "dirty_sources",
            return_value={dirty_path},
        ), mock.patch.object(
            sweep_targets,
            "draft_variants",
            return_value=([], None),
        ):
            result = sweep_targets.sweep(
                max_instructions=None,
                min_instructions=None,
                family=None,
                source=None,
                limit=10,
                gate=False,
                workers=1,
            )

        self.assertEqual(result["matched"], 3)
        self.assertEqual(result["skipped_dirty_sources"], 1)
        self.assertEqual(result["skipped_dirty_targets"], 2)


if __name__ == "__main__":
    unittest.main()
