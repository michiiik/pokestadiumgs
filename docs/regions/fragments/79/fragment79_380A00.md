# Fragment 79 animation dispatch suffix

The source starts at ROM `0x380A00`, following the camera-callback split.
Earlier owner history remains in
`docs/regions/fragments/79/fragment79_37A6E0.md`.

## 2026-10-23: category-camera record index resolved

`func_84116BC0` / `BattleAnim_ConfigureAnimationCamera` is runner-accepted.
The owner is 756 bytes with a 32-byte frame. It copies animation-record bytes into state,
selects a dispatch value from the animation identifier, then chooses a
camera preset from the battle category. These producer/consumer operations
justify the function name. The actual record stride is 20
bytes, and its switch owns the eleven-entry `jtbl_84189028`.

This continuation uses native revision `e011b503`, after the camera split
and wave callback. The existing six-halfword `D_84183BDC` declaration and
`BattleAnim_SelectCameraPreset` signature are already corrected; neither
requires a new companion edit. Whole-module and leading-blank controls
agree with the frozen matching baseline before each source batch.

The decisive retail sequence stores the byte-loaded identifier with a word
store at stack 24, then reloads its low halfword at stack 26 for
`func_8411DC80`. The model and record pointers occupy `$v0` and `$v1`.
The initial named-index source forms retain distinct residuals:

- A wide scalar index gives 748 bytes and a 24-byte frame, keeping the index
  in a register and narrowing it immediately before the lookup.
- A halfword scalar gives the correct 756-byte body and 32-byte frame, but
  stores a halfword at stack 30, adds a narrowing mask, and swaps the two
  pointer registers. The baseline has 21 differing instruction words.
- Separate wide record and narrow selection values can generate the desired
  word store at 24 and halfword reload at 26. They also create extra
  instructions and a 48-byte frame. Initializing the narrow value directly
  from the byte field recovers 756 bytes and a 32-byte frame, but stores a
  halfword at 26 instead of a word at 24; 20 instructions still differ.

The initial 73 source variants in this continuation cover byte promotions,
wide/narrow consumer assignment, integer rank, pointer construction,
record/state field views, category carriers, and genuine pointer-lifetime
transitions. None is accepted. `int` and `unsigned int` do not improve the
SDK's `long`-based scalar forms. Typed record and state views also preserve
the same storage problem. These negatives apply to those measured families,
not to every possible source shape.

Twenty stock/off/on/leading-blank controls calibrate logging-only frame
observations against complete retained parent modules. The wide, halfword,
and two-carrier parents have 8 saved-register bytes and 16 outgoing-argument
bytes, plus 0, 8, and 24 additional frame bytes respectively. This is a
storage/dataflow residual, not permission to add unused locals, fake
address-taking, enlarged arrays, or padding.

A small, independently driver-logged compiler/flag matrix preserves the
known sibling `func_84111C1C` under normal and leading-blank controls.
Stock IDO 5.3 at `-O2` leaves the same measured residuals as 7.1 for the
tested parents; 7.1 at `-O1` grows the two scalar bodies to 908 bytes, and
7.1 `-O2 -g0` leaves those two residuals unchanged. No compiler setting is
changed for the project, and no historical toolchain identification follows
from these bounded negative controls.

### Source-search validity

A calibrated 90-second source-only search reproduces all 187 words and
relocation topology of the retained 748-byte wide-index parent before
searching. Its two lowest-scoring outputs remove the model-pointer
initialization while retaining `entry = model + ...`; both are invalid and
rejected. Disabling the unrelated inline-function-generation pass alone
does not prevent the defect in a second 60-second search.

The dependency's read tracker ignores an entire assignment whenever its
left-hand side is a scalar identifier. It therefore misses reads on the
right-hand side of `entry = model + ...`, allowing expression expansion to
delete a still-needed definition. Any search result must be reviewed for
this error before its score is interpreted. The shared dependency is not
modified by this continuation.

A private correction includes scalar-assignment RHS reads while still
excluding a plain assignment's destination. Synthetic tests using the
dependency's own AST implementation cover scalar RHS reads, compound
assignment, initialized declarations, and address-only output arguments.
The corrected 60-second search retains valid model initialization and
exposes a different source mechanism: direct reads of the animation-ID
field instead of a named scalar cache.

### Accepted source mechanism

The intervening record-copy writes address other state fields, so repeated
reads of animation ID 1560 preserve the original value before the lookup.
Removing the unused index declaration and read from the generated proposal
is mandatory; neither is retained in the accepted source. Expanding the
model and record pointer expressions also removes the extra local storage.

