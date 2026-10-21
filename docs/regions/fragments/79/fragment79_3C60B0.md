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
