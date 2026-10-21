# Fragment 79: flat grid and textured ribbon pool

## Accepted batch

Four US assembly owners are replaced by C, totaling 1236 bytes:

- `FlatGrid16_Initialize` (`func_841614E0`, 400 bytes).
- `FlatGrid16_FillVertex` (`func_84161CF4`, 184).
- `FlatGrid16_BuildViewMatrix` (`func_84162078`, 300).
- `TexturedRibbonSheet_IsComplete` (`func_84162C88`, 352).

The grid uses 28-byte nodes containing position, normal, and signed texture
coordinates. Its 16-by-16 node array starts at offset 20 of a 7188-byte state
reached through `D_84187790`. Initialization resets the header and latch
`D_841A4D90` before loading the node pointer. Positions are
`x = row * 6.75 - 54`, `y = 1`, `z = column * 5.25 - 42`.

Initialization keeps a real signed 16-bit row texture carrier and converts
the column coordinate to signed 16 bits before multiplying by 16 for the
stored texture coordinate. This is a width conversion from 32-bit arithmetic,
not a same-type cast. A full-object control removing that conversion changes
the initializer from 400 to 568 bytes. Named-coordinate and narrower-index
alternatives were tested but did not preserve the original object. The source
retains ordinary nested loops; IDO performs the observed four-way unroll.

Vertex conversion loads three float normal carriers before multiplying by
double 120. The camera builder translates eye and target along their normalized
direction by `105 / (fovy / 30)`, using the same camera layout verified in
the adjacent grid sources.

The ribbon pool contains 14 records, each 856 bytes with ten 80-byte nodes.
`TexturedRibbonSheet_IsComplete` increments `D_841A4DA2`, starts a one-shot
70-frame deadline in `D_841A4DA0` on status 1, advances `D_841A4DA4` from
1 to 2 after the deadline-minus-50 threshold, and returns -1 after the deadline.
It then ages active records, retires records beyond duration plus 10, and calls
`TexturedRibbonSheet_UpdateRecord` for survivors. It returns 0 while any
record survives and -1 otherwise. Initializing the active-record count after
the latch/deadline checks, before acquiring the pool pointer, preserves the
target's register allocation. The status getter retains its unsigned ABI;
a signed local carries its result.

The inspected Stadium 1 witness is
`src/fragments/battle_engine/battle_engine_3512D0.c` in the Stadium 1 tree.
It establishes the ribbon record traversal, but its static 40-record pool and
lack of GS deadline handling are not transferred to GS. The existing matched
`TexturedRibbonSheet_UpdateRecord` in this GS source is the completion loop's
actual callee.

## Verification

The native recorded runner accepted all four owners through full-ROM gates
with host syntax checking enabled. Every successful gate immediately froze
the source, whole translation-unit object, four distinct collateral objects,
and ROM/ELF/linker outputs; independent hashes were checked before another
compile. The final named normal build is gated and frozen separately.

Six whole-object controls cover known, blank-line, readable, named,
named-blank, and target-layout source. All original sections, 7840 text bytes,
twelve function extents, and normalized relocation targets match the retained
original object. No function-size or alignment exception is used. Twenty-two
target-compiler assertions check grid/camera/ribbon sizes and field offsets.
Moving the accepted grid declarations before the earlier assembly owners also
passed independent known/declarations-first/blank whole-object controls.

US retail ROM MD5: `1561c75d11cedf356a8ddb1a4a5f9d5d`.
No instruction rewrite, forced register, dead local, manual unroll, padding
helper, or coverage update is included.

## Remaining owners

- `func_84161670`: grid normal construction. Reuse the adjacent accepted
  grid normal builder as a source hypothesis, retaining this 28-byte stride.
- `func_84161DAC`: grid updater. Preserve its GS fade latch, alpha cap 80,
  decrement 8 after age 16, and readonly references starting at `D_8418C780`.
- `func_841621A4`: grid renderer. Use SDK graphics macros and this file's
  vertex/camera helpers; inspect texture/state symbols in assembly first.
- `func_84162660`: ribbon pool initialization. The original clears 14
  records with ten nodes each; the existing ribbon types currently follow
  this owner, so establish declaration visibility before candidate probes.
- `func_84162798`: ribbon start. Preserve the GS phase-2 emission guard and
  14-record pointer-based pool instead of the Stadium 1 static 40-record pool.
- `func_84162DE8`: ribbon renderer. Reuse the existing matched record and
  rotation helpers and inspect all GS texture/render-state symbols.

These six owners were not candidate-probed in this batch. Readonly data at
ROM `0x3FC010..0x3FC070` remains in the shared assembly owner; literal-emitting
or switch candidates need an independently linked and ROM-gated layout plan
before acceptance. A new file-level subsegment is not part of this batch.
