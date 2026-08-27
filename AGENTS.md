# Repository agent guidance

This file is the entry point for any agent session in this repository. Read it
fully before touching the tree. It has four parts: how to run a session
(§1), the decompilation process rules (§2), the tool reference (§3), and the
verified source-shape heuristics (§4). Historical detail lives in the
referenced docs and in git history, not here.

## 1. Running a session

### 1.1 Two kinds of session

**Decompilation sessions** (the goal is "decompile owners in fragment N /
family F / file X") run **fleet mode**: the session is a coordinator that
assigns one source file each to 4–8 Sonnet decompilation agents, which run
the hand loop in §2.5 against the runner API for a 60-minute time box, commit
their file by explicit path, and report the spellings that matched. Measured
on 2026-08-27 (four agents, 20 minutes): 40 owners accepted, ~17k tokens per
matched owner (~10k in text-segment files, ~55k in fragments), versus 4–5
owners/hour for a single hand session. The mechanical sweeps are saturated
(every remaining owner of 64 instructions or fewer has been probed with the
current variant set); run them only when §2.5 says so.

Coordinator rules:

- One file per agent, never shared. Pick files by remaining owners of ≤128
  instructions (`python3 tools/pragma_targets.py targets --source <file>`),
  text-segment files before fragments (fragments cost ~5× more per owner),
  and skip any file another session touched in the last four hours
  (`git log --since="4 hours ago" --format= --name-only -- disasm/src`).
- The agent prompt is §2.5 plus: the file path, whether the file already has
  its `.rodata` subsegment (`docs/JUMP_TABLES.md`; if not, skip `jtbl_`
  owners), the 60-minute box, "runner-only installs, never hand-edit, never
  `DECOMP_PROVENANCE_SKIP`", commit-by-path every 5 accepts, and the report
  format (attempted/accepted, variants probed, best mismatch kinds, one line
  per accepted spelling, why it gave up, commit shas).
- When agents report, fold every *second* confirmation of a spelling into §4,
  add runner bugs and recurring unsolved shapes to §5, then reassign files.
  Do not run tooling changes and a fleet at the same time in one checkout.
- Do not spawn investigation agents for this loop; the assembly reading is
  the agents' job, not a separate phase.

**Tooling and process sessions** (the goal changes how the pipeline works:
runner, sweep, classifier, hooks, docs, layout) start with **parallel
read-only investigation agents** — one per independent question (the
affected tools, the assembly shape, the probe statistics, the docs, the git
history) — and synthesise their reports into a short plan with evidence and
numbers before proposing changes. Then:

- Investigation agents are read-only: no source edits, no runner batches, no
  `make`. They report facts with file/line references and counts.
- Implementation is delegated to coding agents with a precise spec (files,
  functions, tests, constraints). Run one agent per independent change in an
  isolated git worktree; forbid them from editing `AGENTS.md`, `README.md`, and
  `disasm/src` unless that is the task, and require the unit-test suite to pass
  before they commit on their branch.
- Live-runner work (probing, gating, renaming, extern cleanup) must run in the
  main checkout, one process at a time, and must never overlap with a merge.
- The coordinating session merges branches in order, resolves conflicts, reruns
  `tools/run_tests.sh`, folds the agents' "doc notes" into this file, and
  commits. Reviewing and integrating stays with the coordinator; writing code
  is delegated.
- Measure before and after. Every process change must cite the metric it moves
  (`tools/report_candidate_yield.py`, `tools/near_miss_kinds.py report`,
  `COVERAGE.md`, `tools/name_decompiled.py debt`).

### 1.2 Shared-checkout etiquette

- Several sessions may use this checkout. Foreign modified `disasm/src` files
  or live `disasm/probes/.pragma_probe_*` trees mean another runner
  transaction is in flight: do not build, commit, or run the runner over it.
- Commit your own finished work promptly and **by explicit path**; never sweep
  foreign edits into your commit.
- Prefer one git worktree per session for tooling work. Worktrees fall back
  read-only to the sibling checkout for `disasm/asm` and probe stats.
- Restart the MCP server after editing `tools/try_pragma_compare*.py` (the
  module is loaded once per server process).

### 1.3 Commits and hooks

- Enable the tracked hooks once per checkout: `git config core.hooksPath .githooks`.
- `.githooks/pre-commit` runs every executable in `.githooks/pre-commit.d/`:
  `10-coverage.sh` regenerates and stages `COVERAGE.md` from the index so the
  number lands in the commit it describes; `15-provenance.sh` blocks removing a
  `GLOBAL_ASM` pragma that has no `accepted` runner attempt on file
  (`DECOMP_PROVENANCE_SKIP=1` bypasses, only with a stated justification);
  `20-tests.sh` runs `tools/run_tests.sh` when `tools/*.py` is staged
  (`SKIP_TOOL_TESTS=1` bypasses). There is no post-commit hook any more.
- Commit verified batches per source file or per sweep run, not one function
  per commit. A commit message names the subsystem or family, not a single
  helper.
- `COVERAGE.md` is generated; never hand-edit it. `README.md` only points at it.
- Tests that create throwaway git repos must strip `GIT_DIR`, `GIT_INDEX_FILE`
  and friends from their subprocess environment (see `_GitFixture`): the
  pre-commit hook exports them, and an unstripped fixture commits onto the real
  branch and can flip `core.bare`. If git suddenly reports "must be run in a
  work tree", run `git config core.bare false`.

## 2. Decompilation process rules

1. `pret/pokestadiumgs` is the immutable US-ROM matching baseline; the vendored
   copy lives in `disasm/`. The original assembly is the comparison oracle.
2. An assembly owner is replaced by C only when the full ROM stays
   byte-identical (`make -C disasm COMPARE=1`). A `.text` byte match, a
   permuter score of 0, or a similarity of 1.0 is evidence, never proof.
3. Every candidate goes through the MCP runner (`try_pragma_candidates`):
   isolated object probe first, then link-shape verification, then the ROM
   gate. Never test a hypothesis by hand-editing a tracked source; manual edits
   are for documentation or deliberate post-acceptance cleanup only.
4. Try about 10 plausible compiler-faithful variants for ordinary functions,
   10–50 for difficult ones when justified; stop after the first accepted
   candidate. Change the hypothesis family when a diagnostic repeats instead of
   resending the same body.
5. Read the runner's per-attempt diagnostics (`status`, `mismatch_kind`,
   `similarity_score`, `first_diff_*`, `link_verified`, `expected_tail_kind`)
   and act on the class: `register_allocation_only` → declaration order,
   temporaries, widths; `immediate_drift` → offsets, strides, literal widths;
   `section_layout_drift` → definitive rejection (see 2.7); `symbol_size_drift`
   / alignment tails → `#pragma C_FUNCTION_PADDING(n)` or a `<owner>_padding`
   helper, only for verified layout bytes.
