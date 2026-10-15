# Region notes -- src/fragments/13/fragment13_EEC50.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-15

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-15

func_82405D38: time cap at 0.9057 (raw 0.5755) after 2688s, mismatch operand_or_scheduling_drift; tried families: call_chain; tie-pool no

## 2026-10-15 — four lighting/clock callbacks accepted

The file advances from **36 C / 43 ASM** to **40 C / 39 ASM**. Four normal
native-runner accepts cover **147 instruction words / 588 ROM bytes** under
stock IDO 7.1 / `-O2`. Every owner has `link_verified: true` and a successful
combined full-ROM gate; statistics and host checks stay enabled.

| Owner | Name | Words / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_82405934` | `Fragment13_UpdateSceneLightNode` | 44 / 176 | 0x40 | `bc1f32a9f0d8410990eca5b1caf9fed5` |
| `func_824059E4` | `Fragment13_UpdateSceneDirectionalLightNode` | 29 / 116 | 0x28 | `7615c44b27f542b5b6d04065d8332108` |
| `func_82405A84` | `Fragment13_UpdateClockHourHand` | 40 / 160 | none | `b292669dde624557a4e23e6c9e6fd716` |
| `func_82405B24` | `Fragment13_UpdateClockMinuteHand` | 34 / 136 | none | `dc3f8837f680448da6a552223e3b5ea3` |

### Source mechanisms

- Light node: preload context, then preserve event-2 RGB/flag writes and the
  kind-19..21 vector path versus angle path. Declare the real word-sized kind
  before the six-byte vector and two angle locals; load it after the color
  writes. This restores angle homes at stack+0x2E/+0x2C and vector at +0x30
  without padding or unused locals. A byte kind changes code; omitting the
  named kind leaves angles twelve bytes too high. Sixteen candidates.
- Directional light: a real byte-pointer node alias precedes the context and
  angle locals. That restores frame 0x28, context spill +0x20 and angles
  +0x1E/+0x1C. The direct-parameter spelling has frame 0x20; an angle array
  has the wrong slots. Eight candidates close the historical stack-layout
  requeue, using new evidence from the accepted sibling rather than replaying
  its old scalar orders. Preserve color bytes +0x34..36 and vector +0x38.
- Hour hand: retain the genuine signed word angle, convert to integer before
  negating it, and put the hour term after the fractional-minute expression.
  An inline integer cast without a named angle still loses a target word;
  a separate negating assignment changes allocation. Twenty-four candidates;
  the previously stuck family becomes exact under this new source topology.
- Minute hand: use `seconds / 60.0f + minutes`, store the sum in a float local,
  then multiply by the original scale, divide by 60 and negate before integer
  conversion. The opposite addition order schedules the second byte first;
  keeping a float minute local gives it the wrong colored register. Forty-eight
  candidates across distinct tested families; a calibrated 45-second native
  permuter on the earlier minute-first basin stays 120 -> 120. No mutation
  is adopted. The accepted different expression basin is not contradicted by
  that scoped negative or the runner's advisory register-tie warning.
- Keep the separate original global scale cells, each **65535.0f**, and all
  original event guards, byte-to-float conversions, signed halfword stores
  and source evaluation groupings. Do not simplify to a different turn scale.

### Cleanup, naming and verification

- Add four behavior-backed US compatibility aliases, retaining address-keyed
  symbols and JP. No new helper function or storage object. Correct the local
  vector-conversion declaration to its actual pointer return (ignored here),
  preserve the five-argument vector-mode helper's byte formals, remove duplicate
  prototypes for the already-defined angle helper, and format only the new C.
- Baseline normal ROM rebuild and fresh/twenty-leading-blank whole-object
  controls pass before candidates. After cleanup/naming, the same controls
  preserve all section bytes/layout, all **79 function offsets/sizes/full
  spans**, the four accepted bodies and **75 untouched** C/ASM spans against
  the frozen accepted/original objects. No layout or compiler changes.
- Forced final native ROM build matches retail MD5
  `1561c75d11cedf356a8ddb1a4a5f9d5d`. Explicit host syntax check passes;
  public tooling tests: 22 PASS. Diff whitespace check passes.
- No provenance bypass, forced register, padding, dead-variable scaffold or
  compiler mutation is installed. Only C, US aliases and region notes are
  published. All generators, proof scripts, traces, compilers, objects and
  ROMs stay local. Work is solo/native, without agents or containers.

### `func_824070E4` — requeue, clamped interpolation register roles

Thirty-two candidates reproduce **35/35 instruction opcodes**, frame 0x18
and 140 bytes, but not the registers. Best baseline normalized/raw is
**1.0/0.7714**, with a named index colored instead of the original t6 load.
Inlining the index restores that load, but start/end use v1/a1 instead of
a1/v1; the array-address addition order also differs (best raw 0.7429 in the
field-limit family, 0.7143 in the named-limit inline-index family).

Tested: both min/clamp spellings, load/declaration orders, named versus field
limit, signed-halfword versus word limit, a separate float base, advisory
register spelling and integer/pointer/array address forms. None is installed.
Next: trace the two equal-sized word-value webs and their interference in the
inline-index leader before more declaration/operand variants. Do not change
the known float callback signature or invent unused formals to force a1.

### Historical target-selection caveat

The local ranker's zero-attempt signal did not expose the older directional
callback requeue recorded in the shared region notes. Those notes were read
before probing; it was retried only after the new light-node layout evidence.
Do not treat missing structured history as proof that an owner is fresh.
The larger `func_82405D38` historical handoff remains unchanged and untried.

## Native motion/group batch — 2026-10-15

Three owners accepted: **139 words / 556 bytes**. File advances from 40 C /
39 ASM to **43 C / 36 ASM** (79 total). Solo/native; no agents or containers.

| Original owner | Behavior-backed name | Words | Frame | Acceptance |
| --- | --- | ---: | ---: | --- |
| `func_82405F8C` | `Fragment13_StepVectorToward` | 53 | 0x30 | link-verified, combined ROM gate; `8b6953b80f9b458a9a7a5347817b09e8` |
| `func_82407170` | `Fragment13_FindNearestGroup` | 46 | none | link-verified, combined ROM gate; `2d474116d89048e4b3945eeba14925a1` |
| `func_824048F0` | `Fragment13_InitGroupedList` | 40 | none | relocation-masked, sequential ROM gate; `f8a33b83d997435d899dee0285f93b9a` |

### Measured source shapes

- Vector stepping: compute the three differences before the distance, then
  use explicit `position = position + delta / distance * step` assignments.
  Negative step or **strictly** shorter distance copies the destination and
  returns zero; otherwise return one. Preserve original equality/zero-distance
  behavior rather than adding a divide-by-zero guard. No saved origin locals.
- Nearest group: eight 0x3C-byte records; inline the repeated **X square before
  Z square**, cast the sum to signed integer before comparing, and retain the
  strict comparison/first-on-tie behavior. IDO unrolls the ordinary loop by two.
  Named differences produce the wrong unroll; Z-first inline terms reproduce
  the opcode sequence but swap six X/Z load offsets. Twenty-four candidates
  across these families; no manual unroll or padding.
- Grouped-list initialization: clear 128 halfwords to -1, then write eight
  groups' counts, starts, item indices and separators. The record count is an
  unsigned halfword at offset 0x3A; the uncharacterized tail stays opaque.
  A controlled, token-identical clear-loop reflow proves statement source-line
  grouping controls its branch-delay schedule: single-line body has three
  differing words; a normal multiline body has only the end-address relocation.
  Twenty leading blank lines do not change either result. Pointer-clear and
  loop-shape families did not fix this schedule. No runner change was required:
  the existing candidate identity already preserves token-bearing line groups.
- The initializer materializes `D_82407370 + 480` instead of the assembly's
  equivalent `D_82407550`. It is **not object-link-verified**: the normal
  relocation-masked sequential full-ROM gate establishes acceptance. No symbol
  address, section layout, compiler flag or linker-layout change is needed.

### Cleanup and verification

Three US compatibility aliases; no new helper function or storage object.
Move the shared anchor type before its first use, remove duplicate/unused
externs and format only newly accepted C. Fresh and twenty-leading-blank
whole-object controls preserve every section's bytes/layout, all **79 original
function offsets/sizes/full spans**, all three accepted bodies against the
frozen accepted object, and all **76 untouched** spans against the baseline.
Forced normal native ROM build passes retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`; explicit host syntax check passes with the
existing unrelated line-25 implicit-call warning; 22 public tooling tests pass.
No bypass, forced-register scaffold or compiler mutation. Scratch generators,
proof scripts, compiler files, objects and ROMs remain local and unpublished.

