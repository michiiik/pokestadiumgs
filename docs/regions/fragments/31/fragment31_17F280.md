# Fragment 31 selection helpers

## Native matching batch (2026-10-15)

Four additional owners are accepted. This file now contains nine C
definitions and nineteen assembly owners. All four are link-verified,
normal-runner accepts with combined full-ROM gates, statistics and the
normal host syntax check enabled.

| Owner | Words / bytes | Frame | Accepted batch |
| --- | ---: | ---: | --- |
| `func_8820C040` | 53 / 212 | 0x20 | `1e4f4c46cb0a492394185c01cf49f8bd` |
| `func_8820C798` | 26 / 104 | 0x18 | `b3a51edd199948109706d5864203b3a8` |
| `func_8820C800` | 40 / 160 | 0x28 | `a7ea3a4859f249458d0df035180b1c3b` |
| `func_8820C8A0` | 43 / 172 | 0x20 | `d6e4b262dd02401ca708077a6830f7ec` |

Winning source explanations and labels:

- `func_8820C040`: `f31:selection-index:pointer-0:index-u32`. Use a
  real `u32 index = slot`, the existing void-pointer state and raw signed
  position fields. The unsigned index removes five per-case carrier moves.
  The four defined selection modes are 0..3; outside that original
  switch contract, retail also leaves the position unspecified. Do not add
  an invented default position. The selected list ID is at 12 + 4*index;
  position fields are at 30 + 44*index, 28 + 44*index, zero, or 0xB8.
- `func_8820C798`:
  `f31:predicate-inline:f31:selection-negative-index:form-2:direct-False`.
  Keep `((s32*)state)[4 - slot]` inline in the two mode tests. A named
  mode local preserves opcode order but swaps the mode/result registers.
  The array index also retains the retail negate/add address tree, unlike
  subtracting a byte offset directly from the pointer.
- `func_8820C800`:
  `f31:selection-contains:count-u8-True:index-u32-True:inline-step-False`.
  Keep the actual u8 count return, a u32 loop index, and a two-byte record
  pointer advanced in the for clause. Test the mapped first byte of every
  record and return on the first matching type.
- `func_8820C8A0`: `f31:lookup-add-order:form-7`. Keep the zero u8 result,
  short-circuit mode/list/type guards and u32 count/index. Initialize the
  record pointer from the table, then advance that same pointer using its
  offset byte. Independent table-plus-offset spellings match every opcode
  but reverse the two inputs of one address add. The accepted pointer
  carrier reuse is ordinary defined C; splitting its two assignments onto
  separate physical lines preserves every byte.

The repository permuter was calibrated against the native candidate and
the authoritative 104-byte predicate target. GNU's prelude gives the
target label ELF NOTYPE rather than FUNC and adds eight zero alignment
bytes; comparison uses the native span and verifies that zero-only tail.
Both actual inputs reproduce the native words before searching. A 0.7s
search reports score 30 -> 0, but the proposed source reads its own
uninitialized slot inside a multiply-by-zero index and is rejected as
invalid even though it compiles. Only its legitimate inline-test change is
recovered. Removing that unsafe expression and the unused declaration,
then probing/gating clean source, accepts the predicate independently.
Never publish or replay the unsafe zero-score mutation as a match.

`func_8800005C` in `src/fragments/29/fragment29_166060.c` is already C,
but was declared void while these and existing callers consume its s32
result. Returning `fragment29_main(D_8800686C)` explicitly fixes that source
contract. Fresh/20-leading-blank controls reproduce all original sections
of its containing object; it introduces no instruction or layout change.

After formatting and scoped extern cleanup, fresh
and 20-leading-blank builds reproduce all accepted sections. All five
prior C bodies and all 28 original function offsets remain unchanged.
All nine linked C spans and the entire ROM match retail, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Exactly four removed pragmas have
accepted gate provenance. No layout, alias, compiler, tool or storage
changes. Naming plan has no established mappings.

## Requeue: bounds setters

