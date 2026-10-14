# Region notes: fragment44_20EBC0

## 2026-10-14: func_8AF209E4

This is a distinct fourteen-argument, void aggregate-copy owner. Its original
`func_8AF20A78` caller was audited: it passes four header words, six unsigned
byte values, two additional words and its actual stack buffer at 0x54 in the
outgoing slot 0x34. No return value is consumed. The 1284-byte input buffer
ends within the caller's 0x558 frame.

The accepted `unk_func_8AF209E4` contains 321 `u32` elements. Four header word
stores, six byte stores, the word at offset 0, sentinel -1 at offset 0x14,
and word at offset 0x1C preserve the retail layout. The aggregate assignment
copies to offset 0x28 and emits the exact three-word streaming loop with no
stack frame. Store `arg11` at offset 0 before the sentinel in source order,
following the positively verified sibling recipe. The first spelling matches
all 37 instructions. All names remain unknown address/offset names; no new
semantic names or fake operations were introduced.

History audit: no exact owner attempt or 20EBC0 region record was present at
fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed`; no historical raw score is
available for this owner. All open PR scopes were checked for duplicate work.
The neighboring callback `func_8AF20950` and the deferred `func_8AF20E4C`
pointer-lifetime family were inspected only and remain unchanged.

Independent validation on master `b4ded57db9dbd84a9a209f134f7b72204d97aecb`:
US ROM rebuilt with default host syntax checks and `COMPARE=1`; explicit
`md5sum -c baseroms/us/checksum.md5` passed with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. All fourteen other open process matching PRs
were excluded, preserving merged #880 and current foreign rendering work.
The combined 189-owner workspace also passed. Await the authoritative Public
PR ROM Gate for the current head and actual merge result before integration.
