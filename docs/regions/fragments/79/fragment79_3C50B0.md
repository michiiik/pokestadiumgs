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

## Per-record refresh: requeue, 2026-10-22

`func_84155F28` remains assembly. Its original 788-byte body copies or masks
four move bytes according to species 202 and opposing-state bit 0x8000,
clears six bytes, writes record bytes 11 and 12, and refreshes four calculated
stats. Speed is copied from party-record offset 46, not calculated. The
88-byte party record starts at side-table offset 24. Preserve the helper's
actual `u8 *(u8)` signature and the stat calculator's
`u32(s32, s32, u16, u16, u16)` interface.

Fifty recorded source candidates cover typed party/record views, conditional
byte spelling, stat-experience expression trees, pointer declaration order,
separate byte-loop aliases, bounded loop-index widths and side/record address
association. Every family first passes known/context/leading-blank
whole-original-object controls. No candidate accepts or installs. Ordinary
four- and six-iteration loops already produce compiler unrolling; manually
unrolling them is not the next hypothesis.

The affine stat-experience expression `65280 + ((-(u32)other[4]) << 8)` uses
defined unsigned wraparound before conversion to the real u16 argument. It
recovers the original negate-then-shift instructions, whereas the signed
negative-product spelling uses an extra `$at` carrier and the simple
`(255 - other[4]) << 8` lowers a different expression tree. Cell 0 of the
private `native-f79-record-refresh-exp-tree` batch retains this useful
partial result: 776 bytes, 48-byte frame, normalized similarity 0.9239 and
raw similarity 0.3096. These scores are not match evidence.

An eight-control passive allocator trace compares stock, observer-off/on and
leading-blank complete objects for both the known module and retained affine
parent. All allocatable bytes, sections, function extents and semantic
relocations agree within each parent. The trace measures an address-expression
web assigned to `$s0`; the ROM instead spills the record pointer across the
four stat calls and saves only `$ra`. Byte aliases and simple pointer-order
permutations do not remove this promotion. Address reassociation can instead
promote the slot or side argument, so it does not solve the frame problem.

Next: inspect the retained unsigned-scaling parent's address-expression/web
construction and real pointer lifetime across the copy/reset/stat phases.
Keep the four stat calls, their intervening loads, and the copied speed;
do not add address-taking no-ops, volatile qualifiers, fake locals or altered
helper interfaces to defeat promotion. The compiler trace is diagnostic only,
not a modified-compiler acceptance path.

## Slot updater: typed-view follow-up, 2026-10-22

Twenty-four additional recorded candidates use the established side-record
view, index widths, guard-return spelling, record-pointer lifetimes and a
stored-value call argument. The typed view recovers the original 164-byte
body, frame and opcode sequence. Cell 0 of the private
`native-f79-slot-typed-state` batch has twelve remaining instruction-word
differences, all register operands. The first is the selected-record load
at function offset 48: `$t0` instead of `$a3`. Later temporary registers
shift accordingly. Relocation offsets and kinds agree. No C body installs.

The reduced search input is calibrated against the retained complete-module
candidate: all 41 masked instruction words and relocation topology agree.
A bounded ninety-second native search excludes fake, ABI and type mutations;
its score stays at 95, with no improvement. Its unchanged-score output is not
adopted. Four selected-index widths and both guard spellings also reproduce
the same twelve-word residual, not eight independent improvements.

Eight passive allocator controls cover known and candidate whole objects
under stock, observer-off/on and leading-blank builds. Within each source,
all allocatable bytes, layouts, function extents and semantic relocations
agree. The retained candidate assigns the selected-index local to physical
register 8 while an intermediate expression occupies physical register 7.
This is measured allocation evidence, not proof that a particular historical
declaration is impossible.

Next: inspect that intermediate expression's provenance and the selected
index's lifetime before and after typed record addressing. Preserve the
unconditional selected-record read, slot guard, both move stores and effect
notification. Repeating width, guard or simple declaration-order variants
does not test a new hypothesis. Do not reserve `$a3` using unused expressions,
fake parameters or forced registers.

