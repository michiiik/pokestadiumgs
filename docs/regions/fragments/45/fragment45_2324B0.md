# Fragment 45 state handlers

## Matched handlers

| Owner | Instruction bytes |
| --- | ---: |
| `func_8AB0E21C` | 100 |
| `func_8AB0E280` | 108 |

`func_8AB0E21C` defaults to state 34. Argument zero calls
`func_8AB04AE4`, which clears panel visibility flags in
`src/fragments/45/fragment45_2251A0.c`. Argument one checks
`StageContext_GetFadeMode` and, when it returns zero, returns the result of
`func_8AB0E4BC(0)`. Other arguments leave the default state unchanged.
Its forward declaration now reflects the signed-word return value.

`func_8AB0E280` always returns state 36. Argument zero resets the signed
halfword at `D_8AB1723A`. Argument one checks that counter before incrementing
it: a value of at least 10 calls `func_8AB0E2EC(0)`, which starts a fade from
transparent with duration argument five. The counter continues incrementing
after that call; it is neither clamped nor reset. Other arguments perform no
counter update. A local pointer to the counter preserves the original
separate loads around the conditional call.

These operations are established by source and US ROM disassembly. No
runtime observations or broader gameplay interpretation are claimed.

## Verification

The working-tree changes based on `ba03721d554a0d5f588c5b0c10914d96f0ab7b8a`
were verified for `VERSION=us` with the normal host syntax check and a fresh
compile of `src/fragments/45/fragment45_2324B0.c`. The linked ROM compares
byte-for-byte with `baseroms/us/baserom.z64`, with MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Both owners retain their original
addresses and extents. The match uses ordinary C without instruction
rewrites or forced registers.

## Mode 8 prompt state and initial-state returns

`func_8AB0E350` is matched as `TextMode8_HandlePromptState` (364 bytes,
state 37). Phase zero prepares the prompt and first choice label, enables
their graph nodes, clears the four row selection fields, and resets the
prompt counter. Phase one advances the motion helper. Starting at counter
31, it hides the choice node, enters `func_8AB0E4BC(0)`, and clears the other
prompt node's visibility flag. The counter increments after that check.
Other phases retain state 37.

The signed-halfword counter pointer is declared before the signed-word
result. This preserves the separate counter loads around the conditional
call and the retail result spill at stack offset 24. Ordinary C reproduces
all 364 bytes; no padding or instruction rewrite is needed. The original
address name remains available through the linker alias.

The existing mode wrappers `func_8AB06630`, `func_8AB08C4C`,
`func_8AB0B52C`, `func_8AB0E1FC`, and `func_8AB1005C` now explicitly return
the initial states produced by their callees. Their constructor caller
consumes those signed-word results. This signature cleanup changes no
instructions, function extents, or relocation destinations.

Verification: calibrated whole-module controls, accepted runner provenance,
and the syntax-enabled full US-ROM gate. The ROM remains byte-identical
with MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. Newer upstream C, including
the fade and delay handlers merged in PR #1502, is preserved.

## Selected-row delay state

`func_8AB0F518` now has a matching C implementation (224 instruction bytes).
It defaults to state 44. Argument zero resets `D_8AB17248`, enables the node
at `D_8AB11D00`, loads text archive 57 entry 389 into `D_8AB126A8`, and clears
the visibility bit on the node at `D_8AB16FC8`. It then emits event 102 with
two zero parameters, calls `func_800225C4(40)`, and plays sound 52998.

Argument one increments the signed-halfword counter before calling
`TextHighlight_AnimateScales`. When the counter reaches at least 61, the
handler returns `func_8AB0F5F8(0)` instead of state 44. Other arguments retain
state 44 without those updates. The caller `func_8AB0EED8` records the first
row whose halfword at offset 2 equals one, stores its index in the interface
configuration, and enters this handler with argument zero.

The event wrapper's three signed-word parameters are established by its
definition in `src/fragments/45/fragment45_2251A0.c`. The sound helper's
`void (u16)` declaration follows `Audio_PlayDefaultSound` in `src/229E0.c`;
the original call's address name is an existing linker alias. The counter
pointer is declared before the result, reproducing the original result slot
at stack offset 24 without dummy storage or instruction rewrites.

Verification targets the complete source tree of master
`3349f81941add45a9d3ae2493a68d4964c77c201` plus this change. A fresh
syntax-enabled compile via
`make -W src/fragments/45/fragment45_2324B0.c -j4 VERSION=us rom`
passes the US ROM checksum, and `cmp` confirms byte-for-byte equality with
the retail ROM. MD5 remains `1561c75d11cedf356a8ddb1a4a5f9d5d`.
These behavior claims come from source and disassembly inspection.

