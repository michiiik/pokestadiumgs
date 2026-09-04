package control

import (
	"context"
	"path/filepath"
	"testing"
	"time"

	"fleetctl/internal/agentspec"
	"fleetctl/internal/fleetstate"
	"fleetctl/internal/runner"
)

// TestReassignmentLaunchesOnCooldownRunUnderAnotherAgent is the core of
// sec 12: kimi is on cooldown, codex is idle and in the plan's roster --
// the kimi-assigned partition must launch anyway, under codex, instead of
// sitting queued.
func TestReassignmentLaunchesOnCooldownRunUnderAnotherAgent(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	loop.Agents = []agentspec.Spec{
		{Agent: "kimi", Model: "kimi-code/k3"},
		{Agent: "codex", Model: "gpt-5.6-luna"},
	}
	loop.State.Cooldowns["kimi"] = testNow.Add(time.Hour)

	loop.State.Runs["a"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{ID: "a", File: "disasm/src/a.c", Owners: []string{"f1"}, Agent: "kimi"}, Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"a"}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}

	rec := loop.State.Runs["a"]
	if rec.Status != fleetstate.StatusRunning {
		t.Fatalf("status = %s, want running (reassigned to codex instead of waiting)", rec.Status)
	}
	if rec.Spec.Agent != "codex" || rec.Spec.Model != "gpt-5.6-luna" {
		t.Fatalf("spec agent/model = %s/%s, want codex/gpt-5.6-luna", rec.Spec.Agent, rec.Spec.Model)
	}
	if rec.Note == "" {
		t.Fatal("a reassignment must be logged in the run's own note")
	}
	call := findCall(fake, "LaunchContainer")
	if call == nil || call.Launch.Agent != "codex" {
		t.Fatalf("LaunchContainer call = %+v, want agent=codex", call)
	}
}

// TestReassignmentFallsBackToWaitingWithSingleAgentRoster checks that a
// plan with only one agent configured (or none -- Loop.Agents unset)
// behaves exactly as before sec 12: no other agent to reassign to, so the
// cooling-down run just waits, wait_reason "cooldown".
func TestReassignmentFallsBackToWaitingWithSingleAgentRoster(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	loop.Agents = []agentspec.Spec{{Agent: "kimi", Model: "kimi-code/k3"}}
	loop.State.Cooldowns["kimi"] = testNow.Add(time.Hour)

	loop.State.Runs["a"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{ID: "a", File: "disasm/src/a.c", Owners: []string{"f1"}, Agent: "kimi"}, Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"a"}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	rec := loop.State.Runs["a"]
	if rec.Status != fleetstate.StatusQueued || rec.WaitReason != "cooldown" {
		t.Fatalf("status=%s wait_reason=%q, want queued/cooldown (nothing else to reassign to)", rec.Status, rec.WaitReason)
	}
}

// TestReassignmentSkipsCandidateAtItsOwnConcurrencyCap checks that a
// roster candidate already at its own --agent-concurrency cap is not
// picked -- the cooling-down run keeps waiting instead.
func TestReassignmentSkipsCandidateAtItsOwnConcurrencyCap(t *testing.T) {
	fake := &runner.Fake{
		InspectResults: map[string][]runner.InspectResult{"already-running-cid": {{Found: true, Running: true}}},
	}
	loop, outDir := newTestLoop(t, fake)
	loop.Agents = []agentspec.Spec{
		{Agent: "kimi", Model: "kimi-code/k3"},
		{Agent: "codex", Model: "gpt-5.6-luna"},
	}
	loop.AgentConcurrency = map[string]int{"codex": 1}
	loop.State.Cooldowns["kimi"] = testNow.Add(time.Hour)
	loop.State.Runs["already-running"] = runningRec("already-running", "already-running-cid", outDir, "codex")

	loop.State.Runs["a"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{ID: "a", File: "disasm/src/a.c", Owners: []string{"f1"}, Agent: "kimi"}, Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"a"}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	rec := loop.State.Runs["a"]
	if rec.Status != fleetstate.StatusQueued || rec.WaitReason != "cooldown" {
		t.Fatalf("status=%s wait_reason=%q, want queued/cooldown (codex is already at its cap)", rec.Status, rec.WaitReason)
	}
}

