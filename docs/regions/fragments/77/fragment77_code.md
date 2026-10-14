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

## 2026-10-15: range setup and two word-confirm handlers accepted

The range-setup requeue above is resolved. Batch
`43bbacccdbca4b21bdebb6ef96fb208b` accepts `func_8F801F44` with winner
`f77:range-source-order:012`: 32 words / 128 bytes, frame 0x18,
`link_verified: true`, normal combined full-ROM gate. Write fields 0, 1,
then 2 in C; IDO schedules their stores into retail order 2, 0, 1 and
allocates the expected temporaries. The earlier C store order mirrored
scheduled assembly rather than source order. Real snapshots did not solve
this. A stale advisory register-tie warning accompanies the accepted batch;
it is not a reason to reject the measured acceptance or stop early.

Batch `dfe4cfee21854a3b84d95ef4ad2a78c7` accepts `func_8F80299C` and
`func_8F802D0C`, each 51 words / 204 bytes, frame 0x20,
`link_verified: true`, one combined full-ROM gate. Both use winner
`f77:word-confirm:result-False:pointers-False:bounds-False`. These are
siblings of the prior halfword confirmation handler, using signed word
state at offset 0x14 and their respective input/render calls. The word
clamp naturally retains its newly assigned value rather than inserting
the halfword handler's signed reload. Keep the actual word view and
fresh bounds after the sound call; do not factor the handlers into helpers.

Post-formatting and scoped extern deduplication, fresh/20-leading-blank
controls match all sections and all ten C functions against the original
assembly baseline. The normal full-ROM gate passes retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Naming plan has no known mappings.

`func_8F8026DC` / `func_8F802A68`: **requeue**. The signed decimal/hex
digit initializers use the same natural field initialization order, call
`func_8F8015A8`, reload the word at offset 0x14, then write remainder bytes
starting at offset 12. A guarded do/while with a real byte cursor closes
the source/scheduling differences except one base-address materialization:
retail independently loads the state base for the cursor, while C copies
the already materialized state base. The best bodies are one instruction
short: 228/232 and 212/216 bytes, raw 0.9483 and 0.9444 respectively.
Batch `83cba88888e3475fb43591fc493e9ae5`, cells 1 and 9, preserve those
leads. The residual branch displacement follows that missing instruction.
Further char/u8 pointer views and array-address forms in batch
`583f8d96da1d431a8e2c2ab3b2ee1b5c` do not close it. No body was installed.
Next action: investigate the actual global state/byte-buffer type context
and compiler commoning; do not add duplicate loads with volatile or patches.

`func_8F802324`: **requeue**. Eight text-insertion loop/pointer forms in
batch `b4a9fffae941443aadcc15b2157c0e84` reject. Preserve the signed cursor
and byte loads, unsigned capacity, backward shift, and scalar cursor/capacity
aliases. Do not infer exactness from its best normalized score (~0.81);
read the complete diff before the next family. These are ordinary rejected
source experiments, not tool failures or a demonstrated compiler limitation.

## 2026-10-15: resource initialization and both digit requeues resolved

Four more owners are accepted, all `link_verified: true`, normal runner
statistics/host syntax checks enabled, with combined full-ROM gates:

- `func_8F8031F8`: 78 words / 312 bytes, frame 0x30. Batch
  `b2c99a4bb2584a04a816086d45d4d485`, winner
  `f77:init-global-base:pointer-loop-False:index-first-False:unsigned-False`.
- `func_8F8012C0`: 79 words / 316 bytes, frame 0x30. Batch
  `8cb1ac1d7a974e66b6c4106944749bc1`, winner
  `f77:resource-real-release-return:address-locals-False:count-False:unsigned-stride-False`.
- `func_8F8026DC`: 58 words / 232 bytes, frame 0x18. Batch
  `25d9de48759742538904675f3a6ce6be`, winner
  `f77:editor-union:10:word-field-False:cursor-False:post-loop-True`.
- `func_8F802A68`: 54 words / 216 bytes, frame 0x18. Same batch, winner
  `f77:editor-union:16:word-field-False:cursor-False:post-loop-True`.

The initializer must derive the selected-record pointer from the already
assigned `D_8F809FA8` global, not repeat the literal `D_8F803BF4` address.
The latter was one instruction short and changed the initial scheduling /
temporary allocation. Preserve the separate zero assignments, clock-output
addresses, fourteen 0x6F8-byte resource entries and final halfword return.

The resource reader initially had 76/79 exact words, with only v0/v1 for
the post-release `D_8F809FA4` address differing. The actual
`func_80062304` definition in `src/615D0.c` returns s32, not void. Retyping
its stale extern transactionally closes the mismatch and preserves the
existing writer. Keep the real byte count stores before their word-sized
copies, slot-dependent 6/30 capacities, 0x6F8 stride and 0x58 selection stride.
No unused-return fake or extra local is needed.

The digit initializer requeues above are resolved by declaring the shared
editor state as a union of halfword, word and byte storage views. This
models the existing overlapping accesses, allocates no storage, and leaves
all fixed addresses unchanged. Index the union byte view at `index+12`;
an explicit byte cursor still shares the initial address and misses one
instruction. Preserve the guarded do/while, signed remainder/division,
fresh post-call value read, and unsigned last-digit bound. The transaction
updates five accepted callers to their same halfword view and all retain
their exact words. The word-read cast remains as accepted; merely selecting
the union word member is a distinct compiler-shape experiment.

One initial union batch could not run: synthesized old externs made a
companion edit ambiguous. Explicitly declaring the intended union symbol
in the batch preamble resolved that setup failure. These pre-compiler
diagnostics are process evidence, not failed source hypotheses. Do not
change runner deduplication or replay rejected bodies to work around them.

Post-formatting and scoped extern deduplication, fresh/20-leading-blank
controls match all sections and all fourteen C definitions against the
original assembly baseline, including the old callers and all four new
owners. A fresh normal full-ROM gate passes MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Naming plan has no known mappings.
Exactly sixteen assembly owners remain in this file, including the text
insertion requeue; no unready jump-table owner was replaced here.
