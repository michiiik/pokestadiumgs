# Record-selection trail buffers

## Accepted batch

- `func_82603B20`: advances a trail by the requested number of samples,
  wraps its index modulo 256, caps its retained sample count at 256, and
  marks it free when its current horizontal coordinate leaves
  `[-640, 1280]`. Accepted 592-byte body, label
  `trail:ring-index:index-origin-next:matrix`, with `link_verified: true`.
- `func_826040D8`: clears the 16552-byte effect state, enables it when
  resource 307 is available, sets its sample advance to 32, and marks all
  eight buffers free. Accepted 152-byte body, label
  `trail:init:index:direct:compare`.
- `func_826042A0`: loads resource 307 entry 2, establishes the display-list
  state, and draws all eight trails using that texture's width and height.
  Accepted 228-byte code body, label
  `trail:draw:texture-first:index:nested`. The containing object supplies
  the same twelve final zero alignment bytes as the assembly baseline.

The last two owners initially reported `link_verified: false` because the C
loop spells its endpoint as the start of the buffer array plus eight
records, while the assembly names `D_8261A488` separately. Both passed the
ordinary sequential full-ROM gate. Independent comparison resolved the
relocations to their absolute addresses and checked the linked fragment.
The initial link flag is not evidence of link verification.

## Source mechanisms

`func_82603A9C` scans records at a 2068-byte stride. `func_82603B20` uses a
256-entry ring of two-float points beginning at offset 20. These operations
establish the complete `RecordTrail` layout and its size assertion. The
existing `func_82603AD8` initializer now uses the same point and record types,
retaining its complete generated instructions.

The advance loop needs a distinct integer ring index shared by its two
coordinate stores. A point-pointer temporary introduces an extra address
addition in each compiler-unrolled iteration. Declaration order
`index`, `origin`, `next_index` also places the genuine origin snapshot at
the assembly's stack offset. The source contains a normal counted loop;
the compiler performs the observed unrolling.

The initialization and draw wrappers use integer-indexed eight-record loops.
The corresponding pointer-loop spellings had different register allocation.
No instruction rewriting, explicit padding, unused local, forced frame,
forced ABI argument, or forced register is required by the accepted bodies.

## Verification

The accepted installs each passed the normal repository candidate runner and
host-syntax-enabled full-ROM comparison. Each successful gate was frozen
before another compilation, including inputs, module object, all four other
fragment20 source objects, linked ELF, generated linker script and ROM.
External SHA-256 checks covered the frozen artifacts. Final cleanup repeated
the normal gate: US ROM MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.

Independent checks covered all game sections, resolved relocations, all
eight function positions and code extents, the complete linked fragment20,
and the four collateral objects. Final known-source and twenty-leading-blank
controls passed. A separate exact-delta export preserved the public lookup
implementation and passed original-public, exported-public, and
exported-public-plus-blank controls against the same complete-module oracle.
The native repository's 76 tests passed. Coverage was not edited.

Reconciliation with public master `2edb8be4` after PR #1444 found no changes
to this source file or the three accepted owners. The new definitions in
`fragment20_1286C0.c` and `fragment20_12C460.c` were preserved. All four
public collateral modules passed known/blank controls; address-literal versus
relocation differences in two modules were independently linked at their
measured addresses and matched the frozen fragment's bytes.

`fragment20_1286C0.c` has a pre-existing `void` declaration of
`func_826042A0`, while its assembly and accepted body return the enabled flag.
That caller discards the return value. A coordinated declaration-only cleanup
can use `extern s32 func_826042A0(void);`; it does not require changing the
newly merged `func_82600838` body.

## Requeue

- `func_82604170` (`register-tie`, 304 bytes): the closest genuine spelling
  has the correct frame and both point homes. A coherent temporary-register
  rotation remains at the random-angle mask and cosine lookup: expected
  `t5/t6/t7`, actual `t4/t5/t6`. The separate loop endpoint relocation also
  needs normal linked verification. Best normalized similarity is 1.0 and
  raw similarity 0.9342; neither is acceptance. Tested point representations,
  real-local ordering, typed global point copies, random-angle locals,
  lexical lifetimes, cosine-index expressions, and loop initialization
  placement. A calibrated sixty-second source search did not improve its
  score of 40. Next: inspect the temporary allocation/free events before
  `guRandom`, rather than introducing extra storage to rotate the pool.
- `func_82603A9C` (`requeue`, 60 bytes): the best ordinary three-local scan
  differs only in the order of the initial index-zero operation and the
  positive-count branch. Tested signedness, early returns versus break,
  pointer traversal, guarded initialization, preincrement placement, and
  small same-line groups. A calibrated sixty-second source search did not
  find an exact candidate. The public tree already has a C implementation;
  the export preserves it unchanged. Any cleanup of its unused alias needs
  independent matching evidence.
- `func_82603D70` (`requeue`, 872 bytes): still assembly and not probed in
  this batch. Its trail-point traversal, age-dependent alpha/scale, signed
  rounding, and textured rectangle call can now use the verified full record
  layout. Start with those operations; do not manually unroll the traversal.

## Coordinated integration names

The verified operations are named
`TrailEffect_Advance` (`func_82603B20`), `TrailEffect_Initialize` (`func_826040D8`), `TrailEffect_DrawAll` (`func_826042A0`).
The original names remain linker aliases. No other source implementation is replaced.
