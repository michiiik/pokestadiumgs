# Fragment 20 record-name loading

## 2026-10-23: four-slot names

`82601A84` is accepted as `RecordNames_LoadFourSlots`, 300 bytes, through
the recorded native runner and ordinary host-syntax-enabled full-ROM gate.
The four signed owner bytes select between asset group 42 entry 87 when
overriding assigned slots, and the selected 152-byte record row's name ID
minus one for unassigned slots. Each successful lookup copies exactly
12 bytes to state offset 2256 plus the slot index times 12. Other negative
owner values preserve the existing destination. No terminator or bounds
behavior is added.

The selection halfword at state offset 136 is loaded before the nullable
record-table guard, as the original branch delay slot requires. Halfword
indexing of the context selection table and a 152-byte array-element view
recover both address-add operand orders. Direct signed-slot tests recover
the original sentinel branch; the cached byte local caused one reversed
comparison. A calibrated, restricted source search found that mechanism.
Its dead local/store were removed before the clean candidate was submitted
to the recorded runner. No padding, unused local, forced register/frame,
extra argument, manual unroll, or instruction/relocation rewrite is used.

The real shared interfaces are `func_8004C874(s32, s32) -> void *` in
`src/4CC20.c` and the existing three-argument `_bcopy`. Every first gate
immediately froze source, the complete changed module, four collateral
objects, ROM/ELF/linked script, layout inputs, and assembly dependencies.
External hashes, the complete original module, and unchanged collateral
objects were checked before more compilation. The ROM MD5 remains
`1561c75d11cedf356a8ddb1a4a5f9d5d`. The address alias preserves callers.

## Unresolved neighboring owners

`82601968`: retain the historical requeue. Earlier regional evidence records
56 variants and a best 284-byte candidate with seven allocation/operand
differences. Do not replay its pointer/index, loop, width, or destination
families. Its old missing-toml obstacle no longer describes the calibrated
native permuter used for the four-slot owner; a retained-parent source search
is an available follow-up. This owner was not probed in this block.

`82601D2C`: requeue after an eight-cell ordinary-array family. The original
has two direct row pointers and three selectable row pointers; all five
entries are initialized and used in the draft. Scalar/array declaration
order, counted for/do loops, and direct/cursor slot reads leave 332/336-byte
candidates against retail's 324 bytes, with about 70 raw instruction-word
differences. The state pointer spills and the row-array homes differ.
Next: inspect the state and array-address alias/lifetime webs or use a
measured state-record view; do not enlarge arrays with unused slots to move
the frame. No candidate was installed.
