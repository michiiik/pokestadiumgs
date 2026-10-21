# Fragment 79 terrain-grid source shapes

## Accepted grid point value setter

`8415AC64` / `BattleAnim_SetTerrainGridPointValue` replaces244 original bytes
through recorded native-runner acceptance and a byte-identical full-ROM gate.

The oracle writes a halfword at offset0x10 of20-byte points, with16 points per
row, for interior row/column indices1..14. The point array view begins at the
existing object's offset0x1010. Unknown point bytes stay unnamed; this is not
a claim about the allocation extent of the enclosing state object.

Use ordinary nested loops, a real current-point pointer, and the row-array
address expression. Stock IDO peels the first two inner iterations and unrolls
the remainder by four. Flat byte addressing and flat point-index arithmetic
strength-reduce differently; manually copying the oracle's unroll is unnecessary.
The accepted spelling uses signed32-bit counters. Narrow counters changed the
loop shape and did not match.

The first-success callback froze the full changed TU object, four distinct
collateral objects, source, ROM, ELF and linked script. All nine artifacts were
independently hashed before further compilation. Five complete-original-object
controls cover source cleanup, naming and blank-line stability, including all
previously accepted neighbors. Four emitted layout values verify point size20,
field offset16, row stride320 and field width2. Existing unrelated source and
declarations were preserved.

## Accepted terrain initializer and phase updater

`8415A9E4` / `BattleAnim_InitializeTerrainGrid` (640 bytes) and
`8415AD58` / `BattleAnim_UpdateTerrainGrid` (136 bytes) are recorded native
runner accepts with byte-identical full-ROM gates. Do not re-probe either
accepted owner.

The initializer clears the latch and state header, initializes a 16-by-16
array of 20-byte points starting at state+0x1010, seeds the two phases, and
optionally runs a positive signed-halfword warmup count before rebuilding the
dependent geometry. Its second parameter is `s16`: the oracle stores its
incoming argument home, sign-extends the incoming register, and retains the
narrowed count across calls. A word parameter with a narrow local does not
reproduce this shape. The declaration repair was independently controlled
against the complete original object and full-ROM-gated before probing the
typed owner. The existing third argument is retained; the original body does
not use it. Ordinary nested loops with a continuously advancing point pointer
reproduce IDO's inner-loop unrolling; no source-level unrolling is needed.

The shared point view now names only the proven float offsets 0, 4, 8 and 12,
the existing signed halfword at 16, and the remaining two unknown bytes.
No enclosing allocation extent or additional fields are inferred. Emitted
layout checks establish size20, offsets0/4/8/12/16, row stride320 and field
width2. The previously accepted interior-point setter remains object-identical.

The updater tests the real u32 status getter against1, conditionally initializes
the halfword at state+8 from state+4 plus0x463C and sets the latch, calls
8415A364, then advances two signed halfword phases by+2/-1 modulo0x4000.
The former eight post-call register differences were caused by an incorrect
void declaration of 8415A364. Primary assembly establishes its real signed
status return: the expiry edge at8415A39C has `li v0,-1` in its delay slot;
the normal path sets v0 to zero at8415A924, with no further v0 writes before
the shared epilogue at8415A9D4. `extern s32 func_8415A364(void)` therefore
repairs a real interface, rather than inventing one to reserve a register.
A signed32-bit local for the u32 status getter preserves equality against1
and recovers the original shared constant1.

Both first-success callbacks froze the complete changed TU object, four
distinct collateral objects, source, ROM, ELF and linked script. All nine
artifacts per success were independently hashed before further compilation.
Five complete-original-object controls cover known source, blank-line stability,
shared-view/declaration cleanup, naming and named-source blank-line stability.
No instruction rewrite, register forcing, padding local or byte replacement
was introduced.

## Geometry direction helpers: requeue

`841569E0` and `84156AB4` remain assembly. Sixteen initial probe failures were
a declaration-plumbing defect, not source-shape evidence: declaration synthesis
injected a stale void prototype for the tertiary position wrapper alongside
its typed companion definition. Explicit shared wrapper prototypes repair that
probe context. Eight compiling natural variants per owner then tested array
order, scalar declaration order and grouped/interleaved point snapshots.

Best raw similarities were0.566 for the first owner (204 versus212 bytes)
and0.4237 for the clamped-height owner (224 versus236 bytes). The original
contains a floating equality compare before normalization without a surviving
COP1 branch. These variants do not reproduce it and also differ in float
register lifetimes; this is not merely a register tie. Do not add a dummy
comparison or fake normalizer interface to emit the missing instruction.
Next: inspect natural zero-length/direction handling in related original
sources and establish the comparison's source/control-flow lineage before
another candidate family. The genuine normalizer takes three float pointers.

Separate whole-original-object controls also establish that both existing
position wrappers can use a real `f32 *position` parameter and explicitly
forward `(s32)position` to their actual callees without changing bytes.
Those wrapper cleanups were not installed by the rejected geometry batch.

