# Region notes -- disasm/src/fragments/14/fragment14_FF070.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: float divide by a power of two (AGENTS.md §4) (2026-08-28)

Divide by the **integer** literal (`x / 16`), not `16.0f`: a float literal divisor is strength-reduced to `mul.s` by the reciprocal, an int divisor keeps `div.s`. Evidence: 1 (`func_8130A98C`).

## Unsolved shape: $v0/$v1 swap on counter pairs (AGENTS.md §5) (2026-08-28)

Decrement/increment counter pairs stuck at similarity 1.0 with `$v0`/`$v1` swapped (`func_8130B91C`, `func_8130B95C`).

## Terminal register tie: func_813074E4 (2026-08-30) (2026-08-30)

func_813074E4 reached terminal register-tie futility after 45 prior attempts were recorded at the final batch boundary and 49 variants were sent in this box (53 total attempts including the 4 pre-box attempts). Best hand candidate was call-chain:raw-base:no-pointer-local / callee-first-expression: normalized similarity 1.0000, raw similarity 0.9714, expected and actual size 140 bytes. The remaining fingerprint is register allocation only at offset 76: expected `addu $t8, $t7, $v0`, actual `addu $t8, $v0, $t7`; all frame and stack offsets match. Earlier explicit cached-pointer variants had normalized 1.0000/raw 0.6286 and immediate drift from a -0x28 frame; compound-add variants regressed to normalized 0.8571/raw 0.5429 with the same frame drift. Attempted hypothesis families: pointer-local and integer-local cached base, declaration/order and field temporaries, conditional/branch argument construction, raw-base/no-pointer-local, pointer and integer argument widths, explicit call-result temporaries, callee-first expressions, compound assignment and arithmetic order. Runner futility: `register-tie: 6 prior attempts at >=0.99 register_allocation_only -- source-shape variants will not close this -- register tie -- stop`. Next action: leave for permuter/register-tie handling; do not spend another hand-decompilation box on this source shape unless the permuter or a new compiler/tooling rule changes.

## Box handoff: shared clamp accepted; display-list owner requeue (2026-08-30)

Accepted owner: func_8130C270. Spelling was a padded overlay with explicit f32 delta/step, `step = func_816092FC() / 8`, clamp branches, and `func_8130B12C(arg0)`; probe produced a link-verified hit and the full ROM gate passed (`1561c75d11cedf356a8ddb1a4a5f9d5d`). Commit: 4cf5e279. No evidence-backed name was available.

Requeue owner: func_81308078 (gbi-macro, jump_table_status=not_applicable). All display-list variants used gSPDisplayList/gDPSetFillColor, but no candidate reached link verification. Best hand candidate: `gbi-macro:ctx-reuse2:sp80-sp78-v05sp80`, expected 1956 bytes/489 instructions versus actual 1876 bytes/469 instructions, frame `-0xC8` versus `-0xC0`, normalized similarity 0.7832, raw similarity 0.3333; first diagnostic is the frame/register layout (`expected sw $fp,72(sp)`, actual `sw $a2,200(sp)`). Earlier goto/context-overlay candidate reached raw 0.3211 at 1876/469. Attempted families: compact m2c macro body, reduced/shared locals, goto-form control flow, arg2 lifetime locals, padded context overlay, stack-slot reuse, and padded record overlay. Next action: requeue with a compiler-faithful source rewrite that reproduces the `-0xC0` frame and `$fp/$s6/$s7` allocation before trying any gate.
## Wave 20 accepted owner (2026-09-01)

Accepted `func_8130BF1C` after 53 variants across eight probe batches. The padded struct overlay spelling (`arg0->value += func_816092FC()`, clamp at `16.0f`, then `func_8130AF94`/`func_81302290`) produced `link_verified=true`; the full `make -C disasm COMPARE=1` gate passed with ROM MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. Commit `7656c93e`; no evidence-backed name was available.
