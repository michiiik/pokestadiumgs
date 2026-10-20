# Four-stream trail family

## Accepted four-owner batch, 2026-10-20

Starting from `94ba9b4`, four assembly owners are accepted through the normal
runner and authoritative full-ROM gate:

| Original owner | Name | C body bytes |
|---|---|---:|
| `func_841639D0` | `FourStreamTrail_Init` | 380 |
| `func_84163B4C` | `FourStreamTrail_Start` | 596 |
| `func_84163E60` | `FourStreamTrail_UpdateNodeChain` | 908 |
| `func_84164280` | `FourStreamTrail_Draw` | 1348 |

Each stream has fifteen 68-byte samples beginning at offset 52 of a
1072-byte record. Samples retain current/previous scale, angle, position
and velocity. Init resets the four streams and initializes their samples.
Start selects an inactive stream, sets its lifetime/color/origin and
seeds its sample chain. The node update advances the leading sample and
copies the previous-frame state down the remaining chain. Draw builds two
vertices per sample, clamps their height to the ground and emits fourteen
connected quads, plus an optional marker at the head.

The GS assembly is the oracle. Stadium 1's
`src/fragments/battle_engine/battle_engine_352570.c` and
`battle_engine.h` provide a structural witness for this family. No manual
unrolling, output/relocation rewrite, forced register, volatile local or
dummy storage is added to any of these four functions.

## Constant-pool ownership

This module's 64-byte pool occupies ROM `0x3FC0A0..0x3FC0E0`.
It contains start's float turn constant, the existing transform helper's
two doubles, node-chain's two interpolation doubles, and draw's double
turn/float half-turn constants, followed by normal alignment bytes.

Before migration, writable/const external declarations and consumed
constant snapshots leave extra address carriers or incorrect live ranges.
Those experiments do not prove source-space exhaustion. The layout repair
gives the module its actual rodata subsegment and moves the existing
helper's two constants into ordinary C literals. Isolated original/migrated
extractions, fresh/blank controls and independent retail-address links
prove all text/pool bytes before adoption. The still-assembly start, node
update and draw then pass a normal full-ROM baseline gate. Only after that
gate are literal-based C candidates tested; start and node update accept
without their former snapshots.

The preceding ten-vertex geometry pool remains unchanged. Extraction is
scoped to fragment79, leaves all C inputs and the reviewed linker unchanged,
and archives the superseded generated rodata source privately. No shared
checkout or dependency source is changed.

## Draw's final spill home and interface cleanup

The first padding-free draw body has the correct frame, instructions and
pool except for two accesses to a display-list pointer spill home:
stack offset 104 instead of the original 100. Narrowing unrelated scratch
scopes does not resolve it. Naming the actual strip display-list pointer
and assigning it immediately before submission recovers the original home.
The local is consumed by `gSPDisplayList`; it is not a discarded expression
or an artificial storage reservation.

The header's offset-24 field is a real vertex-buffer pointer: draw allocates
thirty vertices there and submits the resulting buffer. It is typed as
`Vtx *vertices`, removing integer/pointer round trips. Unknown header bytes
remain unknown. The existing completion wrapper and node-chain interface
use the same real stream type. All naming, pointer, declaration and number
formatting cleanups preserve the complete accepted game fingerprint.
Old-address function aliases accompany all four symbol-map names.

## Verification

Every successful comparison callback freezes the complete changed module
and at least four collateral objects, rereads the receipt and externally
checks all SHA256 values before returning. Receipt counts and external
hashes are checked again before further game compilation.

| Frozen stage | Complete object SHA256 |
|---|---|
| First initializer | `0544b375fb6fed8e88fc47b1db3d03005fbffadb85c9d8d58cd16ec5e9b837c5` |
| Owned-pool start | `ff2abf6f810437496a1d47ac6c7104e596a332ee4869acdefbed2ae7e470a409` |
| Owned-pool node update | `a71b0d16aa1d5916c5bd1f24a72b8cda80ccad93f5f138ea03f9cb31f7b4aeff` |
| First draw | `84ab1d69d59cb872430e1ba5569936c4030c42bdddffd1de6ed1b104a0aa1302` |
| Final named module | `5835bed9f48e0edb6af30eced997b740e43438fd4916c3835ccf2779e9c62a10` |

Independent unmodified-linker checks cover the original assembly, initializer,
layout baseline, both subsequent acceptances, draw acceptance and final named
object. All six function starts/body extents and all 3584 linked text bytes
match retail, as do all 64 pool bytes once owned by the module. The original
last assembly symbol includes twelve zero alignment bytes: its 1360-byte
symbol footprint becomes a 1348-byte C body plus the same twelve ordinary
section-alignment bytes. No padding pragma/helper is used.

Fresh canonical/named, twenty-leading-blank, public-wrapper and target-layout
controls reproduce the final complete fingerprint and linked retail bytes.
All nine retained collateral modules preserve their full game fingerprints.
The four removed owners have accepted runner provenance; no accepted owner
is sent back through candidate probing.

The final normal ROM comparison passes with MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. All 427 C sources pass host syntax checks
and all 76 native tool tests pass. Coverage remains outside this change.

## Remaining work

The pre-existing `FourStreamTrail_Update` transform helper retains its
inherited unused `pad2` local, now explicitly marked FAKE. A controlled
removal changes its 240-byte frame to 232 bytes and changes original stack
offsets; it is rejected rather than hidden or replaced with another fake.
That cleanup is not claimed by this four-owner batch. No such padding is
used in the newly accepted functions.

The separate `func_84163380` ten-vertex geometry source-shape requeue remains
unresolved. Completing this family does not establish a complete project
decompilation.
