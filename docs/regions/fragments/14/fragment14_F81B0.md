# Fragment 14 selection setup

## 2026-10-15 follow-up — controller setup and commit handler accepted

Two of four larger related state/setup owners passed one normal link-verified
combined full-ROM gate. The file advances to **41 C / 14 ASM** owners.

| Owner | Name | Instructions / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_81300390` | `Fragment14_ConfigureControllerSelection` | 120 / 480 | 0x60 | `3668257f461042ad80508e0eb8ce092d` |
| `func_813019C8` | `Fragment14_UpdateSelectionCommit` | 133 / 532 | 0x30 | `3668257f461042ad80508e0eb8ce092d` |

Total: 253 instructions / 1,012 bytes, stock IDO 7.1, solo/native.

### Source mechanisms

- Controller setup preserves the bounded port checks, status store, slot
  panel setup, identity/name read, per-slot validity mask, page data bindings,
  resource lookup, transition arguments and conditional count.
- `func_8005D9E0`'s existing C definition copies two 64-bit words. Represent
  that actual 16-byte output buffer as `s64 info[2]`, keep the 16-byte name
  buffer, and declare the ID before the info buffer. This restores the
  original aligned info at stack+0x38, ID at +0x4C and name at +0x50, plus
  the pointer spill homes. Initialize the ID near the name/port block rather
  than before the initial calls. No dummy alignment member or padding.
- An explicit final if/else, rather than initializing -1 before a one-sided
  if, restores the target's ordinary branch and return-value delay slot.
  The consumed controller word is reused for the data pointer and count;
  each value is assigned before use and retains the original 32-bit ABI.
- Commit update preserves the signed panel-result branches, first-slot
  saved selection, 0x240/12-byte record strides, conversion helper, validity
  mask, optional default name, type-4 byte, advance call and mode store.
  Declaring result before the panel pointer restores its spill/reload at
  stack+0x2C instead of +0x28. All other instruction words already matched.
- Use `HAL_Strcpy`'s real signed-byte prototype with explicit pointer views.
  Verify formatting/extern cleanup, remove unused probe-only colors/types
  and declarations, name both owners and preserve address-keyed US symbols.
  Revert the naming tool's unrelated JP symbol rewrite.

### Verification

- Native baseline and known-matching whole-TU controls before candidates: PASS.
- Both normal runner `accepted`, `link_verified: true` and combined ROM gate:
  PASS, statistics and host checks enabled.
- After cleanup/prototypes/naming: fresh and twenty-leading-blank builds
  preserve all section byte views and allocatable layouts, all 55 original
  offsets/sizes, both accepted full spans and 53 untouched C/ASM spans.
- Forced normal build: byte-identical retail ROM, MD5
  `1561c75d11cedf356a8ddb1a4a5f9d5d`. Explicit host syntax check: PASS with the
  same 17 warnings as baseline. Public tooling tests: 22 PASS. Diff check: PASS.
- Only C, two US aliases and region notes are published. No scratch helpers,
  compiler changes, alternate probe types, generated assembly, objects, ROMs
  or JP changes. This is progress, not file/repository completion.

### `func_81300E34` — requeue, dialog setup address/value lifetimes

Best leader `f14-state:dialog:record-True:local-False:reverse-False` has
316/328 bytes, 0.9268 normalized / 0.5488 raw. It swaps the state/base saved
register roles, chooses different selected/idle/position homes and omits the
target's default-coordinate rematerialization around resource lookup 5.
Cached/direct dialog addresses, raw/record field views, local permutations
and three-field selection snapshots do not close it. The source call sequence
and signed metadata tests are understood, but this is not a near-exact match.
Next: inspect the default/conditional coordinate carriers and resource-helper
ABI with assembly evidence before more stack-local permutations.

### `func_81300570` — requeue, description coloring and text-box frame

Best leader `f14-state:textboxes:record-False:colors-False:int-False` has
440/448 bytes, 0.9018 normalized / 0.5982 raw. The target spills description
at stack+0x34 with no saved s0; the candidate colors it into s0, inflating
the frame from 0x40 to 0x48. Raw/record data views, byte/triple color indexing,
int/long kind, array/record text pairs and word/pointer text carriers do not
improve it. Next: inspect the description web's colorability and call-use
accounting against a known-matching control. No forced color or dummy read.

### Older residuals

The narrow-return dialog experiment was refused at preflight: its companion
target `func_813002D0` remains ASM-owned. No compiler attempt or metadata edit
occurred. Eight genuine address/return-carrier lookup probes then failed to
improve that owner. The earlier lookup, dialog and page-address requeues stay
active. Initial raw-array commit probes had a pointer-expression grouping
error and are not valid negative evidence; the reviewed record-field source
alone was accepted. Publish the two verified larger owners independently.

## 2026-10-15 follow-up — title, preview and page updates accepted

Three of five selected/resumed owners now have normal link-verified combined
full-ROM acceptance. The file advances to **39 C / 16 ASM** owners.
`func_8130183C`'s earlier frame requeue is resolved; its historical evidence
below is retained. The dialog and slot-editing page update remain ASM.

| Owner | Name | Instructions / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_8130015C` | `Fragment14_UpdateTitleText` | 58 / 232 | 0x20 | `234f4728e13647aca80367285ba0b909` |
| `func_8130176C` | `Fragment14_UpdateSelectionPreview` | 52 / 208 | 0x30 | `64897d9bbc2941feb5fb3c3c0b60b2b5` |
| `func_8130183C` | `Fragment14_UpdateSelectionPage` | 48 / 192 | 0x30 | `7e5fe024b8fd4960933bec29bb629e9a` |

