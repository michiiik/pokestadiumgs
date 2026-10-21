# Fragment 79: flat grid and textured ribbon pool

## First accepted batch

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

## Second accepted batch

Four additional US owners are C, totaling 3908 bytes:

- `FlatGrid16_RecomputeNormal` (`func_84161670`, 1668 bytes).
- `FlatGrid16_Update` (`func_84161DAC`, 716).
- `FlatGrid16_Draw` (`func_841621A4`, 1212).
- `TexturedRibbonSheet_Init` (`func_84162660`, 312).

The normal builder reuses a node pointer for neighboring positions, with
scalar center coordinates and a signed 16-bit contribution count. It sums
three cross-product contributions and subtracts the fourth, then normalizes
the sum, using an upward normal for a zero vector.

The updater preserves the GS one-shot fade latch: status 1 resets age to zero
and duration to 25, alpha grows by 10 up to 80 before the latch, and falls by
8 starting at age 16 afterward. Amplitude grows by double 0.05 while below
0.25. Each node's radial falloff is `1 - sqrt(x*x + z*z) / radius`; its height
uses the 20-frame sine cycle, three radial phase turns, and amplitude times
falloff. Normals are rebuilt after all heights are updated.

The readonly symbols remain owned by the original shared assembly:
`D_8418C780` is double 0.05, `D_8418C788` is float 76.3667984, and
`D_8418C790` is double 6.2831854820251465. The updater captures radius and
cycle radians in real locals before traversing the grid. This preserves the
immutable loop values across sine calls without new literal pools or layout
changes. A direct-global source hypothesis had a different frame and register
allocation; the captured-value hypothesis passed the complete-ROM gate.

The renderer converts all 256 nodes to vertices, loads texture `D_8418CAB0`
and render state `D_841877C0`, and draws alternating cell diagonals with SDK
macros and ordinary loops. The compiler performs its observed unroll.

Ribbon initialization clears the GS latch and age, then traverses 14 records
and ten nodes per record. It clears active/age/duration and the same position
and velocity fields as the inspected Stadium 1 witness, leaving the other
fields untouched. The existing ribbon layouts were moved before earlier
owners only after known/moved/blank whole-object controls passed.

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

The second batch independently passed the same six whole-object controls and
22 layout assertions. Every original section, all 7840 text bytes, all twelve
function extents, and semantic relocation targets match its retained baseline.
The 96 shared readonly bytes at ROM `0x3FC010..0x3FC070` match retail directly;
the final freeze includes their assembly object. Shared cross-product and
remaining-owner prototypes precede the normal builder, verified through
known/moved/blank object controls before its successful full-ROM gate.

## Completion batch

`TexturedRibbonSheet_Start` (`func_84162798`, 680 bytes) and
`TexturedRibbonSheet_Draw` (`func_84162DE8`, 1432-byte original span) complete
this source. All twelve functions are C; no assembly owners remain.

Start rejects emission when the GS phase latch is 2, finds a free record in
the pointer-based 14-record pool, and initializes ten nodes from position,
velocity, acceleration, color, duration, and phase-step arguments. The random
phase uses the SDK's actual signed `guRandom() % 100` and double cycle literal.
The inspected scale getter retains its float return type.

Drawing loads intensity texture `D_8418CABC`, composes translation/rotation/
scale matrices through the actual helpers, and builds two vertices per node.
It preserves the existing cached-vertex behavior and draws the nine connecting
strips with `D_84187888`; the leading quad uses `D_841878D8`. All graphics
commands use SDK macros and ordinary loops. `TexturedRibbonSheet_Update`
retains its actual float-array output interface; drawing passes the x field
of the three-float offset vector.

### Literal ownership and frame evidence

The completion batch assigns ROM `0x3FC030..0x3FC070`, 64 bytes, to this
source's readonly subsegment. The original shared prefix at
`0x3FC010..0x3FC030` remains assembly-owned and supplies the grid constants.
The existing rotation helper spells its known 360-degree and cycle values
as double literals, allowing its original pool to remain contiguous with
start and drawing's pools. No data bytes are inserted or removed.

An 8-byte cycle-only proposal failed staged linking because its object padded
to 16 bytes and would overlap the following degree constant. A 16-byte
cycle/degrees window then passed normal/blank links and a layout-only ROM gate
with both remaining assembly owners retained. After start accepted, expanding
to the full 64-byte window passed separate normal/blank links and another
layout-only full-ROM gate with drawing retained as assembly.

The local-double snapshot start hypothesis had a 152-byte frame versus 144
in the original. Capturing drawing's constants also enlarged its frame.
Using the real literals in their verified pools restores the target frames
without dummy locals, padding, forced registers, or instruction rewrites.
The compiler performs the observed loop unrolling.

### Completion verification

Both owners passed recorded native full-ROM gates with host syntax checking.
Successful runner gates froze nine artifacts each; both layout-only gates
and the final named gate use independent seventeen-artifact freezes. Hashes
are checked before subsequent compilation.

Six complete-object controls preserve all 7840 text bytes, all 64 owned
readonly bytes, and normalized relocation targets. Eleven function extents
are unchanged. The renderer's 1432-byte original span comprises a 1420-byte
C body plus the same 12 zero bytes at text offsets 7828 through 7839, rounding
the section to 16 bytes. This is the only size-metadata exception; no padding
code is added. Twenty-two target-compiler size/offset assertions pass.
The shared 32-byte readonly prefix and the owned 64-byte pool together remain
the original 96 retail bytes. The US ROM MD5 is unchanged.
