// fleetctl orchestrates a fleet of containerised per-file decomp agents
// (docs/CONTAINER_AGENT.md) so a human does not have to babysit
// container/run.sh + tools/container_merge.py by hand. See
// docs/FLEET_CONTROLLER.md for the full command reference and state
// machine.
package main

import (
	"fmt"
	"os"
)

func main() {
	if len(os.Args) < 2 {
		usage()
		os.Exit(2)
	}

	var err error
	switch os.Args[1] {
	case "plan":
		err = runPlanCmd(os.Args[2:])
	case "run":
		err = runRunCmd(os.Args[2:])
	case "status":
		err = runStatusCmd(os.Args[2:])
	case "stop":
		err = runStopCmd(os.Args[2:])
	case "-h", "--help", "help":
		usage()
		return
	default:
		fmt.Fprintf(os.Stderr, "fleetctl: unknown command %q\n\n", os.Args[1])
		usage()
		os.Exit(2)
	}
	if err != nil {
		fmt.Fprintf(os.Stderr, "fleetctl: %v\n", err)
		os.Exit(1)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, `fleetctl orchestrates containerised per-file decomp agents.

Usage:
  fleetctl plan --repo R (--files N | --file F...) --slots K --agent SPEC... [flags]
  fleetctl run --plan P --state-dir S --runs-dir D --repo R [flags]
  fleetctl status --state-dir S [--json]
  fleetctl stop --state-dir S (--run ID | --all)

--plan is required only the first time --state-dir has no plan persisted in
state.json yet; a restart reuses it (see docs sec 3). "run" also
self-merges a run's PR once its checks go green (--auto-merge, default
true), can re-plan against --merge-repo after every merge or at startup
(--replan), and can alert on gate_failed/ff_failed/vanished/exhausted/stall
events (--alert-issue N, --alert-macos).

Run "fleetctl <command> -h" for command-specific flags. See
docs/FLEET_CONTROLLER.md for the full reference.`)
}

// stringSlice implements flag.Value for a repeatable string flag
// (--file, --agent, --cooldown, --agent-concurrency).
type stringSlice []string

func (s *stringSlice) String() string {
	if s == nil {
		return ""
	}
	out := ""
	for i, v := range *s {
		if i > 0 {
			out += ","
		}
		out += v
	}
	return out
}

func (s *stringSlice) Set(v string) error {
	*s = append(*s, v)
	return nil
}
