# fragment67_3422F0 matching notes

## func_829061CC — accepted C, session 64

The real formals are a word, a pool pointer and a two-word/word-result callback. Original assembly homes all three, invokes the callback twice with (0, 0) and (1, 0), and stores both full-word results. The already compiled sibling `func_82906264` independently uses that exact callback contract. Existing compiled caller `func_82903444` obtains its callback from `func_80004B4C` and the pool from `MainPool_AllocState`; its stale three-word declaration is corrected with explicit pointer/callback casts at the existing call. The full-ROM match proves the caller remains byte-identical.

The owner retains the real word global and canonical layout processor pointer result, four-byte helper call, 1.0 float setup, and callback/layout/callback store order. The already rejected helper `func_82906170` remains assembly and is not retried or modified. No extra arguments, fabricated return, helper ABI change or FAKE construct is introduced.

The first candidate preserves all 38 original executable words, the 24-byte frame, existing C siblings, and the caller. Fleet exact-owner and regional catalog searches contain no owner attempt or fragment67_3422F0 record. The full caller-region history was read, including 04E9C .9091 normalized/.8727 raw, 02FE0 .9355/.6129 and permutation1/.8, and later plateaus; those owners remain excluded. The adjacent interpolation region's 06A50 .9859/.9437 and 06B6C .9885/.9540 narrow-formal blockers remain excluded.

Validation: default host syntax checks, `make rom COMPARE=1 -j2`, and explicit `md5sum -c baseroms/us/checksum.md5` pass. Retail ROM MD5 is `1561c75d11cedf356a8ddb1a4a5f9d5d`. No CI, verification, tool, layout, data, linker or symbol edits are part of this owner transaction.
