package fleetstate

import (
	"path/filepath"
	"testing"
	"time"
)

func TestLoadMissingFileReturnsEmptyState(t *testing.T) {
	s, err := Load(filepath.Join(t.TempDir(), "does-not-exist.json"))
	if err != nil {
		t.Fatal(err)
	}
	if s.Runs == nil || s.Cooldowns == nil || s.RequeueSeq == nil {
		t.Fatalf("Load of a missing file should still initialise maps: %+v", s)
	}
}

func TestSaveLoadRoundTrip(t *testing.T) {
	path := filepath.Join(t.TempDir(), "state.json")
	s := New()
	s.Repo = "/repo"
	s.Queue = []string{"a", "b"}
	s.Runs["a"] = &RunRecord{
		Spec:   RunSpec{ID: "a", File: "disasm/src/x.c", Owners: []string{"func_1"}, Agent: "codex"},
		Status: StatusQueued,
	}
	s.Cooldowns["kimi"] = time.Now().Add(5 * time.Hour).UTC().Truncate(time.Second)

	if err := s.SaveAtomic(path); err != nil {
		t.Fatal(err)
	}
	loaded, err := Load(path)
	if err != nil {
		t.Fatal(err)
	}
	if loaded.Repo != "/repo" || len(loaded.Queue) != 2 {
		t.Fatalf("round trip mismatch: %+v", loaded)
	}
	if loaded.Runs["a"].Spec.File != "disasm/src/x.c" {
		t.Fatalf("round trip run record mismatch: %+v", loaded.Runs["a"])
	}
	if !loaded.Cooldowns["kimi"].Equal(s.Cooldowns["kimi"]) {
		t.Fatalf("round trip cooldown mismatch: got %v want %v", loaded.Cooldowns["kimi"], s.Cooldowns["kimi"])
	}

	// No stray temp files should be left behind.
	entries, err := filepath.Glob(filepath.Join(filepath.Dir(path), ".state-*"))
	if err != nil {
		t.Fatal(err)
	}
	if len(entries) != 0 {
		t.Fatalf("leftover temp files: %v", entries)
	}
}

func TestOnCooldown(t *testing.T) {
	s := New()
	now := time.Now()
	s.Cooldowns["kimi"] = now.Add(time.Hour)
	if !s.OnCooldown("kimi", now) {
		t.Fatal("kimi should be on cooldown")
	}
	if s.OnCooldown("kimi", now.Add(2*time.Hour)) {
		t.Fatal("kimi's cooldown should have expired")
	}
	if s.OnCooldown("codex", now) {
		t.Fatal("codex has no cooldown entry at all")
	}
}

func TestRunningCount(t *testing.T) {
	s := New()
	s.Runs["a"] = &RunRecord{Spec: RunSpec{Agent: "codex"}, Status: StatusRunning}
	s.Runs["b"] = &RunRecord{Spec: RunSpec{Agent: "codex"}, Status: StatusRunning}
	s.Runs["c"] = &RunRecord{Spec: RunSpec{Agent: "kimi"}, Status: StatusRunning}
	s.Runs["d"] = &RunRecord{Spec: RunSpec{Agent: "kimi"}, Status: StatusQueued}

	total, byAgent := s.RunningCount()
	if total != 3 {
		t.Fatalf("total = %d, want 3", total)
	}
	if byAgent["codex"] != 2 || byAgent["kimi"] != 1 {
		t.Fatalf("byAgent = %+v", byAgent)
	}
}

func TestNextRequeueID(t *testing.T) {
	s := New()
	if got := s.NextRequeueID("14640-p0"); got != "14640-p0-r1" {
		t.Fatalf("got %q", got)
	}
	if got := s.NextRequeueID("14640-p0"); got != "14640-p0-r2" {
		t.Fatalf("got %q", got)
	}
	if got := s.NextRequeueID("other"); got != "other-r1" {
		t.Fatalf("got %q", got)
	}
}
