# Region notes -- disasm/src/fragments/14/fragment14_FF070.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: float divide by a power of two (AGENTS.md §4) (2026-08-28)

Divide by the **integer** literal (`x / 16`), not `16.0f`: a float literal divisor is strength-reduced to `mul.s` by the reciprocal, an int divisor keeps `div.s`. Evidence: 1 (`func_8130A98C`).

## Unsolved shape: $v0/$v1 swap on counter pairs (AGENTS.md §5) (2026-08-28)

Decrement/increment counter pairs stuck at similarity 1.0 with `$v0`/`$v1` swapped (`func_8130B91C`, `func_8130B95C`).

## Terminal register tie: func_813074E4 (2026-08-30) (2026-08-30)

func_813074E4 reached terminal register-tie futility after 45 prior attempts plus 32 variants in this box. Best hand candidate was call-chain:raw-base:no-pointer-local / callee-first-expression: normalized similarity 1.0000, raw similarity 0.9714, expected and actual size 140 bytes. The remaining fingerprint is register allocation only at offset 76: expected `addu $t8, $t7, $v0`, actual `addu $t8, $v0, $t7`; all frame and stack offsets match. Earlier explicit cached-pointer variants had normalized 1.0000/raw 0.6286 and immediate drift from a -0x28 frame; compound-add variants regressed to normalized 0.8571/raw 0.5429 with the same frame drift. Attempted hypothesis families: pointer-local and integer-local cached base, declaration/order and field temporaries, conditional/branch argument construction, raw-base/no-pointer-local, pointer and integer argument widths, explicit call-result temporaries, callee-first expressions, compound assignment and arithmetic order. Runner futility: `register-tie: 6 prior attempts at >=0.99 register_allocation_only -- source-shape variants will not close this -- register tie -- stop`. Next action: leave for permuter/register-tie handling; do not spend another hand-decompilation box on this source shape unless the permuter or a new compiler/tooling rule changes.
