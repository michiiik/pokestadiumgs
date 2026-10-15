# Fragment 16 drawing and selection input

## 2026-10-15 — five-owner native batch accepted

All five selected owners are matching C: 319 instructions / 1,276 bytes.
The file moves from 11 C + 19 ASM owners to 16 C + 14 ASM owners. Work was
solo/native, without agents or containers; source installs used the normal
runner with persistent statistics and host checks enabled.

| Owner | Name | Instructions / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_82000C00` | `Fragment16_DrawFadingOverlay` | 44 / 176 | 0x20 | `31dfb6013e57475cbd73ae3c70f0ea28` |
| `func_82000FB0` | `Fragment16_DrawVersionStamp` | 67 / 268 | 0x38 | `37635d36a46147268b520026a2dc1d79` |
| `func_820010BC` | `Fragment16_DrawSelectionList` | 71 / 284 | 0x50 | `adb29898ba9e413d9d940964c3bd292d` |
| `func_820011D8` | `Fragment16_DrawSelectionPopup` | 75 / 300 | 0xB0 | `37635d36a46147268b520026a2dc1d79` |
| `func_82001590` | `Fragment16_HandleSelectionInput` | 62 / 248 | 0x20 | `37635d36a46147268b520026a2dc1d79` |

Version stamp, popup and input passed a combined link-verified ROM gate in
the first forty-candidate batch. The list passed a second combined
link-verified gate. The overlay's pair view changes a relocation spelling,
so its probe is relocation-masked and **not** raw object-link verified; one
successful **sequential full-ROM gate** establishes its acceptance.

### Source mechanisms and naming evidence

- **Overlay:** the positive-alpha guard reads the second halfword of the
  existing four-byte record at `D_82001EA4`. The environment-color command
  reads the already-existing `D_82001EA6` symbol at the same address. This
  preserves the two target address calculations, rather than caching one
  scalar address across both uses. No new field alias or storage is added.
  After acceptance, a typed four-byte counter/alpha declaration replaced
  the pointer cast, with exact whole-object controls. Resource 0x13D, stored
  coordinates, alpha masking and draw arguments 1/0 are preserved.
- **Version stamp:** the existing format is `%s/%s %s:%s version`. Four
  signed-byte buffers retain the original four-byte stack slots; copy two
  bytes apiece and terminate them, stripping a leading zero only from the
  first two groups. Plain `char` emits `lbu` instead of the target `lb`;
  three-byte aggregate buffers shift the addresses. Keep `s8[4]` locals.
- **List:** declare the loop index before the two three-byte RGB records.
  That restores stack offsets 0x48/0x44 without changing frame 0x50. The
  pointer walk and carried row coordinate preserve all five saved-register
  roles. Draw nineteen localized entries, yellow selected / white others,
  from (120, 50) in twenty-pixel steps, inside the existing gradient panel.
- **Popup:** obtain the optional localized name before initializing the
  nested-scope color copies. Keep the explicit measured width and 128-byte
  formatting buffer; panel width is text width + 40. Both final text-draw
  branches are present in the original ASM, even though their visible call
  arguments agree. They are observed target control flow, not diagnostic
  empty branches, and are retained. Named/numeric formatting paths remain.
- **Input:** update the global selection directly, with independent left
  and right repeat tests and wraparound. Retaining writes between tests
  matches; a cached local committed once does not. Preserve change sound 1,
  confirm result/sound 1/2, cancel result/sound -1/3, and cancel priority if
  both buttons are pressed. Reload the controller pointer after sound calls
  as required by the oracle. Typed input-view experiments are not retained.

Names describe these assembly-observed operations without claiming a more
specific menu identity. The naming tool preserved original address-keyed
symbols and added five compatibility aliases. Caller-name propagation stays
within this source file; generated assembly is not published.

### Verification

- Before candidates: file brief and sibling-family report read; history
  checked against native and older statistics; no existing file claim.
- Native baseline: all linked sections and four existing C siblings reproduce
  under stock IDO 7.1. A stock 5.3 control gives no overlay improvement and
  changes the accepted list and popup; keep this file on normal stock 7.1.
- Five normal runner acceptance records and their ROM gates: PASS.
- Duplicate-extern cleanup with the repository's verified cleanup tool:
  PASS. Added the established `_bcopy` prototype; removed unused input type,
  redundant declarations and draft variable names. No compiler flag change,
  padding directive, fake test, new helper function or forced object.
- After cleanup/naming, fresh and twenty-leading-blank whole-TU controls:
  all four section byte views and allocatable sizes/types/flags preserved;
  all thirty original function offsets and sizes preserved; all five
  accepted spans and all twenty-five untouched C/ASM spans unchanged.
- Forced normal ROM build without compiler override, repeated after rebase:
  complete retail equality, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
- Explicit whole-TU host syntax check: PASS with four pre-existing implicit
  declaration warnings outside the new functions. Public tooling discovery:
  22 tests PASS. Diff check: PASS. Exactly five removed pragmas have normal
  full-gate acceptance provenance.

### Remaining work

The selected five-owner batch is closed, but fourteen owners remain ASM.
Re-run owner history and inspect their actual assembly before the next
batch. In particular, the small reset functions have shared-`$at` store
sequences; fresh ranking alone does not establish that the coalescing shape
is ready. `func_8200182C` has a jump table without its per-file rodata
prerequisite. Do not treat those as ordinary fresh scalar wrappers or claim
that this batch completes the file or the repository.
