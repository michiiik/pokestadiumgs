# Fragment 44 scroll-list updates

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
