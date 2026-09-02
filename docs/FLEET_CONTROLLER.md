# fleetctl: the container-fleet orchestrator

Issue #39 follow-up. `docs/CONTAINER_AGENT.md` documents one container: one
source file, a budget, `container/run.sh` to launch it, and
`tools/container_merge.py` to re-gate/commit its results afterward. Running
more than a couple of these by hand means babysitting `docker inspect` in a
loop, remembering which out dir seeds which retry, and never forgetting the
merge step. `tools/fleetctl/` is a single Go binary, `fleetctl`, that
replaces that human orchestrator. It never touches `tools/*.py`,
`container/*`, `disasm/*`, or `.github/*` itself -- it only *invokes* them,
exactly the commands documented in `docs/CONTAINER_AGENT.md` and
`tools/container_merge.py --help`.

Build it once:

    cd tools/fleetctl && go build -o fleetctl .

Everything below assumes that binary is on your `PATH` or invoked by path.

## 1. Commands

### `fleetctl plan`

    fleetctl plan --repo R (--files N | --file F...) --slots K \
        --agent SPEC [--agent SPEC ...] \
        [--owners-per-run 12] [--budget-seconds 3600] \
        [--cooldown AGENT=DURATION ...] [--agent-concurrency AGENT=N ...] \
        [--max-instructions N] [--exclude-recent HOURS] \
        [--out plan.json]

Picks files (`python3 tools/pragma_targets.py rank-files --json`, top
`--files N` by the same `actionable_fresh`-first ordering
`AGENTS.md` sec 1.1 tells a fleet coordinator to use -- or an explicit
`--file` list, repeatable, instead of ranking), lists each file's owners
(`python3 tools/pragma_targets.py targets --source F`, already
smallest-instructions-first), and splits that owner list into partitions of
at most `--owners-per-run` (default 12). Every partition becomes one queued
run spec, with an agent spec assigned round-robin across the whole queue in
file order. The result is written as JSON to `--out` (default `plan.json`);
`fleetctl run` reads that file, it never re-ranks anything itself.

**Agent spec format:** `agent:model[:effort]`, e.g.
`codex:gpt-5.6-luna:high`, `kimi:kimi-code/k3:high`, `alibaba:qwen3.7-max`,
`claude:sonnet` -- the same `AGENT`/`GENERATOR_MODEL`/`GENERATOR_EFFORT`
triple `docs/CONTAINER_AGENT.md` sec 3 documents. `--agent` is repeatable;
pass it once per agent you want in the rotation (repeating the same agent
spec gives it a larger share of the round robin).

`--cooldown AGENT=DURATION` (e.g. `--cooldown kimi=5h`) and
`--agent-concurrency AGENT=N` are baked into the plan and read by `run`:
a `generator_exhausted` exit puts that agent on cooldown for its configured
duration (default one hour, `run`'s own `--default-cooldown`, for an agent
with no `--cooldown` entry); an agent at its `--agent-concurrency` cap is
skipped when `run` looks for the next queue entry to launch, independent of
the global `--max-concurrent`. `--slots K` is recorded as the plan's
suggested fleet size and becomes `run`'s default `--max-concurrent` when
`run` isn't given its own.

`plan` only ever runs `tools/pragma_targets.py` (read-only queries) -- it
never touches docker, git, or GitHub, so there is no `--dry-run` for it.

### `fleetctl run`

    fleetctl run --plan P --state-dir S --runs-dir D --repo R \
        [--max-concurrent 4] [--integration-branch master] \
        [--once] [--dry-run] [--default-cooldown 1h] [--poll-interval 30s]

The control loop. Loads `--plan`'s queue into `<state-dir>/state.json`
(skipping any run id already present, so re-running `run` against the same
`--state-dir` after a restart is idempotent -- see sec 3). Each pass:

1. **Poll.** `docker inspect` every run currently `running`, every
   `--poll-interval` (default 30s).
