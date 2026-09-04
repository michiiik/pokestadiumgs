// Package difficulty combines a runner.TargetOwner's static shape (tools/
// scan_asm_families.py's classify()) with its real probe-attempt history
// (tools/pragma_targets.py's OwnerHardness) into one coarse routing hint,
// and offers a --max-difficulty-style filter callers can apply against it.
//
// Originally control.DifficultyTier/difficultyTierFor (fleetctl PR #94,
// unused outside its own tests); moved into its own package so
// planpkg.Build -- which control already imports, so control could never
// import it back -- can filter owners by tier at plan-build/replan time.
package difficulty

import (
	"fmt"

	"fleetctl/internal/runner"
)

// Tier is a coarse, three-bucket routing hint for one owner -- how much
// genuine reasoning difficulty it's likely to take a generator to close,
// combining runner.TargetOwner's two independent signals:
//
//  1. Family: tools/scan_asm_families.py's classify() shape label, a
//     static structural guess available even for an owner that has never
//     been attempted (branch/call/loop/jump-table counts).
//  2. Hardness: tools/pragma_targets.py's OwnerHardness label
//     (fresh/drift/tie/stuck), built from REAL probe-attempt history when
//     any exists.
//
// Real evidence always wins over a static guess: an owner with a
// hard-looking Hardness label is Hard regardless of how simple its Family
// looked before anyone tried it. Family only decides the tier for a
// genuinely fresh owner (Hardness == "fresh" or empty), which is exactly
// the "before it's ever been analyzed" case a static classifier can
// actually speak to.
//
// This is a routing HINT, not a verdict -- thresholds and family buckets
// below are a reasonable starting point, not a tuned model of any
// particular generator's real strengths.
type Tier string

const (
	Easy   Tier = "easy"
	Medium Tier = "medium"
	Hard   Tier = "hard"
)

// rank orders the three tiers for Allowed's "at or below a ceiling"
// comparison -- lower is easier.
var rank = map[Tier]int{Easy: 0, Medium: 1, Hard: 2}

// driftCloseSimilarityThreshold: a "drift" owner (real gap, but not a
// register-allocation-only tie) whose best recorded attempt still cleared
// this bar has real evidence a close rewrite exists, so it's treated as
// Medium rather than Hard; a drift owner further off than this has shown
// less promise and is treated as Hard.
const driftCloseSimilarityThreshold = 0.85

// largeInstructionThreshold mirrors classify()'s own ">256 instructions"
// large_mixed cutoff -- reused here as a defensive size-based escalation
// to Hard regardless of Family, since a family match that large would
// itself be unusual (classify()'s per-family shape checks already bound
// most families to a small instruction count by construction).
const largeInstructionThreshold = 256

// easyFamilies are classify()'s unambiguous straight-line, branch-free
// wrapper shapes: one or a few calls, no control flow, capped at 28 or 64
// instructions by classify() itself. The most templatable shapes in the
// classifier, and the closest thing to "any generator should handle this."
var easyFamilies = map[string]bool{
	"direct_wrapper":     true,
	"multi_call_wrapper": true,
	"copy_worker":        true,
}

// hardFamilies are classify()'s own catch-all/complex-control-flow
// labels: a backward branch requiring "manual control-flow review"
// (loop_or_state_machine, state_machine), classify()'s explicit size
// cutoff (large_mixed, >256 instructions), its branchier/bigger
// call-sequence catch-all, or no template matching at all (unclassified).
var hardFamilies = map[string]bool{
	"loop_or_state_machine": true,
	"state_machine":         true,
	"large_mixed":           true,
	"call_sequence":         true,
	"unclassified":          true,
}

// TierFor combines owner's static Family with any real Hardness evidence
// into one Tier. See the Tier doc comment for the precedence rule (real
// evidence beats a guess) and each family/threshold constant's own
// comment for why it's bucketed that way.
func TierFor(owner runner.TargetOwner) Tier {
	switch owner.Hardness {
	case "stuck", "tie":
		// Heavily attempted with nothing close (stuck), or a
		// register-allocation-only near-miss no rewrite has closed (tie,
		// the 585D0.c pattern) -- real evidence this owner resists
		// whatever's been thrown at it so far.
		return Hard
	case "drift":
		// A genuine semantic gap, but with room already proven: how close
		// the best attempt got is the more informative signal here than
		// Family, which describes a shape that (by definition, drift
		// excludes tie/stuck) hasn't fully resisted every attempt.
		if owner.BestSimilarity != nil && *owner.BestSimilarity >= driftCloseSimilarityThreshold {
			return Medium
		}
		return Hard
	}

	// Hardness is "fresh" (too few attempts to judge) or empty (no
	// hardness data at all) -- Family is the only difficulty evidence
	// available, which is exactly the pre-analysis case this tier exists
	// to answer.
	if owner.InstructionCount > largeInstructionThreshold {
		return Hard
	}
	if hardFamilies[owner.Family] {
		return Hard
	}
	if easyFamilies[owner.Family] {
		return Easy
	}
	// Every other family (constant_map, state_field_access,
	// bounded_lookup, bounded_state_mutator, jump_table_map,
	// dispatcher_switch, float_math, predicate, init_sequence,
	// queue_dma_loop, plus any unrecognized future family name) --
	// structurally identified by classify() as something more than a bare
	// wrapper, but not one of its own complex-control-flow catch-alls.
	// jump_table_map/dispatcher_switch land here deliberately: classify()
	// is highly confident about the *shape*, but a jump-table owner is a
	// known repo-specific correctness trap (a plain C switch cannot match
	// this repo's link layout -- see AGENTS.md's section_layout_drift
	// probe rejection) rather than a raw-reasoning-difficulty case, so it
	// doesn't belong in either extreme bucket.
	return Medium
}

// Allowed reports whether owner's tier is at or below max -- Easy <=
// Medium <= Hard. An empty max means "no ceiling": every owner passes,
// the zero-value/default behavior a caller gets by simply not setting a
// --max-difficulty-style option.
func Allowed(owner runner.TargetOwner, max Tier) bool {
	if max == "" {
		return true
	}
	return rank[TierFor(owner)] <= rank[max]
}

// ParseTier validates a --max-difficulty-style flag value against the
// three known tiers. Deliberately does NOT accept "" as valid -- an empty
// string means "the flag was never set" to Allowed, a distinct thing from
// "the user typed an empty value"; callers should only call ParseTier once
// they already know the raw flag string is non-empty.
func ParseTier(s string) (Tier, error) {
	switch Tier(s) {
	case Easy, Medium, Hard:
		return Tier(s), nil
	default:
		return "", fmt.Errorf("difficulty: unknown tier %q (want: easy, medium, or hard)", s)
	}
}
