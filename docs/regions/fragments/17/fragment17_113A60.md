# Region notes: fragment17_113A60

## 2026-10-14: func_822085EC

The owner is a no-argument, word-result wrapper. Its original caller
`func_82208A1C` supplies no arguments and branches on the returned word.
The initial helper `func_82206950` also takes no arguments and returns a word.
The other unchanged assembly helpers `func_8220AC38` and `func_82204744` take
no arguments; this owner discards their results. `func_8220ADE0` retains its
existing `s32(s32)` definition and receives the signed halfword at state offset
0. No fabricated arguments or helper return widths are used.

The accepted source initializes `var_v0` before `var_v1`, using the existing
`s16 D_8220EB80[]` declaration through a byte pointer. On the successful initial
guard it returns 1, sets the halfword bit at offset 2, runs the setup helper,
conditionally runs the helper selected by the word at offset 0x14, and invokes
`func_800226C0(52)` when the state is -1 or `func_8220ADE0` returns nonzero.
Other paths return 0. The first spelling matches all 35 instructions, frame
0x20, and result spill at 0x1C. Unknown names remain address/register-based.

History audit: the fleet 113A60 region records a historical accepted
`call-sequence:state-pointer:result-before-pointer` recipe after six iterations.
That paragraph supplies no raw similarity score; no exact owner attempt file
exists at fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed`. The owner was
still `GLOBAL_ASM` on current master, with no open competing PR. The helper
plateaus remain deferred: 06950 normalized .9048/raw .619, AC38 .9167/.75,
and 04744 .9375/.875. Their bodies were audited but not modified or retried.

Independent validation on master `b4ded57db9dbd84a9a209f134f7b72204d97aecb`:
US ROM rebuilt with default host syntax checks and `COMPARE=1`; explicit
`md5sum -c baseroms/us/checksum.md5` passed with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. All thirteen other open process matching PRs
were excluded, including both files for #885 and the new #900 source. Already
merged #880 and current foreign rendering work were preserved. The combined
188-owner workspace also passed. The authoritative Public PR ROM Gate remains
required for each current PR head and actual merge result.
