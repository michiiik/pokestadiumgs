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
	"regexp"
	"sort"
	"strconv"
	"strings"
	"time"

	"fleetctl/internal/agentspec"
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
	// Repo is the checkout container/run.sh and tools/pragma_targets.py are
	// invoked from (a container's launch cwd).
	Repo string
	// MergeRepo is the checkout the merge/branch/PR step -- git checkout,
	// git checkout -b, tools/container_merge.py merge/import-stats, git
	// push, gh pr create -- operates against. Empty means "same as Repo"
	// (see mergeRepo()); a caller only needs to set it when the merge step
	// should run against a different checkout, e.g. a dedicated merge
	// worktree (docs/FLEET_CONTROLLER.md sec 6, "Merge-repo == launch-repo").
	MergeRepo string
	// IntegrationBranch is the branch a run's throwaway container/<id>
	// branch is created from and, on a matched owner, PR'd back into (`gh
	// pr create --base`/`gh pr merge`'s target -- a branch *name*, not a
	// ref, since gh operates on GitHub's own branch, never a local one).
	IntegrationBranch string
	// BaseRef is the ref the merge repo's throwaway branch is force-created
	// from (`git checkout -B`) and left detached at afterward, and the ref
	// a post-merge fetch verifies has advanced -- "" defaults to
	// "origin/<IntegrationBranch>" (see baseRef()). It is deliberately a
	// remote-tracking ref, never IntegrationBranch's own local branch: the
	// merge repo is commonly a linked worktree, and that local branch may
	// already be checked out elsewhere (e.g. the main checkout) -- `git
	// checkout <local-branch>` there fails outright ("already checked
	// out"), so the merge flow never checks out or otherwise touches it
	// (docs/FLEET_CONTROLLER.md sec 2).
	BaseRef string

	MaxConcurrent    int
	AgentConcurrency map[string]int
	CooldownDefaults map[string]time.Duration
	DefaultCooldown  time.Duration
	PollInterval     time.Duration

	// Agents is the plan's own agent roster (planpkg.Plan.Agents, one entry
	// per distinct --agent spec `plan` was given), adopted from LoadPlan
	// unless the caller already set it. It is the pool
	// quota-window-aware scheduling (sec 12) reassigns a cooling-down
	// agent's queued partition to -- a plan with only one agent behaves
	// exactly as before (nothing else to reassign to).
	Agents []agentspec.Spec
	// WindowDurations is the known quota-window length per agent (--window,
	// e.g. kimi=5h), adopted from the plan unless the caller already set
	// it. Read by BuildMetrics (sec 11) to normalize accepts-per-window;
	// falls back to CooldownDefaults, then a 24h default -- see
	// quotaWindowFor.
	WindowDurations map[string]time.Duration
	// WindowBudget is the optional expected-batches-per-window per agent
	// (--window-budget), adopted from the plan unless the caller already
	// set it -- informational only (sec 11).
	WindowBudget map[string]int
	// PermuterSeconds is `--permuter-seconds` forwarded to every
	// permuter-lane launch (sec 13); <=0 defaults to 1200.
	PermuterSeconds int

	// DisableAutoMerge turns off self-merge-on-green (sec 2): a PR is left
	// at StatusDone once opened, same as before self-merge existed, and
	// pollPRs is never called. The zero value (false) matches --auto-merge's
	// own default of true.
	DisableAutoMerge bool

	// SrcOverlay, when set, is forwarded to every launch as env
	// SRC_OVERLAY=<dir> (sec 6) and also suppresses the stale-image check
	// (a launch built from an overlay never runs stale baked-in sources).
	SrcOverlay string
	// ImageRef is the image DockerImageID queries for stale-image awareness
	// (sec 6); "" defaults to "gs-decomp-agent:latest".
	ImageRef string

	// StallAfter is how long a running run's best similarity may sit
	// unimproved before a no_progress_stall alert fires; <=0 defaults to
	// 3h.
	StallAfter time.Duration

	// Notifiers receive every rate-limited alert event (sec 4): gate_failed,
	// ff_failed, container_vanished, agent_exhausted, no_progress_stall,
	// controller_error.
	Notifiers []Notifier
	// DailySummaryNotifier, if set, additionally receives one daily summary
	// post at DailySummaryHourUTC (only --alert-issue posts a daily
	// summary, per sec 4 -- --alert-macos does not).
	DailySummaryNotifier Notifier
	// DailySummaryHourUTC is the UTC hour (0-23) maybeDailySummary fires on.
	DailySummaryHourUTC int

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

// mergeRepo is the checkout the merge/branch/PR step runs against: MergeRepo
// if the caller set one, else Repo.
func (l *Loop) mergeRepo() string {
	if l.MergeRepo != "" {
		return l.MergeRepo
	}
	return l.Repo
}

// baseRef is BaseRef if the caller set one, else "origin/<IntegrationBranch>"
// -- see the Loop.BaseRef doc for why this is a remote-tracking ref, never
// IntegrationBranch's own local branch.
func (l *Loop) baseRef() string {
	if l.BaseRef != "" {
		return l.BaseRef
	}
	return "origin/" + l.IntegrationBranch
}

func (l *Loop) pollInterval() time.Duration {
	if l.PollInterval > 0 {
		return l.PollInterval
	}
	return 30 * time.Second
}

func (l *Loop) autoMergeEnabled() bool {
	return !l.DisableAutoMerge
}

func (l *Loop) stallAfter() time.Duration {
	if l.StallAfter > 0 {
		return l.StallAfter
	}
	return 3 * time.Hour
}