### Guarded index domain resolves the slot-updater requeue

`func_84155CB8` is now `BattleMoveState_UpdateMoveSlot`. It reads the selected
record before validating the slot, copies the live move-table byte at slot+5
to both the selected saved record and current move slot, then invokes
`BattleMoveState_ApplySelectedMoveEffects`. These two stores and the effect
call justify the name; the 164-byte original body remains the comparison
oracle.

A bounded child-expression observer passes eight stock/off/on/leading-blank
whole-object controls. It identifies the intermediate occupying physical
register 7 as a conversion of argument-home offset 7, the slot argument.
An initial side-conversion hypothesis is rejected: sixteen genuine unsigned
side-stride/table-index variants do not change the residual. The child trace,
not the earlier pointer-only allocator log, establishes the operand identity.

Keep the signed `slot < 4` guard, then index the source and two destination
arrays with `(u32)slot`. The guard has already restricted that index to 0..3;
unsigned address arithmetic removes the repeatedly used signed-conversion
web without changing the accepted slot domain or adding an operation. Cell 0
of the eight-cell `native-f79-slot-guarded-index-domain` batch is directly
link-verified and accepted by the normal full-ROM gate. Subsequent candidates
are skipped after acceptance. No fake local, dummy expression, forced register,
prototype change or instruction rewrite is used.

The first successful comparison freezes source, changed whole object, four
distinct collateral objects, ROM, ELF and linked script. All nine hashes are
independently checked before more compilation. Eight subsequent whole-object
controls cover the accepted body, leading blanks, redundant extern removal,
naming and six target-layout assertions. Ten independent unmodified-linker
checks preserve all 4096 retail text bytes and all 26 function extents.
The original-address alias accompanies the renamed address-map entry.

