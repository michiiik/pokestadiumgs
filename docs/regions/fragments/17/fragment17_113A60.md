# Region notes: fragment17_113A60

## 2026-10-18: packed-color mask callback frame requeue

061A8 remains `requeue` after 24 ordinary native runner attempts. Mode zero
caches the node's packed colors at offsets 40/44 in 10678/10680. Mode one
sets visibility from EC38 == 1, independently of the mask returned by
800060E8. A set bit chooses the saved colors or yellow for the selected
index; an unset bit chooses gray. Both special colors copy the complete
primary word to the secondary word. Other modes leave the node unchanged.

Four-byte aggregate assignments preserve the original word-copy operations.
Materializing a separate word-sized presence predicate from the byte mask
restores the byte mask and boolean normalization instructions that direct
branch spelling removes. The best source preserves all 87 instructions,
348 bytes and register roles, with reported normalized/raw 1.0/0.9080.
Exactly eight word differences remain at offsets 0/8/20/28/32/36/40/332:
frame 32 instead of 40, shifted argument homes, and index spill 24 instead
of 32. The visible flag retains the original slot 28. This is not acceptance.

The completed grids cover scalar versus aggregate copies, flag declaration
order, byte/word mask types, byte/word presence predicates, explicit byte
normalization, predicate evaluation inside/outside the EC38 guard, and
ordinary C register hints. The latter do not change the best object.
Known/type-size/twenty-blank complete-TU controls pass. The real byte-return
getter prototype remains unchanged. Stock 5.3 changes the known TU and
introduces more instruction differences in this callback; its blank controls
pass, but no compiler switch or diagnostic output is adopted.

Next investigate the index/flag storage lifetime that distinguishes the
original slots. Do not add artificial homes, dummy locals, fixed registers
or output patches. No candidate, type declaration or runtime helper from
this investigation is installed, and private probes remain unpublished.

## 2026-10-18: strict-stack search calibration for node scale

The default decomp-permuter score ignores stack offsets: the rejected
09F50 seed scores zero despite the five strict-linked frame/home differences
documented below. With the existing --stack-diffs option, the same seed
scores 58. Strict links prove the standalone AST import equals the complete
TU candidate and that the isolated assembly target equals retail, placing
the selected constant at its measured real address rather than dummy rodata.

A 60-second, four-worker conservative source search with stack scoring
enabled remains at 58 with no improved output. Its enabled transformations
exclude dummy declarations, new temporaries, type/prototype mutations and
artificial operations. This is a bounded flat result, not exhaustion of all
legal C forms and not a zero-score match. Stock 7.1/5.3 diagnostics preserve
the same six raw differences for the scalar seed, including the equivalent
constant relocation; 5.3 changes the known TU, and its blank controls pass.
No compiler configuration or output transformation is adopted.

## 2026-10-18: node scale/translation frame-only requeue

09F50 remains `requeue` after 24 ordinary native runner attempts, with no
accepted or installed candidate. It updates translation at node offset 36
and scale at offset 48 through Vec3f_SetComponentsDuplicate. Its fraction
is 1 - (320 - D_822106CE) / 360, clamped to zero below 0.001 and to one
above one. X/Y scale multiplies C4/C8 by that fraction; B6 bit zero reverses
X scale. Translation is (CC - 320, 240 - (D2 + 350), -579), with scale Z one.

The best scalar spelling preserves all 82 instructions and their register
roles, but has frame 40 rather than 56. Explicit 0.0f - scale_x preserves
the original subtraction, while unary negation changes its instruction
shape. Independent versus else-if clamping, scale declaration order,
two-/three-component scale structs/arrays and named translation temporaries
do not close the frame residual. The tuple components and temporaries are
all consumed by the real helper calls; no dead local or fake padding is used.

The initial raw comparison also reports a constant relocation difference:
the C object's .rodata+40 and original D_8220E1A8 denote the same constant.
A strict link at the real text and rodata bases resolves every undefined
symbol, proves the original function equals the retail-gated image, and
leaves exactly five candidate word differences at offsets 48/60/220/288/316.
Those are the frame adjustment, three node-argument home references, and
frame restoration. All 328 bytes otherwise match, including the constant;
all rodata bytes match. This is not ROM acceptance.

