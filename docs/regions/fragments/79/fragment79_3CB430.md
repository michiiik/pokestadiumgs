# Fragment 79 strip and radial allocation

## Accepted strip initializer and straight radial allocator

`8415BBA0` / `Strip400_Initialize` replaces 312 original bytes. It resets the
strip header, stores the supplied position and two RGB colors, and seeds all
400 sixteen-byte nodes with that position and the initial extent. The six
color arguments are bytes: the original loads their low stack bytes rather
than words. An advancing node pointer and an ordinary counted loop reproduce
the compiler's four-way unrolling.

`8415C644` / `Radial20_StartStraight` replaces 576 original bytes. It selects
the first inactive slot among ten 1512-byte states, initializes its header and
three counters, and creates twenty 72-byte nodes. Each node receives copies of
the supplied position and velocity. The first node is opaque; subsequent
alphas use `alpha * (19 - index) / 20`. This allocator adds no wave offsets,
unlike the neighboring `8415C884` and `8415CC74` assembly owners.

The position and velocity are real three-float structs. Declaring them after
the pointers and loop counters recovers their original stack homes. Advancing
the node pointer in the loop body recovers its instruction ordering. Keeping
the three-counter clear loop on one line reproduces the original store and
increment schedule. These are ordinary loops and copies, with no source-level
unrolling, padding locals, register forcing or instruction replacement.

Both owners passed recorded native-runner acceptance and the full-ROM gate.
Each successful gate immediately froze source, the full changed object, four
distinct collateral objects, ROM, ELF and linked script; all nine hashes were
independently checked before further compilation. Five final whole-object
controls cover known source, blank lines, typed strip color/pointer fields,
naming and named-source blank lines. Twenty-two compiler-checked layout facts
cover node/state sizes and the accessed offsets. They preserve all original
game sections, function extents and semantic relocation targets.

## Accepted velocity-wave allocators and per-file readonly pool

`8415C884` / `Radial20_StartYVelocityWave` replaces 1008 original bytes;
`8415CC74` / `Radial20_StartZVelocityWave` replaces 1024. Both allocate the
first free twenty-node state, copy position/velocity vectors and seed two
independent integer phases and periods with four random draws. The first
adds a two-sine product to Y velocity and a smaller sine to Z velocity; the
second applies the larger product to Z and the smaller sine to Y. Both use
the fractional part of half the current node index to offset X position.

The current index is important: the original transfers its old value to a
floating register before incrementing it. Earlier next-index candidates had
three instruction-order differences and used a different fractional offset.
They were rejected. The accepted code increments the index in the loop footer.
Keeping the second phase initialization in the loop initializer and advancing
the phase counters before the node pointer recovers the remaining lifetimes.

The literal double 6.2831854820251465 has exactly the original cycle bits.
It eliminates the addressable cycle local and reproduces the original
216-byte frames. A staged extraction established the per-file readonly window
at ROM 0x3FBEB0..0x3FBFD0 (288 bytes), including the remaining assembly owners'
constants and jump tables. The preceding 48 shared bytes remain external.
Normal and blank-line staged objects independently link to all 13616 retail
text bytes and all 288 readonly bytes with all seven owners still assembly.
The layout-only full-ROM gate passes before either wave owner is installed.

The existing rotation helper's 360-degree and cycle constants now use ordinary
double literals. Its original instructions and pool positions are verified;
unrelated historical locals are preserved. The generated linker change only
places the 48-byte shared head before this object's readonly section and uses
the new shared tail afterward.

Recorded native-runner gates verify each wave allocator separately and both
together. Each successful gate immediately freezes source, the complete changed
object, four distinct collateral objects, ROM, ELF and linked script, with
independent hashes before further compilation. Five final whole-original-object
controls cover known source, blank lines, declaration/readability cleanup,
naming and named-source blank lines. No instruction rewrite, forced register,
dummy local, arbitrary padding or manual unrolling is introduced.

## Accepted position-wave allocator and strip updater

