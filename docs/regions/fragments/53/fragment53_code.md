# Fragment 53 animation family

## 2026-10-16 — pending primary animation accepted

`func_865038A8` is now `Fragment53_ApplyPendingPrimaryAnimation`, **36 words /
144 bytes**, original frame **0x20**. Native runner batch
`a539d4f759ab4c18bc06fec45ee2218c` accepted it with `link_verified: true` and
one combined full-ROM gate. Solo local work, no agents or containers.

The state array has 0x98-byte stride, animation at +0x0C and pending flag at
+0x10. The primary model array has 0x168-byte stride. When pending is exactly
one, apply the selected animation, reset the animation frame to zero, then
clear pending. Both actual callee signatures are preserved.

Use ordinary direct array expressions. Two named pointer locals reproduce
the instructions but grow the frame to 0x28; `register` qualifiers do not
repair it. Parameter reuse restores frame size but changes the argument home
and reload schedule. Eliminating the pointer locals closes the exact match.
The final eight-cell direct-expression batch has link-verified alternatives;
only its first accepted spelling is installed.

After cleanup and naming, fresh and twenty-leading-blank object builds preserve
all text/rodata/data/bss bytes and layout against the accepted object, all 56
function offsets/sizes/spans, and all 55 untouched raw spans against the
pre-batch object. Forced normal ROM build remains byte-identical to retail,
MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 25 tooling tests pass. No scratch
generators, compiler copies, objects, ROMs, padding, or helper functions are
committed. File progress is 13 C / 43 function ASM to 14 C / 42 function ASM.

## Requeues from the four-function family

`func_86508780`: 25 compared candidates. Best normalized/raw 0.9559/0.6471,
264 bytes versus 272 expected. Explicit state/model locals have the expected
0x30 frame but do not preserve the index in `$s0`; direct model expressions
shrink the frame to 0x28 and keep the index in `$a2`. A shared model address
and if-chain change the instruction shape. Case-return combinations and
state-pointer/value snapshots do not fix it. Requeue: investigate why the
original index is callee-saved despite both model addresses being branch-local;
do not add an artificial use to force preservation.

`func_8650863C`: 25 compared candidates. Best normalized/raw 0.9250/0.7250,
320 bytes versus 316 expected. The original preserves model/index in `$s0`/
`$s1` and schedules the frame setup within address formation. Shared model
addresses, state snapshots, if-chains and case exits do not close it.
Requeue: inspect the frame-field load and whole-function live ranges before
allocation permutations. The animation-frame threshold is signed fixed-point
`(frame >> 16) >= 6`; the completion sound takes the low byte of the index.

`func_86508890`: 32 compared candidates, then a calibrated 45-second permuter
search. Moving the dispatch counter initialization before its state-pointer
assignment, and using a real 15-frame random span, reaches the original
97-word / 388-byte opcode shape and 0x30 frame. Raw similarity remains
0.7320: registers still differ. Declaration order is inert in the bounded
eight-cell test. Typed model pointers, pre/post clear placement, separate
state carriers and counter placement do not produce an exact match.

Permuter base/probe bytes and target/oracle bytes are independently identical
before search. Its score improves 240 to 160, but the best mutation reads an
uninitialized model pointer in an empty condition and is rejected as invalid.
No mutation is installed. Other retained outputs introduce a genuine end
pointer; a future source test may use that lifetime after removing any
constant-true wrapper. Requeue: compare the pointer/constant color costs or
test that real end-pointer lifetime, not more declaration permutations.

All unresolved functions remain assembly. Keep model-setup prototypes
consistent with their actual declarations, the signed `guRandom()` remainder,
four actor updates, and both primary/secondary model loops. After an accept,
refresh declarations from the current source instead of reinserting the
already-installed struct definitions.