`func_8820CA50` and `func_8820CAE4`: prior **requeue**, now resolved by
the five-owner batch below. At this handoff there were 36 rejected cells
each; neither replacement nor experimental prototype was installed.
The best normalised scores are 0.8947 and 0.8919, respectively. Retail
uses frame 0x18; the current source families keep frame 0x20. Object
inspection shows a narrowed slot carrier spilled at 0x18 across the bound
lookup, whereas retail reloads the incoming byte after that call.
Ordinary guard form, local width, parameter reuse, explicit bounds casts,
word-width call prototype and explicit slot narrowing did not remove it.
The word-prototype experiment is diagnostic only; do not adopt an API
change to manufacture a score. Next action: inspect why the slot's
narrowed value becomes a live web across the call, or obtain a source
shape that naturally reloads the real incoming parameter. Preserve the
fresh global-state read and full-ROM acceptance requirement.

## Count display and selection-limit check: accepted native batch

`func_8820FC78`: 56 words / 224 bytes, frame 0x38. Normal native batch
`f347500572f24460ac547034a824bd40`, winner
`f31:display-conditional:!slot:initializer-False`, is link-verified and
passes its combined full-ROM gate. Preserve `x = !slot ? 269 : 580`, the
mode switch and real u16 limit kept across the fresh count query. An
equality-test ternary or if/else spelling changes the parameter carrier;
the reversed ternary has the wrong case order. Keep the true variadic
draw signature and u8 count helper. Retyping the old no-prototype forward
declaration to u8 is part of the accepted transaction; the now-redundant
forward declaration can then be removed after acceptance. This owner is
separate from the four functions already merged in PR #967.

`func_8820C94C`: 65 words / 260 bytes, frame 0x40. Native batch
`4b4c0518c00147228036fd6b61a23d66`, winner
`f31:selection-limit-homes:irp:deferred-False`, is link-verified and
passes its combined full-ROM gate. Iterate the two slots with a u32
index, preserving the mode/list/type guards and fetching the other slot's
record before comparing types and the combined limit. Keep the natural
declaration order `index`, initialized s32 `result`, then `other`: the
result lives at 0x38, not 0x3C. Keep `other[1] + func_8820C8A0(...)` to
preserve the target add's operand order. No fake locals, empty branches,
padding or compiler changes are needed.

After formatting and removing redundant generated externs, fresh and
20-leading-blank builds preserve every accepted object section, all nine
previous C bodies and all 28 original function offsets. All eleven linked
C spans and the entire ROM match retail, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Exactly these two removed pragmas
have accepted link-verified gate provenance. Naming plan has no established
mappings. Seventeen assembly owners remain in this source file.

## Requeue: scroll update and initializer

`func_8820C65C`: prior **requeue**, now resolved by the five-owner batch
below. Direct global-state reads recovered the retail
316-byte opcode sequence and 0x20 frame, but registers differ (normalised
1.0, raw 0.6203). A calibrated 45-second permuter improves its own score
195 -> 65; its retained proposal includes an empty constant-false branch,
so it is diagnostic only, not installed or claimed as matching C. Eight
explicit s32/u32 index and flag-pointer cells do not improve the raw match;
K&R formals were also unhelpful. Next action: isolate the global-address
and status-pointer allocation (retail a3/a2, baseline t0/a3), not repeat
the same guard or index spellings.

`func_8820C114`: prior **requeue**, now resolved by the local initializer
acceptance below. Ordinary source cells kept 328 bytes and a
0x50 frame instead of retail 324 bytes / 0x48. Global reads, K&R formals
and eight float-lifetime/declaration cells do not change that output.
Eight address-exposure/real parameter-pointer and local-width cells are
also rejected, at 332 bytes. No experimental API or address-test scaffold
is installed. Next action: inspect the narrowed slot web kept across the
two real TV-rate calls; retail reloads the incoming byte. The quotient
and rounding-lifetime hypothesis did not explain the frame difference.

## Requeue: row-selection predicate and category resolver

`func_8820E450`: **requeue**, 32 normal rejected cells, no replacement
installed. The u32 index initialized from the u8 slot recovers the exact
304-byte opcode sequence and frameless shape; raw similarity is 0.9605.
Only comparisons at instruction rows 29, 46 and 63 reverse their two
register operands. Switching guard nesting, result width, comparison text
order, comparison use of the unchanged index, or explicit integer casts
does not fix those three words. The s16 cast family worsens the shape.
A separately calibrated 45-second permuter reaches score 30 -> 20 by
introducing a comma expression at one slot comparison, but never matches;
its mutations are not installed. Next action: isolate why that expression
changes comparison lowering before another bounded search, retaining the
u32 address index. Do not count normalised 1.0 as instruction exactness.

