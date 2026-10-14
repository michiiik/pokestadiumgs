# Region notes: fragment44_20BDB0

## 2026-10-14: func_8AF1DC14

The original `func_8AF1DCD4` call supplies fourteen real arguments: destination,
four words, six unsigned bytes, two words and the aligned stack-buffer pointer
at 0x6C in outgoing slot 0x34. The 1284-byte source ends at 0x570 within the
caller frame. The caller does not consume a return value.

The accepted `unk_func_8AF1DC14` is a 321-element `u32` aggregate. Header
stores retain their retail offsets, and the aggregate assignment copies to
offset 0x28. Source order stores `arg11` at offset 0 before sentinel -1 at
0x14, following the independently verified sibling recipe. The first source
spelling emits all 37 retail instructions, with no frame and the original
three-word streaming loop. Unknown names remain address/offset names.

Preserve the already matched `func_8AF1DB40` and `func_8AF1DBA4` aggregate
helpers when restoring or refreshing this translation unit. They are distinct
owners; neither was retried or changed for this match.

History audit: no exact owner attempt or 20BDB0 regional record was present at
fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed`; no historical raw score is
available for this owner. All open PR scopes were checked for duplicates.

Independent validation on master `b4ded57db9dbd84a9a209f134f7b72204d97aecb`:
US ROM rebuilt with default host syntax checks and `COMPARE=1`, then explicit
`md5sum -c baseroms/us/checksum.md5` passed with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. All fifteen other open process matching PRs
were excluded while merged #880 and current foreign rendering work remained.
The combined 190-owner workspace also passed. The authoritative Public PR ROM
Gate must validate the current head and actual merge result before integration.