func (l *Loop) imageRef() string {
	if l.ImageRef != "" {
		return l.ImageRef
	}
	return "gs-decomp-agent:latest"
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
	if l.State.MergeRepo == "" {
		l.State.MergeRepo = l.mergeRepo()
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
	if l.WindowDurations == nil && len(p.Windows) > 0 {
		parsed := make(map[string]time.Duration, len(p.Windows))
		for agent, s := range p.Windows {
			d, err := time.ParseDuration(s)
			if err != nil {
				return fmt.Errorf("control: plan window %s=%q: %w", agent, s, err)
			}
			parsed[agent] = d
		}
		l.WindowDurations = parsed
	}
	if l.WindowBudget == nil && len(p.WindowBudget) > 0 {
		l.WindowBudget = p.WindowBudget
	}
	if len(l.Agents) == 0 && len(p.Agents) > 0 {
		l.Agents = p.Agents
	}
	for _, spec := range p.Queue {
		if _, exists := l.State.Runs[spec.ID]; exists {
			continue
		}
		l.State.Runs[spec.ID] = &fleetstate.RunRecord{Spec: spec, Status: fleetstate.StatusQueued}
		l.State.Queue = append(l.State.Queue, spec.ID)
	}
	// Persist the plan itself (not just its queue) so a restarted `run`
	// needs --plan only for this very first load (docs/FLEET_CONTROLLER.md
	// sec 3) and so Replan knows what ranking options to rebuild with (sec
	// 2). Marshal failure is not fatal to loading the plan's queue.
	if data, err := json.Marshal(p); err == nil {
		l.State.PlanJSON = data
	}
	return nil
}

// PersistedPlan unmarshals State.PlanJSON, the plan LoadPlan (or a prior
// Replan) most recently persisted -- nil, false if none has ever been
// loaded into this state.
func (l *Loop) PersistedPlan() (*planpkg.Plan, bool) {
	if len(l.State.PlanJSON) == 0 {
		return nil, false
	}
	var p planpkg.Plan
	if err := json.Unmarshal(l.State.PlanJSON, &p); err != nil {
		return nil, false
	}
	return &p, true
}

// RunOnce performs exactly one control-loop pass: poll every running
// container, handle any that exited, then launch newly-eligible queued
// runs up to the concurrency caps. It reports whether there is still work
// left (something running or queued) so Run knows whether to keep looping.
func (l *Loop) RunOnce(ctx context.Context) (bool, error) {
	if err := l.retryBlockedMergeRuns(ctx); err != nil {
		return false, err
	}
	if err := l.pollRunning(ctx); err != nil {
		return false, err
	}
	if l.autoMergeEnabled() {
		if err := l.pollPRs(ctx); err != nil {
			return false, err
		}
	}
	l.maybeDailySummary(ctx)
	if err := l.launchEligible(ctx); err != nil {
		return false, err
	}
	total, _ := l.State.RunningCount()
	prOpen := l.State.CountByStatus(fleetstate.StatusPROpen)
	// A merge_blocked_dirty run counts as "still work" too -- it is retried
	// at the top of every pass (retryBlockedMergeRuns above), so `run`'s
	// loop must keep polling instead of exiting once it is the only run
	// left, exactly like a stuck MergeBlocked fast-forward already keeps
	// pollPRs (and thus the loop) alive.
	blocked := l.State.CountByStatus(fleetstate.StatusMergeBlockedDirty)
	return total > 0 || len(l.State.Queue) > 0 || prOpen > 0 || blocked > 0, nil
}

// Run drives RunOnce to completion: repeatedly, persisting state after
// every pass, sleeping pollInterval between passes, until either --once is
// set (a single pass, used by the --dry-run smoke test) or no work remains.
func (l *Loop) Run(ctx context.Context, once bool) error {
	for {
		stillWork, err := l.RunOnce(ctx)
		if err != nil {
			l.alert(ctx, "controller_error", "", "fleetctl: control loop error", err.Error())
		}
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
			l.checkStall(ctx, rec)
			continue
		}
		if err := l.handleExit(ctx, rec); err != nil {
			l.logf("run %s: %v", rec.Spec.ID, err)
		}
	}
	return nil
}

