# Region notes — fragment63_308D70

## func_87E06D8C — session 60

The independent initialization wrapper matches all 47 words, its original 32-byte frame and all fourteen calls. The original func_87E08EF0 caller passes its object+1176 and a second pointer-bearing word from object+32. The existing compiled func_87E0027C caller and its declaration agree with void(u8 *, s32); retain that second word handle and cast only at the signed-byte read at offset 8579. No incoming arguments or return values are invented.

Canonical src/3280.c establishes s32 main_pool_push_state(s32). Its original tag is written as decimal 1296516947. Preserve the second word at owner offset 368, sign-extended byte at offset 8, zero words at offsets 4 and 0, and the byte mask clearing bit 0x80 at offset 396. The ordinary full-width complement preserves the original ANDI and byte store.

The two no-argument helpers are established by compiled func_87F0BD10(void) and the original func_80041E2C assembly, which constructs all arguments internally. The existing pointer-formal empty func_87E06D84 remains unchanged. The local compiled helpers retain their actual pointer/word contracts, with explicit pointer-to-word casts where their existing definitions use word handles. The original func_87E069A4 and func_87E06BCC bodies consume one pointer each. All eight pointer-bearing calls and final three word-argument setters retain the original call order. No skipped helper is retried or modified.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact owner attempt or owner reference. The full 308D70 regional note was read: unrelated func_87E07278 remains at normalized .9697/raw .8485; the func_87E06BCC 0/raw None record is not an owner attempt or evidence for retrying that helper. Existing accepted sibling recipes and previous process/user skips remain intact.

The first candidate passed the normal US build with host checks and COMPARE=1 after exact upstream imports through master 95fe6846ebcb9a1116be0f16f92705cfaaf1f27b, including its narrow fragment-44 rodata split. Explicit md5sum -c baseroms/us/checksum.md5 reported OK, MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. All previously merged sources, including #1060/#1061/#1062, remain present. No new semantic names, tokens marked known, fakes, padding, helper implementations, data, layout, compiler, CI or verification changes were authored.
