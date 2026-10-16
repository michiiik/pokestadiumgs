# Fragment 44 record collection and menu callbacks

## 2026-10-16 — input navigation accepted

`func_8AF133C0` is now matching C: **214 instruction words / 856 bytes**,
with its original **0x38-byte frame**. The file advances to **26 C / 12 ASM**
from 38 original functions. Solo native macOS, without agents or containers.

Acceptance: batch `c66f297a5de544f798132f1da5dd37b0`, candidate
`f44-menu-input-grid-declaration:form-3`: **link-verified**, one successful
combined full-ROM gate, 1.218 seconds. Earlier five-operand register ties are
closed, not accepted by normalized similarity or a permuter score.

### Source mechanisms

- Give the existing grid its real four-byte entry declaration (`kind`,
  palette index, unknown byte, blink flag). Keep the two accepted byte-stream
  builders using explicit byte views of that same storage. No new allocated
  data or callable helper is introduced.
- Read the selected entry as `entries[column + row * 4].kind`, and pass its
  actual field address to the refresh routine. The real global record type
  plus `&entries[column + row * 4].kind` closes the final five operands.
  Casting a byte-array declaration to a record pointer was not equivalent
  compiler context; flat byte-address forms retained the register mismatch.
- Model the existing scroll state as seven shorts (14 bytes), consistent
  with the original initializer and scroll callees. Direct aggregate copy
  preserves the aligned three-word plus halfword copy; casts from a byte
  declaration instead caused unaligned operations. The initializer's bzero
  gets its required word-pointer view without changing any instruction.
- Preserve the mutually exclusive A/B/horizontal/vertical input branches,
  repeat versus held-button selection, rereads after the sound call, and
  row/column-change refresh. No fake locals, padding, dead reads, return-type
  trick, compiler patch, or verification bypass.

### Verification and the failed hypotheses

Fresh and twenty-leading-blank complete-TU recompilations preserve the frozen
accepted object, loadable section layout and all relocation rows. All 38
original starts/sizes are unchanged; all 37 untouched raw function bodies
match the 25-C baseline, including both builders and the scroll initializer.
A strict canonical link resolves every external from the normal ROM ELF and
checks the complete 19,264-byte text and 240-byte readonly windows against
both that ELF and immutable retail bytes. No additional data/bss storage.

After cleanup, forced normal native `gmake rom COMPARE=1` passes retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. All 46 native tests pass; host syntax
passes with three unrelated pre-existing warnings (one initializer pointer
warning removed). Evidence-backed naming has no mapping for this owner.

IDO 7.1 stock/diagnostic-off/on/leading-blank full-object calibration passed
for the baseline and five-operand parent. Its residual values were allocated
by UGEN's temporary free list, not colored global-register webs. Unsigned byte
offsets, equivalent refresh predicates, natural logical-line regrouping and
explicit coordinate snapshots did not close the tie. The diagnostic compiler
and scratch campaigns are not publication artifacts. A data-companion
preflight limitation required applying the two byte-view edits before the
struct retype; the resulting whole-file transaction was independently proved
unchanged before testing the input body. No guard was bypassed.

### Remaining drawing owner

`func_8AF13718` remains **requeue**, not installed. Four-byte color-array or
separate RGBA/packed-word views reproduce its unaligned palette copy and three
aligned selection-node stores. Right-bound-before-bottom-bound source order
restores the original width/height temporary ordering; an explicit nested
blink test restores the original branch polarity. Real clip snapshots and
coordinate widths affect frame and saved-register roles but have not matched.
The best opcode-shaped proposal is 1,044 bytes, versus 1,048 including the
original trailing alignment nop; it still has genuine frame/operand/schedule
differences. Do not pad those away. Its earlier raw-byte-grid candidates need
revalidation after the now-accepted global entry type before another search.

## 2026-10-16 — input and grid drawing requeues

Historical pre-acceptance handoff, superseded for input navigation above.
At this point neither owner was installed (25 C / 13 ASM). These measurements
use the post-PR1066 context before the accepted global grid declaration.

- `func_8AF133C0`: **requeue / register-tie**, 856 bytes, frame 0x38.
  The best candidate has all 214 opcode positions correct and 209/214 raw
  instruction words identical. The first 188 words are exact; the only five
  differences are register operands in the final selected-entry address
  calculation, beginning at word 188. Matching size and normalized 1.0 are
  not acceptance. Preserve the original assembly owner.
- The input candidate needs a genuinely typed 14-byte scroll-state aggregate
  (seven shorts): casting an existing byte declaration causes unaligned
  copies. A non-installing whole-file companion-declaration control preserves
  all 38 original spans, frozen loadable sections and relocations, all 19,264
  linked text bytes and 240 readonly bytes against the retail ROM, including
  twenty-leading-blank recompilation. It does not authorize installing the
  unmatched input body or the companion edit on its own.
- For input, use a mutually exclusive button chain, a word-sized pressed
  carrier, and measured local ordering. Model entries as four-byte records
  with byte fields `kind`, `palette`, an unknown byte, and `blink`. The two
  selection loads use `entries[column + row * 4].kind`, but the refresh
  argument must remain a byte-address expression. Row-first record indexing
  and two-dimensional indexing are not interchangeable compiler shapes.
  Preserve rereads after the sound call and all original calls.
- There are 88 cumulative normal rejected input probes, plus eight failed
  companion transactions that compiled nothing. Native declaration synthesis
  duplicates the old byte declaration unless the new declaration is included
  in shared declarations. Two independently calibrated 60-second no-fake
  permuter searches measured 625 to 435 and then, after the real type-context
  improvement, 40 to 40. The first search's narrowing cast and the second's
  equal-score wide cast are not validated fixes. Simple final-expression
  regrouping and reusing dead pressed/changed words did not close the five
  operands. Next: examine the final expression's allocator reservation and
  real consumed index lifetimes; do not replay earlier body spellings.