### `func_8240641C` — requeue, input-load CSE and lifetime

Eighty-one-word / 324-byte target, frame 0x20. Forty submitted candidates
(four compile failures) across record/raw views, byte/word handled flags,
nested/goto tails, controller-field/halfword-array accesses, volatile samples
and an explicit navigation snapshot. Best ordinary family: 316 bytes,
normalized/raw **0.9753/0.7407**. The compiler shares an initial controller load
that the target repeats. Volatile sampling overcorrects to 340 bytes; explicit
navigation snapshots do not close the residual. None is installed.

Preserve B-before-A precedence, independent right/left navigation tests,
post-sound reload behavior and the unconditional final update call. Do not
invent a return value or extra formal to steer allocation. The sound helper's
one-argument call conflicts with this file's existing two-argument prototype;
an old-style unspecified-arity declaration was tested only as a transactional
companion edit, not adopted. The accepted caller and original prototype remain
unchanged. Next: trace controller-load value ownership across the initial B/A
split before another source family; distinguish load CSE from base-address
promotion. These measured failures are not a proof that legal C is impossible.

## Native group-selection batch — 2026-10-15

Four more owners accepted: **185 words / 740 bytes**, file **43 C / 36 ASM →
47 C / 32 ASM**. All four are **link-verified** with successful combined
full-ROM gates. Solo native macOS work; no agents or containers.

