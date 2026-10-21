# Region notes -- src/fragments/7/fragment7_BA250.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-15

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-15

func_830073F8: time cap at 0.9808 (raw 0.7308) after 2712s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-17

func_83007218: matched (call_sequence:carrier:single_pointer_local_exact), 6 iterations, agent codex

## 2026-09-18

func_83000CB4: time cap at 1.0 (raw 0.9794) after 2400s, mismatch immediate_drift; tried families: call_sequence; tie-pool yes

## 2026-09-18

func_83002424: matched (call_sequence:rectangle_overlay:state_carrier_named_thresholds), 1 iterations, agent openrouter

## 2026-09-22

func_83009EC4: plateau at 0.9043 (raw 0.4258), mismatch operand_or_scheduling_drift; tried families: call_chain; tie-pool yes; 3 iteration(s) with a suspicious identical batch-wide failure

## 2026-09-22

func_83006798: plateau at 0.0 (raw None), mismatch section_layout_drift; tried families: dispatcher_switch; tie-pool yes; 2 iteration(s) with a suspicious identical batch-wide failure; 1 iteration(s) hit section_layout_drift -- needs a rom.yaml fix, not more candidates

## 2026-09-22

func_83006798: time cap at 0.4626 (raw 0.1963) after 2400s, mismatch operand_or_scheduling_drift; tried families: dispatcher_switch; tie-pool yes; 3 iteration(s) with a suspicious identical batch-wide failure; 2 iteration(s) hit section_layout_drift -- needs a rom.yaml fix, not more candidates

## 2026-09-22

TYPE CONFLICT: func_818036D8 is extern void func_818036D8(s32, s32, f32, s32), not extern void func_818036D8(s32, s32, s32, s32)

## 2026-09-22

func_83000F04: plateau at 0.8684 (raw 0.8684), mismatch instruction_drift; tried families: call_sequence; tie-pool yes

## 2026-09-22

func_83006F30: matched (call_sequence:aggregate-copy:pair-declared-after-carrier), 1 iterations, agent codex

## 2026-09-22

func_83007160: matched (call_sequence:switch:multiline-local-constants-exact), 1 iterations, agent codex

## 2026-09-27

func_83008960: matched (call_sequence:guard_returns:mutate_argument_index), 1 iterations, agent unbiased

## 2026-09-27

func_83001000: time cap at 0.9067 (raw 0.6933) after 2420s, mismatch instruction_drift; tried families: call_sequence; tie-pool no

## 2026-09-27

func_830022F0: plateau at 1.0 (raw 0.987), mismatch immediate_drift; tried families: call_sequence; tie-pool yes

## 2026-10-04

func_830073F8: matched (call_sequence:aggregate_copy:struct_state_buffer_array), 4 iterations, agent antigravity

## 2026-10-04

func_83008F84: matched (call_sequence:array_pointer_cast:void_ptr_local_alias), 4 iterations, agent antigravity

## 2026-10-04

func_83003320: matched (call_sequence:aggregate_copy:named_state_carrier), 6 iterations, agent unbiased

## 2026-10-04

func_83007D40: plateau at 1.0 (raw 0.9798), mismatch immediate_drift; tried families: call_sequence; tie-pool yes

## 2026-10-12

func_830094C8: matched (call_sequence:pointer_temp:unsigned_last_comma_constant_exact), 1 iterations, agent codex

## 2026-10-12

func_83000BC0: matched (call_sequence:guard_returns:byte_arguments_signed_result), 1 iterations, agent codex

## 2026-10-12

func_8300A5B4: matched (call_sequence:aggregate_copy:matched_direct_global_byte), 1 iterations, agent codex

## 2026-10-12

func_830020CC: matched (call_chain:row_render:inline_common_expressions_exact), 1 iterations, agent codex

## 2026-10-12

func_83009EC4: matched (call_chain:iteration_scope:iteration_local_indexed_pointers), 2 iterations, agent codex

## 2026-10-12

func_83000F04: matched (call_sequence:permuter:instruction_exact_result), 1 iterations, agent codex

## 2026-10-12

func_8300A50C: matched (call_chain:initialization:direct_unsigned_segment), 1 iterations, agent codex

## 2026-10-12

func_830088A0: matched (call_sequence:aggregate_copy:later_first_pointer_with_word_home), 1 iterations, agent codex

## 2026-10-12

func_83000E40: matched (call_sequence:parameter_counters:reuse_both_integer_arguments), 4 iterations, agent codex

## 2026-10-12

func_8300A208: matched (call_chain:state_reload:integer_cast_named_fields), 1 iterations, agent codex

## 2026-10-12

func_83000F04: matched (call_sequence:permuter_exact:compact_struct_spelling), 1 iterations, agent codex

## 2026-10-21

