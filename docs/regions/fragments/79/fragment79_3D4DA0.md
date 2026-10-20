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

## Remaining work

Ten original assembly owners remain in this module, including the anchored
draw function and the other trail families' start/update/draw routines.
They are not claimed as solved. Continue with their GS layouts rather than
copying Stadium 1's field offsets or fifty-record name.

The pre-existing `OwnerAnchoredFourStream_Update` and
`DoubleTextureTrail_RotateVertexOffset` helpers retain inherited unused
matrix-sized storage and locals, now marked FAKE. No such storage is added
to the new matches. Their cleanup remains unresolved, as do the separately
documented owner-linked draw and geometry requeues.
