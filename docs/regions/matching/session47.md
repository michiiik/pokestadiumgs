# Matching investigations, 2026-10-14, batch 47

These owners remain GLOBAL_ASM. Each trial below ran a full US build with the default host syntax checks and retail comparison. Failed sources, object dumps and build logs are retained in `work/session-47`; the workspace was restored and the retail checksum passed after each investigation. No failed recipe is presented as a match. No exact owner attempt or regional recipe was available in fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` for these owners, so no historical normalized or raw score is available. Unrelated caller references were not treated as owner attempts. All open PR scopes were audited before each trial.

## func_81804B74, fragment4_B2D00

The actual two-pointer word-result leaf is separately called by original `func_81804BC8` and compiled `func_818055E0`. Both incoming pointers are real. The body reads signed words at offset 24, returns zero for equal nonnegative values or either sentinel -2, and otherwise returns one. It has 21 instructions, no frame and no padding.

The positive-guard recipe used a captured first word, repeated second-word reads, an early zero return, and a signed sentinel temporary. It reproduced all 21 instructions except two comparison operand ties: retail compares `v1, v0` in the branch at offset 24 and the branch at offset 44; the candidate compares `v0, v1`. Full-ROM MD5 was `524ff6f0c99edb4f424260d84553cf3f`.

Retain this as a comparison-allocation blocker. Do not repeat ordinary positive guards, operand reversal, sentinel/declaration permutations or result variants without new supported lifetime evidence. The fresh baseline preserved all previously merged fragment 4 matches.

## func_8290E2A8, fragment67_34AB40

This no-argument initializer is called by compiled `func_8290ADD0` and `func_8290AE3C`. Original `func_8290E2FC` and `func_8290E438` index the real signed-halfword arrays `D_8291BC00`, `D_8291BC04`, `D_8291BC10` and float array `D_8291BC08`. Retail initializes both halfword elements to 10, 1 and 14, and both float elements to zero, with 21 instructions and no frame or padding.

A counted two-element loop over these four typed arrays retained a loop instead of reproducing the retail unroll. It emitted 25 instructions, an additional end pointer and pointer increments, with different base/constant allocation. Full-ROM MD5 was `c09d27b632cf0692a05b811193779d32`.

The array interpretation is supported; the counted-loop spelling is rejected. Seek new evidence for the original unroll or initialization phases. Do not repeat ordinary counted-loop, pointer-loop or declaration variants. No global data, qualifiers, linker configuration or compiler tools were changed.

## func_800088DC, 8470

This real no-argument wrapper reads the existing word-handle `D_800D0554`, checks it for null, uses its signed byte at offset 22 to select a descriptor pointer at offset 24 plus four times the index, and calls the actual `func_80007328(Gfx**, void*)`. The helper reads the descriptor and updates the display-list pointer. The wrapper then emits the standard `gDPSetCycleType` command for `G_CYC_1CYCLE`. Its compiled no-argument callers ignore any result.

The captured pointer and standard graphics macro recipe reproduced all 26 instructions except the indexed-address addition: retail emits `addu t8, v0, t7`, while the candidate emits `addu t8, t7, v0`. Full-ROM MD5 was `a7ab4eb649d83b31df9996d7c71deee5`.

Retain this as an address-allocation blocker. Do not repeat ordinary raw-pointer arithmetic, operand reversal or typed aliases without new supported object-lifetime evidence. The independent trial excluded only then-open #920; its verified source was restored afterward. Merged #915 remained present throughout. Existing global types, helper behavior and graphics macros were preserved.

## Additional screening

Current master notes record `func_800279C4` at normalized 0.8462/raw 0.5 with call-sequence scheduling drift; it was not retried. `func_81307228` and `func_82202628` are true switch owners whose tables were not defined in their owner ASM; unresolved rodata ownership prevented a trial. Their interior returns were not treated as separate functions. `func_8821B3E0` and `func_87F0E660` were inspected only: the former retains global/coalescing prerequisites, and the latter needs evidence for its empty counted loops before any source model can preserve them. No speculative memory operations or volatile qualifiers were introduced.
