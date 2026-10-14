# Region notes: fragment72_code

## 2026-10-14: func_8F400DE8 remains unmatched

One US/default-host-syntax ROM failure. Actual no-argument initializer clears 0x48 bytes, sets two halfwords, allocates through pointer-result func_80041C98(s32), loads two assets through canonical u8* func_8004BA70(s32), and calls real no-argument func_80041E2C. Separate scalar symbols preserve frame 0x18 and call sequence but produce repeated LUI instructions for the adjacent stores rather than the retail shared-LUI pairs; 39 instructions versus 35. Initial halfword constant/store scheduling also differs. An evidenced semantic aggregate/global-address model is needed before another trial. Do not repeat separate scalar or speculative grouped-field forms, and do not edit linker/data/tools to coalesce them.

History audit: No exact owner attempt or fragment72 region catalog note at fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed.

All failed sources, full build logs, and object disassemblies are retained in
`work/session-44`; each fresh baseline was restored. Open PR scopes were
checked for duplicate owner work. No CI, verification, linker, or data changes
were made. These attempts are failures, not claimed matches. The restored
186-owner workspace passes the US retail checksum with default host syntax
checks. Unknown tokens retain their existing address/offset names.

## 2026-10-15: thumbnail loop accepted; image-family handoffs

Solo native work; no containers or agents. Fresh-source and 20-leading-blank
controls reproduced the complete baseline text and accepted image helpers
before probes. The existing DE8 shared-LUI warning was read; that initializer
and the similarly shaped `func_8F4009A4` were not re-probed or modified.

`func_8F400B88` is accepted by normal batch
`ddda2f1b3b664161b507157e7dc4ed42`, winner
`f72:thumbnail:working-pointers:both-True:early-False:assign-False`:
32 instructions / 128 bytes, frame 0x28, `link_verified: true`, one combined
full-ROM gate with default host syntax checking. Keep unsigned-halfword X/Y
counters and separate working source/destination pointers. Each output pixel
calls the existing averaging helper with stride 160, advances the source four
pixels and destination one, then skips the remaining three source rows after
each 40-pixel output row. Both working pointers are initialized and consumed;
no dummy local or padding is added. Mutating the parameters directly leaves
the four-word prologue-scheduling residual (0.9375 raw); the two real working
pointers close it. Naming has no known mapping.

Post-cleanup fresh and 20-leading-blank controls reproduce all object sections
and all eight accepted C functions in this file. Fresh native full-ROM
comparison passes, retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. The averaging
helper and all other unsolved owners remain assembly. Failed candidate and
companion declarations have been restored; no new global-layout, alias or
compiler changes are included.

Bounded handoffs, not impossibility claims:

- `func_8F400A8C`: requeue. Twenty-four normal cells cover initialized channel
  sums, inline/separate result packing, indexed/advancing input, real stride
  preservation with sample-parameter reuse, signed/unsigned counters and loop
  topology. Ordinary pixel locals introduce an 8-byte frame; reusing the
  incoming stride parameter after saving its real pitch recovers the target
  252-byte frameless shape. Best normalized 0.9841 / raw 0.4921. The first
  retained-family difference is offset 0x18: target pitch in t1, actual t2;
  target row counter v0, actual t1, and loop bound t2 versus t3. Later masks
  and additions are also scheduled differently. Preserve the natural 4x4
  loops and alpha threshold >=5, not manual unrolling or a score-only body.
  Next: calibrated allocator evidence for the row-counter/return-value
  lifetime boundary and the unrolled channel expression schedule.
- `func_8F400C58`: requeue. Eight cells cover typed scalar globals, counter
  preincrement versus separate increment, actual frame-result temporaries
  and transition-line grouping. Best normalized 0.8100 / raw 0.4400, 400-byte
  body versus target 400, frame 0x18. Initial branch first differs at 0x10;
  later scalar-address commoning produces materialized bases and halfword
  reloads instead of the target's direct symbol stores/sign-extended counter.
  Next: audit the actual shared-state representation and alias model against
  the callers before another source campaign. Do not repeat these spellings.
- `func_8F401918`: requeue. Sixteen cells cover independent frame flags,
  switch versus if, declaration order, real object alias and live s16/s32
  countdown copies. Baseline 236 versus target 240 bytes, normalized 0.9500 /
  raw 0.5833, first mismatch at offset zero (a2 versus target t6 initial object
  load). Best normalized 0.9672 / raw 0.7049 instead grows to 244 bytes with a
  real s16 countdown and object copy. Next: separate the incoming mode-home
  and helper-call lifetime from the halfword-store/address-materialization
  residual. No variant is accepted, and neither score is a matching claim.

Scratch generators, retained probes and logs stay local and are not part of
the published game-source batch. The native decomp-workbench command is not
installed here; existing runner word diffs and calibrated fresh/blank controls
are the fallback, not a claim that workbench diagnostics ran.
