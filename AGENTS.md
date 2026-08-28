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

- One file per agent, never shared (the runner enforces it: the first install
  into a file claims it in `disasm/probe-stats/claims.json`, and another live
  session's install is refused with `file_claimed_by_other`). Pick files with
  `python3 tools/pragma_targets.py rank-files --exclude-recent 4` — it scores
  files by recorded probe hardness (`fresh` owners with < 5 attempts plus
  `drift` owners; register ties count zero) and hides files touched by any
  session in the window or dirty in the tree — and cross-check with
  `python3 tools/file_claims.py free --exclude-recent 4`, which also sees
  claims that have not been committed yet. `score` is a count, not a rate:
  look at the `ties` column before trusting a big file at the top.
- Before assigning a file run `python3 tools/analyze_family_shapes.py
  siblings --source <file>`: if its owners cluster around a shared `jal`
  target or carry a `gbi-macro` tag, the agent's first job is the shared
  callee (`unlock --function <callee>` shows how many owners it unblocks),
  then the siblings with the same spelling. `siblings --all --top 30` ranks
  the largest unsolved families tree-wide (984 groups on 2026-08-28; the
  biggest have 7–12 members).
- The agent prompt is now: "Read `docs/FLEET_AGENT.md`; your file is
  `disasm/src/<X>.c`; time box N minutes." That document carries the §2.5
  loop, the §4 table, the runner field cheat-sheet, `tools/fleet_probe.py`
  (JSON batch in, diagnostic table out) and `tools/file_brief.py` (solved
  signatures, extern block, record strides, SDK macros, and the callees
  defined later in the file), the hard rules, and the report format. Add
  only the file-specific facts (`.rodata` subsegment status, owners to skip).
- When agents report, fold every *second* confirmation of a spelling into §4,
  add runner bugs and recurring unsolved shapes to §5, then reassign files.
  Do not run tooling changes and a fleet at the same time in one checkout.
- Do not spawn investigation agents for this loop; the assembly reading is
  the agents' job, not a separate phase.
- `docs/FLEET_AGENT.md` already carries the lessons of 2026-08-28: search
  only inside the repository (a `find / -iname gbi.h` walked `~/Music` and
  raised a macOS media-library prompt; the header is
  `disasm/lib/ultralib/include/PR/gbi.h`), per-agent scratch directories
  (`$CLAUDE_JOB_DIR/tmp/<file>/`; agents overwrote each other's `batch1.py`),
  and the per-owner cap (~12 variants / ~8 minutes; stop after two batches at
  `register_allocation_only` ≥ 0.99 — the runner now says so itself via the
  `futility` field). Register ties go to the permuter, not to agents:
  `docs/REGISTER_TIES.md`.
- Measure yield per file after the first box and do not reassign a file that
  yielded fewer than two accepts: its remaining owners go to §5. Wave of
  2026-08-28 on the six text-segment files no session had touched for 19
  hours (`585D0` ×2, `14640`, `6E850`, `CE80`, `4AC10`): 12 accepts from
  ~295 variants and ~1.25M tokens (~105k per accept versus ~17k in the
  pilot), and half of them came from one file (`4AC10`, 6/14, where a single
  spelling — the `gbi.h` macros — unlocked a family). Files left untouched by
  a running fleet are usually untouched because their small owners are
  register-allocation ties, not because nobody got to them. When the
  text-segment pool looks like that, point the wave at fragments (the
  concurrent fleet kept landing 5–6 commits/hour there) or at the ≥ 0.95
  near-miss pool.
- Two coordinators in one checkout: a coordinator that commits with a broad
  stage (`git add -A`, `git commit -a`) sweeps the other fleet's uncommitted
  installs into its own commits (`0525ec9`); commit by explicit path only,
  and treat a dirty file as owned even when `git log` shows no recent commit.

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
  number lands in the commit it describes; `12-claims.sh` runs
  `tools/check_file_claims.py --staged` and blocks committing a `disasm/src`
  file that another live session's runner claim covers, or claimed files from
  two sessions at once (`PRAGMA_CLAIMS_SKIP=1` bypasses with a justification;
  `CLAIMS_OWNER=<tag>` lets a coordinator commit for its own agents; a claim
  whose session tag is a bare `$PPID` — no `CLAUDE_JOB_DIR` — only warns);
  `15-provenance.sh` blocks removing a
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
  work tree", run `git config core.bare false`. The same applies to any tool
  that shells out to `git` and may run nested inside the hook
  (`file_claims.py`, `check_file_claims.py` strip them).
- Tooling sessions merge their agents' worktree branches on an integration
  branch first, then into `master`; `.claude/worktrees/` is ignored. Agents'
  commits carry a hook-regenerated `COVERAGE.md` from the worktree state —
  take `master`'s copy before merging.

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
7. Stop after two probe batches once the best is `register_allocation_only`
   at ≥ 0.99 (the result's `futility` field says so): that owner belongs to
   the permuter (`docs/REGISTER_TIES.md`), not to more hand variants.
   Otherwise stop after ~15 variants unless the best is ≥ 0.95; leave the record (the
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

- Result fields added 2026-08-28: every attempt carries `prior_attempts`,
  `best_prior` (`{similarity_score, raw_similarity_score, mismatch_kind,
  label, timestamp}`), `futility` (`register-tie: …` / `stuck: …` / null),
  `raw_similarity_score` next to `similarity_score`, and
  `normalized_only_match` (≥ 0.99 normalised but < 0.9 raw — the 1.0 that
  hides swapped fields); the batch carries `futility_summary`. Callees
  defined anywhere in the target file get their real signature injected
  instead of the `s32` fallback prototype.
- `companion_edits=[{"function", "old", "new"}]` (API and MCP) applies an
  exact-once edit to an already-accepted body or prototype in the same file
  for both the probe and the gate and installs it only together with the
  candidate; the stats row records the edited function names. It may not add
  or remove a `#pragma GLOBAL_ASM`. Use it for the §4 "callee prototyped as
  `void`" and "caller passes fewer arguments" cases; the function-pointer
  cast spelling in the T5 example is unverified until a gate accepts it.
- `tools/fleet_probe.py batch.json [--gate] [--json out]` — CLI front end for
  agents that are not wired to the MCP server; prints one row per attempt and
  a per-function verdict (including "register tie — stop").

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

- `python3 tools/near_miss_kinds.py tag-ties [--min-attempts 6]
  [--min-similarity 0.99] [--names]` — every owner whose best attempt is a
  register tie, with total attempts and whether the permuter already ran on
  it (`permute:` labels); 248 owners on 2026-08-28, some with 100–190
  recorded hand attempts.

### 3.3 Discovery and drafting
- `python3 tools/pragma_targets.py rank-files [--exclude-recent H]
  [--no-fragments] [--json]` and `targets --source <file> --skip-ties` —
  hardness-aware file ranking and owner listing (`prior_attempts`,
  `best_similarity`, `best_mismatch_kind`, `hardness` = fresh/drift/tie/stuck
  per owner). `--exclude-recent` uses an absolute timestamp because `git log
  --since="4.0 hours ago"` silently matches the whole history.
- `python3 tools/file_brief.py <file> [--json]` — read this before touching a
  file: solved signatures, extern block, symbols by solved-body count, record
  strides, SDK macros, and the callees defined later in the file with their
  real return types.
- `python3 tools/analyze_family_shapes.py siblings --source <file> |
  --all --top N` and `unlock --function <func>` — opcode-shape clustering of
  remaining owners (registers/immediates abstracted, `jal` targets kept,
  edit distance ≤ 0.15) with the closest solved body and `gbi-macro`
  tagging; `unlock` lists the remaining owners that call a helper.

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

- `python3 tools/sweep_targets.py --near-miss --tie-pool --near-miss-parallel 4
  --near-miss-kind-seconds 300` — the standing overnight permuter run over the
  `tag-ties` pool; `--targets-file names.txt` pins an explicit list.
  `--skip-attempted` never applies to `--near-miss` (by design).

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
| Display-list append (`Gfx` command into `D_800D0510++`) | Use the real `gbi.h` macros — `gSPDisplayList(D_800D0510++, addr)`, `gDPSetFillColor`, `gDPFillRectangle` — never hand-written `p->words.w0 = ...; p->words.w1 = ...;` stores, which stall at 0.93–0.95 on a constant-load/pointer-increment scheduling swap | 6 (`4AC10.c`: `func_8004AC24/AE3C/AF18/A5B8/A708/AD00`) | RDP texture-load sequences (`gDPSetTile`/`gDPLoadBlock`, `func_8004A010`) not yet tried |
| Several `return 1;` guards sharing one epilogue | A single `return a \|\| b \|\| c \|\| d;` expression; separate guard clauses allocate differently and add bytes | 2 (`func_8130AA54`, `func_80057A80`) | — |
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
  (`func_8005633C`, `func_8130CDD4`, `func_80021BBC`, `func_8001FC60`,
  `func_80071E48`); reproduces with a trivial body, so it
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
- Shape: `func_8004B010` (`4AC10.c`, 0.94) re-reads global `s16 D_800950D0`
  after a call and stores `(v + 1) % 12`; every spelling either adds an 8-byte
  spill or lets IDO CSE the address across the call. Next targets in that
  file are the RDP texture-load sequences `func_8004A010` (+ `A174/A2E0/A44C`
  which call it 8× each) with `gDPSetTile`/`gDPLoadBlock`/`gDPSetTileSize`.
- Runner: a candidate can report `similarity_score` 1.0 through register
  normalisation while `raw_similarity_score` is 0.63 with values swapped
  between struct fields; never treat 1.0 as done without the gate.
- Runner: `probe_unavailable` on `func_8006092C` (`585D0.c`) for a
  well-formed candidate; not isolated.
- Runner (fixed 2026-08-28): the fallback prototype for a callee defined
  later in the same file now comes from a position-independent scan of the
  file (`func_8005D92C` sat on the same line as an `extern`, which the
  line-anchored regex missed). `sweep_targets.py`'s
  `_SOURCE_FUNCTION_DEFINITION_RE` has the same line-anchoring defect and is
  not fixed yet. Still open: a same-file forward call to a still-pragma
  function fails the moment that pragma becomes a C definition unless an
  earlier accepted candidate carried the forward prototype in its
  `declarations` (`CE80.c`: `func_8000DDC8`/`func_8000DE34`, five callers).
- Shape: a callee that an already-accepted caller invokes with fewer
  arguments than its real signature (`func_80018A74(void){ func_8001480C(); }`)
  needs a K&R definition to compile, and the K&R form starts IDO's register
  allocation differently — `func_8001480C` sits at similarity 1.0. Both this
  and the `func_80055BA8` return-type case are now reachable with
  `companion_edits` (§3.1); nobody has gated one yet.
- Shape: fixed-stride byte-flag clear loop (`func_8001644C`, 8 records at
  0x160): IDO unrolls every simple `do { p += stride; *p = 0; } while (p != end)`
  spelling (inserting a `divu`); a pretest `while` got 60 bytes versus 48.
  Needs a spelling that defeats the unroll heuristic.
- Shape: byte-argument helpers in `585D0.c` that compute a record pointer
  and make an out-of-line call before writing through the pointer argument
  overshoot the frame by exactly 8 bytes with a `$v1`/`$a3` swap
  (`func_8005A92C`, `func_8005FC7C`, `func_8005FDB0`); no declaration-order
  or type variant closed it.
- Shape: `D_80128570`/`D_801285D0` 112-byte-stride record lookups sit at
  similarity 1.0 `register_allocation_only` (`func_8005C0B0/C12C/C1AC`,
  `func_8005C2B4/C2FC/C348`, `func_8005D9E0`, `func_8005DFD4`); six variants
  each, nothing moved the allocator. Do not spend fleet time here.
- Shape: forward-call wrappers whose last stack argument is a non-zero literal
  (`func_8005F37C`, `func_8005F5D4`) get a different list-scheduler order
  around the call than the accepted `0`-literal siblings; every source
  reordering gave byte-identical diagnostics.
- Shape: `func_8005CBA0` / `func_8005CAA4` literal switches match except for
  whether the last case shares the `jr` delay slot with `default` (same
  class as `func_80050D20`).
- Shape: `6E850.c` float/matrix owners: `func_8007074C` at similarity 1.0
  (`$a3` versus `$a2` for the persisted state copy), `func_8006EFF0` (0.94,
  IDO spills and reloads `arg1+0x14` through `sp+0x14` as a register-pressure
  artefact), `func_8006E944` (0.89; a bare `x * 1.0f` is constant-folded, a
  named `f32 weight = 1.0f` restores the instruction but costs 8 frame
  bytes), `func_8007065C` (0.88, Gfx command block builder). Leave the file
  to a hand session.
- Shape: `CE80.c` channel-pool helpers: `func_8000DDC8`/`func_8000DE34` spill
  only `$a1`/`$a2` to their homes with a fifth stack argument (0.79),
  `func_8000D174` keeps two address registers IDO folds away (0.88),
  `func_8000D710` (0.90, one register), `func_8000D7B8` (0.86, one missing
  spill slot), `func_8000C6D8` (0.73 at equal size; IDO hoists
  `D_800D1220`/`D_8008FA40` into `$s3`–`$s5` in every spelling).
- Shape: `14640.c`: `func_800186B8` ring-buffer push (0.95; the original
  keeps the record base and stores via `addiu`+offset instead of one folded
  immediate), `func_80013A40` pool allocator (0.68, 12 bytes over, `arg0`
  spilled in every variant), `func_80016AB4` at similarity 1.0 with a
  `u8 *base = arg0;` local but an 8-byte frame difference.
- Sweep families other than `frame-padding` in `near_miss_kinds` have no
  accepts yet (0/146); re-evaluate after the fleet's records accumulate.