// checkStall reads <rec.OutDir>/state.json (container_agent.py's own
// per-owner progress record, saved every iteration -- see
// docs/CONTAINER_AGENT.md) and tracks the best similarity seen across every
// owner this run has attempted. When that best has not improved for
// stallAfter(), it raises a rate-limited no_progress_stall alert (sec 4).
// A missing or unparsable state.json (e.g. the very first poll, before any
// iteration has saved one yet) is silently skipped, not an error.
func (l *Loop) checkStall(ctx context.Context, rec *fleetstate.RunRecord) {
	data, err := os.ReadFile(filepath.Join(rec.OutDir, "state.json"))
	if err != nil {
		return
	}
	var owners map[string]struct {
		BestSimilarity float64 `json:"best_similarity"`
	}
	if err := json.Unmarshal(data, &owners); err != nil {
		return
	}
	var best float64
	for _, o := range owners {
		if o.BestSimilarity > best {
			best = o.BestSimilarity
		}
	}
	now := l.now()
	if rec.BestSimilarityAt.IsZero() || best > rec.BestSimilarity {
		rec.BestSimilarity = best
		rec.BestSimilarityAt = now
		return
	}
	if now.Sub(rec.BestSimilarityAt) >= l.stallAfter() {
		l.alert(ctx, "no_progress_stall", rec.Spec.ID,
			fmt.Sprintf("run %s: no progress for %s", rec.Spec.ID, now.Sub(rec.BestSimilarityAt).Round(time.Minute)),
			fmt.Sprintf("Run %s (file %s, agent %s:%s) best similarity has stayed at %.4f since %s.",
				rec.Spec.ID, rec.Spec.File, rec.Spec.Agent, rec.Spec.Model, rec.BestSimilarity, rec.BestSimilarityAt.Format(time.RFC3339)))
	}
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
		l.alert(ctx, "container_vanished", rec.Spec.ID,
			fmt.Sprintf("run %s: container vanished", rec.Spec.ID),
			fmt.Sprintf("Run %s (file %s, agent %s:%s) had no readable summary.json; requeued with --resume (attempt %d).",
				rec.Spec.ID, rec.Spec.File, rec.Spec.Agent, rec.Spec.Model, rec.Spec.Attempt))
		return nil
	}
	rec.StoppedReason = summary.StoppedReason

	if summary.StoppedReason == "generator_exhausted" {
		// The permuter-lane agent has no generator/model to exhaust and is
		// never subject to cooldown (sec 13) -- if this somehow fires for
		// it anyway, just requeue with --resume, no cooldown/window bookkeeping.
		if rec.Spec.Agent == permuterAgent {
			l.logf("run %s: permuter-lane run reported generator_exhausted (unexpected); requeueing with --resume, no cooldown applied", rec.Spec.ID)
			rec.Status = fleetstate.StatusRequeued
			rec.Note = "generator_exhausted"
			l.requeueResume(rec)
			return nil
		}
		until := l.now().Add(l.cooldownFor(rec.Spec.Agent))
		l.State.Cooldowns[rec.Spec.Agent] = until
		l.recordWindowExhausted(rec.Spec.Agent, l.now())
		l.logf("run %s: agent %s generator_exhausted; cooldown until %s, requeueing with --resume",
			rec.Spec.ID, rec.Spec.Agent, until.Format(time.RFC3339))
		rec.Status = fleetstate.StatusRequeued
		rec.Note = "generator_exhausted"
		l.requeueResume(rec)
		l.alert(ctx, "agent_exhausted", rec.Spec.Agent,
			fmt.Sprintf("agent %s exhausted (cooldown)", rec.Spec.Agent),
			fmt.Sprintf("Agent %s hit generator_exhausted on run %s; cooling down until %s.",
				rec.Spec.Agent, rec.Spec.ID, until.Format(time.RFC3339)))
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

// ownerResult is one entry of merge-report.json's "owners" map, as written
// by tools/container_merge.py's write_merge_report: either a bare status
// string ("accepted" | "rejected" | "error" | "missing_source" | ...), or,
// when a host re-gate accepted but `git commit --only` then failed, an
// object {"status": "accepted", "committed": false, "commit_error": "<tail>"}.
// IsObject distinguishes the two forms -- a bare string never sets
// Committed/CommitError, and (per write_merge_report) is only ever emitted
// for a status that is NOT "accepted and committed==false", so a plain
// string result is trusted as fully matched without checking Committed.
type ownerResult struct {
	Status      string
	Committed   bool
	CommitError string
	IsObject    bool
}

func (o *ownerResult) UnmarshalJSON(data []byte) error {
	var s string
	if err := json.Unmarshal(data, &s); err == nil {
		*o = ownerResult{Status: s}
		return nil
	}
	var obj struct {
		Status      string `json:"status"`
		Committed   bool   `json:"committed"`
		CommitError string `json:"commit_error"`
	}
	if err := json.Unmarshal(data, &obj); err != nil {
		return err
	}
	*o = ownerResult{
		Status: obj.Status, Committed: obj.Committed, CommitError: obj.CommitError, IsObject: true,
	}
	return nil
}

// matched reports whether this owner's candidate is fully installed: the
// host re-gate accepted it AND (it is a plain "accepted" string -- commit
// succeeded or was never attempted, e.g. --commit not passed -- or the
// object form's own committed flag is true).
func (o ownerResult) matched() bool {
	return o.Status == "accepted" && (!o.IsObject || o.Committed)
}

// needsManualCommit reports whether the host re-gate accepted this owner
// but its own `git commit --only` failed -- the candidate is installed in
// the merge repo's working tree but not yet committed.
func (o ownerResult) needsManualCommit() bool {
	return o.Status == "accepted" && o.IsObject && !o.Committed
}

// displayStatus is what buildPRBody's table shows for one owner.
func (o ownerResult) displayStatus() string {
	if o.needsManualCommit() {
		return "accepted, NOT committed (needs manual commit; see fleetctl status)"
	}
	return o.Status
}

type mergeReportDoc struct {
	CCCheckBypassed bool                   `json:"cc_check_bypassed"`
	FreshHistory    bool                   `json:"fresh_history"`
	Owners          map[string]ownerResult `json:"owners"`
}

func loadMergeReport(outDir string) mergeReportDoc {
	data, err := os.ReadFile(filepath.Join(outDir, "merge-report.json"))
	if err != nil {
		return mergeReportDoc{Owners: map[string]ownerResult{}}
	}
	var doc mergeReportDoc
	if err := json.Unmarshal(data, &doc); err != nil || doc.Owners == nil {
		return mergeReportDoc{Owners: map[string]ownerResult{}}
	}
	return doc
}

// matchedOwners returns every owner whose candidate is fully installed
// (accepted and committed), sorted.
func matchedOwners(report map[string]ownerResult) []string {
	var out []string
	for owner, r := range report {
		if r.matched() {
			out = append(out, owner)
		}
	}
	sort.Strings(out)
	return out
}

// needsManualCommitOwners returns, sorted, every owner the host re-gate
// accepted but whose commit failed, alongside its commit-error tail.
func needsManualCommitOwners(report map[string]ownerResult) (owners []string, tails map[string]string) {
	tails = map[string]string{}
	for owner, r := range report {
		if r.needsManualCommit() {
			owners = append(owners, owner)
			tails[owner] = r.CommitError
		}
	}
	sort.Strings(owners)
	return owners, tails
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
		result, ok := report.Owners[o]
		status := "not attempted"
		if ok {
			status = result.displayStatus()
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

var prURLNumberRe = regexp.MustCompile(`/pull/(\d+)\D*$`)

// prNumberFromURL extracts the trailing /pull/<n> from a `gh pr create`
// URL, e.g. "https://github.com/o/r/pull/123" -> 123. 0 (with GhPRCreate
// never erroring) means either a --dry-run (GhPRCreate.Fake returns "" or a
// stub), or an unrecognised URL shape -- either way pollPRs never picks the
// run up (it skips PRNumber == 0), matching the pre-self-merge behavior for
// a run whose PR it could not identify.
func prNumberFromURL(url string) int {
	m := prURLNumberRe.FindStringSubmatch(url)
	if m == nil {
		return 0
	}
	n, err := strconv.Atoi(m[1])
	if err != nil {
		return 0
	}
	return n
}

// touchesMergePaths reports whether a git-status path (already stripped of
// its leading two-character XY code) falls inside a tree the merge step
// itself writes to -- disasm/src/, docs/regions/ (see
// tools/container_merge.py's own writes). Everything else -- another
// session's own uncommitted edits elsewhere in the checkout, e.g.
// disasm/Makefile or tools/try_pragma_compare.py -- is tolerated; see
// dirtyMergePath and docs/FLEET_CONTROLLER.md sec 2.
//
// COVERAGE.md is deliberately NOT here even though the merge step writes
// it too: .githooks/pre-commit.d/10-coverage.sh regenerates and stages it
// on *every* commit, so `git commit --only <file>` (tools/container_merge.py's
// own commit path) routinely leaves a fresh, uncommitted COVERAGE.md behind
// in the merge repo -- a leftover from the merge step's own last success,
// never another session's conflicting work. resetGeneratedFiles discards
// it outright before the dirty check runs, so it is never a real conflict.
func touchesMergePaths(path string) bool {
	return strings.HasPrefix(path, "disasm/src/") ||
		strings.HasPrefix(path, "docs/regions/")
}

// resetGeneratedFiles discards any uncommitted state in files the merge
// repo's own tooling regenerates as a side effect of committing -- today
// just COVERAGE.md (see touchesMergePaths' doc) -- before runMerge's dirty
// check runs, so a leftover regenerated-but-uncommitted copy from a prior
// commit never blocks a run that is otherwise clean. `git reset -q --
// COVERAGE.md` unstages it and `git checkout -- COVERAGE.md` discards any
// working-tree modification, restoring it to HEAD's committed version --
// safe to do unconditionally since the pre-commit hook regenerates it from
// scratch on the next real commit anyway.
func (l *Loop) resetGeneratedFiles(ctx context.Context, repoRoot string) error {
	if err := l.Runner.GitResetPath(ctx, repoRoot, "COVERAGE.md"); err != nil {
		return fmt.Errorf("git reset COVERAGE.md: %w", err)
	}
	if err := l.Runner.GitCheckoutPath(ctx, repoRoot, "COVERAGE.md"); err != nil {
		return fmt.Errorf("git checkout COVERAGE.md: %w", err)
	}
	return nil
}

// dirtyMergePath scans `git status --porcelain` output for the first
// tracked (non "??") entry under touchesMergePaths, returning its path, or
// "" if the merge repo is clean everywhere the merge step itself would
// write. Untracked files are always tolerated -- only a *modification* to
// one of these paths is a real conflict, and porcelain's rename lines
// ("R  old -> new") are checked by their destination.
func dirtyMergePath(porcelain string) string {
	for _, line := range strings.Split(porcelain, "\n") {
		if len(line) < 4 || line[:2] == "??" {
			continue
		}
		path := strings.TrimSpace(line[3:])
		if idx := strings.Index(path, " -> "); idx >= 0 {
			path = path[idx+4:]
		}
		if touchesMergePaths(path) {
			return path
		}
	}
	return ""
}

// runMerge is the sequential merge/branch/PR step. The control loop never
// runs two of these concurrently -- RunOnce/pollRunning call it in a plain
// for loop with no goroutines, which is itself the mutex the task asks for
// (see docs/FLEET_CONTROLLER.md).
func (l *Loop) runMerge(ctx context.Context, rec *fleetstate.RunRecord) error {
	branch := branchName(rec.Spec)
	mergeRepo := l.mergeRepo()
	baseRef := l.baseRef()

	// Cleared up front so a retryBlockedMergeRuns attempt that succeeds (or
	// blocks on a *different* path than last time) never leaves a stale
	// note from a prior blocked attempt behind.
	rec.Note = ""

	// Discard any leftover uncommitted COVERAGE.md before checking
	// cleanliness -- see resetGeneratedFiles' doc -- so the pre-commit
	// hook's own regeneration of it never masquerades as another session's
	// conflicting dirt.
	if err := l.resetGeneratedFiles(ctx, mergeRepo); err != nil {
		return fmt.Errorf("reset generated files in %s: %w", mergeRepo, err)
	}

	// The merge repo is shared (often a linked worktree of the same
	// checkout other sessions/tools use), so it may already carry
	// uncommitted changes when a run's merge step reaches it. Refuse to
	// branch/commit over anything the merge itself would touch -- see
	// dirtyMergePath's doc for exactly which paths that is and which are
	// tolerated (docs/FLEET_CONTROLLER.md sec 2, "the merge repo must be
	// clean").
	porcelain, err := l.Runner.GitStatusPorcelain(ctx, mergeRepo)
	if err != nil {
		return fmt.Errorf("git status --porcelain %s: %w", mergeRepo, err)
	}
	if conflict := dirtyMergePath(porcelain); conflict != "" {
		rec.Status = fleetstate.StatusMergeBlockedDirty
		rec.Note = fmt.Sprintf("merge repo %s has uncommitted changes to %s (a path this merge would touch); refusing to branch/commit until it is clean", mergeRepo, conflict)
		l.logf("run %s: %s", rec.Spec.ID, rec.Note)
		l.alert(ctx, "merge_blocked_dirty", rec.Spec.ID,
			fmt.Sprintf("fleetctl: merge repo dirty, run %s blocked", rec.Spec.ID), rec.Note)
		return nil
	}

	if err := l.Runner.GitFetch(ctx, mergeRepo); err != nil {
		return fmt.Errorf("fetch origin before branching: %w", err)
	}
	if err := l.Runner.GitCheckoutNewBranch(ctx, mergeRepo, branch, baseRef); err != nil {
		return fmt.Errorf("create branch %s from %s: %w", branch, baseRef, err)
	}
	rec.Branch = branch

	// Commits, if any, land on `branch` because it is already checked out.
	if _, err := l.Runner.Merge(ctx, runner.MergeSpec{
		OutDir: rec.OutDir, RepoRoot: mergeRepo, FreshHistory: true, Commit: true,
	}); err != nil {
		l.logf("run %s: merge step error: %v", rec.Spec.ID, err)
	}
	if _, err := l.Runner.ImportStats(ctx, rec.OutDir, mergeRepo); err != nil {
		l.logf("run %s: import-stats error: %v", rec.Spec.ID, err)
	}

	report := loadMergeReport(rec.OutDir)
	accepted := matchedOwners(report.Owners)
	rec.MatchedOwners = accepted
	// Collect this run's own tie-pool.json (any run, permuter-lane or not,
	// can plateau into one) into the file's persisted tie-pool store, and
	// drop every owner this run just matched (sec 13, "owners removed once
	// matched") -- before requeueing unmatched owners below, so a matched
	// owner is never both dropped from the pool and left in it.
	l.updateTiePool(rec)
	needsCommit, commitTails := needsManualCommitOwners(report.Owners)
	if len(needsCommit) > 0 {
		rec.NeedsManualCommit = commitTails
		l.logf("run %s: %d owner(s) accepted but NOT committed (git commit --only failed); see fleetctl status and %s/merge-results/",
			rec.Spec.ID, len(needsCommit), rec.OutDir)
	}

	rec.Status = fleetstate.StatusDone
	if len(accepted) > 0 {
		if err := l.Runner.GitPush(ctx, mergeRepo, branch); err != nil {
			l.logf("run %s: git push %s failed: %v", rec.Spec.ID, branch, err)
		} else {
			title := fmt.Sprintf("Container match: %s", strings.Join(accepted, ", "))
			url, err := l.Runner.GhPRCreate(ctx, runner.PRSpec{
				RepoRoot: mergeRepo, Base: l.IntegrationBranch, Title: title, Body: buildPRBody(rec, report),
			})
			if err != nil {
				l.logf("run %s: gh pr create failed: %v", rec.Spec.ID, err)
			} else {
				rec.PRURL = url
				rec.PRNumber = prNumberFromURL(url)
				l.logf("run %s: opened PR %s for %d matched owner(s)", rec.Spec.ID, url, len(accepted))
				// With --auto-merge (the default), the PR is not "done" yet
				// -- pollPRs takes it from here (sec 2). Without it, this
				// matches the pre-self-merge behavior: the PR is left open
				// for a human, and this run is done as far as fleetctl is
				// concerned.
				if l.autoMergeEnabled() && rec.PRNumber != 0 {
					rec.Status = fleetstate.StatusPROpen
				}
			}
		}
	} else {
		l.logf("run %s: no owners matched this run", rec.Spec.ID)
	}

	if err := l.Runner.GitCheckoutDetach(ctx, mergeRepo, baseRef); err != nil {
		l.logf("run %s: checkout --detach %s failed: %v", rec.Spec.ID, baseRef, err)
	}

	// An owner needing a manual commit already has its candidate installed
	// in the merge repo's working tree -- requeueing it would re-probe a
	// duplicate against a tree that (once committed by hand) will already
	// contain it. Only owners neither matched nor awaiting a manual commit
	// go back on the queue for a fresh attempt.
	unmatched := subtract(subtract(rec.Spec.Owners, accepted), needsCommit)
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

// retryBlockedMergeRuns re-attempts, at the top of every poll pass (called
// first thing from RunOnce, before anything else touches the merge repo),
// every run currently StatusMergeBlockedDirty -- mirroring how pollPRs
// retries a stuck fast-forward once at the top of its own pass (sec 7). The
// merge repo's conflicting dirt (disasm/src/, docs/regions/) may have been
// cleaned up by hand since the run first blocked, or (COVERAGE.md, no
// longer even a conflicting path -- see touchesMergePaths) by this retry's
// own runMerge call -- either way there is no reason to wait for a human to
// notice and re-run fleetctl. Runs are visited in id order for
// deterministic logs/tests.
//
// A retry that finds the merge repo still dirty leaves the run exactly
// where it was (runMerge sets StatusMergeBlockedDirty and its note again),
// re-firing the merge_blocked_dirty alert -- rate-limited to once per hour
// per run by Loop.alert's own "event:key" bucket (key is rec.Spec.ID), so a
// run stuck for days does not spam. MergeBlockedRetries counts every
// attempt made (fleetctl status), successful or not.
func (l *Loop) retryBlockedMergeRuns(ctx context.Context) error {
	ids := make([]string, 0, len(l.State.Runs))
	for id, rec := range l.State.Runs {
		if rec.Status == fleetstate.StatusMergeBlockedDirty {
			ids = append(ids, id)
		}
	}
	sort.Strings(ids)
	for _, id := range ids {
		rec := l.State.Runs[id]
		rec.MergeBlockedRetries++
		l.logf("run %s: retrying blocked merge (attempt %d)", id, rec.MergeBlockedRetries)
		rec.Status = fleetstate.StatusMerging
		if err := l.runMerge(ctx, rec); err != nil {
			l.logf("run %s: blocked-merge retry error: %v", id, err)
			rec.Status = fleetstate.StatusMergeBlockedDirty
			continue
		}
		if rec.Status != fleetstate.StatusMergeBlockedDirty {
			l.logf("run %s: blocked merge recovered on retry %d", id, rec.MergeBlockedRetries)
		}
	}
	return nil
}

// pollPRs is the self-merge poll (docs/FLEET_CONTROLLER.md sec 2): for
// every run currently StatusPROpen, check its PR's CI checks and, once they
// all report SUCCESS, merge it -- FAILURE instead moves it to
// StatusGateFailed (left open, alerted, never auto-retried). Runs are
// visited in id order for deterministic test assertions and logs.
//
// If a prior pass's post-merge fast-forward failed, State.MergeBlocked
// gates every further `gh pr merge` until a fast-forward retry (tried once
// at the top of this pass) succeeds -- "stop merging until fixed" (sec 1).
func (l *Loop) pollPRs(ctx context.Context) error {
	if l.State.MergeBlocked {
		if err := l.fastForwardBase(ctx); err != nil {
			l.alert(ctx, "ff_failed", "",
				fmt.Sprintf("fleetctl: fast-forward of %s is still failing", l.IntegrationBranch),
				fmt.Sprintf("Self-merge is paused until this is fixed by hand in %s: %v", l.mergeRepo(), err))
			return nil
		}
		l.logf("merge repo %s: fast-forward of %s recovered; resuming self-merge", l.mergeRepo(), l.IntegrationBranch)
		l.State.MergeBlocked = false
		l.State.MergeBlockedReason = ""
	}

	ids := make([]string, 0, len(l.State.Runs))
	for id, rec := range l.State.Runs {
		if rec.Status == fleetstate.StatusPROpen {
			ids = append(ids, id)
		}
	}
	sort.Strings(ids)

	for _, id := range ids {
		rec := l.State.Runs[id]
		if rec.PRNumber == 0 {
			continue
		}
		result, err := l.Runner.GhPRChecks(ctx, l.mergeRepo(), rec.PRNumber)
		if err != nil {
			l.logf("run %s: gh pr checks %d failed: %v", id, rec.PRNumber, err)
			continue
		}
		switch result.State {
		case "SUCCESS":
			if err := l.Runner.GhPRMerge(ctx, l.mergeRepo(), rec.PRNumber); err != nil {
				l.logf("run %s: gh pr merge %d failed: %v", id, rec.PRNumber, err)
				continue
			}
			rec.Status = fleetstate.StatusMerged
			rec.MergedAt = l.now()
			l.logf("run %s: PR #%d merged", id, rec.PRNumber)
			if err := l.fastForwardBase(ctx); err != nil {
				l.State.MergeBlocked = true
				l.State.MergeBlockedReason = err.Error()
				l.alert(ctx, "ff_failed", "",
					fmt.Sprintf("fleetctl: fast-forward of %s failed after merging PR #%d", l.IntegrationBranch, rec.PRNumber),
					fmt.Sprintf("%v\nSelf-merge is paused until %s is fixed by hand in %s -- fleetctl retries the fast-forward at the top of every poll pass.",
						err, l.IntegrationBranch, l.mergeRepo()))
				// "stop merging until fixed" -- do not evaluate any other
				// StatusPROpen run this pass.
				return nil
			}
			l.State.LastMergeAt = l.now()
			l.recordMergeCommit(ctx, id, rec)
			if err := l.Replan(ctx); err != nil {
				l.logf("run %s: replan after merge failed: %v", id, err)
			}
		case "FAILURE":
			rec.Status = fleetstate.StatusGateFailed
			l.logf("run %s: PR #%d gate failed; left open for manual triage", id, rec.PRNumber)
			l.alert(ctx, "gate_failed", id,
				fmt.Sprintf("Container gate failed: run %s", id),
				fmt.Sprintf("PR %s (run %s) failed its checks and was left open. See `fleetctl status`.", rec.PRURL, id))
		default:
			// PENDING (or an unrecognised state) -- recheck next pass.
		}
	}
	return nil
}

// fastForwardBase is the post-merge "fast-forward" (sec 2/7): `git fetch
// origin` in the merge repo, so its --base-ref remote-tracking ref (e.g.
// origin/master) picks up whatever a self-merge (or anything else) just
// pushed to the real base branch. This is now the merge repo's *only*
// mutating call for this -- its local base branch is never checked out or
// pulled here (see Loop.BaseRef's doc), so fetch failure (network, auth,
// ...) is the only failure mode left, and State.MergeBlocked is set only
// when it returns an error.
func (l *Loop) fastForwardBase(ctx context.Context) error {
	if err := l.Runner.GitFetch(ctx, l.mergeRepo()); err != nil {
		return fmt.Errorf("fetch origin: %w", err)
	}
	return nil
}

// recordMergeCommit sets rec.MergeCommitSHA from `gh pr view --json
// mergeCommit` and logs a (non-blocking) warning if --base-ref's freshly
// fetched sha does not yet match it -- e.g. GitHub's merge-commit metadata
// lagging the fetch by a beat. Never sets State.MergeBlocked: fetch itself
// already succeeded (fastForwardBase's only failure mode), and this is
// just a best-effort verification/record of what landed.
func (l *Loop) recordMergeCommit(ctx context.Context, id string, rec *fleetstate.RunRecord) {
	mergeSHA, err := l.Runner.GhPRView(ctx, l.mergeRepo(), rec.PRNumber)
	if err != nil {
		l.logf("run %s: gh pr view %d --json mergeCommit failed: %v", id, rec.PRNumber, err)
		return
	}
	rec.MergeCommitSHA = mergeSHA
	baseRef := l.baseRef()
	baseSHA, err := l.Runner.GitRevParse(ctx, l.mergeRepo(), baseRef)
	if err != nil {
		l.logf("run %s: git rev-parse %s failed: %v", id, baseRef, err)
		return
	}
	if baseSHA != mergeSHA {
		l.logf("run %s: WARNING: %s (%s) has not advanced to merge commit %s of PR #%d yet",
			id, baseRef, baseSHA, mergeSHA, rec.PRNumber)
	}
}

// Replan re-runs the ranking against the merge repo and rebuilds the queue
// of pending partitions (sec 2): after every merge, and at startup with
// --replan. It is a no-op when no plan has ever been persisted into State
// (PersistedPlan returns false) -- nothing to rebuild from.
func (l *Loop) Replan(ctx context.Context) error {
	plan, ok := l.PersistedPlan()
	if !ok {
		return nil
	}
	opts, err := plan.ToOptions()
	if err != nil {
		return fmt.Errorf("replan: %w", err)
	}
	// "against the merge repo" (sec 2) -- current post-merge ranking/targets,
	// not the (possibly different) launch --repo.
	opts.Repo = l.mergeRepo()
	// "rank-files --exclude-recent 0" (sec 2) -- a fresh replan always
	// considers every file, including one just touched by our own merge.
	opts.ExcludeRecentHours = 0

	fresh, err := planpkg.Build(ctx, l.Runner, opts)
	if err != nil {
		return fmt.Errorf("replan: rank/targets: %w", err)
	}
	l.reconcileQueue(fresh)
	if data, err := json.Marshal(fresh); err == nil {
		l.State.PlanJSON = data
	}
	// One permuter-lane partition per file with pending tie-pool owners
	// (sec 13) -- after reconcileQueue, so it sees the just-rebuilt queue
	// when checking for an already in-flight permuter run per file.
	l.enqueuePermuterLane()
	l.logf("replan: %d fresh partition(s) considered, queue now has %d entr(y/ies)", len(fresh.Queue), len(l.State.Queue))
	return nil
}

// keepAcrossReplan reports whether a still-queued run must survive a
// Replan untouched: either it has already been launched at least once
// (StartedAt set -- a --resume retry of in-progress work, sec 2 "keep
// running runs untouched" extended to its queued-for-relaunch state), or it
// carries SeedDirs (a post-merge reseed of a partition's unmatched owners,
// sec 2 "keep per-file seeding" -- dropping it would discard the seed
// continuity runMerge just built for it, even though it has Attempt==0 and
// has never itself been launched).
func keepAcrossReplan(rec *fleetstate.RunRecord) bool {
	return !rec.StartedAt.IsZero() || len(rec.Spec.SeedDirs) > 0
}

// reconcileQueue rebuilds State.Queue from fresh's candidate partitions:
// every not-yet-launched, not-seeded queue entry is dropped and replaced
// wholesale ("runs already queued but not launched are replaced by the
// fresh plan", sec 2); every run this pass keeps (queued survivors, plus
// every run already running/merging/pr_open) reserves its own owners, and a
// fresh candidate partition has those owners subtracted out so a live
// attempt is never duplicated by a fresh one for the same file+owner.
func (l *Loop) reconcileQueue(fresh *planpkg.Plan) {
	inFlight := map[string]map[string]bool{}
	reserve := func(file string, owners []string) {
		m := inFlight[file]
		if m == nil {
			m = map[string]bool{}
			inFlight[file] = m
		}
		for _, o := range owners {
			m[o] = true
		}
	}

	kept := make([]string, 0, len(l.State.Queue))
	for _, id := range l.State.Queue {
		rec := l.State.Runs[id]
		if rec == nil {
			continue
		}
		if keepAcrossReplan(rec) {
			kept = append(kept, id)
			reserve(rec.Spec.File, rec.Spec.Owners)
		} else {
			delete(l.State.Runs, id)
		}
	}
	for _, rec := range l.State.Runs {
		switch rec.Status {
		case fleetstate.StatusRunning, fleetstate.StatusMerging, fleetstate.StatusPROpen:
			reserve(rec.Spec.File, rec.Spec.Owners)
		}
	}

	for _, spec := range fresh.Queue {
		var owners []string
		for _, o := range spec.Owners {
			if !inFlight[spec.File][o] {
				owners = append(owners, o)
			}
		}
		if len(owners) == 0 {
			continue
		}
		if _, exists := l.State.Runs[spec.ID]; exists {
			// An id collision with a run reconcileQueue just kept (or one
			// still running/merging/pr_open under the same id, e.g. the
			// fresh partition numbering restarting at p0 for a file whose
			// p0 is still active) -- never overwrite it. The remaining
			// (genuinely unclaimed) owners still deserve a queue entry, so
			// give them the next free requeue suffix rather than dropping
			// them silently.
			spec.ID = l.State.NextRequeueID(spec.ID)
		}
		spec.Owners = owners
		l.State.Runs[spec.ID] = &fleetstate.RunRecord{Spec: spec, Status: fleetstate.StatusQueued}
		kept = append(kept, spec.ID)
	}
	l.State.Queue = kept
}

// Notifier is fleetctl's alerting seam (sec 4): every configured Notifier
// receives every rate-limited alert event's title/body. IssueNotifier and
// MacOSNotifier are ExecRunner-backed implementations behind
// --alert-issue/--alert-macos; tests substitute their own.
type Notifier interface {
	Notify(ctx context.Context, title, body string) error
}

// IssueNotifier posts `gh issue comment <Issue> --body ...` (--alert-issue
// N) -- rate-limited by Loop.alert like every other Notifier, plus it is
// the only kind Loop.maybeDailySummary posts to.
type IssueNotifier struct {
	Runner runner.Runner
	Repo   string // the merge repo -- gh's cwd, so it infers the right remote
	Issue  int
}

func (n *IssueNotifier) Notify(ctx context.Context, title, body string) error {
	return n.Runner.GhIssueComment(ctx, n.Repo, n.Issue, title+"\n\n"+body)
}

// MacOSNotifier runs `osascript -e 'display notification ...'`
// (--alert-macos).
type MacOSNotifier struct {
	Runner runner.Runner
}

func (n *MacOSNotifier) Notify(ctx context.Context, title, body string) error {
	return n.Runner.OsascriptNotify(ctx, title, body)
}

// alert fires every configured Notifier for one event occurrence,
// rate-limited (sec 4) to at most once per hour per "event" (key == "") or
// per "event:key" (e.g. one gate_failed per run id, one agent_exhausted per
// agent, but a single shared bucket for ff_failed/controller_error, which
// have no natural per-occurrence key).
func (l *Loop) alert(ctx context.Context, event, key, title, body string) {
	rateKey := event
	if key != "" {
		rateKey = event + ":" + key
	}
	now := l.now()
	if l.State.AlertSent == nil {
		l.State.AlertSent = map[string]time.Time{}
	}
	if last, ok := l.State.AlertSent[rateKey]; ok && now.Sub(last) < time.Hour {
		return
	}
	l.State.AlertSent[rateKey] = now
	for _, n := range l.Notifiers {
		if err := n.Notify(ctx, title, body); err != nil {
			l.logf("alert %s: notifier error: %v", event, err)
		}
	}
}

// maybeDailySummary posts one runs-launched/finished/merged/pr_open/
// cooldown/stall summary (plus a `fleetctl status --json` machine section)
// to DailySummaryNotifier, at most once per UTC calendar day, at
// DailySummaryHourUTC.
func (l *Loop) maybeDailySummary(ctx context.Context) {
	if l.DailySummaryNotifier == nil {
		return
	}
	now := l.now()
	if now.UTC().Hour() != l.DailySummaryHourUTC {
		return
	}
	if !l.State.LastDailySummary.IsZero() && sameUTCDate(l.State.LastDailySummary, now) {
		return
	}
	if err := l.DailySummaryNotifier.Notify(ctx, "fleetctl daily summary", l.buildDailySummaryBody()); err != nil {
		l.logf("daily summary: %v", err)
		return
	}
	l.State.LastDailySummary = now
}

func sameUTCDate(a, b time.Time) bool {
	ay, am, ad := a.UTC().Date()
	by, bm, bd := b.UTC().Date()
	return ay == by && am == bm && ad == bd
}

// buildDailySummaryBody is "runs launched/finished, matches merged with
// commit shas, PRs open, agents on cooldown, stalls" (sec 4) plus an
// embedded `fleetctl status --json` block ("Include fleetctl status --json
// for machines", sec 4).
func (l *Loop) buildDailySummaryBody() string {
	now := l.now()
	var launched, finished, merged, prOpen, gateFailed, stalled int
	var mergedLines []string
	for _, rec := range l.State.Runs {
		if !rec.StartedAt.IsZero() {
			launched++
		}
		switch rec.Status {
		case fleetstate.StatusDone, fleetstate.StatusMerged, fleetstate.StatusGateFailed:
			finished++
		}
		switch rec.Status {
		case fleetstate.StatusMerged:
			merged++
			mergedLines = append(mergedLines, fmt.Sprintf("- %s: %s (%s)",
				rec.Spec.ID, strings.Join(rec.MatchedOwners, ", "), rec.MergeCommitSHA))
		case fleetstate.StatusPROpen:
			prOpen++
		case fleetstate.StatusGateFailed:
			gateFailed++
		case fleetstate.StatusRunning:
			if !rec.BestSimilarityAt.IsZero() && now.Sub(rec.BestSimilarityAt) >= l.stallAfter() {
				stalled++
			}
		}
	}
	sort.Strings(mergedLines)

	var cooldownAgents []string
	for agent, until := range l.State.Cooldowns {
		if until.After(now) {
			cooldownAgents = append(cooldownAgents, agent)
		}
	}
	sort.Strings(cooldownAgents)

	var b strings.Builder
	fmt.Fprintf(&b, "runs launched=%d finished=%d merged=%d pr_open=%d gate_failed=%d stalled=%d cooldown_agents=%s\n",
		launched, finished, merged, prOpen, gateFailed, stalled, strings.Join(cooldownAgents, ","))
	if len(mergedLines) > 0 {
		b.WriteString("\nMerged:\n")
		for _, line := range mergedLines {
			b.WriteString(line + "\n")
		}
	}
	if data, err := json.MarshalIndent(BuildStatus(l.State), "", "  "); err == nil {
		b.WriteString("\n`fleetctl status --json`:\n```json\n")
		b.Write(data)
		b.WriteString("\n```\n")
	}
	return b.String()
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
			rec.WaitReason = "concurrency"
			remaining = append(remaining, id)
		// permuterAgent is never subject to cooldown (sec 13), so this case
		// can never fire for it regardless of what State.Cooldowns holds.
		case rec.Spec.Agent != permuterAgent && l.State.OnCooldown(rec.Spec.Agent, now):
			// Quota-window-aware scheduling (sec 12): rather than leave the
			// slot idle, hand this partition to the next eligible agent
			// (round-robin over the plan's own roster, preferring one whose
			// window just reopened) instead of waiting out rec's own
			// agent's cooldown.
			if alt, ok := l.reassignAgent(rec.Spec.Agent, now, byAgent); ok {
				l.logf("run %s: agent %s on cooldown; reassigning to %s:%s%s (sec 12)",
					id, rec.Spec.Agent, alt.Agent, alt.Model, effortSuffix(alt.Effort))
				rec.Note = appendReassignNote(rec.Note, rec.Spec.Agent, alt.Agent)
				rec.Spec.Agent, rec.Spec.Model, rec.Spec.Effort = alt.Agent, alt.Model, alt.Effort
				if err := l.launch(ctx, rec); err != nil {
					l.logf("run %s: launch failed: %v", id, err)
					remaining = append(remaining, id)
					continue
				}
				totalRunning++
				byAgent[alt.Agent]++
				continue
			}
			rec.WaitReason = "cooldown"
			remaining = append(remaining, id)
		case l.AgentConcurrency[rec.Spec.Agent] > 0 && byAgent[rec.Spec.Agent] >= l.AgentConcurrency[rec.Spec.Agent]:
			rec.WaitReason = "concurrency"
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

	var tiePoolFile string
	if rec.Spec.Mode == "permuter-only" {
		tiePoolFile, err = preparePermuterTiePool(l.RunsDir, outDir, rec.Spec.File)
		if err != nil {
			return err
		}
	}

	// Stale-image awareness (docs/FLEET_CONTROLLER.md sec 6): skipped
	// entirely under --src-overlay -- an overlay makes the image's own
	// baked-in sources irrelevant, so there is nothing to warn about.
	if l.SrcOverlay == "" {
		if id, created, err := l.Runner.DockerImageID(ctx, l.imageRef()); err != nil {
			l.logf("run %s: docker image inspect %s failed: %v", rec.Spec.ID, l.imageRef(), err)
		} else {
			rec.ImageID = id
			if !l.State.LastMergeAt.IsZero() && created.Before(l.State.LastMergeAt) {
				l.logf("run %s: WARNING: %s was built %s, before the last merge (%s) -- rebuild it or pass --src-overlay",
					rec.Spec.ID, l.imageRef(), created.Format(time.RFC3339), l.State.LastMergeAt.Format(time.RFC3339))
			}
		}
	}

	spec := runner.LaunchSpec{
		SourceFile:      rec.Spec.File,
		OutDir:          outDir,
		BudgetSeconds:   rec.Spec.BudgetSeconds,
		Owners:          rec.Spec.Owners,
		SeedFrom:        seedFrom,
		Resume:          rec.Spec.Attempt > 0,
		Agent:           rec.Spec.Agent,
		Model:           rec.Spec.Model,
		Effort:          rec.Spec.Effort,
		SrcOverlay:      l.SrcOverlay,
		Mode:            rec.Spec.Mode,
		TiePoolFile:     tiePoolFile,
		PermuterSeconds: rec.Spec.PermuterSeconds,
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
	rec.WaitReason = ""
	// Quota-window bookkeeping (sec 12): stamps this agent's window start
	// the first time it launches since a cooldown (or ever) -- a no-op once
	// already stamped for the current window.
	l.recordWindowStart(rec.Spec.Agent, rec.StartedAt)
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