| Original owner | Behavior-backed name | Words / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_82404990` | `Fragment13_GetGroupedListItem` | 16 / 64 | none | `97b1db6a39bb48a682922b21291935cd` |
| `func_82404AE8` | `Fragment13_HasSelectionChanges` | 33 / 132 | none | `0f8b5376fdc74737a946ca7c359624cc` |
| `func_82404B6C` | `Fragment13_LoadGroupSelections` | 67 / 268 | 0x40 | `9ea32b145c2141619eeb1127a44e57dc` |
| `func_82404E50` | `Fragment13_UpdateGroupTransition` | 69 / 276 | 0x28 | `0f84cbb2db434051a8b4afe56a440f38` |

### Source mechanisms and historical retries

- The lookup closes a 79-attempt historical requeue using the grouped-list
  type verified in the preceding batch. Keep the two-stage pointer expression
  `(entries + starts[group])[index]`, not a combined integer index or cached
  base pointer. Eight new candidates; the first natural typed form accepts.
- The change predicate closes 46 historical attempts with a natural eight-word
  array comparison and early return. IDO supplies the four-at-a-time unroll;
  no manual unroll is needed. Current selections start at 0x194, previous ones
  at 0x1B4. Eight candidates; the first direct-array form accepts.
- The restore loop uses the grouped list embedded at root+0x54, handle at
  0x190, and current selections at 0x194. Item descriptors are 12 bytes with
  ID/value halfwords at +8/+10. The pointer field at `D_824073A4` repeats at
  the anchor's 0x3C-byte stride; it is not a contiguous array of pointers.
  Preserve -1 for absent values and the first matching item index.
- The first eight restore candidates improve the historical best but miss
  one instruction (264 vs 268 bytes): a word-sized returned value remains in
  v0 instead of moving to a2. Reading `func_8005FFB4`'s assembly establishes
  byte-valued results on every return path, including zero paths. Declaring
  that interface and the local value as `u8` closes the residual without a
  fake use or callee edit. Eight return/value-lifetime candidates; first accepts.
- The transition preserves the twenty-tick clamp, easing-function pointer,
  both original anchor-vector offsets (+0x1C/+0x28), and reloads across the
  first interpolation call. Retain `timer += tick`: the explicit-add form
  misses one floating operand assignment. Eight candidates; the second accepts.

### Cleanup and verification

Four US compatibility aliases, unchanged address-keyed symbols and JP.
Consolidate the two new selection-state views into one verified type, format
the new C, and remove rejected-only transition types and duplicate prototypes.
Fresh and twenty-leading-blank whole-object controls preserve all section
bytes/layout, all **79 original function offsets/sizes/full spans**, all four
frozen accepted bodies and **75 untouched** spans. No new helper function or
storage object, compiler change, layout change, padding or bypass.

Forced normal native ROM comparison passes retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Explicit host syntax check passes with the
existing unrelated line-25 warning; all 22 public tooling tests pass; diff
whitespace check passes. Scratch generators, traces, proof scripts, objects,
compiler files and ROMs remain local and unpublished.

### `func_824050A8` — requeue, time carry/load scheduling

Owner stays ASM: 103 words / 412 bytes, frame 0x18. Fifty-six native-runner
candidates tested natural carry/subtract versus remainder, named/literal
divisors, field views, value carriers, eight legal carry-before-reduction
orders, eight fixed-order adjacent statement-line ties, explicit carry
expressions, and remainder-before-carry/separate-lifetime families. Best
normalized/raw is **0.9709/0.7379**, correct size. The final sixteen remainder
and lifetime trials do not improve it. A duplicate candidate caught before
compilation did not consume an attempt. No candidate is installed.

Calibrated 45-second permuter: **645 → 640**, not exact; its retained change
is only a commutative hours-addition swap. Logging-only compiler stock/off/on/
twenty-blank controls reproduce complete known and leader objects (8/8),
including all bytes/layout, symbols and relocations. Carry quotients already
receive the expected v1/a1/a2/a3 roles in the leader; do not force colors.
Normal and diagnostic `-g0` retain 53 differing words; `-g3` changes the size
to 408 bytes and still differs, so debug flags are not a fix. No diagnostic
compiler or flag is installed in the normal build.

Next: isolate the first temporary-demand/load-hoisting divergence around the
fraction product versus old-seconds load. The leader also preloads hours/day
earlier than the target. Scope the negative to these tested source families;
do not infer that stock C is impossible or restart the same permutations.

## Native persistence/camera batch — 2026-10-15

Three owners accepted: **233 words / 932 bytes**, file **47 C / 32 ASM →
50 C / 29 ASM**. Solo native execution; no agents or containers.

| Original owner | Name | Words / bytes | Frame | Acceptance / batch |
| --- | --- | ---: | ---: | --- |
| `func_824049D0` | `Fragment13_InitAvailableGroupedList` | 70 / 280 | 0x40 | relocation-masked sequential ROM gate; `efb6992b82ce48ea90377b312092c2dd` |
| `func_82404C78` | `Fragment13_ApplyGroupSelections` | 88 / 352 | 0x40 | link-verified combined gate; `cf8870681a744f59ad4e188507e8d3e3` |
| `func_82405C0C` | `Fragment13_ResetGroupCamera` | 75 / 300 | none | link-verified combined gate; `595df897dd6645dbbe6997f5ccd1be97` |

### Source mechanisms

- Correct the already-C `func_8005F9A4` predicate and `func_8005F808`
  declaration to return `s32`; the original assembly callers branch on v0.
  This is independently verified metadata cleanup, not a fabricated signature
  for scoring. All 237 original functions in `585D0.c` retain their complete
  bytes/spans, section layout and relocation topology in fresh/twenty-blank
  controls. Keep the two mode-1/mode-2 command wrappers void and preserve the
  existing argument-home spelling. See `docs/regions/585D0.md`.
- List builder: retain IDs 0x2A4/0x2AF unconditionally, otherwise test the
  stored flag; preserve item order, group starts/counts and -1 separators.
  The typed anchor/item views improve the old 69-attempt requeue. A real
  item-pointer local plus inline ID accesses closes the remaining allocation
  difference; a separately cached ID keeps the pointer in the wrong register.
  Sixteen candidates. Its table+480 end address differs from the assembly's
  equivalent end-symbol relocation: **not object-link-verified**, accepted by
  the normal sequential retail-ROM gate without aliases/layout patches.
- Apply: keep default values for absent selections, the flag predicate and
  both original key/value exceptions, byte-valued apply calls, lock/update/
  unlock order, and final dirty word. Twenty-four candidates. Inline the
  current-selection field and name the actual list item index: the word local
  for the selection monopolizes v0, while an unnamed item index stays a temp.
  The accepted form reproduces the original v1/v0 roles without forced colors.
- Camera reset: a natural typed struct copy plus typed root/vector fields
  closes the historical 62-attempt requeue immediately (eight submitted
  candidates, first accepts). Preserve default Y, four original X/Z bounds,
  clamp order, default eye copy and final X/Z offsets. Do not repeat the old
  manually expanded word-copy family or its incorrect eye-X source expression.

### Cleanup and verification

Consolidate the three anchor views into one 0x3C-byte record: original xyz,
16 opaque bytes, eye/target vectors at +0x1C/+0x28, item pointer +0x34,
signed default +0x38 and unsigned count +0x3A. Reuse the existing motion vector
and item types, remove rejected-only views/duplicate externs and add three US
compatibility aliases. No new helper function or storage object.

Fresh and twenty-leading-blank whole-object controls preserve all section
bytes/layout, all **79 original function offsets/sizes/full spans**, the three
frozen accepted bodies and **76 untouched** spans after cleanup/naming.
Forced normal ROM build passes retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Explicit host checks pass for both source
files; `585D0.c` has the same 82 warnings before/after metadata correction and
the fragment retains its existing line-25 warning. All 22 public tooling
tests and diff whitespace checks pass. No bypass, compiler/layout mutation,
padding or new dead-variable scaffold. All search/proof tools and binary
artifacts stay local; the unresolved flag accessor remains ASM.

## Native group-state initializer — 2026-10-15

`func_82405D38` → `Fragment13_InitGroupState`: **106 words / 424 bytes**,
frame 0x50; file **50 C / 29 ASM → 51 C / 28 ASM**. Runner acceptance
`9ae7bce569c14e969806f2460ed34fd5`, link-verified combined full-ROM gate.
Solo native execution, no agents or containers.

The typed root view connects the existing grouped list (+0x54), camera
vectors (+0x174/+0x180), handle (+0x190), selection arrays and transition
fields. Preserve the metadata copy/name extraction and natural struct copies.
Declare the real counter and target pointer before the two local buffers:
metadata at sp+0x38 and position at sp+0x2C then agree with the original.
Initialize offsetZ early and copy targetState from idle after field18C.
The counter-only loop is present in the original at 0x82405E54–0x82405E60;
it is not newly introduced padding. Let IDO unroll the final array copy.

Forty submitted candidates: eight initial declaration failures, then 32
compared candidates across pointer lifetimes, buffer homes and scalar store
order. No fake locals, register forcing, signature mutation or gate bypass.
Remove the unused rejected-only trainer-info type during cleanup. Rename
the existing caller and add the US compatibility alias.

Fresh and twenty-leading-blank controls preserve all section bytes/layout,
all 79 original offsets/sizes/full spans, the frozen accepted initializer
and 78 untouched spans. Forced normal ROM comparison passes MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`; host checks pass for both touched C files
with existing warnings; all 22 tooling tests pass.

### Lighting selector requeue

`func_82405718`: 16 compared candidates, best normalized/raw 0.7704/0.3407,
532 bytes versus 540 expected, frame 0x18. Eight expression-staging/blink
variants all reproduce the first batch's best output. Do not replay these
equivalent families. The fractional-hour calculation is sunk into the
interpolation path rather than emitted at entry; the signed blink remainder
correction is simplified away. Inspect those mechanisms before another batch.
Its preset-table end uses jtbl_82409058 only as a sentinel, not a local
switch: no rodata-subsegment change is justified by this owner.

## Native RGB interpolation / scene synchronization — 2026-10-15

Two accepted owners, **222 words / 888 bytes**, file **51 C / 28 ASM →
53 C / 26 ASM**. Both link-verified combined full-ROM gates; solo native.

| Owner | Name | Original span / frame | Runner batch |
| --- | --- | --- | --- |
| `func_82405244` | `Fragment13_LerpRgb` | 592 bytes / no frame | `b5f62de5a6f345c8bc8f12cf3b77121c` |
| `func_82407228` | `Fragment13_SyncSceneSelections` | 296 bytes / 0x60 | `d9b1822d176a4207a864a4b323ec8089` |

RGB: read each base byte as an unsigned word before converting to float;
keep the channel difference signed and the final conversion unsigned.
The ordinary three assignments match on the first of eight submitted
candidates. Reversing the floating sum changes the emitted schedule.

Scene sync: resolve eight current selections using the existing grouped-list
entries/starts, then forward them with group, daylight (hours 6 through 22)
and visible-state (1 or 2) flags. A natural eight-iteration loop is unrolled
by IDO. Use the actual typed parameter, not a redundant root-pointer local;
declare the real counter after the local eight-word array. This gives the
original array home sp+0x40 and frame 0x60. The 284-byte C body plus the
existing 12-byte padding directive preserves the original 296-byte span:
three trailing NOPs at 0x82407344–0x8240734C. No fake local or manual unroll.

Twenty-four candidates submitted. The first eight isolate address-tree
shape; current-selection-first is the original pointer-add order. The next
eight remove the pointer alias and compare flag forms; a padding directive
placed before the function does not test its tail and is not evidence of a
tail fix. The final eight vary real scalar homes/flags with padding after
the function; array-before-counter and inline flags accept. Do not replay
the folded unsigned-range flag forms or the redundant pointer local.

