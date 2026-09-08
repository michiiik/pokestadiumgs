# Region notes -- disasm/src/fragments/43/fragment43_1E5A10.c

## Requeue: func_8AC03AFC (2026-09-01)

requeue: Wave 24 probe-only batch attempted 3 display-list candidates; all compile-failed before scoring. The initial batch's duplicate `Fragment43Color405C` declaration was corrected, after which IDO rejected the candidate macro expansion (`Syntax Error` in `gDPFillRectangle` expansion), so this is candidate syntax evidence rather than a runner/tooling failure. Assembly shape is a 0x40-frame conditional call to `func_800504BC`, then three commands: `gSPDisplayList(D_8AC07D90)`, `gDPSetPrimColor` from record offset 0x28, and an F6 rectangle using scratch angles plus record offsets 0x0C/0x0E. No similarity, link verification, gate, or source install. Next action: use a C89-compatible raw `Gfx` command construction or split the macro expansion into proven existing macro spellings, preserving declaration order and the 0x40 frame; then probe fresh variants.

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: _bzero-then-forward call chain (AGENTS.md §4) (2026-08-28)

`_bzero(dst, N); v0 = ctor(a, b); dst[0] = v0; dispatch(field, &callback, dst);` -- the callback is referenced by address even when it is still an unsolved sibling. Evidence: 5 (`func_8AC02C80/02FCC/03334/02770/02830`). Limit: `_bzero` may come before or after the constructor; word stores precede byte stores.

## Requeue: func_8AC00028 (2026-08-30) (2026-08-30)

Runner futility after 20 recorded attempts: best packed unaligned copy-loop candidates matched the 244-byte span at normalized similarity 0.8197 / raw 0.5410 but repeated operand_or_scheduling_drift at offset 57 (expected lui v1, actual lui v0). Tried packed struct assignments, m2c/goto forms, pointer/address order, branch polarity, global-end comparison, index loops, and bounded permuter runs (best permuter score 2105); requeue with a materially different register-allocation hypothesis.

## Requeue: func_8AC00028 (2026-08-30 follow-up) (2026-08-30)

requeue: func_8AC00028 remains unresolved after this 60-minute box. Probe-only best stayed at normalized similarity 0.8197; best raw similarity improved to 0.7705 with the scalar end-address plus u8 lane-pointer hypothesis, but it still mismatched at offset 96 (expected addiu $v0,$v0,0; actual addiu $t2,$t2,0). The packed-struct scalar variant preserved the target high-half sequence but mismatched at offset 97 (expected addiu $v0,$v0,0; actual addiu $v1,$v1,0). The recurring baseline fingerprint remains operand_or_scheduling_drift at offset 57 (expected lui $v1, actual lui $v0). Attempted families in this box: early scalar s32/u32 loop-end lifetime, explicit register scalar, u8 versus packed lane pointers, target/reverse initializer order, declaration/prologue order, direct/global-end compare forms, do/goto loop forms, packed copy-loop bodies, and a 120-second bounded permuter run (best score 1945; prior box best 2105). Earlier box families preserved in the preceding note include packed structs, m2c/goto, pointer/address order, branch polarity, global-end comparison, index loops, and aggregate block copies. Next action: requeue this owner with a materially different source-shape hypothesis for the low-half address scheduling, or investigate an allocator/tooling-supported way to constrain the end-address temporary; do not install or gate a non-hit.

## Requeue: func_8AC00028 allocator/load-hoist audit (2026-08-30) (2026-08-30)

requeue: func_8AC00028 remains unresolved after 241 recorded attempts. This box found a materially better load-hoist family: three explicit s32 temporaries with the fourth source loaded after the first destination store, producing a complete 244-byte span at normalized similarity 0.9508 / raw 0.7377. The exact runner fingerprint is operand_or_scheduling_drift at offset 85 / instruction 21: expected lui $t2 for D_8AC07BB4, actual lui $v0; the live source-4 pointer and end-address scalar are swapped. Direct IDO disassembly confirmed the same swap and showed the four-temporary form spills an 8-byte frame, while one-temporary m2c-shaped forms remap the lane registers. Attempted in this box: allocator declaration/type and split-lifetime variants; three-temp load-hoist/reuse and address-taken-temporary variants; m2c loop order with target/reverse/separate initializer forms; true do-while (compiler unrolled it); and a 120-second bounded permuter on the 0.9508 body (best permuter score 570 from base 680, no score-0 result). The runner/recipe audit found no tooling defect; all runner probes were gate=false, with no link_verified/full-ROM hit and no source installation/name change. Next action: requeue with a genuinely compiler-supported register-allocation constraint or a different aggregate/source abstraction that preserves the load-hoist schedule and assigns source-4 to $t2 and the end scalar to $v0; do not repeat the exhausted pointer/order spellings.

