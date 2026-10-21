# Fragment 79: per-node phase grid

## Accepted source batch

The first batch replaced four US assembly owners: `PhaseGrid16_RecomputeNormal`
(1580 bytes), `PhaseGrid16_FillVertex` (184), `PhaseGrid16_Update` (532),
and `PhaseGrid16_BuildViewMatrix` (300). The batch covers 2596 bytes and retains
original-address aliases for external callers.

The completion batch replaces `PhaseGrid16_AddRipple` (336 bytes),
`PhaseGrid16_Initialize` (596), and `PhaseGrid16_Draw` (1224-byte original
span). These three owners cover 2156 bytes; all seven owners in this source
are now C. The renderer has a 1212-byte body followed by the original 12
zero alignment bytes, so the complete translation unit remains 4752 bytes.

Each 32-byte node stores xyz, a normal vector, texture coordinates, and a
float phase at offset 28. The 16-by-16 node grid starts at offset 20 of an
8212-byte state reached through `D_841876E0`.

The normal builder reuses a real node pointer for neighboring xyz triplets,
with scalar center coordinates and a signed 16-bit contribution count. Vertex
conversion uses three float normal carriers before scaling by double 120.
The camera builder translates eye and target along their normalized direction
by `105 / (fovy / 30)`.

The updater assigns each node's height as `sin(phase) * 0.5 + 1.0`, then
increments its phase by double 0.1. Its GS fade latch is `D_841A4D80`: status 1
starts a one-shot 25-frame fade, alpha falls by 12 starting at age 16, and
amplitude grows by 0.05 while below 0.5. The unsigned status getter keeps its
actual declaration; a signed status local preserves the observed comparison.

## Layout and verification

The readonly pool at ROM `0x3FBFF0..0x3FC010` is assigned to this source:
double 1.5707963705062866, float 0.01 with its original alignment zeros,
double 0.05, and double 0.1. The shared readonly tail begins at `0x3FC010`.
Independent normal and blank-line staged links preserved all 4752 text bytes
and 32 readonly bytes before a layout-only full-ROM gate with all seven
original assembly owners retained.

The native runner accepted all four C owners through full-ROM comparisons
with the host syntax check enabled. Every successful gate froze the source,
whole TU, four distinct collateral objects, and ROM/ELF/linker outputs before
another compile, with externally checked hashes. Retail US ROM MD5:
`1561c75d11cedf356a8ddb1a4a5f9d5d`.

Six whole-object controls cover known, blank-line, readable, named,
named-blank, and target-layout builds. The completed translation unit preserves
every original section byte and normalized relocation target. The only
function-size metadata exception is the renderer's original 1224-byte span
versus its 1212-byte C body: text offsets 4740 through 4751 are the same 12
zeros rounding the section up to a 16-byte boundary. No padding code is added.
The other six function extents are unchanged. Fourteen target-compiler
assertions cover structure sizes and field offsets.

## Completion mechanisms

`PhaseGrid16_AddRipple` adds a quarter-turn phase at the origin and a phase
increment inversely proportional to distance elsewhere. Both distance
components are meaningful float locals, assigned in the inner loop with
column first. Keeping the row carrier in the outer scope preserves the
target's allocation and floating comparison order. The integer-carrier parent
had two differing comparison words at offsets 108 and 224. A passive native
backend observer passed stock/off/on/blank controls on both a matched sibling
and that parent; it exposed the comparison's child ordering. Testing float
distance carriers on this improved lifetime structure produced the accepted
336-byte function. The compiler performs the observed two-way loop unroll.

`PhaseGrid16_Initialize` resets the fade latch and header before obtaining
the node pointer. It lays out x at `row * 6.75 - 54` and z at
`column * 5.25 - 42`, clears phases, and initializes sinusoidal heights.
It seeds the center at (8, 8), then ten random origins using the SDK's
actual signed `guRandom() % 16`, and refreshes heights from the new phases.
The two signed 16-bit random-origin locals have function scope.

`PhaseGrid16_Draw` converts all 256 nodes to vertices, builds the view matrix,
loads texture `D_8418CAB0` and render state `D_84187710`, and emits alternating
diagonals for the 225 cells using ordinary nested loops and SDK macros.

The completion batch passed native runner full-ROM gates with host syntax
checking enabled. Its frozen source/TU/four-collateral/ROM/ELF/linker receipts
were independently hashed before subsequent compilation. The final named
build is checked separately against the all-assembly baseline. No instruction
rewrite, forced register, fake comma expression, dead local, manual unroll,
or padding helper is used. No assembly owners remain in this source.

Search calibration must preserve the SDK's `__sgi`-guarded
`#pragma intrinsic(sqrtf)` during host preprocessing. Without it, the stripped
search input calls `sqrtf` instead of emitting `sqrt.s` and is not the actual
native parent. Both stripped-parent and parser roundtrip comparisons, plus a
known matched sibling through the same wrapper, passed after preserving this
intrinsic. Search scores alone are not acceptance evidence.
