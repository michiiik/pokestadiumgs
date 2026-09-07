# Region notes -- disasm/src/fragments/12/fragment12_E7C00.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Box 2026-08-29 (2026-08-29)

No owners accepted in this box. Probed only this file through the MCP runner. func_81402930: best prior/current spelling init-sequence:s32-params-goto and new limit variants reached similarity 0.9444/raw 0.9444, instruction_drift at setup order (expected li a1,128 before offset/pointer; candidate emits it after); deferred, no gate. func_81404DE4: constant-map switch reached 0.9091/raw 0.8788, operand_or_scheduling_drift from missing sw a0,0(sp) and duplicate_jr_nop_tail; deferred, no gate. func_81403938: reset-table variants reached 0.7857/raw 0.2143 with expected -0x28 frame versus candidate -0x20; deferred. func_814029AC: ANSI f32 body with paired prototype produced owner bytes similarity 1.0 but section_layout_drift because the paired prototype changed the later caller; s32 bit-reinterpretation reached 0.9574/raw 0.9149 with a 4-byte extra stack store; deferred. func_81404724: integer divisor /16 variants reached 0.75/raw 0.475 with float constant scheduling drift; deferred. func_814047C0: integer divisor /16 reached normalized similarity 1.0/raw 0.7872, register_allocation_only; stop/defer. func_814071C4: status-loop variants reached normalized similarity 1.0/raw 0.8919, immediate_drift because s2/s3 hold 4 and 0x4D68 in the opposite roles; deferred. No full gate was run because no isolated probe produced an exact link-verified candidate. User skip list remains active, including all dispatcher_switch/jump_table_map owners.

## Box 2026-08-29 follow-up (2026-08-29)

Follow-up box: four owners accepted after 71 recorded candidate attempts (67 probe-only variants plus 4 single-candidate gates). Accepted exact spellings: func_81407258 via result-nonzero-else (direct indexed 4-iteration loop; explicit nonzero/else result), func_81406EA8 via indexed-for, func_81407118 via indexed-for, and func_814053E4 via first-second (s16 first[4] then second[4]; array order is required for the stack shape). Every accepted attempt was link_verified:true/link=yes and passed the full COMPARE=1 ROM gate; ROM MD5 was 1561c75d11cedf356a8ddb1a4a5f9d5d and build/pokestadiumgs-us.z64 reported OK. Deferred func_81402930 after 15 new variants: best 0.9444 similarity/raw with instruction_drift at first_diff offset 4, expected li a1,128 before the pointer setup but IDO schedules it after; repeated-drift fingerprint persisted. Deferred func_81403758: inherited caller $a0/no-argument forward-prototype issue; typed forms compile-failed against the existing call and K&R forms retained frame/instruction drift, so no link-verified candidate. The user-supplied stuck/register-layout skip list remains active. Dispatcher_switch/jump_table_map and gbi-macro families were not attempted because this file still lacks the required .rodata subsegment; no SDK macros are present. Current file brief totals: solved=25, remaining=45, total=70.

## func_814029AC: stored f32-parameter candidate conflicts with an existing K&R caller (2026-09-06) (2026-09-06)

Flagged as section_layout_drift 'new_occurrence' (jump_table_status: not_applicable, correct -- no jump table, just a float init loop calling func_81402930/func_81402978). The fleet's stored 1.0-raw candidates ('init-sequence:kr-loop:ansi-paired-v1/v2') declare 'void func_814029AC(void *arg0, f32 arg1)', which matches the function's OWN instruction sequence (mtc1 straight from , matching a bit-reinterpret-not-convert float arg) but conflicts with the pre-existing 'extern void func_814029AC();' in this same file at the func_81403894 call site (already-decompiled, matched), which passes the float's raw bit pattern (0x41B00000) as a plain integer literal through the K&R unspecified-args convention. Giving func_814029AC a real f32 prototype makes the compiler see a genuine prototype conflict (clang: 'conflicting types'); worse, if the conflict were silenced, the compiler would apply an actual int-to-float VALUE conversion at the func_81403894 call site instead of preserving the bit pattern, changing that already-matched function's generated code. The real fix needs func_814029AC to accept its float argument as a raw s32/u32 and bit-reinterpret it internally (matching the mtc1 semantics) rather than declaring f32 directly -- not simply replaying the stored candidate. Left as GLOBAL_ASM.

## Accepted owner: func_81404DA0 (register tie closed) (2026-09-06)

Closed a register_allocation_only tie (25 prior rejected attempts sharing one first-diff fingerprint, no permuter attempt on record). tools/permute_candidate.py found a score-0 variant: swapping the declaration-order-adjacent 'result = 0;' assignment to come before the 'limit = ...' load instead of after, changing which register IDO assigns to each. Verified with tools/fleet_probe.py --gate: accepted, link-verified, full-ROM COMPARE=1 gate MD5 1561c75d11cedf356a8ddb1a4a5f9d5d.

## 2026-09-08

func_81404700: plateau at 0.0 (raw None), mismatch unknown; tried families: (none); tie-pool no

## 2026-09-08

func_81404700: plateau at 0.8889 (raw 0.6667), mismatch operand_or_scheduling_drift; tried families: constant-map; tie-pool no

## 2026-09-08

func_814038D4: matched (constant-map:scan:indexed-pointer-array), 2 iterations, agent codex

## 2026-09-08

func_81404D00: plateau at 0.7059 (raw 0.1765), mismatch operand_or_scheduling_drift; tried families: constant-map; tie-pool no

## 2026-09-08

func_81402930: matched (init-sequence:goto:limit-first), 4 iterations, agent codex

## 2026-09-08

func_81403710: plateau at 0.85 (raw 0.5), mismatch operand_or_scheduling_drift; tried families: constant-map; tie-pool no
