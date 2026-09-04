package control

import (
	"testing"

	"fleetctl/internal/runner"
)

func simPtr(f float64) *float64 { return &f }

func TestDifficultyTierFor(t *testing.T) {
	cases := []struct {
		name  string
		owner runner.TargetOwner
		want  DifficultyTier
	}{
		{
			name:  "stuck hardness is hard regardless of an easy-looking family",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "stuck"},
			want:  DifficultyHard,
		},
		{
			name:  "tie hardness is hard regardless of an easy-looking family",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "tie"},
			want:  DifficultyHard,
		},
		{
			name:  "drift close to 1.0 is medium -- real evidence a rewrite can close it",
			owner: runner.TargetOwner{Family: "unclassified", Hardness: "drift", BestSimilarity: simPtr(0.92)},
			want:  DifficultyMedium,
		},
		{
			name:  "drift exactly at the threshold is medium",
			owner: runner.TargetOwner{Family: "unclassified", Hardness: "drift", BestSimilarity: simPtr(driftCloseSimilarityThreshold)},
			want:  DifficultyMedium,
		},
		{
			name:  "drift below the threshold is hard",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "drift", BestSimilarity: simPtr(0.40)},
			want:  DifficultyHard,
		},
		{
			name:  "drift with no recorded similarity is hard -- no evidence to promote it",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "drift", BestSimilarity: nil},
			want:  DifficultyHard,
		},
		{
			name:  "fresh owner in an easy family is easy",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "fresh", InstructionCount: 12},
			want:  DifficultyEasy,
		},
		{
			name:  "fresh owner in a hard family is hard",
			owner: runner.TargetOwner{Family: "loop_or_state_machine", Hardness: "fresh", InstructionCount: 40},
			want:  DifficultyHard,
		},
		{
			name:  "fresh owner in a family that's neither easy nor hard is medium",
			owner: runner.TargetOwner{Family: "jump_table_map", Hardness: "fresh", InstructionCount: 30},
			want:  DifficultyMedium,
		},
		{
			name:  "empty hardness (no data at all) falls back to family, same as fresh",
			owner: runner.TargetOwner{Family: "multi_call_wrapper", Hardness: "", InstructionCount: 20},
			want:  DifficultyEasy,
		},
		{
			name:  "an unrecognized family with fresh hardness defaults to medium",
			owner: runner.TargetOwner{Family: "some_future_family_name", Hardness: "fresh", InstructionCount: 20},
			want:  DifficultyMedium,
		},
		{
			name:  "an oversized owner is hard even in an easy family -- defensive size override",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "fresh", InstructionCount: largeInstructionThreshold + 1},
			want:  DifficultyHard,
		},
		{
			name:  "exactly at the size threshold does not trip the override",
			owner: runner.TargetOwner{Family: "direct_wrapper", Hardness: "fresh", InstructionCount: largeInstructionThreshold},
			want:  DifficultyEasy,
		},
	}

	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			got := difficultyTierFor(c.owner)
			if got != c.want {
				t.Fatalf("difficultyTierFor(%+v) = %v, want %v", c.owner, got, c.want)
			}
		})
	}
}