Known/raw/keep/final and twenty-blank complete-TU controls pass. The stale
s32 return declaration can be corrected to void without changing any
existing game bytes, extents, defined symbols or normalized relocations;
the accepted caller ignores its result and the assembly has no result
definition. That correction is only a companion edit in the rejected
transaction, not installed by itself. Next inspect authentic local
storage/lifetime lowering for the five-word frame residual. Do not force
the frame with dummy locals, padding, compiler flags or output rewriting,
and do not treat the resolved relocation spelling as the remaining cause.

## 2026-10-18: text renderer pointer-folding requeue

083C4 remains `requeue` after 24 ordinary native runner attempts; no
candidate is accepted or installed. The original has 85 instructions,
340 bytes and frame 72. The best tested spelling has 80 instructions,
320 bytes, frame 48 and reported normalized/raw similarity 0.9176/0.6353.
These scores describe a non-match, not an allocation-only tie.

The renderer resolves the node's bank/text ID through 8004C874, starts
font rendering, selects its font, and sets the primary RGBA color. It
compares packed secondary/primary colors after that call and enables
two-cycle texturing when they differ, including when the text is null.
For non-null text, alignment mode 2 calls 800495BC, while modes 0/1 call
800495F8 with alignment arguments 1/2. It disables two-cycle texturing
when enabled and restores font 8 and RGBA (0,255,255,255) before finishing.
The existing font helper definitions in src/47580.c establish the actual
prototypes, including both variadic draw interfaces; no prototype is loosened.

Typed union and raw byte color views, text/flag declaration order,
numeric versus 2/0/1 case-body order, signed/unsigned integer address
expressions, initialization placement, scalar root views and reversed
word comparisons do not preserve the original pointer lifetime. The
compiler folds primary byte loads into node-relative offsets, eliminates
the primary pointer spill across 8004972C, and rematerializes the secondary
pointer after Font_EnableTwoCycleTexturing instead of preserving its spill.
Original text/flag stack slots are 52/48; the best source uses 40/36.

Unchanged-stock raw/keep/final and twenty-blank complete-TU controls pass.
Retained frontend and optimized Ucode streams are calibrated to the exact
function name, procedure 65; the stock assembly listing confirms the folded
address expressions before final instruction scheduling. The proposed
52-byte node view and color offsets 40/44 pass target-compiler assertions
without changing any existing game bytes, extents or normalized relocations;
this proves the accessed prefix only, not the full allocation size.

Next investigate authentic source-level pointer escape/alias topology or
frontend lowering that retains these two pointer values. Do not repeat
the completed constant-address/type grid, infer a register tie from the
normalized score, or add dead locals, volatile accesses, fake stack homes,
padding or compiler/output patches to reproduce the larger frame. All
private capture/probe artifacts stay outside publication and coverage stays
CI-owned.

## 2026-10-18: five-model transform follow-up accepted locally, 260 bytes

06EB8 is accepted by normal runner batch
`7b79bd5a1ce948759657808a5d5f3794`, with link verification and a successful
combined full-ROM gate. It preserves all 65 instructions and frame 24.
This is a local follow-up to the two-owner transform/initializer PR #1186,
not an additional function in that published batch. The native file now
has 43 C functions and 39 assembly owners among its 82 original functions.

07714 registers this callback for the five F290 model records, storing
indices 0..4 as node callback data. Mode zero initializes scene translation
from DA6C: (x - 320, 240 - y, -579). Mode two writes the rotation halfword
at node offset 34 from the DA40-indexed table wave. Indices 0/3/4 select
amplitude 4096; other indices select 2048. Other modes return zero without
those updates. The accepted spelling uses grouped switch cases to select
the float amplitude, then multiplies it by the indexed table value. The
four tested logical-OR forms retain 260 bytes but report normalized/raw
0.9846/0.9231; do not generalize that bounded result to every conditional
spelling. No dead angle read or unused neighboring local is introduced.

The first accepted object is frozen at SHA256
`c0159c3f88d499ffb2136c8cc562a613b7617e04c33a855007d0748928bf2d8b`.
After removing redundant braces/prototypes and whitespace, fresh/twenty-blank
complete-TU controls reproduce its game bytes/layouts, defined symbols and
normalized relocations. All 82 extents, outside-owner text bytes/relocations
and other allocatable sections equal the preceding frozen object, including
the model initializer's callback references. Independent strict links prove
all 260 original/frozen/retail-gated bytes equal, with no unresolved symbols.
Record-layout assertions still pass. No accepted owner is re-probed.

