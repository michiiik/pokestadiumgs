package control

import (
	"context"
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"testing"
	"time"

	"fleetctl/internal/fleetstate"
	"fleetctl/internal/planpkg"
	"fleetctl/internal/runner"
)

var testNow = time.Date(2026, 9, 2, 12, 0, 0, 0, time.UTC)

func newTestLoop(t *testing.T, fake *runner.Fake) (*Loop, string) {
	t.Helper()
	dir := t.TempDir()
	state := fleetstate.New()
	loop := &Loop{
		Runner:            fake,
		State:             state,
		StatePath:         filepath.Join(dir, "state.json"),
		RunsDir:           filepath.Join(dir, "runs"),
		Repo:              "/repo",
		IntegrationBranch: "master",
		MaxConcurrent:     4,
		Now:               func() time.Time { return testNow },
		Log:               func(string) {}, // silence during tests
	}
	return loop, dir
}

func mustWriteFile(t *testing.T, path, content string) {
	t.Helper()
	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(path, []byte(content), 0o644); err != nil {
		t.Fatal(err)
	}
}

func runningRec(id, containerID, outDir, agent string) *fleetstate.RunRecord {
	return &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: id, File: "disasm/src/x.c", Owners: []string{"func_1", "func_2"},
			Agent: agent, Model: "m",
		},
		Status:      fleetstate.StatusRunning,
		ContainerID: containerID,
		OutDir:      outDir,
	}
}

func findCall(fake *runner.Fake, method string) *runner.Call {
	for i := range fake.Calls {
		if fake.Calls[i].Method == method {
			return &fake.Calls[i]
		}
	}
	return nil
}

func methodSequence(fake *runner.Fake) []string {
	out := make([]string, len(fake.Calls))
	for i, c := range fake.Calls {
		out[i] = c.Method
	}
	return out
}

// assertSubsequence checks that `want` appears, in order (not necessarily
// contiguous), within `got`.
func assertSubsequence(t *testing.T, got, want []string) {
	t.Helper()
	i := 0
	for _, g := range got {
		if i < len(want) && g == want[i] {
			i++
		}
	}
	if i != len(want) {
		t.Fatalf("call sequence %v does not contain subsequence %v (matched %d/%d)", got, want, i, len(want))
	}
}

// --- launch: command construction with seeds --------------------------------

func TestLaunchConstructsCommandWithSeeds(t *testing.T) {
	fake := &runner.Fake{}
	loop, dir := newTestLoop(t, fake)

	seedDir := filepath.Join(dir, "seed-run")
	mustWriteFile(t, filepath.Join(seedDir, "state.json"), `{"func_1":{}}`)
	mustWriteFile(t, filepath.Join(seedDir, "accepted", "func_1.json"), `{"source":"disasm/src/x.c"}`)

	spec := fleetstate.RunSpec{
		ID: "x-p0", File: "disasm/src/x.c", Owners: []string{"func_1", "func_2"},
		Agent: "codex", Model: "gpt-5.6-luna", Effort: "high", BudgetSeconds: 3600,
		SeedDirs: []string{seedDir},
	}
	loop.State.Runs[spec.ID] = &fleetstate.RunRecord{Spec: spec, Status: fleetstate.StatusQueued}
	loop.State.Queue = []string{spec.ID}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}

	call := findCall(fake, "LaunchContainer")
	if call == nil {
		t.Fatal("LaunchContainer was never called")
	}
	ls := call.Launch
	if ls.SourceFile != "disasm/src/x.c" || ls.Agent != "codex" || ls.Model != "gpt-5.6-luna" || ls.Effort != "high" {
		t.Fatalf("unexpected launch spec: %+v", ls)
	}
	if len(ls.Owners) != 2 {
		t.Fatalf("owners = %v", ls.Owners)
	}
	if len(ls.SeedFrom) != 1 || ls.SeedFrom[0] != "/out/seeds/seed-run" {
		t.Fatalf("SeedFrom = %v, want [/out/seeds/seed-run]", ls.SeedFrom)
	}
	if ls.Resume {
		t.Fatal("a fresh (Attempt==0) spec must not pass --resume")
	}

	if _, err := os.Stat(filepath.Join(ls.OutDir, "seeds", "seed-run", "state.json")); err != nil {
		t.Fatalf("seed state.json was not copied: %v", err)
	}
	if _, err := os.Stat(filepath.Join(ls.OutDir, "seeds", "seed-run", "accepted", "func_1.json")); err != nil {
		t.Fatalf("seed accepted/func_1.json was not copied: %v", err)
	}

	rec := loop.State.Runs["x-p0"]
	if rec.Status != fleetstate.StatusRunning || rec.ContainerID == "" {
		t.Fatalf("run record not marked running: %+v", rec)
	}
}

