package control

import (
	"encoding/json"
	"os"
	"path/filepath"
	"sort"
	"time"

	"fleetctl/internal/fleetstate"
	"fleetctl/internal/planpkg"
)

// AgentMetrics is one row of `fleetctl status`'s METRICS table, `status
// --json`'s "metrics" field, and the daily summary's embedded status block
// (docs/FLEET_CONTROLLER.md sec 11): per-agent-spec throughput, computed
// from every RunRecord for that agent plus each run's own
// <out>/summary.json and <out>/state.json.
type AgentMetrics struct {
	Agent      string `json:"agent"`
	Runs       int    `json:"runs"`
	Iterations int    `json:"iterations"`
	Accepts    int    `json:"accepts"`

	WallHours          float64 `json:"wall_hours"`
	AcceptsPerWallHour float64 `json:"accepts_per_wall_hour"`

	// QuotaWindow is this agent's configured window length (--window, else
	// --cooldown, else a 24h default -- quotaWindowFor), rendered as a
	// duration string.
	QuotaWindow      string  `json:"quota_window"`
	AcceptsPerWindow float64 `json:"accepts_per_window"`
	// WindowBudget is --window-budget's configured expected batches per
	// window for this agent, when one was given (informational, sec 11).
	WindowBudget int `json:"window_budget,omitempty"`

	// MeanIterationsToAccept is the mean, over every owner this agent's
	// runs accepted, of that owner's own state.json "iterations" count at
	// acceptance -- 0 (field omitted) when this agent has no accepts yet.
	MeanIterationsToAccept float64 `json:"mean_iterations_to_accept,omitempty"`

	OnCooldown    bool      `json:"on_cooldown"`
	CooldownUntil time.Time `json:"cooldown_until,omitempty"`
}

// ownerStateDoc is the subset of one <out>/state.json owner entry
// (tools/container_agent.py's _new_owner_state) BuildMetrics needs: status
// ("accepted" once matched) and the cumulative iteration count.
type ownerStateDoc struct {
	Status     string `json:"status"`
	Iterations int    `json:"iterations"`
}

func readOwnerStates(outDir string) map[string]ownerStateDoc {
	data, err := os.ReadFile(filepath.Join(outDir, "state.json"))
	if err != nil {
		return nil
	}
	var m map[string]ownerStateDoc
	if err := json.Unmarshal(data, &m); err != nil {
		return nil
	}
	return m
}

// summaryWallDoc is the subset of one <out>/summary.json BuildMetrics needs
// for wall-clock accounting.
type summaryWallDoc struct {
	WallSeconds float64 `json:"wall_seconds"`
}

// runWallSeconds is how long rec's current attempt has been running:
// <out>/summary.json's own "wall_seconds" (set once the process exits --
// see tools/container_agent.py's _finalize_run) when readable, else
// rec.EndedAt - rec.StartedAt (rec.EndedAt defaulting to now for a still-
// running rec) -- 0 for a rec that has never launched. Like
// container_agent.py's own wall_seconds, this reflects only the current
// (possibly --resume'd) attempt's process lifetime, not summed across every
// past attempt of a repeatedly-resumed run -- the same simplification sec 6
// already notes for Attempt/cooldown accounting.
func runWallSeconds(rec *fleetstate.RunRecord, now time.Time) float64 {
	if data, err := os.ReadFile(filepath.Join(rec.OutDir, "summary.json")); err == nil {
		var s summaryWallDoc
		if err := json.Unmarshal(data, &s); err == nil && s.WallSeconds > 0 {
			return s.WallSeconds
		}
	}
	if rec.StartedAt.IsZero() {
		return 0
	}
	end := rec.EndedAt
	if end.IsZero() {
		end = now
	}
	if end.Before(rec.StartedAt) {
		return 0
	}
	return end.Sub(rec.StartedAt).Seconds()
}

