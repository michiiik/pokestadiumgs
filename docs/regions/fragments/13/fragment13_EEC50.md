# Region notes -- src/fragments/13/fragment13_EEC50.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-15

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-15

func_82405D38: time cap at 0.9057 (raw 0.5755) after 2688s, mismatch operand_or_scheduling_drift; tried families: call_chain; tie-pool no

## 2026-10-15 — four lighting/clock callbacks accepted

The file advances from **36 C / 43 ASM** to **40 C / 39 ASM**. Four normal
native-runner accepts cover **147 instruction words / 588 ROM bytes** under
stock IDO 7.1 / `-O2`. Every owner has `link_verified: true` and a successful
combined full-ROM gate; statistics and host checks stay enabled.

| Owner | Name | Words / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_82405934` | `Fragment13_UpdateSceneLightNode` | 44 / 176 | 0x40 | `bc1f32a9f0d8410990eca5b1caf9fed5` |
| `func_824059E4` | `Fragment13_UpdateSceneDirectionalLightNode` | 29 / 116 | 0x28 | `7615c44b27f542b5b6d04065d8332108` |
| `func_82405A84` | `Fragment13_UpdateClockHourHand` | 40 / 160 | none | `b292669dde624557a4e23e6c9e6fd716` |
| `func_82405B24` | `Fragment13_UpdateClockMinuteHand` | 34 / 136 | none | `dc3f8837f680448da6a552223e3b5ea3` |

### Source mechanisms

- Light node: preload context, then preserve event-2 RGB/flag writes and the
  kind-19..21 vector path versus angle path. Declare the real word-sized kind
  before the six-byte vector and two angle locals; load it after the color
  writes. This restores angle homes at stack+0x2E/+0x2C and vector at +0x30
  without padding or unused locals. A byte kind changes code; omitting the
  named kind leaves angles twelve bytes too high. Sixteen candidates.
- Directional light: a real byte-pointer node alias precedes the context and
  angle locals. That restores frame 0x28, context spill +0x20 and angles
  +0x1E/+0x1C. The direct-parameter spelling has frame 0x20; an angle array
  has the wrong slots. Eight candidates close the historical stack-layout
  requeue, using new evidence from the accepted sibling rather than replaying
  its old scalar orders. Preserve color bytes +0x34..36 and vector +0x38.
- Hour hand: retain the genuine signed word angle, convert to integer before
  negating it, and put the hour term after the fractional-minute expression.
  An inline integer cast without a named angle still loses a target word;
  a separate negating assignment changes allocation. Twenty-four candidates;
  the previously stuck family becomes exact under this new source topology.
- Minute hand: use `seconds / 60.0f + minutes`, store the sum in a float local,
  then multiply by the original scale, divide by 60 and negate before integer
  conversion. The opposite addition order schedules the second byte first;
  keeping a float minute local gives it the wrong colored register. Forty-eight
  candidates across distinct tested families; a calibrated 45-second native
  permuter on the earlier minute-first basin stays 120 -> 120. No mutation
  is adopted. The accepted different expression basin is not contradicted by
  that scoped negative or the runner's advisory register-tie warning.
- Keep the separate original global scale cells, each **65535.0f**, and all
  original event guards, byte-to-float conversions, signed halfword stores
  and source evaluation groupings. Do not simplify to a different turn scale.

### Cleanup, naming and verification

- Add four behavior-backed US compatibility aliases, retaining address-keyed
  symbols and JP. No new helper function or storage object. Correct the local
  vector-conversion declaration to its actual pointer return (ignored here),
  preserve the five-argument vector-mode helper's byte formals, remove duplicate
  prototypes for the already-defined angle helper, and format only the new C.
- Baseline normal ROM rebuild and fresh/twenty-leading-blank whole-object
  controls pass before candidates. After cleanup/naming, the same controls
  preserve all section bytes/layout, all **79 function offsets/sizes/full
  spans**, the four accepted bodies and **75 untouched** C/ASM spans against
  the frozen accepted/original objects. No layout or compiler changes.
- Forced final native ROM build matches retail MD5
  `1561c75d11cedf356a8ddb1a4a5f9d5d`. Explicit host syntax check passes;
  public tooling tests: 22 PASS. Diff whitespace check passes.
- No provenance bypass, forced register, padding, dead-variable scaffold or
  compiler mutation is installed. Only C, US aliases and region notes are
  published. All generators, proof scripts, traces, compilers, objects and
  ROMs stay local. Work is solo/native, without agents or containers.

### `func_824070E4` — requeue, clamped interpolation register roles

Thirty-two candidates reproduce **35/35 instruction opcodes**, frame 0x18
and 140 bytes, but not the registers. Best baseline normalized/raw is
**1.0/0.7714**, with a named index colored instead of the original t6 load.
Inlining the index restores that load, but start/end use v1/a1 instead of
a1/v1; the array-address addition order also differs (best raw 0.7429 in the
field-limit family, 0.7143 in the named-limit inline-index family).

Tested: both min/clamp spellings, load/declaration orders, named versus field
limit, signed-halfword versus word limit, a separate float base, advisory
register spelling and integer/pointer/array address forms. None is installed.
Next: trace the two equal-sized word-value webs and their interference in the
inline-index leader before more declaration/operand variants. Do not change
the known float callback signature or invent unused formals to force a1.

### Historical target-selection caveat

The local ranker's zero-attempt signal did not expose the older directional
callback requeue recorded in the shared region notes. Those notes were read
before probing; it was retried only after the new light-node layout evidence.
Do not treat missing structured history as proof that an owner is fresh.
The larger `func_82405D38` historical handoff remains unchanged and untried.

## Native motion/group batch — 2026-10-15

Three owners accepted: **139 words / 556 bytes**. File advances from 40 C /
39 ASM to **43 C / 36 ASM** (79 total). Solo/native; no agents or containers.

| Original owner | Behavior-backed name | Words | Frame | Acceptance |
| --- | --- | ---: | ---: | --- |
| `func_82405F8C` | `Fragment13_StepVectorToward` | 53 | 0x30 | link-verified, combined ROM gate; `8b6953b80f9b458a9a7a5347817b09e8` |
| `func_82407170` | `Fragment13_FindNearestGroup` | 46 | none | link-verified, combined ROM gate; `2d474116d89048e4b3945eeba14925a1` |
| `func_824048F0` | `Fragment13_InitGroupedList` | 40 | none | relocation-masked, sequential ROM gate; `f8a33b83d997435d899dee0285f93b9a` |

### Measured source shapes

- Vector stepping: compute the three differences before the distance, then
  use explicit `position = position + delta / distance * step` assignments.
  Negative step or **strictly** shorter distance copies the destination and
  returns zero; otherwise return one. Preserve original equality/zero-distance
  behavior rather than adding a divide-by-zero guard. No saved origin locals.
- Nearest group: eight 0x3C-byte records; inline the repeated **X square before
  Z square**, cast the sum to signed integer before comparing, and retain the
  strict comparison/first-on-tie behavior. IDO unrolls the ordinary loop by two.
  Named differences produce the wrong unroll; Z-first inline terms reproduce
  the opcode sequence but swap six X/Z load offsets. Twenty-four candidates
  across these families; no manual unroll or padding.
- Grouped-list initialization: clear 128 halfwords to -1, then write eight
  groups' counts, starts, item indices and separators. The record count is an
  unsigned halfword at offset 0x3A; the uncharacterized tail stays opaque.
  A controlled, token-identical clear-loop reflow proves statement source-line
  grouping controls its branch-delay schedule: single-line body has three
  differing words; a normal multiline body has only the end-address relocation.
  Twenty leading blank lines do not change either result. Pointer-clear and
  loop-shape families did not fix this schedule. No runner change was required:
  the existing candidate identity already preserves token-bearing line groups.
- The initializer materializes `D_82407370 + 480` instead of the assembly's
  equivalent `D_82407550`. It is **not object-link-verified**: the normal
  relocation-masked sequential full-ROM gate establishes acceptance. No symbol
  address, section layout, compiler flag or linker-layout change is needed.

### Cleanup and verification

Three US compatibility aliases; no new helper function or storage object.
Move the shared anchor type before its first use, remove duplicate/unused
externs and format only newly accepted C. Fresh and twenty-leading-blank
whole-object controls preserve every section's bytes/layout, all **79 original
function offsets/sizes/full spans**, all three accepted bodies against the
frozen accepted object, and all **76 untouched** spans against the baseline.
Forced normal native ROM build passes retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`; explicit host syntax check passes with the
existing unrelated line-25 implicit-call warning; 22 public tooling tests pass.
No bypass, forced-register scaffold or compiler mutation. Scratch generators,
proof scripts, compiler files, objects and ROMs remain local and unpublished.

### `func_8240641C` — requeue, input-load CSE and lifetime

Eighty-one-word / 324-byte target, frame 0x20. Forty submitted candidates
(four compile failures) across record/raw views, byte/word handled flags,
nested/goto tails, controller-field/halfword-array accesses, volatile samples
and an explicit navigation snapshot. Best ordinary family: 316 bytes,
normalized/raw **0.9753/0.7407**. The compiler shares an initial controller load
that the target repeats. Volatile sampling overcorrects to 340 bytes; explicit
navigation snapshots do not close the residual. None is installed.

Preserve B-before-A precedence, independent right/left navigation tests,
post-sound reload behavior and the unconditional final update call. Do not
invent a return value or extra formal to steer allocation. The sound helper's
one-argument call conflicts with this file's existing two-argument prototype;
an old-style unspecified-arity declaration was tested only as a transactional
companion edit, not adopted. The accepted caller and original prototype remain
unchanged. Next: trace controller-load value ownership across the initial B/A
split before another source family; distinguish load CSE from base-address
promotion. These measured failures are not a proof that legal C is impossible.
