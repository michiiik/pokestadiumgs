# Fragment 52 resource and object-pool family

## 2026-10-14: four-owner solo native batch

Accepted existing owners through the normal candidate runner:

- `func_86407AA0`:45 instructions /180 bytes, original0x20 frame.
- `func_86407B54`:39 instructions /156 bytes, original0x30 frame.
- `func_86407BF0`:60 instructions /240 bytes, original0x28 frame.
- `func_86407CE0`:30 instructions /120 bytes, leaf frame0.

No prior attempts for these five owners were found in the consulted private
ledger. Baseline native ROM comparison and fresh known-matching texture/graph
controls pass before hypotheses. Submit eight distinct source variants per
owner,40 in the first family batch. Setup and iteration accept the first
natural pointer-based candidates, link_verified=true and auto_gated=true in
one combined full-ROM gate. Timing:9.057s probes /1.932s gate /10.993s total.
Stop probing accepted owners. Statistics remain enabled throughout.

Setup uses all available memory to allocate the pool state, builds the graph
from D_86409800, finalizes that allocation, loads resource IDs0x157/0x133,
constructs the display list at segment0x0F000000 and initializes four items.
Retain the global reloads around calls, rather than caching state across calls.
Verified state fields: graph at0x7B0, group at0xAF08, inline0x18C-byte items
at0xAF1C and display list at0xB54C. Iteration advances the actual item pointer
while re-reading the current global group count after each callback; no new
count/null guards or cached termination condition.

Display callback does work only for kind5. Preserve pipe sync, black environment
color with alpha0x80, original two-cycle combine fields, segment15 binding via
the existing resource/texture-data loaders, display-list emission and final
existing callback. A block-local live Gfx pointer matches the original0x28
frame and stack home; a top-level pointer instead gives0x20. No frame filler.
The three standard graphics macros and exact segment command words reproduce
the original instruction stream. Initial normalized1.0/raw0.9167 was not proof.

Transform callback does work only for kind2. Always acquire its source and
related-state pointers first, as the original does. Copy x/z, zero y and copy
the signed angle. The condition is the related object's signed field at0x20,
not the pool's offset0 count. Initial candidates using the latter are rejected,
never installed. Real f32 scale locals preserve the original shared loads and
avoid reloading chained stores. The positive path uses D_86409C40 for all axes;
the other path uses D_86409C44 for x and D_86409C48 for y/z. Do not add guards.

Display and transform accept first candidates in their diagnostic-directed
eight-variant families after8 prior attempts each, link_verified=true and
auto_gated=true. Combined timing:7.845s probes /2.032s gate /9.879s total.
Readable cleanup annotates verified offsets, gives the related-state pointer
its actual field view, removes redundant/unused declarations and casts, and
retains the matched expression/statement topology. No new helper functions,
headers, compiler patches, byte rewrites or acceptance bypasses.

Fresh final native gmake rom COMPARE=1 passes with default syntax checks;
retail MD5 remains1561c75d11cedf356a8ddb1a4a5f9d5d. All427 C sources pass
cc-check. Fresh final-source/build/20-leading-blank-line object controls match
all four accepted functions and the unchanged168-byte assembly attachment.
Independently compare their linked retail spans at0x285F60/0x286014/0x2860B0/
0x2861A0/0x286218. An early diagnostic tried comparing an unlinked relocatable
sibling directly with retail bytes; it stopped on the control failure. Correct
the control to object-versus-object plus hash-verified linked-ROM evidence and
reverify before subsequent candidates. The object helper is not an ELF-VMA
reader; do not use it as one. All scratch and dependencies stay local.

## func_86407D58: frame/scheduling requeue

Leave this owner GLOBAL_ASM:40 executable instructions /160 bytes plus eight
verified alignment bytes, original0x20 frame. Preserve optional allocation,
node base at item+0x24, callback/user-data setup, two existing node operations,
graph binding, shared y/z scale constant, x scale constant and signed angle
-0x4000. No accepted C body exists for this owner.

32 normal candidates cover real pointer/word carriers, local scope/declaration
order, shared scale temporaries, final scale/store ordering and natural line
grouping. Best raw0.7857/normalized0.9286 on the full168-byte owner span; the
frame remains0x28 instead of0x20, with displaced incoming/item stack homes
and float-store scheduling. This is not a register-only exactness claim.

