# Fragment 14 selection panel

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
