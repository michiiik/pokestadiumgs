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
    tools/report_candidate_yield.py --by-source
"""

from __future__ import annotations

import argparse
import collections
import json
from collections.abc import Iterator
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


class SourceTally:
    """Facts aggregated from the attempts in batches for one source."""

    __slots__ = (
        "batches",
        "attempts",
        "accepted_attempts",
        "accepted_owners",
        "probe_matches",
        "compile_failed",
        "runner_errors",
        "internal_errors",
        "unavailable",
        "link_verified_accepted",
        "link_verified_probe_matches",
        "mismatch_kinds",
        "_accepted_owner_names",
    )

    _RUNNER_ERROR_STATUSES = frozenset({"probe_error", "runner_error"})
    _INTERNAL_ERROR_STATUSES = frozenset({"internal_error", "runner_internal_error"})
    _UNAVAILABLE_STATUSES = frozenset({"probe_unavailable", "unavailable"})

    def __init__(self) -> None:
        self.batches = 0
        self.attempts = 0
        self.accepted_attempts = 0
        self.accepted_owners = 0
        self.probe_matches = 0
        self.compile_failed = 0
        self.runner_errors = 0
        self.internal_errors = 0
        self.unavailable = 0
        self.link_verified_accepted = 0
        self.link_verified_probe_matches = 0
        self.mismatch_kinds: collections.Counter[str] = collections.Counter()
        self._accepted_owner_names: set[str] = set()

    def add_batch(self) -> None:
        self.batches += 1

    def add_attempt(self, attempt: dict[str, object]) -> None:
        self.attempts += 1
        status = attempt.get("status")
        status = status if isinstance(status, str) else None

        if status == "accepted":
            self.accepted_attempts += 1
            function = attempt.get("function")
            if isinstance(function, str) and function:
                self._accepted_owner_names.add(function)
        elif status == "probe_match":
            self.probe_matches += 1

        if status in {"compile_failed", "combined_compile_failed"}:
            self.compile_failed += 1
        probe_reason = attempt.get("probe_reason")
        probe_reason = probe_reason if isinstance(probe_reason, str) else None
        if status in self._RUNNER_ERROR_STATUSES or probe_reason in {"probe_error", "runner_error"}:
            self.runner_errors += 1
        if status in self._INTERNAL_ERROR_STATUSES or probe_reason in {"internal_error", "runner_internal_error"}:
            self.internal_errors += 1
        if status in self._UNAVAILABLE_STATUSES or probe_reason in {
            "baseline_object_unavailable", "missing_function_bytes", "unavailable"
        }:
            self.unavailable += 1

        if attempt.get("link_verified") is True:
            if status == "accepted":
                self.link_verified_accepted += 1
            elif status == "probe_match":
                self.link_verified_probe_matches += 1

        mismatch_kind = attempt.get("mismatch_kind")
        if isinstance(mismatch_kind, str) and mismatch_kind:
            self.mismatch_kinds[mismatch_kind] += 1

    def finish(self) -> None:
        self.accepted_owners = len(self._accepted_owner_names)


def _iter_records(stats_paths: tuple[Path, ...]) -> Iterator[dict[str, object]]:
    """Yield valid JSON objects from the selected stats paths.

    Keep the explicit-path behavior used by the existing report: callers that
    pass ``--stats`` get exactly those paths, while the default path list is
    still supplied by ``variant_policy.default_stats_paths()``.
    """
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
                if isinstance(record, dict):
                    yield record


def collect(stats_paths: tuple[Path, ...]) -> tuple[dict[str, Tally], dict[str, Tally]]:
    """Return ``(by_prefix, by_variant)`` tallies from the given stats files."""
    by_prefix: dict[str, Tally] = collections.defaultdict(Tally)
    by_variant: dict[str, Tally] = collections.defaultdict(Tally)
    for record in _iter_records(stats_paths):
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


def _source_name(record: dict[str, object]) -> str:
    source = record.get("source")
    if not isinstance(source, str) or not source:
        return "(no source)"
    # Stats can be emitted from either the checkout or a worktree.  Keep the
    # repository-relative spelling for sources that identify this tree, while
    # leaving unrelated absolute paths distinguishable.
    normalized = source.replace("\\", "/")
    marker = "disasm/src/"
    marker_index = normalized.find(marker)
    if marker_index >= 0:
        return normalized[marker_index:]
    return normalized


def collect_by_source(stats_paths: tuple[Path, ...]) -> dict[str, SourceTally]:
    """Return factual attempt totals grouped by each batch's ``source``."""
    by_source: dict[str, SourceTally] = collections.defaultdict(SourceTally)
    for record in _iter_records(stats_paths):
        tally = by_source[_source_name(record)]
        tally.add_batch()
        attempts = record.get("attempts")
        if not isinstance(attempts, list):
            continue
        for attempt in attempts:
            if isinstance(attempt, dict):
                tally.add_attempt(attempt)
    for tally in by_source.values():
        tally.finish()
    return dict(by_source)


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


