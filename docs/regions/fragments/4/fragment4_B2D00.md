# Region notes -- src/fragments/4/fragment4_B2D00.c

### 2026-10-21: resource lifecycle and transition batch accepted

Four US owners are accepted by the normal runner and full-ROM verifier,
640 original bytes in total:

- 81804720: WidgetResources_Release, 192 bytes. Two 32-byte record tables
  terminate at a negative signed ID. The loops call func_81802DC8 and
  func_81802E34, then release the optional resources at offsets 32 and 28.
  Those callees and func_818047E0's default/variant traversal establish the
  resource-release name. Guard each table field before assigning its loop
  iterator; assigning the saved iterator before the guard changes code shape.
- 818048A4: WidgetDefinitions_Initialize, 176 bytes. Walk a null-terminated
  definition-pointer list, invoke each definition's initializer, then resolve
  each of the state's variants through func_818054D0 and initialize its
  optional offset-32 resource. Direct typed parameters avoid an extra saved
  register introduced by separate generic argument aliases.
- 81804A2C: WidgetState_AdvanceTransition, 188 bytes. Add
  func_818006B4()/duration to progress. Modes 1/4 test status at offset 52;
  modes 2/3 test offset 48. Completion or progress >= 1 clamps progress to
  1 and returns true. Preserve logical-not on these integer status words.
- 81804B74: WidgetResources_UseTransitionWeight, 84 bytes. Equal nonnegative
  comparison keys or either key equal to -2 return false. Other pairs return
  true. func_818055E0 uses the state weight when true and full weight otherwise,
  providing the operational name rather than guessing the keys' identities.

The new resource, definition and state views are respectively 44, 52 and 56
bytes. The resource comparison key is at offset 24, the definition's resource
view at 4, its variant map at 48, and state progress at 36. The state words at
48/52 are integers: func_81804BC8 writes boolean computations into them.
The state word at offset 4 is the initializer's integer fifth argument;
existing callers in fragments 5/8 declare and pass s32. These declaration
refinements are independently whole-TU byte-inert. Unknown fields keep unknown
names; these prefix views do not introduce or resize any stored object.

The first successful ROM comparison freezes the complete changed TU and four
collateral TUs before returning from each of the three accepted batches. Each
receipt is reread and every object independently hashed immediately afterward.
All three frozen game fingerprints equal the original 4608-byte text unit.
After naming, deduplicating declarations and removing an unused candidate-only
record type, fresh/twenty-blank/target-layout controls preserve all 24 original
function starts and sizes, every game byte and semantic relocation target.
Address-keyed aliases preserve assembly and cross-file callers.

The final normal gate freezes eight complete TUs, including direct callees,
the frame-time producer, fragment 5/8 callers and core/save collateral. Its
changed-object SHA256 is
cfe39fb97ad4b508997415d59f8696d94ce422845108d1451ef734dcc906bab5;
source SHA256 is
916d239fc65d1c80c9c43ad44b157346f476ae244630ad134eba11355046adc9.
Retail ROM comparison passes, MD5 1561c75d11cedf356a8ddb1a4a5f9d5d.
No new padding, instruction rewrite, dummy local, coverage update or private
experiment driver is part of this batch.

### 2026-10-21: construction and drawing batch accepted

Three more US owners pass the normal runner and retail ROM comparison,
covering 796 original bytes including the final owner's eight alignment bytes:

- 81804954: WidgetState_Initialize, 172 bytes. Set the state's integer context,
  reset the two paired variant bytes, initialize progress/status fields, select
  one of four 40-byte controller slots or NULL, and initialize the definition
  list. Fragment 5/8 callers establish the five-argument interface. Moving the
  real context assignment first reproduces the early incoming stack-word load;
  chained byte clears reproduce the remaining initializer temporary sequence.
  The passive compiler observer was calibrated against stock/off/on/blank
  builds before interpreting the incoming-word emission evidence.
- 81805308: WidgetDefinitions_Draw, 288 bytes. Prepare drawing once, walk a
  null-terminated definition list, obtain each variant's resource, ask its
  bounds callback for four signed halfwords, test clipping and optional context
  visibility, then invoke its draw callback. The existing scissor helper
  func_818017A8 and rectangle helper func_81801C90 corroborate the draw name.
  Preserve height-times-width operand order in the positive-area test.
