# Fragment 14 selection setup

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