- `func_8AF13718`: **requeue**, 40 normal rejected probes. All original calls
  are present. Best normalized similarity is 0.9771 (raw 0.5611): the word-row
  candidate is 1,040 bytes with frame 0x78, versus 1,048 / 0x80 in the ROM.
  Narrowing the row happens to restore total size but adds instructions and
  does not establish the original shape. Separate clipping snapshots,
  byte-sized blink alpha, real clip bounds, packed-word versus RGBA copies,
  union color access, typed node fields and x/y statement order have been
  tested, not accepted. Next: resolve the genuine color aggregate alignment
  and viewport-bound lifetimes. The original copies palette RGBA through
  unaligned word operations into a four-byte local, changes alpha to 255,
  then makes three aligned word stores to the selection nodes. Do not add
  dummy locals, padding, fake branches or compiler changes to obtain 0x80.

## 2026-10-16 — page initializer accepted

Solo native macOS, without agents or containers. The larger original
`func_8AF10D08` initializer becomes matching C: **404 words / 1,616 bytes**,
with its original **0x28-byte frame**. The file advances from **24 C / 14
function ASM to 25 C / 13 function ASM**, out of 38 original functions.
The prior batch's 240-byte readonly window is reused without another layout
change. No new callable helper, allocated data or compiler change.

Acceptance batch: `7c474251e4ec49ec85838005abc61e28`, candidate
`f44-page-init-exits:grouped-False:goto-True:early-False`. The normal runner
accepted it after **one successful sequential full-ROM gate**. Its isolated
probe was relocation-masked, **not** `link_verified`: the table and literal
references are expressed as section-relative addends in the containing object.

### Source mechanisms

- Preserve all **48 original calls**, including the 22 keyed record lookups,
  seven callback attachments, four text-record initializations and three
  visibility resets. The private candidate generator checks the complete
  call inventory against assembly before probing. Existing C definitions
  and remaining callee assembly establish the parameter/return contracts;
  no unused-call return category is changed to influence allocation.
- Reuse the consumed page handle for the title page. Separate handle and
  callback temporaries enlarge the frame. Direct repeated `0.01f`/`0.6f`
  expressions reproduce the original literal pools without the source homes
  charged to two real floating temporaries.
- Keep each mode's original global-store order. The selected record is not
  always the first global written. Correcting that order preserves the
  original address setup and improves the switch residual independently of
  the frame fix.
- Use three genuine `goto scale` exits from the updating cases to the shared
  scale-update block, plus an explicit default. An ordinary break-only exit
  emits a 1,612-byte function with a different shared-address setup; the
  explicit shared exits restore the original 1,616-byte control-flow shape.
  Combining the no-op mode-zero/default labels after acceptance preserves
  the frozen object exactly. There are no fake conditions, artificial locals,
  forced registers, padding or manually unrolled loops.

Fresh and twenty-leading-blank full-TU rebuilds preserve the frozen accepted
object's loadable sections, layout and every relocation row after formatting
and duplicate-extern cleanup. All **38 original spans** and **37 untouched
raw function bodies** remain unchanged. Separate strict canonical linkage,
with every undefined name resolved and no unresolved-symbol suppression,
proves all **19,264 containing text bytes** and all **240 table/literal bytes**
identical to both the normal ROM ELF and immutable retail ROM. Exactly this
one function pragma is removed, with accepted statistics provenance.

Forced normal `gmake rom COMPARE=1` passes, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Edited-TU host syntax passes with the
same four pre-existing pointer warnings; all 46 native tooling tests pass.
Naming plan/apply finds no evidence-backed mapping, so the address name stays.
Scratch generators, controls, objects, compiler binaries and ROMs remain local.

Process evidence: a proposed unchanged leading-blank runner control was
refused at preflight before compilation. It consumed no hypothesis budget
and was not disguised for replay. A separate non-installing fresh/blank
object calibration verified deterministic sections and relocation rows before
the distinct line-layout probes; those probes did not close the exit-path
residual. The renderer, drawing callbacks, section-builder and padding
requeues below remain unresolved and in assembly.

## 2026-10-16 — narrow switch-table layout and three menu routines accepted

Solo native macOS, without agents or containers. Three original assembly
owners become matching C: **268 words / 1,072 bytes**. This file advances
from **21 C / 17 function ASM to 24 C / 14 function ASM**, out of 38 originals.
No new callable helper, data allocation, compiler patch or artificial padding.

| Owner | Behavior | Bytes | Frame | Acceptance batch |
| --- | --- | ---: | ---: | --- |
| `func_8AF1000C` | Update page colors and handle the page transition | 592 | 0x28 | `eb3d28b93e21432399f3eae3f296c128` |
| `func_8AF1025C` | Map the page mode to its texture width | 80 | 0 | `043f41b88f9d44b88db81a69940b69ad` |
| `func_8AF102AC` | Draw the page texture in its original slice sizes | 400 | 0x40 | `fc4aaf51a55540a8accd5132d9c7d8b4` |

### Layout prerequisite, verified before replacing assembly

Add only **ROM 0x217840..0x217930**, a 240-byte, 16-aligned `.rodata`
subsegment for this file, followed by a `rodata`-typed shared tail. An audit
found 16 symbols in this window, each exclusively referenced by one of five
still-assembly owners in this TU. They are jump tables and floating literals,
in function order; no existing accepted C or debug string must be migrated.
The assembly-only full-ROM comparison passed before the first C probe.

Do **not** use the planner's broader 0x217750..0x217A20 proposal: it contains
debug strings and existing C's externally named strings on both sides of
the late tables. Earlier `jtbl_8AF29598`/`jtbl_8AF295B4`, used by
`func_8AF0F2EC`, remain outside this window. The new layout also prepares
`func_8AF10D08` and `func_8AF113D8`; neither is decompiled by this batch.

