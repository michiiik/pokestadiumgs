# Lab PC text lists and message dialogs

## Native C matches (2026-10-19)

`LabPC_DrawSelectableTextList` (`func_889033FC`) draws the list through
`func_88002820`, then places a selection frame using the selected row,
font height, and row spacing. The list's height is byte-sized, as the
original call result is masked before the frame dimensions are computed.

`LabPC_InitTwoChoiceDialog` (`func_889034DC`) loads strings 69/0 and 69/1
into a two-element array, initializes its text-list layout, and clears the
result. The string array follows the complete 52-byte layout, at offsets
56 and 60 in the containing dialog; the result is at offset 64.

`LabPC_OpenMessageDialog` (`func_88903C50`) allocates a 584-byte message
record, copies its title into the 512-byte buffer at offset 60, and points
the text list at that buffer. Completion, cancellation, and callback
fields occupy offsets 572, 576, and 580. These sizes follow the allocation,
copy destination, and callback consumers, rather than extra match storage.
The window API returns a slot index into 76-byte records.

`LabPC_CloseMessageDialog` (`func_88903B2C`) restores controller repeat,
marks completion when a pointer is present, and updates the modal state
when cancellation is unavailable. It reloads the global record after the
completion store, which may alias it, saves the callback before freeing
the record, and then calls the saved callback.

The list producer and drawing consumer establish the field widths and
offsets used by both dialog records.
//@src/fragments/29/fragment29_168330.c

The constructor's compiler symbol covers 444 instruction bytes; the
original assembly extent also includes four trailing zero bytes. Verification
must check the entire 2672-byte translation-unit text region, including
those original zero bytes, rather than inserting a padding helper.

## Matching move-details renderer (`func_889035FC`, 2026-10-20)

`LabPC_DrawMoveDetails` draws move names, power/accuracy/type, PP values,
and the selected-row frame. Its 1284 bytes and 144-byte frame match the
original through the normal native runner and full-ROM comparison. This
replacement leaves all ten functions in this translation unit in C.

A byte-sized move ID reproduces the distinct saved-register carriers used
by comparisons and narrow move-query arguments. Inlining the consumed
power and accuracy label lookups reproduces the frame size. The type-color
lookup writes a three-byte RGB destination and returns its address; making
that actual interface explicit preserves complete game fingerprints for
the helper and its existing formatter caller.
//@src/fragments/29/fragment29_166060.c
//@src/fragments/38/fragment38_1D8160.c

The type-name coordinate uses its width calculation directly in the drawing
call, after the x-coordinate and font tracking. A separate width local adds
a home and shifts the power/accuracy label homes from retail offsets 96/100
to 92/96, despite preserving the overall frame size. Inlining the consumed
width expression also reproduces the coordinate load/add order.

Each row loop advances its index and signed halfword y-coordinate together
in the `for` update expression. Keeping the y update in the body leaves
instruction-order differences in the name-list and PP loops. Combining the
updates reproduces both original delay-slot schedules without instruction
rewrites, explicit register placement, dummy work, or extra storage.

These mechanisms close the previous raw-similarity 0.9626 requeue after
64 total source variants. A logging-only frame observer was first checked
against both the current known source and exact retained parent in stock,
stock-plus-blank, observer-off, observer-on, and observer-on-plus-blank modes.
All ten complete game fingerprints matched before traces were interpreted;
the trace identified local homes rather than temporary-area spills. The
acceptance itself uses the stock canonical compiler, with no observer.
