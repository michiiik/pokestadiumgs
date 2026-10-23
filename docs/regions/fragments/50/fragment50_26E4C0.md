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

## Accepted XZ triangle predicate (US ROM, 2026-10-24)

`func_86207A80` → `Geometry_IsPointInTriangleXZ`, 320 bytes. Its eight
scalar arguments are the queried XZ point and three XZ vertices. The caller
`SceneCollision_TestBoundedPlaneHit` supplies the plane-hit point and the
triangle's vertices. This consumer and the three oriented cross products
establish the name.
//@src/fragments/50/fragment50_266A60.c

Let a, b and c be the vertices relative to the queried point. Compute and
retain AB, BC and CA cross products, then accept either common nonnegative
or common nonpositive signs. Preserve the original positive AB test as the
direct product comparison `a.x*b.z >= b.x*a.z`; the fallback uses the
computed AB difference. BC/CA comparisons are inclusive in both orientations.
Do not replace the direct product test with a difference test: they differ
for some nonfinite/overflowed inputs. Zero-area configurations follow these
same sign tests, without an added degeneracy rejection.

The winning source computes the three cross products once and reuses them
in both orientation tests. This gives the compiler shared values whose
subtractions survive the zero comparisons. Branch-local expressions had
been reduced to product comparisons and did not match. Ordinary optimization
sinks and duplicates the shared expressions as needed to reproduce the
original 64-byte frame and 320-byte body. All locals represent coordinate
deltas or cross products; no copied spill aliases or padding are introduced.

The `bc1fl` at `86207AD0` executes its subtraction delay slot only on the
taken negative path. Positive fallthrough annuls the slot; F6 still holds
a.x when stored at stack offset zero. Both CA tests therefore use a.x.
Structured and goto-only m2c reconstructions confirm this register trace.
The earlier notes' apparent positive-path asymmetry came from overlooking
that annulment and were corrected before this owner was installed.

The runner accepted a full byte-identical US ROM and exact containing-module
section bytes and semantic relocations. The named source is checked by a
fresh ordinary `make COMPARE=1 RUN_CC_CHECK=1`, with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`.

All five original assembly owners in this source file now have accepted C
bodies: triangle predicate, line projection, sphere contact, plane parameter
and segment contact. Their instruction bodies total 1448 bytes; the original
1456-byte text module includes eight unchanged terminal alignment bytes.
