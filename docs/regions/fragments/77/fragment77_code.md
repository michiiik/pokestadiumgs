# Fragment 77 native matching notes

## 2026-10-15: clock and confirmation action accepted

Batch `7dbbf507b1984bdd8f6463cd2e2c25fd` accepts two owners through the normal
native runner, both `link_verified: true`, with one combined full-ROM gate:

- `func_8F8014E4`: 49 words / 196 bytes, leaf. Winner
  `f77:clock:prefix-False:early-return-False:cast-day-False`.
  Preserve nested frame/second/minute/hour carries at 30/60/60/24 and the
  two halfword stores implementing the day increment and eight-bit mask.
- `func_8F8021E8`: 51 words / 204 bytes, frame 0x20. Winner
  `f77:confirm:local-result-False:field-pointers-False:bound-snapshots-False`.
  Read the event, render, then handle confirm/cancel. Confirm plays sound
  before reading table bounds and clamps the signed state halfword against
  unsigned bounds. Keep the post-store signed reload and distinct return 1.

The table is u16 rows of 17 elements; the state remains the existing u16
array with a signed halfword view for the clamp. No fake locals, volatile
accesses, forced registers, helpers, compiler/object changes or layout edits.
Naming plan has no known names for these owners. Post-formatting and scoped
extern deduplication, fresh/20-leading-blank controls reproduce every object
section and all seven C definitions against the original assembly baseline.
The normal ROM gate passes MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.

`func_8F801F44`: **requeue**, not accepted. Eight range-setup candidates
test real row/state pointers and initialization forms. Best normalized
similarity 1.0 hides raw similarity 0.7188, at the correct 128-byte size;
the first residual is `lhu t1,10(v0)` versus `lhu t9,10(v0)` at offset 32.
Do not mistake this for exactness. Preserve the writes to state offsets
4/0/2 before `func_8F8015A8` and the fresh post-call state read at offset 12
for the offset-6 store. Next hypothesis: real field snapshots and declaration
order to explain the temporary allocation; inspect the entire diff before
choosing a permuter follow-up. This batch did not establish a compiler wall.