Four-owner native batch based on 271d80b1: accepted through the recorded
candidate runner and full US-ROM comparison; original ROM MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`.

- `func_830018B0` / `Fragment7_DrawSavedRecordList` (396 bytes): header byte 1
  bounds the names at byte 4 with a 68-byte stride; header byte 0 determines
  the horizontal separators. Indexed source lets IDO derive both row pointers
  and the 26-pixel vertical induction. Uses the SDK display-list macro.
- `func_83002988` / `Fragment7_DrawRecordSummary` (340 bytes): draws the first
  entry when the count at state byte `0x3D959` is nonzero, copies its draw origin, and
  draws the icon and the halfword at entry byte 12. A named, used text-alpha
  intermediate preserves the original coordinate temporary's stack location.
- `func_83008188` / `Fragment7_DrawSelectedRecordView` (264 bytes): state byte
  71 chooses the record/data pair; selections at least 4 include byte 87's
  bank offset. Load the selection inside each branch, then apply the offset
  with a compound assignment. Combining that update into the address
  expressions reverses an operand in the generated index addition.
- `func_8300A898` / `Fragment7_RunSelectionMenu` (328-byte oracle range): loops
  through selection, device checks, dispatch, and cleanup. Its state pointer
  alias preserves the state/range-pointer allocation. The C symbol is 320
  bytes; the remaining eight bytes are unchanged end-of-section alignment
  nops, included in the assembly symbol. No source padding was added.

`func_8300A81C` receives three arguments from the menu and forwards them to
the existing three-argument `func_8300A50C`. Making that call explicit is
whole-object byte-inert and removes the host-only unprototyped-call workaround.
The complete 43,456-byte text and 224-byte rodata sections and semantic
relocations agree with the original object. All other function extents agree;
the menu's verified alignment-tail metadata split is the sole size difference.
Cleanup and naming also pass fresh and twenty-blank-line whole-unit controls.

`func_83008DC0`: requeue. Ordinary aggregate-copy candidates produce the right
452-byte size but a 32-byte frame rather than the original 24-byte frame;
best raw similarity in this batch is 0.7168. Pointer aliases and signed/unsigned
integer-address spellings retain an extra shared biased-base carrier across
the sound call. The oracle copies 68 bytes using a compiler-style three-word
loop and two-word tail. Next inspect the record producers and real state
layout before choosing a typed field-access representation; do not hand-unroll
the copy or add artificial fields to force the frame. Earlier compile failures
were declaration-placement conflicts, not evidence against these source forms.

### Record collection follow-up

Four further owners accepted natively from e11cb2c1: `func_83001A3C`
(`Fragment7_DrawFirstRecordListPanel`, 360 bytes), `func_83001BA4`
(`Fragment7_DrawSecondRecordListPanel`, 520 bytes), `func_83008DC0`
(`Fragment7_SelectSavedRecord`, 452 bytes), and `func_830096B8`
(`Fragment7_InitializeRecordCollections`, 488 bytes). Every owner passed the
recorded runner and full US-ROM comparison. The selector requeue above is closed.

The list layout is witnessed by `func_8300AA58` clearing 548 bytes and setting
capacity 5 or 8, and by `func_8300AAD4` / `func_8300AB58` copying 68-byte
entries after the four-byte header. Thus each list reserves eight entries;
the first list uses only five. Those functions are in
`src/fragments/7/fragment7_C4C10.c` and its matching assembly owners. The
selector's typed list accesses recover its original 24-byte frame without
an artificial base pointer, manual copy loop, or source padding.

The initializer's paired blocks are 548, 7012, and 4356 bytes, from the
clearing sizes in `func_8300AA58`, `func_8300AEEC`, and `func_8300B330`.
Together they occupy 23,832 bytes. The initializer copies that complete region
from state offset `0x39E48` to the snapshot at `0x34130`; `func_83009EC4`
independently compares the same paired block sizes and complete snapshot range.
The typed views leave preceding/intervening bytes explicitly unknown. Reusing
the early title-result pointer and expressing repeated collection addresses
directly lets IDO synthesize its original temporaries and 56-byte frame.

The panel defaults are eight-byte rectangle objects, copied with aligned word
loads. Table rectangles start at `D_8300C01C + index * 24 - 18` and require
unaligned loads. Declare the default objects as rectangles directly rather
than casting a byte/word array address. The second panel's two-instruction
argument-preparation residual is source-line-sensitive: an ordinary one-line
guard around its single list-draw call matches. No multi-statement line group,
line-number pragma, instruction rewrite, or register constraint is retained.

All original game section bytes, function extents, and semantic relocations
agree in the frozen first-success objects. Cleanup, naming, and twenty-blank-line
controls preserve that complete-object result. Seventeen target-compiler layout
assertions check record/list/collection sizes and the used state-field offsets.

### Navigation and status follow-up

Four further owners accepted natively from ff25a234, totaling 1392 bytes:
`func_83008740` / `Fragment7_DrawRecordStatus` (260 bytes), `func_83008A68` /
`Fragment7_SelectTeamRecord` (336 bytes), `func_83008BB8` /
`Fragment7_HandleTeamListScroll` (352 bytes), and `func_830090D0` /
`Fragment7_HandleRecordListScroll` (444 bytes). Each passed the recorded runner
and full US-ROM comparison, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.

The team selector needs separate pointer-stride additions for the selected row
and scroll offset. Plain repeated multiplication by 1168 instead shares a
multiplier and emits `multu`. Ordinary pointer arithmetic on the already
established `Fragment7TeamRecord` reproduces the original shift/add sequence.

Bytes 87/88 are the current/target team-list scroll offsets: byte 87 is added
to record selections at least 4, and the callback scrolls upward at selection
4 or downward at selections at least 6. Bytes 89/90 are the other list's
current/target scroll offsets; its limit subtracts three from the source
slot-count byte at `source_bank * 7012 + 0x3872C`. Both callbacks advance the
shared interpolation at `0x4E03C`
using `func_818006B4() * 0.125f`. Preserve fresh field reads after the readiness
callback. A conventional typed state view of the opaque callback argument
reproduces the latter callback's 24-byte limit spill home without random
partial aliases, extra scalar locals, register constraints, or source padding.

`Fragment7_DrawRecordStatus` copies the 32-byte text record at `D_8300EE88`
and chooses archive entry 79, 80, 78, or 81 from the message selector at
`0x3FF1C`. Its existing per-file rodata migration already owns `jtbl_8300FBA8`,
so an ordinary C switch works. The layout follows the actual
`Fragment4TextRecordView` consumer in `src/fragments/4/fragment4_AFAA0.c`.
All complete original game bytes, extents, and semantic relocations are
preserved; cleanup, naming, blank-line controls, and 15 target layout assertions
pass. Stack-residual searches must use decomp-permuter's `--stack-diffs`:
its default scorer reported zero for a body still spilling at 28 rather than 24.

`func_83008290`: requeue. A natural six-iteration aggregate loop over 88-byte
entries matches the first 117 instructions exactly, including ID lookup and
the real two-argument `func_8005DC48(controller, destination)` call. The source
array begins at `0x3FB60`; destination entries begin at byte 16. The remaining
fallback copies the first byte of the empty-name resource `D_8300F924`.
Scalar-load spellings produce 512 rather than 516 bytes because IDO folds
the low relocation into the byte load; the oracle first materializes the
resource address. Explicit pointer aliases fold the same way. `strcpy`,
`memcpy`, and `bcopy` spellings retain calls. Empty literal probes additionally
introduce non-text section drift, so those probes do not establish a match or
an owner-wide impossibility. Next investigate the resource/address-materialization
representation or frontend lineage while preserving the verified aggregate
loop. Do not resume the earlier four-record/manual word-copy candidates.

### Remaining switch-table ownership and follow-up

Extended the existing `fragment7_BA250` rodata subsegment from ROM `0xC9E10`
through `0xC9EF0`, moving the trailing shared-rodata start rather than adding
a second rodata segment for the same object. This migrates `jtbl_8300FBE0`,
`jtbl_8300FC08`, and `jtbl_8300FC30` to their three real assembly owners. The
pinned spimdisasm 1.35.0-dev0 split and still-assembly full-ROM gate pass with
the original MD5. The generated linker diff is only the shared-tail object's
`C9E10` to `C9EF0` filename change; foreign source changes were hash-preserved.

`func_830095B8`: accepted, 256 bytes. The ordinary switch handles cancel -1
and selections 1 through 8. The record-bank header has its count at byte 1,
followed by eight 544-byte records at byte 4, for a 4356-byte bank stride.
The bank selector is state byte 63; source collections start at `0x3C854`.
Typed header and record access reproduces both bank address computations.
Flat byte offsets wrongly share a biased base across the count guard and
produce only 232 bytes. The opaque callback argument's typed state view
preserves the record pointer's stack home. Acceptance includes the full-ROM
gate and an immediate full-TU/four-distinct-collateral-object freeze.

`func_83009BD0` / `Fragment7_OpenRecordPanel`: accepted, 756 bytes. A typed
state view restores the three record-index load orders and the panel-pointer
reload at `0x3FF00`. Keeping the resource parser/allocation locals in their
own lifetime scope restores the context spill at `36(sp)` while preserving
the parser result at `44(sp)` and allocation pointer at `48(sp)`. An extra
mode scalar expands the frame to 64 bytes and is not the answer. A calibrated
45-second native permuter run with `--stack-diffs` stayed at score 8; its
base matched all 189 masked instruction words and relocation topology of the
retained native probe. The accepted source uses normal live scopes instead.

Postacceptance cleanup gives this initializer its concrete pointer parameter
and updates all same-file prototypes, removing repeated opaque-pointer casts.
The selector is named `Fragment7_SelectOtherRecord` and reuses the existing
544-byte record / 4356-byte bank types rather than a duplicate matrix view.
Fresh, cleanup, naming, blank-line controls, and 14 target-layout assertions
preserve every original game byte, function extent, and semantic relocation.
Both owners passed the recorded runner and full-ROM gate, totaling 1012 bytes.

`func_83008290`: requeue update. Twenty-three additional probes tested a
one-byte fixed-length copy, separate versus reused copy indices, signed versus
unsigned trip counts, and the proposed builtin copy names. None accepted.
Reusing the aggregate-loop index changes its unrolling; independent counters
preserve the good prefix but retain a byte loop (540/544 bytes). The tested
`__builtin_memcpy` and `__builtin_bcopy` names remain calls (520 bytes), not
intrinsics. The earlier 512-byte scalar body remains the best source-level
baseline. Next inspect authentic frontend/block-copy lowering; do not use a
fabricated one-byte name struct, forced address bias, or instruction rewrite.

`func_8300A2CC`: requeue. Ordinary frame-dispatch candidates preserve the
incoming result argument, which is also the default returned value. The
controller context at state `0x4E044` is initialized by `fragment3_main`;
its selection at +8 is the field tested against -1. Cached current/target
bytes and the real five-case switch reach 400 bytes, but the oracle accesses
the interior workspace using a `0x7FFF` pointer bias while raw offsets and
typed workspace/whole-root views lower the large address differently. Whole-root
views are not evidence of an impossible owner. Next isolate the frontend's
large-member addressing mechanism; do not encode the bias by hand just to match.

### Grid scrolling, panel movement, indicators, and comparison refresh

Four owners accepted natively from `47a4cfa5`, totaling 1608 bytes:

- `func_830022F0` / `Fragment7_HandleTeamGridScroll` (308 bytes): preserve both
  real current/target snapshots as signed word locals. Reading the target
  snapshot in the comparison and in the input branch's increment/decrement
  restores the one reversed branch operand. Reload the target after the
  interpolation callback before committing current. State row is byte 75;
  current/target are bytes 87/88 and progress is at `0x4E03C`.
- `func_830061BC` / `Fragment7_RefreshRecordCompatibility` (332 bytes): use the
  selection field directly in the source-record address before choosing the
  reference row. A separate selection scalar survives the row phi and adds
  an unwanted `move a3,v0`. Mode is byte 31, bank/row bytes 63/67, selection
  byte 81, and saved-count byte `0x3A06D`. The source records have 68-byte
  strides; reference banks/records have 4356/544-byte strides.
- `func_83007D40` / `Fragment7_DrawSlidingRecordPanel` (396 bytes): the typed
  state view restores interpolation and the callback-safe panel-pointer reload.
  The real byte-sized target snapshot is read again after the first indicator
  draw. Its consumed comparison with current restores the branch operand order.
  The coefficient is an ordinary `311.0f` literal: referring to the old
  `D_8300FBA4` assembly symbol can text-match but drops the constant's own
  rodata contribution and fails the ROM gate. No such body was accepted.
- `func_8300928C` / `Fragment7_DrawRecordListIndicators` (572 bytes): ordinary
  `gSPDisplayList` and `gDPSetEnvColor` SDK macros reproduce the command writes
  and unsigned alpha conversion; no hand-written command words are needed.
  Put the real state view before the weight local to preserve `48(sp)`.

Every acceptance includes the recorded native runner, full-ROM gate, and an
immediate externally hashed full-TU/four-distinct-collateral-object freeze.

Postacceptance cleanup uses the repository's exact-extern deduper on this
owned file and replaces the indicator header's raw offsets with its verified
fields. Complete original game bytes, function extents, and semantic
relocations agree for every frozen acceptance, declaration cleanup, naming,
blank-line control, and all 20 target-layout assertions. No source padding,
register constraints, dummy locals, or instruction/relocation rewrites were
introduced.

`func_8300A2CC`: requeue update. Stock-driver fixtures now distinguish the
mechanism: both IDO 7.1 and 5.3 emit the `+0x7FFF` / positive-displacement
sequence for pointer arguments but fold direct-global accesses to a different
high/low address shape. The 7.1 fixture path first reproduced the complete
known game object and its blank-line control. Twenty-four new recorded game
probes tested integer-address carriers, use-region lifetimes, and a typed
external workspace. None accepted; carriers can restore an indirect address
but keep a biased base live across callbacks and add spills. This is not a
compiler-impossibility claim. Next isolate address-identity/rematerialization
at a calibrated frontend/backend boundary rather than adding a fixed bias or
replaying the failed carrier families.

### Collection compatibility and team visual resources

Two owners accepted natively from `2417016b`, totaling 688 bytes:

- `func_83000CB4` / `Fragment7_RefreshCollectionCompatibility` (388 bytes):
  checks four records at `0x3FD74` and the saved records at `0x3A070`, with
  68-byte strides. Results go to the word arrays at `0x3FED0` and `0x3FEE0`;
  unused saved slots through index 7 are cleared. The saved count is byte
  `0x3A06D`. Each record is checked against the six 88-byte entries at
  `0x3FB60` and, when supplied, the other deck's entries at byte 16.
  `func_83000274` clears eight bytes, stores the checked-record pointer at
  byte 0, and writes the reason/masks at bytes 4 through 7. Its actual
  eight-byte result object and normal indexed loops reproduce the original
  88-byte frame, including the result at `76(sp)`. A four-byte scalar scratch
  object is insufficient. Making the helper's three-argument integer-return
  prototype visible before `func_830009D8` is whole-object byte-inert.
- `func_83001000` / `Fragment7_LoadTeamVisualResources` (300 bytes): traverses
  two 7012-byte banks, up to six rows per bank, and two parts per row. Each
  row is 1168 bytes; its two 476-byte parts select resource/index bytes at
  offsets 11/12. An ordinary pointer to the row's parts, used by the inner
  loop, gives IDO the original source-address lifetime. The destination
  array starts at state byte 96, and each slot holds all 8200 resource bytes.
  `func_8004E0F0` loads an 8200-byte resource chunk into that destination;
  see `src/4CC20.c`. No manually unrolled loops are needed.

Each acceptance passed the recorded runner and full US-ROM comparison, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`, with an immediate externally hashed
full-TU/four-distinct-collateral-object freeze. Declaration cleanup, the
concrete visual-state parameter, naming, twenty-blank-line controls, and 21
target-compiler layout assertions preserve all original game section bytes,
function extents, and semantic relocations.

