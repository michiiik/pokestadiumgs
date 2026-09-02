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

func TestExitHandlingVanishedRequeuesWithBackoff(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{"cid": {{Found: false}}}}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out-no-summary") // never written
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	// Requeued (with --resume, Attempt bumped) but held back at least 10m
	// (sec 2, "vanished container storm") -- unlike a generator_exhausted
	// requeue, this must NOT relaunch in the same pass even though capacity
	// and cooldowns allow it.
	if rec.Spec.Attempt != 1 {
		t.Fatalf("attempt = %d, want 1", rec.Spec.Attempt)
	}
	if rec.Status != fleetstate.StatusRequeued {
		t.Fatalf("status = %s, want requeued (backed off, not relaunched)", rec.Status)
	}
	if rec.VanishCount != 1 {
		t.Fatalf("vanish count = %d, want 1", rec.VanishCount)
	}
	wantNotBefore := testNow.Add(10 * time.Minute)
	if !rec.NotBefore.Equal(wantNotBefore) {
		t.Fatalf("not_before = %v, want %v", rec.NotBefore, wantNotBefore)
	}
	if rec.WaitReason != "backoff until "+wantNotBefore.Format(time.RFC3339) {
		t.Fatalf("wait_reason = %q", rec.WaitReason)
	}
	if findCall(fake, "LaunchContainer") != nil {
		t.Fatal("must not relaunch within the backoff window")
	}
	if findCall(fake, "Merge") != nil {
		t.Fatal("merge must not run when summary.json is missing")
	}

	// Once the backoff elapses, the next pass relaunches it with --resume.
	loop.Now = func() time.Time { return wantNotBefore.Add(time.Second) }
	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.Status != fleetstate.StatusRunning {
		t.Fatalf("status = %s, want running once the backoff has elapsed", rec.Status)
	}
	launchCall := findCall(fake, "LaunchContainer")
	if launchCall == nil || !launchCall.Launch.Resume {
		t.Fatalf("the relaunch after a vanished run must pass --resume: %+v", launchCall)
	}
	if !rec.NotBefore.IsZero() {
		t.Fatalf("not_before should be cleared once relaunched, got %v", rec.NotBefore)
	}
}

// TestVanishCountResetsOnReadableSummary checks that a run which vanishes
// once and then, on its next attempt, actually produces a readable
// summary.json has its VanishCount reset to 0 -- so a single flaky vanish
// followed by normal completions never creeps toward the
// maxConsecutiveVanishes cap.
func TestVanishCountResetsOnReadableSummary(t *testing.T) {
	loop, dir := newTestLoop(t, &runner.Fake{})
	outDir := filepath.Join(dir, "out")
	rec := runningRec("x-p0", "cid", outDir, "codex")
	rec.VanishCount = 2
	loop.State.Runs["x-p0"] = rec

	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)
	if err := loop.handleExit(context.Background(), rec); err != nil {
		t.Fatal(err)
	}
	if rec.VanishCount != 0 {
		t.Fatalf("vanish count = %d, want reset to 0 once a summary.json is read", rec.VanishCount)
	}
}