func TestLaunchResumePassesResumeFlag(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	spec := fleetstate.RunSpec{ID: "x-p0", File: "disasm/src/x.c", Owners: []string{"func_1"}, Agent: "codex", Attempt: 1}
	loop.State.Runs[spec.ID] = &fleetstate.RunRecord{Spec: spec, Status: fleetstate.StatusQueued}
	loop.State.Queue = []string{spec.ID}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	call := findCall(fake, "LaunchContainer")
	if call == nil || !call.Launch.Resume {
		t.Fatalf("Attempt>0 spec must launch with --resume: %+v", call)
	}
}

// --- exit handling per stopped_reason ---------------------------------------

func TestExitHandlingGeneratorExhausted(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{
		"cid": {{Found: true, Running: false, ExitCode: 3}},
	}}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"generator_exhausted"}`)

	rec := runningRec("x-p0", "cid", outDir, "kimi")
	loop.State.Runs["x-p0"] = rec
	loop.CooldownDefaults = map[string]time.Duration{"kimi": 5 * time.Hour}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}

	if rec.Status != fleetstate.StatusRequeued {
		t.Fatalf("status = %s, want requeued", rec.Status)
	}
	if rec.Spec.Attempt != 1 {
		t.Fatalf("attempt = %d, want 1", rec.Spec.Attempt)
	}
	if len(loop.State.Queue) != 1 || loop.State.Queue[0] != "x-p0" {
		t.Fatalf("queue = %v, want [x-p0]", loop.State.Queue)
	}
	until, ok := loop.State.CooldownUntil("kimi")
	if !ok || !until.Equal(testNow.Add(5*time.Hour)) {
		t.Fatalf("cooldown = %v, ok=%v", until, ok)
	}
	if findCall(fake, "Merge") != nil {
		t.Fatal("merge must not run on generator_exhausted")
	}
}

func TestExitHandlingTriggersMerge(t *testing.T) {
	for _, reason := range []string{"budget_expired", "plateau", "completed", "no_owners", "normal"} {
		t.Run(reason, func(t *testing.T) {
			fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{
				"cid": {{Found: true, Running: false}},
			}}
			loop, dir := newTestLoop(t, fake)
			outDir := filepath.Join(dir, "out")
			mustWriteFile(t, filepath.Join(outDir, "summary.json"), fmt.Sprintf(`{"stopped_reason":%q}`, reason))
			rec := runningRec("x-p0", "cid", outDir, "codex")
			loop.State.Runs["x-p0"] = rec

			if _, err := loop.RunOnce(context.Background()); err != nil {
				t.Fatal(err)
			}

			if rec.Status != fleetstate.StatusDone {
				t.Fatalf("status = %s, want done", rec.Status)
			}
			if findCall(fake, "Merge") == nil || findCall(fake, "ImportStats") == nil || findCall(fake, "GitCheckoutNewBranch") == nil {
				t.Fatalf("expected merge/import-stats/branch calls, got %v", methodSequence(fake))
			}
		})
	}
}

func TestExitHandlingVanishedRequeues(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{"cid": {{Found: false}}}}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out-no-summary") // never written
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	// Nothing else was queued and this agent has no cooldown, so the same
	// pass that requeues it also relaunches it immediately (capacity is
	// free) -- the end-of-pass state is StatusRunning again, with Attempt
	// bumped and --resume on the relaunch.
	if rec.Spec.Attempt != 1 {
		t.Fatalf("attempt = %d, want 1", rec.Spec.Attempt)
	}
	if rec.Status != fleetstate.StatusRunning {
		t.Fatalf("status = %s, want running (relaunched same pass)", rec.Status)
	}
	launchCall := findCall(fake, "LaunchContainer")
	if launchCall == nil || !launchCall.Launch.Resume {
		t.Fatalf("the relaunch after a vanished run must pass --resume: %+v", launchCall)
	}
	if findCall(fake, "Merge") != nil {
		t.Fatal("merge must not run when summary.json is missing")
	}
}

// --- cooldown / concurrency gating -------------------------------------------

func TestCooldownBlocksLaunch(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	loop.State.Cooldowns["kimi"] = testNow.Add(time.Hour)

	loop.State.Runs["a"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{ID: "a", File: "disasm/src/a.c", Owners: []string{"f1"}, Agent: "kimi"}, Status: fleetstate.StatusQueued,
	}
	loop.State.Runs["b"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{ID: "b", File: "disasm/src/b.c", Owners: []string{"f2"}, Agent: "codex"}, Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"a", "b"}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if loop.State.Runs["a"].Status != fleetstate.StatusQueued {
		t.Fatalf("kimi run should remain queued while on cooldown: %s", loop.State.Runs["a"].Status)
	}
	if loop.State.Runs["b"].Status != fleetstate.StatusRunning {
		t.Fatalf("codex run should have launched: %s", loop.State.Runs["b"].Status)
	}
	if len(loop.State.Queue) != 1 || loop.State.Queue[0] != "a" {
		t.Fatalf("queue = %v, want [a]", loop.State.Queue)
	}
}

func TestAgentConcurrencyCap(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	loop.AgentConcurrency = map[string]int{"codex": 1}

	loop.State.Runs["a"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{ID: "a", File: "disasm/src/a.c", Owners: []string{"f1"}, Agent: "codex"}, Status: fleetstate.StatusQueued,
	}
	loop.State.Runs["b"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{ID: "b", File: "disasm/src/b.c", Owners: []string{"f2"}, Agent: "codex"}, Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"a", "b"}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if loop.State.Runs["a"].Status != fleetstate.StatusRunning {
		t.Fatal("a should have launched")
	}
	if loop.State.Runs["b"].Status != fleetstate.StatusQueued {
		t.Fatalf("b should remain queued: codex is capped at 1 concurrent, got %s", loop.State.Runs["b"].Status)
	}
}

// --- merge sequencing / PR construction / unmatched requeue ------------------

func TestMergeSequencingAndPRConstruction(t *testing.T) {
	fake := &runner.Fake{
		InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}},
		GhPRURL:        "https://github.com/example/pokemonStadiumGSRecomp/pull/1",
	}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)

	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		mustWriteFile(t, filepath.Join(spec.OutDir, "merge-report.json"),
			`{"owners":{"func_1":"accepted","func_2":"rejected"}}`)
		return runner.ProcessResult{ExitCode: 1}, nil
	}

	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}

	assertSubsequence(t, methodSequence(fake), []string{
		"InspectContainer", "GitCheckout", "GitCheckoutNewBranch", "Merge", "ImportStats", "GitPush", "GhPRCreate", "GitCheckout",
	})

	if rec.Branch != "container/x-p0" {
		t.Fatalf("branch = %s, want container/x-p0", rec.Branch)
	}
	if rec.PRURL != fake.GhPRURL {
		t.Fatalf("pr url = %s", rec.PRURL)
	}
	if len(rec.MatchedOwners) != 1 || rec.MatchedOwners[0] != "func_1" {
		t.Fatalf("matched = %v, want [func_1]", rec.MatchedOwners)
	}
	if rec.Status != fleetstate.StatusDone {
		t.Fatalf("status = %s", rec.Status)
	}

	branchCall := findCall(fake, "GitCheckoutNewBranch")
	if branchCall == nil || branchCall.Strings[0] != "/repo" || branchCall.Strings[1] != "container/x-p0" || branchCall.Strings[2] != "master" {
		t.Fatalf("branch call = %+v", branchCall)
	}

	prCall := findCall(fake, "GhPRCreate")
	if prCall == nil {
		t.Fatal("GhPRCreate not called")
	}
	if prCall.PR.RepoRoot != "/repo" || prCall.PR.Base != "master" {
		t.Fatalf("pr spec = %+v", prCall.PR)
	}
	if !strings.Contains(prCall.PR.Title, "func_1") {
		t.Fatalf("title = %s, want it to name func_1", prCall.PR.Title)
	}
	if !strings.Contains(prCall.PR.Body, "func_1") || !strings.Contains(prCall.PR.Body, "func_2") {
		t.Fatalf("body = %s, want both owners listed", prCall.PR.Body)
	}

	// The unmatched owner is requeued as a new run (a fresh reseed, not a
	// --resume of x-p0). With capacity free and no cooldown, launchEligible
	// may relaunch it within this same pass, so look for it in Runs rather
	// than assuming it is still sitting in Queue.
	newID := onlyOtherRunID(t, loop.State.Runs, "x-p0")
	newRec := loop.State.Runs[newID]
	if len(newRec.Spec.Owners) != 1 || newRec.Spec.Owners[0] != "func_2" {
		t.Fatalf("requeued run = %+v", newRec)
	}
	if newRec.Spec.Attempt != 0 {
		t.Fatalf("a fresh reseed must have Attempt=0, got %d", newRec.Spec.Attempt)
	}
	if len(newRec.Spec.SeedDirs) != 1 || newRec.Spec.SeedDirs[0] != outDir {
		t.Fatalf("seed dirs = %v, want [%s]", newRec.Spec.SeedDirs, outDir)
	}
}

func TestMergeNoAcceptedOwnersSkipsPR(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}}}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"budget_expired"}`)
	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		mustWriteFile(t, filepath.Join(spec.OutDir, "merge-report.json"), `{"owners":{"func_1":"rejected","func_2":"rejected"}}`)
		return runner.ProcessResult{ExitCode: 1}, nil
	}
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if findCall(fake, "GitPush") != nil || findCall(fake, "GhPRCreate") != nil {
		t.Fatal("must not push or open a PR when zero owners were accepted")
	}
	newID := onlyOtherRunID(t, loop.State.Runs, "x-p0")
	newRec := loop.State.Runs[newID]
	if len(newRec.Spec.Owners) != 2 {
		t.Fatalf("both unmatched owners should be requeued together: %+v", newRec.Spec.Owners)
	}
}

