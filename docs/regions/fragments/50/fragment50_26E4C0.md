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

- **requeue — `func_86207BC0`**, 384 bytes: line projection kernel. The
  best separate-scalar candidate has normalized similarity 0.9375, raw
  0.2708, a 380-byte body and 88-byte frame versus the original 80-byte
  frame. Scalar declaration order and vector aggregates have been tested.
  Eight consumed-endpoint carrier variants changed the frame to 32, 40,
  72 or 80 bytes but missed instruction topology; their best normalized
  similarity was 0.9167. The degeneracy guard compares endpoint X deltas
  directly, Y difference to zero and Z difference to zero. Preserve its
  ordered floating comparisons and reload the parameter after each output
  store to preserve alias behavior. Next: inspect temporary spill lifetimes
  around the parameter division and the first closest-vector store, keeping
  the six-pointer output-only ABI.
- **register-tie — `func_86207EB0`**, 132 bytes: computes the plane
  parameter as the negated plane equation at the point divided by the
  normal/direction dot product, returning positive zero on a zero denominator.
  Twenty-four source variants covered snapshot normals, dot-product
  accumulation and result carriers. A parameter carrier with explicit
  success/failure branches reached normalized 1.0 but raw 0.4848, with
  register differences. A calibrated 90-second source-only permuter improved
  its score from 115 to 95 without an exact match. Stock IDO 5.3 and the
  normal driver both reproduced both accepted contact bodies in complete
  known-module and leading-blank controls. Next: compare this leaf's
  register lifetimes across the stock compiler paths; controls alone do not
  establish an alternate compiler match.
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
