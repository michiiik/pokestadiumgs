# fragment67_34C8B0

## func_8290FDB0

Accepted recipe: a signed-halfword argument and an aligned eight-byte `unk_func_8290FDB0` packet. Copy the existing packet with `func_80054210`, replace byte `unk_00` with `arg0 + 1`, and publish it through `func_80054248`. Keep the preceding `func_80055948(3)` and following `func_80051D64(20, 0)` / `func_80055028()` calls in their original order. The word results from the first and last helpers are ignored.

The original caller `func_8290FE04` passes a signed halfword loaded from its incoming argument home. The owner stores that argument at its incoming home and reads the low signed halfword after the packet copy. The compiled definitions of `func_80054210` and `func_80054248` copy and compare two words at record offset 20, establishing the full eight-byte packet footprint. The unknown bytes are retained by copying the complete packet before changing its first byte. No artificial arguments or scratch padding are needed.

The complete independent owner contains 21 instructions, a 32-byte frame, and its own return. It is separately called and contains no shared switch tail or trailing padding.

History audit: current fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt or `67_34C8B0` regional record. Consequently no historical normalized or raw similarity score is available for this owner. All open PR scopes were checked before the trial; none covered this file or owner.

Validation against master `11917f5fc063360751169e3f616d51690dc2d041`: the first typed-packet recipe passed the full US ROM build with default host syntax checks and `COMPARE=1`, followed by `md5sum -c baseroms/us/checksum.md5`. Retail MD5: `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 193 previously matched US owners remained present. Local validation does not substitute for the current-head and merge-result Public PR ROM Gate.

## Native focused batch, 2026-10-14

Solo native macOS work; no agents or Docker. Only actual game source and these
durable notes are published. Scratch generators, permuter adapters, target
objects, compiler artifacts and ROMs stay local.

### Accepted: func_8291199C

The 356-byte entry owner retains its 0x28 frame, pool tag `0x474244`, graphics
allocation, six-argument configuration, all ten resource requests, and exact
setup/teardown call order. Use a word input and pass `(s16)selection` to the
existing signed-halfword wrapper. Keep the segment mask before the shift:
`((u32)D_1000000 & 0x0F000000) >> 24`; shifting first changes instructions.
The existing final alignment nop requires no padding pragma or helper.

First normal eight-cell batch accepted the direct configuration assignment
and mask-first spelling, with `link_verified=true` and a self-gated full ROM.
Timing: 6.253 seconds probes, 1.385 seconds gate, 7.642 seconds total.

### Accepted: func_82911418

The 456-byte text/resource renderer retains its 0x28 frame. Register the four
resources in order `(0x38,5)`, `(0x38,1)`, `(0x38,7)`, `(0x33,5)`. Preserve
font setup, all three formatted text draws and the final font teardown.
Direct nested lookups and direct state members match. An explicit first-state
pointer changes the frame and instruction sequence; it is not needed.

The two display states are 24-byte records: signed coordinates at 0/2,
selection at 0xC, foreground bytes at 0x12..0x14, background at 0x15..0x17.
The three text table symbols are views of existing word fields separated by
68-byte records. Their local row type adds no allocation or linker alias.
Keep the shared state type before the earlier pragma owners so future probe
declarations can use it.

First normal eight-cell batch accepted direct nested lookups, with
`link_verified=true` and a self-gated full ROM. Timing: 5.188 seconds probes,
0.974 seconds gate, 6.164 seconds total.

### Verification and names

After declaration cleanup, native `gmake rom COMPARE=1 -j2` passes with default
host syntax checks and retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
Separate `gmake cc-check` passes all 427 C sources; existing warnings remain.
Fresh full-source and 20-leading-blank controls reproduce the complete `.text`,
both accepted owners and all six existing C siblings byte-for-byte. The entire
linked source span `0x34C8B0..0x34E600` matches the retail ROM. Normal accepted
probe-stat rows exist for both owners; statistics remained enabled.
The naming plan has no independent existing mapping for either new owner.

### Requeue: func_8290FE04 (register-tie)

Keep assembly. Direct indexed 68-byte palette rows, independent foreground/
background loads and scalar channel copies reproduce all 68 positional opcodes
and 272 bytes with the original 0x18 frame, but raw similarity is only 0.8382
(normalized 1.0). First difference remains incoming `lh $t7,26($sp)` versus
`lh $t6,26($sp)`; later temporary allocation is out of phase. Explicit row
pointers, three coordinate constants and hand-interleaved channel stores are
worse. Field-vs-raw access, real incoming-value carriers, and K&R spelling do
not repair the phase. Ordinary three-channel loops grow the sequence. Eight
additional carrier cells were initially compile-failed because the shared
display typedef followed this owner; after accepted-declaration cleanup and
a verified ROM, their real word/index/y carriers still yield no match.

Calibrated 90-second native stock permuter search from the opcode-identical
indexed parent: base score 85, best 85, no retained improvement. Base/probe
and assembly-target/current-build words were identical before search. Fake
locals, masks, zero expressions and function/prototype type mutations were
disabled. Next action: isolate a real allocator class-crossing or meaningful
live-range boundary, not replay the scalar/access/K&R/loop families.

### Requeue: func_829115E0 (register-tie)

Keep assembly. Real `gSPDisplayList` macros, direct table members and direct
state members reproduce all 156 positional opcodes, 624 bytes and the original
0x40 frame. Best normalized 1.0/raw 0.9551 differs at only seven words: the
selection web uses `$v0` rather than `$v1` at offsets 232,244,252,256,348,352,
356. Explicit row pointers also move a saved display-list stack slot; explicit
state/list pointers and named selection carriers worsen the sequence.

Calibrated 90-second native stock permuter search: base score 195, best 75,
no zero. The best retained change is token-identical physical-line grouping
inside the first expanded display-list macro; the store-order variant scores
95. Both preserve program meaning, but neither is accepted source or ROM
proof. A separate 183-score output introduces an unused mask assignment and
is not adoptable. Base/probe and assembly-target/current-build words were
identical. Next action: recompile the reviewed 75-score layout through the
normal runner, then find a natural macro-source layout carrying any measured
gain. Also measure the selection web lifetime around the conditional resource
draw, preserving real callee return categories; do not invent dummy reads or
retype a void callee solely to occupy `$v0`.

#### Normal-runner follow-up after PR #930

On the separate follow-up branch, eight cells combine the reviewed 75/95-score
retained spellings, restoration of the two conditional `gSPDisplayList` macros,
and an actual row-pointer carrier used by the first secondary draw. No cell
accepts. Expanded 75-score source preserves 624 bytes but its normal raw score
is 0.9423, with a conditional command-store ordering difference first at byte
157. Restoring the conditional macros returns exactly the earlier 1.0/0.9551
seven-word selection tie; row carriers produce 620 bytes and swap saved roles.
The permuter's scalar improvement therefore does not improve the normal
translation-unit oracle. Preserve real macros and do not promote expanded
stores or unused mask locals. Next hypothesis must target the selection web
or its authentic call/lifetime context, not more first-macro reflow alone.

## Native renderer/fade closure, 2026-10-14

PR #930 is merged and its Public PR ROM Gate succeeded. Integrate current
master `3bea111`, retaining the complete renderer research above.

### Accepted: func_829115E0 (prior register-tie resolved)

The underlying draw routine `func_8004CB7C` explicitly returns 0/1 in `$v0`.
Its existing `func_8004D150` and `func_8004D19C` wrappers preserve that status.
Their old void C declarations hid this return contract. Before installation,
an eight-cell no-auto-gate diagnostic with the word-return declaration produces
an instruction-exact, link-verified renderer. Independent resource-object
controls prove explicit status returns through both existing wrappers preserve
the entire `.text`, all selected sibling words and the full retail ROM.
See `docs/regions/4CC20.md` for the underlying ABI evidence.

After that separately verified postacceptance wrapper cleanup, the ordinary
renderer gate accepts the original direct-fields/real-GBI-macro body. All 156
words, 624 bytes and frame 0x40 match. Preserve both conditional image paths,
the four existing border draws, final graphic routines and text renderer.
No forced colors, artificial reads, helper functions or expanded macro stores.
Gate timing: 5.003s probes / 1.098s gate / 6.104s total, link_verified=true.

### Accepted: func_8290FF14

209 words / 836 bytes, original 0x20 frame. Preserve flag states 1/2 as a
two-case switch. State 1 moves all six RGB bytes toward the selected palette;
after all match, set flag 0. State 2 moves them toward the two existing static
triplets; after all match, set flag 1. Every step uses the original 50/50 rates.
Other flags are unchanged. Reload the selected index for each step because the
callee can alter globals. Retain background-before-foreground call order.

The first eight reproduce every opcode with the switch, but comparison operand
order differs between states. State 1 needs record-before-table comparisons;
state 2 needs table-before-record. Separate these hypotheses. Explicit scalar
or array aliases for the three interior target bytes produce a worse 832-byte
body and are discarded; they are not published. The closing eight include
mixed comparison polarity and genuine guard/pointer alternatives. Candidate 2
has only equivalent relocated load fields left, and candidate 3 also probes.

The hit is not link-verified because the three interior byte targets use base
array plus offsets rather than separate symbol relocations. The normal
sequential full-ROM gate is authoritative and accepts the mixed-polarity body.
Timing: 4.834s probes / 1.606s gate / 6.442s total, gate_mode=sequential.
No layout changes, extra storage, aliases, padding or helper functions.

### Remaining initializer requeue and verification

`func_8290FE04` remains assembly. Eight new word-parameter cells update the
existing accepted caller declaration in a companion transaction, varying real
short conversion, input carrier and indexed/raw row access. All yield 264 bytes
(instead of 272), normalized 0.8971/raw 0.7206, with the incoming argument-home
load/prologue shape lost. Nothing installs; the companion caller and its s16
callee declaration remain unchanged. The prior s16 272-byte parent is still
best. Do not replay word-width variants without a new mechanism.

After cleanup, full native ROM comparison passes with default syntax checks;
retail MD5 is `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 427 sources pass separate
host cc-check. Fresh full-source/build and 20-leading-blank controls reproduce
the entire fragment source `.text` and all ten accepted owners. The entire
linked source interval `0x34C8B0..0x34E600` matches retail. Accepted provenance
rows exist for both new owners; statistics stay enabled. Naming plan finds no
independent existing mappings. Only existing game source and durable notes are
published; every scratch generator, probe, compiler object and ROM stays local.