- 818057D0: WidgetResources_DrawRecords, 336 original bytes. Resolve the
  variant and transition weight; position the optional offset-28 resource;
  traverse both signed-ID-terminated, 32-byte drawing-record tables. The first
  table is enclosed by func_800498C4/func_800499EC and uses weighted alpha;
  the second calls func_81803964. The actual third float argument of
  func_81803558 is visible in its mtc1 a2/fa0 and subsequent floating use.
  Its accepted wrapper func_81805644 now explicitly forwards all three input
  words. Known/explicit-caller/twenty-blank complete-TU controls prove that
  correction byte-inert before probing the new owner.

The draw access view is a 32-byte prefix, with callbacks at offsets 8/12 and
content at 28. Target-compiler assertions verify these offsets and the existing
56-byte state view. No stored object is introduced or resized. Semantic names
retain address-keyed linker aliases for assembly and cross-file callers.

Every first successful gate froze the entire changed TU and four collateral
TUs before returning. Receipts were reread and every artifact externally
hashed immediately afterward. Fresh named, twenty-blank and target-layout
controls preserve all 4608 game bytes, all 24 original function starts, and
semantic relocation targets. The last C symbol is 328 bytes while assembly
counts 336: the final eight identical zero bytes are natural translation-unit
alignment, not added source padding. Other function sizes remain identical.

The final named-source normal gate freezes eight complete TUs, including
direct callees, the frame-time producer, fragment 5/8 constructor callers,
and core/save collateral. Main object SHA256:
eac3dfc144b3436b681c69a80978098da3c5faaad1857df5f55fead5accb8f28.
Main source SHA256:
ef0bd5654db32ab74f63567641463c4a829937ebe525c916ea359cc504b7dd08.
Retail ROM MD5: 1561c75d11cedf356a8ddb1a4a5f9d5d.
Private observers, experiment drivers, coverage changes, padding, dummy locals
and instruction/relocation rewrites are excluded from this batch.

### 2026-10-21: dispatcher jump-table layout prerequisite verified

The owner's two five-entry jump tables now occupy its own `.rodata` window,
ROM 0xB4580..0xB45B0. Both boundaries are 16-byte aligned. This narrower window
contains D_81805FA0, jtbl_81805FA4, jtbl_81805FB8 and D_81805FCC; the existing
D_81805F98/D_81805F9C constants remain in the data head, and D_81805FD0 starts
the shared rodata tail. This avoids moving the accepted easing function's
constants into an unmigrated block. The generated linker change adds only
the new tail input after the owner's existing `.rodata` input.

The pinned splat 0.25.0 / spimdisasm 1.35.0-dev0 split migrates both tables into
func_81804FD0's assembly. A normal ROM gate passes with all four remaining
owners still assembly. No C implementation changes in this prerequisite.
The original 3728-byte data span is partitioned into a 1664-byte data head,
48-byte owner rodata and 2016-byte rodata tail. The owner's text remains 4608
bytes; all 24 function starts and sizes are unchanged. Its new rodata has
exactly ten table relocations, with table starts at owner offsets 4 and 24.

That first successful gate freezes ten complete objects before returning:
the changed owner, both data inputs, and seven collateral C units. All receipts
are reread and every artifact externally hashed. Owner object SHA256:
c2dc2ca104a94c89911b129b15b763dde1d724ec12d0d27134bc299e4881207a.
Unchanged C source SHA256:
ef0bd5654db32ab74f63567641463c4a829937ebe525c916ea359cc504b7dd08.
Retail ROM MD5 remains 1561c75d11cedf356a8ddb1a4a5f9d5d.

The accepted transition-status implementation emits the migrated 1.2f
constant rather than merely referencing D_81805FA0 as an external symbol.
The accepted selection renderer emits the migrated first 0.99f constant,
while its second threshold D_81805FD0 remains in the shared tail.
These are ownership/layout requirements, not permission to rewrite code bytes.

### 2026-10-21: flagged reset and selection drawing accepted

Two more US owners pass their normal runner/full-ROM gates, 416 original bytes:

- 81805428: WidgetSelection_ResetFlaggedVariant, 76 bytes. Resolve the
  definition's variant selected by state byte 30. If its offset-32 script is
  present and flag bit 30 is set, reset its state-backed selection to the
  script's default. The called helper's byte store establishes the reset name.
