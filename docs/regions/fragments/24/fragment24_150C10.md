# Region notes -- disasm/src/fragments/24/fragment24_150C10.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## func_82B02A34 requeue after isolated probe hits (2026-08-29)

requeue; tooling-blocked at the 60-minute worker boundary. Owner func_82B02A34 is a 34-instruction call_sequence with no prior attempts at assignment. Required source shape: a local #pragma pack(1) one-word s32 overlay is needed to emit the observed lwl/lwr source load and swl/swr destination store; ordinary s32 pointer casts emitted lw/sw and stalled at the outer-branch fingerprint. Attempted hypothesis families: raw offset and s32/u32 casts; early-return, direct-expression, ternary, and assign-then-return forms; memcpy/_bcopy and indexed packed-record forms; packed-word overlay with declaration-order, temporary/register-allocation, mode-local, arg0 reuse, and branch-polarity variants. Best rejected near-miss was normalized 1.0, raw 0.9118, exact 136-byte size, with only the final mode branch/value polarity differing: expected li a0,167; bltz t3; ... li a0,168 versus actual li a0,168; bgez t3; ... li a0,167. The final packed candidates branch-polarity:packed:ge-then-a8-direct and branch-polarity:packed:gtminus-one both returned probe_match with link_verified=true. A runner-only --gate attempt in an isolated worktree reached the full compare but was rejected before target installation because unrelated src/10BB0.c host clang syntax errors call func_800103C8 with two arguments although its visible prototype accepts one; batch_status=no_candidate_accepted, gate_runs=3, exit_code=2, no accepted row. Shared checkout was not run: foreign disasm/src/517E0.c remained dirty and multiple MCP runner processes were live. Next action: after the foreign transaction and checkout gate prerequisite clear, rerun one winning packed candidate through the runner with gate=true in the shared checkout; do not hand-copy or manually install the body. Preserve the two link-verified probe spellings and recheck the full-ROM gate before naming, coverage, or commit.

## Fleet box 2026-08-30 accepted spellings and requeues (2026-08-30)

Accepted through the MCP runner and full ROM gate: func_82B02924 with label packed:state-init:mode-initialized; func_82B04558 with label multi_call_wrapper:color-select:mode-dispatch:switch-case0; func_82B0556C with label predicate:global-state:explicit-empty-true. Each reported link_verified=true, probe_status=probe_match, batch_status=accepted, and a combined full make COMPARE=1 gate. Requeues from this box: func_82B07BEC best call_sequence:state-select:switch, normalized 1.0/raw 0.9231, immediate_drift at stack offset sp+0x24 versus sp+0x2c; attempted switch/if-else, raw and typed stack arrays/structs, padding, scalar declaration orders, volatile and outgoing-slot forms, then permuter; next hypothesis is address-observable compiler stack-slot layout. func_82B03688 best normalized 0.9348/raw 0.7826, operand_or_scheduling_drift with expected 0x48 frame versus actual 0x40; attempted m2c/similar solved struct and array loop forms, explicit temporaries, conditional entry, pointer/global order, volatility and local-size variants; next hypothesis is exact table alias plus 0x48 stack layout. func_82B00F68 best normalized 0.8983/raw 0.5085, expected 236 bytes versus actual 212, operand_or_scheduling_drift; attempted raw/typed record and rectangle-pointer overlays, cached/reloaded bounds, clamp polarity and guard forms; next hypothesis is the original rectangle record alias/source shape. func_82B01E0C best normalized 0.9394/raw 0.697 at exact 264-byte size, operand_or_scheduling_drift/register allocation; packed-word raw, pointer, local, union and record overlays plus a 30-second permuter pass did not close; next hypothesis is the original packed record source declaration. func_82B02CA0 best normalized 0.9273/raw 0.6727, expected 228 versus actual 236, operand_or_scheduling_drift around the global limit load and result register; requeue with explicit limit/temporary variants. func_82B02ABC best normalized 1.0/raw 0.8519 at exact 232-byte size, register allocation tie between limit/result registers after explicit limit-local variants and permuter; requeue for permuter or a materially different ABI spelling. func_82B029B8 reached normalized 1.0 at exact 124-byte size with volatile global pointer but remains a register allocation tie; the aligned global-source form was normalized 0.9375/raw 0.8438 and four bytes long; requeue for global address/load scheduling. func_82B018CC best normalized 0.9286/raw 0.6429 after explicit result-pointer loop forms, instruction/control-flow drift; requeue with a different loop lowering. func_82B02BA4 reached normalized 1.0/raw 0.8136 at exact 252-byte size but remains a limit/result register allocation tie; requeue for permuter or ABI-level source shape.

## Fleet box 2026-08-30 func_82B03F38 repeated-drift requeue (2026-08-30)

