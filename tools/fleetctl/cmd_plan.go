package main

import (
	"context"
	"flag"
	"fmt"
	"os"

	"fleetctl/internal/agentspec"
	"fleetctl/internal/planpkg"
	"fleetctl/internal/runner"
)

func runPlanCmd(args []string) error {
	fs := flag.NewFlagSet("plan", flag.ContinueOnError)
	repo := fs.String("repo", "", "repo checkout to rank files / list owners against (required)")
	files := fs.Int("files", 0, "rank files with tools/pragma_targets.py rank-files and take the top N")
	var fileList stringSlice
	fs.Var(&fileList, "file", "an explicit disasm/src/<file>.c to include (repeatable; mutually exclusive with --files)")
	slots := fs.Int("slots", 0, "suggested fleet concurrency, recorded in the plan for `run`'s --max-concurrent default")
	ownersPerRun := fs.Int("owners-per-run", planpkg.DefaultOwnersPerRun, "max owners per run partition")
	var agentSpecs stringSlice
	fs.Var(&agentSpecs, "agent", "agent:model[:effort] spec (repeatable; assigned round-robin across the queue)")
	var cooldowns stringSlice
	fs.Var(&cooldowns, "cooldown", "agent=duration, e.g. kimi=5h (repeatable)")
	var agentConcurrency stringSlice
	fs.Var(&agentConcurrency, "agent-concurrency", "agent=N per-agent concurrency cap (repeatable)")
	var windows stringSlice
	fs.Var(&windows, "window", "agent=duration known quota-window length, e.g. kimi=5h (repeatable); baked into the plan and read by `run`'s per-agent throughput metrics (sec 11) and quota-window-aware scheduling (sec 12); an agent with no entry here falls back to its --cooldown entry, then a 24h default")
	var windowBudget stringSlice
	fs.Var(&windowBudget, "window-budget", "agent=N expected batches per quota window (repeatable, optional; informational only, surfaced in `status`'s METRICS table, sec 11)")
	budgetSeconds := fs.Int("budget-seconds", 3600, "--budget-seconds passed to every launched run")
	maxInstructions := fs.Int("max-instructions", 0, "forwarded to rank-files --max-instructions (0 = tool default)")
	excludeRecent := fs.Float64("exclude-recent", -1, "forwarded to rank-files --exclude-recent HOURS (negative = omit the flag entirely; 0 still applies rank-files' own dirty-working-tree exclusion, just with no commit-recency window)")
	out := fs.String("out", "plan.json", "where to write the plan JSON")
	pythonBin := fs.String("python", "", "override the python3 binary (default: python3 on PATH)")
	if err := fs.Parse(args); err != nil {
		return err
	}

	if *repo == "" {
		return fmt.Errorf("plan: --repo is required")
	}
	agents := make([]agentspec.Spec, 0, len(agentSpecs))
	for _, s := range agentSpecs {
		spec, err := agentspec.Parse(s)
		if err != nil {
			return err
		}
		agents = append(agents, spec)
	}
	cooldownMap, err := planpkg.ParseCooldowns(cooldowns)
	if err != nil {
		return err
	}
	concurrencyMap, err := planpkg.ParseAgentConcurrency(agentConcurrency)
	if err != nil {
		return err
	}
	windowMap, err := planpkg.ParseWindows(windows)
	if err != nil {
		return err
	}
	windowBudgetMap, err := planpkg.ParseWindowBudget(windowBudget)
	if err != nil {
		return err
	}

	r := &runner.ExecRunner{RepoRoot: *repo, PythonBin: *pythonBin}
	p, err := planpkg.Build(context.Background(), r, planpkg.Options{
		Repo:               *repo,
		Files:              *files,
		FileList:           fileList,
		Slots:              *slots,
		OwnersPerRun:       *ownersPerRun,
		Agents:             agents,
		Cooldowns:          cooldownMap,
		AgentConcurrency:   concurrencyMap,
		BudgetSeconds:      *budgetSeconds,
		MaxInstructions:    *maxInstructions,
		ExcludeRecentHours: *excludeRecent,
		Windows:            windowMap,
		WindowBudget:       windowBudgetMap,
	})
	if err != nil {
		return err
	}
	if err := p.Save(*out); err != nil {
		return err
	}
	fmt.Fprintf(os.Stdout, "fleetctl: wrote %s: %d run(s) across %d file(s)\n", *out, len(p.Queue), countFiles(p))
	return nil
}

func countFiles(p *planpkg.Plan) int {
	seen := map[string]bool{}
	for _, spec := range p.Queue {
		seen[spec.File] = true
	}
	return len(seen)
}
