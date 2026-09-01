# Region notes -- disasm/src/fragments/47/fragment47_24E0A0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: index-arithmetic loop over a strided array (AGENTS.md §4) (2026-08-28)

`for (i = 0; i < n; i++) { ... &arr[i * STRIDE] ... }` -- the pointer-accumulator spelling allocates differently. Evidence: 2 (`func_86009318`, `func_86009260`).

## Unsolved shape: float scheduling plateau at 0.909 (AGENTS.md §5) (2026-08-28)

`func_86007F6C` and `func_86009D7C` both plateau at 0.909 with one extra instruction and an unexplained `mov.s $f12,$f14` shuffle, at exact instruction counts -- a float argument-register scheduling difference worth its own investigation.

## Verified spelling: large vector call-chain helper (2026-08-31)

func_86008038 accepted, link_verified plus full COMPARE=1 (2026-08-31). Exact IDO shape: declare the f64 accumulator before nine descending 0x18-byte vector temporaries; keep the two func_87C002A8 calls nested inside func_87C00198 so the compiler creates the required sp+0x38 spill. An explicit pointer temporary drifts to sp+0x3C; declaring the accumulator after the vectors grows the frame from 0x120 to 0x128. This helper unlocks func_86008224 (2 calls), func_8600853C, func_860086A4, and func_86008904.

## Verified spelling: commutative float return source order (2026-08-31)

func_8600A144 accepted, link_verified plus full COMPARE=1 (2026-08-31). For both return paths, source operands must be written in the opposite order from the desired add.d operands: early path source arg0[0] + arg0[0x18] emits expected f0=arg0[0x18], f2=arg0[0]; final path source arg0[0x18] + product emits expected add.d f0, product, arg0[0x18]. The mathematically equivalent natural order stopped at raw 0.9677 with only the final add.d operands reversed.

## Register tie: func_86009EF8 (2026-08-31)

register-tie (2026-08-31): runner futility reported 13 prior attempts at >=0.99 register_allocation_only and directed stop. This box tried threshold/value/result declaration orders and inline-load forms; best current raw 0.6154 / normalized 0.9231 instruction_drift because the unused second formal was stored before the expected leading mtc1. Do not resume source-shape variants; send the recorded >=0.99 candidate to the permuter.

## Requeue: func_86008E64 fleet box (2026-09-02) (2026-09-02)

requeue: fresh 58-instruction call-chain owner; no prior probe attempts or recorded best score. Assembly fingerprint: 0x86008E80 jal func_87C007DC, conditional subtract of arg0+0xC8 when arg1 != 0, positive f64 guard, then jal func_87C00814, six-word record copy, func_87C002A8 scale, func_87C00160 apply, func_86007EB4 cleanup, return 1/0. Prepared 8 distinct candidates in /private/tmp/gs49_func_86008E64_batch.json; no runner invoked, so normalized/raw score and mismatch kind are unavailable. Hypothesis families: typed Vec overlays, raw 0x18-byte records, explicit result temporaries, guard polarity, and declaration/order variants. Next action: run the JSON as one probe-only batch, inspect first-diff diagnostics, then change hypothesis family based on mismatch; preserve exact prototypes for func_87C007DC(const f64 *, const f64 *), func_87C00814(void *, void *, void *), func_87C002A8(void *, void *, f64), and func_87C00160(void *, void *, void *).

## Wave 49 coordinator replay (2026-09-02)

tooling-blocked; 8 fresh candidates could not compile because the batch redeclared existing func_87C00160 with an incompatible prototype and defined func_86008E64 as s32 against the existing owner prototype void. No candidate reached comparison. Next action: prepare a fresh full-definition batch using the existing helper prototype and void owner signature, then separately verify whether the target return value requires an accepted prototype change; do not repeat the conflicting declarations.
