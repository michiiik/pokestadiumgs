# Fragment 44 scroll-list updates

## 2026-10-16 — record-image renderer accepted, next batch in progress

Solo native macOS; no agents or containers. `func_8AF02410` is now
`Fragment44_RenderScrollRecord`: **372 bytes / 93 words**, frame **0x28**.
This activates a record, stores its index, signed coordinates and species
code, selects the record image as render target, and draws its background,
thumbnail and name. The file now has **11 C / 7 function ASM** owners.

The first sixteen source cells already reproduced all 93 instruction shapes
but differed in temporary registers after the background call. Eight
explicitly non-installing ABI controls isolated the cause to `func_8004A858`,
not `GfxImage_SetRenderTarget`: the former is still assembly and needs a
legacy word-return declaration in this caller. Its epilogue leaves the last
emitted display-list address in `$v0`; this caller discards it. Other C
callers currently declare that assembly function void, so do not infer a
repository-wide return contract from this local acceptance. No existing C
definition or foreign caller was changed. The render-target declaration
remains void, consistent with its existing C definition.

The normal runner accepted the next eight-cell family through one sequential
full-ROM gate. Its probe link verifier reported **relocation_drift**, not
`link_verified`: `func_80007328` versus its existing canonical alias
`GfxImage_SetRenderTarget`. Do not describe this as probe link-verified. The
authoritative ROM comparison passes, including after cleanup and naming,
MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.

Fresh and twenty-leading-blank controls preserve the frozen accepted object's
complete text/rodata/data/bss, section layout and all relocation rows, all
18 function spans, and all 17 untouched function bodies. The initial proof
harness assertion used pre-#1048 address names for three already-renamed
siblings; correcting those explicit name mappings makes both controls pass.
Host syntax check, all 25 tooling tests and whitespace checks pass. Only
source, the compatibility alias and these notes belong in a publication;
all generators, controls, objects and ROMs stay local.

`func_8AF02584`: **requeue**, 56 compared source cells before replay with
the newly accepted callee. A calibrated native permuter found an object-score
zero by adding an unnecessary local initialized to the constant 0x74.
That scaffold is not installed. Eight replacements using real x/code locals
or reusing actual loop/flag variables do not preserve that score; the best
readable original remains 256 bytes, normalized .9844 / raw .9375. Next use
the actual renderer's ABI and trace the table-base allocation rather than
publish the artificial constant carrier. There is no insertion acceptance.

## 2026-10-16 — five-function scroll batch accepted

Solo native macOS, no agents or containers. **Five functions / 209 words /
836 bytes**, progressing this file from **2 C / 16 function ASM to 7 C /
11 function ASM** (18 original functions).

| Original owner | Accepted name | Bytes | Frame |
| --- | --- | ---: | ---: |
| func_8AF02B88 | Fragment44_ShiftActiveScrollRecords | 160 | 0 |
| func_8AF02FC8 | Fragment44_StepScrollUp | 132 | 0x28 |
| func_8AF0304C | Fragment44_StepScrollDown | 184 | 0x28 |
| func_8AF03104 | Fragment44_AlignAndStepScrollUp | 148 | 0x28 |
| func_8AF03198 | Fragment44_AlignAndStepScrollDown | 212 | 0x28 |

All five winners are **link-verified** and pass combined full-ROM gates:

- `dc4cf735d6cc41a1bf88772447ff8676`: downward step and aligned downward step.
- `942fc3555dfe4dfba101a62c01b8af21`: upward step and aligned upward step.
- `371ad114834b432c9f7e648da1f5464d`: active-record shift.

### Source mechanisms and layout

The scroll state starts at parent +0x28, configuration at +0x44. Keep genuine
pointers to both. Upward callbacks use the configuration pointer for its +0xC
step; placing that assignment on its actual active path gives the original
0x28 frame and state-pointer spill. Inlining the step load through the parent
leaves a 0x20 frame even when normalized instruction similarity is 1.0.
Do not replace the configuration pointer with padding or an unused local.

Preserve signed 16-bit delay/counter loads and stores, the signed offset and
its zero/negative-extent clamps, dirty flags, helper calls, and dispatch codes
1 / 0xC4. The aligned callbacks adjust/clamp the counter and reset the delay
before performing the same update. Do not cache the offset in an extra scalar:
that changes the register roles without fixing the original source shape.

The shift routine visits **36 records**, stride **0x10**, starting at parent
+0x74. Only records whose first signed halfword is one have their signed
halfword at +6 shifted. A natural pointer-based `do` loop matches; IDO performs
the observed four-at-a-time unroll itself. This is not a four-record loop or
a handwritten unroll. The signed-halfword delta parameter reproduces its ABI
home and narrowing behavior; zero delta returns without modifying records.

### Argument forwarding repair

