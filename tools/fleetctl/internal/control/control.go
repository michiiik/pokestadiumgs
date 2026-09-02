// Package control implements fleetctl's control loop: the state machine
// documented in docs/FLEET_CONTROLLER.md (queued -> running -> merging ->
// done|requeued). It launches containers up to a concurrency cap, polls
// them, and on exit either cools an exhausted agent down and resumes the
// same run, or hands off to the sequential merge/branch/PR step and
// requeues any owners that merge left unmatched. Every external effect goes
// through a runner.Runner so this package is fully unit-testable with
// runner.Fake.
package control

import (
	"context"
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"
	"time"

	"fleetctl/internal/fleetstate"
	"fleetctl/internal/planpkg"
	"fleetctl/internal/runner"
)

// Loop holds everything the control loop needs. Zero-value numeric/duration
// fields fall back to sensible defaults (see MaxConcurrentOrDefault,
// pollInterval, cooldownFor).
type Loop struct {
	Runner runner.Runner
	State  *fleetstate.State

	// StatePath is where State is persisted after every mutation.
	StatePath string
	// RunsDir is the parent of every run's own --out directory
	// (<RunsDir>/<run-id>).
	RunsDir string
	// Repo is the checkout container/run.sh, tools/pragma_targets.py, and
	// tools/container_merge.py are invoked from, and the checkout branches,
	// commits, and PRs are made against.
	Repo string
	// IntegrationBranch is the branch a run's throwaway container/<id>
	// branch is created from and, on a matched owner, PR'd back into.
	IntegrationBranch string

	MaxConcurrent    int
	AgentConcurrency map[string]int
	CooldownDefaults map[string]time.Duration
	DefaultCooldown  time.Duration
	PollInterval     time.Duration

	// Now is an injectable clock (tests only); nil uses time.Now.
	Now func() time.Time
	// Log receives one line per structured log event; nil uses fmt.Println.
	Log func(string)
}

func (l *Loop) now() time.Time {
	if l.Now != nil {
		return l.Now()
	}
	return time.Now()
}

func (l *Loop) logf(format string, args ...any) {
	line := fmt.Sprintf(format, args...)
	if l.Log != nil {
		l.Log(line)
		return
	}
	fmt.Println(line)
}

func (l *Loop) maxConcurrent() int {
	if l.MaxConcurrent > 0 {
		return l.MaxConcurrent
	}
	return 4
}

func (l *Loop) pollInterval() time.Duration {
	if l.PollInterval > 0 {
		return l.PollInterval
	}
	return 30 * time.Second
}

func (l *Loop) cooldownFor(agent string) time.Duration {
	if d, ok := l.CooldownDefaults[agent]; ok {
		return d
	}
	if l.DefaultCooldown > 0 {
		return l.DefaultCooldown
	}
	return time.Hour
}

// LoadPlan merges a plan's queue into State, skipping any run id already
// known (so loading the same plan into an existing state dir twice --
// e.g. a restarted `fleetctl run` -- is idempotent) and adopting the plan's
// cooldown defaults / per-agent concurrency caps unless the Loop already has
// its own (a caller-set field always wins).
func (l *Loop) LoadPlan(p *planpkg.Plan) error {
	if l.State.Repo == "" {
		l.State.Repo = p.Repo
	}
	if l.AgentConcurrency == nil && len(p.AgentConcurrency) > 0 {
		l.AgentConcurrency = p.AgentConcurrency
	}
	if l.CooldownDefaults == nil && len(p.Cooldowns) > 0 {
		parsed := make(map[string]time.Duration, len(p.Cooldowns))
		for agent, s := range p.Cooldowns {
			d, err := time.ParseDuration(s)
			if err != nil {
				return fmt.Errorf("control: plan cooldown %s=%q: %w", agent, s, err)
			}
			parsed[agent] = d
		}
		l.CooldownDefaults = parsed
	}
	for _, spec := range p.Queue {
		if _, exists := l.State.Runs[spec.ID]; exists {
			continue
		}
		l.State.Runs[spec.ID] = &fleetstate.RunRecord{Spec: spec, Status: fleetstate.StatusQueued}
		l.State.Queue = append(l.State.Queue, spec.ID)
	}
	return nil
}