requeue; runner futility reached after 24 prior attempts (25 recorded candidate attempts in this box). No body was installed and no ROM gate ran. Best normalized similarity 0.9273, best raw similarity 0.7273, expected 52 instructions / 208 bytes versus the best actual 55 instructions / 220 bytes; mismatch_kind=section_layout_drift. Dominant first-diff fingerprint: ["section_layout_drift",3,0,"0x27bdffb8","0x27bdffc0"] (expected addiu $sp,$sp,-72; actual addiu $sp,$sp,-64). The recurring source-shape drift is an extra saved register: target saves s2/s1/s0 and reloads D_82B1246C with lui t6/lh t6,0(t6) inside the loop, while direct global spellings hoist the global base into s2 and use s3 for the loop bound, shifting the body and tail. Attempted hypothesis families: padded/compact coordinate overlays, raw s16 array and byte-buffer/offset forms; explicit color temporary versus direct v0 forwarding; declaration order, explicit loop limit, do/for/while/goto control flow, branch polarity and ternary; volatile cast, local volatile pointer, block-local selected s16, and volatile-object declaration (compile failed because the file already declares the symbol nonvolatile); a non-conflicting linker-alias declaration was also an IDO syntax compile failure; runner permuter 45 seconds timed out with base_score=525 and no outputs. Next materially different hypothesis: use a compiler-supported, non-conflicting volatile/global alias or a separately runner-mediated declaration-level ABI change that prevents loop-invariant global-address CSE, then rerun one candidate; do not repeat direct D_82B1246C loop spellings or the listed register/layout variants.

## Wave 6 handoff (2026-08-31)

Wave 6 handoff: func_82B04624 unresolved after 12 serial CC_CHECK=1 probes. Best normalized/raw similarity was 1.0000/0.9836 with immediate_drift; frame and instruction count otherwise matched, but expected the local buffer at sp+56 and actual placed it at sp+48. Preserve the 0xC0 frame and adjust declaration/stack-slot ordering to place the buffer at sp+0x38.

## func_82B07960 requeue 2026-08-31 (2026-08-31)

requeue; func_82B07960 fresh owner attempted 3 batches / 5 variants under CC_CHECK=1, no probe hit or gate. Best label call_sequence:mode-loop:switch-raw-bound, normalized 0.8571, raw 0.4921, expected 252 bytes vs actual 248; mismatch operand_or_scheduling_drift, first diff offset 5: expected sw $s2, $sp, 32 but actual sw $ra, $sp, 36. Other labels raw-while and switch-u8-bound-local were 0.7778/0.4603 and 0.7619/0.4444. Tried raw while, typed pointer, switch with raw bound, and local-limit variants; declarations supplied exact later prototypes. Next action: materially different ABI/local-layout model to make IDO save s2 before ra (likely typed packed state/record overlay or declaration ordering matching address-observable global base), then probe and sequential full-ROM gate.

## func_82B01F14 repeated-drift requeue (2026-09-01) (2026-09-01)

requeue; func_82B01F14 (fresh owner, 66 instructions) received 30 recorded candidate attempts across five probe-only batches in this box, with no probe hit, link verification, ROM gate, or source edit. Best normalized similarity 0.9394 and best raw similarity 0.7121 at exact 264-byte size; dominant first-diff fingerprint is ["operand_or_scheduling_drift",1,0,"0x240f0061","0x240e0061"]: expected addiu $t7,$zero,97 but actual addiu $t6,$zero,97. The body is a packed-record initializer: three initial halfword constants, ten unaligned 32-bit packed copies, two halfword constants, and three bytes from D_82B085BC. Attempted hypothesis families: raw packed-word offset assignments, typed base and u8 pointer forms, packed struct/member overlays, explicit s16/u16/s32 scalar temporaries and declaration/order variants, volatile base, pair16 packed members, and compound/pair literals (unsupported or stack-size drift). The 264-byte direct packed forms otherwise preserve target size and shape but retain the register tie; runner reports repeated-drift after 20 prior rejected attempts. Next action: run the decomp-permuter once toml is available, or use a materially different compiler ABI/register-allocation spelling that makes both initial constants live before their stores; do not repeat direct packed offset/member variants. Tooling note: optional decomp-permuter environment currently fails ModuleNotFoundError: toml.

## Wave 26 func_82B025E0 packed initializer requeue (2026-09-01) (2026-09-01)

