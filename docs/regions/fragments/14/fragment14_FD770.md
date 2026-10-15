# Fragment 14 grid selection

## 2026-10-15 — four grid functions accepted, table layout ready

The file advances from **16 C / 15 ASM** to **20 C / 11 ASM**. Four normal
native-runner accepts cover **149 original instruction words / 596 ROM bytes**,
including the close function's natural alignment tail. Stock IDO 7.1 / `-O2`.
This is not file or repository completion. Work is solo/native.

| Owner | Name | Original words / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_81306178` | `Fragment14_ConfirmGridSelection` | 28 / 112 | 0x20 | `8d10828766a04296bca9c2f9b634e565` |
| `func_8130687C` | `Fragment14_UpdateGridCursorStep` | 17 / 68 | none | `ab4e55a480b4471f8a7bed8a09fc3b10` |
| `func_813069BC` | `Fragment14_UpdateGridState` | 84 / 336 | 0x50 | `4bba6bbc3f2a4c32b5469a9e9e62b714` |
| `func_81306E90` | `Fragment14_BeginGridClose` | 20 / 80 | none | `aac7e18326a949c7858ead0d10c4b0d3` |

Confirm/cursor step have `link_verified: true` accepts and combined full-ROM
gates. Dispatcher/close have relocation-masked hits and authoritative sequential
full-ROM acceptance, **not** object-link-verified results. No provenance bypasses.

### Source mechanisms

- Confirm: retain the signed word selection result, reject negative/excluded
  values with sound 5, otherwise store mode 5, the halfword result and timer 4.
  The short-circuit condition reproduces the target's validation and branches;
  the nested-success spelling does not. Keep the real membership signature.
- Cursor step: use a signed word counter, compare before increment, clear the
  counter before the idle-state store, and copy the four selection bytes using
  the existing packed-word view. This reproduces the target's unaligned pair;
  unsigned word comparison changes `slt` to `sltu`.
- Dispatcher: preserve physical case order **0,1,3,2,4,5**, active flags for
  states 1/3/2, the early inactive return and all three rectangle registrations.
  Put the scalar before the three four-short arrays. Sorted case bodies have
  the wrong table image even when instruction comparison looks close.
- Close: keep explicit case 0, states 1/2/3 resetting the timer and falling
  through to the 4/5 close-state store, then clear the owner word for every
  state including unknown values. The C symbol is 68 bytes plus 12 natural
  zero alignment bytes; the old ASM symbol included all 80. Full spans and
  text-section size are unchanged. Do not add a padding pragma.

### Complete the file's table layout before C switches

Add `.rodata` ROM `0x10A660..0x10A6D0`, preserving `SUBALIGN(16)` and all
0x70 bytes: the original named zero word `D_813124D0`, four tables and four
float cells. The leading word is real referenced data, not a new helper or
fabricated padding. A one-element `const u32` array emits its original four
zero bytes in rodata. A scalar const experiment landed in 16 bytes of data,
shifted the ROM, and was rejected; the array form removes that data section.

The already-C readers of `D_813124E8` and `D_813124F4` use their original
`0.1f` literal, preserving separate per-function pool cells and the negated
less-than comparisons (including unordered behavior). The other two literals
migrate into the remaining ASM renderer. No stale data includes are needed.

Gate the still-ASM switch layout first: all 31 function offsets/sizes remain
unchanged; the named leading word and all four literals agree with ROM; the
full ROM is exact. After acceptance, independently resolve **all 23 table
relocations** back to original VRAM destinations, not just normalized scores.
The generated linker change replaces the old 10A660 shared tail with 10A6D0.

### Naming, cleanup and verification

- Add four behavior-backed US aliases; retain address-keyed symbols and JP.
  The selection caller uses the real pointer/context prototype. Another
  caller changes only the close function's name.
- Remove duplicate prototypes, an unused probe typedef and formatting debris.
  No unaccepted scroll body or speculative declarations are installed.
- Fresh and twenty-leading-blank final grid builds preserve all section
  bytes/layout against the frozen accepted object, all 31 original text
  offsets/full spans, four accepted and 27 untouched spans, every table
  destination and literal/data cell. The close symbol's size is explicitly
  checked as 68 code bytes plus its 12-byte original alignment tail.
- Neighboring caller checks preserve the entire 55-function selection object
  and 39-function auxiliary object, including all function offsets/sizes.
- Native baseline, layout prerequisite and four normal acceptance gates match
  retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. Statistics and host checks
  remain enabled. Publish only C, aliases, YAML/generated linker layout and
  region notes; no scratch helpers, runner copies, assembly, compiler artifacts,
  objects or ROMs. No agents or containers.

### `func_81305BA8` — requeue, one commutative multiply instruction

Remains ASM. Thirty-two candidates covered compact float carriers, output
slot ordering, unsigned conversion, expression splitting, negation order,
commuted multiplication and compound assignments. Best is 172/172 bytes,
frame 0x28, normalized 1.0 / raw 0.9767: **42 of 43 instruction words agree**.
Target instruction 21 is `mul.s f18,f0,f16`; the candidate is
`mul.s f18,f16,f0`. This is operand ordering, not a different computation or
a demonstrated physical-register allocation bug. The generic diagnostic's
`register_allocation_only` label is coarser than the actual disassembly.

Reverse the two real float declarations to put the whole output at stack+0x20,
not +0x24. Negate the fractional remainder before multiplying by 28. Additional
explicit float temporaries were previously expected to grow the frame; the
distinct-carrier follow-up below corrects that assumption. Compound assignments
worsen register choices. Swapping just the multiply operands is normalized back to
the same result by this pipeline and does not fix the emitted word.

A calibrated 45-second native permuter, four compiler workers and stack
scoring, stayed **10 -> 10**. Both actual native source and target controls
reproduce before search. Its equal-score addition commute was not installed.
Next: inspect CFE/uopt expression ordering or a genuine distinct value carrier
while preserving the 42 exact words. Do not repeat operand commutes, inflate
the frame, force a register or treat this bounded negative as impossibility.

The remaining four-table owners are now layout-ready. In particular the
float getter and the later state/input switch can be investigated against the
real object layout; do not requeue already-accepted C owners.

## 2026-10-15 follow-up — cursor position, reset and page-forward accepted

The file advances from **20 C / 11 ASM** to **23 C / 8 ASM**. Three normal
native-runner accepts cover **170 instruction words / 680 ROM bytes** under
stock IDO 7.1 / `-O2`. All three have `link_verified: true` and successful
combined full-ROM gates, with statistics and host checks enabled.

| Owner | Name | Words / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_81305AD0` | `Fragment14_ComputeGridCursorPosition` | 54 / 216 | none | `342f8d0cb7d0454e99c531dcd65ad666` |
| `func_813063CC` | `Fragment14_ScrollGridForward` | 71 / 284 | 0x18 | `a9a91b14e8cc4fbfa711d37b96c308de` |
| `func_81306B64` | `Fragment14_ResetGrid` | 45 / 180 | 0x20 | `38e13db27e4045ecb5914ad27324b79f` |

