# Fragment 77 native matching notes

## 2026-10-15: clock and confirmation action accepted

Batch `7dbbf507b1984bdd8f6463cd2e2c25fd` accepts two owners through the normal
native runner, both `link_verified: true`, with one combined full-ROM gate:

- `func_8F8014E4`: 49 words / 196 bytes, leaf. Winner
  `f77:clock:prefix-False:early-return-False:cast-day-False`.
  Preserve nested frame/second/minute/hour carries at 30/60/60/24 and the
  two halfword stores implementing the day increment and eight-bit mask.
- `func_8F8021E8`: 51 words / 204 bytes, frame 0x20. Winner
  `f77:confirm:local-result-False:field-pointers-False:bound-snapshots-False`.
  Read the event, render, then handle confirm/cancel. Confirm plays sound
  before reading table bounds and clamps the signed state halfword against
  unsigned bounds. Keep the post-store signed reload and distinct return 1.

The table is u16 rows of 17 elements; the state remains the existing u16
array with a signed halfword view for the clamp. No fake locals, volatile
accesses, forced registers, helpers, compiler/object changes or layout edits.
Naming plan has no known names for these owners. Post-formatting and scoped
extern deduplication, fresh/20-leading-blank controls reproduce every object
section and all seven C definitions against the original assembly baseline.
The normal ROM gate passes MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.

`func_8F801F44`: **requeue**, not accepted. Eight range-setup candidates
test real row/state pointers and initialization forms. Best normalized
similarity 1.0 hides raw similarity 0.7188, at the correct 128-byte size;
the first residual is `lhu t1,10(v0)` versus `lhu t9,10(v0)` at offset 32.
Do not mistake this for exactness. Preserve the writes to state offsets
4/0/2 before `func_8F8015A8` and the fresh post-call state read at offset 12
for the offset-6 store. Next hypothesis: real field snapshots and declaration
order to explain the temporary allocation; inspect the entire diff before
choosing a permuter follow-up. This batch did not establish a compiler wall.

## 2026-10-15: range setup and two word-confirm handlers accepted

The range-setup requeue above is resolved. Batch
`43bbacccdbca4b21bdebb6ef96fb208b` accepts `func_8F801F44` with winner
`f77:range-source-order:012`: 32 words / 128 bytes, frame 0x18,
`link_verified: true`, normal combined full-ROM gate. Write fields 0, 1,
then 2 in C; IDO schedules their stores into retail order 2, 0, 1 and
allocates the expected temporaries. The earlier C store order mirrored
scheduled assembly rather than source order. Real snapshots did not solve
this. A stale advisory register-tie warning accompanies the accepted batch;
it is not a reason to reject the measured acceptance or stop early.

Batch `dfe4cfee21854a3b84d95ef4ad2a78c7` accepts `func_8F80299C` and
`func_8F802D0C`, each 51 words / 204 bytes, frame 0x20,
`link_verified: true`, one combined full-ROM gate. Both use winner
`f77:word-confirm:result-False:pointers-False:bounds-False`. These are
siblings of the prior halfword confirmation handler, using signed word
state at offset 0x14 and their respective input/render calls. The word
clamp naturally retains its newly assigned value rather than inserting
the halfword handler's signed reload. Keep the actual word view and
fresh bounds after the sound call; do not factor the handlers into helpers.

Post-formatting and scoped extern deduplication, fresh/20-leading-blank
controls match all sections and all ten C functions against the original
assembly baseline. The normal full-ROM gate passes retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Naming plan has no known mappings.

`func_8F8026DC` / `func_8F802A68`: **requeue**. The signed decimal/hex
digit initializers use the same natural field initialization order, call
`func_8F8015A8`, reload the word at offset 0x14, then write remainder bytes
starting at offset 12. A guarded do/while with a real byte cursor closes
the source/scheduling differences except one base-address materialization:
retail independently loads the state base for the cursor, while C copies
the already materialized state base. The best bodies are one instruction
short: 228/232 and 212/216 bytes, raw 0.9483 and 0.9444 respectively.
Batch `83cba88888e3475fb43591fc493e9ae5`, cells 1 and 9, preserve those
leads. The residual branch displacement follows that missing instruction.
Further char/u8 pointer views and array-address forms in batch
`583f8d96da1d431a8e2c2ab3b2ee1b5c` do not close it. No body was installed.
Next action: investigate the actual global state/byte-buffer type context
and compiler commoning; do not add duplicate loads with volatile or patches.

