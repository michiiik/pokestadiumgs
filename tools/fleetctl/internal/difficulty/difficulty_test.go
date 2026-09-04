package difficulty

import (
	"sort"
	"testing"

	"fleetctl/internal/runner"
)

func simPtr(f float64) *float64 { return &f }

func TestTierFor(t *testing.T) {
	cases := []struct {
		name  string
		owner runner.TargetOwner
		want  Tier
	}{
		{
			name:  "stuck hardness is hard regardless of an easy-looking family",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "stuck"},
			want:  Hard,
		},
		{
			name:  "tie hardness is hard regardless of an easy-looking family",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "tie"},
			want:  Hard,
		},
		{
			name:  "drift close to 1.0 is medium -- real evidence a rewrite can close it",
			owner: runner.TargetOwner{Family: "unclassified", Hardness: "drift", BestSimilarity: simPtr(0.92)},
			want:  Medium,
		},
		{
			name:  "drift exactly at the threshold is medium",
			owner: runner.TargetOwner{Family: "unclassified", Hardness: "drift", BestSimilarity: simPtr(driftCloseSimilarityThreshold)},
			want:  Medium,
		},
		{
			name:  "drift below the threshold is hard",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "drift", BestSimilarity: simPtr(0.40)},
			want:  Hard,
		},
		{
			name:  "drift with no recorded similarity is hard -- no evidence to promote it",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "drift", BestSimilarity: nil},
			want:  Hard,
		},
		{
			name:  "fresh owner in an easy family is easy",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "fresh", InstructionCount: 12},
			want:  Easy,
		},
		{
			name:  "fresh owner in a hard family is hard",
			owner: runner.TargetOwner{Family: "loop_or_state_machine", Hardness: "fresh", InstructionCount: 40},
			want:  Hard,
		},
		{
			name:  "fresh owner in a family that's neither easy nor hard is medium",
			owner: runner.TargetOwner{Family: "jump_table_map", Hardness: "fresh", InstructionCount: 30},
			want:  Medium,
		},
		{
			name:  "empty hardness (no data at all) falls back to family, same as fresh",
			owner: runner.TargetOwner{Family: "multi_call_wrapper", Hardness: "", InstructionCount: 20},
			want:  Easy,
		},
		{
			name:  "an unrecognized family with fresh hardness defaults to medium",
			owner: runner.TargetOwner{Family: "some_future_family_name", Hardness: "fresh", InstructionCount: 20},
			want:  Medium,
		},
		{
			name:  "an oversized owner is hard even in an easy family -- defensive size override",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "fresh", InstructionCount: largeInstructionThreshold + 1},
			want:  Hard,
		},
		{
			name:  "exactly at the size threshold does not trip the override",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "fresh", InstructionCount: largeInstructionThreshold},
			want:  Easy,
		},
	}

	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			got := TierFor(c.owner)
			if got != c.want {
				t.Fatalf("TierFor(%+v) = %v, want %v", c.owner, got, c.want)
			}
		})
	}
}

func TestRank(t *testing.T) {
	if !(Rank(Easy) < Rank(Medium)) {
		t.Fatalf("Rank(Easy)=%d must be < Rank(Medium)=%d", Rank(Easy), Rank(Medium))
	}
	if !(Rank(Medium) < Rank(Hard)) {
		t.Fatalf("Rank(Medium)=%d must be < Rank(Hard)=%d", Rank(Medium), Rank(Hard))
	}
}

// TestRankSortsOwnersEasiestFirst exercises Rank the way a real caller
// does -- sort.SliceStable, the exact pattern documented on Rank -- and
// confirms it's stable: two owners in the same tier keep their original
// relative order (mirroring `targets`'s own smallest-instructions-first
// ranking, which callers sort by tier on top of, not instead of).
func TestRankSortsOwnersEasiestFirst(t *testing.T) {
	owners := []runner.TargetOwner{
		{Function: "hard_1", Family: "unclassified", Hardness: "fresh"},
		{Function: "medium_1", Family: "jump_table_map", Hardness: "fresh"},
		{Function: "easy_1", Family: "direct_wrapper", Hardness: "fresh"},
		{Function: "medium_2", Family: "constant_map", Hardness: "fresh"},
		{Function: "easy_2", Family: "multi_call_wrapper", Hardness: "fresh"},
		{Function: "hard_2", Family: "large_mixed", Hardness: "fresh"},
	}
	sort.SliceStable(owners, func(i, j int) bool {
		return Rank(TierFor(owners[i])) < Rank(TierFor(owners[j]))
	})
	var got []string
	for _, o := range owners {
		got = append(got, o.Function)
	}
	want := []string{"easy_1", "easy_2", "medium_1", "medium_2", "hard_1", "hard_2"}
	if len(got) != len(want) {
		t.Fatalf("got %v, want %v", got, want)
	}
	for i := range want {
		if got[i] != want[i] {
			t.Fatalf("order = %v, want %v", got, want)
		}
	}
}
