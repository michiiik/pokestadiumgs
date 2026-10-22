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

## Move accuracy, hit obstacles and stealable-item scoring

Four more original owners, 688 bytes, are replaced by genuine C:

- `84150268` / `BattlePlan_UpdateMoveAccuracy` builds the 12-byte context
  initialized by `func_8414A180`, applies `func_8414A144`, and writes the
  adjusted accuracy byte to plan offset 10 plus side. The initializer clears
  exactly 12 bytes, reads base accuracy through `func_80062DD4`, and writes
  the two record pointers at offsets 4 and 8. Declaration order of the move,
  entry and context recovers the original frame without extra locals.
- `84152600` / `BattlePlan_AddStealableItemBonus` requires an empty own item
  slot and an opponent item accepted by `func_80063754`. The same predicate
  guards the actual item transfer in `func_8412DC20` in
  `src/fragments/79/fragment79_393CA0.c`. It marks the side byte, adds table
  byte 53 times `func_8414A2AC` to the side score at offset 56, and sets the
  plan flag. An integer header base initialized before the guard and a direct
  word-array field view preserve the address transition and 56-byte frame.
- `84152D6C` / `BattlePlan_CountHitObstacles` counts own record byte 18 below
  7 and opponent byte 19 above 7, then adds two when the opponent has type 8
  and the own move list passes `BattlePlan_HasOnlyNormalOrFightingMoves`.
  `func_84149F74` in `fragment79_3B7EA0.c` passes those same two stage fields
  to accuracy adjustment `func_84124410`. The result is a weighted obstacle
  count, not a hit probability. The previously documented move-power getter
  address-test bug remains in the called predicate. Declaring the consumed
  byte count before the two record pointers preserves the original homes.
- `84152E10` / `BattlePlan_AddHitObstacleBonus` skips opponent byte 21 bit 8,
  marks the side byte, and adds the obstacle count times table byte 57 times
  `func_8414A2AC` to the side score. Its consumed header and side-score views
  retain offset 52 in the memory operand. The flag's precise meaning remains
  unresolved.

The active-record getter is defined as `u8 *func_84154B64(u8)` and the type
predicate as `s32 func_84155544(u8 *, u8)` in `fragment79_3C40B0.c`.
Nineteen stale getter prototypes and two predicate prototypes now use those
real interfaces. Four callers (`84151B8C`, `8415220C`, `84152764`, `8415335C`)
also drop a redundant argument mask: the byte parameter already performs
that conversion. Correcting the getter prototypes alone changes those four
callers; correcting the prototypes and removing the masks together preserves
the entire original object, including leading-blank controls.

Each owner has a recorded runner acceptance and passes the ordinary,
host-syntax-checked full-ROM gate. Three probes are directly link-verified.
The obstacle-count probe instead needs the sequential gate because its call
to the newly compiled local predicate changes relocation representation;
the linked retail bytes and complete original object still agree. Every
first success freezes the complete changed object, four collateral whole
objects, source, ROM, ELF, linked script, layout inputs and original ASM;
external hashes are checked before further compilation. No fake locals,
forced registers or frames, padding, instruction rewriting or manual
unrolling is used.

`84150330` is a requeue at 128 bytes with two raw instruction differences:
the final ADDU and SH use `t2` instead of `t4`. Declaration order fixes the
state spill at offset 24. Header-base forms add an offset mismatch; separate
old-score carriers worsen allocation; explicit narrowing and accumulation do
not close the two-word residual. A calibrated stock/off/on/blank UGEN trace
preserves complete-object identity and identifies the sum's temporary-pool
allocation. A bounded source-only search remains flat. Next compare the
emission/free events of a materially different field-expression topology;
retain ASM rather than forcing a register.

## Leech Seed, Heal Bell and Perish Song option scoring

Three more original owners, 768 bytes, are replaced by genuine C. The effect
dispatcher `84153E28` indexes `jtbl_8418C198` by move effect minus one.
Its entries 84, 102 and 114 route to the three owners below. The local move
metadata used by `func_80062D20` independently maps moves 73, 215 and 195 to
those effects; move 182 has effect 111, the Protect follow-up tested here.