`func_8F802324`: **requeue**. Eight text-insertion loop/pointer forms in
batch `b4a9fffae941443aadcc15b2157c0e84` reject. Preserve the signed cursor
and byte loads, unsigned capacity, backward shift, and scalar cursor/capacity
aliases. Do not infer exactness from its best normalized score (~0.81);
read the complete diff before the next family. These are ordinary rejected
source experiments, not tool failures or a demonstrated compiler limitation.

## 2026-10-15: resource initialization and both digit requeues resolved

Four more owners are accepted, all `link_verified: true`, normal runner
statistics/host syntax checks enabled, with combined full-ROM gates:

- `func_8F8031F8`: 78 words / 312 bytes, frame 0x30. Batch
  `b2c99a4bb2584a04a816086d45d4d485`, winner
  `f77:init-global-base:pointer-loop-False:index-first-False:unsigned-False`.
- `func_8F8012C0`: 79 words / 316 bytes, frame 0x30. Batch
  `8cb1ac1d7a974e66b6c4106944749bc1`, winner
  `f77:resource-real-release-return:address-locals-False:count-False:unsigned-stride-False`.
- `func_8F8026DC`: 58 words / 232 bytes, frame 0x18. Batch
  `25d9de48759742538904675f3a6ce6be`, winner
  `f77:editor-union:10:word-field-False:cursor-False:post-loop-True`.
- `func_8F802A68`: 54 words / 216 bytes, frame 0x18. Same batch, winner
  `f77:editor-union:16:word-field-False:cursor-False:post-loop-True`.

The initializer must derive the selected-record pointer from the already
assigned `D_8F809FA8` global, not repeat the literal `D_8F803BF4` address.
The latter was one instruction short and changed the initial scheduling /
temporary allocation. Preserve the separate zero assignments, clock-output
addresses, fourteen 0x6F8-byte resource entries and final halfword return.

The resource reader initially had 76/79 exact words, with only v0/v1 for
the post-release `D_8F809FA4` address differing. The actual
`func_80062304` definition in `src/615D0.c` returns s32, not void. Retyping
its stale extern transactionally closes the mismatch and preserves the
existing writer. Keep the real byte count stores before their word-sized
copies, slot-dependent 6/30 capacities, 0x6F8 stride and 0x58 selection stride.
No unused-return fake or extra local is needed.

The digit initializer requeues above are resolved by declaring the shared
editor state as a union of halfword, word and byte storage views. This
models the existing overlapping accesses, allocates no storage, and leaves
all fixed addresses unchanged. Index the union byte view at `index+12`;
an explicit byte cursor still shares the initial address and misses one
instruction. Preserve the guarded do/while, signed remainder/division,
fresh post-call value read, and unsigned last-digit bound. The transaction
updates five accepted callers to their same halfword view and all retain
their exact words. The word-read cast remains as accepted; merely selecting
the union word member is a distinct compiler-shape experiment.

One initial union batch could not run: synthesized old externs made a
companion edit ambiguous. Explicitly declaring the intended union symbol
in the batch preamble resolved that setup failure. These pre-compiler
diagnostics are process evidence, not failed source hypotheses. Do not
change runner deduplication or replay rejected bodies to work around them.

Post-formatting and scoped extern deduplication, fresh/20-leading-blank
controls match all sections and all fourteen C definitions against the
original assembly baseline, including the old callers and all four new
owners. A fresh normal full-ROM gate passes MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Naming plan has no known mappings.
Exactly sixteen assembly owners remain in this file, including the text
insertion requeue; no unready jump-table owner was replaced here.

## 2026-10-15: text insertion and editor/menu input accepted

Four more owners are accepted. These are all explicitly
`relocation_masked: true`, `link_verified: false`; the normal authoritative
sequential full-ROM gates pass. Do not describe them as raw instruction-exact
or link-verified object probes:

