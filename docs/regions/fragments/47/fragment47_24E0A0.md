# Region notes -- disasm/src/fragments/47/fragment47_24E0A0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: index-arithmetic loop over a strided array (AGENTS.md §4) (2026-08-28)

`for (i = 0; i < n; i++) { ... &arr[i * STRIDE] ... }` -- the pointer-accumulator spelling allocates differently. Evidence: 2 (`func_86009318`, `func_86009260`).

## Unsolved shape: float scheduling plateau at 0.909 (AGENTS.md §5) (2026-08-28)

`func_86007F6C` and `func_86009D7C` both plateau at 0.909 with one extra instruction and an unexplained `mov.s $f12,$f14` shuffle, at exact instruction counts -- a float argument-register scheduling difference worth its own investigation.