Fresh and twenty-leading-blank whole-object controls preserve section
bytes/layout, all 79 original starts/full spans, both frozen accepted spans
and 77 untouched spans. The scene-sync ELF function size is 284 bytes plus
the separately emitted 12-byte alignment tail. Normal forced retail-ROM
comparison and host checks for both touched sources pass; all 22 tooling
tests pass. Update existing callers and add two US compatibility aliases.
No tools, binaries, storage objects or invented helper functions committed.

## Native grouped-item labels — 2026-10-15

`func_82402A14` → `Fragment13_GetGroupedItemLabel`: **66 words / 264 bytes**,
frame 0x20; file **53 C / 26 ASM → 54 C / 25 ASM**. Link-verified combined
full-ROM acceptance, batch `0ba55387746f447d88092a85b9dea292`.

Move the existing item, pointer-span and grouped-list declarations before
their first use; split the item record's opaque prefix to expose the signed
label index at +6 while preserving id/value at +8/+10 and the 12-byte stride.
Fresh/twenty-blank controls prove these declaration refinements leave the
whole object unchanged before probing.

Preserve the empty-label return for an out-of-range entry, negative-group
category labels, final-entry label and descriptor-indexed label lookup.
The original full-width group argument remains live for indexing; narrow it
only at the existing count helper's s16 boundary. An extra named narrow local
puts its home at sp+0x18 instead of the original sp+0x1C. Eight candidates;
the first inline-cast form accepts. Add the behavior-backed US alias without
changing address-keyed symbols, prototypes elsewhere, compiler or layout.

After naming, fresh/twenty-blank controls preserve all section bytes/layout,
all 79 original starts/full spans, the frozen accepted body and 78 untouched
spans. Forced normal retail-ROM comparison, host syntax check and all 22
tooling tests pass. No scratch tools or binaries published; solo native.

### `func_82402B1C` — requeue, scrolling indicators and stack/value roles

195-word / 780-byte owner remains ASM. Sixteen compared candidates preserve
the outer sliding-frame call and both direction-dependent indicator branches,
including repeated count calls, triangle-wave fraction and separate final
constants. First family best normalized/raw **0.9487/0.5077**, correct size,
frame 0x50 rather than 0x60. Named right-indicator X improves raw to **0.5282**
with frame 0x58, still 780 bytes. A named selection alias produces 804 bytes;
splitting the negative starting X from final X produces 832/856 bytes and
does not fix the target. Cached icon Y and guard-return/ternary spellings do
not improve the first basin. One duplicate-parent batch was refused before
compilation; it consumed no hypothesis budget.

Next: investigate the genuine fraction/triangle/result lifetimes. Target
keeps the incoming selection in f14, fraction in f12, and copies the triangle
result from f0 to f2. The first candidate instead uses f12 for input/triangle
and f2 for fraction, with different spill homes. Diagnose those value roles
before more scalar aliases; do not pad the frame, invent unused locals or
alter the established helper interfaces. The missing optional draft CLI in
the public clone is not a compiler failure; all candidates used read assembly.

## Native panel corners — 2026-10-15

`func_8240182C` → `Fragment13_DrawPanelCorners`: **127 words / 508 bytes**,
frame 0x60; file **54 C / 25 ASM → 55 C / 24 ASM**. Link-verified combined
full-ROM acceptance, batch `9f3c581ef96842209c96d511107e7eff`.

Preserve the four-pixel minimum guard, incremented extents, texture setup,
original render-mode bits, F8/FF/7C/FF environment tint, pipe sync, four
eight-pixel corner draws and final display-list restore. Repeated integer
coordinate casts in the calls let Uopt retain the three actual float spills;
named coordinate aliases additionally reserve source homes and enlarge the
frame to 0x68/0x70 without changing instruction count. Eight corrected initial
variants and eight named-coordinate masks; the no-alias mask accepts first.
Eight earlier declaration failures came from overriding existing prototypes
and symbol types; remove the overrides, not the established interfaces.

After formatting, duplicate-extern removal and US compatibility naming,
fresh/twenty-leading-blank whole-object controls preserve every section's
bytes/layout, all 79 original starts/full spans, the frozen accepted body and
78 untouched spans. Normal forced full-ROM comparison, host syntax check,
22 public tooling tests and diff whitespace checks pass. No new helper,
storage, padding, compiler/layout mutation, gate bypass or scratch artifact.

### Scrolling-indicator requeue update

`func_82402B1C` now has **80 compared candidates** in this campaign (16
previously recorded plus 64 this continuation). It remains ASM. The best
source reproduces **all 195 instruction opcodes and registers**, frame 0x60
and 780-byte length; normalized/raw **1.0/0.9179**. Direct byte comparison
isolates exactly 16 differing instruction words: only index spills at sp+0x34
instead of +0x38 and fraction spills at sp+0x30 instead of +0x34. Triangle
spill +0x44 and the rest of the function agree. This is not acceptance.

Measured advances: keep right-arrow scales as nested conditional expressions
inside the draw call to preserve the original result moves. Reuse a genuinely
read integer temporary for the starting X before converting the selection
index, retain a real context alias, and reuse a float pulse for triangle
construction and the first-arrow output. The pulse-to-triangle copy restores
the original f0/f2 roles; input selection/fraction stay f14/f12. Every stored
temporary is read: no dead initial assignment is installed.

A calibrated fixed-interface 45-second permuter improved 839→287 but was
not exact. Its best source contains an unread initial index write; reject
that scaffold. Test its legitimate context/value-lifetime hints separately.
Eight scalar declaration orders leave the same two spill slots unchanged.
Named icon-Y carriers introduce wrong homes/scheduling; split negative-X
locals produce 832-byte bodies. Do not replay these families unchanged.

Next: identify the spill-allocation event before the index/fraction homes,
not another register permutation. A real named count-call result is an
untested source-level hypothesis; a compiler spill-allocation trace is the
stronger diagnostic. Do not insert a dummy slot, change interfaces or pad
the frame. All sources, objects and calibrated search results remain local.

## Native textured panel border — 2026-10-15

`func_82401570` → `Fragment13_DrawTexturedPanelBorder`: **175 words / 700
bytes**, frame 0x68; file **55 C / 24 ASM → 56 C / 23 ASM**. Link-verified
combined full-ROM acceptance, batch `61fcbec4789d475b9ff5a95058d7af8c`.

Preserve the four-pixel size guard, texture setup, original render-mode bits,
four corners followed by four stretched edges, all original UV offsets and
stretch factors, and the final display-list restore. Ordinary integer
coordinate expressions and the existing float draw interface match on the
first of eight submitted candidates. Keep `(origin + extent) - 4`; grouping
the extent subtraction first retains all opcodes but changes load/spill
offsets. No named coordinate aliases, artificial local or manual assembly.

Format the new C, remove only duplicate injected externs and add one US
compatibility alias. Fresh/twenty-leading-blank controls preserve all section
bytes/layout, 79 original starts/full spans, the frozen accepted body and 78
untouched spans. Forced normal retail-ROM comparison, host syntax check,
22 public tooling tests and diff whitespace checks pass. No new helper,
storage, padding, signature/layout/compiler change or gate bypass committed.

### Scrolling-indicator spill-plan follow-up

`func_82402B1C` remains ASM after **112 compared candidates** total: this
continuation adds eight named count-result masks, eight address-conversion
forms, eight grouped phase-record forms and eight typed-texture forms. None
improves the retained exact-opcode/register leader's 16 differing spill-offset
words (normalized/raw 1.0/0.9179). Do not replay these families unchanged.

