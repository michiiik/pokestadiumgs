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
        [--window AGENT=DURATION ...] [--window-budget AGENT=N ...] \
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
the global `--max-concurrent`. Rather than leave a slot idle while its
assigned agent cools down, `run` reassigns that queued partition to another
agent from this same `--agent` roster instead -- see sec 12. `--slots K` is
recorded as the plan's suggested fleet size and becomes `run`'s default
`--max-concurrent` when `run` isn't given its own.

`--window AGENT=DURATION` (e.g. `--window kimi=5h` -- a known quota-window
length, distinct from `--cooldown`'s generator-exhaustion backoff duration,
though the two are commonly the same number) and `--window-budget
AGENT=N` (an optional expected-batches-per-window, informational only) are
also baked into the plan. Both are read by `fleetctl status`'s per-agent
METRICS table (sec 11) and by `run`'s quota-window-aware scheduling (sec
12); an agent with no `--window` entry falls back to its own `--cooldown`
entry, then a 24h default.

`plan` only ever runs `tools/pragma_targets.py` (read-only queries) -- it
never touches docker, git, or GitHub, so there is no `--dry-run` for it.

### `fleetctl run`

    fleetctl run [--plan P] --state-dir S --runs-dir D --repo R \
        [--merge-repo M] [--max-concurrent 4] [--pr-base master] \
        [--base-ref REF] \
        [--once] [--dry-run] [--default-cooldown 1h] [--poll-interval 30s] \
        [--auto-merge] [--replan] [--src-overlay DIR] [--stall-after 3h] \
        [--permuter-seconds 1200] \
        [--alert-issue N] [--alert-macos] [--daily-summary-hour 9]

The control loop. Loads `--plan`'s queue into `<state-dir>/state.json`
(skipping any run id already present, so re-running `run` against the same
`--state-dir` after a restart is idempotent -- see sec 3). Each pass:

1. **Poll.** `docker inspect` every run currently `running`, every
   `--poll-interval` (default 30s); also reads `<out>/state.json` for a
   no-progress-stall check (sec 9).
2. **Handle exits.** See sec 2's state machine for the full switch.
3. **Poll PRs.** (`--auto-merge`, default true.) For every run currently
   `pr_open`, check its PR's CI checks and merge it on green -- sec 7.