### Source mechanisms and acceptance

- Preserve the page dispatcher's full 13-call color-update inventory and
  original case/body order. Its signed halfword result starts at 12 after
  the initial call and becomes 10 on the successful transition. The normal
  runner reports a link-verified, combined-gate acceptance. The first eight
  incomplete drafts omitted one call and are not compiler-family negatives.
- For the width map, use a signed halfword parameter and assign `-1` in
  the explicit default arm, returning the shared result. Initializing the
  result before the switch changes scheduling. Recover grouped case values
  from the original table, not from a plausible mode numbering.
- The texture renderer keeps real word-wide row and byte-count cursors plus
  a separate advancing texture pointer. After 32 ordinary cells, their best
  residual was constant-limit setup order. Eight token-identical line-layout
  probes isolated source-line-sensitive scheduling: grouping the complete
  function on one logical line closed it. The final readable spelling uses
  standard backslash continuations to preserve that same logical line, and
  was rebuilt against the frozen accepted object. No fake statements, unused
  locals, forced registers or manually unrolled loops are involved.

The width map and texture renderer are relocation-masked sequential-gate
accepts, **not** raw probe link-verified results. Each passed one full-ROM
gate. A separate strict canonical link resolves every undefined symbol from
the normal ROM ELF with `--no-undefined`; all **19,264 containing text bytes**,
all **38 original function spans**, and all **240 table/literal bytes** agree
both with that ELF and directly with the immutable retail ROM. No unresolved
symbols are suppressed. Fresh and twenty-leading-blank rebuilds preserve the
frozen object's loadable sections, layout and every relocation row after
formatting and duplicate-extern cleanup. All three owners have accepted
probe-statistics provenance and exactly these three pragmas are removed.

Forced normal `gmake rom COMPARE=1` passes, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Edited-TU host syntax passes with four
pre-existing pointer warnings; all 46 native tooling tests pass. Naming
plan/apply finds no evidence-backed mappings. Only source, layout, findings
and generated coverage are published; scratch helpers, extraction artifacts,
objects, compiler binaries and ROMs remain local. Older callback, section
builder and padding requeues below remain unresolved, not silently skipped.

## 2026-10-16 — grouped-list builder and record-information panel accepted

Solo native macOS, without agents or containers. Two larger original owners
become matching C: **381 words / 1,524 bytes**. The file advances from
**19 C / 19 function ASM to 21 C / 17 function ASM**, out of 38 originals.
No new callable helper, allocated data, compiler patch or artificial padding.

| Owner | Behavior | Bytes | Frame | Acceptance batch |
| --- | --- | ---: | ---: | --- |
| `func_8AF127E8` | Build grouped menu records and heading text | 528 | 0x28 | `0f59f764598349ab80dc0d59493de0f0` |
| `func_8AF12A4C` | Update record information, rates and detail controls | 996 | 0x28 | `db91922329bd4dd49877b7c26e6e4317` |

Both normal-runner accepts are `link_verified`, each with one successful
combined full-ROM gate. Fresh and twenty-leading-blank full-TU rebuilds
preserve the frozen accepted object's loadable sections, section layout and
every relocation row. All **38 original function spans** and **36 untouched
bodies** agree with the prior 19-C baseline. Exactly these two function
pragmas are removed; both have accepted probe-statistics provenance.

### Source mechanisms

- The grouped-list builder needs the original two-case `switch`, not an
  equivalent `if` chain: the chain loses one address-setup instruction and
  changes branch layout. A real signed 32-bit counter with `i != 9` and
  `i != 7` reproduces both mask loops. Preserve separate heading/detail
  lookups, the negative-selection fallback and the existing table strides.
- The information panel shares a real word-wide `texture_index = id - 1`
  across the two texture controls. Recomputing the expression at each store
  emits the same operation sequence but allocates a 0x20 frame rather than
  the original 0x28. A halfword carrier does not fix that layout. The saved
  rate remains an actual byte; widening it emits the wrong store/load width.
- Preserve both original rate-getter calls and multiply-before-divide
  single-precision rounding. Changing to divide-before-multiply is not an
  instruction match. The redundant scratch casts were removed, duplicate
  externs cleaned up, and the final source re-proved against the frozen hit.
- Existing getter definitions in `src/638E0.c` establish their `u8(u8)`
  contracts. Keep full-width flag complements; the original stored bits and
  repeated global pointer loads remain intact.

Forced normal `gmake rom COMPARE=1` passes with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Edited-TU host syntax passes with the
same four pre-existing pointer warnings; all 46 native tooling tests pass.
The naming tool finds no existing evidence-backed mapping for either owner.
Scratch generators, objects, traces, proprietary compilers and ROMs stay local.

Callback **requeue**: a bounded two-field point-aggregate experiment adds
eight distinct cells each for `func_8AF10570`, `func_8AF1060C`,
`func_8AF106A8` and `func_8AF10784`. None matches. The three straight draw
callbacks still place their coordinate pair at stack +0x2C rather than
+0x24; narrow point fields do not repair it, and widening coordinate
carriers changes scheduling/registers. Retain the earlier array-form
leaders and investigate actual local-home/lifetime evidence next, rather
than repeating declaration permutations or adding fake storage. Section and
padding requeues documented below remain unchanged and in assembly.

## 2026-10-16 — four menu-detail, flag and text-bank routines accepted

Solo native macOS, without agents or containers. Four original assembly
owners become C: **347 words / 1,388 bytes**. This file advances from
**15 C / 23 function ASM to 19 C / 19 function ASM**, out of 38 originals.
No new callable helper, data allocation or compiler change.

