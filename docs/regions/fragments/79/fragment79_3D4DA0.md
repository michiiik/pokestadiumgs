# Anchored streams and trail-effect pool

## Accepted batch, 2026-10-20

Following the source published in PR #1327, four original owners pass the
native runner and normal full-ROM comparison:

| Original owner | Name | Bytes |
|---|---|---:|
| `func_84165510` | `OwnerAnchoredFourStream_Init` | 352 |
| `func_84165670` | `OwnerAnchoredFourStream_Start` | 672 |
| `func_841659A0` | `OwnerAnchoredFourStream_UpdateNodeChain` | 652 |
| `func_84166130` | `TrailEffectPool_Init` | 320 |

The anchored family uses four 1052-byte records, each with fifteen 68-byte
samples at offset 28 and a particle handle at offset 24. Initialization
resets the headers and current sample state. Start chooses a free stream,
configures its color/lifetime, sets the species-dependent marker scale and
creates the attached particle. Node update advances the leading sample,
updates its particle position, and propagates previous-frame state through
the remaining samples. It uses the independently verified by-value position
and byte-selector particle API already established in PR #1327.

GS assembly and the retail ROM remain authoritative. Stadium 1's
`src/fragments/battle_engine/battle_engine_3540B0.c` and
`battle_engine_354CD0.c` provide algorithm witnesses, not interchangeable
layouts. The second family has **26**, not fifty, 864-byte records in GS.
Its ten 80-byte nodes start at offset 64. A live scalar at node offset 12
places position at 16 and velocity at 28, four bytes later than the donor
header claims. GS start/update assembly independently confirms those fields.
Other fields remain explicitly unknown. The initializer resets two global
halfwords and record offsets 0, 4 and 6; it deliberately does not reset 2.

All new functions use ordinary C loops and real record fields. There are no
instruction/HEX rewrites, forced registers, fake calls, unused stack locals,
manual unrolling or padding additions. The first initializer's initial
object hit could not install with declarations after its definition; moving
the shared declarations above the first owner is independently neutral.
The corrected pool layout then resolves its initial offset mismatch.

## Constant ownership and verification

The complete module owns ROM `0x3FC130..0x3FC1B0`, a 128-byte constant pool.
Scoped original/migrated extraction, fresh/blank controls and independent
retail-address links verify all twenty original function extents and all
12336 text bytes before adoption. The three accepted matrix helpers use
ordinary literals in the original slots; the remaining shared rodata starts
at `0x3FC1B0`. A still-assembly normal full-ROM layout baseline passes before
candidate work.

Each successful comparison callback freezes the entire changed object plus
at least four collateral objects before returning, rereads its receipt and
externally checks every SHA256. Counts and external hashes are checked again
before further compilation. The first batch has three successful comparison
receipts, including rollback/control state; only start and node update are
accepted from it. The second batch accepts both initializers in one combined
gate. Accepted owners are never candidate-probed again.

| Retained complete module | SHA256 |
|---|---|
| Sequential node gate | `4aa2e3210e64acbc2e1b9f3893b3e2d23a718cf5647a0fa3b542987f1d5842ba` |
| Sequential start gate | `7d610c370311e16a394c748e87331491d6ba6ef13a68ca73feeb00e46dbb74af` |
| Accepted initializer pair | `3e227e567ec7e999bff4612261e65fb3232f69391d91162eb8b906c3ecc5bb16` |
| Final named module | `532e122d7dad0ebeba249a36a3aa6b06dee58f5a789f4387482d11a5398bf894` |

The initializer pair is directly link-verified. Start/node update require
the normal sequential ROM gate for relocation-controlled object differences;
a masked probe alone is not acceptance. Unmodified-linker checks of the
original, layout, every callback-frozen stage and final named object prove
all twenty original extents, all 12336 text bytes and all 128 pool bytes equal
retail. Ten remaining assembly owners stay present throughout this proof.

Canonical/named, twenty-leading-blank, native/public-wrapper and target-layout
controls reproduce the entire final module fingerprint and linked retail
bytes. All twelve collateral translation units retain their complete game
fingerprints. Accepted runner provenance covers exactly the four removed
owners. Symbol aliases preserve existing callers at the original addresses.

