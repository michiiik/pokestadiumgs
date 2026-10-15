# Fragment 16 drawing and selection input

## 2026-10-15 follow-up — lifecycle and list input accepted; two active requeues

Two of the next four selected owners passed normal **link-verified combined
full-ROM gates** under stock IDO 7.1. The file now has 18 C + 12 ASM owners.
The other two selected owners remain ASM and active, not counted as solved.

| Owner | Name | Body instructions / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_820016EC` | `Fragment16_HandleListInput` | 72 / 288 | 0x20 | `6829f6d7957c4ca3940d3a3975ce7294` |
| `func_82001ADC` | `fragment16_main` | 75 / 300 + 8 alignment | 0x28 | `66e68878f4b048d5a78411418d9d5b2d` |

The list handler keeps the flags-first short circuit, independent vertical
repeat tests, 19-row wraparound, change sound 1, confirmation mask 0x9000 /
sound 0x32 and the existing cancellation predicate. Assign the local result
before storing -1 to the global selection on cancellation; reversing these
statements produces the sole original two-instruction ordering difference.
Winning label:
`f16-flow:list-input:flags-first-True:prefix-True:nested-cancel-True:result-before-store`.

The fragment entry preserves its incoming argument stores, TITL pool-state
scope, graphics/stage setup, resource loads, segment load, frame loop,
teardown and packed-result call. Apply the segment mask **before** shifting
the symbol address; shift-first source loses target instructions. Winning
label: `f16-flow:main:pointer-False:mask-first-True:return-local-False`.
Its C body is 300 bytes; the original 308-byte ASM span includes the eight
zero alignment bytes at ROM 0x10F078..0x10F080. Natural compiler alignment
supplies them. No padding directive or padding helper is needed.
The entry's canonical name comes from the existing naming database and
fragment-header trampoline; the input name describes its observed behavior.
Original address symbols and compatibility aliases remain.

### Verification and publication

- Fresh baseline and twenty-leading-blank controls reproduce the previous
  five matches and the remaining original object before the next batch.
- Both normal link-verified acceptance gates: PASS. Persistent statistics
  and host checking remain enabled. No manual candidate installation.
- After naming, verified extern cleanup and removal of unused probe-only
  declarations: fresh and twenty-leading-blank whole-TU controls preserve
  every linked section byte view and allocatable layout, all thirty original
  function offsets, both accepted full spans, and all twenty-eight untouched
  C/ASM spans. The only symbol-size change is the entry's C body versus its
  original alignment-inclusive ASM size; its complete span stays identical.
- Forced normal build without compiler override, repeated after rebase:
  full retail ROM equality, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
- Explicit whole-TU host syntax check: PASS. Four implicit-declaration
  warnings predate this batch; the entry additionally has two unused-argument
  warnings, with those arguments retained to reproduce the original stores.
  Public tooling discovery: 22 tests PASS. Diff check: PASS.
- Only source, two compatibility aliases and these region notes are
  published. No scratch helpers, compiler changes, generated assembly,
  objects, ROMs or unverified C. Solo/native; no agents or containers.

### `func_82001A78` — requeue, inactive return-tail coalescing

Best clean source has 100/100 bytes, 0.9600 normalized / 0.9200 raw. The
active result packing is exact after using a compound OR and an immediate
return. In the inactive path, target initializes `v1` to zero then returns
it with `or v0,v1,zero`; the candidate initializes `v0` directly and ends in
`jr ra` / `nop`. These are two real word differences, not acceptance.
Leader label: `f16-flow:pack:return-topology-compound:unsigned-False`.

The source shape is: if the list is visible, build the low-byte list index
in bits 8..15, set bit 1, OR the low-byte selection in bits 16..23 and return
it; otherwise initialize the result to zero, return 1 when the index is -1,
and return the initialized result on the other path.

Negative families: common versus immediate returns, OR expression versus
compound assignment, signed/unsigned locals, `int` versus `s32` locals,
register hints, status assignment/increment, old-style declarations and a
properly paired `int` return/prototype transaction. `s32` is `long` in these
headers: plain-int definitions initially conflict with the long prototype;
correcting that transaction compiles but does not close the residual.
A calibrated 45-second permuter remains flat at score 105; no fake source
is adopted. Stock controls for this same clean body give two differing words
with 7.1 versus thirteen with 5.3; do not switch the file's compiler.

Next: trace or inspect the stock 7.1 return/coalescing decision on this clean
leader, with a known exact sibling control. Distinguish source-level return
shape from allocator behavior before generating another family. No claim
of unreachable C or general compiler defect is established.

### `func_82001344` — requeue, scroll-coordinate load/store shape

Best signed-coordinate source is 0.9583 normalized / 0.6771 raw, 380 versus
384 bytes. The oracle loads the scrolling word into `v1` and rematerializes
store addresses; the candidate retains its address in `v1`, loads its value
through temporaries and has one fewer instruction. This is an internal
load/store-shape residual, not a missing tail nop. Leader label:
`f16-flow:scroll:early-return-False:point-False:local-scroll-False`.
Future batches need `extern s32 D_82001D00;` plus the established rectangle /
scissor prototypes; unused declarations from these failed probes were removed
from the published file. The leader uses the existing two-halfword coordinate
view at `D_82001EB8`, signed width/height and the existing text helpers.

Negative families: early return versus outer guard, point/array coordinate
views, local versus direct scroll updates, compound conditions, expanded and
associated assignments, reuse of the drawing-X carrier, and `int`/long local
combinations. Reusing X changes frame 0x30 to 0x38 and is not retained. A
paired unsigned-global diagnostic reaches 384 bytes and 0.6875 raw but adds
an unwanted width reload; it neither matches nor installs, and the global
type transaction is rolled back. Stock 5.3 gives the same 380-byte size and
forty differing positional words as 7.1 for the signed leader.

Next: inspect the address-versus-value commoning at the 7.1 compiler boundary
or test an evidence-backed data-record view. Do not repeat the failed tail
families, force registers or add padding to hide the internal mismatch.
Both requeues remain ahead of fresh-owner rotation; this publication merely
ships verified progress without holding it behind the remaining work.

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
