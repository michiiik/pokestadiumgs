# Region notes: fragment74_code

## 2026-10-15: texture strips and background renderer accepted

Solo native work, without agents or containers. Fresh and 20-leading-blank
controls first reproduce full object sections and the four existing C
functions. No earlier local owner attempts or live file claim were present;
open PR scopes did not overlap this file.

| Owner | Instructions / bytes | Frame | Accepted batch |
| --- | ---: | ---: | --- |
| `func_8F6000EC` | 68 / 272 | 0x58 | `acbd75e59c654b14b6fd9da7fb4c69c6` |
| `func_8F6001FC` | 36 / 144 | 0x30 | `8a3e971ee8e44598b035dcb14edd964f` |

Both normal runner results are `accepted`, `link_verified: true`, with one
combined full-ROM gate each, statistics enabled and default host syntax
checks. Naming has no known mapping; retain the address-keyed names.

### Texture helper

Winner `f74:texture-strips:initialization-schedule:cell-0`. Preserve the null
guard, two 64-row strips, 0x1000-byte pixel advance, original image header
loads, doubled width and 512 texture steps. All locals are initialized and
consumed. Keep the signed X conversion before pixel acquisition, and
initialize the offset before the working Y coordinate.

The actual accepted `func_80044270` definition takes eight signed halfwords
and a word. An initial all-word trial prototype suppresses the target's
second X conversion; those cells are not evidence that the correct ABI is
exhausted. Correcting that prototype and ordering offset before Y reaches
0.9853 raw/normalized with just initialization scheduling left. Moving the
X conversion before pixel acquisition then closes through the normal runner.

Source line grouping is measured here: expanding the three setup statements
onto separate physical lines changes three instruction positions in the
initialization schedule and fails the retail checksum. Restoring the compact
setup grouping restores all object sections and the full-ROM match. The
comment explains why it is retained. This is ordinary source formatting,
not a line directive, compiler patch or register force.

### Background renderer

Winner
`f74:background:postinc:cursor-False:packet-advance-False:pair-first-False`.
Use a genuine function-scope `Gfx* packet` before the real two-halfword
coordinate pair; assign it from the display-list cursor's post-increment,
then emit the command through it. The cursor view preserves the existing
u8-array declaration used by the already accepted frame wrapper. The helper
conditionally draws the enlarged texture, converts coordinates using the
existing helper, and draws the normal-size image.

An inline macro-only form puts the coordinate pair at 0x2C instead of 0x28.
A packet local with separate load/update has the right stack home but swaps
the initial pointer registers. The post-increment assignment closes both.
No third coordinate, unused local, padding or data-layout change is added.

### Verification and unresolved owners

Post-cleanup fresh and blank controls reproduce text/data/rodata/bss and all
six accepted C functions. Native `gmake rom COMPARE=1 -j2` passes, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. The existing entry's asset-array pointer
warnings predate this batch. No failed source or declaration remains.

- `func_8F6009F0`: requeue. Twenty-four cells cover switch/if dispatch,
  actual next-state local, repeat-flag placement, byte-mode snapshots,
  known overlapping halfword/byte views, outer-loop spelling and the
  assembly-supported byte formals of `func_800082E0`. Best normalized
  0.9420 / raw 0.7681, 276 versus target 264 bytes, correct 0x38 frame.
  Direct instruction inspection shows an extra saved s5 holding the mode
  global's address across the outer loop; the actual state-dispatch core
  already agrees. Next: calibrated optimizer address-web ownership/priority
  evidence, not another replay of these cells. No variant is accepted.
- `func_8F600020`: tooling-blocked for the existing contiguous-only shared-LUI
  mechanism. The repository scanner resolves three same-page shared-at runs
  and classifies all as interleaved: BF4/BF0, BF8/BFE and C00/C02/C06/C04.
  No candidate is probed and no aggregate or object rewrite is installed.
- `func_8F60051C`: tooling-blocked for the same mechanism. Scanner resolves
  the C00/C02 shared-at stores and reports `contiguous: false`. No candidate
  is probed. These classifications concern the existing coalescer's limits,
  not a proof that no authentic source representation can match.

The text renderer and input handler are unprobed in this batch. All five
unresolved owners remain assembly. Scratch recipes, traces, controls,
compiler binaries, objects and ROMs stay local; none is published. The
decomp-workbench executable is unavailable, so repository runner diagnostics
and explicit controls are used instead; unavailable commands are not claimed
as run. Generated coverage remains with the repository workflow.

## Follow-up while PR #952 validates

