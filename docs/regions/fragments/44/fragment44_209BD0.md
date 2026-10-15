# fragment44_209BD0

## func_8AF1C31C

Accepted recipe: the actual no-argument, no-result wrapper. Call the canonical rendering helpers in order, using 16/0 and four 255 arguments, then test func_8AF1BED8 and func_8AF1BF00 independently and call func_8AC05F00 with the corresponding existing global object address. Both predicates are compiled word-result/no-argument definitions in this TU. Canonical definitions in src/47580.c establish the other helpers' real argument contracts, and src/fragments/43/fragment43_1E5A10.c establishes void func_8AC05F00(void *). No invented incoming arguments, false helper types, new storage, semantic names or fakes.

Original func_8AF00E24 calls this owner without setting arguments and ignores its result. The complete owner has 30 executable words with a 24-byte frame, followed by three alignment NOPs. The existing C_FUNCTION_PADDING(12) pragma after this owner preserves those actual trailing bytes. This is not an interior switch tail or an independent function invented from padding. Prior four-byte-padding dead ends remain untouched.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact owner attempt, reference or fragment44_209BD0 region record, and current master has no document at this path. Historical normalized/raw_similarity_score is unavailable. All open PR scopes were inspected and foreign fragment44_1F0680 work was deferred. The prior func_8AF1B9C0 register/load failure is not retried.

The first recipe passes full US make rom COMPARE=1 -j2 with default host syntax checks and explicit md5sum -c baseroms/us/checksum.md5. After #1049 merged, the same full checks pass against master ebd30a903a9d04ec90dd0c4ccbddd8fd3d67e59e plus only this owner: retail 1561c75d11cedf356a8ddb1a4a5f9d5d. All earlier matched C and upstream changes remain present. Require a fresh actual checksum build in Public PR ROM Gate for the current head/base and tested merge tree before merging; local passes do not repair historical gate gaps.