The compiler then supplies the original hidden word spill at stack 24 and
halfword reload at 26. Offset-first pointer addition reproduces the final
load/shift schedule and operand order. The accepted body has no local
variables, unused record type, artificial address-taking, padding, or
instruction rewriting. Both original pointer reads are real consumers of
the model pointer at state offset 724.

The initial text probe differs only in relocation-controlled fields and
does not claim link verification. Its sequential stock, host-syntax-enabled
full-ROM gate passes. The immediately frozen successful inputs, three
modules, four collateral objects, ELF/linker output and ROM pass external
hash checks. Independent aggregate comparison preserves all 332 original
function extents, game sections, linked relocation encodings, and the full
linked fragment; US MD5 is `1561c75d11cedf356a8ddb1a4a5f9d5d`.

The original address-keyed function name remains a linker alias.

## 2026-10-23: packed-model initialization resolved

`func_8411BB04` / `BattleAnim_InitializePackedModelState` is runner-accepted
at 292 bytes, 73 instructions, and a 40-byte frame. After resetting animation
state, it selects camera 0 or 6 unless camera 33 is active, obtains a side's
halfword format input and packed model state, and passes them through
`func_84112FD0` to `func_80041FD0`. Finally it records `D_84183D50` in the
current side's state slot. These initialization and model-state consumers
justify the name; the packed word's individual byte meanings remain unknown.
//@src/fragments/79/fragment79_380A00.c
//@src/229E0.c

The closest scalar parent already reproduces every instruction except the
cached side's byte-stack home: stores and reloads use 39 or 35 instead of
34. A corrected, calibrated source search reaches a zero-difference proposal
with a redundant pointer alias and byte copy. That proposal is diagnostic
evidence only; neither alias is retained in the accepted source.

Four subsequent eight-cell batches test real-value representations:
halfword camera-table indexing, an actual completion-array base, a named
halfword predicate input, and a model-selection record. The first three do
not match. Separate halfword locals move the saved byte to 37, 33, 39, or
35; this does not establish that all scalar forms are impossible.

The accepted form groups the actual halfword predicate input and cached
side byte in one local record, declared after the predicate result. Both
fields are assigned and consumed: the halfword goes to `func_8006456C`, and
the byte indexes the packed state passed to `func_84112FD0`. The compiler
naturally puts the side at stack 34 and preserves every original register
and instruction. No unused field, artificial address-taking, duplicate
byte copy, forced ABI, padding, or instruction rewriting is present.

Known and leading-blank complete-module controls pass before the batch.
The winning probe is link-verified and passes the normal host-syntax-enabled
full-ROM gate. The first success is immediately frozen with the three source
modules, active assembly and layout inputs, four collateral objects, ELF,
linker output, and ROM; external hashes verify every frozen artifact.
Independent aggregate comparison preserves all 332 original function extents,
game sections, relocation encodings, and the entire linked fragment. US ROM
MD5 is `1561c75d11cedf356a8ddb1a4a5f9d5d`. The address-keyed function name is
retained as a linker alias. This result resolves the earlier saved-side
stack-home requeue, not the remaining assembly owners in this file.

## 2026-10-23: camera resources and model-event batch

Four further owners are runner-accepted, totaling 736 bytes:

- `func_84113590` / `BattleAnim_LoadCameraTrackResource`: 200 bytes. It
  normalizes the byte selection for battle categories 20 and 25, stores
  `D_841911F9`, then copies the selected ROM resource to `D_84190520`.
  Camera updater `func_8410BDA0` consumes this buffer and selection byte.
  Both ROM-offset and 26-byte metadata-row lookups use the stored byte;
  parameter-only lookup forms lose the original address and narrowing steps.
- `func_84113658` / `BattleAnim_LoadSpeciesCameraPreset`: 144 bytes. It
  transfers the species-indexed sixteen-byte record from ROM and writes six
  typed fields into preset 39 of the 28-byte `D_8418455C` camera table.
  Camera consumers `func_8410B884` and `func_8410C934` interpret the two
  halfword/halfword/float groups. Field names remain offset-based where their
  precise axis or scaling role has not been established.
- `func_8411A7D8` / `BattleAnim_ResetPackedModelState`: 168 bytes. It clears
  two state fields, sets the 300-tick interval, and reapplies packed model
  state. The actual predicate-input/side record proven for
  `BattleAnim_InitializePackedModelState` also resolves this sibling's saved
  side at stack 34. Both fields are assigned and consumed.
