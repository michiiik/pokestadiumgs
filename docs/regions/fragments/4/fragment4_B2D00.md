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

### Remaining requeues

81805428 remains assembly after 22 source candidates. Best result is 76 bytes,
with 17/19 instruction words exact: the bit-30 test's shift and branch use t8
instead of retail t9. Byte/member views, signed/unsigned masks, explicit shifts,
comparison forms and real flag carriers do not close the tie. Fifteen complete
stock/blank/off/on observer controls pass on the known TU and two exact retained
parents. UGEN emits an AND-immediate into t8; the final assembler lowers this
to the observed shift/sign branch. Next: trace that lowering's input/temporary
choice, rather than repeat declaration or mask grids. Any accepted two-argument
interface must also fix fragment 7's func_83006308, which currently omits its
second actual argument in C; prove that caller cleanup whole-TU byte-inert.

8180567C remains assembly after eight candidates. The well-defined masked-shift
forms reach 340 bytes and raw similarity 0.7529, but frame size is 56 versus
retail 72. Local declaration reversal and combined versus explicit status
computations do not repair this. Next: compare stack-home allocation for the
weight, mask, selected index and boolean result; do not add unused frame locals.
81804BC8 and 81804FD0 remain assembly and were not probed in this batch.