- 8180567C: WidgetResources_DrawSelection, 340 bytes. Resolve the active
  variant, obtain its transition weight, draw the script resources, then draw
  its selected entry when the high-flag/mask condition permits. Preserve the
  byte selected index and the existing one-based index-minus-one mask.

Both high-flag residuals close with a real bitfield view of the four-byte
script flag word at offset 16. The named fields cover reset-selection bit 30
and hide-masked-selection bit 29; all other bits remain unnamed. Target compiler
size assertions and initialized fixtures independently verify size 4 and word
masks 0x40000000/0x20000000. This is matching-source evidence, not a claim to
possess the original source. Ordinary AND tests, address-carrier changes,
integer-width changes and extra locals did not reproduce that lowering.

The renderer's remaining SP40/SP44 spill residual closes by placing both real
boolean conditions directly in their draw calls. C argument promotion then
owns the selected-index temporary and its correct home. No new index local,
padding, buffer inflation, register constraint or object rewrite is needed.
The migrated first 0.99f constant differs from the ASM symbol only in its
relocation spelling; the sequential full-ROM gate establishes acceptance.

The accepted helper at 81803C9C is now WidgetSelection_ResetToDefault with its
actual script/state pointer interface. It calls func_81803BB8(script, state)
and copies the script's default byte at offset 5 to the returned selection
location. Its old zero-argument call and an existing empty branch are removed
together. Removing only the empty branch changes code generation; explicit
arguments plus that removal, followed by the readable source form and a
twenty-blank control, preserve the entire helper TU. The sibling call in
func_81803C14 also uses the actual pointer prototype.
`//@src/fragments/4/fragment4_AFAA0.c`

Fragment 7's func_83006308 explicitly forwards both real words to the flagged
reset. Known/explicit/twenty-blank whole-TU controls prove this correction
byte-inert before installation. Address-keyed aliases preserve assembly and
cross-file callers for all three semantic names.
`//@src/fragments/7/fragment7_BA250.c`

Each first successful owner gate freezes the complete changed TU, four
collateral C units and both data inputs before returning. Receipts are reread
and all seven artifacts externally hashed immediately afterward. Fresh named
and twenty-blank controls preserve every game section, function extent and
resolved relocation target in all three changed C units. The main TU retains
24 function extents, 4608 text bytes and 48 rodata bytes. The comparison resolves
equivalent relocation fields; no production object is modified by it.

The final named-source normal gate seals exact source/symbol/alias/layout
inputs and freezes eleven complete objects before returning, including all
three changed C units. Its main object SHA256 is
3c5a171d8a3fa9ab797ecd7b09d3575dcb153b0539182c7f46ae26266b98ad7b;
main source SHA256 is
e002615108290992f9542a04e22b0ba5cf892a71c4c877db9614113507c09653.
Retail ROM MD5: 1561c75d11cedf356a8ddb1a4a5f9d5d.
No new padding, instruction/relocation rewrite, dummy local, private experiment
helper or coverage change is part of this batch.

### 2026-10-21: widget state update accepted

81804FD0 is now WidgetState_Update, 824 original bytes. It copies the selected
controller's axes and button words into the widget state, advances one of five
transition phases, derives the draw weights and active variant, runs each
definition's update/bounds callbacks, and submits their results to the optional
context. When the requested variant changes, it activates each new resource
and recomputes transition bounds/status through func_81804BC8. These operations
establish the update name; an address-keyed alias preserves existing callers.

The final source uses ordinary control flow and actual locals:

- Case 0 sets the existing completion flag inside an explicit conditional,
  rather than assigning a boolean comparison. This restores one instruction.
- Case 1 assigns integer zero to the float weight; the other zero assignments
  remain float literals. That source distinction restores the separate zero
  materialization and downstream float-register sequence. Changing all zeros
  together does not reproduce it.
- Update and activation traversals have their own iterator/resource locals.
  This reproduces the saved-register ownership and 120-byte frame. Caching the
  activation callback itself instead removes two required instructions.
- The actual four-halfword bounds array is declared after the update iterator
  and before the activation iterator. This puts it at SP+96 without adding or
  inflating storage. Root-first and root-last declarations put the same
  eight-byte object at SP+112 and SP+76 respectively. Equal comparison scores
  for those placements did not mean their stack offsets were equal.

