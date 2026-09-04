package control

import (
	"context"
	"encoding/json"
	"os"
	"path/filepath"
	"testing"

	"fleetctl/internal/agentspec"
	"fleetctl/internal/fleetstate"
	"fleetctl/internal/planpkg"
	"fleetctl/internal/runner"
)

// TestUpdateTiePoolCollectsAndPrunesMatched exercises the collection half
// of sec 13: a run's own <out>/tie-pool.json is merged into the file's
// persisted store, and any owner that run just matched is dropped from it
// ("owners removed once matched").
func TestUpdateTiePoolCollectsAndPrunesMatched(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}}}
	loop, dir := newTestLoop(t, fake)
	loop.RunsDir = dir
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"plateau"}`)
	mustWriteFile(t, filepath.Join(outDir, "tie-pool.json"), `{
		"func_1": {"source": "disasm/src/x.c", "body": "b1", "label": "tie"},
		"func_2": {"source": "disasm/src/x.c", "body": "b2", "label": "tie"}
	}`)
	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		mustWriteFile(t, filepath.Join(spec.OutDir, "merge-report.json"), `{"owners":{"func_1":"accepted","func_2":"rejected"}}`)
		return runner.ProcessResult{}, nil
	}
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}

	pool := loadTiePoolStore(tiePoolStorePath(dir, "disasm/src/x.c"))
	if _, ok := pool["func_1"]; ok {
		t.Fatalf("func_1 was matched this run and must be dropped from the pool: %+v", pool)
	}
	entry, ok := pool["func_2"]
	if !ok {
		t.Fatalf("func_2 (rejected, still plateaued) should remain in the pool: %+v", pool)
	}
	if entry.Body != "b2" || entry.Source != "disasm/src/x.c" {
		t.Fatalf("func_2 entry = %+v", entry)
	}
}

// TestUpdateTiePoolMergesAcrossRuns checks that a second run's tie-pool.json
// for the same file adds to (not replaces) the first run's still-pending
// entries.
func TestUpdateTiePoolMergesAcrossRuns(t *testing.T) {
	fake := &runner.Fake{}
	loop, dir := newTestLoop(t, fake)
	loop.RunsDir = dir

	rec1 := &fleetstate.RunRecord{
		Spec:   fleetstate.RunSpec{ID: "x-p0", File: "disasm/src/x.c"},
		OutDir: filepath.Join(dir, "out1"),
	}
	mustWriteFile(t, filepath.Join(rec1.OutDir, "tie-pool.json"), `{"func_1":{"source":"disasm/src/x.c","body":"b1"}}`)
	loop.updateTiePool(rec1)

	rec2 := &fleetstate.RunRecord{
		Spec:   fleetstate.RunSpec{ID: "x-p1", File: "disasm/src/x.c"},
		OutDir: filepath.Join(dir, "out2"),
	}
	mustWriteFile(t, filepath.Join(rec2.OutDir, "tie-pool.json"), `{"func_2":{"source":"disasm/src/x.c","body":"b2"}}`)
	loop.updateTiePool(rec2)

	pool := loadTiePoolStore(tiePoolStorePath(dir, "disasm/src/x.c"))
	if len(pool) != 2 {
		t.Fatalf("pool = %+v, want both func_1 and func_2", pool)
	}
}

// TestEnqueuePermuterLaneCreatesPartitionForPendingOwners exercises the
// per-replan enqueue step (sec 13): a persisted tie-pool store with pending
// owners and no in-flight permuter run for that file gets exactly one fresh
// permuter-only partition, launched with the documented flags.
func TestEnqueuePermuterLaneCreatesPartitionForPendingOwners(t *testing.T) {
	fake := &runner.Fake{}
	loop, dir := newTestLoop(t, fake)
	loop.RunsDir = dir
	loop.MergeRepo = "/merge-worktree"
	persistPlan(t, loop, &planpkg.Plan{
		FileList: []string{"disasm/src/x.c"},
		Agents:   []agentspec.Spec{{Agent: "codex", Model: "m"}},
	})
	fake.TargetsResult = map[string][]runner.TargetOwner{
		"disasm/src/x.c": {{Function: "func_1", Source: "disasm/src/x.c"}},
	}

	mustWriteFile(t, tiePoolStorePath(dir, "disasm/src/x.c"), `{
		"func_1": {"source": "disasm/src/x.c", "body": "b1", "label": "tie"}
	}`)

	if err := loop.Replan(context.Background()); err != nil {
		t.Fatal(err)
	}

	var permuterRec *fleetstate.RunRecord
	for _, rec := range loop.State.Runs {
		if rec.Spec.Agent == permuterAgent {
			permuterRec = rec
		}
	}
	if permuterRec == nil {
		t.Fatalf("expected a permuter-lane run to be enqueued; runs = %v", runIDs(loop.State.Runs))
	}
	if permuterRec.Spec.Mode != "permuter-only" {
		t.Fatalf("mode = %q, want permuter-only", permuterRec.Spec.Mode)
	}
	if len(permuterRec.Spec.Owners) != 1 || permuterRec.Spec.Owners[0] != "func_1" {
		t.Fatalf("owners = %v, want [func_1]", permuterRec.Spec.Owners)
	}
	if permuterRec.Spec.PermuterSeconds != defaultPermuterSeconds {
		t.Fatalf("permuter_seconds = %d, want default %d", permuterRec.Spec.PermuterSeconds, defaultPermuterSeconds)
	}
	found := false
	for _, id := range loop.State.Queue {
		if id == permuterRec.Spec.ID {
			found = true
		}
	}
	if !found {
		t.Fatal("the permuter-lane run must be on the queue")
	}
}

// TestEnqueuePermuterLaneSkipsWhenAlreadyInFlight checks that a second
// Replan does not create a duplicate permuter-lane partition for a file
// that already has one active.
func TestEnqueuePermuterLaneSkipsWhenAlreadyInFlight(t *testing.T) {
	fake := &runner.Fake{}
	loop, dir := newTestLoop(t, fake)
	loop.RunsDir = dir

	mustWriteFile(t, tiePoolStorePath(dir, "disasm/src/x.c"), `{
		"func_1": {"source": "disasm/src/x.c", "body": "b1"}
	}`)
	loop.State.Runs["x-permuter"] = &fleetstate.RunRecord{
		Spec:   fleetstate.RunSpec{ID: "x-permuter", File: "disasm/src/x.c", Agent: permuterAgent, Mode: "permuter-only"},
		Status: fleetstate.StatusRunning,
	}

	loop.enqueuePermuterLane()

	count := 0
	for _, rec := range loop.State.Runs {
		if rec.Spec.Agent == permuterAgent {
			count++
		}
	}
	if count != 1 {
		t.Fatalf("permuter-lane run count = %d, want 1 (no duplicate while one is already active)", count)
	}
}

// TestEnqueuePermuterLaneSkipsOwnersAlreadyClaimedByAnOrdinaryRun
// reproduces the real gap this closes: func_1 sits in the tie-pool store
// (from an earlier plateau) but an ORDINARY, non-permuter run already has
// a live, kept-across-replan claim on it right now (the same owner's own
// unmatched-owner reseed, in practice) -- the permuter lane must not also
// launch a container onto it. func_2, with no such claim, must still go
// out normally.
func TestEnqueuePermuterLaneSkipsOwnersAlreadyClaimedByAnOrdinaryRun(t *testing.T) {
	fake := &runner.Fake{}
	loop, dir := newTestLoop(t, fake)
	loop.RunsDir = dir

	mustWriteFile(t, tiePoolStorePath(dir, "disasm/src/x.c"), `{
		"func_1": {"source": "disasm/src/x.c", "body": "b1"},
		"func_2": {"source": "disasm/src/x.c", "body": "b2"}
	}`)
	// An ordinary (non-permuter) reseed of func_1, kept across a replan
	// because it carries SeedDirs -- exactly how runMerge's own
	// unmatched-owner requeue looks.
	loop.State.Runs["x-p0-r1"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "x-p0-r1", File: "disasm/src/x.c", Owners: []string{"func_1"},
			Agent: "codex", Model: "m", SeedDirs: []string{"/out/seeds/x-p0"},
		},
		Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"x-p0-r1"}

	loop.enqueuePermuterLane()

	var permuterRec *fleetstate.RunRecord
	for _, rec := range loop.State.Runs {
		if rec.Spec.Agent == permuterAgent {
			permuterRec = rec
		}
	}
	if permuterRec == nil {
		t.Fatalf("expected a permuter-lane run for func_2; runs = %v", runIDs(loop.State.Runs))
	}
	if len(permuterRec.Spec.Owners) != 1 || permuterRec.Spec.Owners[0] != "func_2" {
		t.Fatalf("permuter owners = %v, want exactly [func_2] -- func_1 is already claimed by x-p0-r1", permuterRec.Spec.Owners)
	}
}

// TestEnqueuePermuterLaneSkipsEntirelyWhenEveryOwnerIsAlreadyClaimed checks
// the all-claimed case: no permuter-lane run is created at all when every
// pending tie-pool owner already has a live ordinary claim, rather than
// enqueueing an empty/zero-owner partition.
func TestEnqueuePermuterLaneSkipsEntirelyWhenEveryOwnerIsAlreadyClaimed(t *testing.T) {
	fake := &runner.Fake{}
	loop, dir := newTestLoop(t, fake)
	loop.RunsDir = dir

	mustWriteFile(t, tiePoolStorePath(dir, "disasm/src/x.c"), `{
		"func_1": {"source": "disasm/src/x.c", "body": "b1"}
	}`)
	loop.State.Runs["x-p0-r1"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "x-p0-r1", File: "disasm/src/x.c", Owners: []string{"func_1"},
			Agent: "codex", Model: "m", SeedDirs: []string{"/out/seeds/x-p0"},
		},
		Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"x-p0-r1"}

	loop.enqueuePermuterLane()

	for _, rec := range loop.State.Runs {
		if rec.Spec.Agent == permuterAgent {
			t.Fatalf("no permuter-lane run should be created when its only pending owner is already claimed: %+v", rec)
		}
	}
}

// TestEnqueuePermuterLaneSkipsEmptyPool checks that a tie-pool store with
// zero remaining entries (every owner already matched and pruned) does not
// enqueue anything.
func TestEnqueuePermuterLaneSkipsEmptyPool(t *testing.T) {
	fake := &runner.Fake{}
	loop, dir := newTestLoop(t, fake)
	loop.RunsDir = dir
	mustWriteFile(t, tiePoolStorePath(dir, "disasm/src/x.c"), `{}`)

	loop.enqueuePermuterLane()

	if len(loop.State.Runs) != 0 {
		t.Fatalf("runs = %v, want none enqueued for an empty pool", runIDs(loop.State.Runs))
	}
}

// TestPreparePermuterTiePoolCopiesStoreIntoOutDir checks launch()'s own
// "copying the pool file into the out dir" step end to end via RunOnce,
// and that the resulting LaunchContainer call carries the documented
// in-container path.
func TestPreparePermuterTiePoolCopiesStoreIntoOutDir(t *testing.T) {
	fake := &runner.Fake{}
	loop, dir := newTestLoop(t, fake)
	loop.RunsDir = dir

	poolJSON := `{"func_1":{"source":"disasm/src/x.c","body":"b1","label":"tie"}}`
	mustWriteFile(t, tiePoolStorePath(dir, "disasm/src/x.c"), poolJSON)

	loop.State.Runs["x-permuter"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "x-permuter", File: "disasm/src/x.c", Owners: []string{"func_1"},
			Agent: permuterAgent, Mode: "permuter-only", PermuterSeconds: 1200,
		},
		Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"x-permuter"}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}

	call := findCall(fake, "LaunchContainer")
	if call == nil {
		t.Fatal("LaunchContainer was never called")
	}
	ls := call.Launch
	if ls.Mode != "permuter-only" || ls.TiePoolFile != "/out/tie-pool-input.json" || ls.PermuterSeconds != 1200 {
		t.Fatalf("launch spec = %+v", ls)
	}
	if ls.Agent != permuterAgent || ls.Model != "" {
		t.Fatalf("expected AGENT=permuter with no model, got agent=%q model=%q", ls.Agent, ls.Model)
	}

	copied, err := os.ReadFile(filepath.Join(ls.OutDir, "tie-pool-input.json"))
	if err != nil {
		t.Fatalf("tie-pool-input.json was not copied into the out dir: %v", err)
	}
	var got, want map[string]TiePoolEntry
	if err := json.Unmarshal(copied, &got); err != nil {
		t.Fatal(err)
	}
	if err := json.Unmarshal([]byte(poolJSON), &want); err != nil {
		t.Fatal(err)
	}
	if len(got) != len(want) || got["func_1"] != want["func_1"] {
		t.Fatalf("copied pool = %+v, want %+v", got, want)
	}
}
