package control

import (
	"context"
	"encoding/json"
	"testing"

	"fleetctl/internal/agentspec"
	"fleetctl/internal/fleetstate"
	"fleetctl/internal/planpkg"
	"fleetctl/internal/runner"
)

func persistPlan(t *testing.T, loop *Loop, p *planpkg.Plan) {
	t.Helper()
	data, err := json.Marshal(p)
	if err != nil {
		t.Fatal(err)
	}
	loop.State.PlanJSON = data
}

func TestReplanNoopWithoutAPersistedPlan(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	if err := loop.Replan(context.Background()); err != nil {
		t.Fatal(err)
	}
	if findCall(fake, "RankFiles") != nil || findCall(fake, "Targets") != nil {
		t.Fatal("Replan must not rank/target anything with no persisted plan")
	}
}

// TestReplanReconciliation exercises the full reconciliation described in
// docs/FLEET_CONTROLLER.md sec 2: a fresh ranking/targets pass drops owners
// that are now matched (naturally, since Targets no longer returns them), a
// virgin (never launched, unseeded) queued entry is dropped and replaced,
// a running run's owners are protected from a duplicate fresh partition
// (renamed via the requeue-suffix mechanism when the fresh id collides),
// and a seeded-but-not-yet-launched reseed survives untouched with its
// owner still reserved.
func TestReplanReconciliation(t *testing.T) {
	fake := &runner.Fake{
		TargetsResult: map[string][]runner.TargetOwner{
			"disasm/src/a.c": {
				{Function: "a_owner0", Source: "disasm/src/a.c"},
				{Function: "a_owner1", Source: "disasm/src/a.c"},
				{Function: "a_owner2", Source: "disasm/src/a.c"}, // genuinely new/unclaimed
			},
			"disasm/src/b.c": {
				{Function: "b_owner0", Source: "disasm/src/b.c"}, // already reserved by the seeded reseed below
				{Function: "b_owner5", Source: "disasm/src/b.c"}, // genuinely new/unclaimed
			},
		},
	}
	loop, _ := newTestLoop(t, fake)
	loop.MergeRepo = "/merge-worktree"

	plan := &planpkg.Plan{
		Repo: "/orig-repo", OwnersPerRun: 12,
		FileList: []string{"disasm/src/a.c", "disasm/src/b.c"},
		Agents:   []agentspec.Spec{{Agent: "codex", Model: "gpt-5.6-luna"}},
	}
	persistPlan(t, loop, plan)

	// a-p0 is actively running -- its owners a_owner0/a_owner1 must never
	// be re-queued by the fresh plan.
	loop.State.Runs["a-p0"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "a-p0", File: "disasm/src/a.c", Owners: []string{"a_owner0", "a_owner1"}, Agent: "codex",
		},
		Status:    fleetstate.StatusRunning,
		StartedAt: testNow,
	}
	// b-p0 is a virgin queued entry (never launched, no seeds) -- dropped
	// and replaced wholesale by the fresh plan.
	loop.State.Runs["b-p0"] = &fleetstate.RunRecord{
		Spec:   fleetstate.RunSpec{ID: "b-p0", File: "disasm/src/b.c", Owners: []string{"stale_owner"}, Agent: "codex"},
		Status: fleetstate.StatusQueued,
	}
	// b-p0-r1 is a post-merge reseed (SeedDirs set, never itself launched)
	// -- must survive untouched, and its owner stays reserved.
	loop.State.Runs["b-p0-r1"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "b-p0-r1", File: "disasm/src/b.c", Owners: []string{"b_owner0"}, Agent: "codex",
			SeedDirs: []string{"/runs/b-p0/out"},
		},
		Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"b-p0", "b-p0-r1"}

	if err := loop.Replan(context.Background()); err != nil {
		t.Fatal(err)
	}

	// Ranking/targets ran against the merge repo, not the original plan's
	// Repo or the launch --repo.
	for _, call := range fake.Calls {
		if call.Method == "Targets" && call.Strings[0] != "/merge-worktree" {
			t.Fatalf("Targets ran against %s, want /merge-worktree", call.Strings[0])
		}
	}

	// The running run is untouched.
	running := loop.State.Runs["a-p0"]
	if running == nil || running.Status != fleetstate.StatusRunning {
		t.Fatalf("a-p0 (running) must survive untouched: %+v", running)
	}
	// The seeded reseed survives untouched.
	seeded := loop.State.Runs["b-p0-r1"]
	if seeded == nil || len(seeded.Spec.Owners) != 1 || seeded.Spec.Owners[0] != "b_owner0" {
		t.Fatalf("b-p0-r1 (seeded) must survive untouched: %+v", seeded)
	}

	// A fresh partition for a.c collided with the still-running a-p0, so it
	// must have been renamed via the requeue-suffix mechanism and keep only
	// the genuinely unclaimed owner.
	renamed, ok := loop.State.Runs["a-p0-r1"]
	if !ok {
		t.Fatalf("expected a renamed fresh a.c partition at a-p0-r1; runs = %v", runIDs(loop.State.Runs))
	}
	if len(renamed.Spec.Owners) != 1 || renamed.Spec.Owners[0] != "a_owner2" {
		t.Fatalf("a-p0-r1 owners = %v, want [a_owner2] (a_owner0/a_owner1 are still in flight)", renamed.Spec.Owners)
	}

	// The fresh b.c partition reused the now-free b-p0 id (the virgin
	// entry that used to own it was dropped) and dropped the reserved
	// b_owner0.
	freshB, ok := loop.State.Runs["b-p0"]
	if !ok {
		t.Fatalf("expected a fresh b.c partition at b-p0; runs = %v", runIDs(loop.State.Runs))
	}
	if len(freshB.Spec.Owners) != 1 || freshB.Spec.Owners[0] != "b_owner5" {
		t.Fatalf("b-p0 owners = %v, want [b_owner5] (the virgin's stale_owner is gone, and b_owner0 is reserved by b-p0-r1)", freshB.Spec.Owners)
	}

	wantQueue := map[string]bool{"b-p0-r1": true, "a-p0-r1": true, "b-p0": true}
	if len(loop.State.Queue) != len(wantQueue) {
		t.Fatalf("queue = %v, want exactly %v", loop.State.Queue, wantQueue)
	}
	for _, id := range loop.State.Queue {
		if !wantQueue[id] {
			t.Fatalf("unexpected queue entry %s", id)
		}
	}

	// The persisted plan was refreshed too, so a later Replan reuses the
	// same Options again.
	refreshed, ok := loop.PersistedPlan()
	if !ok {
		t.Fatal("PersistedPlan should still be set after Replan")
	}
	if len(refreshed.FileList) != 2 {
		t.Fatalf("refreshed plan FileList = %v", refreshed.FileList)
	}
}