// TestExitHandlingVanishedThreeTimesMarksFailed checks the
// maxConsecutiveVanishes cap (sec 2): three vanishes of the same run id in a
// row, with no readable summary.json ever seen in between, mark it
// StatusFailed with a container_vanished_repeatedly alert instead of
// requeueing it a third time.
func TestExitHandlingVanishedThreeTimesMarksFailed(t *testing.T) {
	loop, dir := newTestLoop(t, &runner.Fake{})
	notifier := &fakeNotifier{}
	loop.Notifiers = []Notifier{notifier}
	outDir := filepath.Join(dir, "out-no-summary") // never written
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	ctx := context.Background()
	if err := loop.handleExit(ctx, rec); err != nil {
		t.Fatal(err)
	}
	if rec.VanishCount != 1 || rec.Status != fleetstate.StatusRequeued {
		t.Fatalf("after 1st vanish: count=%d status=%s", rec.VanishCount, rec.Status)
	}
	if err := loop.handleExit(ctx, rec); err != nil {
		t.Fatal(err)
	}
	if rec.VanishCount != 2 || rec.Status != fleetstate.StatusRequeued {
		t.Fatalf("after 2nd vanish: count=%d status=%s", rec.VanishCount, rec.Status)
	}
	if len(notifier.calls) != 1 {
		t.Fatalf("notifier calls after 2 vanishes = %d, want 1 (container_vanished)", len(notifier.calls))
	}

	if err := loop.handleExit(ctx, rec); err != nil {
		t.Fatal(err)
	}
	if rec.VanishCount != 3 {
		t.Fatalf("vanish count = %d, want 3", rec.VanishCount)
	}
	if rec.Status != fleetstate.StatusFailed {
		t.Fatalf("status = %s, want failed after 3 consecutive vanishes", rec.Status)
	}
	if rec.Note != "vanished 3x; needs operator" {
		t.Fatalf("note = %q", rec.Note)
	}
	if len(notifier.calls) != 2 {
		t.Fatalf("notifier calls after 3 vanishes = %d, want 2 (container_vanished_repeatedly is a distinct rate-limit key)", len(notifier.calls))
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
	if loop.State.Runs["a"].WaitReason != "cooldown" {
		t.Fatalf("a wait_reason = %q, want %q", loop.State.Runs["a"].WaitReason, "cooldown")
	}
	if loop.State.Runs["b"].WaitReason != "" {
		t.Fatalf("b wait_reason = %q, want empty once launched", loop.State.Runs["b"].WaitReason)
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
	if loop.State.Runs["b"].WaitReason != "concurrency" {
		t.Fatalf("b wait_reason = %q, want %q (per-agent concurrency cap, not a cooldown)", loop.State.Runs["b"].WaitReason, "concurrency")
	}
}

// TestGlobalConcurrencyWaitReason checks that a run left queued because the
// global --max-concurrent cap (not a per-agent cap or a cooldown) is full
// is recorded with wait_reason "concurrency" too, per
// docs/FLEET_CONTROLLER.md sec 6's "distinguish cooldown vs concurrency"
// design note.
func TestGlobalConcurrencyWaitReason(t *testing.T) {
	fake := &runner.Fake{
		InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: true}}},
	}
	loop, outDir := newTestLoop(t, fake)
	loop.MaxConcurrent = 1
	loop.State.Runs["already-running"] = runningRec("already-running", "cid", outDir, "codex")
	loop.State.Runs["b"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{ID: "b", File: "disasm/src/b.c", Owners: []string{"f2"}, Agent: "kimi"}, Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"b"}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if loop.State.Runs["b"].Status != fleetstate.StatusQueued {
		t.Fatalf("b should remain queued: global max-concurrent=1 is full, got %s", loop.State.Runs["b"].Status)
	}
	if loop.State.Runs["b"].WaitReason != "concurrency" {
		t.Fatalf("b wait_reason = %q, want %q", loop.State.Runs["b"].WaitReason, "concurrency")
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
		"InspectContainer", "GitStatusPorcelain", "GitFetch", "GitCheckoutNewBranch", "Merge", "ImportStats", "GitPush", "GhPRCreate", "GitCheckoutDetach",
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
	// --auto-merge defaults to true (DisableAutoMerge's zero value), so a
	// PR opened this run is not "done" yet -- pollPRs takes it from here.
	if rec.Status != fleetstate.StatusPROpen {
		t.Fatalf("status = %s, want pr_open", rec.Status)
	}
	if rec.PRNumber != 1 {
		t.Fatalf("pr number = %d, want 1 (parsed from %s)", rec.PRNumber, fake.GhPRURL)
	}

	branchCall := findCall(fake, "GitCheckoutNewBranch")
	if branchCall == nil || branchCall.Strings[0] != "/repo" || branchCall.Strings[1] != "container/x-p0" || branchCall.Strings[2] != "origin/master" {
		t.Fatalf("branch call = %+v, want from=origin/master (the default --base-ref)", branchCall)
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

func TestBranchNameFoldsInMergeRound(t *testing.T) {
	spec := fleetstate.RunSpec{ID: "x-p0"}
	if got := branchName(spec, 0); got != "container/x-p0" {
		t.Fatalf("round 0: branchName = %q, want container/x-p0", got)
	}
	if got := branchName(spec, 1); got != "container/x-p0-m2" {
		t.Fatalf("round 1: branchName = %q, want container/x-p0-m2", got)
	}
	if got := branchName(spec, 2); got != "container/x-p0-m3" {
		t.Fatalf("round 2: branchName = %q, want container/x-p0-m3", got)
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

// --- merge-report.json owner-entry shapes ------------------------------------
//
// tools/container_merge.py's write_merge_report emits, per owner, either a
// bare status string, or -- only for an owner whose host re-gate accepted
// but whose `git commit --only` then failed -- an object
// {"status":"accepted","committed":false,"commit_error":"<tail>"}. These
// tests exercise both shapes, plus the (defensive) object-with-committed:true
// shape, through loadMergeReport/matchedOwners/needsManualCommitOwners as
// exercised by runMerge.

func TestMergeReportPlainStringAccepted(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}}}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)
	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		mustWriteFile(t, filepath.Join(spec.OutDir, "merge-report.json"), `{"owners":{"func_1":"accepted"}}`)
		return runner.ProcessResult{}, nil
	}
	rec := &fleetstate.RunRecord{
		Spec:        fleetstate.RunSpec{ID: "x-p0", File: "disasm/src/x.c", Owners: []string{"func_1"}, Agent: "codex"},
		Status:      fleetstate.StatusRunning,
		ContainerID: "cid",
		OutDir:      outDir,
	}
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if len(rec.MatchedOwners) != 1 || rec.MatchedOwners[0] != "func_1" {
		t.Fatalf("matched = %v, want [func_1]: a bare \"accepted\" string must count as matched", rec.MatchedOwners)
	}
	if len(rec.NeedsManualCommit) != 0 {
		t.Fatalf("needs_manual_commit = %v, want empty for a plain string entry", rec.NeedsManualCommit)
	}
	if _, requeued := loop.State.Runs["x-p0-r1"]; requeued {
		t.Fatal("a fully matched owner must not be requeued")
	}
}

