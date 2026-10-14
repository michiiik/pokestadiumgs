# Region notes: fragment73_code

## 2026-10-15: fade-state handler and resource entry accepted

Solo native work, without containers or agents. Fresh-source and
20-leading-blank controls reproduce the complete object text and the already
accepted `func_8F500810` loop before probing. Normal runner statistics stay
enabled. Two owners are accepted with `link_verified: true`, one combined
full-ROM gate each, and default host syntax checking:

| Owner | Instructions / bytes | Frame | Accepted batch |
| --- | ---: | ---: | --- |
| `func_8F500774` | 39 / 156 | 0x20 | `c90add1063da4b5abd5b3b74ec901180` |
| `func_8F50086C` -> `fragment73_main` | 69 / 276 | 0x28 | `571768e3a4dd4cb4a7a1e24baa72a03c` |

The state-handler winner is
`f73:state:separate-init-False:state-selector-False:group-False`. Preserve the
incoming selector and a separate returned state. Mode 0 waits for fade mode
zero; mode 1 polls the existing input handler and starts the exit fade and
sound transition; mode 2 waits for fade mode one. No jump table is emitted.

The entry winner is `f73:entry:natural-call-group-0`. Preserve the actual two
incoming words, the saved configuration handle, pool tag 0x42474D50, segment
selection, resource setup, main loop and reverse cleanup sequence. The known
name comes from `gs_names.json`; the original address symbol is retained by
an alias. No argument, local, padding or compiler intervention was invented.

Post-cleanup fresh/blank controls reproduce complete text/data/rodata/bss and
all three accepted C functions, including the pre-existing frame loop.
Native full-ROM comparison passes, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Scratch recipes, probes, compiler output,
objects and ROMs remain local. The decomp-workbench command is unavailable;
existing runner diagnostics and calibrated controls are the fallback, not a
claim that workbench diagnostics ran.

### Unresolved handoffs

- `func_8F500020`: requeue. Eight cells model the actual 24-byte zeroed state
  record, camera/resource local order and initial store grouping. Best
  normalized 0.8088 / raw 0.3676; 244 bytes versus target 272, frame 0x30
  versus 0x28. The compiler retains a state base in s0 rather than the retail
  independent-symbol/shared-at addressing. The assembly includes shared-LUI
  stores with intervening instructions; no coalescer classification has yet
  been measured. Next: audit actual symbol/alias representation and classify
  those sites before choosing a different source family. Do not repeat the
  aggregate cells or claim an impossible compiler shape from this result.
- `func_8F500414`: requeue. Sixteen cells cover nested/merged animation guards,
  node pointer spelling, marker coordinate temporary, initialized consumed
  s16/s32 animation snapshots, declaration order and unsigned store view.
  Natural parent: normalized 0.9474 / raw 0.7895, correct 304-byte size and
  0x20 frame, but node stack home 0x1C instead of 0x18 and global-address
  commoning. Snapshot cells can recover the node home and reach normalized
  0.9605 / raw 0.6842, but do not close the address/scheduling residual.
  Next: inspect global expression ownership and alias representation, not
  more scalar spellings. Preserve both animation calls and reload globals
  after the first call. No failed declarations remain installed.
- `func_8F5002F4`: requeue. Sixteen cells cover advancing u8/u16 texture
  pointers, texture-load position, for/do loops, immutable base plus indexed
  source, real strip local and Y derived by division or shift. Best first
  family normalized 0.8125 / raw 0.4750; indexed family 0.8101 / 0.5443.
  Indexed parent is 316 versus target 288 bytes; both families retain a
  0x48 frame instead of 0x38. Next: inspect call-argument lifetimes and loop
  induction ownership. Preserve the first signed-halfword X load, second
  word X load and two texture calls per strip. Do not replay these families.

The remaining renderer and input handler have not been probed in this batch.
All five unresolved owners remain assembly. These are bounded negative
results, not exhaustion or impossibility claims.

## 2026-10-15: text-renderer follow-up after PR #948

`func_8F500130`: requeue. Twenty-four cells cover indexed/advancing label
tables, char/u8 buffer views, loop initialization, final conditional-expression
orientation, a real final string selector, the known state record and
initialized consumed text-result locals at each of three call sites. All
failed source and declarations are restored. The first family incorrectly
declared the unused result of `func_8004C594` as void; later families use its
actual s32 result. Do not interpret the first family as exhausting the
correct-prototype space.

The correct-prototype record/selector parent reaches normalized 0.9478 /
raw 0.7130, 460 bytes versus retail 452. A different loop-init parent reaches
normalized 0.9483 / raw 0.7069 but remains 464 bytes; it is not closer by
exact size or raw words. Frame size is already the correct 0x88. Direct
inspection of the retained parent shows six saved registers s0-s5 versus
retail five s0-s4, an extra saved base for the selected-row global across
the loop, another saved base for the alternate-row global after the loop,
and buffer offset 0x48 instead of 0x3C. Merely introducing real returned-text
locals does not remove those address webs. A final explicit selector local
also changes the target's short branch shape, so that separate topology
residual must not be mistaken for a register-only tie.

