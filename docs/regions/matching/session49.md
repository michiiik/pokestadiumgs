# Matching investigations, session 49

Accepted recipes are documented separately in matching PRs #934 (`func_83F0012C`) and #938 (`func_87C02488`). This document retains three failed investigations. All failed source edits were restored, every restored full US build passed with default host syntax checks and `COMPARE=1`, and the explicit retail checksum passed. No merged matching source was removed.

## func_8300B330: retained assembly

The actual `func_830096B8` caller supplies two buffers separated by 4356 bytes, a real word selector 0 or 1, and a real second word. The owner clears that full buffer through the existing `_bzero`, sets byte zero to 8 or 1, writes bit `0x80` and the two bits `0x60` in byte 2, and has no consumed result. The unknown bitfield record described the actual 4356-byte footprint; it added no arbitrary formals or padding.

The first bitfield/if recipe reproduced all 30 instructions, the 24-byte frame and all byte masks/stores. Only the two literal initializations differ: retail initializes `t7=1` before the branch and places `t6=8` in its delay; the candidate initializes `t6=8` first and puts `t7=1` in the delay. Full-ROM MD5: `94dc3f49bc8d0f5902a5096d239aa66f`. This needs a supported literal/control lifetime model; do not replay ordinary bitfield, if/ternary, declaration or operand forms.

No exact fleet owner attempt or owner-specific `7_C4C10` regional record was found in the consulted catalog. Current master had no regional document. All open scopes were checked before the trial; only documentation drafts #922 and #932 were open.

## func_8130EA8C: retained assembly

Original `func_8130EB04` supplies two actual record pointers and ignores the result. The owner compares the incoming pointer and its word at offset 88 against saved fields at offsets 108 and 36. When either differs, it updates the saved pointer/word, byte 57, and state words, while forwarding the real address at offset 60 and the incoming byte zero to `func_81601D24`. The compiled helper definition takes two words, so both stale four-formal declarations in the candidate TU were corrected consistently for the trial. No null guard or invented arguments were added.

The first pointer/word OR-guard recipe emitted 29 rather than 30 instructions. It uses a regular BNE with the constant initialization in its delay and one shared pointer store; retail uses branch-likely with the pointer store in its delay plus the duplicate store on the other path. The constant/load scheduling then differs. Full-ROM MD5: `eeb0bbc37aebc63871394e6ce5ed6e53`. A supported guard/store lifetime model is required; do not replay ordinary OR/nested guards, pointer aliases, declarations or operand forms. Both declaration corrections and the owner were restored.

No exact owner attempt or `14_104FC0` regional record was found in the consulted fleet history, and current master had no regional document. All open scopes were checked before the trial.

## func_8AF0F1A0: retained assembly

The real callback registered by `func_8AF0F2EC` through `func_8004E308` has a mode word and node pointer, with no result consumed. Registration supplies mode 0 and a word index stored at node offset 32; the owner reads its signed low halfword at offset 34. Mode 1 updates a three-halfword table row. The canonical `func_800504BC(s16*)` writes exactly two coordinate halfwords, so the trial used a genuine two-element pair and the live signed index, without a padded third coordinate or invented callback result.

The switch/pair/index recipe reproduced all 32 instructions, the 40-byte frame, index at stack offset 38, pair at 32/34, and the first 20 instructions exactly. The stack and object coordinate values are assigned opposite temporary registers for both additions, so the body still differs. Full-ROM MD5: `332654e92fc0effec8af2d97645533cc`. This needs a supported coordinate/value lifetime model; do not repeat ordinary pair/scalar, padding, declaration or operand variants. Compiler pointer warnings belonged to existing `func_8AF0EFF0` and `func_8AF129F8`, not the trial owner.

No exact owner attempt was found. The full `44_1FD260` fleet notes were consulted; unrelated exhausted owners, including `func_8AF133C0` (best normalized/raw 0.9674/0.4651 and exact-size 0.9533/0.4766), were not retried. All open PR scopes were checked; merged #934 was preserved throughout.

## Historical screens without trials

Defer `func_8005BFA8`: its exact record has normalized/raw 0.8889/0.8889 instruction drift, while the regional time cap records 0.8889/0.7222 after 1209 seconds. Defer `func_841121CC`: the regional wrapper time cap is 0.9474/0.9474 after 2401 seconds. Defer `func_81306178`: the regional explicit skip records 21 attempts, 0.9643/0.8929 instruction drift. No ordinary retries were made.

This documentation changes no source or verification and remains outside the matching-PR merge authorization.
