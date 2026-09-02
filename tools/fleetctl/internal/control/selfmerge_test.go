package control

import (
	"context"
	"fmt"
	"testing"
	"time"

	"fleetctl/internal/fleetstate"
	"fleetctl/internal/runner"
)

// fakeNotifier is a scriptable Notifier for alert/daily-summary tests --
// simpler than routing through runner.Fake's GhIssueComment/OsascriptNotify
// since Notifier is exactly the seam Loop.alert/maybeDailySummary program
// against.
type fakeNotifier struct {
	calls []struct{ title, body string }
}

func (f *fakeNotifier) Notify(_ context.Context, title, body string) error {
	f.calls = append(f.calls, struct{ title, body string }{title, body})
	return nil
}

func prOpenRec(id, prURL string, prNumber int) *fleetstate.RunRecord {
	return &fleetstate.RunRecord{
		Spec:     fleetstate.RunSpec{ID: id, File: "disasm/src/x.c", Owners: []string{"func_1"}, Agent: "codex"},
		Status:   fleetstate.StatusPROpen,
		PRURL:    prURL,
		PRNumber: prNumber,
	}
}

// --- self-merge on green -----------------------------------------------

func TestSelfMergeSuccessMergesAndFastForwards(t *testing.T) {
	fake := &runner.Fake{
		GhPRChecksResult:  runner.PRChecksResult{State: "SUCCESS"},
		GhPRViewResult:    "deadbeef",
		GitRevParseResult: "deadbeef",
	}
	loop, _ := newTestLoop(t, fake)
	rec := prOpenRec("x-p0", "https://github.com/o/r/pull/42", 42)
	loop.State.Runs["x-p0"] = rec

	if err := loop.pollPRs(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.Status != fleetstate.StatusMerged {
		t.Fatalf("status = %s, want merged", rec.Status)
	}
	if rec.MergedAt.IsZero() {
		t.Fatal("MergedAt not set")
	}
	if rec.MergeCommitSHA != "deadbeef" {
		t.Fatalf("merge commit sha = %q, want deadbeef", rec.MergeCommitSHA)
	}
	if loop.State.LastMergeAt.IsZero() {
		t.Fatal("State.LastMergeAt not set")
	}
	mergeCall := findCall(fake, "GhPRMerge")
	if mergeCall == nil || mergeCall.Strings[0] != "/repo" || mergeCall.Strings[1] != "42" {
		t.Fatalf("GhPRMerge call = %+v", mergeCall)
	}
	// The post-merge "fast-forward" is now just a fetch -- the merge repo's
	// local base branch is never checked out (docs/FLEET_CONTROLLER.md sec
	// 2); the merge commit sha comes from `gh pr view`, verified against a
	// rev-parse of --base-ref (default origin/<pr-base>).
	if findCall(fake, "GitFetch") == nil {
		t.Fatal("GitFetch (the post-merge fast-forward) was not called")
	}
	viewCall := findCall(fake, "GhPRView")
	if viewCall == nil || viewCall.Strings[0] != "/repo" || viewCall.Strings[1] != "42" {
		t.Fatalf("GhPRView call = %+v, want repo /repo, PR 42", viewCall)
	}
	revParseCall := findCall(fake, "GitRevParse")
	if revParseCall == nil || revParseCall.Strings[1] != "origin/master" {
		t.Fatalf("GitRevParse call = %+v, want ref origin/master", revParseCall)
	}
}

func TestSelfMergePendingLeavesRunUntouched(t *testing.T) {
	fake := &runner.Fake{GhPRChecksResult: runner.PRChecksResult{State: "PENDING"}}
	loop, _ := newTestLoop(t, fake)
	rec := prOpenRec("x-p0", "https://github.com/o/r/pull/1", 1)
	loop.State.Runs["x-p0"] = rec

	if err := loop.pollPRs(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.Status != fleetstate.StatusPROpen {
		t.Fatalf("status = %s, want pr_open (still pending)", rec.Status)
	}
	if findCall(fake, "GhPRMerge") != nil {
		t.Fatal("must not merge a still-pending PR")
	}
}

func TestSelfMergeFailureMarksGateFailedAndAlerts(t *testing.T) {
	fake := &runner.Fake{GhPRChecksResult: runner.PRChecksResult{State: "FAILURE"}}
	loop, _ := newTestLoop(t, fake)
	notifier := &fakeNotifier{}
	loop.Notifiers = []Notifier{notifier}
	rec := prOpenRec("x-p0", "https://github.com/o/r/pull/7", 7)
	loop.State.Runs["x-p0"] = rec

	if err := loop.pollPRs(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.Status != fleetstate.StatusGateFailed {
		t.Fatalf("status = %s, want gate_failed", rec.Status)
	}
	if findCall(fake, "GhPRMerge") != nil {
		t.Fatal("must not merge a failed gate")
	}
	if len(notifier.calls) != 1 {
		t.Fatalf("notifier calls = %d, want 1 (gate_failed)", len(notifier.calls))
	}
}

func TestAutoMergeDisabledSkipsPollPRsEntirely(t *testing.T) {
	fake := &runner.Fake{
		InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: false}}},
		GhPRURL:        "https://github.com/example/repo/pull/9",
	}
	loop, dir := newTestLoop(t, fake)
	loop.DisableAutoMerge = true
	outDir := dir + "/out"
	mustWriteFile(t, outDir+"/summary.json", `{"stopped_reason":"completed"}`)
	fake.MergeFunc = func(spec runner.MergeSpec) (runner.ProcessResult, error) {
		mustWriteFile(t, spec.OutDir+"/merge-report.json", `{"owners":{"func_1":"accepted","func_2":"rejected"}}`)
		return runner.ProcessResult{}, nil
	}
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.Status != fleetstate.StatusDone {
		t.Fatalf("status = %s, want done (auto-merge disabled leaves the old pre-self-merge behavior)", rec.Status)
	}
	if rec.PRURL == "" {
		t.Fatal("a PR should still have opened for the matched owner")
	}
	if findCall(fake, "GhPRChecks") != nil {
		t.Fatal("pollPRs must never run when auto-merge is disabled")
	}
}