The cleaned source passes the ROM gate again, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`, all 427 host syntax checks, 76 native
tooling tests, accepted provenance and whitespace checks. The naming plan
has no established mapping, so the address name remains. This verified
follow-up is prepared as a separate partial batch after #1186 merged;
coverage remains CI-owned and no private helper artifacts are published.

## 2026-10-17: model-group initializer accepted, 536 original bytes

07714 is accepted in normal runner batch
`d25c0ed9369b47f599137fc9dde65946`, preserving 134 instructions and frame
48. It is a relocation-masked match with preliminary `link_verified: false`:
the existing geometry decoder's old func_80040E80 reference and its accepted
process_geo_layout name differ, as do equivalent script-end expressions.
The authoritative sequential full-ROM gate passes. This is not presented
as direct link verification. Together with 07414, the next batch replaces
980 bytes; the native file now has 42 C functions and 40 assembly owners.

The initializer decodes a root and three layout groups of 5/4/4 entries in
a temporary main-pool allocation, finalizes that allocation, then creates
13 model nodes. Each node receives its group's transform callback and its
index as callback data before its decoded layout is attached. The accepted
source uses indexed loops throughout, with an `entry` pointer for layout
stores and a separate `record` pointer for model setup. Sharing those roles
retains all operations but rotates the saved registers. Explicit pointer
walks instead lose the original induction shape. The unused word argument
is part of the original caller interface and prologue, not an invented home.

The shared 372-byte record now exposes the real 360-byte model prefix and
layout pointer at offset 360; texture/tile fields stay at 364/368/370.
Known/refined/twenty-blank whole-TU controls prove this refinement preserves
all previously accepted functions before any candidate runs. It is installed
only transactionally with the accepted initializer. The callback prototype
keeps its word-result, mode-word and node-pointer contract; no function-pointer
casts, omitted arguments, unused locals or compiler/output transformations
are used. The naming plan has no established mapping for this owner.

The first accepted object is frozen at SHA256
`387cd8beb079e8d217fbb2f8f32ad1d2e530198adb826ac9055bdd478a0a59c5`.
All 82 original extents, every outside-owner text byte/normalized relocation
and all other allocatable sections equal the preceding frozen object.
Independent strict links resolve every symbol and prove the original,
accepted and retail-gated 536-byte function images equal. After extern
cleanup, fresh/twenty-blank whole-TU builds reproduce the frozen object's
complete game bytes/layouts, defined symbols and normalized relocations.
Target-compiler assertions verify the model size, record size and layout/
texture offsets. No accepted owner is re-probed.

The cleaned source passes the full-ROM gate again, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`, all 427 host syntax checks, 76 native
tooling tests, accepted provenance and whitespace checks. Coverage remains
CI-owned; private generators, diagnostic copies, objects and ROMs stay local.

## 2026-10-17: clip renderer calibrated address-web frontier

06A2C remains `requeue` after 32 native normal-runner probes. Unchanged-stock
keep/raw/final and stock/logging-off/logging-on/twenty-blank controls pass
for the canonical 312-byte parent. Exact-name calibration identifies global
color procedure 47 and UGEN procedure 46. The context-address web 48 has
saving 4.33333349 and receives physical register 21, creating the sixth
saved register. A separate timer-address web receives register 3. This is
measured constant-address reuse, not a generic register permutation.

Raw header views retain that address web. Explicit first/second cursors
repair their saved-register roles and improve the reported raw score to
0.6282 at 312 bytes. Hoisting the second cursor gives reported normalized
0.9231/raw 0.6282 but leaves the context-address mismatch. Stock 5.3 emits
304 bytes, changes the known TU and does not rescue either parent; its blank
controls pass. No compiler switch is adopted.

A calibrated 60-second conservative search starts at weighted score 1070.
The apparent 955 output is invalid: it moves the clip reset outside its
guard and reads the timer before initializing it. Reject it regardless of
score. A valid cursor-hoist output scores 1050 and informed the bounded
normal-runner follow-up above; no searched output is installed. Its work
directory ends `func_82206A2C-_j6abjll`, with strict linked AST/TU and original
assembly/retail controls. Next separate context-address reuse across the
prelude/root-call path while retaining both cursor roles. Do not replay the
completed pointer/decrement/compiler-version grids or treat these negatives
as exhaustion of all legal source forms.

