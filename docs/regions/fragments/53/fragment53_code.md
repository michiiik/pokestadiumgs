# Fragment 53 animation family

## 2026-10-16 — round initializer accepted; earlier rodata ownership resolved

`func_86502720` → `Fragment53_InitRoundState`, **142 words / 568 bytes**, frame
**0x50**, batch `25e2c509ff8c4dfa8dd58252d284d00c`. This is a relocation-masked
**sequential full-ROM accept, not link-verified**. The two raw address addends
use equivalent one-past-array bounds; the linked retail ROM is exact. Progress:
**25 C / 31 function ASM → 26 C / 30 function ASM**.

Extend the existing canonical rodata window to **0x296B80..0x296D70**: 496 bytes
instead of 64, adding 432 bytes at the front. Both ends are 16-aligned. The
extension has 56 referenced symbols, all belonging to this TU; its first bytes
are the 0.3 double, 10000 float and 3.1 float. Do not use the coarse planner's
0x296350 start, which includes an unreferenced prefix. Do not create duplicate
same-file rodata subsegments or duplicate the constants.

Accepted `func_86502620`'s last scale case now uses its genuine **double 0.3**
literal instead of external D8650D6D0. A scratch build verifies identical raw
helper instructions and the expected leading eight rodata bytes. The other
accepted C's external doubles remain in the shared head. Re-split with pinned
SPLAT/spimdisasm, then pass a normal retail-ROM gate with the round and result
owners **still assembly** before installing any candidate. This baseline gate
proves the complete intervening pools, tables and alignment bytes are retained.

The round initializer preserves four actor records' clears, bounds, floating
fields, unsigned RNG remainders, signed random direction, trajectory setup,
scene resets and nested four-by-two model resets. Its actual **10000.0f**
literal closes the former entry-load schedule residual. Read the scene counter
before the other context clears, as in the oracle. Natural indexed `for` loops
match; no pointer scaffold or hand-unrolled loop remains.

After readable cleanup and naming, fresh and twenty-leading-blank object builds
preserve all frozen section bytes/layout, all 56 pre-layout function spans,
all **55 untouched post-layout raw spans**, and the complete **496-byte rodata**
against the assembly-only baseline. Forced normal ROM comparison is retail-
identical, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`; host syntax check and all
25 tooling tests pass. Only source, YAML, one compatibility alias and these
notes are committed. Generated assembly/YAML, scratch scripts/proofs, compiler
copies, objects and ROMs stay local. No agents, containers, padding or bypasses.

### Newly ready dispatchers and measured requeues

The extension gives **jtbl_8650D70C / func_86503938**,
**jtbl_8650D72C / func_865040E4**, and **jtbl_8650D808 / func_8650515C** canonical
ownership. jtbl_8650D680 is before the new cut and remains a separate prerequisite.

`func_86503938`: **requeue / frame residual**, 33 compared cells. Best natural
source is 152 words / 608 bytes, normalized/raw 1.0/0.9803: only an eight-byte
frame excess (0x38 versus 0x30) and the jump table's object relocation offset
differ. A genuine index-copy local and branch-assigned model pointer reproduce
the instruction roles. Removing the explicit offset local does not reduce the
frame; a state-pointer carrier, narrow/register formals, branch-local model
scope and parameter reuse do not close it. A calibrated 45-second permuter
improves 30→10 via a valid comparison-operand swap, but the full-TU replay
retains the same frame mismatch. Do not treat the standalone score as acceptance.

The standalone import has table offset zero versus full-TU offset 0x3C. Before
search, link both at their actual text/rodata addresses using canonical symbol
addresses: all 608 linked instruction bytes and 32 table bytes are identical.
This is import calibration, not a ROM gate. Next inspect CFE local homes and
uopt/UGEN spill ownership; do not repeat the source families above or patch the
frame. The dispatcher remains assembly.

`func_86502B88`: **requeue**, now 64 compared cells. Eight genuine 3.1f literal
cells improve best raw similarity to 0.7937 at normalized 0.9762, but the
result-store constant sharing/stack layout still differs (492 versus 504
bytes). Canonical placement alone does not solve it. Retain the previous
constant/alias-ownership next hypothesis; do not re-send the literal family.

`func_86500020`: **requeue**, now 16 compared cells. Readonly template/index-table
declarations leave the prior unroll residual unchanged (best 0.4927/0.1171,
580 versus 820 bytes). The additional known template consumer copies it too;
the const hypothesis is not an unroll fix. All unresolved pragmas stay installed.

## 2026-10-16 — actor state/order and start-state transition accepted

Two solo native accepts, **207 words / 828 bytes**, progressing the file from
**23 C / 33 function ASM to 25 C / 31 function ASM**:

- `func_86502958` → `Fragment53_InitActorStateAndOrder`, 140 words / 560 bytes,
  frame 0x40, batch `cc483c232a20441fa9647b8f5f35e6e2`.
- `func_86508B20` → `Fragment53_UpdateStartState`, 67 words / 268 bytes,
  frame 0x30, batch `386740e7d44c4fae9df585111232d736`.

Both have relocation-masked probe evidence and **sequential full-ROM acceptance,
not link verification**. The compiler uses equivalent one-past-array addresses
for the actor height loop and the secondary model loop. The authoritative
linked retail-ROM gate validates their resolved addresses, not their object
relocation spellings.

The initializer preserves unsigned `func_8003570C` remainders, the original
negated-subtraction height expression, and signed `guRandom()` remainders.
It initializes four actor records, fills the five-entry order table, then makes
ten swap attempts. Retry until the two indices differ, but do not swap slot
zero. Saving the **first** entry as the swap temporary, then replacing first
from second, closes the eight load/store register differences. Direct indexed
actor/height arrays and ordinary `for` loops need no pointer scaffold.

Move the existing 0x98-byte actor type and 0x168-byte model type before their
first C use; expose verified score/result fields at +0x18/+0x84 while retaining
animation +0x0C, pending +0x10, kind +0x88 and all record strides. The assembly-
only owners and all existing C remain byte-identical after this type cleanup.

The start handler polls shared status twice, preserves both sounds, enters
state one/phase minus two and initializes four primary/secondary model pairs.
Its sole call in `func_86509E54` discards the return and later reloads the scene
state. Preserve the original early zero return and other paths' fallthrough;
do not manufacture a return value or read an uninitialized temporary. Correct
the accessor prototype to its real `u32` result and compare explicit `s32`
casts: leaving comparisons unsigned introduces an extra literal-one load.
The host's missing-return warning is expected for this legacy discarded-result
contract. Put the real void sound prototype before its earlier caller through
the accepted companion edit; that caller's raw bytes remain unchanged.

After readable cleanup and naming, fresh and twenty-leading-blank objects
preserve all frozen section bytes/layout, all 56 original function spans and
all **54 untouched raw spans**. Forced normal ROM comparison remains retail-
identical, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`; host syntax check and all
25 tooling tests pass. No padding, helpers, storage, compiler edits or bypasses
are included. Scratch tools, traces, generated assembly, objects and ROMs stay
local. No agents or containers are used.

