# Fragment 66 record reset, callback and scene setup

## 2026-10-14: three solo native full-ROM accepts

Review the older private region notes before scheduling:00700 has prior
instruction drift;01898's older probe-unavailable report was tooling evidence,
not proof that C cannot match;02508 had declaration-context failures;04734 had
an unreliable normalized match with very low raw agreement. Fresh controls first
reproduce matching callbacks/wrappers and the unchanged reset against the current
build,20-leading-blank recompiles and linked retail before new candidates run.

- `func_82E04734`:36 instructions /144 bytes, leaf. The table contains100
  twenty-byte records at D_82E05968, ending at D_82E06138. Each iteration clears
  word0, sets word4 from D_82E05948, writes word8 as old word16 minus D_82E0594C
  and copies old word16 to word12; word16 is unchanged. Direct array indexing
  lets IDO perform the original four-record unroll. Pointer loops and explicit
  cached globals are controls, not winners. The object hit has a different
  end-address relocation; link_verified=false. Gate that existing unverified hit
  sequentially through the normal runner: accepted after24 prior probes,
  5.422s probes /1.856s gate /7.282s total. The full ROM, not masking, proves it.
- `func_82E01898`:70 instructions /280 bytes, leaf. Preserve kind0/1 dispatch,
  both big-endian byte-pair values, conditional5/6 adjustment, the second value's
  unchanged high byte plus scaled low byte, flag-bit0 clearing and return0.
  Scalar numerator/denominator reuse reproduces the runtime division checks;
  swapping the second sum's operand demand fixes its temporary-register cycle.
  Explicit extra stage temporaries do not close it. Accepted after16 prior probes,
  link_verified=true,5.212s probes /1.078s combined gate /6.292s total.
- `func_82E02508`:84 instructions /336 bytes,0x28 frame. Preserve mode query,
  flag, pool state, all three graph loaders, allocation finalization, three
  320x240 views, renderer/node initialization, data-state push, post-incremented
  counter and the final0x52 call. The old prototype declared main_pool_push_state
  void, but its accepted definition in src/3280.c returns s32. Atomic prototype
  correction with the candidate fixes the four-register-word residual after
  that call. Both existing callers in02658 retain their bytes. Accepted after
  eight prior probes, link_verified=true,5.525s probes /1.231s combined gate /
  6.759s total. This is actual ABI evidence, not an invented return-category trick.

Cleanup removes an unused input-record type and redundant declarations, retains
the actual view-state/table types and keeps the real pool-return prototype.
Naming plan has no existing evidence-backed names for these three owners.
Full native COMPARE=1 retains MD51561c75d11cedf356a8ddb1a4a5f9d5d; all427 host
syntax checks pass. Fresh-source/build/blank comparisons match the entire file's
.text and individual accepted/sibling functions, including464-byte02658; all
new linked retail spans match. No compiler patch, new helper function, header,
data subsegment or linker change is needed. Scratch stays local.

## Remaining coordinate callback requeue

`func_82E00700` stays GLOBAL_ASM:60 instructions /240 bytes. Sixteen new probes
test raw/typed event and state views, switch/guard/nested-if topology and real
early returns. Best new normalized0.8500/raw0.6333 has232 bytes; old private
notes had0.8667/0.7667. Preserve both kind and selector dispatches, coordinate
updates, conditional scaling and flag clearing. Do not invent eight padding
bytes: the oracle has real duplicated/scheduled case loads and control transfers.
Next action is a calibrated control-flow/statement-line discriminator on the
closest complete body, not more record-field typing or arbitrary guards.

## 2026-10-14: coordinate requeue resolved and scissored overlay accepted

`func_82E00700` now has a normal sequential full-ROM acceptance:60 instructions
/240 bytes, leaf. Fresh instruction inspection disproves padding as the missing
size:the original first stores the byte-pair width through the direct label,
materializes the coordinate base later, and reloads width before scaling.
One unified typed view lets IDO cache width and hoist its address. Eight address
variants and a calibrated scalar-declaration control retain that mismatch.
Eight explicit volatile-access diagnostic variants recover the reload but not
the separate address setup; they are not installed.

An explicit structured linker alias, `D_82E06138_view = D_82E06138`, expresses
the overlapping access view without allocating storage. Direct first-store
access plus this view for coordinate stores and the conditional width reload
reproduces all60 instruction words apart from equivalent relocation spelling.
No volatile access, invented padding, extra function, guard or compiler patch.
The alias-only baseline first passes COMPARE=1; the existing unverified probe
hit then passes the normal sequential gate. link_verified=false due solely to
the alias relocation target, so the full ROM is the acceptance oracle, not the
object comparison. Gate after40 prior probes:4.840s probe /1.745s gate /
6.588s total. This resolves the prior coordinate requeue above; it does not
claim the original source used these particular names.