// RunOnce performs exactly one control-loop pass: poll every running
// container, handle any that exited, then launch newly-eligible queued
// runs up to the concurrency caps. It reports whether there is still work
// left (something running or queued) so Run knows whether to keep looping.
func (l *Loop) RunOnce(ctx context.Context) (bool, error) {
	if err := l.pollRunning(ctx); err != nil {
		return false, err
	}
	if err := l.launchEligible(ctx); err != nil {
		return false, err
	}
	total, _ := l.State.RunningCount()
	return total > 0 || len(l.State.Queue) > 0, nil
}

// Run drives RunOnce to completion: repeatedly, persisting state after
// every pass, sleeping pollInterval between passes, until either --once is
// set (a single pass, used by the --dry-run smoke test) or no work remains.
func (l *Loop) Run(ctx context.Context, once bool) error {
	for {
		stillWork, err := l.RunOnce(ctx)
		if saveErr := l.State.SaveAtomic(l.StatePath); saveErr != nil && err == nil {
			err = saveErr
		}
		if err != nil {
			return err
		}
		if once || !stillWork {
			return nil
		}
		select {
		case <-ctx.Done():
			return ctx.Err()
		case <-time.After(l.pollInterval()):
		}
	}
}

// pollRunning inspects every run currently marked Running and hands exited
// (or vanished) ones to handleExit.
func (l *Loop) pollRunning(ctx context.Context) error {
	for _, rec := range l.State.Runs {
		if rec.Status != fleetstate.StatusRunning {
			continue
		}
		res, err := l.Runner.InspectContainer(ctx, rec.ContainerID)
		if err != nil {
			l.logf("run %s: inspect %s failed: %v", rec.Spec.ID, rec.ContainerID, err)
			continue
		}
		if res.Found && res.Running {
			continue
		}
		if err := l.handleExit(ctx, rec); err != nil {
			l.logf("run %s: %v", rec.Spec.ID, err)
		}
	}
	return nil
}

type summaryDoc struct {
	StoppedReason string `json:"stopped_reason"`
}

func loadSummary(outDir string) (*summaryDoc, error) {
	data, err := os.ReadFile(filepath.Join(outDir, "summary.json"))
	if err != nil {
		return nil, err
	}
	var s summaryDoc
	if err := json.Unmarshal(data, &s); err != nil {
		return nil, err
	}
	return &s, nil
}

// handleExit is the exit-handling switch described in
// docs/CONTAINER_AGENT.md's output contract and the fleetctl task: a
// container that vanished without a readable summary.json is requeued with
// --resume, same as generator_exhausted (after also cooling that agent
// down); every other stopped_reason (budget_expired, plateau, a normal
// completion, no_owners, ...) hands off to the sequential merge step.
func (l *Loop) handleExit(ctx context.Context, rec *fleetstate.RunRecord) error {
	rec.EndedAt = l.now()
	summary, err := loadSummary(rec.OutDir)
	if err != nil {
		l.logf("run %s: no readable summary.json (%v); requeueing with --resume", rec.Spec.ID, err)
		rec.Status = fleetstate.StatusRequeued
		rec.StoppedReason = ""
		rec.Note = "vanished without summary.json"
		l.requeueResume(rec)
		return nil
	}
	rec.StoppedReason = summary.StoppedReason

	if summary.StoppedReason == "generator_exhausted" {
		until := l.now().Add(l.cooldownFor(rec.Spec.Agent))
		l.State.Cooldowns[rec.Spec.Agent] = until
		l.logf("run %s: agent %s generator_exhausted; cooldown until %s, requeueing with --resume",
			rec.Spec.ID, rec.Spec.Agent, until.Format(time.RFC3339))
		rec.Status = fleetstate.StatusRequeued
		rec.Note = "generator_exhausted"
		l.requeueResume(rec)
		return nil
	}

	l.logf("run %s: stopped_reason=%s, merging", rec.Spec.ID, summary.StoppedReason)
	rec.Status = fleetstate.StatusMerging
	return l.runMerge(ctx, rec)
}

// requeueResume puts rec.Spec.ID back on the queue tail for another attempt
// against the SAME out dir (Attempt>0 launches with --resume, per
// docs/CONTAINER_AGENT.md: --resume and --seed-from are mutually exclusive,
// so a resumed spec keeps whatever SeedDirs it already had from its
// original launch and does not gain new ones).
func (l *Loop) requeueResume(rec *fleetstate.RunRecord) {
	rec.Spec.Attempt++
	l.State.Queue = append(l.State.Queue, rec.Spec.ID)
}

