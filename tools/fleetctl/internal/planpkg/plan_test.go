package planpkg

import (
	"context"
	"path/filepath"
	"testing"

	"fleetctl/internal/agentspec"
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

// TestBuildOrdersOwnersEasiestFirstWithinAFile is the actual "let agents
// work the easy targets first, graduate to harder ones once those run
// out" use case end to end: a file mixing easy/medium/hard owners queues
// ALL of them (nothing is ever dropped -- see internal/difficulty's
// package doc for why a hard --max-difficulty ceiling was tried first and
// reverted, live, when it left the fleet with nothing to do the moment
// one ranked file's easy owners ran out), but easy owners fill the
// earlier partitions and hard owners the later ones, so they're worked
// first without needing every medium/hard owner cleared out first.
func TestBuildOrdersOwnersEasiestFirstWithinAFile(t *testing.T) {
	fake := &runner.Fake{
		TargetsResult: map[string][]runner.TargetOwner{
			"disasm/src/mixed.c": {
				{Function: "mixed_hard", Source: "disasm/src/mixed.c", Family: "unclassified", Hardness: "fresh"},
				{Function: "mixed_easy", Source: "disasm/src/mixed.c", Family: "direct_wrapper", Hardness: "fresh"},
				{Function: "mixed_stuck", Source: "disasm/src/mixed.c", Family: "direct_wrapper", Hardness: "stuck"},
				{Function: "mixed_medium", Source: "disasm/src/mixed.c", Family: "jump_table_map", Hardness: "fresh"},
			},
		},
	}
	plan, err := Build(context.Background(), fake, Options{
		Repo: "/repo", FileList: []string{"disasm/src/mixed.c"}, OwnersPerRun: 2,
		Agents: []agentspec.Spec{{Agent: "claude", Model: "haiku"}},
	})
	if err != nil {
		t.Fatal(err)
	}
	// All 4 owners are still queued -- ordering resequences, never drops.
	if len(plan.Queue) != 2 || len(plan.Queue[0].Owners)+len(plan.Queue[1].Owners) != 4 {
		t.Fatalf("Queue = %+v, want all 4 owners across 2 partitions of 2", plan.Queue)
	}
	// mixed_easy (Easy) sorts before mixed_medium (Medium), which sorts
	// before both mixed_hard and mixed_stuck (Hard, Hardness=fresh vs
	// stuck doesn't change their relative order -- both rank Hard).
	if plan.Queue[0].Owners[0] != "mixed_easy" {
		t.Fatalf("Queue[0].Owners = %v, want mixed_easy first", plan.Queue[0].Owners)
	}
	if plan.Queue[0].Owners[1] != "mixed_medium" {
		t.Fatalf("Queue[0].Owners = %v, want mixed_medium second", plan.Queue[0].Owners)
	}
}

func boolPtr(b bool) *bool { return &b }

// TestBuildExcludesUnschedulableOwners is the primary-goal regression: an
// owner pragma_targets.py reports Schedulable=false (a jump-table owner
// whose file lacks its rodata subsegment, or one whose ground truth depends
// on an interleaved shared-$at lui run -- see runner.TargetOwner's
// Schedulable doc) must never be queued into a fresh plan, while an
// ordinary schedulable owner in the same file still is.
func TestBuildExcludesUnschedulableOwners(t *testing.T) {
	fake := &runner.Fake{
		TargetsResult: map[string][]runner.TargetOwner{
			"disasm/src/mixed.c": {
				{Function: "func_ready", Source: "disasm/src/mixed.c", Family: "direct_wrapper", Hardness: "fresh", Schedulable: boolPtr(true)},
				{Function: "func_jt_blocked", Source: "disasm/src/mixed.c", Family: "dispatcher_switch", Hardness: "fresh", Schedulable: boolPtr(false), JumpTableUnready: true},
				{Function: "func_coalesce_blocked", Source: "disasm/src/mixed.c", Family: "call_sequence", Hardness: "fresh", Schedulable: boolPtr(false), CoalesceUnready: true},
			},
		},
	}
	plan, err := Build(context.Background(), fake, Options{
		Repo: "/repo", FileList: []string{"disasm/src/mixed.c"}, OwnersPerRun: 12,
		Agents: []agentspec.Spec{{Agent: "claude", Model: "haiku"}},
	})
	if err != nil {
		t.Fatal(err)
	}
	if len(plan.Queue) != 1 {
		t.Fatalf("Queue = %+v, want exactly 1 partition", plan.Queue)
	}
	if got := plan.Queue[0].Owners; len(got) != 1 || got[0] != "func_ready" {
		t.Fatalf("Queue[0].Owners = %v, want only [func_ready]", got)
	}
}

// TestBuildExcludesUnschedulableFileEntirely covers the edge where every
// owner remaining in a file is unschedulable: the file must be dropped from
// the queue instead of producing an empty-owners run.
func TestBuildExcludesUnschedulableFileEntirely(t *testing.T) {
	fake := &runner.Fake{
		TargetsResult: map[string][]runner.TargetOwner{
			"disasm/src/all_blocked.c": {
				{Function: "func_a", Source: "disasm/src/all_blocked.c", Schedulable: boolPtr(false), JumpTableUnready: true},
				{Function: "func_b", Source: "disasm/src/all_blocked.c", Schedulable: boolPtr(false), CoalesceUnready: true},
			},
		},
	}
	plan, err := Build(context.Background(), fake, Options{
		Repo: "/repo", FileList: []string{"disasm/src/all_blocked.c"}, OwnersPerRun: 12,
		Agents: []agentspec.Spec{{Agent: "claude", Model: "haiku"}},
	})
	if err != nil {
		t.Fatal(err)
	}
	if len(plan.Queue) != 0 {
		t.Fatalf("Queue = %+v, want empty -- every owner in the file was unschedulable", plan.Queue)
	}
}

// TestBuildKeepsOwnerWithNilSchedulable proves the fail-open contract: a
// TargetOwner whose Schedulable pointer is nil (a payload from before this
// field existed, or any other decode surprise) is scheduled exactly as
// before this change -- a false exclusion would silently drop real,
// solvable work forever, which is worse than the wasted budget this
// feature exists to prevent.
func TestBuildKeepsOwnerWithNilSchedulable(t *testing.T) {
	fake := &runner.Fake{
		TargetsResult: map[string][]runner.TargetOwner{
			"disasm/src/old.c": {
				{Function: "func_old", Source: "disasm/src/old.c"}, // Schedulable left nil
			},
		},
	}
	plan, err := Build(context.Background(), fake, Options{
		Repo: "/repo", FileList: []string{"disasm/src/old.c"}, OwnersPerRun: 12,
		Agents: []agentspec.Spec{{Agent: "claude", Model: "haiku"}},
	})
	if err != nil {
		t.Fatal(err)
	}
	if len(plan.Queue) != 1 || len(plan.Queue[0].Owners) != 1 || plan.Queue[0].Owners[0] != "func_old" {
		t.Fatalf("Queue = %+v, want func_old scheduled (nil Schedulable fails open)", plan.Queue)
	}
}

// TestBuildUnschedulableOwnerBecomesSchedulableAgain is the self-correcting
// property the task calls for: nothing here is a static snapshot -- the
// exact same owner, reported schedulable again by a later Targets call (the
// live signal flipping once its file gets a rodata subsegment, or once
// coalesce_lui.py gains interleaved-fold support), is queued on the next
// plan build with zero code changes.
func TestBuildUnschedulableOwnerBecomesSchedulableAgain(t *testing.T) {
	fake := &runner.Fake{
		TargetsResult: map[string][]runner.TargetOwner{
			"disasm/src/x.c": {
				{Function: "func_x", Source: "disasm/src/x.c", Schedulable: boolPtr(false), JumpTableUnready: true},
			},
		},
	}
	opts := Options{
		Repo: "/repo", FileList: []string{"disasm/src/x.c"}, OwnersPerRun: 12,
		Agents: []agentspec.Spec{{Agent: "claude", Model: "haiku"}},
	}
	blockedPlan, err := Build(context.Background(), fake, opts)
	if err != nil {
		t.Fatal(err)
	}
	if len(blockedPlan.Queue) != 0 {
		t.Fatalf("Queue = %+v, want empty while func_x is jump-table-unready", blockedPlan.Queue)
	}

	// The file's rodata subsegment lands (or the coalesce site resolves
	// contiguous) -- pragma_targets.py now reports the same owner
	// schedulable, with no code or plan change on fleetctl's side.
	fake.TargetsResult["disasm/src/x.c"][0].Schedulable = boolPtr(true)
	fake.TargetsResult["disasm/src/x.c"][0].JumpTableUnready = false

	readyPlan, err := Build(context.Background(), fake, opts)
	if err != nil {
		t.Fatal(err)
	}
	if len(readyPlan.Queue) != 1 || len(readyPlan.Queue[0].Owners) != 1 || readyPlan.Queue[0].Owners[0] != "func_x" {
		t.Fatalf("Queue = %+v, want func_x scheduled once its readiness signal flips", readyPlan.Queue)
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