Passive observer controls pass for stock, stock-plus-blank, observer-off,
observer-on and observer-plus-blank builds of a known unit and each retained
parent before interpreting frame events. The final candidate differs at the
two jump-table relocation fields only; the normal sequential full-ROM gate,
not normalized similarity or an isolated link-verified claim, accepts it.

The first successful gate freezes the entire changed TU, four collateral C
units and both data inputs before returning. All seven retained objects are
independently hashed immediately afterward. Known, cleaned/named and
twenty-blank whole-TU controls preserve every game byte modulo separately
verified equivalent relocation fields, every function extent and resolved
relocation target. All 24 function extents, 4608 text bytes and 48 rodata bytes
remain intact. Unused experimental declarations are removed after acceptance.

The final clean named-source gate seals source/symbol/alias/layout inputs and
freezes eleven complete objects before returning. All receipts are reread and
externally hashed before further compilation. Main object SHA256:
19b4857a78929e9c5ce6bc5df41949081b199febd851a56f4de431e2529ac057.
Main source SHA256:
4c74ea036d043f2e663210de779f9b57269eb37ce15fd37616e0a0f310935264.
Retail ROM MD5: 1561c75d11cedf356a8ddb1a4a5f9d5d.
No padding, dummy local, instruction/relocation rewrite, private diagnostic
helper or coverage change is part of this batch.

### 2026-10-21: transition status accepted; no remaining GLOBAL_ASM owners

81804BC8 is now WidgetState_RefreshTransitionStatus, 1032 original bytes.
For each definition, its bounds callback computes the endpoint rectangles at
weights zero and one. The function checks viewport containment/separation,
compares endpoint areas and resource keys, accumulates entry/exit/size flags,
emits the corresponding effects through func_800226C0, then restores the
saved transition weight and writes both integer status words. Those status
words are consumed by WidgetState_AdvanceTransition; WidgetState_Update
invokes this refresh after activating a newly requested variant. These
producer/consumer relationships establish the status-refresh name.

Eight one-bit fields describe the actual high byte of the four-byte flag
word. A direct structure and direct field assignments reproduce the retail
byte updates and word-based high-bit tests. A nested union retains an extra
address register and does not reproduce that lowering. The initial value is
copied from the existing D_81805C50 word; its extern type introduces no stored
object or data-layout change. Target-compiler sizeof assertions and eight
independent initializers verify size four and masks 0x80000000 through
0x01000000. The migrated 1.2f literal is emitted by this owner.

The source declares its three actual eight-byte rectangles and existing
scalar locals in the order that reproduces the 160-byte frame. Screen bounds
occupy SP+152, start bounds SP+124 and end bounds SP+116. Height-times-width
operand order reproduces the area load sequence. The definition iterator is
loaded before copying the initial flag word, allowing its store to occupy
the rectangle-helper call's delay slot. These are ordinary source-level
declarations, expressions and assignments; no local is added just to reserve
storage or force a register.

The recorded normal runner accepts the implementation through the full-ROM
gate. Its first successful comparison freezes the entire changed TU, four
collateral C units and both data inputs before returning; all seven artifacts
are independently hashed immediately afterward. Known, cleaned/named and
twenty-blank whole-TU controls preserve all game bytes modulo independently
verified equivalent relocation fields, all function extents and resolved
relocation targets. The unit retains 24 function extents, 4608 text bytes and
48 rodata bytes. Unused probe declarations are removed after acceptance.

The final named-source gate seals source/symbol/alias/layout inputs and freezes
eleven complete objects before returning. Receipts are reread and all objects
externally hashed before further game compilation. Main object SHA256:
43710c992822baf527ea38c0942adc3271ed529e5a0b4e6fa049ade4975d6d00.
Main source SHA256:
007ac0ce8fbe61732cab2c14853df69aaf8e852be42f03790d00dfff089c8a55.
Retail ROM MD5: 1561c75d11cedf356a8ddb1a4a5f9d5d.
The address-keyed alias preserves existing references. No new padding, dummy
local, forced register, instruction/relocation rewrite, private helper or
coverage change is included. This source file has no GLOBAL_ASM owners left;
this result does not imply completion of other fragment 4 files or the ROM.
