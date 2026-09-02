package control

import (
	"sort"
	"time"

	"fleetctl/internal/fleetstate"
)

// RunStatus is one run's row of `fleetctl status --json` / the daily
// summary's embedded status block -- the same fields `fleetctl status`'s
// table prints, machine-readable.
type RunStatus struct {
	ID                string    `json:"id"`
	Status            string    `json:"status"`
	File              string    `json:"file"`
	Agent             string    `json:"agent"`
	Model             string    `json:"model"`
	Owners            int       `json:"owners"`
	Matched           int       `json:"matched"`
	Attempt           int       `json:"attempt"`
	Note              string    `json:"note,omitempty"`
	StoppedReason     string    `json:"stopped_reason,omitempty"`
	WaitReason        string    `json:"wait_reason,omitempty"`
	NeedsManualCommit []string  `json:"needs_manual_commit,omitempty"`
	Branch            string    `json:"branch,omitempty"`
	PRURL             string    `json:"pr_url,omitempty"`
	PRNumber          int       `json:"pr_number,omitempty"`
	MergedAt          time.Time `json:"merged_at,omitempty"`
	MergeCommitSHA    string    `json:"merge_commit_sha,omitempty"`
	// MergeBlockedRetries mirrors fleetstate.RunRecord.MergeBlockedRetries --
	// how many times control.Loop.retryBlockedMergeRuns has re-attempted
	// this run's merge step; nonzero only for a run that has been (or
	// currently is) merge_blocked_dirty.
	MergeBlockedRetries int `json:"merge_blocked_retries,omitempty"`
}

// StatusJSON is `fleetctl status --json`'s whole document: one row per run,
// the cooldowns table, the per-agent-spec METRICS table (sec 11), and the
// same running/queued summary the table's last line prints.
type StatusJSON struct {
	Runs           []RunStatus          `json:"runs"`
	Cooldowns      map[string]time.Time `json:"cooldowns,omitempty"`
	MergeBlocked   bool                 `json:"merge_blocked,omitempty"`
	Running        int                  `json:"running"`
	Queued         int                  `json:"queued"`
	RunningByAgent map[string]int       `json:"running_by_agent,omitempty"`
	Metrics        []AgentMetrics       `json:"metrics,omitempty"`
}

// BuildStatus renders state into StatusJSON -- shared by `fleetctl status
// --json` (cmd_status.go) and Loop.buildDailySummaryBody, so both always
// agree on what a run's status row looks like.
func BuildStatus(state *fleetstate.State) StatusJSON {
	ids := make([]string, 0, len(state.Runs))
	for id := range state.Runs {
		ids = append(ids, id)
	}
	sort.Strings(ids)

	runs := make([]RunStatus, 0, len(ids))
	for _, id := range ids {
		rec := state.Runs[id]
		var needsCommit []string
		for owner := range rec.NeedsManualCommit {
			needsCommit = append(needsCommit, owner)
		}
		sort.Strings(needsCommit)
		runs = append(runs, RunStatus{
			ID:                  id,
			Status:              string(rec.Status),
			File:                rec.Spec.File,
			Agent:               rec.Spec.Agent,
			Model:               rec.Spec.Model,
			Owners:              len(rec.Spec.Owners),
			Matched:             len(rec.MatchedOwners),
			Attempt:             rec.Spec.Attempt,
			Note:                rec.Note,
			StoppedReason:       rec.StoppedReason,
			WaitReason:          rec.WaitReason,
			NeedsManualCommit:   needsCommit,
			Branch:              rec.Branch,
			PRURL:               rec.PRURL,
			PRNumber:            rec.PRNumber,
			MergedAt:            rec.MergedAt,
			MergeCommitSHA:      rec.MergeCommitSHA,
			MergeBlockedRetries: rec.MergeBlockedRetries,
		})
	}

	total, byAgent := state.RunningCount()
	return StatusJSON{
		Runs:           runs,
		Cooldowns:      state.Cooldowns,
		MergeBlocked:   state.MergeBlocked,
		Running:        total,
		Queued:         len(state.Queue),
		RunningByAgent: byAgent,
		Metrics:        BuildMetrics(state, time.Now()),
	}
}
