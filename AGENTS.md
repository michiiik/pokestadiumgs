# Repository agent guidance

This file is the entry point for any agent session in this repository. Read it
fully before touching the tree. It has four parts: how to run a session
(§1), the decompilation process rules (§2), the tool reference (§3), and the
verified source-shape heuristics (§4). Historical detail lives in the
referenced docs and in git history, not here.

## 1. Running a session

### 1.1 Two kinds of session

**Decompilation sessions** ("decompile owners in fragment N / family F /
file X") run **fleet mode**: the session is a coordinator that assigns one
source file each to 4–8 Sonnet agents, which follow `docs/FLEET_AGENT.md`
for a 45–60 minute box and report what matched. Measurements and past
incidents behind these rules: `docs/FLEET_LOG.md`.

Coordinator rules:

- One file per agent, never shared, and assignment is manual: install-time
  claims are advisory (§1.2), not a lock.
- Pick files with `python3 tools/pragma_targets.py rank-files
  --exclude-recent 4`, ranking first by **`READY_FRESH`**
  (`actionable_fresh` in JSON), then by `fresh`, not by `score` (`score` counts
  drift owners other sessions already failed on). `JT_UNREADY` marks
  jump-table owners whose file still lacks the required per-file `.rodata`
  subsegment; those are coordinator layout work, not normal fresh slots.
  Cross-check `python3 tools/file_claims.py free --exclude-recent 4` and `git
  status`, and re-check both when reassigning a file for a second box.
- Before assigning, run `python3 tools/analyze_family_shapes.py siblings
  --source <file>`. If the owners cluster on a shared `jal` target or carry
  a `gbi-macro` tag, the agent's first job is that family, not the file's
  smallest owner (`unlock --function <callee>` shows what a helper unblocks).
- `rank-files` is a file-level signal, not permission to choose any owner in
  that file. Before assigning a fresh slot, run
  `python3 tools/pragma_targets.py targets --source <file>` and choose an
  owner with `prior_attempts < 5`, unless the slot is explicitly the oldest
  documented `requeue` or a near-miss/permuter follow-up. A shared family
  unlock never overrides an owner history: do not spend a fresh box on a
  100+ attempt owner merely because its file has fresh siblings.
- The agent prompt is: "Read `docs/FLEET_AGENT.md`; your file is
  `disasm/src/<X>.c`; time box N minutes." Everything file-specific comes
  from `docs/regions/<path>.md`, which `tools/file_brief.py` prints to the
  agent — put new file-specific findings there, not in this document.
- After each box: append the agent's winning spellings and every unresolved
  owner's durable handoff to the region notes (`python3
  tools/region_notes.py append`). A handoff must contain `requeue`,
  `register-tie`, `layout-prerequisite`, or `tooling-blocked`, plus the best
  scores, mismatch/fingerprint, attempted hypothesis families, and next
  action. Fold a spelling into §4 only once two *different* files confirm it,
  and add tool defects to §5.
- A zero-accept box is not permission to abandon the file or rotate its
  owners into an undated skip list. The next wave must reserve a slot for the
  oldest `requeue` owner and resume it with a materially different hypothesis
  before taking fresh work; fresh files fill the remaining slots. A file's
  two-accept yield rule is a ranking signal, not an owner-resolution rule.
  Hand every successor the predecessor's winning spellings, diagnostics, and
  explicit next hypothesis.
- A candidate batch must be preflighted against the selected source. Candidate
  names must still own active `GLOBAL_ASM` pragmas; companion edits may target
  only an existing accepted C definition/prototype and may not target a
  candidate owner. Invalid-owner or invalid-companion diagnostics are process
  evidence and must not consume a hypothesis budget.
- Never introduce a rule through a mid-task message: an agent cannot verify a
  message, and three have refused one as prompt injection. Commit the rule to
  `docs/FLEET_AGENT.md` or this file, then send a pointer to the sha. Messages
  may carry scope changes only (stop, switch file, skip these owners), and
  must never ask an agent to touch a path outside its assignment.
- Do not run tooling changes and a fleet in one checkout at the same time.
- Do not spawn investigation agents for this loop; reading the assembly is
  the agents' job.

### 1.2 Shared-checkout etiquette

- Several sessions may use this checkout. Foreign modified `disasm/src` files
  or live `disasm/probes/.pragma_probe_*` trees mean another runner
  transaction is in flight: do not build, commit, or run the runner over it.
- One source file per agent does not make a shared checkout safe for concurrent
  runner work. The runner lock serializes its rewrite/restore and gate phases,
  but another agent's installed, uncommitted source still makes a global gate
  unsafe and can cause a clean agent to report `tooling-blocked`. Use isolated
  worktrees/snapshots for concurrent runner agents; otherwise serialize runner
  ownership and let the other agents do assembly-only preparation. If a
  foreign source becomes dirty, stop before the next probe and preserve the
  owner as `tooling-blocked` for a later box.
- Commit your own finished work promptly and **by explicit path**; never sweep
  foreign edits into your commit.
- Prefer one git worktree per session for tooling work. Worktrees fall back
  read-only to the sibling checkout for `disasm/asm` and probe stats.
- Restart the MCP server after editing `tools/try_pragma_compare*.py` (the
  module is loaded once per server process).
- A **Codex session** commonly shares this checkout. It does not set
  `CLAUDE_JOB_DIR`, so its claims carry a bare-`$PPID` tag and its commit
  messages are generic ("Decompile fragment NN … helpers"). Treat any dirty
  file as owned by someone.
- Install-time file claims (`disasm/probe-stats/claims.json`, written by the
  runner) are **advisory**: identity is per job, not per agent, so a conflict
  warns and proceeds. `PRAGMA_CLAIMS_ENFORCE=1` makes it refuse. The
  commit-time hook (§1.3) is the guard that matters.

### 1.3 Commits and hooks

- Enable the tracked hooks once per checkout: `git config core.hooksPath .githooks`.
- `.githooks/pre-commit` runs every executable in `.githooks/pre-commit.d/`:
  `10-coverage.sh` regenerates and stages `COVERAGE.md` from the index so the
  number lands in the commit it describes; `12-claims.sh` blocks committing a
  `disasm/src` file another live session's claim covers, or claimed files from
  two sessions at once (`PRAGMA_CLAIMS_SKIP=1` bypasses with a justification;
  bare-`$PPID` identities only warn); `15-provenance.sh` blocks removing a
  `GLOBAL_ASM` pragma that has no `accepted` runner attempt on file
  (`DECOMP_PROVENANCE_SKIP=1` bypasses, only with a stated justification);
  `16-alias-rename.sh` blocks renaming an existing address-keyed entry in
  `disasm/linker_scripts/us/symbol_addrs_code.txt` unless the same commit
  also adds a matching `<old> = <new>;` line to `aliases.ld` (the PR #58/#59
  convention `tools/container_merge.py`'s `merge()` and
  `tools/name_decompiled.py apply` both implement; `ALIAS_RENAME_SKIP=1`
  bypasses with a stated justification); `20-tests.sh` runs
  `tools/run_tests.sh` when `tools/*.py` is staged (`SKIP_TOOL_TESTS=1`
  bypasses). There is no post-commit hook any more.
- Commit verified batches per source file or per sweep run, not one function
  per commit. A commit message names the subsystem or family, not a single
  helper.
- **In a shared checkout, commit with `git commit --only <your path>`, never
  `git add <path> && git commit`.** The git index is shared by every process
  in the checkout, so a plain `git commit` also commits whatever another
  session has staged; `--only` builds a temporary index from HEAD plus the
  named paths and leaves their work staged and untouched
  (`docs/FLEET_LOG.md` records the commit where this went wrong).
- Name only your own path. `COVERAGE.md` reaches the commit by itself:
  `--only` points `GIT_INDEX_FILE` at that temporary index and
  `10-coverage.sh` stages the snapshot there. Never ask an agent to stage a
  path outside its assignment.
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
   are for documentation or deliberate post-acceptance cleanup only. A
   probe-only batch now gates by itself the moment a candidate comes back
   `link_verified` (§3.1); you do not send a second batch to gate a hit.
4. Try about 10 plausible compiler-faithful variants for ordinary functions,
   10–50 for difficult ones when justified; stop after the first accepted
   candidate. Change the hypothesis family when a diagnostic repeats instead of
   resending the same body — the runner now refuses a body that owner has
   already had *rejected* under the same `declarations` (§3.1). That refusal
   is a preflight diagnostic: it costs no hypothesis budget, but it is not a
   puzzle to work around. `futility` warns and never refuses; persistence
   past it is how several owners actually close.
5. Read the runner's per-attempt diagnostics (`status`, `mismatch_kind`,
   `similarity_score`, `first_diff_*`, `link_verified`, `expected_tail_kind`)
   and act on the class: `register_allocation_only` → declaration order,
   temporaries, widths; `immediate_drift` → offsets, strides, literal widths;
   non-text `section_layout_drift` → definitive rejection (see 2.7);
   `text_layout_drift` → recoverable owner-size/frame drift, so keep the
   candidate eligible for a sequential gate after fixing the body or verified
   padding; `symbol_size_drift` / alignment tails →
   `#pragma C_FUNCTION_PADDING(n)` or a `<owner>_padding` helper, only for
   verified layout bytes.
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
12. Shared-`$at` `lui` runs: a ground-truth owner occasionally has one
    `lui $at, %hi(S1)` feeding `sw`/`sh`/`sb`/`lw`/`lh`/`lb`/`swc1`/`lwc1`
    (also the `l.s`/`s.s`/`l.d`/`s.d` float pseudo-ops) to *several distinct*
    symbols `S1, S2, ...` that happen to share a page -- an assembler
    artifact neither IDO's compiler nor GNU `as` reproduces from ordinary,
    independent per-statement C (each statement gets its own `lui`). This ROM
    is a matching decompilation with every data symbol's address already
    fixed, so `#pragma COALESCE_AT_LUI(function_name)` (see
    `disasm/tools/coalesce_lui.py`'s module docstring; landed via #133/#137,
    `func_84136D84` is the worked example,
    `docs/regions/fragments/79/fragment79_393CA0.md` the full trail)
    post-processes the compiled object to fold the redundant `lui`s back to
    one, matching ground truth. Write each symbol as its own independent
    store/load -- **not** array indexing, which materializes a base register
    instead of reusing `$at` and produces a completely different, wrong
    shape (an existing array-typed declaration can still be reused via a
    compile-time-constant `arr[0]` index, which costs no extra instruction).
    Only reach for this when the `lui` and its uses are truly *contiguous* in
    ground truth (no unrelated instruction between them --
    `python3 disasm/tools/scan_coalesce_sites.py` finds and classifies every
    such site in the ROM, `contiguous` vs `interleaved`); the current fold
    logic cannot handle a scheduler-hoisted, interleaved `lui`, and a
    function whose byte-match also depends on an interleaved shared-`lui`
    elsewhere in its own body cannot land through this mechanism at all
    today, regardless of how the targeted site is written.
13. Known dead ends are excluded from fresh fleet scheduling
    (`tools/pragma_targets.py`'s `jump_table_unready`/`coalesce_unready`/
    `schedulable` fields, filtered by `fleetctl plan`), but an owner can
    still reach you from an already-in-flight run, an explicit `--file`/
    `--owners` override, or a hand-picked slot. `tools/file_brief.py`'s
    banner surfaces the file's region notes before you write anything --
    read them first. If a note already tags this owner (or the file's
    jump-table/coalescing shape in general) `layout-prerequisite` or
    `tooling-blocked` with rule 7's `section_layout_drift` (no `.rodata`
    subsegment yet) or rule 12's `interleaved` shared-`$at` pattern, that is
    not a hypothesis to re-litigate: run at most one confirming probe (a
    note can be stale -- the subsegment may have landed, or the site may
    have resolved differently on a re-scan), and if it reproduces the same
    rejection, stop after that one iteration. Leave the existing handoff in
    place (or refresh its evidence) rather than spending the rest of the box
    on candidate spellings no C rewrite can fix.

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
   **Eight candidates is a floor, not a ceiling.** A probe costs ~0.35 s and
   they run in parallel; the expensive part is your own round-trip. Measured
   over a two-hour fleet window: 398 batches for 1205 attempts, median batch
   size 2, and 46% of batches carried a single candidate — while the runner
   used 424 s of a 7200 s window (6%). Compute is not the constraint; batches
   per hour is. Never send a one-candidate probe batch.
   Read the per-attempt result: `mismatch_kind`, `first_diff_offset`,
   `expected_instruction_text` vs `actual_instruction_text`,
   `similarity_score`, `expected_size` vs `actual_size`, `expected_tail_kind`.
5. Iterate on the diagnostic, never on intuition alone:
   `register_allocation_only` → declaration order, temporaries, widths;
   `immediate_drift` → offsets, strides, literal widths, frame padding;
   `symbol_size_drift` / tail kinds → `C_FUNCTION_PADDING` or a `_padding`
   helper; a non-text `section_layout_drift` on a `switch` → the file needs
   its subsegment first. A `text_layout_drift` is a recoverable owner-size
   or frame mismatch; fix the body or verified padding before gating. A
   `similarity_score` of 1.0 with different registers is
   an operand-order or declaration-order problem, not a semantic one.
6. The first `link_verified` probe hit gates itself — the runner runs the
   authoritative ROM gate in the same call rather than handing the hit back
   (`auto_gate: false` opts out for diagnosis). Do not keep probing variants
   for an owner that already has a hit. Then name it if evidence exists
   (`python3 tools/name_decompiled.py plan`). If there is no hit, keep this
   owner active: change the hypothesis family and continue until acceptance,
   an explicit terminal prerequisite/tooling state, or box expiry. Do not
   move to another owner just because a bounded batch rejected its candidates.
7. The ~15-variant guideline is a per-box source-shape budget, not a reason
   to declare the owner done. At box expiry, leave a durable `requeue`
   handoff with the best diagnostic and next hypothesis; the next agent starts
   there. A runner-reported `futility` register tie at ≥ 0.99 belongs to the
   permuter (`docs/REGISTER_TIES.md`). Do not commit a body that only matches
   with `DECOMP_PROVENANCE_SKIP`.

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

Unattended, one-file-per-container alternative to fleet mode (issue #39):
`docs/CONTAINER_AGENT.md` (build/run, output contract, loop/plateau/permuter-poll
semantics), merged into the tree with `tools/container_merge.py`.

### 3.1 Runner and MCP

- `tools/try_pragma_compare.py` / `tools/try_pragma_compare_mcp.py` — the
  candidate runner. MCP tools: `try_pragma_candidates` (`gate: false` for
  probe-only batches; `declarations` for shared externs; `source` may be
  omitted when every candidate resolves to one owner), `find_owner`,
  `get_function_asm`, `list_targets`, `draft_candidates` (m2c drafts plus
  `similar_solved`), `permute_candidate`.
  `permute_candidate` accepts the same `companion_edits` transaction as the
  runner; use it when a near-match only compiles after retyping its stale
  prototype or updating an accepted caller.
- Probe compiles bypass `make`: the recipe is captured once per Makefile
  revision and asm-processor/IDO run directly (~0.3–0.7 s per probe; the ROM
  gate is ~2 s incremental). Probe sources live under ignored `disasm/probes/`.
- A `.text` hit is checked against the baseline object's link shape. Verified
  hits (`link_verified: true`) share one combined gate; unverified hits gate
  sequentially; non-text `section_layout_drift` is rejected immediately, but
  `text_layout_drift` remains eligible for the sequential gate. Winners are
  installed incrementally; a winner that only conflicts in combination is
  reported `combined_compile_failed` and not retried alone.
- A candidate whose only raw `.text` differences are recognized relocation
  fields with identical relocation topology is reported with
  `relocation_masked: true`. It is never link-verified from that comparison
  and always goes through the sequential full-ROM gate; the mask is only
  permission to run the authoritative gate, not acceptance evidence.
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
  exact-once edit to a C body or prototype in the same file for both the probe
  and the gate and installs it only together with the candidate; candidate
  substitution happens first, so a stale extern for the candidate owner may be
  retyped in the same transaction. The stats row records the edited function
  names. It may not add or remove a `#pragma GLOBAL_ASM`. Use it for the §4
  "callee prototyped as `void`" and "caller passes fewer arguments" cases; the
  function-pointer cast spelling in the T5 example is unverified until a gate
  accepts it.
- `tools/fleet_probe.py batch.json [--gate] [--no-auto-gate] [--json out]` —
  CLI front end for agents that are not wired to the MCP server; prints one row
  per attempt and a per-function verdict (including "register tie — stop").

- Batch preflight (`validate_candidate_batch`, runs before any compiler worker
  starts) refuses, on top of the invalid-owner/companion checks, a candidate
  body this owner has already had **rejected** under the **same
  `declarations`** — whitespace- and comment-insensitive, checked against the
  full probe-stats history and within the batch itself. Both narrowings are
  measured, not cautious: replaying the two-hour window with body-only
  identity destroyed all six of its accepts (five were the legitimate
  discover-then-gate re-send; `func_8822B63C` accepted a body that had
  `compile_failed` 41 s earlier under a shorter externs block). As shipped the
  same replay blocks 19% of attempts and destroys none.
- `futility_warnings` surfaces the `_futility_verdict` the runner has always
  computed and nothing ever read — on the MCP result as `futility_warnings`,
  on stderr from `fleet_probe.py`. It **warns and never refuses**: the same
  replay showed the verdict is a good ranking signal and a bad stopping rule
  (`func_81303BF4` closed at `register-tie: 12`, `func_8822B63C` at `stuck:
  16`, `func_80050E88` at `repeated-drift: 40`). Read it, then decide; a
  `register-tie` warning names the `permute_candidate` call worth making.
- Probe-only batches self-gate: a `link_verified` hit runs the full ROM gate
  in the same call and the result carries `auto_gated: true`. `auto_gate:
  false` (MCP) / `--no-auto-gate` (CLI) / `PRAGMA_AUTO_GATE=0` forces a pure
  probe.
- Declaration synthesis covers three sources, in order, and never guesses: the
  owner's own file, then a spelling every other `disasm/src` file agrees on
  (`_declaration_index`, cached per file mtime), for both `func_` callees and
  `D_` data symbols. A symbol two files spell differently, or that nothing
  declares, is left alone. This closed the largest compile-failure class:
  "there should be a full prototype for the function being called" plus
  undefined `D_` symbols were 153 of 1205 attempts (13%) in the measured
  window.

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
  hardness- and layout-aware file ranking and owner listing (`prior_attempts`,
  `best_similarity`, `best_mismatch_kind`, `hardness` = fresh/drift/tie/stuck
  per owner). `rank-files` reports `READY_FRESH`, `JT_UNREADY`, and their
  JSON forms `actionable_fresh`/`jump_table_unready`; `targets` reports each
  jump-table owner's `jump_table_status`. `--exclude-recent` uses an absolute
  timestamp because `git log --since="4.0 hours ago"` silently matches the
  whole history.
- `python3 tools/file_brief.py <file> [--json]` — read this before touching a
  file: solved signatures, extern block, symbols by solved-body count, record
  strides, SDK macros, and the callees defined later in the file with their
  real return types. It also warns when an owner has leading local `.rodata` or
  `.late_rodata` in split assembly; those owners need manual layout work before
  a switch candidate is useful. Prints that file's `tools/region_notes.py`
  notes first.
- `python3 tools/region_notes.py show|append|list` — the per-file notes
  store behind `file_brief.py`'s banner: file-specific spellings, skip
  lists and unsolved shapes that do not generalise into §4/§5, at
  `docs/regions/<source path>.md`.
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
| Guard/return polarity | IDO branches on the negated condition: write the `if` in the polarity whose negation is the observed `beq`/`bne`, e.g. `if (arg1 == x) { ... } return v;` rather than `if (arg1 != x) return v;` | 2 (`func_81306EE0`, `func_80059234`) | — |
| Display-list append (`Gfx` command into `D_800D0510++`) | Use the real `gbi.h` macros — `gSPDisplayList(D_800D0510++, addr)`, `gDPSetFillColor`, `gDPFillRectangle` — never hand-written `p->words.w0 = ...; p->words.w1 = ...;` stores, which stall at 0.93–0.95 on a constant-load/pointer-increment scheduling swap | 10 (`4AC10.c`: `func_8004AC24/AE3C/AF18/A5B8/A708/AD00`; `fragment47_24E0A0.c`: `func_8600B474`; `fragment49_code.c`: `func_86100BA0/05F68/09D64`) | holds across overlays; RDP texture-load sequences (`gDPSetTile`/`gDPLoadBlock`, `func_8004A010`) still untried, and one owner (`func_82C01FE4`) drifts on the order of two independent `lui` loads inside the macro |
| Several `return 1;` guards sharing one epilogue | A single `return a \|\| b \|\| c \|\| d;` expression; separate guard clauses allocate differently and add bytes | 2 (`func_8130AA54`, `func_80057A80`) | — |
| Nested command constructor from a fixed record | Use a local typed overlay with the proven padding/child field, then pass the nested field directly to the helper; keep each constructor's exact field width | 10 (`229E0.c`: `func_8003FD98/3FE6C/40004/40050/4009C/400E8`; `4EE50.c`: `func_8004E868/4E8D0/4E9C8/4EA60`) | only when the record offsets and helper call shape are proven |
| General | Preserve narrow `sb`/`sh`/`sw` widths, initialise results before NULL checks, raw 32-bit address arithmetic (`(u8 *)(u32)global + off`) before inferred structs, `uintptr_t` casts for raw addresses, explicit `s32` loop counters, array-index vs pointer-add as separate variants, deliberate signed/unsigned masks | repo scan | ABI hypotheses until compared |

Type spellings: `u8-void` and `s32-s32` account for essentially all m2c-draft
accepts; other widths only on diagnostic evidence via the variant policy.

A row here generalises across two or more source files. A spelling verified
in only one file lives in that file's notes under `docs/regions/` and
reaches an agent through `tools/file_brief.py`, not here.

## 5. Tooling backlog and recurring unsolved shapes

- Runner (fixed 2026-08-30): raw object comparison previously rejected exact
  source spellings when equivalent symbol-plus-addend forms changed only
  relocatable immediate fields. The runner now promotes same-topology,
  recognized relocation-field-only differences to an unverified sequential
  full-ROM gate. An audit found seven high-similarity owners worth replaying;
  `relocation_masked` must never be treated as `link_verified`.
- Runner: `probe_unavailable` / `list index out of range` also reproduces on
  `func_82C04880` (`fragment83_code.c`) — same last-owner diagnostics bug,
  now five recorded instances.
- Runner (cosmetic): a `companion_edits` install can leave a redundant
  forward prototype next to the retyped declaration it just fixed (the
  callee-declaration scan injects one, the companion edit corrects the
  file-level extern). Valid C, harmless, but `dedupe_externs.py` should
  learn to fold it away (`fragment47_24E0A0.c`, `func_87C00160`).
- Runner: `probe_error` / `list index out of range` on the last pragma owner
  of a file when the function has trailing alignment nops
  (`func_8005633C`, `func_8130CDD4`, `func_80021BBC`, `func_8001FC60`,
  `func_80071E48`); reproduces with a trivial body, so it
  is a diagnostics-path bug, not a candidate problem.
- Runner: `654A0.c` cannot get its `.rodata` subsegment until asm-processor
  handles mixed 4/8-byte `.late_rodata_alignment` without growing `.text`.
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
- Sweep families other than `frame-padding` in `near_miss_kinds` have no
  accepts yet (0/146); re-evaluate after the fleet's records accumulate.
- Probe comparator (2026-08-30): a decompiled `switch` whose jump table the
  baseline stub references via `%lo(jtbl_…)` reads as `immediate_drift` at
  normalized similarity 1.0 — the C object resolves the section offset
  numerically where the stub keeps a symbol relocation. Relocation-equivalent;
  verified through the ROM gate (`517E0.c`
  `func_80050DE4/80053230/800532F0`). The comparator should normalise
  relocation-carried immediates.
- Runner (2026-08-30): a gate batch that ends `no_candidate_accepted` after a
  `probe_rejected` can still leave the winning candidate's bodies installed in
  the tracked source (observed with the `517E0.c` switch batch above); check
  `git diff` after a failed gate before re-probing the same owners.
- Runner (fixed 2026-09-02): `companion_edits` now substitutes candidate
  owners before applying same-file extern/prototype edits, so a stale callee
  signature can be corrected in the same candidate transaction while the
  no-add/remove-pragma guard remains active.
- Build (2026-08-30): `make -C disasm COMPARE=1` fails in the host clang
  syntax check on committed, unmodified code
  (`fragments/44/fragment44_1F1850.c`: old-style definitions + a
  too-few-arguments call, strict clang). `RUN_CC_CHECK=0` completes the ROM
  compare until that file is cleaned up. The same class in
  `fragments/79/fragment79_38D510.c` was repaired on 2026-08-30 with the
  file's own `#ifdef CC_CHECK` shim pattern (ROM compare verified).
- Fleet (2026-08-30): a readiness-aware wave produced 13 new full-ROM-gated
  owners from five fresh-heavy, layout-ready fragment files, confirming that
  `READY_FRESH` is a better selection signal than the composite score. Do not
  count explicit requeues as fresh work. Repeated helper-call drift that adds
  `jalr` or `trunc.w.s` is an ABI hypothesis failure; stop expression
  permutations and reconstruct the direct callee signature. A repeated
  argument-home fingerprint (`expected sw a1,4(sp)` vs `actual sll t6,a1,12`)
  likewise requires a new scheduling model, not more return-width variants.
- Fleet (2026-08-30): the five-box owner-explicit wave produced 6 accepted
  owners from 439 recorded attempts (356 probe rejections, 44 compiler
  failures, 17 skipped gate entries, and 16 probe matches). Fragment69's
  direct-lvalue family produced three accepts; fragment79 produced two; the
  remaining fresh fragment46 owner spent 40 valid probes below a gateable
  match. A foreign dirty source blocked fragment60 before meaningful probing.
  The wave also exposed that the runner's old `section_layout_drift` label
  included recoverable `.text` size changes; these are now reported as
  `text_layout_drift`. Keep one-function persistence, but select only owners
  with a valid first hypothesis and serialize runner work in a shared checkout.

Skip lists and unsolved shapes that are specific to one function or file
live in that file's notes under `docs/regions/` and reach an agent through
`tools/file_brief.py`, not here.