`func_8300112C`: requeue. The real stream records are 88 bytes, not the old
64-byte draft buffer. Ordinary aggregate assignment, a six-entry limit, and
3200-byte output slots now reach the original 576 bytes and 168-byte frame.
Controller home is `156(sp)`. Best raw similarity is 0.9931: only the two
adjacent instructions at offsets 404/408 (`subu t9,t9,s3` and
`ori at,at,0xFB60`) are reversed. The retained parent is candidate 3 of
`native-f7-deck-controller-home-batch`; typed-state candidate 0 of
`native-f7-deck-typed-range-batch-v2` reaches the same frontier. A calibrated
native permuter reproduced all 144 masked parent words and relocation
topology, then reached zero only with a multi-statement line group spanning
the clearing loop and output setup. That proposal was not installed.
Normal iterator-preparation orders, scoped initializers, real-size expression
forms, clear-loop spellings, and cursor-loop/guard variants did not close the
residual. Some alternate cursor loops regress to 584--600 bytes or a 160-byte
frame. Next isolate source-line assignment at the assembler scheduling
boundary using the retained exact parent and blank-line controls; do not
add register constraints, rewrite instructions, or replay the old 64-byte
buffer/manual-copy families. Early prototype-placement failures are context
diagnostics, not evidence against the record-layout hypothesis.

