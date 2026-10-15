# Fragment 14 selection setup

## 2026-10-15 follow-up — slot advance, exit status and slot dialog accepted

Three more functions are accepted: **148 instructions / 592 bytes**. The file
now has **47 C / 8 ASM functions**, plus one preserved data-only ASM include.
All seven jump tables now belong to the file's `.rodata`; none is blocked on
the previous missing subsegment. This is not file or repository completion.

| Owner | Name | Instructions / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_81300730` | `Fragment14_AdvanceSelectionSlot` | 64 / 256 | 0x20 | `89d496d52dd649a18bd60dd068edacd4` |
| `func_81300B50` | `Fragment14_GetSelectionExitStatus` | 20 / 80 | none | `efc29d5100604cf6bbe7effc1e4abe27` |
| `func_81301548` | `Fragment14_UpdateSlotDialog` | 64 / 256 | 0x28 | `694732e33a564d5ea9fae720cf65f3eb` |

### Preserve leading data while completing the layout

- Expand the existing `.rodata` window from ROM `0x10A390` back to
  `0x10A310`, still ending at `0x10A430`: 0x120 bytes total. Keep the original
  `SUBALIGN(16)` and linker order; no linker-script rewrite is necessary.
- Explicitly declare the original 24-byte `D_81312180` symbol with
  `force_not_migration:true`. Include its generated data-only assembly before
  the functions so splat preserves it even though its referencing function is
  already C. This is the original named data, not a new helper function.
- Re-extract using pinned splat/spimdisasm. Gate all three owners still in
  assembly first. All 55 function offsets/sizes remain unchanged, the owner
  rodata is exactly 0x120 bytes, and the retail ROM matches. Verify the first
  24 bytes separately against ROM `0x10A310..0x10A328`.
- The data-only include is derived by extraction; do not publish generated
  assembly. Its explicit metadata and source pragma make it reproducible.

### Source mechanisms and acceptance

- Advance: retain the next-slot call, both exhausted-end states, signed slot
  store, seven-case unsigned kind dispatch and 0x240-byte clear on kind 4.
  Existing full-record slot/data views produce the required load order; a
  separate raw upper pointer reverses two loads. Keep a local result rather
  than reusing the consumed direction argument, which moves its spill home.
- Exit status: explicit continuing cases 0/1/2/3/5 return zero, state 8
  returns -1, state 9 returns +1, and the default returns zero after the
  switch. This preserves the two distinct zero-return tails.
- Slot dialog: reuse the accepted controller-dialog call shape with the real
  second context argument and inline dialog addresses. Preserve commit and
  preview branches, cancellation's -1 kind store/backward advance, controller
  result stores, and explicit no-op -2. The upper-address expressions retain
  the original pointer materialization in each branch.
- All three are normal runner `accepted`, `relocation_masked: true` hits
  verified by authoritative sequential full-ROM gates. They are **not**
  object-link-verified hits. Statistics and host checks remain enabled.
- Clean up formatting and duplicate prototypes, add the real `_bzero`
  prototype, and apply three behavior-backed names with US aliases. Fresh
  and twenty-leading-blank builds preserve every allocatable section byte
  and layout, all 55 function offsets/sizes, three accepted and 52 untouched
  spans, and all 24 original leading data bytes.
- Forced normal build matches retail MD5
  `1561c75d11cedf356a8ddb1a4a5f9d5d`. Host syntax check passes with the same
  17 warnings as baseline. Public tooling tests: 22 PASS. Diff check PASS.
- Re-extraction from the final C/YAML/metadata and a normal native rebuild
  also match retail, demonstrating that the leading data include does not
  depend on stale generated assembly.

### Integration tooling failure — preserve original oracles between gates

The first mixed batch accepted advance, then re-extracted assembly without
that now-C owner's `.s`. Subsequent sequential candidate transactions restored
the original source baseline, including advance's old pragma, but not its
assembly file. The compiler reported `Cannot open file GLOBAL_ASM:...` for
the missing **earlier** owner. All eight exit-status bodies and two matching
slot-dialog bodies were affected; those gate failures are not source-shape
rejections. The isolated probes had already matched.

Safe fallback: gate the remaining owners in separate calls against the
cumulatively installed source. Exit status and slot dialog both accept in
about seven seconds per call. Retry only the two already-matching slot-dialog
bodies, not its six genuine rejected variants; the duplicate preflight
correctly rejects a whole-batch replay. No ledger bypass or manual C install.

Tooling follow-up: retain the batch's original assembly dependencies across
extraction and source restoration, and classify missing baseline oracles as
environment/integration failures rather than candidate compile failures. A
regression fixture should accept owner A, remove A's extracted oracle, then
test B against a restored A/B baseline. The public PR contains no runner copy.

### Active requeues

- `func_813002D0`: all 32 previous native candidates returned a word. Eight
  new signed-byte-return variants use the supported candidate-own forward
  prototype transaction (unlike retyping an unrelated still-ASM callee).
  They do not improve the leader: the best new shape is 72/68 bytes,
  0.7778 normalized / 0.3889 raw. The source and word-return prototype are
  restored; do not use the speculative narrow-return declaration to try
  to improve the neighboring dialog's spill homes.
- `func_8130209C`: eight new integer/pointer address-carrier probes do not
  improve the existing 280-byte leader or its +0x18 versus +0x1C pointer
  spill. Integer state-pointer form adds another instruction. The earlier
  bounded 45-second permuter yielded no saved improvement (score 23 to 23);
  its source control explicitly validates all ten jump-table destinations
  before ignoring section-relative relocation fields. This is bounded
  negative evidence, not an impossibility claim. Next: inspect allocation
  and stack-home ownership before further source permutations.
- `func_81300BE8`: sixteen new probes establish six 0x60-byte team records,
  0x58-byte payload copies from source stride 0xCE8, metadata flag bit 26,
  conditional per-record flag clearing, trainer name and ID handling. The
  closest structural leader is 584/588 bytes, 0.9932 normalized / 0.4558 raw;
  it is not a near-exact byte match. Two explicit source-pointer carriers
  restore 588 bytes but inflate frame 0x28 to 0x30 and perturb allocation
  (0.9796 normalized / 0.2993 raw). Separate clear-loop locals are worse.
  Next: recover the two induction addresses without adding two independent
  stack locals. No probe-only payload/source/data types are installed.

## 2026-10-15 follow-up — jump-table layout and three dispatchers accepted

The file advances to **44 C / 11 ASM** owners. Three of four newly unblocked
dispatchers are accepted: **184 instructions / 736 bytes**, stock IDO 7.1,
solo/native. The update dispatcher remains ASM, not an accepted normalized hit.

| Owner | Name | Instructions / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_813018FC` | `Fragment14_UpdateControllerDialog` | 51 / 204 | 0x28 | `37af195cce1a4123adbb1c4d1b8b7329` |
| `func_81301F64` | `Fragment14_EnterSelectionState` | 78 / 312 | 0x18 | `ac44ada94428451e861ac20107404546` |
| `func_813021B4` | `Fragment14_DrawSelectionState` | 55 / 220 | 0x18 | `37af195cce1a4123adbb1c4d1b8b7329` |