The final normal full-ROM comparison passes with MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. All 427 source syntax checks and all
76 native tooling tests pass. Private experiment utilities and generated
coverage are not included in the batch.

## Pool and double-texture batch, 2026-10-20

Following PR #1328 (native source base `a2569c37`), four more owners pass the
normal runner and full-ROM gate:

| Original owner | Name | Bytes |
|---|---|---:|
| `func_84166270` | `TrailEffectPool_Start` | 732 |
| `func_8416691C` | `TrailEffectPool_IsComplete` | 328 |
| `func_84166F60` | `DoubleTextureTrail_InitPool` | 328 |
| `func_841670A8` | `DoubleTextureTrail_Spawn` | 912 |

Pool start refuses new work in shutdown phase 2, selects one of the 26 free
records, and initializes its ten samples. GS assigns the three header floats
differently from Stadium 1; the matching source reflects those actual stores.
Pool completion advances its global timer, schedules a 70-tick deadline,
stops spawning once the timer exceeds deadline minus 50 and returns -1 after
the deadline. It otherwise
advances active records through the original assembly node updater.

The pool node has acceleration at 40, previous scale at 52, previous position
at 56 and previous velocity at 68, as read from GS start/update instructions.
These replace the earlier opaque forty-byte data extent without changing any
already accepted function. The double-texture family uses four 576-byte
records, ten 40-byte nodes at offset 176, and a real halfword at offset 6
cleared by spawn. Shared types move before their new consumers; target-layout
assertions and fresh/blank controls prove the complete prior object unchanged.
The existing texture loader retains its complete code and data footprint.

The completion getter `func_841094EC` actually returns `u32`; its prototype
is preserved. `func_841086F0`, `func_8410874C` and `func_8410878C` in
`fragment79_377F80.c` initialize its backing flag to 0 or 1. A normal signed
local consumes that state before the phase comparisons. Compared with a
direct unsigned-return comparison, this closes one redundant constant load
and preserves the original 328-byte body. The flag's broader interpretation
remains unknown; it is not named as an owner-completion event.

There are no fake calls/prototypes, discarded values, forced registers,
unused stack locals, padding or manual unrolling in the four new matches.
The source/store and pointer-lifetime experiments are bounded to the measured
residuals. A failed declaration-visibility attempt is compiler/process
evidence, not an accepted source or a claim of an impossible compiler shape.

| Retained complete module | SHA256 |
|---|---|
| Accepted double-texture pair | `587a3c0df9d4445ad3920fd6fd63765d5c61528f1cb28a22c0e06c57fcace1ef` |
| Accepted pool start | `82281c46b0b6c30e987db61c33a9029ed43ef69b9a9fbe3d8a6c4aa4d3b13ae2` |
| Accepted pool completion | `72503682fb7fe3a5bcb674e69186b71fbdb8d5eb03c61f21b5133f6eae4e932c` |
| Final reviewed module | `4601041b4b8c8fa1ca37cddb2617fc82ad05dcdbf785bd2eca28c76080638369` |

Each of the three acceptance callbacks freezes the complete changed module
and four collateral objects, with immediate receipt rereads/external hashes
before returning and again before more compilation. Final naming/declaration
cleanup passes a normal ROM gate with thirteen frozen complete modules.
All twelve collateral game fingerprints remain unchanged. Init/spawn and
completion are directly link-verified; pool start requires the normal
sequential ROM gate for relocation-controlled probe words.

Independent unmodified-linker proofs cover all twenty original function
extents, all 12336 text bytes and all 128 pool bytes for the prior accepted,
prepared, three new acceptance and final named objects. Canonical/named,
twenty-leading-blank, native/public-wrapper and target-layout controls
reproduce the final complete game fingerprint and retail bytes. Accepted
provenance covers the four newly removed owners. The final normal full-ROM
MD5 remains `1561c75d11cedf356a8ddb1a4a5f9d5d`.
All 427 source syntax checks and 76 native tool tests pass for this batch.

## Double-texture update and strip draw, 2026-10-20

