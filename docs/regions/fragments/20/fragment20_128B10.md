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

## 2026-10-23: two-slot record-name family

Four more owners are accepted through the recorded native runner and
ordinary host-syntax-enabled US full-ROM gate: 1296 matching bytes total.

- `82601BB0` becomes `RecordNames_FormatTwoSlots` (380 bytes). Two
  1064-byte context descriptors select between formatting one or two signed
  byte values and copying an existing record name. The mode at descriptor
  offset zero is a signed halfword; the signed bytes are at offsets two
  and three. The destination slots are 12 bytes at state offset 2256.
  `func_8004C594` supplies values and `func_8004C8A0` formats asset group
  18 entries 29 or 28; the copy fallback uses group 42. Their real
  interfaces are defined in `src/4CC20.c`. Loading selection before the
  table and using the 152-byte array view recover the record-address
  sequence. A signed state pointer with an explicit destination byte view
  recovers the three remaining address-add operand orders.
- `82601D2C` becomes `RecordNames_LoadTwoSlots` (324 bytes). The two
  direct row pointers and three profile choices are all initialized and
  used. Signed owner -1 chooses the profile indexed by the state halfword
  at offset 12; -2 preserves the destination; every other owner chooses
  the direct row for that slot. A two-case `switch`, with -1 before -2
  and default last, recovers the original allocation without a jump table
  or rodata change. Placing the three used loop locals after the two real
  arrays recovers their original stack homes. No array capacity is added.
- `82601E70` becomes `RecordNames_LoadSelectedOrDefaultSlots` (288
  bytes). The same owner cases choose a selected record or the table's
  first record for either slot. Selection uses state offset 136 and the
  context halfword map at offset 24. Independent selected/default row
  expressions avoid retaining the raw table pointer throughout the loop.
  The same two-case switch fixes the allocation class; initializing the
  default row before the state snapshot resolves the final row-register
  swap. No transient pointer-copy chain is needed.
- `82601F90` becomes `RecordText_SelectAndMeasure` (304 bytes). Each
  selected 152-byte record chooses text group `record[3] + 76`. Entry 39
  is used below the state threshold at offset 136; later rows choose from
  the three `D_82615348` entries. Successful lookups store the chosen ID
  and measured width/height as halfwords. The SDK declares `guRandom`
  as returning `int` in `lib/ultralib/include/PR/gu.h`; an explicit
  `u32` conversion before modulo three reproduces retail's unsigned
  division without changing that interface. Initializing the real index
  first and placing its declaration before the two used measurement outputs
  recover the initialization order and output homes. An opaque context
  parameter with explicit byte addressing recovers the final address add.

All four first successful gates immediately froze the source, complete
changed module, four collateral objects, ROM/ELF/linked script, layout
inputs, and original assembly dependencies. External hashes, complete
original-module equality, and unchanged collateral objects passed before
further compilation. ROM MD5 remains `1561c75d11cedf356a8ddb1a4a5f9d5d`.
Address aliases preserve existing callers. No instruction/relocation
rewrite, padding, unused local, synthetic read, forced register/frame,
fake argument/interface, or manual unroll is used.

### Resolved requeue and source-search safeguards

The earlier `82601D2C` requeue is resolved. Typed views and a unified
five-entry table had removed the spill but retained 22/23 instruction-word
differences. Calibrated logging-only allocation/frame diagnostics passed
stock/off/on/20-leading-blank whole-module controls and localized the
table-base/state competition. The decisive change was the owner switch,
which left only seven stack-home words; relocating three already-used
local declarations closed them.

A later two-array source search returned deceptively close variants.
Review rejected a last-row load from the state buffer instead of the
context table, an uninitialized state pointer, a changed captured-state
read, and a cursor reset on every iteration. Corrected forms did not retain
their apparent gains. None of those variants was installed. The accepted
matches came from the clean source families described above, not from the
invalid mutations.

## Unresolved neighboring owner

`82601968` remains a requeue. Earlier regional evidence records 56 variants
and a best 284-byte candidate with seven allocation/operand differences.
Do not replay its pointer/index, loop, width, or destination families.
The old missing-toml obstacle no longer describes the calibrated native
permuter. Resume its retained parent with a reviewed source search or the
new owner-dispatch/allocation evidence; the historical C spelling must
still be recovered and verified. This owner was not probed in this block.