func TestMergeReportObjectCommittedTrueCountsMatched(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}}}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)
	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		mustWriteFile(t, filepath.Join(spec.OutDir, "merge-report.json"),
			`{"owners":{"func_1":{"status":"accepted","committed":true}}}`)
		return runner.ProcessResult{}, nil
	}
	rec := &fleetstate.RunRecord{
		Spec:        fleetstate.RunSpec{ID: "x-p0", File: "disasm/src/x.c", Owners: []string{"func_1"}, Agent: "codex"},
		Status:      fleetstate.StatusRunning,
		ContainerID: "cid",
		OutDir:      outDir,
	}
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if len(rec.MatchedOwners) != 1 || rec.MatchedOwners[0] != "func_1" {
		t.Fatalf("matched = %v, want [func_1]: an object entry with committed:true must still count as matched", rec.MatchedOwners)
	}
	if len(rec.NeedsManualCommit) != 0 {
		t.Fatalf("needs_manual_commit = %v, want empty", rec.NeedsManualCommit)
	}
}

func TestMergeReportObjectCommittedFalseNeedsManualCommit(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}}}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)
	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		mustWriteFile(t, filepath.Join(spec.OutDir, "merge-report.json"),
			`{"owners":{"func_1":{"status":"accepted","committed":false,"commit_error":"error: did not match any file(s) known to git\nfatal: pathspec"}}}`)
		return runner.ProcessResult{ExitCode: 1}, nil
	}
	rec := &fleetstate.RunRecord{
		Spec:        fleetstate.RunSpec{ID: "x-p0", File: "disasm/src/x.c", Owners: []string{"func_1"}, Agent: "codex"},
		Status:      fleetstate.StatusRunning,
		ContainerID: "cid",
		OutDir:      outDir,
	}
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}

	// Not matched.
	if len(rec.MatchedOwners) != 0 {
		t.Fatalf("matched = %v, want empty: accepted-but-uncommitted must not count as matched", rec.MatchedOwners)
	}
	// Not requeued -- the candidate is already installed in the merge repo's
	// working tree, and a requeue would re-probe a duplicate.
	if len(loop.State.Queue) != 0 {
		t.Fatalf("queue = %v, want empty: an accepted-but-uncommitted owner must not be requeued", loop.State.Queue)
	}
	for id := range loop.State.Runs {
		if id != "x-p0" {
			t.Fatalf("unexpected extra run %s: accepted-but-uncommitted owner must not spawn a requeue", id)
		}
	}
	// Recorded for a manual commit.
	tail, ok := rec.NeedsManualCommit["func_1"]
	if !ok {
		t.Fatalf("needs_manual_commit = %v, want an entry for func_1", rec.NeedsManualCommit)
	}
	if !strings.Contains(tail, "did not match any file") {
		t.Fatalf("needs_manual_commit[func_1] = %q, want the commit_error tail preserved", tail)
	}
	// No PR opened: zero owners actually matched this run.
	if findCall(fake, "GhPRCreate") != nil {
		t.Fatal("must not open a PR: no owner in this run was fully matched")
	}
}

