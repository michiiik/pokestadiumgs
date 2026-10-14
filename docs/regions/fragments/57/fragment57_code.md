# Region notes: fragment57_code

## 2026-10-14: func_833084B0 remains unmatched

One US/default-host-syntax ROM failure. Actual no-argument state loop initializes result 1, forwards fade duration 10 through the existing implicit-forwarding StageFade_StartFromOpaque ABI, checks global word +8 against -1, calls real func_83303564(void), and feeds the word result through func_83307C7C(s32) until 14. Do not replace incoming fade duration with zero or try to match the known-dead-end fade owner. The ordinary cached byte-pointer form folds D_8330A288+8 into a direct relocation each iteration, eliminating the saved global base. It emits 32 versus 35 instructions with three rather than four saved registers; sentinel comparison operands and S1/S2 allocation differ. Need a supported global-base/call lifetime model; no ordinary cached/raw pointer, loop or declaration-order retry.

History audit: No exact owner attempt or fragment57 region catalog note at fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed.

All failed sources, full build logs, and object disassemblies are retained in
`work/session-44`; each fresh baseline was restored. Open PR scopes were
checked for duplicate owner work. No CI, verification, linker, or data changes
were made. These attempts are failures, not claimed matches. The restored
186-owner workspace passes the US retail checksum with default host syntax
checks. Unknown tokens retain their existing address/offset names.