// TestReassignmentPrefersJustReopenedWindow exercises "when the window
// reopens, prefer the cooled-down agent for the next launches to rebalance"
// (sec 12): kimi's own cooldown lapsed (window reopened, never relaunched
// since), codex is on cooldown now -- codex's queued partition must be
// reassigned to kimi, not some other roster agent.
func TestReassignmentPrefersJustReopenedWindow(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	loop.Agents = []agentspec.Spec{
		{Agent: "codex", Model: "gpt-5.6-luna"},
		{Agent: "kimi", Model: "kimi-code/k3"},
		{Agent: "alibaba", Model: "qwen3.7-max"},
	}
	// codex is on cooldown right now.
	loop.State.Cooldowns["codex"] = testNow.Add(time.Hour)
	// kimi was exhausted in the past but its cooldown has already lapsed,
	// and it has not been relaunched since (WindowStart still zero) -- its
	// window has just reopened.
	loop.State.WindowState = map[string]*fleetstate.AgentWindowState{
		"kimi": {LastExhausted: testNow.Add(-6 * time.Hour)},
	}

	loop.State.Runs["a"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{ID: "a", File: "disasm/src/a.c", Owners: []string{"f1"}, Agent: "codex"}, Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"a"}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	rec := loop.State.Runs["a"]
	if rec.Spec.Agent != "kimi" {
		t.Fatalf("reassigned to %s, want kimi (its window just reopened, sec 12 rebalance)", rec.Spec.Agent)
	}
}

// TestRecordWindowStartAndExhaustion exercises the window bookkeeping
// directly: a launch stamps WindowStart once (not on a second launch), and
// a generator_exhausted exit zeroes it again while stamping LastExhausted.
func TestRecordWindowStartAndExhaustion(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)

	loop.recordWindowStart("kimi", testNow)
	ws := loop.State.WindowState["kimi"]
	if ws == nil || !ws.WindowStart.Equal(testNow) {
		t.Fatalf("window state = %+v, want WindowStart=%v", ws, testNow)
	}
	later := testNow.Add(time.Hour)
	loop.recordWindowStart("kimi", later) // must not overwrite an already-stamped window start.
	if !loop.State.WindowState["kimi"].WindowStart.Equal(testNow) {
		t.Fatalf("WindowStart was overwritten: %v", loop.State.WindowState["kimi"].WindowStart)
	}

	loop.recordWindowExhausted("kimi", later)
	ws = loop.State.WindowState["kimi"]
	if !ws.WindowStart.IsZero() {
		t.Fatalf("WindowStart should be zeroed on exhaustion, got %v", ws.WindowStart)
	}
	if !ws.LastExhausted.Equal(later) {
		t.Fatalf("LastExhausted = %v, want %v", ws.LastExhausted, later)
	}
}

// TestPermuterAgentNeverGetsReassignedToOrCooledDown checks the "never
// subject to cooldown" guarantee (sec 13) end to end: a permuter-lane
// partition launches even though State.Cooldowns somehow carries an entry
// for it, and the roster never offers permuterAgent as a reassignment
// target for another agent's cooling-down run.
func TestPermuterAgentNeverGetsReassignedToOrCooledDown(t *testing.T) {
	fake := &runner.Fake{}
	loop, dir := newTestLoop(t, fake)
	loop.RunsDir = dir
	loop.Agents = []agentspec.Spec{{Agent: "codex", Model: "m"}, {Agent: permuterAgent}}
	// Defensive: even if something set a cooldown for "permuter", it must
	// never block a permuter-lane launch.
	loop.State.Cooldowns[permuterAgent] = testNow.Add(time.Hour)

	mustWriteFile(t, tiePoolStorePath(dir, "disasm/src/x.c"), `{"func_1":{"source":"disasm/src/x.c","body":"b"}}`)

	loop.State.Runs["x-permuter"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "x-permuter", File: "disasm/src/x.c", Owners: []string{"func_1"},
			Agent: permuterAgent, Mode: "permuter-only",
		},
		Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"x-permuter"}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	rec := loop.State.Runs["x-permuter"]
	if rec.Status != fleetstate.StatusRunning {
		t.Fatalf("status = %s, want running (permuter must never be treated as on cooldown)", rec.Status)
	}

	// Also: the roster excludes permuterAgent as a reassignment target.
	alt, ok := loop.reassignAgent("codex", testNow, map[string]int{})
	if ok {
		t.Fatalf("reassignAgent must never offer permuterAgent as a target, got %+v", alt)
	}
}