### Layout prerequisite and source mechanisms

- Add the 160-byte owner `.rodata` window at ROM `0x10A390..0x10A430`,
  containing `jtbl_81312200`, `jtbl_81312224`, `jtbl_8131224C` and
  `jtbl_81312274`. Preserve the existing `SUBALIGN(16)` and split the
  remaining rodata tail at `0x10A430`. Re-extract with pinned splat64 0.25.0
  and spimdisasm 1.35.0.dev0. No generated assembly is published.
- The earlier planner window starting `0x10A310` also includes data referenced
  by already-decompiled title/controller setup. Do not migrate that whole
  window blindly: splat does not automatically preserve such data for an
  existing C definition. The first three tables remain outside this cut.
- Gate the layout with every owner still ASM before testing C. All 55
  function offsets/sizes remain unchanged and the full retail ROM matches.
- Dialog update: retain the two-argument `func_81310894` call. Its callee
  consumes incoming a1 even without an explicit caller move. Keep only the
  result local, express the dialog address inline, and retain the explicit
  no-op -2 case. A cached dialog or reuse of the consumed context word moves
  the frame/spill homes. Preserve result -1, controller 0..3 and sentinel 6.
- State entry: clear the transition flag, store requested then active state,
  copy the real eight-byte position record, and dispatch ten initializers.
  The byte-aligned opaque position record reproduces the unaligned word
  copy; an aligned word-array assumption would change its instructions.
- Draw: dispatch the active unsigned byte and preserve context on the eight
  two-argument paths. The two dialog paths consume only the state pointer.
- Consolidate accepted fields into `Fragment14SetupState`; remove unused
  alternate probe types/prototypes. Keep required helper declarations before
  the earliest new definition. The first mixed batch exposed a declaration
  placement failure during integration, not a source-shape rejection; moving
  the installed declarations and re-gating resolves it. Do not count its
  compile failures as evidence against the isolated matching bodies.
- Apply three behavior-backed names and safe US aliases. The one cross-file
  draw caller is renamed with no section-byte/layout change. JP and the
  address-keyed symbol table are untouched.

### Acceptance and verification

- All three have normal runner `accepted` and full-ROM gate provenance.
  Dialog update is object-link-verified. Entry and draw have
  `relocation_masked: true`, so their authoritative evidence is the successful
  sequential full-ROM gate, not object link verification. Do not describe
  those two as `link_verified: true`.
- Fresh and twenty-leading-blank whole-TU builds after cleanup/naming preserve
  all allocatable section bytes/layouts, all 55 original function offsets and
  sizes, the three accepted spans and 52 untouched spans. The renamed caller's
  whole-object section bytes/layout are unchanged as well.
- Forced normal ROM rebuild: byte-identical retail ROM, MD5
  `1561c75d11cedf356a8ddb1a4a5f9d5d`. Host syntax check of both affected C
  files passes, with the same 17 warnings as the main-file baseline. Public
  tooling tests: 22 PASS. Diff check PASS.
- Publish only two C files, YAML/linker layout, aliases and this note. No
  scratch helpers, alternate compiler, generated assembly, objects or ROMs.

### `func_8130209C` — requeue, upper-state pointer spill home

Best leader `f14-dispatch:update:typed-False:alias-False:selector-False` has
280/280 bytes, 1.0000 normalized / 0.9571 raw. The instruction count/opcode
sequence and frame 0x20 agree. The upper-state pointer's save/reload is at
stack+0x18 instead of the target's +0x1C; the other raw difference is the
relocatable jump-table address. Preserve context as the second argument on
all ten update paths and the final no-argument `func_81609CB8` flush.

Twenty-four probes covered raw/typed upper views, explicit context and
selector locals, context declaration/initialization order, and signed-byte
versus word requested-state locals. Added locals inflate the frame to 0x28
without fixing the desired home; do not repeat these families. No fake local,
padding, forced register or failed body is installed. Next: calibrate a
bounded stack-difference permuter on the leader with the current named callee
prototypes; if flat, inspect the pointer's actual allocation/home mechanism.

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
