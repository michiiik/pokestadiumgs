package control

import (
	"sort"
	"time"

	"fleetctl/internal/agentspec"
	"fleetctl/internal/fleetstate"
)

// defaultQuotaWindow is the quota-window length BuildMetrics/quotaWindowFor
// normalizes accepts-per-window against when neither --window nor
// --cooldown configures one for an agent (docs/FLEET_CONTROLLER.md sec 11)
// -- deliberately not the same as `run`'s own --default-cooldown (1h): a
// "typical daily quota" default, not a generator-exhaustion backoff.
const defaultQuotaWindow = 24 * time.Hour

// quotaWindowFor is agent's configured quota-window length: its own
// windows[agent] entry if set, else its own cooldowns[agent] entry (e.g.
// kimi=5h -- the same duration --cooldown already configures for it), else
// defaultQuotaWindow. Shared by control.Loop.quotaWindowFor (live
// caller-set maps) and BuildMetrics (maps recovered from a persisted plan),
// so both agree on the same fallback chain.
func quotaWindowFor(agent string, windows, cooldowns map[string]time.Duration) time.Duration {
	if d, ok := windows[agent]; ok && d > 0 {
		return d
	}
	if d, ok := cooldowns[agent]; ok && d > 0 {
		return d
	}
	return defaultQuotaWindow
}

func (l *Loop) quotaWindowFor(agent string) time.Duration {
	return quotaWindowFor(agent, l.WindowDurations, l.CooldownDefaults)
}

// windowState returns (creating if necessary) agent's persisted quota-window
// bookkeeping record (docs sec 12).
func (l *Loop) windowState(agent string) *fleetstate.AgentWindowState {
	if l.State.WindowState == nil {
		l.State.WindowState = map[string]*fleetstate.AgentWindowState{}
	}
	ws := l.State.WindowState[agent]
	if ws == nil {
		ws = &fleetstate.AgentWindowState{}
		l.State.WindowState[agent] = ws
	}
	return ws
}

// recordWindowExhausted marks agent's quota window as ended by a
// generator_exhausted exit (sec 12): WindowStart is zeroed, so its next
// launch (once its cooldown lapses) is recognised as starting a fresh
// window -- see windowReopened.
func (l *Loop) recordWindowExhausted(agent string, now time.Time) {
	ws := l.windowState(agent)
	ws.LastExhausted = now
	ws.WindowStart = time.Time{}
}

// recordWindowStart stamps agent's window start the first time it launches
// since a cooldown (or ever) -- a no-op once already stamped for the
// current window (sec 12).
func (l *Loop) recordWindowStart(agent string, now time.Time) {
	ws := l.windowState(agent)
	if ws.WindowStart.IsZero() {
		ws.WindowStart = now
	}
}

// windowReopened reports whether agent's quota window has just reopened --
// its cooldown has lapsed since it was last exhausted, but it has not yet
// been relaunched (WindowStart still zero). reassignAgent prefers such an
// agent first ("prefer the cooled-down agent for the next launches to
// rebalance", sec 12).
func (l *Loop) windowReopened(agent string, now time.Time) bool {
	ws := l.State.WindowState[agent]
	if ws == nil || ws.LastExhausted.IsZero() {
		return false
	}
	if l.State.OnCooldown(agent, now) {
		return false
	}
	return ws.WindowStart.IsZero()
}

// agentRoster returns every distinct agent spec known to this plan (from
// Loop.Agents, first-seen order, permuterAgent excluded -- the permuter
// lane is never a reassignment target) -- the pool launchEligible reassigns
// a cooling-down agent's queued partition to (sec 12). A single-agent plan
// yields a single-entry (or empty, once the original is excluded) roster,
// so reassignment is naturally a no-op and launchEligible falls back to its
// pre-sec-12 behaviour of just waiting out the cooldown.
func (l *Loop) agentRoster() []agentspec.Spec {
	seen := map[string]bool{}
	var out []agentspec.Spec
	for _, spec := range l.Agents {
		if spec.Agent == permuterAgent || seen[spec.Agent] {
			continue
		}
		seen[spec.Agent] = true
		out = append(out, spec)
	}
	return out
}

// eligibleForReassignment reports whether candidate agent currently has
// spare capacity to take on a reassigned partition: not on cooldown, and
// under its own --agent-concurrency cap (if any), accounting for byAgent's
// already-decided launches this pass.
func (l *Loop) eligibleForReassignment(agent string, now time.Time, byAgent map[string]int) bool {
	if l.State.OnCooldown(agent, now) {
		return false
	}
	if limit := l.AgentConcurrency[agent]; limit > 0 && byAgent[agent] >= limit {
		return false
	}
	return true
}

// reassignAgent picks the next eligible agent spec to launch a queued
// partition under instead of its own (currently cooling-down) original
// agent (sec 12): an agent whose window just reopened is preferred first,
// sorted by name for determinism when more than one qualifies; otherwise
// the roster is walked round-robin from State.ReassignCursor, which is
// advanced (and persisted) past whichever agent is picked. Returns false
// if no other roster agent currently has spare capacity -- launchEligible
// then falls back to leaving the partition queued with wait_reason
// "cooldown", exactly as before sec 12.
func (l *Loop) reassignAgent(original string, now time.Time, byAgent map[string]int) (agentspec.Spec, bool) {
	roster := l.agentRoster()
	if len(roster) == 0 {
		return agentspec.Spec{}, false
	}

	var reopened []agentspec.Spec
	for _, spec := range roster {
		if spec.Agent != original && l.eligibleForReassignment(spec.Agent, now, byAgent) && l.windowReopened(spec.Agent, now) {
			reopened = append(reopened, spec)
		}
	}
	if len(reopened) > 0 {
		sort.Slice(reopened, func(i, j int) bool { return reopened[i].Agent < reopened[j].Agent })
		return reopened[0], true
	}

	n := len(roster)
	for i := 0; i < n; i++ {
		idx := (l.State.ReassignCursor + i) % n
		spec := roster[idx]
		if spec.Agent == original {
			continue
		}
		if l.eligibleForReassignment(spec.Agent, now, byAgent) {
			l.State.ReassignCursor = (idx + 1) % n
			return spec, true
		}
	}
	return agentspec.Spec{}, false
}

// appendReassignNote records a launchEligible reassignment in a run's own
// Note (fleetctl status's note column, sec 12), preserving whatever note
// was already there (e.g. a prior pass's own reassignment, or a "stopped by
// operator" note from an earlier requeue).
func appendReassignNote(note, from, to string) string {
	clause := "reassigned " + from + "->" + to + " (cooldown)"
	if note == "" {
		return clause
	}
	return note + "; " + clause
}