// TestSiblingModelUnderSameAgentIsNotBlockedByAnotherModelsCooldown
// reproduces the real incident end to end -- through the actual write path
// (a genuine luna exhaustion via RunOnce, not a hand-set cooldown key), so
// this fails on pre-fix code for the right reason (the bare-agent write
// really did block spark), not by accident.
//
// gpt-5.6-luna and gpt-5.3-codex-spark are both AGENT=codex, but confirmed
// live to draw from separate usage-limit pools -- luna genuinely exhausted
// (a multi-day cooldown) while spark succeeded immediately after, on the
// same auth. A bare-agent cooldown key made luna's exhaustion block spark
// too, even though spark had quota to spare.
func TestSiblingModelUnderSameAgentIsNotBlockedByAnotherModelsCooldown(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{
		"luna-cid": {{Found: true, Running: false, ExitCode: 3}},
	}}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"generator_exhausted"}`)
	loop.CooldownDefaults = map[string]time.Duration{"codex": 72 * time.Hour}

	// luna exhausts for real, through the same code path that wrote the
	// bare "codex" key in the actual incident.
	loop.State.Runs["luna-run"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "luna-run", File: "disasm/src/x.c", Owners: []string{"func_1"},
			Agent: "codex", Model: "gpt-5.6-luna",
		},
		Status: fleetstate.StatusRunning, ContainerID: "luna-cid", OutDir: outDir,
	}
	// spark is queued under the same agent, a different model, never run yet.
	loop.State.Runs["spark-run"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "spark-run", File: "disasm/src/a.c", Owners: []string{"f1"},
			Agent: "codex", Model: "gpt-5.3-codex-spark",
		},
		Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"spark-run"}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}

	rec := loop.State.Runs["spark-run"]
	if rec.Status != fleetstate.StatusRunning {
		t.Fatalf("status = %s, want running (spark has its own quota, luna's exhaustion must not block it)", rec.Status)
	}
	if rec.Spec.Model != "gpt-5.3-codex-spark" {
		t.Fatalf("spec model = %s, want gpt-5.3-codex-spark (must launch as itself, not a sec-12 reassignment)", rec.Spec.Model)
	}
}

// TestExhaustedModelStillBlocksItselfAndOnlyItself is the write-side half
// of the same fix: an exhausted run must still requeue and wait, and a
// second queued run under the SAME agent+model must still be blocked by
// that cooldown (the fix narrows the key, it does not remove enforcement).
func TestExhaustedModelStillBlocksItselfAndOnlyItself(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{
		"cid": {{Found: true, Running: false, ExitCode: 3}},
	}}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"generator_exhausted"}`)

	rec := &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "x-p0", File: "disasm/src/x.c", Owners: []string{"func_1"},
			Agent: "codex", Model: "gpt-5.6-luna",
		},
		Status: fleetstate.StatusRunning, ContainerID: "cid", OutDir: outDir,
	}
	loop.State.Runs["x-p0"] = rec
	loop.CooldownDefaults = map[string]time.Duration{"codex": 5 * time.Hour}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}

	until, ok := loop.State.CooldownUntil("codex:gpt-5.6-luna")
	if !ok || !until.Equal(testNow.Add(5*time.Hour)) {
		t.Fatalf("cooldown = %v, ok=%v", until, ok)
	}

	// A second, later run under the identical agent+model must still be
	// held back by that same cooldown -- the fix must not have accidentally
	// stopped enforcing it altogether.
	loop.State.Runs["x-p1"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "x-p1", File: "disasm/src/x.c", Owners: []string{"func_2"},
			Agent: "codex", Model: "gpt-5.6-luna",
		},
		Status: fleetstate.StatusQueued,
	}
	loop.State.Queue = []string{"x-p1"}
	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if loop.State.Runs["x-p1"].Status != fleetstate.StatusQueued {
		t.Fatalf("x-p1 status = %s, want still queued (blocked by its own model's cooldown)", loop.State.Runs["x-p1"].Status)
	}
}

