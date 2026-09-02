package control

import (
	"testing"

	"fleetctl/internal/fleetstate"
)

func TestBuildStatus(t *testing.T) {
	state := fleetstate.New()
	state.MergeBlocked = true
	state.MergeBlockedReason = "conflict"
	state.Runs["a-p0"] = &fleetstate.RunRecord{
		Spec:          fleetstate.RunSpec{ID: "a-p0", File: "disasm/src/a.c", Owners: []string{"f1", "f2"}, Agent: "codex", Model: "m", Attempt: 1},
		Status:        fleetstate.StatusPROpen,
		MatchedOwners: []string{"f1"},
		PRURL:         "https://github.com/o/r/pull/9",
		PRNumber:      9,
	}
	state.Runs["b-p0"] = &fleetstate.RunRecord{
		Spec:   fleetstate.RunSpec{ID: "b-p0", File: "disasm/src/b.c", Agent: "kimi"},
		Status: fleetstate.StatusRunning,
	}

	got := BuildStatus(state)
	if !got.MergeBlocked {
		t.Fatal("MergeBlocked should reflect state.MergeBlocked")
	}
	if got.Running != 1 || got.RunningByAgent["kimi"] != 1 {
		t.Fatalf("running/byAgent = %d/%v", got.Running, got.RunningByAgent)
	}
	if len(got.Runs) != 2 {
		t.Fatalf("runs = %d, want 2", len(got.Runs))
	}
	// Sorted by id.
	if got.Runs[0].ID != "a-p0" || got.Runs[1].ID != "b-p0" {
		t.Fatalf("run order = %v", []string{got.Runs[0].ID, got.Runs[1].ID})
	}
	a := got.Runs[0]
	if a.Status != "pr_open" || a.Owners != 2 || a.Matched != 1 || a.Attempt != 1 || a.PRNumber != 9 {
		t.Fatalf("a status row = %+v", a)
	}
}