Already-accepted `func_8AF00130` in `fragment44_1EE290.c` had an inaccurate
no-argument definition and no-argument declaration for `func_800226C0`. Its
assembly leaves incoming `$a0` intact across the call, and the dispatcher
explicitly saves and reads `$a0`; existing fragment 44 callers pass one code.
Give the wrapper a real `s32 code` parameter and forward it explicitly.
Fresh/blank builds prove **all 40 function spans and every section byte in
that wrapper TU unchanged**, including the wrapper. This repairs the C
contract without adding a helper or claiming another newly decompiled owner.

### Verification and publication

Before new probes, both existing C siblings pass fresh/twenty-leading-blank
controls through the same native compiler, including complete sections and
all relocation rows. After readable cleanup and naming, fresh/blank builds
preserve frozen text/rodata/data/bss bytes and section layout, all **18 original
list-function spans**, and all **13 untouched list bodies**. The wrapper TU
retains all **40 spans/bodies** and complete frozen sections. No rodata layout
change is needed for this batch.

Forced native `gmake rom COMPARE=1` after cleanup/naming passes, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Host syntax checks for both edited TUs,
all 25 tooling tests and whitespace checks pass. Five compatibility aliases
retain the address-keyed US symbols; no JP assembly is changed. Generated
assembly, scratch generators/controls, compiler copies, objects and ROMs stay
local. No compiler changes, register forcing, padding or provenance bypasses.

### Leading-row builder requeue

`func_8AF0299C`: **requeue**, 32 compared source cells, 152-byte target.
Best normalized similarity **0.7895** (144 bytes); best raw similarity
**0.3421** belongs to a different 140-byte cell. Initial direct stores emit
124 bytes. Pre-store position/pixel snapshots, nested configuration views,
actual local decrement, signed/unsigned row arithmetic and pointer-vs-byte
indexing improve parts but do not close it. No row-job struct or builder C
is installed.

Target has separate narrowed look-behind/data-row arithmetic, a retained
+0x44 base and a separate extent negation. The candidates over-share those
computations or fold the base into parent-relative offsets. The stock 5.3
diagnostic does not improve the three selected forms; the project stays on
its unmodified 7.1 compiler. Both stock drivers preserve the two known C
controls, so that control alone does not identify historical compiler lineage.

Next inspect arithmetic/field provenance with the now-accepted caller layouts
and distinct signed address/index domains; do not replay declaration swaps or
infer an impossible compiler shape from the bounded negative. The trailing
builder remains assembly too and has an unprobed m2c draft for this session.
An initial callback-generator increment-parenthesis error produced compile
failures only; those records are retained as process evidence, not counted
as source-shape trials or accepted owners.

## 2026-10-16 — record culling and trailing-row batch accepted

Solo native macOS, no agents or containers. **Three functions / 149 words /
596 bytes**, taking this file from **7 C / 11 function ASM to 10 C / 8
function ASM**. All are leaf functions with no allocated frame.

| Original owner | Accepted name | Bytes | Full-ROM acceptance batch |
| --- | --- | ---: | --- |
| func_8AF02684 | Fragment44_CullScrollRecordsAbove | 204 | 7ac74937c0de4682a5d8e165d9e1dedc |
| func_8AF02750 | Fragment44_CullScrollRecordsBelow | 220 | 717cc7208e9044b49763f4633ed8bf2b |
| func_8AF02A34 | Fragment44_PrepareTrailingScrollRow | 172 | f9a4a132f6ad46f0941489aee57e5372 |

Each winner is link-verified and passed its authoritative full-ROM gate.
The culling routines scan all 36 records at parent +0x74, stride 0x10, and
clear only an active record whose signed coordinate crosses the appropriate
signed-halfword threshold. A natural pointer-based `for` loop reproduces
IDO's four-at-a-time unroll; the otherwise equivalent `do` form differs in
constant/counter scheduling. Keep the step as a real scalar. Swapping the
base-coordinate sum's source operands fixes its input-load ordering.

The trailing builder retains a configuration pointer at parent +0x44 and
loads step/width before computing the narrowed count and row. Declaration
permutations alone were inert; changing these independent load assignments
resolved the four-variable register rotation. Cache the completed pixel
address, not just its base. Preserve the capacity guard, tag 0x4F474942,
signed-halfword position/step and one-row/active fields in the existing
24-byte descriptor. No new callable helper is introduced.

