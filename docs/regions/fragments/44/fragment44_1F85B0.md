# Region notes: fragment44_1F85B0

## 2026-10-14: func_8AF0AAF8 remains unmatched

Two US/default-host-syntax ROM failures. Actual no-argument owner has a real no-argument caller. Helpers are canonical u8(u8) func_8006397C/func_800639C0, s16(s16) Trade_GetSelectedBox, and u8(u8,u8,u8,s32) func_80063454. Do not substitute the stale s32 helper declarations in 615D0. Scalar byte results stay in S2/S3, requiring five saved registers and 39 instructions/frame 0x30 rather than retail three saved registers/35 instructions/frame 0x38. Two-byte array captures recover byte spills 0x2C/0x2D and three saved registers, but global address still folds to two direct LUI/LBU calls, frame remains 0x30, and output pointer increment/store delay order differs (also 35 instructions). Need an evidenced global/pair lifetime and loop scheduling model. Do not repeat scalar/array/pointer/declaration-order forms or false helper prototypes. Preserve previously merged func_8AF0A850 when restoring this source.

History audit: No exact owner attempt or 1F85B0 region record at fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed. Prior process failure func_8AF0A340 remains deferred; its recipe was not retried.

All failed sources, full build logs, and object disassemblies are retained in
`work/session-44`; each fresh baseline was restored. Open PR scopes were
checked for duplicate owner work. No CI, verification, linker, or data changes
were made. These attempts are failures, not claimed matches. The restored
186-owner workspace passes the US retail checksum with default host syntax
checks. Unknown tokens retain their existing address/offset names.
