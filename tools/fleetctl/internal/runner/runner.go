// Package runner defines the one seam between fleetctl's control logic and
// the outside world: docker, git, gh, and the repo's own python tooling
// (tools/container_merge.py, tools/pragma_targets.py). Every external
// command fleetctl issues goes through the Runner interface so control-loop
// tests can substitute a Fake instead of touching real containers, git
// history, or GitHub.
package runner

import "context"

// LaunchSpec is everything needed to start one container run via
// container/run.sh (docs/CONTAINER_AGENT.md sec 2).
type LaunchSpec struct {
	SourceFile       string   // repo-relative disasm/src/<file>.c
	OutDir           string   // absolute host out dir, bind-mounted at /out
	BudgetSeconds    int      // --budget-seconds
	Owners           []string // --owners a,b,c ; empty = every pragma in the file
	SeedFrom         []string // in-container paths, e.g. /out/seeds/<name>
	Resume           bool     // --resume
	GeneratorTimeout int      // --generator-timeout seconds; 0 = unset
	MaxInstructions  int      // --max-instructions; 0 = unset
	Agent            string   // AGENT env
	Model            string   // GENERATOR_MODEL env
	Effort           string   // GENERATOR_EFFORT env; "" = unset
}

// InspectResult is the outcome of a `docker inspect` poll.
type InspectResult struct {
	Found    bool // false if the container id is no longer known to docker
	Running  bool
	ExitCode int
}

// MergeSpec drives one `tools/container_merge.py merge` invocation.
type MergeSpec struct {
	OutDir       string
	RepoRoot     string // --repo: the checkout to re-gate/commit against
	FreshHistory bool   // --fresh-history
	Commit       bool   // --commit
	NoCCCheck    bool   // --no-cc-check
}

// ProcessResult is the raw outcome of any subprocess this package runs, kept
// uniform so callers can log/inspect exit codes and output.
type ProcessResult struct {
	ExitCode int
	Stdout   string
	Stderr   string
}

// PRSpec drives one `gh pr create` invocation.
type PRSpec struct {
	RepoRoot string
	Base     string // --base, the integration branch
	Title    string
	Body     string
}

// FileRank is one row of `tools/pragma_targets.py rank-files --json`.
type FileRank struct {
	File            string `json:"file"`
	Remaining       int    `json:"remaining"`
	ActionableFresh int    `json:"actionable_fresh"`
	Fresh           int    `json:"fresh"`
	Drift           int    `json:"drift"`
	Score           int    `json:"score"`
}

// TargetOwner is one row of `tools/pragma_targets.py targets`'s
// "targets" array: an owner ranked smallest-instructions-first.
type TargetOwner struct {
	Function         string `json:"function"`
	Source           string `json:"source"`
	InstructionCount int    `json:"instructions"`
}

// Runner is the interface fleetctl's control loop programs against.
// ExecRunner (exec.go) is the real implementation; Fake (fake.go) is a
// scriptable stand-in for tests.
type Runner interface {
	// LaunchContainer runs `bash container/run.sh <file> <out> ...` with
	// RUN_DETACHED=1 and returns the printed container id.
	LaunchContainer(ctx context.Context, spec LaunchSpec) (containerID string, err error)
	// InspectContainer polls `docker inspect` for one container id.
	InspectContainer(ctx context.Context, containerID string) (InspectResult, error)
	// StopContainer runs `docker stop <containerID>` -- never a filter.
	StopContainer(ctx context.Context, containerID string) error

	// Merge runs `python3 tools/container_merge.py merge ...`.
	Merge(ctx context.Context, spec MergeSpec) (ProcessResult, error)
	// ImportStats runs `python3 tools/container_merge.py import-stats <out> --repo <repo>`.
	ImportStats(ctx context.Context, outDir, repoRoot string) (ProcessResult, error)

	// GitCheckoutNewBranch runs `git -C repoRoot checkout -b branch from`.
	GitCheckoutNewBranch(ctx context.Context, repoRoot, branch, from string) error
	// GitCheckout runs `git -C repoRoot checkout ref`.
	GitCheckout(ctx context.Context, repoRoot, ref string) error
	// GitPush runs `git -C repoRoot push -u origin branch`.
	GitPush(ctx context.Context, repoRoot, branch string) error
	// GhPRCreate runs `gh pr create --base ... --title ... --body ...` and
	// returns the printed PR URL.
	GhPRCreate(ctx context.Context, spec PRSpec) (url string, err error)

	// RankFiles runs `python3 tools/pragma_targets.py rank-files --json ...`.
	RankFiles(ctx context.Context, repoRoot string, maxInstructions int, excludeRecentHours float64, limit int) ([]FileRank, error)
	// Targets runs `python3 tools/pragma_targets.py targets --source ...`
	// and returns every matched owner (it pages past --limit itself).
	Targets(ctx context.Context, repoRoot string, source string) ([]TargetOwner, error)
}
