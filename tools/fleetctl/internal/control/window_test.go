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
