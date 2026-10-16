# Region notes -- src/fragments/10/fragment10_D4C50.c

## func_82800020 -- accepted 2026-10-16

The owner has three real formals: a pointer to the 192-byte destination, a descriptor pointer, and a signed word. The original caller func_82800490 supplies all three. The descriptor contains signed halfwords at offsets 0 and 2 and a word at offset 4. The owner clears the destination, loads resources 341 and 54, stores the result of func_8004D690 at offset 180, creates and finalizes a pool state, stores the pointer returned by func_81600E28 at offset 8, and retains the descriptor pointer at offset 184. The last call receives destination + 12, descriptor halfword 2, the third formal, descriptor word 4, and destination word 180.

The helper audit uses the canonical u16 argument of func_8004C8C0, the word argument/result of func_8004D690, the pointer result of MainPool_AllocState and pointer argument of MainPool_FinalizeAllocation, and the actual pointer/word/word arguments and pointer result of func_81600E28. The actual five-word/pointer ABI of func_82801510 is preserved. No unused formals, aggregate shims, volatile accesses, or padding were introduced.

The first body matched all 43 owner instructions. An explicit SDK _bzero prototype was then added and the final source was rebuilt with the host checks enabled. US COMPARE=1 passed; md5sum -c baseroms/us/checksum.md5 returned OK, with ROM MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. Adjacent merged func_8280018C is retained. This local result does not assert remote gate or merge provenance; those require the actual current-head gate and merge-tree audit.