// onlyOtherRunID returns the single run id in runs that is not exclude,
// failing the test if there is not exactly one.
func onlyOtherRunID(t *testing.T, runs map[string]*fleetstate.RunRecord, exclude string) string {
	t.Helper()
	var found []string
	for id := range runs {
		if id != exclude {
			found = append(found, id)
		}
	}
	if len(found) != 1 {
		t.Fatalf("expected exactly one other run id besides %s, got %v", exclude, found)
	}
	return found[0]
}

// --- LoadPlan idempotency ----------------------------------------------------

func TestLoadPlanIdempotent(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	p := &planpkg.Plan{
		Repo: "/repo", Slots: 4,
		Cooldowns:        map[string]string{"kimi": "5h0m0s"},
		AgentConcurrency: map[string]int{"codex": 2},
		Queue:            []fleetstate.RunSpec{{ID: "a", File: "disasm/src/a.c", Owners: []string{"f1"}, Agent: "codex"}},
	}
	if err := loop.LoadPlan(p); err != nil {
		t.Fatal(err)
	}
	if err := loop.LoadPlan(p); err != nil {
		t.Fatal(err)
	}
	if len(loop.State.Queue) != 1 {
		t.Fatalf("queue duplicated across two LoadPlan calls: %v", loop.State.Queue)
	}
	if loop.CooldownDefaults["kimi"] != 5*time.Hour {
		t.Fatalf("cooldown default = %v", loop.CooldownDefaults)
	}
	if loop.AgentConcurrency["codex"] != 2 {
		t.Fatalf("agent concurrency = %v", loop.AgentConcurrency)
	}
}

