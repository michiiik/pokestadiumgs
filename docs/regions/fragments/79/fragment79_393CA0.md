# fragment79_393CA0

## func_841366C4

Accepted recipe: retain the unsigned-byte first argument and use a signed-halfword second argument. Read byte 19841 of `D_84195280`, subtract one, replace a negative index with 29, then call the existing `func_841365F4(u8*, u8, s16)` with the record at index times 640 and both real arguments. Keep unknown names and decimal literals. Update the six existing owner declarations to the same signed-halfword type.

The original owner normalizes incoming `a1` through a shift-left/arithmetic-shift-right pair at entry, forwards it in `a2`, and stores both real arguments at their incoming homes. Its separately called 23-instruction body has a 24-byte frame and a complete return, with no shared switch tail or trailing padding. Original ASM callers, including `func_8413146C` and `func_84129374`, supply a byte and -1 and ignore the result. The compiled callers also pass -1. The helper normalizes its byte and signed-halfword inputs and stores them into the selected record; its existing prototype is retained.

The first trial kept the stale word second formal and cast only at the helper call. It failed the full ROM checksum (`4c66f0ae26d4207794df386f124ce142`): the resulting 22-instruction owner loaded the low halfword from the stack at call time instead of reproducing retail's early normalization pair. Correcting the real narrow formal and all six declarations produced the accepted match. No unrelated caller implementation or helper body changed. A declaration-count precondition initially aborted before any source write or build; it was corrected after confirming the unchanged baseline.

History audit: fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt. References to this owner in other failed candidates are caller references. The full regional notes provide the record-stride clamp-wrapper recipe and warn about incoming-home and rodata dead ends. The helper's unrelated plateau (normalized 0.8788, raw 0.5455) was read and not retried; no historical owner raw score is available. All open PR scopes were checked before both trials.

Independent validation against master `47055da7fbdf7bda1f80f70fbd626c5d8233ab94`: full US ROM build with default host syntax checks and `COMPARE=1`, followed by successful `md5sum -c baseroms/us/checksum.md5`. Retail MD5: `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 194 previously matched US owners, including merged #915, remained present. This local result does not substitute for the current-head and merge-result Public PR ROM Gate.
