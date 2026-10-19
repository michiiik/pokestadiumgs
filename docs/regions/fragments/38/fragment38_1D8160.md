# Lab PC move and evolution queries

## Native matching evidence (2026-10-19)

`func_88902E8C` (`LabPC_FindLevelUpEvolution`) walks three-byte evolution
records. It returns the target species for level, friendship, and relative
Attack/Defense conditions, with the held-item and cartridge-mode guards from
the original assembly. The optional clock path selects species 196 or 197.

The clock reader's first output is a `u16` day count, followed by byte-sized
hour, minute, and second outputs. `func_8005F190` loads/stores the first output
with `lhu`/`sh`, but advances seconds, minutes, and hours with `lbu`/`sb`.
Four byte locals give the wrong stack offsets; a real halfword day count
reproduces the original 56-byte frame and all clock-output addresses.

`func_88902E4C` initializes a level-up move cursor and returns the result of
`func_88902CF0`. The stat-animation completion callback tests that result.
Its former `void` declaration discarded an observable return contract; the
explicit return preserves the complete translation-unit game fingerprint.

## Matching colored move-name formatter (`func_88902C3C`)

`LabPC_FormatColoredMoveName` matches the original 180-byte instruction
sequence and 48-byte frame. It passes the resolved name directly to `sprintf`
instead of keeping a separate name local. This lets the compiler place the
live move value's caller-save home at offset 36, as in retail.

`func_88000510` writes the actual three-byte RGB struct defined in
`src/fragments/29/fragment29_166060.c` to its first argument and returns that
destination pointer. This explicit interface and the earlier struct-return
spelling produce identical complete game objects for the helper and its
formatter caller. The explicit pointer result also lets renderers pass the
destination directly to `func_880006E0`. The original format string is
`<COL1,PUSH,%d,%d,%d,255>%s<COL1,POP>`. Move 252 uses the special-name lookup;
other moves use the move-name and move-type APIs.

Earlier spellings with a name local put that home at offset 32: four raw
instruction differences despite normalized similarity 1.0. Narrow types,
selected-move caches, disjoint scopes, and branching on the RGB result did
not resolve that residual. A passive frame trace, calibrated against current
known and retained-parent stock/blank/off/on/on-blank complete-object
controls, identified a local-home difference rather than a temporary-area
spill. Inlining the consumed name expression closes it without dummy locals,
wider RGB storage, artificial padding, or compiler changes.

## Matching stone-evolution maps

The three species maps are fire (37 to 38, 58 to 59, 133 to 136), water
(61 to 62, 90 to 91, 120 to 121, 133 to 134), and leaf (44 to 45, 70 to 71,
102 to 103). Each returns zero for a species without a listed evolution.
`func_88902624` selects these maps when applying an evolution item.
//@src/fragments/38/fragment38_1D5610.c

Ordinary C switches reproduce the original early-return/shared-tail shape
with source case order 133/37/58 for fire, 133/61/90/120 for water, and
70/102/44 for leaf. Sorted cases produce different basic-block order. No
manual branch encoding or padding is required. Together with the formatter,
these replacements leave `fragment38_1D8160.c` entirely in C.