The final named normal ROM gate passes with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d` and immediately freezes thirteen complete
objects plus source, ROM, ELF and linked script. Every frozen hash is checked
externally. Three owners remain assembly: the per-record refresh
`func_84155F28` and dispatchers `func_84155AC4` / `func_841562BC`. The refresh
requeue and dispatcher readonly-layout prerequisite above remain open.

## Record-refresh phase investigation: requeue, 2026-10-22

Forty additional recorded candidates leave `func_84155F28` in assembly.
An eight-control passive child-expression trace identifies the `$s0` web as
the complete side/slot record address, including its 18-byte header offset.
It is not a conversion-only reservation like the resolved slot updater.

A real halfword view of the stat region at record offset 14 removes the
saved-register promotion. Its initial 796-byte body still has an extra
pointer adjustment and spill compared with retail's 788 bytes. Explicit
calculated-value locals do not improve it. Absolute/relative copy, fill and
clear loops and reuse of a real record cursor also fail; retain the ordinary
loops rather than manually unrolling the stores.

The reduced stat-phase source reproduces all 199 masked instruction words
and relocation topology of its immutable whole-module parent before a
ninety-second fake-restricted native search. The search score improves from
1055 to 425, but the best output retains a redundant record reassignment and
is not adopted. Its useful hypotheses are the common-else address lifetime
and partial inlining of the stat pointer, not the redundant assignment.

The reviewed common-else form assigns the record address only once on each
path. Combined with the real suffix stat view, cell 5 of
`native-f79-refresh-reviewed-stat-lifetimes` has normalized similarity
0.9749, raw similarity 0.8543, size 796 and a 64-byte frame. Its raw audit
still finds 44 differing instruction words, including frame/spill homes,
store scheduling and the final two stat writes. Removing the remaining stat
alias entirely restores the unwanted saved register, even with that cleaner
control flow. None of these bodies passes a link check or ROM gate.

Next: keep the reviewed parent and investigate the last two stat writes'
address lifetime without a retained biased pointer. Preserve all four stat
calls, their intervening loads and the copied speed. Do not retain redundant
assignments, add frame storage or patch the eight-byte size/frame residuals.

## Dispatcher readonly-layout prerequisite: verified, 2026-10-22

The selected-state file now owns its original jump-table window at ROM
`0x3FBCA0..0x3FBD50` (176 bytes). It contains `jtbl_8418C410` (36 entries),
`jtbl_8418C4A0` (five entries), and twelve original zero bytes. The following
format string at `0x3FBD50` stays in a separate shared readonly tail.

Pinned spimdisasm 1.35.0-dev0 migrates both tables into their original
assembly owners in an isolated split first. Normal/leading-blank whole-object
preflights independently link all 4096 text bytes and 176 readonly bytes to
retail. The installed generated linker change is exactly the normalized
staged output: shared head, selected-state object, then new shared tail.
No unrelated generated-library paths or source changes are copied.

The normal original-assembly full-ROM gate passes with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Its successful callback freezes fifteen
whole objects plus eleven source/layout/linked artifacts, including both
shared-pool objects and all three original assembly owners. Every hash is
checked externally before another compile. The installed complete module
equals the independently linked staged object; twelve previously frozen
collateral objects are unchanged. All four unrelated dirty paths are preserved.

Both dispatchers are now eligible for genuine C switch candidates. This
layout-only gate accepts no new C body: `func_84155AC4`, `func_84155F28` and
`func_841562BC` all remain assembly. Keep the separate refresh requeue active.

## Selected-state dispatchers: accepted, 2026-10-22

Two genuine C switches replace 696 original text bytes:

- `func_84155AC4` becomes `BattleMoveState_RecordMoveAgainstSlot` (272B).
  It checks the byte-returning power getter, excludes effect codes 3, 7, 8,
  26, 38, 89, 144, 148 and 154, and otherwise stores the move at
  `D_8419EE17[side * 306 + selected * 24 + opposing]`. Its caller
  `BattleMoveState_ApplySelectedMoveEffects` obtains `selected` from the own
  side and `opposing` from the other side. The lookup `func_84155D5C` reads
  the same indexed byte. These producer/caller/consumer operations justify
  the function name without assigning broader semantics to `unk_05`.
- `func_841562BC` becomes `BattleMoveState_CopyPartyStatToRecord` (424B).
  It selects one of five cached party halfwords at offsets 42, 44, 46, 48
  and 50 and copies it to the saved record's attack, defense, speed,
  special-attack or special-defense field. The party stride is 88 bytes,
  beginning at side-table offset 24. Other selector values do nothing.

The move dispatcher accepts its first nested-guard/direct-selector candidate
with direct link verification. The stat copier's first two flat halfword
alias forms are 444B rather than 424B. The existing typed side/record fields
recover the exact text shape. That winner is relocation-masked, not directly
link-verified: its `D_8419EE00 + 32` field reference resolves to the original
`D_8419EE20` address. Only the normal sequential full-ROM gate establishes
its acceptance. Both switches preserve the original jump-table case targets.
The initial stat context duplicated an already installed experimental typedef;
the corrected context reuses it. That failed control is not a compiler
hypothesis or a C acceptance.

The first-success callbacks retain 16 and 15 artifacts respectively, including
source, changed whole object, four distinct collateral objects, both shared
readonly-pool objects, ROM, ELF, linked script and original assembly/layout
inputs. Each hash is independently checked before further compilation.
Six cleanup/naming/layout whole-object controls and nine independent retail
links preserve all 4096 text bytes, 176 readonly bytes and 26 function extents.
Unused experimental declarations and the unused party view are removed;
original-address aliases accompany both renamed address-map entries.

The final named normal ROM gate passes with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d` and immediately freezes 26 artifacts,
including fifteen complete objects and the readonly-layout inputs. No
instruction/relocation rewrite, fake storage, forced register, manual unroll,
volatile qualifier or altered helper interface is used. Only `func_84155F28`
remains assembly in this file; its documented phase/lifetime requeue and the
separate geometry requeue remain unresolved.
