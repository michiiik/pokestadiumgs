# Containerised per-file agent

Issue #39. An alternative to fleet mode (`docs/FLEET_AGENT.md`) for the same
goal -- an agent iterating candidates for `disasm/src/<file>.c` toward a
byte-identical ROM -- with no orchestrator holding it together while it runs.
A container gets **one source file**, a time/iteration budget, and the repo's
own tooling (compiler, gate, permuter, probe scripts); it works alone, polls
its own permuter output rather than waiting on a notification a subagent
cannot receive (the loss #38 measured), and writes its results to a mounted
directory. Nothing lands in the tree until a separate, deliberate host-side
step re-gates and commits it.

Building and running the image, and the driver loop itself
(`tools/container_agent.py`), belong to `container/*` (`Dockerfile`,
`entrypoint.sh`, `build.sh`, `run.sh`). This page documents the contract
those pieces implement and the host-side merge step
(`tools/container_merge.py`) that consumes it -- read their own `--help` /
source for exact flags, which may extend what's described here.

## 0. Prerequisites

- **Docker with `linux/amd64` emulation.** IDO -- the compiler the ROM gate
  compares against -- ships as an x86_64 Linux binary. On an Apple Silicon
  host, Docker's default `linux/arm64` either refuses to run it or runs it
  under emulation with different floating-point/optimizer behavior,
  silently invalidating the gate. `container/build.sh` and
  `container/run.sh` already pin `--platform linux/amd64`.
- **`disasm/baseroms/us/baserom.z64` must already exist in your checkout
  before `container/build.sh` runs.** It's gitignored and not fetched by
  the build -- the Dockerfile's `COPY . /work` copies it from the host
  build context straight into the image. Without it, `make -C disasm
  extract` fails partway through the image build.
- `disasm/asm/` and the rest of `disasm/build/` are **regenerated at image
  build time**: the Dockerfile bakes in a full `make -C disasm extract` plus
  a full `make -C disasm rom`, so a complete matching build already exists
  on disk when the container starts -- what lets the runner's gate
  (`make -C disasm COMPARE=1 -j2`) stay an incremental timestamp-check-and-
  relink instead of a from-scratch rebuild each iteration (see the "ROM gate
  note" comment in `container/entrypoint.sh`).
- Expect the built image to be roughly **1 GB**, and the first build to take
  **several minutes** (toolchain + npm installs + a full extract + a full
  ROM build, all baked in).

## 1. Build

    container/build.sh

Produces the image from a clean clone: the mips toolchain, clang for the
host syntax check, `decomp-venv` (permuter plus the pinned spimdisasm from
`requirements.txt` -- see `docs/JUMP_TABLES.md` §3 for why the pin matters),
the repo's probe/gate scripts, and a baked initial matching build (§0).
`container/build.sh` and `container/run.sh` already pin `--platform
linux/amd64` (see §0); pass it yourself if you invoke `docker build` /
`docker run` by hand.

## 2. Run

    export ANTHROPIC_API_KEY=sk-...
    container/run.sh disasm/src/4AC10.c /abs/out --budget-seconds 3600

`/abs/out` must be an absolute host path -- it is bind-mounted into the
container as the output directory. The driver
(`tools/container_agent.py`, invoked by `container/entrypoint.sh`) accepts:

| Flag | Meaning |
|---|---|
| `--source` | the one `disasm/src/<file>.c` this container owns |
| `--out` | output directory (mounted; matches the host path given to `run.sh`) |
| `--budget-seconds` | overall wall-clock budget for the run |
| `--max-iterations` | overall iteration cap, independent of the time budget |
| `--plateau N` | stop an owner after `N` consecutive iterations with no best-similarity improvement |
| `--owner-seconds N` | per-owner wall-clock cap (default 2400s), measured from the owner's first generator call (`--mode full`) or first permuter job (`--mode permuter-only`) in this run -- time already spent on the owner in an earlier `--resume` run counts too. See §6.2 |
| `--permuter-seconds` | budget per permuter invocation (default 300 in `--mode full`, 1200 in `--mode permuter-only` -- §6.1) |
| `--permuter-bodies N` | on a trigger, run the permuter on up to `N` distinct bodies from that iteration, each its own background process (default 3) |
| `--owners` | restrict the run to an explicit owner list instead of every pragma in the file |
| `--owner-order {size,file}` | discovery order when `--owners` is not given: smallest-instructions-first (default) or the order owners appear in the source |
| `--max-instructions N` | skip discovered owners with more instructions than `N` (default: unlimited); ignored when `--owners` is given explicitly |
| `--generator-cmd` | shell template for candidate generation; `{prompt}` and `{batch}` are substituted |
| `--generator-timeout` | cap in seconds on a single generator invocation (default 1800, raised from 600 -- see §4.1); still bounded further by the run's remaining budget. Kimi K3 at high effort can exceed 10 minutes per batch on its own -- raise this further rather than letting it time out |
| `--probe-tool {on,off}` | toggle the `BATCH_CONTRACT` paragraph telling an agentic generator it may/should call `tools/probe_one.py` to iterate before writing the batch (see §4.1). Default: the `PROBE_TOOL` env var if set, else `on` |
| `--candidate-file` | test mode: use a fixed batch file once for the first owner, then exit -- no generator/model call at all |
| `--seed-from DIR[,DIR...]` | seed a **fresh** run (not `--resume`) from one or more earlier `--out` dirs' own `state.json` -- see §2.1 |
| `--examples N` | up to `N` already-matched functions of the active owner's family, rendered as worked examples in the prompt (§4 item 3); default 3, `0` disables |
| `--mode {full,permuter-only}` | `full` (default): the normal generate/probe/permuter loop. `permuter-only`: never calls the generator -- see §6.1 |
| `--tie-pool-file PATH` | in `--mode permuter-only`, a JSON file shaped like `tie-pool.json` to seed owners' best bodies from -- see §6.1 |

### 2.1 Seeding a fresh run from earlier output dirs

`--seed-from /abs/out1,/abs/out2` warms up a brand-new run (never combined
with `--resume`; a resumed owner already has its own real state, and
`--seed-from` is silently ignored -- with a log line saying so -- when both
are passed) from one or more earlier `--out` directories, this run's own
past attempts or another run's (a different generator/model against the
same file, or the same generator retried). Owner names are unique function
symbols, not scoped to any one source file, so this looks at *every* owner
mentioned in any of the given dirs' `state.json`, not just this run's
current file's owners.

Per owner, `seed_owner_states()` in `tools/container_agent.py`:

- merges `best_candidates` from every seed dir that has that owner: ranked
  by the same `attempt_rank` the normal loop uses, deduplicated by
  normalised body text, and capped at `BEST_CANDIDATES_KEPT` (5) -- but
  always keeping at least the single best candidate from *every*
  contributing source, even past the cap, so one source's several
  near-misses can never fully crowd out another source's one good lead;
- unions `tried_bodies`/`tried_labels` across every seed dir, so a body or
  hypothesis already probed in any of them is never resent this run (the
  usual within-run dedup in `filter_batch` just inherits a bigger seed set);
- takes the first `m2c_draft` found (and marks it fetched, so this run
  never re-runs `pragma_targets.py draft` for that owner);
- takes the best (lowest-score; 0 is instruction-exact) `permuter_seed`
  across every seed dir that has one.

`status`/`iterations`/`plateau_count`/`history` are **never** imported --
a seeded owner still starts exactly like a normal pending owner (status
`in_progress`, `iterations` 0, empty `history`) to `process_owner`/`main`;
it just has a warm `best_candidates` pool, tried-body/label memory, an m2c
draft, and a permuter seed already in hand, so the very first prompt built
for it naturally shows those seeded bodies (with their diagnostics) instead
of a blank slate. The owner's `state.json` entry also records
`seeded_from` (the contributing seed dir paths) and `seed_best_similarity`
(the best similarity among what was actually imported, or `null` if
nothing scored), and one log line per owner: `"<owner>: seeded N
candidate(s), best X from <dir>"`.

An owner a seed dir already marked `accepted` is not skipped -- its exact
installed body (`accepted/<owner>.json`'s first candidate, the same file
`capture_accepted` writes) is imported as one more `best_candidates` entry
with `similarity_score` 1.0, and the driver logs loudly that the owner was
already matched elsewhere: **the host merge (§9) decides** whether it
actually lands, never the seed step itself. A seed dir that marks an owner
`accepted` but has no readable `accepted/<owner>.json` (e.g. a hand-built
fixture) still gets the owner recorded (with a WARNING logged) -- there is
just nothing to show for the accept itself.

Every field is read with a safe default, so an older out dir's `state.json`
missing `tried_bodies`/`tried_labels`/`feedback`/`normalized_only` (a schema
predating those additions) seeds cleanly with whatever it does have.

### 2.2 Keeping a stale image's owners current: `SRC_OVERLAY`

The image's `disasm/src`/`disasm/include`/`disasm/linker_scripts` (and the
full matching build baked from them, §0) are frozen at whatever the
checkout looked like when `container/build.sh` last ran. A container
launched from an older image still discovers every `GLOBAL_ASM` owner that
was in `disasm/src` *at build time* -- including ones some other run has
since matched and merged to master -- and the driver has no way to tell
those apart from a genuinely unmatched owner: it just sees the pragma.
Rebuilding the image before every run is the correct fix but expensive
(§0's "several minutes"); `SRC_OVERLAY` is the cheap one for the common
case of "the image is a few merges behind, but otherwise fine."

    SRC_OVERLAY=/abs/path/to/checkout container/run.sh disasm/src/4AC10.c /abs/out ...

`container/run.sh` mounts `$SRC_OVERLAY` read-only at `/src` and passes
the container the fixed in-container path (`SRC_OVERLAY=/src`) that
`container/entrypoint.sh` checks for. When set, `entrypoint.sh`:

1. Runs `container/overlay_src.sh` -- read live out of `/src` itself
   (`/src/container/overlay_src.sh /src`), **never** a copy baked into the
   image, so this keeps working even for an image built before
   `overlay_src.sh` existed at all. It fully replaces `/work/disasm/src`
   and `/work/disasm/include` with `$SRC_OVERLAY`'s copies (so a file the
   overlay checkout deletes doesn't silently keep linking the image's
   stale `.o`), and overlays (never delete-syncs) `$SRC_OVERLAY`'s
   `disasm/linker_scripts` onto the image's own.
