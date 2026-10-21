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