4. **Launch.** Fill free concurrency slots (global `--max-concurrent`, and
   each agent's own `--agent-concurrency` cap from the plan) from the front
   of the queue. An entry whose agent is currently on cooldown is not just
   skipped: it is reassigned to the next eligible agent from the plan's own
   roster instead, so the slot is not left idle (sec 12) -- only a
   single-agent plan (or every other agent also unavailable) falls back to
   waiting. Replanning (sec 8) also enqueues one permuter-lane partition per
   file with owners still pending in its tie-pool store (sec 13); those
   count toward `--max-concurrent` like any other launch but are exempt
   from every per-agent cap and cooldown.
5. **Persist.** `state.json` is rewritten atomically (temp file + rename)
   after every pass.

`--merge-repo M` points the merge/branch/PR/self-merge step -- `git fetch`,
`git checkout -B`/`checkout --detach`, `tools/container_merge.py
merge`/`import-stats`, `git push`, `gh pr
create`/`checks`/`merge`/`view` -- at a different checkout than `--repo`
(`container/run.sh`'s cwd and `tools/pragma_targets.py`'s target, including
the ranking `--replan` re-runs -- sec 8). Defaults to `--repo` when omitted,
the common case of one shared checkout; set it when the merge/branch/PR
step should run against a dedicated merge worktree instead (see sec 2 for
exactly which calls this affects).

**`--merge-repo` never checks out, force-resets, or pulls `--pr-base`'s own
local branch.** If `--merge-repo` is a linked worktree of the same
checkout `--repo` (or another session) uses, that local branch may already
be checked out elsewhere -- `git checkout master` there fails outright
("already checked out"), and even when it wouldn't fail, that local branch
copy is commonly stale. Instead, every merge-repo git call sec 2/7
describes below works against `--base-ref` (default
`origin/<pr-base>`) -- a remote-tracking ref -- and the merge repo is left
**detached** at it between runs, never on a named local base branch.
`git fetch origin` is the merge repo's only call that touches that
remote-tracking ref at all.

**`--plan` is required only the first time `--state-dir` has no plan
persisted in `state.json` yet.** `LoadPlan` now persists the whole plan
(not just its queue) into `state.json`, so a restart of `run` against the
same `--state-dir` reuses it automatically -- `--plan` is still accepted
(and still idempotent to repeat, sec 3) for whoever wants to be explicit,
but omitting it on a restart is no longer an error the way it used to be.

A run left in the queue after a pass records **why** in `state.json`'s
`wait_reason` field, distinct from `stopped_reason`: `"cooldown"` (its
agent is cooling down) or `"concurrency"` (the global `--max-concurrent` cap
or that agent's own `--agent-concurrency` cap is full) -- `fleetctl status`
shows it alongside the cooldowns table so an operator can tell "waiting for
a slot" from "waiting out a cooldown" at a glance.

`--once` performs a single pass and returns instead of looping until the
queue drains -- used for the `--dry-run` smoke test (sec 5) and for driving
the loop from an external scheduler (sec 4) instead of its own sleep.

`--dry-run` prints every `docker`/`git`/`gh pr create`/`gh pr merge`/`gh
issue comment`/`osascript` command instead of running it
(`container/run.sh` and `tools/container_merge.py`/`tools/pragma_targets.py`
invocations, plus the read-only `gh pr checks`/`gh pr view`/`git status
--porcelain`/`docker image inspect` queries sec 2/7/10 use, are still real
subprocess constructions, logged verbatim; only the process that would
actually start a container, move a branch, commit, push, merge a PR,
comment on an issue, or open a PR is suppressed). **No real container is
ever started under `--dry-run`, and
`gh pr merge`/`gh issue comment` never run for real** -- `LaunchContainer`
returns a synthetic `dryrun-<run-id>` id and the poll loop treats it as
already exited-cleanly on the next pass, and `GhPRCreate` returns an empty
URL (so a run can never reach `pr_open` under `--dry-run`, since there is
no real PR number to poll) -- a `--dry-run --once` run is safe to point at
the real `--repo`/`--merge-repo` and a real plan, `--replan` included.

See sec 7 (self-merge), sec 8 (replanning), sec 9 (alerting), sec 10
(stale-image awareness), sec 12 (quota-window-aware scheduling), and sec 13
(the permuter-only lane, including `--permuter-seconds`) for the rest of
this section's flags.

### `fleetctl status`

    fleetctl status --state-dir S [--json]

Prints one row per run (id, status, file, agent, owner count, matched-owner
count, note/stopped-reason/wait-reason/needs-manual-commit owners/PR URL), a
`NEEDS MANUAL COMMIT` section (one line per owner still awaiting a manual
`git commit --only`, with its run id, branch, out dir, and the first line
of the recorded commit error -- see sec 2's "Reading the merge report"),
a cooldowns table, a `METRICS` table (one row per agent spec seen in
`state.json`'s runs -- runs/iterations/accepts, accepts per wall-hour,
accepts per configured quota window, mean iterations-to-accept, and current
cooldown state; see sec 11), a `MERGE BLOCKED: <reason>` line when a
post-merge fast-forward has failed (sec 7), and a
`running=N queued=M (agent=n ...)` summary line. A run whose merge step
found `--merge-repo` dirty in a way that would conflict with the merge (sec
2) shows status `merge_blocked_dirty`, with the conflicting path in its
note column, plus (once at least one retry has run) `retried Nx` -- distinct
from `MERGE BLOCKED`, which is global (every run), not per-run. `--json`
prints the same information as one
`control.BuildStatus` JSON document instead (its `metrics` field is the
METRICS table) -- for scripting, and what the `--alert-issue` daily summary
(sec 9) embeds for machines.

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
             dirty? (git status --porcelain finds a conflicting path, sec 2)
                              |                                  |
                             yes                                 no
                              |                                  |
                              v                                  v
                    merge_blocked_dirty          (sequential: fetch -> branch -B
                    (alert, retried at the         <base-ref> -> merge --commit ->
                    top of every pass until          import-stats -> push+PR if any
                    clean)                            owner matched -> checkout
                                                      --detach <base-ref>)
                                                                   v
                       no owner matched --------------- >=1 owner matched
                              |                                  |
                              v                                  v
                            done                    --auto-merge (default true)?
                              |                        |                  |
                              |                       yes                 no
                              |                        |                  |
                              |                        v                  v
                              |                     pr_open              done
                              |                        |
                              |            [pollPRs: gh pr checks, every pass]
                              |                        |
                              |            SUCCESS-----+-----FAILURE
                              |                |                |
                              |                v                v
                              |     gh pr merge, then      gate_failed
                              |     fetch <base-ref>       (alert, left
                              |     (sec 7); on success:    open, never
                              |     merged + Replan (sec 8) auto-retried)
                              |                |
                              v                v
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

0a. `git -C <merge-repo> reset -q -- COVERAGE.md` then
   `git -C <merge-repo> checkout -- COVERAGE.md` -- unconditionally discards
   any uncommitted state in COVERAGE.md before the dirty check below ever
   runs. `.githooks/pre-commit.d/10-coverage.sh` regenerates and stages
   COVERAGE.md on *every* commit, so a prior `git commit --only <file>` in
   this same merge repo (this merge step's own commit path, sec 2 step 3)
   routinely leaves a fresh, uncommitted COVERAGE.md behind -- a leftover
   from the merge step's own last success, never another session's
   conflicting work, and safe to discard outright since the hook
   regenerates it from scratch on the next real commit anyway.
0b. `git -C <merge-repo> status --porcelain` -- if any **tracked** entry
   (not `??` untracked) names a path under `disasm/src/` or `docs/regions/`
   (the trees the merge step itself writes to, besides COVERAGE.md, which
   step 0a above already made harmless), abort immediately: no fetch, no
   branch, no commit. The run moves to `merge_blocked_dirty` (its note
   names the conflicting path) and a rate-limited `merge_blocked_dirty`
   alert fires (sec 9). Unlike `gate_failed`, this is not "never
   auto-retried": the *next* pass (and every pass after that, at the very
   top, before anything else touches the merge repo) redoes step 0a and
   this check, so a run left `merge_blocked_dirty` recovers on its own as
   soon as an operator cleans up the conflicting path -- no restart needed.
   `fleetctl status`'s note column shows `retried Nx` once at least one
   retry has run (`state.json`'s `merge_blocked_retries`). Anything else --
   untracked files anywhere, or tracked modifications outside those two
   paths (e.g. another session's own uncommitted edits to
   `disasm/Makefile` or `tools/try_pragma_compare.py`) -- is tolerated:
   `<merge-repo>` is commonly a checkout other tools/sessions share, and
   only the paths this merge would actually touch need to be clean.
1. `git -C <merge-repo> fetch origin`
2. `git -C <merge-repo> checkout -B container/<run-id> <base-ref>` --
   force-created (`-B`, not `-b`) *before* the merge commit, from
   `<base-ref>` fresh off the fetch, so any commit `merge --commit` makes
   lands on this throwaway branch, not the base branch, and always starts
   from current remote state rather than wherever the branch was left last
   time.
3. `python3 tools/container_merge.py merge <out> --repo <merge-repo> --fresh-history --commit`
4. `python3 tools/container_merge.py import-stats <out> --repo <merge-repo>`
5. Read `<out>/merge-report.json`'s `owners` map (see "Reading the merge
   report" below) for this run's matched owners. If any:
   - `git -C <merge-repo> push -u origin container/<run-id>`
   - `gh pr create --base <pr-base> --title "Container match: <owners>" --body <owner/status table>`
     -- the table also names any owner that needs a manual commit (below),
     so it is never silently dropped from a PR opened for its sibling
     owners. The PR's number (parsed from the printed URL) is recorded in
     `state.json` as `pr_number`; with `--auto-merge` (default true) this
     run's status becomes `pr_open` instead of `done` -- see sec 7 for what
     happens next. `--auto-merge=false` restores the pre-self-merge
     behavior: `done`, PR left open for a human.
6. `git -C <merge-repo> checkout --detach <base-ref>` regardless of whether
   anything was accepted, so the merge repo is never left on a throwaway
   branch between runs -- and never on a named local base branch either
   (see sec 1's "`--merge-repo` never checks out ... `--pr-base`'s own
   local branch").

`<merge-repo>` is `--merge-repo` if set, else `--repo` (sec 1). `<pr-base>`
is `--pr-base` (sec 1; default `master`) -- the branch name `gh pr
create --base`/`gh pr merge` operate on. `<base-ref>` is `--base-ref` (sec
1; default `origin/<pr-base>`) -- the ref every merge-repo git call above
actually branches from, verifies against, and detaches onto; it replaces
the earlier `--integration-branch` flag name now that the same branch is
also self-merge's target (sec 7), not just where a throwaway branch is cut
from.

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
with the same `--state-dir` (with or without `--plan` -- sec 1) re-loads
whatever plan is persisted, skips every queue entry whose run id is already
known, and continues polling any run still marked `running` (a real
container that outlived the restart is picked back up by its recorded
container id) -- an idempotent resume, not a re-plan. Pass `--replan` to
additionally rebuild the queue from a fresh ranking on this same restart
(sec 8); without it, a restart is a pure resume.

Besides the run queue, `state.json` also persists: the most recently
loaded/rebuilt plan itself (`plan`, a `planpkg.Plan`, used by `Replan` to
know what ranking options to rebuild with -- sec 8); `merge_blocked`/
`merge_blocked_reason` (sec 7, a paused self-merge); `last_merge_at` (sec 10,
stale-image awareness); and `alert_sent`/`last_daily_summary` (sec 9's
rate-limit bookkeeping).

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

**`--plan` still generate it once first.** `fleetctl run` no longer *errors*
without `--plan` once a plan has already been persisted into `state.json`
(sec 1, sec 3), but the very first launch against a fresh `--state-dir`
still needs one -- there is no default plan path `run` invents on its own.
The installer always passes `--plan <state-dir>/plan.json`, so generate
that file once *before* installing (or after changing the file set fleetctl
should work on from scratch, as opposed to letting `--replan` -- sec 8 --
evolve the existing persisted one):

    fleetctl plan --repo <repo> --files N --slots 4 --agent claude:sonnet \
        --out ~/projects/gs-container-runs/fleet-state/plan.json

`fleetctl run` only reads `--plan` to seed `state.json` the first time;
passing it again on every launchd restart is harmless (a no-op for any run
id `state.json` already knows, sec 3) but no longer necessary. The
installer checks whether the file exists and prints this same reminder if
it doesn't.

**`--src-overlay` and `--alert-macos` are now implemented** (sec 7's
self-merge landed the rest of `fleetctl run`'s auto-merge/replan/alerting
surface in the same change): `--src-overlay <dir>` forwards `SRC_OVERLAY=
<dir>` in the environment of every `container/run.sh` invocation
`fleetctl run` launches (`tools/fleetctl/internal/runner`) -- exactly as if
a human had exported `SRC_OVERLAY=<dir>` before running `container/run.sh`
by hand. See `docs/CONTAINER_AGENT.md` sec 2.2 for the full contract:
`run.sh` mounts `<dir>` read-only at `/src` and passes the container's
`entrypoint.sh` the fixed in-container path (`SRC_OVERLAY=/src`);
`entrypoint.sh` then overlays `<dir>`'s `disasm/src`/`disasm/include`/
`disasm/linker_scripts` onto the image's build tree and runs one
incremental `make -C disasm rom` before the driver starts, so a fleet
running against an image that predates some already-merged owners doesn't
keep rediscovering them -- and it also suppresses `fleetctl run`'s own
stale-image warning (sec 10), since an overlay makes the baked-in image
irrelevant. Passing `--repo`'s own value is the common case (the fleet's
own checkout is exactly the source of truth for what has landed) --
`fleetctl plan`'s doc note about `--merge-repo` differing from `--repo`
(sec 6) applies here too, if that setup is ever used. `--alert-macos` runs
`osascript -e 'display notification ...'` on every alert event (sec 9).

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
(every matched owner in that run, sorted), based against `--pr-base`
(default `master`), with a body table of every owner the run attempted and
that owner's status (`accepted`, `rejected`, `error`, or, for an
accepted-but-uncommitted owner, `accepted, NOT committed (needs manual
commit; see fleetctl status)`). With `--auto-merge` (default true) it is
also, from here, self-merged on green -- sec 7.

## 6. Design notes / open questions

- **Merge-repo == launch-repo, unless `--merge-repo` says otherwise.**
  `fleetctl run` takes `--repo` for `container/run.sh`'s cwd and
  `tools/pragma_targets.py`'s target, and a separate `--merge-repo`
  (defaulting to `--repo`) for the merge/branch/PR/self-merge step's
  `git`/`gh`/`tools/container_merge.py --repo` calls (sec 1, sec 2, sec 7)
  -- and, since replanning re-ranks (sec 8), for `Replan`'s own
  `tools/pragma_targets.py` calls too, deliberately *not* `--repo`. Every
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
- **A shared 1-hour rate-limit bucket across every configured notifier.**
  `Loop.alert` (sec 9) rate-limits once per `"event[:key]"` regardless of
  which of `--alert-issue`/`--alert-macos` is configured -- a macOS
  notification and an issue comment for the same event share one clock,
  rather than each notifier tracking its own. Simpler, and in practice the
  two are usually both on or both off.
- **Why `--base-ref` (a remote-tracking ref) instead of `--pr-base`'s own
  local branch.** `--merge-repo` is frequently a linked worktree of the
  same checkout `--repo` (or an entirely separate session/tool) already
  has checked out -- and git refuses to check out a branch that is already
  checked out in another worktree ("already checked out"), so a plain
  `git -C <merge-repo> checkout master` fails outright whenever the main
  checkout has `master` checked out, which is the common case. A local
  branch there can also simply be stale even when it isn't already
  checked out elsewhere. `--base-ref` (sec 1, sec 2, sec 7) sidesteps
  both: the merge repo only ever fetches, branches from, and detaches onto
  a remote-tracking ref, and never checks out, force-resets, or pulls the
  local branch of the same name.

## 7. Self-merge on green

Branch protection / auto-merge is not available on this repo (private,
no GitHub Pro), so `fleetctl run` merges its own PRs once
`.github/workflows/container-gate.yml`'s "Rebuild + compare ROM in
container" check goes green -- `--auto-merge` (default true; `false`
restores the pre-self-merge behavior of sec 2/sec 5, a PR left open at
`done` for a human).

Every pass, for every run currently `pr_open` (sorted by run id, so a
`--dry-run`/log trace is deterministic), `pollPRs`:

1. `gh pr checks <n> --json name,state` against `--merge-repo` (a read-only
   query -- never gated by `--dry-run`, same reasoning as
   `tools/pragma_targets.py`'s calls, sec 1). Every reported check's state
   rolls up into one of `SUCCESS` (every check succeeded, `SKIPPED`/
   `NEUTRAL` count as "did not block"), `FAILURE` (any one check reported
   `FAILURE`/`ERROR`/`CANCELLED`/`TIMED_OUT`/`ACTION_REQUIRED`/`STALE`), or
   `PENDING` (still running, or no checks reported yet) -- rechecked next
   pass.
2. **`SUCCESS`:** `gh pr merge <n> --merge --delete-branch`. On success the
   run moves to `merged` (`merged_at` recorded), then:
   - **fast-forward `<base-ref>`** in `--merge-repo`: `git fetch origin`
     -- and *only* that. `<merge-repo>`'s local `--pr-base` branch is never
     checked out or pulled here (sec 1, sec 2), so there is no local branch
     left to fast-forward or rebase -- fetching is enough to bring
     `<base-ref>` (e.g. `origin/master`) up to date with whatever `gh pr
     merge` just pushed. On success, `state.json`'s `last_merge_at` is
     updated (sec 10's stale-image awareness), `gh pr view <n> --json
     mergeCommit` is recorded as the run's `merge_commit_sha` (logging a
     non-blocking warning if a `git rev-parse <base-ref>` right after the
     fetch doesn't yet match it -- GitHub's own merge-commit metadata can
     lag the fetch by a beat), then **`Replan` runs** (sec 8) -- so the
     very next launch already sees whatever this merge just landed.
   - **On failure** (the fetch itself failed -- network, auth, ...),
     `state.json`'s `merge_blocked`/`merge_blocked_reason` are set, a
     rate-limited `ff_failed` alert fires (sec 9), and *no further
     `pr_open` run is evaluated this pass* -- "stop merging until fixed" is
     deliberately global, not per-run, since every self-merge shares the
     same `<base-ref>` and a stuck fetch usually means the merge repo (or
     its network access) genuinely needs a human's attention before any
     more of them can land cleanly. The *next* pass retries the fetch once,
     at the top of `pollPRs`, before touching any `pr_open` run -- if it
     now succeeds, `merge_blocked` clears and merging resumes
     automatically; no restart or flag needed to recover.
3. **`FAILURE`:** the run moves to `gate_failed`, a rate-limited
   `gate_failed` alert fires (sec 9), and it is left exactly as-is --
   `fleetctl status` (its PR URL is in the note column) and the PR itself
   are how an operator triages it. **Never auto-retried**: unlike a
   `generator_exhausted`/vanished container, a failed *host* CI check on
   already-accepted, already-committed candidates is not the kind of
   failure a fresh container attempt would fix.

## 8. Replanning

`Replan` re-runs the ranking against `--merge-repo` --
`rank-files --exclude-recent 0 --limit <plan's --files>` (or the plan's
original `--file` list verbatim, whichever the persisted plan used --
sec 3) and `targets --source <file>` for each -- and rebuilds the queue of
*pending* (not yet launched) partitions from the result: it runs
automatically after every successful self-merge (sec 7, step 2) and,
optionally, once more at startup with `--replan`, before the control loop's
first pass.

`--exclude-recent 0` (not omitted) is deliberate: unlike `fleetctl plan`'s
own default (which omits the flag -- no filtering at all), a fresh replan
still wants `rank-files`' unconditional dirty-working-tree exclusion, just
with no commit-recency window, since a replan should reconsider a file this
merge just touched rather than skip it for looking "recently touched".

Reconciling the fresh candidate partitions against the run already in
flight (`control.Loop.reconcileQueue`):

- **A queued-but-never-launched partition is dropped and wholesale
  replaced** by the fresh plan's own partitioning of that file -- "runs
  already queued but not launched are replaced by the fresh plan". A
  partition is "never launched" if it has no `started_at` recorded *and*
  carries no `seed_dirs`.
- **A post-merge reseed survives untouched** ("keep per-file seeding"): a
  queued partition with `seed_dirs` set (runMerge's own requeue of a run's
  unmatched owners, sec 2) is kept even though it has never itself been
  launched -- dropping it would discard the seed continuity (the
  contributing out dir's `state.json`/`accepted/`) that requeue just built
  for it.
- **A running/merging/`pr_open` run is never touched**, and every owner it
  is holding is reserved: a fresh partition covering the same file has
  those owners subtracted out, so a live attempt is never duplicated by a
  fresh one for the same file+owner. (In the ordinary case this is also
  automatic -- `targets` itself stops listing an owner once it is
  committed -- reservation only matters for an owner still *mid-attempt*,
  not yet landed, that `targets` still legitimately reports.)
- **A fresh partition's id can collide** with a partition number that is
  still active under the *first* replan for a file (partition numbering
  restarts at `p0` every `Replan`/`Build` call) -- when it does, the
  remaining, genuinely unclaimed owners are not silently dropped; they get
  the next free id via the same `<base>-r<N>` requeue-suffix mechanism sec 2
  uses for a post-merge reseed (`state.json`'s `requeue_seq`).

The reconciled plan (including the fresh ranking options) replaces
`state.json`'s persisted plan (sec 3), so a later `Replan` -- another
merge, or a future `--replan` restart -- keeps using the same `--files`/
`--file`/`--agent`/... options the original `fleetctl plan` invocation set,
without needing the plan file again.

## 9. Alerting

Six events, each posted through every configured `Notifier`
(`--alert-issue N`: `gh issue comment N --body ...` against `--merge-repo`;
`--alert-macos`: `osascript -e 'display notification ...'`), rate-limited
by `Loop.alert` to at most one post per `"event[:key]"` per hour (`key` is
typically a run id or agent name, so e.g. two different runs' `gate_failed`
alerts don't share a bucket, but `ff_failed` -- with no natural per-run key
-- does):

| Event | Fired when | Key |
|---|---|---|
| `gate_failed` | a PR's checks reported `FAILURE` (sec 7) | run id |
| `ff_failed` | the post-merge (or retry) fetch of `<base-ref>` failed (sec 7) | (none) |
| `merge_blocked_dirty` | a run's merge step found `--merge-repo` dirty in a way that conflicts with the merge (sec 2) | run id |
| `container_vanished` | a running container's id is no longer known to `docker inspect` (sec 2) | run id |
| `agent_exhausted` | a run stopped `generator_exhausted` (sec 2) | agent name |
| `no_progress_stall` | a still-`running` run's best similarity (read from `<out>/state.json`, the same per-owner `best_similarity` `docs/CONTAINER_AGENT.md` documents) hasn't improved for `--stall-after` (default 3h) | run id |
| `controller_error` | `RunOnce` returned an error (`Run`'s loop, before it exits) | (none) |

`--alert-issue N` additionally posts one **daily summary** -- runs
launched/finished, matches merged (with their `merge_commit_sha`), PRs
open, gate-failed count, stalled-run count, agents currently on cooldown,
plus an embedded `fleetctl status --json` block "for machines" (its
`metrics` field is the same per-agent throughput table sec 11 describes) --
at most once per UTC calendar day, at `--daily-summary-hour` (default 9,
0-23 UTC). `--alert-macos` does not post a daily summary (an ephemeral
notification isn't the right shape for a multi-paragraph report).

## 10. Stale-image awareness

Every launch (unless `--src-overlay` is set -- sec 1) queries
`docker image inspect gs-decomp-agent:latest --format '{{.Id}}|{{.Created}}'`
(read-only, never gated by `--dry-run`), records the id in that run's
`state.json` (`image_id`), and logs a warning when the image's build time
predates `state.json`'s own `last_merge_at` (sec 7 -- the last time
`fleetctl run`'s *own* self-merge landed a commit): the image was built
before code the fleet itself just merged, so a container launched from it
may re-discover already-accepted candidates or misjudge similarity against
stale reference sources. Rebuilding the image, or passing `--src-overlay`
(sec 1) so the launch overlays current sources without needing a rebuild,
are the two ways to clear the warning.

This only tracks merges `fleetctl run` performed itself (`--auto-merge`);
a commit landed by a human merging a PR by hand isn't reflected in
`last_merge_at`.

## 11. Per-agent throughput metrics

`control.BuildMetrics` computes one `AgentMetrics` row per distinct agent
spec seen in `state.json`'s runs -- shown as `fleetctl status`'s `METRICS`
table, `status --json`'s `metrics` field, and embedded in the `--alert-issue`
daily summary (sec 9). Nothing new is persisted for this: every input is
already on disk -- `state.json` itself (run records, `cooldowns`, the
persisted plan's `--cooldown`/`--window`/`--window-budget` maps) plus each
run's own `<out>/summary.json` and `<out>/state.json` (the per-owner record
`docs/CONTAINER_AGENT.md` documents: `status` -- `"accepted"` once matched --
and a cumulative `iterations` count, with a timestamped `history` entry per
generator batch).

Per agent:

- **`runs`** -- how many `state.json` run records have this agent.
- **`iterations`** -- the sum, across every one of those runs' own
  `<out>/state.json`, of every owner's `iterations` count.
- **`accepts`** -- how many of those owners have `status == "accepted"`.
- **`accepts_per_wall_hour`** -- `accepts` divided by summed wall-clock
  hours, one run's own contribution read from its `<out>/summary.json`'s
  `wall_seconds` (`tools/container_agent.py`'s `_finalize_run`) when
  present, else `ended_at - started_at` (`now` in place of `ended_at` for a
  run still `running`). Like `summary.json`'s own `wall_seconds`, this is
  only the *current* attempt's process lifetime -- a repeatedly `--resume`d
  run's wall-clock time from earlier attempts is not summed in (the same
  simplification sec 6 already notes for `Attempt`/cooldown accounting).
- **`quota_window`** / **`accepts_per_window`** -- `quota_window` is this
  agent's configured window length: its own `--window` entry if the plan
  has one, else its own `--cooldown` entry (the task's own "e.g. kimi=5h"
  example -- a `--cooldown`-only agent's window defaults to the same
  duration its generator-exhaustion backoff uses), else a 24h default.
  `accepts_per_window` is `accepts` normalized to that window length:
  `accepts / (wall_seconds / quota_window_seconds)`.
- **`window_budget`** -- this agent's `--window-budget` entry, if the plan
  has one; informational only (0/omitted otherwise), not read by any
  scheduling decision.
- **`mean_iterations_to_accept`** -- the mean, over every owner this
  agent's runs accepted, of that owner's own `iterations` count at
  acceptance (0/omitted with no accepts yet).
- **`on_cooldown`** / **`cooldown_until`** -- from `state.json`'s
  `cooldowns` map, exactly like the `COOLDOWNS` table.

`fleetctl status` (no `--json`) reads live (`time.Now()`); `status --json`
and the daily summary do the same. There is no injectable clock for this
path the way the control loop itself has one (`Loop.Now`, tests only) --
`accepts_per_wall_hour`/`accepts_per_window` for a still-`running` run
change slightly between two `status` calls a moment apart, same as the
`COOLDOWNS` table's own "remaining" column already does.

## 12. Quota-window-aware scheduling

An agent commonly has a real quota window shorter than how long a fleet
runs (e.g. a subscription plan that resets every 5h) -- `--cooldown` alone
already reacts to hitting that limit (`generator_exhausted` -> cool down ->
resume), but every queued partition assigned to that agent still just sits
idle for the whole cooldown even when another configured agent has spare
capacity right now. `--window AGENT=DURATION` (sec 1) names each agent's
known window length, and `run`'s control loop uses it (together with
`state.json`'s own tracked window start/exhaustion, `window_state`) to keep
those partitions moving instead:

- **Window start.** The first time an agent launches anything (fresh, or
  its first launch after a cooldown), `state.json`'s `window_state[agent]`
  records `window_start = now`.
- **Exhaustion.** A `generator_exhausted` exit (sec 2) still cools that
  agent down exactly as before, and additionally zeroes
  `window_state[agent].window_start` and stamps `last_exhausted = now` --
  its window has ended.
- **Reassignment instead of idling.** `launchEligible` (sec 1 step 4), on
  reaching a queued partition whose agent is currently on cooldown, no
  longer just leaves it queued: it looks for another agent from the plan's
  own `--agent` roster (deduplicated by agent name) that is itself neither
  on cooldown nor at its own `--agent-concurrency` cap, and launches the
  partition under that agent instead -- `RunSpec.Agent`/`Model`/`Effort` are
  rewritten to the reassigned agent, and the run's `note` records the
  reassignment (`"reassigned kimi->codex (cooldown)"`), so `fleetctl
  status`'s NOTE column shows it. Every reassignment is also logged. A plan
  with only one configured agent (or one where every other agent is
  likewise unavailable) has nothing to reassign to, so it falls back to
  exactly the pre-sec-12 behaviour: `wait_reason: "cooldown"`, retried next
  pass.
- **Rebalancing once a window reopens.** Among agents with spare capacity,
  one whose window has *just* reopened -- its cooldown has lapsed since it
  was last exhausted, but it has not yet been relaunched (`window_start`
  still zero) -- is preferred first, so the fleet swings load back onto it
  rather than leaving it starved by an ordinary round robin that happens to
  keep landing on other agents. Otherwise, eligible agents are walked
  round-robin from `state.json`'s persisted `reassign_cursor`, which
  advances past whichever agent is picked (and survives a restart).

None of this changes what `--agent-concurrency`/`--cooldown` themselves
mean -- a reassigned partition still counts against its *new* agent's own
cap once launched, and a cooling-down agent is still genuinely unavailable
for new work of its own until its cooldown lapses. `--window`/
`--window-budget` are otherwise inert for scheduling beyond feeding this
reassignment preference and sec 11's metrics -- they do not, for instance,
cap how much work an agent is handed within a window.

## 13. The permuter-only lane

Some owners plateau at a *register tie* or a normalized-only match: the
generator-driven loop (`docs/CONTAINER_AGENT.md`) cannot close the gap with
another prompted batch, but `decomp-permuter` grinding on the tied
candidate for a while longer sometimes can. `tools/container_agent.py`
(`--mode permuter-only`, another change) writes every such owner, whichever
run it happened on, to that run's own `<out>/tie-pool.json` --
`{owner: {source, body, declarations, raw, label}}`. `fleetctl run` collects
these across every run of a file and periodically launches a dedicated,
generator-free container against just that file's pending pool.

**Collection.** At the end of every run's merge step (`runMerge`, sec 2,
after `matched_owners` is known -- any run, permuter-lane or not, can
plateau into a `tie-pool.json`), `updateTiePool` merges that run's own
`<out>/tie-pool.json` (if it wrote one) into
`<runs-dir>/tie-pools/<fileslug>.json` -- one persisted store per source
file, `<fileslug>` the same `disasm/src/fragments/79/fragment79_3BF4C0.c` ->
`fragment79_3BF4C0` mapping sec 5 already uses for branch names. Any owner
that run's own `matched_owners` just landed is then dropped from the store
("owners removed once matched") -- a tie a later run actually resolves
never lingers in the pool forever.

**Enqueueing.** `Replan` (sec 8), after reconciling the queue, enqueues one
fresh permuter-only partition per `<runs-dir>/tie-pools/*.json` store that
still has at least one pending owner and no permuter-lane run already
active for that file (queued/running/merging/`pr_open`/requeued/
`merge_blocked_dirty`) -- so a store is never given two overlapping
partitions. The new `RunSpec` covers every owner currently in that store,
with `agent: "permuter"` and `mode: "permuter-only"`.

**Launch.** `launch()` copies the file's tie-pool store into
`<out>/tie-pool-input.json` and passes it to `container/run.sh` as:

    RUN_DETACHED=1 AGENT=permuter bash container/run.sh <file> <out> \
        --mode permuter-only --tie-pool-file /out/tie-pool-input.json \
        --permuter-seconds 1200 --owners <owner1,owner2,...>

`--permuter-seconds` is `run`'s own `--permuter-seconds` flag (default
1200) -- unlike an ordinary launch, **no `--budget-seconds` is passed at
all**: the permuter-only driver stops on `--permuter-seconds`/plateau, not
a wall-clock budget. The `permuter` agent spec carries no model and no API
key (`AGENT=permuter`, no `GENERATOR_MODEL`) -- it is never a target
`fleetctl plan --agent` accepts on the command line; `enqueuePermuterLane`
is the only code path that ever creates one. From here a permuter-lane run
is an ordinary `RunRecord`: it is polled, its exit still hands off to the
same merge/branch/PR step (sec 2) for whatever it managed to land, and any
still-plateaued owner it reports lands right back in the tie-pool store via
the collection step above.

**Never subject to cooldown, never counts against a model agent's cap.**
`launchEligible` never evaluates the on-cooldown case for `agent ==
"permuter"` at all (sec 12's reassignment logic also never treats it as a
candidate target); a `generator_exhausted` exit for it (which should never
happen -- there is no generator to exhaust) is requeued with `--resume` and
skips the cooldown/window bookkeeping entirely, defensively. A permuter-lane
run counts toward the global `--max-concurrent` cap exactly like any other
launch, but toward no agent's own `--agent-concurrency` cap except its own
(`byAgent["permuter"]`, which nothing else ever shares) -- a fleet that
never configures `--agent-concurrency permuter=N` leaves it uncapped
per-agent by construction.

**`container/entrypoint.sh` needs one more case for this to actually run
key-free.** `entrypoint.sh`'s auth guard (its `case "$AGENT" in ...`
block) already has no case for `AGENT=permuter` and falls through the
default `*)` branch, which does not demand a key -- so the guard itself
does not block this launch. But the block just above it,

    if [ "$have_generator_cmd" -eq 0 ] && [ "$have_candidate_file" -eq 0 ]; then
        args=(--generator-cmd "/work/container/generators/run_generator.sh {prompt} {batch}" "${args[@]}")
    fi

unconditionally defaults `--generator-cmd` onto the args whenever neither
`--generator-cmd` nor `--candidate-file` was passed -- which is exactly the
permuter-lane launch's shape (sec 13 passes neither). That silently hands
`container_agent.py --mode permuter-only` a `--generator-cmd` it never
asked for. `container/entrypoint.sh` was intentionally left untouched by
this change (out of scope -- `container/agent.py`'s own `--mode
permuter-only` support is a separate, concurrent change); it needs a third
"caller already handles this" detector alongside `have_generator_cmd`/
`have_candidate_file`, guarding *both* the default-`--generator-cmd`
injection above and the auth-guard block right after it:

    have_permuter_only=0
    prev=""
    for arg in "$@"; do
        case "$arg" in
            --generator-cmd|--generator-cmd=*) have_generator_cmd=1 ;;
            --candidate-file|--candidate-file=*) have_candidate_file=1 ;;
            --mode=permuter-only) have_permuter_only=1 ;;
        esac
        case "$prev $arg" in
            "--mode permuter-only") have_permuter_only=1 ;;
        esac
        prev="$arg"
    done

    args=("$@")
    if [ "$have_generator_cmd" -eq 0 ] && [ "$have_candidate_file" -eq 0 ] && [ "$have_permuter_only" -eq 0 ]; then
        args=(--generator-cmd "/work/container/generators/run_generator.sh {prompt} {batch}" "${args[@]}")
    fi

    if [ "$have_candidate_file" -eq 0 ] && [ "$have_generator_cmd" -eq 0 ] && [ "$have_permuter_only" -eq 0 ]; then
        AGENT="${AGENT:-claude}"
        ...
    fi

(the auth-guard `if` already happens to be harmless for `AGENT=permuter`
today, but gating it on `have_permuter_only` too keeps it that way
deliberately, rather than by accident of `permuter` matching no known
`case` arm.)