## Native border campaign, 2026-10-14

PR #933's Public PR ROM Gate succeeded and the PR merged into public master
`834ec35`. Integrate that baseline, preserving all prior accepted source and
notes. Work remains solo/native; no agents, Docker or compiler modifications.
The tracked game source remains unchanged throughout this bounded campaign:
neither owner below has an acceptance or an installed companion edit.

### Requeue: func_82910510 (geometry/frame and RGB ordering)

Target: 140 words / 560 bytes, frame 0x58. Lookup `(0x52,1)`, validate texture,
compute `(width-10)/unsigned_texture_width`, require positive scale and both
interior dimensions, install the existing display list/render mode, load the
texture, pipe sync and both colors, then draw the inset rectangle. Texture
derivative is 1024/scale, rounded by selecting +0.5 or -0.5 then adding before
integer truncation. Preserve the helper's real one-pointer argument, not m2c's
speculative three-argument guess from ambient live registers.

Eight-cell families cover natural texture/float declaration order, guard
shape, float carrier reuse, genuine interior-width/height locals, signed
coordinate formals with a transactional existing-caller declaration, inline
rounding and the separately selected bias. Initial cells have 556 bytes,
frames 0x60/0x68 instead of 0x58, normalized 0.8929/raw about 0.40. Bias plus
explicit guard geometry improves normalized 0.9085/raw 0.4648, but has 568
bytes and frame 0x70. Direct u16-to-float versus an explicit u32 cast does not
close this parent. Do not read a high normalized score as frame acceptance.

