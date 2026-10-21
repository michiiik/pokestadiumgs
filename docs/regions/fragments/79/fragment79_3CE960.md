# Fragment 79: 16-by-16 ripple grid

## Accepted source batch

Five US assembly owners are replaced by C: `RippleGrid16_RecomputeNormal`
(1668 bytes), `RippleGrid16_FillVertex` (184), `RippleGrid16_Update` (704),
`RippleGrid16_BuildViewMatrix` (300), and `RippleGrid16_Draw` (1220-byte
original span). Original-address aliases preserve callers outside this file.

The names describe inspected operations: the updater assigns radial sine
heights to a 16-by-16 grid, then rebuilds its normals; the renderer converts
all 256 nodes to vertices and draws 225 cells with alternating triangle
diagonals. The matrix builder offsets the camera eye and target along the
normalized view direction using `105 / (fovy / 30)`.

The normal builder reuses a real node pointer for neighboring xyz triplets.
It retains scalar center coordinates and a signed 16-bit contribution count.
No unused stack local is needed. Vertex conversion retains three float normal
carriers before the double-precision multiplication by 120.

The updater interprets `func_841094EC` through a signed status local while
preserving the getter's actual unsigned return declaration. Status 1 starts
the one-shot 25-frame fade. Alpha rises by 10 to 128 before the latch, then
falls by 12 starting at fade age 16. Amplitude rises by 0.05 while below 1.

## Readonly ownership and verification

The 32-byte literal window at ROM `0x3FBFD0..0x3FBFF0` belongs to this file's
`.rodata`: float 0.01, double 0.05, float 76.3667984, and double
6.2831854820251465, including the original alignment zeros. The shared tail
starts at `0x3FBFF0`. Independent normal and blank-line staged links preserved
all 4480 text bytes and these 32 readonly bytes before the layout-only full-ROM
gate. Compiler-owned literals are necessary for the updater's floating-point
constant retention across sine calls.

The native candidate runner accepted all five owners through successful
full-ROM comparisons with the host syntax check enabled. Every successful
gate froze its source, whole translation unit, four distinct collateral
objects, ROM, ELF, and linker script before another compile, with independently
checked SHA-256 hashes. The retail US ROM MD5 is
`1561c75d11cedf356a8ddb1a4a5f9d5d`.

Known, blank-line, readable, named, named-blank, and target-layout controls
preserve the original complete text and readonly sections and normalized
relocation targets. Thirteen target-compiler assertions cover the 28-byte
node, 7188-byte grid state, camera layout, and field offsets.

The renderer's 1212-byte C body ends at section offset 4472. Its original
1220-byte assembly extent includes eight zero bytes of natural 16-byte final
section alignment. All original section bytes and relocations are preserved;
only this function's ELF size excludes the verified eight-byte alignment.
There is no explicit padding or object rewrite.

## Unresolved initializer: requeue / register-tie

`func_8415F0D0` remains a 404-byte assembly owner. The best ordinary C spelling
matches all instruction counts and opcode shapes but exchanges `a2` and `a3`
across ten words in the row texture-coordinate carrier and column induction.
Use the late node-pointer initialization, signed 16-bit row/column texture
carriers, and literal 0.01f. The source initializes x as `row * 6.75 - 54`,
z as `column * 5.25 - 42`, and y as 1.

Covered families: early/late node pointer, row UV outside/inside the inner
loop, column-carrier removal, UV assignment order, pointer footer/body, signed
and unsigned coordinate widths, and compiler-owned versus external literal.
These did not close the ten-word tie. Next action: a calibrated allocation
trace or bounded genuine-source permuter focused on the two UV carrier
lifetimes, not another width sweep. No forced register, dead local, identity
arithmetic, or hand-unrolled fallback is accepted.
