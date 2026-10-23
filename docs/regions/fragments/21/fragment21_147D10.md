# Region notes -- src/fragments/21/fragment21_147D10.c

## 2026-10-23: cellular screen-transition batch

Three owners were accepted through the native repository runner and the ordinary
US `COMPARE=1 RUN_CC_CHECK=1` gate. The resulting ROM MD5 is
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Acceptance was measured on native base
`47e1bffee228f8e3325d667ad51ad26d86739570`, followed by a fresh gate after
declaration cleanup. These results do not claim a build of a later public base.

| Owner | Bytes | Operation and source mechanism |
| --- | ---: | --- |
| `func_82507DC0` | 296 | Clear the 4800-byte packed buffer; make ten random placements of state 1 in a 160-by-120 grid. Keep the random column separate from the final cell index; unsigned remainder operands and a signed row-product expression reproduce the division/multiply sequence. The flag field at byte 4 is unsigned. |
| `func_82507EE8` | 300 | Produce eight empty-cell indicators and their count using signed offsets and circular wrapping over 19200 cells. A normal eight-iteration `for` loop produces the compiler's two-way unroll. Use the byte-valued packed-cell test directly; a separately cached byte instead changes allocation. |
| `func_8250850C` | 216 | Dispatch between the packed-mask renderer and a 640-by-480 fill according to transition state and flag bit 0. A regular `switch` matches. The fill helper is the existing `GfxImage_FillRectangle` at 0x80007444; its defining signature in `src/7A50.c` ends in `u16 color`. |

All three accepted attempts had `link_verified: true`. Immediate acceptance
snapshots preserved source, active assembly inputs, layout, module, four
collateral objects, linked ELF/linker script, and ROM before further compilation.
Complete module game sections, all 11 function extents, semantic relocations,
the entire linked fragment21, and the collateral objects matched the baseline.
External SHA-256 checks verified the frozen artifacts. Known-source and
twenty-leading-blank controls matched the complete baseline module. Removing
the neighbor scan's unnecessary initial `cell = 0` and duplicate declarations
also preserved the complete module; the cleaned source passed the fresh gate.
The native tooling suite passed 76 tests.

Proposed evidence-backed names for integration are
`CellularTransition_SeedCells`, `CellularTransition_FindEmptyNeighbors`, and
`CellularTransition_Draw`. Symbol-map and alias changes are coordinated
separately from this file-owned batch.

### Public-base overlap check

Public master `2edb8be4ac90c08f045e62bc733e6eb6b669a3f3` includes PR #1444.
That PR changes no fragment21 source. This file at that public revision is
identical to the native batch's committed baseline, and all three accepted
owners remain assembly there. Its symbol-map changes affect fragment79;
its other symbol additions do not overlap this batch. Future exports must
preserve the full public base and transfer only this batch's owned delta.

### Unresolved owners

- **requeue -- `func_82508014`:** best valid source is 596 bytes, the correct
  160-byte frame, and the exact observed stack homes (completion flag 104,
  eight-word availability buffer 108, step counter 144). The useful declaration
  order is: a real offset-table pointer or computed current-cell pointer;
  packed-buffer pointer; finished count; step; byte state; availability array;
  completion flag; available count; direction; neighbor index; current index.
  All values are used; no unused storage is needed. Best valid similarity is
  normalized 0.9799, raw 0.9329. Ten words differ: the neighbor-table and 19200
  constant use s7/s8 in the opposite roles, and four setup positions differ
  beginning at byte 0x3C. The remaining body, stack homes, and instruction count
  agree. Tested array/value declaration ordering, explicit table/current-cell
  views, guarded-do/for/while forms, and signed/unsigned bound domains. Naming a
  constant grid size or making the loop bound unsigned changes the divide
  sequence and is not a solution. Defining the actual eight-offset array in C
  for diagnosis leaves the same ten-word residual and adds rejected data-layout
  drift; data migration is not established as a prerequisite. Next action:
  measure the stock IDO 7.1 allocator's table-address versus constant decisions
  before another source family. A bounded, calibrated 90-second source search
  found no valid improvement: its lower score moved the table-pointer
  initialization after reads, and was discarded. Corrected read tracking alone
  does not make unrestricted statement reordering semantically safe.
- **requeue -- `func_825082C8`:** render contiguous horizontal runs of selected
  packed cells with real GBI macros, four screen pixels per cell. Best measured
  source is normalized 0.7742, raw 0.3226; 620 bytes versus the 580-byte oracle.
  The oracle duplicates lower-corner preparation in the two flag branches and
  shares the command-store tail; tested direct macros, coordinate temporaries,
  sum/distributed/shift forms, normal loop forms, and actual packet-value
  intermediates. Packet intermediates are worse and are not installed. Next
  action: reconstruct the shared draw-tail control flow, rather than repeat
  coordinate spelling variants.
- **requeue -- `func_825085E4`:** 60-byte start-cover operation: if state is 0,
  set it to 1, clear flag bit 0, and return success. Natural scalar forms remain
  normalized 0.6000, best raw 0.4000. The compiler reuses materialized global
  addresses; the oracle uses independent scalar accesses. Result widths,
  switch/guard/boolean forms, and explicit flag values did not resolve that
  shape. A minimal scalar-only compiler control and one with address-taking
  elsewhere produce the same instructions, so address escape in this TU has
  been ruled out as the cause. Next action: inspect scalar-address commoning
  and the actual state-block type, not more result-width variants.
- **requeue -- `func_82508620`:** not probed in this batch. The oracle changes
  state 3 to 1, sets flag bit 0, and returns success; its final flag store shares
  the earlier `$at` page load. The scheduler's existing coalescing warning is
  not evidence of a valid C match or permission to rewrite instructions. Next
  action: investigate a genuine state-block/source representation or compiler
  mechanism without post-compile instruction transformation.

## Coordinated integration names

The verified operations are named
`CellularTransition_SeedCells` (`func_82507DC0`), `CellularTransition_FindEmptyNeighbors` (`func_82507EE8`), `CellularTransition_Draw` (`func_8250850C`).
The original names remain linker aliases. No other source implementation is replaced.