Known C controls pass fresh/twenty-leading-blank compilation before probing.
After cleanup and naming, both builds retain complete frozen section bytes
and layout, all 18 original spans and all 15 untouched function bodies.
A forced native `gmake rom COMPARE=1` passes with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`; the edited TU's host syntax check,
all 25 tooling tests and whitespace checks pass. Three aliases retain the
address-keyed US symbols. No JP assembly, generated assembly, scratch helper,
compiler, object or ROM is included in the change.

### Updated unresolved owner handoffs

- `func_8AF0299C`: **requeue**, now 88 source cells plus one calibrated
  45-second native permuter run. Using configuration-relative prefix inputs
  preserves the missing base; distinct row computations and a narrowed
  negative extent recover the 152-byte target length. The useful 152-byte
  leader has normalized similarity 0.9474 (raw 0.3947); a different 156-byte
  form scores 0.9487 but has an extra instruction and is not a better shape.
  Remaining differences include row-web allocation and scheduling. Explicit
  early versus late unsigned data-row snapshots were inert in that basin.
  Replaying the permuter's inline decrement, carrier reuse and a 32-bit offset
  did not close it; its unexplained 64-bit offset mutation was not adopted.
  Next inspect the row/configuration web lifetimes with the stock compiler,
  then test a genuine typed configuration view against that measured trace.
- `func_8AF02AE0`: **requeue**, 16 source cells. Best normalized similarity
  0.8095, raw 0.3333, 164 versus 168 bytes, correct 8-byte frame. A wide current
  snapshot preserves the separate narrowed address input. Configuration vs
  parent-relative input loads and pixel/position snapshot order were tested;
  widening/reusing the total and moving its assignment earlier did not help.
  Target keeps capacity/step/total in different registers and has a
  branch-likely return with restore. Next inspect the configuration/total
  lifetimes and original record ABI before changing control-flow shape.

Neither unresolved body is installed. A runner warning that source variants
"will not close" a register tie was contradicted by the trailing builder's
accepted load-order change; treat that wording as advisory, not proof of a
compiler limitation. No tool or compiler behavior was changed in this batch.

## 2026-10-16 — initializer and draw follow-up, no new C acceptance

All work remains solo/native. The source still has **10 C / 8 function ASM**;
the normal retail-ROM comparison passes after the diagnostic work. No
compiler setting, partial C body, padding or register patch is installed.

- `func_8AF02C28`: **requeue**, 80 recorded source attempts and a calibrated
  45-second permuter search. The 380-byte / 95-instruction leader has the
  correct 0x30 frame and differs in only two raw words: offset 0x20 expects
  `addiu v1,a0,0x44` instead of `addiu s2,a0,0x44`; offset 0x28 expects
  `move s2,v1` instead of `move v1,s2`. An explicit endless entry scan with
  a negative-sentinel break fixes the rotated-loop shape. Distinguish the raw
  configuration address from its saved allocation-loop view. Taking a typed
  bound-field pointer inside the loop condition closes the instruction shape;
  removing that view loses one real copy, while caching it earlier changes
  scheduling. Pointer/integer view combinations and a paired pointer-ABI
  correction did not close the remaining copy direction; none was installed.
  The permuter's sole useful mutation was a fully initialized pointer used
  for the bound read, not a fake constant or an uninitialized carrier.
- `func_8AF02DD0`: **requeue**, 56 recorded source attempts. The 328-byte /
  82-instruction leader has the correct 0x50 frame, exact positional opcode
  sequence and eight raw differences, all stack offsets. Its normalized
  width is at sp+0x30 rather than 0x38, normalized third-height at 0x2C rather
  than 0x30, and byte advance at 0x28 rather than 0x2C. Inlining the temporary
  image-header view removes an extra frame slot; moving the byte-offset
  declaration after the signed x/y snapshots fixes their homes. Shared extent
  expressions, explicit width lifetime changes and an all-used local drawing
  state were tested without closing the remaining temporary homes. Preserve
  signed division by three, two equal buffer advances, and third-row y as
  `y + height * 2 / 3`, not `y + (height / 3) * 2`.

Twelve stock/diagnostic optimizer-listing controls preserve complete sections,
layout, symbols and every relocation row. They distinguish the leading-row
builder's copied row from the modified value in the `current` source slot;
a source slot is not one semantic value through the whole function.
`func_8AF0299C` now has 176 recorded attempts; the final eight-row manifest
contained six distinct bodies, a generator defect retained as process
evidence rather than claimed as eight independent hypotheses. Its generator
now asserts uniqueness. `func_8AF02AE0` has 32 attempts; an early-return guard
was inert on the previously recorded forms.

The alternate stock 5.3 driver leaves the initializer's two-word residual
unchanged, worsens the draw leader to 336 bytes / 69 raw differing words, and
changes four of the ten accepted siblings. The configured 7.1 driver retains
all ten siblings. This rules out that proposed whole-file compiler switch,
not every historical frontend. For the initializer, forced g0 does not alter
the residual; g3 changes other instructions and is not a fix. Calibrated AS1
listings already contain the reversed pair before instruction scheduling.
Next isolate its producer before that boundary rather than blame scheduling
or declare a compiler impossibility. For drawing, inspect the real/synthetic
temporary-home allocation rather than add unused locals to move the frame.