6. Shared declarations for a batch go in the `declarations` argument, not in
   every candidate; `tools/dedupe_externs.py --apply --verify` cleans up
   duplicates left by earlier batches.
7. Jump tables: splat originally placed every `jtbl_*` in a shared data/rodata
   blob, so a C `switch` (whose table IDO emits into the owner's `.rodata`)
   shifted the ROM (`section_layout_drift`). The fix is a per-file `.rodata`
   subsegment in `disasm/yamls/us/rom.yaml` (`- [rom, .rodata, <file>]` plus a
   retyped `rodata` tail), re-split with the pinned spimdisasm, and the
   hand-written alias lines re-applied to `pokestadiumgs.ld`; verified
   byte-identical for a text-segment file and a fragment. Before decompiling
   a `dispatcher_switch` / `jump_table_map` owner, give its file a subsegment
   with `python3 tools/add_rodata_subsegments.py plan|for-jtbl` and gate the
   still-assembly owner first. Details, gotchas, and the run-by-run plan are in
   `docs/JUMP_TABLES.md`.
8. Name a function at the moment it is decompiled (a renamed pragma owner loses
   its `.s`; see `DECOMP_SETUP.md`). After a batch is accepted run
   `python3 tools/name_decompiled.py apply --verify` (or set
   `PRAGMA_NAME_ON_ACCEPT=1` for the runner) so evidence-backed Stadium 1 /
   `gs_names.json` names land in the same change. Until then, record intended
   names as `// type:func Name` comments in `symbol_addrs_code.txt`.
9. The ROM gate runs `make -C disasm COMPARE=1` with the host-side clang
   syntax check enabled (`PRAGMA_GATE_CC_CHECK=0` opts out for diagnosis
   only). A candidate that matches bytes but fails the check is not
   installable: it would break the next plain `make`. The Makefile keeps
   IDO-accepted int/pointer conversions as warnings; a real arity or
   declaration mismatch must be fixed in the candidate (for example an
   old-style `void f()` definition when byte-matched callers pass arguments).
10. Probe statistics are the process memory. They must never be disabled during
   real work, and their location (`disasm/probe-stats/`) is outside `build/`.
   Any decompiled owner without an `accepted` row is a process violation the
   pre-commit hook rejects.
11. Document a recurring pattern in §4 only with its evidence count and its
    limits; use it to order candidates, never to skip the gate.

## 2.5 The hand-decompilation loop

This is the default working mode. Volume now comes from reading assembly and
writing compiler-faithful C, with the runner as the oracle. Work one source
file at a time so declarations, structs and names accumulate in one place.

### Pick targets in this order

1. **Near-misses at ≥ 0.95 similarity** — `python3 tools/near_miss_kinds.py
   list --kind register_allocation_only|immediate_drift|
   operand_or_scheduling_drift --min-similarity 0.95`. About 385 owners sit
   here with a recorded best candidate; each is usually one source-shape change
   away. Read the recorded `first_diff_*` instructions and `mismatch_kind`
   before writing anything.
2. **Files that already have their `.rodata` subsegment** (the 26 text-segment
   files listed in `docs/JUMP_TABLES.md`): their `dispatcher_switch` /
   `jump_table_map` owners can now be written as a C `switch`. For a fragment
   dispatcher, add the subsegment first (`tools/add_rodata_subsegments.py
   for-jtbl`, re-split, gate the assembly owner) — see §2 rule 7.
3. **The rest of a file you are already in**: `python3 tools/pragma_targets.py
   targets --source disasm/src/<file>.c` ranks its remaining owners by size and
   family. Finish a file's small owners before moving on; every solved
   neighbour is a struct/ABI hint for the next one.
4. **65–128-instruction owners** (about 1,900) by family: `init_sequence`,
   `call_chain`, `float_math`, `predicate`, `state_field_access` are the
   shape-predictable ones. Leave `large_mixed` (>256) for last.

### Work one function

1. `get_function_asm` / read the `.s`. Note argument masks (`andi 0xff` →
   `u8` parameter), frame size (`addiu $sp`), saved registers, stack-arg
   loads, narrow loads/stores, and the return tail (`jr`/`nop` duplicates,
   alignment nops).
2. `draft_candidates` gives an m2c draft plus `similar_solved` (accepted
   bodies with the same opcode shape). Start from the closest accepted
   winner's spelling, not from m2c, when similarity is high and the length
   matches. Check the neighbouring solved functions in the same file.
3. Write 5–10 variants that differ in one hypothesis each (declaration order,
   temp widths, index-vs-pointer form, guard-return vs assign-then-return,
   explicit temporaries, old-style callee prototypes). Use the §4 table to
   order them. Put shared externs in `declarations`, not in each body.
4. Send them as **one probe-only batch** (`gate: false`) with descriptive
   labels (`<family>:<shape>:<hypothesis>`, e.g. `lookup:guard-return:u8-arg`).
   Read the per-attempt result: `mismatch_kind`, `first_diff_offset`,
   `expected_instruction_text` vs `actual_instruction_text`,
   `similarity_score`, `expected_size` vs `actual_size`, `expected_tail_kind`.
5. Iterate on the diagnostic, never on intuition alone:
   `register_allocation_only` → declaration order, temporaries, widths;
   `immediate_drift` → offsets, strides, literal widths, frame padding;
   `symbol_size_drift` / tail kinds → `C_FUNCTION_PADDING` or a `_padding`
   helper; a `section_layout_drift` on a `switch` → the file needs its
   subsegment first. A `similarity_score` of 1.0 with different registers is
   an operand-order or declaration-order problem, not a semantic one.
6. Gate the first probe hit (`gate: true`). Then name it if evidence exists
   (`python3 tools/name_decompiled.py plan`), and move to the next owner in
   the file.
7. Stop after ~15 variants unless the best is ≥ 0.95; leave the record (the
   near-miss tooling and `similar_solved` build on it) and move on. Do not
   commit a body that only matches with `DECOMP_PROVENANCE_SKIP`.

### Batches and commits

- Commit per source file or per working block (five to twenty owners), with a
  message naming the file or subsystem; do not commit one helper at a time.
- Run `python3 tools/dedupe_externs.py --apply --verify` when a file's extern
  block has grown, and `name_decompiled.py apply --verify` at the end of a
  session.
- When a shape matches for the second time with the same spelling, add a row
  to §4 with the evidence count and limit.

### When a sweep is still worth running

- `--near-miss --near-miss-parallel 4 --near-miss-kind-seconds 300` overnight on
  the ≥ 0.95 pool (about 5% conversion; the only sweep that still pays).
- `--skip-attempted` bands right after a new variant spelling or rewrite rule
  lands in `sweep_targets.py` / `near_miss_kinds.py` — it costs nothing when
  there is nothing new to try.
- `--large` only with a budget above 180 s per owner; at 180 s it drafts
  well (median 0.89 similarity) but does not close.

## 3. Tool reference

### 3.1 Runner and MCP

- `tools/try_pragma_compare.py` / `tools/try_pragma_compare_mcp.py` — the
  candidate runner. MCP tools: `try_pragma_candidates` (`gate: false` for
  probe-only batches; `declarations` for shared externs; `source` may be
  omitted when every candidate resolves to one owner), `find_owner`,
  `get_function_asm`, `list_targets`, `draft_candidates` (m2c drafts plus
  `similar_solved`), `permute_candidate`.
- Probe compiles bypass `make`: the recipe is captured once per Makefile
  revision and asm-processor/IDO run directly (~0.3–0.7 s per probe; the ROM
  gate is ~2 s incremental). Probe sources live under ignored `disasm/probes/`.
- A `.text` hit is checked against the baseline object's link shape. Verified
  hits (`link_verified: true`) share one combined gate; unverified hits gate
  sequentially; `section_layout_drift` is rejected immediately. Winners are
  installed incrementally; a winner that only conflicts in combination is
  reported `combined_compile_failed` and not retried alone.
- Results and stats carry `timing` (`probe_seconds`, `gate_seconds`,
  `gate_runs`, `gate_mode`) and `batch_status`. Tune batch size and workers
  from those, not from guesses. `PRAGMA_COMPILE_TIMEOUT`,
  `PRAGMA_COMPARE_TIMEOUT`, `PRAGMA_PROBE_WORKERS` are the knobs.
- m2c and decomp-permuter are optional clones under `disasm/tools/`
  (`tools/setup_decomp_tools.sh`); their absence is an explicit error.

### 3.2 Probe statistics

- Default file `disasm/probe-stats/probe-stats.jsonl` (schema 2: batch rows
  carry `timestamp`, `batch_id`, `worktree`, `git_head`; attempts carry
  `family`, `label`, `status`, `mismatch_kind`, scores, `candidate`,
  `declarations`, a 2000-char `diagnostic`; `assembly_diff` is runtime-only).
  Rotates at 64 MiB to `probe-stats.<N>.jsonl`; every reader includes rotated
  and legacy (`disasm/build/probe-stats.jsonl`) files. `PRAGMA_PROBE_STATS`
  overrides the path; empty disables (tests only).
- `python3 tools/probe_stats.py migrate` folds the legacy file in once.
- `python3 tools/report_candidate_yield.py` — attempts, compile-fail rate,
  probe matches and accepts per label prefix. Cite it when changing variants.
- `python3 tools/check_decomp_provenance.py --staged` — the pre-commit guard.

### 3.3 Discovery and drafting

- `python3 tools/pragma_targets.py targets [--family F] [--limit N]` — remaining
  owners ranked by instruction count with family classification and
  `family_counts`; `draft <func>` and `similar <func>` for m2c drafts and
  solved-shape neighbours.
- `tools/scan_asm_families.py` — the family classifier and bundle generator.
  Families: `bounded_lookup`, `state_field_access`, `constant_map`,
  `direct_wrapper`, `multi_call_wrapper`, `call_sequence`, `jump_table_map`,
  `loop_or_state_machine`, plus the shape sub-families `call_chain`,
  `dispatcher_switch`, `large_mixed`, `init_sequence`, `float_math`,
  `state_machine`, `predicate`, and `unclassified`.
  `tools/analyze_family_shapes.py` prints the feature clusters behind them.
- `tools/xmatch_stadium1.py --near-source <c>` and `tools/s1_transfer.json` —
  Stadium 1 shape neighbours and evidence-backed names (hints, never proof).
- `tools/s1_transfer_sweep.py` — transplants Stadium 1 bodies onto GS pragmas
  (`s1:` labels; `--dry-run` first). `tools/template_transfer.py` /
  `sweep_targets.py --templates` — rewrites an accepted winner of identical
  opcode shape onto the target (`template:` labels).

### 3.4 Sweeps (saturated for ≤64-instruction owners since 2026-08-27; see §2.5)

- `tools/sweep_targets.py` — the small-function loop: listing filter → m2c
  draft → mechanical rewrites → isolated probes per source → gated install →
  padding/duplicate-tail retries. Read its per-family summary (`best:*`,
  `kind:*`, `near_miss_ge_0.9`, `remaining`) before hand-writing variants.
  Options: `--fragment-range A-B` (exclusive band: nobody else touches it while
  it runs), `--skip-attempted` (per function+label), `--exclude-family`,
  `--min-family-remaining`, `--large` (owners >64 instructions via
  `--gotos-only` drafts straight into permute-and-gate), `--variant-policy`.
- Variant selection is data-driven (`tools/variant_policy.py`): a retry
  spelling runs only when it is unexplored (<30 attempts) or has a recorded
  accept/probe-match rate above zero. The pointer-retry trio
  (`ptr-void`/`ptr-s32`/`u32-void`) is no longer emitted automatically (738
  attempts, 0 accepts); function-pointer calls get a `fnptr-cast` variant;
  missing prototypes fall back to synthesized old-style declarations from
  `repo-prototypes-fallback.h`.
- Near-miss program: `python3 tools/near_miss_kinds.py report` shows the
  open-owner pool by `mismatch_kind` × similarity band;
  `sweep_targets.py --near-miss-kinds [--kinds ...] [--min-similarity 0.9]`
  runs the deterministic kind-specific rewrites (declaration-order permutations,
  width swaps, temp hoist/inline, operand swaps; offset/frame/literal/stride
  repairs; statement split/merge and loop-form swaps) through probe-only
  batches and gates the hits before any permuter time. `--near-miss` remains the
  permuter path (`--near-miss-kind-seconds` gives `register_allocation_only`
  and `immediate_drift` a longer budget).

### 3.5 Naming and coverage

- `tools/name_decompiled.py plan|apply|debt` — applies evidence-backed names
  to decompiled `func_` symbols everywhere (`symbol_addrs_code.txt`, C
  sources, includes, and the `.s` tree), refuses collisions per row, logs to
  `disasm/probe-stats/renames.jsonl`; `--verify` runs the ROM gate.
- `tools/apply_names.py` — the general naming applier (`--dry-run`, `--check`,
  `--qa`); `docs/NAMING.md` explains the evidence rules.
- `tools/update_coverage.py [--staged|--revision R]` — generates `COVERAGE.md`
  (totals plus per-file remaining owners).
- `tools/run_tests.sh` — the unit-test suite (`unittest`, no pytest).

## 4. Verified source-shape heuristics

Each entry: shape → spelling that matched → evidence → limit. Order candidates
by these; always probe and gate.

| Shape | Spelling that matched | Evidence | Limit |
|---|---|---|---|
| Wrapper returning a callee result vs void | Direct `return f(...)` / plain call, exact prototype and call order; explicit temporaries in multi-call wrappers | many owners | — |
| Fixed-stride byte-flag pool scan | Uniquely named padded local record, `s8` flag at the proven offset, `s32 i`, result initialised before the pool load, post-incremented record pointer | 1 S1 transfer | same scan only |
| `lbu`/`andi`/`jr`/`sb` flag clear | `arg0[off] &= 0xFF7F` (`0xFFFE`) on a `u8 *`, literal 16-bit mask kept | 2 | same load-mask-store shape |
| `lbu` index → pointer table → `lbu`/`ori`/`sb` | `table[index][off] \|= lit` with `u8 *[]` table declared locally; byte-typed argument when the asm masks it | 2 (+1) | — |
| Four `sh` stores at 0/2/4/6, fifth value from stack | `u8 *` plus `u16 *` casts, `s32` params, explicit halfword widths | 2 | no struct inferred |
| Two-component `s16` add/sub | add: uniquely named two-`s16` struct; sub: explicit `u8 *` offsets — probe both | 2 | — |
| Three-component float copy | `arg0[0..2] = arg1[0..2]` on `f32 *` | 3 | exact 3-copy shape |
| `lhu`/`andi` bit test | `s32 result = 0; if (global & mask) result = 1; return result;` with `u16` global | 5 | no ternary / compact bool |
| Byte-argument state predicates | `u8` parameter, initialised `s32` result, nested explicit checks over raw byte offsets | 4 | `s32` params did not match |
| Word-field predicates | Uniquely named local struct overlay padded to 0x10/0x14, comparison written `arg0 == state->value` | 2 | overlay is local |
| Isolated stack-slot immediate drift | 12-byte local with 4-byte leading pad; declare a temp pointer before the saved-result pointer | 3 (`14640.c`) | only for slot drift |
| Forwarded 3-arg wrapper into 5-arg helper | Four-word `s32 locals[4]`, pass `&locals[2]`, `&locals[1]` | 2 | keeps 0x30 frame |
| Post-call index fallback | Keep the incoming index formal in place; single `u8 *` temp from `(u8 *)(u32)f(arg0) + (arg1 << 4)` | 1 | — |
| Compact enum dispatcher | C `switch` over a `u8` global with literal cases | 1 | blocked by §2.7 when a jtbl is emitted |
| Resource initializer | Byte-stride global write, `s32`-indexed `while (i < table[arg][bound])`, final wrapper call | 1 | same table/loop shape |
| Multi-local near-miss | Declare fixed stack locals ascending (`sp24, sp26, sp28`) rather than m2c's descending order (`stack-slots-ascending` retry) | audit | — |
| Duplicate `jr`/`nop` tail | Empty owner + uniquely named `<owner>_padding(void) {}` helper | 1 | not for alignment-only tails |
| Trailing alignment nops | `#pragma C_FUNCTION_PADDING(bytes)` | several | verified layout bytes only |
| Bounded lookup returning a value | Guard-clause early return `if (cond) return table[i]; return 0;` first; assign-then-return second; ternary last; `u8` param when the asm masks with `andi 0xff`; compound condition read from the real second range check (`blez` → `> 0`, `bltz` → `>= 0`); non-power-of-two strides from the `sll`/`subu`/`addu` chain | 9/14 guard, 5/14 assign, 0/14 ternary | — |
| Globals loaded with `lw` into an argument | Try `void *` before `u32` | scan | no help for `lui`-before-`sw $ra` scheduling drift |
| Near-miss `immediate_drift` with an `addiu $sp` frame mismatch | `near_miss_kinds` `frame-padding` (add/remove a pad local to hit the baseline frame) | 2/2 probe hits accepted (first bounded run, 2026-08-27) | — |
| Near-miss `register_allocation_only` / `operand_or_scheduling_drift` | `commute-swap`, `decl-order`, `hoist-temp`, `type-width`, `loop-form`, `reorder-store-call` | 0 hits in 146 attempts on the first run — treat as unproven; prefer hand analysis of the first differing instruction | — |
| Float divide by a power of two | Divide by the **integer** literal (`x / 16`), not `16.0f`: a float literal divisor is strength-reduced to `mul.s` by the reciprocal, an int divisor keeps `div.s` | 1 (`func_8130A98C`) | — |
| Guard/return polarity | IDO branches on the negated condition: write the `if` in the polarity whose negation is the observed `beq`/`bne`, e.g. `if (arg1 == x) { ... } return v;` rather than `if (arg1 != x) return v;` | 2 (`func_81306EE0`, `func_80059234`) | — |
| Several `return 1;` guards sharing one epilogue | A single `return a \|\| b \|\| c \|\| d;` expression; separate guard clauses allocate differently and add bytes | 1 (`func_8130AA54`) | — |
| Wrapper whose callee result feeds a conditional second call | `s32 result = f(arg0, N); if (result != 0) { g(arg0); } return result;` (second call's value discarded; `$v1` spill/reload across the call is the tell) | 3 (`func_8005A0B4/A0F4/A134`) | — |
| Table-field forward with 112-byte stride into bcopy/bzero | Load the field into an explicit `s32 v0 = *(s32 *)(D_X + idx * 112);` **before** the call; inlining it into the argument reorders the frame allocation | 6 (`585D0.c`) | same stride/forward shape |
| Non-power-of-two stride (`arg2 * 47`) | Hoist the multiply into its own local declared **before** the table-load local to fix `addu` operand order | 2 (`func_8005C880/C988`) | — |
| Selector index into two parallel tables | `idx = f(SEL, -1); if (arg0 == 0) D_A[idx * 0xC] + ADD else D_B[idx * 0xC] + ADD` — note the inverted condition sense | 11 (`517E0.c` wrapper family) | — |
| Small struct copy from a returned pointer | Uniquely named `typedef struct { s32 a, b; }` and `*arg0 = *(Pair *)((u8 *)ret + off);` | 3 (`func_80054210/8005493C/8005487C`) | — |
| Nested command constructor from a fixed record | Use a local typed overlay with the proven padding/child field, then pass the nested field directly to the helper; keep each constructor's exact field width | 10 (`229E0.c`: `func_8003FD98/3FE6C/40004/40050/4009C/400E8`; `4EE50.c`: `func_8004E868/4E8D0/4E9C8/4EA60`) | only when the record offsets and helper call shape are proven |
| Fixed-record parser/serializer with narrow fields | Keep the raw record base, use explicit `u8`/`u16` temporaries and direct offset loads/stores; parser loops use the observed break/fill shape, serializers keep the observed conversion order | 8 (`615D0.c`) | exact record format only; do not infer a shared struct from this pattern |
| Byte-indexed state-table loop | Use a byte-typed argument/index, initialize the table pointer before the loop, and preserve explicit post-increment/index updates around the lookup | 2 (`615D0.c`: `func_80060B28/60F98`) | only when the assembly shows byte masking and the same loop-carried pointer |
| Aligned pool wrapper with conditional initialization | Round the requested size with `(arg0 + 3) & ~3`, declare the allocation local before the result, and initialize/return the result only when the block is nonzero | 2 (`3A00.c`: `func_80002E00/030D0`) | same pool-allocation wrapper shape |
| Aligned graph-node constructor wrapper | If the pool handle is nonzero, replace the incoming result with `MainPool_AllocAligned`; if the result is nonzero, call the constructor with the observed old-style narrow-field formals, then return it | 4 (`4EE50.c`: `func_8004E368/4E3C8/4E438/4E52C`) | only for the matching allocation/constructor call sequence |
| Callee prototyped earlier as `void` but its return is needed | Block-scope re-prototype does not work (hard "redeclaration" error); the earlier definition must change to return the value — do it as a separate gated change | 1 (`func_80055BA8`, open) | — |
| Wrapper called with four registers but only three read | Declare only the parameters the body reads (`a3` was caller garbage); the fourth formal changes the frame | 1 (`func_841518D0`) | — |
| General | Preserve narrow `sb`/`sh`/`sw` widths, initialise results before NULL checks, raw 32-bit address arithmetic (`(u8 *)(u32)global + off`) before inferred structs, `uintptr_t` casts for raw addresses, explicit `s32` loop counters, array-index vs pointer-add as separate variants, deliberate signed/unsigned masks | repo scan | ABI hypotheses until compared |

Type spellings: `u8-void` and `s32-s32` account for essentially all m2c-draft
accepts; other widths only on diagnostic evidence via the variant policy.

## 5. Tooling backlog and recurring unsolved shapes

- Runner: `probe_error` / `list index out of range` on the last pragma owner
  of a file when the function has trailing alignment nops
  (`func_8005633C`, `func_8130CDD4`, `func_80021BBC`); reproduces with a trivial body, so it
  is a diagnostics-path bug, not a candidate problem.
- Runner: `654A0.c` cannot get its `.rodata` subsegment until asm-processor
  handles mixed 4/8-byte `.late_rodata_alignment` without growing `.text`.
- Shape: `u8 *p = arg0 + 4; p[arg1 + 8] = 0xFF; p[0] |= 2;` — IDO keeps the
  table pointer in `$t7`; no declaration-order/pointer-form variant reproduced
  it (`func_841523BC`, `func_84151CD8`, likely `func_84151DD4`). Needs a
  dedicated variant family.
- Shape: decrement/increment counter pairs stuck at similarity 1.0 with
  `$v0`/`$v1` swapped (`func_8130B91C`, `func_8130B95C`).
- Shape: 15-case dispatcher `func_80050D20` matches except for how IDO shares
  the last case's tail with `default` (size 200 vs 196).
- Shape: jump-table owners can remain normalized matches with relocation-only
  immediate drift even after a file has a `.rodata` subsegment
  (`func_80060AC8`, `func_80060B74`, `func_8006179C`, `func_80067930`,
  `func_80002178`); preserve the assembly owner until the table offset is
  proven rather than accepting the normalized score.
- Shape: large fixed-record constructor `func_8004E610` reaches similarity 1.0
  with equal 312-byte output, but IDO assigns the stack byte load to a
  different temporary (`$t0` versus `$t8`); declaration-order and temporary
  variants did not resolve it.
- Shape: `func_8004E298` remains an instruction-drift near miss (100 generated
  bytes versus 112 expected), with the first difference in the ABI stack-home
  sequence; do not pad it without proving the missing body shape.
- Shape: `func_80067800` has a one-instruction return-tail drift and the
  permuter cannot assemble its `.late_rodata_alignment`; preserve the helper
  until the late-rodata path is repaired.
- Sweep families other than `frame-padding` in `near_miss_kinds` have no
  accepts yet (0/146); re-evaluate after the fleet's records accumulate.
