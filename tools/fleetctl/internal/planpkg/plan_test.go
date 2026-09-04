package planpkg

import (
	"context"
	"path/filepath"
	"testing"

	"fleetctl/internal/agentspec"
	"fleetctl/internal/difficulty"
	"fleetctl/internal/runner"
)

func ownersNamed(prefix string, n int) []runner.TargetOwner {
	out := make([]runner.TargetOwner, n)
	for i := range out {
		out[i] = runner.TargetOwner{Function: prefixed(prefix, i), Source: "disasm/src/" + prefix + ".c", InstructionCount: i}
	}
	return out
}

func prefixed(prefix string, i int) string {
	return prefix + "_owner" + itoa(i)
}

func itoa(i int) string {
	digits := "0123456789"
	if i == 0 {
		return "0"
	}
	var b []byte
	for i > 0 {
		b = append([]byte{digits[i%10]}, b...)
		i /= 10
	}
	return string(b)
}

func TestBuildPartitioning(t *testing.T) {
	fake := &runner.Fake{
		RankFilesResult: []runner.FileRank{
			{File: "disasm/src/14640.c"},
			{File: "disasm/src/79A00.c"},
		},
		TargetsResult: map[string][]runner.TargetOwner{
			"disasm/src/14640.c": ownersNamed("14640", 25), // 25 owners, owners-per-run=12 -> 3 partitions (12,12,1)
			"disasm/src/79A00.c": ownersNamed("79A00", 5),  // 5 owners -> 1 partition
		},
	}
	agents := []agentspec.Spec{
		{Agent: "codex", Model: "gpt-5.6-luna", Effort: "high"},
		{Agent: "kimi", Model: "kimi-code/k3", Effort: "high"},
	}
	plan, err := Build(context.Background(), fake, Options{
		Repo: "/repo", Files: 2, OwnersPerRun: 12, Agents: agents, BudgetSeconds: 3600,
	})
	if err != nil {
		t.Fatal(err)
	}
	if len(plan.Queue) != 4 { // 3 partitions for 14640.c + 1 for 79A00.c
		t.Fatalf("len(Queue) = %d, want 4", len(plan.Queue))
	}
	wantSizes := []int{12, 12, 1, 5}
	for i, spec := range plan.Queue {
		if len(spec.Owners) != wantSizes[i] {
			t.Fatalf("Queue[%d] has %d owners, want %d", i, len(spec.Owners), wantSizes[i])
		}
		if spec.BudgetSeconds != 3600 {
			t.Fatalf("Queue[%d].BudgetSeconds = %d, want 3600", i, spec.BudgetSeconds)
		}
	}
	// Round robin: codex, kimi, codex, kimi.
	wantAgents := []string{"codex", "kimi", "codex", "kimi"}
	for i, spec := range plan.Queue {
		if spec.Agent != wantAgents[i] {
			t.Fatalf("Queue[%d].Agent = %s, want %s", i, spec.Agent, wantAgents[i])
		}
	}
	if plan.Queue[0].ID != "14640-p0" || plan.Queue[1].ID != "14640-p1" || plan.Queue[2].ID != "14640-p2" {
		t.Fatalf("unexpected partition ids: %v", []string{plan.Queue[0].ID, plan.Queue[1].ID, plan.Queue[2].ID})
	}
	if plan.Queue[3].ID != "79A00-p0" {
		t.Fatalf("unexpected id for second file: %s", plan.Queue[3].ID)
	}
}

func TestBuildExplicitFileList(t *testing.T) {
	fake := &runner.Fake{
		TargetsResult: map[string][]runner.TargetOwner{
			"disasm/src/foo.c": ownersNamed("foo", 3),
		},
	}
	plan, err := Build(context.Background(), fake, Options{
		Repo: "/repo", FileList: []string{"disasm/src/foo.c"},
		Agents: []agentspec.Spec{{Agent: "claude", Model: "sonnet"}},
	})
	if err != nil {
		t.Fatal(err)
	}
	if len(plan.Queue) != 1 || plan.Queue[0].File != "disasm/src/foo.c" {
		t.Fatalf("unexpected queue: %+v", plan.Queue)
	}
	// RankFiles must never be called when an explicit file list is given.
	for _, call := range fake.Calls {
		if call.Method == "RankFiles" {
			t.Fatalf("RankFiles was called despite an explicit --file list")
		}
	}
}