// --- state persistence round trip at the loop level --------------------------

func TestRunPersistsStateAtomically(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	spec := fleetstate.RunSpec{ID: "a", File: "disasm/src/a.c", Owners: []string{"f1"}, Agent: "codex"}
	loop.State.Runs["a"] = &fleetstate.RunRecord{Spec: spec, Status: fleetstate.StatusQueued}
	loop.State.Queue = []string{"a"}

	if err := loop.Run(context.Background(), true); err != nil {
		t.Fatal(err)
	}

	reloaded, err := fleetstate.Load(loop.StatePath)
	if err != nil {
		t.Fatal(err)
	}
	if reloaded.Runs["a"].Status != fleetstate.StatusRunning {
		t.Fatalf("persisted status = %s, want running", reloaded.Runs["a"].Status)
	}
}

// --- stop safety --------------------------------------------------------------

func TestStopSafety(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	loop.State.Runs["a"] = &fleetstate.RunRecord{Spec: fleetstate.RunSpec{ID: "a"}, Status: fleetstate.StatusRunning, ContainerID: "cid-a"}
	loop.State.Runs["b"] = &fleetstate.RunRecord{Spec: fleetstate.RunSpec{ID: "b"}, Status: fleetstate.StatusQueued}

	if err := loop.StopAll(context.Background()); err != nil {
		t.Fatal(err)
	}
	var stopped []string
	for _, c := range fake.Calls {
		if c.Method == "StopContainer" {
			stopped = append(stopped, c.Strings[0])
		}
	}
	if len(stopped) != 1 || stopped[0] != "cid-a" {
		t.Fatalf("stopped containers = %v, want exactly [cid-a]", stopped)
	}
	if loop.State.Runs["a"].Status != fleetstate.StatusRequeued {
		t.Fatalf("a status = %s", loop.State.Runs["a"].Status)
	}
	if loop.State.Runs["b"].ContainerID != "" {
		t.Fatalf("b was never running and must be untouched: %+v", loop.State.Runs["b"])
	}

	if err := loop.StopRun(context.Background(), "does-not-exist"); err == nil {
		t.Fatal("want error for an unknown run id")
	}
	if err := loop.StopRun(context.Background(), "b"); err == nil {
		t.Fatal("want error stopping a run with no running container")
	}
}
