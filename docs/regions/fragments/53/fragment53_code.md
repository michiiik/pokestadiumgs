# Fragment 53 animation family

## 2026-10-16 — four-function batch complete

`func_86501D6C` is now `Fragment53_CountTrajectorySamplesInRange`, **77 words /
308 bytes**, no stack frame. Batch `3b6c0332772d477a98da174091ad3236`
accepted the second candidate with `link_verified: true` and one combined
full-ROM gate. It resets the count, calculates the lower vertical boundary,
and evaluates 100 parabolic samples at successive trajectory times.

Use the direct double-precision expression, round each position to `f32`, and
count when neither `position < lower` nor `upper < position` holds. The
negated less-than spelling preserves the oracle's unordered/NaN behavior;
replacing it with two positive ordered comparisons changes instructions and
semantics. The normal compiler unrolls the natural 100-iteration loop by two:
no hand-unrolling, local cached scale, or local time is needed. Naming,
indentation, and duplicate-extern cleanup preserve all accepted object bytes.

The four accepted functions total **282 words / 1128 bytes**. Final fresh and
twenty-leading-blank builds preserve full text/rodata/data/bss bytes and
layout, all 56 original function spans, and all **52 untouched raw spans**.
Forced normal `COMPARE=1`, host syntax check, and all 25 tooling tests pass.
The ROM is byte-identical to retail, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Overall file progress is
**13 C / 43 function ASM to 17 C / 39 function ASM**. Only source,
compatibility aliases, and these evidence notes belong in the PR.

## 2026-10-16 — trajectory and scene transition accepted

`func_86501FA0` is now `Fragment53_UpdateTrajectoryPosition`, **78 words /
312 bytes**, frame **0x18**. Batch `5b2f65f77dc843949684fe4024295802`
accepted the direct-global spelling with `link_verified: true` and one combined
full-ROM gate. Advance/wrap/clamp the trajectory step in mode ten; otherwise
invoke its selector. Preserve the double-precision parabolic expression and
the subsequent single-precision normalized integer output. No local time,
scale, or counter carrier is needed. Unused declarations from the exploratory
batch are removed after acceptance.

`func_8650A278` is now `Fragment53_RunSceneTransition`, **91 words / 364 bytes**,
frame **0x30**. Batch `3fcf5edadb0a40bfae7cfc5084e79743` accepted it with
`link_verified: true` and one combined full-ROM gate. In mode four, reset four
primary/secondary actor models and choose signed random animation frames;
then fade from opaque and update the scene until its stored result is three.

The calibrated 45-second permuter improved a 110-point seed to 95 without a
match; reviewed source variants then closed the residual. Initialize secondary
and primary model pointers on one line, then resource/state pointers and the
`do` on one line. This schedules the entry address construction correctly.
An explicit end-pointer local changes allocation and does not help. The last
one-word residual is the final `bne` operand order: test the stored scene result,
not its local return-value carrier. This is an actual source-level distinction,
not a patched branch. Eight-cell exit batch accepted its fourth candidate.

The accepted giant-line loop was replaced with a readable multiline body after
a fresh scratch build proved every text/rodata/data/bss byte and the complete
object link shape identical. Only the two short initialization groups need
to stay paired. Redundant casts/declarations are removed; no fake conditions,
uninitialized reads, padding, compiler modifications, or helper functions land.

After naming, fresh and twenty-leading-blank object builds preserve all 56
original function offsets/sizes/spans and all **53 untouched raw spans**.
Full section bytes/layout match the frozen accepted object. Forced normal ROM
build is retail-identical, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. Progress
from the original batch baseline is **13 C / 43 ASM to 16 C / 40 ASM**.

### Updated unresolved handoffs

`func_86508890`: **48 compared** plus the earlier calibrated permuter. Eight
real-end-pointer placements/reused-span variants and eight typed byte/word
state views retain best normalized/raw **1.0/0.7320**, 388 bytes, frame 0x30.
A fresh logging-only IDO calibration passes stock/off/on/blank controls for a
known match and this leader, including section bytes, symbols and relocations.
Its measured colors are model/index `$s0` (disjoint), state `$s1`, resource
`$s2`, secondary `$s3`, end `$s4`, literal fifteen `$s5`; original roles differ.
Requeue: change a genuine pointer/constant cost or live-range relationship,
not declaration permutations, span widths, end placement, or typed views alone.
This trace describes the candidate, not the unknown original compiler IR.

`func_86509318`: **24 compared**, plus eight declaration-order compile failures
that are not source-shape evidence. Best normalized/raw **0.8222/0.6778**,
356 bytes against 360 expected. Typed effect views, loop form, shared stride,
entry/per-iteration scale caching, and geometry snapshots are tested. Original
caches the scale across actors but reloads after initialization callbacks,
loads geometry before stores, and uses a different alpha-saturation branch.
Requeue: inspect alias-sensitive scale ownership and the alpha clamp before
further carrier permutations. Leave the owner in assembly.

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