Total: 158 instructions / 632 bytes, stock IDO 7.1. Solo/native, no agents
or containers. No helper function, compiler override, padding or fake branch.

### Source mechanisms

- Title: preserve the flag-selected localized text, 0x0200 metadata test,
  signed localized-name index at info+0x3E, embedded-name fallback and default
  resource 0x2B. Compare the cached pointer before updating text slot 1 and
  its scrolling state. Callee assembly proves `func_81700B8C` takes the text
  pointer as a second argument and returns a word result. The existing C
  definition proves `func_81700CDC` also returns a word. The accepted runner
  transaction corrects both declarations together with the candidate.
- Reuse the consumed flag argument for the signed name index. Keep the text
  as the sole explicit local; repeated split-address expressions let IDO
  spill the base at 0x18 and text at 0x1C without extra local homes. An
  explicit base local inflated the frame to 0x28. The title store uses the
  observed state field so its address rematerializes after the text calls.
- Merge that field into the existing record at **0x1A164**, retaining status
  at 0x1A168; remove the temporary alternate view. This is existing storage,
  not a new object. Add the text-lookup prototype from its real C definition.
- Preview: preserve the negative-result state 0, the positive 1/2/3 to
  states 3/6/7 mapping, position copy and context update. The three-case
  switch compiles as the observed branch chain, not a jump table.
- Page: retain the corrected two-argument first helper call, all view updates,
  position output and signed result branches to states 2/3. Use a direct
  expression for the page address, keep the panel local, and reuse the now
  consumed context word for the result. These mechanisms compose to restore
  both the 0x30 frame and original pointer homes; neither alone was enough.
- Apply conservative behavior names with US compatibility aliases, preserving
  address-keyed symbols. The naming tool's unrelated JP rename was reverted.

### Verification

- Native baseline / known-matching whole-TU controls before probes: PASS.
- All three normal runner `accepted`, `link_verified: true` combined ROM
  acceptance gates: PASS, statistics and host checks enabled.
- After record-view consolidation, formatting, prototype cleanup and naming:
  fresh and twenty-leading-blank builds preserve all section byte views /
  allocatable layouts, all 55 original function offsets and sizes, all three
  accepted full spans and 52 untouched C/ASM spans.
- Forced normal ROM rebuild: byte-identical retail ROM, MD5
  `1561c75d11cedf356a8ddb1a4a5f9d5d`. Host syntax check: PASS, same 17 warnings
  as the baseline. Public tooling tests: 22 PASS. Diff check: PASS.
- Publish only game C, three US aliases and region notes. No scratch helpers,
  compiler instrumentation, generated assembly, objects, ROMs or JP changes.

### `func_813010B0` — requeue, selected-result stack home

Best clean source: 264/264 bytes, 1.0000 normalized / 0.9697 raw. All words
except the selected-result spill/reload offset match: target stack+0x3C,
candidate stack+0x44. Frame 0x48 and the idle flag at stack+0x40 already match.
Leader: `f14-family:dialog:record-True:local-False:reverse-False`.

Eight initial variants tested record/raw views, cached/direct dialog address
and local order. Follow-ups tested inline result/flag expressions, small
record/array snapshots, scoped declarations/initializers and register hints.
Inlining the lookup result fixes its home but moves the idle read before
the lookup; it is not exact. A calibrated 45-second native permuter with
stack scoring reproduces source and target, then stays flat at **16 -> 16**.
No mutated candidate is adopted. Do not add dummy locals or use unsequenced
argument writes to manufacture the desired stack layout.

