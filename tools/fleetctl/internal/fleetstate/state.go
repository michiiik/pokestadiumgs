// Package fleetstate is fleetctl's persisted control-loop state: the run
// queue, every run record ever seen (queued/running/merging/done/requeued),
// and per-agent cooldowns. State is rewritten atomically after every
// mutation so `fleetctl run` can be killed and restarted at any point and
// pick up exactly where it left off (idempotent restart).
package fleetstate

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"time"
)

// Status is one node of the run state machine documented in
// docs/FLEET_CONTROLLER.md: queued -> running -> merging ->
// done|requeued|pr_open -> merged|gate_failed.
type Status string

const (
	StatusQueued   Status = "queued"
	StatusRunning  Status = "running"
	StatusMerging  Status = "merging"
	StatusDone     Status = "done"
	StatusRequeued Status = "requeued"
	StatusFailed   Status = "failed"
	// StatusPROpen is a run whose merge step opened a PR and --auto-merge
	// is on: the control loop polls its checks (control.Loop.pollPRs) until
	// they land on StatusMerged or StatusGateFailed.
	StatusPROpen Status = "pr_open"
	// StatusMerged is a StatusPROpen run whose PR's checks all went SUCCESS
	// and `gh pr merge --merge --delete-branch` succeeded.
	StatusMerged Status = "merged"
	// StatusGateFailed is a StatusPROpen run whose PR's checks reported a
	// FAILURE -- left open for manual triage, never auto-retried.
	StatusGateFailed Status = "gate_failed"
	// StatusMergeBlockedDirty is a run whose merge step found the merge
	// repo already carrying uncommitted changes to a path the merge itself
	// would touch (disasm/src/, COVERAGE.md, docs/regions/ -- see
	// docs/FLEET_CONTROLLER.md sec 2, "the merge repo must be clean") and
	// refused to branch or commit anything -- left exactly as-is, like
	// StatusGateFailed, for an operator to resolve by hand.
	StatusMergeBlockedDirty Status = "merge_blocked_dirty"
)

// RunSpec is one queued unit of work: one file, one partition of that
// file's owners, one agent spec.
type RunSpec struct {
	ID            string   `json:"id"`
	File          string   `json:"file"`
	Owners        []string `json:"owners"`
	Agent         string   `json:"agent"`
	Model         string   `json:"model"`
	Effort        string   `json:"effort,omitempty"`
	BudgetSeconds int      `json:"budget_seconds"`
	// Attempt counts resumes of this exact spec (generator_exhausted, or a
	// container that vanished without a summary) -- Attempt > 0 launches
	// with --resume against the same OutDir rather than a fresh one.
	Attempt int `json:"attempt"`
	// SeedDirs are prior runs' host out dirs for this same file, copied
	// into this run's own out dir under seeds/ and passed via --seed-from
	// (see docs/CONTAINER_AGENT.md sec 2.1). Only set on a *fresh* requeue
	// (unmatched owners after a merge), never alongside Attempt>0 --resume,
	// matching container_agent.py's own rule that --seed-from is ignored
	// together with --resume.
	SeedDirs []string `json:"seed_dirs,omitempty"`
}

