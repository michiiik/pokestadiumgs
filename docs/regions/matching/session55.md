# Session 55 failed investigation

## func_88B04BB4

One audited source trial failed the full US retail comparison. Original func_88B007A0 calls this independent leaf without arguments and compares its word result with 11. The owner scans 36 bytes from D_88B069CE and counts nonzero bytes using byte-width accumulation. Its original body is 33 words with no frame, trailing padding or shared switch tail.

The candidate used a u8 count initialized to zero and an s32 counted for loop over indices 0 through 35, incrementing the count for each nonzero byte. The compiler retains the four-way unrolled byte tests and byte-width count increments, but strength-reduces the loop to an end pointer at D_88B069CE + 36 in v0, with a cursor in a0 advanced by four. Retail instead retains an index in v0 advanced by four, a bound of 36 in a1 and one-byte cursor increments between tests. The candidate adds another global LUI, changes prologue and load scheduling, and moves the next iteration load into the likely backedge delay. It emits 30 instead of 33 words. Full-ROM MD5: d531d59e91b6e1fb6fe558e2ae74f453.

Retain this index/cursor/end lifetime blocker. Do not repeat ordinary counted, pointer, while, declaration or explicit-unroll recipes without supported new evidence. No speculative volatile accesses, dummy formals, memory writes, compiler settings or tools were used. Failed source, object dump and full build log remain in work/session-55.

Only the failed owner and its newly added duplicate extern were restored. The fresh current-master source blob 777c399af426c17c6718f085a84ffe93360b5cba is exact. A full make rom COMPARE=1 build with default host syntax checks and explicit md5sum -c baseroms/us/checksum.md5 passes retail 1561c75d11cedf356a8ddb1a4a5f9d5d, preserving all 211 previously merged process owners and both new open implementations.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact owner attempt or reference. Full fragment40_1E0550 notes were read, including the unrelated func_88B048C4 historical normalized/raw 0.9714/0.9714 scheduling residual and exact-line acceptance, and func_88B05494 normalized/raw 1/0.5526 resolved selector lifetime. Those source families were not retried. Current master had no regional document for this file. Every open PR scope was inspected; active foreign fragment 13 dispatch/layout work was deferred.

Accepted func_88215CE0 and func_81802438 recipes and the former's resolved first failure are documented in their separate matching PRs #1031 and #1032. This failed-note PR changes no game source or verification and is outside matching merge authorization.