### Round initializer: concrete layout prerequisite

`func_86502720`: **layout-prerequisite**, 40 compared cells plus eight initial
prototype compile failures (fixed without changing the existing callee return
contract). The external-float leader has the original 142 words / 568 bytes
and 0x50 frame, normalized/raw 0.9930/0.9718. Reading the scene counter before
the other context clears fixes the later setup schedule. Actor-base lifetime,
cached/inline zero, loop-init and first-store line ties do not fix the remaining
entry float-load schedule; a calibrated 45-second permuter stays at 100.

Using the actual **10000.0f** literal closes the scheduling residual: normalized
1.0, raw 0.9859, with only the two one-past-array relocation addends differing.
The runner rejects **section_layout_drift** because D8650D6D8 is still in the
shared head at ROM **0x296B88**. Stop source variants here. The file's current
canonical rodata starts at 0x296D30/D8650D880, too late for this float. Next:
plan an earlier canonical ownership range, preserving already-accepted C's
external doubles/constants and original rodata order, then gate the still-ASM
owner before retrying the retained literal candidate. Do not emit a second
copy of this float, introduce padding, or bypass the non-text layout rejection.

### Other bounded unresolved work

`func_86500D5C`: **register-tie / requeue**, now 48 compared cells. Eight genuine
vertex/packet pointer-reuse cells and eight index/stride width cells retain
normalized/raw 1.0/0.9515. The calibrated logging-only trace identifies literal
360 in uopt global coloring, not UGEN temp rotation. The captured leader uses
physical register three for this stride; the original uses six. Next inspect
interference/lifetime legality, not another declaration/cast/reuse spelling.

`func_86502B88`: **requeue**, 56 compared cells and a calibrated 45-second
permuter (725→487; its constant-one carrier leader is not adopted). Explicitly
cache the shared 3.1 float: `const` on its extern alone is inert. A real 26.0f
height local before the flags array reproduces the stack-array placement and
saved float roles. Joining the initial best-score assignment to the loop header
and re-reading the non-overlapping score improves the source to 0.9762/0.7540
(492 versus 504 bytes, 0x90 versus 0x88 frame). The shorter exact-frame leader
is 0.9762/0.6746. Four all-tie result stores still share constants differently.
Pointer/index loops, typed fields, flag-store statement groups/chains, float
local order and the two valid permuter replays have been measured. Next examine
the constant-sharing and alias ownership; do not replay those families.

