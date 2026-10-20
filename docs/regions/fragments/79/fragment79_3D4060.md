# Owner-linked four-stream trails

## Accepted lifecycle batch, 2026-10-20

On the native tree following `f110aa12` (the source state published in
PR #1326), three owners pass the normal runner and full-ROM gate:

| Original owner | Name | Bytes |
|---|---|---:|
| `func_841647D0` | `OwnerLinkedFourStream_Init` | 340 |
| `func_84164924` | `OwnerLinkedFourStream_Start` | 628 |
| `func_84164C28` | `OwnerLinkedFourStream_UpdateNodeChain` | 992 |

The four stream records are 1076 bytes each. Their fifteen 68-byte samples
begin at offset 56; offset 52 holds the particle handle. Each sample retains
current/previous scale, angle, position and velocity. Init resets the stream
headers and initializes their samples with ordinary loops. Start selects an
inactive stream, copies the initial position/velocity, configures its
lifetime/color and creates the attached particle handle. The leading sample
then advances and updates that handle's position; the remaining samples
copy their predecessor's previous-frame state.

The GS assembly and retail bytes remain the oracle. Stadium 1's
`src/fragments/battle_engine/battle_engine_353370.c` and its record types in
`battle_engine.h` supply an algorithm/ABI witness. No instruction rewrite,
forced register, manual unrolling, dummy local or padding is added to the
three newly matched functions.

## Constant ownership and particle ABI

The module owns the original 80-byte pool at ROM `0x3FC0E0..0x3FC130`.
Isolated original/migrated extraction, fresh/blank controls and independent
retail links prove all 3392 text bytes and the complete pool before adoption.
The still-assembly start, node update and draw pass a full-ROM layout
baseline before further C candidates. The accepted matrix helper's two
external constants become ordinary literals in their original pool slots;
the preceding trail/geometry pools remain unchanged.

GS `func_84109B88` and `func_84109BA4` are no-op stubs, but their callers
still pass a three-float position by value. The first caller consumes a
particle handle; the second passes that handle before the position.
Their former four-integer source definitions obscure those contracts.
The typed definitions in `fragment79_377F80.c` preserve that module's entire
original game fingerprint, not merely the two selected symbols.

The selector width has independent evidence: Stadium 1's actual
`src/fragments/battle_engine/battle_engine_317E70.c` implementation and
`battle_engine.h` declare a `u8` particle variant and pass it to the particle
variant configurator. Modeling the unused GS selector as s32 initially
leaves one linked updater instruction wrong: a saved-register move instead
of the original immediate load of 1. Ordinary event guards, named constants
and a local enum do not resolve it. Correcting the shared API to the
witnessed u8 selector preserves both the complete GS stub object and the
already-accepted start object under fresh/blank controls, then passes a
normal full-ROM baseline. The unchanged updater source subsequently accepts.
No fake call cast, discarded expression or loose prototype is used.

The retail creation stub never defines its return register despite callers
consuming the handle. The typed C therefore retains its missing-return bug
and labels it explicitly; no fabricated return value or instruction is
introduced. This is an inspected assembly property, not a claim that the
stub creates a working particle at runtime.

## Verification

Every successful comparison callback freezes the complete changed module
and at least four collateral objects before returning, rereads the receipt
and externally checks every SHA256. Receipt counts and external hashes are
checked again before more game compilation. Layout/selector/final gates
freeze twelve complete modules, including the repaired stub translation unit.

| Frozen complete module | SHA256 |
|---|---|
| First initializer | `c526adc913ea6471e6d3020ac04c36b369df4de0f7362e8342bbbe118658fd2f` |
| First start | `14e24a1fb66048ecd61318298372ae8e01ca0aac2e71ab20e5c27ab84add04a5` |
| First node update | `65ff9c4f4c41317a7804dbcc6bad55b50148c57fb2ff7d2b26c50abdd0e261f6` |
| Final named module | `27e8c28d0e144c628a30f05dd615baf9cc53e23fb5d50a4bcf2ecfb3a4e1140b` |

Init/start are directly link-verified. Node update has relocation-controlled
object differences and is accepted only by its normal sequential ROM gate;
the masked probe is not acceptance evidence by itself. Independent
unmodified-linker checks of the original, layout, selector, each acceptance
and final named objects prove all six original function extents, all 3392
linked text bytes and all 80 owned pool bytes equal retail. The draw owner
remains original assembly throughout this proof.

Canonical/named, twenty-leading-blank, public-wrapper and target-layout
controls reproduce the final module fingerprint and retail bytes. The
repaired stub module also passes fresh native/public and blank controls
against its complete original fingerprint. All eleven retained collateral
modules are game-identical. Accepted runner provenance covers the three
removed pragmas; accepted owners are not candidate-probed again.

The final normal full-ROM comparison passes with MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. All 427 C source syntax checks and all
76 native tool tests pass. Coverage and private campaign utilities are not
part of this change. Naming, pointer-based completion-wrapper cleanup and
declaration deduplication are independently whole-module neutral.

## Requeue and remaining cleanup

`func_841650A8`: **requeue**. Four padding-free draw variants cover a real
point struct versus float array and direct versus consumed display-list
pointer submission. Their best C body is 1116 bytes with a 320-byte frame;
retail has a 376-byte frame. The donor's unused fourteen-word local and
unused scalar are excluded rather than copied as a match. Recover actual
aggregate/macro-temporary lifetimes before pursuing register ties. Do not
add 56 bytes of padding or repeat the point/list grid as fresh work. This
negative is scoped to those four candidates, not all legal C or compilers.

The pre-existing `OwnerLinkedFourStream_Update` helper retains inherited
unused matrix-sized storage and a local, now explicitly marked FAKE.
Controlled removal changes its complete game fingerprint and is rejected;
that helper cleanup is not claimed by this batch. The separate ten-vertex
geometry requeue also remains unresolved. This is not a complete project
decompilation.
