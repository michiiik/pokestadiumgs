# Fragment 79 selected-move state

## Accepted selected-record copies and move effects

Three owners, 484 original bytes, accepted through the recorded native runner
and authoritative byte-identical full-ROM gates:

- `84155A44` / `BattleMoveState_CopySelectedMoves` (128B).
- `8415623C` / `BattleMoveState_RefreshSelectedMoves` (128B).
- `84155BD4` / `BattleMoveState_ApplySelectedMoveEffects` (228B).

Both copy owners retain the selected-record byte at side-state offset0xA,
0x132-byte side stride, 0x18-byte record stride, and four bytes copied from
selected record offsets0x13..0x16 to current offsets3..6. Ordinary zero-based
C loops produce the original checks through stock IDO; no manual unrolling.
Building the selected pointer in separate real pointer-add steps recovers the
observed operand order. The refresh spelling is called after the per-record
refresh loop; the other copy is called from the battle-state update path.

The effect owner preserves the real byte-returning effect lookup, both selected
record reads, sparse effects0x59/0x90/0x62, flag updates4/8/0x10, and the final
four-byte-argument continuation call. Declaring the real selected/opposing bytes
in that order puts the opposing byte at its original stack home. No dummy local
or fake return interface is needed.

First-success callbacks froze the changed whole TU object, four distinct
collateral objects, source, ROM, ELF and linked script; each artifact was
independently hashed before another compile. Eight complete-original-object
controls cover accepted source, blank-line stability, extern deduplication,
unused extern removal, and evidence-backed names with address aliases. These
controls include every previously accepted neighbor, not just the new owners.

## Slot updater: requeue

`84155CB8` remains assembly. Twenty-four genuine forms preserve the unconditional
selected-record lookup, slot<4 guard, move lookup, both stores, and effect call.
The best cached-base forms are168B versus original164B; the side-pointer index,
slot and move carriers differ from the first dozen instructions. Introducing a
real widened slot local, guard return, separate record pointer, and reusing the
consumed slot argument for the move did not close the residual. No draft was
installed. Next: calibrated argument/slot lifetime trace before more variants;
do not force registers or add unused locals.

Other owners retain their assembly; jump-table dispatchers require layout
preflight before attempting C switches.
