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
