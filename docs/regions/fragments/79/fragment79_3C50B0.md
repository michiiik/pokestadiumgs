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

## Selected stat refresh: accepted, 2026-10-22

`84155820` is now `BattleMoveState_RefreshSelectedStats`. Its 508-byte body refreshes the selected
record's five staged stats, reduces speed for status bit 0x40 and attack for
bit 0x10, then copies auxiliary byte 1 into each side's selected record.
The helper `func_84125508` has the existing `void(u8 *, u16, u8)` interface.
The record stride is 24 bytes, the side stride is 306, and the five selected
stats are at side-relative offsets 32 through 40 after applying the record
index. The copied auxiliary byte is at record offset 11. Its broader meaning
is still unknown.

The entry masks the side argument to eight bits. Correcting the existing
wrapper's declaration from s32 to u8 preserves the entire original module
under known, corrected and leading-blank controls. Five additional whole-object
controls, including six target-compiler type/offset assertions, verify that
this interface cleanup and the proposed record views leave every existing
function and readonly byte unchanged. At this interface-only stage the source
still has all six original assembly owners; it does not yet install new C.

Forty-eight recorded candidates cover typed record views, signed versus byte
selection carriers, explicit stage-table addresses, byte/halfword stat
addresses, the selected-record address origin and immediate selection
consumption. These are consumed values and addresses, not dummy locals or
instruction rewrites. Known/context/leading-blank controls pass before each
family. The initial attempt to retype an assembly owner's prototype through
`companion_edits` is a refused preflight, not an additional compiler hypothesis.

The best intermediate body is cell 2 of the private
`native-f79-selected-stat-record-origin` batch (cell 6 has the same residual).
Its size and relocation topology match retail. Exactly ten raw instruction
words differ, all in frame allocation/release or stack homes: frame 64
versus 56 bytes, side argument 64/67 versus 56/59, and two spill homes
44/48 versus 40/44. All other instruction words agree after matching
relocation fields are excluded. The ordinary `sizeof(MoveStatRecord)` stride
and typed side-record tail recover the original multiply/address sequence;
flat signed arithmetic does not.

Removing the selection local or narrowing the stat pointer's lexical scope
does not shrink the frame and disrupts other instructions. Preserve the
ten-word parent rather than adopting those variants. A passive frame observer
passes ten stock, observer-off/on and leading-blank whole-object controls
across the known module and this immutable parent. Its target trace reports
a 64-byte frame, 24-byte saved-register area and zero late temporary area.
This narrows the next investigation to earlier reservation/lifetimes; it
does not prove which historical declaration existed. Inspect frontend/optimizer
reservation for the exact parent before another width or scope grid. Do not
fill, truncate or patch the eight-byte frame difference.

The byte-interface-only cleanup passes the normal full-ROM gate with MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Its callback freezes thirteen complete
objects plus source, ROM, ELF and linked script; all seventeen snapshots
are independently hashed before further compilation. All 76 native tool
tests pass. This is verification of neutral cleanup, not acceptance of the
near-match, and generated coverage is unchanged.

### Composed pointer lifetimes resolve the requeue

Eight subsequent global-base-expression candidates remove the source-local
side pointer. The best has the correct 56-byte frame and its first 244 bytes
of instruction words agree after relocation fields are excluded, but two
required pointer-table reloads disappear
from the later status updates. This is useful partial evidence, not an
accepted 500-byte substitute for the original 508-byte function.

The selected-stat address is dead after the five stage-helper calls. Reusing
that real pointer as the side-stat base for the two status updates gives
both the correct reservation and the original memory-access sequence.
Cell 0 of `native-f79-selected-stat-phase-pointer` is directly link-verified
and accepted by the normal full-ROM gate. The compiler warning about prior
repeated drift is a ranking signal; it does not invalidate this distinct,
source-level lifetime hypothesis. No unused local, forced register, fake
prototype, manual unrolling, padding or instruction/relocation rewrite is used.

The first successful comparison immediately freezes source, the complete
changed object, four distinct collateral objects, ROM, ELF and linked script.
Every hash is independently checked before more compilation. Six subsequent
whole-original-object controls cover the first acceptance, leading blanks,
extern deduplication, redundant-cast removal, readable pointer names, the
semantic function name and six target-layout assertions. All sections,
function extents and semantic relocations match the original module.
The original-name linker alias accompanies the renamed address-map entry.

The final named normal full-ROM gate also passes with the same retail MD5
and freezes seventeen artifacts before returning. Five assembly owners remain
in this module. The separate geometry source-shape requeue remains unresolved;
this match is not completion of either the module or the project.

## Best-power move scan: accepted, 2026-10-22

