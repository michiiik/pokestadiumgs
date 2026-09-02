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
| `--permuter-seconds` | budget per permuter invocation |
| `--owners` | restrict the run to an explicit owner list instead of every pragma in the file |
| `--generator-cmd` | shell template for candidate generation; `{prompt}` and `{batch}` are substituted |
| `--candidate-file` | test mode: use a fixed batch file once for the first owner, then exit -- no generator/model call at all |

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

## 5. Test mode

    container/run.sh disasm/src/X.c /abs/out --candidate-file /out/batch.json

`--candidate-file` skips the generator/model call entirely: the driver uses
that one fixed batch for the first owner, then exits. The file must be
visible *inside* the container, so put `batch.json` under the host out-dir
you're mounting to `/out` and refer to it by its in-container path
(`/out/batch.json`), not the host path. Like `--generator-cmd`, this also
skips `entrypoint.sh`'s API-key check.

## 6. Loop semantics

Per owner, until a terminal state:

1. Generate a batch of candidates via `--generator-cmd` (or `--candidate-file`
   in test mode).
2. Probe the batch (isolated object compare), then gate a link-verified hit
   through the full ROM compare -- the same runner fleet agents use
   (`tools/fleet_probe.py`, AGENTS.md §3.1).
3. On a near-miss, launch the permuter for up to `--permuter-seconds` and
   **poll its output directory** (`disasm/build/permuter/<function>-<suffix>/`)
   rather than waiting on any notification -- the fix for the exact failure
   #38 measured (three of five fleet trees stalled waiting on a permuter
   notification a subagent cannot receive). A container has no orchestrator
   to notify it either, so it must poll on its own clock.
4. Repeat until one of: the owner gates (`accepted`, move to the next
   owner); `--plateau N` iterations pass with no best-similarity improvement
   (stop this owner, record its plateaued state); or `--max-iterations` /
   `--budget-seconds` is exhausted for the run.

Every iteration's outcome (similarity, status, diagnostic) is appended to
that owner's `history[]` in `state.json` as it happens, so a run killed
mid-owner still leaves a readable trail.

## 7. Output contract

Everything lands under the mounted `--out` directory:

| Path | Contents |
|---|---|
| `state.json` | `owner -> {best_similarity, iterations, history[], status}` for every owner attempted this run |
| `accepted/<owner>.json` | a `fleet_probe` batch JSON (`source`, `declarations`, one `candidates[]` entry, optional `companion_edits`) for each owner that reached a gated accept |
| `accepted/<owner>.patch` | the same accepted change as a patch, for inspection without re-running anything |
| `log.txt` | the run's diagnostics log |
| `summary.json` | owners attempted, owners matched, best similarity per owner, iteration counts, wall time for the run |

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
never commit, even with `--commit`).

The command prints a table (owner, source, host-re-gate status, whether it
committed, detail) and exits non-zero if any container-accepted candidate
fails the host re-gate, so it is safe to gate a script or CI step on its
exit code.

To read a run's own progress without merging anything:
`python3 tools/container_merge.py summary /abs/out` prints `summary.json`
and `state.json` as readable tables (per-owner status, best similarity,
iteration/history counts).

## Temp-file leak bounding

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