- `84151F9C` / `BattlePlan_AddLeechSeedBonus` rejects opponent record byte 24
  mask `0x90` and type 22, marks the plan's side byte, and adds table byte 19
  times `func_8414A2A0` to its score. An own move with effect 111 adds the
  same amount again. A consumed integer header base initialized before the
  guard preserves the saved-register lifetime and original 64-byte frame.
- `8415252C` / `BattlePlan_AddHealBellBonus` tests the party-condition helper
  with mask `0xFF` or own record byte 23 bit `0x80`. It marks the plan flag
  and side byte, then adds table byte 52 times `func_8414A2AC` times the
  existing `841524B4` party count. The helper `84154B9C` consumes a byte side
  and a halfword mask; its original ASM confirms both argument widths.
  The header base's lifetime across the guard recovers the 56-byte frame.
- `84152EE8` / `BattlePlan_AddPerishSongBonus` checks opponent byte 21 bit
  `0x10` and own header byte 9, then adds table byte 58 times
  `func_8414A2AC`. Opponent header byte 9 equal to one adds three more times
  that amount; an own effect-111 move adds one more. The precise meanings of
  the header counts and flag remain limited to these inspected operations.
  Removing the ephemeral opponent pointer and using a consumed side index,
  header, amount and table recovers the original frame. The reverse-side
  lookup uses a signed scaled byte displacement from `D_841951FC`, the
  second side slot. Scaling before negation preserves the two original
  instructions that array-negative indexing emitted in the opposite order.

All three have recorded, directly link-verified runner acceptances and pass
the ordinary host-syntax-enabled full-ROM gate. Their complete original
66-function object and four collateral whole objects agree. Every first
success freezes the source, objects, ROM, ELF, linked script, layout inputs
and original ASM; external hashes are checked before further compilation.
The changes use no dummy locals, forced registers or frames, padding,
instruction rewriting, or manual unrolling.

The `841524B4` requeue now includes eight typed-record-origin controls. All
retain the same 120-byte, 14-word residual, including the missing row alias.
Record type and count declaration order do not explain it. Next compare the
alias web before and after induction rewriting; another width/cache grid is
not supported by these results.

## Rain Dance, Sunny Day and stage comparison

Three owners, 1,040 bytes, now have directly link-verified runner acceptances
and pass the normal host-syntax-enabled full-ROM gate. The complete original
66-function object remains identical, including independent linkage of all
19,440 retail text bytes and leading-blank controls. Their original-address
aliases preserve ASM callers. These results extend native revision
`a2730070`; 23 ASM owners remain in this source file.

- `841537FC` / `BattlePlan_AddRainDanceBonus`: move 240 has effect 136,
  whose dispatcher entry reaches `.L841547C0`. Unless weather byte 408 is
  already 1, table byte 43 times `8414A2B8` contributes for an own powered
  Water move, incoming Fire move, and own Thunder move 87. Half the signed
  amount is always added within that weather guard, with C division's
  toward-zero rounding. The side byte is marked and plan flag 2 is set.
- `84153930` / `BattlePlan_AddSunnyDayBonus`: move 241 has effect 137,
  dispatched through `.L841547D0`. Weather 2, table byte 42, own Fire moves,
  incoming Water moves and SolarBeam move 76 form the corresponding tests.
- `84153B10` / `BattlePlan_HasUnfavorableStages`: the seven stage bytes at
  record offsets 13 through 19 are compared with neutral 7. Any own stage
  below 7 or opposing stage above 7 returns true. The source is a loop;
  IDO generates the observed unroll. Consumer `84153CB8` belongs to move
  244 / effect 143, dispatched through `.L841547F0`, and scores positive
  opposing-minus-own stage differences.

