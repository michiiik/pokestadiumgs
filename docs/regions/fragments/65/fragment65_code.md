# Fragment 65 vector and matrix family

## 2026-10-14: four native, full-ROM-gated owners

Work is solo/native macOS, with normal runner statistics enabled. Fresh-source,
build and20-leading-blank controls first reproduce all nine functions and their
linked retail spans before any candidate is tested. The older private Wave13
note for00720 records no acceptance; its normalized percentage is not proof.

Accepted owners:

- `func_87D00020` / `fragment65_main`:97 instructions /388 bytes,0x38 frame.
  Normalize the supplied axis, convert the angle with the original data constant,
  preserve sine/cosine calls, initialize the matrix and fill its rotation entries.
  Real scalar square reuse closes the diagonal expressions. Normal runner accepts
  on the first eight-candidate batch, link_verified=true. Timing5.581s probes /
  1.295s combined gate /6.879s total.
- `func_87D001A4`:108 instructions /432 bytes,0x30 frame. Preserve axis
  normalization, original angle constant, trigonometry, horizontal magnitude,
  identity fallback and all sixteen output fields. Source stores in column order
  close the schedule; the emitted-order draft misses one instruction. Acceptance
  follows eight prior probes; link_verified=true. Timing5.260s probes /0.972s
  combined gate /6.234s total.
- `func_87D00354`:57 instructions /228 bytes,0xD0 frame. Preserve positive
  horizontal-magnitude guard, up vector, cross product/normalization, matrix copy,
  rotation construction, multiplication and three row normalizations. Matrices
  precede scalar/vector locals in the winning declaration order. First batch
  accepts, link_verified=true. Timing9.021s probes /52.547s combined gate /
  61.571s total; this initial gate rebuilds the baseline.
- `func_87D00670`:44 instructions /176 bytes, leaf. Preserve parallel-line
  failure, both parameter results and original memory reloads after the first
  output store. A typed two-float record plus a real pointer to its x member
  isolates the remaining operand-demand issue. Calibrated searches improve
  165to75 and50to10; reviewed normal source reaches one differing multiply
  operand order at raw0.9773. Commuting that specific multiplication closes it.
  The pointer is used for the actual second-result load, not dead allocator
  scaffolding. Acceptance follows40 prior normal probes, link_verified=true.
  Timing5.309s probes /1.152s combined gate /6.464s total.

Repository naming evidence identifies00020 as the header trampoline's target
at ROM0x335DC0/VRAM0x87D00000. Apply the existing `fragment65_main` entry name
and retain `func_87D00020 = fragment65_main` in US aliases; this is a fragment
export entry, not evidence of a game main loop. The other three names remain
address-based without an independent existing mapping. JP files are unchanged.

After duplicate declaration cleanup and naming, full-ROM compare retains MD5
1561c75d11cedf356a8ddb1a4a5f9d5d; all427 host syntax checks pass. Fresh final
source/build/blank controls match all nine functions and linked retail spans.
The three previously accepted routines and two remaining assembly owners are
unchanged. No data subsegment, compiler patch, new helper function or header is
needed. Only source, the compatibility alias and these notes are published.

## Requeues before completion

- `func_87D00438`:32 normal probes across scalar-role reuse, record views,
  threshold operand direction and output topology. Best normal candidate has
  exact356-byte size/0x38 frame, normalized0.9663/raw0.7416, but still different
  matrix-store scheduling. Calibrated90-second search810to565 has no zero and
  its proposal is not installed. Requeue on measured statement topology/line
  relationships, retaining scalar-role reuse and column-layout controls; do not
  replay the original separate reciprocal/translation live-home family.
- `func_87D00720`:24 normal probes, best normalized0.9545/raw0.6818 with the
  complete padded176-byte owner. Float colors form a coherent cycle, and final
  result loads are reversed. The first scratch importer omitted gu.h's
  `#pragma intrinsic(sqrtf);`, producing a library call: calibration refuses
  before search. Restore the exact pragma after its declaration in local scratch;
  base/probe and target/oracle then agree. Calibrated90-second search75to50
  has no zero. Requeue on direction/squared-magnitude ownership and natural
  statement grouping. Never accept a normalized register score or the uncalibrated
  importer result; retain the verified eight trailing alignment bytes.

Local ignored evidence lives in scratch/native-vector-*.json/log and bounded
permuter directories. These are local diagnostics, not public prerequisites.

## 2026-10-14: both requeues accepted, fragment 65 complete

Fresh source/build/blank controls reverify all nine functions before follow-up.
Normal batches exercise materially new source topology rather than replaying
rejected variants. Both remaining owners now pass the full-ROM gate:

- `func_87D00438`:89 instructions /356 bytes, original0x38 frame. Row-order
  nonzero entries plus reversed zero stores11/7/3 recover the original schedule;
  put the homogeneous1 at the end. Preserve the squared dot threshold, identity
  fallback/return1, reciprocal, translation, all16 matrix fields and success0.
  Accepted after32 prior normal attempts, link_verified=true. Timing5.251s
  probes /0.998s combined gate /6.252s total.
- `func_87D00720`:42 executable instructions /168 bytes plus8 verified alignment
  bytes, leaf. Direct accesses to the existing two-float record's x/y members
  eliminate the temporary-component color swap; preserve the post-first-store
  direction-y reload. Retain displacement, degenerate-direction copy, projection,
  both output fields and final length, with original multiplication/addition order.
  Accepted after48 prior normal attempts, link_verified=true. Timing5.211s
  probes /0.886s combined gate /6.100s total. No register forcing or fake locals.

The discarded record-only and lifetime-carrier cells did not close projection;
actual record-member expressions did. Never generalize this to replacing all
array accesses with records without probing. Likewise, zero-store ordering and
row ordering need each other's context in00438: the former column-order baseline
was not an exact program. The two earlier requeues above are historical, not
current blockers or exclusions.

After declaration cleanup and indentation-only cleanup, full-ROM compare retains
MD51561c75d11cedf356a8ddb1a4a5f9d5d; all427 host syntax checks pass. Fresh final
source/build/20-leading-blank controls match all nine complete function spans and
their linked retail bytes, including the full176-byte padded projection owner.
The other seven functions are unchanged. Naming plan has no evidence-backed
existing names for these two; retain their address names. No data or linker
changes are needed. This file now has zero GLOBAL_ASM owners.
