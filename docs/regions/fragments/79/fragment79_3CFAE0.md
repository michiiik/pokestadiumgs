# Fragment 79: per-node phase grid

## Accepted source batch

Four US assembly owners are replaced by C: `PhaseGrid16_RecomputeNormal`
(1580 bytes), `PhaseGrid16_FillVertex` (184), `PhaseGrid16_Update` (532),
and `PhaseGrid16_BuildViewMatrix` (300). The batch covers 2596 bytes and retains
original-address aliases for external callers.

Each 32-byte node stores xyz, a normal vector, texture coordinates, and a
float phase at offset 28. The 16-by-16 node grid starts at offset 20 of an
8212-byte state reached through `D_841876E0`.

The normal builder reuses a real node pointer for neighboring xyz triplets,
with scalar center coordinates and a signed 16-bit contribution count. Vertex
conversion uses three float normal carriers before scaling by double 120.
The camera builder translates eye and target along their normalized direction
by `105 / (fovy / 30)`.

The updater assigns each node's height as `sin(phase) * 0.5 + 1.0`, then
increments its phase by double 0.1. Its GS fade latch is `D_841A4D80`: status 1
starts a one-shot 25-frame fade, alpha falls by 12 starting at age 16, and
amplitude grows by 0.05 while below 0.5. The unsigned status getter keeps its
actual declaration; a signed status local preserves the observed comparison.

## Layout and verification

The readonly pool at ROM `0x3FBFF0..0x3FC010` is assigned to this source:
double 1.5707963705062866, float 0.01 with its original alignment zeros,
double 0.05, and double 0.1. The shared readonly tail begins at `0x3FC010`.
Independent normal and blank-line staged links preserved all 4752 text bytes
and 32 readonly bytes before a layout-only full-ROM gate with all seven
original assembly owners retained.

The native runner accepted all four C owners through full-ROM comparisons
with the host syntax check enabled. Every successful gate froze the source,
whole TU, four distinct collateral objects, and ROM/ELF/linker outputs before
another compile, with externally checked hashes. Retail US ROM MD5:
`1561c75d11cedf356a8ddb1a4a5f9d5d`.

Six whole-object controls cover known, blank-line, readable, named,
named-blank, and target-layout builds. All original sections, seven function
extents, and normalized relocation targets are preserved; no function-size
exception is used. Fourteen target-compiler assertions cover structure sizes
and field offsets. Shared accepted declarations precede every remaining
assembly owner, verified by separate known/declarations-first/blank controls.

## Remaining owners

- `func_84160250`: requeue / register-tie. Best ordinary source is 336 bytes
  with only two raw instruction differences, at owner offsets 108 and 224:
  target `c.eq.s f12,f14`, candidate `c.eq.s f14,f12`. Computing both signed
  row/column deltas inside the inner loop, column first, removed the earlier
  seven-word `a2`/`a3` swap. Both pointers and arithmetic remain ordinary C.
  Keep this improved parent, not the original nine-word candidate.
- `func_841603A0`: initializer remains assembly. It seeds a central ripple,
  ten random ripple origins, and heights derived from node phases. Draft from
  the inspected sibling structure, preserving GS spacing and the actual
  signed `guRandom` declaration.
- `func_84161018`: renderer remains assembly. Its vertex iteration, SDK
  commands, and alternating diagonals parallel the adjacent completed grid;
  retain this file's 32-byte node stride and texture/render-state symbols.

For the ripple near-match, a calibrated native source-permutation run improved
the search score from 65 to 20 within 90 seconds; the complete-TU runner then
confirmed exactly two differing words. Tested families include integer/float
deltas, comparison order, pointer footer/body, delta scopes/order, inverted
center tests, and nested/chain center control flow. Nested flow increases
instruction count; plain condition operand reversal is inert. Next action:
trace the remaining floating-comparison operand ordering on the improved
parent, or extend a bounded source search from it. No comma-expression fake,
forced register, dead local, identity arithmetic, or instruction rewrite is
an accepted fallback.

Search calibration must preserve the SDK's `__sgi`-guarded
`#pragma intrinsic(sqrtf)` during host preprocessing. Without it, the stripped
search input calls `sqrtf` instead of emitting `sqrt.s` and is not the actual
native parent. Both stripped-parent and parser roundtrip comparisons, plus a
known matched sibling through the same wrapper, passed after preserving this
intrinsic. Search scores alone are not acceptance evidence.