- `func_84111EC4` / `BattleAnim_ClearFinishedEventTrack`: 224 bytes. It
  checks model and battle-state guards, then passes -1 to the event-track
  setter only when a non-null track has finished. The helper's stale local
  `void (void *, u8)` declaration is corrected to `s32 (void *, s32)` in the
  same runner transaction. The callee explicitly recognizes -1; its existing
  byte-valued caller remains byte-identical.
//@src/fragments/79/fragment79_37A6E0.c
//@src/229E0.c

The species loader's real record, ROM-range pointer, and destination pointer
produce its 48-byte frame naturally. Eight initial single-pointer forms
place the sixteen-byte transfer at stack 32 or 28; removing the range cache
changes both the frame and instruction count. Declaring the two consumed
pointers before the record, and computing the destination after the ROM
copy, supplies stack 24 and all original loads/stores. No enlarged buffer,
unused local, dummy field, or padding is used.

Each batch begins with known and leading-blank complete-module controls.
Every accepted owner is link-verified and passes the normal host-syntax-enabled
full-ROM gate, with an immediate frozen success before later compilation.
Independent aggregate comparisons preserve all 332 original function extents,
game sections, linked relocations, the full linked fragment, and four
collateral objects. External hashes verify the captured inputs and outputs;
the US ROM MD5 remains `1561c75d11cedf356a8ddb1a4a5f9d5d`.

An initial reset-sibling batch rejects a late `s32` declaration of a helper
that earlier callers already declared implicitly as `int`. Removing that
new declaration allows the unchanged, ABI-equivalent side-selection call
to compile; no forced signature or compiler changes are made. This is a
declaration-context correction, not a source-shape hypothesis failure.

The four old function names remain linker aliases. No instruction or
relocation rewrites, fake reads, artificial address-taking, volatile tricks,
or manual loop unrolling are introduced. Other assembly owners remain.

## 2026-10-23: callback pipeline and model-state batch

Four further owners are accepted, totaling 1,072 bytes:

- `func_84111774` / `BattleAnim_RunCameraStageCallbacks`: 244 bytes. Two
  ordinary loops run seven eight-byte context/callback entries for the two
  cameras, then call `func_841114A8`. The shared `D_841911EC` counter is
  reloaded after every callback because callbacks can modify it. An inline
  typed slot view matches; caching a slot pointer or spelling a while-loop
  changes the instruction sequence. The seven-slot layout is also written
  by `func_84111348` and `func_841113F8`.
- `func_841156D0` / `BattleAnim_UpdateAscentPhase`: 264 bytes. It fires
  timed effects at the trigger byte, continues their updater after the
  elapsed halfword reaches that trigger, and advances the phase when the
  state float at 40 reaches baseline float 1616 plus 200. Both actual
  counters are reloaded after the callbacks. Loading and declaring the
  trigger before elapsed reproduces the original `$v0`/`$v1` assignment.
- `func_8411DAE0` / `BattleAnim_UpdateBothSideCallbacks`: 276 bytes. It
  sets bit 0 of each side's flags at 2028, runs common update hooks, and
  conditionally runs each side's object callbacks using the two mode bytes.
  Each mode-byte reload across a callback is retained. Both sides' finished
  event tracks are checked afterwards.
- `func_84112C98` / `BattleAnim_RefreshSpeciesModel`: 288 bytes. It compares
  requested species 1628 to current species 1624, reloads a changed model,
  restores animation and side-state effects, then clears two state fields.
  A direct requested-first entry comparison supplies the original branch
  operands and current/requested load schedule; two scalar species caches
  rotate many registers. The `func_84112EAC` caller now explicitly passes
  its actual model pointer in the same acceptance transaction. Its entire
  compiled function remains unchanged.

Each owner uses calibrated known and leading-blank whole-module controls,
followed by the normal host-syntax-enabled full-ROM gate. The first, second,
and fourth winners are link-verified in the runner. The two-side updater's
initial link-shape check reports a relocation-name difference because its
last two calls use `BattleAnim_ClearFinishedEventTrack` rather than the old
address-keyed alias. It passes the authoritative sequential ROM gate;
independent aggregate relocation normalization and the complete linked
fragment establish the identical final call destinations. The initial
runner flag is not reported as link-verified.

