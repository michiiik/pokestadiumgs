# Region notes -- disasm/src/fragments/63/fragment63_308D70.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 19 func_87E078DC (2026-08-31)

accepted: call-chain:switch:scoped-inner-temp. Full ROM gate accepted with link_verified=true after probe_match. Exact spelling uses s32 temp_v0 declared before s32 sp20; initialize sp20=2 before D_87E1EB90=arg0; scope temp_v0_2 inside case 1 and use a nested switch; preserve word load *(s32 *)(arg0 + 8) before the narrow sb. Isolated object matched the 288-byte target exactly. Earlier variants showed stable offset/scheduling drift when sp20 was declared first or temp_v0_2 function-scope (sp20 landed at sp+0x24 and/or global store preceded li).

## 2026-09-08

func_87E06E48: matched (constant_map:two-scans:assign-then-return), 1 iterations, agent codex

## 2026-09-08

func_87E07278: plateau at 0.9697 (raw 0.8485), mismatch instruction_drift; tried families: constant_map, init-decl, limit-local, ptr-temp; tie-pool no

## 2026-09-08

func_87E05CE4: matched (call_chain:five_args:callee-result-order), 1 iterations, agent codex

## 2026-09-08

func_87E06BCC: plateau at 0.0 (raw None), mismatch unknown; tried families: call_chain; tie-pool no

## 2026-09-08

func_87E07040: matched (call_chain:random-angle:decl-v0-v1-a0), 3 iterations, agent codex

## 2026-09-08

func_87E06B54: matched (call_sequence:pool_loop:pointer-postincrement), 1 iterations, agent codex
