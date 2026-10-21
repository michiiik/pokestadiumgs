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

## Wave allocators: requeue

`8415C884` and `8415CC74` remain assembly. Natural vector/loop forms initially
produced 1032/1044 bytes versus the original 1008/1024. Caching the readonly
cycle angle once outside the node loop removes repeated loads across math
calls. Separating random phase seeds from their advancing counters and moving
the node index increment before the fractional position offset reproduces
both original instruction counts. The best cached forms still use a 224-byte
frame versus 216, with 33 raw differing words including stack homes and cycle
load scheduling. A match is not established.

The cycle constants at `D_8418C670` and `D_8418C678` both encode the double
6.28318548202514648. Readonly extern qualification alone did not produce the
original hoisting. Next: independently preflight a per-file literal-pool
layout with remaining owners still assembly, then test the authentic literal
expression instead of an addressable cycle local. Preserve existing accepted
neighbors and use full-ROM acceptance; do not fill the frame with dummy data.

## Strip renderer: requeue

`8415C2E0` remains assembly. A nested two-vertex loop produced 504 bytes versus
592 and did not reproduce the original pair shape. An exploratory explicitly
written pair was closer, but is not adopted as a manually unrolled solution.
Color expression ordering also differs in the SDK macro expansion. Next:
establish the original pair representation and macro expression tree before
further probes; no renderer candidate is installed.