// TestMergeReportMixedMatchedAndManualCommitMentionsBothInPRBody exercises a
// run where one owner matched (triggering a PR for the *other* owners of
// this run) and a second owner needs a manual commit -- the manual-commit
// owner must be mentioned in that PR's body, not silently dropped, and must
// still not be requeued.
func TestMergeReportMixedMatchedAndManualCommitMentionsBothInPRBody(t *testing.T) {
	fake := &runner.Fake{
		InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}},
		GhPRURL:        "https://github.com/example/pokemonStadiumGSRecomp/pull/2",
	}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)
	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		mustWriteFile(t, filepath.Join(spec.OutDir, "merge-report.json"), `{"owners":{
			"func_1":"accepted",
			"func_2":{"status":"accepted","committed":false,"commit_error":"fatal: commit failed"}
		}}`)
		return runner.ProcessResult{ExitCode: 1}, nil
	}
	rec := &fleetstate.RunRecord{
		Spec:        fleetstate.RunSpec{ID: "x-p0", File: "disasm/src/x.c", Owners: []string{"func_1", "func_2"}, Agent: "codex"},
		Status:      fleetstate.StatusRunning,
		ContainerID: "cid",
		OutDir:      outDir,
	}
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if len(rec.MatchedOwners) != 1 || rec.MatchedOwners[0] != "func_1" {
		t.Fatalf("matched = %v, want [func_1]", rec.MatchedOwners)
	}
	if _, ok := rec.NeedsManualCommit["func_2"]; !ok {
		t.Fatalf("needs_manual_commit = %v, want an entry for func_2", rec.NeedsManualCommit)
	}
	prCall := findCall(fake, "GhPRCreate")
	if prCall == nil {
		t.Fatal("GhPRCreate not called: func_1 matched, a PR should still open")
	}
	if !strings.Contains(prCall.PR.Body, "func_2") || !strings.Contains(prCall.PR.Body, "needs manual commit") {
		t.Fatalf("PR body = %s, want func_2's needs-manual-commit status mentioned", prCall.PR.Body)
	}
	// func_2 must not be requeued either.
	for id := range loop.State.Runs {
		if id != "x-p0" {
			t.Fatalf("unexpected extra run %s: func_2 needs a manual commit, not a requeue", id)
		}
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

// --- MergeRepo (docs/FLEET_CONTROLLER.md sec 6, "merge-repo == launch-repo") -

// TestMergeRepoSeparatesLaunchFromMergeCheckout checks that, when Loop.MergeRepo
// is set to a different checkout than Loop.Repo, every merge/branch/PR call
// (git checkout, git checkout -b, merge --repo, import-stats --repo, git
// push, gh pr create) targets MergeRepo, while a container launch (which
// happens in a separate test path, but shares the same ExecRunner.RepoRoot
// concept) is unaffected -- Loop.Repo is never passed to those calls.
func TestMergeRepoSeparatesLaunchFromMergeCheckout(t *testing.T) {
	fake := &runner.Fake{
		InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}},
		GhPRURL:        "https://github.com/example/pokemonStadiumGSRecomp/pull/3",
	}
	loop, dir := newTestLoop(t, fake)
	loop.MergeRepo = "/merge-worktree"
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)
	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		if spec.RepoRoot != "/merge-worktree" {
			t.Fatalf("Merge repo root = %s, want /merge-worktree", spec.RepoRoot)
		}
		mustWriteFile(t, filepath.Join(spec.OutDir, "merge-report.json"), `{"owners":{"func_1":"accepted"}}`)
		return runner.ProcessResult{}, nil
	}
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}

	for _, method := range []string{"GitStatusPorcelain", "GitFetch", "GitCheckoutNewBranch", "GitPush", "GitCheckoutDetach"} {
		call := findCall(fake, method)
		if call == nil {
			t.Fatalf("%s not called", method)
		}
		if call.Strings[0] != "/merge-worktree" {
			t.Fatalf("%s repo root = %s, want /merge-worktree (Loop.Repo=/repo must not leak in)", method, call.Strings[0])
		}
	}
	importCall := findCall(fake, "ImportStats")
	if importCall == nil || importCall.Strings[1] != "/merge-worktree" {
		t.Fatalf("ImportStats repo root = %+v, want /merge-worktree", importCall)
	}
	prCall := findCall(fake, "GhPRCreate")
	if prCall == nil || prCall.PR.RepoRoot != "/merge-worktree" {
		t.Fatalf("GhPRCreate repo root = %+v, want /merge-worktree", prCall)
	}
}

