# Region notes -- src/fragments/67/fragment67_33D6A0.c

## func_82901554 -- accepted 2026-10-16

This wrapper has two signed-halfword and two unsigned-halfword formals. The original func_829016B0 caller supplies all four, and the owner preserves all four real homes. It fetches resource 344 using the canonical word handle from func_8004C990, emits the setup display list, sets both combiner cycles to primitive RGB and texture alpha, selects opaque black with the actual four-byte helper func_829000F8, and forwards the original formals to the two drawing helpers.

The original func_82900AFC body consumes the four narrow formals plus its fifth resource handle. The original func_82900254 consumes eight real arguments; the last four come from signed halfwords at offsets 6, 8, 2 and 4 of D_829188B0. The existing seven-halfword array declaration and all adjacent C owners remain unchanged. The combiner is represented with the SDK gDPSetCombineLERP macro, reproducing command words 0xFCFFFFFF and 0xFFFDF2F9. No fake local, unused formal, hand-unrolling, padding, volatile access or false helper ABI was introduced.

The first candidate reproduces all 53 owner instructions, the 48-byte frame, the resource spill at stack offset 44, and every original argument/home and global access. US COMPARE=1 and host syntax checks pass; md5sum -c baseroms/us/checksum.md5 returns OK, with ROM MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. This local result does not substitute for a fresh remote gate and exact tested/actual merge-tree audit.

The full fleet note for this region was read. Its previous func_829012E4 normalized 0.8261/raw 0.5362 scheduling and frame plateau is unrelated and was not retried. Existing accepted func_82901DD4/func_82902024 recipes are retained. No exact fleet attempt for func_82901554 was found; references from other owners were not treated as attempts.
