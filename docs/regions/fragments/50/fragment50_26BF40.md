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