`func_8820E580`: prior **requeue**, now resolved by the accepted batch below.
At this handoff, eight normal cells were rejected and no replacement was
installed. A natural category resolver uses the current record, the other
slot's type, the selected record's last-entry flag, and the inclusive
0xC0/0xC2 position bounds. Real `func_88A00FD4(u8)` returns s32, as its
existing C definition confirms. The best normalised score is 0.9589,
288 bytes versus retail 292, from an explicit last-entry flag, direct
global-state accesses and a merged return. Cached state reaches 292 bytes
but only 0.9452 normalised / 0.6438 raw. Inline last-entry tests and early
returns shorten the shape further and are not improvements. Next action:
inspect the missing control-flow instruction and pointer reload lifetime
in the direct-global, explicit-flag baseline before further spelling cells.

## Accepted native transfer and category batch

Four more owners, 335 instructions / 1340 bytes, are accepted with
`link_verified: true` and normal combined full-ROM gates:

| Owner | Words / bytes | Frame | Accepted batch |
| --- | ---: | ---: | --- |
| `func_8820CB74` | 77 / 308 | 0x28 | `4dd906a7e8154ed29d085ffa7d5468dd` |
| `func_8820CCA8` | 97 / 388 | 0x38 | `1ec621a14444450792fd84c1d5f04729` |
| `func_8820CE2C` | 88 / 352 | 0x40 | `29720e31bf0d47ff98e15f42702d48e6` |
| `func_8820E580` | 73 / 292 | 0x20 | `19a8d0fa45d140d2817c385f7bb4431b` |

- Transfer initializer: `f31:transfer-homes:u32:separate-False:sizeof-False`.
  The real transfer record has a pointer at zero, two delta bytes, a slot,
  and two count bytes. Declare the u32 index before the allocation pointer
  to retain its stack home at 0x20. Raw-byte record access lost one word;
  typed fields recover the target shape without padding or dummy locals.
- Selection switch: `f31:switch-bound-fields:stores-False:reverse-False:unsigned-False`.
  Retain the short-circuit guarded flag, current/other byte types, two-argument
  bound setters, and conditional sound. Typed list, table and lower-bound
  fields recover the real load and operand order. Adding a cached table
  pointer or a width temporary changes allocation and does not help.
- Completion path: `f31:complete-four-homes:iorp`. Keep the real local order
  u32 index, other-record pointer, s16 position, then two-byte item pair.
  The position is sampled before filling the pair. Typed list/record fields
  repair two address operands; the declaration order gives frame 0x40 and
  the pair at 0x34, not frame 0x48 / pair 0x38. Four earlier typed cells
  failed because their typedef was below the owner; those are setup errors,
  not failed source hypotheses. Moving accepted types before consumers was
  separately checked to preserve every object section.
- Category resolver: `f31:category-record-fields:wide-False:count-True:local-False`.
  A real u32 selected-slot temporary fixes the first address add. Keep the
  word-width other type with explicit byte mask, then the ternary last-entry
  flag. Both position and count must use the same typed record path; typing
  only one loses CSE. The last address add then matches, with no comma or
  empty-branch mutation. A calibrated 45-second permuter had improved its
  own score 20 -> 10; its nonmatching scaffolding is not installed.

Native state offsets used here are slot 0, list IDs 0x0C, 44-byte records
0x14, enabled flags 0xB0 and lower bound 0xC0. Unknown fields stay reserved;
the global pointer is not retyped across translation units. The limits
table has four count bytes at +1 and lower bytes at +5. Category helper C
returns only 0 through 3. The existing display/lookup source remains intact.

Post-acceptance formatting, duplicate-extern cleanup and correction of
`func_88004990`'s second parameter to its actual u8 ABI preserve all accepted
object sections. Its only new call passes zero. Fresh and 20-leading-blank
controls preserve all eleven previous C bodies and all 28 original offsets.
All fifteen linked C spans and the entire ROM match retail, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Exactly these four removed pragmas have
accepted link-verified gate provenance. Scoped dedupe finds zero remaining
duplicates; naming plan has no established mappings. Thirteen assembly
owners remain. No compiler, tooling, linker, YAML or data-layout changes.