// TestGeneratorExhaustionStopsSiblingRunsUnderTheSameAgentModel reproduces
// the scenario observed live: five concurrent spark containers each
// independently exhausted within seconds of each other, each paying its
// own full failure-detection wall-clock cost, when the first failure
// already told fleetctl everything the rest needed to know. A sibling run
// under the identical agent+model should be stopped and requeued the
// moment the first one's generator_exhausted confirms the rate limit,
// rather than left to fail on its own.
func TestGeneratorExhaustionStopsSiblingRunsUnderTheSameAgentModel(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{
		"exhausted-cid": {{Found: true, Running: false, ExitCode: 3}},
		// Still genuinely running as far as pollRunning's own exit-check is
		// concerned -- an id with no InspectResults entry looks "vanished"
		// to that unrelated path, which would confound this test with the
		// pre-existing vanish-handling logic instead of isolating
		// stopSiblingRuns.
		"sibling-same-cid":        {{Found: true, Running: true}},
		"sibling-other-model-cid": {{Found: true, Running: true}},
	}}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"generator_exhausted"}`)
	loop.CooldownDefaults = map[string]time.Duration{"codex": time.Hour}

	loop.State.Runs["exhausted"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "exhausted", File: "disasm/src/x.c", Owners: []string{"func_1"},
			Agent: "codex", Model: "gpt-5.3-codex-spark",
		},
		Status: fleetstate.StatusRunning, ContainerID: "exhausted-cid", OutDir: outDir,
	}
	// Same agent+model, still mid-flight: must be stopped.
	loop.State.Runs["sibling-same"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "sibling-same", File: "disasm/src/y.c", Owners: []string{"func_2"},
			Agent: "codex", Model: "gpt-5.3-codex-spark",
		},
		Status: fleetstate.StatusRunning, ContainerID: "sibling-same-cid",
	}
	// Same agent, DIFFERENT model: must be left alone (that is luna/spark's
	// whole point -- separate quota pools).
	loop.State.Runs["sibling-other-model"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "sibling-other-model", File: "disasm/src/z.c", Owners: []string{"func_3"},
			Agent: "codex", Model: "gpt-5.6-luna",
		},
		Status: fleetstate.StatusRunning, ContainerID: "sibling-other-model-cid",
	}
	// Same agent+model, but already past StatusRunning: must be left alone.
	loop.State.Runs["sibling-merging"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "sibling-merging", File: "disasm/src/w.c", Owners: []string{"func_4"},
			Agent: "codex", Model: "gpt-5.3-codex-spark",
		},
		Status: fleetstate.StatusMerging, ContainerID: "sibling-merging-cid",
	}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}

	same := loop.State.Runs["sibling-same"]
	if same.Status != fleetstate.StatusRequeued {
		t.Fatalf("sibling-same status = %s, want requeued", same.Status)
	}
	if same.Spec.Attempt != 1 {
		t.Fatalf("sibling-same attempt = %d, want 1 (requeueResume must have run)", same.Spec.Attempt)
	}
	if same.Note == "" {
		t.Fatal("sibling-same must record why it was stopped")
	}
	stopCall := findCall(fake, "StopContainer")
	if stopCall == nil || stopCall.Strings[0] != "sibling-same-cid" {
		t.Fatalf("StopContainer call = %+v, want sibling-same-cid", stopCall)
	}
	// Exactly one StopContainer call: the other-model and merging siblings
	// must not have been touched.
	n := 0
	for _, c := range fake.Calls {
		if c.Method == "StopContainer" {
			n++
		}
	}
	if n != 1 {
		t.Fatalf("StopContainer called %d times, want exactly 1", n)
	}

	other := loop.State.Runs["sibling-other-model"]
	if other.Status != fleetstate.StatusRunning {
		t.Fatalf("sibling-other-model status = %s, want still running (separate quota pool)", other.Status)
	}
	merging := loop.State.Runs["sibling-merging"]
	if merging.Status != fleetstate.StatusMerging {
		t.Fatalf("sibling-merging status = %s, want untouched", merging.Status)
	}
}

// TestGeneratorExhaustionWithNoSiblingsIsANoOp guards against a panic or
// spurious StopContainer call when the exhausted run has no siblings at
// all -- the common case.
func TestGeneratorExhaustionWithNoSiblingsIsANoOp(t *testing.T) {
	fake := &runner.Fake{InspectResults: map[string][]runner.InspectResult{
		"cid": {{Found: true, Running: false, ExitCode: 3}},
	}}
	loop, dir := newTestLoop(t, fake)
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"stopped_reason":"generator_exhausted"}`)
	loop.CooldownDefaults = map[string]time.Duration{"codex": time.Hour}

	loop.State.Runs["solo"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{
			ID: "solo", File: "disasm/src/x.c", Owners: []string{"func_1"},
			Agent: "codex", Model: "gpt-5.3-codex-spark",
		},
		Status: fleetstate.StatusRunning, ContainerID: "cid", OutDir: outDir,
	}

	if _, err := loop.RunOnce(context.Background()); err != nil {
		t.Fatal(err)
	}
	if findCall(fake, "StopContainer") != nil {
		t.Fatal("no sibling exists; StopContainer must not be called")
	}
}