Every success is frozen before subsequent compilation. Independent checks
preserve all 332 original function extents, complete game sections and
relocation encodings, the entire linked fragment, four collateral objects,
and externally hashed inputs/outputs. US ROM MD5 remains
`1561c75d11cedf356a8ddb1a4a5f9d5d`. No fake local/field/read, padding,
instruction rewriting, forced ABI/register/frame, or manual unrolling is
used. Original function names remain linker aliases.

Public integration must start after merged #1444 (`2edb8be4`) and its
camera-helper declaration repair. That merge changes a separate prefix
module, `fragment79_37A6E0.c`, but none of these four owners. The public
prefix and all other merged source bodies must be preserved; fresh public
whole-module checks are required before publishing this batch.

## 2026-10-23: timed feedback and side-model initialization

Four owners still active as assembly on public master `0a8b6347` are
runner-accepted, totaling 1,548 bytes:

- `func_841153DC` / `BattleAnim_UpdateTimedFinishPhase`: 284 bytes. Fire
  the trigger's callbacks/feedback, adjust camera 4's scalar to 60, set
  the track flag, then finish at the specified elapsed frame or when a
  zero-valued completion selector allows the model-animation completion
  test. The two finish paths retain their separate flag/phase/reset tails.
  Keep the existing word-sized object parameter and a real byte-pointer
  view; an incompatible new prototype is not a source hypothesis.
- `func_84117AA0` / `BattleAnim_DispatchActionFeedback`: 376 bytes. Handle
  action 48 and actions 217/168 separately, then select the remaining
  feedback from the side's halfword status and global mode. The actual
  entry classification is a word-sized snapshot; the value sent to the
  dispatch helper is read again after the sound callback. The byte-sized
  snapshot has the same operations but a different register. A typed
  eight-halfword row view preserves both side queries and the original
  address-addition order. A calibrated, read-corrected source-only search
  suggested the snapshot role; the retained source uses no generated
  placeholder or unused value.
- `func_84115B34` / `BattleAnim_UpdateBurrowTransition`: 444 bytes. A regular
  four-case switch matches the observed branch chain. The phases delay,
  start the transition, update the ordinary/special model paths, then reset
  the side-facing angle after 30 frames. Diglett/Dugtrio IDs 50/51 skip the
  ordinary descent/effect path; the preceding producer selects action 91.
  Keep the species reload after the effect callback. The equivalent if-chain
  has different dispatch instructions and is not installed.
- `func_8411D7F8` / `BattleAnim_InitializeActorFromSide`: 444 bytes. Query
  the side's species, format and packed model state, initialize model and
  scene hooks, copy the current species into shared state, then reset flags
  and mark the appropriate side ready. Chained species stores preserve the
  single source read. The requested-species field view is consumed by the
  later model call, preserving a fresh field read after callbacks rather
  than caching its earlier value. All locals have real consumers. The
  ordinary scalar-only parent differs only in frame extent; eight attempts
  to replace the accepted field view with a freshly read scalar reject in
  complete-module comparison. No unused reservation, synthetic padding,
  dummy read, or address escape is retained.

The private suffix had a stale byte-sized first parameter for
`func_800231A0`. Its assembly explicitly handles action ID 300, so that
declaration cannot describe the supported input domain. A word-sized
integer declaration preserves all existing native game sections/extents
under normal and leading-blank controls, and is installed transactionally
with the feedback routine. Both signed word spellings produce the same
residual until the classification snapshot is corrected; the type change
alone is not a match. The helper's historical source spelling is unknown.
Public integration must reconcile its narrower declaration too and prove
that every already accepted public owner remains unchanged.

Every winner initially reports `link_verified: true` and passes the ordinary
host-syntax-enabled full-ROM gate. The first success is frozen before any
subsequent compilation: source and active assembly/layout inputs, all three
camera modules, four collateral objects, ELF/linker output and ROM.
Independent comparison preserves all 332 original function extents,
complete game sections/semantic relocations, and the entire linked fragment.
External SHA-256 checks pass; US MD5 is
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Original names remain linker aliases.

No instruction or relocation rewriting, forced register/frame/ABI, fake
local/field/read, volatile trick, or manual unrolling is introduced. Future
target selection must intersect the private owner's active pragma with
fresh public master before probing: four earlier private track matches were
already C publicly and were deliberately not exported or counted as new
coverage. Transfer only this batch's owned definitions, aliases, declarations,
and this note; preserve all other newer public source and notes.

## 2026-10-23: category camera, records, audio and viewport transition

Four further owners are runner-accepted, totaling 2,588 code bytes:

