# Region notes -- disasm/src/fragments/13/fragment13_EEC50.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Unsolved shape: list-scheduler order around a non-zero stack literal (AGENTS.md §5) (2026-08-28)

Forward-call wrappers whose last stack argument is a non-zero literal (`func_8005F37C`; sibling `func_8005F5D4` is in `585D0.c`) get a different list-scheduler order around the call than the accepted `0`-literal siblings; every source reordering gave byte-identical diagnostics.

## Accepted GBI render helpers and 2026-08-29 sweep (2026-08-29)

Accepted func_82401E30 and func_82401F08 with label gbi-macro:env-first-field-order:v3, and func_82401FE0 with label gbi-macro:env-white:direct-fields-v1. The winning spelling uses gDPSetEnvColor on D_800D0510++, the raw u16 coordinate fields at offsets 0 and 2 from the proven D_8240783x record, then func_8004D1FC and func_82400BD0. Each first hit was gated; link_verified:true and the combined full COMPARE=1 ROM gate passed. No evidence-backed symbol renames were available, so naming was not run.

Deferred after probe-only batches: func_82404230 best normalized 1.0/raw 0.963 register_allocation_only; func_82402904 best normalized 1.0/raw 0.9643 with the lui $a0 versus $a2 operand tie; func_82405C0C best normalized 0.9867/raw 0.6 with the remaining addu destination/register scheduling drift; func_824059E4 retained stack-frame/local-slot drift (best focused variants 0.8621, prior best 0.9655); func_82402A14 retained frame-shape drift (best 0.8485); func_82404990 best normalized 1.0/raw 0.9375 with the addu operand-order tie; and func_824020B4 best normalized 1.0/raw 0.9677, 60/62 exact instructions, with the second display-list address setup in $a2 instead of oracle $a0. None of these deferred owners was gated. The documented non-zero stack-literal scheduler blocker around func_8005F37C was unchanged and skipped.