A calibrated 90-second stock native search verifies base/probe words and
assembly-target/current-build words, then descends score 2714 to 456 without
zero. Reject the best output: it contains artificial mask locals and a
written-but-unread assignment. Reject the 2593 output because it moves the
height assignment after its first guard read. The 1897 output's reuse of the
already-consumed geometry carrier as the actual inset 10 is semantically
valid; so is the 1978 output's initialized, consumed reference to the real
width parameter. No mutation is adopted solely on its score.

Project only reviewed changes into an ordinary eight-cell family. Reusing
height work for the final width and height subtractions restores all 140
positional opcodes and 560 bytes: normalized 1.0/raw 0.8357. However, the frame
shrinks to 0x40, all incoming homes move by -0x18, and the prim/env RGB load
and shift order still differs. This is the best scalar parent, not a match.
Using a real six-field working record (all fields read, no filler) keeps the
opcode shape and gives frames 0x48/0x50 depending on field layout, still below
0x58. A pointer to that record worsens the sequence. Explicit unsigned RGB
packing through the real `gDPSetColor` macro does not improve it; retain the
ordinary prim/env macros rather than expanded stores or artificial masks.

The rectangle helper's actual signature in `src/44E70.c` is eight signed
halfwords plus a word cycle. An installation-disabled eight-cell diagnostic
using that signature leaves the scalar-parent result unchanged. Existing
caller declarations remain unmodified after all rejected transactions.