The Stadium1 counterparts `BattleAnim_CalcVectorAtToDm` and
`BattleAnim_CalcVectorAtToDm2` were inspected read-only. Their current decomp
contains an empty zero-vector conditional and unused padding. This explains
how that source retains a comparison, but is not evidence of genuine original
source. Neither construct was copied. The geometry owners remain a requeue;
no source-lineage impossibility claim is established.

## Accepted camera bounds builder

`84159D30` / `BattleAnim_BuildTerrainCameraBounds` replaces632 original bytes
through native runner acceptance and a byte-identical full-ROM gate. Never
re-probe the accepted owner.

The original reads the camera pointer directly fromD_80094908, with eye/at/up
floats at0xA8..0xC8 and projection floats at0x2C/0x30/0x34. It normalizes the
view direction, writes a plane center20 units beyond the near distance,
computes a guarded tangent radius from the field of view, and uses two cross
products and two normalizations to build scaled plane axes. The output is
nine floats. No additional camera fields or enclosing allocation are inferred.

Natural live trig intermediates recover the original192-byte frame without
padding locals. Write the plane center before computing the trig angle;
otherwise IDO changes the instruction schedule. The eye-X carrier can be
reused for the absolute radius after writing the center. Separating the sine,
scaled sine and signed half-height preserves the original float allocation.
Every scalar is initialized before use and participates in the calculation.

The final two-word residual was exactly the angle's store/reload home,116
versus72 bytes above the stack pointer. Exchanging the declarations of the
live distance and angle locals resolved it without changing the calculations.
The successful candidate has the original632-byte body, register sequence and
relocation topology. No instruction rewrite, forced register, fake interface,
dummy conditional, unused local or arbitrary padding was introduced.

Fifteen complete-object controls calibrate passive frame observation against
stock builds, observer-off/on builds and blank-line variants for the known TU
and two retained parents. Both camera parents have frame192, saved24, temp0;
the trace locates the observed frame addresses rather than inferring hidden
spill bytes. The passive observer is diagnostic only and is not shipped.

The first-success callback froze source, the complete changed object, four
distinct collateral objects, ROM, ELF and linked script; all nine were
independently hashed before further compilation. Five complete-original-object
controls verify the accepted source, blank-line stability, readable local
names, redundant forward-declaration cleanup and semantic function naming.
Previously accepted terrain owners and all other neighbors remain identical.

## Accepted terrain height and slope sampler

`84159FA8` / `BattleAnim_SampleTerrainHeightAndSlope` replaces956 original
bytes through recorded native runner acceptance and a byte-identical full-ROM
gate. Never re-probe this accepted owner.

The primary assembly converts world coordinates to signed cell indices with
`((x+440)/150)+8` and `(z/200)+8`, truncates toward zero and clamps each index
to0..14. It snapshots the four cell corners from the existing16-by-16 grid of
20-byte points, selects a triangle using the original squared-distance test,
and uses its cross-product normal to solve the plane height. A zero normal-Y
falls back to the three-vertex mean. It writes the normal's atan2-derived
slope in degrees, folded into[-90,90], and returns the sampled height.

The real `MathUtil_Atan2s(f32,f32)` return type is signed16, as verified in
the accepted definition in `BF50.c`; do not replace it with a guessed word or
float interface. The original sampler's arithmetic is single precision,
including the mean and angle scaling. Stadium1's padded source is not the
matching oracle and was not transplanted.

The first natural cell/plane forms already reproduced all956 instruction
bytes modulo stack addresses, with identical relocation topology. Explicit
live cell coordinates, squared corner distances, relative coordinates and
weighted normal terms recover the original224-byte frame. The accepted form
also names the two edge vectors passed to the real cross-product helper.
Every scalar is initialized before use and participates in the calculation;
there are no padding locals, dummy operations, forced registers, fake
interfaces or instruction/HEX/relocation rewrites.

Use the existing shared point view and row-array indexing. The sampler and
initializer now share one declaration of that view, moved before the sampler.
Only the already established fields and two unknown tail bytes are named.
Eight emitted layout values verify size20, offsets0/4/8/12/16, row stride320
and halfword width2. No enclosing state allocation extent is inferred.

The first-success callback froze source, the complete changed TU object,
four distinct collateral objects, ROM, ELF and linked script; all nine were
independently hashed before further compilation. Five complete-original-object
controls cover accepted source, blank-line stability, shared-type/extern
cleanup, readable guards, semantic naming and named-source blank-line
stability. All previously accepted camera/terrain owners and other neighbors
remain object-identical.

## Accepted radial emitters and trail updates

Four owners replace1552 original bytes through recorded native runner accepts
and full-ROM gates:84156CCC/8415782C are the396-byte effect19/effect98 radial
variant-D emitters;84157ADC/84157CDC are the380-byte effect11/effect57 trail
updates. Their semantic names retain old address-name linker aliases. Never
re-probe these accepted owners.

The real secondary-owner scale getter returns f32, as established by the
accepted84109544 definition. Its wrapper now explicitly returns that value.
The anchor-position wrapper now accepts a real float-position pointer and
forwards its32-bit address to the actual84109780 callee. Both repairs preserve
the wrappers' complete original object bytes; they do not invent interfaces
to obtain a register allocation.

