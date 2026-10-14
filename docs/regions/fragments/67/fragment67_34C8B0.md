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
