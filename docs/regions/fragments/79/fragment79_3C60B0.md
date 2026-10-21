# Fragment 79 terrain-grid source shapes

## Accepted grid point value setter

`8415AC64` / `BattleAnim_SetTerrainGridPointValue` replaces244 original bytes
through recorded native-runner acceptance and a byte-identical full-ROM gate.

The oracle writes a halfword at offset0x10 of20-byte points, with16 points per
row, for interior row/column indices1..14. The point array view begins at the
existing object's offset0x1010. Unknown point bytes stay unnamed; this is not
a claim about the allocation extent of the enclosing state object.

Use ordinary nested loops, a real current-point pointer, and the row-array
address expression. Stock IDO peels the first two inner iterations and unrolls
the remainder by four. Flat byte addressing and flat point-index arithmetic
strength-reduce differently; manually copying the oracle's unroll is unnecessary.
The accepted spelling uses signed32-bit counters. Narrow counters changed the
loop shape and did not match.

The first-success callback froze the full changed TU object, four distinct
collateral objects, source, ROM, ELF and linked script. All nine artifacts were
independently hashed before further compilation. Five complete-original-object
controls cover source cleanup, naming and blank-line stability, including all
previously accepted neighbors. Four emitted layout values verify point size20,
field offset16, row stride320 and field width2. Existing unrelated source and
declarations were preserved.

## Phase/latch updater: requeue

`8415AD58` remains assembly after16 genuine source variants. It tests the real
u32 status getter against1, conditionally initializes the halfword at state+8
from state+4 plus0x463C and sets the latch, calls8415A364, then advances two
signed halfword phases by+2/-1 modulo0x4000.

Using a signed32-bit local for the real status result recovers the original
shared constant1 and matches the entire pre-call section. Equality against1
is unchanged by this signed conversion. The best136-byte draft has only eight
raw word differences, all in the post-call phase pointer registers: candidate
v0/v1 versus original v1/a0. Nested guards, state-pointer caching and explicit
phase pointers do not resolve it. Next: calibrated post-call register-availability
trace and actual8415A364 declaration/return lineage. Do not invent a return
type, dummy use or owner interface solely to reserve v0.

No phase updater draft was installed. Other owners retain their assembly.