Next action: start from the reviewed geometry-reuse parent or its all-live
working record. Isolate one real storage/lifetime change needed for the 0x58
frame, and separately discriminate the RGB expression/load topology. Do not
repeat the original three-float/guard/coordinate-width families, add dummy
padding, or promote the mask-containing permuter winner. The negative is
bounded to these families, not a claim that natural source is impossible.

### Requeue: func_82910740 (atlas frame and operand layout)

Target: 252 words / 1008 bytes, frame 0xA0. Lookup `(0x51,1)`, read texture
width/height before the existing null branch, derive signed width/4, and
retain the exact eight border rectangles in order: top-left/center/right,
left-center, bottom-left/center/right, right-center. Texture S advances through
the original width*32, twice-width*32 and three-width*32 regions. Preserve
all 0/1024 derivative combinations, signed-halfword rectangle/texture fields,
render commands and both RGB triplets. Do not invent a pre-read null guard.

Initial eight with an old-style rectangle declaration produce 940 bytes,
normalized 0.6349/raw up to 0.5556. Using the independently verified nine-
argument signature restores the repeated signed conversions: 1024 bytes,
normalized 0.9531/raw 0.6328, frame 0xA8/0xB8. The remaining early prologue
mismatch is decisive: s16 coordinate formals shift incoming a1/a2 into saved
registers immediately; target stores word homes and loads signed coordinates
only after the texture/render setup. Do not rotate scalar temp declarations
around that wrong input lifetime.

Eight new cells retain the actual word-coordinate interface and assign real
signed origin locals only after colors. The ordinary, unstaged forms reproduce
all 252 positional opcodes and 1008 bytes. Word-coordinate temporaries give
normalized 1.0/raw 0.9087, frame 0xC0 instead of 0xA0; short temporaries give
1.0/0.8413, frame 0xB8. Pointer declaration placement is inert on this family.
No body or caller edit is installed. Next action: preserve this late-origin,
typed-rectangle parent and isolate actual local storage/field layout and RGB
operand scheduling. Do not restore the speculative short input formals or
old-style rectangle interface that produced the measured 940-byte sequence.

### Calibration and publication

The native baseline full-ROM build passes with default syntax checks and MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Fresh source/build/20-leading-blank controls
match complete fragment `.text`, all ten accepted siblings and the full linked
retail interval `0x34C8B0..0x34E600`. The search's base/probe and target/oracle
controls pass independently. Statistics remain enabled for every ordinary
probe. `decomp-workbench` is not installed; use the calibrated repository
object diagnostics and stock native permuter, not an unrun trace claim.
Only durable notes are published for this zero-accept working block. All
generators, mutation output, objects and ROMs remain local. Coverage is not
claimed to increase from research or a normalized opcode match.

## Native dispatcher layout prerequisite, 2026-10-14

The table planner identifies the aligned 48-byte window
`0x3542C0..0x3542F0`: three distinct four-byte "%s" format objects, the six
words of `jtbl_829177CC` and its existing twelve trailing zero bytes. Stop
before `D_829177F0`, which starts the fragment relocation data. The preceding
table belongs to another source file and remains in the shared rodata head.

Pair this window with `fragment67_34C8B0.c`, keep a separate rodata-typed tail,
and run the native pinned splitter (splat 0.25.0, spimdisasm 1.35.0-dev0).
The already-accepted text renderer owns the three string addresses: retain
them as three distinct named const char array definitions, not pooled literal
arguments and not a dropped unmigrated assembly stub. Their addresses stay
`0x829177C0`, `0x829177C4`, `0x829177C8`; no new bytes or symbols are allocated.

The fresh split migrates the table into the still-assembly dispatcher and
generates the two-entry linker adjustment. Normalize only the generated local
libultra archive path prefix back to its existing relative form. No unrelated
linker edits remain. The split also emits unused matching assembly under a
directory the public Makefile scans as raw assembler input; preserve that
generated directory in local scratch, outside the build scan, rather than
changing the Makefile or retaining duplicate source objects.