`func_83008290`: requeue update. An integer native-address view of
`D_8300F924` now restores its explicit high/low address materialization and
the original 516-byte size. All instructions except the final fallback
byte load/store agree: target uses `t8`, candidate `t7`, raw 0.9845.
The calibrated 129-word native permuter proposal adds an identity index and
redundant byte mask, so it was rejected as source. Readable consumed name
buffer/value carriers do not close that temporary allocation. Next inspect
UGEN allocation/free events on that exact retained parent; preserve the
already verified six-entry aggregate loop and real callee signatures.

`func_83007788`: requeue. Eight new typed export candidates use the actual
88-to-60-byte `func_80051864` conversion and a real 12-byte name buffer,
but produce 376--380 rather than 348 bytes; best raw 0.5579. The original
counts occupied entries before conversion and stops after six. Next isolate
the count-loop topology and controller lifetime, checking the caller
`func_830078E4` before making any interface change. Its visible call prepares
only two arguments. No candidate was installed.

### Controller decks, team construction, and team actions

Three owners accepted natively from `8c559bb`, totaling 1468 bytes:

- `func_8300112C` / `Fragment7_LoadControllerDeck` (576 bytes): opens the
  controller's type-32 stream, normalizes and filters 88-byte entries, copies
  at most six using ordinary aggregate assignment, and clears unused species.
  When the panel is open, it builds the corresponding 3200-byte visual slots
  and copies or clears the 16-byte controller identity. The final scheduling
  residual is closed by initializing the consumed input/output byte-range
  pointers in one declaration. A conventional continuation after `*end =`
  preserves the match. The output loop advances real 88/3200-byte strides;
  there is no multi-statement line group, fake local, instruction rewrite, or
  manually unrolled copy. The earlier requeue is closed.
- `func_83007788` / `Fragment7_BuildControllerTeam` (348 bytes): fills the
  trainer ID and encoded name, scans up to six occupied entries, converts
  them from 88 to 60 bytes with `func_80051864`, clears remaining species,
  sets the active/flags bytes, and copies text resource 41:41 into the label.
  The 60-byte entry's species is at byte 0. The name decoder's real buffer
  holds eleven bytes: `func_80060E48` decodes ten characters plus a terminator;
  see `src/615D0.c`. Declaring that consumed buffer before the counters restores
  its original `76(sp)` home. A bounded scan with an early break restores
  pointer induction; the prior empty-loop spelling retained multiplication.
  The original stores incoming `a2` at `96(sp)` and never reads that home;
  the C preserves this unused third argument. `func_830078E4` carries its rule
  pointer in `a2` into the fallback call. The earlier export requeue is closed.
- `func_83007568` / `Fragment7_HandleTeamActions` (544 bytes): handles cancel,
  a complete 1168-byte team copy, the next-mode action, and a 68-byte rule
  copy from team offset `0x424`. Banks have a four-byte header and six teams,
  with a 7012-byte stride; their first team is at state `0x382A0`. The panel
  pointer at byte 56 must be reloaded after the aggregate copy before writing
  its changed word at byte 16. For the rule-only source, use a signed byte
  offset for the row and an unsigned object-size offset for scrolling.
  Writing both multiplications in the unsigned domain makes IDO share a
  multiplier and emits `multu`; the oracle uses independent shift/add chains.
  `(s32)sizeof(Fragment7ActionTeam)` expresses the real signed row stride
  without a duplicated numeric size or hand-written strength reduction.

