# Fragment 15 code matching notes

## func_83F0012C

Accepted recipe: initialize the word result to zero, subtract the existing `OSTime` pair `D_83F00400` from `osGetTime()`, convert through the SDK `OS_CYCLES_TO_USEC` macro, and set the result to one when the converted low unsigned word is at least 1000000. The SDK macro performs the original unsigned 64-bit multiply by 64 and divide by 3000. The explicit `u32` conversion preserves the original comparison of the low quotient word. Unknown names and `var_v0` are retained; no fake, artificial argument or semantic name is introduced.

Original `func_83F001A8` calls this owner without arguments and tests its word return. That caller also stores the real `osGetTime` high and low return words at `D_83F00400` and `D_83F00404`, establishing the actual time pair. The owner's complete 31-instruction body has a 32-byte frame, result at offset 28, three real calls including the SDK arithmetic helpers, no trailing padding and no shared switch tail. No data definitions or aliases are changed.

History audit: fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt or fragment 15 regional document in the consulted catalog. No historical normalized or raw similarity score is available for this owner. Current master has no regional document at this path. All open PR scopes were inspected; only documentation drafts #922 and #932 were open and neither covered this owner.

Independent validation against master `834ec350a0d6f5cc4bd2c9e881295b2ec591f84f`: the first SDK time recipe passed the full US ROM build with default host syntax checks and `COMPARE=1`, followed by `md5sum -c baseroms/us/checksum.md5`. Retail MD5: `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 199 previous matched US owners and foreign #933 remain present. Fresh current-head and merge-result Public PR ROM Gate validation must actually run its checksum build before merging; skipped draft checks do not count.
