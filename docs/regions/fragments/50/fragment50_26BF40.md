# Fragment 50 motion/model helpers

## 2026-10-24: verified rodata ownership

The repository's `add_rodata_subsegments.py --disasm . for-jtbl
jtbl_8620E104` attributes the aligned ROM range `0x274B40..0x274B70` to this
source file. It contains:

- `D_8620E100`: 0.4f at ROM `0x274B40`.
- `jtbl_8620E104`: seven model-state dispatch entries at ROM `0x274B44`.
- `D_8620E120`: 0.31f at ROM `0x274B60`, followed by 12 natural alignment bytes.

The per-file `.rodata` subsegment precedes the already-recovered CPU threshold
and paired-model pools. The existing linker script already enumerates this
file's `.rodata`, so the tracked layout delta is one YAML line. A full pinned
splat/spimdisasm split was used, without the cached-split option that previously
dropped unrelated undefined symbols. The original assembly owners were gated
before trying C against the recovered pool.

### Verification

The normal host-syntax-enabled ROM build remains byte-identical, US MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Immediately frozen inputs, objects, ELF and
ROM have externally checked hashes. Independent comparison preserves all
4752 text bytes and 17 function extents. Exactly six HI16/LO16 references
change from external pool symbols to local offsets 0, 4 and 32.

All seven table relocations resolve to the original absolute destinations:
`0x86205E18`, `0x86205F08`, `0x86205E40`, `0x86205F24`, `0x86205F24`,
`0x86205DD0`, `0x86205EE0`. Reassembling the shared data prefix, this pool,
the CPU and paired-model pools, and the relocation-record tail reproduces the
entire original data blob and its other semantic relocations. Linked fragments
50/79, 332 existing function extents, four collateral objects and foreign-file
hashes remain unchanged. Negative controls reject a text opcode change, a table
addend change, a table-symbol change and a final alignment-byte change.

No new assembly owner has been replaced by C in this layout prerequisite.
Coverage files and private probes/compiler observers are unchanged or excluded.

## `func_862055F0`: register-tie / requeue

The model direction-pose reconstruction reaches the original 308-byte extent
and complete opcode sequence. The player index is replaced with the facing
slot read from the 24-byte input record at context offset 474066; the choice
index selects a 64-byte `SceneDirectionChoice`. X/Z placement uses its origin
and indexed direction, coefficients 18 and 5, and context floats at 216 and 204.
Y is 30; uniform scale is the context float at 216 times 0.4. Facing slots map
to signed rotations -24576, 24576, -8192 and 8192 at model offset 68.

Writing X and Z before Y recovers the original instruction ordering. Reusing
the consumed index parameter recovers the integer registers; a separate index
local does not. Best retained spelling is
`model-direction-pose-values:xz-then-y:scale-coefficient-first:speed-factor-first`
(raw 0.8701, normalized 1.0). The remaining ten words concern floating
multiplication operand order and the f16/f18 temporary rotation. Outer time
operand commutes and scale spelling were compared without improvement.
A calibrated 90-second source-only search retained score 70 with no proposal.

Named constant-object experiments changed non-text layout and were rejected;
keep the verified literal-pool ownership. No C body is installed. Next action:
trace the float expression/temporary allocation at the first residual (byte
128) before another source campaign; preserve the original arithmetic grouping
and the reloads between position stores.

## `func_862057A8`: register-tie / requeue

This 116-byte helper removes the inward velocity component when the dot product
between the velocity at object offset 16 and the supplied normal is negative.
Velocity X/Y/Z are read before stores; normal Y/Z are reloaded after preceding
component stores, so caching all normal components would change alias behavior.

Snapshot spellings recover all 29 opcodes but put the first velocity in f0
rather than f2, shifting the other float assignments. Changing declaration order
alone does not fix it. Direct field expressions and response-block bindings
were compared; the latter introduce extra loads and grow to 144 bytes. The
standalone m2c draft has a void return, and the only assembly caller ignores
its return registers. Do not introduce an unproven float-return ABI merely to
reserve f0. A calibrated 90-second source-only permuter search improved its score from
130 to 85 by introducing a redundant velocity alias. That proposal was rejected
as artificial; it is not source evidence. Eight follow-up candidates captured
the actual scalar inputs inside the dot expression without an alias. Their
best raw score was 0.5172 at the original 116-byte extent, still a register
allocation mismatch. No C body is installed. Next action: inspect the leaf float allocation and a proven
object-prefix type, retaining the actual component read/write order.

## Remaining family work

`func_86205500` initializes model flags, a 24-byte attachment record, scale and
RGBA. The model records have a verified 396-byte stride. The input action and
selection helpers `func_86205B8C` and `func_86205C8C` share the direction-pose
callee and model animation APIs. The state owner `func_86205D98` can now use its
seven-entry jump table without moving the shared data layout. These owners had
no attempts in the inspected local history before this working block. Preserve
all unresolved owners as requeues, and prioritize the direction-pose follow-up
before filling the rest of the next batch from this family.

## 2026-10-24: accepted four-function motion/model batch

All four replacements passed the normal host-syntax-enabled full ROM gate,
then complete-module, data-partition, linked-fragment and collateral checks:

| Original owner | C name | Instruction bytes |
| --- | --- | ---: |
| `func_86205500` | `SceneModel_InitPlayerAttachment` | 232 |
| `func_86205B8C` | `SceneModel_StartPlayerAction` | 256 |
| `func_86205C8C` | `SceneModel_SelectPlayerDirection` | 268 |
| `func_86205D98` | `SceneModel_UpdateAnimationState` | 412 |

Total: 1168 instruction bytes. Each retains its complete original extent;
there are no padding helpers, instruction rewrites or forced registers.
Address-keyed compatibility aliases preserve remaining assembly callers.

### Source mechanisms

The initializer needs five distinct, useful pointers for the flag update,
attachment link, attachment rotation, model scale and attachment color groups.
Each group reloads the appropriate pool through the shared context. Reusing
one model/attachment pointer across groups changes allocation. The 396-byte
model stride and 24-byte attachment stride come directly from the assembly;
no padded record layout was invented.

The action-start handler reads metadata after the outer high-bit flag guard,
then tests the action flag and elapsed counter. Reading metadata before both
flags leaves just two scheduled words swapped; declaring a context or counter
snapshot introduces other lifetime/frame differences. The winning form keeps
the original 40-byte frame with ordinary pointer expressions. Its threshold
is six context ticks plus three context ticks, in that evaluation order.

The direction-selection handler uses nested flag/choice checks, updates either
the current or pending selection, and calls the original animation APIs.
Explicitly retaining a separate animation pointer moves a stack spill; repeating
`model + 36` lets the compiler recover the original 48-byte frame and stores.

The animation-state handler is an ordinary C switch. Source case order
5, 0, 2, 6, 1 with break exits preserves the original code order and all seven
jump-table destinations, including the shared default for states 3 and 4.
Its elapsed threshold keeps three ticks plus six ticks. Multiplying by nine
instead shortens the generated expression and fails the instruction match.
The recovered per-file rodata pool is required before accepting this switch.

### Remaining work

The direction-pose and velocity-projection register ties above remain active
requeues with their diagnostic evidence. The remaining assembly owners in this
file are `func_862055F0`, `func_862057A8`, `func_8620581C`, `func_86205A7C`,
`func_86205F34`, `func_862061B0`, `func_86206334` and `func_86206508`.
Prioritize the recorded float-allocation follow-up before filling the next
batch from these same-file callers. The input decoder/dispatcher handoffs are
in the neighboring `fragment50_26D1D0.md` notes. No coverage was regenerated.

## Post-batch projection follow-up: measured coloring / requeue

A logging-only IDO 7.1 uopt observer was calibrated against the stock compiler
with tracing off/on and a blank-line control, on both the accepted initializer
and the retained projection candidate. All eight controls preserve complete
module game sections, 17 extents and semantic relocations. The earlier retained
candidate predates this file's rodata recovery; calibration therefore requires
its exact 116-byte body inside the current otherwise-unchanged verified module,
including the recovered 48-byte pool, rather than equating the old external
constant ownership with the current local ownership.

The candidate trace assigns the first velocity web to f0 and the dot-product
web to f16; the original instructions require velocity X in f2 and dot in f0.
This is observed global coloring, not a reason to rotate temporary-register
pools or change the return ABI. Eight partial-sum variants (two/three stages,
operand order and early Z snapshot) retain the 116-byte extent but alter
scheduling without reaching the target (best raw 0.4483). Eight uniform
float-pointer variants of the snapshot/direct expressions also fail (best raw
0.5517). No C body was installed and the accepted four-function source is
unchanged.

Next action: calibrate the direct-expression candidate through the same narrow
observer and align its float webs/uses with the snapshot candidate to identify
which genuine live-range change can put dot in the first global color. Preserve
the original left-associated float arithmetic, original normal reloads after
component writes, and void ABI. Keep the already-rejected pure aliases and
response-block extra-load variants out of the next campaign.

## 2026-10-24: motion and animation callback follow-up

### Accepted projection (`func_862057A8`, 116 bytes)

The calibrated direct-expression observer showed that the dot product already
held f0, while its memory-value webs put velocity Z in f2 instead of velocity X.
Changing the expression tree to Z plus (Y plus X), then commuting each product
independently, recovered all 29 original instructions. The accepted expression is
`velocity_z * normal[2] + (velocity_y * normal[1] + normal[0] * velocity_x)`;
the compiler emits the original X/Y pair before adding Z. The three response
stores keep ordinary compound assignments and reload normal Y/Z after prior
stores. No snapshots, fake aliases, return-type changes or register directives
are needed. The full ROM and containing module were independently verified.

### Accepted contact loop (`func_86205A7C`, 272 bytes)

An ordinary four-iteration for loop advances the model pointer by 396 bytes.
For models carrying the action flag, it traverses the context's linked node
list, clears each node's displacement, invokes the existing contact helper,
adds the resulting three components to position, then clears displacement
again. Separate reverse-order initial zero stores and normal-order final stores
match. No manual loop unrolling or record padding is used. The first candidate
passed the normal full-ROM gate and complete-module checks.

### Accepted animated-position callback (`func_862061B0`, 340 bytes)

The metadata pointer survives the existing position helper. The animation frame
is `(frame_word >> 16) - 4` in state 2, otherwise zero; a ternary clamp reproduces
the original two zero paths. An ordinary if assignment or shared goto merges
those paths and removes eight bytes. Rotation-first addition operands recover
the position float assignments. Reading the metadata's player index as unsigned
and placing its 24-byte record offset before the attachment-pool pointer
recovers the remaining eight integer-register words. The same player-slot field is used
by the four-model initialization path. The real pointer/width choice avoids
extra locals and keeps the original 32-byte frame. The callback retains the
mode-dependent dispatch to the existing state handlers.

### Direction pose: register-tie / requeue

A logging-only IDO observer passed stock/off/on/blank controls for both the
accepted initializer and the retained 308-byte pose candidate. Its global colors
cover the scale result and shared constants 18 and 5; the f16/f18 rotation occurs
in temporary expression evaluation after those reservations. Eight natural
coefficient/displacement binding candidates did not improve the best raw 0.8701.
Binding both displacement intermediates can grow the function to 312 bytes.
Keep the original arithmetic grouping and context reloads. Next action: use the
calibrated expression events to isolate the multiply operand/free sequence at
byte 128, then test a source mechanism that preserves the earlier constants.

### Player initializer: register-tie / requeue

`func_86206334` reconstructs four model nodes, animation resources, scale, initial
facing-dependent choices and attachments. The best retained body is
`model-player-init:for:shared-work-True:chain-False`: original 468-byte extent,
complete opcode sequence and raw 0.9402. One displayed immediate difference
is the legitimate local 0.31 pool reference at offset 32; the true residual is
six integer-register words in the input-record address calculation at bytes
240 through 264. The scale constant, switch cases, flags, callbacks and all
later calls otherwise reproduce the original sequence.

Sharing one work pointer between the animation and metadata roles keeps the
original 104-byte frame. Separate pointer locals or an explicit input-record
view can grow the frame to 112 bytes. Changing index signedness, pointer/base
addition order, raw 32-bit address arithmetic or inlining the switch selector
did not close the residual. A calibrated 90-second source-only search reproduced
all 117 base words and relocation targets, then stayed at score 55 with no
proposal. No initializer C body is installed.

Next action: capture the selected procedure's temporary allocation/free events
for the index/root loads and compare the working attachment-address spelling
in the accepted animated-position callback. The root load needs the earlier
temporary even though scheduling moves the index load first. Preserve actual
resource signatures and callback behavior; do not add arguments or padding to
force a frame. Five assembly owners remain in this source: `func_862055F0`,
`func_8620581C`, `func_86205F34`, `func_86206334` and `func_86206508`.