## Fleet box handoff 2026-08-30 (2026-08-30)

Accepted: func_8AC0405C via u8 D_8AC07D90[] plus RGBA field order and gSPTextureRectangleFlip corners (arg0,arg1,arg0+2,arg1+arg2), dsdx=0x400,dtdy=0; full-ROM link=yes, commit bf0f6448. Accepted: func_8AC044DC via the existing accepted Fragment43Color405C callee, proven scratch struct, and inner declaration order x,color,y,z; full-ROM link=yes, commit 68ab2186. No evidence-backed names were available. requeue: func_8AC0198C expired unresolved; best corrected direct/macro family was normalized 0.7951 / raw 0.3033 at 456 bytes, section_layout_drift fingerprint [section_layout_drift,3,0,0x27bdffa8,0x27bdffb8], target 488 bytes; earlier explicit packet form was 472 bytes with first fingerprint [section_layout_drift,8,2,0x8c860014,0x3c020000]. Next action: preserve the 88-byte frame while using the 405C-proven u8 display-list symbol and force the post-call inline pointer/height homes without direct-store address hoisting. requeue: func_8AC017B0 terminal stuck after 15 attempts; best normalized 0.7899 / raw 0.2185 at 440 bytes, section-layout/frame fingerprint [section_layout_drift,3,0,0x27bdffa8,0x27bdffd8], target 476 bytes; next action is a materially different allocator/layout hypothesis for the 88-byte frame and indirect-versus-inline offset-0x14 objects. requeue: func_8AC03F64 terminal stuck after 20 attempts; best normalized 0.9355 / raw 0.3387 at 248 bytes, operand_or_scheduling_drift fingerprint [operand_or_scheduling_drift,17,4,0x3c180000,0x3c0fde00], expected D_8AC07D90 load versus actual DE00 command load; next action is reuse the accepted 405C u8-array/RGBA-field declaration with the non-flipped rectangle operands. requeue: func_8AC0444C terminal stuck after 15 attempts; best normalized 0.8333 / raw 0.4444 at 144 bytes, frame fingerprint [operand_or_scheduling_drift,3,0,0x27bdffd0,0x27bdffe0], target 48-byte frame versus 32-byte candidate; next action is a materially different by-value color ABI/local scratch layout. requeue: func_8AC0619C terminal repeated-drift futility after 34 attempts; best normalized 0.9394 / raw 0.3636 at 132 bytes, first fingerprint [instruction_drift,0,0,0xafa50004,0x00057300], expected sw a1,4(sp) versus actual sll t6,a1,12; next action is a fresh argument-home/float-table scheduling hypothesis. requeue: func_8AC06220 terminal repeated-drift futility after 14 prior attempts with best normalized 0.9394 / raw 0.3939 at 132 bytes and the same sw/sll fingerprint; next action is a materially different argument-home/float-table scheduling hypothesis. requeue: func_8AC062A4 terminal repeated-drift futility after 15 prior attempts with best normalized 0.9394 / raw 0.3636 at 132 bytes and the same sw/sll fingerprint; next action is a materially different argument-home/float-table scheduling hypothesis. requeue: func_8AC06328 terminal repeated-drift futility after 16 prior attempts with best normalized 0.9394 / raw 0.3939 at 132 bytes and the same sw/sll fingerprint; next action is a materially different argument-home/float-table scheduling hypothesis.

## Fleet box 2026-08-31: multiply helper requeued (2026-08-31)

requeue: func_8AC0665C received 9 serial CC_CHECK-enabled variants. Best normalized similarity was 1.0 and raw 0.9808, but the persistent operand drift is expected multu s1,t6 versus actual multu t6,s1. No link-verified candidate or ROM gate. Next action: investigate an allocator/register constraint or materially different multiplication abstraction; do not repeat commuted operands, raw offsets, or explicit stride temporaries.

## Requeue: func_8AC06DC8 recursive helper (2026-09-01) (2026-09-01)

requeue: func_8AC06DC8 was probed with 5 runner-only variants after the recursive tooling path was repaired; no link-verified hit or gate. The best valid all-declarations raw-offset body produced 232 bytes versus expected 208, normalized similarity 0.6379 / raw 0.569, with operand_or_scheduling_drift first at offset 9 (expected lh $v0, actual lh $v1), followed by prologue/global scheduling and loop-shape drift. Initial attempts that declared locals after statements were compile failures from IDO syntax rules, not tooling failure. Attempted raw pointer/null, typed base, direct field, declaration-hoisted recursive forms. Next action: materially different typed overlay/field ABI and declaration/register lifetime hypothesis; inspect recursive call argument roles before further variants.

