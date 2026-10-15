# Fragment 29 archive and render state

## Accepted quadrant renderer

`func_88005390`: 225 instructions / 900 bytes, frame 0x80, accepted batch
`429d15a3887b45aa9a350afa59ffe09b`, label
`f29:quadrant-quotients:inline-x-True:inline-y-True:no-pointer-True`.
Normal native probe, `link_verified: true`, automatic combined full-ROM gate.

Preserve signed texture dimensions and half-size locals, sign-aware floating
rounding, all four texture quadrants, the negative edge/step values and the
SDK fill-rectangle handling of odd width/height. Inline the scale quotients
inside their rounded step expressions and read the texture header directly.
Named quotient/pointer locals reproduce all opcode shapes but change frame
or spill homes; inlining the final rounded steps instead duplicates work.

The native renderer consumes three arguments. The existing accepted wrapper
forwards an unused opaque fourth argument, whose bits must remain in its
original instructions. A three-argument K&R definition avoids an extra
incoming-a3 save. The host-only `CC_CHECK` signature represents the wrapper's
four-argument call, following the project's compatibility-shim convention;
the whole body is still syntax checked and no check is disabled. Remove the
redundant later forward declaration. Both renderer and wrapper instructions
are independently preserved.

A fresh re-split/rebuild exposed this caller-arity issue after the incremental
runner gate had accepted a cached object. Do not rely on that incremental
gate alone for host syntax acceptance: explicitly run the existing Makefile
`cc-check` target over the complete changed translation units, independent
of object timestamps, and force their ordinary object rebuild at handoff.
Both checks pass after the compatibility correction.

After formatting and duplicate cleanup, fresh and twenty-leading-blank
controls preserve every accepted object section, all three previous C bodies
and all six offsets. All four linked C spans and the full ROM match retail,
MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. Naming has no established mapping.
Two assembly owners remain in this source; no speculative body is installed.

### Requeue: full window/text rendering

`func_88005740`: requeue, sixteen scored source-shape cells, no accepted body.
Initial arrays, dimensions, SDK calls and staged double texture-size query
reach 1020 bytes versus a 1056-byte owner span, normalized 0.8598 / raw 0.5644,
frame 0x118 versus 0x110. The target's first row-height calculation has
separate `rows * 20` and `rows * 6` terms; collapsing it to `rows * 26`
changes the multiplication lowering. A named maximum-row value and those
separate terms raise normalized similarity to 0.9018 but yield 1100 bytes,
raw 0.5455. A named Y-array endpoint provokes loop versioning/unrolling,
unlike the target's simple three-element pointer loop; narrower declaration
scopes alone do not resolve it.

Preserve the 128-byte formatted-string buffer, four string pointers, four
byte row counts, three shared row Y positions plus the footer Y, the duplicate
texture-width queries, resource/setup calls and state-dependent text draws.
No trial arrays, globals or rounding helpers are installed. Next action:
recover the local aggregate/footer-Y boundary and loop topology, then inspect
the first allocation/layout divergence; do not repeat declaration-scope-only
or literal-26 variants.

### Native follow-up after PR #980

`func_88005740`: requeue, 48 additional scored cells (64 total), no C body
installed. The strongest complete-size candidate has normalized 0.9583,
raw 0.7652, 1056 bytes and the correct 0x110 frame. Its winning-family label
is `f29:window-height:late-False:cast-True:footer-False`; source-body SHA256
`8967c45ff11cc1e3f6eb1e1ecb1c3ee7fcddb1f1a8772c133526d5dee47d98fb`.
This is not acceptance: the size includes extra loop instructions instead
of the target's natural eight trailing zero bytes.

Reusing a word-sized local for the maximum-row calculation and the later
texture query reproduces the target's saved-register roles and avoids
keeping top in that register. A word-sized height assigned the explicitly
signed-halfword expression, plus a byte cursor for the Y loop, reproduces
the original string-array, row-array, formatted-buffer and Y-array offsets.
All original resource/font calls and both texture queries remain present.
The first mismatch moves past setup into the row cursor spill: expected
`sw v1,0x44(sp)`, actual `sw v1,0x5C(sp)`. Rectangle scalar homes still differ,
the Y endpoint is recomputed inside the loop, and temporary allocation /
scheduling differs in geometry and texture rounding. Do not pad this body
or call its same-size object a match.

Measured alternatives: separate footer and rectangle-array/struct spelling
alone do not repair the frame; merely splitting top into a draw-top local
does not close it. Reusing the row or string iterator removes a source
pointer but can introduce alias/copy instructions. A union or integer
carrier shared with the string iterator reaches no better raw score than
0.6932. Explicit state caching does not improve the best candidate. These
are negative findings for those measured source families, not a compiler
impossibility claim. No alternate callee ABI, speculative extra arguments,
forced compiler output or trial local aggregate is retained.

Next action: start with the complete-size candidate above and recover the
natural typed Y-loop/end boundary and declaration/carrier ownership of its
0x44 cursor spill and rectangle scalars. Inspect that narrow residual before
another source family; do not replay array/struct, scope-only or shared-scan
grids. Keep the still-assembly owner and all accepted siblings intact.

### Requeue: line-sensitive schedule and fixed scalar homes

The next native block adds 56 scored cells (120 total), still with no
accepted replacement. A natural source order, left assignment before top,
reaches normalized 0.9811. Declaring word-sized height before the three
signed-halfword geometry locals restores width/top/left at sp+0x106/0x108/
0x10A while retaining the 0x110 frame and the original arrays/buffer.

