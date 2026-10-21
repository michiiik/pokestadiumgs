# Fragment 79 side-indexed effect bookkeeping

## 2026-10-21: five genuine matching owners

| Owner | Name | Bytes |
| --- | --- | --- |
| `8414D910` | `BattleEffects_CopyOpposingMove` | 168 |
| `8414E224` | `BattleEffects_SetOpposingAmountFromHP` | 132 |
| `8414E508` | `BattleEffects_ClearInsufficientAmount` | 168 |
| `8414E5B0` | `BattleEffects_DoubleConditionalScale` | 168 |
| `8414E7D8` | `BattleEffects_DoubleScaleForIncomingAmount` | 168 |

The five owners total 804 original bytes. The active-side getter and
side-record getter are defined in `fragment79_3C40B0.c`: the latter returns
`D_8419E780 + side * 0xCC + 8`. The dispatcher `func_8414E880` calls these
owners according to the move-effect code. Names describe observed updates,
not a speculative assignment to a particular move.

The shared `Fragment79EffectView` describes only an observed subview at
argument offset 4. Its selected-side byte is at 1, moves at 2, halfword
arrays at 0x0A/0x12/0x1A, and word scales at 0x34. Unknown gaps remain
opaque. Its 60-byte C extent is not a claim about the size of the complete
enclosing game record, and production code does not allocate one.

Copying the opposing move preserves all four following refresh calls.
The amount setter copies the opposing record's HP only under the original
side and amount guard. The insufficient-amount helper clears the current
amount under the original side-dependent threshold. The two scale helpers
double the existing word under their distinct HP/amount conditions. Both
record lookups are retained even where one return value is discarded.
Amounts remain halfwords and scales remain unsigned words; no new range
checks, arithmetic widening, or call removal is introduced.

The first three initial drafts differed only in the operand order of their
equality branch. Writing the selected field first recovers the original
branch operands. Typed subview expressions also preserve the original
explicit offset-4 address materialization; flattening all accesses to
outer byte offsets can remove an instruction and change carriers. The two
further guards match through the same ordinary typed view and field-first
tests. No dummy storage, forced register, padding, manual unrolling,
fabricated callee return type, or instruction/relocation rewrite is used.

The native runner accepted the first three together, then the two further
guards in a second full-ROM-gated transaction. Each first-success callback
froze the whole changed object, four distinct collateral objects, source,
ROM, ELF, and linked script. All nine artifacts were independently hashed
before another compilation. Eight cleanup/whole-original-object controls
verify extern deduplication, formatting, read-only record views, naming,
and blank-line shifts. Fourteen emitted values verify all observed view
offsets, field widths, array extents, and the partial C view extent.
Pre-existing non-prototype warnings and unrelated legacy source spellings
are preserved; none is used to obtain these matches.

## `8414DA70`: requeue, capped-update register carriers

The owner remains assembly. A truthful draft obtains both side records,
preserves the discarded move-effect lookup, adds the other side's 0x0A
amount into the current 0x1A halfword (including its original narrowing),
then caps the stored result at the current record's HP.

Best source has exact 164-byte size, opcode sequence, frame, and relocation
topology, but nine register words differ: after the move-effect lookup its
base is v1 instead of v0, the amount pointer is a0 instead of v1, and the
cap is a1 instead of a0. Source families tested: typed versus raw subview,
side width, pointer declaration order and lifetime, comparison direction,
compound assignment, explicit cap local, inline view, argument-view reuse,
and explicit discard. A calibrated 60-second native fake-restricted source
search stayed at its initial score; no result was accepted or installed.
Do not change the real `u8 func_80062D20(u8)` return category to free a
register: `src/638E0.c` defines that actual interface.

Next action: capture the allocator decisions around the final discarded
lookup and the rematerialized base, with complete-object controls and a
verified procedure mapping. Resume the retained best source rather than
replaying these closed families. No instruction rewrite, dummy local, or
register forcing is an acceptable final source solution.
