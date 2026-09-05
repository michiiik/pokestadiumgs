package projectreg

import (
	"path/filepath"
	"strings"
	"testing"
)

// withHome points $HOME at a fresh temp dir for the duration of one test,
// so Path()/Load()/Save() never touch the real developer's
// ~/.config/fleetctl/projects.json.
func withHome(t *testing.T) string {
	t.Helper()
	dir := t.TempDir()
	t.Setenv("HOME", dir)
	return dir
}

func TestLoadWithNoRegistryFileYetIsEmptyNotAnError(t *testing.T) {
	withHome(t)
	entries, err := Load()
	if err != nil {
		t.Fatal(err)
	}
	if len(entries) != 0 {
		t.Fatalf("entries = %+v, want empty", entries)
	}
}

func TestSaveThenLoadRoundTrips(t *testing.T) {
	home := withHome(t)
	if err := Save(map[string]string{"stadium2": "/a/b/fleet-state"}); err != nil {
		t.Fatal(err)
	}
	path, err := Path()
	if err != nil {
		t.Fatal(err)
	}
	if want := filepath.Join(home, ".config", "fleetctl", "projects.json"); path != want {
		t.Fatalf("Path() = %s, want %s", path, want)
	}
	entries, err := Load()
	if err != nil {
		t.Fatal(err)
	}
	if entries["stadium2"] != "/a/b/fleet-state" {
		t.Fatalf("entries = %+v", entries)
	}
}

func TestResolveUnknownNameReturnsAHelpfulError(t *testing.T) {
	withHome(t)
	_, err := Resolve("nope")
	if err == nil {
		t.Fatal("want an error for an unregistered name")
	}
	if got := err.Error(); !strings.Contains(got, "nope") || !strings.Contains(got, "fleetctl projects") {
		t.Fatalf("error = %q, want it to name the lookup and point at `fleetctl projects`", got)
	}
}

func TestResolveKnownNameReturnsItsStateDir(t *testing.T) {
	withHome(t)
	if err := Save(map[string]string{"stadium2": "/a/b/fleet-state"}); err != nil {
		t.Fatal(err)
	}
	dir, err := Resolve("stadium2")
	if err != nil {
		t.Fatal(err)
	}
	if dir != "/a/b/fleet-state" {
		t.Fatalf("dir = %q", dir)
	}
}

func TestNamesIsSorted(t *testing.T) {
	got := Names(map[string]string{"zzz": "x", "aaa": "y", "mmm": "z"})
	want := []string{"aaa", "mmm", "zzz"}
	if len(got) != len(want) {
		t.Fatalf("Names() = %v", got)
	}
	for i := range want {
		if got[i] != want[i] {
			t.Fatalf("Names() = %v, want %v", got, want)
		}
	}
}
