# fragment11_D7BC0

## func_81600340

Accepted recipe: a single `f32 arg0`, the existing zero/one clamp guards, then `arg0 = (arg0 - 0.5f) * 2.0f` and the left-associated cubic expression `arg0 * arg0 * arg0 * 0.5f + 0.5f`. IDO emits the original subtraction, doubling through `add.s`, three multiplies, and final addition. The comparisons, including their behavior for unordered floating-point input, retain the original instruction sequence. Unknown names and decimal literals are preserved; no fakes or additional arguments are needed.

The original leaf reads `f12` and returns `f0`. Data at `D_8160BD00` registers it as entry 8 at offset 32 alongside the existing `f32(f32)` clamp callbacks. Original table calls in `func_824070E4` and `func_8130881C` pass a single float in `f12` and consume `f0`; these particular calls select the first table entry. No direct named caller for entry 8 was found. The owner's complete 28-instruction body ends before the separate `func_816003B0`, with no stack frame, trailing padding or shared switch tail.

History audit: fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt or `11_D7BC0` regional record, and current master has no regional document at this path. No historical normalized or raw similarity score is available for this owner. Earlier failed `func_81600450` and `func_81600884` investigations were retained and not retried. All open PR scopes were inspected; only documentation draft #922 was open before the trial.

Independent validation against master `c73a3a3c9a8097a4e5ff8b85cc062e5a0b531fee`: the first recipe passed the full US ROM build with default host syntax checks and `COMPARE=1`, followed by `md5sum -c baseroms/us/checksum.md5`. Retail MD5: `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 195 prior matched US owners remained present. The Public PR ROM Gate must actually run its checksum build successfully for the current PR head and merge result before merging; a skipped draft check is not validation.
