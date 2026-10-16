# Fragment 30 16D4F0 matching notes

## func_881000B8

Accepted recipe: view the existing byte pointer `D_88104E80` through `unk_func_881000B8` with signed halfwords at offsets 0 and 2 and bytes at 4, 5 and 6. If the first halfword is 3 and the second is 0, copy byte 6 to byte 5 and clear byte 6. Otherwise, if those halfwords are 3 and 1, clear byte 6; all other paths clear byte 4. Finally call the existing `func_8810009C(3, 2)`. Preserve the original global declaration, unknown names, repeated guards and real byte-pointer reload after the first store. The typed field view describes actual accesses and introduces no fake, arbitrary argument or semantic rename.

The compiled caller in `fragment30_170430.c` already declares this owner as `void(void)`, and original `func_88103A64` supplies no arguments or consumed result. The canonical compiled `func_8810009C` takes two real words and stores their halfwords. The owner has 33 instructions and a 24-byte frame, no trailing padding, jump table or shared switch tail. All original branch paths and byte-write ordering are retained.

History audit: live fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt, owner reference or `30_16D4F0` regional document in the consulted catalog. No normalized or raw similarity score is available. Current master has no regional document at this path. All open PR scopes were inspected: process PR #949 covers the separate rectangle owner, and drafts #922, #932 and #940 cover only session documentation.

Independent validation against master `09ed36b421c6d4217ed030f1e29e4313381ce198`: the first typed-guard recipe passed the full US `make rom COMPARE=1 -j2` with default host syntax checks. The separate unmerged #949 implementation was excluded for that independent build and restored immediately afterward. Its independent MD5 and the combined build both equal retail `1561c75d11cedf356a8ddb1a4a5f9d5d`; `md5sum -c baseroms/us/checksum.md5` passed after the combined build. All 202 already merged process owners, including strictly verified #947, and current foreign master matches remain present. No CI, verification, compiler or layout changes are authored. The Public PR ROM Gate must actually run its checksum build for the current head and merge result before merging; skipped draft checks do not count.

Current-master integration: after #949 was strictly verified as merged at `0b954039fd0a8d23c50204394bae8fd574ac1e0b`, the unchanged typed-guard owner passed the full US build and explicit retail checksum again with all 203 merged process owners present. The draft branch was refreshed onto that master before ready validation.

## func_8810106C -- accepted 2026-10-16

The original func_8810179C caller provides eleven consumed arguments: two resource pointers, two signed-halfword coordinates, four primitive-color bytes, and three environment-color bytes. The owner uses the canonical pointer contracts and word results of func_8004D1FC and func_8004D27C, ignores their results, and preserves the actual nine-argument func_80044270 contract. The two resource dimension halfwords are loaded signed at offsets 0 and 2 exactly as in retail. The drawing call retains both -16 coordinates, both 1024 steps, and G_CYC_2CYCLE.

The pipe synchronization and both color writes use standard SDK macros. No semantic token rename, unused formal, aggregate shim, extra local, padding, or false helper ABI is needed. The first candidate reproduces all 70 executable words, the 48-byte frame and all incoming byte/halfword homes. The previously merged func_881000B8 and all neighboring C remain present.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact owner attempt or owner-specific regional note. The complete current region document was read; its existing accepted recipe is unrelated and was not replayed. Actual helper definitions and all three original call sites establish the ABI rather than unrelated draft declarations.

US COMPARE=1 passes with host syntax checks enabled. md5sum -c baseroms/us/checksum.md5 returns OK, ROM MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. A current-head remote Build and tested/actual merge-tree audit is still required; local acceptance alone is not remote provenance.
