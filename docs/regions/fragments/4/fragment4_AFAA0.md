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

The text-drawing requeue and its float-interface prerequisite are resolved by
the following batch. Other drawing owners remain separate work.

## 2026-10-21: text record drawing and traversal accepted

Three more US owners pass the normal recorded runner and full-ROM gate,
512 original bytes:

- 81803558: WidgetText_DrawRecord, 272 bytes. Select the current style or
  blend the two neighboring styles modulo three, configure text drawing,
  resolve the buffered archive string, then draw at the origin plus the
  record's signed x/y offsets. The existing text resolver and func_800495F8's
  formatted-text implementation establish the text-drawing role.
- 81803668: WidgetText_DrawRecordList, 112 bytes. Walk 32-byte records until
  their first signed halfword is negative, forwarding the origin, floating
  weight and variant to each record draw.
- 81803720: WidgetText_DrawRecordListWithSetup, 128 bytes. Preserve the
  original enclosing setup/finish calls and invoke the per-record setup
  wrapper for each nonnegative record. Using the iterator parameter directly
  reproduces the saved-register ownership; separate iterator aliases did not.

The existing C wrapper at 818036D8 is now WidgetText_DrawRecordWithSetup. Its
actual interface is two pointers, a floating weight and an integer variant;
it is not counted as a newly decompiled owner. func_800498C4 resets the text
rendering context and func_800499EC processes its buffered primitives.
//@src/47580.c

The record view is exactly 32 bytes. Target-compiler assertions verify signed
x/y offsets at 4/6, the eight-byte settings prefix at 8, the mode word at 16,
and the three style pointers at 20. The mode word is only tested for nonzero,
so it is represented as an integer flag, not a dereferenced pointer. This
type-only view introduces no stored object or data-layout change.

Whole-TU controls prove the full pointer/float wrapper interface byte-inert
before new candidates are tried. Fragment 7's two direct wrapper callers now
pass actual float expressions rather than word-punned float bits. All six
weight lookups in that TU explicitly pass their incoming definition/state
addresses through the real full prototype. These interface changes and the
later prototype deduplication preserve every game byte in the entire caller
TU. A separate negative control removing a pre-existing unused local changed
that object and was not installed; no new padding or dummy local is added.
//@src/fragments/7/fragment7_BA250.c

Each of the two accepted batches' first successful comparisons freezes both
changed C units, the direct neighboring resource unit, four collateral C
units and both data inputs before returning. Receipts are reread and all nine
objects independently hashed immediately afterward. Both retained main units
have the original full-game fingerprint. Known, cleaned/named and twenty-blank
controls pass for both changed TUs; four further word-mode/layout cleanup
controls also pass. The main unit retains all 74 function extents and 12896
text bytes, with identical resolved relocation targets. Comparison-only
relocation normalization never edits a production object.

The final named-source gate seals both changed source files and the
symbol/alias/layout inputs, then freezes eleven complete objects before
returning. All artifacts are externally hashed before further compilation.
Main object SHA256:
6b162a5ac0340402bbf333404f0d7be2e37b119c3f4bdc99d2d8befbff5ed787.
Main source SHA256:
a8d47bea8e7c2e9bb3e2a871800fbbc69730dd428454c5b799fe0cfdb8566994.
Fragment 7 source SHA256:
1d8a7cc6dc47eb63078df849a48da28710e92b2ef06ee0b4e41506d0ab2eef86.
Retail ROM MD5: 1561c75d11cedf356a8ddb1a4a5f9d5d.
Four address-keyed aliases preserve other callers. No instruction/relocation
rewrite, forced register, new padding, private helper, coverage update or
layout change is included. Texture drawing and other remaining owners in this
file are not claimed as solved by this text batch.

## 2026-10-21: texture colors, geometry and viewport tiling accepted

Three more US owners pass the normal recorded runner and full-ROM gate,
1136 original bytes:

- 818024B0: WidgetTexture_SetWeightedColors, 480 bytes. Emit standard
  gDPSetPrimColor/gDPSetEnvColor commands from the style's two RGBA byte
  groups, multiplying their alpha components by the actual floating weight.
  The SDK macros reproduce the unsigned float conversions and channel masks;
  no instruction-level conversion implementation is needed.
- 81803964: WidgetTexture_DrawRecord, 272 bytes. Resolve the descriptor,
  copy the two real eight-byte rectangles from record offsets 4/12, add the
  origin, fill default extents from texture dimensions and apply the selected
  style pointer at offset 20 + variant*4. Sizes up to 4096 use the existing
  scaled rectangle path; larger textures use func_8004D19C's alternate path.
- 81801FE8: WidgetTexture_TileViewport, 384 bytes. Resolve the descriptor,
  configure the existing display-list/render mode and RGB environment color,
  then draw nested tiles using the live viewport limits. Increment x/y by the
  descriptor width/height and emit the original finishing display list. Byte
  RGB parameters reproduce the incoming mask and stack-byte loads; word
  parameters instead produced an extra instruction.

The existing C wrapper at 81802BAC is now WidgetTexture_ApplyStyle and is not
counted as a newly decompiled owner. Its real interface is a style pointer and
floating weight; its render-mode/combiner/style-list calls establish the apply
name. The direct caller in func_81802CA8 now passes the actual style pointer
and 1.0f rather than an integer encoding of that float. Known, typed and
twenty-blank whole-TU controls prove this correction byte-inert before probes.

