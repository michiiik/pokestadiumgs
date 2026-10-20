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

### Constructor requeue

81804954 remains assembly after twelve candidates. Its best result has the
correct 172-byte extent but raw similarity 0.6977. Ordinary controller guards,
direct versus locally viewed state pointers, and explicit fifth-argument
captures preserve the same prefix residual: retail loads that incoming word
early and saves s0 before ra, whereas the candidate loads it later and changes
the controller-address temporary sequence. The existing integer fifth-argument
contract is verified by fragment 5/8 callers; changing it to a pointer does not
solve the residual. Next: inspect compiler input/emission ordering for the
fifth-word load and initialization prefix before another spelling grid. Keep
the owner active as a requeue; do not manufacture frame space or force registers.
