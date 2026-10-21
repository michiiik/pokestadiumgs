# Fragment 7 record-bank helpers

## 2026-10-21: four matching initialization/provider helpers

The native runner accepted four owners as one full-ROM-gated batch:

| Owner | Name | Bytes |
| --- | --- | --- |
| `8300AA58` | `Fragment7_InitializeRuleBank` | 124 |
| `8300AEEC` | `Fragment7_InitializeTeamBank` | 124 |
| `8300B284` | `Fragment7_LoadTeamBank` | 152 |
| `8300B330` | `Fragment7_InitializeProfileBank` | 120 |

All three banks have the same four-byte word-sized bitfield header: eight
capacity bits, eight count bits, the expanded-bank flag, a two-bit source
selector, and thirteen remaining flag bits. Their physical arrays contain
eight 68-byte rules, six 1168-byte teams, or eight 544-byte profiles. The
initializers clear the complete bank and set capacities 5/8, 3/6, or 1/8
depending on the expanded flag. Rule initialization also clears unused
record slots through `func_8300A9E0`.

The team loader opens provider 25 for an expanded bank, or provider 39 with
the source selector for the other bank. It reads at most the bank capacity,
stores the returned count, and closes the handle. `func_8006218C`,
`Deck_ReadEntries`, and `func_80062304` in `src/615D0.c` establish the handle
and entry-reading operations. The initialization sequence in
`Fragment7_InitializeRecordCollections` in `fragment7_BA250.c` establishes the three
bank roles and which copies receive the expanded flag.

Capacity assignment as a conditional expression matches the original
constant scheduling. A word-sized bitfield gives the original field loads
and masked byte stores. The public functions preserve their existing
`void *` interfaces; explicit bank views preserve the original object,
whereas adding local pointer aliases changes it. No padding, unused local,
forced register, altered argument count, or instruction rewrite is used.

The first successful gate froze and independently hashed the complete changed
object, four distinct collateral objects, source, ROM, ELF, and linked
script before further compilation. Eight complete-original-object controls
verify declaration cleanup, removal of probe-only types, canonical type
names, compatible interfaces, function naming, and blank-line shifts. Ten
emitted layout values verify header/bank sizes, record offsets, and strides;
two emitted header words verify the bit positions (`1234C000`, `00006000`).

## 2026-10-21: five matching provider and validity helpers

| Owner | Name | Bytes |
| --- | --- | --- |
| `8300ADA4` | `Fragment7_SaveRuleBank` | 156 |
| `8300AE40` | `Fragment7_LoadRuleBank` | 152 |
| `8300B1CC` | `Fragment7_SaveTeamBank` | 148 |
| `8300B504` | `Fragment7_IsValidProfilePokemon` | 72 |
| `8300B818` | `Fragment7_SaveProfileBank` | 148 |

The I/O helpers reuse the verified header. Rule providers are 24/38, team
providers are 25/39, and profile writers use 27/40; the expanded flag picks
the first provider, while the two-bit source selector chooses a controller
for the second. The helpers pass open mode 0 for reads and 1 for writes.
Reads request the bank
capacity and store the returned count; writes supply the current count. All
successful opens are closed through `func_80062304`. Rule saving first clears
unused slots through `func_8300A9E0`.

`Deck_ReadEntries`, `Deck_WriteEntries`, and the provider open/close functions
in `src/615D0.c` establish these operations. Initialization calls the rule
loader, and `func_83009EC4` calls the three writers when collections change
relative to their snapshot. The four I/O interfaces remain `void *`; no call
arity or return-type changes are needed.

The validity predicate accepts species 1 through 251 with positive level and
low flag bit clear. Its consumer `func_8300B54C` checks six 88-byte entries in
a profile, clears unusable species slots, and compacts the remaining entries.
The earlier requeue is resolved: an inline nonzero flag test compared with
zero retains the original `sltu` and subsequent branch topology. Logical
negation folds away that conversion and produces 68 bytes instead of 72;
named booleans change register carriers. The accepted expression uses no
dummy local, identity arithmetic, padding, or register forcing.

The native runner accepted the I/O helpers together, then the predicate in a
separate full-ROM-gated transaction. Each first-success gate froze and
independently rehashed the complete changed object, four distinct collateral
objects, source, ROM, ELF, and linked script before another compilation.
Eight further complete-original-object controls cover declaration cleanup,
profile type naming, handle initialization, readable call formatting,
function naming, and blank-line shifts. Fifteen emitted layout values cover
the bank layouts and the 88-byte profile entry, including species at 0,
level at 29, flags at 30, and payload at 32. The two emitted header words
still verify the flag positions.

## 2026-10-21: five matching record removal/swap helpers

