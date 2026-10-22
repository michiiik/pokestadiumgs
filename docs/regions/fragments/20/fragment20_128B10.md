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

## 2026-10-23: unassigned-owner text and name loading

Three additional owners (792 bytes) passed the recorded native runner and
ordinary host-syntax-enabled US full-ROM gate. A fourth function replaces
an existing public C implementation without adding decompilation coverage.

- `82601968` becomes `RecordText_CopyUnassignedEntries` (284 bytes),
  resolving the requeue above. Signed owner -1 selects six text lookups
  from entries 33 through 38 of group `row[3] + 76`. Non-null, nonempty
  results copy 12 bytes into the corresponding record. The destination
  identity `outer * 528 + inner * 88 + 196` is
  `144 + (outer * 6 + inner) * 88 + 52`: four groups of six 88-byte
  records with text at byte 52. The grid ends at 2256, where the accepted
  four-slot name loaders begin. Compile-time size checks describe this
  external state; no local array or runtime storage is added. The text's
  game-facing label is unresolved. The historical parent used an `s32`
  lookup return, while `func_8004C874` in `src/4CC20.c` returns `void *`.
  Correcting that interface alone retained five instruction differences;
  the typed grid destination closed the remaining address-expression chain.
- `82602AC0` becomes `RecordNames_LoadUnassignedFourSlots` (220 bytes).
  Each signed owner -1 loads the selected row's group-42 name into its
  12-byte slot at state offset 2256; other owners and failed lookups preserve
  their slots. The row is fixed across all four slots. Selection-before-table
  initialization, a 152-byte row view, and the signed-state/byte-destination
  distinction transfer from the accepted neighboring formatter.
- `82602CF4` becomes `RecordNames_LoadSelectedOrDefaultPair` (288 bytes).
  Its opcode shape is identical to `RecordNames_LoadSelectedOrDefaultSlots`
  at `82601E70`; transferring that accepted C body matches this distinct
  retail entry point too. Owner -1 selects the mapped row, -2 preserves
  the slot, and other owners use the table's first row. Both entry points
  remain separate definitions at their original addresses.
- `82603814` becomes `RecordOwners_AnyUnassigned` (92 bytes). The public
  implementation used an unused pointer read and four repeated tests.
  A natural four-iteration loop matches the same retail bytes; IDO performs
  the unrolling. All four owners are inspected, with result one if any is
  -1. This is source cleanup, not a newly decompiled public owner.

The first successful gates froze source, complete changed module, four
collateral objects, ROM/ELF/linked script, layout inputs, and original assembly
dependencies before further compilation. Independent external hashes,
whole-module comparisons, and collateral checks passed. ROM MD5 remains
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Address aliases preserve callers.
No instruction/relocation rewrite, padding, unused local, synthetic read,
forced register/frame, fake interface, or source-level manual unroll is used.

### Requeue: `82602FE8` descriptor validation

Retail sums signed bytes starting at descriptor offset four, using the signed
halfword at zero as its count. It then checks a halfword at
`46 + index * 88` for every index below that sum. The result starts at one
and becomes zero on any zero field; a nonpositive sum returns one. Older
manually unrolled candidates that returned zero for an empty input change
this behavior and must not be reused.

A natural pointer sum loop followed by an indexed field-check loop reaches
the original 252-byte size and near-identical opcode sequence, but remains
unmatched. Logging-only allocator diagnostics passed known-sibling and
stock/off/on/20-leading-blank complete-module controls. They identify the
count temporary taking V0 while the sum takes A1, unlike retail's count A3
and sum V0. Parameter-walk and inline-count families produced 248-byte
objects with different bulk-loop induction. A calibrated 90-second source
search improved its own score from 435 to 240 through ordinary initialization
ordering but did not match. These scores are not acceptance evidence.

Next: retain the natural 252-byte loop topology, compose the measured
initialization-order improvement with a source-lifetime change for count,
and inspect exact register/operand differences. Keep the known descriptor
dimensions (8-byte header plus twelve 88-byte entries = 1064) without
inventing the checked field's gameplay meaning. No candidate for this owner
has been installed.

## 2026-10-23: optional default names and remaining selection phases

`82602B9C` is accepted as `RecordNames_LoadTwoSlotsOptionalDefaults`
(344 bytes). It uses the two real direct-row pointers and three real profile
pointers of `RecordNames_LoadTwoSlots` at `82601D2C`. Owner -1 selects the
profile indexed by the state halfword at offset 12; owner -2 preserves its
name; other owners copy their direct-row name only when `use_defaults` is
nonzero. A failed lookup also preserves the destination. Both destinations
are 12-byte slots at state offset 2256.

