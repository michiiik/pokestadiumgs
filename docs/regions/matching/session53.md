# Session 53 failed investigations

## func_86C00148: saved-register and comparison lifetime

The real original func_86C001CC caller supplies no arguments and ignores the result. The independent 33-instruction owner calls the canonical void(s32) func_800086A4 with 2, actual s32(s32) StageFade_StartFromOpaque with duration 5, and actual void(void) func_80064D28. It advances the word result of func_86C000B4 and calls the existing void(void) func_86C00070 until the result is 3. The global signed word at D_86C00350 + 8 determines whether to read inputs.

The fade-duration forwarding prerequisite from the earlier inspection is resolved by current master's explicit canonical fade wrappers. No speculative argument, false helper prototype or padding was used. Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact or solved owner attempt, owner reference, or fragment 62 regional note, so historical normalized and raw similarity scores are unavailable. All open scopes were inspected; the only source PR was this process's independent func_86C000B4.

This one ordinary trial failed full-ROM comparison with MD5 e7821e9daa57574f2a97c33c2f1e0f69:

```c
void func_86C00148(void) {
    s32 var_s0 = 0;

    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    do {
        if (*(s32*)(D_86C00350 + 8) == -1) {
            func_80064D28();
        }
        var_s0 = func_86C000B4(var_s0);
        func_86C00070();
    } while (var_s0 != 3);
}
```

All 33 words, frame 40, prologue, calls, loop and return topology are reproduced. The global base uses s2 instead of retail s1, and the sentinel uses s1 instead of s2. The inner BNE compares sentinel/value instead of retail value/sentinel. This is a value-allocation/comparison residual, not an ABI or shared-tail problem. Require supported global/sentinel comparison lifetime evidence before another trial; do not repeat ordinary do/while, scalar/pointer, declaration, operand or helper-prototype permutations.

The owner alone was restored while preserving the accepted func_86C000B4 source; default host syntax checks, COMPARE=1 and explicit md5sum -c baseroms/us/checksum.md5 then passed retail 1561c75d11cedf356a8ddb1a4a5f9d5d. Full trial source, object, ABI notes and build logs remain in work/session-53. No failed game-source edits remain.

## func_8130F630: predicate/control-merge lifetime

The original func_8130F6A4 passes a real pointer and branches on the returned word. The owner normalizes word offset 68 equal to zero and, when true, byte offset 56 equal to 1. Otherwise it normalizes word offset 72 unequal to -1, 4 and 5, then byte offset 56 at least 4. No unrelated region, shared switch tail, padding or additional formal is involved. There is no exact/solved owner attempt or reference in fleet main, and no fleet 1077C0 regional file; historical normalized/raw scores are unavailable. The full current-master 1077C0 note for the earlier failed func_8131109C was read and that owner was not retried.

One explicit phased s32 result trial failed full-ROM comparison with MD5 220ffad24fd28115194cbcf3d89e7fa5. It retains all 27 instructions, no frame, all normalization operations and the final result move, but emits an initial regular BEQ/nop rather than retail BEQL with the word-72 load in the delay slot and duplicated alternate load. Its add-one temporary uses a1 rather than v1; two intermediate zero-result guards branch to the next phase instead of retail's shared return. The source used sequential if assignments for each normalization; no scalar or ordinary predicate variant is a verified match.

Require supported predicate/control-merge lifetime evidence before retrying. Do not repeat ordinary phased/grouped/nested/ternary result, declaration or operand forms. The owner alone was restored, preserving accepted func_8130FF70 and merged #1010/#1011; the full default-host-check build and explicit retail checksum pass. Full source/object/build evidence is retained under work/session-53.

## Screened without trials

- func_87F0C930 is already C on current master; no duplicate work.
- func_86000C6C has exact normalized 1 / raw 0.875 register-only history; no new allocation evidence.
- func_8AF12E30 has exact and regional normalized 0.8421 / raw 0.6842 operand drift and an extra JR/NOP boundary.
- func_82B02800 has normalized 0.8421 / raw 0.5789 lookup drift.
- func_88508B98 has exact normalized 1 / raw 0.7619, an explicit regional tie skip, and a later normalized 0.9524 / raw 0.2857 plateau.
- func_8003C2D8 was inspected only; its regional entry is normalized 0 / raw null with no tried family.

The accepted func_80019670 and func_8130FF70 recipes and their resolved first trials are recorded in their separate narrow matching PR region notes. All earlier user/process/raw/regional skips remain in force. No authored tooling, layout, data, CI or verification changes.