// TestMergeRepoDefaultsToRepo checks that an unset Loop.MergeRepo (the
// common case, a single shared checkout) falls back to Loop.Repo -- the
// pre-existing tests in this file all rely on exactly this default.
func TestMergeRepoDefaultsToRepo(t *testing.T) {
	loop := &Loop{Repo: "/repo"}
	if got := loop.mergeRepo(); got != "/repo" {
		t.Fatalf("mergeRepo() = %s, want /repo", got)
	}
	loop.MergeRepo = "/other"
	if got := loop.mergeRepo(); got != "/other" {
		t.Fatalf("mergeRepo() = %s, want /other", got)
	}
}

// TestBaseRefDefaultsToOriginPRBase checks that an unset Loop.BaseRef
// defaults to "origin/<IntegrationBranch>" -- deliberately a remote-
// tracking ref, never the local branch itself (docs/FLEET_CONTROLLER.md
// sec 2) -- and that an explicit --base-ref overrides it.
func TestBaseRefDefaultsToOriginPRBase(t *testing.T) {
	loop := &Loop{IntegrationBranch: "master"}
	if got := loop.baseRef(); got != "origin/master" {
		t.Fatalf("baseRef() = %s, want origin/master", got)
	}
	loop.BaseRef = "origin/release"
	if got := loop.baseRef(); got != "origin/release" {
		t.Fatalf("baseRef() = %s, want origin/release", got)
	}
}

// --- merge repo dirty-check (docs/FLEET_CONTROLLER.md sec 2, "the merge
// repo must be clean") ---------------------------------------------------

// TestRunMergeAbortsWhenMergeRepoHasConflictingDirtyFiles checks that a
// tracked, modified file under one of the paths the merge step itself
// writes to (disasm/src/, COVERAGE.md, docs/regions/) blocks the merge
// entirely: no fetch, no branch, no commit -- the run is marked
// merge_blocked_dirty and an alert fires, instead of runMerge touching a
// shared merge repo that another session has mid-flight changes in.
func TestRunMergeAbortsWhenMergeRepoHasConflictingDirtyFiles(t *testing.T) {
	fake := &runner.Fake{
		InspectResults:           map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}},
		GitStatusPorcelainResult: " M disasm/src/x.c\n",
	}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)
	notifier := &fakeNotifier{}
	loop.Notifiers = []Notifier{notifier}
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.Status != fleetstate.StatusMergeBlockedDirty {
		t.Fatalf("status = %s, want merge_blocked_dirty", rec.Status)
	}
	if !strings.Contains(rec.Note, "disasm/src/x.c") {
		t.Fatalf("note = %q, want it to name the conflicting path", rec.Note)
	}
	for _, method := range []string{"GitFetch", "GitCheckoutNewBranch", "Merge", "GitPush"} {
		if findCall(fake, method) != nil {
			t.Fatalf("%s must not run once the merge repo is found dirty", method)
		}
	}
	if len(notifier.calls) != 1 {
		t.Fatalf("notifier calls = %d, want 1 (merge_blocked_dirty)", len(notifier.calls))
	}
}