Before replacing any dispatcher pragma, native full-ROM COMPARE=1 passes with
default host syntax checks and MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
Owner `.text` remains exactly `0x1D50` bytes; owned `.rodata` is exactly `0x30`
bytes. The linked map places the three strings and table at their original
retail addresses and the tail at `0x829177F0`. This is a verified layout
prerequisite, not dispatcher acceptance or increased matching-C coverage.

### Requeue: layout-ready func_82910258

The six entries map states 0..5 to the physical case order in assembly. The
signed timer is at flow offset 0, completion flag at 2 and unsigned phase at 4.
Preserve postincrement comparisons against old timer values 15 and 12, both
duplicate 0xA9 audio calls, the two independent 50/50 Y steps, flag/fade setup,
the bounded 101 timer, the event at 85, fade completion plus timer >=86, the
60-frame input wait with button bit 0x8000 at input offset 8, both final X steps
at 70/70, and the unconditional completion flag in state 4. Unknown phase
values leave state unchanged. No input-null or range guards are added.

Forty-eight normal probes, all statistics enabled, yield no acceptance. Best
uses direct record coordinates, unsigned phase and the original postincrement
tests: normalized 0.9885/raw 0.7816, correct 696-byte owner and 0x18 frame.
The first reported difference is the table's relocated LO16 field (0 versus
0xC), not proof of a semantic table error. Genuine mismatches remain at the
case-1 branch/constant scheduling and case-2 flag-check/load scheduling.
The jump-table case mapping and owned 0x30-byte section are independently known.

Bounded negatives cover direct versus existing coordinate aliases, actual
Boolean/transition carriers and scopes, compound conditions versus guards,
chained flag stores, signed phase plus a u16 dispatch cast, cached unsigned
phase, de Morgan predicate trees, multiline conditions and real comma-sequenced
assignments/calls. Signed phase adds LH/ANDI instead of the required LHU;
cached phase shifts the selector from t6 to v0; chained stores grow to 700
bytes. The unsigned transition and predicate variants do not repair the two
scheduling sites. No draft or declaration transaction is installed.

Next action: a calibrated schedule/allocator discriminator on the retained
696-byte parent, not another broad scalar/guard replay. Account for table and
interior-field relocation spelling before interpreting a permuter floor.
Keep all six table entries and all three existing strings in the calibration;
a standalone target omitting the 12-byte string prefix is not the full object's
rodata context. Authoritative acceptance still requires the full linked ROM.

### Atlas storage follow-up

Eight record/union cells separate actual top-row texture S, side texture S and
bottom texture S. The optional union overlays top S with interior height only
after top S's final read. All fields are written/read with real geometry roles;
there is no filler. None improves the parent: 1008 bytes remain but frame is
0xC8, raw 0.9087 for the ordinary record and 0.8413 for the overlap. Keep the
original late-coordinate scalar parent; this is a bounded storage negative.

A calibrated 180-second stock native search on that scalar parent verifies
base/probe and assembly-target/current-build words, then descends 528 to 358
without zero. The 358 output is token-identical physical-line grouping over
the first render setup; it is semantically valid but not normal-runner or ROM
acceptance. The 508 pipe-sync grouping is also a valid retained layout witness.
Other outputs contain mask scaffolding or an unused renderer-word assignment
and are rejected. Next follow-up must test reviewed layouts through the normal
oracle and recover a readable macro spelling, not promote mutation scores.

### Final prerequisite controls

Fresh final-source/build/20-leading-blank controls reproduce both complete
`.text` and `.rodata`, all ten accepted C siblings and the unchanged assembly
dispatcher. The string prefix is exactly three copies of `25 73 00 00`; the
owned section preserves its final 12 zero bytes. Complete linked text and
`0x3542C0..0x3542F0` rodata match retail. Final native full-ROM comparison passes
with default syntax checks and MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
Separate cc-check passes all 427 C sources. No tools, generated matching asm,
objects, proprietary compiler artifacts or ROMs are published. This prerequisite
does not claim any new function is decompiled or alter generated coverage.

### Dispatcher schedule discriminator, 2026-10-14

Requeue remains active. Forty additional normal probes (88 total for this
layout-ready owner) reject five bounded families: per-case return exits,
nested condition trees, pair/triple shared transition assignments, initialized
case-local transition carriers before the coordinate tests, and signed-compatible
phase store lvalues while retaining the unsigned selector. Statistics remain
enabled and no candidate is installed. Return and nested-condition variants
reproduce the 696-byte parent; they do not change its genuine schedule residual.