Logging-only optimizer/code-generator copies were calibrated on the current
known object, the retained leader and the named-count control. All twelve
stock/logging-off/logging-on/twenty-blank builds preserve complete section
bytes/layout, FUNC/OBJECT symbols and relocation topology. The ordinary
`gettemp` and UGEN dynamic-spill hooks do not allocate these slots. The
optimizer's separate `spilltemps` path does; a source-line/web-ID association
links its pre-globalcolor ordinal 25 to this owner's globalcolor ordinal 26.

Measured leader plan: webs 10 and 23 share temp 0 at -40; web 39 uses temp 1
at -44; web 44 uses temp 2 at -48; web 67 uses temp 3 at -52. The count local
shifts the whole temporary area by four bytes, not just the two offending
slots. This is why it cannot repair the residual. Correctly typed texture
pointer declarations also preserve the complete known object but do not
change the leader's two slots; that optional metadata experiment is reverted
and is not part of the border change. No interface mutation was installed.

Next: inspect the spill-slot interference/reuse decisions for webs 23/39/44
and the provenance of their expressions, not declaration order or frame
padding. The useful question is why the retained leader cannot reuse temp 0
for the index, while the target's index/fraction offsets are four bytes
higher and its final icon-Y spill already agrees. Do not call this a stock
compiler impossibility. All diagnostic drivers, compiler copies, generated
code, objects and traces stay local and unpublished.

### Colored panel fill and shared clipped texture primitive

Accepted `func_82401A28` as `Fragment13_DrawColoredPanelFill` (235 words,
940 bytes, frame 0x18) and `func_82400BD0` as
`Fragment13_DrawClippedTextureRect` (268 words, 1072 bytes, leaf). The file
advances from 56 C / 23 ASM to 58 C / 21 ASM. Runner batches
`5f75140481a043f19818377a913666ba` and
`860c3a8c88c840ef9f4b45098d783e52` each report accepted, link-verified and
a successful combined full-ROM gate.

The fill needs the SDK's masked color-pack expression tree in G/B/R order,
without changing the RGB bit positions. Raw unmasked shift/OR spellings
change scheduling. Twenty-four submitted candidates identify the masked-tree
winner (later candidates are skipped after acceptance). The texture primitive preserves the original floating clipping,
integer-before-quarter-pixel coordinate conversion and SDK scissored texture
rectangle expansion. Its UV formals are signed halfwords, as the original
stack loads/stores show. Narrowing both 1024-scaled steps to signed halfwords
restores four sign-extension instructions missing from the initial eight
candidates; the first corrected candidate accepts. Sixteen candidates were
submitted across these two texture batches. No artificial frame or padding.
The existing forward declaration was corrected consistently; redundant
declarations were removed after acceptance. All compiled callers are neutral.

The texture-step batch accidentally logged to the local claims file. Its
single appended JSONL row was recovered verbatim into normal probe statistics,
verified equal and unique by batch ID, and the original claims JSON restored
from its preserved prefix. Candidate, link, gate and timing evidence remain
unchanged; no provenance bypass was used. This was a logging-path error, not
a successful probe being promoted without its gate.

After formatting and behavior-backed naming, fresh and twenty-leading-blank
controls preserve all section bytes/layout and all 79 original function
starts/sizes/full spans: two accepted spans and 77 untouched spans. Forced
normal native `gmake rom COMPARE=1`, host syntax checking and all 22 tooling
tests pass; ROM MD5 remains `1561c75d11cedf356a8ddb1a4a5f9d5d`. Only C,
compatibility aliases and these notes belong in the publication.

### Confirmation dialog renderer: requeue

`func_824046A4` remains ASM. Eight initial candidates failed compilation due
to a synthesized wide-argument `Gfx_SetScissorRect` declaration conflicting
with the real signed-halfword prototype. Calling its original compatibility
symbol with the actual prototype avoids that synthesis conflict. Eight
corrected candidates compile; the best has 508 bytes, frame 0x50,
normalized/raw 1.0/0.9685 and `register_allocation_only`, first difference at
325 (`lui a1` expected, `lui a0` actual). Cached text-Y variants grow the
frame to 0x58 and are worse. Next: inspect the four differing words around
the text helper's argument setup, preserving real helper signatures and the
original scissor height. Do not replay the x-width/guard/Y-cache family.

### Confirmation dialog renderer accepted: real callee result

The requeue above is resolved. `func_824046A4` is now
`Fragment13_DrawConfirmationDialog`, 127 words / 508 bytes, frame 0x50.
Batch `7e03f750b87145e9a4c05b13d88df96e` accepts the first corrected
candidate with link verification and a combined full-ROM gate (7.732 seconds
probe, 1.448 seconds gate). File advances 58 C / 21 ASM to 59 C / 20 ASM.

Before that success, eight display-head lifetime forms (separate increment,
local packet, head alias, pre-advance; second list alone or both lists) all
failed and worsened size/frame or allocation. They are not the next family.
The decisive evidence is the existing definition in `src/4CC20.c`:
`func_8004D19C` returns `s32`, but this file's two forward declarations said
`void`. Retyping both declarations consistently to the real five-word-argument
signature repairs the four display-head register words. This is a declaration
correction supported by the callee, not an invented result or argument used to
steer allocation. The actual signed-halfword scissor signature and the sound
helper declaration remain unchanged. The new dialog view names only the
observed offsets; the original scissor height, selected-image ordering and
text coordinates are preserved.

Fresh and twenty-leading-blank builds match every byte and layout of the
frozen accepted object's text/rodata/data/bss and all 79 original spans.
The 78 untouched spans, including all existing callers of the retyped image
helper, also match the pre-dialog object. Formatting, duplicate-extern cleanup,
an explicit actual `func_8004989C(s32)` declaration and behavior-backed naming
are object-neutral. Forced normal retail-ROM comparison passes with MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Scratch generators, objects, compiler
copies and ROMs remain local and unpublished.

### Page-transition arrows: requeue, six-word float spill residual

`func_8240330C` remains ASM after 64 compared native candidates. Best retained
source is local `native-f13-page-arrows-homes.json`, candidate 0:
`f13-page-arrows:observed-homes:prefix-pulse-y-animatedY:early-stage-False`.
It has all 198 words / 792 bytes, frame 0x58, and the exact opcode/register
sequence (normalized/raw 1.0/0.9697). Exactly six instructions use the
position float spill at stack+0x30 instead of the original stack+0x28;
the y spill +0x2C, retained triangle +0x34 and page count +0x3C agree.
Differing instruction indices are 98, 100, 123, 126, 141 and 145.

Useful progression: a shared pulse carrier for the initial triangular phase
and subsequent arrow arguments removes four extra instructions. Separating
the initial interpolated position from its post-call use and retaining the
actual float y calculation restores the frame. Placing the real count and
triangle locals in the observed home order repairs their stack offsets.
No dummy variable, artificial frame padding or signature mutation is used.
Do not replay literal/local divisor, count/guard order, in-place triangle,
upper-page local, conversion local, early/late stage copy or input-factor
reuse families unchanged. Input-factor reuse is substantially worse.
Eight subsequent two-field phase-record variants (initial/working position,
fraction or animated y, both field orders) also preserve the same six-word
spill residual. They do not justify another aggregate-layout sweep.