## Prompt dispatch state

`func_8AB0EF44` now has a matching C implementation (356 instruction bytes).
It defaults to state 40. Argument zero runs the reference-command parser,
shuffles the choices, and calls `func_8AB0D330`. It sets `D_8AB1722C` to one,
clears `D_8AB1722E` and the 256-byte `D_8AB16FD0` buffer, enables the node at
`D_8AB16FC8`, hides the node at `D_8AB11D00`, and updates panel visibility.
It then sets text substitution slot two to `D_8AB12694 + 1`, clears
`D_8AB112C0` and `D_8AB17224`, and calls `func_8AB004E0`.

Argument one calls the input and text-update helpers `func_8AB0E9E8` and
`func_8AB0E8B4`. If `D_8AB1722E` equals one, it obtains a candidate state
from `func_8AB0F0A8(0)`. A separate check of `D_8AB17230` can replace that
candidate with `func_8AB0F2F0(0)`; when `D_8AB1722E` is then zero, it also
refreshes the buffer from the node's archive and entry keys at offsets 48
and 50. Finally, `func_8AB0EED8` can replace the candidate when a selected
row enters its delay state. Argument two and other values return state 40
without these updates. The separate checks preserve that transition order.

`func_8004C594` in `src/4CC20.c` validates a substitution-slot index and writes
its signed-word value. `func_8004C5E0` reads that slot to format a number
during text expansion. The parser, choice shuffle, panel-visibility update,
and `func_8AB004E0` are in `src/fragments/45/fragment45_2251A0.c`. Other
callee names and state words retain their address-based names where their
broader interpretation is unresolved.

Verification targets master `1459ffd283b2b7f0b0f2ae3d04cfb50ced6e0aa3` plus
this change. The normal syntax-enabled forced source compile and full
`VERSION=us` ROM build pass, and `cmp` confirms byte-for-byte equality with
the retail ROM. MD5 is `1561c75d11cedf356a8ddb1a4a5f9d5d`. Ordinary C
preserves the 32-byte frame and result at stack offset 28, without dummy
storage, forced registers, or instruction rewrites. Behavior descriptions
are based on source and disassembly inspection.

## CPU answers and row-cleanup state

| Original owner | C name | Instruction bytes |
| --- | --- | ---: |
| `func_8AB0D330` | `TextMode8_InitCpuAnswerSettings` | 372 |
| `func_8AB0D4BC` | `TextMode8_ChooseCpuAnswerMask` | 312 |
| `func_8AB0F2F0` | `TextMode8_HandleRowCleanupState` | 404 |

These three owners contribute 1088 bytes of matching C. Their address names
remain linker aliases for assembly callers.

The initializer writes delay and correct-answer chance into the last two
signed halfwords of each 148-byte player row, at offsets 144 and 146.
Configuration byte two selects the ranges below; nonzero `D_8AB12CA8` selects
configuration four. Each row receives independent random draws. The delay
coefficient is multiplied by `func_80001FF0() / 2`, and the shared answer
clock is reset after all four rows are initialized.

| Configuration | Delay coefficient, inclusive | Correct-answer chance, inclusive |
| --- | --- | --- |
| 1 | 7-10 | 15-65 |
| 2 | 6-9 | 25-75 |
| 3 | 5-8 | 35-85 |
| 4 | 4-7 | 45-95 |
| Other | 5 | 50 |

The answer helper returns zero until the shared clock reaches that row's
delay. A draw below the row's chance selects the correct-answer index;
otherwise a one-to-three offset modulo four chooses a different index.
Indices zero through three map to input masks 8, 1, 4 and 2. The producer
`TextChoice_ShuffleAndRefresh` tracks the correct index across swaps in
`src/fragments/45/fragment45_2251A0.c`. The consumer `func_8AB0E9E8` reads
controller input for human rows and this helper's mask for CPU rows, then
compares the selected answer with that same correct index.

The cleanup handler defaults to state 42. Phase zero checks whether every
active row is in state two. If so, it calls the existing row-update helper
for all four rows and sets `D_8AB17224`; otherwise it updates only active
rows still in state zero. Phase one increments the signed-halfword counter,
updates highlight scales, emits event 102 at `func_80001FF0() / 4`, and
enters `func_8AB0F484(0)` at counter 31. Phase two and other phases retain
state 42. Declaring the result before its counter pointer recovers its
retail stack slot without extra storage.