// TestBuildFiltersOwnersByMaxDifficulty exercises the actual "let agents
// only work the easy targets for now" use case end to end: a file mixing
// easy/medium/hard owners only contributes its easy ones to the queue
// when MaxDifficulty is set, and a file with no easy owners at all is
// skipped entirely -- same as a file Targets returns nothing for.
func TestBuildFiltersOwnersByMaxDifficulty(t *testing.T) {
	fake := &runner.Fake{
		TargetsResult: map[string][]runner.TargetOwner{
			"disasm/src/mixed.c": {
				{Function: "mixed_easy", Source: "disasm/src/mixed.c", Family: "direct_wrapper", Hardness: "fresh"},
				{Function: "mixed_hard", Source: "disasm/src/mixed.c", Family: "unclassified", Hardness: "fresh"},
				{Function: "mixed_stuck", Source: "disasm/src/mixed.c", Family: "direct_wrapper", Hardness: "stuck"},
			},
			"disasm/src/allhard.c": {
				{Function: "allhard_1", Source: "disasm/src/allhard.c", Family: "loop_or_state_machine", Hardness: "fresh"},
			},
		},
	}
	plan, err := Build(context.Background(), fake, Options{
		Repo: "/repo", FileList: []string{"disasm/src/mixed.c", "disasm/src/allhard.c"},
		Agents:        []agentspec.Spec{{Agent: "claude", Model: "haiku"}},
		MaxDifficulty: difficulty.Easy,
	})
	if err != nil {
		t.Fatal(err)
	}
	// allhard.c contributes nothing -- its one owner is Hard, filtered out,
	// leaving it with zero owners, same as an empty Targets result.
	if len(plan.Queue) != 1 {
		t.Fatalf("len(Queue) = %d, want 1 (only mixed.c's easy owner)", len(plan.Queue))
	}
	if len(plan.Queue[0].Owners) != 1 || plan.Queue[0].Owners[0] != "mixed_easy" {
		t.Fatalf("Queue[0].Owners = %v, want exactly [mixed_easy]", plan.Queue[0].Owners)
	}
	if plan.MaxDifficulty != difficulty.Easy {
		t.Fatalf("plan.MaxDifficulty = %q, want %q", plan.MaxDifficulty, difficulty.Easy)
	}
}

// TestBuildWithoutMaxDifficultyQueuesEverything is an explicit regression
// guard: the zero-value MaxDifficulty ("") must keep queueing every owner
// Targets returns, unfiltered -- the exact pre-existing behavior every
// other test in this file (which never sets MaxDifficulty at all) already
// relies on implicitly.
func TestBuildWithoutMaxDifficultyQueuesEverything(t *testing.T) {
	fake := &runner.Fake{
		TargetsResult: map[string][]runner.TargetOwner{
			"disasm/src/mixed.c": {
				{Function: "a", Source: "disasm/src/mixed.c", Family: "direct_wrapper", Hardness: "fresh"},
				{Function: "b", Source: "disasm/src/mixed.c", Family: "unclassified", Hardness: "fresh"},
				{Function: "c", Source: "disasm/src/mixed.c", Family: "unclassified", Hardness: "stuck"},
			},
		},
	}
	plan, err := Build(context.Background(), fake, Options{
		Repo: "/repo", FileList: []string{"disasm/src/mixed.c"},
		Agents: []agentspec.Spec{{Agent: "claude", Model: "haiku"}},
	})
	if err != nil {
		t.Fatal(err)
	}
	if len(plan.Queue) != 1 || len(plan.Queue[0].Owners) != 3 {
		t.Fatalf("Queue = %+v, want all 3 owners in one partition", plan.Queue)
	}
}