2. **Handle exits.** See sec 2's state machine for the full switch.
3. **Launch.** Fill free concurrency slots (global `--max-concurrent`, and
   each agent's own `--agent-concurrency` cap from the plan) from the front
   of the queue, skipping (not dropping) any entry whose agent is currently
   on cooldown.
4. **Persist.** `state.json` is rewritten atomically (temp file + rename)
   after every pass.

`--once` performs a single pass and returns instead of looping until the
queue drains -- used for the `--dry-run` smoke test (sec 5) and for driving
the loop from an external scheduler (sec 4) instead of its own sleep.

`--dry-run` prints every `docker`/`git`/`gh` command instead of running it
(`container/run.sh` and `tools/container_merge.py`/`tools/pragma_targets.py`
invocations are still real subprocess constructions logged verbatim; only
the process that would actually start a container, move a branch, commit,
push, or open a PR is suppressed). **No real container is ever started
under `--dry-run`** -- `LaunchContainer` returns a synthetic
`dryrun-<run-id>` id and the poll loop treats it as already exited-cleanly
on the next pass, so a `--dry-run --once` run is safe to point at the real
`--repo` and real plan.

### `fleetctl status`

    fleetctl status --state-dir S

Prints one row per run (id, status, file, agent, owner count, matched-owner
count, note/stopped-reason), a cooldowns table, and a
`running=N queued=M (agent=n ...)` summary line.

### `fleetctl stop`

    fleetctl stop --state-dir S --run ID
    fleetctl stop --state-dir S --all [--dry-run]

Stops container(s) **by the container id recorded in `state.json`, never by
a docker filter or label match** -- `--all` walks every run `state.json`
marks `running` and stops exactly those ids; a run id `state.json` does not
know, or one not currently `running`, is refused with an error rather than
silently matched some other way. This is the only command allowed to
`docker stop` anything, and it is still restricted to what fleetctl itself
launched and recorded.

## 2. State machine

    queued --launch--> running --exit--> [handleExit switch]
                                              |
                     stopped_reason == "generator_exhausted"
                                              |
                                              v
                    requeued (agent cooled down, --resume, same out dir)
                                              |
                              (relaunched once capacity/cooldown allow)
                                              v
                                          running (Attempt+1)

                     stopped_reason missing/unreadable (container vanished)
                                              |
                                              v
                    requeued (--resume, same out dir, Attempt+1)

                          any other stopped_reason
                     (budget_expired, plateau, a normal completion, ...)
                                              |
                                              v
                                          merging
                                              |
                (sequential: branch -> merge --commit -> import-stats ->
                 push+PR if any owner matched -> checkout back)
                                              v
                                            done
                                              |
                (owners the merge left unmatched: fresh run, new run id,
                 seeded from this out dir, appended to the queue)
                                              v
                                    a *new* queued entry

A `--resume` requeue reuses the **same** run id and out dir (the container
image's own `--resume` flag continues that exact `state.json`); a
post-merge requeue for unmatched owners gets a **new** id
(`<original-id>-r1`, `-r2`, ...) and a fresh out dir seeded from the just-
finished run (never `--resume` and `--seed-from` together, matching
`docs/CONTAINER_AGENT.md` sec 2.1's own rule). Both kinds of requeue go back
onto the same queue and may be relaunched in the very same control-loop
pass that requeued them, if capacity and cooldowns allow -- `state.json`'s
`status` field always reflects the *latest* attempt, and `attempt` counts
how many times a `--resume` id has been relaunched.

`merging` never runs concurrently with itself: `run`'s control loop is a
single goroutine with no concurrent merge dispatch, so "one merge at a
time" (required because the git index is shared -- `AGENTS.md` sec 1.3) is
structural, not a separate lock. The merge step itself is:

1. `git -C <repo> checkout <integration-branch>`
2. `git -C <repo> checkout -b container/<run-id> <integration-branch>` --
   created *before* the merge commit so any commit `merge --commit` makes
   lands on this throwaway branch, not the integration branch.
3. `python3 tools/container_merge.py merge <out> --repo <repo> --fresh-history --commit`
4. `python3 tools/container_merge.py import-stats <out> --repo <repo>`
5. Read `<out>/merge-report.json`'s `owners` map for this run's accepted
   owners. If any:
   - `git -C <repo> push -u origin container/<run-id>`
   - `gh pr create --base <integration-branch> --title "Container match: <owners>" --body <owner/status table>`
6. `git -C <repo> checkout <integration-branch>` regardless of whether
   anything was accepted, so the checkout is never left on a throwaway
   branch between runs.

`--fresh-history` and `--commit` are always passed to `merge` (sec 9.3 of
`docs/CONTAINER_AGENT.md` -- a prior host re-gate on record must never trip
the "already rejected" preflight for a re-attempt); `--no-cc-check` is not
passed by `fleetctl run` itself (it is a real bypass of a real check, per
sec 9.2, and stays a human's deliberate call outside this tool).

## 3. Persistence and restart

`<state-dir>/state.json` is the only state `fleetctl run` needs: it is
rewritten atomically (write to a sibling temp file, `fsync`, `rename`)
after every pass, so a kill at any point leaves either the previous or the
current pass's state, never a partial write. Restarting `fleetctl run`
with the same `--state-dir`/`--plan` re-loads it, skips every plan queue
entry whose run id is already known, and continues polling any run still
marked `running` (a real container that outlived the restart is picked
back up by its recorded container id) -- an idempotent resume, not a
re-plan.

## 4. Running under launchd

`fleetctl run` without `--once` already loops forever (poll, handle exits,
launch, sleep `--poll-interval`) until the queue and every run drain, so
the simplest launchd job just keeps the process alive across machine
reboots/crashes rather than driving individual passes itself:

```xml
<!-- ~/Library/LaunchAgents/com.local.fleetctl.plist -->
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN"
  "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>Label</key><string>com.local.fleetctl</string>
  <key>ProgramArguments</key>
  <array>
    <string>/usr/local/bin/fleetctl</string>
    <string>run</string>
    <string>--plan</string><string>/abs/path/plan.json</string>
    <string>--state-dir</string><string>/abs/path/state</string>
    <string>--runs-dir</string><string>/abs/path/runs</string>
    <string>--repo</string><string>/abs/path/pokemonStadiumGSRecomp</string>
  </array>
  <key>RunAtLoad</key><true/>
  <key>KeepAlive</key><true/>
  <key>StandardOutPath</key><string>/abs/path/fleetctl.log</string>
  <key>StandardErrorPath</key><string>/abs/path/fleetctl.log</string>
</dict>
</plist>
```

Load/unload with `launchctl load|unload ~/Library/LaunchAgents/com.local.fleetctl.plist`.
Because state is on disk and reloading a plan is idempotent (sec 3), a
crash-restart under `KeepAlive` is safe; `fleetctl stop --state-dir S --all`
before `launchctl unload` is the clean way to also stop in-flight
containers (unloading the agent alone does not touch already-launched
containers -- they keep running until their own budget or `stop` ends
them).

An alternative for a single supervised pass per invocation (e.g. driven by
`cron` or another scheduler instead of `KeepAlive`) is `--once`, run
repeatedly on whatever interval you want polling to happen.

## 5. Branch and PR naming

A run's throwaway branch is `container/<run-id>`, where `<run-id>` is the
plan's own run id: `<fileslug>-p<N>` for an original partition (e.g.
`container/14640-p0`) or `<fileslug>-p<N>-r<M>` for the `M`th post-merge
reseed of that partition (e.g. `container/14640-p0-r1`). `<fileslug>` is
the source file's basename without `.c`
(`disasm/src/fragments/79/fragment79_3BF4C0.c` -> `fragment79_3BF4C0`).

A PR is opened only when a run's host re-gate accepted at least one owner,
titled `Container match: <owner1>, <owner2>, ...` (every accepted owner in
that run, sorted), based against `--integration-branch` (default
`master`), with a body table of every owner the run attempted and that
owner's `merge-report.json` status (`accepted`, `rejected`, or `error`).

## 6. Design notes / open questions

- **Merge-repo == launch-repo.** `fleetctl run` takes one `--repo` for
  everything: `container/run.sh`'s cwd, `tools/container_merge.py`'s
  `--repo`, and the checkout `git`/`gh` operate on. A setup that wants the
  merge/branch/PR step to run against a *different* checkout than the one
  containers are launched from (e.g. a dedicated merge worktree) would need
  a second `--merge-repo` flag; not added since every current use is a
  single shared checkout.
- **Per-agent concurrency vs. cooldown interaction.** An agent at its
  `--agent-concurrency` cap is treated identically to one on cooldown
  (skipped this pass, retried next pass) -- there is no separate signal in
  `status` distinguishing "waiting for a slot" from "waiting out a
  cooldown" beyond the cooldowns table already printed.
- **`merge-report.json`'s `owners` map is the only signal `fleetctl` reads
  to decide what got committed** -- it does not separately confirm each
  accepted owner's `git commit --only` actually succeeded (that is
  `tools/container_merge.py`'s own `committed`/`commit_detail` column,
  visible in its printed table but not in `merge-report.json`). A commit
  failure after an accepted re-gate would currently still be reported as
  "matched" by `fleetctl status`; surfacing `container_merge.py`'s commit
  outcome per owner would need either a `merge-report.json` schema change
  owned by `tools/container_merge.py` or parsing its stdout table.
- **No automatic backoff on repeated `--resume` failures.** A run that
  keeps coming back `generator_exhausted` is requeued and retried every
  time its agent's cooldown lapses, forever -- there is no cap on
  `Attempt` or escalating cooldown. `fleetctl status`'s `ATTEMPT` column is
  the signal an operator would watch to notice one spinning.