Every acceptance passed the recorded native runner and full US-ROM gate,
MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`, with an immediate externally hashed
full-TU/four-distinct-collateral-object freeze. Complete original game section
bytes, function extents, and semantic relocations agree for all three frozen
objects. Cleanup shares the verified deck-state view between loading and
export, gives the row stride its actual object size, and deduplicates externs.
Cleanup, naming, blank-line controls, and 31 target size/offset assertions pass.

`func_830078E4`: requeue. Ordinary 1168-byte and 476-byte aggregate copies
now reach the original 768-byte size. The rule pointer is genuinely preserved
across `func_80071250` and passed to the controller-team fallback. Compute the
selected team before snapshotting the previous panel destination. On the
saved-part path, reload `state->panel->team` after the rule predicate; the
cached previous pointer is used only by the fallback. Reusing it for the
saved-part copy drops one real pointer load and changes subsequent temporaries.

Best raw similarity is 0.9792, candidate 0 of
`native-f7-team-swap-fresh-output-batch`. A relocation-masked raw comparison
finds exactly four differing words: entry/exit adjust the frame by 56 rather
than 64 bytes; offsets 636/640 use `s1` rather than `v0` for the rule-only
source-address intermediate. All other instructions, including both part-copy
loops, agree. The actual previous/rule spill homes already match `48(sp)` and
`36(sp)`. Separate scoped source pointers and integer/byte address views
retain this scalar score, but the expanded raw comparison below distinguishes
their register improvement from the remaining frame/spill differences. A consumed fresh
destination carrier can give the 64-byte frame but moves the previous home
to 52 or 56 and changes temporary allocation, so it is not an acceptance.
A calibrated 60-second native permuter run reproduced all 192 masked parent
words and relocation topology; best score 8, with an identity-XOR proposal
rejected as source. Next inspect the exact parent's web coalescing and live
scopes; do not pad the frame, force registers, add dummy locals, or restore
the old incomplete/manual-copy drafts. No body for this owner was installed.

### Team-part and record actions

Two owners accepted natively from `b15f76e`, totaling 1388 bytes:

- `func_830078E4` / `Fragment7_HandleTeamPartActions` (768 bytes): copies the
  selected 1168-byte team, preserves the rule argument across the predicate,
  copies the two real 476-byte parts, or builds a controller team on fallback.
  The old destination snapshot is used only by that fallback; the saved-part
  branch reloads the current panel destination. A separate short-lived rule
  source, a typed view of the opaque callback argument, and the real local
  declaration order reproduce the 64-byte frame and `48(sp)` / `36(sp)` homes.
  No padding, dummy locals, identity arithmetic, or register constraints are
  needed. The requeue above is closed.
- `func_83008494` / `Fragment7_HandleRecordActions` (620 bytes): cancellation
  refreshes compatibility for the selected 544-byte record; selections 1--3
  copy that record, build a profile, copy the selected 68-byte rule, and set
  the panel side/changed state. Panel fields at bytes 8/12 are pointers to the
  destination buffers, not embedded buffers. Bank 2 uses state byte 67 minus
  one for the record index; other banks use index zero. The incoming selection
  remains live for `3 - selection` across both calls. Direct bank-field reads
  on cancellation keep its temporary independent from the cached bank used
  by the later copy, restoring the original `v1` bank / `v0` index assignment.

Both owners passed the recorded native runner and full US-ROM gate, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`, with an immediate externally hashed
full-TU/four-distinct-collateral-object freeze. Every original game section
byte, function extent, and semantic relocation agrees in the frozen objects.
Postacceptance cleanup shares the actual team/record layouts, names state
byte 78 as the part selector, and uses signed object sizes for row strides.
Cleanup, naming, blank-line controls, and 36 target-layout assertions pass.

The resource-buffer view now gives `Fragment7TeamVisualState` its real
96-byte leading state header followed by full 8200-byte slots. The bank/row/part
strides remain 98400/16400/8200, and the team banks still start at `0x3A290`.
`func_8004E0F0` writes all 8200 bytes, so the prefix belongs before the array,
rather than shortening every slot's content member to 8104 bytes. This layout
cleanup preserves the complete original game object, including
`Fragment7_LoadTeamVisualResources`; it is not another candidate acceptance.

Raw comparison and passive optimizer controls are decisive for future ties:
the independent rule-source parent had the same 0.9792 scalar score as the
shared-source parent, but their four differences were different. The shared
parent differed at frame adjustments and offsets 636/640 (`s1` versus `v0`);
the independent parent already fixed the registers and differed at frame
adjustments plus the rule spill at offsets 296/304 (`32(sp)` versus `36(sp)`).
Stock/off/on/blank controls passed for the complete known game object and
three exact retained parents before interpreting optimizer color/stack logs.
Combining the independently verified source view and callback view left only
the previous-pointer home; reordering its real declaration closed that pair.
The private harness now reports concrete non-relocation word differences,
with checked four-word and identical-object controls; it changes diagnostics,
not acceptance or compiler behavior.

`func_83008290`: requeue update. Eight valid new layout/view candidates tested
signed versus unsigned ID storage, the shared 88-byte deck entry, and the
verified controller-state view. All remain 516 bytes with exactly two differing
non-relocation words: the fallback load/store at offsets 488/492 use `t7`
rather than `t8`. An omitted identifier replacement in two generated probes
was repaired and those two probes rerun; it is a generator diagnostic, not
an owner-wide limitation. Next capture a calibrated UGEN temporary allocation
and free trace against one exact retained parent, including an emission-to-
object map before interpreting event ordinals. Do not repeat these layout
views or accept an identity-mask/index workaround.

`func_83000AA4` / `func_830013A8`: layout-prerequisite. Their actual jump tables
`jtbl_8300F958` / `jtbl_8300F9FC` remain in `fragment7_data.data.s`, at ROM
`0xC9B88` / `0xC9C2C`. The per-file `.rodata` subsegment currently begins only
at ROM `0xC9D30` (VRAM `0x8300FB00`). Between the two early tables and that
boundary, `D_8300FAA8` through `D_8300FAFC` form an 88-byte floating-constant
pool. Next plan ownership of both tables and that intervening pool together,
then re-split with the pinned tool and full-ROM-gate the still-assembly
owners before sending C switch candidates. Extending the existing per-file
subsegment must not create a second overlapping `.rodata` output for this
source or drop constants used by already accepted functions.

### Profile fallback: calibrated temporary-allocation handoff

