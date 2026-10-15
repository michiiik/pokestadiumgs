# Fragment 53 animation family

## 2026-10-16 — actor initializer accepted; four-function follow-up complete

`func_86508484` is now `Fragment53_InitActorModels`, **110 words / 440 bytes**,
frame **0x50**. Batch `f5faea2051ed41278f66725c1f5024c0` accepts the natural
four-actor `for` loop with the actual `0.095f` scale literal, signed random
animation frames, model resets, placement, flags, and final scene setup.
This is a **relocation-masked sequential full-ROM acceptance, not link-verified**.
The three other accepts below are link-verified combined-gate results.

The prerequisite is now resolved: add the tight **64-byte** canonical `.rodata`
window at ROM **0x296D30..0x296D70**, re-split with splat 0.25.0 / pinned
spimdisasm 1.35.0-dev0, and gate the still-ASM initializer before replacing it.
The window contains D8650D880, D8650D884, all 13 entries of jtbl_8650D888, then
D8650D8BC, in source order. Both boundaries are aligned and no unreferenced
prefix/tail is dropped. The rest remains in the shared head and rodata tail.
The assembly-only ROM gate passes before the candidate is installed.

The layout move preserves all 56 original function starts/sizes. It changes
one untouched object's representation: exporting `.L8650A054` for the rodata
tail creates **15 R_MIPS_PC16 branch relocations** in `func_86509E54`, instead
of in-object resolved displacements. Every differing raw word is accounted
for by one of those relocations; both linked ROMs remain retail-identical.
Do not describe this as an unchanged raw object or a code change.

Final fresh/twenty-leading-blank builds preserve complete frozen section bytes
and layout, all 56 original function spans, all 52 untouched post-layout raw
spans, and 51 untouched pre-batch raw spans plus the measured relocation owner.
The four functions total **340 words / 1360 bytes**, progressing this file
from **17 C / 39 ASM to 21 C / 35 ASM**. Forced normal ROM comparison,
host syntax checks and all 25 tooling tests pass after cleanup/naming.

The local runner's duplicate guard previously fingerprinted the Makefile and
compiler override but not canonical layout, incorrectly blocking the proven
candidate after this split. A local layout-context fingerprint and historical
fallback fix that stale rejection; changed-layout replay, unchanged-layout
rejection, compiler identity and conservative legacy behavior are checked.
No guard/statistics bypass or compiler patch is used. Runner copies and scratch
proofs are not part of the public decompilation PR.

## 2026-10-16 — secondary handlers and model-height callback accepted

Three additional native matches, all `link_verified: true` and accepted through
one combined full-ROM gate each:

- `func_86508780` → `Fragment53_UpdateSecondaryAnimation`: 68 words / 272 bytes,
  frame 0x30, batch `0fcf54d4a8114533acb1b69aee41d5f8`.
- `func_8650863C` → `Fragment53_UpdateTimedSecondaryAnimation`: 79 words /
  316 bytes, frame 0x30, batch `a05bf1b620b84a09a333b96aacfab972`.
- `func_8650455C` → `Fragment53_UpdateActorModelHeights`: 83 words / 332 bytes,
  frame 0x20, batch `6c0cdf774eb641af937f59a0cc14c1c8`.

Both animation handlers need a genuine `index = arg0` local followed by direct
state-array references. For the ordinary handler, use direct model-array
expressions too: a model-pointer local grows the frame. For the timed handler,
keep its branch-assigned model-pointer local: direct model expressions instead
move the saved state address from stack +0x20 to +0x24. Signed/unsigned and
`register` formal variations alone were inert. The index local is actively
used, not padding or an unused register-forcing variable.

The timed handler preserves the signed fixed-point frame-six threshold,
zero-frame restart, triple/double animation speeds, and actor-indexed completion
sound. The ordinary handler preserves the pending-primary-animation flag.
The callback cycles the 24-step pose counter and updates paired model heights;
one shared `index * 0x168` offset closes its register-role mismatch.

After naming/cleanup, fresh and twenty-leading-blank builds preserve complete
section bytes/layout, all 56 original function spans and all 53 untouched spans.
Normal forced ROM comparison, host syntax check and 25 tooling tests pass.
No new helpers, storage, padding, compiler changes, or provenance bypasses.
Progress is 17 C / 39 ASM to 20 C / 36 ASM (230 words / 920 bytes accepted).

### Initializer layout prerequisite

`func_86508484`: 32 compared plus a calibrated 45-second permuter. Best external-
scale spelling has the exact loop body/size/frame but a different entry load
schedule; explicit cached-height initialization and eight logical-line cells
do not repair it. The permuter is flat at 491, with no retained improvements.

Using the actual `0.095f` literal instead yields **raw/normalized 1.0/1.0**,
110 words / 440 bytes, but `section_layout_drift`: the literal still lives in
shared fragment data. This is `layout-prerequisite`, not a register tie. Do not
repeat source spellings until canonical rodata ownership is installed and the
still-ASM initializer is gated. A tight aligned window is ROM 0x296D30..0x296D70
(VRAM D8650D880 through D8650D8BC): earlier two float owners, the complete
13-entry `jtbl_8650D888`, then this initializer's float, in source order. The
coarse planner's much larger widened run is not the correct cut point.

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
