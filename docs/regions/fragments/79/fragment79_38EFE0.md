# Region notes -- src/fragments/79/fragment79_38EFE0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-15

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-15

func_84123E74: plateau at 0.4706 (raw 0.1765), mismatch instruction_drift; tried families: state_field_access; tie-pool no


## 2026-09-19

func_841211CC: matched (state_field_access:branch_local_success:direct_field_baseline), 4 iterations, agent unbiased

## 2026-09-19

func_84122CCC: matched (state_field_access:permuter_replay:verbatim_zero_score), 5 iterations, agent unbiased

## 2026-09-19

func_8412391C: matched (call_chain:load_store_pipeline:next_step_before_pending_store), 2 iterations, agent unbiased

## 2026-09-19

func_84123034: matched (float_math:raw_offsets:u8_compound_assignments), 1 iterations, agent unbiased

## 2026-09-27

func_84122AB8: time cap at 0.9 (raw 0.4667) after 2400s, mismatch operand_or_scheduling_drift; tried families: bounded_lookup, state_field_access; tie-pool yes

## 2026-09-27

func_84122998: matched (call_sequence:void_ptr:local_rate_temp_inline_target), 1 iterations, agent claude

## 2026-10-23: terrain pose and rotated actor movement

Three runner-accepted owners add 752 code bytes / 188 MIPS instructions:

- `func_84122A0C` / `BattleAnim_UpdateTerrainPose` (108 bytes) samples
  terrain at the actor's X/Z position, adds the actor's height offset to
  the resulting Y position, and writes X rotation from the sampled slope.
  The slope is converted to `s16` before multiplying by 182. A direct
  `s32` conversion has the same opcode shape but different registers.
- `func_84122EEC` / `BattleAnim_InitSignedRotatedMotion` (328 bytes)
  initializes shared motion coefficients, copies the original translation
  and three-component rotation constants, substitutes the actor's Y
  rotation, and rotates a Z offset selected by `func_8411E1D4`'s sign.
  It clears both actor motion vectors and stores the negated rotated vector
  in the first. The direction helper's original argument is preserved.
- `func_84123150` / `BattleAnim_InitRotatedMotion` (316 bytes) uses its own
  translation/rotation constants and a Z offset of -50, initializes the
  shared coefficients, clears both motion vectors, writes the negated
  rotated result, and clears the actor's byte at offset 1571.

`func_84123034` consumes the shared coefficients and the vectors at actor
byte offsets 1508 and 1520 while advancing the actor position. The matrix
builder consumes all three components of the real six-byte rotation type;
its fields do not reserve artificial storage. The existing `S1_Vec3f` and
`S1_MtxF` types describe the other copied vectors and matrix.

The constant aggregate copies and matrix-first declaration order reproduce
both initializer frames. In the fixed-offset initializer,
reading the actor rotation before assigning the initial Z offset resolves
the final scheduling difference. The signed initializer needs the verified
`s32 func_8411E1D4(s32)` declaration; its definition is in
`src/fragments/79/fragment79_38D510.c`. Two older accepted callers,
`func_84121724` and `func_841217E4`, previously relied on implicit `int`
returns. Their new block declarations prevent a conflicting late prototype.
A declaration-only complete-module control preserves their existing bytes.

All three candidates report `link_verified: true` and pass the ordinary
host-syntax-enabled full-ROM gate. Successful artifacts are frozen
immediately. Independent checks preserve the complete helper module,
complete camera modules and their 332 original extents, the complete linked
fragment 79, semantic relocations, four collateral objects, external
SHA-256 hashes, and ROM MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
Original names remain aliases. Generated coverage and compiler tooling are
unchanged; no instruction rewriting, padding, artificial locals/fields,
forced allocation, or manual unrolling is introduced.

### Afterimage initializer requeue

`func_8412230C`: **requeue** after 24 native candidates. The two-record,
368-byte-stride walk and copied three-short table produce a 312-byte
candidate versus the original 316. The direct pointer walk reaches
normalized 0.9620 / raw 0.8228. A real consumed frame-index local improves
the normalized shape to 0.9873 / raw 0.8101. The original materializes the
table-copy address and loop iterator separately; the candidate coalesces
that address computation. Integer-count loops worsen the result; ordinary
struct/member/void address forms and initializer-versus-assignment copies
do not resolve it. No candidate is installed. Next action: investigate the
aggregate-copy/iterator lifetime with a calibrated compiler trace, retaining
all real flag writes, frame setup calls, and both records.
