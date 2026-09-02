package main

import (
	"flag"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"
	"time"

	"fleetctl/internal/fleetstate"
)

func runStatusCmd(args []string) error {
	fs := flag.NewFlagSet("status", flag.ContinueOnError)
	stateDir := fs.String("state-dir", "", "directory holding state.json (required)")
	if err := fs.Parse(args); err != nil {
		return err
	}
	if *stateDir == "" {
		return fmt.Errorf("status: --state-dir is required")
	}
	state, err := fleetstate.Load(filepath.Join(*stateDir, "state.json"))
	if err != nil {
		return err
	}
	printStatusTable(os.Stdout, state)
	return nil
}

func printStatusTable(w *os.File, state *fleetstate.State) {
	ids := make([]string, 0, len(state.Runs))
	for id := range state.Runs {
		ids = append(ids, id)
	}
	sort.Strings(ids)

	fmt.Fprintf(w, "%-28s %-10s %-30s %-20s %-8s %-8s %-8s %s\n",
		"RUN", "STATUS", "FILE", "AGENT", "OWNERS", "MATCHED", "ATTEMPT", "NOTE")
	for _, id := range ids {
		rec := state.Runs[id]
		file := filepath.Base(rec.Spec.File)
		agent := rec.Spec.Agent + ":" + rec.Spec.Model
		note := rec.Note
		if rec.StoppedReason != "" {
			if note != "" {
				note = rec.StoppedReason + "; " + note
			} else {
				note = rec.StoppedReason
			}
		}
		fmt.Fprintf(w, "%-28s %-10s %-30s %-20s %-8d %-8d %-8d %s\n",
			id, rec.Status, file, agent, len(rec.Spec.Owners), len(rec.MatchedOwners), rec.Spec.Attempt, note)
	}

	if len(state.Cooldowns) > 0 {
		fmt.Fprintln(w, "\nCOOLDOWNS:")
		agents := make([]string, 0, len(state.Cooldowns))
		for a := range state.Cooldowns {
			agents = append(agents, a)
		}
		sort.Strings(agents)
		now := time.Now()
		for _, a := range agents {
			until := state.Cooldowns[a]
			remaining := "expired"
			if until.After(now) {
				remaining = until.Sub(now).Round(time.Second).String() + " remaining"
			}
			fmt.Fprintf(w, "  %-12s until %s (%s)\n", a, until.Format(time.RFC3339), remaining)
		}
	}

	total, byAgent := state.RunningCount()
	agentSummary := make([]string, 0, len(byAgent))
	for a, n := range byAgent {
		agentSummary = append(agentSummary, fmt.Sprintf("%s=%d", a, n))
	}
	sort.Strings(agentSummary)
	fmt.Fprintf(w, "\nrunning=%d queued=%d (%s)\n", total, len(state.Queue), strings.Join(agentSummary, " "))
}
