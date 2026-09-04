package control

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"sort"

	"fleetctl/internal/fleetstate"
	"fleetctl/internal/planpkg"
)

// permuterAgent is the internal agent name the control loop assigns to
// every permuter-only-lane partition it creates itself (docs sec 13). It is
// never a target `fleetctl plan --agent` accepts on the command line -- an
// operator never picks it; enqueuePermuterLane is the only place that ever
// sets RunSpec.Agent to it.
const permuterAgent = "permuter"

// defaultPermuterSeconds is `--permuter-seconds` when neither the run flag
// nor a RunSpec's own PermuterSeconds sets one (sec 13).
const defaultPermuterSeconds = 1200

func (l *Loop) permuterSeconds() int {
	if l.PermuterSeconds > 0 {
		return l.PermuterSeconds
	}
	return defaultPermuterSeconds
}

// TiePoolEntry is one owner's entry of a run's <out>/tie-pool.json --
// {owner: {source, body, declarations, raw, label}} -- written by
// tools/container_agent.py for an owner that plateaued at a register tie or
// a normalized-only match: the candidate the permuter-only lane (sec 13)
// picks up and keeps working.
type TiePoolEntry struct {
	Source       string `json:"source"`
	Body         string `json:"body"`
	Declarations string `json:"declarations,omitempty"`
	Raw          string `json:"raw,omitempty"`
	Label        string `json:"label,omitempty"`
}

// tiePoolStorePath is where every run's tie-pool.json for a given source
// file is collected: <runs-dir>/tie-pools/<fileslug>.json (sec 13).
func tiePoolStorePath(runsDir, file string) string {
	return filepath.Join(runsDir, "tie-pools", planpkg.FileSlug(file)+".json")
}

func loadTiePoolStore(path string) map[string]TiePoolEntry {
	data, err := os.ReadFile(path)
	if err != nil {
		return map[string]TiePoolEntry{}
	}
	var m map[string]TiePoolEntry
	if err := json.Unmarshal(data, &m); err != nil {
		return map[string]TiePoolEntry{}
	}
	return m
}

func saveTiePoolStore(path string, pool map[string]TiePoolEntry) error {
	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		return err
	}
	data, err := json.MarshalIndent(pool, "", "  ")
	if err != nil {
		return err
	}
	return os.WriteFile(path, data, 0o644)
}

// updateTiePool merges rec's own <out>/tie-pool.json (if present -- any
// run, permuter-lane or not, can plateau into one) into
// <runs-dir>/tie-pools/<fileslug>.json, then drops every owner
// rec.MatchedOwners just landed ("owners removed once matched", sec 13).
// Called once per run, at the end of runMerge, after MatchedOwners is
// known. A run with neither a tie-pool.json nor any matched owner already
// in the store is a no-op -- the store is left untouched, not rewritten.
func (l *Loop) updateTiePool(rec *fleetstate.RunRecord) {
	if l.RunsDir == "" {
		return
	}
	path := tiePoolStorePath(l.RunsDir, rec.Spec.File)
	pool := loadTiePoolStore(path)
	changed := false

	if data, err := os.ReadFile(filepath.Join(rec.OutDir, "tie-pool.json")); err == nil {
		var runPool map[string]TiePoolEntry
		if err := json.Unmarshal(data, &runPool); err == nil {
			for owner, entry := range runPool {
				pool[owner] = entry
				changed = true
			}
		}
	}
	for _, owner := range rec.MatchedOwners {
		if _, ok := pool[owner]; ok {
			delete(pool, owner)
			changed = true
		}
	}
	if !changed {
		return
	}
	if err := saveTiePoolStore(path, pool); err != nil {
		l.logf("run %s: tie-pool store %s: %v", rec.Spec.ID, path, err)
	}
}

// permuterActiveStatuses are the RunRecord statuses permuterInFlight treats
// as "still holding this file" -- everything short of a terminal outcome
// (done/merged/gate_failed), matching reconcileQueue's own notion of
// "in flight".
var permuterActiveStatuses = map[fleetstate.Status]bool{
	fleetstate.StatusQueued:            true,
	fleetstate.StatusRunning:           true,
	fleetstate.StatusMerging:           true,
	fleetstate.StatusPROpen:            true,
	fleetstate.StatusRequeued:          true,
	fleetstate.StatusMergeBlockedDirty: true,
}

// permuterInFlight reports whether a permuter-lane run for file is already
// active (sec 13) -- enqueuePermuterLane skips creating a duplicate
// partition while one is still active, whatever its current owner list.
func (l *Loop) permuterInFlight(file string) bool {
	for _, rec := range l.State.Runs {
		if rec.Spec.Agent == permuterAgent && rec.Spec.File == file && permuterActiveStatuses[rec.Status] {
			return true
		}
	}
	return false
}