### Source mechanisms and verification

- Cursor position: keep ratio and the two interpolated float coordinates as
  separate real values, then apply the 172/28 spacing and 38/18 screen origin.
  Inlining both coordinates changes scheduling and adds an instruction.
- Page forward: preserve the word-sized last-page limit, four-row advance,
  signed-halfword clamp and unsigned old-page byte. Keep signed delta and
  absolute distance separate before the original float-to-unsigned-byte
  duration conversion. Reusing delta removes target instructions.
- Reset: retain the actual word-sized coordinate formals and optional list
  pointer, the existing packed four-byte selection copy, all state/timer
  stores and original helper calls. Halfword formals change incoming loads.
- Name with three US compatibility aliases. Correct the existing caller's
  reset prototype to pointer/context types and explicitly cast its integer
  address; no behavioral or ABI change. Remove duplicate externs introduced
  by runner synthesis and format only newly accepted bodies.
- Fresh and twenty-leading-blank builds after cleanup/naming preserve all
  section byte views/layout against the frozen accepted object, all 31
  function offsets/sizes/full spans, three accepted and 28 untouched spans,
  all 23 table destinations, the leading zero word and four float cells.
  Both caller controls preserve its entire 55-function object.
- Forced normal ROM rebuild after cleanup/naming matches retail MD5
  `1561c75d11cedf356a8ddb1a4a5f9d5d`. Explicit host syntax check passes;
  public tooling tests: 22 PASS. No padding pragma, forced register,
  speculative body or compiler modification is installed.
- Publish only game C, US aliases and these notes. All search/proof artifacts
  stay local. Work remains solo/native; no agents or containers.

### Requeues — navigation and input

