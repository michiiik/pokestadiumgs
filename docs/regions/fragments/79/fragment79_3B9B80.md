# Fragment 79 3B9B80 matching notes

## func_8414C7D4

Accepted recipe: switch on the existing `func_80062D20(arg0)` byte result. Cases 111 and 116 return 3; case 103 returns 2; cases 28, 89 and 144 return 0. The default returns 0 for incoming byte 233 and 1 otherwise. Preserve the real byte argument and word result, unknown function names, and all original behavior. No fake, artificial argument, semantic rename or padding is introduced.

Original `func_8414C858` supplies byte loads in both calls, consumes the full word result, and separately narrows its saved result to a byte. The canonical compiled `func_80062D20` has the actual `u8(u8)` ABI, already declared correctly in this TU. The complete owner has 33 instructions and a 24-byte frame; its six-case comparison chain is independent, with no jump table or shared switch tail.

History audit: live fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt, owner reference or `79_3B9B80` regional document in the consulted catalog. No normalized or raw similarity score is available for this owner. Current master has no document at this regional path. All open scopes were inspected: documentation drafts #922, #932 and #940 cover only their session notes. Original matching PRs #558, #559 and #561 are already merged.

Independent validation against master `21d7fb8c6505eb8e66031331e63eabf8d2d8fe96`: the first switch recipe passed `make rom COMPARE=1 -j2` with default host syntax checks enabled, followed by `md5sum -c baseroms/us/checksum.md5`. Retail MD5: `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 201 previous process matches and foreign #941 through #946 remain present. No CI, verification, compiler or layout changes are authored. A fresh current-head and merge-result Public PR ROM Gate must actually run the Build and compare against the retail checksum step before merging; skipped draft checks do not count.