The texture record retains its real width/height values and both rectangles.
Declaration order places destination at SP+56, source at SP+48 and the width
home at SP+40. No unused storage or inflated array is added. Target compiler
assertions verify rectangle size eight and signed-halfword offsets 0/2/4/6;
the ordinary structure copies reproduce the original unaligned word loads.

Each of the three accepted batches' first successful comparisons freezes the
entire changed TU, the direct resource and fragment 7 caller units, four
collateral C units and both data inputs before returning. Receipts are reread
and all nine objects independently hashed immediately afterward. All three
retained main objects have the original full-game fingerprint. Known,
cleaned/named, twenty-blank and layout controls preserve all game bytes modulo
separately verified equivalent relocation fields, all 74 function extents and
resolved relocation targets. Text remains 12896 bytes. Redundant synthesized
prototypes are removed after acceptance; four address-keyed aliases preserve
other C and assembly callers.

The final named-source gate seals source/symbol/alias/layout inputs and freezes
eleven complete objects before returning. All artifacts are externally hashed
before further compilation. Main object SHA256:
f1a158901a8aaeb0efa8f358ce27bff44dc26bca240a78d154582c67eddf7975.
Main source SHA256:
998a623881c5ff250c7ffc63f53cf6250a4bf811302b87db1f0e730fa85facd5.
Retail ROM MD5: 1561c75d11cedf356a8ddb1a4a5f9d5d.
No instruction/relocation rewrite, forced register, new padding, dummy local,
private helper, coverage update or layout change is included. The remaining
style-blending and selection/input owners are separate decompilation work.

## 2026-10-21: selection marker accepted; angle return contract corrected

81804534 is now WidgetSelection_DrawMarker. Its first ordinary candidate
passes the recorded native runner, link-shape verification and normal full-ROM
gate. It copies the eight-byte rectangle at entry +6 in a 24-byte selection
record, adds the supplied origin, emits the standard setup display list and
white environment color with opacity 255.0f * weight, then chooses the marker
from flag bit 31. Texture markers are static or animated; rectangular markers
use the active highlight or the inactive 150/150/90 border. Existing renderer
definitions and WidgetResources_DrawSelection establish these roles and the
actual five-argument pointer/pointer/index/float/active interface.

The retail owner span is 492 bytes. Compiled C occupies 484 bytes, followed by
the same eight zero bytes from natural final section alignment. No padding
pragma, helper, local or special alignment directive was added. Complete game
sections, all function starts and semantic relocation targets/addends remain
identical; only this final function's ELF size excludes the alignment tail.
The gate preserves the whole-ROM checksum, not just an object text score.

The first successful comparison freezes the complete changed TU, four
collateral C units, the direct resource and fragment 7 callers, and both data
inputs before returning. Both receipts are reread and all nine retained
objects independently hashed before any later game compilation. Five further
whole-TU controls cover known source, corrected float return, cleaned semantic
names, twenty leading blank lines, and target rectangle offsets/size. They
preserve every complete game section, the accepted function extents and all
resolved relocation targets. Rectangle size is eight, with x/y/w/h at 0/2/4/6.

Existing 81803CD4 is named WidgetSelection_WrapAngle. Existing 81803D44 is
named WidgetSelection_AngleDifference and now explicitly returns its actual
f32 result: wrap(wrap(to) - wrap(from)). The assembly navigation caller reads
that result from f0. Its previous void spelling hid a real return contract;
the corrected definition is whole-TU byte-inert, not a new decompiled owner.
Three compatibility aliases preserve old address-keyed references. Unused
probe-only types and redundant declarations are removed after acceptance.

The final named-source normal gate seals source/symbol/alias/layout inputs
and freezes eleven complete objects before returning. Receipts are reread
and every object independently hashed before later compilation. Final main
object SHA256:
d273fca7040cb95641081c1eb7a79d11f92115d24f7cea92d6c083cf64c668f5.
Final main source SHA256:
41f7dd8a621e06b003f8e975dd6d6a151933482893c6c3bdad8cf9fb5fed8b25.
Retail ROM MD5: 1561c75d11cedf356a8ddb1a4a5f9d5d. No instruction/relocation
rewrite, forced register, dummy local, new padding, layout or coverage change
is part of this batch; private experiment helpers are not published.

requeue: 81802754 remains assembly-backed. Its natural eight-channel blend
has correct 1112-byte size and 0x40 frame, with 276/278 instruction words
matching; only the final output-pointer increment and FPCSR restore are
swapped at offsets 936/940. Independent whole-TU audit verifies all other game
bytes, extents and resolved relocations. Stock -keep captures, known/raw/final
and twenty-blank controls locate restore-before-store/increment in UGEN output.
The driver's normal verbose recipe already uses g0; an explicit g0 option
therefore did not test a different debug baseline. Genuine stock 5.3 and 7.1
retain the same residual. A recorded atomic byte-pointer prototype transaction
with valid initializer lifetimes also leaves that residual. No observer or
instruction patch was used to turn the near match into an acceptance. Next
investigate compiler-phase ordering on this retained parent or an authentic
source witness; do not repeat flat-loop casts, counter widths, cursor loops,
storage views, nested RGBA loops or initializer grids without new evidence.

requeue: 818042E4 remains assembly-backed. Its two texture/text passes and
selected-last behavior have an ordinary 588-byte parent versus target 592,
with an initial s0/s1 carrier swap. Moving the shared text-index reset before
the selected texture draw recovers 592 bytes but leaves a missing selected
index copy and extra second-loop strength reduction. Separate pass counters
regress to a 0x58 frame. Next investigate the real selection/index carrier
lifetimes and loop roles; no forced registers or dummy locals are installed.
