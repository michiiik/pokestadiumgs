# Session 54 failed investigation

## func_8003C2D8: destination subobject lifetime

One audited source trial failed the full US ROM comparison. Retail is 1561c75d11cedf356a8ddb1a4a5f9d5d; the failed result was c1101f52508a58d3b6cf151872c8fe5d. The owner remains GLOBAL_ASM. Only its candidate and one corresponding forward declaration were restored; the exact fresh-master 229E0 blob cf3ee3a7952fdbe6ac4e056dbeddd08ae10412ef is retained. A full default-host-check COMPARE=1 build and explicit checksum pass after restoration, preserving both new matching owners and all 209 previous process owners.

The independent leaf receives one word, writes its low halfword and has no used return value. Original func_8003C390 passes literal 100; compiled Geo_NodeAnchor passes an actual signed-halfword load. The trial uses a word formal, correcting the stale same-file s16 forward declaration consistently; no artificial formal or return was introduced. Existing void-pointer D_8009491C remains unchanged. Its byte at offset 167 is a count bounded by 12, followed by 16-byte records at offset 168. The source float triple comes from D_80124F68 plus its signed word at offset 4256 times 64, at offsets 48, 52 and 56.

The candidate describes the destination with unknown-address/offset structs: a 167-byte prefix, count byte, and twelve records with a halfword at 0 and floats at 4, 8 and 12. It captures the count, increments the byte, captures the source pointer, stores the incoming halfword, then streams the three floats into the indexed record. The compiled owner has 26 instructions instead of 27, with no frame. It folds the required destination-plus-168 address materialization into stores at 172/176/180. Source/destination pointers use a0/a1 instead of retail a1/a0; the source address addition uses index/base instead of base/index, and the first count temporary/shift schedule differs. The first three instructions and guard base agree; float streaming and guards retain the original semantics.

Require supported destination-subobject/address lifetime evidence before retrying. Do not repeat ordinary raw/typed/indexed/pointer, declaration, operand or prototype variations. Full candidate source, original/candidate object evidence and build logs are retained under work/session-54. No failed source edit remains.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact/solved owner attempt; its regional entry is normalized 0/raw null with no tried family. References from an unrelated rejected func_8003C390 are not owner attempts. The complete fleet and current-master 229E0 notes were consulted; previous 3C9B8, 34838, 425C0 and 27EE0 families were not replayed. All open scopes were inspected before edits; only this process's separate func_8F102A20 source PR was open.

## Additional screening

- func_861000B8: full fragment 49 notes explicitly defer normalized/raw 0.8846/0.8846 instruction drift; its extra JR/NOP boundary also needs evidence. No trial.
- func_8160A270: full E1E10 notes record 42 attempts at normalized 0.7647/raw 0.1176 with exhausted non-folded index arithmetic families. No trial.
- All fragment 69 terminal histories and the earlier process failure for func_8F100020 remain untouched.

Accepted recipes are documented in their separate narrow matching PRs. This documentation stays draft and outside matching-PR merge authorization. No authored data, tooling, layout, CI or verification changes.
