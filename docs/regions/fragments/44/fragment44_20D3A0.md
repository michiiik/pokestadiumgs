# Region notes: fragment44_20D3A0

## 2026-10-14: func_8AF1F378

The owner receives fourteen real arguments: a destination pointer, four words,
six unsigned bytes, two words, and an aligned source pointer. All three original
call sites were audited: `func_8AF1F978` passes its stack buffer at 0x54, and the
two `func_8AF1FCA4` call sites pass the stack buffer at 0x74. The corresponding
outgoing stack slot is 0x34. The callers do not consume a return value.

The accepted `unk_func_8AF1F378` contains 321 `u32` elements, preserving the
1284-byte copy into destination offset 0x28. The compiler emits the retail
three-word streaming copy loop with no stack frame. Four word stores and six
byte stores retain the original header offsets. Unknown tokens retain address,
argument, and offset names under the separate repository's contributing guide.

Use source order `*(s32 *)arg0 = arg11` before the store of -1 at offset 0x14.
This reproduces the retail instruction order: argument load, sentinel store,
argument store. An initial sentinel-first spelling produced 37 instructions but
swapped t3/t4 allocation and moved the sentinel store ahead of the last byte
store. Its failed source, full build log, and object disassembly are retained
in `work/session-45`. The corrected header order follows the independently
verified sibling recipes and matches all 37 instructions. Do not retry the
sentinel-first or manual pointer-copy-loop families for this owner.

History audit: no exact owner attempt or 20D3A0 regional note was present in
`michiiik/pokestadium-fleet/knowledge-base/gs-attempt-history` at main
`afee707ab78d3f63f2f9deeadc7551ec0080eeed`; unrelated references are not owner
attempts. All open PR scopes were inspected for duplicate owner work.

Independent validation on master `b4ded57db9dbd84a9a209f134f7b72204d97aecb`:
the US ROM rebuilt with default host syntax checks and `COMPARE=1`, then
`md5sum -c baseroms/us/checksum.md5` passed with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. All twelve still-open process matches were
excluded, preserving the already merged #880 source and current foreign
rendering matches. The combined 187-owner workspace also passed. The Public
PR ROM Gate must still validate each current PR head and actual merge result.
