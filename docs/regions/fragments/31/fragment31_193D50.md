# Region notes — fragment31_193D50

## func_88220AD0 — session 60

The independent 44-word wrapper matches with its original 584-byte frame. Original caller func_8820908C passes two words (320, 240) and ignores the result; compiled callers pass either literals or signed halfwords, and the existing local declaration is void(s16, s16). The owner preserves both actual signed-halfword formals and their home loads after the buffer-formatting calls.

A real 512-byte local buffer is passed to canonical void *func_8004C8A0(void *, s32, s32, s32) with (buffer, 512, 31, 19). The preceding count is obtained from actual no-argument word-result func_88203FB4 and passed to actual s32(s32, s32) func_8004C594 with selector 4. The returned buffer pointer is forwarded directly to func_88903C50, preserving the original temporary lifetime and stack layout.

The full original func_88903C50 body was audited: its two coordinates are read as signed halfwords, color/mode fields as bytes, two pointer arguments are stored as pointer fields and used as word output pointers, and its final callback is saved before later use. The supplied func_88903B00 is compiled void(void); D_88000E4C is the original no-argument JR/NOP stub used as a callback. Keep the constructor's actual thirteen-argument declaration; do not fabricate incoming arguments or change the callback/helper implementations. The known failed func_88903B2C and skipped 88004804/88004990 families were inspected only as ABI evidence, never retried or modified.

No exact owner attempt, reference or owner-specific regional record was found at fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed, so there is no historical normalized/raw_similarity_score for this owner. Current master and all open PR scopes were inspected before editing. This first candidate passed the normal US build with host checks and COMPARE=1, followed by explicit md5sum -c baseroms/us/checksum.md5: OK, retail MD5 1561c75d11cedf356a8ddb1a4a5f9d5d.

No new semantic names, tokens marked known, artificial padding, fakes, data, layout, CI, compiler or verification changes were authored. The two new source/doc blobs are based on master 58cb58d58dc38711c4d3ec2517436161bd40639a. All earlier matches and failure notes remain intact.
