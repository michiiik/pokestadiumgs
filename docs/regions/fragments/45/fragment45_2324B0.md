# Region notes -- disasm/src/fragments/45/fragment45_2324B0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Fleet box 2026-08-29 (2026-08-29)

Accepted func_8AB0F484 with call-sequence:counter-threshold:pointer-global: s32 result initialized to 0x2B, s16 *counter = &D_8AB17246, switch on arg0, threshold check at 0xB, and func_8AB0E684(0); probe matched with link shape and the gated candidate passed link_verified:true plus full COMPARE=1 ROM gate (MD5 1561c75d11cedf356a8ddb1a4a5f9d5d). Box total: 30 variants/attempts across 3 owners, 1 accepted. Deferred func_8AB0F518 after 15 probes: best 0.9821 normalized/0.8036 raw, 224-byte size match but persistent first diff at offset 19, expected sw t6, $sp, 24 versus actual sw t6, $sp, 28; 12 operand_or_scheduling_drift and 3 instruction_drift results, no gate attempted. Deferred func_8AB0E8B4 after 8 probes: best 0.9452/0.6027, persistent frame first diff at offset 11, expected addiu $sp, $sp, -40 versus actual -32; no gate attempted. Existing func_8AB0E21C and func_8AB0E280 remain deferred per assignment as prior drift/setup owners.

## Fleet box 2026-08-31: threshold helper requeued (2026-08-31)

No accepted owner. func_8AB0D4BC received 5 probes plus 45 seconds of permuter time; best was 0.9487 normalized similarity with a 24-byte frame and an s16 temporary, still operand_or_scheduling_drift. Next spelling: hoist func_8AB023EC(0x64) into the s16 temporary while preserving the existing threshold/map structure. Keep deferred func_8AB0E21C, func_8AB0E280, func_8AB0F518, func_8AB0E8B4 and jump-table func_8AB0E0F4/func_8AB0DFC0 skipped.

## Wave 10 handoff (2026-08-31)

No accepted owner. func_8AB0EF44 was tooling-blocked after two candidate attempts failed CFE parser compilation before semantic scoring. No source, link verification, or ROM gate. Next action is to repair the runner/parser cascade involving generated assembly placeholders, then retry the raw-global dispatcher candidate.
