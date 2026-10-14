# fragment67_34C8B0

## func_8290FDB0

Accepted recipe: a signed-halfword argument and an aligned eight-byte `unk_func_8290FDB0` packet. Copy the existing packet with `func_80054210`, replace byte `unk_00` with `arg0 + 1`, and publish it through `func_80054248`. Keep the preceding `func_80055948(3)` and following `func_80051D64(20, 0)` / `func_80055028()` calls in their original order. The word results from the first and last helpers are ignored.

The original caller `func_8290FE04` passes a signed halfword loaded from its incoming argument home. The owner stores that argument at its incoming home and reads the low signed halfword after the packet copy. The compiled definitions of `func_80054210` and `func_80054248` copy and compare two words at record offset 20, establishing the full eight-byte packet footprint. The unknown bytes are retained by copying the complete packet before changing its first byte. No artificial arguments or scratch padding are needed.

The complete independent owner contains 21 instructions, a 32-byte frame, and its own return. It is separately called and contains no shared switch tail or trailing padding.

History audit: current fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt or `67_34C8B0` regional record. Consequently no historical normalized or raw similarity score is available for this owner. All open PR scopes were checked before the trial; none covered this file or owner.

Validation against master `11917f5fc063360751169e3f616d51690dc2d041`: the first typed-packet recipe passed the full US ROM build with default host syntax checks and `COMPARE=1`, followed by `md5sum -c baseroms/us/checksum.md5`. Retail MD5: `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 193 previously matched US owners remained present. Local validation does not substitute for the current-head and merge-result Public PR ROM Gate.
