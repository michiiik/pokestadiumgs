# Region notes -- src/fragments/79/fragment79_393CA0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-14

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-14

TYPE CONFLICT: D_841951BD is extern u8 D_841951BD, not extern u8 D_841951D1, D_841951BC, D_841951BD

## 2026-09-14

func_84126440: plateau at 0.0 (raw None), mismatch unknown; tried families: call_sequence; tie-pool no

## 2026-09-18

func_8413860C: plateau at 0.9474 (raw 0.5263), mismatch operand_or_scheduling_drift; tried families: bounded_lookup; tie-pool yes

## 2026-09-18

func_84126850: matched (state_field_access:return_width:unsigned_halfword_result), 2 iterations, agent unbiased

## 2026-09-18

func_84126EDC: matched (constant_map:nested:single_u8_local), 1 iterations, agent unbiased

## 2026-09-18

func_841351EC: matched (state_field_access:aggregate_transfer:single_word_struct_assignment), 3 iterations, agent unbiased

## 2026-09-18

func_841256E0: matched (init_sequence:halfword_entry:constant_biased_byte_base), 2 iterations, agent unbiased

## 2026-09-18

func_84130A74: matched (state_field_access:compound_assignment:signed_global_clamp), 1 iterations, agent unbiased

## 2026-09-18

func_84125484: matched (state_field_access:while:direct-global-index), 1 iterations, agent unbiased

## 2026-09-18

func_84125424: matched (state_field_access:global_while:narrow_parameter), 1 iterations, agent unbiased

## 2026-09-18

func_84128B30: plateau at 0.7143 (raw 0.2857), mismatch operand_or_scheduling_drift; tried families: state_field_access; tie-pool yes

## 2026-09-18

func_84133B14: plateau at 0.9688 (raw 0.75), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool yes

## 2026-09-18

func_8412F39C: matched (call_sequence:direct-index:all-inline-accesses), 4 iterations, agent codex

## 2026-09-19

func_8412BB9C: matched (call_sequence:direct-index:u8-cast-u16-store), 4 iterations, agent codex

## 2026-09-19

TYPE CONFLICT: D_841951BF is extern u8 D_841951BF, not extern u8 D_841951E6, D_841951BF

## 2026-09-19

func_841383B4: matched (call_sequence:direct_global:exact_probe_match), 5 iterations, agent codex

## 2026-09-19

TYPE CONFLICT: D_84195278 is extern u8 D_8418615C, D_84195278, not extern u8 D_84195278

## 2026-09-19

TYPE CONFLICT: D_8418615C is extern u8 D_8418615C, not extern u8 D_8418615C, D_8419A006, D_8419A007, D_84199D82

## 2026-09-20

func_8413C2C0: plateau at 0.9492 (raw 0.8305), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool yes

## 2026-09-20

TYPE CONFLICT: func_8413584C is void func_8413584C(u8), not extern void func_8413584C(u8)

## 2026-09-20

func_8412DC20: matched (call_sequence:nested_guard:u8_argument_temp), 1 iterations, agent unbiased

## 2026-09-20

func_841306AC: matched (call_sequence:indexed:direct-global-access), 1 iterations, agent unbiased

## 2026-09-20

func_8412E420: matched (call_sequence:if_else:pointer_baseline), 1 iterations, agent unbiased

## 2026-09-20

func_84139528: matched (call_sequence:else_chain:direct_indexing), 1 iterations, agent unbiased

## 2026-09-20

func_841350F4: time cap at 0.9516 (raw 0.9516) after 2400s, mismatch instruction_drift; tried families: call_sequence; tie-pool yes

## 2026-09-20

func_8412C47C: matched (call_sequence:postflag:independent-switch), 2 iterations, agent codex

## 2026-09-20

func_8413794C: time cap at 0.9074 (raw 0.5988) after 2400s, mismatch instruction_drift; tried families: call_sequence; tie-pool no; 1 iteration(s) with a suspicious identical batch-wide failure

## 2026-09-20

func_8413A12C: time cap at 0.0 (raw None) after 2401s, mismatch unknown; tried families: (none); tie-pool no

## 2026-09-20

func_8413B254: matched (call_sequence:switch:cast-index), 1 iterations, agent openrouter

## 2026-09-21

func_84137D04: matched (call_sequence:nested:repeated-byte-index), 4 iterations, agent unbiased

## 2026-09-21

func_84124E44: plateau at 0.9787 (raw 0.8298), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool yes

## 2026-09-21

func_841246AC: matched (call_sequence:narrow_signature:direct_parameter), 2 iterations, agent unbiased

