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
