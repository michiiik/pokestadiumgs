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