Transferring the accepted sibling's switch and declaration order recovers
the allocation and real array homes. The conditional default row must be
expressed as a conditional expression: an equivalent initial-zero/conditional
assignment retained 14 instruction differences. Initializing state before
the first direct-row expression matches; reversing those statements retained
two instruction differences. Every array entry is initialized and used.
No extra array capacity, unused local, artificial read, padding, instruction
rewrite, or forced frame/register is introduced.

The recorded native runner accepted this owner through the ordinary
host-syntax-enabled US full-ROM gate. Its first successful gate immediately
froze source, complete changed module, four collateral objects, ROM/ELF,
linked script, layout inputs, and original assembly dependencies. External
hashes, whole-module equality, unchanged collateral objects, and ROM MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d` passed independently before further
compilation. This is the first accepted owner of the next publication batch.

### Requeue: `82602FE8` count and descriptor views

Follow-up count-lifetime variants reach 252 bytes with 30 differing instruction
words and an allocation-only diagnostic. Keeping a bound pointer initialized
at the descriptor, then extending it only inside the positive-count guard,
recovers retail's count A3 and scan-end A1 in one parent. Its preserved base
and byte cursor remain swapped. Moving the actual incoming argument instead
of a separate cursor changes bulk-loop induction and emits 248 bytes.
Resetting that argument for the second scan does not close the difference.

A second calibrated 90-second source search improves its own score from
225 to 180, without matching. Review finds its base-to-unchanged-context
substitution semantically valid; a same-line initialization group improves
the score further. Neither is acceptance evidence, and the packed source
is not installed. Keep both the original 252-byte parent and this measured
partial improvement. Next: compare their exact allocation webs before
another source-lifetime family; do not replay parameter-walk, count-width,
byte-view, declaration-only, or cursor-reset families unchanged.

### Requeue: `82603870` phase dispatcher

The natural four-case switch reaches 304 bytes with the correct frame,
state-pointer home, result home, and branch/call body. The best parent has
raw similarity 0.9474; nine to ten instruction words differ in its opening
global counter address/update sequence. IDO retains the counter's address
in V1 while retail uses separate high/low load and store references.
Plain `++`, `+= 1`, explicit addition in either operand order, and a named
tick snapshot do not close it. Changing the snapshot into a new local
worsens allocation and sometimes the frame; it is not installed.

Required interface evidence: `StageContext_GetFadeMode` returns `u8`
in `src/8470.c`; `Audio_RequestIfChanged` (alias `800355E4`) returns `s32`
in `src/229E0.c`; `82614F0C` returns `s32` in
`src/fragments/20/fragment20_12C460.c`; assembly `80044144` dereferences
its argument, so its argument is a pointer. Prototypes must precede their
first uses in the existing `82602930` sibling, not only this new candidate.
Companion edits can hoist them without changing that sibling's object.
The runner synthesizes declarations before applying companions: explicitly
supply these same interfaces in the batch declarations as well, or its
cross-file fallback injects conflicting void-return/integer-argument forms.
These context failures are not source-shape rejections.

Next: obtain a calibrated logging-only allocation/expression trace for the
global address common subexpression. The ordinary source-level counter
families above are already measured; do not add volatile qualifiers or
instruction rewrites to suppress the commoning.

### Resolved: `826039A0` enclosing phase loop

`RecordSelection_RunPhaseLoop` is accepted through the recorded runner and
ordinary host-syntax-enabled US full-ROM gate. It advances `82603870` until
phase four while updating the background, UI, and selection view. After the
loop, `826058CC` classifies the saved state's byte-seven mode: modes zero
and four return zero, one and three return one, and other modes return -1
(`src/fragments/20/fragment20_12C460.c`). Category zero permits the two
finishing actions selected by the saved high byte at state offset eight:
`0x300` invokes `826036DC`, and `0x600` invokes `826037BC`.

The first natural loop retained six frame/home instruction differences.
Calibrated logging-only UGEN frame diagnostics passed stock/off/on/20-leading-
blank controls for both the accepted `82602A0C` sibling and retained parent.
They locate the missing space in the local area, not extra saved registers
or invented arguments. Keeping the actual mode-category query result as a
named, used local resolves it: category, state pointer, mode group, next
phase, and current phase are all initialized and used. The 48-byte frame
places the pointer at stack offset 40 and the mode group at 38. There is
no unused local or artificial storage.

First-success artifact verification distinguishes instruction extent from
terminal section alignment. The assembly owner reports 240 bytes, including
two trailing zero words. IDO reports 232 instruction bytes ending in the
retail `jr ra` / stack-restore epilogue, followed by the same eight natural
section-alignment bytes outside its function symbol. The entire text section
has the same length and bytes; every other function extent and all semantic
relocations agree. The initial strict symbol-size comparison correctly
surfaced this metadata difference; the follow-up audit checks exactly this
single terminal 240-versus-232 case, its epilogue, and its eight-byte tail.
No source padding, helper, or object modification produces these bytes.

The first successful gate froze source, complete module, four collateral
objects, layout/assembly inputs, linked script, ROM, and ELF before further
compilation. External hashes, whole-module byte/relocation equality with the
explicit terminal-alignment audit, unchanged collateral objects, and a full
`cmp` against the US baserom passed. ROM MD5 remains
`1561c75d11cedf356a8ddb1a4a5f9d5d`. This is the second accepted owner in
the current publication batch: 576 instruction bytes plus eight natural
terminal alignment bytes across the two original owner extents.

### Phase-dispatcher diagnostic follow-up

The calibrated `82603870` trace passes known-owner and retained-parent
stock/off/on/20-leading-blank complete-object controls. It identifies the
counter address as an allocator web selected into V1 in phase one, rather
than a delay-slot or post-link issue. A stock IDO 5.3 versus 7.1 control also
produces the same candidate prefix and the same known complete module.
Neither stock C driver resolves this parent; no compiler selection changed.
The next experiment must change that address-expression web through genuine
source structure, not add register pressure or alter instruction bytes.

### Requeue: `82602710` viewport border fill

The signed halfwords at context offsets 160 and 164 through 170 select
full-screen fill or four border rectangles around a 640-by-480 viewport.
`GfxImage_FillRectangle` in `src/7A50.c` takes a display-list pointer,
four signed 32-bit geometry arguments, and a 16-bit color. The initial
natural geometry family compiles to 332 bytes versus retail's 376, with
S0/S1 saved rather than retail's caller-saved geometry. Separate, used
left/right border heights and a pointer initialized only in the draw
branch improve the structural size to 360/364 bytes, but still save S0
and retain operand/scheduling differences (best reported raw similarity
0.3085). Typed/raw views, width/height ordering, and moving the constants
to the end of the subtraction do not resolve it. No candidate is installed.
Next: inspect the retained branch-local pointer's allocation/liveness and
the independent border geometry, preserving the reloads after drawing
calls rather than retaining stale viewport fields across them.

The follow-up native box passes eight stock/off/on/20-leading-blank whole-
module controls for a known owner and the retained geometry parent. Its
logging-only trace assigns the incoming pointer web to S0 in allocator phase
one (`save=1.6`, five uses); this is a measured saved-register choice, not an
assembler delay-slot hypothesis. Signed-halfword snapshots, explicit embedded
array/struct views, advancing the incoming argument to the viewport, and an
early full-fill return all remain unmatched. Halfword snapshots can reach
376 bytes but retain the wrong frame and saved pointer; they are not close
instruction matches. The best later reported raw score is 0.3404 with a
360-byte argument-advance body. Keep the 364-byte geometry parent as well:
different scalar scores do not settle its better structural subregions.
Next: distinguish the named/derived pointer's coalescing from its saved-
register cost, using the calibrated allocation evidence before any new
source family. No pointer-address escape, extra read, volatile qualifier,
fabricated argument, or padding is justified by these results.

### Resolved: `82600BA0` sorted unique index selection

`RecordSelection_ChooseSortedIndices` calls `82600A40` with an output array,
draw count, and pool count, then selection-sorts the chosen signed indices
in ascending order. `82600D38` supplies six output slots and the row count
from its packed table; the callee `82600A40` reads all three arguments.
The interface is therefore three arguments even though the wrapper forwards
the incoming pool-count register without emitting a new assignment.

The accepted 340-byte source uses a guarded do/while over the last index
and an ordinary inner scan. IDO performs the inner unrolling. The swap
loads the chosen minimum first. No source-level unrolling, extra storage,
object rewrite, or padding is used. Recorded runner acceptance and the
normal host-syntax-enabled full-ROM gate passed. The first-success source,
complete module, four collateral objects, layout/assembly inputs, ROM, ELF,
and linked script were frozen before further compilation. Independent
external hashes, whole-module byte/relocation/extent equality, unchanged
collateral and foreign files, and US ROM MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d` passed.

