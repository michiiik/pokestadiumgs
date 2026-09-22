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
