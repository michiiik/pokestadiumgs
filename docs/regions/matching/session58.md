# Session 58 failed investigations

Both rejected owners remain GLOBAL_ASM. Every valid trial used the full US build with default host syntax checks and COMPARE=1, followed by the explicit retail checksum. Sources, object dumps, build logs and failed MD5s remain under work/session-58. Only each failed owner and its newly introduced declaration or declaration placement were restored. All previously merged C and exact imported master changes remain present; restored builds pass retail 1561c75d11cedf356a8ddb1a4a5f9d5d. These notes remain draft and outside matching merge authorization.

## func_8AF1C574

Independent no-argument/no-result leaf, 31 words, no frame, padding, jump table or shared switch tail. Original func_8AF1C830 and func_8AF1CE2C calls supply no formals and ignore the result. Six existing void-pointer globals are read in the original order, and bit 2 is cleared in the unsigned halfword at offset 2 of each pointed object. Existing companion func_8AF1C5F0 sets the same bit in the same order; no global type or storage change was needed.

The first source recipe was:

```c
void func_8AF1C574(void) {
    *(u16 *)((u8 *)D_8AF37778 + 2) &= 0xFFFD;
    *(u16 *)((u8 *)D_8AF37784 + 2) &= 0xFFFD;
    *(u16 *)((u8 *)D_8AF3777C + 2) &= 0xFFFD;
    *(u16 *)((u8 *)D_8AF37788 + 2) &= 0xFFFD;
    *(u16 *)((u8 *)D_8AF37780 + 2) &= 0xFFFD;
    *(u16 *)((u8 *)D_8AF3778C + 2) &= 0xFFFD;
}
```

Full-ROM failure MD5: bca9f99d96cfdadccaa570a552c1ce98. IDO retains all 31 words, all six address relocations, all load/store ordering and the first 14 instructions exactly. Starting with the third pointed value, the candidate uses t0/t1, t2/t3, t4/t5 and t6/t7, while retail uses t1/t2, t3/t4, t5/t6 and t7/t8. The source matches the mask semantics but lacks the original temporary allocation. Need supported flag/temporary-value lifetime evidence; do not replay ordinary direct/typed/cast/mask/declaration/operand variants. No speculative register forcing or helper/storage/tool change is adopted.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact attempt, reference or fragment44_20A610 regional note for this owner; historical normalized/raw_similarity_score is unavailable. Earlier failed func_8AF1C3A0 coordinate lifetime and sibling family skips remain untouched. The owner and the existing declaration placement were restored narrowly from the freshly fetched current-master transaction, and the whole restored TU is verified against its expected blob. Evidence: candidate-c574.c, c574-object.txt, c574-build.log, c574-md5.txt, restored-c574-build.log and restored-c574-checksum.txt.

## func_8AF1F490

Independent 33-word word-result owner, 32-byte frame, no padding, jump table or shared tail. Original func_8AF1F5F0 passes a signed halfword load in a0 and an explicitly sign-extended value in a1, then branches on the word result. The owner stores both incoming words at their homes and makes an a0-to-a2 copy before narrowing for its first helper call. Canonical compiled func_8AF01654 is u8(u8); no false word return or helper ABI was used.

Unlike earlier failed func_8AF1F40C, this owner calls the helper twice, and the first result's two nibbles must survive the second call. The trial preserved that real lifetime:

```c
extern u8 func_8AF01654(u8);
s32 func_8AF1F490(s32 arg0, s32 arg1) {
    u8 var_a1;
    u8 var_v0;
    u8 var_a0;
    u8 var_a2;
    u8 var_v0_2;

    var_v0_2 = func_8AF01654(arg0);
    var_a1 = (var_v0_2 & 0xF0) >> 4;
    var_v0 = var_v0_2 & 0xF;
    var_v0_2 = func_8AF01654(arg1);
    var_a0 = (var_v0_2 & 0xF0) >> 4;
    var_a2 = var_v0_2 & 0xF;
    if ((var_a0 == var_a1) || (var_a2 == var_a1) ||
        (var_a0 == var_v0) || (var_a2 == var_v0)) {
        return 1;
    }
    return 0;
}
```

Full-ROM failure MD5: c9f2d078046a132f29e652a6438a63c9. IDO emits 31 rather than 33 words, retaining the 32-byte frame and both helper calls. The word-formal recipe omits the original first home and a0-to-a2 copy. The first nibble pair occupies stack bytes 31/30 rather than retail 30/29. Its first/second high-nibble values use a0/a1 instead of retail a1/a0, with corresponding comparison operand drift. Need supported actual first-formal home and nibble-result lifetime evidence. Do not replay ordinary word/narrow/scalar/array/declaration/operand/helper-prototype families; never use a false word-result func_8AF01654 or retry the failed func_8AF1F40C recipes.

Fleet main has no exact owner attempt, reference or fragment44_20D3A0 region entry for this owner. Historical normalized/raw_similarity_score is unavailable. The complete current-master region document, including accepted F378 and F514 recipes, was read and preserved. Only F490 and its newly introduced canonical helper declaration were restored; the exact fresh TU blob 8f992bdc3d0c0e4fe518d056ed46f010c1ab398e remains installed. Evidence: candidate-f490.c, f490-object.txt, f490-build.log, f490-md5.txt, restored-f490-build.log and restored-f490-checksum.txt.

## Resolved initial width failure

Accepted func_87F0E39C's first u16-local spelling failed with MD5 152857216cfc62bddeca272aa326d0b6: every other instruction matched, but it returned through a move instead of the original ANDI. The original return normalization and caller evidence support the accepted word-width result local with a u16 return. That source passes the whole retail ROM and is recorded in its narrow PR's accepted region note. Do not replay the first width recipe.

## Scope and process

Master's foreign fragment53/44 source, aliases, canonical YAML and coverage changes were imported exactly after their merges. Foreign #1048's entire scope was deferred until merge; it was never manually merged here. Own #1049 was kept draft until refreshed against that master and was accepted only after its actual successful checksum job and tested/actual parent/tree proof. No docs or unrelated PR was manually merged. No authored CI, tooling, compiler, linker, YAML, data or verification change occurred. The 28 older validation-gap records remain exactly unchanged; local checks are not retroactive proof.