Logging-only compiler controls were revalidated on this current known object
and the leader: stock, logging-off, logging-on and twenty-leading-blank
objects preserve complete section bytes/layout, function/object symbols and
relocation topology. The leader's pre-globalcolor spill-plan ordinal 26
corresponds to globalcolor ordinal 27 (line 334 and common web IDs); UGEN
procedure 26 starts at this owner's source line 320. Measured plan: web 28
uses temp 0 at -40; web 34 uses temp 1 at -44; integer web 54 reuses temp 1;
float web 85 uses temp 2 at -48. These offsets identify the candidate's slot
assignment, not a proof of the target's internal compiler decisions.

A separately calibrated, fixed-interface, stack-scored 45-second native
permuter reproduces both its base and target instruction words, but does not
reach exact (48 -> 24). The best mutant adds an empty `if (arg1)` and is
rejected as scaffolding, not installed or treated as source evidence. Next:
inspect interference/reuse between web 28 and float web 85 to find a real
expression/lifetime change that lets the retained position reuse temp 0.
This is not evidence that the stock compiler cannot emit the target.

### Scaled/tinted icon renderer: requeue, channel topology established

`func_8240239C` remains ASM after 40 native candidates. Best opcode-shape
candidate is local `native-f13-scaled-icon-channel.json`, candidate 1,
`f13-scaled-icon:channel-update:all-reads-False:explicit-False:inline-inverse-True`:
278 words / 1112 bytes, frame 0x50, normalized/raw 0.9748/0.5863. All-read-first
channels are worse. Do not mistake the normalized score for a near-exact
register result: many operands and some scheduling still differ.

Recover scale `1 + amount`, blend clamped to [0,1], original texture height
minus three, integer center positioning, the original minimum-scale cell,
RGB interpolation toward 220, and reciprocal texture stepping. Inline the
original dimension expressions rather than preloading two dimension locals.
Each byte channel must be loaded and updated sequentially before emitting
the environment-color command; direct expressions inside that macro are
evaluated in a different order. Byte channel carriers and an inline reciprocal
produce the original size/frame. Remaining opcode differences are around
display-head materialization, FPU conversion restore scheduling, color-pack
mask ordering and stack-argument stores. Next: follow the display-head value
lifetime through the first channel conversion, rather than permuting the
already-established clamp/dimension forms.

The original visibility call supplies context, id and two dimensions. Its
probe uses an old-style declaration at that call site, consistent with the
later two-argument view; it does not change the actual helper definition or
invent dimensions. A separate consistent correction to the texture-bind
helper's real `s32` return was also tested through companion edits. It does
not close the owner (best opcode/raw 0.9676/0.6043 for the channel candidate),
and no declaration correction or candidate body was installed. No gate was
bypassed and no failed source edit remains.

### Dialog input accepted, native partial batch

`func_82404440` is now `Fragment13_HandleConfirmationInput`: 73 words /
292 bytes, frame 0x18. File advances 59 C / 20 ASM to 60 C / 19 ASM.
Eight submitted candidates identify the word-sized button local, two-case
switch and common navigation/cancel return. The byte-sized button local has
the same opcode sequence but uses v1 instead of the original v0; explicit
early returns and if/else sound dispatch do not match. Winning batch
`4e5058597a2d40cdbabf1cb2425f4bec` reports accepted, link-verified and a
successful combined full-ROM gate (5.701 seconds probe, 1.182 seconds gate).

Preserve phase 8.0, signed selection checks, right/left priority over confirm
and cancel, selection values 0/1/2, state 3 and the original sound requests.
These original call sites pass only the sound word. A C89 old-style sound
declaration at this owner preserves those calls, while the existing later
`extern void func_800226C0(s32, void *);` and contextual caller are unchanged.
No callee definition, invented optional argument or verification setting is
changed. Host syntax checking passes, but now reports eight additional
deprecated-non-prototype warnings, besides the existing unrelated implicit-call
warning. This is deliberate historical call compatibility, not C23 support;
do not describe all nine warnings as pre-existing or silence the check.

