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

## Orbit allocator: requeue

`8415D074` remains assembly. Natural two-angle sine/cosine variants reproduce
its 956-byte instruction count but retain a 232-byte frame versus 216 and
31 raw differing words. Removing redundant phase seeds and reusing the slot
index reduce the frame, but also alter allocation and instruction counts;
the fully reused form has the right frame and 952 bytes, not a match.
Next: inspect the stock compiler's real local reservations and phase lifetimes
against the retained 956-byte parent before changing source topology again.
Do not add padding or remove a live value to close the frame difference.

## Strip renderer: requeue

`8415C2E0` remains assembly. A nested two-vertex loop produced 504 bytes versus
592 and did not reproduce the original pair shape. An exploratory explicitly
written pair was closer, but is not adopted as a manually unrolled solution.
Color expression ordering also differs in the SDK macro expansion. Next:
establish the original pair representation and macro expression tree before
further probes; no renderer candidate is installed.
