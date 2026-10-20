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

- `func_83100DBC`: requeue. Sixteen source variants preserve or worsen the
  scroll handler. The best is 220 bytes but has a 40-byte frame instead of the
  target's 48-byte frame, plus operand/scheduling differences. Named live
  selection, scroll, button, and active-state values did not fix it. Investigate
  genuine source lifetimes; do not copy unrelated callbacks' unused result arrays.
- `func_831001A8`: longer selection/state lookup; not probed in this batch.
- `func_83101804`: requeue. Eighty recorded variants retain a best 768-byte,
  104-byte-frame candidate with 174/192 positional words exact, correct float
  spill homes, and an eighteen-word register-only residual. Derived text Y
  from the real ordinal fixed the cached-opacity home. Pixel-carrier and
  separator-bound variants did not improve it. A calibrated local search's
  lower scores required an unnecessary boolean-copy variable and were
  rejected. Continue genuine availability/count and live-range hypotheses;
  no candidate has been accepted for this owner.
- `func_8310065C`: layout prerequisite. Its `jtbl_83103998` remains outside
  the owner. Migrate the table and gate the still-assembly layout before
  attempting a C switch.
