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

### Capped-update trace follow-up

Two passive allocator campaigns and a stock frontend/optimizer stream
capture were calibrated against complete original objects, including
observer-off/on and blank-line controls. The retained parent's procedure
ordinal was explicitly mapped to 22. The base, amount pointer, and HP cap
are assigned internal colors 2/3/4, corresponding to v1/a0/a1. Their
forbidden mask is populated from the terminal block in that retained run:
`updateforbidden` imports the block's `40000000` mask, excluding color 1
(v0). This is measured optimizer ownership, not an assembler guess.

Moving the base later causes address folding and changes the expression
webs; eight genuine sequencing variants retained either the same nine-word
residual or a worse shape. The original C/ABI declarations around the
discarded call and block-mask construction need further investigation.
The callee's real return category was not modified, and no candidate was
installed. These observations apply to the retained parent and toolchain.

## 2026-10-21: four matching HP/amount planners

| Owner | Name | Bytes |
| --- | --- | --- |
| `8414CA80` | `BattleEffects_PlanCalculatedRecovery` | 144 |
| `8414CE08` | `BattleEffects_PlanSharedHP` | 216 |
| `8414EB90` | `BattleEffects_ApplyOpposingByteWeight` | 136 |
| `8414ECE0` | `BattleEffects_HalveAmountsForStatus` | 124 |

The four owners total 620 original bytes. Calculated recovery preserves
the initializer/modifier calls, stores the calculated amount, and caps
half of that amount at missing HP when the opposing record's 0x42 field
is zero. The initializer `func_84149D54` clears exactly 32 bytes and fills
the four pointer fields at 0x10/0x14/0x18/0x1C. This establishes the real
`Fragment79DamageCalculation` record, not an arbitrary stack buffer.
Its amount is at 0x0C; the remaining header bytes stay opaque.

The selected side's interleaved halfword lane is addressed with the
original 32-bit integer byte-address calculation. Pointer-only arithmetic
folds away the separate offset-4 instruction and produces 140 bytes;
the ordinary integer-address spelling reproduces all 144 bytes. Every
scalar and pointer local has an actual arithmetic or addressing role.

Shared-HP planning computes the signed-shift average of the two current
HP values, caps each target at that record's maximum HP, then records
positive or negative deltas in the original amount fields. Real HP locals
recover the addition order; declaration order places the actual saved
Pokemon pointer at stack byte 24 in the 40-byte frame. No dummy local or
padding is used to obtain either home.

The byte-weight helper preserves the existing `s32` address interface and
computes `own_byte * (255 - other_byte) / 255`. The real denominator local
is used in both subtraction and division; stock IDO emits the original
division and checks. Status adjustment preserves both record lookups and
halves the two halfword amounts only under the original 0x27 flag mask.

The shared effect view now decodes the established halfword arrays at
0x0E and 0x16. One visible type replaces the two temporary local copies;
all five earlier accepted helpers still reproduce the original object.
Eight complete-original-object controls verify cleanup, shared type
visibility, decoded fields, formatting, naming, and blank-line shifts.
Twenty-four emitted values verify the partial view and calculator layout.
Each accepted transaction immediately froze and independently rehashed
the full changed object, four distinct collateral objects, source, ROM,
ELF, and linked script before further compilation.

### `8414D9B8`: requeue, filtered amount update

A truthful draft preserves the five excluded effect codes, the conditional
0x4C/mode-2 guard, and the opposite-side halfword doubling. The best 184-byte
draft has a 32-byte frame instead of 40 and loses the original explicit
offset-4 subview carrier. Typed/raw views, switch/default and guard forms,
address interfaces, and actual move/mode temporaries were tested without
closing it. Next: trace source-slot and pointer-web lifetimes around the
conditional mode call. Do not add unused frame storage or padding.

`8414CB10` was inspected but not probed: its oracle reads a pointer from
0(sp) without a preceding write in that owner. Reconcile that original
behavior before proposing C; an uninitialized local must not be introduced
merely to obtain matching bytes.

## 2026-10-21: matching move/type response

`8414DB14` is now `BattleEffects_AddMoveTypeResponse`, 324 original bytes.
It receives the existing offset-4 effect view, not the enclosing record.
Under the original move 0x44/0xF3 and opposing move-category conditions,
it retains the opposing record lookup and the 0x08/0x1B two-byte-record
test, adds twice the opposing 0x0A amount into its 0x1A halfword, and sets
bit 2 of the view's first byte only when the supplied side is active.
`func_800630C0` and `func_84155544` both really return `s32`; the latter
tests the record's bytes 2 and 3, rather than an invented flag interface.

Writing the doubled incoming amount first in both sums recovers the
original temporary sequence. The last two differing words were the saved
selected-side byte-lane pointer at stack byte 44 instead of 40. Naming that
real pointer, then reading its move byte at offset 2, recovers the original
home without extra storage. It is read-only in the cleaned C. All halfword
narrowing, calls, fallback behavior, and active-side checks are retained.

