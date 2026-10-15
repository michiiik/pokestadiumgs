# Fragment 14 selection panel

## 2026-10-15 — contents renderer accepted

The current file is **13 C / 1 ASM**. `func_813051B8` is now
`Fragment14_DrawPanelContents`: **207 instructions / 828 bytes**, frame 0x60,
normal acceptance batch `c2869a8631a64ae18983e94f1016731c`, label
`f14-panel:renderer-direct:record-True:separate-offset-False:shared-slide-False`.
It is a relocation-masked, sequential full-ROM accept, **not** an
object-link-verified result. Stock IDO 7.1 / `-O2`; no compiler override.

- Sixteen probes tested array/record rectangle views, optional explicit
  loop-offset carrier, shared/inline text slide, and direct argument access
  versus an extra rectangle-pointer local. The direct record view with
  inline slide and a single loop index reproduces all target instructions.
  Other leaders have the same opcode structure but frames 0x68/0x70 instead
  of 0x60. Do not reintroduce those redundant locals.
- Cleanup gives the argument its real four-short rectangle type, removing
  repeated casts without adding an alias local. Fresh and twenty-leading-
  blank whole-TU builds preserve every accepted byte, all 14 function offsets/
  sizes, the renderer and all 13 untouched spans. The unchanged wrapper casts
  its existing eight-byte stack rectangle to that type. A US compatibility
  alias retains the original address-keyed symbol; JP remains untouched.
- Preserve the background/header/lower box, display-list call, icon, two
  font settings, opacity color, clipped sliding headings, four entry labels,
  valid-selection cursor guard and final scissor restoration. The existing
  0x60-byte rodata layout and both float literals remain exact.
- Reconcile the background helper's signature with both existing C callers
  and this target: `func_816048E0` now names its unused fifth f32 parameter.
  It is an existing function, not a new helper. Fresh and twenty-leading-blank
  builds preserve its **entire object's bytes/layout and all 97 function
  offsets/sizes**, followed by a normal full-ROM gate. No body or caller
  behavior changes, speculative casts or assembly patches are needed.
- Normal sequential acceptance and final-source full-ROM builds are retail-
  identical, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. Only source, the US alias
  and region notes are published; compiler artifacts, scratch generators,
  assembly, objects and ROMs remain local. Solo/native, no agents/containers.

The status getter remains ASM with its branch-to-next requeue below. The
renderer is accepted, but this is still not file or repository completion.

## 2026-10-15 — four panel functions accepted

The file advances from **8 C / 6 ASM** to **12 C / 2 ASM**. Four normal
native-runner accepts cover **276 instructions / 1104 bytes**. Stock IDO 7.1
and `-O2` throughout; no padding, physical register override or compiler hack.
This is not file completion. Work is solo/native, without agents or containers.