func branchName(spec fleetstate.RunSpec) string {
	return "container/" + spec.ID
}

type mergeReportDoc struct {
	CCCheckBypassed bool              `json:"cc_check_bypassed"`
	FreshHistory    bool              `json:"fresh_history"`
	Owners          map[string]string `json:"owners"`
}

func loadMergeReport(outDir string) mergeReportDoc {
	data, err := os.ReadFile(filepath.Join(outDir, "merge-report.json"))
	if err != nil {
		return mergeReportDoc{Owners: map[string]string{}}
	}
	var doc mergeReportDoc
	if err := json.Unmarshal(data, &doc); err != nil || doc.Owners == nil {
		return mergeReportDoc{Owners: map[string]string{}}
	}
	return doc
}

func ownersWithStatus(report map[string]string, status string) []string {
	var out []string
	for owner, s := range report {
		if s == status {
			out = append(out, owner)
		}
	}
	sort.Strings(out)
	return out
}

func subtract(all, remove []string) []string {
	skip := make(map[string]bool, len(remove))
	for _, o := range remove {
		skip[o] = true
	}
	var out []string
	for _, o := range all {
		if !skip[o] {
			out = append(out, o)
		}
	}
	return out
}

func buildPRBody(rec *fleetstate.RunRecord, report mergeReportDoc) string {
	var b strings.Builder
	fmt.Fprintf(&b, "Container match run `%s` (file `%s`, agent `%s:%s%s`).\n\n",
		rec.Spec.ID, rec.Spec.File, rec.Spec.Agent, rec.Spec.Model, effortSuffix(rec.Spec.Effort))
	if report.CCCheckBypassed {
		b.WriteString("**Warning:** merged with `--no-cc-check` was NOT used here; see merge-report.json.\n\n")
	}
	b.WriteString("| Owner | Host re-gate status |\n|---|---|\n")
	owners := append([]string(nil), rec.Spec.Owners...)
	sort.Strings(owners)
	for _, o := range owners {
		status := report.Owners[o]
		if status == "" {
			status = "not attempted"
		}
		fmt.Fprintf(&b, "| %s | %s |\n", o, status)
	}
	return b.String()
}

func effortSuffix(effort string) string {
	if effort == "" {
		return ""
	}
	return ":" + effort
}

// runMerge is the sequential merge/branch/PR step. The control loop never
// runs two of these concurrently -- RunOnce/pollRunning call it in a plain
// for loop with no goroutines, which is itself the mutex the task asks for
// (see docs/FLEET_CONTROLLER.md).
func (l *Loop) runMerge(ctx context.Context, rec *fleetstate.RunRecord) error {
	branch := branchName(rec.Spec)

	if err := l.Runner.GitCheckout(ctx, l.Repo, l.IntegrationBranch); err != nil {
		return fmt.Errorf("checkout %s before branching: %w", l.IntegrationBranch, err)
	}
	if err := l.Runner.GitCheckoutNewBranch(ctx, l.Repo, branch, l.IntegrationBranch); err != nil {
		return fmt.Errorf("create branch %s: %w", branch, err)
	}
	rec.Branch = branch

	// Commits, if any, land on `branch` because it is already checked out.
	if _, err := l.Runner.Merge(ctx, runner.MergeSpec{
		OutDir: rec.OutDir, RepoRoot: l.Repo, FreshHistory: true, Commit: true,
	}); err != nil {
		l.logf("run %s: merge step error: %v", rec.Spec.ID, err)
	}
	if _, err := l.Runner.ImportStats(ctx, rec.OutDir, l.Repo); err != nil {
		l.logf("run %s: import-stats error: %v", rec.Spec.ID, err)
	}

	report := loadMergeReport(rec.OutDir)
	accepted := ownersWithStatus(report.Owners, "accepted")
	rec.MatchedOwners = accepted

	if len(accepted) > 0 {
		if err := l.Runner.GitPush(ctx, l.Repo, branch); err != nil {
			l.logf("run %s: git push %s failed: %v", rec.Spec.ID, branch, err)
		} else {
			title := fmt.Sprintf("Container match: %s", strings.Join(accepted, ", "))
			url, err := l.Runner.GhPRCreate(ctx, runner.PRSpec{
				RepoRoot: l.Repo, Base: l.IntegrationBranch, Title: title, Body: buildPRBody(rec, report),
			})
			if err != nil {
				l.logf("run %s: gh pr create failed: %v", rec.Spec.ID, err)
			} else {
				rec.PRURL = url
				l.logf("run %s: opened PR %s for %d matched owner(s)", rec.Spec.ID, url, len(accepted))
			}
		}
	} else {
		l.logf("run %s: no owners matched this run", rec.Spec.ID)
	}

	if err := l.Runner.GitCheckout(ctx, l.Repo, l.IntegrationBranch); err != nil {
		l.logf("run %s: checkout back to %s failed: %v", rec.Spec.ID, l.IntegrationBranch, err)
	}

	rec.Status = fleetstate.StatusDone

	unmatched := subtract(rec.Spec.Owners, accepted)
	if len(unmatched) > 0 {
		newID := l.State.NextRequeueID(rec.Spec.ID)
		newSpec := fleetstate.RunSpec{
			ID:            newID,
			File:          rec.Spec.File,
			Owners:        unmatched,
			Agent:         rec.Spec.Agent,
			Model:         rec.Spec.Model,
			Effort:        rec.Spec.Effort,
			BudgetSeconds: rec.Spec.BudgetSeconds,
			SeedDirs:      append(append([]string(nil), rec.Spec.SeedDirs...), rec.OutDir),
		}
		l.State.Runs[newID] = &fleetstate.RunRecord{Spec: newSpec, Status: fleetstate.StatusQueued}
		l.State.Queue = append(l.State.Queue, newID)
		l.logf("run %s: %d unmatched owner(s) requeued as %s with fresh seeds", rec.Spec.ID, len(unmatched), newID)
	}
	return nil
}