## 2026-10-17: transform follow-up accepted locally, 444 original bytes

07414 is accepted by normal runner batch
`5829b3d9b6b444b5a5b0eecb72cad89e`, with link verification and a successful
combined full-ROM gate. It preserves all 111 instructions and frame 32.
This native follow-up was completed while the two-owner texture PR #1185
was validating; it is not part of that published two-owner batch.
The native file now has 41 C functions and 41 assembly owners.

Mode zero converts the indexed DAFC position pair into scene coordinates
(x - 320, 240 - y, -579). Mode two updates indices 0/2 horizontally using
the DAD8-indexed table wave, or indices 1/3 through the signed rotation
halfword at node offset 34. The horizontal expression retains double
precision for `(wave + 1.0) * 10.0 * 0.5`, then narrows to a signed halfword
before the index-2 negation. The rotation path retains float multiplication
by 6144 and negates the stored halfword for index 3. Other modes/indices
leave those fields unchanged and return zero. No unused neighbor locals,
angle reads or empty statements were copied from the older 071E8 source.

The first 444-byte accepted whole object is frozen at SHA256
`5c6f34179b58ca08e0ea2665252b9c3cc6182d6cf667d62a0ccca545aa6040ce`.
After duplicate-extern cleanup, fresh/twenty-blank complete-TU controls
preserve that object's game bytes/layouts, all defined symbols and normalized
relocations. These also equal the original still-assembly baseline, including
both previously accepted texture callbacks and all 82 original extents.
The cleaned source passes the full-ROM gate again with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. The accepted owner is never re-probed.
The naming plan has no established mapping, so its address name remains.

## 2026-10-17: clip rendering state/allocator requeue

06A2C remains `requeue` after 16 native probes. Its 068E0 producer clears
1616 bytes; the renderer selects one of two 802-byte lists following a
12-byte header. Each list has a count halfword and space for 100 four-short
rectangles. When the timer at offset 8 is zero, it submits every rectangle
to 80006F70 and 81600F0C, reloading count after calls, then restores the
640-by-480 clip rectangle. Otherwise it invokes 800468A0. A positive signed
timer is decremented afterward.

Eight typed-context, byte/row-pointer and decrement forms produce 304/312
bytes; the local signed-halfword timer gives the full 312-byte extent but
reported normalized/raw 0.9103/0.5000. A further eight forms exposing the
root as its scalar pointer with a typed context view emit the same basin.
The compiler retains a sixth saved register for the context address, where
retail uses a temporary base only in the prelude and rematerializes the root
for calls. The two rectangle cursors also reverse saved-register roles.
Next inspect optimized address-expression reuse/web cost across the prelude
and call path, rather than repeating row-pointer/decrement type grids.
No clip-context declaration or rejected body is installed. The three accepted
callback objects remain frozen independently of this investigation.

## 2026-10-17: paired texture callbacks accepted, 648 original bytes

072D0 and 075D0 are accepted C, superseding their scheduling requeue below.
Each retains all 81 original instructions, 324 bytes and frame 88. Normal
runner batch `894c36e7b88b47a18743e5acf362cc27` reports `link_verified: true`
for both and passes one combined authoritative full-ROM gate. The file now
has 40 C functions and 42 assembly owners among its 82 original functions.
The naming tool has no established mappings for these owners, so their
address names remain; no speculative screen or feature name is introduced.

Calibrated stock assembler listings identify the decisive mechanism. With
byte-pointer arithmetic for DAC8, the assembler treats coordinate reads as
disjoint from outgoing stack stores. Their address-reload chain has length
5, while potentially aliasing texture-header reads have length 17; it hoists
the header loads. With `(s32)position_table + offset` byte-address arithmetic,
the coordinate loads also precede those stores in the dependency graph. The
same single address computation then has chain length 22 and schedules first,
matching retail without the alternate parent's duplicate address addition.
The signed and unsigned address forms both produce probe matches; the first
signed, inline form is the installed winner. A named address local instead
grows the frame to 96. No forced alias annotation, compiler option change,
instruction transform or dummy stack home is needed.

