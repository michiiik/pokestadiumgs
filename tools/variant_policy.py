#!/usr/bin/env python3
"""Data-driven gating for m2c diagnostic-triggered retry variants.

``sweep_targets.py``'s ordinary probe pass is small on purpose (see its
``DEFAULT_VARIANT_NAMES``), but a compile failure can still trigger a second,
diagnostic-selected retry pass (``compile_failure_variant_names``).  That
retry pass has historically included a trio of type spellings --
``ptr-void``/``ptr-s32``/``u32-void`` -- that the probe stats show almost
never compiles: see the module docstring evidence cited in
``tools/sweep_targets.py`` and the repository issue this module answers.

``VariantPolicy`` reads the recorded probe-stats attempts and aggregates,
per ``(variant, diagnostic_class)``, how many times that variant was tried
and how often it actually paid off (an accepted or isolated-probe-matching
candidate).  ``allowed_retry_variants`` then filters a candidate variant
list down to the ones still worth spending a real ``m2c``/compiler
invocation on: an *unexplored* variant (fewer than ``min_attempts`` recorded
attempts for this diagnostic class) is always allowed, since there is no
evidence against it yet; an *explored* variant is only allowed again if it
has actually paid off at least once.

The default policy (``VariantPolicy.permissive()``, also the module-level
``DEFAULT_POLICY``) allows every candidate unconditionally -- this is what
every call site in ``sweep_targets.py`` falls back to when no explicit
policy is passed, so existing behavior and tests are unaffected until a
caller opts in (the sweep CLI does, via ``--variant-policy``; pass
``--variant-policy off`` to opt back out).

Usage:
    python3 -c "
import variant_policy as vp
policy = vp.VariantPolicy.from_stats()
print(policy.allowed_retry_variants('pointer_operand', ['ptr-void', 'ptr-s32']))
"
"""

from __future__ import annotations

import json
import re
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

import probe_stats

REPO_ROOT = Path(__file__).resolve().parent.parent
DISASM_ROOT = REPO_ROOT / "disasm"

# A companion migration moves the probe-stats file to this repository-tracked
# location; ``STATS_PATH_LEGACY`` remains a fallback for a worktree (or an
# older checkout) that has not picked up that move yet.  ``default_stats_paths``
# is the one place that reconciles the two so every other caller -- the
# policy, the report script -- can just merge whatever exists.  These mirror
# ``probe_stats.DEFAULT_STATS_PATH``/``LEGACY_STATS_PATH`` (kept as separate
# module attributes, rather than read straight off ``probe_stats``, so a
# test can still mock just this module's view of them).
STATS_PATH_CURRENT = DISASM_ROOT / "probe-stats" / "probe-stats.jsonl"
STATS_PATH_LEGACY = DISASM_ROOT / "build" / "probe-stats.jsonl"


def default_stats_paths() -> tuple[Path, ...]:
    """Return the probe-stats files that currently exist, current path first.

    Both may exist during the migration window (an old build/ file plus a
    freshly relocated one); both are merged.  Neither existing is not an
    error -- callers get an empty, permissive-equivalent aggregate.  The
    actual existence-plus-rotated-siblings resolution is delegated to
    ``probe_stats.resolve_paths`` so this module has one less copy of that
    logic to keep in sync.
    """
    return tuple(probe_stats.resolve_paths((STATS_PATH_CURRENT, STATS_PATH_LEGACY)))


# ---------------------------------------------------------------------------
# Diagnostic classification
#
# This mirrors the keyword buckets ``sweep_targets.compile_failure_variant_names``
# already uses to pick retry candidates from a compiler diagnostic, so the
# class computed here for aggregation lines up with the class a live call
# site will look up a policy decision under.
# ---------------------------------------------------------------------------

CLASS_NO_PROTOTYPE_ANON = "no_prototype_anonymous_call"
CLASS_NO_PROTOTYPE_FUNC = "no_prototype_call"
CLASS_POINTER_OPERAND = "pointer_operand"
CLASS_UNDEFINED = "undefined_undeclared"
CLASS_SYNTAX = "syntax"
CLASS_REDECLARATION = "redeclaration"
CLASS_HALFWORD = "halfword"
CLASS_UNKNOWN_TYPE = "unknown_type"
CLASS_OTHER = "other"
CLASS_NONE = "none"

_CFE_ERROR_RE = re.compile(r"(?m)^cfe:\s+Error(?:\s+\d+)?\s*:\s*(.*)$")


def first_cfe_error(diagnostic: str | None) -> str | None:
    """Return the first CFE error message, excluding warnings and context.

    Kept identical in shape to ``sweep_targets._first_cfe_error`` -- both
    exist because ``sweep_targets`` predates this module and keeps its own
    copy for backward compatibility, but they must classify the same way.
    """
    text = diagnostic or ""
    match = _CFE_ERROR_RE.search(text)
    if match is not None:
        return match.group(1).strip()
    if "cfe:" not in text.lower() and text.strip():
        return text.strip()
    return None


def classify_diagnostic(diagnostic: str | None) -> str:
    """Bucket a compiler diagnostic into a coarse, retry-relevant class.

    Only the first CFE error is considered (a later error is often a cascade
    from the first).  A missing/empty diagnostic -- the normal case for an
    ``accepted``/``probe_match``/``probe_rejected`` attempt -- classifies as
    ``CLASS_NONE``.
    """
    message = first_cfe_error(diagnostic)
    if message is None:
        return CLASS_NONE
    text = message.lower()
    if "anonymous function" in text:
        return CLASS_NO_PROTOTYPE_ANON
    if "no prototype for the call to func_" in text:
        return CLASS_NO_PROTOTYPE_FUNC
    if "syntax error" in text:
        return CLASS_SYNTAX
    if "redeclaration" in text or "redefinition" in text:
        return CLASS_REDECLARATION
    if "undefined" in text or "undeclared" in text:
        return CLASS_UNDEFINED
    if any(token in text for token in (
        "operand", "pointer", "conversion", "convert", "dereference",
        "selector requires", "incompatible",
    )):
        return CLASS_POINTER_OPERAND
    if any(token in text for token in ("short", "halfword", "s16")):
        return CLASS_HALFWORD
    if any(token in text for token in ("unknown type", "m2c_unk")):
        return CLASS_UNKNOWN_TYPE
    return CLASS_OTHER