The rain scorer's four-word spill residual was caused by the score-address
carrier. Forty earlier spellings and eight phase-reuse variants did not
close it. Eight stock/off/on/blank complete-object controls calibrated an
all-procedure passive trace: spill planning reserved header and score-address
temporaries at -28 and -32; later temporary allocation selected -32. A typed
header with direct score-array access removes the separate score-pointer
carrier and reproduces offset 44 in every original spill/reload. The same
source shape matches the sun scorer on its first tested candidate. Shared
partial record views describe only the accessed fields; unknown ranges
remain unnamed. The stage predicate also needs the consumed loop index
declared before its two record pointers to recover the original stack home.

The default permuter comparison ignores stack offsets: its zero for the
rain residual was not an exact match. `--stack-diffs` exposes score 16; the
bounded 45-second source search was flat. No forced compiler, dummy locals,
padding, instruction rewriting or manual unrolling is used. First successes
freeze source, complete objects, ROM, ELF, linked script, layouts and original
ASM; external hashes are checked before any further compilation.

## Psych Up scoring and resisting move slots

Two more genuine matches, 400 bytes, extend native revision `0895b6c2`.
That batch left 21 ASM owners in this file.

- `84153CB8` / `BattlePlan_AddPsychUpBonus` resolves the previous requeue.
  Initializing the consumed header address before the active-record lookups
  recovers the separate final ADDIU and original 72-byte frame. The same
  seven-stage loop adds only positive opposing-minus-own differences through
  `84150B14`, passing move 244, slot `0xFF`, stage index and difference.
  Move 244 has effect 143, routed through `.L841547F0`. The ordinary full-ROM
  gate accepts the result; the isolated probe requires a sequential gate
  because the call to the newly compiled local stage predicate changes its
  relocation representation. Canonical whole-object comparison and an
  independent retail link verify the resolved destination and every byte.
- `841514F8` / `BattlePlan_CountResistingMoveSlots` checks four own move
  slots with `84151420`. For each eligible move, it tests
  `80063454(incoming_type, own_move_type, own_move_type, 0) < 10` and counts
  the slot in a byte. `80063454` in `src/63CF0.c` computes type effectiveness
  with neutral 10; passing the same defending type twice applies its table
  entry once. The original ADDU operand order requires unsigned byte-address
  provenance for the move-list read. Initializing the count before the
  record getter preserves the original saved-register schedule. This probe
  is directly link-verified and passes the normal full-ROM gate.

The helper's consumer `841515AC` is the Conversion scorer: local move 160
has effect 30, dispatched through `.L84154528`. It uses a planned opponent
move or `84148C74` fallback, then multiplies the resisting-slot count by table
byte 48 and `8414A2AC`. The helper name describes counted slots, including
duplicate move types, rather than distinct types.

Both first-success gates freeze complete objects, source, ROM, ELF, linked
script, layouts and original ASM before any further compilation. Six native
complete-object controls, including leading blanks and ABI checks, preserve
all 66 original extents; nine independent links reproduce all 19,440 retail
text bytes. No fake locals, forced registers/frames, padding, instruction
rewrites or manual unrolling are used.

## Conversion, Mimic, flinch and Curse scoring

Four more genuine matches, 1,020 bytes, extend native revision `2fefe5be`.
This batch leaves 17 ASM owners in the file. The original-address aliases
preserve callers that remain in ASM.

- `841515AC` / `BattlePlan_AddConversionBonus` resolves the Conversion
  requeue. Move 160 has effect 30 and dispatches through `.L84154528`.
  A planned opponent move, or the `84148C74` fallback, supplies the type for
  `BattlePlan_CountResistingMoveSlots`. The byte count times table byte 48
  times `8414A2AC` contributes to the side score. An early header base and
  consumed byte temporaries retain the original 48-byte frame. The decisive
  source expression is `other_side = 1 - side`: normal integer promotion
  before narrowing to a byte reproduces the original register and mask
  sequence. The previous `(u32)side` subtraction created a different
  conversion expression and an extra mask in the byte-carrier variants.
  The existing two-argument interface remains intact.
