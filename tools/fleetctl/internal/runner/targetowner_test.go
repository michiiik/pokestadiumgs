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

// TestTargetOwnerSchedulableJSONDecoding pins the schedulable/
// jump_table_unready/coalesce_unready tags pragma_targets.py's
// _jump_table_readiness/_coalesce_readiness add to every `targets` row
// (see runner.go's Schedulable doc) -- and confirms a payload from before
// those fields existed decodes Schedulable to nil, not false, so
// planpkg.schedulableOwners fails open on an old/foreign payload instead of
// silently excluding every owner in it.
func TestTargetOwnerSchedulableJSONDecoding(t *testing.T) {
	const payload = `{
		"targets": [
			{"function": "func_ready", "source": "disasm/src/x.c", "instructions": 4, "family": "direct_wrapper", "hardness": "fresh", "best_similarity": null, "prior_attempts": 0, "schedulable": true, "jump_table_unready": false, "coalesce_unready": false},
			{"function": "func_jt_blocked", "source": "disasm/src/x.c", "instructions": 40, "family": "dispatcher_switch", "hardness": "fresh", "best_similarity": null, "prior_attempts": 0, "schedulable": false, "jump_table_unready": true, "coalesce_unready": false},
			{"function": "func_coalesce_blocked", "source": "disasm/src/x.c", "instructions": 40, "family": "call_sequence", "hardness": "fresh", "best_similarity": null, "prior_attempts": 0, "schedulable": false, "jump_table_unready": false, "coalesce_unready": true},
			{"function": "func_old_payload", "source": "disasm/src/x.c", "instructions": 4, "family": "direct_wrapper", "hardness": "fresh", "best_similarity": null, "prior_attempts": 0}
		]
	}`

	var doc struct {
		Targets []TargetOwner `json:"targets"`
	}
	if err := json.Unmarshal([]byte(payload), &doc); err != nil {
		t.Fatalf("unmarshal: %v", err)
	}
	if len(doc.Targets) != 4 {
		t.Fatalf("got %d owners, want 4", len(doc.Targets))
	}

	ready := doc.Targets[0]
	if ready.Schedulable == nil || !*ready.Schedulable {
		t.Fatalf("func_ready.Schedulable = %v, want true", ready.Schedulable)
	}

	jtBlocked := doc.Targets[1]
	if jtBlocked.Schedulable == nil || *jtBlocked.Schedulable {
		t.Fatalf("func_jt_blocked.Schedulable = %v, want false", jtBlocked.Schedulable)
	}
	if !jtBlocked.JumpTableUnready {
		t.Fatalf("func_jt_blocked.JumpTableUnready = false, want true")
	}

	coalesceBlocked := doc.Targets[2]
	if coalesceBlocked.Schedulable == nil || *coalesceBlocked.Schedulable {
		t.Fatalf("func_coalesce_blocked.Schedulable = %v, want false", coalesceBlocked.Schedulable)
	}
	if !coalesceBlocked.CoalesceUnready {
		t.Fatalf("func_coalesce_blocked.CoalesceUnready = false, want true")
	}

	oldPayload := doc.Targets[3]
	if oldPayload.Schedulable != nil {
		t.Fatalf("func_old_payload.Schedulable = %v, want nil (missing field must decode to nil, not false)", oldPayload.Schedulable)
	}
}