// TestRunMergeToleratesUnrelatedDirtyFiles checks that modifications
// outside disasm/src/ and docs/regions/ (e.g. another session's own
// uncommitted edits to disasm/Makefile and tools/try_pragma_compare.py) --
// and any untracked file, anywhere -- do not block the merge.
func TestRunMergeToleratesUnrelatedDirtyFiles(t *testing.T) {
	fake := &runner.Fake{
		InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}},
		GitStatusPorcelainResult: " M disasm/Makefile\n" +
			" M tools/try_pragma_compare.py\n" +
			"?? disasm/src/scratch.c\n",
	}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)
	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		mustWriteFile(t, filepath.Join(spec.OutDir, "merge-report.json"), `{"owners":{"func_1":"accepted","func_2":"accepted"}}`)
		return runner.ProcessResult{}, nil
	}
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.Status == fleetstate.StatusMergeBlockedDirty {
		t.Fatalf("status = %s, unrelated dirty files must not block the merge", rec.Status)
	}
	if findCall(fake, "GitFetch") == nil || findCall(fake, "GitCheckoutNewBranch") == nil {
		t.Fatal("the merge should have proceeded past the dirty check")
	}
}

// TestRunMergeResetsCoverageMdBeforeDirtyCheck checks that runMerge discards
// COVERAGE.md's uncommitted state -- `git reset -q -- COVERAGE.md` then
// `git checkout -- COVERAGE.md` -- before running `git status --porcelain`,
// matching the observed failure: .githooks/pre-commit.d/10-coverage.sh
// regenerates and stages COVERAGE.md on every commit, so a prior
// `git commit --only <file>` in the merge repo routinely leaves a fresh,
// uncommitted COVERAGE.md behind that must never be mistaken for another
// session's conflicting dirt.
func TestRunMergeResetsCoverageMdBeforeDirtyCheck(t *testing.T) {
	fake := &runner.Fake{
		InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}},
	}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)
	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		mustWriteFile(t, filepath.Join(spec.OutDir, "merge-report.json"), `{"owners":{}}`)
		return runner.ProcessResult{}, nil
	}
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}

	seq := methodSequence(fake)
	idx := func(method string) int {
		for i, m := range seq {
			if m == method {
				return i
			}
		}
		return -1
	}
	resetIdx, checkoutIdx, statusIdx := idx("GitResetPath"), idx("GitCheckoutPath"), idx("GitStatusPorcelain")
	if resetIdx == -1 || checkoutIdx == -1 || statusIdx == -1 {
		t.Fatalf("expected GitResetPath, GitCheckoutPath, and GitStatusPorcelain to all run; sequence=%v", seq)
	}
	if resetIdx > statusIdx || checkoutIdx > statusIdx {
		t.Fatalf("COVERAGE.md reset/checkout must precede the dirty check; sequence=%v", seq)
	}
	if call := findCall(fake, "GitResetPath"); call == nil || call.Strings[1] != "COVERAGE.md" {
		t.Fatalf("GitResetPath call = %+v, want its path arg to be COVERAGE.md", call)
	}
	if call := findCall(fake, "GitCheckoutPath"); call == nil || call.Strings[1] != "COVERAGE.md" {
		t.Fatalf("GitCheckoutPath call = %+v, want its path arg to be COVERAGE.md", call)
	}
}