- `84151E44` / `BattlePlan_AddMimicBonus`: move 102 has effect 82 and
  dispatches through `.L8415461C`. The opponent's recorded move at byte 36
  must be nonzero, differ from Struggle 165, and be absent from all four own
  move slots. Table byte 62 times `8414A2AC` is added to the side score. An
  early header base preserves the separate address increment. Removing the
  separate score-pointer carrier, and declaring the consumed header before
  the amount, recovers the original 64-byte frame and spill homes.
- `8415169C` / `BattlePlan_AddFlinchBonus`: effect 31 (Headbutt 29, Bite 44,
  Rock Slide 157) routes through `.L8415454C` with a chance byte. Effect 141
  routes through `.L84154538` with `0xFF`. Opponent byte 24 mask `0x10` and
  halfword 38 mask `0x27` reject the bonus, as does a false action-order
  predicate `8414C858`. Its ASM compares move priority, then the two records'
  halfwords at offset 66. Table byte 17 times `8414A288` times chance,
  divided by 255, contributes to the side score. Direct typed-header access
  avoids the extra spill slot introduced by a separate score pointer.
- `84152980` / `BattlePlan_ScoreCurse`: move 174 has effect 109, dispatched
  through `.L841546FC`. An own Ghost type (8) selects the guarded branch
  that replaces the side score with table byte 22 times `8414A2AC`; this is
  an assignment, not an addition. Otherwise the two `84150B14` calls use
  stage indices 0 and 1, and `84150EA4` receives the opposing side and index
  2 so its opposing-target adjustment applies to the user's own record.
  An early header base and signed-promoted byte side complement preserve
  the original 64-byte frame and shared spill lifetime.

The Conversion investigation retains the earlier 32 rejected candidates and
eight stock/off/on/blank frame/allocation controls. Eight further calibrated
expression-construction controls preserve the complete parent object and
confirm that its side complement is emitted into `v0`. The following
eight-candidate signed-complement family accepts its first candidate. This
is evidence about this function's conversion expression, not a general rule
that all side subtraction must be signed.

All four have recorded runner acceptances and pass the normal,
host-syntax-enabled full-ROM gate. Mimic, flinch and Curse are directly
link-verified. Conversion uses a sequential gate because the call to its
newly compiled local counter changes relocation representation. Every first
success freezes complete objects, source, ROM, ELF, linked script, layouts
and original ASM, with external hashes checked before further compilation.
Six complete-object controls, including cleanup/naming, leading blanks and
ABI checks, preserve all 66 original extents. Eleven independent links
reproduce all 19,440 retail text bytes. No fake locals, forced registers or
frames, padding, instruction rewrites or manual unrolling are used.

The party-count `841524B4` and entry-hazard `84150330` requeues remain
unresolved, together with the other remaining ASM owners. The near-match
evidence for those functions above still applies; this batch does not
install either body or claim that the file is complete.

## Party-count copy-propagation checkpoint

`841524B4` remains a requeue on native revision `e6d5a853`; its best retained
candidate is still 120 bytes with 14 raw differences. Forty further source
candidates reject. The five eight-candidate families cover consumed-header
reuse, positively guarded byte extents, mixed array/byte-address row origins,
an independent global-header bound, and a consumed integer row-address value.
Header reuse triggers unwanted unrolling in the record-count forms. The
other forms produce 124--140-byte loops or retain an extra loop-carried
pointer; none recovers the original per-record copy and register ownership.
No candidate is installed and no compiler modification is used for matching.

Two corrected logging-only observers pass sixteen fresh stock/off/on/blank
complete-object controls, covering the known matching module and the exact
retained candidate object. The first observer's empty capture was rejected:
the active CFG head is at compiler VM address `0x1001C358`, while
`0x1001C360` is a traversal cursor. The corrected snapshots capture all 32
candidate statements without truncation; both leading-blank controls agree.

The assignment `row = party[i]` is statement 14, tied to retained source
line 418 by the preceding location record. It survives loop-unroll handling
with statement word `0x7B000000`, then becomes `0x60000000` immediately
across `f_copypropagate`. The earlier party-base assignment, statement 4,
changes in the same pass. The row assignment is already eliminated before
`f_findinduct` and `f_eliminduct`, so another induction-only loop-spelling
grid does not target the measured cause. This identifies the owning pass
for the retained candidate, not an impossibility proof for genuine C.

