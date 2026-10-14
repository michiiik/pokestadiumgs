# Fragment 68 code matching notes

## func_8F000020

Accepted recipe: preserve the one incoming word while allocating through `func_80041C98(5)`, calling the actual no-argument `func_80041E2C`, and forwarding the returned pointer to `func_80042C68` with both dimensions equal to 128. Store the real returned pointer in `D_8F000924`, clear bit `0x100` of its first halfword, clear `D_8F00092C`, and set `D_8F000920` to zero or the nonzero incoming word minus one. The existing unknown global names are retained; no fake, semantic name or artificial argument is introduced.

Original `func_8F0007E8` forwards its first incoming word from its real stack home and ignores the owner's result. The owner has a complete 30-instruction body, a 32-byte frame and one incoming argument home, with no trailing padding or shared switch tail. Original `func_80041C98` takes one word and returns an allocated pointer; `func_80041E2C` reads no incoming arguments; `func_80042C68` takes the real pointer and two word dimensions, stores those dimensions as halfwords, and returns the allocated object. The helper declarations follow those definitions rather than unrelated stale word-handle declarations.

History audit: fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt or fragment 68 regional document in the consulted catalog. No historical normalized or raw similarity score is available for this owner. Current master has no regional document at this path. All open PR scopes were inspected; only documentation draft #922 was open, and its scope did not cover this owner.

Independent validation against master `3bea111c0caa68eed37a2c812c4adab1f491c75f`: the first pointer initializer recipe passed the full US ROM build with default host syntax checks and `COMPARE=1`, then `md5sum -c baseroms/us/checksum.md5` passed with retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 198 previous matched US owners and foreign #930 remain present. The current-head and merge-result Public PR ROM Gate must actually run its checksum build before merging; skipped draft checks do not count.