Token-identical line-group controls through the normal runner prove this
compiler's schedule is line-sensitive: joining the render phase or pairing
source lines reaches normalized 0.9886, raw 0.7614, 1052 bytes. The label is
`f29:window-line-groups:render-region-joined`, source-body SHA256
`77af84bcf265159d26e6123f89bb020f222aa703efd727a44de97da2b81adf05`.
This is a diagnostic schedule basin, not publishable exact C. The runner's
existing candidate-identity implementation already preserves logical line
groups, so no duplicate-filter bypass or tooling change is needed.

The cursor still spills at sp+0x5C rather than sp+0x44. The Y loop retains a
base copy and computes its endpoint inside the loop, unlike retail. It has
an extra real instruction and lacks the original natural alignment tail;
do not repair that with padding. Typed/void/union cursors and a three-row
plus-footer local record leave this basin unchanged. Naming the endpoint
through a separate pointer, the query word or the earlier string pointer
provokes loop versioning and a larger frame. Narrower cursor scopes combined
with a named footer-row count regress to 0x118, normalized at most 0.9886 /
raw 0.6970. Those are scoped negatives in this source/schedule basin.

Both 45-second stack-aware permuter imports reproduce the actual native
candidate and assembly target before searching. The first score improves
2829 to 1659 through a redundant top assignment; the natural reordered
source above keeps the useful scheduling insight without that duplicate.
The second improves 1678 to 788 through joined source lines and a one-shot
loop wrapper. No mutation is adopted. Another result narrows a display-list
opcode to a byte, which changes the program and is rejected regardless of
its score. The only tracked changes in this source campaign are these notes;
all four already-accepted sibling C bodies still reproduce their accepted
instruction words under a fresh normal compile.

At block expiry, resume with a materially different induction-variable /
allocation-web hypothesis for the cursor spill and Y endpoint. Preserve
the fixed scalar homes and line-sensitive schedule controls; do not replay
the cursor-type, local-record, endpoint-carrier or scope grids unchanged.

## Previous accepted native batch

| Owner | Role | Instructions / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_88004FF0` | select archive entry zero | 22 / 88 | 0x20 | `a85f1b77010e4faab0671c5da3b0c556` |
| `func_8800528C` | set render mode and environment color | 65 / 260 | 0x30 | `f43b4005aa834c68b09e329542383e01` |

Both are normal native accepts with `link_verified: true`, an automatic
combined full-ROM gate and one gate run apiece. Host checks and persistent
statistics remain enabled.

- Archive label: `f29:archive-select:reverse-False:group-False:unsigned-False`.
  Preserve the preparatory call, separate cases 0x3A then 0x3B, and entry-zero
  lookup. Grouping the cases or reversing their source order changes code.
  The original default path reads an untouched stack slot: do not invent
  a default entry or initialize the local merely to silence that pre-existing
  behavior. Only 0x3A/0x3B establish the entry index. The preparatory callee's
  existing K&R implementation consumes the word-sized archive argument;
  preserve the old-style caller declaration instead of inserting a u16 mask.
- Render label: `f29:render-state:nonzero-True:cached-False`.
  Use real SDK macros, append the common display list first, then branch on
  nonzero mode. Keep both exact render-mode words and environment colors.
  Query the animation inside `gDPSetEnvColor`, after the command pointer has
  advanced and its first word is stored. Eagerly caching the query or reversing
  the branch changes frame/allocation/order. The assembly query returns a
  signed halfword; this caller consumes the promoted word and masks its low
  byte. It only reads argument zero; no guessed extra arguments are passed.

Fresh and twenty-leading-blank builds after formatting/extern cleanup preserve
all accepted object sections, all six original offsets and the previous
44-byte accepted C wrapper. All three linked C spans and the entire ROM match
retail, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. Exactly two removed pragmas
have accepted, link-verified gate provenance. Naming has no established
mapping. Three assembly owners remained at that batch; no layout/tool changes
were installed.

## Requeue: animation envelope initialization

`func_88005048`: requeue. The original has eight frame-rate calls, preserves
four raw query results and three rounding offsets across later calls, and
retains zero-times-frame-rate floating arithmetic. Direct rounded call
arguments produce 548 bytes (target 580), normalized 0.6000 / raw 0.3586.
Explicit staged query/rounding locals reach 512 bytes, normalized 0.7241 /
raw 0.4621. Assembly inspection shows the native compiler folding literal
zero products and sharing their quotients, unlike retail. Changing the
helper's local prototype to old-style does not fix it and is not retained.

Word-sized zero/duration locals preserve the floating products and reach
584 bytes, normalized 0.7877 / raw 0.3836, but add integer-to-float conversions,
spills and a 0x60 frame rather than retail 0x50. Floating locals fold back to
512 bytes. Float multiplication operand order, rounding guard polarity,
ternary/if form, local order, shared rounding carrier, explicit constants and
denominator locals do not close these tested basins. No helper call is cached
away, and no failed body, experimental declaration or extra helper is installed.
An early constants generator accidentally rewrote a substring inside 40.0f;
those eight syntax failures are invalid generator cells, not compiler evidence.
The corrected eight-cell family is the scored constants result above.

Next action: investigate the authentic source/phase boundary that preserves
floating zero products without adding conversion/spill artifacts. Preserve
all eight calls and compare raw instructions; another width/rounding sweep
or accepting the m2c draft's spurious ninth argument is not justified.