The remaining row predicate received eight typed-slot/field cells; all are
rejected and the previous three-operand residual is unchanged. Do not
repeat that field-spelling family as the next hypothesis.

## Category renderer: accepted

`func_8820E9BC`: 86 words / 344 bytes, frame 0x38. Batch
`e50ff4b2062746909e93448738973cb1`, winner
`f31:category-renderer:color-first-True:early-False:typed-True`, is
link-verified and passes its normal combined full-ROM gate. Preserve the
four-byte color buffer before the s32 category, typed current-list guard,
four color cases and actual text lookup/draw calls. There is no jump table.

The same accepted transaction corrects the stale text-lookup declaration
to `void* func_8004C874(s32, s32)`, matching its existing C definition.
Fresh and 20-leading-blank native builds reproduce every accepted object
section, all fifteen previous C bodies and the original owner offsets;
the previous `func_8820FD80` caller's words are unchanged. Scoped duplicate
cleanup and final normal full-ROM build pass with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Naming plan has no established mapping.
This renderer is separate from the four functions merged in PR #969 and
is not counted as published there. It is included in the following batch.

## Accepted scroll, bounds and renderer batch

Five owners, 355 instructions / 1420 bytes, are accepted with
`link_verified: true` and normal combined full-ROM gates:

| Owner | Words / bytes | Frame | Accepted batch |
| --- | ---: | ---: | --- |
| `func_8820C65C` | 79 / 316 | 0x20 | `63f3f2d4bed94068b877bf93b304f612` |
| `func_8820CA50` | 37 / 148 | 0x18 | `74aa762a204a4a85989d1a9b9fb4e053` |
| `func_8820CAE4` | 36 / 144 | 0x18 | `94d4d5ec14944c0383aaca9606054345` |
| `func_8820E9BC` | 86 / 344 | 0x38 | `e50ff4b2062746909e93448738973cb1` |
| `func_8820EB14` | 117 / 468 | 0x18 | `acb522facca74cc2afa44efde92b675f` |

- Scroll update: `f31:scroll-state-fields:early-False:index-False:typed-True`.
  Use the existing typed enabled/list arrays and 44-byte record, with the
  byte slot parameter directly. This resolves the old a3/a2 allocation
  residual without the permuter's empty branch. Both enabled/disabled
  paths preserve their fresh count query, count adjustment, scrolling
  branch and final refresh.
- Moving bounds: `f31:bounds-state-fields:func_8820CAE4:s32:early-False:parameter-True`.
  The typed state paths recover the incoming-byte reload and retail 0x18
  frame. Keep the s32 lookup result and explicit signed-halfword bounds.
- Fixed bounds: `f31:bound-distinct-values:s16:table-True`.
  Keep category as s32 and the separate table-derived bound as s16. Reusing
  one value for category and bound, or using u8/u16/s32 for that bound,
  gives two extra narrowing instructions. Typed table access fixes the
  last address operand. The real existing signed-halfword callee prototype
  is retained; no word-width API experiment is installed.
- Category renderer: winner and source explanation above. Its corrected
  pointer-returning text-lookup declaration matches the actual existing
  C definition and preserves the prior caller's words. Correct the related
  `func_80049064` text argument to `const char*`, as its existing definition
  in `src/47580.c` declares, removing the pointer-to-integer warnings in
  that prior caller without changing its instructions.
- Type fill colour: `f31:type-fill:s32:ternary-False:sorted-False`.
  Use SDK `gDPSetFillColor` in each explicit conditional arm. Preserve case
  block order 1, 3, 4, 2; sorting changes the raw words despite the same
  opcode shape. Ternary colour selection merges branches and is 112 bytes
  too short. Four cases require no jump-table/rodata prerequisite.

The limits-table type was moved before its new consumers, separately
verified section-identical. Post-acceptance formatting, redundant-forward
removal and scoped extern dedupe preserve every accepted object section.
Fresh and 20-leading-blank controls preserve all fifteen previous C bodies
and all 28 original function offsets. All twenty linked C spans and the
entire ROM match retail, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
Exactly five removed pragmas have accepted link-verified gate provenance.
Naming plan has no established mappings. Eight assembly owners remain in
this file. No scratch helpers, tooling, compiler, linker or layout changes.