// launchEligible walks the queue in order, launching every entry whose
// agent is neither on cooldown nor at its per-agent concurrency cap, until
// the global concurrency cap is reached. An ineligible entry is left in
// the queue (in place) rather than skipped permanently, so it is retried
// on the next pass once capacity frees up.
func (l *Loop) launchEligible(ctx context.Context) error {
	if len(l.State.Queue) == 0 {
		return nil
	}
	totalRunning, byAgent := l.State.RunningCount()
	now := l.now()
	max := l.maxConcurrent()

	remaining := l.State.Queue[:0:0]
	for _, id := range l.State.Queue {
		rec := l.State.Runs[id]
		if rec == nil {
			continue
		}
		switch {
		case totalRunning >= max:
			remaining = append(remaining, id)
		case l.State.OnCooldown(rec.Spec.Agent, now):
			remaining = append(remaining, id)
		case l.AgentConcurrency[rec.Spec.Agent] > 0 && byAgent[rec.Spec.Agent] >= l.AgentConcurrency[rec.Spec.Agent]:
			remaining = append(remaining, id)
		default:
			if err := l.launch(ctx, rec); err != nil {
				l.logf("run %s: launch failed: %v", id, err)
				remaining = append(remaining, id)
				continue
			}
			totalRunning++
			byAgent[rec.Spec.Agent]++
		}
	}
	l.State.Queue = remaining
	return nil
}

func (l *Loop) launch(ctx context.Context, rec *fleetstate.RunRecord) error {
	outDir := filepath.Join(l.RunsDir, rec.Spec.ID)
	if err := os.MkdirAll(outDir, 0o755); err != nil {
		return fmt.Errorf("mkdir %s: %w", outDir, err)
	}
	seedFrom, err := prepareSeeds(outDir, rec.Spec.SeedDirs)
	if err != nil {
		return err
	}
	spec := runner.LaunchSpec{
		SourceFile:    rec.Spec.File,
		OutDir:        outDir,
		BudgetSeconds: rec.Spec.BudgetSeconds,
		Owners:        rec.Spec.Owners,
		SeedFrom:      seedFrom,
		Resume:        rec.Spec.Attempt > 0,
		Agent:         rec.Spec.Agent,
		Model:         rec.Spec.Model,
		Effort:        rec.Spec.Effort,
	}
	id, err := l.Runner.LaunchContainer(ctx, spec)
	if err != nil {
		return err
	}
	rec.ContainerID = id
	rec.OutDir = outDir
	rec.Status = fleetstate.StatusRunning
	rec.StartedAt = l.now()
	rec.EndedAt = time.Time{}
	rec.StoppedReason = ""
	l.logf("run %s: launched container %s (agent=%s:%s owners=%d resume=%v seeds=%d)",
		rec.Spec.ID, id, rec.Spec.Agent, rec.Spec.Model, len(rec.Spec.Owners), spec.Resume, len(seedFrom))
	return nil
}

