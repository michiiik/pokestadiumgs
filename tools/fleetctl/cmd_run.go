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
	planPath := fs.String("plan", "", "plan JSON from `fleetctl plan` (required)")
	stateDir := fs.String("state-dir", "", "directory holding state.json (required)")
	runsDir := fs.String("runs-dir", "", "directory each run's --out dir is created under (required)")
	repo := fs.String("repo", "", "checkout to launch containers / merge / branch / PR against (required)")
	maxConcurrent := fs.Int("max-concurrent", -1, "max containers running at once (default: the plan's --slots, else 4)")
	integrationBranch := fs.String("integration-branch", "master", "branch a run's throwaway branch is cut from and PR'd back into")
	once := fs.Bool("once", false, "perform a single control-loop pass and exit, instead of looping until the queue drains")
	dryRun := fs.Bool("dry-run", false, "print every docker/git/gh command instead of executing it (real containers are never started)")
	defaultCooldown := fs.Duration("default-cooldown", time.Hour, "cooldown applied to an agent with no --cooldown entry in the plan")
	pollInterval := fs.Duration("poll-interval", 30*time.Second, "how often to poll running containers")
	pythonBin := fs.String("python", "", "override the python3 binary (default: python3 on PATH)")
	if err := fs.Parse(args); err != nil {
		return err
	}
	if *planPath == "" || *stateDir == "" || *runsDir == "" || *repo == "" {
		return fmt.Errorf("run: --plan, --state-dir, --runs-dir, and --repo are all required")
	}

	plan, err := planpkg.Load(*planPath)
	if err != nil {
		return err
	}
	statePath := filepath.Join(*stateDir, "state.json")
	state, err := fleetstate.Load(statePath)
	if err != nil {
		return err
	}

	execRunner := &runner.ExecRunner{RepoRoot: *repo, PythonBin: *pythonBin, DryRun: *dryRun}

	loop := &control.Loop{
		Runner:            execRunner,
		State:             state,
		StatePath:         statePath,
		RunsDir:           *runsDir,
		Repo:              *repo,
		IntegrationBranch: *integrationBranch,
		DefaultCooldown:   *defaultCooldown,
		PollInterval:      *pollInterval,
	}
	if *maxConcurrent > 0 {
		loop.MaxConcurrent = *maxConcurrent
	} else if plan.Slots > 0 {
		loop.MaxConcurrent = plan.Slots
	}

	if err := loop.LoadPlan(plan); err != nil {
		return err
	}
	if err := state.SaveAtomic(statePath); err != nil {
		return err
	}

	ctx, cancel := signal.NotifyContext(context.Background(), os.Interrupt, syscall.SIGTERM)
	defer cancel()

	if *dryRun {
		fmt.Fprintln(os.Stdout, "fleetctl: --dry-run: no container, git, or gh command below actually ran")
	}
	return loop.Run(ctx, *once)
}