A 180-second, four-worker native stock permuter run first reproduces the
normal parent's instruction words and the assembly oracle's instruction words.
Its target includes the actual three named formats before all six table
entries and the twelve zero tail bytes: the full 48-byte rodata context, not
an omitted-prefix target or patched text oracle. Search descends from 645 to
260 but never reaches zero. The 260 output is invalid: its transition
initialization sits before the first switch case label and cannot execute,
leaving the later reads uninitialized. Reject it regardless of score.

The valid 365/370 proposals combine two real transition stores. Normal-runner
reproduction fixes the case-1 branch-likely/constant shape but introduces an
extra halfword reload when propagating an assignment value, growing the owner
to 700 bytes (normalized 0.9943, raw 0.7543). Three-field trees can grow to
704. Signed-compatible store access does not remove the reload. Legitimately
initialized precondition carriers grow to 712 bytes instead; do not adopt the
uninitialized mutation to avoid that cost. Keep the original 696-byte parent
as the whole-function baseline and retain these partial mechanism witnesses
locally rather than claiming a closer normalized score proves a match.

Fresh whole-object and twenty-leading-blank controls again reproduce both
sections, all ten accepted siblings and the assembly dispatcher. The linked
text, owned rodata and complete ROM remain retail-identical. Next action is
to isolate the actual transition-value lifetime and case-2 flag-read scheduling
under the calibrated stock frontend, not repeat the exit/condition or signedness
families above. All generators and search output remain local scratch; no new
helper, compiler artifact, ROM, or unmatched C body is published.

### Atlas RGB closure and smaller-frame parent, 2026-10-14

Requeue `func_82910740` remains assembly. Eighty additional native object
probes and a calibrated 180-second stock search produce no acceptance, but
the normal runner now isolates a frame-only residual. No hypothesis is
installed and no helper or scratch script is published.

Use the real SDK `gDPSetColor` command for both primitive and environment
color. Primitive min-level and LOD fraction were both zero, so its command
word is unchanged. Preserve RGBA bit positions while expressing the packed
word as green, then blue, then red, then alpha:

```c
_SHIFTL(color[1], 16, 8) | _SHIFTL(color[2], 8, 8) |
_SHIFTL(color[0], 24, 8) | _SHIFTL(255, 0, 8)
```

Of eight packing cells, this spelling matches every original RGB load, shift
and packing instruction. The resulting 1008-byte/252-word parent has 241 raw
words exact (0.9563), rather than 229 (0.9087). Its only eleven differences
are the prologue/epilogue frame and incoming argument-home accesses: frame
0xC0 instead of 0xA0, with every affected home displaced by the same 0x20.
These are raw normal-oracle measurements, not normalized acceptance.

A second controlled family groups only the five spilled geometry values into
a local record with signed-halfword fields `middleX`, `rightX`, `middleY`,
`innerWidth`, and `innerHeight`. Keep `bottomY` and `textureS` as separate
word carriers, the original signed origins and corner copies, and all original
rectangle-argument conversions. This reduces the frame to 0xB8 and the
uniform argument-home displacement to 0x18, without disturbing any of the
other 241 instruction words. Both logical and measured spill-slot field orders
reproduce this result. This smaller-frame record is the next parent.

Bounded negatives on the new RGB parent: removing corner aliases is inert;
reusing input/origin values reduces some frames but changes opcode/register
shape; moving geometry declarations into render-phase scopes and C89 register
storage classes is inert. Ordinary seven-field word records preserve the
0xC0 frame; halfword records rotate remaining geometry registers. Arrays
change actual spill loads/stores and can overshoot below the target frame.
Packing additional origins/corners into the five-field record leaves 0xB8;
making the two remaining word carriers halfword fields rotates registers.

Diagnostic-only sharing of the five expanded SDK command pointers can reduce
frame size but changes allocation. It is not an accepted replacement for the
SDK-macro spelling and was never installed. Keep it only as a storage-mechanism
witness. No filler, uninitialized value, changed helper arity or object rewrite
is used to force the missing bytes.

The old 358 line-grouping search witness, reproduced in the normal runner,
does not improve the old 0.9087 parent. The new RGB-parent search calibrates
base/probe and target/oracle words, then descends from 468 to 298 without zero;
its retained proposals are token-identical setup line grouping, not a smaller
frame or ROM acceptance. Do not rank their search scores above the freshly
measured normal-oracle record parent. Fresh/blank whole-object controls again
confirm both sections, all ten accepted siblings, the assembly dispatcher and
the linked retail layout.

