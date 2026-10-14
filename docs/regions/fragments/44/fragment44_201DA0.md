# Region notes: fragment44_201DA0

## 2026-10-14: func_8AF145B4

This distinct owner receives fourteen real arguments: destination pointer,
four words, six unsigned bytes, two words, and an aligned source pointer.
The full original func_8AF14648 caller was audited. It zeroes 1284 bytes at
stack offset 104, passes that buffer in outgoing slot 52, and does not consume
a return value. The buffer ends at offset 1388 within the 1416-byte frame.

The accepted unk_func_8AF145B4 has 321 u32 elements. Aggregate assignment
copies those 1284 bytes to destination offset 40, preserving the original
three-word streaming loop and all 37 instructions without a stack frame.
The header retains four word stores, six byte stores, the word at offset 0,
sentinel -1 at offset 20, and word at offset 28. Source order stores arg11
before the sentinel, following the independently verified sibling recipe.
Unknown tokens retain address, argument and offset names. New numeric literals
use decimal under the current contributing guide. No fakes were introduced.

History audit: no exact owner attempt or 201DA0 region record exists in fleet
gs-attempt-history at main afee707ab78d3f63f2f9deeadc7551ec0080eeed; no
historical raw similarity score is available. All open PR file scopes were
checked before the trial. This owner is independently called and has a
complete return boundary; it is not an interior switch tail.

Independent validation against master
73d4d5df5a1f893b389f92f77ffa1062bb700d81: the US ROM rebuilt with default
host syntax checks and COMPARE=1. Explicit md5sum -c baseroms/us/checksum.md5
passed with retail MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. All 5 other
open process matching PRs were excluded. Both already merged #885 source files,
all other merged process sources and current foreign source were preserved.
Earlier validation also passed against the pre-integration master with sixteen
open siblings excluded. The combined
191-owner workspace also passed. The Public PR ROM Gate must actually run
its checksum build successfully for the current PR head and merge result.
The upstream draft-skip policy is not a verification pass.