Next inspect the copy-propagation eligibility and expression identity of
those two assignments, then test a source-level distinction supported by
that evidence. Preserve the original one-byte side interface and byte count;
do not add parameters, dead reads, volatile qualifiers or forced registers
to reserve a color or retain the copy.

### Copy substitution and cursor-advance follow-up

Eight additional stock/off/on/leading-blank whole-object controls validate
passive logging inside the copy-substitution helper and final dead-store
deletion. The retained parent's row use at compiler expression `0x10071738`
is replaced by address expression `0x10071AA8`; its party-base uses are
likewise replaced. The final deletion at `L41A188` removes statements 4 and
14 after these substitutions. This separates use replacement from the later
removal of the now-unused assignments; it does not establish the original
source's variable names or expression topology.

Sixteen recorded source candidates test real cursor advances rather than
dead uses: saving `party[i++]` before reading either field yields 124 bytes,
with a copy before the halfword load instead of the original branch-delay
copy. Reading the halfword before the advance, either through a consumed
halfword local or separate guarded advances, produces 132 or 144 bytes.
The original 120-byte, 14-raw-word parent remains best. Both eight-candidate
batches pass known/context/leading-blank controls and install nothing.

`841524B4` remains a requeue. A next hypothesis must account for the copy's
placement as well as its existence; repeating the saved-index cursor forms
or induction-only spellings above is not a new experiment. The passive
observer, retained sources, objects and raw reports stay in private scratch.

## Protect/Detect score allocation checkpoint

`84152AC0` is a requeue on native revision `e6d5a853`. The original move
effect table routes effect 111 through `.L8415470C` to this owner; the
local six-byte move table gives that effect to moves 182 (Protect) and 197
(Detect). It stores `255 >> own[33]` to the side byte at plan offset 12,
scales table byte 55 times `8414A2AC` by that byte divided by 255, then
applies four status-dependent score updates. The individual opposing
status-field meanings remain unresolved.

Fifty-six recorded candidates cover header representation and lifetime,
measured stack-home ordering, real incoming-pointer/chance reuse, a consumed
side-index local, alias-preserving explicit status-byte lifetimes, and
integer-product expression topology. Every eight-candidate batch passes
known/context/leading-blank whole-object controls. One earlier batch is
refused before compilation because it contains a previously rejected body;
that refusal is not counted as an attempted hypothesis. No body is installed.

The best retained parent is candidate 1 of
`native-f79-plan-status-score-header-lifetime`: 372 bytes, the original
56-byte frame, original stack offsets and relocation topology, and thirteen
raw word differences. Moving the header calculation just after the second
record getter fixes the earlier header-register difference. The remaining
differences are the coherent `a1`/`a2` exchange between the signed bonus
amount and the promoted opposing status-byte load. Integer and typed-header
spellings reach the same residual; normalization reporting 1.0 is not an
exact match.

A calibrated 45-second source-only permuter search improves its own score
from 105 to 65, but its proposed additional side-index local expands the
real frame to 64 bytes. Eight recorded lifetime variants confirm that this
is not an improved project match. Removing that local and isolating the
header-lifetime move produces the thirteen-word parent above. The returned
edits were reviewed for initialized uses and integer arithmetic before
testing; no forced code or compiler output is adopted.

Sixteen fresh stock/off/on/leading-blank whole-object controls validate
normal allocation logging and semantic-web tree logging against the exact
retained parent, with procedure ordinal 53 in both captures. Bonus web 31
is the signed local at virtual slot -20; it receives physical register 5
(`a1`). Web 66 is a promoted byte-load tree rooted in the opposing record
at virtual slot -12 and receives physical register 6 (`a2`). Both have
reported save priority 2, with the bonus processed first. The explicit-byte
and staged-product families do not improve the parent. Next inspect the
priority/tie ordering of these two genuine webs before another source
family; changing declaration order alone already failed to affect the
initial rotation. Preserve the alias-sensitive status rereads after score
stores, signed division and right shift, and the original two-argument ABI.

