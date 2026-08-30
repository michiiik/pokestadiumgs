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

## Fleet box 2026-08-30 accepted spelling and requeue (2026-08-30)

Accepted through the runner and full ROM gate: func_84129A80 with exact label init:raw-fields:repeated-direct-pointer. Probe reported probe_match with link_verified=true; the gate reported batch_status=accepted and rebuilt the baseline ROM (MD5 1561c75d11cedf356a8ddb1a4a5f9d5d). Requeue func_8412E220 after 35 probe attempts across five probe-only batches: best label predicate:loop:frame-padding-8:decl-limit-result-ptr, normalized similarity 1.0000/raw 0.7069, exact expected/actual size 232 bytes, mismatch register_allocation_only at expected lw t2, 0x1c(sp) versus actual lw t4, 0x1c(sp). The initial m2c/direct/loop/pointer/guard/raw-offset and declaration variants were immediate_drift with expected frame -0x28 versus actual -0x20; documented frame-padding variants reached the expected frame and size but did not resolve the register tie. The runner futility was repeated-drift after 12 prior rejected attempts sharing fingerprint [immediate_drift,3,0,0x27bdffd8,0x27bdffe0]. Next action: use an address-observable stack-slot layout or the permuter on the exact-size compact frame-padding form; do not repeat the current frame-padding declaration permutations.