func TestBuildRequiresAgentAndFiles(t *testing.T) {
	fake := &runner.Fake{}
	if _, err := Build(context.Background(), fake, Options{Repo: "/repo", Files: 1}); err == nil {
		t.Fatal("want error with no --agent")
	}
	if _, err := Build(context.Background(), fake, Options{
		Repo: "/repo", Agents: []agentspec.Spec{{Agent: "claude", Model: "sonnet"}},
	}); err == nil {
		t.Fatal("want error with neither --files nor --file")
	}
	if _, err := Build(context.Background(), fake, Options{
		Repo: "/repo", Files: 1, FileList: []string{"x.c"},
		Agents: []agentspec.Spec{{Agent: "claude", Model: "sonnet"}},
	}); err == nil {
		t.Fatal("want error when both --files and --file are given")
	}
}

func TestSaveLoad(t *testing.T) {
	fake := &runner.Fake{
		TargetsResult: map[string][]runner.TargetOwner{
			"disasm/src/foo.c": ownersNamed("foo", 2),
		},
	}
	cooldowns, err := ParseCooldowns([]string{"kimi=5h"})
	if err != nil {
		t.Fatal(err)
	}
	concurrency, err := ParseAgentConcurrency([]string{"codex=2"})
	if err != nil {
		t.Fatal(err)
	}
	plan, err := Build(context.Background(), fake, Options{
		Repo: "/repo", FileList: []string{"disasm/src/foo.c"}, Slots: 4,
		Agents:           []agentspec.Spec{{Agent: "kimi", Model: "kimi-code/k3", Effort: "high"}},
		Cooldowns:        cooldowns,
		AgentConcurrency: concurrency,
		MaxDifficulty:    difficulty.Easy,
	})
	if err != nil {
		t.Fatal(err)
	}
	path := filepath.Join(t.TempDir(), "plan.json")
	if err := plan.Save(path); err != nil {
		t.Fatal(err)
	}
	loaded, err := Load(path)
	if err != nil {
		t.Fatal(err)
	}
	if len(loaded.Queue) != len(plan.Queue) {
		t.Fatalf("round trip queue length: got %d, want %d", len(loaded.Queue), len(plan.Queue))
	}
	if loaded.Cooldowns["kimi"] != "5h0m0s" {
		t.Fatalf("round trip cooldowns: %+v", loaded.Cooldowns)
	}
	if loaded.AgentConcurrency["codex"] != 2 {
		t.Fatalf("round trip agent concurrency: %+v", loaded.AgentConcurrency)
	}
	if loaded.Slots != 4 {
		t.Fatalf("round trip slots: %d", loaded.Slots)
	}
	if loaded.MaxDifficulty != difficulty.Easy {
		t.Fatalf("round trip max difficulty: %q, want %q", loaded.MaxDifficulty, difficulty.Easy)
	}
	// ToOptions must carry MaxDifficulty back out too -- this is the exact
	// path control.Loop.Replan uses to rebuild Options from a persisted
	// plan (not a fresh CLI invocation), so a replan after a restart keeps
	// honoring the original ceiling without needing --max-difficulty again.
	opts, err := loaded.ToOptions()
	if err != nil {
		t.Fatal(err)
	}
	if opts.MaxDifficulty != difficulty.Easy {
		t.Fatalf("ToOptions().MaxDifficulty = %q, want %q", opts.MaxDifficulty, difficulty.Easy)
	}
}

func TestFileSlug(t *testing.T) {
	cases := map[string]string{
		"disasm/src/14640.c":                          "14640",
		"disasm/src/fragments/79/fragment79_3BF4C0.c": "fragment79_3BF4C0",
	}
	for in, want := range cases {
		if got := FileSlug(in); got != want {
			t.Fatalf("FileSlug(%q) = %q, want %q", in, got, want)
		}
	}
}