## Requeue: func_8AC01354 (2026-09-02) (2026-09-02)

requeue: func_8AC01354 remained unresolved after a 9-candidate CC-check-enabled runner probe batch (gate=false, auto_gate=false); no probe match, link_verified result, full-ROM gate, or source install. Prior best remains normalized/raw 0.9535 (168-byte span, 42 instructions), fingerprint [operand_or_scheduling_drift,13,3,0xafb1001c,0xafb00018] (expected sw s1,28(sp), actual sw s0,24(sp)). Fresh best was normalized 0.8571 / raw 0.8095 at the complete 168-byte span, fingerprint [operand_or_scheduling_drift,25,6,0x00a0a025,0x00008825] (expected move s4,a1, actual move s1,zero); other fresh variants expanded to 180-188 bytes and drifted in the saved-register frame. Attempted materially distinct families: declaration/lifetime ordering, do-while with early return, u8-record pointer, for-loop update expression, guard/infinite loop, typed s32-array overlay, while/early-return, offset spelling, and explicit do-while with reloaded stored value. Next action: requeue with a focused ABI/register-lifetime hypothesis preserving the exact 0x30 frame and assembly's simultaneous long-lived values (arg1 in s4, record pointer in s0, count in s2, index in s1, D_8AC07F28 in s3), likely by introducing a named record pointer plus separate s32 index/count declarations in the order that forces those callee-saved assignments; then probe >=8 fresh variants. Do not repeat the rejected loop forms or gate a non-hit.

## 2026-09-02

requeue: func_8AC015B0 (2026-09-02)
This box ran an 8-candidate CC-check-enabled MCP probe batch (gate=false, auto_gate=false), with no link_verified hit, full-ROM gate, or source installation. All seven compiling variants retained operand_or_scheduling_drift but missed the required exact 0x20 frame: best fresh normalized similarity 0.8529 / raw 0.6176, complete 132-byte expected span versus 136-byte actual, first-diff fingerprint [operand_or_scheduling_drift,3,0,0x27bdffe0,0x27bdffe8] (expected addiu sp,-32; actual addiu sp,-24). The prior best remains normalized 0.9118 / raw 0.7059, label m2c:u8-void. Attempted families: shared declaration with func_8AC013FC(s16,s16,s32,s16), s32 versus s16 result, explicit casts, declaration/lifetime ordering, direct conditional, guard-return, goto control flow, branch polarity, local copies of D_8AC099B8/BA, and compact versus split call forms. Variant 8 also compile-failed because it returned an expression from void; this was candidate syntax evidence, not tooling failure. Concrete next action: requeue with a materially different ABI/frame hypothesis that forces the incoming stack arg to be loaded as s16 at 0x32(sp) before argument homes, likely using a named fourth parameter type/ordering and an explicit volatile or address-taken stack temporary only if supported by prior accepted same-frame bodies; preserve func_8AC013FC four-argument prototype and test >=8 fresh variants. Do not repeat the rejected -0x18-frame expression forms or gate a non-hit.

## Fleet box 2026-09-02: func_8AC01574 tooling-blocked (2026-09-02)

tooling-blocked: Wave 45 box. Preflight confirmed call_sequence owner func_8AC01574 with prior_attempts=3. Assembly is a 0x20-byte wrapper: lh stack arg at 0x32(sp), homes a0/a1, sign-extends both via sll/sra, calls func_8AC013FC, returns void. Prepared /private/tmp/gs45_func_8AC01574.json with 8 distinct hypotheses and validated it with python3 -m json.tool (exit 0). After required 360-second delay, launched exactly one fresh CLI runner command: python3 tools/fleet_probe.py /private/tmp/gs45_func_8AC01574.json --json /private/tmp/gs45_func_8AC01574.result.json > /private/tmp/gs45_func_8AC01574.log 2>&1 & echo $!. Shell emitted zsh:1: nice(5) failed: operation not permitted; subsequent poll showed result artifact absent and log present but 0 bytes. No runner status, scores, mismatch kind, first-diff fingerprint, sizes, futility, link state, acceptance, or source install exists. Attempted family: direct wrapper call, explicit casts, s16/s32 temporaries, volatile stack arg, unsigned/formal-width variants, explicit locals. Next action: rerun fresh CLI only after host launch/resource issue is repaired; preserve the 0x20 frame and investigate func_8AC013FC ABI/argument count materially rather than treating missing output as source evidence.

## Coordinator replay after wave 45 (2026-09-02)

Directly replayed /private/tmp/gs45_func_8AC01574.json without the host nice wrapper. All eight candidates were probe_rejected; best normalized/raw similarity 0.7778/0.6111, with stack frame drift (-32 expected, -24 actual) and one instruction_drift candidate. Requeue with a frame/declaration-order hypothesis.

