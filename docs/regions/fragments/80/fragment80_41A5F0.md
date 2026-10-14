# fragment80_41A5F0

## func_842016BC

Accepted recipe: a real unsigned-byte first argument and an output pointer described by `unk_func_842016BC`. Write byte `unk_00`, then bytes `unk_01` through `unk_04` from the four existing helper calls. Finally clear the words at `unk_10` and `unk_0C`, in that order. The unknown seven-byte gap is left unchanged. The struct describes only the owner's written footprint; it does not add initialization of any later fields. Unknown names and decimal literals are retained, with no fakes or artificial arguments.

The compiled definitions in `src/638E0.c` establish all four helpers as `u8(u8)`: `func_80062D20`, `func_80062D5C`, `func_80062D98`, and `func_80062DD4`. These true widths reproduce the original byte normalization and outgoing masks. Older word prototypes in unrelated files were not used or changed.

Original `func_8420199C` supplies a byte loaded from its record or an explicitly byte-masked selector, plus a stack buffer at offset 56. Original `func_84201AEC` supplies a loaded byte and its buffer at offset 76. Both consume the initialized output and ignore any return. The owner is a complete independent 27-instruction function with a 32-byte frame and no trailing padding or shared tail.

History audit: fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt, and current master has no regional document at this path. The full fleet regional note records the unrelated `func_84201728` frame plateau (normalized 0.8621, raw 0.4483); that owner was not retried. No historical raw score is available for this owner. All open PR scopes were inspected before the trial; only documentation draft #922 was open.

Independent validation against master `a2ffd597ba7211af7f3875767930b721849be2f3`: the first typed-output recipe passed the full US ROM build with default host syntax checks and `COMPARE=1`, followed by `md5sum -c baseroms/us/checksum.md5`. Retail MD5: `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 196 previously matched US owners, including merged #927, remained present. The Public PR ROM Gate must actually run its checksum build for the current PR head and merge result before merging; skipped draft checks do not count as validation.

## func_84201620

Accepted recipe: `unk_func_84201620` describes the byte at `unk_01` and pointer at `unk_14`. When bit 0 of the pointed word is clear, call the existing `func_8420138C` unless the byte equals 38, 40, 41, 87, 88 or 148. The nested positive guard and six unequal comparisons reproduce the original branches and final branch-likely delay. The unknown intervening bytes are not modified. No fakes, new semantic names or artificial arguments are introduced.

The compiled `func_8420168C` forwards its single real pointer after two other helpers. Original `func_8420138C` reads this same incoming pointer and updates the record through existing helpers; the owner ignores its result. The owner has a complete 27-instruction body, a 24-byte frame, no incoming argument home or trailing padding, and no shared switch tail. The new declaration forwards the real pointer rather than substituting a no-argument call.

No exact owner attempt or owner-specific regional recipe exists in the consulted fleet history. The existing regional notes and unrelated `func_84201728` normalized 0.8621/raw 0.4483 plateau were retained and not retried. All open PR scopes were checked before the trial; only documentation draft #922 was open. The current master source and accepted #928 note were fetched before editing.

Independent validation against master `aaec8dda638d77c2c786919634db2e530e44cb3b`: the first typed-record guard recipe passed the full US ROM build with default host syntax checks and `COMPARE=1`, then `md5sum -c baseroms/us/checksum.md5` passed with retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 197 previous matched US owners, including #928 in this same file, remained present. Fresh current-head and merge-result Public PR ROM Gate validation is still required before merging.