func TestSelfMergeFastForwardFailureBlocksFurtherMergesUntilFixed(t *testing.T) {
	fake := &runner.Fake{
		GhPRChecksResult: runner.PRChecksResult{State: "SUCCESS"},
		GitFetchErr:      fmt.Errorf("network unreachable"),
	}
	loop, _ := newTestLoop(t, fake)
	notifier := &fakeNotifier{}
	loop.Notifiers = []Notifier{notifier}
	recA := prOpenRec("a-p0", "https://github.com/o/r/pull/1", 1)
	recB := prOpenRec("b-p0", "https://github.com/o/r/pull/2", 2)
	loop.State.Runs["a-p0"] = recA
	loop.State.Runs["b-p0"] = recB

	if err := loop.pollPRs(context.Background()); err != nil {
		t.Fatal(err)
	}
	if recA.Status != fleetstate.StatusMerged {
		t.Fatalf("a status = %s, want merged (gh pr merge itself succeeded before the ff)", recA.Status)
	}
	if !loop.State.MergeBlocked {
		t.Fatal("State.MergeBlocked should be set after a fast-forward failure")
	}
	if recB.Status != fleetstate.StatusPROpen {
		t.Fatalf("b status = %s, want still pr_open: merging must stop for the rest of this pass", recB.Status)
	}
	if len(notifier.calls) != 1 {
		t.Fatalf("notifier calls = %d, want 1 (ff_failed)", len(notifier.calls))
	}

	// Next pass: still broken -- no further merges attempted, and the
	// alert is rate-limited (same hour, same clock in this test).
	if err := loop.pollPRs(context.Background()); err != nil {
		t.Fatal(err)
	}
	mergeCalls := 0
	for _, c := range fake.Calls {
		if c.Method == "GhPRMerge" {
			mergeCalls++
		}
	}
	if mergeCalls != 1 {
		t.Fatalf("GhPRMerge calls = %d, want 1: b must never be attempted while blocked", mergeCalls)
	}
	if len(notifier.calls) != 1 {
		t.Fatalf("notifier calls after second blocked pass = %d, want still 1 (rate-limited)", len(notifier.calls))
	}

	// Fix the underlying problem -- the next pass's retry recovers and
	// resumes merging.
	fake.GitFetchErr = nil
	if err := loop.pollPRs(context.Background()); err != nil {
		t.Fatal(err)
	}
	if loop.State.MergeBlocked {
		t.Fatal("MergeBlocked should clear once the retry succeeds")
	}
	if recB.Status != fleetstate.StatusMerged {
		t.Fatalf("b status = %s, want merged once unblocked", recB.Status)
	}
}

// --- alert rate limiting -------------------------------------------------

func TestAlertRateLimitedPerHourPerKey(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	notifier := &fakeNotifier{}
	loop.Notifiers = []Notifier{notifier}

	loop.alert(context.Background(), "gate_failed", "run-a", "t1", "b1")
	loop.alert(context.Background(), "gate_failed", "run-a", "t2", "b2")
	if len(notifier.calls) != 1 {
		t.Fatalf("calls = %d, want 1 (second call rate-limited)", len(notifier.calls))
	}
	// A different key is a different rate-limit bucket.
	loop.alert(context.Background(), "gate_failed", "run-b", "t3", "b3")
	if len(notifier.calls) != 2 {
		t.Fatalf("calls = %d, want 2 (different key = different bucket)", len(notifier.calls))
	}
}

// --- no-progress stall detection -----------------------------------------

