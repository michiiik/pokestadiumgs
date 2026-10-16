# Region notes — fragment31_19DCA0

## func_8822AB28 — session 60

The independent no-argument draw callback matches all 48 words and its original 32-byte frame. The original func_8822ABE8 registers its address in the callback slot passed to func_88004804. The no-argument callback family and dispatcher were audited in earlier recorded constructor work; this owner consumes no incoming argument and no argument is invented here.

Use gSPDisplayList(D_800D0510++, D_80094DE0) and the actual void(s16, s16, s16) func_880008B0 with (178, 179, 204). The text setup/cleanup helpers func_800498C4 and func_800499EC have canonical void(void) definitions. func_800496A4 is void(s32, s32), func_8004C874 returns a pointer from two word arguments, and func_80048E30 is s32(u8 *, s32, s32, const char *, s32). Keep the first lookup nested in the first draw call to preserve the real returned-pointer lifetime.

The existing D_882348E0 word handle stays unchanged. Its second string is at byte offset 4, so the local owner casts that address to const char * and advances by 4. No global retyping, helper implementation, source callback, font data, or display-list allocation is changed. The two text calls retain their original positions, strings and draw flag 1.

No exact owner attempt, reference or owner-specific regional record was found at fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed, so no historical normalized/raw_similarity_score exists. The first candidate passed the normal US host checks and COMPARE=1 build, followed by explicit md5sum -c baseroms/us/checksum.md5: OK, retail MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. Both earlier session-60 sources were retained; they are now independently gated and merged as #1060 and #1061.

No new semantic names, tokens marked known, fakes, artificial padding, helper implementations, data, layout, compiler, CI or verification changes were authored. The new source/doc blobs are based on master 30f31883a22329f303123cfa182b7c887057cd2e. All earlier matching sources and rejected-owner evidence remain intact.

## func_8822ABE8 — 2026-10-17; fragment 31_19DCA0 complete

The constructor `func_8822ABE8` matches all 84 words and its original 0x50 frame size. ROM gate passes retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
With this function, `fragment31_19DCA0.c` has 0 remaining `GLOBAL_ASM` pragmas.

Allocates 0x208 bytes via `Util_Malloc` into `D_882348E0`, sets up callbacks (`D_88000E4C`, `func_8822AB28`, `func_8822AA20`, `func_8822AA50`) into `func_88004804`, indexes the returned value into `D_8800ED50` using the 0x4C stride, updates `*D_882348E0` header fields at 0x10, 0x12, and 0x2C, invokes string/icon initialization via `func_8004C54C`, `func_800635E0`, and `func_8004C8A0`, clears `D_880068B4`, and writes 3 to byte `D_88234746`.