`func_83008290`: requeue. A passive UGEN observer passed ten complete-game-
object controls: known source and one exact retained 516-byte parent, each
under stock, stock plus twenty blank lines, observer off, observer on, and
observer on plus twenty blank lines. The actual procedure mapping is 110 for
the known record-action callback and 108 for this retained profile parent;
these numbers are not reusable for another input without recalibration.

Decoded operands and blank-control events map emission 129 to the trainer-ID
clear at object offset 480, emission 131 to the split address materialization
at offsets 476/484, emission 132 to the byte load at 488, and emission 133 to
the byte store at 492. Emission ordinal is therefore not an object-word index.
The address consumes temporary register 25. Its release leaves register 15 at
the queue head, followed by register 24; the load consumes 15 (`t7`), whereas
ground truth uses 24 (`t8`). This is measured temporary-allocation evidence,
not an inference from a normalized score.

Eight new natural fallback-topology candidates did not close it. Reversing
the byte/ID writes or initializing a consumed byte before the ID write moves
the ID store and leaves four differing words. A consumed initialized byte
after the ID write preserves the original schedule but colors the byte into
`v0`, still leaving two differing words. Separately initialized native-address
pointer views retain the original `t7` pair. Ordinary one-byte `memcpy`/`bcopy`
with native resource-address views retain a real call and grow to 520 bytes.
No candidate was installed; all of the earlier aggregate-copy words remain
matched. Next trace a source topology that changes a real allocation/free
boundary while preserving the fallback store order; do not rotate the free
list with identity operations or invented one-byte aggregate types.

Earlier jump-table planning also needs the actual aligned cut: the first
table starts at `0xC9B88`, not a 16-byte boundary. Widening to `0xC9B80` includes
the two zero-valued title resources `D_8300F950`/`D_8300F954`, referenced by an
already accepted later callback. Their ownership and the already accepted
float-resource references must survive any re-split; do not simply move the
subsegment to the unaligned table start.

### Earlier tables: held-item classification and mode header

Two owners accepted natively from `ec16bcd`, totaling 1072 bytes:

- `func_83000AA4` / `Fragment7_ClassifyHeldItem` (284 bytes) returns a held-item
  category using the item's effect byte from `func_80063660`, with special
  item groups in the original jump table. The name is supported by consumer
  `func_83000BC0`: category 5 requires item/species pairs including Light Ball
  with Pikachu (item 163, species 25), Lucky Punch with Chansey (30, 113),
  Thick Club with Cubone/Marowak (118, 104/105), Stick with Farfetch'd (105,
  83), and Metal Powder with Ditto (35, 132). The effect is an ordinary `u8`;
  retaining an extra wider result changes its masking and branch shape.
- `func_830013A8` / `Fragment7_DrawModeHeader` (788 bytes) copies the actual
  32-byte text descriptor, selects its entry by state byte 31 and bank bytes
  61--63, draws four texture records and the two offset background rectangles,
  then draws the selected text with the saved weight. Explicit no-op cases
  0/1 preserve the original zero-based table. A real display-list cursor,
  consumed by `gSPDisplayList`, declared before the weight and text descriptor,
  gives the original 104-byte frame, record at `64(sp)`, and weight at
  `96(sp)`. Direct macro postincrement gives the same non-stack instructions
  but a 96-byte frame and weight at `60(sp)`; no padding or dummy local is
  involved in the accepted source.

The earlier layout prerequisites above are closed. The existing per-file
rodata window now begins at ROM `0xC9B80`, covering the two original title
resources, both early tables, the intervening floating constants, and the
already migrated later tables through `0xC9EF0`. The title resources remain
ordinary data-only assembly includes, with no text section or function code.
The six constants used by accepted list-panel callbacks are ordinary
`0.01f`/`0.99f` literals, emitted at their original pool positions. No symbol
address override, additional rodata output, or linker-script edit is needed.

Before adoption, the pinned splitter's isolated baseline reproduced the
known whole object. The migrated layout and its twenty-blank-line control
then linked all 43456 original text bytes and 880 rodata bytes directly to
the corresponding US-ROM ranges, with every function extent unchanged.
After a normal re-split, the still-assembly switch owners passed the full-ROM
gate before C probes began. The first classifier generator omitted the
out-of-table item-173 case; the repaired batch included it. This was a
generator defect, not evidence about the compiler or an accepted program.

