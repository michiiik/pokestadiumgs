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