`func_84155DB4` is now `BattleMoveState_FindStrongestMove`. It scans four slots, selecting from the
active-side move table or the saved current-move bytes. It ignores move
0xFF, filters by `func_800630C0` according to category 0 or 1, and keeps a
move only when its power exceeds the running value initialized to 1. The
retail path calls the power getter twice on an improvement; both calls are
preserved. Its real power getter returns u8, and the running power is u16.

The initial eight switch/if-else, loop-bound and move-width variants include
a 380-byte switch body versus retail's 372. Its category argument is cached
in a saved register, whereas retail reloads that byte from its argument home
inside the loop. The if-else family retains that reload but lowers a different
branch topology and hoists the move-table base. These are separate measured
differences, not merely interchangeable register names.

Eight more candidates add a consumed per-move category snapshot, test the
equivalent missing-move continue guard and reverse the equality operands.
All pass known/context/leading-blank whole-object controls; none accepts.
Snapshot widths and equality order collapse to identical compiler outcomes;
the continue guard yields 376-byte bodies but still changes control flow and
table-base lifetime. Do not count those equal outcomes as distinct progress.
The previously accepted stat-refresh body remains installed and unchanged.

The initial handoff routes to calibrated optimizer web/lifetime diagnostics
for the category argument and move-table base on both retained parents.
The sixteen attempts and raw diffs are preserved as process evidence; the
resolution below adds neither a volatile argument, dummy local, forced
register nor an altered getter signature to prevent promotion.

### Typed record indexing and the reviewed source-search result

The passive optimizer observer passes fifteen stock, observer-off/on and
leading-blank whole-module controls across the known module and both scan
parents. The historical parent's sole helper-binding difference is inspected:
an undefined old-name call and a local call at text offset 948 both resolve
to `0x84155BD4` through the existing alias. Canonical relocation comparison
accounts for that equivalence; no object or instruction is patched.

The switch's frontend IR introduces a promoted selector temporary, whereas
the if-else source reloads its byte argument but lowers a different branch
topology. Equality guards, alternative dispatches, promoted value roles and
conditional move expressions do not resolve both differences. Both authentic
stock C drivers are calibrated on their known complete objects and blank
controls. IDO 7.1 and 5.3 reproduce the same retained switch and if-else
residuals; 5.3 also changes the current module's complete fingerprint. This
negative covers those parents and drivers, not every legal source/frontend.

Indexing the saved moves through the real 306-byte side record recovers the
original frame, instruction count and memory/control-flow shape. The four
current-move bytes occupy offsets 3..6, as independently established by the
accepted copy routines and this function's GS loads. The earlier view that
placed a four-byte member at offset 2 is corrected without changing any
already accepted instruction. Five whole-object controls, six target-layout
assertions and a normal ROM gate verify that field-only cleanup. Unknown
record bytes retain address-based names; the copied byte at offset 11 is
`unk_0B`, whose broader meaning remains unresolved.

The typed-view parent has ten register-operand word differences. Its reduced
permuter input reproduces all 93 instruction words and relocation topology
of the immutable full-module candidate before search. A bounded ninety-second
native search excludes fake, ABI and type mutations. The reviewed improvement
only reverses the symmetric side equality and moves the consumed power
declaration before the result declaration. It introduces no new operations,
unused locals, forced registers, padding, manual unrolling or output rewrites.

The search's nonzero score is not acceptance. The recorded runner accepts
the reviewed source only after its normal sequential full-ROM comparison.
The isolated object references `D_8419EE00 + 3` where the oracle references
the equivalent `D_8419EE03`; the probe therefore has relocation masking and
is not directly link-verified. The successful callback immediately freezes
the changed whole module, four collateral objects, source, ROM, ELF and linked
script, with external hash checks before further compilation.

Independent unmodified-linker checks resolve all undefined symbols from the
actual linked ELF and compare every one of the module's 4096 text bytes to
retail. Original, first-accepted and six fresh whole-object controls pass,
including readable field accesses, naming, leading blanks and target layout.
All 26 function starts/extents are preserved. The address-map name has an
original-name alias. The final named normal ROM gate passes and freezes
seventeen artifacts; four assembly owners remain in this module.

## Current two-owner batch

The new matches total 880 bytes: selected stat refresh (508) and strongest
move selection (372). Both keep the real getter interfaces and all observable
calls. The full-ROM MD5 remains `1561c75d11cedf356a8ddb1a4a5f9d5d` and all
76 native tool tests pass. Scratch experiments and generated coverage remain
outside the change.

Remaining owners are `func_84155AC4`, `func_84155CB8`, `func_84155F28` and
`func_841562BC`. The two dispatchers need their per-file jump-table readonly
subsegment before C switch candidates. The move-slot requeue above and the
separate ten-vertex geometry requeue remain unresolved; this batch does not
complete the file or project.