`func_8F6009F0` remains a requeue. Eight additional cells introduce an
initialized, consumed configuration handle between creation and activation,
vary the real next-state local, move repeat initialization to the outer
loop, and put the switch default before the named cases. The handle local
does not remove the extra mode-address register: best remains normalized
0.9420 / raw 0.7681, 276 versus 264 bytes. Outer repeat initialization makes
the dispatch worse (0.8551 / 0.5652). No source/declaration is installed.
These are now 32 recorded loop cells. Next remains calibrated address-web
diagnosis; do not replay the handle/default/repeat family. The two display
owners published in #952 are unaffected by this rejected follow-up.

## 2026-10-15: text renderer and display-loop requeues resolved

PR #952 independently passes public ROM-validation CI and merges before this
follow-up. Two more owners now pass the normal runner with statistics and
default host syntax checking, each `accepted`, `link_verified: true` and one
combined full-ROM gate:

| Owner | Instructions / bytes | Frame | Accepted batch |
| --- | ---: | ---: | --- |
| `func_8F60028C` | 146 / 584 | 0x50 | `6409414fd0ee4af597d40fbdc0adbf5e` |
| `func_8F6009F0` | 66 / 264 | 0x38 | `f24c5836fc1d49a4868f777f9a222fd0` |

### Measured address-lifetime diagnosis

The retained loop parent passes fresh stock, temporary diagnostic-off/on and
20-leading-blank controls: complete sections and all six already accepted C
siblings agree. Its actual optimizer listing assigns the mode-address
constant web to internal register 19 (the observed s5) with adjusted save
about 1.6667. This is address code motion/global allocation, not a UGEN
temporary-name tie. The first diagnostic draft omitted forward declarations;
it failed compilation, then was corrected to use the runner's exact
declaration augmentation before the passing controls. That failed setup is
not code-generation evidence.

Eight halfword-value-to-byte-formal cells and eight qualified byte/halfword
sampling cells leave that loop residual unchanged. Volatile views are not
installed. No duplicate source body is replayed for those experiments.

The initial text family reaches the right 584-byte size, normalized 0.9932 /
raw 0.8699, but has a 0x48 frame and coordinate pair at 0x38 instead of 0x40.
A real, consumed word-sized font local assigned from each conditional
expression restores the 0x50 frame and coordinate home, improving raw to
0.9726; its remaining differences are in the two mode loads. Separate branch
calls, formatted-argument locals and narrow font variants do not close it.

A scratch-only visibility test compares an external declaration, tentative
definition and initialized definition of the mode halfword. All produce
identical complete text and accepted coordinate-helper words; each also
passes a blank-line control. The initialized cell adds data, never goes
through installation and is not a source candidate. This excludes those
tested declaration forms as the cause; it does not justify moving data or
changing the compiler.

### Clean source explanation

A bounded 90-second, four-worker native permuter search passes exact
base/probe and target/oracle word controls before searching. Score improves
225 -> 55 without reaching zero. Its reviewed best change adds an initialized,
consumed pointer to the mode halfword and dereferences it at the same two
font-selection sites. It adds no data read, write, guard or argument. This is
a source-lifetime clue, not a matching claim or directly adopted mutation.

Normal source families then discriminate the stack and register effects:
reusing the label cursor preserves the coordinate home but swaps loop
registers; a dedicated mode pointer before the pair puts it at 0x3C. Keeping
that real pointer after the real two-halfword coordinate pair closes the
text renderer with one consumed font word. Winner:
`f74:text:pointer-layout:position-1:split-font-False:decl-init-False`.
The earlier inline/global forms and their LDA web need not be retained.

The same source hypothesis immediately closes the display loop: initialize
an actual s8 pointer to the observed mode byte before entering the outer
pool loop, then dereference it when creating each display configuration.
The value is not cached across iterations. The extra saved address register
disappears through the normal compiler. Winner:
`f74:display-loop:mode-pointer:halfword-False:inside-outer-False:pointer-first-False`.
Initializing the pointer inside the loop does not close the residual. Keep
the existing state 3 reset/restart and state 4 exit, pool tag, fade sequence,
frame callbacks and cleanup unchanged.

All added locals are initialized and consumed. Neither function has padding,
an unused local, extra coordinate, volatile view, fake argument, line
directive, forced register or object rewrite. Naming has no known mapping.
Post-cleanup fresh/blank controls reproduce all sections and all eight C
functions, and a fresh native full-ROM comparison passes retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Diagnostic artifacts stay local.

### Remaining owners

The input handler `func_8F600610` is also scanned without probing: its
BF8/BFC shared-at stores resolve to one page but are interleaved. Together
with the initializer and texture-update sites above, these are the three
remaining assembly owners. The existing contiguous-only coalescer does not
cover these measured sites. Their source/alias or tooling prerequisites are
not resolved here; no impossibility claim or tool change is made.