Eight further whole-object controls validate passive logging at the actual
allocation scan. Both competing webs are eligible with identical priority
bits `0x40000000` in rounds 1--5. The scan walks web indices in ascending
order and updates its winner only for a strictly greater priority. In round
5, web 31 replaces incumbent web 19; web 66 then ties it and is skipped.
These indices are the scan's work-list indices, distinct from the expression
hash bits printed by the earlier color receipt. Thus the tie is measured,
not inferred from rounded final priorities. Eight typed-record/field-access
candidates retain exactly the same thirteen-word residual, despite covering
typed own/opposing record pointers and direct/cast status-field accesses.
No body is installed. A successor must change real web construction or cost
without dummy reads or forced colors; another record-field spelling grid
does not address this measured first-wins scan.

## Accepted Rampage score bonus

`84151270` / `BattlePlan_AddRampageBonus` replaces 188 original bytes with
genuine C. The local six-byte move table assigns effect 27 to Thrash (37),
Petal Dance (80) and Outrage (200); the effect dispatcher reaches this owner
through `.L84154508`. With snapshot byte 3 bit 4 clear and the original
getter-result guard passing, it marks the side's byte at plan offset 12 and
adds table byte 18 times `8414A2A0` to the score word at offset 56.

The original guard stores `func_80063660(sub[1]) != 25` into a byte, then
tests that Boolean against 0, 16 and 15. The latter two tests therefore
cannot filter the getter's values; the C preserves this behavior and marks
it with `//!bug`. The exact meaning of those getter codes is not asserted
here. Its declaration is corrected to the `u8` return type of the definition
in `src/641E0.c`; whole-object controls prove the existing caller remains
unchanged. Four newly redundant declarations are removed within this file.

An early, consumed header base recovers the original 56-byte frame and
188-byte instruction sequence. Declaring the real table pointer before the
one-byte multiplier moves that multiplier from stack offset 39 to original
offset 35, resolving the final two word differences without dummy locals,
padding, volatile qualifiers, forced registers or instruction rewriting.
The runner accepts the first candidate of that measured layout family,
directly verifies its link shape and passes the ordinary host-syntax-enabled
full-ROM gate. Source, complete object, four collateral objects, ROM, ELF,
linked script, layouts and original ASM are frozen and externally hashed
immediately after the first successful gate, before another compilation.

Six additional full-module controls cover cleanup, naming, leading blanks
and ABI widths; eight independent links reproduce all 19,440 retail text
bytes and preserve all 66 original function extents. Sixteen ASM owners
remain in this file. The Protect/Detect and party-count checkpoints above
remain unresolved; no diagnostic tooling or rejected candidate is published.

## Accepted Haze scoring

On native revision `e4057715`, `84151128` accepts as 328 bytes of genuine C.
Move 114 has effect 25 in the local move table, whose dispatcher entry is
`.L841544F8`, so the intended name is `BattlePlan_ScoreHaze`. It inspects
both sides' seven stage bytes: above neutral 7 it invokes `84150EA4` through
the opposite side, and below neutral it invokes `84150B14` through the same
side. Both helpers receive move 114, chance 255, the stage index and its
distance from neutral. It then marks the requested side and plan bit 2.
This evaluates the move's score; it does not directly reset battle stats.

Independent record pointers strength-reduce into two extra saved pointers
and produce the wrong loop. A real two-element record-pointer array keeps
the original adjacent pointer homes at stack offsets 48 and 52. An early
header base restores the original tail address formation. These changes
leave only a 56-versus-64-byte frame difference. Two distinct signed stage
locals, each initialized from its side and consumed by that side's guards
and helper arguments, declared before the pointer array, reproduce the
original frame and all instruction words. No variable is unused, no array
is oversized, and no padding, forced register, volatile access or manual
loop unrolling is used.