# ---------------------------------------------------------------------------
# Label parsing
#
# A probe-stats attempt's label is ``m2c:<variant>`` or ``m2c-gotos:<variant>``
# (``--large`` mode), optionally followed by one or more ``:<suffix>`` tags
# such as ``:compile-retry``, ``:mismatch-retry``, or ``:callee-unprototyped``.
# A handful of suffixes name a mechanical rewrite that is itself worth
# tracking as its own variant (``:fnptr-cast`` -- see ``sweep_targets
# .fnptr_cast_candidate``); when one of those is present it takes priority
# over the base type-spelling name so the policy can learn about the rewrite
# independently of whichever spelling it was layered onto.
# ---------------------------------------------------------------------------

_LABEL_VARIANT_RE = re.compile(r"^(?:m2c|m2c-gotos):([A-Za-z0-9_-]+)")
_LABEL_SUFFIX_VARIANTS: tuple[str, ...] = ("fnptr-cast",)


def label_variant(label: str) -> str | None:
    """Return the variant key a probe-stats attempt's label counts toward."""
    match = _LABEL_VARIANT_RE.match(label)
    if match is None:
        return None
    segments = label.split(":")
    for suffix in _LABEL_SUFFIX_VARIANTS:
        if suffix in segments:
            return suffix
    return match.group(1)


@dataclass(frozen=True)
class VariantStats:
    """Aggregated outcome counts for one ``(variant, diagnostic_class)`` pair."""

    attempts: int = 0
    accepted: int = 0
    probe_match: int = 0

    @property
    def success(self) -> int:
        return self.accepted + self.probe_match


class VariantPolicy:
    """Historical evidence for which retry variants still earn a real compile."""

    def __init__(
        self,
        stats: dict[tuple[str, str], VariantStats] | None = None,
        *,
        permissive: bool = False,
    ) -> None:
        self._stats: dict[tuple[str, str], VariantStats] = dict(stats or {})
        self._permissive = permissive or not self._stats

    @classmethod
    def permissive(cls) -> "VariantPolicy":
        """A policy with no evidence: every candidate is allowed.

        This reproduces the pre-policy behavior of
        ``compile_failure_variant_names``/``compile_failure_candidates`` and
        is the default every call site falls back to.
        """
        return cls(permissive=True)

    @classmethod
    def from_stats(
        cls, stats_paths: Iterable[Path | str] | Path | str | None = None,
    ) -> "VariantPolicy":
        """Aggregate ``(variant, diagnostic_class)`` outcomes from stats files.

        ``stats_paths`` defaults to ``default_stats_paths()``.  A missing or
        unreadable file is skipped rather than raising, so a fresh worktree
        with no recorded history yields a policy that behaves exactly like
        ``permissive()``.
        """
        if stats_paths is None:
            paths: tuple[Path, ...] = default_stats_paths()
        elif isinstance(stats_paths, (str, Path)):
            paths = (Path(stats_paths),)
        else:
            paths = tuple(Path(path) for path in stats_paths)

        totals: dict[tuple[str, str], list[int]] = {}
        for path in paths:
            if not path.exists():
                continue
            try:
                handle = path.open(encoding="utf-8", errors="replace")
            except OSError:
                continue
            with handle:
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
                        if not isinstance(label, str):
                            continue
                        variant = label_variant(label)
                        if variant is None:
                            continue
                        diagnostic = attempt.get("diagnostic")
                        diagnostic_class = classify_diagnostic(
                            diagnostic if isinstance(diagnostic, str) else None
                        )
                        bucket = totals.setdefault((variant, diagnostic_class), [0, 0, 0])
                        bucket[0] += 1
                        status = attempt.get("status")
                        if status == "accepted":
                            bucket[1] += 1
                        elif status == "probe_match":
                            bucket[2] += 1

        stats = {key: VariantStats(*values) for key, values in totals.items()}
        return cls(stats)

    def stats_for(self, variant: str, diagnostic_class: str) -> VariantStats:
        """Return the aggregated evidence for one ``(variant, class)`` pair."""
        return self._stats.get((variant, diagnostic_class), VariantStats())

    def allowed_retry_variants(
        self,
        diagnostic_class: str,
        candidates: Iterable[str],
        *,
        min_attempts: int = 30,
    ) -> tuple[str, ...]:
        """Filter ``candidates`` to the variants still worth a real compile.

        A permissive policy (no stats loaded) allows every candidate
        unchanged.  Otherwise a variant is only kept when it is unexplored
        for this diagnostic class (fewer than ``min_attempts`` recorded
        attempts) or has a positive historical accept+probe_match count for
        it -- an explored variant with zero successes over that many tries
        is dropped.
        """
        allowed: list[str] = []
        for name in candidates:
            if self._permissive:
                allowed.append(name)
                continue
            stat = self.stats_for(name, diagnostic_class)
            if stat.attempts < min_attempts or stat.success > 0:
                allowed.append(name)
        return tuple(allowed)


DEFAULT_POLICY = VariantPolicy.permissive()
