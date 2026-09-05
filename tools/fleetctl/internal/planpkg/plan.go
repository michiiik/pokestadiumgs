// Package planpkg builds and persists a fleetctl plan: a ranked file list,
// each file's owners split into fixed-size partitions, and a round-robin
// agent assignment across the whole queue.
package planpkg

import (
	"context"
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"
	"time"

	"fleetctl/internal/agentspec"
	"fleetctl/internal/difficulty"
	"fleetctl/internal/fleetstate"
	"fleetctl/internal/runner"
)

// DefaultOwnersPerRun matches the task's default partition size.
const DefaultOwnersPerRun = 12

// Options configures Build.
type Options struct {
	Repo string

	// Exactly one of Files (rank files and take the top N) or FileList
	// (use exactly these files, in the given order) must be set.
	Files    int
	FileList []string

	Slots            int
	OwnersPerRun     int // 0 -> DefaultOwnersPerRun
	Agents           []agentspec.Spec
	Cooldowns        map[string]time.Duration
	AgentConcurrency map[string]int
	BudgetSeconds    int

	// Windows is the known quota-window length per agent (e.g. kimi=5h,
	// --window on `plan`/`run`) -- read by control.BuildMetrics to
	// normalize accepts-per-window (docs/FLEET_CONTROLLER.md sec 11) and by
	// control.Loop's quota-window-aware scheduling (sec 12). An agent with
	// no entry here falls back to its own Cooldowns entry, then a 24h
	// default -- see control.quotaWindowFor.
	Windows map[string]time.Duration
	// WindowBudget is the optional expected-batches-per-window per agent
	// (--window-budget) -- informational only, surfaced in `status`'s
	// METRICS table/`status --json` (sec 11); it does not itself gate
	// scheduling.
	WindowBudget map[string]int

	// Forwarded to `rank-files` when Files is used. ExcludeRecentHours < 0
	// omits --exclude-recent entirely (no filtering at all); >= 0 (0
	// included) passes it through explicitly -- see ExecRunner.RankFiles.
	MaxInstructions    int
	ExcludeRecentHours float64
}

// Plan is the JSON document `fleetctl plan` writes and `fleetctl run` reads.
// Besides the queue it built, it also records the Options it was built
// with (Files/FileList/Agents/MaxInstructions/ExcludeRecentHours/
// BudgetSeconds), so a Plan loaded back out of state.json's persisted copy
// (fleetstate.State.PlanJSON) can be fed straight into ToOptions and Build
// again for control.Loop.Replan (docs/FLEET_CONTROLLER.md sec 2).
type Plan struct {
	GeneratedAt  time.Time `json:"generated_at"`
	Repo         string    `json:"repo"`
	Slots        int       `json:"slots"`
	OwnersPerRun int       `json:"owners_per_run"`
	// Files/FileList mirror Options: Files > 0 means the plan ranked its
	// own top-N files (a Replan reranks fresh); FileList means an explicit
	// --file list was used (a Replan reuses that exact list).
	Files              int               `json:"files,omitempty"`
	FileList           []string          `json:"file_list,omitempty"`
	Agents             []agentspec.Spec  `json:"agents,omitempty"`
	MaxInstructions    int               `json:"max_instructions,omitempty"`
	ExcludeRecentHours float64           `json:"exclude_recent_hours,omitempty"`
	BudgetSeconds      int               `json:"budget_seconds,omitempty"`
	Cooldowns          map[string]string `json:"cooldowns,omitempty"`
	AgentConcurrency   map[string]int    `json:"agent_concurrency,omitempty"`
	// Windows/WindowBudget mirror Options.Windows/WindowBudget, durations
	// rendered as strings the same way Cooldowns is (sec 11/12).
	Windows      map[string]string    `json:"windows,omitempty"`
	WindowBudget map[string]int       `json:"window_budget,omitempty"`
	Queue        []fleetstate.RunSpec `json:"queue"`
}

