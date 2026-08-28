# Region notes -- disasm/src/fragments/17/fragment17_10FFC0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Unsolved shape: unaligned 4-byte copy needs a struct-typed assignment (AGENTS.md §5) (2026-08-28)

An unaligned 4-byte copy assembled as `lwl/lwr`+`swl/swr` needs a **struct-typed assignment** (`*(Pair16 *)(p + a) = *(Pair16 *)(p + b);` with a 2x`s16` typedef); a plain `*(s32 *)` cast compiles to `lw`/`sw` because IDO trusts the cast's alignment (`func_82201C70`: raw 0.26 -> 0.74, size exact, still unaccepted).