After formatting and behavior-backed naming, fresh/twenty-leading-blank
whole-object controls preserve text/rodata/data/bss bytes/layout and every
original function start/size/full span. The 78 untouched spans, including the
contextual sound caller, match the pre-input object. Normal forced native
retail-ROM comparison passes (MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`),
as do all 22 tooling tests and whitespace checking. No new helper, data,
padding, compiler or layout change is part of the source acceptance.

The state-dispatch sibling `func_824045B4` has a real five-entry jump table.
Its file currently lacks an explicit per-file `.rodata` subsegment in the
YAML, so no switch probe was attempted before that layout prerequisite.

### Dialog and scene dispatchers accepted after layout prerequisite

Two owners now have matching C: **209 words / 836 bytes**, advancing this
file from **60 C / 19 ASM to 62 C / 17 ASM** (79 original functions).
The eleven data-only GLOBAL_ASM includes described below are not functions.

| Owner | Name | Words / bytes | Frame | Accepted batch |
| --- | --- | --- | --- | --- |
| `func_824045B4` | `Fragment13_UpdateConfirmationDialog` | 60 / 240 | 0x38 | `df985b59995942f68bbd4a6b9487b71c` |
| `func_82406A78` | `Fragment13_UpdateGroupScene` | 149 / 596 | 0x48 | `09338ac6fb7a4b7c938d1131dc1f4d8b` |

Both runner records are **relocation-masked, sequential full-ROM accepts**,
not link-verified accepts. The regenerated ASM baseline calls old compatibility
names as UND symbols, while C calls a definition in this translation unit.
The masked comparison permits the normal sequential gate; only its byte-exact
retail-ROM result establishes acceptance. No check or provenance bypass.

#### Layout and preserved data

The read-only planner identifies `0xF6F80..0xF7120` for this file. Add its
per-file `.rodata` subsegment and a bare `rodata` tail for the original
relocation data. The pinned splitter is splat 0.25.0 / spimdisasm 1.35.0-dev0.
A first split correctly exposed undefined shared cells rather than silently
providing a working layout. Preserve the original eleven named cells at
`D_82408F00..D_82408F78` as generated data-only GLOBAL_ASM includes, with exact
sizes and force-not-migration metadata, following the fragment 14 convention.
Their combined 0x158-byte prefix equals the original ROM bytes. This is
existing data, not new storage or authored replacement assembly.

The first jump table also serves as the lighting iterator's end marker.
Force its migration to its original earlier dispatcher; preserve the marker
after C emits an anonymous table with a conditional linker alias relative to
`fragment13_RODATA_START + 0x158`. Restore the three clock scale cells as the
ordinary `65535.0f` literals that regenerate the original three distinct
four-byte pool cells after that table. The later 0.95 and 3000.0 cells and
second jump table retain their order. The owner object has exactly 0x1A0
read-only bytes. With both dispatchers still ASM, the full retail-ROM gate
passes and all 79 function starts/sizes are unchanged; the known input sibling
also retains identical instruction words before any switch candidate.

#### Source mechanisms and compatibility

Dialog: source case order 1/2/3/0/4, status initialized to zero, state reload
after each handler and original visibility/rectangle queue. First of eight
submitted candidates accepts. Caching state makes an extra instruction.

Scene: preserve camera/lighting updates, all six queued rectangles, previous
mode assignment, the 0/1/2 confirmation outcomes and case 4's early return.
The draft omitted that case, so the assembly was the oracle. Keep mode
assignment in the switch expression and confirmation result as a nested
switch expression rather than two named locals; this restores frame 0x48,
change flag +0x44 and dialog spill +0x34. Twenty-four candidates submitted.

The original sound protocol supplies a sound word and optional context.
Consistent `void func_800226C0(s32, ...)` declarations support both actual
call shapes without a fabricated argument. A one-argument function-pointer
cast instead emits an indirect call and two extra words, so it is rejected.
The variadic correction is installed with the scene candidate through runner
companion edits. All existing callers' raw instruction spans remain identical;
the eight old-style-declaration warnings from the preceding input PR disappear.
Keep the actual group-selection pointer view at its call site. No new helper,
fake local, padding, compiler change or warning suppression is installed.

#### Final controls and coverage accounting

After formatting, deduplication and naming, fresh/twenty-leading-blank builds
preserve every text/rodata/data/bss byte and section layout against the frozen
accepted object, all 79 original starts/sizes/full spans, both accepted bodies
and all 77 untouched raw spans against the post-layout assembly baseline.
Removing the eleven generated data includes into recoverable scratch storage
and re-running the canonical split regenerates all eleven byte-identically;
the normal full ROM still equals retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Host syntax checking passes with only the
existing unrelated implicit-call warning; all 25 tooling tests pass.

The coverage counter previously counted data-only D_/jtbl_ includes as code
owners, making preserved constants look like lost function matches. The
existing counter now excludes only address-keyed data/table names, retaining
ordinary and named functions. Three regression tests cover mixed owners,
data-only files and staged input. The function gain in this batch is two,
not eleven data includes or an unrelated historical counting correction.
Generated COVERAGE.md remains managed by CI.

## 2026-10-15 — group-list transition accepted

`func_82406880` becomes `Fragment13_UpdateGroupListTransition`: 126 instruction
words / 504 bytes, original frame 0x38. File advances **62 C / 17 function ASM
to 63 C / 16 function ASM**, from 79 original functions. The eleven preserved
data includes are not functions. Solo native macOS; no agents or containers.
Runner batch `028ad84224614d91b7fa30ef2403e00c` is link-verified and accepted
by the combined full-ROM gate, with statistics and host checks enabled.

The routine eases the current phase, advances/clamps the visibility timer,
synchronizes rendered mode with requested mode at zero, preserves transition
sounds 0xAA/0xA9, then dispatches group-list/page-arrow rendering with original
positions, selection interpolation and direction. The first eight variants
agree in size/frame and 125 of 126 words; the sole residual is the timer
addition's floating operands. Write `func_82403F10() + phase`, not the reverse.
The first of the corrected eight variants accepts. Do not cache the group
before a callback that can change the root state.

The runner's advisory register-tie warning appears even in this accepted
result. It is not proof of an impossible source shape and must not overrule
the actual link verification and retail-ROM acceptance.

After formatting, removal of newly redundant prototypes and naming with a
compatibility alias, fresh/twenty-leading-blank controls preserve complete
frozen text/rodata/data/bss bytes and layout, all 79 original function starts,
sizes and spans, and all 78 untouched raw instruction spans. No helper,
padding, storage, compiler patch or verification bypass is installed.

Forced normal `gmake rom COMPARE=1` after cleanup/naming matches retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`; the host syntax check passes with only
the pre-existing unrelated implicit call warning. All 25 tooling tests and
whitespace checks pass. Scratch generators/proofs and binary outputs stay local.

### List-input requeue, not accepted

`func_82406560`: sixteen candidates, best normalized/raw 0.8100/0.6450,
expected 800 bytes versus 792, correct frame 0x20. Two families tested:
word/halfword button local, literal/local five-column divisor and row/count
initialization order; then shared handled-tail control flow, halfword count,
row reuse for the left-limit value, base/index expression order and captured
post-predicate selection/count. Shared-tail versions are 784 bytes and do not
improve the result. No candidate is installed.

The decisive mechanism is division placement: original computes both signed
divisions before directional guards, while these candidates sink row division
into the up/down path and page division after the left guard. Address additions
also reverse base/index operands, and the timer addition is reversed. Keep the
real two-argument `func_824048A0(root, oldSelection)` signature, signed random
modulo four and sound protocol; draft extra call arguments are not evidence of
real additional formals. Next hypothesis: model the actual grouped-state
subobjects and semantic quotient lifetimes before another source family;
do not replay scalar declaration permutations or add unused call arguments.

## 2026-10-15 — group-scene rendering accepted

`func_82406E14` becomes `Fragment13_DrawGroupScene`: **157 instruction words /
628 bytes**, original frame 0x28. File advances **63 C / 16 function ASM to
64 C / 15 function ASM**. Together with the transition routine above this is
283 words / 1,132 bytes in the current partial batch.

Runner batch `8f9d89e855b54fe58f04f952b2885bf0` accepts the first of eight
submitted candidates through the normal sequential full-ROM gate. This is
**not link-verified**: the object check reports relocation drift for the
already-named same-translation-unit confirmation callee. The authoritative
linked ROM is byte-identical; no relocation mask, provenance override or
verification bypass is claimed for this record.

Preserve the initial full-redraw result, short-circuit selector checks in
order 4, 5, 7, 6, both four-case state dispatches with original panel passes,
selected-content clipping/restoration and frame, and the final list,
confirmation and auxiliary-panel calls. Use ordinary switches: spelling
both dispatches as if-chains produces 596 bytes, frame 0x30 and raw 0.4076,
not the original 628 bytes/frame 0x28. No new jump table/layout work is needed.
Keep the existing integer panel-handle ABI views and pointer selector view;
no extra call arguments are invented.

Remove runner-injected duplicate declarations after acceptance. Name the
existing frame caller's reference and retain the old symbol via a US
compatibility alias; JP and address-keyed symbol entries stay unchanged.
Fresh/twenty-leading-blank controls preserve all complete frozen sections,
all 79 original starts/sizes/full spans and the 77 untouched raw function
spans against the pre-batch object. A separate fresh caller build preserves
its complete section bytes/layout after the call/prototype rename. The
forced normal native full-ROM build after naming/cleanup matches retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Scratch scripts, generated assembly,
objects, compiler binaries and ROM outputs remain local.
Both changed C files pass the host syntax check with only their existing
warnings; all 25 tooling tests and whitespace checks pass.

## 2026-10-15 — camera/list/panel requeues, no new acceptance

The following investigations leave all three owners ASM. They do not change
the file's **64 C / 15 function ASM** count. Each scored family uses the
native runner with statistics enabled; there is no compiler/provenance bypass.
Fresh and twenty-leading-blank controls still reproduce the frozen accepted
object, all 79 function spans, the 77 untouched pre-batch spans, the separate
caller object and the retail ROM before these investigations.

### `func_82406060`: camera-input requeue

Twenty-four compared candidates plus eight initial compile failures. The
initial failure is a stale later `void *` owner declaration versus the typed
group-state definition. Consistent prototype and existing-caller cast edits
are tested transactionally, never installed alone. Two malformed companion
preflights are corrected before compilation and are not source hypotheses.

Best shape is normalized/raw **0.9749/0.6192**, 948 rather than 956 bytes,
frame 0x60. A distinct same-size basin is **0.9707/0.7238**, 956 bytes/frame
0x60. Preserve both rather than ranking their scalar scores as equivalent.
Families: real axis/magnitude locals, target-vector pointer, vector and
handled-local placement; typed versus byte-addressed input fields; shared
handled join versus structured B/A chain; arithmetic operand ordering and
the actual previous/current-group store order.

The first differing raw word consistently uses `$v1` instead of `$t6` for
the pressed-button load. These candidates reuse that load for A after the B
guard, whereas the original reloads it. Analog fields also materialize one
shared base instead of the original independent `$at` accesses. A magnitude
local restores vector/axis stack homes but changes the absolute-threshold
branch merge and target-pointer spill. No evidence justifies adding volatile
accesses or a fake call to force reloads. Next: trace the controller-value CSE
and constant-address materialization before another declaration family; keep
that distinct from the stack-home/absolute-branch residual.

### `func_82402E28`: list-rendering requeue

Sixteen compared candidates, best normalized/raw **0.8474/0.5016**,
1284 rather than 1252 bytes. One leader has the original frame 0x70 but its
three-byte color copy is at +0x6C rather than +0x5C. Preserve the RGB copy,
header/label clipping, both directional icon paths and original negative
blend cells. The candidate narrows the real fourth formal to `s16`, with its
stale later declaration corrected in the same transaction; no edit is installed.

Families: RGB/local placement, named versus inline blend and label results,
and separate versus reused header/arrow index and fraction lifetimes. The
second family does not change the opcode-shape result. The original computes
the left-arrow geometry before the directional branch; these candidates sink
and duplicate it into the branches, while caching width/offset/display-list
bases differently. Next: diagnose that geometry/address lifetime, not more
scalar-order permutations. The original named blend cells are preserved;
no fresh rodata layout issue has been established.

### `func_82403C84`: textured-panel requeue

Live source verification corrects a stale handoff assumption: the current
`src/4CC20.c` definition is **`s32 func_8004D27C(u8 *, s32, s32)`**, exactly
three arguments, not five. Its body uses all three to load texture metadata.
Use that declaration and the real dimension/format getter signatures. Do not
invent trailing arguments or an indirect-call/old-style workaround.

Move the existing motion-vector/group-anchor definitions and their existing
extern earlier in the same source so this earlier owner can use those types.
This creates no new type/storage/helper: fresh/twenty-leading-blank controls
preserve every complete section byte/layout and all original function spans,
and the normal full-ROM build passes while the owner remains ASM.

Twenty-four compared candidates. Best normalized/raw **0.9527/0.5621**,
676 rather than 652 bytes, frame 0x88 rather than 0x70. Families: pointer versus
indexed asset loop, array position, separate width role; named format result,
halfword bit count and for/do shape; if-chain versus switch, real stride/
dimension temporary reuse and default-value placement. The current best
keeps the switch and reuses the actual stride/dimension temporary; earlier
best-size-equivalent bodies are 0.9408/0.5385.

The decisive extra six words include hoisting format constants 1 and 3 into
`$s6/$s7`, their saves/restores, and the two initializers. The original uses
local `$at` immediates and only saves through `$s5`. If-chains remove two words
but lose the original four-case shape and remain wrong. Next: calibrate a
loop-constant allocation/hoisting trace on this residual before tuning frame
layout. The literal-hoist observation is not proof of an impossible frontend
or a reason to install patched compiler output. Candidate bodies and logs
remain local; no rejected source is installed.

## 2026-10-16 — clamped list interpolation accepted

`func_824070E4` becomes `Fragment13_GetInterpolatedListPosition`: **35 words /
140 bytes**, original frame 0x18. The historical register-role requeue above
is closed. File advances **64 C / 15 function ASM to 65 C / 14 function ASM**.
Current pending partial batch now contains three functions, **318 words /
1,272 bytes**, not a claim that all remaining owners are solved.

Runner batch `ec2962c5579f45dba8503cd24ac6ec95` is **link-verified**, combined
full-ROM accepted, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. No compiler, layout,
padding or verification change is needed. The callback retains its real
`f32 (*)(f32)` signature; the root retains its public `void *` ABI and uses
the existing group-state type through a genuine local pointer.

The first eight new lifetime candidates still have the wrong word-value
registers. A fresh stock/off/on/twenty-leading-blank trace calibration preserves
complete section bytes/layout, symbols and relocations for the known source
and candidate. It identifies two equal-cost word webs: cost 2, two uses and
three interference neighbors each, assigned `$v1`/`$a1` in the wrong roles.
The successful combination defines **end before start**, keeps both loads
after the callback, clamps start, converts start to a float base, then clamps
end and interpolates. The actual typed `list.counts[group]` view also restores
the original base/index addition order. Earlier reverse-load tests used a
named index, while inline-index tests inherited the other load order; they
had not tested this combination. The third candidate of the eight-cell
web-order batch accepts. There were 32 earlier submitted candidates, eight
new lifetime candidates and eight web-order candidates; the runner stops
installation after the first accepted owner.

The untyped counterpart in the final batch agrees in 34 of 35 raw words but
reverses the address-add operands. It is not an acceptance. The runner again
prints its advisory "source-shape variants will not close this" even on the
accepted result; actual diagnostics/gates take precedence over that warning.

After formatting and naming with a US compatibility alias, fresh and
twenty-leading-blank builds preserve all frozen text/rodata/data/bss bytes,
all 79 original starts/sizes/full spans and **76 untouched** pre-batch raw
function spans. The existing renamed scene caller also retains identical
complete section bytes/layout. All scratch drivers, traces, compiler copies,
objects, generated assembly and ROMs remain local.
Forced normal full-ROM verification after cleanup/naming matches retail;
host syntax checking passes with the existing unrelated warning only. All
25 tooling tests and whitespace checks pass.

### Panel requeue follow-up: calibrated negative, not a compiler workaround

`func_82403C84` now has **48 compared candidates**. Fresh known/candidate
stock/off/on/twenty-leading-blank controls preserve every section byte/layout,
symbol and relocation. The logging-only optimizer trace locates constants
1 and 3 in webs 140/142 of procedure 34, with cost 2, five recorded uses and
nine interference neighbors, colored to physical registers 22/23 (`$s6/$s7`).
These are allocator webs, not instruction offsets.

Twenty-four new candidates test unsigned offset division versus shifting,
strict viewport bounds and loop form; format/index/offset signedness; pointer,
countdown and index endpoints with explicit/default eight-bit formats. None
removes the extra saved constants or improves the retained best
0.9527/0.5621, 676-byte/frame-0x88 leader. One old-body preflight is not a
compiler attempt and is replaced with an actual new counter-width hypothesis,
not a whitespace replay.

Flag diagnostics on scratch objects are separate from runner acceptance:
`-g0` is byte-identical to normal; `-g3` changes 52 already-C functions and
grows the candidate to 680 bytes; `-O1` changes 58 and grows it to 836 bytes.
Stock IDO 5.3 changes eleven already-C functions and still yields a 676-byte
nonmatching candidate. The known-source target remains ASM in those controls,
so its unchanged bytes are not evidence of a C match. No alternate flag,
compiler or patched artifact is installed. Keep the normal compiler and this
bounded negative; next useful work requires a new constant-lifetime mechanism,
not another spelling of these tested families.
