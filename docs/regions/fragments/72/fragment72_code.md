# Region notes: fragment72_code

## 2026-10-14: func_8F400DE8 remains unmatched

One US/default-host-syntax ROM failure. Actual no-argument initializer clears 0x48 bytes, sets two halfwords, allocates through pointer-result func_80041C98(s32), loads two assets through canonical u8* func_8004BA70(s32), and calls real no-argument func_80041E2C. Separate scalar symbols preserve frame 0x18 and call sequence but produce repeated LUI instructions for the adjacent stores rather than the retail shared-LUI pairs; 39 instructions versus 35. Initial halfword constant/store scheduling also differs. An evidenced semantic aggregate/global-address model is needed before another trial. Do not repeat separate scalar or speculative grouped-field forms, and do not edit linker/data/tools to coalesce them.

History audit: No exact owner attempt or fragment72 region catalog note at fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed.

All failed sources, full build logs, and object disassemblies are retained in
`work/session-44`; each fresh baseline was restored. Open PR scopes were
checked for duplicate owner work. No CI, verification, linker, or data changes
were made. These attempts are failures, not claimed matches. The restored
186-owner workspace passes the US retail checksum with default host syntax
checks. Unknown tokens retain their existing address/offset names.
