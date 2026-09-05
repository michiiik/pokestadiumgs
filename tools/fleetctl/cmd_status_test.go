package main

import (
	"testing"

	"fleetctl/internal/projectreg"
)

// TestResolveStateDir pins the "--state-dir, or a registered project name"
// contract: an explicit --state-dir always wins outright (even over a
// registered name of the same string, which would otherwise be ambiguous);
// a lone positional arg is looked up in the registry; zero or 2+
// positional args without --state-dir are errors.
func TestResolveStateDir(t *testing.T) {
	t.Setenv("HOME", t.TempDir())
	if err := projectreg.Save(map[string]string{"stadium2": "/a/b/fleet-state"}); err != nil {
		t.Fatal(err)
	}

	cases := []struct {
		name       string
		flagValue  string
		positional []string
		want       string
		wantErr    bool
	}{
		{"explicit --state-dir, no positional", "/explicit/dir", nil, "/explicit/dir", false},
		{"registered name resolves", "", []string{"stadium2"}, "/a/b/fleet-state", false},
		{"--state-dir wins over a positional name", "/explicit/dir", []string{"stadium2"}, "/explicit/dir", false},
		{"unregistered name errors", "", []string{"nope"}, "", true},
		{"neither given errors", "", nil, "", true},
		{"too many positional args errors", "", []string{"a", "b"}, "", true},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			got, err := resolveStateDir(c.flagValue, c.positional)
			if c.wantErr {
				if err == nil {
					t.Fatalf("resolveStateDir(%q, %v) = %q, nil; want an error", c.flagValue, c.positional, got)
				}
				return
			}
			if err != nil {
				t.Fatalf("resolveStateDir(%q, %v) error: %v", c.flagValue, c.positional, err)
			}
			if got != c.want {
				t.Fatalf("resolveStateDir(%q, %v) = %q, want %q", c.flagValue, c.positional, got, c.want)
			}
		})
	}
}