// TestReassignmentSkipsRosterCandidateStillOnItsOwnCompositeCooldown
// reproduces a real incident live on 2026-09-04: gpt-5.3-codex-spark was
// deep in its own composite-keyed cooldown (codex:gpt-5.3-codex-spark), but
// eligibleForReassignment only ever checked the bare "codex" key -- which a
// real per-model exhaustion (handleExit) never writes -- so it always read
// "not on cooldown" and reassignAgent kept sending queued runs right back
// into codex, over and over, each one re-exhausting within moments and
// pushing codex's own cooldown a little further out every time, while
// gemini and alibaba (both genuinely idle, with real spare capacity) never
// got a single one of these runs.
func TestReassignmentSkipsRosterCandidateStillOnItsOwnCompositeCooldown(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	loop.Agents = []agentspec.Spec{
		{Agent: "codex", Model: "gpt-5.3-codex-spark"},
		{Agent: "claude", Model: "sonnet"},
		{Agent: "gemini", Model: "gemini-3.8-flash-medium"},
		{Agent: "alibaba", Model: "qwen3.6-flash"},
	}
	// Only the fine-grained key is set, exactly as a real generator_exhausted
	// exit writes it (control.go's handleExit) -- no bare "codex" entry.
	loop.State.Cooldowns["codex:gpt-5.3-codex-spark"] = testNow.Add(time.Hour)

	alt, ok := loop.reassignAgent("claude", testNow, map[string]int{})
	if !ok {
		t.Fatal("reassignAgent found no candidate, want gemini (genuinely idle)")
	}
	if alt.Agent == "codex" {
		t.Fatalf("reassigned to %s:%s, which is still on cooldown by its own composite key", alt.Agent, alt.Model)
	}
	if alt.Agent != "gemini" {
		t.Fatalf("reassigned to %s, want gemini (next idle roster entry after codex is correctly skipped)", alt.Agent)
	}
}

// TestReassignmentWindowPreferenceDoesNotOverrideARealCompositeCooldown
// covers the same bug in windowReopened's "prefer the just-reopened agent"
// fast path (sec 12): codex's bare-agent WindowState looks reopened (it was
// exhausted a while ago and never relaunched since), but its one roster
// model is still genuinely on cooldown by its own composite key -- that
// must not be read as "reopened", or this fast path would keep preferring
// codex over a real cooldown, same as the bare round-robin bug above. With
// no other roster agent to fall back to, the run is left queued instead of
// wrongly relaunched.
func TestReassignmentWindowPreferenceDoesNotOverrideARealCompositeCooldown(t *testing.T) {
	fake := &runner.Fake{}
	loop, _ := newTestLoop(t, fake)
	loop.Agents = []agentspec.Spec{
		{Agent: "codex", Model: "gpt-5.3-codex-spark"},
		{Agent: "claude", Model: "sonnet"},
	}
	loop.State.Cooldowns["codex:gpt-5.3-codex-spark"] = testNow.Add(time.Hour)
	loop.State.WindowState = map[string]*fleetstate.AgentWindowState{
		"codex": {LastExhausted: testNow.Add(-6 * time.Hour)},
	}

	alt, ok := loop.reassignAgent("claude", testNow, map[string]int{})
	if ok {
		t.Fatalf("reassignAgent picked %+v, want no candidate (codex's only roster model is still really on cooldown)", alt)
	}
}