| Owner | Behavior | Bytes | Frame | Acceptance batch |
| --- | --- | ---: | ---: | --- |
| `func_8AF0F040` | Update record-detail text and category labels | 352 | 0x30 | `e73cb423e36f4fdb8e930632de863194` |
| `func_8AF10840` | Clear the visibility flag on six existing records | 124 | 0 | `32906cce1ad24f8ebc3297ebed4f68e6` |
| `func_8AF10944` | Reset colors and highlight the selected record | 372 | 0x18 | `e5ee4394f4d643debf75ddd02ff8ec17` |
| `func_8AF10AB8` | Initialize nine banks of text records and colors | 540 | 0x38 | `1b8bf191ebb44866845839fbb10e5adb` |

Each normal-runner acceptance passed one full-ROM gate. The first three
are object link-verified combined-gate accepts. The initializer is a
relocation-masked sequential-gate accept: IDO represents the bank endpoint
as `D_8AF30158 + 0xEA0`, exactly the original `D_8AF30FF8` address. A separate
strict canonical link resolves every undefined name from the normal ELF
and proves the complete containing text, all **38 original functions**,
byte-identical to the assembly-backed baseline. No unresolved symbols are
suppressed, and no probe-only result is counted as acceptance.

### Source mechanisms

- Preserve the detail callback's signed record-index snapshot and real
  word-wide `index - 1` lookup shared by three string-table calls. Its two
  mapped category bytes and saved first string pointer reproduce the original
  stack homes without artificial locals. Keep the original mapping-call order.
- Clear flags with full-width complements `~1` and `~2`, not truncated
  `0xFFFE`/`0xFFFD` literals. The final halfword bits are equivalent, but the
  intermediate expression width changes IDO's temporary allocation. This
  mechanism matched two routines in this file; it is not a cross-file rule.
- Declare the existing color objects as four actual RGBA bytes and copy the
  aggregate directly. Alignment-losing pointer casts generated ten extra
  unaligned source-load instructions. The destination fields remain genuinely
  unaligned and retain their original paired stores.
- The text initializer uses a real descriptor cursor plus indexed bank loop.
  The signed inner `i < count` test already skips nonpositive counts; an
  additional positive guard emitted a redundant branch. Let IDO perform the
  original four-way unrolling rather than spelling it by hand. Initializing
  the descriptor before the outer loop preserves address setup order.

After formatting and duplicate-extern cleanup, fresh and twenty-leading-blank
builds reproduce frozen sections, layout and every relocation row. All **38
original spans** and **34 untouched bodies** are preserved. Forced native
`gmake rom COMPARE=1` passes, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Edited-TU host syntax passes with four
pre-existing pointer warnings; all 46 native tooling tests pass. The naming
tool finds no existing evidence-backed mappings, so address names remain.
The RGBA type describes existing storage; it defines no additional data.
No fake condition, padding, volatile, forced register or provenance bypass.

The section builder remains a **requeue** after eight new early-continue
variants: no full match. The padding helper also remains a **requeue** after
eight real output-alias variants; its closest new body is 156 bytes versus
the original 152, with different bound/register choices. Neither replaces
its assembly. Scratch generators, traces, objects, compilers and ROMs stay
local and are not included in the PR.

## 2026-10-16 — category-filtered collection accepted

Solo native macOS, without agents or containers. `func_8AF125D0` becomes
matching C: **83 words / 332 bytes**, with its original **0x38-byte frame**.
This file advances from **14 C / 24 function ASM to 15 C / 23 function ASM**,
out of 38 originals. No new callable helper or data allocation.

Acceptance batch: `523529ea9b704e62a730680d10f4312d`, candidate
`f44-menu-kind-filter-indexed:narrow-False:less-False:global-True`.
The normal runner accepted it after **one successful sequential full-ROM
gate**. The isolated probe was relocation-masked, not `link_verified`:
the compiler expresses the input endpoint as the input-array symbol plus
250 instead of the separately named marker. A separate strict canonical
link resolves every undefined name from the normal ELF and proves the
complete containing text, including **all 38 original functions**, identical
to the assembly-backed baseline. No unresolved-symbol suppression is used.

### Source mechanism

Use a real `s32` index into the global 250-byte input array, with
`index != 250`. IDO strength-reduces this into the original pointer walk;
keeping an explicit input/end pointer pair produced the same operations but
the wrong saved-register allocation and pointer-add order. Preserve the two
real early-continue guards after mapping the ID: first exclude ID 0xA5,
then reject nonmatching categories. Moving those tests before the mapping
calls would change the original call behavior.

The signed halfword ID and separate unsigned halfword snapshot retain the
original call-argument and stored-ID carriers. All locals have real uses;
there are no empty conditions, artificial arrays or forced registers.

The input's extern becomes `u8[250]`, supported by the accepted collector's
250-entry limit and the original endpoint-address difference of 0xFA.
The existing mask filter now takes its start pointer directly from that
array. These are declarations of existing storage, not additional data.
The candidate, array declaration and accepted-caller adjustment were probed
and installed in the same transaction.

