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
// docs/FLEET_CONTROLLER.md: queued -> running -> merging -> done|requeued.
type Status string

const (
	StatusQueued   Status = "queued"
	StatusRunning  Status = "running"
	StatusMerging  Status = "merging"
	StatusDone     Status = "done"
	StatusRequeued Status = "requeued"
	StatusFailed   Status = "failed"
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
	Branch        string    `json:"branch,omitempty"`
	PRURL         string    `json:"pr_url,omitempty"`
	Note          string    `json:"note,omitempty"`
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
}

// New returns an empty State ready to have a plan's queue loaded into it.
func New() *State {
	return &State{
		Runs:       map[string]*RunRecord{},
		Cooldowns:  map[string]time.Time{},
		RequeueSeq: map[string]int{},
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

// NextRequeueID returns a fresh, stable id for a requeue of baseID
// ("<baseID>-r1", "-r2", ...), so repeated requeues of the same spec never
// collide.
func (s *State) NextRequeueID(baseID string) string {
	s.RequeueSeq[baseID]++
	return fmt.Sprintf("%s-r%d", baseID, s.RequeueSeq[baseID])
}