2. Runs one incremental `make -C disasm rom` (no explicit `COMPARE` --
   see the "ROM gate note" above for why passing `COMPARE=1` here would be
   wrong) so the baked build tree is consistent with the overlaid sources
   *before* the driver's own gate calls run. Prints the combined
   overlay+rebuild time to stderr.

`container/gate_pr.sh` (the PR gate, see its own header) uses the exact
same `container/overlay_src.sh`, invoked the same way -- out of the
checkout mounted at `/src`, never a baked copy -- so both callers share
one implementation of "what files matter to a `make rom` build" (see that
script's own header for exactly which three directories and why).

Unset/empty `SRC_OVERLAY` (the default): no `/src` mount, no overlay --
`container/run.sh`/`entrypoint.sh` behave exactly as they did before this
existed.

## 3. Choosing the coding agent

By default (no `--generator-cmd`, no `--candidate-file`), `entrypoint.sh`
injects `--generator-cmd "/work/container/generators/run_generator.sh
{prompt} {batch}"`, a dispatcher that execs `container/generators/$AGENT.sh
<prompt> <batch>`, selected by the `AGENT` env var (default `claude`).
`container/run.sh` forwards `AGENT`, `GENERATOR_MODEL`, `GENERATOR_EFFORT`,
and every agent's auth through to `docker run` when set in your shell.
`container/generators/README.md` is the authoritative source for this table
(CLI/package, verified flags, provider docs); keep changes there:

| `AGENT=`        | CLI / package                          | Required env vars                                      | Default model (`GENERATOR_MODEL`) |
|------------------|------------------------------------------|------------------------------------------------------------|--------------------------------------|
| `claude`         | `@anthropic-ai/claude-code` (`claude`)   | `ANTHROPIC_API_KEY`                                          | `sonnet`                             |
| `codex`          | `@openai/codex` (`codex`)                | `OPENAI_API_KEY`, or a mounted ChatGPT login (`~/.codex/auth.json`) | `gpt-5.1-codex`               |
| `qwen`           | `@qwen-code/qwen-code` (`qwen`)          | `OPENAI_API_KEY` (or `DASHSCOPE_API_KEY`)                    | `qwen3-coder-plus`                   |
| `kimi`           | official Kimi Code CLI (`kimi`, native binary) | a mounted subscription login (`~/.kimi-code/credentials/`), or `KIMI_MODEL_NAME`+`KIMI_MODEL_API_KEY` | `kimi-code/k3` |
| `kimi_api`       | none -- routes to `openai_compat.sh`     | `MOONSHOT_API_KEY`                                            | `kimi-k2.7-code`                     |
| `openai_compat`  | none (`python3` stdlib only)             | `OPENAI_API_KEY`, `OPENAI_BASE_URL`, `GENERATOR_MODEL`       | (none -- must be set)                |
| `claude_via`     | `@anthropic-ai/claude-code` (`claude`), a third-party Anthropic-compatible endpoint | `CLAUDE_VIA=alibaba\|zai\|custom` + that provider's token, `GENERATOR_MODEL` | (none -- must be set) |
| `alibaba`        | shorthand for `claude_via CLAUDE_VIA=alibaba` | `ANTHROPIC_AUTH_TOKEN` (`run.sh` reads it from `~/.qwen/settings.json`) or `ALIBABA_API_KEY`, `GENERATOR_MODEL` | (none -- must be set) |
| `zai`            | shorthand for `claude_via CLAUDE_VIA=zai` | `ZAI_API_KEY`, `GENERATOR_MODEL`                              | (none -- must be set)                |

`entrypoint.sh` checks that `AGENT`'s required auth is present *before*
starting the driver, so a missing key/login fails fast instead of partway
through the first iteration. That check (and the default `--generator-cmd`
injection) is skipped entirely when the caller passes `--generator-cmd` or
`--candidate-file` themselves -- see §4 and §5.

For `kimi`, `GENERATOR_EFFORT` (`low`/`high`/`max` for the default
`kimi-code/k3`) is forwarded to the CLI as `KIMI_MODEL_THINKING_EFFORT`.

Examples:

    # claude (default agent, default model "sonnet")
    export ANTHROPIC_API_KEY=sk-ant-...
    container/run.sh disasm/src/4AC10.c /abs/out

    # codex, overriding the model
    export OPENAI_API_KEY=sk-...
    AGENT=codex GENERATOR_MODEL=gpt-5.1-codex container/run.sh disasm/src/4AC10.c /abs/out

    # kimi, official CLI under your own subscription login (already logged
    # in via `kimi login` on the host -- container/run.sh mounts a throwaway
    # copy of ~/.kimi-code, same pattern as codex's ~/.codex/auth.json)
    AGENT=kimi container/run.sh disasm/src/4AC10.c /abs/out
    # ...or at high thinking effort:
    AGENT=kimi GENERATOR_EFFORT=high container/run.sh disasm/src/4AC10.c /abs/out

    # kimi_api, a plain Moonshot API key (no CLI, no login state)
    AGENT=kimi_api MOONSHOT_API_KEY=sk-... container/run.sh disasm/src/4AC10.c /abs/out

    # openai_compat, pointed at a self-hosted OpenAI-compatible endpoint
    AGENT=openai_compat OPENAI_API_KEY=local-key OPENAI_BASE_URL=http://my-host:8000/v1 \
    GENERATOR_MODEL=my-local-model container/run.sh disasm/src/4AC10.c /abs/out

    # alibaba, Bailian Coding Plan (shorthand for AGENT=claude_via
    # CLAUDE_VIA=alibaba) -- run.sh reads the Coding Plan key out of
    # ~/.qwen/settings.json for you; no key export needed if it's there
    AGENT=alibaba ALIBABA_PLAN=coding GENERATOR_MODEL=qwen3-coder-plus \
    container/run.sh disasm/src/4AC10.c /abs/out

    # alibaba, Bailian Token Plan instead (verified working on this repo's
    # dev machine as of 2026-09-02 -- see container/generators/README.md's
    # claude_via.sh section for why "coding" may 401 for you too)
    AGENT=alibaba ALIBABA_PLAN=token GENERATOR_MODEL=qwen3.7-plus \
    container/run.sh disasm/src/4AC10.c /abs/out

    # zai, Z.ai GLM Coding Plan
    AGENT=zai ZAI_API_KEY=... GENERATOR_MODEL=glm-4.6 \
    container/run.sh disasm/src/4AC10.c /abs/out

    # claude_via, any other Anthropic-compatible endpoint
    AGENT=claude_via CLAUDE_VIA=custom \
    CLAUDE_VIA_BASE_URL=https://my-provider.example/anthropic CLAUDE_VIA_API_KEY=... \
    GENERATOR_MODEL=my-model container/run.sh disasm/src/4AC10.c /abs/out


> **Kimi login is mounted live, not copied.** `container/run.sh` bind-mounts
> the host's `~/.kimi-code` read-write. Kimi Code rotates its refresh token on
> every refresh, so a refresh inside a *copy* invalidates the host login
> ("The provided authorization grant is invalid", credential cleared; fix with
> `kimi login`). Do not use `kimi` on the host while a container run is active,
> and never run two Kimi containers at once.

## 4. Supplying your own `--generator-cmd`

`--generator-cmd` is a shell command template, substituted by
`render_generator_command()` in `tools/container_agent.py`: `{prompt}` and
`{batch}` are replaced with absolute paths before the command runs (cwd is
the repo root). The prompt file at `{prompt}` already contains the batch
JSON schema and the exact `{batch}` output path (`BATCH_CONTRACT` in
`tools/container_agent.py`), so a custom command's only jobs are: run
whatever model/tool you want, and make sure `{batch}` ends up on disk as
valid JSON afterward. Passing `--generator-cmd` yourself overrides the
default dispatcher entirely -- `entrypoint.sh` forwards your command as-is
and does not gate on any API key (it's your command, your auth).

### What the prompt contains

`build_prompt()` assembles each iteration's prompt, in this order (a
section is omitted entirely when it has nothing to show):

1. **File brief** (`tools/file_brief.py`) -- already-decompiled functions,
   the extern/prototype block, symbol usage, stride/SDK-macro hints, and the
   remaining-owners table.
2. **Target assembly** for the active owner (`tools/pragma_targets.py asm`).
3. **Worked examples** -- up to `--examples` (default 3, `0` disables)
   already-matched functions of the owner's own family, each rendered as
   `== matched example (family <family>): <name> ==` followed by its full C
   definition (and its `.s` size when that's cheap to look up). Prefers
   `tools/pragma_targets.py similar <owner>` (opcode-shape similarity
   against every previously accepted candidate, AGENTS.md §2.5 step 2: "start
   from the closest accepted winner's spelling, not from m2c"); when that
   returns nothing, falls back to other already-defined functions in the
   same source file (preferring ones whose `.s` still lives in the owner's
   own nonmatchings directory -- the same directory `list_targets`'s family
   classification comes from), then other files in the same directory.
   Capped at ~12 KB total (`EXAMPLES_BYTE_CAP`). Fetched once per owner per
   run and cached in `state.json` (`examples`), so `--resume`/`--seed-from`
   do not refetch.
4. **m2c draft** -- a structural hint from `tools/pragma_targets.py draft`
   (unknown-struct fields, guessed types; retype/reshape freely, never a
   match). Fetched once per owner per run and cached in
   `state.json` (`m2c_draft`), so `--resume` does not re-run it.
5. **Best candidates tried so far this run** -- up to 5, highest similarity
   first, with diagnostics/frame/instruction-count/diff-excerpt feedback and
   the static diff-reading guide.
6. **Labels already tried this run** -- the last 30, so a generator does not
   resend a hypothesis under a new name.
7. **decomp-permuter output**, when a background job (§6 step 3) has
   produced one -- submit it close to verbatim as one candidate.
8. **"The file already declares these callees/data (do not redeclare)"** --
   names pulled from the file brief's extern/prototype block, as an explicit
   rule alongside the declaration-hygiene filtering already applied to the
   previous batch's shared `declarations` (see §6 step 1).
9. The batch JSON contract/rules (`BATCH_CONTRACT`) and the exact output path.

### 4.1 Fast inner loop

`BATCH_CONTRACT` (step 8 above) includes a paragraph -- on by default,
toggled by `--probe-tool {on,off}` -- inviting an agentic generator to
iterate for itself, in its own turn, before it ever writes the batch file:

> You MAY and SHOULD iterate before writing the batch: put a draft in a
> file and run `python3 tools/probe_one.py --source <source> --function
> <owner> --body draft.c [--declarations decls.h]` (about 10-20 s each; use
> `--quiet` for just the numbers). Read the diff, change one thing, probe
> again. Do this as many times as useful (dozens is fine), then put your
> best 8-16 distinct bodies in the batch, best first. Do NOT run `make`,
> `fleet_probe.py`, the permuter, or write into `disasm/src` yourself.

This is a deliberate reversal from the driver's own outer loop, which
still tells the generator not to touch the toolchain (`--probe-tool off`
renders that older rule instead -- see below): `tools/probe_one.py` (issue
#39 follow-up) is a single-candidate wrapper around `tools/fleet_probe.py`
that a model can call directly, itself, dozens of times inside one turn --
write a draft body to a scratch file, probe it, read back similarity/raw
score/frame size/first mismatch/a diff excerpt, change one thing, probe
again -- instead of paying a full driver generate/probe/prompt-rebuild
cycle (~5 minutes) for every single hypothesis. It never touches the ROM
gate (`--no-auto-gate` is always passed) and never installs anything, so it
is safe for a generator to call it freely.

**Probe-stats isolation.** `tools/fleet_probe.py`/`tools/try_pragma_compare.py`
normally record every attempt into a shared history
(`PRAGMA_PROBE_STATS`) that the runner's own preflight consults to reject
an already-rejected body. A generator iterating on drafts calls
`probe_one.py` many times per turn; if those quick probes landed in that
same shared history, a later driver batch containing the winning body could
get rejected as "already rejected" before it ever reached the real gate. So
by default `probe_one.py` points its `fleet_probe.py` subprocess at a
private scratch file instead, `disasm/scratch/probe_one-stats.jsonl`,
leaving the driver's real probe-stats history untouched. Pass `--stats
shared` to opt back into the runner's default history, or `--stats PATH`
for an explicit location.

**Expected pattern**, from a generator's point of view: read the file brief
and target assembly from the prompt, write a candidate body to a scratch
file, run `probe_one.py --quiet` for a quick score, and only drop `--quiet`
(or add `--json out.json`) when a candidate is worth reading the diff for.
Repeat, changing one hypothesis at a time per the "how to read the diff"
guide already in the prompt, until a handful of distinct, promising bodies
have emerged -- then write those (8-16, best first) to the batch JSON file
at the path the contract names. `--probe-tool` exists because not every
generator wrapper can act on this: `container/generators/claude.sh`,
`codex.sh`, `qwen.sh`, and `kimi.sh` all give the model real Read/Write/Bash
tool access and can run `probe_one.py` mid-turn (see
`container/generators/README.md`), but `openai_compat.sh`/`kimi_api.sh` are
plain HTTP chat-completions calls with no tool access at all -- for those,
`container/entrypoint.sh` exports `PROBE_TOOL=off` automatically (never
overriding a value the caller already set) whenever `AGENT` is
`openai_compat` or `kimi_api`, and the driver's `--probe-tool` falls back to
that env var whenever the flag itself is not passed on the command line.

## 5. Test mode

    container/run.sh disasm/src/X.c /abs/out --candidate-file /out/batch.json

`--candidate-file` skips the generator/model call entirely: the driver uses
that one fixed batch for the first owner, then exits. The file must be
visible *inside* the container, so put `batch.json` under the host out-dir
you're mounting to `/out` and refer to it by its in-container path
(`/out/batch.json`), not the host path. Like `--generator-cmd`, this also
skips `entrypoint.sh`'s API-key check.

## 6. Loop semantics

Owners are discovered once per run (`--owner-order`, `--max-instructions`,
§2) and then worked one at a time, each until a terminal state:

1. Generate a batch of candidates via `--generator-cmd` (or `--candidate-file`
   in test mode). Before probing, a `declarations` statement that redeclares
   a name the source file already declares or defines is dropped (logged),
   the same way an already-tried body is filtered.
2. Probe the batch (isolated object compare), then gate a link-verified hit
   through the full ROM compare -- the same runner fleet agents use
   (`tools/fleet_probe.py`, AGENTS.md §3.1).
3. On a near-miss (effective similarity >= 0.95, or >= 0.90 when
   `mismatch_kind` is `operand_or_scheduling_drift` or a register-allocation
   tie whose raw score trails its normalized one, or any runner-reported
   register tie regardless of score), launch the permuter as a **background
   job** on up to `--permuter-bodies` distinct bodies from that iteration
   (each its own process, run sequentially in one thread) rather than
   blocking the loop -- it runs concurrently with the *next* generator call.
   The driver **polls its output directory**
   (`disasm/build/permuter/<function>-<suffix>/`) at the start of the next
   iteration's prompt build and again after that iteration's probe, rather
   than waiting on any notification -- the fix for the exact failure #38
   measured (three of five fleet trees stalled waiting on a permuter
   notification a subagent cannot receive). A container has no orchestrator
   to notify it either, so it must poll on its own clock. Every permuter
   process still running when the run ends is terminated in the finalize
   path -- none outlives the run.
4. Repeat until one of: the owner gates (`accepted`, move to the next
   owner); `--plateau N` iterations pass with no best-similarity improvement
   (stop this owner, record its plateaued state); `--owner-seconds` is
   exhausted for this owner (§6.2 -- stop this owner, record it exactly like
   a plateau); or `--max-iterations` / `--budget-seconds` is exhausted for
   the run.

Every iteration's outcome (similarity, status, diagnostic) is appended to
that owner's `history[]` in `state.json` as it happens, so a run killed
mid-owner still leaves a readable trail.

Whenever an owner's run ends in **`accepted`**, **`plateau`**, or
**`time_cap`** (only those three -- not `budget_expired`/`max_iterations`/
`generator_failed`, which are run/box bookkeeping, not durable knowledge
about the file), the driver:

- appends a short, dated note to `<out>/region-notes/<source path, "/" ->
  "__">.md`, in the exact section format `tools/region_notes.py append`
  itself produces (§7, §9.5 on the host side): `"<owner>: matched (<label>),
  <N> iterations, agent <AGENT>"` on an accept, `"<owner>: plateau at <best>
  (raw <raw>), mismatch <kind>; tried families: <family, ...>; tie-pool
  yes|no"` on a plateau, or `"<owner>: time cap at <best> (raw <raw>) after
  <elapsed>s, mismatch <kind>; tried families: <family, ...>; tie-pool
  yes|no"` on a `time_cap`, plus one `"TYPE CONFLICT: <callee> is <new sig>,
  not <old sig>"` line per companion-edit type conflict this run recorded
  (`filter_declarations`/`run_iteration`, AGENTS.md §2 rule 9).
- on a **plateau** or **`time_cap`** specifically, also checks whether the
  owner's best attempt was a tie -- a normalized-only match (near-1.0
  similarity, raw well below 0.95) or a runner-reported register-allocation
  tie (`docs/REGISTER_TIES.md`) -- and if so, marks `state.json`'s
  `tie_pool: true` for that owner and appends its best body/declarations to
  a cumulative `<out>/tie-pool.json`, the input a later `--mode
  permuter-only` pass (§6.1) reads via `--tie-pool-file`. Its
  `best_candidates` pool (kept regardless of status) is also what a later
  `--resume` or `--seed-from` prompt starts from, so a `time_cap` owner is
  never starting cold next time.

### 6.1 `--mode permuter-only`: a permuter-first pass over a tie pool

    container/run.sh disasm/src/4AC10.c /abs/out2 --mode permuter-only \
        --tie-pool-file /abs/out/tie-pool.json --budget-seconds 28800

`docs/REGISTER_TIES.md`: "coordinators run the permuter overnight ... instead
of looping agents through the same class of diff." `--mode permuter-only`
(default `full`) is that overnight pass: the driver **never calls the
generator** (`--generator-cmd`/`AGENT` are not required in this mode). For
each owner it takes up to `--permuter-bodies` distinct bodies from
`state.json`'s `best_candidates` -- populated by `--seed-from` and/or
`--tie-pool-file <json>` (the same shape `tie-pool.json` itself is:
`{owner: {source, body, declarations, raw, label}}`) for any owner
`--seed-from` didn't already cover -- and runs `tools/permute_candidate.py`
on each in the **foreground** (there is no concurrent generator call here to
overlap with, unlike the background jobs in §6 step 3), with
`--permuter-seconds` defaulting to **1200** in this mode (300 in `full`).

- The first output with score 0 is probed as a one-candidate batch (label
  `"permuter:zero"`) through the exact same probe/gate path a normal run
  uses (`run_iteration`), so a real accept writes `accepted/<owner>.json`
  exactly as it always does.
- Otherwise, the lowest-scoring output across every body tried is recorded
  as a new (unprobed) `best_candidates[0]` entry (label
  `"permuter-only:best"`) -- the seed a *later* permuter-only pass over this
  same `--out` (or a fresh run seeded from it) starts closer from -- and the
  owner is done for this pass (`plateau`).

Tie-pool recording and region notes (above) apply the same way regardless of
which mode produced the `plateau`/`accepted`/`time_cap` status, so a
permuter-only pass over a tie pool keeps updating both.

### 6.2 `--owner-seconds`: a per-owner wall-clock cap

An agentic generator that explores via `tools/probe_one.py` before
converging (§4.1) does not iterate at a predictable pace: a single call can
run 12-17 minutes without improving. `--plateau N` alone is too slow a stop
in that regime -- a whole `--budget-seconds` run can be eaten by one or two
owners, each burning its non-improving iterations at that pace before
`--plateau` finally trips. `--owner-seconds N` (default 2400) is a second,
independent stop: a wall-clock cap on one owner, checked *in addition to*
`--plateau`, whichever trips first.

- The timer starts the moment this run is about to make the owner's first
  generator call (`--mode full`) or first permuter job (`--mode
  permuter-only`) -- not when the owner's turn simply begins (prompt/example
  gathering before that first call doesn't count against it).
- It is only ever checked at a **safe point** -- before starting another
  generator call or permuter job -- never while one is actually running,
  so a running probe, generator call, or permuter job is never cut short by
  it.
- `state.json` tracks it per owner as `elapsed_seconds` (a running total,
  frozen and persisted every time the owner's attempt this run ends,
  whatever the terminal status) and a transient `started_at` (set only
  while this run's timer is actively running). A `--resume`d owner keeps
  accumulating onto its own `elapsed_seconds` -- time already spent on it in
  an earlier run of the same `--out` counts toward this run's cap too, so an
  owner that already burned most of its budget across several resumed runs
  stops quickly rather than getting a fresh 2400s every time.
- Exceeding the cap ends the owner with status `"time_cap"`, recorded
  exactly like a `"plateau"` (region note, tie-pool check, `best_candidates`
  kept for seeding -- §6 above); the run then moves on to the next owner.
- `--generator-timeout` (§2, §4.1) is also shrunk by whatever's left of an
  owner's `--owner-seconds` budget, on top of the run's remaining
  `--budget-seconds` -- so as an owner's cap nears, its next generator call
  is given correspondingly less time rather than being allowed to overrun it
  before the *following* iteration's safe-point check would otherwise catch
  it.

## 7. Output contract

Everything lands under the mounted `--out` directory:

| Path | Contents |
|---|---|
| `state.json` | `owner -> {best_similarity, iterations, history[], status, ...}` for every owner attempted this run; also carries per-owner `examples` (§4 item 3), `tie_pool` (§6.1), and `elapsed_seconds`/`started_at` (§6.2) |
| `accepted/<owner>.json` | a `fleet_probe` batch JSON (`source`, `declarations`, one `candidates[]` entry, optional `companion_edits`) for each owner that reached a gated accept |
| `accepted/<owner>.patch` | the same accepted change as a patch, for inspection without re-running anything |
| `tie-pool.json` | `owner -> {source, body, declarations, raw, label}`, cumulative across this run, for every owner whose plateaued or time-capped best was a register-allocation tie (§6, §6.1, §6.2); the `--tie-pool-file` input to a later `--mode permuter-only` pass |
| `region-notes/<source, "/" -> "__">.md` | dated notes appended on every accept/plateau/time_cap (§6, §6.2), in the exact shape `tools/region_notes.py append` produces; folded into `docs/regions/<source>.md` by the host merge step (§9.5) |
| `log.txt` | the run's diagnostics log |
| `summary.json` | owners attempted, owners matched, best similarity per owner, iteration counts, wall time for the run |
| `probe-stats/probe-stats.jsonl` | a copy of the runner's own probe-stats history (see §9.1) |

`merge` (§9) writes its own results back under the same `--out` directory:

| Path | Contents |
|---|---|
| `merge-results/<owner>.json` | the raw `fleet_probe --gate --json` result for each owner, kept (not deleted) so a failed re-gate can be inspected |
| `merge-results/<owner>.commit.log` | only when the host re-gate accepted but `git commit --only` then failed: the full combined stdout+stderr of that failed commit (§9's "commit failures" below) |
| `merge-report.json` | `owner -> status` for the run, plus `cc_check_bypassed` / `fresh_history` flags (§9.2/§9.3); an owner whose commit failed or succeeded maps to an object instead of a bare status string (below); cumulative across runs against the same `<out>` (§9.4); also carries this run's own (never cumulative) `notes_applied` (§9.5) and `names` (§9.6) |
| `merge-history.jsonl` | only with `--fresh-history`: this run's own probe-stats history (§9.3) |

`merge` also *reads* `<out>/region-notes/<source with "/" replaced by "__">.md`, if the container driver wrote any, when folding notes into `docs/regions/` (§9.5).

## 8. Why the container never commits

The container's own verdict is not trusted by construction -- it might be
running against a stale clone, a tampered tree, or (in test mode) fixed
candidates that were never really compared. `git commit` never happens
inside the container; landing changes is a **separate, deliberate step** run
on the host, against the host's own current checkout, exactly like fleet
mode treats `tools/integrate_fleet.py` as the only thing allowed to land a
branch (AGENTS.md §1.3). The in-container gate is the real ROM gate
(`make -C disasm COMPARE=1 -j2`), not a stand-in -- it's the container's
authority to *commit* that's withheld, not the rigor of its check; the host
merge step (§9) still re-runs that gate independently before trusting it.

## 9. Merging results

    python3 tools/container_merge.py merge /abs/out --commit

For each `accepted/<owner>.json`, this re-runs the real oracle on the host:

    python3 tools/fleet_probe.py accepted/<owner>.json --gate --json <result>

against **this** checkout -- not the container's. Only a candidate the host
itself just gated is eligible to be committed; the container's own
`accepted:` claim is not evidence on its own. A rejected owner is reported
and makes the command exit non-zero; nothing about it is committed.

With `--commit`, each owner the host re-gate accepts is committed by exact
path, per AGENTS.md §1.3's shared-checkout rule (`git commit --only
<source> -m "Land container match for <owner>"`) -- never `git add`, which
in a shared checkout would sweep in whatever another session has staged.

Useful flags: `--repo PATH` (host checkout to re-gate/commit against,
default `.`); `--dry-run` (re-gate every owner and print the table, but
never commit, even with `--commit`); `--no-cc-check` (§9.2); `--fresh-history`
(§9.3); `--owners a,b,c` (limit this run to those owners; §9.4); `--no-notes`
(§9.5); `--no-naming` (§9.6).

The command prints a table (owner, source, host-re-gate status, whether it
committed, detail) and exits non-zero if any container-accepted candidate
fails the host re-gate, so it is safe to gate a script or CI step on its
exit code (an owner skipped as `already_landed`, §9.4, counts as neither
accepted nor rejected and never affects the exit code). Every run also
writes `<out>/merge-report.json`
(`owner -> status`, plus the `--no-cc-check` / `--fresh-history` flags for
that run) and keeps each owner's raw `fleet_probe --gate --json` output at
`<out>/merge-results/<owner>.json` rather than deleting it, so a rejected
owner can be inspected after the fact without re-running anything.

**Commit failures.** A host re-gate accepting a candidate does not
guarantee `git commit --only <source>` then succeeds (a concurrent session
touched the same path, `--only` found nothing staged for it, etc). When
that happens the owner's row stays `accepted` / `committed: no`, and the
table's DETAIL column names the log file to check: `commit failed (see
merge-results/<owner>.commit.log)`. `merge` also prints the last 15 lines
of that commit's combined stdout+stderr directly in its own output, keeps
the full copy at `<out>/merge-results/<owner>.commit.log`, and records the
same 15-line tail in `merge-report.json` as
`{"status": "accepted", "committed": false, "commit_error": "<tail>"}` in
place of the plain status string every other owner gets -- so a commit
failure is visible without re-running anything.

**Commit successes.** When `git commit --only <source>` succeeds, `merge`
immediately reads the hash back (`git rev-parse HEAD` in `--repo`) and
records it in `merge-report.json` as
`{"status": "accepted", "committed": true, "commit": "<sha>"}` -- the
`"commit"` key is omitted if the hash couldn't be read back for some
reason, but `committed` stays `true`. A bare `"accepted"` string means the
host re-gate accepted but no commit was ever attempted (`--commit` not
passed, `--dry-run`, or a batch with no `source` to commit) -- see §9.4 for
why a *reader* must still treat a bare `"accepted"` string from an older
run as possibly meaning "committed" (`tools/fleetctl` already handles both
the plain-string and object shapes of an owner's entry; the `"commit"`
field is new and simply ignored by a reader that doesn't look for it).

To read a run's own progress without merging anything:
`python3 tools/container_merge.py summary /abs/out` prints `summary.json`
and `state.json` as readable tables (per-owner status, best similarity,
iteration/history counts).

`merge` always ends by printing a reminder to also run `import-stats`
(§9.1) -- probe-stats history is a separate import from accepted
candidates, and easy to forget since `merge` never does it for you.
(`--fresh-history` runs, §9.3, fold their own history in automatically on a
successful accept -- the reminder is still printed for the ordinary,
non-fresh-history probe-stats copy at `<out>/probe-stats/probe-stats.jsonl`.)

### 9.1 Importing probe-stats history

    python3 tools/container_merge.py import-stats /abs/out
    python3 tools/container_merge.py import-stats /abs/out --repo . --dry-run

The container's own runner (`tools/fleet_probe.py`/
`tools/try_pragma_compare.py`, via `tools/probe_stats.py`) records every
attempt it probes into a `PRAGMA_PROBE_STATS`-resolved JSONL history --
inside the container's own checkout, so it would be lost once the container
exits. `tools/container_agent.py` copies it out to
`<out>/probe-stats/probe-stats.jsonl` on every state save and at finalize
(resolved the same way the runner resolves it: the `PRAGMA_PROBE_STATS` env
var if set -- empty disables it entirely -- else
`<repo>/disasm/probe-stats/probe-stats.jsonl`). `import-stats` folds that
copy into *this* checkout's own probe-stats history (resolved the same
way), appending only lines not already present verbatim -- a safe, careful
line-level dedupe rather than a blind concatenation, so re-running
`import-stats` on the same out dir, or importing the same run from two
different out dirs, never double-counts. It prints how many lines were
read, how many were new, and how many were already present; `--dry-run`
counts without writing. Like `merge`, this never runs automatically -- it
is its own deliberate host-side step.

### 9.2 `--no-cc-check`: working around an unrelated host clang failure

    python3 tools/container_merge.py merge /abs/out --commit --no-cc-check

`disasm/Makefile`'s `COMPARE=1` build runs a host clang syntax check
(`RUN_CC_CHECK=1`, `CC_CHECK_COMP=gcc` -- which is clang on macOS) over the
whole tree as part of `merge`'s host re-gate. On the first real merge, an
unrelated file (`disasm/src/fragments/79/fragment79_37A6E0.c`, three "too
many arguments to function call" errors) failed that check, which made
*every* host re-gate report `compare_rejected` regardless of the
candidate -- the ROM gate itself never even ran.

`--no-cc-check` sets `PRAGMA_GATE_CC_CHECK=0` for the `fleet_probe --gate`
subprocess only (this process's own environment, and any other subprocess
it starts, are untouched), which `tools/try_pragma_compare.py` honours by
passing `RUN_CC_CHECK=0` to `make`. This is a real bypass of a real check,
so it is loud by design: `merge` prints a `WARNING` line naming it, and
records `"cc_check_bypassed": true` in `<out>/merge-report.json` (alongside
the run's `owner -> status` map) as a durable record that every candidate
accepted in that run was **not** verified to compile cleanly by the host's
own check. Use it only to work around a known-unrelated failure, and treat
`merge-report.json`'s flag as something to check before trusting a
`--no-cc-check` run's results.

### 9.3 `--fresh-history`: re-gating without the shared probe-stats history

    python3 tools/container_merge.py merge /abs/out --commit --fresh-history

The host's shared probe-stats history (§9.1's target,
`<repo>/disasm/probe-stats/probe-stats.jsonl` by default) is also a
preflight the runner consults before probing: it dedups on the exact
attempt body, so once one host re-gate has been recorded as rejected (for
example, because of the clang-check problem §9.2 exists for), a second
`merge` attempt for the same owner is refused before it even reaches the
ROM gate ("already rejected") -- even after the underlying problem is
fixed.

`--fresh-history` points `PRAGMA_PROBE_STATS` at a dedicated
`<out>/merge-history.jsonl` for the `fleet_probe --gate` subprocess
(created empty if it doesn't already exist, and reused across every owner
in the same `merge` run), so the runner's preflight only ever sees attempts
*this run* has made -- never a prior host re-gate recorded in the real,
shared history. That real history is also exactly what
`tools/check_decomp_provenance.py`'s pre-commit hook checks for an
"accepted attempt on record" before it allows a `disasm/src` file's removal
to be committed, so re-gating against a private history file alone would
make a `--fresh-history` merge's own commit step fail that hook.

**Ordering matters here.** `merge` closes this gap per owner, immediately
after that owner's re-gate accepts and *before* `git commit --only` is even
attempted for it: it folds `<out>/merge-history.jsonl`'s accepted line(s)
(only lines with at least one `attempts[].status == "accepted"` entry --
never the rejected-attempt noise from the rest of the run) into the host's
real probe-stats history, using the same verbatim-dedup logic as
`import-stats` (§9.1), so the pre-commit hook already finds the accepted
attempt it requires by the time it runs. This was found the hard way on a
real merge with `--fresh-history --commit`: the host re-gate accepted the
owner, but the commit step reported "committed 0/1 accepted owner(s)" with
no error recorded anywhere in `merge-report.json`, because the import back
then only ran once, after *every* owner's commit had already been
attempted -- so the pre-commit hook never saw an accepted attempt on record
and silently refused every commit. (With `commit=False`/`--dry-run`, where
no commit is ever attempted, the same import still runs once at the end of
the run so the accepted evidence is still on record.) This happens
automatically as part of `merge` itself -- no separate `import-stats` step
is needed for `--fresh-history`'s own history file (see §9's note on the
reminder `merge` still prints for the *ordinary* probe-stats copy).

### 9.4 Idempotency: re-running `merge` safely

    python3 tools/container_merge.py merge /abs/out --commit
    python3 tools/container_merge.py merge /abs/out --commit   # run again: safe

`merge` is safe to re-run against the same `--out` directory, including
with `--commit`, without re-doing (or re-attempting to commit) work an
earlier run already landed. This was found the hard way: running `merge
<out> --fresh-history --commit` a second time on an out dir whose
`accepted/func_A.json` had already been merged and committed earlier
re-gated `func_A` again -- which reinstalled the same body into an
already-matched source and then `git commit --only` failed with nothing to
commit, reporting "accepted / commit failed" for an owner that had, in
fact, already landed cleanly.

Before re-gating an owner, `merge` checks two independent signals and, if
either fires, skips it entirely -- never calling `fleet_probe --gate` or
`git commit --only` for it at all -- with status `"already_landed"`:

* the owner's batch `source` file, read from **this** checkout (`--repo`),
  no longer contains that owner's `#pragma GLOBAL_ASM(".../<owner>.s")`
  line (the same pattern `tools/container_agent.py`'s `PRAGMA_RE` matches)
  -- i.e. the candidate is already installed in the tree, regardless of
  what any report says; or
* the previous `merge-report.json` in `--out` (if any) already marks this
  owner committed -- either the plain `"accepted"` string (ambiguous
  before this fix -- it could mean "committed" or "accepted but never
  committed" -- so a bare `"accepted"` string from *any* run, old or new,
  is read conservatively as already-committed) or an object entry with
  `"committed": true`.

`already_landed` counts as neither accepted nor rejected: it never makes
`merge`'s exit code non-zero, and the table's STATUS column shows it
plainly so a run's output still names every owner it looked at.

`merge-report.json` is cumulative across runs against the same `--out`: an
owner not present in this run's `rows` at all (skipped via `--owners`,
below) keeps whatever entry an earlier run recorded for it, rather than
disappearing. An owner this run *did* touch -- including one resolved as
`already_landed` -- always gets this run's own entry, overwriting whatever
an earlier run recorded for it.

**`--owners a,b,c`** limits a `merge` run to just those owners (matched
against `accepted/<owner>.json` stems); every other owner's accepted batch
is left completely untouched this run. Combined with the cumulative report
above, this makes it possible to retry a single stuck owner (say, after
fixing whatever made its commit fail) without re-touching everything else
in a large `--out` directory:

    python3 tools/container_merge.py merge /abs/out --commit --owners func_A

### 9.5 Applying container region notes

    python3 tools/container_merge.py merge /abs/out --commit
    python3 tools/container_merge.py merge /abs/out --commit --no-notes

The container driver can write file-specific knowledge (skip lists, proven
spellings, unsolved shapes -- see `tools/region_notes.py`'s own module
docstring) as it works a source file, one file per owner's `source`, to
`<out>/region-notes/<source with "/" replaced by "__">.md` (e.g.
`disasm/src/4AC10.c` -> `<out>/region-notes/disasm__src__4AC10.c.md`) in the
same on-disk shape `region_notes.py append` itself produces (a `# Region
notes -- ...` header, then dated `## ...` sections). `merge` never trusts
that copy directly, the same "redo it against this checkout" spirit as the
re-gate itself: for every such file it finds, it extracts each note line
(skipping the structural markdown) and replays only the ones not already on
record, verbatim, in this checkout's own `docs/regions/<source>.md`, via

    python3 tools/region_notes.py append <source> --text "<line>"

so a re-run over the same `<out>`, or two different `<out>` dirs that
happened to record the same note, never double-writes it.

This runs **regardless of whether any owner was accepted this run** -- a
run where every candidate was rejected can still carry useful notes for the
next attempt. With `--commit`, a `source` this run also committed at least
one owner for gets its notes folded into that owner's own land commit
(`git commit --only <source> docs/regions/<source>.md`, reusing "Land
container match for `<owner>`"); a `source` with new notes but no accept
this run gets its own commit instead, "Record container run notes for
`<source>`", with `--only` on just the notes file. Without `--commit` (or
with `--dry-run`), notes are still folded into the working tree, just never
committed. Disable entirely with `--no-notes`. Every run records this run's
own `notes_applied` in `merge-report.json` (`source -> newly appended
lines`, omitting a source with nothing new) -- never cumulative across runs,
unlike `owners` (§9.4).

### 9.6 Naming a function on accept

    python3 tools/container_merge.py merge /abs/out --commit
    python3 tools/container_merge.py merge /abs/out --commit --no-naming

`tools/try_pragma_compare.py`'s own `PRAGMA_NAME_ON_ACCEPT` opt-in already
renames a just-accepted winner in-container, immediately, if
`tools/name_decompiled.py` already has an evidence-backed name for it and
no other pragma owner remains (see that tool's own module docstring). This
does the host-side equivalent, deliberately, right after an owner is
accepted **and committed** by this `merge` run: it offers the owner's
function to

    python3 tools/name_decompiled.py plan --only <function> --repo-root <repo>

and, only if that proposes an evidence-backed name, actually lands it with

    python3 tools/name_decompiled.py apply --only <function> --repo-root <repo>

`apply` can still refuse a plan-proposed name (a collision with an existing
symbol), in which case nothing is renamed. A rename that does land gets its
own follow-up commit, "Name `<owner>` -> `<name>`", over every
`disasm/src`/`disasm/include` file `apply` actually touched -- found via
`git status --porcelain` (filtered to those two trees) rather than asking
`apply` for a file list, since it reports only counts. Nothing here amends
an existing commit. A failure at any step (the subprocess itself, or a
refused/unconfirmed rename) is only logged, never fails the `merge` run --
naming is a bonus, not a gate. Disable entirely with `--no-naming`. Every
run records this run's own `names` in `merge-report.json` (`owner -> new
name`, only for owners actually renamed this run) -- never cumulative
across runs, unlike `owners` (§9.4).

IDO's compiler passes (`as0`, `as1`, `ugen`) create `ctm*` temp files that
honour `$TMPDIR` and only get removed on a normal exit. decomp-permuter
kills unpromising candidate compiles by design (that's how it works), so a
pass gets killed constantly and strands its file -- ~7.5M files/hour
measured during an active run (issue: IDO temp-file leak in the container).
There are two sinks, not one: plain `/tmp`, and `/work/disasm/scratch`
(`tools/try_pragma_compare.py` redirects `TMPDIR` there at import for any
runner-driven compile, e.g. via `tools/permute_candidate.py`).

`container/run.sh` mounts both as bounded tmpfs (`--tmpfs /tmp:size=2g,
nr_inodes=4m` and the same for `/work/disasm/scratch`), so a leak fails
loudly (ENOSPC / inode exhaustion) instead of silently growing the
container's writable layer -- and, since neither is a bind mount, never
touches host disk either way. `container/entrypoint.sh` also runs a
background sweeper for the life of the container: every 120s it deletes
`ctm*` files idle 5+ minutes (far above a live compile's lifetime of
seconds) from both directories, so a long session never gets close to the
cap.

To verify a leak isn't accumulating during a run:

    docker exec <container> sh -c \
        "find /tmp /work/disasm/scratch -maxdepth 1 -name 'ctm*' | wc -l"

This should stay bounded (tens to low hundreds, not climbing into the
thousands/millions), not grow unbounded. Count files, not bytes: on
APFS/overlay, a directory's on-disk size is a high-water mark of entries
it has ever held and never shrinks, so `du`/`stat` on the directory itself
looks the same whether cleanup is working or not -- only a file count
reflects it.