After formatting and removing redundant externs, fresh and twenty-leading-
blank builds reproduce the frozen accepted object's complete sections,
layout and every relocation row. All 38 original spans and the 37 untouched
function bodies are preserved. Forced normal ROM comparison passes, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`; edited-TU host syntax passes with four
pre-existing pointer warnings; all 46 native tooling tests pass. The naming
tool finds no evidence-backed public mapping, so the address name stays.

The adjacent section builder remains a **requeue**: its 296-byte leader has
the original 74-operation sequence but swapped input/output saved registers.
A real scan/emission cursor split fixes its first 33 words but adds a move
and grows it to 300 bytes. Neither is accepted. The renderer and callback
residuals below also remain unresolved. Scratch generators, traces, compiler
binaries, objects and ROMs remain local and are not part of the PR.

## 2026-10-16 — three native matching routines accepted

Solo native macOS, without agents or containers. Three existing assembly
owners become C: **134 words / 536 bytes**. This file advances from
**11 C / 27 function ASM to 14 C / 24 function ASM**, out of 38 originals.
No new callable helper, data allocation, layout change or compiler patch.

| Owner | Behavior | Bytes | Frame | Full-ROM acceptance batch |
| --- | --- | ---: | ---: | --- |
| `func_8AF0F1A0` | Collect indexed record positions | 128 | 0x28 | `90ffb797fdef41b4aa13cbc6e3d83be6` |
| `func_8AF0F220` | Recursively collect three-byte evolution entries | 204 | 0x30 | `159a50c71150453d8b73c4949bc2fe42` |
| `func_8AF1271C` | Filter IDs into four-byte output records, then pad | 204 | 0x30 | `6885a4aac1c442129ddb323bbbc9db1f` |

All three are **link-verified** normal-runner accepts, each passing one
combined full-ROM gate. No provenance or host-syntax bypass is used. The
naming tool finds no existing evidence-backed mappings for these owners;
their address names remain rather than introducing speculative public names.

### Source mechanisms

The position callback must declare its signed index before its two-halfword
position array. The original offset/coordinate additions, not their
commuted spellings, give the expected temporary allocation. Preserve the
unconditional record-index snapshot and the mode-zero/mode-one guard.

The recursive collector follows three-byte entries until their first byte
is zero. Preserve the incremented signed global index snapshot, ID store,
three-byte aggregate copy and recursive call before advancing the input.
An explicit infinite loop with a top-of-loop exit matches the original
branch layout; an ordinary `while` rotates the load/exit and is one word
longer. The aggregate has three actual byte fields and no padding member.

The filter needs a real word-wide ID, not a byte local: narrowing only at
the verified byte-argument call preserves the original normalization. A
separate destination carrier fixes its saved-register allocation. Keep the
prologue on one logical source line and both endpoint assignments on the
same physical line; backslash splices make the prologue readable without
changing IDO's measured instruction schedule. Advance the destination
before incrementing the signed-halfword count. Every local has a real use.
The callee declarations retain the actual `u8(u8)` and `s16(s16)` contracts;
no return-type mismatch is used to manufacture instructions.

After formatting and removal of redundant/unused externs, fresh and
twenty-leading-blank builds reproduce the frozen accepted object's entire
text/rodata/data/bss, section layout and every relocation row. All **38
original function spans** and **35 untouched bodies** are preserved. The
forced native full-ROM comparison passes, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. The edited TU passes host syntax with
four pre-existing pointer-type warnings; all **46 tooling tests** pass.
Scratch generators, controls, objects, compiler binaries and ROMs stay local.

### Unresolved adjacent owners

- `func_8AF10570`, `func_8AF1060C`, `func_8AF10784`: **requeue**, 32 cells
  each. Ordinary signed-coordinate variants have exact opcode sequences,
  original sizes/frames, but place the position array at sp+0x2C rather
  than sp+0x24. Declaration order, real saved-record carriers, case-local
  arrays and an all-used coordinate aggregate do not close this. The
  word-coordinate aggregate reaches sp+0x24 but adds memory traffic;
  narrowing its members does not repair that. Next investigate the actual
  automatic-object lifetime/stack-home mechanism, not unused locals or
  artificial padding.
- `func_8AF106A8`: **requeue**, eight initial cells. Best has the correct
  220-byte size, normalized 1.0 / raw .9273, but the same position-array
  offset discrepancy. Preserve its real conditional drawing calls and
  signed y snapshot. It is not accepted.
- `func_8AF12410`: **requeue**, 24 cells. It fills only the first two bytes
  of each four-byte record with 0xFF, padding a positive signed remainder
  to a multiple of four. Natural loop bounds, parameter reuse and explicit
  signed normalization expose the original unrolled shape, but no cell
  matches. The 152-byte leader has normalized .9474 / raw .2632; matching
  size alone is weak evidence. Next resolve the signed remainder/bound
  carriers and real parameter home, not hand-written unrolling.

A stock-driver comparison preserves all eleven pre-existing C controls
under 7.1. Stock 5.3 changes two of them and worsens both the callback and
padding leaders; this does not justify changing this file's compiler.
Leading-blank controls are stable. This is a bounded negative, not proof
of an impossible source shape or a broken compiler.
## 2026-10-16 — grid drawing four-word requeue, not acceptance

`func_8AF13718` remains **requeue** and assembly. This continuation accepts
**zero** new functions. The unchanged production source remains 32 C / 6
function ASM out of 38 originals; its SHA256 is
`57402c73c73f6b998ad67da13fc698a529f91229e4f0aee7f62bee351d93d7f6`.
The improvement below is a measured partial source reconstruction, not a
normalized-score match, linked byte match, or full-ROM acceptance.

### Three real source mechanisms

1. Declare a consumed `s16 *limit` after the existing RGBA object and its
   two consumed pointer views. Initialize it to `&D_8AF316BA` before the
   row loop; use `*limit` in both row cutoffs. This reproduces the original
   `$t8` load and its two comparison temporaries. Reading the field directly
   through the seven-short scroll structure first demonstrated this gain,
   but the pointer to the actual halfword also preserves the original
   relocation reference. Moving the pointer declaration later restores the
   original frame `0x80`, color at `sp+0x54`, alpha byte at `sp+0x57`, row
   count at `sp+0x62`, bottom at `sp+0x64` and top at `sp+0x68`.
2. Represent each of the three actual packed-color transfers as a copy of
   a four-byte word aggregate, retaining the existing RGBA copy and alpha
   update. `struct MenuGridWordCopy { u32 value; };` is only a type view,
   not additional allocated storage. For example:

   ```c
   *(struct MenuGridWordCopy *)((u8 *)D_8AF3118C + 0x28) =
       *(struct MenuGridWordCopy *)color_word;
   ```

   Use the same view for that node's `+0x2C` and the other node's `+0x2C`.
   This restores the original temporary-register sequence through all
   three loads/stores, the flag updates, and the rest of the drawing body.
3. A typed clip-panel view, without retyping the production global, fixes
   one more clip-add operand order:

   ```c
   struct MenuGridPanelView {
       u16 type, flags;
       u8 header[4];
       s16 x, y, width, height;
   };
   ```

   A reviewed clip-only search then finds a useful, semantically valid
   reuse of the existing signed-short X before its later per-entry drawing
   definition:

   ```c
   x = ((struct MenuGridPanelView *)D_8AF31184)->x;
   row = ((struct MenuGridPanelView *)D_8AF31184)->y;
   left = x;
   x = left - 3;
   top = row;
   right = left + ((struct MenuGridPanelView *)D_8AF31184)->width;
   bottom = row + ((struct MenuGridPanelView *)D_8AF31184)->height;
   func_8AC0077C((s16)x, row, right, bottom);
   ```

   Keep the actual callee contract `void(s32, s32, s32, s32)`. Do not
   manufacture a narrow callee prototype to change caller code generation.
   No extra local, dummy read, oversized array, return-type change or forced
   register is used. This is evidence in this file, not a general heuristic
   validated across two different source files.

### Exact remaining words and section scope

Fresh and twenty-leading-blank builds of that uninstalled draft have the
same complete loadable sections, layout and relocation rows. A strict
canonical link resolves every undefined symbol from the normal ELF and
compares the entire 19,264-byte text and 240-byte rodata windows directly
against both the ELF and retail ROM. All 37 untouched raw bodies and their
original starts/sizes stay identical. The linked text differs only here:

| Address | Retail instruction | Draft instruction |
| --- | --- | --- |
| `0x8AF137A0` | `addiu a0, v1, -3` | `addiu s7, v1, -3` |
| `0x8AF137A4` | `addu a3, a1, t2` | `addu a3, t2, a1` |
| `0x8AF137B0` | `sll a0, a0, 16` | `sll s7, s7, 16` |
| `0x8AF137BC` | `sra a0, a0, 16` | `sra a0, s7, 16` |

The C symbol is 1,044 bytes, but its original 1,048-byte owner span is
already preserved by the text section's implicit terminal zero alignment
word. **Do not add `C_FUNCTION_PADDING(4)` to this draft.** That redundant
marker increases this object's text from 19,264 to 19,280 bytes after
alignment. A function-size difference alone did not prove missing bytes;
the whole-section control caught the mistaken padding hypothesis. Earlier
padding-bearing variants are not evidence of a new layout prerequisite.

### Controls, scoped negatives, and next action

Stock normal and `-g0` diagnostic builds retain the same six-word residual
on the pre-X-carrier lead; natural line grouping does not close it. A
calibrated 180-second clip-only permuter search improves score 240 to 30.
Its expanded region markers and a leading-blank control reproduce the full
stripped object, symbol layout and every relocation row before searching.
Only six real clip statements are randomized. Search scores are not
acceptance evidence; each proposed source edit is independently reviewed.

This continuation records 224 normal drawing rejections, plus eight each
for a section phase-union family, flag-helper return blocks, and padding
store/stride shapes. Those neighbors also stay assembly. The section's
declaration-move control was revalidated against the current 32-C object;
no ABI or companion change was installed. Additional clip snapshots,
literal widths, real phase carriers, bounds records and lexical scopes do
not close the measured residual in their tested contexts. Preserve the
four-word lead instead of restarting from the older broad register drift.

Next investigate why the clip-margin definition inherits the later draw-X
`$s7` web instead of `$a0`, together with the single bottom-add operand
ordering. Separate real lifetimes without adding fake storage, then rerun
the normal runner and full ROM gate before removing the pragma. The
unchanged production ROM still compares byte-identically, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`, and all 46 native tooling tests pass.
No unaccepted C, scratch driver, compiler observer, object, assembly or ROM
is published with this handoff.