requeue; func_82B025E0 (66 instructions, fresh at box start) received 51 recorded attempts in this box across packed raw-word direct/source-order, packed scalar temporaries, packed formal/indexed pointer forms, reversed initialization order, typed outer/Pair overlays, local global/destination pointers, volatile accesses, and global declaration type variants. No source edit, probe hit, link verification, ROM gate, or acceptance. Best normalized similarity 0.9394 and best raw similarity 0.7424 at exact 264-byte size (the direct packed form is 0.9394/0.697); dominant mismatch_kind=operand_or_scheduling_drift. Direct packed words preserve the target lwl/lwr/swl/swr sequence and all 66 instructions, but expected initial constant registers are t7/t8/t6 while actual is t6/t7/t8; expected li t1,404 but actual t9; expected D_82B085C8 address in t3 but actual a1; and later expected p38 copy/0xA0 stores are scheduled differently. Reversed u16-index initialization improved raw to 0.7424 but changed the p1/p0 store dependency order and did not close. Typed outer structs added 48 bytes; stack/pair temporaries added frames. Attempted next hypotheses must be materially different: recover the original packed record declaration/field alias and IDO register-lifetime ordering, or run decomp-permuter once its missing toml dependency is repaired; do not repeat direct raw packed forms. Tooling is otherwise healthy (workers=1; no EMFILE); MCP permute_candidate is blocked by ModuleNotFoundError: toml.

## 2026-09-02

requeue; func_82B0341C fresh owner: two 8-candidate runner batches compile_failed before scoring. Batch 1 used invalid second subscript with s32* D_82B085FC; batch 2 corrected table shape but redeclared existing func_8004C990 (s32) via declarations, causing preflight compile failure. No source edit, link verification, ROM gate, or acceptance. Next action: rerun with declarations limited to symbols absent from file (do not redeclare func_8004C990); preserve packed raw u8 record offsets 0x50/0x52 and pair[2] ABI.

## func_82B041C8 call-chain requeue (2026-09-02) (2026-09-02)

requeue; func_82B041C8 (68 instructions, prior_attempts=4 at assignment) received three probe batches in this box: first two batches of 8 compile_failed because candidate bodies were supplied with outer braces (runner expects full function definitions), then the corrected full-definition batch scored all 8 with host CC checks enabled. No source edit, link verification, ROM gate, or acceptance. Best normalized/raw similarity 0.8235/0.5000 (call-chain:full:typed-mode), mismatch_kind=operand_or_scheduling_drift, expected 272 bytes vs actual 248; first-diff fingerprint at instruction 34: expected addiu $a1,$zero,255 vs actual addiu $a1,$zero,-1. Base and callee-temp forms scored 0.8088 normalized / 0.5147 raw, expected 272 vs actual 252, first diff at instruction 37: expected lui $v1,0x0000 vs actual lui $a0,0x0000. Attempted families: GBI macro display-list appends (compile_failed because macro expansion under if/else), raw Gfx pointer command writes, one shared command pointer, three command pointers, mode initialization/branch polarity, declaration order/lifetime, separate render-mode assignment, and callee-result temporary. Next materially different action: reconstruct the original compiler-visible display-list type/alias and preserve the observed global-pointer address in a dedicated local before mode/command temporaries; then vary exact command struct field access or use proven gbi macros outside conditional contexts. Do not repeat the submitted raw pointer forms or retry the malformed brace payload. Tooling otherwise healthy; no jump-table/YAML work performed.

## func_82B01BB8 requeue after raw and packed probes (2026-09-02) (2026-09-02)

requeue; func_82B01BB8 fresh owner received two 8-candidate probe batches (16 distinct candidates total), host CC checks enabled, no source edit/install, link verification, ROM gate, or acceptance. Batch 1 attempted raw u8/s16/s32 overlays, temporaries, declaration order, volatile and split-load forms: best normalized 0.3243, raw 0.0270, expected 296 bytes vs actual 180; dominant operand_or_scheduling_drift (best raw base/temps/etc 0.1757/0.0270, 296 vs 164), first-diff fingerprint instruction 1 expected addiu ,,423 but actual addiu ,,-640. Batch 2 attempted packed struct, packed raw fields, pragma-pack (compile_failed), halfword overlay, volatile, pointer-temporary, declaration-order, and explicit byte-copy forms: best normalized 0.2973, raw 0.0270, expected 296 vs actual 164; first diff instruction 1 expected addiu ,,423 but actual addiu ,,423. No link_verified=true results and no futility/register-tie signal. Next materially different action: define a true packed record overlay with named unaligned s32 members corresponding to offsets 0x10/0x0C/0x14/0x18 and assign those members (including copies) in assembly order, preserving the compiler's lwl/lwr/swl/swr generation; use exact D_82B085BC byte-array declaration. Do not repeat raw offset-cast or malformed in-body pragma forms.

## func_82B01BB8 diagnostic correction (2026-09-02)

Correction: first-diff fingerprints were expected addiu t7,$zero,423 vs actual addiu t8,$zero,-640 (batch 1), and expected addiu t7,$zero,423 vs actual addiu t6,$zero,423 (batch 2).