func runIDs(runs map[string]*fleetstate.RunRecord) []string {
	out := make([]string, 0, len(runs))
	for id := range runs {
		out = append(out, id)
	}
	return out
}

// TestReplanAfterSuccessfulMerge checks that a self-merge (sec 1) triggers
// exactly the Replan wiring: pollPRs calls it once fastForwardBase
// succeeds, and it reranks against the merge repo using the persisted
// plan's options.
func TestReplanAfterSuccessfulMerge(t *testing.T) {
	fake := &runner.Fake{
		GhPRChecksResult: runner.PRChecksResult{State: "SUCCESS"},
		TargetsResult: map[string][]runner.TargetOwner{
			"disasm/src/a.c": {{Function: "a_owner9", Source: "disasm/src/a.c"}},
		},
	}
	loop, _ := newTestLoop(t, fake)
	persistPlan(t, loop, &planpkg.Plan{
		FileList: []string{"disasm/src/a.c"},
		Agents:   []agentspec.Spec{{Agent: "codex", Model: "m"}},
	})
	rec := prOpenRec("x-p0", "https://github.com/o/r/pull/5", 5)
	loop.State.Runs["x-p0"] = rec

	if err := loop.pollPRs(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.Status != fleetstate.StatusMerged {
		t.Fatalf("status = %s, want merged", rec.Status)
	}
	if findCall(fake, "Targets") == nil {
		t.Fatal("a successful merge should have triggered a Replan (Targets was never called)")
	}
	if _, ok := loop.State.Runs["a-p0"]; !ok {
		t.Fatalf("replan should have queued a fresh a-p0 partition; runs = %v", runIDs(loop.State.Runs))
	}
}
