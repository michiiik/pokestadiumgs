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
  slots are 8200 bytes each and their resource content begins at byte 96.
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
