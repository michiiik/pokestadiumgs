#!/usr/bin/env python3
"""Print candidate-attempt yield per label prefix from the probe stats.

Every ``try_pragma_compare``/``sweep_targets`` attempt lands one JSON record
per batch in the probe-stats file (see ``variant_policy.default_stats_paths``
for where that file lives).  This script aggregates those attempts by their
label's leading prefix -- ``m2c``, ``manual``, ``permute``, a hand-written
family label, and so on -- and, separately, by the ``m2c:<variant>`` type
spelling those labels carry, and prints how many attempts each group had,
what fraction failed to compile, and how many isolated-probe-matched or were
fully accepted.  This is the measurement tools/variant_policy.py's gating
decisions are based on; run it before and after a policy change to see the
effect on real numbers.

Usage:
    tools/report_candidate_yield.py
    tools/report_candidate_yield.py --stats disasm/build/probe-stats.jsonl
    tools/report_candidate_yield.py --min-attempts 10
"""

from __future__ import annotations

import argparse
import collections
import json
from pathlib import Path

import variant_policy


def _label_prefix(label: str) -> str:
    return label.split(":", 1)[0] if label else "(no label)"


class Tally:
    __slots__ = ("attempts", "compile_failed", "probe_match", "accepted")

    def __init__(self) -> None:
        self.attempts = 0
        self.compile_failed = 0
        self.probe_match = 0
        self.accepted = 0

    def add(self, status: str | None) -> None:
        self.attempts += 1
        if status == "compile_failed":
            self.compile_failed += 1
        elif status == "probe_match":
            self.probe_match += 1
        elif status == "accepted":
            self.accepted += 1

    @property
    def compile_fail_rate(self) -> float:
        return self.compile_failed / self.attempts if self.attempts else 0.0


def collect(stats_paths: tuple[Path, ...]) -> tuple[dict[str, Tally], dict[str, Tally]]:
    """Return ``(by_prefix, by_variant)`` tallies from the given stats files."""
    by_prefix: dict[str, Tally] = collections.defaultdict(Tally)
    by_variant: dict[str, Tally] = collections.defaultdict(Tally)
    for path in stats_paths:
        if not path.exists():
            continue
        with path.open(encoding="utf-8", errors="replace") as handle:
            for line in handle:
                line = line.strip()
                if not line:
                    continue
                try:
                    record = json.loads(line)
                except json.JSONDecodeError:
                    continue
                if not isinstance(record, dict):
                    continue
                attempts = record.get("attempts")
                if not isinstance(attempts, list):
                    continue
                for attempt in attempts:
                    if not isinstance(attempt, dict):
                        continue
                    label = attempt.get("label")
                    if not isinstance(label, str) or not label:
                        continue
                    status = attempt.get("status")
                    by_prefix[_label_prefix(label)].add(status if isinstance(status, str) else None)
                    variant = variant_policy.label_variant(label)
                    if variant is not None:
                        by_variant[variant].add(status if isinstance(status, str) else None)
    return dict(by_prefix), dict(by_variant)


def _print_table(title: str, rows: dict[str, Tally], *, min_attempts: int) -> None:
    print(f"\n{title}")
    header = f"{'name':<28} {'attempts':>9} {'compile_fail%':>14} {'probe_match':>12} {'accepted':>9}"
    print(header)
    print("-" * len(header))
    ordered = sorted(rows.items(), key=lambda item: -item[1].attempts)
    for name, tally in ordered:
        if tally.attempts < min_attempts:
            continue
        print(
            f"{name:<28} {tally.attempts:>9} {tally.compile_fail_rate * 100:>13.1f}% "
            f"{tally.probe_match:>12} {tally.accepted:>9}"
        )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument(
        "--stats", type=Path, action="append", dest="stats",
        help="probe-stats JSONL path (repeatable); default: variant_policy.default_stats_paths()",
    )
    parser.add_argument(
        "--min-attempts", type=int, default=1,
        help="omit a row with fewer than this many attempts (default 1: show everything seen)",
    )
    parser.add_argument("--json", type=Path, help="also write the raw tallies to this file")
    args = parser.parse_args()

    stats_paths = tuple(args.stats) if args.stats else variant_policy.default_stats_paths()
    if not stats_paths:
        print("no probe-stats file found (checked variant_policy.default_stats_paths())")
        return 1

    by_prefix, by_variant = collect(stats_paths)
    print(f"stats: {', '.join(str(path) for path in stats_paths)}")
    _print_table("By label prefix", by_prefix, min_attempts=args.min_attempts)
    _print_table("By m2c/m2c-gotos variant", by_variant, min_attempts=args.min_attempts)

    if args.json:
        payload = {
            "by_prefix": {
                name: {
                    "attempts": tally.attempts,
                    "compile_failed": tally.compile_failed,
                    "compile_fail_rate": tally.compile_fail_rate,
                    "probe_match": tally.probe_match,
                    "accepted": tally.accepted,
                }
                for name, tally in by_prefix.items()
            },
            "by_variant": {
                name: {
                    "attempts": tally.attempts,
                    "compile_failed": tally.compile_failed,
                    "compile_fail_rate": tally.compile_fail_rate,
                    "probe_match": tally.probe_match,
                    "accepted": tally.accepted,
                }
                for name, tally in by_variant.items()
            },
        }
        args.json.write_text(json.dumps(payload, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