Following PR #1329 (native source base `92f90054`), two more original owners
pass the normal runner and sequential full-ROM gate:

| Original owner | Name | Bytes |
|---|---|---:|
| `func_841674C0` | `DoubleTextureTrail_Update` | 772 |
| `func_84167864` | `DoubleTextureTrail_DrawStrips` | 1224 |

The updater interpolates ten nodes between secondary/tertiary owner anchors
using the original divisor 9. Its GS state flag starts a thirty-tick deadline,
enters phase 2 at deadline minus 15, then shrinks node radii by 1.0f with a
0.1f floor. The real `u32` getter signature remains unchanged. The legacy
anchor-output wrapper's existing integer-address ABI is retained explicitly;
the new caller does not invent a conflicting prototype.

A typed record parameter, paired transactionally with the existing caller,
closes the endpoint locations without an unused local. Known/typed/blank
controls prove that changing the caller from byte offsets to the actual
576-byte record leaves its entire module fingerprint unchanged before any
updater candidate is run. The already-C completion wrapper is named
`DoubleTextureTrail_UpdateAll`; this is cleanup, not a third newly decompiled
function. The donor's unused scalar is omitted.

Strip drawing updates the GS phase-dependent alpha only on pass 0, using
`(age - deadline + 15) * 0.07f`, and emits nine eight-quad strips on both
passes. Initializing the two real color-metadata pointers at declaration
reproduces their lifetimes across the phase transition. Cached byte alphas,
ordinary nested loops and SDK macros produce the original code. No forced
register, padding, unused local, fake call/prototype or instruction rewrite
is added to either match.

| Retained complete module | SHA256 |
|---|---|
| First accepted update and typed caller | `f7559ff7b8990746ae5d52ef9796b99be1b52a2c552eacf1ca67b803ffe3fbfb` |
| First accepted strip draw | `7ccc0b00d844bde7f2cc5f20dcd24c8cd47924fdbbedb06701c9f8be3296064a` |
| Final named module | `dc5122b62ceecca27e291827eb870a8db0be54b94dd7f4cb4fecddaf349a10b3` |

The update callback freezes thirteen complete translation units; the strip
callback freezes the changed module plus four collateral objects. Both
reread their receipts and externally hash every snapshot before returning;
counts and hashes are checked again before further compilation. Final naming
passes another normal ROM gate with thirteen frozen complete modules.
Both probe hits are relocation-controlled, so their normal sequential ROM
gates, not masked probe scores, establish acceptance.

Independent unmodified-linker proofs cover all twenty original function
extents, 12336 text bytes and 128 pool bytes across the prior, typed-caller,
two first-accepted and final named objects. Fresh canonical/named,
twenty-leading-blank, public-wrapper and target-layout controls reproduce the
complete game fingerprint. The unchanged assembly draw-all owner has two
calls whose canonical spelling binds locally while the named spelling binds
through the original-name alias. Only those two inspected R_MIPS_26 target
identities are treated as equivalent; raw section bytes are identical, and
independent retail links prove both resolve to `0x84167864`. No object or
instruction is modified for this comparison.

All twelve collateral game fingerprints are unchanged. Accepted provenance
covers exactly the two newly removed owners; aliases preserve all three
named entries. Full-ROM MD5 remains `1561c75d11cedf356a8ddb1a4a5f9d5d`.
All 427 source syntax checks and 76 native tool tests pass. Private campaigns
and generated coverage remain outside the change.

### Pool updater requeue

`func_841665D4`: **requeue**. A padding-free 840-byte body now matches all
208 interior instruction words exactly. The only raw differences are stack
allocation/release: retail reserves 168 bytes, while this source reserves
136. A consumed `height_delta` before the anchor declaration closes both the
float-register residual and the anchor's stack location. Its steering uses
the actual float(float) sine/cosine ABIs and single-precision 20.0f clamps.
Do not trust the earlier drafts with missing math prototypes or double
clamps, even though their normalized shapes look close.

