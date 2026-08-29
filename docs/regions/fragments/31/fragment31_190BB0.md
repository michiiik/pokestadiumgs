# Region notes -- disasm/src/fragments/31/fragment31_190BB0.c

Per-file spellings, skip lists, and unsolved shapes for this source file.

## 2026-08-29 fleet box

Accepted owner: `func_8821E5F8`. The accepted spelling uses raw 32-bit address
arithmetic, `u16 temp_a0`, `s16 temp_v1`, `s32 temp_v0_2`, and the permuter's
empty null guard before the button dispatch. The installed declaration for
`func_88002720` is `void func_88002720(void *, u16, void *)`. The
`permute:score0:empty-null-guard` probe reported `probe_match` with
`link_verified:true`; the gate reported `accepted`, `link_verified:true`,
`gate_mode=combined`, `gate_runs=1`, and `install_compiles=1` for the full
`make -C disasm COMPARE=1` ROM gate.

Prior accepted-neighbour spellings/signatures confirmed by `file_brief`:
`func_8821EAD8(void)`, `func_8821E8C8(void)`, `func_8821E8EC(void)`, and
`func_88220248(u8 *)`. The accepted E5F8 body is the new local raw-offset
button-dispatch spelling; no display-list owner was tested in this box.

Deferred diagnostics:

- `func_8821E4B4`: 18 probe attempts, 7 `compile_failed` and 11 rejected.
  Strongest was normalized `0.7209`, raw `0.5062`; the recurring kind was
  `operand_or_scheduling_drift`, with the expected branch-likely shape still
  differing at the initial state dispatch. No link-verified candidate.
- `func_8821E964`: 17 probe attempts, 5 `compile_failed` and 12 rejected.
  Strongest was normalized `0.9677`, raw `0.6022` from the permuter-derived
  `new-var-child-base` spelling; all usable attempts were
  `operand_or_scheduling_drift`. No link-verified candidate.
- `func_8821E73C`: 5 rejected probe attempts, no compile failures. Strongest
  was normalized `0.9697`, raw `0.7879` from the conditional-spill spelling;
  the first diagnostic remained `operand_or_scheduling_drift` with the frame
  offset differing (`-0x50` expected versus `-0x58` actual). No gate run.
- `func_88220400` was not retested: existing record is 21 prior attempts,
  normalized `0.9219`, raw `0.8125`, `operand_or_scheduling_drift`.

Explicit skips: `func_8821DA70`, `func_882202E8`, `func_882204F8`,
`func_8821EE00`, `func_882206A0`, and `func_8821F01C` are dispatcher/jump-table
owners deferred because no rodata subsegment is prepared; `func_8821E0BC`,
`func_8821FFB4`, and `func_8821D930` are existing allocator-tie owners, with
`func_8821D930` also tagged `gbi-macro`. Fresh owners `func_8821DAC0`,
`func_8821DC48`, `func_8821EC34`, `func_88220050`, `func_8821DE58`, and
`func_8821E21C` were left untouched when the box ended.
