package control

import (
	"path/filepath"
	"testing"
	"time"

	"fleetctl/internal/fleetstate"
)

func metricsFor(t *testing.T, metrics []AgentMetrics, agent string) AgentMetrics {
	t.Helper()
	for _, m := range metrics {
		if m.Agent == agent {
			return m
		}
	}
	t.Fatalf("no metrics row for agent %q in %+v", agent, metrics)
	return AgentMetrics{}
}

// TestBuildMetricsComputesThroughput exercises the core computation (docs
// sec 11): two owners in one run's <out>/state.json, one accepted after 5
// iterations, one still in_progress after 3 -- runs=1, iterations=8 (5+3),
// accepts=1, mean-iterations-to-accept=5, plus wall-hour/quota-window
// normalization from <out>/summary.json's wall_seconds and the persisted
// plan's --cooldown (no --window entry, so kimi's own cooldown -- 5h -- is
// used as its quota window, matching the task's "e.g. kimi=5h" example).
func TestBuildMetricsComputesThroughput(t *testing.T) {
	dir := t.TempDir()
	outDir := filepath.Join(dir, "out")
	mustWriteFile(t, filepath.Join(outDir, "state.json"), `{
		"func_1": {"status": "accepted", "iterations": 5},
		"func_2": {"status": "in_progress", "iterations": 3}
	}`)
	mustWriteFile(t, filepath.Join(outDir, "summary.json"), `{"wall_seconds": 3600}`)

	state := fleetstate.New()
	state.Runs["x-p0"] = &fleetstate.RunRecord{
		Spec:   fleetstate.RunSpec{ID: "x-p0", File: "disasm/src/x.c", Owners: []string{"func_1", "func_2"}, Agent: "kimi"},
		Status: fleetstate.StatusDone,
		OutDir: outDir,
	}
	state.PlanJSON = []byte(`{"cooldowns":{"kimi":"5h0m0s"},"queue":[]}`)

	now := time.Date(2026, 9, 2, 12, 0, 0, 0, time.UTC)
	got := metricsFor(t, BuildMetrics(state, now), "kimi")

	if got.Runs != 1 {
		t.Fatalf("runs = %d, want 1", got.Runs)
	}
	if got.Iterations != 8 {
		t.Fatalf("iterations = %d, want 8", got.Iterations)
	}
	if got.Accepts != 1 {
		t.Fatalf("accepts = %d, want 1", got.Accepts)
	}
	if got.WallHours != 1 {
		t.Fatalf("wall_hours = %v, want 1 (3600s)", got.WallHours)
	}
	if got.AcceptsPerWallHour != 1 {
		t.Fatalf("accepts_per_wall_hour = %v, want 1", got.AcceptsPerWallHour)
	}
	if got.QuotaWindow != "5h0m0s" {
		t.Fatalf("quota_window = %q, want 5h0m0s (from the plan's --cooldown kimi=5h, no --window entry)", got.QuotaWindow)
	}
	// wallHours=1, window=5h -> windows elapsed = 1/5 = 0.2 -> accepts/windows = 1/0.2 = 5.
	if got.AcceptsPerWindow != 5 {
		t.Fatalf("accepts_per_window = %v, want 5", got.AcceptsPerWindow)
	}
	if got.MeanIterationsToAccept != 5 {
		t.Fatalf("mean_iterations_to_accept = %v, want 5", got.MeanIterationsToAccept)
	}
	if got.OnCooldown {
		t.Fatal("kimi should not be on cooldown: state.Cooldowns is empty")
	}
}

// TestBuildMetricsWindowFlagOverridesCooldown checks the quota-window
// fallback chain: an explicit --window entry wins over --cooldown.
func TestBuildMetricsWindowFlagOverridesCooldown(t *testing.T) {
	state := fleetstate.New()
	state.Runs["x-p0"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{ID: "x-p0", File: "disasm/src/x.c", Agent: "kimi"}, Status: fleetstate.StatusDone,
	}
	state.PlanJSON = []byte(`{"cooldowns":{"kimi":"1h0m0s"},"windows":{"kimi":"5h0m0s"},"queue":[]}`)

	got := metricsFor(t, BuildMetrics(state, time.Now()), "kimi")
	if got.QuotaWindow != "5h0m0s" {
		t.Fatalf("quota_window = %q, want the --window entry (5h0m0s) to win over --cooldown (1h)", got.QuotaWindow)
	}
}

// TestBuildMetricsDefaultWindowWhenUnconfigured checks the final fallback:
// neither --window nor --cooldown configures this agent, so it gets the
// 24h default the task's own "e.g. kimi=5h, else 24h" describes.
func TestBuildMetricsDefaultWindowWhenUnconfigured(t *testing.T) {
	state := fleetstate.New()
	state.Runs["x-p0"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{ID: "x-p0", File: "disasm/src/x.c", Agent: "codex"}, Status: fleetstate.StatusDone,
	}

	got := metricsFor(t, BuildMetrics(state, time.Now()), "codex")
	if got.QuotaWindow != "24h0m0s" {
		t.Fatalf("quota_window = %q, want the 24h default", got.QuotaWindow)
	}
}

// TestBuildMetricsCooldownState checks the on_cooldown/cooldown_until
// fields reflect state.Cooldowns as of `now`.
func TestBuildMetricsCooldownState(t *testing.T) {
	state := fleetstate.New()
	state.Runs["x-p0"] = &fleetstate.RunRecord{
		Spec: fleetstate.RunSpec{ID: "x-p0", File: "disasm/src/x.c", Agent: "kimi"}, Status: fleetstate.StatusRequeued,
	}
	now := time.Date(2026, 9, 2, 12, 0, 0, 0, time.UTC)
	state.Cooldowns["kimi"] = now.Add(2 * time.Hour)

	got := metricsFor(t, BuildMetrics(state, now), "kimi")
	if !got.OnCooldown {
		t.Fatal("kimi should be on cooldown")
	}
	if !got.CooldownUntil.Equal(now.Add(2 * time.Hour)) {
		t.Fatalf("cooldown_until = %v, want %v", got.CooldownUntil, now.Add(2*time.Hour))
	}

	// An expired cooldown must not count.
	state.Cooldowns["kimi"] = now.Add(-time.Minute)
	got = metricsFor(t, BuildMetrics(state, now), "kimi")
	if got.OnCooldown {
		t.Fatal("an expired cooldown must not count as on_cooldown")
	}
}

// TestBuildMetricsMultipleAgentsSortedByName checks every distinct agent
// among state.Runs gets its own row, sorted.
func TestBuildMetricsMultipleAgentsSortedByName(t *testing.T) {
	state := fleetstate.New()
	state.Runs["a"] = &fleetstate.RunRecord{Spec: fleetstate.RunSpec{ID: "a", Agent: "kimi"}, Status: fleetstate.StatusDone}
	state.Runs["b"] = &fleetstate.RunRecord{Spec: fleetstate.RunSpec{ID: "b", Agent: "codex"}, Status: fleetstate.StatusDone}
	state.Runs["c"] = &fleetstate.RunRecord{Spec: fleetstate.RunSpec{ID: "c", Agent: "codex"}, Status: fleetstate.StatusDone}

	got := BuildMetrics(state, time.Now())
	if len(got) != 2 {
		t.Fatalf("len = %d, want 2 distinct agents", len(got))
	}
	if got[0].Agent != "codex" || got[1].Agent != "kimi" {
		t.Fatalf("order = [%s, %s], want [codex, kimi]", got[0].Agent, got[1].Agent)
	}
	if got[0].Runs != 2 {
		t.Fatalf("codex runs = %d, want 2", got[0].Runs)
	}
}