## 2026-09-21

func_84137BD4: matched (call_sequence:cached_destination:byte_subscript_address), 2 iterations, agent unbiased

## 2026-09-22

func_84139EB0: matched (call_sequence:else_if:pointer_table:s32_flags_exact), 4 iterations, agent codex

## 2026-09-22

func_8413DD94: plateau at 0.8919 (raw 0.4595), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool yes

## 2026-09-22

func_8413860C: plateau at 0.0 (raw None), mismatch operand_or_scheduling_drift; tried families: bounded_lookup; tie-pool yes

## 2026-09-22

func_84128B30: plateau at 0.7143 (raw 0.2857), mismatch operand_or_scheduling_drift; tried families: address_exposed_scalar, aggregate_copy, aggregate_mask, bitfield_narrowing, bitfield_update, boolean_high_bit, complement_extract, destination_alias, idempotent_recurrence, mask_algebra, mask_join, mask_phi, mask_store, masked_dispatch, masked_termination, ordered_bit_partition, ordered_conditional_phi, ordered_extract, ordered_mask, ordered_mask_absorption, ordered_mask_phi, ordered_masked_dispatch, ordered_masked_termination, ordered_modular_difference, ordered_remainder, ordered_xor_cancellation, pointer_loop, quotient_reconstruction, range_normalization, single_iteration, source_array_scalarization, state_field_access, store_forwarding, wide_extract, wide_lane_extract, wide_mask, wide_remainder; tie-pool yes

## 2026-09-22

func_8413860C: matched (bounded_lookup:conditional:permuter-shape), 8 iterations, agent codex

## 2026-09-22

TYPE CONFLICT: D_841951E5 is extern u8 D_841951E5, not extern u8 D_841951E4, D_841951E5

## 2026-09-22

func_84128B04: plateau at 0.9167 (raw 0.75), mismatch operand_or_scheduling_drift; tried families: algebraic_reset, alias_reset, assignment_dispatch, bounded_reset_loop, comparator_lifetime, comparator_materialization, comparison_narrowing, compound_reset, exclusive_arithmetic_reset, label_dispatch, local_phi, loop_dispatch, ordered_reset, permuter_seed, predicate_dispatch, reset_operand, selector_widening, sequential_guards, single_pass_block, state_field_access, store_value_lifetime; tie-pool yes

## 2026-09-22

func_84132B9C: plateau at 1.0 (raw 0.9906), mismatch register_allocation_only; tried families: call_sequence; tie-pool yes

## 2026-09-22

func_84128954: matched (call_sequence:global_access:canonical_compound_updates), 2 iterations, agent unbiased

## 2026-09-22

func_84126CD0: time cap at 0.8818 (raw 0.3273) after 2400s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-22

func_841397FC: matched (call_sequence:locals:u8-index-m2c), 1 iterations, agent codex

## 2026-09-22

func_84131760: time cap at 0.9886 (raw 0.9886) after 2400s, mismatch instruction_drift; tried families: call_sequence; tie-pool yes

## 2026-09-23

func_8412D53C: matched (call_sequence:loop:byte_pointer_arithmetic), 3 iterations, agent openrouter

## 2026-09-24

func_8413A53C: matched (call_sequence:pointer-table:casted-base-expression), 1 iterations, agent openrouter

## 2026-09-27

func_84135A2C: time cap at 0.9444 (raw 0.3704) after 2400s, mismatch operand_or_scheduling_drift; tried families: address_expression, argument_definition, base_dataflow, base_materialization, cache_definition, cache_signedness, cache_storage, call_sequence, copy_address, copy_argument, exit_topology, guard_base, guard_materialization, identifier_store, lexical_lifetime, local_layout, lookup_result, parameter_home, parameter_lifetime, permuter_output, permuter_seed, pointer_storage, promoted_call_boundary, record_representation, result_lifetime, tail_dataflow, tail_increment, tail_materialization, tail_operand_order, tail_statement_order, tail_width; tie-pool yes; 1 iteration(s) with a suspicious identical batch-wide failure

## 2026-09-27

func_8412DDC0: plateau at 0.963 (raw 0.963), mismatch symbol_size_drift; tried families: call_sequence; tie-pool yes

## 2026-09-27

func_84135D3C: matched (call_sequence:guard_returns:direct_byte_indexing), 1 iterations, agent unbiased

## 2026-09-27

func_84139244: matched (call_sequence:for_loop:inequality_termination), 1 iterations, agent unbiased

## 2026-09-27

func_841266C4: matched (call_sequence:direct_index:signed_result), 1 iterations, agent unbiased

## 2026-09-27