`func_82E02F00`:108 instructions /432 bytes, leaf. Existing prototype requires
u8 opacity; the initial s32 draft's compile failure is declaration evidence,
not a scored hypothesis. Use gSPDisplayList, gDPSetEnvColor with255-opacity,
and gSPScisTextureRectangle for the shifted320x240 rectangle and clipped
texture coordinates. The ordinary literal/shift spelling accepts with
link_verified=true and a combined full-ROM gate:6.251s probe /1.394s gate /
7.648s total. No manual command-word stores or helper functions.

The adjacent renderers remain GLOBAL_ASM, with durable requeues:

- `func_82E02AA4`:128 instructions /512 bytes,0x40 frame. Correct RGBA16
  load-block macros and16x16 rectangles cover the320x240 image, advancing
  its pointer by512 bytes. Literal-only bounds spill heavily; named width /
  height plus y-before-x locals gives normalized1.0/raw0.9141 at exact size
  and frame. Remaining differences rotate the row-coordinate s1/s2 webs and
  inner x counter t3/t4. Explicit row temporaries, next-X reuse and eight
  declaration orders do not close it. A stock-native90-second permuter is
  calibrated with base/probe and target/oracle instruction identity; score
 455 ->75, no zero. Its best expanded source wraps commands in a do/while(0)
  group; do not publish that diagnostic scaffold or flattened command words.
  Next action:measure the row-web demand/scope mechanism and translate any
  useful result back to ordinary GBI macro source, then re-probe and gate.
- `func_82E02CCC`:121 instructions /484 bytes,0x30 frame. RGBA16 load-tile
  macros draw320x6 strips across240 rows, advancing3840 bytes per strip.
  Named bounds and explicit next-row reuse reach normalized1.0/raw0.9091 at
  exact size/frame. Signed/unsigned narrow coordinate carriers and operand
  order do not improve it. Next action:calibrate a bounded search from the
  complete best body, focusing on horizontal-coordinate and counter webs,
  not more literal-vs-local or narrow-coordinate variants.

Scratch generators, permuter output and diagnostic objects remain local.
Final cleanup removes the new redundant display-list-pointer declaration.
The naming plan has no independent existing mappings for either new owner.
Native COMPARE=1 retains MD51561c75d11cedf356a8ddb1a4a5f9d5d; all427 host
syntax checks pass. Fresh final-source/build/20-leading-blank controls agree
across the entire file's .text, both new functions and all selected siblings.
Both new linked retail spans match; git diff --check passes. The two alias
symbols resolve to the same linked address. No generated tools or artifacts
are part of the change; project-wide decompilation remains unfinished.

## 2026-10-14: renderer requeue discriminators

The final source/build/20-leading-blank baseline still reproduces the entire
file's .text and all selected accepted siblings before new work.

`func_82E02AA4` requeue:the original complete macro body,20-leading-blank
control, two macro invocations on one line, plain block grouping, do/while(0)
grouping, and both grouping forms on one line all retain512 bytes and the
normalized1.0/raw0.9141 residual. Putting the entire function on one line is
worse:0.9219/0.8203. This falsifies simple call-line/grouping as the source of
the earlier flattened permuter score gain; it does not exhaust arbitrary
statement layouts or compiler pass behavior. The flattened winner is still
diagnostic-only. Eight new unsigned-corner/multiply spellings retain the best
residual or worsen allocation, and eight narrow-counter variants add real
instructions or enlarge the frame. Do not requeue these same families.
Next action:inspect the exact expanded-parent/winner expression-tree and
compiler-context difference, or capture narrow row-web allocation evidence;
keep the ordinary macro spelling as the maintainable baseline.

`func_82E02CCC` requeue:eight explicit loop-limit/right-edge carrier and
formal-counter variants do not improve the previous1.0/0.9091 full body.
The best of that new family is0.9835/0.8017. A stock-native90-second search
is first calibrated with identical base/probe and target/oracle instruction
words at484 bytes, then improves permuter score350 ->190 without zero.
All output is retained locally and remains uninstalled. Next action:review
the best mutation for valid source changes and separate expression topology
from mere flattened source layout before composing a new ordinary-macro
family. Both renderer owners remain GLOBAL_ASM, and tracked game source is
unchanged throughout these negative experiments.

Next file-local layout work:`func_82E017E0` and `func_82E04040` use five- and
eleven-entry jump tables respectively; `func_82E0424C` shares the same nearby
read-only region. The YAML still places those tables in fragment66_data.data.
Before probing C switches, derive the per-file .rodata range, re-split with
the pinned toolchain and gate all three still-assembly owners. This is a
layout prerequisite, not permission to try switches against the current blob.