`8415D074` / `Radial20_StartPositionWaves` replaces 956 original bytes. It
allocates the first inactive twenty-node state, copies the supplied vectors,
and offsets Y position with a product of two sines and Z position with a
product of two cosines. Four random draws supply two seeds and two periods.
The source expresses each phase as seed plus current node index; the compiler
performs the phase induction and angle reuse. This recovers the original
216-byte frame without explicit angle or advancing-phase locals. The
fractional X offset uses the current index, and alpha is stored in each node
rather than the state header. The analogous Stadium 1 `Radial20_VariantE`
provided a source-shape witness; the GS assembly and ROM gate establish the
actual target behavior and match.

`8415BD48` / `Strip400_Update` replaces 1432 bytes. It advances the strip's
age, growth and ending phases, chooses an anchor, and updates two distinct
vertices per section. The second vertex has an additional vertical sine
offset; this is paired geometry, not source-level loop unrolling. A signed
16-bit age snapshot reproduces the original sign extension. The anchor flag
selects `func_8410971C` or `func_84109B1C` in
`src/fragments/79/fragment79_377F80.c`; both use `D_84190194` with different
selector/transform behavior. The flag does not identify a third owner.

Both owners passed recorded native-runner acceptance and the full-ROM gate.
Each successful gate immediately froze source, the complete changed object,
four distinct collateral objects, ROM, ELF and linked script, with external
hash verification before further compilation. Five whole-original-object
controls cover known source, blank lines, readable locals/declaration cleanup,
naming and named-source blank lines. All original game sections, function
extents, semantic relocation targets and the 288-byte readonly pool remain
equal. No instruction rewrite, forced register, dummy local, arbitrary
padding or manual unrolling is introduced.

## Accepted radial node updater and anchor output interface

`8415D4C4` / `Radial20_UpdateNodes` replaces 1568 original bytes. Explicit
cases 0 through 5 reproduce the six-entry jump table: modes 0, 4 and 5 perform
full node motion; mode 2 applies gravity and clamps velocity; modes 1 and 3
share the default anchor behavior. The twenty nodes retain their delay,
position, velocity, angle and scale operations in ordinary counted loops.
The existing state updater now calls this function through the same typed
state view used by the accepted allocators.

The remaining 18-word near-match was an anchor-address/loop-limit register
exchange. Two passive compiler observers were calibrated with twenty
whole-object controls. The color-cost trace showed `a0` was excluded for the
anchor address, not merely more expensive. Moving pointer initialization
around the call did not remove the exclusion, and a restricted 90-second
local permutation search found no improvement. These are bounded negative
results, not an exhaustion claim.

The decisive source correction is `func_84109780`'s output parameter. It
passes the supplied address to `GeoRender_FindAnchorPosition`, falls back to
`func_8411DCCC` (which writes three floats), then calls `func_84109630` (whose
assembly adds offsets to those three floats). Its `void *position` parameter
expresses this output-buffer role without imposing one caller's local vector
type. The helper definition and all three existing C callers now agree on
that pointer interface. The helper's casts retain the legacy integer-address
interfaces of its downstream declarations; callers pass their vector address
directly. Evidence is in `src/fragments/79/fragment79_377F80.c`,
`src/fragments/79/fragment79_38D510.c`, and the original `84109630` assembly.
Sixteen known/blank/typed/typed-blank controls prove the helper and three
existing caller objects remain unchanged in every game section, function
extent and semantic relocation. A full-ROM gate verifies this four-file
cleanup before the new updater is installed.

The pointer-typed updater then passed recorded runner acceptance and the
full-ROM gate. Its successful gate immediately froze all five changed sources
and their complete objects, four distinct collateral objects, ROM, ELF and
linked script: seventeen artifacts, externally hash-checked before further
compilation. Five final whole-original-object controls cover known source,
blank lines, declaration cleanup, naming and named-source blank lines.
All 13616 original text bytes and the 288-byte readonly pool are preserved.
No dummy use, forced register, arbitrary padding, instruction rewrite, fake
ABI or manual unrolling is introduced.

## Accepted strip renderer and RGB records

