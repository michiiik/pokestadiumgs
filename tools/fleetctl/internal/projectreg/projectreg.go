// Package projectreg is a small machine-local registry mapping a short
// project name (e.g. "stadium2") to a --state-dir path, so a host that
// only ever points fleetctl at a handful of repos can run `fleetctl status
// stadium2` instead of typing the full --state-dir path every time. See
// `fleetctl projects` (cmd_projects.go) for the CLI that manages it.
//
// The registry is deliberately not part of any repo's checked-in state: it
// lives under the user's home directory (like a shell rc file), one entry
// per project this machine operates on, independent of which repo/worktree
// happens to be current.
package projectreg

import (
	"encoding/json"
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"sort"
)

// Path returns the registry file's location: ~/.config/fleetctl/projects.json.
func Path() (string, error) {
	home, err := os.UserHomeDir()
	if err != nil {
		return "", fmt.Errorf("projectreg: %w", err)
	}
	return filepath.Join(home, ".config", "fleetctl", "projects.json"), nil
}

// Load returns the registry's current {name: state-dir} entries. A
// registry that does not exist yet (nothing has ever been registered) is
// not an error -- it loads as empty.
func Load() (map[string]string, error) {
	path, err := Path()
	if err != nil {
		return nil, err
	}
	data, err := os.ReadFile(path)
	if errors.Is(err, os.ErrNotExist) {
		return map[string]string{}, nil
	}
	if err != nil {
		return nil, fmt.Errorf("projectreg: read %s: %w", path, err)
	}
	entries := map[string]string{}
	if err := json.Unmarshal(data, &entries); err != nil {
		return nil, fmt.Errorf("projectreg: parse %s: %w", path, err)
	}
	return entries, nil
}

// Save writes entries back to the registry file, creating its parent
// directory if this is the first entry ever registered.
func Save(entries map[string]string) error {
	path, err := Path()
	if err != nil {
		return err
	}
	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		return fmt.Errorf("projectreg: %w", err)
	}
	data, err := json.MarshalIndent(entries, "", "  ")
	if err != nil {
		return fmt.Errorf("projectreg: %w", err)
	}
	data = append(data, '\n')
	if err := os.WriteFile(path, data, 0o644); err != nil {
		return fmt.Errorf("projectreg: write %s: %w", path, err)
	}
	return nil
}

// Resolve looks up name's registered state-dir. The error message is
// meant to be shown to a user directly (it names the failing lookup and
// points at `fleetctl projects list`).
func Resolve(name string) (string, error) {
	entries, err := Load()
	if err != nil {
		return "", err
	}
	dir, ok := entries[name]
	if !ok {
		return "", fmt.Errorf("no project named %q is registered (see `fleetctl projects list`, or register one with `fleetctl projects set %s <state-dir>`)", name, name)
	}
	return dir, nil
}

// Names returns every registered project name, sorted, for `fleetctl
// projects list`.
func Names(entries map[string]string) []string {
	names := make([]string, 0, len(entries))
	for name := range entries {
		names = append(names, name)
	}
	sort.Strings(names)
	return names
}