// TestRunMergeToleratesCoverageMdOnlyDirt checks that a tracked modification
// to COVERAGE.md alone -- once the repo's regenerate-on-commit hook has
// left one behind -- never blocks the merge: COVERAGE.md is no longer a
// conflicting path at all (touchesMergePaths), on top of being reset
// outright before the check runs.
func TestRunMergeToleratesCoverageMdOnlyDirt(t *testing.T) {
	fake := &runner.Fake{
		InspectResults:           map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}},
		GitStatusPorcelainResult: " M COVERAGE.md\n",
	}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)
	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		mustWriteFile(t, filepath.Join(spec.OutDir, "merge-report.json"), `{"owners":{"func_1":"accepted","func_2":"accepted"}}`)
		return runner.ProcessResult{}, nil
	}
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.Status == fleetstate.StatusMergeBlockedDirty {
		t.Fatalf("status = %s, COVERAGE.md-only dirt must not block the merge", rec.Status)
	}
	if findCall(fake, "GitFetch") == nil || findCall(fake, "GitCheckoutNewBranch") == nil {
		t.Fatal("the merge should have proceeded past the dirty check")
	}
}

// TestBlockedMergeRunRetriedAndRecoversWhenClean checks the fix for the
// observed cycle bug end to end: a run blocked merge_blocked_dirty is
// re-attempted at the top of the very next RunOnce pass (retryBlockedMergeRuns),
// with no restart and no operator action beyond cleaning up the conflicting
// path -- and MergeBlockedRetries tracks how many attempts were made.
func TestBlockedMergeRunRetriedAndRecoversWhenClean(t *testing.T) {
	fake := &runner.Fake{
		InspectResults:           map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}},
		GitStatusPorcelainResult: " M disasm/src/x.c\n",
	}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)
	notifier := &fakeNotifier{}
	loop.Notifiers = []Notifier{notifier}
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.Status != fleetstate.StatusMergeBlockedDirty {
		t.Fatalf("status = %s, want merge_blocked_dirty", rec.Status)
	}
	if rec.MergeBlockedRetries != 0 {
		t.Fatalf("MergeBlockedRetries = %d, want 0 before any retry pass has run", rec.MergeBlockedRetries)
	}

	// An operator (or this pass's own COVERAGE.md reset, for a real
	// conflict it would be a human) cleans up the conflicting path; drive
	// one more pass and expect retryBlockedMergeRuns to pick this run back
	// up with no InspectContainer/exit involved at all.
	fake.GitStatusPorcelainResult = ""
	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		mustWriteFile(t, filepath.Join(spec.OutDir, "merge-report.json"), `{"owners":{"func_1":"accepted","func_2":"accepted"}}`)
		return runner.ProcessResult{}, nil
	}
	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.Status == fleetstate.StatusMergeBlockedDirty {
		t.Fatalf("status = %s, retry against a clean repo should have unblocked the run", rec.Status)
	}
	if rec.MergeBlockedRetries != 1 {
		t.Fatalf("MergeBlockedRetries = %d, want 1", rec.MergeBlockedRetries)
	}
	if findCall(fake, "GitFetch") == nil {
		t.Fatal("the retry should have proceeded past the dirty check once clean")
	}
	if len(notifier.calls) != 1 {
		t.Fatalf("notifier calls = %d, want exactly 1 (the initial block; the recovered retry must not alert again)", len(notifier.calls))
	}
}

// TestBlockedMergeRunStillBlockedIsRetriedAndReAlerted checks that a run
// still dirty on retry stays merge_blocked_dirty, keeps counting attempts,
// and is left exactly as-is for an operator -- no fetch/branch/commit --
// same as the very first block.
func TestBlockedMergeRunStillBlockedIsRetriedAndReAlerted(t *testing.T) {
	fake := &runner.Fake{
		InspectResults:           map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}},
		GitStatusPorcelainResult: " M disasm/src/x.c\n",
	}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"completed"}`)
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.Status != fleetstate.StatusMergeBlockedDirty {
		t.Fatalf("status = %s, want merge_blocked_dirty (still dirty on retry)", rec.Status)
	}
	if rec.MergeBlockedRetries != 1 {
		t.Fatalf("MergeBlockedRetries = %d, want 1 after one retry pass", rec.MergeBlockedRetries)
	}
	for _, method := range []string{"GitFetch", "GitCheckoutNewBranch", "Merge", "GitPush"} {
		if findCall(fake, method) != nil {
			t.Fatalf("%s must not run while the merge repo is still dirty", method)
		}
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
