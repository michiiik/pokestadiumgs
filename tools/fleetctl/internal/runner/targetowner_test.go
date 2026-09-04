package runner

import (
	"encoding/json"
	"testing"
)

// TestTargetOwnerJSONDecoding pins TargetOwner's JSON tags against a
// payload shaped exactly like a real `tools/pragma_targets.py targets`
// row (list_targets: _classify_owner's family/instructions plus
// OwnerHardness.as_dict()'s prior_attempts/best_similarity merged in,
// hardness set separately) -- Targets (exec.go) decodes the CLI's raw
// stdout the same way, so a tag typo here would silently zero out a field
// on every real call instead of failing loudly.
func TestTargetOwnerJSONDecoding(t *testing.T) {
	const payload = `{
		"targets": [
			{
				"function": "func_80057D74",
				"source": "disasm/src/585D0.c",
				"instructions": 42,
				"family": "call_sequence",
				"hardness": "drift",
				"best_similarity": 0.91,
				"prior_attempts": 6
			},
			{
				"function": "func_8005ADD8",
				"source": "disasm/src/585D0.c",
				"instructions": 8,
				"family": "direct_wrapper",
				"hardness": "fresh",
				"best_similarity": null,
				"prior_attempts": 0
			}
		]
	}`

	var doc struct {
		Targets []TargetOwner `json:"targets"`
	}
	if err := json.Unmarshal([]byte(payload), &doc); err != nil {
		t.Fatalf("unmarshal: %v", err)
	}
	if len(doc.Targets) != 2 {
		t.Fatalf("got %d owners, want 2", len(doc.Targets))
	}

	drifted := doc.Targets[0]
	if drifted.Function != "func_80057D74" || drifted.InstructionCount != 42 {
		t.Fatalf("owner 0 base fields = %+v", drifted)
	}
	if drifted.Family != "call_sequence" || drifted.Hardness != "drift" {
		t.Fatalf("owner 0 family/hardness = %q/%q", drifted.Family, drifted.Hardness)
	}
	if drifted.BestSimilarity == nil || *drifted.BestSimilarity != 0.91 {
		t.Fatalf("owner 0 best_similarity = %v, want 0.91", drifted.BestSimilarity)
	}
	if drifted.PriorAttempts != 6 {
		t.Fatalf("owner 0 prior_attempts = %d, want 6", drifted.PriorAttempts)
	}

	fresh := doc.Targets[1]
	if fresh.Family != "direct_wrapper" || fresh.Hardness != "fresh" {
		t.Fatalf("owner 1 family/hardness = %q/%q", fresh.Family, fresh.Hardness)
	}
	if fresh.BestSimilarity != nil {
		t.Fatalf("owner 1 best_similarity = %v, want nil (a JSON null must decode to a nil pointer)", fresh.BestSimilarity)
	}
}