## 2026-10-16 — remaining conditional drawing callback accepted

`func_8AF106A8` now replaces **55 original instruction words / 220 bytes**,
frame `0x30`. Solo native macOS, no agents or containers. File **31 C / 7
function ASM to 32 C / 6 function ASM**, out of 38 originals. Acceptance
batch `76f5d3f781fd4f5ab0bf02cd7c2991ca`, candidate
`f44-menu-callback-branch-operands:pointer-first-True:reverse-x-True:negative-False`,
is link-verified with one combined full-ROM gate. This supersedes the fourth
callback's requeue below; all four position-drawing callbacks are accepted.

Keep the consumed record pointer before the two consumed halfword coordinates
and the real two-halfword position array. Both coordinate additions put the
record field before its corresponding position element. Together with the
real pointer lifetime established by the preceding family, this preserves
the original `sp+0x24` array, both temporary-load sequences, the signed Y
snapshot at `sp+0x28`, and the branch-specific taken-path normalization.
Keep the positive `D_8AF31000 == 3` branch and the two actual drawing callees.
No separate word-Y local, extra snapshot, artificial storage or type change
is needed. Operand order alone in the earlier wrong-home context was not a
solution; reopen it after the measured storage/lifetime change.

A calibrated 60-second local permuter search improved score 320 to 10 with a
semantically valid Y operand swap. Two other proposals read newly introduced
locals without initialization on the selected switch path; reject them,
regardless of their improved scores. An eight-cell reviewed normal-runner
batch composed the valid swap with X order, record declaration order and
branch orientation; the first exact positive-branch proposal gated normally.
The permuter never installed source and its scratch outputs are not published.

After declaration cleanup, fresh and twenty-leading-blank builds reproduce
the frozen accepted object's complete loadable sections/layout and every
relocation row. All 38 original starts/sizes and 37 untouched raw bodies
match the verified 31-C baseline. A strict canonical link reproduces all
19,264 text bytes and 240 rodata bytes directly against both the normal ELF
and retail ROM. Forced native `gmake rom COMPARE=1` passes, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Host syntax passes with the same three
pre-existing warnings; all 46 native tooling tests pass. Naming plan/apply
finds no mapped name. No helper script, compiler copy, object, assembly or
ROM is published. The six remaining larger dispatcher/drawing and
section/padding/flag owners remain assembly, with their previous scoped
requeues and layout evidence intact.

