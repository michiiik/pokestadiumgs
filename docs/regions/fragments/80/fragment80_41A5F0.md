# fragment80_41A5F0

## func_842016BC

Accepted recipe: a real unsigned-byte first argument and an output pointer described by `unk_func_842016BC`. Write byte `unk_00`, then bytes `unk_01` through `unk_04` from the four existing helper calls. Finally clear the words at `unk_10` and `unk_0C`, in that order. The unknown seven-byte gap is left unchanged. The struct describes only the owner's written footprint; it does not add initialization of any later fields. Unknown names and decimal literals are retained, with no fakes or artificial arguments.

The compiled definitions in `src/638E0.c` establish all four helpers as `u8(u8)`: `func_80062D20`, `func_80062D5C`, `func_80062D98`, and `func_80062DD4`. These true widths reproduce the original byte normalization and outgoing masks. Older word prototypes in unrelated files were not used or changed.

Original `func_8420199C` supplies a byte loaded from its record or an explicitly byte-masked selector, plus a stack buffer at offset 56. Original `func_84201AEC` supplies a loaded byte and its buffer at offset 76. Both consume the initialized output and ignore any return. The owner is a complete independent 27-instruction function with a 32-byte frame and no trailing padding or shared tail.

History audit: fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt, and current master has no regional document at this path. The full fleet regional note records the unrelated `func_84201728` frame plateau (normalized 0.8621, raw 0.4483); that owner was not retried. No historical raw score is available for this owner. All open PR scopes were inspected before the trial; only documentation draft #922 was open.

Independent validation against master `a2ffd597ba7211af7f3875767930b721849be2f3`: the first typed-output recipe passed the full US ROM build with default host syntax checks and `COMPARE=1`, followed by `md5sum -c baseroms/us/checksum.md5`. Retail MD5: `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 196 previously matched US owners, including merged #927, remained present. The Public PR ROM Gate must actually run its checksum build for the current PR head and merge result before merging; skipped draft checks do not count as validation.
