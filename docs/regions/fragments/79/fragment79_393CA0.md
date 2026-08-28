# Region notes -- disasm/src/fragments/79/fragment79_393CA0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: record-stride forwarding wrapper (AGENTS.md §4) (2026-08-28)

Record-stride forwarding wrapper (overlay fragments) -- `helper(&BASE[BASE[idx_field] * STRIDE], a0, ...)` with the remaining formals forwarded verbatim; the clamp variant is `idx = BASE[idx_field] - 1; if (idx < 0) idx = LAST;` then the same forward. Evidence: 12 (bases `D_84195280` stride 0x280, `D_84195208`, `D_841951F8`). Limit: argument widths vary per owner (`u8`/`s16`/`u16`, 5th arg stack-passed) -- read each `.s`.

## Verified spelling: pointer-table guard lookup (AGENTS.md §4) (2026-08-28)

Pointer-table guard lookup -- `if (arg0 < 4) { u8 *ptr = D_84186160[arg0]; if (ptr) helper(ptr, ...); }`. Evidence: 2 (`func_84134D80`, `func_84135B8C`). Limit: a `ptr + 8` variant exists; pick by the offset in the `.s`.

## Verified spelling: dead tail longer than one jr/nop pair (AGENTS.md §4) (2026-08-28)

When `symbol_size_drift` is more than 8 bytes short, add N uniquely-named trailing `void <owner>_paddingK(void) {}` helpers; `#pragma C_FUNCTION_PADDING` did not reproduce it. Evidence: 1 (`func_841352DC`). Limit: one owner so far; prefer the pragma first.

## Unsolved shape: incoming-argument stack-home spill (AGENTS.md §5) (2026-08-28)

An incoming-argument stack-home spill (`sw a0, N(sp)` with no intervening call) that no C spelling reproduces -- the single most common dead end in fragment work: 7+ owners in this file alone. Drop an owner as soon as its first diff is this.
