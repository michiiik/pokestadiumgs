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