// ToOptions reconstructs the Options a Plan was Build-ed with, so it can be
// fed into Build again (control.Loop.Replan's use case).
func (p *Plan) ToOptions() (Options, error) {
	cooldowns := make(map[string]time.Duration, len(p.Cooldowns))
	for agent, s := range p.Cooldowns {
		d, err := time.ParseDuration(s)
		if err != nil {
			return Options{}, fmt.Errorf("planpkg: cooldown %s=%q: %w", agent, s, err)
		}
		cooldowns[agent] = d
	}
	windows := make(map[string]time.Duration, len(p.Windows))
	for agent, s := range p.Windows {
		d, err := time.ParseDuration(s)
		if err != nil {
			return Options{}, fmt.Errorf("planpkg: window %s=%q: %w", agent, s, err)
		}
		windows[agent] = d
	}
	return Options{
		Repo:               p.Repo,
		Files:              p.Files,
		FileList:           append([]string(nil), p.FileList...),
		Slots:              p.Slots,
		OwnersPerRun:       p.OwnersPerRun,
		Agents:             append([]agentspec.Spec(nil), p.Agents...),
		Cooldowns:          cooldowns,
		AgentConcurrency:   p.AgentConcurrency,
		BudgetSeconds:      p.BudgetSeconds,
		MaxInstructions:    p.MaxInstructions,
		ExcludeRecentHours: p.ExcludeRecentHours,
		Windows:            windows,
		WindowBudget:       p.WindowBudget,
	}, nil
}

// FileSlug turns "disasm/src/fragments/79/fragment79_3BF4C0.c" into
// "fragment79_3BF4C0" -- unique enough for run ids because splat's per-file
// basenames already are (fragment numbers, function-address names). Also
// used by control.tiePoolStorePath to name a file's collected tie-pool
// store (docs/FLEET_CONTROLLER.md sec 13).
func FileSlug(file string) string {
	base := filepath.Base(file)
	return strings.TrimSuffix(base, filepath.Ext(base))
}

// schedulableOwners drops any owner runner.TargetOwner.Schedulable reports
// as false -- a jump-table owner whose file still lacks its rodata
// subsegment, or an owner whose ground truth depends on an interleaved
// shared-$at lui run (see the Schedulable field's own doc). Both are
// provably unsolvable by today's tooling regardless of candidate quality,
// so excluding them here (never scheduled into a run at all) is strictly
// better than letting a container burn its budget discovering the same
// rejection a fresh box would have hit anyway. A nil Schedulable (an owner
// from a payload that predates this field, or any other decode surprise)
// is kept -- failing open, since silently dropping real work is worse than
// the waste this filter exists to prevent. This never changes an
// already-running container's behavior; it only affects what a fresh
// planpkg.Build queues.
func schedulableOwners(owners []runner.TargetOwner) []runner.TargetOwner {
	kept := owners[:0]
	for _, o := range owners {
		if o.Schedulable == nil || *o.Schedulable {
			kept = append(kept, o)
		}
	}
	return kept
}

// Build ranks/selects files, partitions each file's owners (already
// smallest-instructions-first from `targets`) into chunks of at most
// OwnersPerRun, and assigns agent specs round-robin across the resulting
// queue in file order.
func Build(ctx context.Context, r runner.Runner, opts Options) (*Plan, error) {
	if len(opts.Agents) == 0 {
		return nil, fmt.Errorf("plan: at least one --agent SPEC is required")
	}
	if opts.Files <= 0 && len(opts.FileList) == 0 {
		return nil, fmt.Errorf("plan: --files N or --file F (repeatable) is required")
	}
	if opts.Files > 0 && len(opts.FileList) > 0 {
		return nil, fmt.Errorf("plan: --files and --file are mutually exclusive")
	}

	ownersPerRun := opts.OwnersPerRun
	if ownersPerRun <= 0 {
		ownersPerRun = DefaultOwnersPerRun
	}

	files := opts.FileList
	if len(files) == 0 {
		ranks, err := r.RankFiles(ctx, opts.Repo, opts.MaxInstructions, opts.ExcludeRecentHours, opts.Files)
		if err != nil {
			return nil, fmt.Errorf("plan: rank-files: %w", err)
		}
		for _, row := range ranks {
			if len(files) >= opts.Files {
				break
			}
			files = append(files, row.File)
		}
	}

	var queue []fleetstate.RunSpec
	agentIdx := 0
	for _, file := range files {
		owners, err := r.Targets(ctx, opts.Repo, file)
		if err != nil {
			return nil, fmt.Errorf("plan: targets --source %s: %w", file, err)
		}
		owners = schedulableOwners(owners)
		if len(owners) == 0 {
			continue
		}
		// Easiest-first within this file, on top of (not instead of)
		// targets's own smallest-instructions-first ranking -- a stable
		// sort keeps that relative order inside each tier. This never
		// drops an owner, just resequences it: a file's medium/hard
		// owners still get queued eventually (later partitions), so a
		// tier that happens to be scarce or empty in a given file (e.g.
		// classify()'s Easy wrapper shapes are largely already claimed
		// across this codebase's remaining backlog) never starves the
		// fleet the way an exclude-above-a-ceiling filter would -- see
		// internal/difficulty's package doc for why that was tried first
		// and reverted.
		sort.SliceStable(owners, func(i, j int) bool {
			return difficulty.Rank(difficulty.TierFor(owners[i])) < difficulty.Rank(difficulty.TierFor(owners[j]))
		})
		names := make([]string, len(owners))
		for i, o := range owners {
			names[i] = o.Function
		}
		slug := FileSlug(file)
		part := 0
		for start := 0; start < len(names); start += ownersPerRun {
			end := min(start+ownersPerRun, len(names))
			agent := opts.Agents[agentIdx%len(opts.Agents)]
			agentIdx++
			queue = append(queue, fleetstate.RunSpec{
				ID:            fmt.Sprintf("%s-p%d", slug, part),
				File:          file,
				Owners:        append([]string(nil), names[start:end]...),
				Agent:         agent.Agent,
				Model:         agent.Model,
				Effort:        agent.Effort,
				BudgetSeconds: opts.BudgetSeconds,
			})
			part++
		}
	}

	cooldowns := make(map[string]string, len(opts.Cooldowns))
	for agent, d := range opts.Cooldowns {
		cooldowns[agent] = d.String()
	}
	windows := make(map[string]string, len(opts.Windows))
	for agent, d := range opts.Windows {
		windows[agent] = d.String()
	}

	return &Plan{
		GeneratedAt:        time.Now().UTC(),
		Repo:               opts.Repo,
		Slots:              opts.Slots,
		OwnersPerRun:       ownersPerRun,
		Files:              opts.Files,
		FileList:           opts.FileList,
		Agents:             opts.Agents,
		MaxInstructions:    opts.MaxInstructions,
		ExcludeRecentHours: opts.ExcludeRecentHours,
		BudgetSeconds:      opts.BudgetSeconds,
		Cooldowns:          cooldowns,
		AgentConcurrency:   opts.AgentConcurrency,
		Windows:            windows,
		WindowBudget:       opts.WindowBudget,
		Queue:              queue,
	}, nil
}