Each new owner's first successful gate froze the complete changed object,
four distinct collateral objects, source, ROM, ELF, and linker output;
external SHA-256 checks completed before another compile. Both frozen
objects, extern deduplication, shared text/origin layouts, naming, and
twenty-blank-line controls preserve all original game section bytes,
function extents, and semantic relocation targets. All nine target-compiler
layout assertions passed. The linked US ROM remains byte-identical, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`.

### Record-panel initialization and profile rows

Two owners accepted natively from `61d2f6a`, totaling 1544 bytes:

- `func_830098A0` / `Fragment7_InitializeRecordPanel` (816 bytes): clears the
  actual `0x4E070`-byte state, checks the controller, initializes the 43 widget
  definitions, copies four distinct 68-byte rule resources (IDs 5/12/10/0),
  restores the saved configuration when present, and initializes the record
  collections. The controller flags use an unsigned domain independently
  from the signed invalid-controller boolean; combining their constant-one
  stores loses an instruction and changes subsequent temporary allocation.
  The cleared byte is state byte 82, not scroll byte 88.
- The saved configuration is one real 31-byte, byte-aligned aggregate at
  panel byte 28 and state byte 60. It contains the controller at byte 0,
  cleared byte at 22, restored mode at 26, and three scroll bytes at 28--30.
  One ordinary assignment emits seven unaligned word copies plus the three
  trailing byte copies. A 28-byte copy followed by three independent scroll
  assignments reproduces the instructions but leaves a temporary-register
  residual; splitting this aggregate is the wrong source model. The panel
  parameter's stale integer prototype is repaired in the same runner
  transaction, and its accepted caller uses an explicit native-address view.
- `func_83003F40` / `Fragment7_DrawProfileRecordRow` (728 bytes): derives the
  one-based row from the 52-byte widget-definition stride, selects the
  544-byte record from a 4356-byte bank, and draws its name, trainer ID,
  texture record, and resource thumbnail. Later modes delegate to
  `func_830034C8`. The one-based byte anchor `0x3C638` equals the first real
  bank start `0x3D958` plus the four-byte header minus one 4356-byte bank
  and one 544-byte record. Its unsigned
  row-byte stride keeps the actual row number distinct from the zero-based
  array index; the signed form cancels the increment and changes the count
  comparison and address shape.
- Using opaque state/origin callback inputs with actual decoded local views
  gives the original 80-byte frame. Direct typed parameters otherwise match
  every instruction but use a 72-byte frame; the only four differences are
  the frame entry/exit and incoming definition's store/load offsets. Extra
  display-list cursor and shared-alpha variants do not repair that frame.
  No unused locals, frame padding, forced registers, or fabricated interfaces
  are needed. The 544-byte profile layout is shared with the existing other-
  record copy type after complete-object verification.

Both owners passed the recorded native runner and full US-ROM gate, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Each first successful gate immediately
froze the changed complete object, four distinct collateral objects, source,
ROM, ELF, and linker output; independent SHA-256 checks finished before
another compilation. Hoisting the real layouts, naming configuration bytes,
sharing the profile record, fixing the caller address view, naming functions,
and twenty-blank-line controls preserve every original game section byte,
function extent, and semantic relocation. All 30 target-compiler layout
values were verified from emitted object data, including the complete
state extent, 31-byte settings, and panel size 60 including alignment. An
intentional invalid-array control confirms that IDO only warns on negative
array bounds; successful compilation alone is not a layout assertion gate.

`func_83008290`: requeue. Eight character-signedness probes did not close the
fallback byte-copy residual. Explicit signed-byte views produce `lb`, which
is the wrong opcode; ordinary `char` views retain `lbu` but still allocate
`t7` instead of `t8`. The destination text-byte signedness is inert here.
Keep the calibrated UGEN emission/queue evidence above as the next diagnostic
basis; do not repeat these character views or install the nonmatching body.

### Team-list rendering and real collection-bank views

`func_83004CBC` / `Fragment7_DrawTeamListRows` accepted natively from
`9e6ef8e` (772 bytes), for publication on `b4b4ca7`. The callback interpolates
the scroll position, derives the widget row from a 52-byte definition stride,
and draws one compact row or two full rows through `func_830043F0`. It uses
the existing 8-byte rectangle and 8200-byte visual-buffer layouts. Modes
11/12 at both transition endpoints use full weight; weights below the
original double-precision `0.01` cutoff skip drawing.

The integer index first carries the truncated scroll position across
`WidgetResources_DrawRecords`, then becomes the drawing-loop index. The
floating visible-row accumulator is initialized from that integer before
adding the widget row. These real lifetime boundaries remove an extra float
move and reproduce the saved-float allocation. Decoding the origin callback
pointer locally and declaring the rectangle before the bank pointer gives
the original 168-byte frame and rectangle at stack byte 132. No dummy locals,
forced registers, instruction rewrites, or padding are used.

`Fragment7_InitializeRecordCollections` and the bank-selection callbacks
establish two real team banks beginning at state byte `0x3A290` and two
profile banks beginning at `0x3D958`. Logical bank selectors are 1/2. Team
row selectors are also one-based. The action, profile-display, and
other-record-selection views now describe those actual two-element arrays
and subtract one from selectors. In particular, a two-element array based
at `0x3829C` with an unsubtracted selector 2 extended past its declared
bounds; a three-element profile array based at `0x3C854` included a shifted
anchor rather than a real extra bank. All corrected views preserve the
complete original object, including previously accepted functions.

Target-compiler emitted-data controls verify 30 sizes, offsets, array
counts, and selector-derived addresses. Team bank 1/row 1 addresses
`0x3A294`, bank 2/row 1 addresses `0x3BDF8`; profile bank 1/record 0
addresses `0x3D95C`, bank 2/record 0 addresses `0x3EA60`. Visual storage
begins at byte 96 with 98400-byte bank and 16400-byte row strides. The
fixture's extra data is excluded only when checking the unchanged game
sections; all positive compiler logs are checked for invalid-array warnings.

The first successful runner gate immediately froze the complete changed
object, four distinct collateral objects, source, ROM, ELF, and linker
output. External hashes were checked before another compilation. Extern
deduplication, layout formatting, naming, and twenty-blank-line controls
preserve all original game section bytes, function extents, and semantic
relocations. The final normal US-ROM gate remains byte-identical, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`.

`func_83008290`: requeue. The calibrated two-word fallback byte-copy
register residual remains unresolved. The team-list renderer is accepted
and must not be sent as a new candidate. Continue with its remaining
row-rendering sibling `func_830043F0`, using the proven real-bank and visual
layouts rather than shifted array anchors.

### Team-detail renderer: record layout and optimizer handoff

`func_830043F0`: requeue from `455a87f`. This 2252-byte renderer draws two
476-byte team parts, each with six 60-byte creature records. A part's
trainer ID is at byte 36 and creatures begin at byte 40. Within a creature,
species/item are bytes 0/1, level is byte 29, and the displayed encoded name
begins at byte 36. The enclosing 1168-byte team has flags at `0x464` and
display text at `0x468`. Held-item markers are enabled by flag `0x04000000`;
`func_83000BC0` chooses their highlighted versus gray environment color.
The level sprite cache uses 19200-byte part and 3200-byte creature strides
from state byte `0x3FF38`.

The title resources at `D_8300F8D8`, `D_8300F8E0`, `D_8300F8E8`, and
`D_8300F8F0` are eight-byte text settings: word mode at byte 0 and spacing,
line-spacing, and font bytes at 4/5/6, consumed by `func_8180351C`.
Target-compiler emitted-data checks verify 20 record/style sizes and
offsets. Their context and blank-line controls preserve the complete game
object; the extra fixture data alone is excluded from the game comparison.
These layout results do not establish a matching renderer.

Forty-eight recorded game probes tried indexed/pointer creature walks,
loop predicates, scalar versus complete title settings, direct/local
argument views, shared versus separate grid scopes, coordinate lifetimes,
signed/unsigned pixel strides, and unsigned-alpha hoisting. None accepted.
The highest normalized score is 0.9396, but its raw bytes still differ
substantially. A retained natural parent has raw 0.5808, 2200 bytes versus
2252, and the original 336-byte frame. Text-buffer capacities 128/180 are
draft hypotheses, not recovered bounds; obtaining a matching frame alone
does not prove either capacity or the original local layout.