Eight fully consumed history-snapshot variants do not resolve the frame:
they enlarge the body to 956-1004 bytes and frames to 176-312 bytes. Both
authentic stock C drivers are calibrated on complete known matching objects
and leading-blank controls. IDO 7.1 retains the two-word frame residual;
IDO 5.3 also reserves 136 bytes and changes more instructions. Its complete
current module differs as well, so that driver is not an installable
substitute for this translation unit. These negatives cover only those
source families and two C drivers, not every legal source or frontend.

Next: inspect CFE/ugen stack reservation for this exact live-value source,
distinguishing genuine retained aggregate lifetimes from unreferenced
historical storage. Do not repeat the loop/snapshot grid or fill the 32-byte
gap with padding. The owner remains original assembly.

## Full double-texture renderer (2026-10-20)

`func_84168000` is now `DoubleTextureTrail_DrawAll`: a 1332-byte C body
followed by twelve ordinary section-alignment bytes. It allocates ninety
vertices per active trail, builds ten nine-vertex rings, optionally draws
the endpoint/camera-facing geometry, and renders both front- and back-culled
texture passes. The four-record traversal, calls to the accepted texture and
strip helpers, and Stadium 1's corresponding renderer justify the name.

The GS camera getter returns a word-sized address; its eye vector is at
offset 168. `Gfx_AllocDisplayList` also returns a word-sized address and takes
a signed size. Both retain those real interfaces, with explicit pointer
casts. The vertex-offset helper receives the first component of a real
three-float vector; no alternate prototype is introduced.

The final stack reservation requires independently useful source mechanisms:
the consumed vertex-buffer address and vertex angle, plus the consumed
texture-V coordinate declared after the address-taken vectors and camera.
The intermediate alone fixes the static display-list pointer's spill slot;
the declaration placement alone fixes camera/vector offsets. Their
composition matches the 288-byte retail frame and all instructions. Explicit
cached display-list pointer lifetimes instead alter the instruction stream
and are not adopted. No unused locals, padding, forced registers, manual
unrolling, instruction rewrites or relocation rewrites are added.

The normal sequential ROM gate accepted the first composed candidate; its
isolated relocation-masked result is not the acceptance proof. The first
successful gate froze the complete object and four collateral objects before
returning. The named gate froze thirteen complete objects; all twelve
collateral fingerprints are unchanged. Independent unmodified-linker checks
cover all twenty function starts/body extents, all 12336 text bytes, all
128 rodata bytes and the natural twelve-byte tail for original, first-accepted
and named objects. Canonical/named, native/public-wrapper, twenty-leading-
blank and target-layout controls pass. Full-ROM MD5 remains
`1561c75d11cedf356a8ddb1a4a5f9d5d`. All 427 source syntax checks and 76 native
tool tests pass. The original-address linker alias is retained.

### Draw requeues

`func_84165CC0` and `func_84166A64`: **requeue**. Initial padding-free draw
sources reproduce their respective 1136- and 1276-byte bodies, but reserve
312/360 bytes rather than retail's 376/424. These tests use real allocator
and matrix-helper interfaces; the GS pool draw additionally takes a signed
texture-table index and traverses 26 records. Cached display-list and vector
array variants do not close the gaps. Investigate consumed matrix/vector
lifetimes before another source-shape family; do not insert matrix-sized
unused storage to fill the difference.

The updater **requeue** above remains open. A passive stack observer now
passes stock/off/on and leading-blank controls against the known module and
both retained updater/renderer parents. It reports no late temporary spills
for either retained parent. That observation narrows the next investigation
to reservation and meaningful source-local lifetimes; it does not prove
that any particular historical declaration existed.

## Remaining work

Three original assembly owners remain in this module: `func_84165CC0`,
`func_841665D4` and `func_84166A64`.
They include the node updater and draw functions and are not
claimed as solved. Continue with their GS layouts rather than copying
Stadium 1's field offsets or fifty-record name.

The pre-existing `OwnerAnchoredFourStream_Update` and
`DoubleTextureTrail_RotateVertexOffset` helpers retain inherited unused
matrix-sized storage and locals, now marked FAKE. No such storage is added
to the new matches. Their cleanup remains unresolved, as do the separately
documented owner-linked draw and geometry requeues.