- `func_8F802324`: 37 words / 148 bytes, leaf. Batch
  `a50bf3f1814947e9b6898c8d343f3fc5`, winner
  `f77:text-view:pointer-loop-False:while-False:state-pointer-True`.
- `func_8F8027C4`: 118 words / 472 bytes, frame 0x28. Batch
  `5c8009014e4b41c7aee1070b3777b06a`, winner
  `f77:numeric-buttons:10:s32:inner-buttons-False:inner-index-False`.
- `func_8F802B40`: 115 words / 460 bytes, frame 0x28. Same batch,
  `f77:numeric-buttons:16:s32:inner-buttons-False:inner-index-False`.
- `func_8F802ECC`: 153 words / 612 bytes, frame 0x20. Batch
  `3d48646afc184ed3806aca0cad12127d`, winner
  `f77:menu-input:alias-table-False:ternary-wrap-False:switch-False`.

Add named text and numeric views to the existing state union, rather than
independent scalar aliases. Text has its signed cursor at 12, byte buffer
at 14 and unsigned capacity at 32. Numeric state has signed selection at
8, unsigned last index at 10, signed digits at 12 and word value at 20.
The explicit state pointer and named text fields preserve cursor reloads
while shifting bytes; separate scalar declarations let IDO treat the
overlapping addresses as independent. The original text-insertion requeue is
resolved. No data is allocated or moved by the type additions.

Both numeric handlers use a real word-wide D-pad result and a signed-halfword
switch input. Keep `raw = Input_GetRepeatedDPad(); input = raw;` on one
physical source line: the measured IDO source-line tie fixes the initial
schedule. Declare the real raw result before the return-status local to
preserve its 0x20 stack home, and keep button flags word-wide. A u16 button
local produces the final v0/v1 difference. Removing the full-width D-pad
result changes the nonzero test and frame; these are not dummy locals.
Digit changes wrap modulo 10/16 and confirmation folds signed digit bytes
into the unsigned word accumulator in reverse index order.

The menu handler needs the descending directional if/else chain and direct
byte views of the existing 34-byte table rows. The alias-table switch
variants have the wrong branch order. Preserve confirm/cancel priority,
sound-before-data reads, separate decrement/negative-wrap stores, and the
0x58-byte selected-record update. No helper factoring is required.

Post-formatting and scoped extern deduplication, fresh/20-leading-blank
builds reproduce every section and all eighteen C definitions against the
accepted-object baseline. The fourteen pre-existing definitions retain
their original assembly-baseline words, and all original offsets remain
unchanged. All four newly linked retail spans and the full ROM pass MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. The 23 table rows and the existing
dispatcher table bound configured numeric/text sizes to 5/11, within the
8/18-byte view arrays. Naming plan has no known mappings.

Twelve assembly owners remain. Next local lanes are the text keyboard
handler `func_8F8023B8` and range handler `func_8F801FC4`, whose assembly has
been read but no candidates submitted in this block. Establish any
jump-table or shared-lui prerequisites before replacing their dispatcher
siblings. Preserve all prior probe statistics and do not confuse advisory
stuck warnings with terminal source or compiler evidence.

## 2026-10-15: tight jump-table layout and five render/dispatch matches

The six dispatch-table owners are now layout-ready. Use the narrow ROM
window `0x36CA50..0x36CCA0` (0x250 bytes), not the planner's broad
`0x36C530..0x36D5B0` interval. The fragment header identifies relocation
offset 0x3BE0, ROM size 0x4CD0 and RAM size 0xA000. At ROM 0x36CCA0 the
1081-entry relocation table starts; its padded tail ends at the next
fragment, 0x36DD90. Preserve that tail as a separate rodata-typed subsegment.
The generated linker script gains exactly one tail-object line; the
handwritten compatibility aliases do not change.