`func_813064E8` (left): eight initial candidates preserve the 324-byte size
and 0x18 frame; best normalized/raw **0.9877/0.9259**. The second branch's
sound argument is materialized later, allowing delta to occupy a0 rather than
the original v1. Changing flag-store order is worse. Next: examine the second
branch's constant-argument lifetime, not repeated operand/declaration swaps.

`func_8130662C` (right): eight initial candidates reach 340/340 bytes and
normalized/raw **1.0/0.9529**, with delta in a0 instead of v1. A calibrated
45-second-bounded, four-worker native permuter reaches score **20 -> 0**,
but its proposal moves the saved-page declaration into the outer else and
introduces a redundant `if (1)` around the transition update. Semantic review
finds no changed live values, but it is not accepted source. Eight natural
scope/block compositions without `if (1)` all retain the register residual.
No zero-score scaffold is installed or counted as a match. Next: identify
the frontend/optimization boundary introduced by that conditional, then seek
a natural source topology; preserve the proposal as diagnostic evidence.

`func_81306780` (button handler): 24 candidates test integer versus pointer
address expressions, cached/typed controller pointers, word/halfword button
values, early returns and directional-value scopes. A cached integer-derived
controller pointer restores the target addiu, improving the best to
normalized/raw **0.9365/0.8413**, 244 versus 252 bytes, frame 0x18. Remaining
differences begin at the pressed-button load (v0 versus a1); the target has
two subsequent value copies not retained by these sources. Do not invent
extra formals or repeat the same snapshot assignments. Next: inspect the
button-value ownership/branch topology against a solved input sibling.

### Scroll distinct-carrier follow-up

Eight new candidates split ratio/progress and returned fraction into genuine
separate float locals, testing six declaration orders and two advisory
`register` spellings. They **do not necessarily grow the frame**: the best
retains 172 bytes and the original one-word multiply-operand residual at
normalized/raw **1.0/0.9767**. Other orders move the whole-value slot to
stack+0x24 or +0x1C. There are now 40 recorded candidates. This rejects the
distinct-carrier family as tested, not all possible C spellings. Next remains
the CFE/uopt multiply-operand ownership boundary; do not repeat these orders.

## 2026-10-15 — rectangle animation accepted for the next batch

`func_81305780` becomes **`Fragment14_ComputeGridRectangles`**, 164 words /
656 bytes, frame 0x20. The file is now **24 C / 7 ASM**. Normal native batch
`0318a1098fd94583ba4e95ccc05fce8c`, label
`f14-grid:rectangles-shape:records-True:origin-last-False:offset-group-False`,
is `accepted`, `link_verified: true`, with a successful combined full-ROM gate.
Stock IDO 7.1 / `-O2`, statistics and host checks remain enabled.

The function gets the grid phase progress, calls the real width/height easing
callbacks, computes three centered rectangles and returns the original
progress. Preserve the dimensions 148x41, 440x143 and 302x67, integer division
by two, and the original integer first-origin versus float later-origin
expressions, including vertical offsets 30 and 162.

Eight initial raw-offset drafts top out at normalized/raw **0.8841/0.4878**,
652 versus 656 bytes, with the correct frame in the leading declaration order.
Eight follow-ups test output/origin record views and addition grouping. The
record view with the original addition order matches immediately. This is
measured translation-unit/type/expression context evidence, not proof that
every difference is owned by a particular compiler pass. Explicitly grouped
later y origins have the wrong shape; commuting origins reaches another
register residual. Do not replace the accepted typed view with raw casts.

Use partial records only for observed storage: root word at zero and position
halfwords at 4/6; output rectangle x/y/width/height at 0/2/4/6. These define
existing data views, not new storage or helper functions. Preserve the real
float-returning callback declarations and the existing four-pointer ABI.
Add one US compatibility alias; retain address-keyed symbols and JP.

After formatting/naming, fresh and twenty-leading-blank controls preserve
whole-object section bytes/layout, all 31 original function offsets/sizes/
full spans, the accepted body and all 30 untouched C/ASM spans. Independently
verify all 23 jump-table destinations, the leading zero word and four float
cells. Forced normal ROM rebuild and explicit host syntax check pass;
retail MD5 is `1561c75d11cedf356a8ddb1a4a5f9d5d`. Public tooling tests remain
22 PASS. No scaffold, padding, forced register, compiler patch or provenance
bypass. Publish only C, the alias and these notes; all search/proof artifacts
stay local. Solo/native work continued while PR #1007's ROM CI ran; that
three-function PR passed and merged before this next-batch commit.