// RunRecord is what fleetctl knows about one RunSpec's lifetime.
type RunRecord struct {
	Spec          RunSpec   `json:"spec"`
	Status        Status    `json:"status"`
	ContainerID   string    `json:"container_id,omitempty"`
	OutDir        string    `json:"out_dir"`
	StartedAt     time.Time `json:"started_at,omitempty"`
	EndedAt       time.Time `json:"ended_at,omitempty"`
	StoppedReason string    `json:"stopped_reason,omitempty"`
	MatchedOwners []string  `json:"matched_owners,omitempty"`
	// NeedsManualCommit holds, per owner, the tail of `git commit --only`'s
	// failure output for an owner whose host re-gate accepted the candidate
	// but whose commit then failed (merge-report.json's
	// {"status":"accepted","committed":false,"commit_error":...} form --
	// see tools/container_merge.py's write_merge_report). Such an owner is
	// neither counted in MatchedOwners nor requeued: the candidate is
	// already installed in the merge repo's working tree, so requeueing
	// would re-probe a duplicate. An operator must commit it by hand.
	NeedsManualCommit map[string]string `json:"needs_manual_commit,omitempty"`
	Branch            string            `json:"branch,omitempty"`
	PRURL             string            `json:"pr_url,omitempty"`
	// PRNumber is parsed from PRURL (the trailing /pull/<n>) so
	// control.Loop.pollPRs can call `gh pr checks`/`gh pr merge` without
	// re-parsing the URL every pass. Zero until a PR is opened.
	PRNumber int `json:"pr_number,omitempty"`
	// MergedAt is when `gh pr merge` succeeded for this run's PR (Status ==
	// StatusMerged).
	MergedAt time.Time `json:"merged_at,omitempty"`
	// MergeCommitSHA is this run's PR's merge commit sha, from `gh pr view
	// --json mergeCommit` once the post-merge fetch of --base-ref (sec 2,
	// "self-merge on green") has run -- the commit this run's matched
	// owners landed as. The merge repo's local base branch is never
	// checked out to learn this.
	MergeCommitSHA string `json:"merge_commit_sha,omitempty"`
	// ImageID is the gs-decomp-agent image id (docker image inspect
	// --format {{.Id}}) this run's container was launched from; empty when
	// launched with --src-overlay (sec 6, "stale-image awareness" --
	// SrcOverlay makes the baked-in image irrelevant, so it is not even
	// queried).
	ImageID string `json:"image_id,omitempty"`
	// BestSimilarity/BestSimilarityAt track this run's own progress, read
	// from <out_dir>/state.json on every poll while Status == StatusRunning
	// -- BestSimilarityAt is the last time BestSimilarity improved, and a
	// gap since then of --stall-after or more raises a no_progress_stall
	// alert (sec 4).
	BestSimilarity   float64   `json:"best_similarity,omitempty"`
	BestSimilarityAt time.Time `json:"best_similarity_at,omitempty"`
	Note             string    `json:"note,omitempty"`
	// WaitReason explains why a queued/requeued run is still waiting as of
	// the last control-loop pass: "cooldown" (its agent is cooling down) or
	// "concurrency" (global --max-concurrent or the agent's own
	// --agent-concurrency cap is full). Empty once launched, and empty
	// until the first pass that considered and deferred this run.
	WaitReason string `json:"wait_reason,omitempty"`
}

// State is the full persisted control-loop state.
type State struct {
	PlanFile          string                `json:"plan_file"`
	Repo              string                `json:"repo"`
	MergeRepo         string                `json:"merge_repo"`
	IntegrationBranch string                `json:"integration_branch"`
	Queue             []string              `json:"queue"`       // RunSpec IDs, in launch order
	Runs              map[string]*RunRecord `json:"runs"`        // by RunSpec ID, every id ever seen
	Cooldowns         map[string]time.Time  `json:"cooldowns"`   // agent -> until
	RequeueSeq        map[string]int        `json:"requeue_seq"` // base spec id -> next requeue suffix

	// PlanJSON is the most recently loaded/rebuilt plan (planpkg.Plan),
	// persisted verbatim so a restarted `run` needs --plan only for the
	// very first start (docs/FLEET_CONTROLLER.md sec 3) and so `Replan`
	// knows what ranking options (--files, --agent, ...) to rebuild the
	// queue with (sec 2). Stored as a raw blob, not planpkg.Plan itself, to
	// avoid an import cycle (planpkg already imports fleetstate for
	// RunSpec).
	PlanJSON json.RawMessage `json:"plan,omitempty"`

	// MergeBlocked is set when a post-merge fast-forward of the base branch
	// failed (sec 2, "self-merge on green"): no further `gh pr merge` runs
	// until a later poll pass's retry of the fast-forward succeeds.
	MergeBlocked       bool   `json:"merge_blocked,omitempty"`
	MergeBlockedReason string `json:"merge_blocked_reason,omitempty"`
	// LastMergeAt is when fleetctl's own self-merge last landed a commit on
	// the base branch -- compared against a launch's image build time for
	// stale-image awareness (sec 6).
	LastMergeAt time.Time `json:"last_merge_at,omitempty"`

	// AlertSent rate-limits Loop.alert to at most one notification per
	// "event[:key]" per hour (sec 4).
	AlertSent map[string]time.Time `json:"alert_sent,omitempty"`
	// LastDailySummary is when the --alert-issue daily summary last posted,
	// so it fires at most once per UTC calendar day (sec 4).
	LastDailySummary time.Time `json:"last_daily_summary,omitempty"`
}

