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
        [--merge-repo M] [--max-concurrent 4] [--integration-branch master] \
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

`--merge-repo M` points the merge/branch/PR step -- `git checkout`,
`git checkout -b`, `tools/container_merge.py merge`/`import-stats`,
`git push`, `gh pr create` -- at a different checkout than `--repo`
(`container/run.sh`'s cwd and `tools/pragma_targets.py`'s target). Defaults
to `--repo` when omitted, the common case of one shared checkout; set it
when the merge/branch/PR step should run against a dedicated merge worktree
instead (see sec 2 for exactly which calls this affects).

A run left in the queue after a pass records **why** in `state.json`'s
`wait_reason` field, distinct from `stopped_reason`: `"cooldown"` (its
agent is cooling down) or `"concurrency"` (the global `--max-concurrent` cap
or that agent's own `--agent-concurrency` cap is full) -- `fleetctl status`
shows it alongside the cooldowns table so an operator can tell "waiting for
a slot" from "waiting out a cooldown" at a glance.

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
count, note/stopped-reason/wait-reason/needs-manual-commit owners), a
`NEEDS MANUAL COMMIT` section (one line per owner still awaiting a manual
`git commit --only`, with its run id, branch, out dir, and the first line
of the recorded commit error -- see sec 2's "Reading the merge report"),
a cooldowns table, and a `running=N queued=M (agent=n ...)` summary line.

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
                (owners neither matched nor awaiting a manual commit:
                 fresh run, new run id, seeded from this out dir,
                 appended to the queue)
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

1. `git -C <merge-repo> checkout <integration-branch>`
2. `git -C <merge-repo> checkout -b container/<run-id> <integration-branch>` --
   created *before* the merge commit so any commit `merge --commit` makes
   lands on this throwaway branch, not the integration branch.
3. `python3 tools/container_merge.py merge <out> --repo <merge-repo> --fresh-history --commit`
4. `python3 tools/container_merge.py import-stats <out> --repo <merge-repo>`
5. Read `<out>/merge-report.json`'s `owners` map (see "Reading the merge
   report" below) for this run's matched owners. If any:
   - `git -C <merge-repo> push -u origin container/<run-id>`
   - `gh pr create --base <integration-branch> --title "Container match: <owners>" --body <owner/status table>`
     -- the table also names any owner that needs a manual commit (below),
     so it is never silently dropped from a PR opened for its sibling
     owners.
6. `git -C <merge-repo> checkout <integration-branch>` regardless of whether
   anything was accepted, so the checkout is never left on a throwaway
   branch between runs.

`<merge-repo>` is `--merge-repo` if set, else `--repo` (sec 1).

`--fresh-history` and `--commit` are always passed to `merge` (sec 9.3 of
`docs/CONTAINER_AGENT.md` -- a prior host re-gate on record must never trip
the "already rejected" preflight for a re-attempt); `--no-cc-check` is not
passed by `fleetctl run` itself (it is a real bypass of a real check, per
sec 9.2, and stays a human's deliberate call outside this tool).

**Reading the merge report.** `tools/container_merge.py`'s
`write_merge_report` (see its own docstring) maps each owner to either a
bare status string (`"accepted"`, `"rejected"`, `"error"`, ...) or, when a
host re-gate accepted the candidate but the immediately-following
`git commit --only` failed, an object
`{"status": "accepted", "committed": false, "commit_error": "<tail>"}`.
`fleetctl` treats an owner as **matched** only when its status is
`"accepted"` *and* (it is the bare-string form -- committed, or commit was
never attempted -- or the object form's own `committed` is `true`);
`state.json`'s `matched_owners` and the PR's accepted-owner list are built
from exactly this set. An owner that is `"accepted"` but the object form
with `committed: false` is recorded separately, in `state.json`'s
`needs_manual_commit` map (owner -> the commit-error tail), and is:

- **not** counted as matched (no silent "probably fine"),
- **not** requeued for a fresh attempt -- its candidate is already applied
  in `<merge-repo>`'s working tree on the throwaway `container/<run-id>`
  branch (the failed step is only the commit itself), so requeueing would
  have a fresh container re-probe a duplicate of work already done,
- surfaced in `fleetctl status` (a `NEEDS MANUAL COMMIT` section plus a
  per-row note) and in the PR body's status table when a PR opens for other
  matched owners of the same run.

An operator resolves one by inspecting `<merge-repo>`'s working tree (and
`<out>/merge-results/<owner>.commit.log` for the full failure, not just the
15-line tail `fleetctl` keeps) and committing by hand.

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
reboots/crashes rather than driving individual passes itself.

### 4.1 Scripted install: `container/install_fleetctl_service.sh`

    container/install_fleetctl_service.sh [--repo <path>] [--dry-run] [--uninstall]

Builds `tools/fleetctl` (`go build -o ~/.local/bin/fleetctl .` run with cwd
`<repo>/tools/fleetctl` -- that directory's own `go.mod`, not a repo-root
one, is why a plain `go build ./tools/fleetctl` from the repo root doesn't
work; same invocation as this doc's own "Build it once" line above, just
with an absolute `-o`), writes
`~/Library/LaunchAgents/com.gs-decomp.fleetctl.plist`, and
`launchctl bootstrap gui/$UID` it (the modern, non-deprecated replacement
for `launchctl load` -- booting out first if a prior instance is already
loaded, so re-running the installer is idempotent). `--repo` defaults to
the checkout the script itself lives in. The plist it writes runs:

    fleetctl run --plan <state-dir>/plan.json --state-dir <state-dir> \
        --runs-dir ~/projects/gs-container-runs --repo <repo> \
        --src-overlay <repo> --max-concurrent 4 --alert-macos

where `<state-dir>` is `~/projects/gs-container-runs/fleet-state`, with
`KeepAlive`/`RunAtLoad` both true, both stdout and stderr redirected to
`~/Library/Logs/gs-decomp/fleetctl.log`, and an explicit `PATH` (launchd
agents don't inherit an interactive shell's) built from `docker`'s and
`gh`'s resolved directories plus the usual Homebrew/system locations, so
the containers, `git`, and `gh pr create` `fleetctl run` shells out to are
all reachable.

**`--plan` is still required.** `fleetctl run` (as of this writing) has no
fallback when `--plan` is omitted -- there is no default plan path it
reads on its own. The installer always passes
`--plan <state-dir>/plan.json`, so generate that file once *before*
installing (or after changing the file set fleetctl should work on):

    fleetctl plan --repo <repo> --files N --slots 4 --agent claude:sonnet \
        --out ~/projects/gs-container-runs/fleet-state/plan.json

`fleetctl run` only ever reads `--plan` to seed `state.json`; re-loading
the same plan on every launchd restart is a no-op for any run id
`state.json` already knows (sec 3), so this is a one-time step per plan,
not a per-restart chore. The installer checks whether the file exists and
prints this same reminder if it doesn't.

**`--src-overlay` and `--alert-macos` contract, for whoever is implementing
them on `fleetctl run`:** neither flag exists yet as of this writing (see
`tools/fleetctl/cmd_run.go`'s current flag set) -- the installer only
*invokes* `fleetctl` with them, matching this doc's own rule (sec 0) that
`fleetctl` never touches `container/*`/`disasm/*`/`.github/*` itself, only
invokes them.
- `--src-overlay <dir>`: forward it as `SRC_OVERLAY=<dir>` in the
  environment of every `container/run.sh` invocation `fleetctl run`
  launches (`tools/fleetctl/internal/runner`) -- exactly as if a human had
  exported `SRC_OVERLAY=<dir>` before running `container/run.sh` by hand.
  See `docs/CONTAINER_AGENT.md` sec 2.2 for the full contract: `run.sh`
  mounts `<dir>` read-only at `/src` and passes the container's
  `entrypoint.sh` the fixed in-container path (`SRC_OVERLAY=/src`);
  `entrypoint.sh` then overlays `<dir>`'s `disasm/src`/`disasm/include`/
  `disasm/linker_scripts` onto the image's build tree and runs one
  incremental `make -C disasm rom` before the driver starts, so a fleet
  running against an image that predates some already-merged owners
  doesn't keep rediscovering them. Passing `--repo`'s own value is the
  common case (the fleet's own checkout is exactly the source of truth for
  what has landed) -- `fleetctl plan`'s doc note about `--merge-repo`
  differing from `--repo` (sec 6) applies here too, if that setup is ever
  used.
- `--alert-macos`: `tools/fleetctl/internal/runner/runner.go` already
  carries a comment naming this flag's one effect -- an
  `osascript -e 'display notification ...'` call, presumably on a run
  reaching `merging`/`done`/an operator-actionable `stopped_reason` so a
  human working elsewhere on the same Mac notices without tailing
  `fleetctl status` or the log file.

`--dry-run` prints the composed plist body and every command the installer
would otherwise run (`mkdir`, `go build`, `launchctl bootout`/`bootstrap`)
without creating a directory, building anything, writing a file, or
invoking `launchctl` -- safe to run against a real `--repo`.
`--uninstall` (`--dry-run` also works with it) runs
`launchctl bootout gui/$UID/com.gs-decomp.fleetctl` (if loaded) and removes
the plist; like unloading by hand, it does **not** stop already-launched
containers -- run `fleetctl stop --state-dir <state-dir> --all` first if
you want that too.

### 4.2 Manual plist, if you'd rather not use the installer

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

A PR is opened only when a run has at least one **matched** owner (sec 2 --
accepted and committed), titled `Container match: <owner1>, <owner2>, ...`
(every matched owner in that run, sorted), based against
`--integration-branch` (default `master`), with a body table of every owner
the run attempted and that owner's status (`accepted`, `rejected`, `error`,
or, for an accepted-but-uncommitted owner, `accepted, NOT committed (needs
manual commit; see fleetctl status)`).

## 6. Design notes / open questions

- **Merge-repo == launch-repo, unless `--merge-repo` says otherwise.**
  `fleetctl run` takes `--repo` for `container/run.sh`'s cwd and
  `tools/pragma_targets.py`'s target, and a separate `--merge-repo`
  (defaulting to `--repo`) for the merge/branch/PR step's
  `git`/`gh`/`tools/container_merge.py --repo` calls (sec 1, sec 2). Every
  current use still points both at the same single shared checkout; the
  flag exists for a setup that wants a dedicated merge worktree instead.
- **Per-agent concurrency vs. cooldown interaction.** An agent at its
  `--agent-concurrency` cap is treated identically to one on cooldown for
  *launch* purposes (skipped this pass, retried next pass), but
  `state.json`'s `wait_reason` field (sec 1) now records which one applied
  to a still-queued run, and `fleetctl status` prints it -- "waiting for a
  slot" (`"concurrency"`, whether the global `--max-concurrent` cap or a
  per-agent `--agent-concurrency` cap) is distinguishable from "waiting out
  a cooldown" (`"cooldown"`) without cross-referencing the cooldowns table
  by hand.
- **`merge-report.json`'s `owners` map now records the commit outcome too**
  (`tools/container_merge.py`'s `write_merge_report`): an owner whose host
  re-gate accepted the candidate but whose own `git commit --only` failed
  maps to `{"status": "accepted", "committed": false, "commit_error": ...}`
  instead of a bare string, and `fleetctl` reads that -- such an owner is
  excluded from `matched_owners`/the PR's accepted list, recorded in
  `needs_manual_commit` instead of silently reported "matched", and neither
  requeued (the candidate is already applied in the merge repo's working
  tree) nor dropped (it is surfaced in `fleetctl status` and the PR body;
  see sec 2's "Reading the merge report").
- **No automatic backoff on repeated `--resume` failures.** A run that
  keeps coming back `generator_exhausted` is requeued and retried every
  time its agent's cooldown lapses, forever -- there is no cap on
  `Attempt` or escalating cooldown. `fleetctl status`'s `ATTEMPT` column is
  the signal an operator would watch to notice one spinning.
