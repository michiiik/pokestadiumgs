# Fragment 50 motion and CPU input selection

## 2026-10-24 accepted owners

| Original owner | Name | Instruction bytes |
| --- | --- | ---: |
| `func_862067B4` | `SceneMotion_ComputeNearbyDirection` | 364 |
| `func_86206C34` | `SceneInput_AdvanceSelectionPhase` | 236 |
| `func_86206D20` | `SceneInput_UpdateCpuSelection` | 472 |

The three owners replace 1072 instruction bytes. The existing paired-value
swap remains C; three other owners remain assembly as described below.
Backward aliases retain the original entry names.

### Nearby direction calculation

`func_86206920` supplies an origin and indexed direction from `D_86208F28`,
an object from the list at context offset 384, and a three-float stack output.
`SceneMotion_ComputeNearbyDirection` computes a displaced point using the
supplied direction, context floats at offsets 204 and 216, and base position
`D_862090C0`. It subtracts that point from the object's position at offset 72
and normalizes the result through `func_87D005E8`, which returns its original
length. Below a strict scale-dependent distance threshold, it applies the
directional/upward terms implemented by `func_8620573C` and returns 1;
otherwise it clears all three output components and returns 0. The threshold
uses a float at metadata offset 52, with metadata read from object offset 32.
//@src/fragments/50/fragment50_26BF40.c
//@src/fragments/65/fragment65_code.c

All three predicted coordinates are read before output stores. Scalar
coordinate locals preceding the metadata pointer reproduce the original
48-byte frame. The X/Z addition order and the threshold's final multiplication
order preserve the original arithmetic grouping and float temporary order.
`speed_scale = 5.0f; speed_scale *= context_value;` reproduces the last two
load destinations. Accepted runner label:
`cpu-contact-scale-load:factor-then-multiply:speed-first`.

### Timed selection and CPU policy

`SceneInput_AdvanceSelectionPhase` operates on the 24-byte record at context
offset `474044 + index * 24`. It retains the signed button mask at record
offset 16 and dispatches the byte at offset 19:

- Phase 0 advances to phase 1 and clears the counter when the counter at
  offset 8 is strictly greater than the entry delay.
- Phase 1 calls `func_86206920(index, rank, threshold)`. A nonzero mask moves
  to phase 2 and clears the counter; a zero result clears the returned mask.
- Phase 2 adds `0x4000`, returns to phase 0 and clears the counter when the
  counter is strictly greater than the release delay.

The selector's 16-bit return contract is supported by a normal-compiler
call-site control: narrowing and testing an s16-returning callee reproduces
the original branch on v0, whereas an s32 declaration inserts another test
carrier. Assigning directly to the retained mask reproduces the original
return/state-pointer reload schedule. Accepted runner label:
`input-three-state-return-carrier:direct`.

`SceneInput_UpdateCpuSelection` supplies the phase machine's parameters from
the difficulty word at record offset 12:

| Difficulty | Entry delay | Rank | Threshold | Release delay |
| --- | --- | --- | --- | --- |
| 0 | 40 through 80 | 0 through 2 | 0 | 0 through 30 |
| 1 | 17 through 34 | 0 or 1 | 0.7 | 0 through 12 |
| 2 | 15 through 30 | 0 | 0.85 | 0 through 5 |
| 3 | 12 through 24 | 0 | 0.9 | 0 through 3 |

Every difficulty consumes three random draws, including the fixed-rank
cases. Omitting those two discarded rank draws changed both the instruction
sequence and subsequent RNG state. After the phase update, this owner
increments the counter and stores the returned mask with `0x4000` cleared,
while returning the complete mask to its caller.

`func_862026C8` supplies difficulty values by choosing one of the four ROM
profiles referenced by `D_862090A8` through `D_862090B4`, shuffling its entries,
and copying them to CPU records. The profile words at `D_86209068` through
`D_862090A4` are all in the range 0 through 3. The recovered updater preserves
the original switch over those four codes. Accepted runner label:
`cpu-input-policy:buttons-first:difficulty-record:counter-post:preserve-rank-rng`.

### Float-pool ownership and hook interfaces

The thresholds 0.7f, 0.85f and 0.9f occupy the original range at ROM
`0x274B70` through `0x274B7F`, VRAM `0x8620E130` through `0x8620E13F`.
The per-file `.rodata` subsegment recovers these 12 constant bytes and their
4 natural alignment bytes. Its original assembly owner passed the normal
ROM gate after the layout split and before its C replacement. The six
HI16/LO16 references now target local `.rodata` offsets 0, 4 and 8 at the
same linked addresses.