`8415C2E0` / `Strip400_Draw` replaces 592 original bytes. With fewer than two
active sections it returns the display-list cursor unchanged. Otherwise it
allocates two vertices per section, converts node positions to vertex
coordinates while clamping negative height to zero, and sets the two texture
edges to T coordinates 0 and 512. It emits the existing display list, primitive
and environment colors, then a vertex load and two triangles per adjacent
section pair.

The explicit two-edge representation is witnessed by Stadium 1's
`Strip400_Draw`, and the GS updater writes the two corresponding geometrically
distinct nodes. The first and second edges have different T coordinates; they
are not duplicated identical loop iterations introduced to force an unroll.
The section and triangle loops remain ordinary counted loops.

The three color bytes at offsets 48 and 51 are named RGB records rather than
array-index expressions. This retains the initializer's original stores and
layout while restoring the renderer's original SDK-macro color expression
order. Expanding and regrouping the color packing manually did not match;
the accepted source uses the unchanged SDK color macros. Advancing the vertex
pointer at the end of the triangle-loop body, rather than in its footer,
recovers the final two instruction-order differences.

Recorded native-runner acceptance and the full-ROM gate verify the renderer
and paired RGB/initializer cleanup together. The successful gate immediately
froze source, the complete object, four distinct collateral objects, ROM, ELF
and linked script, with external hashes checked before further compilation.
Six whole-original-object controls cover known source, blank lines,
declaration cleanup, naming, named-source blank lines and layout assertions.
Six compiler-checked facts verify the three-byte RGB size, complete state size
and vertex/color/environment/node offsets. All original text, the 288-byte
readonly pool, function extents and semantic relocations remain equal.
No instruction rewrite, forced register, dummy local, arbitrary padding or
manual loop unrolling is introduced. The radial renderer is documented below.

## Accepted radial renderer; file complete

`8415DBBC` / `Radial20_Draw` replaces the final assembly owner in this file.
It visits ten states, generates twenty cross-sections for each active state,
emits the front and back geometry passes, and draws the associated auxiliary
effect. GS modes 0/2 use two textured edge vertices; modes 1/3 use three
colored vertices; mode 4 uses six vertices around each ring; mode 5 uses three
triangular lobes, interpolated colors and occasional auxiliary particles.
The six-entry tables, existing display lists, RGB arrays and radial scale
array establish these mode-dependent paths.

Stadium 1's `func_84362084` provides a structural source witness. Its nine
modes are not copied verbatim: GS removes the fifteen-vertex path and maps
the remaining modes into six values. Explicit mode labels for the default
front-face path reproduce the original dispatch and allocator behavior.
The accepted source uses a real three-float output vector and ordinary loops;
moving the state pointer into the outer loop footer or switching the output
to an array changed allocation and was not adopted. Existing helper signatures
are used consistently, including the rotation and auxiliary-effect calls.

The renderer state view has named color records, a vertex-buffer pointer at
offset 28, and twenty 72-byte nodes at offset 72. Nine compiler-checked facts
verify the color/state/node sizes and every accessed header layout group.
No new data definitions are introduced; the original display lists and color
and scale tables remain external.

Recorded native-runner acceptance uses the sequential full-ROM gate for the
relocation-masked probe. The successful gate immediately freezes source, the
complete changed object, four distinct collateral objects, ROM, ELF and linked
script, with external hashes checked before further compilation. Six final
whole-original-object controls cover known source, blank lines, readable
locals/declarations, naming, named-source blank lines and layout assertions.
All 13616 text bytes, 288 readonly bytes, section shapes and semantic relocation
targets match the original object. Every other function extent is unchanged.

The original assembly owner's 5396-byte span includes twelve terminal zero
bytes after its return delay slot. The compiled C body is 5384 bytes; natural
16-byte section alignment supplies the same twelve zeros. Only the function's
`st_size` excludes that alignment tail. This metadata difference is explicitly
audited: body start, section end, all tail bytes, all other function extents
and all relocation records are checked. No padding pragma or helper, dummy
local, forced register, instruction rewrite or manual unrolling is added.

There are now no `GLOBAL_ASM` owners in `fragment79_3CB430.c`; its complete C
translation unit passes full-ROM comparison. This is file-level completion,
not completion of the repository-wide decompilation.