| Owner | Name | Bytes |
| --- | --- | --- |
| `8300ABCC` | `Fragment7_RemoveRuleRecord` | 192 |
| `8300B038` | `Fragment7_RemoveTeamRecord` | 164 |
| `8300B0DC` | `Fragment7_SwapTeamRecords` | 240 |
| `8300B468` | `Fragment7_RemoveProfileRecord` | 156 |
| `8300B728` | `Fragment7_SwapProfileRecords` | 240 |

Each removal shifts the following records down with aggregate assignments
and decrements the count. Rule removal also calls `func_8300A9E0` to clear
unused slots; team/profile removal leaves the unused tail unchanged. Each
swap uses three aggregate assignments and one real whole-record temporary.
The compiler emits the original copy loops and the 1176/552-byte swap
frames. There is no handwritten word-copy loop, manual unrolling, padding,
or synthetic temporary.

The byte-sized count is explicitly compared as `s32`, preserving the
original signed `slt` checks. No new lower-bound checks are introduced. All
five public functions preserve their existing `void *` interfaces.

The storage records are now shared by bank arrays, append/replace helpers,
removals, and swaps: 17, 292, or 136 aligned words for the established
68/1168/544-byte payloads. These are opaque serialized storage, not invented
decoded fields. Consolidating the six older per-function copy types and
the new move-only views preserves the entire original game object,
including all previously accepted helpers in this translation unit.

All five owners passed one native-runner full-ROM gate. Its first-success
callback froze and independently rehashed the whole changed object, four
distinct collateral objects, source, ROM, ELF, and linked script before
another compilation. Eight further complete-original-object controls verify
declaration cleanup, shared record/bank types, consolidation of legacy
copy types, readable formatting, naming, and blank-line shifts. Thirteen
emitted layout values verify the record/bank sizes, record offsets, and
strides; the two header words reverify the bit positions.

## 2026-10-21: rule swap, profile loading, and original no-op

| Owner | Name | Bytes |
| --- | --- | --- |
| `8300AC8C` | `Fragment7_SwapRuleRecords` | 280 |
| `8300B260` | `Fragment7_TeamBankNoOp` | 36 |
| `8300B8AC` | `Fragment7_LoadProfileBank` | 220 |

Rule swapping uses the shared 68-byte aggregate and three assignments,
then clears unused rules through `func_8300A9E0`. Its signed count guards
and real record temporary reproduce the original 96-byte frame.

Profile loading first resets the count, opens provider 27 or 40 in mode 0,
reads at most the bank capacity, closes the acquired handle, then calls
`func_8300B54C` on every loaded 544-byte profile. The expanded/source flags
choose the provider just as in the other accepted bank loaders. There is
no processing when acquisition fails, because count was reset first.

`8300B260` really is an empty count-bounded traversal: its original nine
instructions contain no call, memory store, or observable per-entry work.
No caller or data reference was found in the source/split assembly. The
delay-slot increment leaves an incidental register value even for an empty
bank; this is not invented as a C return value. The void function retains
the actual empty loop rather than adding work to force another owner.

All three owners passed one native runner/full-ROM gate. The first-success
callback froze the complete changed object, four distinct collateral
objects, source, ROM, ELF, and linked script; all nine artifacts were
independently rehashed before later compilation. Eight complete-original-
object controls cover cleanup, formatting, documentation, naming, and
blank-line shifts. Thirteen emitted layout values and two header words
reverify the shared storage types.

### `8300B54C`: requeue, discarded aggregate-result stack home

This is the only remaining assembly owner in the file. Its real operation
checks six 88-byte Pokemon at profile offset 16, clears invalid species,
compacts entries with aggregate assignments while clearing moved-from
species, and finally calls `func_8003F5AC` for each remaining entry.
That callee returns a four-byte tint aggregate through a hidden result
pointer; the result is discarded, not an explicit extra source argument.
The accepted consumer in `src/4CC20.c` and callee assembly establish this
ABI. Do not use a made-up eight-byte return type or unused color local.

Seven eight-variant source batches explored search termination, the actual
tint union, declaration ownership/order, real traversal scopes/reuse, and
fixed bounds. Guarding `gap = 1` with `gap < remaining` then using a do-loop
with `gap != remaining` recovers the original search branch and 476-byte
size. The best candidate has the exact frame, opcode sequence, and
relocation topology. Only byte offset 396 differs: `addiu s2,sp,76` instead
of `addiu s2,sp,80` (raw similarity 0.9916). A distinct final-pass counter
places the result at 80 but enlarges the frame to 104, so it is not a fix.
A calibrated 60-second native fake-restricted permuter search stayed flat
at its initial score. No candidate was installed or claimed matching.

Next action: trace the discarded aggregate-result temporary's allocation
and source-lifetime ownership, rather than retrying these closed families.
Do not add padding, forced registers, unused locals, or instruction rewrites.
