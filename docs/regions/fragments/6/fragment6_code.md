# Fragment 6 selection controls

## Accepted C mechanisms

`Fragment6_InitializeSelectionState` (`func_83101C80`, 244 bytes) clears the
756-byte state, retains the supplied setup address at offset 56, and calls
`WidgetState_Initialize` with the setup's signed controller byte and nine
widget definitions from `D_831038A0`. A nonzero setup byte at offset 12 enables
a nine-byte configuration copy from setup+4 to state+60. The mode assignment
chains the state bytes at offsets 31, 29, 28, and 30 from one read. A zero
setup mode selects mode 1 instead. The remaining calls initialize two random
timers, call `func_83100584`, populate the available-entry list through
`func_831000FC`, call `func_831001A8`, and position the list through
`func_83100E98` using the unsigned byte value of `D_8009F864`.

`Fragment6_DrawSelectionControls` (`func_83101244`, 444 bytes) copies the two
32-byte caption records and their sentinel from `D_83103168`. The data contains
archive 44 entries 0 and 1, followed by a negative archive/entry sentinel. The
copy is mutable: selecting `D_83102B4C` or `D_83102B64` enables blending for the
first caption; selecting `D_83102F64` enables it for the second. Inactive
selection groups are drawn separately. The copied records are accessed through
a pointer consumed by both the blend writes and `WidgetText_DrawRecordListWithSetup`.
The final text and texture use style 0 only in mode 4 with selection below 6;
otherwise they use style 2. `WidgetResources_DrawSelection` draws the active
selection afterward.

The record layouts follow their actual copy extents and consumers; they add no
runtime padding. Target-compiler checks establish a nine-byte configuration,
32-byte text records, a 96-byte caption/sentinel list, blend offset 16, and
style-pointer offset 20. The initializer preserves the existing integer-encoded
setup-address interface used by `func_831020D0`.

## Verification

Both owners passed the recorded native candidate runner and a byte-identical
US full-ROM comparison, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. The drawing
owner's sequential gate resolves its existing fragment-4 function aliases;
the object comparator initially reports the old/new alias spellings as
relocation drift. Independent whole-translation-unit checks normalize those
verified names and compare every game section, all 39 function extents, and
semantic relocation targets/addends. Cleanup, naming, blank-line, and layout
controls preserve that complete fingerprint. No instruction rewrites, dummy
locals, manufactured padding, or hand-unrolled loops are used by these owners.

## Remaining owners

- `func_83100DBC`: requeue. Sixteen source variants preserve or worsen the
  scroll handler. The best is 220 bytes but has a 40-byte frame instead of the
  target's 48-byte frame, plus operand/scheduling differences. Named live
  selection, scroll, button, and active-state values did not fix it. Investigate
  genuine source lifetimes; do not copy unrelated callbacks' unused result arrays.
- `func_831001A8`: longer selection/state lookup; not probed in this batch.
- `func_83101400` and `func_83101804`: drawing owners with SDK display-list
  macro shapes; use the GBI macros for their actual commands.
- `func_8310065C`: layout prerequisite. Its `jtbl_83103998` remains outside
  the owner. Migrate the table and gate the still-assembly layout before
  attempting a C switch.
