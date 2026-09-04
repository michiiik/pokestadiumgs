package difficulty

import (
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

func TestAllowed(t *testing.T) {
	easyOwner := runner.TargetOwner{Family: "direct_wrapper", Hardness: "fresh"}
	mediumOwner := runner.TargetOwner{Family: "jump_table_map", Hardness: "fresh"}
	hardOwner := runner.TargetOwner{Family: "unclassified", Hardness: "fresh"}

	cases := []struct {
		name  string
		owner runner.TargetOwner
		max   Tier
		want  bool
	}{
		{"no ceiling allows easy", easyOwner, "", true},
		{"no ceiling allows medium", mediumOwner, "", true},
		{"no ceiling allows hard", hardOwner, "", true},

		{"easy ceiling allows an easy owner", easyOwner, Easy, true},
		{"easy ceiling rejects a medium owner", mediumOwner, Easy, false},
		{"easy ceiling rejects a hard owner", hardOwner, Easy, false},

		{"medium ceiling allows an easy owner", easyOwner, Medium, true},
		{"medium ceiling allows a medium owner", mediumOwner, Medium, true},
		{"medium ceiling rejects a hard owner", hardOwner, Medium, false},

		{"hard ceiling allows everything", easyOwner, Hard, true},
		{"hard ceiling allows a hard owner", hardOwner, Hard, true},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			got := Allowed(c.owner, c.max)
			if got != c.want {
				t.Fatalf("Allowed(%+v, %q) = %v, want %v", c.owner, c.max, got, c.want)
			}
		})
	}
}

func TestParseTier(t *testing.T) {
	for _, s := range []string{"easy", "medium", "hard"} {
		got, err := ParseTier(s)
		if err != nil {
			t.Fatalf("ParseTier(%q) = %v, want no error", s, err)
		}
		if string(got) != s {
			t.Fatalf("ParseTier(%q) = %q", s, got)
		}
	}
	for _, s := range []string{"", "EASY", "trivial", "impossible"} {
		if _, err := ParseTier(s); err == nil {
			t.Fatalf("ParseTier(%q) = nil error, want an error", s)
		}
	}
}