The first three eight-candidate families reject; the fourth accepts candidate
3 after three rejected layouts. All four batches pass known/context/leading-
blank full-object controls. The acceptance is directly link-verified and
passes the ordinary host-syntax-enabled full-ROM gate. Its first-success
source, entire module object, four collateral objects, ROM/ELF/linked script,
layouts and original ASM are frozen and externally hashed before further
compilation. Independent verification confirms all original module extents,
the unchanged collateral objects and preserved foreign edits.

The retained first-success receipt is `native-f79-plan-haze-stage-values`.
This owner joins the condition-scoring batch below. The preceding Rampage
batch was published and merged independently as PR #1414.

## Accepted Poison, Burn and Freeze scoring

Together with Haze, three further original owners bring this batch to four
genuine matches and 1,520 bytes:

- `84150538` / `BattlePlan_ScorePoison` (408 bytes): move 40 (Poison Sting)
  has effect 2, which dispatches through `.L84153EF4`; move 92 (Toxic) has
  effect 33, dispatching through `.L84153EE0` with chance 255. After status,
  snapshot, held-item-code, Poison-type and effectiveness guards, the scorer
  adds table byte 13 times `8414A264` times the incoming chance divided by
  255. Toxic adds half again. An own move with effect 111 adds the scaled
  amount again: `841556C4` compares `80062D20` move effects, not move IDs;
  Protect (182) and Detect (197) have effect 111 in the local move table.
  The consumed record view is reused for the later table lookup. Declaring
  the header base before the type byte and amount preserves the original
  spill offset 36. Keeping the Toxic guard and update on one physical line
  recovers the measured shift/constant scheduling order. Wider line layouts
  preserve semantics but retain two differing words.
- `841506D0` / `BattlePlan_ScoreBurn` (424 bytes): Fire Punch (7), Ember
  (52), Flamethrower (53) and Fire Blast (126) have effect 4 and dispatch
  through `.L84153F04`. Table byte 14 supplies the chance-scaled amount. An
  existing opposing status with bit `0x20` marks the side and subtracts the
  amount; other nonzero statuses stop scoring. With no status, the snapshot,
  item-code, type and effectiveness guards gate the score addition and the
  same own-effect-111 bonus. Derived record and score addresses, rather
  than a source-level cursor variable, let CSE share the original pointer
  spill at stack offset 36. The existing generic plan-pointer interface is
  preserved; no argument or return category is invented for allocation.
- `84150878` / `BattlePlan_ScoreFreeze` (360 bytes): Ice Punch (8), Ice
  Beam (58) and Blizzard (59) have effect 5 and dispatch through
  `.L84153F14`. Weather value 2, opposing capability bit `0x20`, status,
  snapshot, item-code, type and effectiveness guards precede table byte 15
  times `8414A264` times chance divided by 255. It preserves the original
  absence of a plan-bit-2 write. Placing the consumed cursor before the
  move-type byte gives that byte its original stack offset 47. The opposing
  side is an actual byte local used by both side-indexed helpers.

The three scorers' pointer/amount locals are consumed by real loads, guards,
arithmetic or calls. Eight stock/off/on/leading-blank whole-object controls
validate passive poison-frame logging. Reusing consumed views or changing their
representations alone does not suffice: record/table view reuse, precise
spill homes and the independently measured scheduling relation each have
separate retained controls. No forced frame, dummy read, volatile local,
instruction rewrite, padding or manual loop unrolling is used.

All four acceptances are directly link-verified and pass the normal
host-syntax-enabled full-ROM gate. Every first success freezes complete
objects, source, ROM, ELF, linked script, layouts and original ASM, with
external hashes checked before further compilation. Six full-module
controls cover cleanup, naming, leading blanks and ABI widths. Eleven
independent links reproduce all 19,440 retail text bytes and all 66 original
function extents. Scoped cleanup removes twenty redundant declarations;
diagnostic helpers and rejected candidates stay outside the publication.
Twelve ASM owners remain in this file, including the unresolved party-count
and Protect/Detect allocation checkpoints.
