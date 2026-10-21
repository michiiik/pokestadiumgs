# Region notes -- src/fragments/79/fragment79_3BF4C0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-15

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-15

func_841524B4: plateau at 0.9667 (raw 0.5), mismatch operand_or_scheduling_drift; tried families: state_field_access; tie-pool no

## 2026-09-15

func_84152D6C: time cap at 0.9512 (raw 0.9512) after 2678s, mismatch instruction_drift; tried families: call_sequence; tie-pool no

## 2026-09-19

func_8415132C: matched (call_sequence:canonical:base_sub_state_mult_var_table), 1 iterations, agent antigravity

## 2026-09-19

func_8415335C: matched (call_sequence:canonical:exact_matching_spelling), 1 iterations, agent antigravity

## 2026-09-19

func_8415220C: matched (call_sequence:nested_if:exact_canonical), 1 iterations, agent antigravity

## 2026-09-26

func_84151270: time cap at 1.0 (raw 0.9787) after 2400s, mismatch register_allocation_only; tried families: call_sequence; tie-pool yes

## 2026-09-26

func_841528C4: matched (call_sequence:nested_gate:typed_state_pointer), 4 iterations, agent codex

## 2026-09-26

func_84152140: matched (call_sequence:five-local:late-byte-spill), 1 iterations, agent codex

## 2026-09-29

func_84152408: matched (call_sequence:spill_layout:scratch_table_base_multiplier_guard), 6 iterations, agent unbiased

## 2026-09-29

func_84153A64: matched (call_sequence:constant_offset:permuter_exact), 3 iterations, agent unbiased

## 2026-10-04

func_84151B8C: matched (call_sequence:guard:exact_stack_homes), 1 iterations, agent codex

## 2026-10-04

func_84152764: time cap at 0.9432 (raw 0.8864) after 2421s, mismatch instruction_drift; tried families: call_sequence; tie-pool no

## 2026-10-04

func_84153D94: matched (call_sequence:exact:accepted-stack-home-order), 1 iterations, agent codex

## 2026-10-04

func_84151A5C: matched (call_sequence:guard:zero-left), 1 iterations, agent codex

## 2026-10-04

func_84151AF4: matched (call_sequence:predicate:zero-first), 1 iterations, agent codex

## 2026-10-04

func_841526CC: matched (call_sequence:canonical:parenthesized-guard), 1 iterations, agent codex

## 2026-10-04

func_8415178C: matched (call_sequence:decl-order:sbpta), 1 iterations, agent codex

## 2026-10-04

func_84152308: matched (call_sequence:carrier_reuse:signed_amount_compound_multiply), 2 iterations, agent codex

## 2026-10-13

func_84152764: matched (call_sequence:carrier_address:signed_scaled_byte_displacement), 3 iterations, agent codex

## Accepted plan multiplier, move-type predicate and condition bonus

Three original owners, 368 bytes, are replaced by genuine C:

- `841502D0` / `BattlePlan_ApplyPursuitMultiplier` (96 bytes) checks move
  228, reevaluates its plan through `func_8414D198`, then doubles the
  side-relative halfword at offset 14. The snapshot-aware callers
  `func_8414EE88` and `func_8414EFF0` apply it to the plan returned by
  `func_8414C98C`. Move 228 is Pursuit; its local move metadata has effect
  128, power 40 and type 27. The integer address base and unsigned side
  displacement preserve the original operand ownership and incoming homes.
  The pointer's separate four-byte advance is the plan header transition.
- `84152CD8` / `BattlePlan_HasOnlyNormalOrFightingMoves` (148 bytes) scans
  the four packed move bytes at offsets 4 through 7, stopping at the first
  zero. The existing `func_80062D98` reads move types; ids 0 and 1 are
  Normal and Fighting. A `u16` result carrier preserves the original
  comparison lowering without an additional constant temporary.
- `84153780` / `BattlePlan_AddConditionCountBonus` (124 bytes) marks the
  side's byte at offset 12, obtains the existing condition count from
  `func_84153718`, and adds `count * 128 * func_8414A2AC()` to the side's
  word at offset 56. It then marks plan byte 4 with bit 2. The helper's
  individual flag meanings remain unresolved. Separate, consumed base,
  entry, count and amount locals recover the original frame and byte home;
  the side-relative entry keeps its field offset in the memory operand.

The type predicate preserves a retail bug: it tests the address of
`func_80062D5C` instead of calling that move-power getter. The original ASM
loads the symbol into a saved register and branches on the address, with no
call to it. The source marks this with `//!bug`; inserting a call would change
the program. The direct small-switch spelling removes this address test and
does not match. A source search's materialized-constant diagnostic was not
adopted; the ordinary halfword result carrier matches without that local.

The three recorded runner acceptances are directly link-verified and each
passes the normal, host-syntax-checked US full-ROM gate. Every first success
immediately freezes the complete changed object, four other whole objects,
source, ROM, ELF, linked script and original ASM inputs; their hashes are
independently checked before further compilation. The retail ROM MD5 is
`1561c75d11cedf356a8ddb1a4a5f9d5d`.

Six complete-object controls cover accepted source, leading blanks, removal
of two newly redundant externs, semantic names and four target-ABI assertions.
Ten independent links reproduce all 19,440 text bytes in ROM range
`0x3BF4C0..0x3C40B0`. All 66 original function extents, sections and semantic
relocations agree. Address aliases preserve original ASM callers. No
instruction/relocation rewrite, fake local, forced register/frame, artificial
padding, volatile workaround or manual unrolling is introduced.

`841524B4` remains a requeue. The count reads party count at state offset 8
and 88-byte records after the 24-byte header; its predicate reads halfword
38 and byte 36. Their field meanings are still unknown. Byte-extent bounds,
record-count loops, pointer walks and row/header views leave register/origin
differences or trigger unwanted compiler unrolling. The latest 120-byte row
view has 14 differing raw instruction words. Next inspect its address and
induction webs before changing the loop again; retain ASM until a full match.
