# Lab PC evolution-view controller

## Matching initializer and input family (2026-10-20)

`LabPC_InitEvolutionView` (`func_88900030`, 1124 bytes) opens the EVOV pool
state, allocates the actual 348-byte controller, loads its text/background
resources, initializes frame-rate-derived timing fields, and creates a
208-by-141 model preview. `func_80001FF0` returns 50 or 60 according to the
TV mode; these values are timing inputs, not random numbers.
//@src/dp_intro.c

The timing stores use an unsigned word conversion followed by signed
halfword narrowing. The integer divisor `2` preserves the original `div.s`;
spelling it `2.0f` lets this compiler substitute multiplication by 0.5 and
changes the instruction sequence. The rounded 245760/rate expression calls
the rate helper twice, as the original instructions do. The model resource,
flag clear, and callback setter use their actual producer/API contracts.
//@src/43700.c
//@src/fragments/29/fragment29_16B030.c

`LabPC_OpenChoiceWindow` (`func_88900B08`, 332 bytes) initializes the existing
two-choice record and creates its window. Its callers use mode 0 or 1;
the original assigns no coordinates/style for other modes. The real window
API returns a byte-sized slot into 76-byte records. Declaring that consumed
`u8` slot before the two coordinates reproduces the original 88-byte frame
and homes at offsets 84, 82, and 76. No padding or unused local is present.
//@src/fragments/29/fragment29_168330.c
//@src/fragments/38/fragment38_1D8990.c

`LabPC_HandleMovePaneInput` (`func_88900C78`, 276 bytes) confirms or cancels
the selected move, updates the controller transition fields, and opens the
appropriate choice window. It captures the twenty-byte move pane across
sound calls. Its selected row is a signed halfword, count is a byte, and
the fallback scrolling API receives the selection address and mask.

`LabPC_HandleChoiceInput` (`func_889007A0`, 828 bytes) handles the two-choice
list in states 9, 11, 12, and 14. Confirmation of its first row chooses the
forward transition and sound; either button on the other row follows the
cancel transition. Without a button it scrolls the actual 52-byte text list.
Inlining the immediately consumed button checks removes an unnecessary
snapshot home and preserves the original 40-byte frame and feedback home.

The window-slot API and move-count API declarations now agree with their
definitions. The existing move-window and transition-setup callers were
adapted only with actual pointer/callback-slot conversions. Before use in
runner companion transactions, known/changed and blank-line controls proved
their complete game-section, symbol-extent, and relocation fingerprints
unchanged. They are ABI cleanup, not additional accepted owners.

## Remaining owners and layout prerequisite

`func_88900528`, `func_88900F54`, `func_88901A24`, and `func_88902624` own
tables/float literals in ROM 0x1D9450..0x1D95D0. A per-file rodata migration
was tested with all assembly owners unchanged. Its 384-byte rodata size was
correct, but controller text grew from 0x2B50 to 0x2B60 and the full ROM
comparison failed. Earlier text-region bytes also changed after extraction;
the precise pass/owner cause has not been established. This is a
`layout-prerequisite`, not a source-shape mismatch to brute-force.

The trial YAML change was reverted, the prior extraction restored, and a
complete rebuild of both code and data objects passed the retail checksum.
No C switch from that experiment was installed. Investigate the extraction
and assembly-stub size changes before migrating these tables again.

An isolated fragment-only extraction of the US controller source narrows
one failure to `func_88900528`. The tested source has SHA-256
`4ac0f7b8f3905e39182adb5924ab4bd6f39c30fb3195f38b663708116b96b35d`.
The baseline's complete text, function
extents, and resolved relocations equal retail; eight relocation spellings
change only because current descriptive aliases resolve inside or outside
the object. Migrating the 384-byte run leaves a four-byte gap immediately
after the predicate and moves every later function by four. In this isolated
case the text section stays 0x2B50 because its final alignment absorbs the
growth; this does not explain every difference from the earlier whole-tree
experiment.

Passive stock-compiler input/output capture, calibrated on the current unit
and the exact retained migration with stock/blank/off/on/on-blank controls,
shows the cause of that gap: the predicate's temporary asm-processor
placeholder is 56 bytes, but its assembly body is 52 bytes. The placeholder
uses three instructions for its double literal, nine for a synthetic switch,
and two for the return. The processor budgets only thirteen instructions
and copies the 52-byte body without removing the extra return-delay word.
//@tools/asm-processor/asm_processor.py

Moving the existing placeholder store after the switch produces 52 bytes
but relocates the literal from pool offset 0 to 32, so it is not a valid
replacement for the current placeholder mechanism. No processor, generated
assembly, linker layout, or source workaround from these diagnostics was
installed. A scaffold fix must preserve both text extent and literal/table
order, then pass the unchanged-owner full-ROM gate before C switches resume.

## Matching view opener (2026-10-20)

`LabPC_OpenEvolutionView` (`func_889027A4`) now matches through ordinary C.
It selects the model's Pokemon, initializes the audio buffer, selects window
coordinates/colors and sounds, creates the 376-by-303 window, records the
Pokemon/context/callback, copies the display names, and starts the appropriate
evolution or move transition. Signed byte offsets and slot arguments, the
actual byte-returning window API, and the unsigned frame-timer conversion
preserve the original instructions. The model-selection API receives both
the model and Pokemon pointers; the original retains incoming `a1` there.
//@src/43700.c
//@src/229E0.c
//@src/fragments/29/fragment29_168330.c

The first eight-variant batch accepted its direct-expression candidate.
Coordinate locals change the argument narrowing/scheduling; keeping the
immediately consumed coordinates in the window call matches naturally.
The instruction body is 960 bytes; the original 972-byte assembly symbol
includes twelve final zero bytes supplied by ordinary translation-unit
alignment. No padding helper or pragma was added. The formatter's historical
assembly name and descriptive C name cause preliminary relocation-name
drift; the sequential full-ROM gate resolves the alias and passes retail
comparison. Complete-unit independent retail links verify the physical
bytes, rather than treating that preliminary symbol-name check as proof.

Only the four layout-prerequisite owners listed above remain assembly in
this controller file.
