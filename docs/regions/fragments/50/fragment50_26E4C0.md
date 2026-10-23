# Fragment 50 contact geometry

## Accepted contact routines (US ROM, 2026-10-23)

`func_86207D40` → `Geometry_TestSphereContact` subtracts the second
position from the first into the output normal. Ordered component bounds
reject candidates before the Euclidean distance test. Distance equal to the
radius is accepted. A coincident pair sets only the normal's X component to
1; otherwise `func_80035A10` normalizes the three components. The depth output
is radius minus distance and is written only on success. The normal output
is also the component workspace and therefore changes on failure.

`func_86207F34` → `Geometry_TestSegmentContact` calls `func_86207BC0`
for the distance, segment parameter and closest relative vector. It accepts
only distance strictly below radius and parameter inclusively between 0 and
1. Success normalizes and negates the vector and writes radius minus distance
to the depth output. The kernel writes the vector even if the contact test
fails; the depth output is written only on success. These operations justify
the contact names independently of byte matching.

The normalizer's pointer return and three-float argument follow its actual
definition in `src/229E0.c`; the call does not consume the returned pointer.
The segment kernel uses six pointer arguments and writes its results through
them. The local three-component type has no unused fields.

Source mechanisms: the sphere routine accesses the output components directly
rather than caching them, with the integer result declared before distance.
The segment routine assigns its integer result in both success and failure
branches. Both spellings passed the normal compiler and complete ROM gate.

Verification uses `make COMPARE=1 RUN_CC_CHECK=1` for the US ROM, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`, with complete containing-module section
bytes and semantic relocations checked against the assembly baseline.
The sphere body is 368 bytes; the segment body is 244 bytes. The assembly
symbol for the latter includes eight terminal zero alignment bytes (252 bytes
in total). C emits the same module bytes and terminal alignment, with a
244-byte function symbol. No padding is added to the C body.

## Unresolved owners

- **requeue — `func_86207A80`**, 320 bytes: XZ orientation predicate.
  Eight conditional-delta/product variants reached normalized 0.7125 and
  raw 0.15, with a 304-byte body and 48-byte frame versus 320/64. Eight
  up-front-delta branch-chain variants regressed. The positive orientation's
  final test uses the first cross product where the negative path uses the
  first X delta; the assembly's stack offsets establish this asymmetry.
  Preserve it rather than substituting a conventional triangle predicate.
  Next: test scoped short-circuit topology with conditional third-point
  loads and explicit result assignment.

Rejected candidates are not installed. No instruction rewriting, forced
registers, artificial locals, manual loop unrolling or source padding is used.

## Accepted plane parameter (US ROM, 2026-10-23)

`func_86207EB0` → `Geometry_ComputePlaneParameter`, 132 bytes: for plane
coefficients `(nx, ny, nz, d)`, point P and direction V, returns
`-(n dot P + d) / (n dot V)`, or positive zero for a zero denominator.
The formula establishes the name. It preserves the original grouping of
three-term dot products and the early return without point loads on a zero
denominator. Nonzero and unordered denominators take the division path.

The direct array expression and conditional result gave the denominator its
original F0 register. Commuting operands within the same grouped additions
and multiplications then gave the normal components their original register
order. The last mismatch was a multiplication with reversed source operands;
reversing that source pair produced an exact match. No reassociation,
register forcing, extra reads, padding or object edits were required.

The runner accepted this body with a full byte-identical US ROM, complete
module section/semantic-relocation comparison and unchanged collateral.
The named and formatted source also passed a fresh ordinary ROM gate.
Logging-only IDO controls reproduced the complete module with tracing on,
off and after leading blank lines. Equal-cost floating globals selected the
normal components before the denominator in the explicit-result candidate;
the direct conditional expression changed that ordering and supplied the
starting point for the successful operand-order candidates.

### Remaining handoff

- **requeue — `func_86207A80`**: eight conditional cross-guard variants
  improved raw similarity to 0.2875 while retaining normalized 0.7125 and
  a 304-byte body/48-byte frame. Eight explicit second/last cross-product
  temporaries produced the original 64-byte frame, but the body remained
  304 bytes, normalized 0.7125, raw 0.2000. All temporaries carried real
  products consumed by the predicate. Next: compare that 64-byte-frame
  candidate's short-circuit branches and duplicated first-product lifetimes
  against the original 80-instruction topology; do not add unused locals.

## XZ Boolean follow-up

**requeue — `func_86207A80`**, 2026-10-24: sixteen variants tested a
single short-circuit OR between the two orientation paths, direct versus
cached third-point deltas, and explicit consumed cross-product temporaries.
The best normalized score increased from 0.7125 to 0.7250 (raw 0.1750),
with a 312-byte body versus the original 320. Frames ranged from 40 to 56
bytes; cached deltas shortened the body further to 288 bytes. These results
do not supersede the earlier 64-byte-frame explicit-cross candidate.
Next: compare that candidate's branch graph and value lifetimes against the
original before combining expression changes. Preserve the positive path's
use of the first cross product in the final test.

## Accepted line projection (US ROM, 2026-10-24)

`func_86207BC0` → `Geometry_ComputeLineProjection`, 384 bytes. For point
P and endpoints A/B, form p=A-P, q=B-P and d=q-p. The parameter is
`-(p dot d)/(d dot d)`; the vector output is `p + parameter*d`, the
closest position on the infinite line relative to P. The distance is that
vector's Euclidean length. `Geometry_TestSegmentContact` bounds the
parameter to [0,1] and normalizes/negates the relative vector on success.
These producers and consumer justify the projection name and vector type.

The degenerate guard preserves its exact comparisons: q.x equals p.x,
Y delta equals zero, and Z delta equals zero. Degenerate input writes zero
to distance, parameter and all vector fields, even if P differs from the
coincident endpoints. The first parameter value is used for X, then the
parameter is reloaded for Y and Z after the preceding vector stores. This
preserves behavior when the parameter pointer overlaps the vector output.

Winning source mechanisms:

- Direct point-coordinate reads let IDO share the three coordinate values;
  explicit origin snapshots had an 88-byte frame. The accepted frame is 80.
- A named Y direction delta in the zero test preserves the subtraction;
  the inline test was folded into a direct comparison of endpoint deltas.
- Declaration order places the Z endpoint delta before X/Y endpoint deltas,
  then the Z direction delta before X/Y direction deltas. An explicit final
  `point_distance` carries the computed square root to the distance store.
  Every local participates in the projection or distance calculation.
- Three-component output fields reproduce the final load order and floating
  globals. The accepted body was cleaned up to take `GeometryVec3 *`
  directly, with its only C caller updated and the obsolete extern removed.
  The six-pointer calling convention is unchanged.

The runner accepted the complete ROM and full containing-module bytes and
semantic relocations. The named, typed and formatted cleanup passed a fresh
`make COMPARE=1 RUN_CC_CHECK=1`, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Stock 5.3 and 7.1 drivers had reproduced
the same residuals on the tested near-match candidates after complete current
module and blank-line controls; the ordinary driver produced the final match.

### Remaining XZ diagnostic

**requeue — `func_86207A80`**: eight direct-delta expression variants
were also rejected. Flag forms gave 284 bytes; OR forms gave 268, against
320 bytes in ground truth. Best normalized similarity remained 0.7250,
raw 0.1500. Direct expressions alone do not reproduce this predicate's
spill/branch topology. Resume from the earlier 64-byte-frame candidate and
compare its branch graph, preserving the asymmetric positive-path formula.
