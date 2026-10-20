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

`Fragment6_HandleAvailableListScroll` (`func_83100DBC`, 220 bytes) handles
scrolling at the visible list edges while the widget is active. Selection
below two and input mask 0x800 scroll upward if the offset is positive;
selection at least ten and mask 0x400 scroll downward while offset+10 does
not exceed the available-entry count. Each successful move plays sound 1
and returns handled. Other input delegates to `func_81805524`.

Selection and scroll are actual consumed locals declared before the handled
result, giving the target 48-byte frame and result home sp+36. The complete
upward condition includes positive scroll; this keeps selection live through
the scroll test for the downward eligibility check. Earlier nested conditions
and different local declaration order produced the wrong branch/register
shape or a 40-byte frame. No unused result record or frame padding is used.
The runner reports link-verified acceptance and the full US ROM comparison
passes. Frozen first-success objects and five whole-TU cleanup/name/blank
controls preserve every game byte, all 39 extents, and semantic relocations.

`Fragment6_DrawSavedEntryList` (`func_83101804`, 768 bytes) draws the saved
entries populated by `func_83100584` in this file. That producer gives
state+204 and capacity eight to `func_80062390`, then stores its count at
state+748. Each entry occupies 68 bytes. The renderer draws those strings at
origin+(59,39+26*row), highlights the one-based selection byte at state+63,
and rechecks selection after each string draw before restoring white.

A separately consumed nonempty flag selects texture/text style before the
text loop. Both loops use ordinary row ordinals: entries start at zero, and
the seven separator lines use rows one through seven. The compiler derives
the pixel induction and separator termination value 208. Reusing one ordinal
between the loops avoids an extra colored coordinate without dummy uses or
manual pixel-counter management. Weight remains at sp+88 and cached floating
opacity at sp+76 in the 104-byte frame. Text alpha is signed integer
255*weight; line alpha uses the actual byte-color rectangle interface.

The saved-entry prefix describes only verified fields and unknown byte ranges,
not the entire 756-byte state. Target-compiler layout controls verify selection
offset 63, entry offset 204, count offset 748, row size 68, and capacity eight.
SDK display-list setup and compiler-generated unsigned float conversion remain
ordinary C. The recorded sequential full-ROM gate and named-source final gate
are byte-identical to the US ROM. Existing fragment-4 alias spellings leave
the runner's link-shape diagnostic false; independent canonical-name comparison
verifies all game bytes, 39 function extents, and semantic relocations. Frozen
first-success artifacts and five whole-TU cleanup/name/blank/layout controls
cover the accepted source.

`Fragment6_DrawAvailableEntryList` (`func_83101400`, 788 bytes) draws ten
26-pixel-spaced rows from the available-entry mapping initialized by
`func_831000FC` in `src/fragments/6/fragment6_code.c`. That producer writes
available indices at state+172, fills unused slots with -1, and records the
count at state+203. The renderer combines each visible row with the scroll
offset at state+67. Position zero uses archive 44 string 31; positive
positions read the signed mapping at state+171+position, skip negative slots,
and map nonnegative indices to strings 32 onward. Selection at state+64 is
one-based. Active selection is yellow; string 62 has the original gray
fallback. The original negative-slot skip and subsequent sign-dependent
string mapping both remain in the ROM's control flow.

The renderer draws its black background at origin+(54,54), size 253 by 286,
using byte alpha 100*weight. Text uses signed integer alpha 255*weight.
The scroll offset is reloaded across callbacks before checking the upper
and lower arrow conditions. Its actual local carries both the table-index
calculation and the later arrow predicates. Declaring weight after the three
row-selection locals gives the target's 96-byte frame and sp+80 float home.
The display-list setup uses the SDK macro, and float-to-byte conversion is
compiler-generated.

The string-return declaration now agrees with `func_8004C874` in
`src/4CC20.c`: it returns `void *`. The existing message-panel caller keeps
its integer-encoded pointer interface through explicit casts. The recorded
runner installed these companion changes only with the accepted renderer.
The sequential full-ROM gate passed with MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. The runner's link-shape field remains false
because of existing fragment-4 alias spellings; independent canonical-name
comparison verifies all game sections, 39 function extents, and semantic
relocation targets/addends. Frozen first-success artifacts and five complete-TU
cleanup/name/blank controls verify the accepted source and interface changes.

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

- `func_831001A8`: longer selection/state lookup; not probed in this batch.
- `func_8310065C`: layout prerequisite. Its `jtbl_83103998` remains outside
  the owner. Migrate the table and gate the still-assembly layout before
  attempting a C switch.