Verification against master `fef41e0a`: normal runner acceptance and the
syntax-enabled full US-ROM gate for each owner, followed by complete-module
controls and a repeat ROM gate after naming and typed-row cleanup. The
cleanup handler's array-end relocation uses the same fixed address as the
adjacent end label and passes the sequential ROM gate. The complete module
retains all 9264 text bytes, 24 function extents and resolved relocation
destinations. A changed-frame negative control is rejected. Frozen linked
fragments, collateral objects and retail ROM are compared independently;
US MD5 remains `1561c75d11cedf356a8ddb1a4a5f9d5d`. These behavior descriptions
come from source, disassembly and data-producer/consumer inspection.

## Mode 8 update and draw dispatchers

| Original owner | C name | Instruction bytes |
| --- | --- | ---: |
| `func_8AB0DFC0` | `TextMode8_UpdateState` | 308 |
| `func_8AB0E0F4` | `TextMode8_DrawState` | 264 |

Both switches cover states 34 through 45. The update dispatcher calls the
selected handler with phase one, saves its next-state value, advances
`func_8AB0148C` for answer-effect indices zero through three, and returns
the saved state.
An unknown state is returned unchanged after those four effect updates.
The existing caller `func_8AB051AC` selects this dispatcher for mode eight.

The draw dispatcher first traverses the graph at `D_8AB16FA0` through
`func_800503A4`, then calls the selected handler with phase two. Unknown
states still draw that graph. Its frame-rendering caller `func_8AB04EE8`
follows it with `TextInterface_DrawMarkers`; phase two of `func_8AB0E4BC`
also draws its model through `func_8003C6B8`. Those consumers support the
draw name.

| State | Handler |
| --- | --- |
| 34 | `func_8AB0E21C` |
| 35 | `func_8AB0E2EC` |
| 36 | `func_8AB0E280` |
| 37 | `TextMode8_HandlePromptState` |
| 38 | `func_8AB0E4BC` |
| 39 | `func_8AB0E684` |
| 40 | `func_8AB0EF44` |
| 41 | `func_8AB0F0A8` |
| 42 | `TextMode8_HandleRowCleanupState` |
| 43 | `func_8AB0F484` |
| 44 | `func_8AB0F518` |
| 45 | `func_8AB0F5F8` |

The source file now owns its original 208-byte rodata window at ROM
`0x236D40..0x236E10` / VRAM `0x8AB11BC0..0x8AB11C90`. Four existing strings
occupy the first 108 bytes, including their ordinary alignment; the two
12-entry switch tables follow at offsets 108 and 156, with natural final
alignment. The strings are ordinary unsized readonly character arrays with
the exact retail contents. The earlier shared prefix and following tail
remain separate rodata inputs in their original order. No storage addresses
or linked bytes change.

The layout is verified while both dispatchers are still assembly, before
any C switch probe. Normal runner acceptance then passes the syntax-enabled
full retail-ROM gate for each switch. After naming and the caller update,
controls preserve the complete 9264-byte mode text, 24 function extents,
208-byte rodata window and relocation destinations, together with the full
23008-byte caller module. Leading-blank controls agree; changed instruction,
string and jump-target negative controls are rejected. The entire former
shared rodata, four linked fragments, collateral objects and frozen build
hashes are independently compared. `cmp` confirms byte-for-byte equality
with the retail US ROM; MD5 remains `1561c75d11cedf356a8ddb1a4a5f9d5d`.
These behavior claims are based on source, disassembly and data inspection.

## Prompt text reveal

`func_8AB0E8B4` is `TextMode8_RevealPromptText` (292 instruction bytes).
It copies the text selected by the archive and entry halfwords at offsets
48 and 50 of `D_8AB11D00` into the 256-byte buffer `D_8AB16FD0`, then
truncates that text after the requested number of logical characters.
A newline advances one byte; another high-bit byte advances two bytes;
other characters advance one byte. Reaching NUL sets `D_8AB1722E` and
returns zero. Otherwise it returns one and, on even frames, plays the
newline or ordinary-character sound and increases the reveal count.

The phase-zero caller `func_8AB0EF44` starts that count at one and clears
the completion flag. Its phase-one path calls the reveal function and
uses the completion flag to advance to `func_8AB0F0A8`. These producer and
consumer operations support the name. The source reads unsigned bytes
directly and keeps the original two-key, four-argument text-copy API.

Normal runner acceptance passes the syntax-enabled retail-US-ROM gate.
After naming and removal of duplicate forward declarations, before/after
and leading-blank controls preserve the complete 9264-byte mode text,
24 function extents, 208-byte rodata and relocation destinations. Changed
instruction, newline and jump-target controls are rejected. A fresh full
build and `cmp` preserve the retail ROM (MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`). Behavior is established from the source,
original disassembly and the text-copy implementation in `src/4CC20.c`.
