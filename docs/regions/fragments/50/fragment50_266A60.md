# Fragment 50 scene-motion matching notes

## Four-function batch, 2026-10-23

The matching baseline is public master `11ceeb60791d7ea18d45f22a51a41b7973510974`.
The four original assembly owners contribute 588 instruction bytes:

| Original owner | C name | Bytes |
| --- | --- | ---: |
| `func_8620050C` | `SceneMotion_CreateThreeModels` | 168 |
| `func_86201790` | `SceneMotion_IsCrossXZNonnegative` | 104 |
| `func_86203BA8` | `SceneMotion_CopyNodePositionsToModels` | 68 |
| `func_86203C58` | `SceneMotion_RunSubsteps` | 248 |

The model initializer makes three allocation attempts through `func_87F025B8`.
Each successful result supplies a model at offset 36, initialized through
`func_8003F1DC` and `func_8003F114` with the corresponding context asset word.
Failed allocations leave that iteration without a model initialization.

The side predicate subtracts the X/Z coordinates at offsets 72/80 of
`D_87F119DC` from both input points and tests the nonnegative two-dimensional
cross product. Its local delta aggregate stores Z before X, matching the
original two stack stores. Both fields of both deltas participate in the
calculation. No unused fields, artificial stack storage or forced registers
are needed.

The position-copy routine follows the context list at offset 384. Each node
supplies its next pointer at offset 4 and model pointer at offset 32. The
three-float position at node offset 72 is copied to model offset 60. A named
model pointer reproduces the original word-copy destination register; an
inline destination expression leaves only register differences.

The substep routine first copies positions, runs its update pipeline for the
current context count at offset 60, and then computes model displacement
through `func_86203BEC`. Keep the four `func_87F0277C` calls in order and
reload the context between calls. The count is read again at each loop test;
no snapshot across callbacks was introduced. Existing `func_86203B08` and
`func_86203BEC` expose the position/transform/displacement relationship that
supports the scene-motion names. No minigame identity is inferred.

All four owners have accepted runner rows with link verification. The normal
US `make COMPARE=1 RUN_CC_CHECK=1` gate passes with retail ROM MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Immediate gate captures preserve the inputs,
complete changed module, ELF and ROM. Complete module sections, function
extents and semantic relocations agree with the still-assembly module;
leading-blank controls also pass. Old names remain linker aliases for
assembly callers. Coverage is unchanged.

## Remaining owners

`func_862025E0`: **requeue**. The retained scalar coefficient snapshots and
reused Z carrier produce 232 bytes, normalized 0.9655 / raw 0.8276. The first
difference is the table-address versus coefficient-address `lui` order;
rotated coordinates also use different float registers. Initializer scopes
and const locals do not repair those differences. Direct global coefficient
reads add reloads and change the frame. The 12-byte table entries passed to
`func_86201300` contain a word kind, pointer and word count, as shown by that
callee's existing C; a float-vector table cast is not an established type.
Next action: use that actual descriptor ABI and trace the two rotated-value
webs on the retained fixed-size body before another scheduling campaign.

`func_8620169C`: **requeue**. Sixteen source candidates preserve all three
RNG calls in each swap iteration, including the first discarded result,
plus initialization of the four-entry order array and clearing the following
byte. The 240-byte leader matches through instruction 49, normalized 0.9836 /
raw 0.9508, but reuses a high-address register where the original 244-byte
body materializes a new high half. A real five-byte order/cursor subview
retains that result; a separately named final subview instead produces 248
bytes and earlier register drift. Next action: inspect compiler versus
assembler ownership of that final large-offset store. Do not insert a dummy
instruction, enlarge a context with fake prefix fields, or force a register.
