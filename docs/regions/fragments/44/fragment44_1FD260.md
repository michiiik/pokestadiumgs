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
