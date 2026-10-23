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
`func_86201300` contain a vertex pointer, triangle pointer and word count.
`func_86200870` indexes three-float vertices through the first pointer using
the three byte indices at triangle offsets 16..18; the triangle stride is
20 bytes. The original data at `D_8620DF60` also records both pointers.
A float-vector table cast is not an established descriptor type.
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

### Subsequent shuffle diagnostics

`func_8620169C`: **requeue**. Eight further cells vary ordinary signed,
unsigned and long integer literal categories at the actual large byte
offsets. None repairs the final store; the unsigned order-array offset also
changes the second random-index register earlier. Do not repeat those cells.

Eight logging controls cover the known position-copy routine and retained
240-byte shuffle parent, each through stock, logging-off, logging-on and
leading-blank builds. Complete modules, extents, semantic relocations and
parent instruction words remain identical. The shuffle is UOPT procedure
30 / UGEN 29. Its UOPT global-color trace assigns the genuine high-offset
constant 458752 (0x70000) to s1, with four uses. That is consistent with the
observed compiled reuse at the final cursor store. The original uses s1 in
the array accesses but materializes a new high half for the final store.
This identifies an optimizer-visible shared constant in the candidate;
it does not establish the original source or prove that one pass owns the
whole residual. Next action: distinguish constant-address lowering from
assembler expansion using retained generated assembly before another
source-type or field-view family. No source owner was installed by these
diagnostics, and no compiler or binary was changed.

## Bounded plane contact and record flags, 2026-10-23

The baseline for this batch is public master
`f4b177f9cdc7266d20b24b69b96333c5b44f8169` (the preceding four-function batch).
Two further owners match, totaling 480 code bytes / 120 instructions:

| Original owner | C name | Bytes |
| --- | --- | ---: |
| `func_862009E4` | `SceneCollision_TestBoundedPlaneHit` | 240 |
| `func_86203DE8` | `SceneFlags_MarkWhenCountsMatch` | 240 |

The contact predicate uses the node position at offsets 72/76/80, a plane's
four floats, a parameter limit, and three triangle vertices. It negates the
plane normal and calls `func_86207EB0`, whose original assembly computes
`-(dot(normal, position) + constant) / dot(normal, direction)` and returns
zero for a zero denominator. If the returned parameter is in the inclusive
range from zero to the supplied limit, the predicate computes the hit's X/Z
coordinates and calls `func_86207A80` with the three vertices' X/Z pairs.
Keep both ordered comparisons: the original rejects a NaN parameter.
//@src/fragments/50/fragment50_26E4C0.c

Naming the two consumed hit coordinates reproduces the original 72-byte
frame. Declaring result, distance, three-component direction, then the two
hit coordinates puts the result at its original stack offset 68 while
retaining the direction at offset 52. All declared values contribute to the
intersection or predicate call; no dummy local or explicit alignment is
present. The float helper's three-pointer interface and the triangle
predicate's eight-float interface come from their original assembly. The
complete containing module confirms that the additional compatible
prototype leaves existing callers unchanged.

The flag routine counts bit 30 and bit 24 across four records with a 24-byte
stride. When the two counts agree, it sets bit 31 on records carrying bit 30.
The bit meanings remain unknown. Initializing the second counter before the
first reproduces the original counter registers. The second four-iteration
C loop is automatically unrolled by the normal compiler; the source contains
no manually expanded record updates.

Both owners have accepted runner rows with link verification and successful
normal full-ROM gates. The final named source passes
`make COMPARE=1 RUN_CC_CHECK=1` with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Complete module sections, all function
extents and semantic relocations agree with the original assembly module.
Aliases retain both old entry names. Coverage is unchanged.

### Follow-up evidence

`func_862048B0`: **register-tie**, still assembly. Correct callee interfaces,
named context/flag snapshots, ordinary zero tests and terminal void-return
spellings leave the 336-byte leader at normalized 1.0 / raw 0.7619. The
90-second constrained source search calibrates all 84 instruction words and
relocation targets before searching, stays flat at local score 140, and
produces no proposal. Eight logging controls preserve complete modules for
the known position copier and retained drawing candidate. UOPT procedure 70
(UGEN 69) colors the context-load web to v1 and the flag-load web to a0; the
original uses v0 and v1. Next action: inspect availability/interference at
those two global-color decisions. The logging evidence does not establish
an original return-type change, and no such change was made.

`func_86202AC4`: **requeue**. Eight candidates reproduce both pool loops,
RNG seeding, setup calls and camera arguments, but remain 332 bytes versus
336. The candidate shares a high-address constant between two final state
stores where the original materializes separate high halves. Next action:
resume address-lowering diagnostics alongside the shuffle residual; do not
add prefix fields or filler instructions to make a context type.

`func_86200870`: **requeue**. Sixteen candidates use the observed vertex,
20-byte triangle and 12-byte group layouts. The retained snapshot/break
candidate has the original 372-byte extent but a different frame and float
registers (normalized 0.9570 / raw 0.7957). Explicit coefficient snapshots
can reproduce the 80-byte frame but regress other instructions. Next action:
compose the measured frame mechanism with the original coefficient/rotated
coordinate lifetimes before any further declaration-only retry. The first
group field is a vertex pointer, established by indexed loads in this owner
and both pointers in the ROM table at `D_8620DF60`; it is not a kind word.

`func_862025E0`: **requeue**. Eight descriptor/table-base variants do not
repair its existing ordering/color residual. Use the corrected descriptor
roles when resuming; those rejected candidates installed no new type.

The proposed text-assembly diagnostic is **tooling-blocked** on calibration:
normal C compilation and `-S` followed by assembly do not reproduce the same
known module before assembly-owner injection (21,728 versus 21,872 text
bytes). The target shuffle was not run through that failing harness. Existing
logging-only controls remain valid. Next action: recover the normal binary
assembler input and its exact pass options before treating a text round trip
as evidence about source or compiler reachability.