For this layout edit, a cached split regenerated only 17 undefined data
symbols and caused unrelated link failures. A full split with the pinned
splat/spimdisasm regenerated the complete set and passed the ROM gate.
Use a full split for this layout, before interpreting any candidate result.

The sole caller `func_862070B0` establishes the arguments to two existing
empty hooks in `fragment50_26BF40.c`: `func_86205724` receives the player
index; `func_8620572C` receives that index, the selected origin pointer and
selected direction pointer. Their declarations now express those roles.
Their containing module is byte-identical before and after the type cleanup;
their argument counts and word representations are preserved.

### Verification

Accepted owners have native runner provenance and passed ordinary
`make COMPARE=1 RUN_CC_CHECK=1` gates. The US retail ROM MD5 is
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Final names, shared declarations and the
RNG comment are gated again. Complete-module comparison covers all seven
function extents, text and semantic relocation targets. Independent aggregate
comparison reconstructs the original shared data blob from its prefix, both
recovered float pools and relocation-record tail. Linked fragments 50 and 79,
332 existing function extents, four collateral objects and foreign-file
hashes remain unchanged. Private probes, searches and compiler binaries are
excluded from the public change.

## Remaining owners

### `func_86206920`: requeue

The five-choice scoring, shuffle and descending bubble-sort reconstruction
reaches the original 788-byte extent and opcode sequence. Explicit parallel
array cursors retain its outer counter. Simple candidates use a 208-byte
frame instead of 224. Eight calibrated logging controls cover the matching
helper and retained selector, each stock/off/on/leading-blank, and preserve
complete modules. The selector trace measures 72 saved-register bytes,
16 argument-area bytes and 120 local-area bytes. Aggregate zero initializers
introduce copying/data and are rejected; enlarging arrays or adding padding
is unsupported.

A calibrated 90-second source search improves local score 867 to 253, but its
best proposal adds an artificial constant-offset carrier and is rejected.
Useful extracted hypotheses concern the indexed-context address and the
choice slot passed to the swap. Locals for the actual object weight and
unweighted dot product recover the 224-byte frame. Moving the sort-slot
pointer below the result declaration recovers the original stack homes. The
retained candidate matches its first 47 words before context-address
allocation diverges at byte 188 (normalized 1.0, raw 0.7919).
Next action: trace that indexed-context web and the dot/weighted-score float
coalescing, then compose the measured mechanisms with the earlier simple
scoring form. Keep the evidenced s16 selector return contract.

### `func_86206EF8`: requeue

The mode decoder reads current buttons at controller offset 6, newly pressed
buttons at offset 8, and a latch at player-record offset 20. Modes cover
latched cardinal/diagonal selection, direct pressed buttons, held-direction
priority plus an action pulse, and action-only input. The controller producer
`func_80005F0C` establishes the signed port/stick fields at offsets 0, 2 and 4
and the two unsigned button fields; a 10-byte prefix view was tested without
inventing preceding fields.

Return layout, case order, mask caching/width, byte/halfword views and the
proven controller prefix do not repair the initial parameter-lifetime
residual: candidates copy a1 to a2 at byte 8, while the original initializes
v1 there. No decoder body is installed. Next action: inspect the compiler's
parameter and latched-mask global-color decisions and case CFG before another
source spelling campaign. The decoded bit-priority chains are retained in
private drafts and the original assembly remains authoritative.

### `func_862070B0`: requeue

The player dispatcher walks four 24-byte input records and four 40-byte
controller records, scans five 64-byte input choices, and dispatches the
selected vectors or action pulse according to the context mode. Candidate
frames are the correct 64 bytes; the original final zero word is natural
alignment. The best ordinary source has raw similarity 0.7931. Its first
register difference is the context reload at byte 92, with the table's high
half allocated to v1 rather than the original assembler temporary. Pointer
initialization, field signedness and byte/float table views do not repair it.

A calibrated 90-second source search improves score 150 to 145 only by
assigning `buttons & 0x4000` to an 8-bit selector, which erases the mode-3
call. That proposal is semantically invalid and is rejected. Next action:
trace the table-address high-half web against the original dependency order;
retain the proven hook signatures and every mode-specific call.
