# Region notes: fragment44_20F140

## 2026-10-14: func_8AF20F64

This distinct fourteen-argument owner receives a destination pointer, four
words, six unsigned bytes, two words and an aligned source pointer.
The full original func_8AF20FF8 caller was audited. It zeroes the actual
1284-byte buffer at stack offset 84 and passes that pointer in outgoing slot
52. The buffer ends at offset 1368, exactly within the caller's 1368-byte
frame. No return value is consumed.

The accepted unk_func_8AF20F64 contains 321 u32 elements. The aggregate
assignment copies to destination offset 40 and emits all 37 retail
instructions, including the three-word streaming loop and no stack frame.
The header retains all field widths and offsets. Store arg11 at offset 0
before sentinel -1 at offset 20 in source order, following the independently
verified sibling recipe. The first source spelling passes. Unknown tokens
retain address/offset/argument names, and new numeric literals are decimal.
No semantic names or fakes were introduced.

History audit at fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed found
no exact owner attempts or owner-specific regional note and therefore no
historical raw score. The existing 20F140 history concerns func_8AF221C4:
ten, seven and five exhausted probes reached normalized/raw .84/.38,
.74/.34 and .66/.34 with global-address register drift. That owner remains
unchanged and was not retried. All open PR scopes were inspected before this
trial; this owner has a separate call and complete return boundary.

Independent US ROM validation on master e587efc2aca4b35aa7dfdaa72497b54c53c509db
passed with default host syntax checks and COMPARE=1, followed by explicit
md5sum -c baseroms/us/checksum.md5 and retail MD5
1561c75d11cedf356a8ddb1a4a5f9d5d. Only 6 freshly open matching siblings
were excluded; all merged process sources, both #885 files, and the newly
merged foreign resource-loading changes were preserved. The combined
193-owner workspace also passed. Require an actual successful Public PR ROM
Gate checksum build for the current head and merge result before integration;
skipped draft checks are not a pass.