| Owner | Name | Instructions / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_81304CE0` | `Fragment14_InterpolatePanelRectangle` | 77 / 308 | 0x20 | `5a50b94a71984b23a22f887b67304ee3` |
| `func_81304E80` | `Fragment14_UpdatePanelInput` | 99 / 396 | 0x18 | `ad149286c77642d680a758738a6ed527` |
| `func_813050D0` | `Fragment14_UpdatePanelState` | 58 / 232 | 0x40 | `725c12cec64c450bbcad0dd75279c363` |
| `func_813054F4` | `Fragment14_DrawSelectionPanel` | 42 / 168 | 0x40 | `0593b797f0cc4d2686447d7dc176fefa` |

Input/render are object-link-verified accepts with combined full-ROM gates.
Position/dispatcher are relocation-masked hits accepted by sequential full-ROM
gates, **not** object-link-verified. Statistics and host checks stay enabled.

### Complete and verify the table layout before C

Extend the existing `.rodata` subsegment from ROM `0x10A600..0x10A620` to
`0x10A600..0x10A660`. Keep `SUBALIGN(16)`, the leading `D_81312470` C data,
all three tables and the renderer's two trailing float literals/padding.
Pinned extraction regenerates the one-line linker tail change from 10A620
to 10A660. Do not create a second dotted subsegment for the same file.

The still-ASM layout passes the retail ROM gate. All 14 function offsets and
sizes remain unchanged. Four raw text words change only because PC16 branches
to `.L81304DB0` become locally resolved: their old relocation fields are
0xFFFF, and the new immediates calculate precisely that same target. Every
other text word agrees. The first 0x20 rodata bytes are unchanged and the last
16 literal/padding bytes match their retail ROM slice. Raw object identity
across the migration is therefore not the right control; relocation-aware
comparison and the linked ROM are. All three tables migrate into their owners.

### Source mechanisms

- Position: retain case 1 before the grouped 0/3/4/5 states, the nested
  rectangle choice, default origin at panel+4, and normalized return value.
  Declare progress before the origin pointer to reproduce stack+0x1C and
  stack+0x18. **Keep the divisor integer `16`.** This compiler emits target
  `div.s` for that source, but rewrites `/ 16.0f` into reciprocal `mul.s`.
  A local floating duration also emits division but grows the frame; double
  arithmetic, scoped/const/register duration and reuse variants do not match.
  No extra duration local is installed. Preserve the capped interpolation
  factor `progress > 0.5f ? 1.0f : progress + progress`.
- Input: compute the controller pointer through `(u32)D_800CE060 + index *
  0x28`, then read the pressed halfword at +0xC. Direct pointer/record indexing
  folds the symbol relocation into the load and drops one target instruction.
  No address is hardcoded and no speculative controller record type remains.
  Preserve confirm priority, count>=10 transition, case-0 fallthrough to the
  1/2 action, cancellation, bounded up/down movement and all sound ordering.
- Dispatcher: declare the four-short rectangle before the result word,
  initialize the result immediately before the six-state switch, preserve
  unknown-state zero and pass all four rectangle fields to region registration.
- Render: preserve activity/visibility short-circuiting, eight-byte rectangle,
  distinct progress/opacity locals, post-halfway opacity and metadata argument.
  Correct the position helper's existing `void` prototype to its real `f32`
  return in the accepted transaction. Declaration synthesis initially injected
  the stale prototype; passing the correct shared declaration fixes that
  compile failure without changing a compiler hypothesis or bypassing guards.

### Naming, ABI cleanup and verification

- Add four behavior-backed names with US aliases; keep address-keyed symbols
  and JP untouched. The neighboring selection file now passes the real second
  context argument to update/draw and uses the correct float-return prototype.
  These were previously implicit incoming-register dependencies. Fresh and
  twenty-leading-blank whole-TU builds preserve all 55 neighboring functions,
  section layouts/bytes and the original 24-byte data include exactly.
- Remove duplicate prototypes and the unused probe-only controller typedef.
  Fix the existing `&D_81311F40` pointer-to-array mismatch to array decay, and
  document intentional fallthrough without changing instructions.
- Final fresh and twenty-leading-blank panel builds preserve all section bytes
  against the frozen accepted object, the 0x60-byte rodata layout, all 14
  original function offsets/sizes and all four accepted / ten untouched spans.
- Forced native baseline, still-ASM layout, four normal acceptance gates and
  final-source ROM builds: retail-identical, MD5
  `1561c75d11cedf356a8ddb1a4a5f9d5d`.
- Whole-TU host syntax check: PASS. Two intentional-fallthrough warnings
  remain (the previous pointer-type warning is removed). Public tooling
  tests: 22 PASS. No provenance bypasses.
- Publish only accepted C, YAML/generated linker layout, compatibility aliases
  and these notes. Scratch generators, runner copies, generated assembly,
  proprietary compiler artifacts, objects and ROMs stay local.

### `func_8130559C` — requeue, branch-to-next return tail

Thirty-two candidates cover guard/positive conditionals, byte/word indices,
ternary/explicit result, outer/inner switches, default order, scopes and common
exits. The best guard/explicit-result body is 56 versus 68 bytes, normalized
0.8235 / raw 0.7647. It retains the repeated byte load but omits the target's
unconditional branch-to-next (with -1 in its delay slot) and two trailing nops.
The changed branch distance is a real body residual, not just missing padding.
No body is installed. Preserve zero unless state byte 0x1A is 5, then index
byte 0x18 + 1 for 0..2, otherwise -1. Next: isolate return-tail lowering or
natural statement-line topology before repeating source spellings. Do not add
padding while the branch still differs or call this source shape impossible.

The 207-instruction renderer `func_813051B8` remains unattempted in this block;
its literal layout is now ready. Its assembly takes rectangle, float opacity,
word selection, field pointer and metadata. Those two owners are the remaining
file work; do not report the panel file as complete.

## Follow-up after the four-function PR

At entry this follow-up had **12 C / 2 ASM**. Eight common-result
status-getter probes (outer result initialized to zero versus assigned in
else, narrow/word index, conditional versus explicit result) are all worse.
Total status history is now 40 candidates; do not repeat that family. The
branch-to-next residual above remains the best next diagnostic target.

### Renderer preparation — requeue, ABI and geometry inventory

The initial renderer inventory was 207 instructions,
828 bytes, frame 0x60; locals retain a sliding text offset at stack+0x40.
Its argument mask is rectangle pointer, f32 opacity, s32 selection, f32 cursor
pointer and metadata pointer. Its two local float literals are 323.0f and
0.99f, already migrated with the file layout.

- Geometry: fading lower height is `(s32)(122.0f * opacity)`; lower y is
  rectangle y+height minus that height minus 12. Header height is
  `(s32)(34.0f * opacity)`. Text x is `(s32)(x+width-323.0f)`.
- Preserve calls to frame background setup, panel scissor begin, header box,
  the `D_80094D90` display list, lower RGB rectangle (120,160,255), icon
  `(106,185,9,-1,opacity)`, text begin/font/spacing and white opacity color.
- If header height >=4, draw resource 0x4B, metadata-selected resource at
  signed metadata+0x3E, and resource 0x4A. The first two share the actual
  local text slide `(1.0f-opacity)*34.0f`; the third uses lower y+12.
- Draw four resources 0x46..0x49 with y stride 32, end text, then draw the
  cursor only for opacity>0.99f and signed selection 0..3. Restore scissor.
- `func_81603598` consumes its fifth f32 argument (load from original
  stack+0x10). `Gfx_FillRectRgb` has four s16 geometry arguments and three u8
  colors. Use the real variadic prototypes of the two text draw functions.
- **ABI evidence, now reconciled by the byte-preserving cleanup above:** this renderer and the already-C neighboring
  file `fragment14_FD770.c` pass five arguments to `func_816048E0`, including
  a float. Its earlier accepted definition in `fragment11_D9520.c` named
  only four integer parameters and consumed no fifth parameter. This was
  existing cross-file prototype debt, not evidence to delete the target's
  fifth stack store. Inspect all callers and freeze/prove the helper object
  before deliberate signature cleanup; do not modify the shared private
  checkout or disguise the discrepancy with a guessed incompatible cast.

The next batch should work from this inventory and normal runner controls,
not repeat the already-closed interpolation/input experiments.
