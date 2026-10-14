# Matching investigations, session 51

Accepted `func_885011EC` is documented in matching PR #956. Its Public PR ROM Gate executed the checksum build successfully for the final head; the tested merge parent and tree exactly match the actual repository-auto merge. This document preserves four failed investigations. All four source edits were restored and every restored full US build passed with default host syntax checks, `COMPARE=1` and the explicit retail checksum. No merged matching source was removed. Documentation stays outside the matching-PR merge authorization.

## func_8820B09C: retained assembly

The original no-argument `func_8820B6C8` caller saves the word result at stack offset 204. The canonical compiled `func_88201ED0` takes two actual bytes and returns a pointer. The trial retained the existing global pointer, captured it in a byte pointer, initialized a word result to zero, and applied the original word/halfword guards before the indexed word guard and two-byte lookup. The returned record's byte at offset 21 determines the result. No null guard, artificial argument or false helper prototype was added.

The candidate reproduced all 34 instructions, the 32-byte frame, control flow, calls and result register `a3`. The index was in `v0` rather than retail `a2`; the two indexed ADDU instructions used shift/base instead of base/shift; and the result spill/reload used stack offset 24 rather than 28. Full-ROM MD5: `002743443b55c1153632278968176b85`. A supported index/address and result-stack lifetime model is needed; do not replay ordinary raw/indexed address, operand, declaration, result or scratch variants. The complete first recipe, object and build log remain in the session archive.

No exact fleet owner attempt, owner reference or `31_17B150` regional record was found in the consulted catalog, and current master had no regional document. All open scopes were inspected before the trial; only session documentation drafts were open after foreign #955 merged.

## func_860065E8: retained assembly

Original `func_8600666C` branches on the word result, and compiled `func_86006774` uses the same word-address/word-result ABI. Original `func_87F01A40` takes no arguments and returns a word. Preserve that word on the default path; cases 3 and 4 update bits `0x20`, `0x80` and `0x10` of the byte at offset 30144, then return 1. The trial used the actual full-byte bitfield view, without zeroing an unhandled result or changing the existing caller declaration.

Every byte flag operation and temporary register matched, with the correct 24-byte frame. The candidate emitted 35 rather than 33 instructions: it copied the helper result from `v0` to `v1`, used `v1` for result 1, and added a final return move. The argument reload and first branch-delay schedule also differ. Full-ROM MD5: `84c48f4ae3be7ec81b92defdccf481f8`. A supported default-result and return-tail lifetime model is required; do not replay ordinary switch, bitfield, return, declaration or control variants.

No exact owner attempt or reference was found. Full fleet `47_24AE60` notes were consulted, including the unrelated `func_86006364` frame plateau at normalized/raw 0.9825/0.8772 and the other documented raw-score caps and skips; none was retried. Current master had no regional document. The separate then-open #956 implementation was excluded only for the independent trial and restored immediately; no merged source was removed.

## func_8AB02FE0: retained assembly

Original `func_8AB03394` supplies a real unsigned halfword selector, pointer to two-halfword rows, and unsigned halfword row index. The existing initializer clears the 16-byte pointer array and 1024-byte buffer. Canonical compiled `func_8004C8A0` returns a pointer and takes a buffer pointer plus three words. The trial preserved both selected halfword stores, repeated pointer loads and the original buffer helper call, using the actual row and field types without changing global declarations.

All 33 instructions, the 24-byte frame and all three argument homes were reproduced. The third argument's load/shift used `t1`/`t2` rather than retail `t9`/`t1`, the row ADDU used base/shift instead of shift/base, and the later buffer base used `t1` instead of `t9`. Full-ROM MD5: `1ce453d381cedf1a32fdd07ea54b49bc`. A supported narrow-index and address lifetime model is needed; do not repeat ordinary typed-row, raw/indexed address, operand, declaration or prototype variants.

No exact owner attempt or reference was found, and current master had no regional document. Full `45_2251A0` fleet notes were read: `func_8AB02240` normalized/raw 0.8696/0.7101, `func_8AB0234C` 1.0/0.85, `func_8AB01140` 0.9878/0.5488 and `func_8AB00FF8` 0.8537/0.4268 families remain untouched. Merged #956 remained present.

## func_8300AEEC: retained assembly

Original `func_830096B8` supplies buffers at offsets `0x3A290` and `0x3BDF4`, separated by 7012 bytes, with actual word arguments 0/1 and the selected word/0. The genuine `_bzero` clears the entire 7012-byte record. Unlike the earlier branch-first `func_8300B330` attempt, this owner's first byte-2 flag write precedes the selector branch. That measured order was the basis for one fresh flag-first recipe; the branch-first sibling family was not replayed.

The trial's unknown full-record bitfield view reproduced all 31 instructions, the 24-byte frame, masks, shifts, stores and branches. Only the two literal initialization positions differ: retail initializes 3 in `t3` before the first byte load and 6 in `t2` later; the candidate initializes 6 first and 3 later. Full-ROM MD5: `27e7d9b10f9503f28b2f8ded9bb7db77`. The flag-first lifetime hypothesis did not solve the literal schedule. A supported literal/control lifetime model is needed; no ordinary bitfield, if/ternary, source-order, declaration or operand repeats. `func_8300AA58` remains deferred as the known branch-first sibling family.

No exact owner attempt, owner reference or `7_C4C10` fleet regional record was found, and current master had no regional document. Foreign open #957 covered fragment 76 and was deferred. All failed edits were restored; the current master after foreign #957 also passes the full retail checksum.

## Read-only handoffs

`func_81803720` needs a consistent real pointer/pointer/float/word ABI across `func_81803558`, the compiled wrapper `func_818036D8` and its two compiled callers. Existing word-bit spellings and an implicit no-argument call to the real two-pointer float helper complicate that chain. No invented argument or false word prototype was tried. Retain the unrelated `func_81803558` normalized/raw 0.9265/0.7794 prerequisite and `func_818021B4` 0.8095/0.7619 guard plateau.

`func_861049C0` has an extra trailing JR/NOP boundary; it was inspected without a padding assumption or trial. The larger `func_8820B124` is a real switch owner whose jump-table prerequisite remains; interior tails were not treated as functions. Current master foreign fragment 76 notes preserve `func_8F700538` 0.8571/raw 0.5714 and later raw 0.6190, and `func_8F700420` 0.9714/raw 0.9286; their ordinary families were not retried.
