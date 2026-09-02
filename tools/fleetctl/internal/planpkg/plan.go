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
	"strings"
	"time"

	"fleetctl/internal/agentspec"
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

	// Forwarded to `rank-files` when Files is used.
	MaxInstructions    int
	ExcludeRecentHours float64
}

// Plan is the JSON document `fleetctl plan` writes and `fleetctl run` reads.
type Plan struct {
	GeneratedAt      time.Time            `json:"generated_at"`
	Repo             string               `json:"repo"`
	Slots            int                  `json:"slots"`
	OwnersPerRun     int                  `json:"owners_per_run"`
	Cooldowns        map[string]string    `json:"cooldowns,omitempty"`
	AgentConcurrency map[string]int       `json:"agent_concurrency,omitempty"`
	Queue            []fleetstate.RunSpec `json:"queue"`
}

// fileSlug turns "disasm/src/fragments/79/fragment79_3BF4C0.c" into
// "fragment79_3BF4C0" -- unique enough for run ids because splat's per-file
// basenames already are (fragment numbers, function-address names).
func fileSlug(file string) string {
	base := filepath.Base(file)
	return strings.TrimSuffix(base, filepath.Ext(base))
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
		if len(owners) == 0 {
			continue
		}
		names := make([]string, len(owners))
		for i, o := range owners {
			names[i] = o.Function
		}
		slug := fileSlug(file)
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

	return &Plan{
		GeneratedAt:      time.Now().UTC(),
		Repo:             opts.Repo,
		Slots:            opts.Slots,
		OwnersPerRun:     ownersPerRun,
		Cooldowns:        cooldowns,
		AgentConcurrency: opts.AgentConcurrency,
		Queue:            queue,
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
