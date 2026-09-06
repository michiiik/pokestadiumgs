# Region notes -- disasm/src/fragments/87/fragment87_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Templated slot family 81B002EC..81B005EC: frame-size + register-tie plateau (solved) (2026-09-06)

`func_81B002EC` / `func_81B003EC` / `func_81B004EC` / `func_81B005EC` are one
templated family: four byte-identical shapes 0x100 apart that differ only in
six immediates (the two `addiu $a3` codes, the two `slti` bounds, the
`sp2C[]`/`sp28[]` slot indices, and the sound id 0x741..0x744). The last three
sat on a shared `similarity=1.0 / raw=0.5938 / mismatch_kind=immediate_drift`
plateau (triage `score_clustering` fingerprint 1f41f2fd5e45f667, best label
`call-sequence:paired64:u8-direct-index`).

`immediate_drift` was a misread of the runner's first-diff: the drifting
immediate was instruction 0, `addiu $sp, $sp, -0x38` against the target's
-0x30, and every `$sp`-relative offset downstream inherited the +8. Two real
causes, both now proven:

1. IDO reserves a stack slot for **every declared local, in declaration
   order**, even ones that end up purely in registers. The plateau body
   declared five locals (`sp2C`, `sp28`, `sp27`, `s32 temp_s0`, `u8 var_a3`);
   the fifth pushed the locals area past the saved-register block and grew
   the frame by 8. Four locals in the order `u8 *sp2C; u8 *sp28; u8 sp27;
   s32 temp_s0;` lands them at 0x2C / 0x28 / 0x27 / 0x20 and gives the exact
   0x30 frame. (`temp_s0` may also be dropped entirely and `arg0` used
   directly - same frame.) The plateau body also had `*sp28 = ...` where the
   target stores at `sp28[<slot>]`.

2. What was left after that is a pure **register tie**, not immediate drift:
   the target puts the reloaded `arg1` byte in `$v1` and the 2/3 code in
   `$a3`; every hand spelling put the code in `$v1` and `arg1` in `$a2`
   (44/64 instructions, 12 register-only diffs). Measured pool order for
   these candidates is `$v1, $a3, $t0, ...` by declaration order, with a
   parameter-derived temp taking `$a2`; `arg1` and `sp27` tie at four
   references each and the local wins the tie. One extra *conditional read*
   of `arg1` anywhere in the body breaks the tie the target's way. The
   permuter found it in 157s (`if ((!arg1) && (!arg1)) { }` in the else arm);
   a single `if (!arg1) { }` is enough for 81B003EC/81B005EC but not for
   81B002EC/81B004EC, so all four use the doubled form.

Dead ends, all re-verified byte-for-byte at 44/64 - do not retry:
declaration-order permutations, `s8`/`s32` widths for the byte local, a
`u8 sp24[4]` array in place of it, `switch` instead of `if` on
`func_8005D92C(...) == 7`, ternary, dropping `temp_s0`, a local copy of
`arg1` (IDO copy-propagates it but still burns its stack slot), `s32`
parameters with `(u8)` casts, inverted `(<30 || >=53)` condition, a third
`&&` term, `arg1 = 0;` / `arg1 = arg1;` in the else arm (an assignment does
not count, only a read in a condition), `extern` return/parameter width
changes on `func_800648A0`, IDO 5.3 instead of 7.1, and -O1/-O2 -g0/-mips1.
