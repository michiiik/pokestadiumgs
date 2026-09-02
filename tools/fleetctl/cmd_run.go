package main

import (
	"context"
	"flag"
	"fmt"
	"os"
	"os/signal"
	"path/filepath"
	"syscall"
	"time"

	"fleetctl/internal/control"
	"fleetctl/internal/fleetstate"
	"fleetctl/internal/planpkg"
	"fleetctl/internal/runner"
)

func runRunCmd(args []string) error {
	fs := flag.NewFlagSet("run", flag.ContinueOnError)
	planPath := fs.String("plan", "", "plan JSON from `fleetctl plan` (required the first time --state-dir has no plan persisted in state.json yet; a restart reuses it, see docs sec 3)")
	stateDir := fs.String("state-dir", "", "directory holding state.json (required)")
	runsDir := fs.String("runs-dir", "", "directory each run's --out dir is created under (required)")
	repo := fs.String("repo", "", "checkout to launch containers from, and tools/pragma_targets.py runs against (required)")
	mergeRepo := fs.String("merge-repo", "", "checkout the merge/branch/PR/self-merge step (git fetch/checkout -B/checkout --detach/push, tools/container_merge.py, gh pr create/checks/merge/view) operates on (default: --repo)")
	maxConcurrent := fs.Int("max-concurrent", -1, "max containers running at once (default: the plan's --slots, else 4)")
	prBase := fs.String("pr-base", "master", "branch a run's throwaway branch is PR'd into, and (with --auto-merge) merged into")
	baseRef := fs.String("base-ref", "", "ref the merge repo's throwaway branch is force-created from (git checkout -B) and left detached at afterward -- default origin/<pr-base>. Deliberately a remote-tracking ref, never --pr-base's own local branch: the merge repo may be a linked worktree whose local base branch is already checked out elsewhere (e.g. the main checkout), so the merge flow never checks that branch out itself")
	once := fs.Bool("once", false, "perform a single control-loop pass and exit, instead of looping until the queue drains")
	dryRun := fs.Bool("dry-run", false, "print every docker/git/gh command instead of executing it (real containers are never started, no gh pr merge/issue comment ever runs for real)")
	defaultCooldown := fs.Duration("default-cooldown", time.Hour, "cooldown applied to an agent with no --cooldown entry in the plan")
	pollInterval := fs.Duration("poll-interval", 30*time.Second, "how often to poll running containers")
	pythonBin := fs.String("python", "", "override the python3 binary (default: python3 on PATH)")
	permuterSeconds := fs.Int("permuter-seconds", 0, "--permuter-seconds passed to every permuter-lane launch (sec 13); 0 = the built-in default (1200)")

	autoMerge := fs.Bool("auto-merge", true, "once a run's PR's checks are all green, `gh pr merge --merge --delete-branch` it automatically (see docs sec 2, self-merge on green)")
	replan := fs.Bool("replan", false, "re-run the ranking against --merge-repo and rebuild the pending queue once at startup, before entering the control loop (see docs sec 2, replanning)")
	srcOverlay := fs.String("src-overlay", "", "when set, forwarded to every launch as env SRC_OVERLAY=DIR (container/run.sh + entrypoint.sh overlay these sources into the container at start, so a launch after a merge does not need a rebuilt image); also suppresses the stale-image warning")
	stallAfter := fs.Duration("stall-after", 3*time.Hour, "alert when a running run's best similarity has not improved for this long")

	alertIssue := fs.Int("alert-issue", 0, "post alerts as comments on this GitHub issue number (gh issue comment), rate-limited to one per event type per hour, plus a daily summary (see --daily-summary-hour)")
	alertMacOS := fs.Bool("alert-macos", false, "post alerts as macOS notifications (osascript display notification)")
	dailySummaryHour := fs.Int("daily-summary-hour", 9, "UTC hour (0-23) --alert-issue posts its once-daily summary at")

	if err := fs.Parse(args); err != nil {
		return err
	}
	if *stateDir == "" || *runsDir == "" || *repo == "" {
		return fmt.Errorf("run: --state-dir, --runs-dir, and --repo are all required")
	}
	if *dailySummaryHour < 0 || *dailySummaryHour > 23 {
		return fmt.Errorf("run: --daily-summary-hour must be 0-23, got %d", *dailySummaryHour)
	}

	statePath := filepath.Join(*stateDir, "state.json")
	state, err := fleetstate.Load(statePath)
	if err != nil {
		return err
	}

	execRunner := &runner.ExecRunner{RepoRoot: *repo, PythonBin: *pythonBin, DryRun: *dryRun}

	loop := &control.Loop{
		Runner:              execRunner,
		State:               state,
		StatePath:           statePath,
		RunsDir:             *runsDir,
		Repo:                *repo,
		MergeRepo:           *mergeRepo,
		IntegrationBranch:   *prBase,
		BaseRef:             *baseRef,
		DefaultCooldown:     *defaultCooldown,
		PollInterval:        *pollInterval,
		DisableAutoMerge:    !*autoMerge,
		SrcOverlay:          *srcOverlay,
		StallAfter:          *stallAfter,
		DailySummaryHourUTC: *dailySummaryHour,
		PermuterSeconds:     *permuterSeconds,
	}

	mergeRepoPath := *mergeRepo
	if mergeRepoPath == "" {
		mergeRepoPath = *repo
	}
	if *alertIssue > 0 {
		issueNotifier := &control.IssueNotifier{Runner: execRunner, Repo: mergeRepoPath, Issue: *alertIssue}
		loop.Notifiers = append(loop.Notifiers, issueNotifier)
		loop.DailySummaryNotifier = issueNotifier
	}
	if *alertMacOS {
		loop.Notifiers = append(loop.Notifiers, &control.MacOSNotifier{Runner: execRunner})
	}

	if *planPath != "" {
		plan, err := planpkg.Load(*planPath)
		if err != nil {
			return err
		}
		if err := loop.LoadPlan(plan); err != nil {
			return err
		}
		if *maxConcurrent > 0 {
			loop.MaxConcurrent = *maxConcurrent
		} else if plan.Slots > 0 {
			loop.MaxConcurrent = plan.Slots
		}
	} else {
		persisted, ok := loop.PersistedPlan()
		if !ok {
			return fmt.Errorf("run: --plan is required the first time --state-dir has no plan persisted yet (%s)", statePath)
		}
		if *maxConcurrent > 0 {
			loop.MaxConcurrent = *maxConcurrent
		} else if persisted.Slots > 0 {
			loop.MaxConcurrent = persisted.Slots
		}
	}
	if err := state.SaveAtomic(statePath); err != nil {
		return err
	}

	ctx, cancel := signal.NotifyContext(context.Background(), os.Interrupt, syscall.SIGTERM)
	defer cancel()

	if *dryRun {
		fmt.Fprintln(os.Stdout, "fleetctl: --dry-run: no container, git, gh pr merge, or gh issue comment command below actually ran")
	}

	if *replan {
		if err := loop.Replan(ctx); err != nil {
			return fmt.Errorf("run: --replan: %w", err)
		}
		if err := state.SaveAtomic(statePath); err != nil {
			return err
		}
	}

	return loop.Run(ctx, *once)
}