func_84136678: matched (init_sequence:narrow_owner_signature:direct_record), 6 iterations, agent codex

## 2026-09-27

func_84128B30: plateau at 0.0 (raw None), mismatch operand_or_scheduling_drift; tried families: address_exposed_scalar, aggregate_copy, aggregate_mask, bitfield_narrowing, bitfield_update, boolean_high_bit, complement_extract, control_wrapper, copy_chain, destination_alias, destination_indirection, idempotent_recurrence, loop_wrapper, mask_algebra, mask_join, mask_phi, mask_store, masked_dispatch, masked_termination, ordered_bit_partition, ordered_conditional_phi, ordered_extract, ordered_mask, ordered_mask_absorption, ordered_mask_phi, ordered_masked_dispatch, ordered_masked_termination, ordered_modular_difference, ordered_remainder, ordered_xor_cancellation, pointer_loop, quotient_reconstruction, range_normalization, single_iteration, source_array_scalarization, source_indirection, state_field_access, store_forwarding, wide_extract, wide_lane_extract, wide_mask, wide_remainder; tie-pool yes

## 2026-09-27

func_84136014: matched (call_sequence:early_guard:probed_exact_s32_result), 1 iterations, agent codex

## 2026-09-27

func_84124E44: time cap at 0.9787 (raw 0.8723) after 2400s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool yes

## 2026-09-27

func_8412E680: plateau at 0.0 (raw None), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool yes; 3 iteration(s) with a suspicious identical batch-wide failure

## 2026-09-27

TYPE CONFLICT: func_84136124 is extern s32 func_84136124(u8, s16, u16, u8, u8), not extern void func_84136124(u8, s16, u16, u8, u8)

## 2026-09-29

func_8412E82C: plateau at 0.9722 (raw 0.9722), mismatch symbol_size_drift; tried families: bounded_lookup; tie-pool yes

## 2026-09-29

func_841260D4: matched (state_field_access:indexed:signed_index_byte_counter), 1 iterations, agent unbiased

## 2026-09-29

func_84124F40: time cap at 0.9875 (raw 0.975) after 2408s, mismatch operand_or_scheduling_drift; tried families: call_chain; tie-pool yes

## 2026-09-30

func_84125EC0: matched (call_sequence:byte_pointer:nonpositive_clamp), 4 iterations, agent codex

## 2026-09-30

TYPE CONFLICT: D_841951D9 is extern u8 D_841951D8, D_841951D9, not extern u8 D_841951D9

## 2026-09-30

func_84129E84: time cap at 0.9811 (raw 0.7925) after 2412s, mismatch instruction_drift; tried families: call_sequence; tie-pool yes; 2 iteration(s) hit section_layout_drift -- needs a rom.yaml fix, not more candidates

## 2026-09-30

func_841358B0: plateau at 1.0 (raw 0.9828), mismatch register_allocation_only; tried families: call_sequence; tie-pool yes

## 2026-09-30

TYPE CONFLICT: Display_QueueFramebufferRequest_fragment79 is void Display_QueueFramebufferRequest_fragment79(OSMesg), not extern void Display_QueueFramebufferRequest_fragment79(OSMesg)

## 2026-09-30

TYPE CONFLICT: func_84135808 is void func_84135808(u8 *), not extern void func_84135808(u8 *)

## 2026-09-30

func_8413C2C0: matched (initial_narrowing:wide_index:explicit_initializer_mask), 2 iterations, agent unbiased

## 2026-09-30

func_84132E40: matched (call_sequence:direct_index:signed_inequality_loop), 1 iterations, agent unbiased

## 2026-09-30

func_841350F4: plateau at 0.9841 (raw 0.619), mismatch operand_or_scheduling_drift; tried families: aggregate_address_binding, aggregate_destination_bias, aggregate_destination_view, aggregate_member_projection, aggregate_representation, aggregate_result, aggregate_source_bias, aggregate_source_view, aggregate_storage, binding_definition_point, binding_lexical_home, branch_home_representation, call_sequence, local_layout, permuter_address_form, permuter_aggregate_kind, permuter_aggregate_representation, permuter_cleanup, permuter_declaration_order, permuter_home_allocation, permuter_lifetime, permuter_output, permuter_representation, permuter_result, permuter_scope, permuter_source_address, permuter_storage, permuter_transfer_lvalue, permuter_unused_home, result_home_representation, result_home_width, scalar_transfer, scalar_union, source_home_representation, transfer_member_selection, unused_binding_alignment, unused_binding_storage_class; tie-pool yes

## 2026-10-04