Next: inspect named-local versus temporary spill-home ownership on the two
leaders, preserving lookup-before-idle-read-before-count-query order. Future
probes need the real five-argument `func_8130FC80` and ten-argument
`func_8130FD10` declarations; unused probe declarations were removed here.

### Remaining page/lookup requeues

Six corrected-ABI inline-address compositions do not improve `func_81301648`;
its previous page-address coloring requeue remains active. The selected-slot
lookup is unchanged. Ship the three verified owners without holding them
behind these residuals; do not count the file or repository as complete.

## 2026-10-15 follow-up — advancement and mode-zero panel accepted

Two of the next four related owners passed one normal link-verified combined
ROM gate under stock IDO 7.1. The file now has **36 C / 19 ASM** owners.
The two update routines remain ASM with the requeues below.

| Owner | Name | Instructions / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_81300F7C` | `Fragment14_InitSelectionAdvance` | 45 / 180 | 0x38 | `659d95984ee2417790950ee0d25faedd` |
| `func_813012C0` | `Fragment14_InitSelectionPanelMode0` | 64 / 256 | 0x30 | `659d95984ee2417790950ee0d25faedd` |

The advancement routine preserves the signed saved selection at data+slot+
0x93C, forward-slot exhaustion test, reset calls, intermediate status clear,
seven setup arguments (both exhaustion flags), and final mode 1 store.
The mode-zero panel preserves the first-slot/type-4 guard, signed saved
selection lookup with 0x240 stride, negative-result clamp, existing 0xD18
panel / 0x1A154 binding and forward-exhaustion flag. Existing record fields,
word-sized selection/exhaustion locals and direct panel expressions match;
raw-offset alternatives did not. No new record or helper is needed.

Verification after naming, formatting, removal of unused probe declarations
and verified duplicate-extern cleanup: fresh and twenty-leading-blank builds
preserve all section byte views / allocatable layouts, all 55 original
offsets and sizes, both accepted full spans and all 53 untouched C/ASM spans.
Forced normal ROM rebuild: byte-identical retail ROM, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Host syntax check passes with the same
17 warnings as the baseline; public tooling tests: 22 PASS. Only source,
two compatibility aliases and region notes are published. Solo/native.

### `func_81301648` — requeue, page-address allocation

The 292-byte target saves only s0 and spills the page address at stack+0x24;
the 296-byte candidate colors that address into s1, changing the saved
register set and epilogue. Leader:
`f14-flow:abi-two-arg:func_81301648:reverse-False:cache-False:guard-True`,
0.9054 normalized / 0.8108 raw. Call sequence, positive/negative result
branches, slot clear and -1 byte store are understood, but not matched.

Important ABI evidence: `func_8130A044` reads incoming a1 (stored at callee
stack+0x7C, later used by the text/drawing calls). The update must call it
with the original context argument, not just the panel pointer. No move is
needed at the first call because incoming a1 is already in place. Future
declarations need `extern void func_8130A044(void *, s32);` plus the established
page/drawing helper signatures; the unused probe declarations were removed
from published source. This is an argument-count finding, not a compiler bug.

Negative families: outer result guard versus separate tests, pointer-local
order, input/result carrier reuse, integer address carriers, int/long
argument/result spellings, array/nested-record address views, inline versus
cached addresses, and their corrected-two-argument call compositions.
Next: inspect the page-address web's colorability/lifetime with the corrected
ABI; do not repeat the original one-argument call or force a register.

### `func_8130183C` — requeue, two frame-size words

Correcting that same missing context argument makes register roles and all
instruction words except the frame decrement/increment exact: 192/192 bytes,
1.0000 normalized / 0.9583 raw. Leader:
`f14-flow:abi-two-arg:func_8130183C:reverse-False:cache-False:guard-True`.
Target frame is 0x30, candidate 0x38. Both pointer homes already match target
stack+0x28/+0x24. A separate input/result-reuse source has the correct 0x30
frame but moves both pointer homes down four bytes (0.9167 raw); retain both
leaders rather than discarding either mechanism.

Negative follow-ups: all local declaration orders, register hints, scoped
result declarations, integer carriers, int/long types and paired narrow-return
metadata based on `func_81304AD0`'s observed -1/0/1 result range. None closes
the frame/home combination. Prototype experiments roll back; no speculative
metadata is installed. Next: inspect stack-home assignment/reuse on these two
leaders with a known-match control. Do not add dummy locals or padding to
hide the frame difference. Publish the two verified owners independently.

### Selected-slot lookup follow-up

Eight additional index/return-carrier reuse probes leave `func_813002D0`
unmatched. Explicit pointer caching, int/long carriers and common/immediate
returns did not improve the earlier leader. Keep the previous requeue active;
do not replay these families or count the lookup as solved.

## 2026-10-15 — four setup owners accepted

Five related owners were selected after checking native and older probe
history. Four are now verified C; the selected-slot lookup remains ASM.
The file advances from 30 C / 25 ASM to **34 C / 21 ASM** owners.
Work was solo/native, without agents or containers.

| Owner | Name | Instructions / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_81301030` | `Fragment14_InitSelectionPreview` | 32 / 128 | 0x28 | `03bede7e70bc452f8a66b6dd0dbda8ea` |
| `func_813011B8` | `Fragment14_InitSelectedController` | 41 / 164 | 0x30 | `fb75d9e123de469d98fc4a376fe0b9be` |
| `func_813013C0` | `Fragment14_InitSelectionPanelMode2` | 34 / 136 | 0x28 | `4de722459e0c4393b672116917f5176d` |
| `func_81301448` | `Fragment14_InitSelectionPanelMode1` | 34 / 136 | 0x28 | `4de722459e0c4393b672116917f5176d` |