Next action: isolate the remaining 24-byte frame reservation on the five-field
record parent, keeping the now-exact RGB tree and all other instruction words
as controls. Reopen storage/lifetime levers only with measured changes on that
parent, not another RGB permutation or replay of the inert scope/register
families. Function-level probe evidence is still insufficient for removal of
the pragma: the authoritative full-ROM gate must accept the final candidate.

### Atlas stock-phase controls and trace limitation, 2026-10-15

Requeue remains the 1008-byte five-halfword-field parent: 241/252 raw words
exact, frame 0xB8 instead of 0xA0, uniform incoming-home displacement +0x18.
Forty further scored probes do not accept a function. Moving the real record
through all declaration positions is inert, as are explicit discards of the
actual texture-loader status, redundant narrow-conversion removal, and register
storage classes on the actual expanded SDK packet pointers. Keep SDK macros
and the known helper definitions; do not invent return values or argument counts.

An unspecified-parameter declaration for the rectangle helper still passes all
nine actual arguments, but changes narrow argument conversion code and shrinks
the owner to 928 bytes while leaving the 0xB8 frame. It is a diagnostic negative,
not an adopted declaration. Retain the real eight-s16-plus-s32 prototype.

Overlaying the early texture pointer with the later geometry record is a valid
lifetime experiment: the pointer's final read precedes every geometry write.
Eight corrected cells reduce frame to 0xB0 but grow the owner to 1012 bytes and
disrupt allocation (normalized 0.9684, raw 0.4783). Keep the frame-only parent,
not the smaller but otherwise worse union. An initial generator removed the
union's pointer declaration as well as the outer declaration; its eight compile
failures are process evidence, not hypothesis evidence. The corrected generator
anchors the removal to a complete outer declaration line and asserts that the
union retains exactly one pointer member.

Stock native `-K` retention reproduces the normal probe's instruction words and
exposes a real `.frame $sp,184,$31` in the generated assembly. The preserved
optimizer input shows nominal local homes through -60; the texture pointer
appears at -40 and the five SDK packet temporaries at -44/-48/-52/-56/-60.
These are partial trace observations, not proof that those homes own the final
24-byte frame excess. Final coloring/retained-frame ownership is not available.

Tooling-blocked (detailed optimizer trace only): native IDO 7.1 debug levels
1 and 3 abort in `wrapper_ecvt`, whose runtime implementation is an assertion
stub. Preserve the partial listings and failure logs, but do not describe either
run as a successful trace or promote its failed output. Normal compilation is
unaffected and remains available; the project goal is not blocked by this alone.

The failed retained-phase run also exposes a calibration-file collision: the
driver uses `base.o` as an intermediate beside `base.c`, overwriting a same-named
calibration ELF before it aborts. The apparent repeat-control difference was
that clobbered reference, not different generated instructions. Compare against
the normal probe object outside the retained-phase directory instead. With that
immutable reference, the changed-working-directory control reproduces all 1008
bytes exactly. Do not repeat a search based on the overwritten non-ELF file.

Next action: recover detailed native trace capability in an isolated tool copy,
or use a materially different source-level discriminator for the measured frame
reservation. No trace-owned allocation claim has yet been earned. Preserve the
five-field parent and exact RGB tree while doing so; no new helper, proprietary
artifact or unmatched C body is published from this block.

### Accepted atlas renderer, 2026-10-15

`func_82910740` is now accepted matching C. This closes the earlier atlas
requeues and supersedes their proposed next parents. Do not resume a historical
atlas attempt unless a fresh active pragma and a genuine regression exist.

The decisive source change is to express the six cached rectangle geometry
values and all three texture-S phases directly at the eight real draw calls.
Let stock IDO perform common-expression reuse across calls. Retain only the
two signed-halfword origin locals, word strip width and texture height, and
the actual texture pointer. No corner aliases, geometry work record, union,
padding, register forcing, helper-arity change or compiled-object patch remains.
The exact RGB packing tree established above remains in the real SDK color
commands. Header reads still precede the original texture-null guard, and all
eight rectangle argument combinations and derivative values remain unchanged.

