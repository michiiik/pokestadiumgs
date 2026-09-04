// Package runner defines the one seam between fleetctl's control logic and
// the outside world: docker, git, gh, and the repo's own python tooling
// (tools/container_merge.py, tools/pragma_targets.py). Every external
// command fleetctl issues goes through the Runner interface so control-loop
// tests can substitute a Fake instead of touching real containers, git
// history, or GitHub.
package runner

import (
	"context"
	"time"
)

// LaunchSpec is everything needed to start one container run via
// container/run.sh (docs/CONTAINER_AGENT.md sec 2).
type LaunchSpec struct {
	SourceFile    string // repo-relative disasm/src/<file>.c
	OutDir        string // absolute host out dir, bind-mounted at /out
	BudgetSeconds int    // --budget-seconds
	// OwnerSeconds is the per-owner wall-clock cap (--owner-seconds); 0
	// leaves container_agent.py's own default. budget/owner-seconds is how
	// many owners a run can reach at all, so this is the knob that decides
	// coverage per run, not just per-owner patience.
	OwnerSeconds     int
	Owners           []string // --owners a,b,c ; empty = every pragma in the file
	SeedFrom         []string // in-container paths, e.g. /out/seeds/<name>
	Resume           bool     // --resume
	GeneratorTimeout int      // --generator-timeout seconds; 0 = unset
	MaxInstructions  int      // --max-instructions; 0 = unset
	Agent            string   // AGENT env
	Model            string   // GENERATOR_MODEL env
	Effort           string   // GENERATOR_EFFORT env; "" = unset
	// SrcOverlay, when set, is forwarded as env SRC_OVERLAY=<dir> -- it
	// overlays the current sources into the container at start (container/
	// run.sh + entrypoint.sh), so a launch can pick up post-merge sources
	// without rebuilding the gs-decomp-agent image (docs/FLEET_CONTROLLER.md
	// sec 6, "stale-image awareness").
	SrcOverlay string

	// Mode is "" (the ordinary run) or "permuter-only" (the permuter-only
	// lane, docs/FLEET_CONTROLLER.md sec 13): passed as `--mode permuter-
	// only`, and switches this LaunchSpec to the TiePoolFile/PermuterSeconds
	// fields below instead of BudgetSeconds -- no --budget-seconds is
	// passed at all for this mode (container_agent.py's own default
	// applies, unused since the permuter-only driver stops on
	// PermuterSeconds/plateau, not a wall-clock budget).
	Mode string
	// TiePoolFile is the in-container path (e.g. "/out/tie-pool-input.json")
	// to a copy of this file's collected tie-pool entries, passed as
	// `--tie-pool-file` -- only set when Mode == "permuter-only".
	TiePoolFile string
	// PermuterSeconds is `--permuter-seconds` -- only set when Mode ==
	// "permuter-only".
	PermuterSeconds int
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

// PRChecksResult is the aggregate outcome of `gh pr checks <n>` (see
// GhPRChecks): every reported check's state rolled up into one of
// "SUCCESS" (every check succeeded), "FAILURE" (at least one check failed,
// errored, or was cancelled/timed out), or "PENDING" (still running, or no
// checks reported yet).
type PRChecksResult struct {
	State string
}

// PRStateResult is the outcome of `gh pr view <n> --json
// state,mergeable,mergeStateStatus` (see GhPRState): State is gh's own
// "OPEN"/"CLOSED"/"MERGED"; Mergeable is "MERGEABLE"/"CONFLICTING"/
// "UNKNOWN" (gh has not finished computing it yet).
type PRStateResult struct {
	State            string
	Mergeable        string
	MergeStateStatus string
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
// "targets" array: an owner ranked smallest-instructions-first, carrying
// both a static structural-shape guess and (once any exist) real
// probe-attempt history -- see control.difficultyTierFor, which combines
// them into a routing hint.
type TargetOwner struct {
	Function         string `json:"function"`
	Source           string `json:"source"`
	InstructionCount int    `json:"instructions"`
	// Family is tools/scan_asm_families.py's classify() shape label (e.g.
	// "direct_wrapper", "loop_or_state_machine", "unclassified") -- a
	// static guess at structural difficulty, available even for an owner
	// that has never been attempted. Empty only if pragma_targets.py's
	// output is from before this field existed or the owner's .s file was
	// unreadable when classified.
	Family string `json:"family"`
	// Hardness is pragma_targets.py's OwnerHardness.label: one of
	// fresh/drift/tie/stuck, built from REAL probe-attempt history
	// (tools/pragma_targets.py:load_owner_hardness) when any exists.
	// "fresh" is also the default for an owner with too few attempts to
	// judge -- in that case Family is the only real difficulty evidence.
	Hardness string `json:"hardness"`
	// BestSimilarity is the highest similarity_score any recorded attempt
	// for this owner has reached, or nil if it has never been attempted.
	BestSimilarity *float64 `json:"best_similarity"`
	// PriorAttempts is how many probe attempts this owner has on record.
	PriorAttempts int `json:"prior_attempts"`
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

	// GitFetch runs `git -C repoRoot fetch origin` -- the merge repo's only
	// mutating call against its remote-tracking refs. Used both before
	// branching a new run (so --base-ref, e.g. origin/master, is current)
	// and as the post-merge "fast-forward" (sec 2/7): the merge repo's own
	// local base branch is never checked out or pulled, so there is no
	// local branch left to fast-forward -- only its remote-tracking ref
	// needs refreshing.
	GitFetch(ctx context.Context, repoRoot string) error
	// GitCheckoutNewBranch runs `git -C repoRoot checkout -B branch from`
	// (force-create/reset, not `-b`): `from` is ordinarily a remote-
	// tracking ref like origin/master (--base-ref), so this always starts
	// the throwaway branch fresh from the fetched remote state, never from
	// wherever the branch happened to be left last time.
	GitCheckoutNewBranch(ctx context.Context, repoRoot, branch, from string) error
	// GitCheckoutDetach runs `git -C repoRoot checkout --detach ref` --
	// leaves the merge repo checked out at ref with no local branch
	// attached, so a run's merge step never requires (or fights over)
	// checking out the local base branch itself, which may already be
	// checked out elsewhere (e.g. the main checkout, if the merge repo is
	// a linked worktree).
	GitCheckoutDetach(ctx context.Context, repoRoot, ref string) error
	// GitStatusPorcelain runs `git -C repoRoot status --porcelain` -- a
	// read-only query (never gated by DryRun, same as RankFiles/Targets/
	// DockerImageID/GitRevParse) used to confirm the merge repo is clean
	// of conflicting changes before a run's merge step branches it.
	GitStatusPorcelain(ctx context.Context, repoRoot string) (string, error)
	// GitDiffNames runs `git -C repoRoot diff --name-only HEAD <ref>` --
	// the files whose content differs between the current checkout and
	// ref. Read-only. A `git checkout -B <branch> <ref>` must rewrite
	// exactly these, so a locally-modified file in this set is what makes
	// the checkout refuse; one outside it is harmless dirt.
	GitDiffNames(ctx context.Context, repoRoot, ref string) ([]string, error)
	// GitResetPath runs `git -C repoRoot reset -q -- path` -- unstages path
	// without touching the working tree.
	GitResetPath(ctx context.Context, repoRoot, path string) error
	// GitCheckoutPath runs `git -C repoRoot checkout -- path` -- discards
	// any working-tree modification to path, restoring it to the index's
	// version. Used together with GitResetPath to discard a generated
	// file's uncommitted state (e.g. COVERAGE.md, regenerated and staged by
	// .githooks/pre-commit.d/10-coverage.sh on every commit) before the
	// merge repo's dirty check, so a leftover regenerated-but-uncommitted
	// copy from a prior `git commit --only` never trips it.
	GitCheckoutPath(ctx context.Context, repoRoot, path string) error
	// GitPush runs `git -C repoRoot push -u origin branch`.
	GitPush(ctx context.Context, repoRoot, branch string) error
	// GitRevParse runs `git -C repoRoot rev-parse ref` and returns the
	// resolved sha -- used to verify a remote-tracking ref (e.g.
	// origin/master) has picked up a just-merged PR's merge commit.
	GitRevParse(ctx context.Context, repoRoot, ref string) (string, error)
	// GhPRCreate runs `gh pr create --base ... --title ... --body ...` and
	// returns the printed PR URL.
	GhPRCreate(ctx context.Context, spec PRSpec) (url string, err error)
	// GhPRChecks runs `gh pr checks <prNumber> --json name,state` and rolls
	// every reported check up into one PRChecksResult.
	GhPRChecks(ctx context.Context, repoRoot string, prNumber int) (PRChecksResult, error)
	// GhPRMerge runs `gh pr merge <prNumber> --merge`. It deliberately does
	// NOT pass --delete-branch: the merge repo is always detached HEAD, and
	// gh's own post-merge branch-delete step there fails with "could not
	// determine current branch" even though the merge itself already
	// landed on GitHub -- see GitDeleteRemoteBranch, which callers use
	// instead, best-effort, after a merge succeeds.
	GhPRMerge(ctx context.Context, repoRoot string, prNumber int) error
	// GhPRView runs `gh pr view <prNumber> --json mergeCommit` and returns
	// the merge commit's sha -- a read-only query (never gated by DryRun,
	// same as GhPRChecks) used to record a just-merged PR's landed commit
	// without ever checking out or rev-parsing a local base branch.
	GhPRView(ctx context.Context, repoRoot string, prNumber int) (mergeCommitSHA string, err error)
	// GhPRState runs `gh pr view <prNumber> --json
	// state,mergeable,mergeStateStatus` -- a read-only query (never gated
	// by DryRun, same as GhPRChecks/GhPRView) used both for idempotent
	// merge recovery (gh already reports MERGED even though a prior
	// GhPRMerge/GhPRClose call errored -- e.g. the detached-HEAD "could not
	// determine current branch" failure GhPRMerge's own doc describes) and
	// to detect a PR that has fallen CONFLICTING with its base (another PR
	// touching the same file landed first, or this PR's base has simply
	// moved on) so pollPRs can replay the run instead of retrying a merge
	// that will never succeed.
	GhPRState(ctx context.Context, repoRoot string, prNumber int) (PRStateResult, error)
	// GhPRClose runs `gh pr close <prNumber> --comment <comment>` -- used to
	// close out a PR pollPRs is replaying after finding it CONFLICTING
	// (docs/FLEET_CONTROLLER.md sec 2/7, "PR conflict replay").
	GhPRClose(ctx context.Context, repoRoot string, prNumber int, comment string) error
	// GitDeleteRemoteBranch runs `git -C repoRoot push origin --delete
	// branch` -- best-effort cleanup of a run's throwaway branch, called
	// after a self-merge (GhPRMerge no longer passes --delete-branch, see
	// its own doc) or a PR conflict replay's close. Callers only log its
	// error; a leftover remote branch is cosmetic, never fatal.
	GitDeleteRemoteBranch(ctx context.Context, repoRoot, branch string) error
	// GhIssueComment runs `gh issue comment <issueNumber> --body ...` --
	// the --alert-issue notifier's one effect.
	GhIssueComment(ctx context.Context, repoRoot string, issueNumber int, body string) error

	// RankFiles runs `python3 tools/pragma_targets.py rank-files --json ...`.
	RankFiles(ctx context.Context, repoRoot string, maxInstructions int, excludeRecentHours float64, limit int) ([]FileRank, error)
	// Targets runs `python3 tools/pragma_targets.py targets --source ...`
	// and returns every matched owner (it pages past --limit itself).
	Targets(ctx context.Context, repoRoot string, source string) ([]TargetOwner, error)

	// DockerImageID runs `docker image inspect <image> --format
	// '{{.Id}}|{{.Created}}'` -- a read-only query, never gated by DryRun
	// (see docs/FLEET_CONTROLLER.md sec 6, "stale-image awareness").
	DockerImageID(ctx context.Context, image string) (id string, created time.Time, err error)

	// OsascriptNotify runs `osascript -e 'display notification ...'` --
	// the --alert-macos notifier's one effect.
	OsascriptNotify(ctx context.Context, title, body string) error
}
