# Region notes: fragment14_1077C0

## 2026-10-14: func_8131109C remains GLOBAL_ASM

No match was accepted. The original func_81301548 and func_813018FC callers
both pass their real pointer at incoming object offset 0xF64C, retain the
word result across a subsequent call, and use it as a signed switch selector.
The callee reads only that pointer, returns -2 for either outer guard failure,
-1 when the word at offset 168 is zero, and the word at offset 72 otherwise.
It is a separately called owner; the callers' switch tails are not owners.
The retail boundary contains nineteen executable words and two trailing nops.

This ordinary nested spelling failed the full US ROM checksum:

```c
s32 func_8131109C(u8* arg0) {
    s32 var_v1 = -2;

    if (arg0[56] == 5) {
        if (arg0[58] >= 3) {
            if (*(s32*)(arg0 + 168) != 0) {
                return *(s32*)(arg0 + 72);
            }
            return -1;
        }
    }
    return var_v1;
}
#pragma C_FUNCTION_PADDING(8)
```

The compiled owner has eighteen executable words instead of nineteen.
IDO coalesces the default -2 into v0 instead of the required v1 followed by
a return move, and moves the -1 literal into the return delay slot rather
than before the inner word guard. The byte loads, comparisons and pointer
offsets otherwise follow the expected body. This is the known result/tail
allocation family. Do not repeat ordinary nested, ternary, result-phi or
declaration permutations without a materially new supported lifetime model.

The valid trial used default host syntax checks and COMPARE=1 against master
1b4e3e80a7dc471cecbe89311c25f86080ba1f81, excluding only the four other
freshly open matching PRs. All merged sources, including both #885 files and
current foreign resource-loading work, were preserved. Make failed the retail
comparison with MD5 d465fdd16c22474d6537387365d45b47. The baseline and all
canonical siblings were restored; a full rebuild and explicit
md5sum -c baseroms/us/checksum.md5 passed with retail MD5
1561c75d11cedf356a8ddb1a4a5f9d5d. Source, logs and object evidence remain in
work/session-46. No unverified trial is left in the working source.

An earlier host-only failure used C_FUNCTION_PADDING as a macro call instead
of the repository's pragma syntax. Host checking rejected it; its object
dump was still the assembly baseline and is explicitly not candidate evidence.
The invalid source and diagnostic log were retained separately. The corrected
pragma trial above is the only full-ROM failure for this owner.

History audit found no exact owner attempts, unrelated references or 1077C0
regional note at fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed, so no
historical raw similarity score is available. All open PR scopes were inspected
before source edits. Unknown names remain address/argument/register based.


## 2026-10-15: func_8130FF70 matched

The original func_813102A4 callers pass f12 and consume f0; the existing compiled func_8130FFE0 also declares the actual f32(f32) ABI. This is an independent 28-instruction leaf with no padding. Its four existing symbols D_81312988/8C/90/94 reside in the shared 10AA10 rodata block and contain single-precision 3.141592741, 6.283185482, -3.141592741 and 6.283185482 respectively. Retain those existing symbol references; no new pool, data, mapping or layout is needed.

The first two direct while loops using those globals failed full-ROM comparison with MD5 801eec6ec917735a54182b9233c8af7b. All 28 words and the first loop match; the second increment constant loads only inside the loop guard rather than unconditionally before its comparison, shifting the guard displacement. Capturing both existing second-loop threshold and increment in f32 locals before the loop reproduces the original unconditional loads and passes. The first-loop increment remains conditional as in retail. All arithmetic, strict first comparison and inclusive second comparison remain unchanged.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact/solved owner attempt, owner reference or 1077C0 regional file, so no historical normalized/raw scores exist. The earlier func_8131109C rejection above remains unchanged and was not retried. All open source PRs were this process's separate matching owners.

Based on master 224774092bdc686b39361e5308a59d6567d7ed75. Full US rebuild with default host syntax checks and COMPARE=1, then explicit md5sum -c baseroms/us/checksum.md5 passes retail 1561c75d11cedf356a8ddb1a4a5f9d5d. Source/object/build evidence for both variants remains in work/session-53. No new semantic names, tokens, fakes, helper edits or verification changes.
