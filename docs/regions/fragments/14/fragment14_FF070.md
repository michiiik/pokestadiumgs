# Region notes -- disasm/src/fragments/14/fragment14_FF070.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: float divide by a power of two (AGENTS.md §4) (2026-08-28)

Divide by the **integer** literal (`x / 16`), not `16.0f`: a float literal divisor is strength-reduced to `mul.s` by the reciprocal, an int divisor keeps `div.s`. Evidence: 1 (`func_8130A98C`).

## Unsolved shape: $v0/$v1 swap on counter pairs (AGENTS.md §5) (2026-08-28)

Decrement/increment counter pairs stuck at similarity 1.0 with `$v0`/`$v1` swapped (`func_8130B91C`, `func_8130B95C`).
