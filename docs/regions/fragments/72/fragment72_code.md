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

- `func_8F400A8C`: requeue at this batch boundary, resolved below. Twenty-four normal cells cover initialized channel
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

## 2026-10-15: averaging helper accepted after calibrated allocation diagnosis

`func_8F400A8C` is accepted in normal batch
`004277567c20412ab6ed249fdadcdc4f`, winner
`f72:average:direct-channel-loads:reverse-True:byte-stride-False:group-False`:
63 instructions / 252 bytes, frameless, `link_verified: true`, one combined
full-ROM gate with default host syntax checks. The prior requeue is resolved.

The accepted source reads each channel mask directly from `*image` and then
increments the pointer, rather than storing a pixel in a local or overwriting
the stride parameter. IDO shares the loads and unrolls the inner four-pixel
loop itself. Keep the four unsigned sums, real signed pitch, 4x4 loops, final
right shifts/masks, alpha coverage >=5 and u16 result. The existing u16/u16
caller ABI is retained; only its redundant declaration after the definition
is removed. There is no manual unroll, padding, dead local or register forcing.

Diagnosis before the winning batch:

- The retained u16-parameter-reuse parent and a word-input comparison parent
  each pass stock versus temporary diagnostic-off/on and 20-leading-blank
  controls for complete object sections and accepted siblings. Optimizer and
  UGEN listings are actually present, not just an enabled flag. Diagnostic
  objects are never acceptance evidence or installed compiler replacements.
- In the retained reuse parent, the optimizer gives the converted parameter
  value a separate live expression. The matching UGEN trace emits the copy
  into physical register 2 (`v0`), while the row counter uses physical 9 (`t1`)
  and pitch uses physical 10 (`t2`). This comes from emitter arguments and
  source-line alignment, not treating emission ordinals as final object rows.
- Eight explicit word-return/u16-packed-result cells leave the residual
  unchanged; return type is not the fix. Eight word-sized pixel-local cells
  introduce an 8-byte frame. Signed channel-sum cells also fail. Word-input
  normalization can improve the loop but loses the required incoming-home
  store and still assigns the counter/pitch/bound differently. All temporary
  prototype edits were restored, and none is adopted.
- Two generated word-input/pixel-local cells had an erroneous normalization
  substitution that reads an uninitialized pixel. They were rejected and are
  excluded from valid negative evidence, not offered as source hypotheses.
  They were never installed or accepted. Retained manifests identify them as
  indices 1 and 3 of that local word-input batch.
- A 90-second, four-worker native permuter run verifies exact base/probe and
  target/oracle instruction words before searching. Score improves 495 -> 40
  but never reaches zero. Its best reviewed mutation adds an initialized,
  consumed `unsigned int` pixel copy; that is a diagnostic clue, not an
  accepted body. Other outputs containing empty-condition scaffolding are
  not adoption candidates. The clean direct-load family then closes through
  the normal runner without any of those mutations.

Post-cleanup fresh/blank controls reproduce complete text/data/rodata/bss and
all nine accepted C functions in this file, including the thumbnail caller.
A fresh native full-ROM comparison is retail-identical, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Naming has no known mapping. No diagnostic
compiler, trace, scratch helper, object, ROM or tooling change is published.

### Preview renderer handoff

`func_8F401828`: requeue. Sixteen cells cover combined/nested guards, a real
index local, coordinate temporaries, pointer/word handle views and size-local
placement. The natural parent has 240 bytes and the correct 0x28 frame,
normalized 0.9500 / raw 0.3500. A real word-handle local fixes the initial
v0 load but only improves raw to 0.4500: the next mismatch is offset 0x14,
where the index load starts in t0 rather than target t6; dimension and
coordinate-register allocation and later scheduling also differ. No preview
body or handle declaration remains installed. Next: inspect index-expression
ownership and lifetimes across the signed quotient/remainder and display-list
setup before trying more surface spelling. Do not repeat these cells or
claim that byte count / normalized similarity is a match.