func TestNoProgressStallAlertsAfterStallAfter(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{"cid": {{Found: true, Running: true}}}}
	loop, dir := newTestLoop(t, fake)
	notifier := &fakeNotifier{}
	loop.Notifiers = []Notifier{notifier}
	loop.StallAfter = time.Hour

	outDir := dir + "/out"
	mustWriteFile(t, outDir+"/state.json", `{"func_1":{"best_similarity":0.5}}`)
	rec := runningRec("x-p0", "cid", outDir, "codex")
	loop.State.Runs["x-p0"] = rec

	now := testNow
	loop.Now = func() time.Time { return now }

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.BestSimilarity != 0.5 {
		t.Fatalf("best similarity = %v, want 0.5 (first observation)", rec.BestSimilarity)
	}
	if len(notifier.calls) != 0 {
		t.Fatal("must not alert on the very first observation")
	}

	// Advance past stall-after with no improvement.
	now = testNow.Add(2 * time.Hour)
	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if len(notifier.calls) != 1 {
		t.Fatalf("calls = %d, want 1 (stalled)", len(notifier.calls))
	}

	// Similarity improves -- BestSimilarityAt resets, no new alert even
	// much later.
	mustWriteFile(t, outDir+"/state.json", `{"func_1":{"best_similarity":0.9}}`)
	now = testNow.Add(3 * time.Hour)
	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if rec.BestSimilarity != 0.9 {
		t.Fatalf("best similarity = %v, want 0.9 after improvement", rec.BestSimilarity)
	}
}

// --- stale-image awareness / --src-overlay -------------------------------

func TestLaunchWarnsOnStaleImageUnlessSrcOverlaySet(t *testing.T) {
	fake := &runner.Fake{DockerImageIDResult: "sha256:old", DockerImageIDCreated: testNow.Add(-2 * time.Hour)}
	loop, _ := newTestLoop(t, fake)
	loop.State.LastMergeAt = testNow.Add(-time.Hour) // merge landed after the image was built

	spec := fleetstate.RunSpec{ID: "x-p0", File: "disasm/src/x.c", Owners: []string{"func_1"}, Agent: "codex"}
	loop.State.Runs[spec.ID] = &fleetstate.RunRecord{Spec: spec, Status: fleetstate.StatusQueued}
	loop.State.Queue = []string{spec.ID}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if findCall(fake, "DockerImageID") == nil {
		t.Fatal("DockerImageID should have been queried (no --src-overlay)")
	}
	if loop.State.Runs["x-p0"].ImageID != "sha256:old" {
		t.Fatalf("ImageID = %q, want sha256:old", loop.State.Runs["x-p0"].ImageID)
	}
}

// --- daily summary --------------------------------------------------------

func TestDailySummaryFiresOncePerUTCDayAtConfiguredHour(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	notifier := &fakeNotifier{}
	loop.DailySummaryNotifier = notifier
	loop.DailySummaryHourUTC = 9

	// Wrong hour: no summary.
	now := time.Date(2026, 9, 2, 8, 0, 0, 0, time.UTC)
	loop.Now = func() time.Time { return now }
	loop.maybeDailySummary(context.Background())
	if len(notifier.calls) != 0 {
		t.Fatalf("calls = %d, want 0 (wrong hour)", len(notifier.calls))
	}

	// Right hour: fires once.
	now = time.Date(2026, 9, 2, 9, 0, 0, 0, time.UTC)
	loop.maybeDailySummary(context.Background())
	if len(notifier.calls) != 1 {
		t.Fatalf("calls = %d, want 1", len(notifier.calls))
	}

	// Same hour, called again (e.g. two poll passes within the hour): no
	// second post the same UTC day.
	loop.maybeDailySummary(context.Background())
	if len(notifier.calls) != 1 {
		t.Fatalf("calls = %d, want still 1 (same day)", len(notifier.calls))
	}

	// Next day, same hour: fires again.
	now = now.Add(24 * time.Hour)
	loop.maybeDailySummary(context.Background())
	if len(notifier.calls) != 2 {
		t.Fatalf("calls = %d, want 2 (a new UTC day)", len(notifier.calls))
	}
}

func TestLaunchSkipsImageCheckAndForwardsSrcOverlay(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	loop.SrcOverlay = "/overlay/src"

	spec := fleetstate.RunSpec{ID: "x-p0", File: "disasm/src/x.c", Owners: []string{"func_1"}, Agent: "codex"}
	loop.State.Runs[spec.ID] = &fleetstate.RunRecord{Spec: spec, Status: fleetstate.StatusQueued}
	loop.State.Queue = []string{spec.ID}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if findCall(fake, "DockerImageID") != nil {
		t.Fatal("DockerImageID must not be queried under --src-overlay")
	}
	launchCall := findCall(fake, "LaunchContainer")
	if launchCall == nil || launchCall.Launch.SrcOverlay != "/overlay/src" {
		t.Fatalf("launch spec = %+v, want SrcOverlay=/overlay/src", launchCall)
	}
}