All four have normal runner `accepted`, `link_verified: true` and successful
combined full-ROM gate provenance under stock IDO 7.1. Total: 141 instructions,
564 bytes. No compiler override, forced registers, padding or helper function.

### Source explanation

- The state record preserves the observed mode word at 0x1A138, signed slot
  and controller bytes at 0x1A142/0x1A143, data pointer at 0x1A148, and status
  word at 0x1A168. The intervening bytes are opaque, not new storage.
- Scalar byte-offset casts allowed the compiler to retain a shared address
  across calls, adding spills. Record-field stores reproduce the independent
  target address calculations. Removing redundant local aliases restores
  the three 0x28-byte frames; all original saved-register roles remain.
- Preview initialization uses the existing 0xF630 subobject and 0x1A15C
  binding. The panel variants use 0xD18 and 0x1A154, preserving their distinct
  call order and mode argument (2 versus 1).
- Controller setup reads the signed selection before calls, conditionally
  selects only values 0..3, preserves all seven setup arguments, and sets
  mode 1. The status clear remains before the conditional call.
- Names describe observed behavior. Address-keyed symbol entries remain
  unchanged; four compatibility aliases are added.
- An initial compact preview probe could not see the record typedef because
  its definition was later in the file. Moving the shared type before its
  users fixed this declaration-order error; no compiler hypothesis was spent
  on the failed compile. A stale batch containing already accepted owners
  was refused at preflight and corrected to the one active owner.

### Verification

- Forced native baseline ROM equality and known-C whole-object control: PASS.
- Fresh and twenty-leading-blank controls before candidates: identical
  section bytes/layout and original C/ASM symbols.
- All four normal link-verified full-ROM acceptance gates: PASS.
- Verified duplicate-extern cleanup, unused probe-local removal and naming:
  fresh and twenty-leading-blank whole-TU builds preserve all section byte
  views and allocatable layouts, all 55 original function offsets and sizes,
  the four accepted spans and every untouched C/ASM span.
- Forced normal ROM rebuild after cleanup/naming: byte-identical retail ROM,
  MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
- Explicit whole-TU host syntax check: PASS, 17 warnings. The original source
  control produces the same 17 warnings; no new warning count increase.
- Public tooling tests: 22 PASS. Diff whitespace check: PASS.
- Publish only source, compatibility aliases and these notes. No scratch
  helpers, compiler instrumentation, generated assembly, objects or ROMs.

### `func_813002D0` — requeue, selected-slot return carrier

Remains ASM. It loads the data pointer at 0x1A148, indexes its signed bytes
at 0x900 using the signed index at 0x1A142, returns the byte when in 0..3,
and otherwise returns zero. The target uses v1 for the split state address
and fallback zero, and v0 for the loaded byte.

Sixteen candidates tested signed-byte/word locals, both guard orders,
common versus immediate returns, explicit pointer-before-index loads,
record access, and zero initialization before/after the load. Explicit loads
restore their order, but the best normalized result is 0.8824 with only
0.4118 raw similarity (68/68 bytes); it is not a near-exact match.
First difference: target state address in v1, candidate in v0.
No rejected body or prototype change is installed.

Next bounded pass: inspect an accepted sibling with the same return topology
or test a genuine result/lookup carrier reuse. Do not repeat this batch's
guard/order families or interpret normalized similarity as exactness.
Ship the four verified siblings without holding them behind this owner.