The paired trail updates increment signed-halfword counters, emit on even
frames, calculate three randomized offsets scaled by the actual owner scale,
and choose horizontal velocity toward the origin. Return the genuine
TrailEffectPool_IsComplete result. The Stadium1 source's hard-coded zero is
not the GS behavior. A three-float local position record, live jitter terms
and declaration placement reproduce the original112-byte frame without the
donor's unused padding. Preserve the double-precision zero comparison on x.

The radial emitters use the real six-output direction helper and18-argument
variant-D backend, whose signed-halfword and byte arguments are established
by the original callee loads. Preserve both random draws, signed remainder
operations, float arithmetic grouping, colors and literal arg6=2 from GS
assembly. Retaining the second draw in a live local recovers the original
first draw's stack home, without an unused padding word. The two bodies have
the same code shape but different independently checked colors and constants.

Place a multi-owner batch in source order: the combined installer emits shared
declarations only with its first winner. An initially out-of-source-order
batch produced isolated exact hits but failed the combined compile because
an earlier caller preceded those declarations. The source-ordered retry used
the same matched bodies and passed the gate; it was a declaration-plumbing
repair, not a new source hypothesis or an ungated installation.

Both first-success transactions froze the whole changed TU, four distinct
collateral objects, source, ROM, ELF and linked script. All nine artifacts per
success were independently hashed before further compilation. Five complete
original-object controls cover source/blank-line stability, declaration cleanup,
readable guards, naming and named-source blank-line stability. Previous
camera, sampler and terrain owners remain identical. No byte rewrite, forced
register, dummy conditional, arbitrary padding or unused local was introduced.

## Four-stream effect45 update: requeue

841580C8 remains assembly after eight natural variants. Its original576-byte
body includes mixed float/double phase construction and conversion around
the sin/cos calls; the closest float-call form is560 bytes, while standard
double-math forms are572 bytes. Neither is accepted. Scalar/phase/result
declaration variants alone do not settle the call-lowering difference.
Next: inspect authentic compiler intrinsic lowering and the original mixed
precision expression lineage, rather than add identity casts or padding.

## Ribbon and owner-linked emitters: accepted

Three native runner accepts, 1084 bytes, each through the normal full-ROM
gate (retail MD5 1561c75d11cedf356a8ddb1a4a5f9d5d):

- 84157128, 376 bytes: BattleAnim_StartEffect7TexturedRibbonSheet_Emit.
- 8415839C, 388 bytes: BattleAnim_StartEffect62OwnerLinkedFourStream_Update.
- 84158588, 320 bytes: BattleAnim_StartEffect67OwnerAnchoredFourStream_Init.

84157128 uses the secondary geometry helper, scales velocity by20, then
applies three independent signed RNG jitters. A reused live s32 random
carrier plus three live f32 jitter terms, declared before the six geometry
outputs and scale, reproduces the104-byte frame and scale home0x40. The
random carrier is declared after scale. Without it, the best376-byte body
had six differing words: frame96 and scale home0x5C. No unused locals or
padding were added. Array/record jitter variants did not improve that basin.

8415839C increments the signed counter, emits on each fourth frame while
its arithmetic right-shifted count is less than4, computes its three-way
angle, and scales vx by7*cosf(angle), vy by10*sinf(angle), vz to zero. A live
completion-result local declared before the geometry outputs and angle
gives the original104-byte frame. Return the actual completion result when
counter>=2, otherwise zero. The right-shift is signed, not division by4.

84158588 resets matrix/state, initializes its backend, obtains six geometry
outputs, and multiplies each velocity by double5.0 before narrowing to f32.
It passes a genuine12-byte xyz record by value to func_84109B88 with kind1.
That real particle-stub ABI is already evidenced by its C definition and
other accepted backends; the ignored return is a particle pointer, not a
fabricated void or integer interface. Declare the record before outputs.
Float5.0f loses the original double conversions and does not match.

All first-success evidence captured the complete changed translation unit,
four distinct collateral objects, source and linked outputs, externally
hashed before another compile. Five complete-original-object controls cover
baseline/blank stability, minimal declarations/readable source with12/4/8
position size/offset assertions, names, and named-source blank stability.
Existing radial, trail, terrain and camera neighbors remain unchanged.

## Radial effect33 emitter: requeue

84157398 remains assembly after24 natural variants in this session. Best
body448 bytes matches all instruction shapes and relocation topology, but
has nine raw differing words: a coherent f0/f2 exchange between vy and the
shared D_8418C548 spread constant. Its colors are255/255/255/100/100/150/150,
backend kind2, signed RNG moduli5/5, and final scale3.0f*ownerScale. Backend
8415C884 has s16 kind/lifetime, seven u8 colors, and real f32 values;
its primary assembly stack loads confirm these widths.

Closed families: two RNG placements and four live-local orders; four
velocity expression orders with/without a shared spread carrier; four
explicit jitter/velocity carrier forms with two declaration positions.
Explicit extra carriers changed frame or schedule and did not close the
exchange. Next hypothesis is an allocator-web trace for vy versus the
common spread constant, not another declaration permutation or dummy use.
