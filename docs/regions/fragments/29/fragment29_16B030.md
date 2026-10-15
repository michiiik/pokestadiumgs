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
