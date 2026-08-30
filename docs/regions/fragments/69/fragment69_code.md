# Region notes -- disasm/src/fragments/69/fragment69_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-30 wave 6 accepted sibling families (2026-08-30)

accepted: func_8F102618 and func_8F102708 match as signed-byte wrap/update helpers when D_8F1DEE48 is modeled as a 4-byte union and passed by value as func_80041FD0's third Fragment69PackedState argument; the aggregate ABI home copy emits the required sw a2, 8(sp). Exact sibling reuse changes only bytes[3] to bytes[2]. Both were link_verified and full-ROM COMPARE=1 gated.

accepted: func_8F100594 and func_8F100740 match as two-item rendering loops with a 6-byte Fragment69MenuState source record, 10-byte position records, and separate item/table-byte/Y induction variables. IDO requires the exact one-line spelling 'item = 0; tableOffset = 0; yOffset = 0; do {' to schedule both pointer-table base adjustments before counter zeroing; putting do on the next line is 105/107 exact, and putting only tableOffset/yOffset/do together is 106/107. Exact sibling reuse changes the initial color/text assets and Y base/stride (0x28/0xE versus 0x14/0xC). Both were link_verified and full-ROM COMPARE=1 gated.

## 2026-08-30 fleet box accepted owner (2026-08-30)

accepted: func_8F102A98 uses the direct counter-lvalue spelling: snapshot D_8F1DEE5C, apply the 0x200 decrement/zero clamp and 0x100 increment/one clamp directly to the global, compare the snapshot against D_8F1DEE5C, then call func_80041FD0 with *(Fragment69PackedState *)&D_8F1DEE44 and a separately assigned 0/1 var_a3. Runner probe matched with link_verified=yes; the full-ROM runner gate accepted it and verified build/pokestadiumgs-us.z64: OK. The raw-pointer/temp-variable family repeatedly drifted at expected lui/lw  versus actual  (best normalized 0.9778, raw 0.3778, 176 expected vs 180 actual), so retain the direct global-lvalue shape for this owner.

## 2026-08-30 fingerprint correction (2026-08-30)

Correction: the repeated raw-pointer fingerprint was expected lui/lw $a0 versus actual lui/lw $a1; this was a rejected probe shape, not the accepted direct-lvalue body.

## 2026-08-30 fleet box accepted call-chain owner (2026-08-30)

accepted: func_8F1036F4 matches with var_s0 initialized before the fade calls, a do loop, and the negated allowed-state condition written with literals on the left: (4 != D_8F1DEE58) && (5 != D_8F1DEE58) && (6 != D_8F1DEE58), assigning var_a1 to 1 in that branch and 0 in the else. The runner probe was link_verified and the full-ROM runner gate accepted it with build/pokestadiumgs-us.z64: OK. The direct comparison spelling (D_8F1DEE58 != 4 etc.) was a normalized 1.0 register-allocation near miss with the state address and first literal reversed, so retain the reversed-equality spelling.

## 2026-08-30 fleet box accepted camera owner (2026-08-30)

accepted: func_8F100C64 uses f32 position[3] and s32 output[3], passes both arrays to Vec3f_SetComponentsDuplicate and func_800371B4, reads the input halfwords at offsets 0 and 2, and uses raw D_8F1DECA4 offset-0xC access for func_80038E14 and GeoCamera_SetPerspective. The runner probe was link_verified and the full-ROM gate accepted it with build/pokestadiumgs-us.z64: OK. Separate locals and typed struct variants were rejected by stack-layout or immediate drift.

## 2026-08-30 fleet box expiry handoff (2026-08-30)

requeue: func_8F102394 remains unresolved at box expiry. Owner-level prior count reached 16 from the two completed probe batches; no third batch was run. Best probe 1 was normalized 0.9683, raw 0.5397, section_layout_drift, expected 244 bytes versus actual 252, with first fingerprint offset 1: expected initial indirect-object load into v0 but actual used t6. The object-temp family in probe 2 improved the fingerprint but still reached normalized 0.9516, raw 0.8226, section_layout_drift, expected 244 versus actual 248, with the clamp load/register swap at offset 47 and a 4-byte tail setup drift. Attempted direct three-argument animation-helper calls, typed item/object/method temporaries, explicit limit locals, and direct/global arithmetic variants. Next action in a fresh box: run the prepared two-argument helper batch using the object temporary plus index-pointer variants, then gate the first link-verified hit. Do not treat the prepared batch as evidence because it was not run. requeue: func_8F10049C was not reached; prior_attempts=0 at assignment and remains fresh. Resume only after resolving or terminally requeuing func_8F102394. requeue: func_8F1002F0 was not reached; prior_attempts=0 at assignment and remains fresh. Resume only after the earlier explicit owners.