func_84133304: matched (call_sequence:direct_index:narrow_signature_baseline), 1 iterations, agent unbiased

## 2026-10-04

func_84139C54: matched (stride_signedness:destination:unsigned_index), 2 iterations, agent unbiased

## 2026-10-04

func_84124798: plateau at 0.0 (raw None), mismatch unknown; tried families: call_sequence; tie-pool no

## 2026-10-04

func_84129180: matched (call_sequence:direct_index:u16_compound_baseline), 1 iterations, agent unbiased

## 2026-10-04

func_84135E4C: matched (record_base_lifetime:embedded_matrix:eliminate_record_local), 3 iterations, agent unbiased

## 2026-10-04

func_8412A028: matched (store_signedness:first_flag:unsigned_byte_alias), 2 iterations, agent unbiased

## 2026-10-04

func_8413293C: matched (call_sequence:indexed_loop:narrow_argument_local), 1 iterations, agent unbiased

## 2026-10-04

func_84139618: plateau at 0.8384 (raw 0.404), mismatch operand_or_scheduling_drift; tried families: call_lowering, call_scope, call_sequence, callee_designator, callee_type_erasure, dispatch_alias, dispatch_argument_width, erased_dispatch_address, erased_dispatch_control, erased_dispatch_index, erased_dispatch_record, erased_dispatch_table, guard_topology, index_dataflow, index_storage, owner_base, owner_index, record_addressing, record_dispatch, record_layout, record_materialization, record_representation, restriction_load, restriction_materialization, restriction_topology, selection_allocation, selection_lifetime, selection_phi, selection_scope, state_lifetime, validation_branch, validation_dataflow, validation_operand, variadic_dispatch; tie-pool yes

## 2026-10-04

TYPE CONFLICT: D_841951F8 is extern u8 *D_841951F8[], not extern void *D_841951F8[]

## 2026-10-04

func_84126440: matched (call_sequence:switch:direct_callee_individual_returns), 5 iterations, agent antigravity

## 2026-10-04

func_84126C3C: matched (call_sequence:byte_offset_arithmetic:shift_neg_cast_and_masked_sub), 1 iterations, agent antigravity

## 2026-10-04

func_84128204: time cap at 0.9459 (raw 0.7297) after 2400s, mismatch unaligned_data_drift; tried families: call_sequence; tie-pool no

## 2026-10-04

func_8412D4A8: plateau at 0.0 (raw None), mismatch unknown; tried families: call_sequence; tie-pool no; 6 iteration(s) with a suspicious identical batch-wide failure

## 2026-10-05

func_8412F170: matched (comparison_dataflow:record_pointer:two_byte_array_stride), 2 iterations, agent unbiased

## 2026-10-05

func_841268A0: matched (call_sequence:direct_global:baseline), 1 iterations, agent unbiased

## 2026-10-05

func_84131F80: plateau at 0.7209 (raw 0.3023), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool yes; 2 iteration(s) with a suspicious identical batch-wide failure

## 2026-10-05

func_84124E44: matched (call_input_materialization:second_lookup:byte_local), 2 iterations, agent unbiased

## 2026-10-05

func_8412E680: plateau at 0.9455 (raw 0.9273), mismatch operand_or_scheduling_drift; tried families: argument_materialization, call_sequence, callee_return_contract, definition_contract_repair, duration_lifetime, initial_dispatch, mode_reuse, outgoing_stack_argument, permuter_repair, permuter_seed, result_dataflow, state_base_bias, state_representation, state_store, state_store_sequence, state_value_lifetime, tail_control, tail_expression, tail_short_circuit; tie-pool yes

## 2026-10-05

func_84139F44: matched (call_sequence:switch:direct_global_index), 1 iterations, agent unbiased

## 2026-10-05

func_8412EC70: plateau at 0.0 (raw None), mismatch unknown; tried families: call_sequence; tie-pool no; 6 iteration(s) with a suspicious identical batch-wide failure

## 2026-10-05

func_8412EC70: plateau at 0.0 (raw None), mismatch unknown; tried families: call_sequence; tie-pool no; 7 iteration(s) with a suspicious identical batch-wide failure

## 2026-10-05

func_841318C0: time cap at 0.9841 (raw 0.9683) after 2400s, mismatch instruction_drift; tried families: call_sequence; tie-pool yes

## 2026-10-05

func_8413A6CC: time cap at 0.8819 (raw 0.8583) after 2400s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## func_841366C4

Accepted recipe: retain the unsigned-byte first argument and use a signed-halfword second argument. Read byte 19841 of `D_84195280`, subtract one, replace a negative index with 29, then call the existing `func_841365F4(u8*, u8, s16)` with the record at index times 640 and both real arguments. Keep unknown names and decimal literals. Update the six existing owner declarations to the same signed-halfword type.