def _print_source_report(rows: dict[str, SourceTally], *, min_attempts: int) -> None:
    print("\nBy source")
    header = (
        f"{'source':<44} {'batches':>7} {'attempts':>9} {'accepted':>9} "
        f"{'owners':>7} {'probe_matches':>12} {'compile_failed':>12} "
        f"{'runner_errors':>13} {'internal_errors':>14} {'unavailable':>11} "
        f"{'link_verified_accepted':>23} {'link_verified_probe_matches':>27}"
    )
    print(header)
    print("-" * len(header))
    ordered = sorted(rows.items(), key=lambda item: (-item[1].attempts, item[0]))
    for source, tally in ordered:
        if tally.attempts < min_attempts:
            continue
        print(
            f"{source:<44} {tally.batches:>7} {tally.attempts:>9} "
            f"{tally.accepted_attempts:>9} {tally.accepted_owners:>7} "
            f"{tally.probe_matches:>12} {tally.compile_failed:>12} "
            f"{tally.runner_errors:>7} {tally.internal_errors:>8} "
            f"{tally.unavailable:>11} {tally.link_verified_accepted:>9} "
            f"{tally.link_verified_probe_matches:>10}"
        )
        mismatch_text = ", ".join(
            f"{kind}={count}" for kind, count in sorted(tally.mismatch_kinds.items())
        )
        print(f"  mismatch_kinds: {mismatch_text or '(none recorded)'}")


def _source_payload(tally: SourceTally) -> dict[str, object]:
    return {
        "batches": tally.batches,
        "attempts": tally.attempts,
        "accepted_attempts": tally.accepted_attempts,
        "accepted_owners": tally.accepted_owners,
        "probe_matches": tally.probe_matches,
        "compile_failed": tally.compile_failed,
        "runner_errors": tally.runner_errors,
        "internal_errors": tally.internal_errors,
        "unavailable": tally.unavailable,
        "link_verified_accepted": tally.link_verified_accepted,
        "link_verified_probe_matches": tally.link_verified_probe_matches,
        "mismatch_kinds": dict(sorted(tally.mismatch_kinds.items())),
    }


def main(argv: list[str] | None = None) -> int:
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
    parser.add_argument(
        "--by-source", "--wave", action="store_true", dest="by_source",
        help="also report attempts grouped by each batch source",
    )
    args = parser.parse_args(argv)

    stats_paths = tuple(args.stats) if args.stats else variant_policy.default_stats_paths()
    if not stats_paths:
        print("no probe-stats file found (checked variant_policy.default_stats_paths())")
        return 1

    by_prefix, by_variant = collect(stats_paths)
    print(f"stats: {', '.join(str(path) for path in stats_paths)}")
    _print_table("By label prefix", by_prefix, min_attempts=args.min_attempts)
    _print_table("By m2c/m2c-gotos variant", by_variant, min_attempts=args.min_attempts)

    by_source = collect_by_source(stats_paths) if args.by_source else None
    if by_source is not None:
        _print_source_report(by_source, min_attempts=args.min_attempts)

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
        if by_source is not None:
            payload["by_source"] = {
                name: _source_payload(tally)
                for name, tally in sorted(by_source.items(), key=lambda item: (-item[1].attempts, item[0]))
            }
        args.json.write_text(json.dumps(payload, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
