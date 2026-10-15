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

## 2026-10-15: func_8AF1F514

Matched the independent 31-instruction sparse-switch owner with a real s16 argument and word boolean result. Both original func_8AF1F5F0 call sites explicitly sign-extend the selected value into a0 and branch on v0. The case set is 29, 30, 31, 113, 115, 124, 238, 241 and 242; initialize var_v1 to zero, set it to one for the shared cases, then return it. IDO emits the original binary decision tree and shared result tail. There is no jump table, padding, additional formal or independent switch-tail owner.

The first source recipe passes the full US build with default host syntax checks and COMPARE=1, followed by explicit md5sum -c baseroms/us/checksum.md5: retail 1561c75d11cedf356a8ddb1a4a5f9d5d. The local combined build also retains the independently verified func_8F102A20 source. Both owners are in separate translation units and separate narrow PRs. No global, helper, data, tooling, layout or verification changes.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed contains no exact/solved owner attempt, owner reference or 20D3A0 region note; historical normalized/raw scores are unavailable. The complete current-master region note above was read. Earlier failed func_8AF1F40C and func_8AF208D0 families remain untouched. All open scopes were inspected; the only source PR was this process's separate func_8F102A20. Unknown names, decimal case constants and var_register locals follow the contributing guide. Source/object/build evidence is retained in work/session-54.
