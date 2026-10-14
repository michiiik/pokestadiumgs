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

`func_8820CA50` and `func_8820CAE4`: **requeue**, 36 rejected cells each;
neither source replacement nor experimental prototype is installed.
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