The original owner normalizes incoming `a1` through a shift-left/arithmetic-shift-right pair at entry, forwards it in `a2`, and stores both real arguments at their incoming homes. Its separately called 23-instruction body has a 24-byte frame and a complete return, with no shared switch tail or trailing padding. Original ASM callers, including `func_8413146C` and `func_84129374`, supply a byte and -1 and ignore the result. The compiled callers also pass -1. The helper normalizes its byte and signed-halfword inputs and stores them into the selected record; its existing prototype is retained.

The first trial kept the stale word second formal and cast only at the helper call. It failed the full ROM checksum (`4c66f0ae26d4207794df386f124ce142`): the resulting 22-instruction owner loaded the low halfword from the stack at call time instead of reproducing retail's early normalization pair. Correcting the real narrow formal and all six declarations produced the accepted match. No unrelated caller implementation or helper body changed. A declaration-count precondition initially aborted before any source write or build; it was corrected after confirming the unchanged baseline.

History audit: fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt. References to this owner in other failed candidates are caller references. The full regional notes provide the record-stride clamp-wrapper recipe and warn about incoming-home and rodata dead ends. The helper's unrelated plateau (normalized 0.8788, raw 0.5455) was read and not retried; no historical owner raw score is available. All open PR scopes were checked before both trials.

Independent validation against master `47055da7fbdf7bda1f80f70fbd626c5d8233ab94`: full US ROM build with default host syntax checks and `COMPARE=1`, followed by successful `md5sum -c baseroms/us/checksum.md5`. Retail MD5: `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 194 previously matched US owners, including merged #915, remained present. This local result does not substitute for the current-head and merge-result Public PR ROM Gate.

## 2026-10-22: weather healing, command sequence, and record write slot

Three owners were accepted by the recorded native candidate runner with the
ordinary host-syntax-enabled full-ROM comparison, totaling 512 bytes:

| Owner | Name | Bytes |
| --- | --- | --- |
| `8412F49C` | `BattleEffect_HealByWeather` | 264 |
| `841315C4` | `BattleCommand_RunSequence` | 160 |
| `84136CA8` | `BattleRecord_AdvanceWriteSlot` | 88 |

The healing effect reads current/max HP at offsets 38/40 of the selected
`D_84195200` record. Weather byte 2500 of `D_841951F0` selects a right shift
of 1, 0, or 2; the heal is capped by missing HP. Its real helpers are
`func_84136AF8(u8, s16, s16, u8)` and `func_841366C4(u8, s16)`.
The shift byte follows the meaningful halfword amount local, recovering
retail's stack home without padding. Maximum-first equality recovers the
original branch operands. Weather values outside 0..3 leave the shift
unspecified in the original owner; the matching source adds no default.

The command sequence dispatches bytes through `D_84185EB0`, stopping at a
byte at least 254 or a global cursor at least 27. Advancing `D_841951B8` as
a statement before loading the next command recovers the original temporary
sequence; pre-increment inside the subscript instead leaves six register
differences. The slot advance increments byte 19841 of `D_84195280`, wraps
at 30, and clears the selected 640-byte record. The neighboring record
writers provide the same stride and index evidence. Array-address spelling
recovers the original address-add operand order.

Every first successful gate immediately froze the complete changed object,
four collateral objects, source, ROM, ELF, linked script, layout inputs,
and original assembly dependencies. External hashes were checked before
further compilation. Full original-module comparison and the four unchanged
collateral objects were checked independently. No byte rewrite, artificial
local, padding, manual unroll, extra argument, or generated coverage edit
was used. Address aliases preserve the existing callers.

### `84130380`: requeue, scan/copy value lifetimes

The original scans seven stage bytes at record offset 30, advancing its byte
cursor before checking the current value against 7. If any differs, it copies
all seven stages from `D_841951BD` to `D_841951BC`, updates the target, and
emits message 73; otherwise it uses the existing failure helper. Five
eight-cell families tested cached/inline records, for/do loops, independent
scan/copy indices and byte values, advance-before-test ordering, promoted
wrapped cursors, and byte/word flags. The advance-before-test/copy-temporary
family reaches the original 256-byte size, but still has 37 raw word
differences, including a v1/a0 and a1/a2 role shift and differing relocation
positions. This is not a proven register-only residual. Next: capture the
first scan-value web and determine why it survives in v1 rather than an
uncolored byte temporary; preserve the two original loop roles. The owner
remains assembly, with no near-match installed.