- `func_84118C08` / `BattleAnim_RefreshCategoryCamera`: 460 bytes. It
  prepares actor tracks, refreshes the category-dependent camera, and
  installs the current side callback. Reroll categories must be enumerated:
  unlisted categories, including 71 and 75, leave the camera untouched.
  The retry loop reloads the camera pointer after the preset callback and
  continues until its identifier changes. The previous identifier is a
  signed halfword declared before the actual camera pointer.
- `func_841189EC` / `BattleAnim_DispatchCategoryRecord`: 540 bytes. Once
  frame 2 is reached, it selects a category-specific animation record (or
  the category-89 action), updates phase 2, and installs the side callback.
  The switch directly consumes the promoted halfword category. Unsigned
  word and narrow cached alternatives do not reproduce its signed range
  check and register ownership. Its existing jump-table layout is retained.
- `func_841114A8` / `BattleAnim_UpdateAudioProjections`: 716 bytes. It
  copies two existing three-float points and computes angle/distance pairs
  for audio channels 0, 1 and 2. Category and flag checks choose the actor
  point used by channels 1 and 2. Actual helper output arguments account
  for the six polar outputs. Expanding the actor field expressions removes
  an unnecessary cached point local and recovers the original 80-byte frame;
  the compiler supplies its own common-expression spill at stack 36.
- `func_8411CD38` / `BattleAnim_UpdateSideViewportTransition`: 872 bytes.
  Five phases coordinate the side viewport slide, model completion,
  frame-triggered audio and model-track resets. A typed sixteen-byte
  metadata-record view reproduces the original register ownership. The
  published view skips the sixteen-byte header and reads halfword 2 within
  each eight-halfword record. Four independently compiled post-acceptance
  cleanup forms all preserve the complete module; the earlier cross-row
  byte-pointer expression is not retained.

The camera, record dispatcher and viewport probes initially differ in
relocation-controlled fields and do not claim `link_verified`. Their
sequential normal, host-syntax-enabled full-ROM gates pass. The audio probe
is link-verified and passes the same gate. Each success is frozen before
subsequent compilation, followed by independent comparison of all 332
original function extents, complete game sections and semantic relocations,
four collateral objects, and the entire linked fragment. Final names and
cleanup are re-gated together. US MD5 is
`1561c75d11cedf356a8ddb1a4a5f9d5d`; original function names remain aliases.

No generated coverage, instruction/relocation rewriting, artificial locals,
padding, forced registers/frame/ABI or manual unrolling is introduced.
The species transform loader at `func_84113014` remains assembly: its
diagnostic near-match is not part of this accepted batch.

## 2026-10-23: category action and camera track sequences

Four further owners are runner-accepted, totaling 5,016 code bytes:

- `func_84118DD4` / `BattleAnim_UpdateCategoryActionTimeline`: 1,464 bytes.
  Frame 2 dispatches category-specific records and audio; frame 71 clears
  the original two flags independently, restores tracks, installs the side
  callback, and stops category-specific audio. Preserve fresh global and
  actor-field reads across callbacks, the per-category call order, and the
  separate side queries. Typed sixteen-byte metadata records reproduce the
  original address-tree register ownership.
- `func_8411C418` / `BattleAnim_UpdateSideTrackViewportTransition`: 928
  bytes. This sibling of `BattleAnim_UpdateSideViewportTransition` adds
  side-track setup, sound when the sliding viewport reaches 30, a viewport
  reset at 320, and a forty-frame model transition. Its five explicit
  phases match with direct phase and viewport-field reads; caching the
  phase in a word changes register allocation.
- `func_841170A0` / `BattleAnim_InitializeCategoryAction`: 1,332 bytes.
  Category dispatch chooses animation tracks and duration, then configures
  the camera and side feedback. The two duration consumers preserve a real
  signed-halfword snapshot from the animation data at pointer offset 68,
  field offset 10. Keep the separate metadata reads and callback branches.
  The original duplicate equality branch before the byte-1562 write is
  preserved as two nested guards; this is an observed retail control-flow
  detail, not an additional read or a historical source claim. Existing
  address-keyed aliases are used for previously named helper functions.
- `func_8411BCC8` / `BattleAnim_UpdateCategoryCameraSequence`: 1,292 bytes.
  Five phases coordinate track selection, camera movement, timed audio,
  and final flag cleanup. A signed-halfword camera selector is saved and
  restored across callbacks. Test the original camera field before the
  temporary selector change; testing the narrow saved scalar instead adds
  a stack reload and eight code bytes. All three metadata consumers need
  the typed record view. The eight-cell composition confirms each site
  independently removes its three-register residual; all three together
  pass the ROM gate.