// plannedWindowConfig recovers the --window/--cooldown/--window-budget maps
// a persisted plan (state.PlanJSON) was built with, for BuildMetrics'
// standalone (Loop-less) use from `fleetctl status`/the daily summary --
// mirroring what a live control.Loop already has in its own
// WindowDurations/CooldownDefaults/WindowBudget fields. Zero values
// (including no persisted plan at all) yield empty maps, which
// quotaWindowFor already falls back from correctly.
func plannedWindowConfig(state *fleetstate.State) (windows, cooldowns map[string]time.Duration, windowBudget map[string]int) {
	windows, cooldowns, windowBudget = map[string]time.Duration{}, map[string]time.Duration{}, map[string]int{}
	if len(state.PlanJSON) == 0 {
		return
	}
	var p planpkg.Plan
	if err := json.Unmarshal(state.PlanJSON, &p); err != nil {
		return
	}
	for agent, s := range p.Cooldowns {
		if d, err := time.ParseDuration(s); err == nil {
			cooldowns[agent] = d
		}
	}
	for agent, s := range p.Windows {
		if d, err := time.ParseDuration(s); err == nil {
			windows[agent] = d
		}
	}
	windowBudget = p.WindowBudget
	return
}

func round2(f float64) float64 {
	return float64(int(f*100+0.5)) / 100
}

// BuildMetrics computes one AgentMetrics row per distinct agent spec seen
// in state.Runs (docs sec 11): runs, iterations, accepts (each read from
// that run's own <out>/state.json), wall-clock throughput (accepts per wall
// hour and per configured quota window, from <out>/summary.json plus
// state.json), mean iterations-to-accept, and current cooldown state (from
// state.Cooldowns). now is the reference time for wall-hours of a still-
// running run and for on_cooldown; callers with no injectable clock (`status`)
// pass time.Now().
func BuildMetrics(state *fleetstate.State, now time.Time) []AgentMetrics {
	type agg struct {
		runs                int
		iterations          int
		accepts             int
		wallSeconds         float64
		acceptIterationsSum int
		acceptCount         int
	}
	aggs := map[string]*agg{}
	for _, rec := range state.Runs {
		agent := rec.Spec.Agent
		a := aggs[agent]
		if a == nil {
			a = &agg{}
			aggs[agent] = a
		}
		a.runs++
		for _, o := range readOwnerStates(rec.OutDir) {
			a.iterations += o.Iterations
			if o.Status == "accepted" {
				a.accepts++
				a.acceptIterationsSum += o.Iterations
				a.acceptCount++
			}
		}
		a.wallSeconds += runWallSeconds(rec, now)
	}

	windows, cooldowns, windowBudget := plannedWindowConfig(state)

	agents := make([]string, 0, len(aggs))
	for agent := range aggs {
		agents = append(agents, agent)
	}
	sort.Strings(agents)

	out := make([]AgentMetrics, 0, len(agents))
	for _, agent := range agents {
		a := aggs[agent]
		wallHours := a.wallSeconds / 3600
		window := quotaWindowFor(agent, windows, cooldowns)
		m := AgentMetrics{
			Agent:        agent,
			Runs:         a.runs,
			Iterations:   a.iterations,
			Accepts:      a.accepts,
			WallHours:    round2(wallHours),
			QuotaWindow:  window.String(),
			WindowBudget: windowBudget[agent],
		}
		if wallHours > 0 {
			m.AcceptsPerWallHour = round2(float64(a.accepts) / wallHours)
			if window > 0 {
				m.AcceptsPerWindow = round2(float64(a.accepts) / (a.wallSeconds / window.Seconds()))
			}
		}
		if a.acceptCount > 0 {
			m.MeanIterationsToAccept = round2(float64(a.acceptIterationsSum) / float64(a.acceptCount))
		}
		if until, ok := state.CooldownUntil(agent); ok && until.After(now) {
			m.OnCooldown = true
			m.CooldownUntil = until
		}
		out = append(out, m)
	}
	return out
}