// Save writes the plan as indented JSON.
func (p *Plan) Save(path string) error {
	data, err := json.MarshalIndent(p, "", "  ")
	if err != nil {
		return fmt.Errorf("plan: marshal: %w", err)
	}
	if dir := filepath.Dir(path); dir != "." {
		if err := os.MkdirAll(dir, 0o755); err != nil {
			return fmt.Errorf("plan: mkdir %s: %w", dir, err)
		}
	}
	if err := os.WriteFile(path, data, 0o644); err != nil {
		return fmt.Errorf("plan: write %s: %w", path, err)
	}
	return nil
}

// Load reads a plan file written by Save.
func Load(path string) (*Plan, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return nil, fmt.Errorf("plan: read %s: %w", path, err)
	}
	var p Plan
	if err := json.Unmarshal(data, &p); err != nil {
		return nil, fmt.Errorf("plan: parse %s: %w", path, err)
	}
	return &p, nil
}

// ParseCooldowns parses repeated "agent=duration" flag values.
func ParseCooldowns(values []string) (map[string]time.Duration, error) {
	out := map[string]time.Duration{}
	for _, v := range values {
		agent, d, err := agentspec.ParseKeyDuration(v)
		if err != nil {
			return nil, err
		}
		out[agent] = d
	}
	return out, nil
}

// ParseAgentConcurrency parses repeated "agent=N" flag values.
func ParseAgentConcurrency(values []string) (map[string]int, error) {
	out := map[string]int{}
	for _, v := range values {
		agent, n, err := agentspec.ParseKeyInt(v)
		if err != nil {
			return nil, err
		}
		out[agent] = n
	}
	return out, nil
}

// ParseWindows parses repeated "agent=duration" --window flag values (e.g.
// "kimi=5h") -- the known quota-window length per agent, docs sec 11/12.
func ParseWindows(values []string) (map[string]time.Duration, error) {
	out := map[string]time.Duration{}
	for _, v := range values {
		agent, d, err := agentspec.ParseKeyDuration(v)
		if err != nil {
			return nil, err
		}
		out[agent] = d
	}
	return out, nil
}

// ParseWindowBudget parses repeated "agent=N" --window-budget flag values --
// the optional expected-batches-per-window per agent, docs sec 11.
func ParseWindowBudget(values []string) (map[string]int, error) {
	out := map[string]int{}
	for _, v := range values {
		agent, n, err := agentspec.ParseKeyInt(v)
		if err != nil {
			return nil, err
		}
		out[agent] = n
	}
	return out, nil
}