// prepareSeeds copies each prior out dir's state.json + accepted/ into
// <outDir>/seeds/<name>/ and returns the in-container paths to pass via
// --seed-from -- only /out is mounted in the new container, so an earlier
// run's own host out dir is never directly reachable (see
// docs/CONTAINER_AGENT.md sec 2.1).
func prepareSeeds(outDir string, seedDirs []string) ([]string, error) {
	if len(seedDirs) == 0 {
		return nil, nil
	}
	var refs []string
	used := map[string]int{}
	for _, src := range seedDirs {
		name := filepath.Base(src)
		if n := used[name]; n > 0 {
			name = fmt.Sprintf("%s-%d", name, n)
		}
		used[filepath.Base(src)]++
		dst := filepath.Join(outDir, "seeds", name)
		if err := copySeedTree(src, dst); err != nil {
			return nil, fmt.Errorf("seed from %s: %w", src, err)
		}
		refs = append(refs, "/out/seeds/"+name)
	}
	return refs, nil
}

func copySeedTree(src, dst string) error {
	if err := os.MkdirAll(dst, 0o755); err != nil {
		return err
	}
	if data, err := os.ReadFile(filepath.Join(src, "state.json")); err == nil {
		if err := os.WriteFile(filepath.Join(dst, "state.json"), data, 0o644); err != nil {
			return err
		}
	} else if !os.IsNotExist(err) {
		return err
	}
	acceptedSrc := filepath.Join(src, "accepted")
	entries, err := os.ReadDir(acceptedSrc)
	if err != nil {
		if os.IsNotExist(err) {
			return nil
		}
		return err
	}
	acceptedDst := filepath.Join(dst, "accepted")
	if err := os.MkdirAll(acceptedDst, 0o755); err != nil {
		return err
	}
	for _, e := range entries {
		if e.IsDir() {
			continue
		}
		data, err := os.ReadFile(filepath.Join(acceptedSrc, e.Name()))
		if err != nil {
			return err
		}
		if err := os.WriteFile(filepath.Join(acceptedDst, e.Name()), data, 0o644); err != nil {
			return err
		}
	}
	return nil
}

// StopRun stops exactly one run's container, by the container id recorded
// in state -- never by a filter, and never a run id state does not know
// about.
func (l *Loop) StopRun(ctx context.Context, id string) error {
	rec, ok := l.State.Runs[id]
	if !ok {
		return fmt.Errorf("stop: run id %q not found in state", id)
	}
	if rec.Status != fleetstate.StatusRunning || rec.ContainerID == "" {
		return fmt.Errorf("stop: run id %q has no running container (status=%s)", id, rec.Status)
	}
	if err := l.Runner.StopContainer(ctx, rec.ContainerID); err != nil {
		return err
	}
	rec.Status = fleetstate.StatusRequeued
	rec.Note = "stopped by operator"
	rec.EndedAt = l.now()
	return l.State.SaveAtomic(l.StatePath)
}

// StopAll stops every run currently Running, each strictly by its own
// recorded container id.
func (l *Loop) StopAll(ctx context.Context) error {
	var firstErr error
	ids := make([]string, 0, len(l.State.Runs))
	for id := range l.State.Runs {
		ids = append(ids, id)
	}
	sort.Strings(ids)
	for _, id := range ids {
		rec := l.State.Runs[id]
		if rec.Status != fleetstate.StatusRunning || rec.ContainerID == "" {
			continue
		}
		if err := l.Runner.StopContainer(ctx, rec.ContainerID); err != nil {
			l.logf("stop %s: %v", id, err)
			if firstErr == nil {
				firstErr = err
			}
			continue
		}
		rec.Status = fleetstate.StatusRequeued
		rec.Note = "stopped by operator"
		rec.EndedAt = l.now()
	}
	if err := l.State.SaveAtomic(l.StatePath); err != nil && firstErr == nil {
		firstErr = err
	}
	return firstErr
}
