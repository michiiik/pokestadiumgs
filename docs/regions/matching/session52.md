# Matching investigations, session 52

Accepted `func_87E005C0` is documented in matching PR #1000. Its current-head Public PR ROM Gate ran the checksum build successfully; the tested merge and actual repository-auto merge have identical trees and the same master parent. This separate document retains four failed investigations. Every failed source was restored and the full US build with default host syntax checks, `COMPARE=1` and the explicit retail checksum returned to `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 206 merged process owners remain present. Documentation is outside the matching-PR merge authorization.

## func_8AF1F40C: retained assembly

Original `func_8AF1F5F0` supplies a packed byte and a signed halfword, then branches on the word result. Canonical compiled `func_8AF01654(u8)` returns a byte. The owner compares both input nibbles with both returned nibbles. It has 33 instructions and a 32-byte frame. The first byte-formal recipe used four genuine byte nibble locals and the true byte helper. The caller's LBU does not establish the owner's source formal width; the original word home also supports a word-formal interpretation, so that was checked separately without inventing an argument or changing the helper.

Both recipes defer input-nibble calculations until after the helper, eliminate the two original byte spills and emit 31 instructions with a 24-byte frame. The byte form reloads the incoming byte; the word form reloads the incoming word. Full-ROM MD5s: `680b7a95fb61f4637068712ac614c624` and `2561f1f038848ec5a906199d90eefd12`. A supported nibble-value lifetime model is required. Do not replay ordinary scalar, pair/array, declaration, formal-width or operand variants. No exact fleet attempt, owner reference or 20D3A0 regional record was found. Current master's accepted `func_8AF1F378` note was read and preserved.

## func_84153780: retained assembly

Original `func_84153E28` forwards its real pointer and live byte selector and ignores the result. Canonical compiled `func_8414A2AC(void)` and `func_84153718(u8)` return bytes. The recipe clears the selected byte to 255, captures the first byte result, obtains the second result, adds `(second << 7) * first` to the original selected word and sets flag `0x2`. No helper prototype or caller behavior was changed.

The candidate has all 31 instructions and the 40-byte frame, but caches the index across calls at stack offset 24, puts the byte at 39 rather than 30, and folds the required base-plus-four address into word offset 56 and byte offset 4. Retail materializes the base and uses offsets 52 and 0. Initial index and subsequent temporary allocation also differ. Full-ROM MD5: `361d15b232fc171ebb8cbb4b4f3adb0d`. Seek supported index/base-subobject lifetime evidence; no ordinary scalar, pointer, declaration or operand repeats.

No exact fleet owner attempt or reference was found. Full fleet and current-master 3BF4C0 notes were read, including the unrelated 50268 normalized/raw 0.9615/0.8462, 502D0 0.9583/0.9583, 524B4 0.9667/0.5, 52D6C 0.9512/0.9512 and 51270 1.0/0.9787 plateaus. Those owners were not retried.

## func_8001C6C8: retained assembly

Original `func_8001CF5C` supplies a pointer and ignores the result. Compiled `func_8001C744` forwards its actual pointer-valued word field; the trial consistently typed that call and declaration. Canonical compiled `func_8001A994(void*)` and `func_8001A9B4(void*)` dispatch modes 6 and 7. The unknown typed view preserves the offset-96 pointer, offset-80 nested pointer, genuine word bit 30, sentinel pointer guard and the two separate byte flag writes. No new fake or arbitrary formal was introduced.

All 31 instructions, the 24-byte frame, control flow and word-bit extraction match in shape. The sentinel BEQ uses `v0,t6` rather than retail `t6,v0`; the final byte ANDI uses `t3` rather than `t4`, and OR uses `t4` rather than `t5`. Full-ROM MD5: `bddb3e73d308fb57cd18d6d930e21f98`. A supported comparison/byte-value lifetime model is needed; no ordinary typed guard, mask, bitfield, declaration, operand or prototype repeats. Both caller edits were restored.

No exact fleet owner attempt or reference was found. The full 1CDC0 notes and current-master failed CDE4 note were read; the F9B0 terminal and accepted DE58 normalized 1/raw None history were retained. This was not a retry of CDE4.

## func_8420138C: retained assembly

Compiled `func_84201620` forwards its actual pointer. Original `func_84200038` takes a pointer and byte selector and returns a word predicate; canonical `src/641E0.c` establishes both color helpers as `u8(u8)`. Original `func_800632CC` takes the word pointer, three bytes and a word, and returns a byte. The trial preserves the conditional signed-word update, two byte-result calls and final helper invocation. The previously failed helper itself was not modified.

The scalar recipe reproduces all 31 instructions and the 48-byte frame except the first byte's spill/reload offset: 47 rather than retail 46. A genuine two-byte result array instead emits 32 instructions, places its bytes at 44/45 and adds a second SB. Full-ROM MD5s: `a408f36c167c7d2c021c3249c19494dd` and `1c7ebfcdd8fd5ecdd9d0e63a83b040f2`. A supported byte-result/home lifetime model is needed; no ordinary scalar, pair/array, padding, declaration or prototype repeats. Do not force false word-return helper types to remove byte operations.

No exact fleet owner attempt or reference was found. The complete 80_41A5F0 notes were read; unrelated 01728 normalized/raw 0.8621/0.4483 remains deferred. Existing accepted 01620/016BC source and notes were preserved, including merged #1000 elsewhere.

All open scopes were inspected before trials; only the session documentation drafts and, temporarily, the distinct #1000 owner were covered. No merged source was excluded. All failed sources, object dumps and full build logs remain in `work/session-52`. Exact upstream master changes, including upstream build/layout/naming changes, were imported with blob-hash checks; no CI, compiler, layout, data or verification change is authored by this process.