### Requeue: `82600D38` randomized party records

The packed-table row count controls six unique sorted choices. For each
record, `82600A40` produces a three-element permutation whose first two
entries select the two sides' 24-byte packed Pokemon. `80071E48` unpacks
each into an 88-byte working record. Unassigned sides divide five distinct
stat-experience fields according to profile zero/four, one/two, or other/one,
then `82600CF4` refreshes the record.

The field interpretation is producer/consumer verified: `80071E48` copies
packed halfwords to working offsets 12, 14, 16, 18, and 20, and supplies
them to `Pokemon_CalculateStat` for HP, Attack, Defense, Speed, and both
Special stats respectively. `Pokemon_CalculateStat` and
`Pokemon_GetDVForStat` in `src/615D0.c` establish the stat-exp role and stat
index mapping. A named-field model replaces the earlier speculative
indexed loop; this is not a hand-unrolled generic array operation.

Sixteen controlled candidates test that model and then packed-row versus
destination evaluation order and selector width. Whole-module original,
declaration-context, and leading-blank controls pass. The best reported raw
similarity reaches 0.8107, but that 816-byte body remains eight bytes shorter
than retail. Other 820-byte parents have the correct 216-byte frame and
more faithful subregions. All remain rejected and none is installed.
Computing the row first restores the retail inner-loop S1/S2 roles; genuine
array stack homes, divisor branch topology, and temporary order still differ.
Next: test selector/divisor lifetime reuse and inspect the real local-area
layout; do not inflate the permutation or selected arrays, add padding,
invent reads, or force allocation.