## func_82B01CE0 requeue after packed-state probes (2026-09-02) (2026-09-02)

requeue; func_82B01CE0 fresh owner received two runner-only batches of 8 distinct candidates each with host CC checks enabled. No source edit, link_verified result, ROM gate, or acceptance. Batch 1 attempted anonymous packed raw-word/struct overlays, raw offset s32/u32 overlays, explicit temporaries, declaration/lifetime ordering, typed state overlay, and indexed packed-word forms. Five packed variants compile_failed because IDO rejected anonymous/in-body packed struct expressions; raw:offsets:explicit-temporaries best normalized 0.2800/raw 0.0267, expected 300 bytes versus actual 164, mismatch_kind=operand_or_scheduling_drift, first-diff fingerprint instruction 1 expected addiu $t7,$zero,76 but actual addiu $t8,$zero,480. Batch 2 used the existing file-level struct PackedWord82B02924 to avoid anonymous types and varied direct/base-temp/order/typed-16/volatile/separate-state/base-pointer packed overlays, but all 8 compile_failed: IDO reports Reference of an expression of void type or an incomplete type at packed struct pointer assignment/dereference expressions. These are tooling/source-payload failures, not evidence against the packed shape. Next materially different action: use a file-level named packed record declaration already accepted by IDO (or exact runner-mediated companion declaration if permitted) and assign through its .value member / named local s32 temporaries, avoiding void* dereferences and anonymous structs; preserve the observed lwl/lwr/swl/swr sequence. Do not repeat anonymous in-body structs or casts that dereference void expressions.

## func_82B05F60 tooling-blocked 2026-09-02 (2026-09-02)

tooling-blocked; fresh owner func_82B05F60 (66 instructions, prior_attempts=0) received one valid 8-candidate batch prepared after file_brief.py, pragma_targets.py targets, analyze_family_shapes.py siblings, and exact assembly inspection. Candidates covered call_sequence families: raw/typed global pointer bases, while/for/do loops, explicit loop bounds, pointer post-increment, callee-result temporaries, and address-observable table locals; no dispatcher or jump-table forms. python3 -m json.tool validated the batch at /private/tmp/gs45_func_82B05F60_batch_validated.json. Required 120-second stagger timer was started, but its marker was not created; shell emitted zsh:1: nice(5) failed: operation not permitted despite no nice/renice wrapper. One runner launch was attempted with stdout/stderr redirected to /private/tmp/gs45_func_82B05F60.log and raw result /private/tmp/gs45_func_82B05F60.json; shell again emitted zsh:1: nice(5) failed: operation not permitted (PID 22087), log remained empty, and raw result was absent. No candidate score, mismatch_kind, first-diff fingerprint, size, futility, link state, source install, or ROM gate exists. Next action: repair/verify host launch policy and rerun the same or materially refreshed 8-candidate batch; do not infer source evidence from this launch failure.

## Coordinator replay after wave 45 (2026-09-02)

Directly replayed /private/tmp/gs45_func_82B05F60_batch_validated.json without the host nice wrapper. All eight candidates were probe_rejected; best normalized/raw similarity 0.7750/0.6750, expected 320 versus actual 288, stable operand_or_scheduling_drift at the stack frame (-40 expected, -56 actual). Requeue with a materially different frame/ABI hypothesis.

## 2026-09-09

func_82B062BC: plateau at 0.9375 (raw 0.875), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-09

func_82B07A5C: plateau at 0.9565 (raw 0.8696), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-09

func_82B010BC: plateau at 0.0 (raw None), mismatch unknown; tried families: call_sequence; tie-pool no

## 2026-09-09

func_82B07BEC: matched (call_sequence:switch:braced-cases-four-halfwords), 2 iterations, agent codex

## 2026-09-09

func_82B029B8: plateau at 0.9677 (raw 0.5161), mismatch operand_or_scheduling_drift; tried families: state_field_access; tie-pool no

## 2026-09-09

func_82B02EDC: plateau at 0.8205 (raw 0.1538), mismatch operand_or_scheduling_drift; tried families: state_field_access; tie-pool no

## 2026-09-09

func_82B02D84: matched (state_field_access:switch:limit-before-increment), 2 iterations, agent codex

## 2026-09-09

func_82B00E10: time cap at 0.9 (raw 0.4) after 2404s, mismatch operand_or_scheduling_drift; tried families: state_field_access; tie-pool no

## 2026-09-09

func_82B042D8: matched (call_sequence:gfx-macros:env-color-standard), 1 iterations, agent codex

## 2026-09-09

func_82B07E18: time cap at 0.9231 (raw 0.4396) after 2413s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-09

func_82B072DC: time cap at 0.9681 (raw 0.9468) after 2400s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no
