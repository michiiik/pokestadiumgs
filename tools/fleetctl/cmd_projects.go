package main

import (
	"flag"
	"fmt"
	"os"
	"path/filepath"

	"fleetctl/internal/projectreg"
)

func runProjectsCmd(args []string) error {
	if len(args) == 0 {
		return fmt.Errorf("projects: want a subcommand (set|list|remove) -- see `fleetctl projects -h`")
	}
	switch args[0] {
	case "set":
		return runProjectsSetCmd(args[1:])
	case "list":
		return runProjectsListCmd(args[1:])
	case "remove":
		return runProjectsRemoveCmd(args[1:])
	case "-h", "--help", "help":
		fmt.Fprintln(os.Stdout, projectsUsage)
		return nil
	default:
		return fmt.Errorf("projects: unknown subcommand %q -- see `fleetctl projects -h`", args[0])
	}
}

const projectsUsage = `fleetctl projects manages the machine-local project registry (see
internal/projectreg), so commands that take --state-dir can take a
registered name instead: e.g. "fleetctl status stadium2" instead of
"fleetctl status --state-dir /long/path/to/fleet-state".

Usage:
  fleetctl projects set <name> <state-dir>   register (or update) a project
  fleetctl projects list                     list every registered project
  fleetctl projects remove <name>            forget a registered project`

func runProjectsSetCmd(args []string) error {
	fs := flag.NewFlagSet("projects set", flag.ContinueOnError)
	if err := fs.Parse(args); err != nil {
		return err
	}
	rest := fs.Args()
	if len(rest) != 2 {
		return fmt.Errorf("projects set: want exactly `<name> <state-dir>`, got %d arg(s)", len(rest))
	}
	name, dir := rest[0], rest[1]
	abs, err := filepath.Abs(dir)
	if err != nil {
		return fmt.Errorf("projects set: %w", err)
	}
	entries, err := projectreg.Load()
	if err != nil {
		return err
	}
	entries[name] = abs
	if err := projectreg.Save(entries); err != nil {
		return err
	}
	fmt.Printf("registered %q -> %s\n", name, abs)
	return nil
}

func runProjectsListCmd(args []string) error {
	fs := flag.NewFlagSet("projects list", flag.ContinueOnError)
	if err := fs.Parse(args); err != nil {
		return err
	}
	entries, err := projectreg.Load()
	if err != nil {
		return err
	}
	names := projectreg.Names(entries)
	if len(names) == 0 {
		fmt.Println("no projects registered (see `fleetctl projects set <name> <state-dir>`)")
		return nil
	}
	for _, name := range names {
		fmt.Printf("%-20s %s\n", name, entries[name])
	}
	return nil
}

func runProjectsRemoveCmd(args []string) error {
	fs := flag.NewFlagSet("projects remove", flag.ContinueOnError)
	if err := fs.Parse(args); err != nil {
		return err
	}
	rest := fs.Args()
	if len(rest) != 1 {
		return fmt.Errorf("projects remove: want exactly `<name>`, got %d arg(s)", len(rest))
	}
	entries, err := projectreg.Load()
	if err != nil {
		return err
	}
	if _, ok := entries[rest[0]]; !ok {
		return fmt.Errorf("projects remove: no project named %q is registered", rest[0])
	}
	delete(entries, rest[0])
	return projectreg.Save(entries)
}
