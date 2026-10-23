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

## 2026-10-23: staged turning and two-state oscillation

Three runner-accepted owners add 1,188 code bytes / 297 MIPS instructions:

- `func_841212A0` / `BattleAnim_UpdateStagedTurn` (396 bytes) advances the
  actor's signed-byte stage count, performs the side-directed turn, and
  computes its later angle step from a wrapped progress fraction. Two real
  f32 locals preserve the integer-to-float rounding of the remaining angle
  and the double calculation `(131072.0 - remaining) / 131072.0`. The
  resulting f32 fraction is wrapped at 1.0, scaled by the original double
  coefficient, converted to s16, and clamped to at least 3640. It retains
  both direction-helper calls and the final facing-angle write. Multiplying
  the signed direction by 16384 reproduces the original narrowed shifts
  without left-shifting a negative C value.
- `func_84121920` / `BattleAnim_UpdateWideOscillation` (408 bytes) copies
  the original vector initializer, uses a two-case state switch, approaches
  amplitude 50 then 0, advances the phase by 3640, updates the actor's
  position, and calls the two-record follower `func_84120F5C` in each arm.
  The second arm retains its additional low-amplitude callback.
- `func_84123CF4` / `BattleAnim_UpdateTimedOscillation` (384 bytes) uses
  its own copied vector initializer, increments the first-state counter,
  approaches amplitude 0.6 at rate 0.4, and enters the second state after
  count 30. The two phase increments are 25486 and 16384. The second state
  approaches zero at rate 0.1 and retains the low-amplitude callback.

For both oscillation owners, a real f32 distance local declared before the
vector reproduces the frame and original vector-copy offsets. Writing the
amplitude before the sine-table factor in each multiplication resolves the
four swapped float-register instructions. Independent first-arm/second-arm
composition probes verify that both arms need that order. The switches
lower to the original short branches and emit no jump tables.

All three candidates report `link_verified: true` and pass the ordinary
host-syntax-enabled full-ROM gate. Successful artifacts are frozen
immediately. Independent verification preserves the complete helper module,
three complete camera modules and their 332 original function extents,
complete linked fragment 79, semantic relocations, four collateral objects,
external hashes, and ROM MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
Final pointer cleanup explicitly converts the byte field addresses to the
float-helper pointer type. Normal and leading-blank complete-module controls
preserve all game bytes and semantic relocations, followed by a fresh ROM
gate. Original names remain aliases. Coverage and compiler tooling are unchanged;
no instruction rewriting, padding, artificial storage/reads, forced
registers/frame/ABI, or manual unrolling is introduced.

### Damped-motion requeue

`func_841204BC`: **requeue** after 16 compiling source candidates. Its ABI
loads floating target/step values from the incoming word homes and narrows
the fourth argument as an angle. A read-only control corrects the two old
word-argument declarations and spells the callers' same IEEE-754 bits as
`1.45f, 0.015f` and `2.0f, 0.002f`; the complete module stays identical.
These interface changes are companion proposals only and remain uninstalled.
Initial companion preflight failures are tooling diagnostics, not hypotheses.

Real vector/scalar declaration order, velocity snapshots, named projections,
and forward-force expression order do not close it. The best opcode shape
is normalized 0.9286 / raw 0.4405 at 336 bytes; the strongest raw comparison
is normalized 0.9048 / raw 0.5952 at the same length and an 88-byte frame.
Declaring damping before previous speed corrects their stack homes; the
remaining first reported difference is byte 65. Next action: continue from
that real-local parent and inspect the post-call damping reload and force
expression scheduling. No float-interface repair or candidate body lands
without the candidate's successful full-ROM gate.

### Camera up-vector rotation requeue

`func_84121B18`: **requeue** after eight candidates. The original rotates
camera up about its normalized view direction using the sine/cosine tables,
then clamps negative actor height to zero. Separate real difference and
normalized-direction locals produce the original 404-byte length but a
64-byte frame versus 80, normalized 0.9109 / raw 0.6733. Reusing the input
components shortens the code to 372 bytes. Declaration order and the shared
Y product do not close it. Next action: recover the meaningful scalar
lifetimes for the normalized direction, double `1.0 - cosine` calculation,
and the three separately reloaded camera outputs. No frame padding or
uninitialized extra local is installed.

## 2026-10-23: actor movement setup/update dispatch

`func_84123F60` / `BattleAnim_InitMovementByType` and `func_84124104` /
`BattleAnim_UpdateMovementByType` each dispatch one actor to 23 handlers
selected by values 3 through 26, with 17 and out-of-range values doing nothing.
The shared actor sequencer in `fragment79_380A00.c` passes byte 1567 as the
selector, initializes on the trigger frame and calls the update dispatcher
on subsequent frames. The selected handlers include staged turning,
oscillation, terrain pose and rotated translation.

The original physical case order is 3-10, 13-15, 12, 16, 18-20, 11, 21-26.
Preserve the table-to-handler map rather than inferring it from function
addresses. Both dispatchers compile as ordinary switches with one call per
case and a common return.

Only the two 96-byte tables at ROM 0x3F95D0 and 0x3F9630 move into this
source's `.rodata` subsegment. The preceding float pool and large table
remain shared. The still-assembly layout was gated before replacing either
owner. Pinned splat 0.25.0 and spimdisasm commit
`fe1338434c99240eb4adca0b7860edc12b847565` produced the split.

Verification covers the normal host-syntax-enabled full-ROM comparison,
complete helper text and shared-rodata bytes, fixed-address relocation
destinations, the entire linked fragment 79 and four collateral objects.
Resolve the old object's two internal PC-relative fixups before comparing
unlinked text. The update function has 420 code bytes followed by eight
unchanged module-alignment zero bytes; the old assembly symbol includes
those bytes in its 428-byte extent. No source padding is needed.

The runner's combined install can place shared declarations after a prior
pending owner when a later owner gates sequentially first. This produced a
prototype-order compile failure for the setup switch. Gating the setup owner
against the accepted update owner with its own shared declarations resolves
the declaration scope without changing either handler's ABI.