Stock/logging-off/logging-on/twenty-blank whole-TU controls pass independently
for the old canonical parent, the 328-byte alternate parent and the final
accepted source. The diagnostic copy only enables the assembler's built-in
listing; it changes no game bytes, defined symbols or relocations. This is
measured scheduler dependency evidence, not a conclusion from a scalar score.

The texture record is 372 bytes: its four-byte texture pointer is stored at
offset 364, tile count at 368 and tile height at 370. The pointed-to header
is eight bytes. The even tile height comes from
`(2048 / width) & ~1`; the tile count is the ceiling of image height divided
by tile height. 06BA4 consumes those fields as its strip height and loop
count. The callback references in the four DD10..DDAC and four DDE0..DE7C
layouts supply indices 0..3. No index-dependent source narrowing or padding
is introduced.

The first accepted whole object was frozen before cleanup (SHA256
`08a5ad576751d097256853b35ad155d921b84ffa49e96e9d5031674f15c2ef64`).
After removing duplicate externs, formatting calls and correcting field names,
fresh/twenty-blank controls reproduce that object's complete allocatable
bytes/layouts, defined FUNC/OBJECT symbols and normalized relocations. Those
game sections also equal the original still-assembly baseline, preserving
all 82 original starts/extents. Target-compiler assertions verify header
size 8, record size 372 and field offsets 368/370. These are whole-TU
controls; neither accepted owner is re-probed as a candidate.

