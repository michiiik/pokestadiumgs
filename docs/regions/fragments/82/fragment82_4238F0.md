# Region notes -- disasm/src/fragments/82/fragment82_4238F0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-29 (2026-08-29)

Accepted func_82D04B84 with gbi:display-list:nested-color:raw-fields. Use gSPDisplayList(D_800D0510++, D_82D071D8), raw u8/s16 field accesses, nested sp24 color selection, and direct helper calls. Probe hit had link_verified:true; gate accepted with one combined full COMPARE=1 run. Do not replace the display-list macro with words.w0/w1 stores.

Accepted func_82D065C0 with state:dispatch-switch:s32-count. The winning spelling uses a u8 * argument, a switch on arg0[0] with cases 2/3/5/4, then an s32 count temporary from offset 0xC and explicit flag-byte updates at offsets 0xB/0xA. Probe hit had link_verified:true; gate accepted with one combined full COMPARE=1 run.

Deferred func_82D05D74 after two five-variant batches: best 0.9167 normalized and 0.7708 raw, operand_or_scheduling_drift, expected 196 bytes versus actual 200. Deferred func_82D0639C after one five-variant batch: best 0.8136 normalized and 0.678 raw, operand_or_scheduling_drift. Deferred func_82D03778 because the existing earlier func_80044270 call creates a declaration-context conflict and the no-declaration form stayed at 0.8261 normalized/0.4783 raw with a frame mismatch. Deferred func_82D05C90 because source-order extern/type context conflicts persisted and it calls deferred jump-table owner func_82D05BD8. Do not reopen tie-heavy func_82D068A0 without a new hypothesis; its prior best was a register-allocation-only tie at 1.0 normalized/0.95 raw after 45 attempts. User-deferred jump/dispatcher owners remain untouched: func_82D068F0, func_82D06CC0, func_82D06514, func_82D05BD8.