`func_86500020`: **requeue**, eight first-source cells; best normalized/raw
0.4927/0.1171, 580 versus 820 bytes. The oracle copies fourteen Vtx records
with a peeled/unrolled loop and fully expands seven paired Y-coordinate edits.
Natural indexed/pointer copy loops, direct/local context and for/do adjustment
loops do not reproduce that expansion. Next verify template/index-table
immutability and the compiler's unroll decision; do not hand-unroll just to
improve a score. All unresolved pragmas remain installed.

## 2026-10-16 — scene rendering and lifecycle entry accepted

Two native, solo full-ROM accepts after the actor/model batch:

- `func_865082C8` → `Fragment53_DrawSceneFrame`, 111 words / 444 bytes,
  frame 0x20, batch `684ff48c27a14142a6470311f142d3b4`.
- `func_8650A3E4` → `Fragment53_RunScene`, 127 words / 508 bytes,
  frame 0x28, batch `23f574cc468d4e0d99a56579f3f03618`.

Both use a sequential authoritative retail-ROM gate, **not link verification**.
The dispatcher has relocation-masked probe evidence. The entry's local call to
the already-decompiled transition changes object relocation representation
(`UND:func_8650A278` versus a section-relative call); the linked ROM is exact.

The canonical 13-entry jump table added with the previous batch makes the
dispatcher ready. Keep the switch directly on context +0x0C, with no explicit
default arm or shared context-pointer local. Cases 2/12 share one path;
10 falls through to 1/6. All independent overlay conditions and the final
mode-four overlay are preserved. Adding an explicit default grows the owner.

The entry initializes display/resources/assets, invokes the transition loop,
releases resources, and returns the scene result. Read the mode byte through
the stored global context after assigning it, not directly through the formal;
the latter loses the expected load/schedule. The existing shared 1.2 float
remains external. No extra rodata split, padding, helper, storage or compiler
change is needed. `func_8004DEF8` is called with its observed return-value ABI:
this caller and `func_80071984` both consume its forwarded return, although its
current C definition in another translation unit is spelled `void`.

Readable cleanup, behavior-backed names and address-compatible aliases retain
all frozen text/rodata/data/bss bytes and layout in fresh and twenty-leading-
blank object builds. All 56 original function spans and 54 untouched raw spans
are preserved. Forced normal `gmake rom COMPARE=1` is retail-identical, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`; host syntax check and all 25 tooling tests
pass. Progress: **21 C / 35 ASM → 23 C / 33 ASM**, 238 words / 952 bytes.
Scratch proofs, generators, extracted assembly, compiler copies, objects and
ROMs stay local; no agents or containers are used.

### Unresolved handoffs from this block

`func_86500D5C`: **register-tie / requeue**, 32 compared source cells and a
calibrated 45-second permuter. Vtx union copies give exact 103-word opcode
shape and 0x18 frame, normalized/raw 1.0/0.9515. The remaining five raw words
are the shared model stride's `$a2` versus `$v1` and one address operand order.
Vtx_t field copies grow the owner to 540 bytes. Typed model access, a real
stride local, element/pointer copy forms, guard return, callback-node typing,
the allocator's actual u32 return ABI, and copy/display-list line grouping
do not close it. The permuter's 150→30 line-only improvement does not reproduce
when replayed through the full translation-unit runner; it is not a match.
Next: inspect whole-TU reservation/lifetime evidence for the stride and packet
carriers, not another spelling-only loop. Leave the pragma installed.

`func_8650A074`: **requeue**, 40 compared source cells plus eight initial
compile failures (postincrement precedence, fixed; not hypothesis evidence).
Best normalized/raw 0.9023/0.4586, 532 bytes versus 516; the shorter natural
baseline is 520 bytes at 0.8923/0.4769. Context pointer/direct/typed views,
phase cache, random-delay carrier reuse, signedness, timer temporaries, split
pause guards, pointer/index animation scans, and genuine stage-pointer
lifetimes have been tested. A calibrated 45-second permuter improves 3005→1725,
but its leader introduces a synthetic constant-zero carrier and is not adopted.
Other outputs suggest a real stage pointer; the bounded replay above improves
shape but not size or raw bytes. Next: inspect initial phase/delay pointer
ownership and the extra global-address materialization before random callbacks;
do not repeat declaration order or those source families. Keep ASM.

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