The cleaned source passes `gmake rom COMPARE=1`, retail ROM MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`, all 427 host syntax checks, all 76 native
tooling tests, the repository accepted-provenance guard and whitespace checks.
The other color callbacks and state initializer retain their separate
handoffs below. Coverage remains CI-owned. Private diagnostics, generators,
objects and compiler copies are not part of the publication.

## 2026-10-17: paired texture callbacks, shared offset and schedule frontier

072D0 and 075D0 remain `requeue` after 32 native runner attempts each.
Their original 324-byte bodies have the same shape: node offset 20 selects
a four-byte asset-id row and a 372-byte record; mode zero obtains archive-1
texture data, derives columns/rows and stores fields at 364/368/370. Mode
five resolves the pixel payload and submits the signed position pair,
unsigned texture header fields, tile dimensions and final flag one to
06BA4, then calls 8003CD84. Other modes return zero. The two families use
F9D8/DAAA/DAC8 and FFA8/DAEE/DB0C respectively. Retail table data confirms
the four-byte strides; the texture header is consumed as two unsigned
halfwords followed by format/size bytes.

The initial eight source variants per owner use implicit table indexing
and produce 320/328 bytes, best reported raw 0.4024. Keeping the genuine
four-byte table offset across the pixel-helper call restores 324 bytes,
the original 88-byte frame, index/offset spill homes and register roles.
The canonical offset parent reports raw 0.9136. Its direct whole-object
comparison has 18 positional differing words, all at offsets 212..280 in
the draw-call schedule. All defined function names/starts/extents, section
layouts and outside-owner text bytes agree. Selected relocation positions
move with the schedule and do not yet agree; this is not link verification.

Known TU, canonical offset parent and twenty-blank controls reproduce their
independent normal builds through unchanged-stock keep/raw/final captures.
The UGEN assembly already orders coordinate-address setup before width and
height loads; the final assembler instead hoists those header loads before
the coordinate setup. Eight token-identical formatting controls, including
whole-body single-line and helper/call same-line forms, emit identical
324-byte function bytes. These diagnostic controls do not install source,
consume normal-runner hypotheses or bypass duplicate rejection.

Eight call/snapshot source forms per owner do not close the residual. Two
of those cells narrowed unsigned width/height snapshots to signed s16;
exclude those generator mistakes from semantic/source-exhaustion evidence.
They were rejected, and no source was installed. Named snapshots and local
coordinate-pointer forms also enlarge the frame rather than repairing it.

A conservative 60-second, four-worker source search on 072D0 improves its
weighted scorer from 575 to 210, not zero. Before searching, the actual AST
object is strictly linked and compared with the full-TU candidate, while the
isolated assembly target is strictly linked and compared with the project's
linked original; no unresolved symbols remain. The retained work directory
ends `func_822072D0-weo5u929`. Every proposed source change was reviewed:
recompute an invariant index-times-four expression, or rederive the same
record address; no writes, calls or initialized values are removed.

Eight normal-runner compositions of those three transformations per owner
retain a useful second parent: normalized 0.9878/raw 0.7805 in 328 bytes.
It moves the coordinate setup ahead of header loads but duplicates the
coordinate-address addition and rotates the subsequent temporary sequence.
Preserve both parents rather than ranking the normalized score as exactness.
Next inspect the stock assembler's alias/dependency boundary for the
canonical parent's coordinate loads, then compose that mechanism with the
328-byte parent's earlier setup. No candidate reaches a ROM gate or becomes
accepted C; no compiler/output patch, fake stack home or coverage change is
part of this work.

## 2026-10-17: typed state and callback-contract controls

At native revision 71035c25, 05E04 remains `requeue` after 136 native
normal-runner attempts. Eight signed-halfword getter-contract variants,
eight ordinary local register-storage variants and eight prototype/K&R
parameter-storage forms all retain the same 296-byte allocation residual
(reported normalized 1.0/raw 0.8243). These are ordinary C storage hints,
not physical-register bindings. No candidate reaches a ROM gate.
Declaring both the existing selection getter prototype and definition as
s16 preserves the entire existing TU in fresh/twenty-blank controls,
including its accepted caller; that contract change remains uninstalled.

06854 remains `requeue` after 16 native probes. A 24-byte typed state
object with halfword fields at 0/2/4/6 and words at 8/12/16/20 preserves
the existing TU's allocatable bytes, section layouts, defined symbols and
normalized relocations in fresh/twenty-blank controls. The sole metadata
change is the undefined D_8220EB80 symbol's size, from 0 to 24. Its two
accepted consumers retain their original access expressions through the
typed object's address. No accepted body is re-probed as a candidate.

Eight pointer/direct aggregate, scalar/field word-store and chained/separate
assignment variants produce 132..152 bytes rather than the required 140.
The best pointer-field form has 148 bytes and reported raw 0.8108, improving
the earlier scalar family's 152 bytes/raw 0.7368. Extra high-half loads and
the reload/store schedule remain; the aggregate does not reproduce the
original interleaved shared-$at materialization. Preserve that source as a
partial parent. Next inspect its unchanged compiler address-lowering boundary
against the original shared-$at run before generating another type grid.
The typed object and consumer edits remain private and uninstalled; these
bounded negatives do not establish that every legal source form is exhausted.

The preserved 148-byte parent now has calibrated unchanged-stock B/O/as1
capture: known source, candidate and twenty-leading-blank controls agree
with their independent normal builds, including raw keep/final objects.
UGEN emits independent macro stores to D_8220EB80+2, +0, +12, +16 and +20;
the assembler does not reproduce the original shared-high-half runs.
The original shares a high-half across offsets 2/0 with an intervening
argument reload, and across 16/20 in the first guard's delay slot. The
148-byte result has two extra words. Any follow-up must preserve the normal
compiler/assembler and distinguish statement-line scheduling from address
expansion; an output-folding workaround is not a source match.
Eight token-identical statement-line controls (halfword stores, word stores
and guard groupings) reproduce the same 148 function bytes. Those measured
line groupings do not resolve the shared-high-half residual.

## 2026-10-17: packed-color copy mechanism verified, allocation still requeue

Stock phase capture supersedes the scalar table-address hypotheses below.
The scalar 05E04 parent has four folded symbol-plus-index loads/stores.
Replacing its four color-word transfers with four-byte aggregate assignments
produces four stock O-stream `mov` records and explicit UGEN table addresses.
It restores the full 296-byte extent. An independent decoder verifies all
74 positional operation identifiers against original assembly, distinguishing
major opcodes, SPECIAL functions, REGIMM suboperations and nops. There are
still 14 positional raw-word differences; normalized 1.0 is not acceptance.

The aggregate object preserves all 82 defined function starts/extents,
all outside-owner text bytes/normalized relocations, and every other
allocatable section's bytes/normalized relocations. The selected function's
relocation topology also agrees. Fresh/twenty-blank normal, retained raw
compiler and final postprocessed whole-TU controls pass. The private
`native-f17-color-mechanism-verdict.json` joins these facts to the retained
stock B/O/assembly files and the independently calibrated allocator objects.
No output or compiler transformation is used to manufacture this result.

Known TU, early-gate scalar, case-local-gate scalar and aggregate parents have
their own stock/logging-off/logging-on/twenty-blank controls. Exact-name
calibration selects global-color procedure 32 and UGEN procedure 31, including
the generated assembly placeholders. The aggregate model leaves allocation
unchanged: index local slot -4 has saving 1.25/register 6; the gate local at
-12 has saving 1.5/register 3, and the mode parameter later shares register 3.
The original needs index/mode/gate in 3/4/4, with an index spill at 24 rather
than 28. The old early-gate model puts the index in register 3 but preserves
a separate gate across the call. Do not discard either partial mechanism.

Producer evidence refines the data interpretation: func_8004E308 in
`src/4EE50.c` stores an opaque `void *` callback argument at node offset 32
and invokes mode zero immediately. The registration code in 0792C supplies
the menu indices through that argument. Pointer/integer views of that field,
typed color nodes, named RGBA channels, immutable snapshot declarations,
byte/halfword gate widths and four equivalent enable-condition topologies
do not close the remaining allocation mismatch. Directly reusing the mode
as the computed gate improves some roles but grows the function to 300..308
bytes. Moving the real gate initialization after the selection call instead
preserves 296 bytes and the index register, but makes mode/gate overlap;
best reported raw score is 0.8919, not a match. Keep this parent alongside
the complete-operation-shape aggregate parent (reported raw 0.8243).
05E04 now has 112 native normal-runner attempts; none reaches a ROM gate.

A 60-second conservative source search on the aggregate parent is flat at
scorer 70, with no output. Before searching, the actual permuter AST object
is strictly linked and compared to the full-TU candidate at the same address;
its isolated assembly target is strictly linked and compared to the project's
linked original. All symbols resolve, and all 296 target bytes agree.
The retained work directory ends `func_82205E04-z6k2dwu3`. Do not repeat that
search unchanged or describe its flat result as source impossibility.

The same aggregate-copy mechanism transfers to 05B00, whose original captures
words at node offsets 40/44. Its selected path writes RGB (255,255,0), keeps
the fourth byte and copies the entire primary word to the secondary word.
Eight new native probes retain all 276 bytes and report normalized 1.0;
the best reported raw score is 0.8116 with aggregate selected-word copying.
The same index/gate register and spill mismatch remains. This is a family
follow-up to the historical 28-attempt owner, not a fresh-owner claim.
No 05B00 body is installed or marked accepted.

Six host-compiled source families pass 113329152 candidate evaluations against
an independent byte-level reference: all 65536 flag words, six valid indices,
enabled/disabled states, selected/unselected paths, and an additional mode
matrix. Return values, single getter invocation, both saved tables, node bytes
and preserved fourth color bytes are checked. These are source-semantics
checks with fixed-width integers, not MIPS or ROM acceptance. The 32-bit
opaque-pointer variants are not covered by this 64-bit host harness.

Stock 5.3 also fails to rescue the aggregate source: it retains 296 bytes but
has 34 positional raw-word differences instead of 14 and changes the known
whole TU. Its blank controls pass. No compiler switch, false exactness claim,
artificial home or physical-register binding is adopted. Both color owners
remain `requeue`; next inspect caller-save interference and mode/gate lifetime
with aggregate moves fixed, using the preserved case-local/after-call parents.
Do not replay the completed type/cast/scope grids without a new mechanism.

## 2026-10-17: state initialization and color callback requeues

Native history-aware discovery at `2fd0d040` includes both the active ledger
and the older shared ledger. `func_82206854` and `func_82205E04` had zero
recorded attempts and still own assembly on upstream master `bcc2084d`.
The file brief and region notes were read before probing. Fresh and
twenty-leading-blank whole-TU controls reproduce all 82 original function
starts/extents, allocatable bytes/layouts and normalized relocations.
After the probes, tracked C still equals the preflight source (SHA256
`3d54ae26b274cae878379197fad2610b3a8f33d2912725e565d207cca37a9d62`).
The rebuilt original also reproduces the frozen baseline's game sections,
symbols and normalized relocations; full ELF metadata is not byte-identical.

`func_82206854` remains `requeue` after eight probes. It clears the 24-byte
state at D_8220EB80, writes the mode halfword and zero flag halfword, stores
the two incoming words at offsets 12/16/20 (the first word is duplicated),
and clears offset 16 when both incoming words are nonzero. It then calls
func_80054CC4 on the pointer at context offset 32 plus 8, with argument zero.
The original caller supplies three word arguments and discards the result.
Scalar/array flag views, nested/combined guards and chained/separate word
stores all compile to 152 bytes rather than 140; best normalized/raw scores
are 0.8421/0.7368. Original assembly shares one $at high-half load between
the flag/mode stores with an intervening argument reload. Scalar C emits
another high-half load; the tested array view materializes a base register.
The repeated offset-16 stores also acquire a common address register instead
of the original separate $at materializations. This is a source/address-shape
lead, not an impossibility claim. Next investigate a genuine aggregate state
declaration; do not patch instructions or insert artificial homes.

`func_82205E04` remains `requeue` after 48 probes. The callback reads its
node's index at offset 32, calls the signed-halfword selection getter
func_8220AD10, captures two color words at offsets 60/64 in mode zero, and
updates them in mode one. Index 5 is enabled only while D_8220EB90 is nonzero.
Unselected entries restore both captured words. The selected entry writes
RGB bytes (0,156,216) and (52,43,135), preserving each fourth byte. All other
modes return zero without a color update; the getter is still called.

The initial eight cells vary gate declaration position, selected/restore
branch order and word/byte node views. The first-order gate lifetime can
produce a 40-byte frame instead of 32. Moving initialization into case one
or reusing the mode fixes the frame but not the match. Retain the earlier
gate-first draft's correct index register as a partial result, not acceptance.
Further families test genuine shared byte offsets, typed node fields,
32-bit integer address arithmetic, a mode-derived gate with four widths and
two scopes, and composition of early declaration with late initialization.
They do not close the function. Strongest normalized shape is 0.9189 at
280 bytes versus 296, raw 0.2568; highest raw score is 0.3378 in the earlier
288-byte family. Those scalar scores do not order all partial mechanisms.

The aligned differences include index register/spill placement and four
folded table-address sequences where the original materializes full bases.
The original no-context m2c draft is retained privately, without adopting its
explicit spill local or unknown field syntax. Next capture the stock B/O
boundary for the index, mode and update gate, and the table-address folds;
do not repeat the measured cast/offset/scope families unchanged. Private
manifests/results use `native-f17-state-init` and `native-f17-color-callback`
prefixes. No candidate qualifies for a ROM gate, no C replacement is
installed, and coverage/private diagnostic tools are excluded from commits.

## 2026-10-14: func_822085EC

The owner is a no-argument, word-result wrapper. Its original caller
`func_82208A1C` supplies no arguments and branches on the returned word.
The initial helper `func_82206950` also takes no arguments and returns a word.
The other unchanged assembly helpers `func_8220AC38` and `func_82204744` take
no arguments; this owner discards their results. `func_8220ADE0` retains its
existing `s32(s32)` definition and receives the signed halfword at state offset
0. No fabricated arguments or helper return widths are used.

The accepted source initializes `var_v0` before `var_v1`, using the existing
`s16 D_8220EB80[]` declaration through a byte pointer. On the successful initial
guard it returns 1, sets the halfword bit at offset 2, runs the setup helper,
conditionally runs the helper selected by the word at offset 0x14, and invokes
`func_800226C0(52)` when the state is -1 or `func_8220ADE0` returns nonzero.
Other paths return 0. The first spelling matches all 35 instructions, frame
0x20, and result spill at 0x1C. Unknown names remain address/register-based.

History audit: the fleet 113A60 region records a historical accepted
`call-sequence:state-pointer:result-before-pointer` recipe after six iterations.
That paragraph supplies no raw similarity score; no exact owner attempt file
exists at fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed`. The owner was
still `GLOBAL_ASM` on current master, with no open competing PR. The helper
plateaus remain deferred: 06950 normalized .9048/raw .619, AC38 .9167/.75,
and 04744 .9375/.875. Their bodies were audited but not modified or retried.

Independent validation on master `b4ded57db9dbd84a9a209f134f7b72204d97aecb`:
US ROM rebuilt with default host syntax checks and `COMPARE=1`; explicit
`md5sum -c baseroms/us/checksum.md5` passed with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. All thirteen other open process matching PRs
were excluded, including both files for #885 and the new #900 source. Already
merged #880 and current foreign rendering work were preserved. The combined
188-owner workspace also passed. The authoritative Public PR ROM Gate remains
required for each current PR head and actual merge result.