## 2026-09-05

func_8AC06DC8: matched (call_sequence:recursive:permuter-exact-limit-expression), 6 iterations, agent codex

## 2026-09-05

func_8AC0672C: plateau at 1.0 (raw 0.9811), mismatch register_allocation_only; tried families: call_sequence; tie-pool no

## 2026-09-05

func_8AC0686C: time cap at 0.0 (raw None) after 2636s, mismatch unknown; tried families: (none); tie-pool no

## 2026-09-05

func_8AC03C28: matched (constant_map:struct_copy:local_struct_s32), 1 iterations, agent gemini

## 2026-09-05

func_8AC063AC: matched (state_field_access:motion_struct:baseline_arg0_if_u16), 1 iterations, agent gemini

## 2026-09-05

func_8AC06EC0: time cap at 0.9231 (raw 0.7308) after 82357s, mismatch instruction_drift; tried families: constant_map; tie-pool no

## 2026-09-05

func_8AC0619C: time cap at 0.9697 (raw 0.7576) after 2400s, mismatch instruction_drift; tried families: state-field; tie-pool no

## 2026-09-05

func_8AC06220: time cap at 0.9697 (raw 0.7576) after 2400s, mismatch instruction_drift; tried families: state_field; tie-pool yes

## 2026-09-06

func_8AC03C74: time cap at 0.9111 (raw 0.8667) after 90697s, mismatch instruction_drift; tried families: constant_map; tie-pool no

## 2026-09-06

func_8AC06C10: time cap at 0.9783 (raw 0.9348) after 2400s, mismatch instruction_drift; tried families: arithmetic, cast, direct, group, lifetime, loads, locals, ptrabi, raw, sequencing, shift, struct, volatile, width; tie-pool no

## 2026-09-06

func_8AC05F38: plateau at 0.0 (raw None), mismatch unknown; tried families: (none); tie-pool no

## 2026-09-06

TYPE CONFLICT: Fragment43Motion602C is struct Fragment43Motion602C, not extern void func_8AC05F38(Fragment43Motion602C *)

## 2026-09-06

func_8AC03F64: matched (state_field_access:rectangle:nonflipped-dtdy), 1 iterations, agent codex

## 2026-09-06

func_8AC016A8: plateau at 0.9848 (raw 0.8333), mismatch instruction_drift; tried families: init_sequence; tie-pool no

## 2026-09-06

func_8AC04154: matched (state_field_access:direct_macros:s32_corners_405c), 1 iterations, agent gemini

## 2026-09-06

func_8AC04418: matched (call_sequence:direct:s32_formal_parameters), 1 iterations, agent gemini

## 2026-09-06

func_8AC043A8: plateau at 0.0 (raw None), mismatch unknown; tried families: call_sequence; tie-pool no

## 2026-09-06

func_8AC043E0: matched (call_sequence:forward-rvalue:typed-aggregate), 3 iterations, agent codex

## 2026-09-06

func_8AC01574: matched (call_sequence:wrapper:s16-fourth-s32-middle), 1 iterations, agent codex

## 2026-09-06

func_8AC06D8C: plateau at 0.9375 (raw 0.875), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-06

func_8AC00270: plateau at 0.9231 (raw 0.8077), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-06

func_8AC00FFC: plateau at 0.9259 (raw 0.9259), mismatch instruction_drift; tried families: call_sequence; tie-pool no

## 2026-09-06

func_8AC06328: plateau at 0.9697 (raw 0.7576), mismatch instruction_drift; tried families: state_field_access; tie-pool yes

## 2026-09-06

func_8AC05E40: plateau at 0.8947 (raw 0.5), mismatch operand_or_scheduling_drift; tried families: call_chain; tie-pool no

## 2026-09-06

func_8AC06570: matched (constant-map:ceil-div:narrow-quotient-wide-remainder), 2 iterations, agent codex

## 2026-09-06

func_8AC01F8C: plateau at 0.95 (raw 0.425), mismatch operand_or_scheduling_drift; tried families: state-field; tie-pool no

## 2026-09-08

func_8AC04418: matched (call_sequence:color_access:explicit_pointer_cast), 1 iterations, agent codex

## 2026-09-08

func_8AC015B0: matched (call_sequence:result-narrowing:precompute-s16), 1 iterations, agent codex

## 2026-09-08

func_8AC0444C: plateau at 0.0 (raw None), mismatch unknown; tried families: call_sequence; tie-pool no

## 2026-09-08

func_8AC0665C: plateau at 0.9808 (raw 0.9615), mismatch instruction_drift; tried families: call_sequence; tie-pool no