## 2026-10-16 — three position-drawing callbacks accepted

Solo native macOS, no agents or containers. Three existing owners replace
**125 original instruction words / 500 bytes**, each with frame `0x30`:
`func_8AF10570` (156 bytes), `func_8AF1060C` (156 bytes), and
`func_8AF10784` (188 bytes). The file advances from **28 C / 10 function ASM
to 31 C / 7 function ASM**, out of 38 originals. All three are link-verified
acceptances in batch `d758c5bf0be84a5ca463a6aa029e2577`, each labeled
`f44-menu-callback-record-order:byte-False:first-False:case-False`.
One combined byte-identical full-ROM gate accepts them together.

### Actual storage/lifetime mechanism

Keep two consumed signed-halfword coordinates, then the consumed local
record pointer, then the real two-halfword position array. The local pointer
is initialized from the callback's record argument and used for both the
flag update and drawing-coordinate fields. This restores the position array
at `sp+0x24` without changing the original parameter home or argument
registers. No unused local, enlarged array, padding member or forced register.

Earlier width and declaration-order families were tested separately. Their
composition with two standalone word coordinates restores the array home,
but incorrectly reallocates the draw arguments; the consumed record-pointer
form with halfword coordinates closes both mechanisms. A calibrated native
logging-only stock/off/on/twenty-blank experiment preserves the complete
control and candidate objects, including symbols and relocation rows. Its
UGEN callback is procedure 18, while the corresponding UOPT entry is 19;
identify passes by source/function evidence, not a shared numeric procedure
assumption. The observer and all scratch artifacts remain private.

### Verification and remaining callback

