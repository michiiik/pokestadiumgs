# fragment4_AFAA0 matching notes

## func_81802438

One independent 30-word leaf now uses the standard gSPDisplayList macro. Its signed byte at offset 9 selects the existing display list D_81805940 for case 1 or D_81805960 for case 2. Other values emit nothing. Original data contains the two genuine four-command display lists; no data or layout was changed. The owner reads only its incoming word address and has no consumed result. No padding or shared switch tail is involved.

The definition retains the existing word-address calling convention. The same-file forward declaration is narrowed from unspecified parameters to one word, and func_81802BAC now passes its real first word explicitly without the unused second argument. Its later calls continue using both original inputs. func_81802CA8 already supplies one word. All compiled caller bytes remain retail-identical in the full build.

The first switch/macro recipe passes the full US make rom COMPARE=1 build with default host syntax checks and md5sum -c baseroms/us/checksum.md5: 1561c75d11cedf356a8ddb1a4a5f9d5d. No semantic names, new fakes, invented formals, CI, compiler or verification changes were introduced. The Public PR ROM Gate must independently validate the current head/merge result before merge.

Historical probe snapshot: fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed had no exact owner attempt, reference or historical normalized/raw score for func_81802438. Earlier regional notes recorded func_818021B4 at normalized/raw 0.8095/0.7619 after eight guard variants, and func_81803558 at 0.9265/0.7794 with its actual float ABI prerequisite. Neither family was retried in that display-list batch. Later acceptance or requeue status appears below.

## 2026-10-21: five resource and selection accessors accepted

Five US owners pass the recorded native runner and normal full-ROM gate,
324 original bytes in total:

- 81801FA0: WidgetTexture_GetDescriptor, 72 bytes. Two nonnegative signed
  halfword IDs select an archive entry through func_8004C990; negative IDs
  return NULL. func_81802CA8 passes the result to the texture drawing helpers,
  whose consumers read its width, height, format and pixel data.
- 81802168: WidgetText_GetString, 76 bytes. Resolve the same pair of IDs
  through func_8004C874, or return the existing empty string D_81805D40.
- 818021B4: WidgetText_GetBufferedString, 84 bytes. Resolve/copy through
  func_8004C8A0 using D_81805FF0 and capacity 255, or return the existing empty
  string D_81805D44. The text resolver's destination/capacity path establishes
  the buffered-string name. This resolves the earlier guard-family near miss
  with a different, sibling-proven control-flow family.
- 81803BB8: WidgetSelection_GetValuePointer, 48 bytes. When the script's
  entry pointer and offset-8 state offset are nonzero, return the address of
  the state-backed selection byte. WidgetSelection_ResetToDefault writes the
  script's default byte through this pointer.
- 81803BE8: WidgetSelection_GetMask, 44 bytes. Under the same entry guard,
  a nonzero offset at script+12 locates the 32-bit state-backed selection mask.
  func_81803C14 and WidgetResources_DrawSelection consume its bits.

The texture and text archive operations are implemented in the core archive
resolver; selection consumers also appear in the neighboring resource unit.
//@src/4CC20.c
//@src/fragments/4/fragment4_B2D00.c

All five use explicit two-arm result assignments. Initializing a default
result and assigning only the successful arm, or returning early from that
arm, produces different branch/return tails. The state accessors retain the
offset assignment inside the short-circuit guard, so an absent script entry
does not cause its state offset or state-backed value to be read.

Existing C interfaces are corrected before probing: func_81802CA8 explicitly
passes its real descriptor to the texture lookup; func_81803C14 supplies both
real addresses to the mask lookup through its full pointer prototype.
Known, texture-only, mask-only, combined and twenty-blank combined whole-TU
controls prove those caller corrections byte-inert. No missing argument,
old-style prototype or fabricated formal is used to obtain a new match.

Each first successful comparison freezes the complete changed TU, the direct
neighboring resource caller, four collateral C units and both data inputs
before returning. The three accepted batches' receipts are reread and all
eight artifacts independently hashed immediately afterward. Their full game
fingerprints equal the pre-batch unit. Known, cleaned/named and twenty-blank
whole-TU controls preserve all game bytes modulo separately verified
equivalent relocation fields, all 74 function extents and resolved targets.
Text remains 12896 bytes. Unused candidate-only types and redundant prototypes
are removed after acceptance; five address-keyed aliases preserve other
assembly and C callers.

The final clean named-source gate seals source/symbol/alias/layout inputs and
freezes eleven complete objects before returning. All receipts are reread and
objects externally hashed before further compilation. Main object SHA256:
4806e42f3d12015765bc9d05d7bfae1285e626a3dfb07c9c9c89cf45c0892398.
Main source SHA256:
38cf6086c499708d2de5bea409589aaded3f593b3097a85db908cb21134767a8.
Retail ROM MD5: 1561c75d11cedf356a8ddb1a4a5f9d5d.
No new padding, dummy local, forced register, instruction/relocation rewrite,
private experiment helper, coverage update or layout change is included.

Remaining drawing owners are separate work. In particular, func_81803558's
earlier requeue requires its actual floating third argument and a corresponding
caller-interface correction before resuming the recorded near match; the
five-function accessor batch does not resolve that prerequisite.
