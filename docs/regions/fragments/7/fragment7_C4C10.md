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

`func_8300B504`: `requeue` after sixteen recorded variants. This 72-byte
predicate accepts species 1 through 251 with positive level and low flag bit
clear. Its consumer `func_8300B54C` checks six 88-byte entries in a profile,
clears unusable species slots, and compacts the remaining entries. Straight
byte-mask and byte/word bitfield views produce a 68-byte body: the original
boolean materialization (`sltu`) is absent, and the level branch form also
differs. A named boolean preserves the extent but changes register carriers.
Resume with the boolean-expression lifetime and branch topology; do not add
a dummy local or force a register. The function remains assembly.