A first window beginning at 0x36C960 failed because splat silently dropped
non-migratable format strings inside it. The tighter start crosses the
last four bytes of the existing `D_8F80397C` format string: `32 64 00 00`.
`const u32 D_8F803990[1]` represents those exact bytes, not code padding.
IDO puts a scalar const in data here; the const array is required for its
actual readonly section. The original data head now ends at that boundary.
Pinned spimdisasm 1.35.0-dev0 re-split and a normal full-ROM gate with all
six dispatchers still assembly passed. Fresh/20-leading-blank controls
preserved all eighteen C functions and all thirty original function offsets;
the owner object's rodata is exactly 0x250 bytes with the real suffix first.

Five owners are accepted after that prerequisite:

- `func_8F803130`: 50 words / 200 bytes, frame 0x20. Batch
  `86981cf3f1f44bcab22fa871ff9b8853`, winner
  `f77:dispatch-loop:sorted-False:state-pointer-False:break-loop-False`.
- `func_8F802DD8`: 61 words / 244 bytes, frame 0x20. Batch
  `46fe3ff2a1ec4a5db63ad71e4c8f4d16`, winner
  `f77:action-byte-slot:kind-local-False:early-return-False:decimal-first-False`.
- `func_8F8010E4`: 119 words / 476 bytes, frame 0x38. Batch
  `165c0f96e22c47eea6227d21bccf751f`, winner
  `f77:frame-render:pointer-loop-False:label-local-False:array-rows-False`.
- `func_8F800E50`: 75 words / 300 bytes, frame 0x30. Batch
  `49179cbe7953452cace4b6f383d4294f`, winner
  `f77:number-render:False:state-pointer-True:pointer-loop-False:glyph-local-False`.
- `func_8F800F7C`: 90 words / 360 bytes, frame 0x30. Same batch,
  `f77:number-render:True:state-pointer-True:pointer-loop-False:glyph-local-False`.

The frame renderer is link-verified and passes its combined ROM gate.
The other four are explicitly relocation-masked, not link-verified, and
pass authoritative sequential full-ROM gates. Statistics and normal host
syntax checking remain enabled. Keep loop case-body order 0,4,1,2,3;
action-switch hex/decimal/text body order and the actual byte slot alias
`D_8F809F9F`; and fresh field reads in the backwards numeric glyph loops.
The frame renderer retains its conditional slot label, device/day table
strides, optional clock, and 23-entry menu loop. Do not factor helpers or
format-pointer/glyph temporaries into the matched bodies.

The first runner gate refreshed extraction despite the preceding manual
split/build. It accepted the loop, then a later candidate's old snapshot
reinserted that loop's now-missing ASM include. That is a setup failure,
not evidence against the action-switch C. Before new candidate transactions
after layout changes, establish the runner's own extraction prerequisites
with all affected owners still assembly, not merely the Makefile build.
A fresh action batch based on the installed loop closes normally. No
runner modification or duplicate-rejection bypass was used.

Post-formatting, shared-type relocation and scoped extern cleanup, fresh/
20-leading-blank controls reproduce every accepted section and all 23 C
definitions. The original eighteen C definitions' words and all thirty
offsets remain unchanged. Five newly linked spans, the rodata window,
relocation tail and full ROM match retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Naming plan has no known mappings.

`func_8F801FC4`: **requeue**. Twenty-four new range-view, local-value,
input-reuse and coupled-field cells reject; no range view is installed.
Best raw 0.7007 / normalized 0.9781, size 548 bytes, is in the input-reuse
batch, label
`f77:range-reuse-input:left-local-True:right-local-False:status-after-half-True`.
Its first residual is the wrong frame, 0x28 versus retail 0x20; matching
total byte size is not enough. Coupled stores did not improve the whole
allocation. Next action: narrow the real selected-value temporary's scope
to the directional cases and recheck the 0x1A input / 0x1C return-status
homes before more field-order experiments. Preserve the signed selection /
origin, unsigned step/maximum and actual field writes; no dummy locals,
volatile qualifiers, padding or forced-register fixes.

Seven assembly owners remain: entry renderer `func_8F8000D0`, text
renderer `func_8F8006B0`, range renderer `func_8F800924`, editor initializer
`func_8F8015A8`, editor writer `func_8F801988`, range input `func_8F801FC4`
and text input `func_8F8023B8`.