The native runner accepted the owner through the authoritative full-ROM
gate. Its first successful gate immediately froze source, the entire changed
object, four distinct collateral objects, ROM, ELF, and linked script; all
nine were independently rehashed before another compile. Eight whole-object
controls cover known/blank sources, extern cleanup, readable source, the
read-only lane, and naming/blank naming. Twenty-four emitted layout values
recheck the existing effect-view and calculator types; neither type's layout
was changed for this owner. Earlier accepted helpers remain byte-identical.

### Remaining owners: updated durable handoffs

- `8414DA70`: requeue. New logging-only observer campaigns passed complete
  original-object controls before interpretation. The `40000000` terminal
  mask is written in `localcolor`, then imported by `updateforbidden` before
  global allocation. The producer is a fixed-register expression for
  register 2, not an assembler decision. Both stock IDO 7.1 and 5.3 retain
  the same nine-word residual; 5.3 also changes unrelated code in the TU.
  Next: follow the fixed-register expression's frontend/Ucode liveness and
  actual declaration lineage. Do not fake the lookup's real `u8` return or
  invent a return interface for this owner.
- `8414CD18`: requeue. A real two-pass calculator draft now has the original
  88-byte frame, calculator at stack byte 40, address lane, body operations,
  and register assignments. The best retained family uses a cached amount
  multiplied by the zero-based hit index plus one; its 156-byte result still
  uses an equality loop exit rather than the original signed comparison.
  Fifty-six genuine accumulation/product, bound, and increment-placement
  forms were tested; a duplicate preflight rejection was not counted.
  Next: capture loop lowering and induction/exit ownership from this parent,
  rather than repeat the earlier source spellings or add frame filler.
- `8414D9B8`: requeue. Eight further integer-address view spellings did not
  fix the original frame/home difference. Resume pointer lifetime/source-slot
  tracing around the conditional mode call, not more literal view casts.
- `8414DC58`: requeue. Preserve its existing `s32` address interface, both
  record lookups, HP gate, sparse effect switch, and conditional calls to the
  newly matched response. The best 316-byte draft has the right frame and
  instruction shape but 22 differing register/home words. Pointer/side/index
  declaration and width families were tested. Next: trace side/other/base
  webs and their cached stack homes around the second lookup and effect call.
  The first void-pointer ABI drafts failed the existing prototype; those
  context failures are not evidence against the source algorithm.

## 2026-10-21: matching residual-damage planner

`8414D348` is now `BattleEffects_PlanResidualDamage`, 468 original bytes.
It preserves both record lookups, all status/record-byte conditions, the
original HP fractions and multiplier, each halfword accumulation, and the
final current-HP override. The observed halfword lanes at view offsets 0x22
and 0x26 are now part of the existing partial effect view. Its 60-byte C
extent and every earlier field offset remain unchanged; it is not a complete
enclosing-state allocation model.

Compound accumulation produces the original operand/temp sequence. The last
two differences were the saved own-record pointer at byte 28 instead of 24
in the original 32-byte frame. Declaring the opposing pointer before the own
pointer recovers that real home. Both records are read-only in cleaned C.
No extra storage, padding, fake interface, or instruction rewrite is used.

Native-runner acceptance passed the full-ROM gate. Its first successful gate
immediately froze and independently rehashed the whole changed object, four
distinct collateral objects, source, ROM, ELF, and linked script. This owner
shares a four-owner, 836-byte batch with the state-query/snapshot helpers in
`fragment79_3C40B0.c`. Fifteen complete-original-object cleanup controls cover
both files; 28 emitted layout values include both new halfword arrays. No
earlier accepted function changed its object bytes.

### Further loop/status/weight requeues

`8414CD18`: fifteen stock complete-object controls calibrated frontend and
optimizer captures for the retained product and incremental drafts. The
product draft's signed frontend loop test becomes equality in optimizer
output, before assembly. Narrow counters reintroduce multiplication/narrowing;
current-versus-next hit roles and constant-first comparisons do not close the
exit. The original 156-byte product draft remains best; resume induction/exit
tracing, not the now-tested width, increment-placement, or comparison families.

`8414EA4C`: requeue. Two batches preserve both record calls, move-code groups,
selected-side guard, flag masks, and the discarded effect lookup, but produce
a 40-byte frame instead of 48. Shared versus branch-local views and address/
guard spellings do not fix it. Next: trace actual pointer/source-slot lifetimes;
do not add an unused record pointer merely to fill the frame.

`8414D720`: requeue. The truthful draft retains both records, lethal-amount
gate, selected/active-side checks, two signed divisions, narrowed byte weight,
minimum-one behavior, conditional queries, and original HP amount stores.
The existing `s32` address and real `u8` callee arguments are preserved.
Thirty-two expression, old-weight, scope, store-order, index-width, and call-
sequencing variants did not close it. A 496-byte/64-byte-frame spelling reaches
0.9839 normalized similarity but only about 0.34 raw: it is not a match.
Next: trace side/other/base carriers and expression/stack ownership around the
second record lookup and the conditional calls before more source variants.