## Scroll initializer: accepted

`func_8820C114`: 81 words / 324 bytes, frame 0x48. Batch
`f2871972bbf14c67b5f73d47a3300fbc`, winner
`f31:init-inline-count:lt:ternary-False:zero-False`, is link-verified and
passes its normal combined full-ROM gate. This is separate from the five
functions merged in PR #970 and is part of the following batch.

Typed state list/record fields first recover the retail opcode sequence,
including the incoming-byte reload, but explicit count/TV-rate/float
locals put flags in the wrong frame. Changing their declaration order
does not explain the original spills. The target comes from call-bearing
arguments: keep the count query inline and round with
`600.0f / func_80001FF0() + (0.0f < (600.0f / func_80001FF0()) ? 0.5f : -0.5f)`.
Only the real s16 flags remains a named local. The compiler spills the
count at 0x3B and first TV-rate return at 0x3C, with flags at 0x46; no
padding, dummy locals or prototype experiments are required. Both real
TV-rate calls are preserved. The flags if/else form matters; a ternary
changes the branch words.

Formatting, scoped duplicate cleanup, fresh and 20-leading-blank native
controls preserve every accepted object section, all twenty previous C
bodies and all original function offsets. The entire ROM remains retail
MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. Naming plan has no established
mapping. Seven assembly owners remain locally in this file.

## Accepted setup, initializer and texture renderer batch

Three larger owners, 536 instructions / 2144 bytes, are accepted with
`link_verified: true` and normal combined full-ROM gates:

| Owner | Words / bytes | Frame | Accepted batch |
| --- | ---: | ---: | --- |
| `func_8820C114` | 81 / 324 | 0x48 | `f2871972bbf14c67b5f73d47a3300fbc` |
| `func_8820C258` | 257 / 1028 | 0x158 | `bcd55ba6f3034151bd525fa1946b4ee9` |
| `func_8820E6A4` | 198 / 792 | 0x38 | `cde54bb886394292adc76f50f7504660` |

- Initializer: winner and call-expression explanation above. No fake stack
  padding or float temporaries are needed.
- Setup: `f31:setup-callback-symbol:enable-chain:clear-plain`. Keep the u32
  loop index before the pool pointer and the real chained enable assignment
  `D_880068B4 = D_880068B8 = 1`. Separate literal assignments omit the address
  materialization and change the following constant scheduling. Keep the two
  zero assignments separate. All 79 constructor arguments were recovered
  from the straight-line register/stack stores and independently checked
  against the callee: 76 signed halfwords, two bytes, then the teardown
  callback. Use its complete fixed prototype, not the exploratory varargs
  declaration. Preserve the original `D_88000E4C` callback symbol. The first
  instruction hits failed link/gate because the draft had incorrectly
  spelled it `func_88000E4C`; no alias or guessed symbol was installed.
  The corrected source independently passes object, link and full-ROM gates.
- Texture renderer: `f31:category-textures:typed-False:category-first-True:early-False`.
  Keep category before texture, the typed current-list guard, signed first
  dimensions and unsigned second texture-coordinate calculation. Normal SDK
  pipe-sync/environment-colour macros and the existing narrow rectangle
  helper signature match directly; no raw display-list writes or API
  experiment is needed. Reversing the two local declarations swaps their
  stack homes. The unused exploratory texture typedef is removed afterward.

After formatting and scoped extern cleanup, fresh and 20-leading-blank
builds reproduce every accepted object section, all twenty previous C
bodies and all 28 original function offsets. All twenty-three linked C spans
and the entire ROM match retail, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
Exactly three removed pragmas have accepted link-verified gate provenance.
Naming plan has no established mappings. Five assembly owners remain in
this source. No compiler, tooling, linker, YAML or data-layout changes.

The row predicate received eight real loaded-selection-local cells (u8,
s32, u32, s16, both comparison orders). All reject at 304 bytes, raw 0.3421;
they change allocation/control ordering instead of closing the prior
three-operand residual. No local or rejected predicate source is installed.
Next action remains comparison-lowering forensics on the preserved near-match,
not another local-width or textual operand-order sweep.
