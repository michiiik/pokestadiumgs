# Region notes -- disasm/src/fragments/46/fragment46_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Unsolved shape: branch-likely null guard (AGENTS.md §5) (2026-08-28)

A leading null/zero guard that IDO emits as a branch-likely (`bnel`/`beql`) where every C spelling produces a plain `bne` (`func_8AE011E0`/`func_8AE01248`). The §4 guard-polarity row does not cover it.

## Fleet box 2026-08-29: accepted owners and deferred near-misses (2026-08-29)

Accepted via MCP full linked ROM gate: func_8AE00380 label camera:temps:u8-ordered (two temporary u8 field pointers, 0xB4 then 0xA8); func_8AE0043C label gbi:display-env:hex-components (gSPDisplayList/gDPSetEnvColor/gSPDisplayList/gSPDisplayList with D_800D0510++); func_8AE03214 label range:ascending:s16 (ascending s16 range chain); func_8AE038DC label callchain:address-global (0x100-byte local buffer and D_8AE083EC as an address-decaying u8 array). Every accepted candidate reported link_verified:true and one combined full COMPARE=1 gate run. Deferred: func_8AE01164 best 0.8387 normalized / 0.4516 raw, instruction_drift around branch-likely scan and unaligned copy; func_8AE012B0 best 0.9091 normalized / 0.5758 raw, operand_or_scheduling_drift around output base and packed copy; func_8AE00230 best 1.0 normalized / 0.9032 raw, exact-size register-allocation tie (oracle v1 versus candidate t8 for D_8AE09B44 pointer store; probe-only companion retyped func_8AE00020 but did not install); func_8AE0605C best 0.8125 normalized / 0.4375 raw, state spill/branch-form drift; func_8AE027B0 best 1.0 normalized / 0.9783 raw, exact-size add.s operand-order register tie. Do not retry tie-pool owners func_8AE00C94, func_8AE032C8, func_8AE002AC, func_8AE00314, func_8AE01738; leave dispatcher_switch/jump-table owners as assembly. gDPSetFillColor was a one-instruction near-miss for 0043C; opcode 0xFB requires gDPSetEnvColor with four component arguments.