// enqueuePermuterLane is Replan's last step (sec 13): for every
// <runs-dir>/tie-pools/*.json store with at least one still-pending owner
// and no permuter-lane run already in flight for it, enqueue one fresh
// permuter-only partition covering every pending owner in that store --
// except any owner inFlightOwners says an ordinary (non-permuter) run
// already has a live claim on right now.
//
// Without that check, this used to build the permuter partition straight
// from the tie-pool store with no cross-check against ordinary runs at
// all: a run's own plateau/tie result feeds BOTH the tie-pool store
// (updateTiePool, in runMerge) AND that same run's own unmatched-owner
// reseed (a fresh ordinary partition with SeedDirs) for another normal
// attempt -- from the very same runMerge call. permuterInFlight only ever
// asked "is there already a permuter-lane run for this file", never
// "does some *ordinary* run already have this exact owner" -- so the next
// replan could launch a permuter-only container onto an owner an ordinary
// reseeded partition was already actively attempting, two containers
// burning real work on the identical function at the same time.
func (l *Loop) enqueuePermuterLane() {
	if l.RunsDir == "" {
		return
	}
	dir := filepath.Join(l.RunsDir, "tie-pools")
	entries, err := os.ReadDir(dir)
	if err != nil {
		return // no tie-pools directory yet -- nothing pending.
	}
	names := make([]string, 0, len(entries))
	for _, e := range entries {
		if !e.IsDir() && filepath.Ext(e.Name()) == ".json" {
			names = append(names, e.Name())
		}
	}
	sort.Strings(names)

	inFlight := l.inFlightOwners()

	for _, name := range names {
		pool := loadTiePoolStore(filepath.Join(dir, name))
		if len(pool) == 0 {
			continue
		}
		file, owners := tiePoolFileAndOwners(pool)
		if file == "" || l.permuterInFlight(file) {
			continue
		}
		var available []string
		for _, o := range owners {
			if !inFlight[file][o] {
				available = append(available, o)
			}
		}
		if len(available) == 0 {
			// Every pending tie-pool owner already has a live claim
			// elsewhere (most likely that same owner's own ordinary
			// reseed) -- nothing left for the permuter lane to add right
			// now; it'll be reconsidered on the next replan.
			continue
		}
		owners = available
		slug := planpkg.FileSlug(file)
		id := slug + "-permuter"
		if _, exists := l.State.Runs[id]; exists {
			id = l.State.NextRequeueID(id)
		}
		spec := fleetstate.RunSpec{
			ID: id, File: file, Owners: owners, Agent: permuterAgent,
			Mode: "permuter-only", PermuterSeconds: l.permuterSeconds(),
		}
		l.State.Runs[id] = &fleetstate.RunRecord{Spec: spec, Status: fleetstate.StatusQueued}
		l.State.Queue = append(l.State.Queue, id)
		l.logf("permuter lane: enqueued %s for %s (%d pending tie-pool owner(s))", id, file, len(owners))
	}
}

// tiePoolFileAndOwners returns the source file every entry in pool carries
// (each TiePoolEntry names its own owning file, see TiePoolEntry.Source)
// and every owner name, sorted for deterministic RunSpec.Owners ordering.
// "" file means pool was empty -- callers already skip that case.
func tiePoolFileAndOwners(pool map[string]TiePoolEntry) (file string, owners []string) {
	for owner, entry := range pool {
		if file == "" {
			file = entry.Source
		}
		owners = append(owners, owner)
	}
	sort.Strings(owners)
	return file, owners
}

// preparePermuterTiePool copies file's collected tie-pool store into
// <outDir>/tie-pool-input.json and returns the in-container path
// (/out/tie-pool-input.json) launch() passes as LaunchSpec.TiePoolFile
// (sec 13's "after copying the pool file into the out dir").
func preparePermuterTiePool(runsDir, outDir, file string) (string, error) {
	src := tiePoolStorePath(runsDir, file)
	data, err := os.ReadFile(src)
	if err != nil {
		return "", fmt.Errorf("permuter lane: read tie-pool store %s: %w", src, err)
	}
	dst := filepath.Join(outDir, "tie-pool-input.json")
	if err := os.WriteFile(dst, data, 0o644); err != nil {
		return "", fmt.Errorf("permuter lane: write %s: %w", dst, err)
	}
	return "/out/tie-pool-input.json", nil
}