// New returns an empty State ready to have a plan's queue loaded into it.
func New() *State {
	return &State{
		Runs:       map[string]*RunRecord{},
		Cooldowns:  map[string]time.Time{},
		RequeueSeq: map[string]int{},
		AlertSent:  map[string]time.Time{},
	}
}

// Load reads a state file. A missing file is not an error -- it returns a
// fresh empty State, matching "run resumes from it (idempotent restart)"
// for a first run with no state file yet.
func Load(path string) (*State, error) {
	data, err := os.ReadFile(path)
	if os.IsNotExist(err) {
		return New(), nil
	}
	if err != nil {
		return nil, fmt.Errorf("fleetstate: read %s: %w", path, err)
	}
	var s State
	if err := json.Unmarshal(data, &s); err != nil {
		return nil, fmt.Errorf("fleetstate: parse %s: %w", path, err)
	}
	if s.Runs == nil {
		s.Runs = map[string]*RunRecord{}
	}
	if s.Cooldowns == nil {
		s.Cooldowns = map[string]time.Time{}
	}
	if s.RequeueSeq == nil {
		s.RequeueSeq = map[string]int{}
	}
	if s.AlertSent == nil {
		s.AlertSent = map[string]time.Time{}
	}
	return &s, nil
}

// SaveAtomic writes the state file via a temp-file-plus-rename so a reader
// (or a crash) never observes a partial write: encode to a sibling temp
// file in the same directory (so the rename is same-filesystem), fsync it,
// then atomically rename it over the real path.
func (s *State) SaveAtomic(path string) error {
	dir := filepath.Dir(path)
	if err := os.MkdirAll(dir, 0o755); err != nil {
		return fmt.Errorf("fleetstate: mkdir %s: %w", dir, err)
	}
	data, err := json.MarshalIndent(s, "", "  ")
	if err != nil {
		return fmt.Errorf("fleetstate: marshal: %w", err)
	}
	tmp, err := os.CreateTemp(dir, ".state-*.json.tmp")
	if err != nil {
		return fmt.Errorf("fleetstate: create temp file: %w", err)
	}
	tmpPath := tmp.Name()
	if _, err := tmp.Write(data); err != nil {
		tmp.Close()
		os.Remove(tmpPath)
		return fmt.Errorf("fleetstate: write temp file: %w", err)
	}
	if err := tmp.Sync(); err != nil {
		tmp.Close()
		os.Remove(tmpPath)
		return fmt.Errorf("fleetstate: sync temp file: %w", err)
	}
	if err := tmp.Close(); err != nil {
		os.Remove(tmpPath)
		return fmt.Errorf("fleetstate: close temp file: %w", err)
	}
	if err := os.Rename(tmpPath, path); err != nil {
		os.Remove(tmpPath)
		return fmt.Errorf("fleetstate: rename into place: %w", err)
	}
	return nil
}

// CooldownUntil returns the time an agent's cooldown expires, and whether
// one is recorded at all.
func (s *State) CooldownUntil(agent string) (time.Time, bool) {
	t, ok := s.Cooldowns[agent]
	return t, ok
}

// OnCooldown reports whether agent is still cooling down at t.
func (s *State) OnCooldown(agent string, t time.Time) bool {
	until, ok := s.Cooldowns[agent]
	return ok && t.Before(until)
}

// RunningCount returns how many runs are currently Status==Running, total
// and per agent.
func (s *State) RunningCount() (total int, byAgent map[string]int) {
	byAgent = map[string]int{}
	for _, rec := range s.Runs {
		if rec.Status == StatusRunning {
			total++
			byAgent[rec.Spec.Agent]++
		}
	}
	return total, byAgent
}

// CountByStatus returns how many runs currently have exactly this status.
func (s *State) CountByStatus(status Status) int {
	n := 0
	for _, rec := range s.Runs {
		if rec.Status == status {
			n++
		}
	}
	return n
}

// NextRequeueID returns a fresh, stable id for a requeue of baseID
// ("<baseID>-r1", "-r2", ...), so repeated requeues of the same spec never
// collide.
func (s *State) NextRequeueID(baseID string) string {
	s.RequeueSeq[baseID]++
	return fmt.Sprintf("%s-r%d", baseID, s.RequeueSeq[baseID])
}
