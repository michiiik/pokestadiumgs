# Region notes -- disasm/src/fragments/47/fragment47_24AE60.c

Per-file spellings, skip lists, and unsolved shapes for this source file.
Delivered to agents by `tools/file_brief.py`; extend it with
`tools/region_notes.py append`.

## 2026-08-29

The box at `git_head cbc9af3` produced 0 accepts from 42 attempts. All 42
attempts targeted `func_86006364` and repeated the same operand/scheduling
first difference: the oracle frame is `addiu $sp,$sp,-0x68` (104 bytes), while
the candidate frame was `-0x60` (96 bytes). Best normalized/raw similarity was
0.9825/0.8772. Treat this as a frame-layout/source-shape problem and do not
repeat the same hypothesis family without changing the local declarations.

The file also contains fresh dispatcher/large owners and register-tie or
near-miss owners; rank them separately after reading the current file brief.

## 2026-08-29 fleet box: probe-only handoff (2026-08-29)

Probe-only handoff for this 60-minute box. No candidate was accepted, no `link_verified:true` result was produced, no ROM gate was run, and the tracked source remains untouched. All 79 attempts below used MCP `try_pragma_candidates` with `gate:false`.

Attempt counts and diagnostics:
- `func_86006C30`: 21 attempts — 8 `instruction_drift`, 9 `operand_or_scheduling_drift`, 4 `register_allocation_only`. Best `call-sequence:switch:volatile-casts`: normalized 1.0000, raw 0.8197, exact 244-byte size, but the first difference is the flag-load register (`t3` oracle versus `v0` candidate). The runner emitted no futility/register-tie field; do not treat this normalized-only result as accepted.
- `func_86004840`: 25 attempts — 7 compile failures and 18 probe rejections (17 `operand_or_scheduling_drift`, 1 `instruction_drift`). Best frame-array spelling scored 0.9595/0.8243 with matching 296-byte size, but its first branch target was 64 versus oracle 62; the direct-f32 spelling scored 0.9595/0.7973 with candidate frame `-0x30` versus oracle `-0x38`.
- `func_86005B3C`: 17 attempts — 12 `immediate_drift`, 5 `operand_or_scheduling_drift`. Best `call-sequence:record-setup:two-ptrs-direct` scored 0.9787/0.8404, but was 368 bytes versus oracle 376 and differed at the loop branch target (81 versus 83). Integer-address locals restored instruction count but forced the wrong `-0x38` frame instead of `-0x30`.
- `func_86007428`: 12 attempts — 5 compile failures, 3 `instruction_drift`, 4 `operand_or_scheduling_drift`. Best normalized score was 0.8958 (saved-callback variants had a `-0x40` candidate frame versus oracle `-0x38`); best raw score was 0.625 (direct old-prototype spelling, 368 versus 384 bytes).
- `func_8600520C`: 4 attempts — 4 `operand_or_scheduling_drift`. Best scored 0.8699/0.5447; candidate frame was `-0x78` versus oracle `-0x60` and 476 versus 492 bytes.

Explicit skips/deferred owners:
- `func_86006364`: retain the documented 42-attempt frame-layout near miss (oracle `-0x68`, candidates `-0x60`); the current brief reports 68 prior attempts and best normalized/raw 0.9825/0.8421 with operand/scheduling drift. Skip unless local declarations/source shape materially changes.
- Defer allocator ties `func_860053F8`, `func_86004968`, `func_86004EA8`, and `func_86006448`.
- Skip dispatcher/jump-table owners `func_86007648`, `func_86006F20`, `func_8600666C`, and `func_86006D64` until the required rodata layout is independently prepared.
- Other fresh call-sequence/call-chain owners not reached in this box remain deferred: `func_86004FDC`, `func_860057D0`, `func_86004BD4`, `func_86006964`, `func_860076EC`, `func_86005434`, and `func_86005A00`. No accepted spelling to carry forward.