A calibrated native90-second permuter run proves parent/probe words identical
and target/oracle168-byte words identical before searching. Score312 improves
to94, but no zero is found. Proposed one-shot-loop wrappers are not adopted;
review their transformations into natural block scopes and statement grouping
and test eight normal variants. None passes. The padding pragma accounts only
for the existing eight alignment bytes, not stack-frame or missing-code bytes.

Next action: materially different real carrier lifetime/float-conversion
topology or a calibrated narrow allocator/frame trace explaining the extra
live-home space. Avoid replaying the same scoped layout families. This bounded
search does not establish that the function cannot match. Full matching-C
decompilation remains unfinished; descriptive names await independent evidence.

## 2026-10-14: attachment follow-up, no source acceptance

Fresh controls reverify all four accepted siblings and the unchanged attachment
against current source/build objects, blank-line recompiles and linked retail.
Forty additional normal candidates test materially different hypotheses:
declaration initialization and parameter reuse, standard C register hints on
real carriers, the allocator's 32-bit address boundary with assembly-verified
narrow node-operation formals, fixed-literal const views, and scalar member
versus array-field lowering. None fixes the0x28 versus0x20 frame. Const views
are justified by the consulted source/assembly having only literal definitions
and this owner's loads, no writes; even that cell is negative. No variant or
new type/prototype from these probes is installed or published. Do not replay
these families under unchanged context. The next useful discriminator remains
a calibrated compiler/frame trace explaining the reserved space, rather than
further surface-level scope hints. This is bounded evidence, not impossibility.

## 2026-10-14: attachment source shape resolved; data-layout prerequisite

Forty-eight fresh normal candidates and a calibrated native permuter follow-up
change the next action. The original inline-node candidates retained an unused
node declaration. Removing it gives the original 0x20 frame and stack homes;
adding a float temporary restores the unwanted 0x28 frame. Independent accesses
to private scale constants avoid the external-data alias/reload issue.

The native search on exact float literals starts at score200 and reaches zero
after51 seconds. Both base/probe and target/oracle calibrations pass. The zero
source contains no artificial locals, loops, guards, uninitialized reads or
deleted behavior: it groups allocation, null guard, callback setup and the next
call on one physical line, then binds the graph and writes x/y/z scales followed
by the angle. Eight reviewed normal storage-provenance variants confirm that
both the literal and function-local-static versions reach the same shape.

Fresh comparisons over the complete168-byte span, including the verified eight
alignment bytes, leave only the relocation-controlled low field of the second
float load: baseline0 versus compiled4. The compiler function symbol remains
160 bytes; a symbol-only diagnostic omits the separate padding block and reports
normalized0.9524 rather than complete-span instruction agreement. The raw
complete-span score is0.9762, not exact bytes and not acceptance. File-scope
static storage does not preserve this shape.

Use exact initialized words: scaleYZ5.28f is0x40A8F5C3; scaleX2.534400225f is
0x4022339D. The shorter2.5344f is0x4022339C, one ULP wrong. The initial private
storage cells used that shorter literal, so they establish code-shape evidence
only, not data correctness. Subsequent literal and reviewed-zero cells use the
correct bits, independently verified in emitted data.

Next action, layout-prerequisite: give this C file the original32-byte data block
at ROM0x288100..0x288120. Its first three floats are the existing CE0 symbols
D_86409C40/44/48, followed by D58's private y/z and x scales at offsets12/16.
Preserve old address aliases for D_86409C4C/50, split the original assembly data
before and after that block, and gate the still-assembly D58 before the runner
transaction transfers its actual scale storage into the accepted candidate.

An off-tree prerequisite preflight defines the three existing CE0 globals and
temporarily gives CE0 the two initialized scales consumed by the original D58
assembly. All five function words remain identical to the current build and
the emitted32-byte data block is exactly retail, including its12 trailing zero
bytes. This is object evidence only; no tracked layout/source edit or full-ROM
gate for that prerequisite has occurred yet. Temporary storage must be removed
atomically when D58 takes ownership; never publish duplicate/fallback scales.

Local artifacts: scratch/native-attachment-zero-batch.json candidates0 and2,
native-attachment-zero-diagnose.log, native-attachment-data-preflight.log, and
permuter/func_86407D58-ekk41y71/output-0-1/source.c. Normal runner provenance has
no accepted D58 row yet; its GLOBAL_ASM remains untouched. Baseline full ROM,
all427 host syntax checks, fresh/blank controls and diff checks pass.
