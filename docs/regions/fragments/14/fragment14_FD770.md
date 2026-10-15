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
explicit float temporaries would grow the frame; compound assignments worsen
register choices. Swapping just the multiply operands is normalized back to
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
