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

## Move-details renderer requeue (`func_889035FC`)

The remaining owner draws move names, power/accuracy/type, PP values, and
the selected-row frame. Its best controlled candidate has the original
1284-byte size and 144-byte frame, with raw similarity 0.9626 and normalized
similarity 0.9813. It remains assembly; it is not an accepted C replacement.

A byte-sized move ID reproduces the distinct saved-register carriers used
by comparisons and narrow move-query arguments. Inlining the consumed
power and accuracy label lookups reproduces the frame size. The type-color
lookup writes a three-byte RGB destination and returns its address; making
that actual interface explicit preserves complete game fingerprints for
the helper and its existing formatter caller.
//@src/fragments/29/fragment29_166060.c
//@src/fragments/38/fragment38_1D8160.c

Forty-eight source variants cover move-ID widths, label lifetimes, cursor
reset/progression, coordinate grouping, and accuracy-result lifetime. The
remaining differences are loop scheduling, two caller-temporary stack
locations (92/96 versus retail 96/100), and coordinate-expression scheduling.
Next: inspect the retained best parent's local/temporary-area allocation
and expression provenance before further variants. A new diagnostic compiler
mode needs current known and exact-parent stock/blank/off/on/on-blank controls.