The decisive structural residual is a shared multiplier: the draft keeps
82 in a saved register and emits `multu`, while the oracle expands that
stride separately at the grid sites. Early title-setting addresses are
also kept across calls in the draft instead of independently rematerialized.
Several remaining differences follow these choices, so declaration-only
permutations are not a sufficient next hypothesis.

A bounded 45-second native permuter search first reproduced all 550 masked
instruction words and relocation topology of that exact parent. Its best
score reduction used empty conditions, and another used a synthetic
constant-one carrier in SDK macro expansions; both were rejected as fakes.
The useful unsigned-alpha hoist was rewritten with ordinary SDK macros and
tested through the recorded runner, but did not accept.

Passive optimizer observation is now calibrated with ten complete-object
controls: known accepted source and the exact retained parent, each under
stock, stock-plus-blank-lines, observer-off, observer-on, and
observer-on-plus-blank-lines. Procedure order was checked against the
stock driver's complete listing. In the parent, procedure 52 / color event
29 has the constant-82 expression and receives internal color 22. This is
an optimizer color identifier, not an unverified MIPS register number.
The logged stack extent is 220 at local-color exit and 244 at global-color
entry/exit; it is not the final machine frame size.

Next inspect this constant web's interference and the competing texture-
address lifetimes, using the calibrated observer before trying another
source family. No instruction/relocation rewrite, empty condition, dummy
local, fixed-register constraint, or nonmatching C body was installed.

#### Isolated part-counter scopes and remaining text-address residual

Follow-up from `455a87f`: 56 additional recorded probes (104 total game
probes for this owner) isolated a real source mechanism. Separating only
the two part-counter locals used by the level and text loops removes all
four promoted `multu` sites, while preserving the 336-byte frame. Splitting
the creature index, pixel-column accumulator, or part pointer instead does
not remove those sites. The earlier fully separate-scope variant had already
removed them, but its larger frame obscured that useful partial result.

The new natural parent is 2240 bytes versus 2252, normalized 0.9680 and raw
0.7567. Both rectangle locals now use the oracle's stack bytes 308/312,
without padding or extra locals. The text buffer still begins at 152 rather
than 128, and its original capacity is not established. The remaining
mechanisms include early title-address rematerialization, retained level-
label coordinates, and the final text loop's independently advanced header
and creature-name addresses. Indexed, byte-indexed, pointer-end, and actual
header-string-field forms did not close these differences. Neither did
truthful eight-byte byte/word/style views or snapshots of the text mode.

`func_800495F8` is genuinely variadic, as its definition in `src/47580.c`
shows. Repairing its local declaration to the real four fixed parameters
plus ellipsis preserves the complete known object. Eight recorded companion-
transaction probes in the new source basin did not accept. The declaration
was therefore not installed separately, and the owner remains assembly.

A second calibrated 45-second native source search disabled empty-condition,
dummy-local, type/ABI, and other fake-producing mutation families. Its useful
output moved the real part-origin declaration before the buffer. Bounded
stack-order probes applied that finding with SDK macros intact and reached
the matching rectangle offsets above; none reached a full object match.

The older wide observer's speculative edge dump faults with SIGBUS on this
new parent, although stock and observer-off builds preserve its complete
object. A private narrowed logger reads only the known web fields and the
primary expression prefix. Ten fresh stock/off/on/blank complete-object
controls pass for accepted source and the exact new parent. In procedure 52,
the constant-82 expression now appears at color events 30/44/45 with internal
color 255, rather than the old parent's assigned color 22; the new object
contains zero `multu` instructions. Logged extents are now 224 at local-color
exit and 248 at global-color entry/exit, still distinct from frame size.

Next use this new parent and narrowed observer to map the title-resource
address webs and final text-address induction. Do not resume from the older
2200-byte parent or repeat broad scope/stride/view permutations. All tracked
source, symbol-name, and alias bytes remain identical to `455a87f`; only this
handoff is pending for the next accepted batch.

#### Stock title-address pass boundary

Further investigation on `455a87f` retained stock compiler B/O streams after
15 complete-object stock/keep/blank controls. For the first three title
resources, the frontend emits separate address and value accesses; the
optimizer introduces the cached address and indirect mode load. The residual
therefore cannot be attributed to the frontend from the assembly alone.

Small two-call fixtures using the same eight-byte settings layout emit the
oracle's separate address/value loads through both stock IDO 7.1 and 5.3.
Each driver also reproduces its known matching game-object control. Those
fixtures do not prove that the full renderer can match, but exclude a claim
that this address pattern alone requires a different compiler. Six valid
game probes moving real coordinate and display-list lifetimes did not close
the residual. Two malformed generated loops did not compile and provide no
evidence against their intended hypotheses. The owner remains `requeue`;
resume from the 2240-byte parent, preserving the isolated part scopes.

### Rule selection list

`func_83003000` / `Fragment7_DrawRuleSelectionList` is accepted from
`455a87f`: 800 bytes, recorded runner acceptance, and a byte-identical full
US ROM with MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.

The callback draws four fixed rules followed by the saved rules counted at
state byte `0x3A06D`. Selection byte 81 chooses their yellow highlight;
compatibility status arrays at `0x3FED0` and `0x3FEE0` select gray for
unavailable entries. These are the fields consumed by
`Fragment7_RefreshCollectionCompatibility` and the selection handler
`func_83003320`. Fixed records start at `0x3FD74`, saved records at
`0x3A070`, both with a 68-byte stride. The signed halfword at fixed-record
byte 62 selects text resource group 15; negative values use the record's
own text. Fourteen emitted target-compiler size/offset values check this
view, including both record strides and both status-array strides.

The matching source uses one ordinary row index for all three loops.
Coordinates are `index * 21`, including the eleven horizontal separators;
IDO derives the original pixel and address induction. Separately maintained
pixel counters change loop scheduling and live ranges. Keeping the fixed
label choice inline also recovers the original independently advanced text
and resource-ID addresses. The equality spelling with the selected byte on
the left preserves the fixed-row successor across the draw call. No source
padding, empty condition, instruction rewrite, register constraint, or
manually unrolled loop is present.

The first successful gate froze the complete changed object, four distinct
collateral objects, source, ROM, ELF, and linked script before another
compilation; independent hashes verified the copies. The entire original
game object agrees in section bytes, function extents, and semantic
relocations. Eight further whole-object controls cover declaration cleanup,
readable formatting, color literals, naming, and blank-line shifts. The
named version retains the same 800-byte extent and 96-byte frame. Research
scripts and compiler captures remain private artifacts, not repository
helpers.