Each winning probe differs only in relocation-controlled fields and does
not claim initial `link_verified`. Each passes its authoritative sequential
normal, host-syntax-enabled ROM gate. Successful inputs and outputs are
immediately frozen before further compilation. Independent proof preserves
all 332 original function extents, complete game sections and semantic
relocations, four collateral objects, and the entire linked fragment.
Naming is re-gated with the whole batch. External SHA-256 checks pass;
US ROM MD5 is `1561c75d11cedf356a8ddb1a4a5f9d5d`.

Original function names remain linker aliases. Export only these four
definitions and their exact alias, prototype/call-name, and note deltas.
No generated coverage, instruction/relocation rewriting, artificial
locals/fields/reads, padding, forced register/frame/ABI, or manual
unrolling is introduced.

`func_84113014` remains a requeue, not accepted C. A further controlled
eight-cell batch tests signed/unsigned numeric stream-address fields and
pointer/numeric sum forms. The numeric forms retain the four reversed
`addu` operands at raw similarity 0.9837; pointer forms move to a worse
basin. No zero-table label or linker metadata is added. Resume from the
documented exact-opcode parent and resolve its arithmetic ownership and
zero-table representation together.

## 2026-10-23: guarded category cameras and the move timeline

Two large owners are runner-accepted, totaling 3,948 code bytes and 987
MIPS instructions:

- `func_84113E7C` / `BattleAnim_ConfigureGuardedCategoryCamera`: 1,924
  bytes. It emits one-time category feedback, checks each side prerequisite
  independently, and selects category-specific camera tracks, randomized
  presets, visibility, and timers. The real byte rejection flag survives
  callbacks at stack 39; a word flag does not reproduce the code. Preserve
  each separate prerequisite call and side lookup: short-circuiting the
  checks would skip callbacks present in the original.
- `func_84114BF4` / `BattleAnim_UpdateMoveTimeline`: 2,024 bytes. It handles
  initial model tracks, signed-byte start timing, category/species lookups,
  frame-triggered audio and camera changes, visibility, and completion.
  Both completion paths clear flag 8, then flag 1, then assign phase 4.
  This statement order resolves all fourteen remaining register differences;
  the compiler schedules the resulting instructions exactly as in the ROM.
  The eight-cell composition varies the phase write's position independently
  in the two blocks; only placing it after both flag writes in both blocks
  passes the ROM gate. No artificial flag snapshot or additional local is
  retained.

The camera owner's last instruction residual was an unnecessary byte mask
before `func_8411F750`. Its definition in `fragment79_38EFE0.c` takes `s32`
in both the native and public trees; an older block declaration inside
`func_84112E40` incorrectly said `u8`. The runner companion transaction
corrects that declaration to `s32` and adds the same forward declaration
for the new caller. A declaration-only control preserves the complete
existing module before the candidate runs. The defining helper and its
other translation unit are unchanged.

The move owner initially uses the file's existing word-address parameter
and explicit byte-pointer views. Post-acceptance controls replace that
parameter and its one forward declaration with `u8 *`, removing repeated
casts throughout the body. Both normal and leading-blank versions preserve
the complete module, including existing callers; that readable pointer
form is retained. An alternative local pointer view also preserves the
module but is not installed.

The camera probe is relocation-masked and does not claim initial
`link_verified`; its authoritative sequential ROM gate passes. The move
probe is link-verified and passes the same normal host-syntax-enabled gate.
Successful inputs and outputs are frozen immediately. Independent proof
preserves all 332 original function extents, complete game sections and
semantic relocations, four collateral objects, and the entire linked
fragment. Final cleanup and names are re-gated together. External SHA-256
checks pass; US MD5 is `1561c75d11cedf356a8ddb1a4a5f9d5d`.

The original names remain linker aliases. No generated coverage,
instruction/relocation rewriting, padding, artificial locals/fields/reads,
forced registers/frame/ABI, or manual unrolling is introduced.

`func_84113014` remains the only shared assembly owner in this suffix.
Eight new incremental pointer-construction forms do not improve its
documented four-addition residual; literal-zero forms still fold the zero
table address instructions away. No diagnostic zero label is installed.
Resume from the raw-0.9837 parent with exact opcode order; its next action
remains resolving constant-base arithmetic ownership and the genuine zero
table representation together.