The next eight candidates reuse the profile selector as the divisor and vary
the placement of the three real arrays relative to used scalar locals. They
remain rejected at 820 bytes (best reported raw 0.8010); neither family fixes
the stack homes or the missing instruction. A logging-only frame trace then
passes eight stock/off/on/leading-blank complete-object controls for the
accepted sorted-selector sibling and this retained parent. The parent has a
216-byte frame: 48 bytes at the saved-register phase, a 16-byte local area,
and a 152-byte area added before entry/exit emission. The frame total already
matches retail; this is an internal-home ordering problem, not evidence for
additional storage. The same trace identifies the packed-row and destination
induction webs in S1/S2. Next inspect their expression lifetimes and the
profile-to-divisor branch before changing the declarations again.

### Resolved: `82600D38` two-party preparation

`RecordSelection_PrepareTwoParties` is accepted at 824 bytes through the
recorded native runner and normal host-syntax-enabled full-US-ROM gate.
With randomization enabled it selects six distinct sorted table rows and
uses an independent three-element permutation for each row to choose one
packed Pokemon for each of two parties. An optional nonzero seed initializes
the deterministic RNG. Unassigned sides scale HP, Attack, Defense, Speed,
and Special stat experience by the selected profile's divisor and refresh
their calculated stats. Metadata loading runs for both sides even when
randomization is disabled.

The final source mechanisms are independently explainable. The divisor is
unsigned and only takes one, two, or four; the profile selector remains a
signed halfword. Placing the three real arrays after the two loop indices
matches their stack locations without changing their sizes or introducing
storage. Evaluating the selected row index before its table pointer restores
the temporary lifetime. This leaves exactly one swapped-source `addu` at
owner offset 308; eight byte-pointer arithmetic spellings do not fix it.

The last instruction resolves with the actual packed-row model: an eight-
byte header followed by six 24-byte Pokemon records. `func_80071B58` in
`src/72720.c` establishes the 152-byte row stride; `func_80071BB8` reads
the count at offset four and records at offset eight, bounded to six.
`func_80071E48` supplies the unpacked record and stat-experience evidence.
Ordinary `row->pokemon[index]` member indexing produces the exact operand
order. A pointer-addition spelling on the same member remains one word off.
The implementation has no instruction rewrite, padding, unused variable,
extra read, fabricated ABI, or manually unrolled generic array loop.

The first successful gate froze source, complete module, four collateral
objects, layout/assembly dependencies, linked script, ROM, and ELF before
further compilation. Independent external hashes, complete-module game
sections/bytes/extents/semantic relocations, unchanged collateral and foreign
files, and US ROM MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d` passed. The
earlier requeue entries above describe the rejected parents, not the final
accepted body.
