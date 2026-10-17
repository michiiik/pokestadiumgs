# Fragment 23 matching notes

## func_82A009A0

The function maps signed word selectors 1 through 7 to 11, 7, 1, 15, 9, 13, and 3. Every other selector returns 5. It takes one word argument and returns a word. The compiled `func_82A00A04(s32, s32)` forwards its first argument and consumes the result as a word; its original caller `func_82A00ABC` supplies the selector loaded from `D_82A01A09` and stores the eventual result as a halfword at object offset 38.

Evidence is in `src/fragments/23/fragment23_code.c`, `asm/us/nonmatchings/fragments/23/fragment23_code/func_82A009A0.s`, and `func_82A00ABC.s` in the same assembly directory. The target begins with an unsigned range test of selector minus 1, then dispatches through seven entries of `jtbl_82A01950`. All entries target labels inside this owner. The next owner begins at address `0x82A00A04`; no shared tail is treated as another function.

The existing compiled neighbor `func_82A00A04` uses a preinitialized word result and a seven-case switch. The new owner uses that supported control model with default 5. IDO emits the target's six direct return arms and its last case/common result move: 25 executable words, no frame, and no extra padding. The existing YAML `.rodata` subsegment at ROM address `0x14F880` already covers this owner's table and the neighbor's table. No table, split, linker, compiler, verification, helper ABI, or other function changes are required.

Fleet history at `afee707ab78d3f63f2f9deeadc7551ec0080eeed` contains no exact owner attempt or reference to `func_82A009A0`, and its region catalog has no fragment 23 note. The existing compiled neighbor supplies the source-shape evidence.

Local validation used public master `67180352e9ef1e09a4b1130e782fd81e145ab843` plus this owner replacement, source Git blob `76ee1a895c8e8836fd921e73f3ad87b4e0ddcd35`, targeting the US ROM. `make rom COMPARE=1 -j2`, an explicit `md5sum -c baseroms/us/checksum.md5`, and all 427 host syntax checks passed. The built ROM MD5 is `1561c75d11cedf356a8ddb1a4a5f9d5d`. The full-ROM check includes the unchanged compiled neighbor and its existing table. This local result is separate from public CI validation of the published commit.