An eight-cell normal runner batch accepts the origins-only inline spelling:
252 words/1008 bytes, original 0xA0 frame, raw object match, link_verified true,
auto_gated true, one combined full-ROM gate. The native ROM is byte-identical
with MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`, default host syntax checks enabled.
Post-acceptance cleanup gives the loader its known s32(u8*) signature and an
explicit byte-pointer cast, and removes redundant externs. A fresh full-ROM
gate verifies that cleanup. Naming-tool plan finds no evidence-backed mapping
for this owner, so the address-keyed name is retained rather than guessed.

Calibrated native compiler controls do not justify a compiler switch: the
7.1 parent and its blank-line control reproduce 241/252 words, while stock 5.3
produces 274 words with only 17 positional words exact and the same 0xB8 frame.
Both return-zero instruction controls pass; known accepted siblings reproduce
under the normal 7.1 wrapper. These findings apply to the tested parent, not
every possible source or historical compiler point release.

The cross-ROM search uses current public GS metadata and independently verifies
the complete retail extraction of both border owners before comparison. Its
positional searches find no >=0.50 donor. Broader opcode-only hints are not name
or matching evidence. Reading Stadium 1's actual filled-panel C provides the
useful natural-expression hypothesis; no foreign source or checkout is edited
or imported as an accepted result. The native debug limitation remains real,
but it was not a prerequisite for closing this owner.

All earlier search artifacts stay local. Published changes are the matching
renderer and these durable diagnostics only; no scratch helper, proprietary
compiler artifact or ROM is included. Remaining owners in this file still
require their own full-ROM acceptance.

### Background RGB follow-up after atlas acceptance, 2026-10-15

Requeue `func_82910510` remains assembly. Transfer the accepted atlas's actual
SDK packed-color tree, not its source geometry or function name. Eight normal
packing cells improve the scalar background parent from 117/140 raw words
(0.8357) to 129/140 (0.9214). All RGB loads, shifts and packing words now match;
the eleven remaining words are exclusively the frame and argument homes:
0x40 instead of 0x58, with the affected incoming-home displacements all -0x18.
Owner length remains 560 bytes. This is not acceptance or increased C coverage.

Keep the actual loader s32(u8*) declaration and explicit pointer cast introduced
by accepted-source cleanup, the real rectangle signature, original scale guard
order and signed +/-0.5 rounding. The candidate's companion transaction retypes
only its existing forward declaration in the already accepted caller block,
and is rebuilt from the current source rather than replaying a stale block.
No transaction remains installed after the rejected batches.

Eight real final-call-carrier variants cache the rounded coefficient, output
coordinates and output dimensions, singly and together; every value is used.
They reproduce the same 0x40 frame and all 129 exact words. Do not replay that
family or add unused locals to pad the missing 24 bytes. Next action is a
different, compiler-faithful representation of the real floating/rectangle
working state, preserving the now-exact RGB tree and the accepted atlas sibling
as controls. All generators and probe outputs stay local.

### Accepted background renderer, 2026-10-15

`func_82910510` now has full-ROM-accepted matching C. This closes the preceding
background requeues; do not resume their rejected scalar or padding hypotheses
once the pragma is gone.

The winning source groups only real values into a local eight-field work record:
the texture pointer, scale, derivative, signed rounding bias, interior width,
the height-check/inset carrier, and the two output coordinates. Each field is
written and consumed. The output coordinates are computed from the original
signed inputs plus five and passed to the real rectangle helper. This is actual
working storage, not an unused field or frame-padding device.

Eight working-state cells vary the presence of the real rounded-result,
coordinate and dimension carriers. The coordinate pair, without a separate
rounded-result or final-dimension pair, gives 140/140 raw words, 560 bytes and
the original 0x58 frame. The normal runner accepts
`f67:background:real-working-state-2`, link_verified true, auto_gated true, one
combined full-ROM gate. The scalar parent and seven other cells are not adopted.

Preserve the original null/scale/width/height guard ordering, unsigned texture
width conversion, +/-0.5 float rounding and actual SDK packed-color tree. The
paired transaction corrects the existing forward declaration to the accepted
signed-coordinate interface; the already accepted caller remains byte-identical.
Post-acceptance cleanup removes duplicate externs and the now-redundant forward
declaration. A fresh default-check native full-ROM comparison passes after that
cleanup, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.

The naming-tool plan has no evidence-backed mapping for this owner, so its
address-keyed name remains. No helper function, scratch script, proprietary
compiler artifact, ROM, forced register, padding, or object rewrite is published.
Four assembly owners remain in this file and still need separate acceptance.
