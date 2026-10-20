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

Future C candidates replacing func_81804BC8 must emit the migrated 1.2f
constant rather than merely referencing D_81805FA0 as an external symbol.
Similarly, replacing func_8180567C must account for the migrated first 0.99f
constant, while its second threshold D_81805FD0 remains in the shared tail.
These are ownership/layout requirements, not permission to rewrite code bytes.

### Remaining requeues

81805428 remains assembly. Best result is 76 bytes,
with 17/19 instruction words exact: the bit-30 test's shift and branch use t8
instead of retail t9. Byte/member views, signed/unsigned masks, explicit shifts,
comparison forms and real flag carriers do not close the tie. Fifteen complete
stock/blank/off/on observer controls pass on the known TU and two exact retained
parents. UGEN emits an AND-immediate into t8; the final assembler lowers this
to the observed shift/sign branch. Next: trace that lowering's input/temporary
choice, rather than repeat declaration or mask grids. Further direct-resource
guards, bit extraction, 64-bit masks and same-width int/long domains do not
close the tie. Fifteen additional stock/blank/off/on complete-object controls
calibrate the assembler's existing peephole diagnostic, but that log does not
identify the required AND-to-sign-test lowering decision. Do not interpret
its INST ordinals as final object offsets. Twelve stock 7.1/5.3 controls show
the same refresh residual under both; 5.3 also changes already-matching
neighbors, so no compiler configuration change is justified.
Any accepted two-argument
interface must also fix fragment 7's func_83006308, which currently omits its
second actual argument in C; prove that caller cleanup whole-TU byte-inert.

8180567C remains assembly. Capturing its actual byte selection result as u8
reproduces the 72-byte frame without padding. Its 340-byte variant is raw
0.8824: the first 54 words match, followed by a high-flag temporary sequence
and selected-index spill at SP40 versus retail SP44. The 344-byte explicitly
masked-index variant is raw 0.8953 but has an extra ANDI. Both forms are retained
privately. Distinct condition locals, real script/flag carriers, inline call
conditions and same-width integer domains do not close the residual. Fifteen
independent frame-observer controls precede that interpretation. Next: trace
the byte result's promoted stack home and the shared high-flag lowering;
do not add unused locals or enlarge a buffer to force a frame.

81804FD0 is now layout-ready but remains assembly after sixteen source
candidates. The best 816-byte body is raw 0.7961, with a 112-byte frame versus
retail 120 and an 824-byte original extent. Both five-case switches compile
with their owned tables; array versus four-halfword structure, direct versus
locally viewed state, and real old/new variant captures do not close the frame
difference. A narrow next-phase local worsens it. The existing context helpers
func_81600954 and func_81600A34 take actual pointer arguments; the retained
follow-up declarations/calls reflect that interface. Next: trace real stack
homes and input-to-state float-field lowering, keeping both switch case maps.

81804BC8 remains assembly after eight rectangle/status candidates. The best
1040-byte body has raw similarity 0.3077, a 152-byte frame versus retail 160,
and eight extra text bytes. All candidates preserve the two actual endpoint
rectangles, containment/separation tests, area comparisons, integer status
results and packed sound flags. Union versus word/byte flag access and local
state/rectangle declaration order do not solve the allocation. Next: compare
endpoint/result lifetimes and the original saved-register set, while honoring
the newly migrated 1.2f constant's ownership.