After declaration deduplication and formatting, fresh and twenty-leading-
blank builds match the frozen accepted object's complete loadable sections,
layout and every relocation row. All 38 original starts/sizes stay fixed;
all 35 untouched raw instruction spans match the verified 28-C baseline.
Strict canonical linking reproduces all 19,264 text bytes and 240 rodata
bytes directly against the normal ELF and retail ROM. Forced native
`gmake rom COMPARE=1` passes with MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`; host syntax passes with the same three
pre-existing warnings; all 46 native tooling tests pass. Naming plan/apply
finds no evidence-backed mapped names, so address names remain.

`func_8AF106A8` remains **requeue**, not accepted. The same real record-pointer
mechanism repairs its position home, but the best 216-byte body is four
bytes short: the original taken branch normalizes Y from its live word
while the other branch reloads its signed-halfword snapshot at `sp+0x28`.
Eight distinct word/signed-snapshot carrier proposals do not close that
branch-dependent lifetime and scheduling. Next test that actual lifetime
with preserved load operand order, not artificial storage. Thirty-two mode
guard/lifetime variants and thirty-two standalone wide-coordinate/order
variants were also measured before the accepted record-pointer family;
their negatives are scoped to those source families. Other larger drawing,
section, padding and dispatcher requeues remain assembly.

## 2026-10-16 — six-entry menu renderer accepted

Solo native macOS, no agents or containers. `func_8AF1043C` replaces
**65 original instruction words / 260 bytes**, frame `0x30`. The file
advances from **27 C / 11 function ASM to 28 C / 10 function ASM**, out of
38 originals. Acceptance batch `cee8467ac10a420dadbf5d1bc2412250`, candidate
`f44-menu-renderer-guards:early-False:record-False:id-True`, is link-verified
with one combined full-ROM gate; no companion edits were installed.

- Preserve the six position records, species-ID guard, texture lookup and
  the original `gSPDisplayList` / opaque-surface `gDPSetRenderMode` macros.
  An explicit zero-ID `continue` within the positive record guard closes
  the nine remaining saved-register differences. A combined positive guard
  had the same 65 opcode positions but the wrong saved-register allocation.
- Keep the current contracts: the bank mode is `u16` with an explicit `s16`
  call conversion; the texture lookup returns an integer handle converted
  to the renderer's existing `u8 *` image argument. The production resource
  handle remains `s32`; exploratory opaque-pointer global retyping did not
  help and was not installed. No fake storage or return-category change.
- After removing duplicate injected declarations and cleaning formatting,
  fresh and twenty-leading-blank builds reproduce all frozen loadable
  section bytes/layout and every relocation row. All 38 original starts and
  sizes stay fixed, and all 37 untouched raw instruction spans match the
  27-C baseline. Strict canonical linking reproduces the entire 19,264-byte
  text and 240-byte rodata window against both the normal ELF and retail ROM.
- Forced native `gmake rom COMPARE=1` passes, MD5
  `1561c75d11cedf356a8ddb1a4a5f9d5d`. Host syntax passes with the same three
  pre-existing pointer warnings. All 46 native tooling tests pass. Naming
  plan/apply finds no evidence-backed mapped name; retain the address name.
  No scratch helpers, compiler copies, objects, assembly or ROM are published.

Remaining **requeues**: eight drawing cutoff/carrier variants still leave
the row-bound in `$v0`; none is accepted. Seven earlier drawing guard shapes
were inspected for component wins, without finding the missing row-bound or
retained-top-store mechanism. Eight positive/negative section-loop variants
likewise fail to close the saved-register swap; its companion-only complete
grid-type control was revalidated against the accepted 28-C renderer object.
An old-style padding-parameter experiment stopped at companion preflight
because its target remains an assembly owner; no compiler result or padding
acceptance is claimed. Resume only through a valid runner transaction with
consistent prototypes and independently verified existing callers.

## 2026-10-16 — grid-page initialization accepted

Solo native macOS, without agents or containers. `func_8AF12EB8` replaces
**322 original instruction words / 1,288 bytes**, with frame `0x60`.
The file advances from **26 C / 12 function ASM to 27 C / 11 function ASM**,
out of 38 originals. Acceptance batch:
`e576e2a87a6949d99de275e347a744b2`, candidate
`f44-menu-grid-init-loops:positive-False:skip-True:unsigned-False`.
This is a link-verified acceptance with one combined full-ROM gate.

### Source mechanisms and verification

- Walk the real four-byte `MenuGridEntry` records, bounded at 250 entries.
  A nonpositive-byte sentinel ends the scan. Count the `0xFF` placeholders
  in the total, but use a `continue` before counting and annotating ordinary
  entries. This removes the last eight-word `$s2`/`$s3` allocation swap;
  the equivalent enclosing positive guard did not match.
- Keep six distinct, consumed resource handles for `ers1` through `ers6`.
  Declaring the real late-use `node` local before these handles restores
  all three original spill homes, without padding or unused storage.
- Preserve all font/page setup, node callbacks and field updates, the `abtn`
  resource ID `0x6162746E`, selector setup, and the fourteen-byte saved-scroll
  aggregate restoration. Existing engine parameter contracts are retained.
- Fresh and twenty-leading-blank builds of the cleaned source reproduce
  the frozen accepted object's complete loadable sections, layout and all
  relocation rows. All 38 original starts/sizes stay fixed, and all 37
  untouched raw instruction spans remain identical to the 26-C baseline.
- A strict canonical link, resolving every undefined symbol from the normal
  ELF, reproduces the entire 19,264-byte text and 240-byte literal/table
  window directly against both the ELF and retail ROM. Forced normal native
  `gmake rom COMPARE=1` also passes, MD5
  `1561c75d11cedf356a8ddb1a4a5f9d5d`.
- Host syntax passes with the same three pre-existing pointer warnings;
  all 46 native tooling tests pass. The naming plan/apply finds no mapped
  name for this owner, so its address name remains. No scratch script,
  compiler observer, object, generated assembly or ROM is published.

### Remaining requeues

- `func_8AF13718`: **requeue**. The current 1,044-byte drawing draft has the
  correct `0x80` frame and RGBA homes at `sp+0x54`/`sp+0x57`. Computing the
  bottom bound from the viewport field saves the retained top early, but
  the store is still one instruction too early. Normalized `.9885` / raw
  `.6489` is not a match. A calibrated stock/off/on/blank trace establishes
  the current row-bound value in `$v0`, followed by a different temporary
  sequence. Real carrier reuse, bounded counter widths and continue-guard
  shapes did not close it. A calibrated 180-second permuter search improved
  its score only with canceled-offset scaffolding or an uninitialized
  local; no proposal was adopted. Resume with a materially new lifetime or
  expression-tree hypothesis, not another storage-spelling sweep.
- The four small drawing callbacks remain **requeue**. Two new eight-cell
  families per owner test exactly four position bytes in a word and real
  resource/index/flag argument snapshots. Word storage still has the wrong
  position home; argument snapshots grow the frame. No artificial buffer
  enlargement or unused fields are justified.
- `func_8AF124A8`: **requeue**. The accepted grid type is defined after this
  owner. A companion-only declaration move was independently byte-verified
  in the 26-C context, then eight complete-type output views were tested.
  They do not repair the saved-register swap. Four earlier incomplete-type
  compile failures are context setup failures, not evidence against typed
  field access. Rebaseline the control to the current 27-C source before
  resuming that transaction. Existing section and padding handoffs remain.

## 2026-10-16 — four-byte-stride padding routine accepted

`func_8AF12410` is now C: **38 instruction words / 152 bytes**, frame zero.
This advances the original file from **32 C / 6 ASM to 33 C / 5 ASM**.
Runner batch `81621dc9ca8745a9816d258500eaf43f`, label
`f44-padding-parameter-bound:alias-False:directguard-False:neq-False`,
accepted with `link_verified: true` and one combined full-ROM gate.
This supersedes the older padding requeue; it does not resolve another owner.

The routine preserves `u8 *(u8 *, s16)`. For a positive signed remainder
`count % 4`, it advances by four bytes per iteration, writes `0xFF` only to
the first two bytes of each record, and returns the advanced pointer. Bytes
two and three remain untouched. The winning loop tests
`i < 4 - (count % 4)` directly, while the outer guard uses the actual local
remainder. Keeping a separate padding-bound local or overwriting the
remainder changes IDO's induction recognition and allocation. An ordinary
`<` loop over the separate local remains rolled; a `!=` spelling can unroll
but still has the wrong guard/registers. Repeating the immutable parameter
expression lets stock IDO produce the original unrolling and allocation.
No manual unrolling, fake local, padding pragma, or prototype change is used.

Verification after acceptance:

- Fresh and twenty-leading-blank builds match the immediately frozen accepted
  object in all loadable sections, section layout and every relocation row.
- All 38 original function starts, sizes and raw instruction bodies match the
  preceding 32-C baseline, including both existing callers of this routine.
- A strict canonical link resolves every undefined symbol and reproduces all
  19,264 text bytes and all 240 literal/table bytes against both the normal
  ELF and retail ROM.
- Forced native `gmake rom COMPARE=1` passes, retail MD5
  `1561c75d11cedf356a8ddb1a4a5f9d5d`. Host syntax and all 46 native tests pass.
- The naming plan has no mapped name for this owner; retain its address name.
  Private compiler observers, search drivers, rejected candidates, generated
  assembly, objects and ROMs are not published.

The remaining owners are `func_8AF0F2EC`, `func_8AF113D8`, `func_8AF124A8`,
`func_8AF12E30`, and `func_8AF13718`. They remain assembly with their existing
requeues. In particular, the four-word linked renderer draft is not accepted.
