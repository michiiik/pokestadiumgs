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

`func_889027A4` remains assembly and has no jump-table prerequisite. Its
view-opening flow is the next controller owner to recover.