Next: capture calibrated optimizer address-web ownership/priority evidence
for the selected and alternate globals, preserving the natural two-row loop
and genuine 64-byte text buffer. Do not replay the 24 cells, invent stack
padding, force registers or call this compiler shape impossible. The input
handler remains unprobed. PR #948's two accepted owners have independently
passed public ROM-validation CI and merged; this follow-up adds no C match.

### Calibrated follow-up and input-handler handoff

Fresh stock, temporary diagnostic-off/on and 20-leading-blank builds reproduce
all object sections and all three accepted C siblings for the retained
correct-prototype text parent. The emitted optimizer listing is present:
the selected-state address web spans the loop and has adjusted save about
3.3333; the alternate-state address has adjusted save 0.5 across later calls.
Those constants are register-allocated, not merely different UGEN temporary
names. No diagnostic compiler or forced result is installed or accepted.

`func_8F500544`: requeue. Forty cells cover the actual first-four-halfword
state, record/array/separate-symbol views, snapshot widths, case order,
preincrement versus separate stores, initialized consumed signed delta
temporaries, and a mixed initial record snapshot with later independent
symbols plus a typed controller view. The plain aggregate/array families
reach normalized 0.6143 / raw 0.2071; separate scalars 0.5143 / 0.1214.
Explicit signed deltas improve the shape to 0.7071 / 0.2643, while the mixed
snapshot family reaches 0.7143 / 0.2286. These best deltas are 528 versus
target 560 bytes. None is a match and no failed declarations remain.

The assembly-derived draft independently confirms that clamp tests consume
signed halfword temporaries, not a stored-then-reloaded global; its inferred
three-argument sound calls and self-comparison are decompiler artifacts, not
adopted source. The existing one-word sound ABI and the genuine previous
selection snapshot are retained in the real trials. Current failures still
cache controller/state addresses and values differently from the target's
repeated direct-symbol reloads. Next: use the calibrated optimizer to
distinguish alias invalidation from address-code-motion ownership; do not
replay the forty cells or replace real prototypes with invented arguments.

The initializer/frame/background handoffs above remain active. No fragment
73 function is newly accepted in this follow-up; the next fresh batch moves
to fragment 74 while retaining these specific requeues.

The existing shared-LUI scanner now resolves both initializer groups and
classifies each as interleaved (`contiguous: false`): A8/AA/AC and B0/B4.
This confirms that the current contiguous-only coalescer is not applicable;
no new confirming source campaign or object rewriting was attempted. A
future source/alias representation hypothesis must account for that measured
instruction shape rather than repeating the aggregate trials above.

## 2026-10-15: text renderer and frame-wrapper requeues resolved

The clean mode-pointer spelling accepted in fragment 74 (#953) is confirmed
in a second source file. Both owners below now pass the normal native runner
with `accepted`, `link_verified: true`, one combined full-ROM gate each,
default host syntax checking and statistics enabled:

| Owner | Instructions / bytes | Frame | Accepted batch |
| --- | ---: | ---: | --- |
| `func_8F500130` | 113 / 452 | 0x88 | `555aaa8ae37f4c16b524378a4d0655c8` |
| `func_8F500414` | 76 / 304 | 0x20 | `3e29457e0df440f6ba4b761ee9887232` |

`func_8F500414` winner:
`f73:frame:field-pointers:first-True:inside-guard-False:alternate-False`.
A genuine s16 pointer to the animation field, declared before the actual
node pointer and initialized before the animation-finished guard, closes both
the global-address and node-home residual. No snapshot substitutes for a
global reload: both animation calls remain, and the second reads the current
animation field after the first call. The image query, display setup, text
and marker calls are unchanged. No extra marker local or alternate-field
pointer is needed.

`func_8F500130` winner: `f73:text:buffer-layout:before-mask-0110`.
Use one initialized, consumed field cursor for the row selection, then reuse
it for the alternate-entry metadata after the loop. Initialize the real row
table cursor before Y, and keep a consumed word-sized footer-entry local.
This closes the address webs and final conditional-expression schedule.
The resulting parent differs in only the buffer-address immediate. Moving
the existing Y and item declarations before the genuine 64-byte buffer
restores its exact 0x3C home without changing the already correct 0x88 frame.
No buffer resizing, third coordinate, padding or unused local is introduced.

The earlier first-family void declaration of `func_8004C594` is not retained;
the accepted source uses the actual s32 return type. All pointer locals are
initialized and dereferenced; mode values are not cached across helper calls.
The field-cursor spelling is now evidenced in both fragment 73 and fragment
74, but is a hypothesis to test on siblings, not permission to skip a gate.

Post-cleanup fresh and 20-leading-blank controls reproduce full
text/data/rodata/bss and all five C functions, including the previously
accepted state handler, loop and entry. Fresh native full-ROM comparison
passes retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. No tooling, compiler,
linker, data or object rewrite is included, and naming has no known mapping.
Only redundant declarations after accepted definitions are removed.

Three assembly owners remain: initializer `func_8F500020`, striped renderer
`func_8F5002F4`, and input handler `func_8F500544`. Preserve their scoped
handoffs above. The initializer's interleaved sites are not re-probed here;
the new pointer spelling is not proof that its layout prerequisite is solved.
For the input/background requeues, the next source-family hypothesis can now
use real field-cursor lifetimes rather than replaying old scalar spellings.
