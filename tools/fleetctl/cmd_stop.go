package main

import (
	"context"
	"flag"
	"fmt"
	"path/filepath"

	"fleetctl/internal/control"
	"fleetctl/internal/fleetstate"
	"fleetctl/internal/runner"
)

func runStopCmd(args []string) error {
	fs := flag.NewFlagSet("stop", flag.ContinueOnError)
	stateDir := fs.String("state-dir", "", "directory holding state.json (required)")
	run := fs.String("run", "", "stop exactly this run id")
	all := fs.Bool("all", false, "stop every run currently marked running in state")
	dryRun := fs.Bool("dry-run", false, "print the docker stop command instead of executing it")
	if err := fs.Parse(args); err != nil {
		return err
	}
	if *stateDir == "" {
		return fmt.Errorf("stop: --state-dir is required")
	}
	if (*run == "") == *all {
		return fmt.Errorf("stop: exactly one of --run ID or --all is required")
	}

	statePath := filepath.Join(*stateDir, "state.json")
	state, err := fleetstate.Load(statePath)
	if err != nil {
		return err
	}
	loop := &control.Loop{
		Runner:    &runner.ExecRunner{DryRun: *dryRun},
		State:     state,
		StatePath: statePath,
	}
	ctx := context.Background()
	if *all {
		return loop.StopAll(ctx)
	}
	return loop.StopRun(ctx, *run)
}
