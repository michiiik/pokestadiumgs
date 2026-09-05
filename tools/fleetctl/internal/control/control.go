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

	MaxConcurrent int
	// AgentConcurrency caps how many runs may be Running at once under one
	// key -- either a bare agent name or the fleetstate.AgentModelKey
	// composite ("agent:model"), so one specific model sharing an agent's
	// name can be capped independently of its siblings (e.g.
	// "codex:gpt-5.3-codex-spark" without also capping
	// "codex:gpt-5.6-luna"). agentConcurrencyExceeded checks both forms.
	AgentConcurrency map[string]int
	// MaxPerFile caps how many runs may be Running at once against the
	// same target source file, regardless of agent -- 0 means unlimited.
	// Too many concurrent containers on one file don't add real
	// parallelism; they mostly just race each other into PR-merge
	// conflicts (docs sec 2's conflict-replay path), each conflict paying
	// for a full redo of that PR's owners against the new base.
	MaxPerFile       int
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

	// OwnerSeconds is `--owner-seconds` forwarded to every ordinary launch;
	// 0 leaves container_agent.py's own default (2400s). budget/owner-seconds
	// bounds how many owners a run can reach: at the 7200s default budget,
	// 2400s reaches 3 of a 12-owner spec and 1200s reaches 6.
	OwnerSeconds int

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

	// HardBudgetGrace is how far past its own --budget-seconds a running
	// container may go before pollRunning force-stops it directly, rather
	// than waiting indefinitely on the in-container timeout
	// (container_agent.py's own --generator-timeout/--owner-seconds
	// enforcement) to notice and self-terminate. That in-container
	// enforcement is normally reliable, but is not an absolute guarantee --
	// observed live under Rosetta (amd64-on-arm64 emulation, required by
	// the vendored x86_64 IDO compiler): a single generator subprocess call
	// sat blocked past its 30-minute cap for over two hours, holding a
	// concurrency/file slot the whole time with nothing to show for it.
	// <=0 defaults to 30m. A run with Spec.BudgetSeconds<=0 is exempt (no
	// budget to overrun).
	HardBudgetGrace time.Duration

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

	// lastMergeFailure de-dupes pollPRs' "gh pr merge N failed" log line
	// (docs/FLEET_CONTROLLER.md sec 7): keyed by PR number, holds the most
	// recently logged error message so an unresolved failure is logged
	// once, then again only when the message itself changes -- not once
	// per poll pass, forever.
	lastMergeFailure map[int]string
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

func (l *Loop) hardBudgetGrace() time.Duration {
	if l.HardBudgetGrace > 0 {
		return l.HardBudgetGrace
	}
	return 30 * time.Minute
}

func (l *Loop) imageRef() string {
	if l.ImageRef != "" {
		return l.ImageRef
	}
	return "gs-decomp-agent:latest"
}

// stopSiblingRuns proactively stops every OTHER currently-running run under
// the exact agent+model that just reported generator_exhausted, instead of
// leaving them to burn their own remaining budget on calls almost certain
// to hit the identical, already-confirmed rate limit. Observed live: five
// concurrent spark containers each independently exhausted within seconds
// of each other, each paying its own full failure-detection cost, when the
// first one to fail already told fleetctl everything the rest needed to
// know. A stopped sibling loses no work -- generator calls are stateless
// per iteration -- only the wall-clock it would have spent failing; it
// requeues with --resume against its own out dir, same as a genuine
// generator_exhausted of its own, and is picked up again once this
// agent+model's cooldown lifts or sec 12 reassigns it. Runs already past
// StatusRunning (merging, pr_open, ...) are never touched.
func (l *Loop) stopSiblingRuns(ctx context.Context, exhausted *fleetstate.RunRecord) {
	ids := make([]string, 0, len(l.State.Runs))
	for id := range l.State.Runs {
		ids = append(ids, id)
	}
	sort.Strings(ids)
	for _, id := range ids {
		rec := l.State.Runs[id]
		if rec == exhausted || rec.Status != fleetstate.StatusRunning {
			continue
		}
		if rec.Spec.Agent != exhausted.Spec.Agent || rec.Spec.Model != exhausted.Spec.Model {
			continue
		}
		// The sibling very often self-exits from hitting the identical
		// quota limit before this Stop lands -- observed live, that race
		// is the common case (roughly 85% of attempts), not the
		// exception. Inspect first so it resolves as a quiet no-op
		// instead of a docker-stop error every single time it happens;
		// InspectContainer already treats "no such object" as
		// Found:false (already reaped), the same signal pollRunning uses
		// elsewhere for a container that vanished out of band.
		if info, err := l.Runner.InspectContainer(ctx, rec.ContainerID); err == nil && !info.Found {
			rec.Status = fleetstate.StatusRequeued
			rec.StoppedReason = ""
			rec.Note = fmt.Sprintf("stopped: sibling run %s just confirmed %s:%s is rate-limited (container had already exited)", exhausted.Spec.ID, rec.Spec.Agent, rec.Spec.Model)
			rec.EndedAt = l.now()
			l.requeueResume(rec)
			l.logf("run %s: sibling %s's generator_exhausted confirmed %s:%s is rate-limited (container already exited); requeueing with --resume",
				rec.Spec.ID, exhausted.Spec.ID, rec.Spec.Agent, rec.Spec.Model)
			continue
		}
		if err := l.Runner.StopContainer(ctx, rec.ContainerID); err != nil {
			l.logf("run %s: stop after sibling %s's generator_exhausted failed: %v", rec.Spec.ID, exhausted.Spec.ID, err)
			continue
		}
		rec.Status = fleetstate.StatusRequeued
		rec.StoppedReason = ""
		rec.Note = fmt.Sprintf("stopped: sibling run %s just confirmed %s:%s is rate-limited", exhausted.Spec.ID, rec.Spec.Agent, rec.Spec.Model)
		rec.EndedAt = l.now()
		l.requeueResume(rec)
		l.logf("run %s: stopped (sibling %s's generator_exhausted just confirmed %s:%s is rate-limited); requeueing with --resume",
			rec.Spec.ID, exhausted.Spec.ID, rec.Spec.Agent, rec.Spec.Model)
	}
}

// cooldownKey is the fine-grained key State.Cooldowns is written under: the
// bare agent name (unchanged behaviour) when model is empty -- the
// permuter lane and any caller that genuinely has no model -- else
// "agent:model", so one model's exhaustion cannot leak into a sibling
// model's cooldown status. reassignAgent's roster-eligibility checks
// (windowReopened, eligibleForReassignment) check both this key and the
// bare-agent one: a roster entry (agentRoster) pins one specific model, so
// reassigning to it launches exactly that model -- checking only the bare
// key there let a queued run get reassigned right back into a model that
// was, in fact, still on cooldown (see those functions' own comments).
func cooldownKey(agent, model string) string {
	return fleetstate.AgentModelKey(agent, model)
}

// agentConcurrencyExceeded reports whether launching agent/model now would
// break either the coarse per-agent --agent-concurrency cap or a
// finer-grained one set under the model-specific cooldownKey/
// fleetstate.AgentModelKey composite -- e.g. capping
// "codex:gpt-5.3-codex-spark" specifically without also capping codex's
// other models. byAgent and byAgentModel must both already account for any
// launches decided earlier in the same reconcile pass (mirroring how
// byAgent alone was threaded through before this existed).
func (l *Loop) agentConcurrencyExceeded(agent, model string, byAgent, byAgentModel map[string]int) bool {
	if limit := l.AgentConcurrency[agent]; limit > 0 && byAgent[agent] >= limit {
		return true
	}
	key := fleetstate.AgentModelKey(agent, model)
	if limit := l.AgentConcurrency[key]; limit > 0 && byAgentModel[key] >= limit {
		return true
	}
	return false
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
			if l.forceStopIfBudgetOverrun(ctx, rec) {
				continue
			}
			l.checkStall(ctx, rec)
			continue
		}
		if err := l.handleExit(ctx, rec); err != nil {
			l.logf("run %s: %v", rec.Spec.ID, err)
		}
	}
	return nil
}

// forceStopIfBudgetOverrun docker-stops rec's container directly once it
// has run more than hardBudgetGrace() past its own --budget-seconds,
// instead of waiting indefinitely on the in-container timeout to notice
// and self-terminate (see HardBudgetGrace's doc). docker stop sends
// SIGTERM first, which container_agent.py's own signal handler
// (request_stop) already treats as a graceful-shutdown request -- the same
// finalize path a normal in-container timeout takes, writing a real
// summary.json and preserving any already-accepted candidates -- so the
// next pollRunning pass's handleExit call proceeds exactly as it would for
// a container that timed out on its own. Reports true (the caller must not
// also checkStall this pass) iff a stop was attempted.
func (l *Loop) forceStopIfBudgetOverrun(ctx context.Context, rec *fleetstate.RunRecord) bool {
	if rec.Spec.BudgetSeconds <= 0 || rec.StartedAt.IsZero() {
		return false
	}
	budget := time.Duration(rec.Spec.BudgetSeconds) * time.Second
	elapsed := l.now().Sub(rec.StartedAt)
	if elapsed < budget+l.hardBudgetGrace() {
		return false
	}
	l.logf("run %s: still running %s after a %s budget (%s past it); force-stopping -- the in-container timeout did not fire",
		rec.Spec.ID, elapsed.Round(time.Second), budget, (elapsed - budget).Round(time.Second))
	if err := l.Runner.StopContainer(ctx, rec.ContainerID); err != nil {
		l.logf("run %s: force-stop after budget overrun failed: %v", rec.Spec.ID, err)
	}
	l.alert(ctx, "budget_overrun_killed", rec.Spec.ID,
		fmt.Sprintf("fleetctl: run %s force-stopped, budget overrun", rec.Spec.ID),
		fmt.Sprintf("Run %s (file %s, agent %s:%s) was still running %s after its %s budget; force-stopped because the in-container timeout did not fire on its own.",
			rec.Spec.ID, rec.Spec.File, rec.Spec.Agent, rec.Spec.Model, elapsed.Round(time.Second), budget))
	return true
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

// vanishBackoff is how long a vanish-triggered requeue's launch is deferred
// (docs/FLEET_CONTROLLER.md sec 2, "vanished container storm") -- long
// enough that a one-off environmental problem (e.g. an image that fails at
// container startup) can't relaunch the same run dozens of times a minute.
const vanishBackoff = 10 * time.Minute

// maxConsecutiveVanishes is how many vanishes in a row (see
// fleetstate.RunRecord.VanishCount) move a run to StatusFailed instead of
// requeueing it again.
const maxConsecutiveVanishes = 3

// handleExit is the exit-handling switch described in
// docs/CONTAINER_AGENT.md's output contract and the fleetctl task: a
// container that vanished without a readable summary.json is requeued with
// --resume, same as generator_exhausted (after also cooling that agent
// down), unless it has now vanished maxConsecutiveVanishes times in a row,
// in which case it is left StatusFailed for an operator instead (sec 2);
// every other stopped_reason (budget_expired, plateau, a normal
// completion, no_owners, ...) hands off to the sequential merge step.
func (l *Loop) handleExit(ctx context.Context, rec *fleetstate.RunRecord) error {
	rec.EndedAt = l.now()
	summary, err := loadSummary(rec.OutDir)
	if err != nil {
		rec.VanishCount++
		if rec.VanishCount >= maxConsecutiveVanishes {
			rec.Status = fleetstate.StatusFailed
			rec.StoppedReason = ""
			rec.Note = "vanished 3x; needs operator"
			l.logf("run %s: vanished %d times in a row (no readable summary.json); marking failed, needs operator",
				rec.Spec.ID, rec.VanishCount)
			l.alert(ctx, "container_vanished_repeatedly", rec.Spec.ID,
				fmt.Sprintf("run %s: vanished %d times in a row", rec.Spec.ID, rec.VanishCount),
				fmt.Sprintf("Run %s (file %s, agent %s:%s) has had no readable summary.json %d consecutive times; marked failed instead of requeued again. This usually means an environmental problem (e.g. every container failing at startup), not this run's own work -- needs an operator.",
					rec.Spec.ID, rec.Spec.File, rec.Spec.Agent, rec.Spec.Model, rec.VanishCount))
			return nil
		}
		l.logf("run %s: no readable summary.json (%v); requeueing with --resume (vanish %d/%d, backoff %s)",
			rec.Spec.ID, err, rec.VanishCount, maxConsecutiveVanishes, vanishBackoff)
		rec.Status = fleetstate.StatusRequeued
		rec.StoppedReason = ""
		rec.Note = "vanished without summary.json"
		rec.NotBefore = l.now().Add(vanishBackoff)
		l.requeueResume(rec)
		l.alert(ctx, "container_vanished", rec.Spec.ID,
			fmt.Sprintf("run %s: container vanished", rec.Spec.ID),
			fmt.Sprintf("Run %s (file %s, agent %s:%s) had no readable summary.json; requeued with --resume (attempt %d), held back at least %s.",
				rec.Spec.ID, rec.Spec.File, rec.Spec.Agent, rec.Spec.Model, rec.Spec.Attempt, vanishBackoff))
		return nil
	}
	rec.VanishCount = 0
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
		// Keyed by agent+model, not just agent: confirmed directly (two
		// live codex calls, same auth) that gpt-5.6-luna and
		// gpt-5.3-codex-spark draw from separate usage-limit pools -- luna
		// hit "You've hit your usage limit ... try again at Sep 7th" while
		// spark succeeded immediately after. The old bare-agent key made
		// one model's real, multi-day exhaustion block every other model
		// under the same CLI, including one with quota to spare.
		l.State.Cooldowns[cooldownKey(rec.Spec.Agent, rec.Spec.Model)] = until
		l.recordWindowExhausted(rec.Spec.Agent, l.now())
		l.logf("run %s: agent %s:%s generator_exhausted; cooldown until %s, requeueing with --resume",
			rec.Spec.ID, rec.Spec.Agent, rec.Spec.Model, until.Format(time.RFC3339))
		l.stopSiblingRuns(ctx, rec)
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

// branchName is a run's throwaway branch: "container/<id>", or
// "container/<id>-m<mergeRound+1>" once mergeRound > 0 -- a PR conflict
// replay (sec 2/7, pollPRs' replayConflictedPR) increments
// RunRecord.MergeRound and needs a fresh branch name each time, since the
// old one's PR was just closed and its remote branch (best-effort) deleted.
func branchName(spec fleetstate.RunSpec, mergeRound int) string {
	if mergeRound > 0 {
		return fmt.Sprintf("container/%s-m%d", spec.ID, mergeRound+1)
	}
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

// rejectedOwners returns, sorted, every owner the container accepted that the
// host re-gate then threw out. These are matches the run really did find, so
// reporting the run as "no owners matched" hides them: the drought of
// 2026-09-02/03 was six such rejections that read as the fleet simply finding
// nothing, when the gate was failing on an unrelated broken build.
func rejectedOwners(report map[string]ownerResult) []string {
	var out []string
	for owner, r := range report {
		if r.matched() || r.needsManualCommit() {
			continue
		}
		if r.Status == "already_landed" {
			continue
		}
		out = append(out, owner)
	}
	sort.Strings(out)
	return out
}

// rotateAttemptedToTail moves the owners this run actually attempted to the
// end of the requeued list, keeping never-attempted ones at the front.
//
// A run covers only budget/owner-seconds owners -- 3, for the 7200s/2400s
// default -- but a spec carries 12, and the requeue used to preserve order.
// An owner therefore only left the head by *matching*, so a partition whose
// first owners were hard re-ground those same few every cycle and never
// reached the rest: 173 of 252 planned owners (68%) had never been attempted
// once. Rotating gives every owner a turn, which matters because a
// never-tried owner matches at ~23% against ~15% for a retry.
//
// Order within each group is preserved, so the plan's own ranking still
// decides who goes first among the untried.
func rotateAttemptedToTail(owners, attempted []string) []string {
	if len(attempted) == 0 || len(owners) == 0 {
		return owners
	}
	tried := make(map[string]bool, len(attempted))
	for _, o := range attempted {
		tried[o] = true
	}
	fresh := make([]string, 0, len(owners))
	used := make([]string, 0, len(owners))
	for _, o := range owners {
		if tried[o] {
			used = append(used, o)
		} else {
			fresh = append(fresh, o)
		}
	}
	return append(fresh, used...)
}

// summaryOwnersAttempted reads owners_attempted from a finished run's
// summary.json, or nil when it is missing/unreadable (in which case the
// requeue keeps its original order, exactly as before).
func summaryOwnersAttempted(outDir string) []string {
	data, err := os.ReadFile(filepath.Join(outDir, "summary.json"))
	if err != nil {
		return nil
	}
	var doc struct {
		OwnersAttempted []string `json:"owners_attempted"`
	}
	if err := json.Unmarshal(data, &doc); err != nil {
		return nil
	}
	return doc.OwnersAttempted
}

// summaryOwnersAlreadyResolved reads owners_already_resolved from a
// finished run's summary.json: owners container_agent.py dropped before
// its main loop even started because they were no longer active
// GLOBAL_ASM stubs in the (SRC_OVERLAY-current) checkout -- some other run
// matched and merged them while this one sat queued/requeued/reassigned.
// nil when the field is missing/unreadable (an older summary.json, or a
// run that never wrote one), in which case nothing extra is dropped from
// the requeue, exactly as before this field existed.
func summaryOwnersAlreadyResolved(outDir string) []string {
	data, err := os.ReadFile(filepath.Join(outDir, "summary.json"))
	if err != nil {
		return nil
	}
	var doc struct {
		OwnersAlreadyResolved []string `json:"owners_already_resolved"`
	}
	if err := json.Unmarshal(data, &doc); err != nil {
		return nil
	}
	return doc.OwnersAlreadyResolved
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

// blockingDirtyPath returns the first locally-modified tracked file that a
// `git checkout -B <branch> <baseRef>` would have to overwrite, or "".
//
// touchesMergePaths alone is not enough for this. It names the paths the
// *merge* writes, but the checkout that precedes the merge rewrites every
// file differing between HEAD and baseRef -- so a modification anywhere in
// that set makes git refuse, whatever the path. That gap stranded run
// 585D0-p11-r1: uncommitted disasm/Makefile and tools/try_pragma_compare.py
// passed the two-prefix check, then aborted the checkout.
//
// Dirt outside the set is still tolerated, which matters: the merge repo is
// a shared worktree that routinely carries unrelated edits, and blocking on
// those would stall merges that git would have allowed.
func blockingDirtyPath(porcelain string, rewritten []string) string {
	if len(rewritten) == 0 {
		return ""
	}
	set := make(map[string]bool, len(rewritten))
	for _, name := range rewritten {
		set[name] = true
	}
	for _, path := range modifiedTrackedPaths(porcelain) {
		if set[path] {
			return path
		}
	}
	return ""
}

// modifiedTrackedPaths lists every tracked (non "??") path in `git status
// --porcelain` output, resolving rename lines ("R  old -> new") to their
// destination.
func modifiedTrackedPaths(porcelain string) []string {
	var out []string
	for _, line := range strings.Split(porcelain, "\n") {
		if len(line) < 4 || line[:2] == "??" {
			continue
		}
		path := strings.TrimSpace(line[3:])
		if idx := strings.Index(path, " -> "); idx >= 0 {
			path = path[idx+4:]
		}
		out = append(out, path)
	}
	return out
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

// blockDirty puts rec into the retryable blocked-dirty state with note as
// its reason: logged, alerted (rate-limited per run by Loop.alert), and
// collected by retryBlockedMergeRuns on every later pass.
func (l *Loop) blockDirty(ctx context.Context, rec *fleetstate.RunRecord, note string) {
	rec.Status = fleetstate.StatusMergeBlockedDirty
	rec.Note = note
	l.logf("run %s: %s", rec.Spec.ID, rec.Note)
	l.alert(ctx, "merge_blocked_dirty", rec.Spec.ID,
		fmt.Sprintf("fleetctl: merge repo dirty, run %s blocked", rec.Spec.ID), rec.Note)
}

// runMerge is the sequential merge/branch/PR step. The control loop never
// runs two of these concurrently -- RunOnce/pollRunning call it in a plain
// for loop with no goroutines, which is itself the mutex the task asks for
// (see docs/FLEET_CONTROLLER.md).
func (l *Loop) runMerge(ctx context.Context, rec *fleetstate.RunRecord) error {
	branch := branchName(rec.Spec, rec.MergeRound)
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
		l.blockDirty(ctx, rec, fmt.Sprintf("merge repo %s has uncommitted changes to %s (a path this merge would touch); refusing to branch/commit until it is clean", mergeRepo, conflict))
		return nil
	}

	if err := l.Runner.GitFetch(ctx, mergeRepo); err != nil {
		return fmt.Errorf("fetch origin before branching: %w", err)
	}

	// Fetch first, so the HEAD..baseRef comparison is against the ref the
	// checkout will actually use.
	rewritten, err := l.Runner.GitDiffNames(ctx, mergeRepo, baseRef)
	if err != nil {
		l.logf("run %s: could not list files %s would rewrite (%v); attempting the checkout anyway", rec.Spec.ID, baseRef, err)
	} else if conflict := blockingDirtyPath(porcelain, rewritten); conflict != "" {
		l.blockDirty(ctx, rec, fmt.Sprintf("merge repo %s has uncommitted changes to %s, which checking out %s would overwrite; refusing to branch until it is clean", mergeRepo, conflict, baseRef))
		return nil
	}

	if err := l.Runner.GitCheckoutNewBranch(ctx, mergeRepo, branch, baseRef); err != nil {
		// Defect: this used to return a bare error, leaving the run in
		// StatusMerging -- which pollRunning skips and
		// retryBlockedMergeRuns does not collect, so it never advanced
		// again, while still reserving its owners as in-flight (see
		// reserve() in reconcileQueue) and so silently withholding them
		// from every future run. Block retryably instead: whatever the
		// cause, the next pass retries and it heals once the repo is
		// clean.
		l.blockDirty(ctx, rec, fmt.Sprintf("create branch %s from %s failed: %v", branch, baseRef, err))
		return nil
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
	} else if rejected := rejectedOwners(report.Owners); len(rejected) > 0 {
		// Distinguish "found nothing" from "found something the host re-gate
		// refused" -- the two look identical in the log otherwise, and only
		// the second one means something is wrong with the gate.
		l.logf("run %s: no owners matched this run: %d container-accepted owner(s) "+
			"REJECTED by the host re-gate (%s); see %s/merge-results/",
			rec.Spec.ID, len(rejected), strings.Join(rejected, ", "), rec.OutDir)
	} else {
		l.logf("run %s: no owners matched this run", rec.Spec.ID)
	}

	if err := l.Runner.GitCheckoutDetach(ctx, mergeRepo, baseRef); err != nil {
		l.logf("run %s: checkout --detach %s failed: %v", rec.Spec.ID, baseRef, err)
	}

	// An owner needing a manual commit already has its candidate installed
	// in the merge repo's working tree -- requeueing it would re-probe a
	// duplicate against a tree that (once committed by hand) will already
	// contain it. An owner container_agent.py reported as already resolved
	// (owners_already_resolved: dropped before its main loop even started,
	// because some other run matched and merged it while this one sat
	// queued/requeued/reassigned) would just fail the same live check on
	// its next attempt too -- requeueing it again would loop forever,
	// relaunching a whole container each time only to have it drop the
	// same owner in under a second. Only owners neither matched, awaiting
	// a manual commit, nor already resolved elsewhere go back on the queue
	// for a fresh attempt.
	alreadyResolved := summaryOwnersAlreadyResolved(rec.OutDir)
	if len(alreadyResolved) > 0 {
		l.logf("run %s: %d owner(s) already resolved elsewhere before this run's own generator ever ran, dropping from requeue: %s",
			rec.Spec.ID, len(alreadyResolved), strings.Join(alreadyResolved, ", "))
	}
	unmatched := rotateAttemptedToTail(
		subtract(subtract(subtract(rec.Spec.Owners, accepted), needsCommit), alreadyResolved),
		summaryOwnersAttempted(rec.OutDir),
	)
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
			if l.attemptMerge(ctx, id, rec) {
				// "stop merging until fixed" -- do not evaluate any other
				// StatusPROpen run this pass (finishMerge's own fast-forward
				// failed).
				return nil
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

// attemptMerge is pollPRs' per-run merge attempt for a PR whose checks all
// report SUCCESS. Before ever calling `gh pr merge`, it queries GhPRState
// (sec 2/7):
//
//   - state == MERGED already -- idempotent recovery (bug: the merge repo
//     is always detached HEAD, so a PAST `gh pr merge` call could have
//     landed the merge on GitHub and then still returned an error --
//     "could not determine current branch" -- from its own now-removed
//     --delete-branch step; without this check pollPRs would retry forever,
//     logging "already merged" every pass). finishMerge runs exactly as if
//     GhPRMerge had just succeeded.
//   - mergeable == CONFLICTING -- another PR touching the same file (or
//     files) landed first, or this PR's base has simply moved on: `gh pr
//     merge` would fail every pass forever, so replayConflictedPR closes it
//     and re-runs the merge step against a freshly fetched base instead.
//
// Otherwise it calls GhPRMerge as before; a GhPRMerge error is given the
// same idempotent-recovery check (gh may have merged before erroring) before
// being logged (de-duplicated by logMergeFailure).
//
// Returns true when pollPRs must stop evaluating any further StatusPROpen
// run this pass (see finishMerge).
func (l *Loop) attemptMerge(ctx context.Context, id string, rec *fleetstate.RunRecord) bool {
	mergeRepo := l.mergeRepo()
	state, err := l.Runner.GhPRState(ctx, mergeRepo, rec.PRNumber)
	if err != nil {
		l.logf("run %s: gh pr view %d --json state,mergeable failed: %v", id, rec.PRNumber, err)
	} else {
		if state.State == "MERGED" {
			l.logf("run %s: PR #%d is already MERGED on GitHub (idempotent recovery)", id, rec.PRNumber)
			return l.finishMerge(ctx, id, rec)
		}
		if state.Mergeable == "CONFLICTING" {
			l.replayConflictedPR(ctx, id, rec)
			return false
		}
	}
	if err := l.Runner.GhPRMerge(ctx, mergeRepo, rec.PRNumber); err != nil {
		if state2, err2 := l.Runner.GhPRState(ctx, mergeRepo, rec.PRNumber); err2 == nil && state2.State == "MERGED" {
			l.logf("run %s: PR #%d was already merged despite a gh pr merge error (idempotent recovery): %v", id, rec.PRNumber, err)
			return l.finishMerge(ctx, id, rec)
		}
		l.logMergeFailure(id, rec.PRNumber, err)
		return false
	}
	return l.finishMerge(ctx, id, rec)
}

// finishMerge lands a merge pollPRs now considers successful -- either
// GhPRMerge itself just succeeded, or GhPRState reported the PR already
// MERGED (idempotent recovery, see attemptMerge). It marks the run merged,
// best-effort deletes its remote branch (GhPRMerge no longer passes
// --delete-branch -- see its own doc -- since that fails outright from the
// merge repo's always-detached HEAD), fast-forwards the base ref, and
// replans. Returns true when pollPRs must stop evaluating any further
// StatusPROpen run this pass (a fast-forward failure sets
// State.MergeBlocked, "stop merging until fixed", sec 1).
func (l *Loop) finishMerge(ctx context.Context, id string, rec *fleetstate.RunRecord) bool {
	rec.Status = fleetstate.StatusMerged
	rec.MergedAt = l.now()
	l.logf("run %s: PR #%d merged", id, rec.PRNumber)
	if rec.Branch != "" {
		if err := l.Runner.GitDeleteRemoteBranch(ctx, l.mergeRepo(), rec.Branch); err != nil {
			l.logf("run %s: delete remote branch %s failed (best-effort): %v", id, rec.Branch, err)
		}
	}
	if err := l.fastForwardBase(ctx); err != nil {
		l.State.MergeBlocked = true
		l.State.MergeBlockedReason = err.Error()
		l.alert(ctx, "ff_failed", "",
			fmt.Sprintf("fleetctl: fast-forward of %s failed after merging PR #%d", l.IntegrationBranch, rec.PRNumber),
			fmt.Sprintf("%v\nSelf-merge is paused until %s is fixed by hand in %s -- fleetctl retries the fast-forward at the top of every poll pass.",
				err, l.IntegrationBranch, l.mergeRepo()))
		return true
	}
	l.State.LastMergeAt = l.now()
	l.recordMergeCommit(ctx, id, rec)
	if err := l.Replan(ctx); err != nil {
		l.logf("run %s: replan after merge failed: %v", id, err)
	}
	return false
}

// replayConflictedPR handles a PR pollPRs found CONFLICTING against the
// current base (docs/FLEET_CONTROLLER.md sec 2/7, "PR conflict replay") --
// e.g. another PR touching the same file(s) landed first, or this PR was
// simply opened from a now-stale base. `gh pr merge` would fail on it every
// pass forever, so instead: close the stale PR, best-effort delete its
// remote branch, clear the run's PR bookkeeping, bump MergeRound (so
// branchName cuts a fresh branch rather than reusing the closed PR's one),
// fetch the base ref, and re-run the merge step. container_merge.py's own
// re-gate is idempotent (an owner already landed on master is reported
// already_landed), so this only ever re-gates what is still actually
// missing -- runMerge's own no-accepted-owners path (StatusDone, no PR)
// applies cleanly if nothing is left.
// discardStaleMergeReport removes <outDir>/merge-report.json, if any. A
// missing file is not an error (a run that never merged before, or whose
// out_dir was already cleaned up, has none to discard).
func discardStaleMergeReport(outDir string) error {
	if outDir == "" {
		return nil
	}
	if err := os.Remove(filepath.Join(outDir, "merge-report.json")); err != nil && !os.IsNotExist(err) {
		return err
	}
	return nil
}

func (l *Loop) replayConflictedPR(ctx context.Context, id string, rec *fleetstate.RunRecord) {
	mergeRepo := l.mergeRepo()
	prNumber := rec.PRNumber
	l.logf("run %s: PR #%d is CONFLICTING with %s; replaying the run against a fresh base",
		id, prNumber, l.IntegrationBranch)

	comment := fmt.Sprintf(
		"Closing: this PR's base has moved on (e.g. another PR touching the same file merged first) and it now conflicts. fleetctl is replaying run %s against the current base.",
		id)
	if err := l.Runner.GhPRClose(ctx, mergeRepo, prNumber, comment); err != nil {
		l.logf("run %s: gh pr close %d failed: %v", id, prNumber, err)
	}
	if rec.Branch != "" {
		if err := l.Runner.GitDeleteRemoteBranch(ctx, mergeRepo, rec.Branch); err != nil {
			l.logf("run %s: delete remote branch %s failed (best-effort): %v", id, rec.Branch, err)
		}
	}
	rec.PRURL = ""
	rec.PRNumber = 0
	rec.Branch = ""
	rec.MergeRound++

	if err := l.Runner.GitFetch(ctx, mergeRepo); err != nil {
		l.logf("run %s: git fetch before replay failed: %v", id, err)
	}

	// Round N's own merge-report.json in rec.OutDir marks these owners
	// "accepted" (or an object with committed:true) because round N really
	// did commit them -- to the branch just closed and deleted above.
	// container_merge.py's idempotency check (process_owner,
	// previous_entry_marks_committed) reads exactly this file and, left in
	// place, reads that stale "accepted" as proof the owner already landed
	// on IntegrationBranch, silently reporting already_landed and never
	// re-committing it -- the re-gate this replay exists to do never
	// actually re-gates anything. That check is correct for its designed
	// case (re-running merge --commit against an <out> whose PR really did
	// merge); it just cannot tell a merged branch from a closed one. Since
	// this replay just discarded round N's branch/PR, its report is stale
	// evidence and must not carry forward. Observed live: three PRs closed
	// this way (five accepted functions total) were never recreated and
	// had to be recovered by hand from each PR's own still-live git ref.
	if err := discardStaleMergeReport(rec.OutDir); err != nil {
		l.logf("run %s: discard stale merge-report.json failed (best-effort): %v", id, err)
	}

	rec.Status = fleetstate.StatusMerging
	if err := l.runMerge(ctx, rec); err != nil {
		l.logf("run %s: replay merge error: %v", id, err)
	}
	l.alert(ctx, "pr_conflict_replayed", id,
		fmt.Sprintf("fleetctl: PR conflict replayed for run %s", id),
		fmt.Sprintf("Run %s's PR #%d conflicted with %s and was closed; replayed as merge round %d.",
			id, prNumber, l.IntegrationBranch, rec.MergeRound))
}

// logMergeFailure logs "gh pr merge N failed" once per distinct error
// message per PR number: pollPRs runs every pass, and an unresolved failure
// (an auth hiccup, a not-yet-detected conflict, ...) would otherwise print
// the identical line forever.
func (l *Loop) logMergeFailure(id string, prNumber int, err error) {
	msg := err.Error()
	if l.lastMergeFailure == nil {
		l.lastMergeFailure = map[int]string{}
	}
	if l.lastMergeFailure[prNumber] == msg {
		return
	}
	l.lastMergeFailure[prNumber] = msg
	l.logf("run %s: gh pr merge %d failed: %v", id, prNumber, err)
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

// inFlightOwners returns, per file, the set of owners already claimed by a
// run that a replan must never duplicate: every currently queued run that
// would survive reconcileQueue (keepAcrossReplan -- already launched at
// least once, or carrying seed dirs from a post-merge reseed), plus every
// run already Running/Merging/PROpen. Shared by reconcileQueue (so a fresh
// ordinary partition never re-claims a live attempt's owner) and
// enqueuePermuterLane (so a permuter-lane partition never does either --
// see that function's own comment for the gap this closes). Deliberately
// agent-agnostic: an ordinary run's owner is off-limits to a fresh
// permuter-lane partition exactly as much as another ordinary run's is,
// and vice versa (permuterInFlight already keeps two permuter-lane runs
// for the same file from coexisting; this is the complementary,
// owner-level check across the two lanes).
// reserveOwners records file's owners as claimed in claimed, the shared
// per-file owner-reservation shape inFlightOwners builds and
// launchEligible keeps live for the rest of its own pass.
func reserveOwners(claimed map[string]map[string]bool, file string, owners []string) {
	m := claimed[file]
	if m == nil {
		m = map[string]bool{}
		claimed[file] = m
	}
	for _, o := range owners {
		m[o] = true
	}
}

// runningOwners returns, per file, the owners already claimed by a run
// that's genuinely active right now, independent of State.Queue entirely:
// Running/Merging (its full Spec.Owners -- nothing about it has been
// resolved yet) or PROpen (MatchedOwners only, not Spec.Owners -- by the
// time a run reaches StatusPROpen, its own runMerge call has already
// split any unmatched remainder off into a fresh sibling spec via its own
// unmatched-owner reseed, so Spec.Owners is stale; MatchedOwners is the
// accurate "still genuinely tied up in this open PR" set. Reserving the
// full Spec.Owners here would wrongly claim the unmatched owners against
// their own just-created sibling, which needs them free to attempt).
func (l *Loop) runningOwners() map[string]map[string]bool {
	claimed := map[string]map[string]bool{}
	for _, rec := range l.State.Runs {
		switch rec.Status {
		case fleetstate.StatusRunning, fleetstate.StatusMerging:
			reserveOwners(claimed, rec.Spec.File, rec.Spec.Owners)
		case fleetstate.StatusPROpen:
			reserveOwners(claimed, rec.Spec.File, rec.MatchedOwners)
		}
	}
	return claimed
}

// inFlightOwners extends runningOwners with every currently queued run
// that would survive reconcileQueue (keepAcrossReplan) -- for checking a
// brand new candidate that is not itself already a member of State.Queue
// (a fresh Build() partition, or an enqueuePermuterLane partition), so
// there's no risk of a queue entry claiming against itself. launchEligible
// deliberately uses runningOwners instead, NOT this: it iterates
// State.Queue itself and reserves each entry's owners only once that
// entry has actually launched (see reserveOwners's call sites there), so
// pre-seeding from the whole queue here would make every keepAcrossReplan
// entry claim against its own unlaunched self.
func (l *Loop) inFlightOwners() map[string]map[string]bool {
	claimed := l.runningOwners()
	for _, id := range l.State.Queue {
		rec := l.State.Runs[id]
		if rec != nil && keepAcrossReplan(rec) {
			reserveOwners(claimed, rec.Spec.File, rec.Spec.Owners)
		}
	}
	return claimed
}

// pruneClaimedOwners removes from rec.Spec.Owners any owner already
// claimed per `claimed` (see inFlightOwners/reserveOwners) -- the
// launch-time backstop for reconcileQueue/enqueuePermuterLane's own
// replan-time dedup, closing the gap regardless of how two queue entries
// ended up sharing an owner in the first place. Observed live: two
// independent codex/gemini runs launched onto the identical owner at the
// same time, because NextRequeueID's counter is keyed by a plain string
// shared across two semantically different callers -- reconcileQueue's
// own ID-collision rename (a brand new partition that happens to compute
// the same "<file>-p<N>" id as an old, already-finished run) and
// runMerge's genuine unmatched-owner reseed (a specific run's own actual
// leftover work) -- so the same base run id can silently end up with two
// unrelated children, each carrying its own, potentially-overlapping
// owner list, with nothing before launch time ever cross-checking them
// against each other again. Mutates rec.Spec.Owners only when something
// was actually dropped; returns the dropped owners, for logging.
func pruneClaimedOwners(rec *fleetstate.RunRecord, claimed map[string]map[string]bool) []string {
	already := claimed[rec.Spec.File]
	if len(already) == 0 {
		return nil
	}
	var kept, dropped []string
	for _, o := range rec.Spec.Owners {
		if already[o] {
			dropped = append(dropped, o)
		} else {
			kept = append(kept, o)
		}
	}
	if len(dropped) == 0 {
		return nil
	}
	rec.Spec.Owners = kept
	return dropped
}

// reconcileQueue rebuilds State.Queue from fresh's candidate partitions:
// every not-yet-launched, not-seeded queue entry is dropped and replaced
// wholesale ("runs already queued but not launched are replaced by the
// fresh plan", sec 2); every run this pass keeps (queued survivors, plus
// every run already running/merging/pr_open) reserves its own owners
// (inFlightOwners, computed before any deletion below -- a dropped entry is
// by definition never kept-or-active, so it was never reserved either), and
// a fresh candidate partition has those owners subtracted out so a live
// attempt is never duplicated by a fresh one for the same file+owner.
func (l *Loop) reconcileQueue(fresh *planpkg.Plan) {
	inFlight := l.inFlightOwners()

	kept := make([]string, 0, len(l.State.Queue))
	for _, id := range l.State.Queue {
		rec := l.State.Runs[id]
		if rec == nil {
			continue
		}
		if keepAcrossReplan(rec) {
			kept = append(kept, id)
		} else {
			delete(l.State.Runs, id)
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
//
// Before anything else, every entry is pruned against claimed (seeded from
// runningOwners -- NOT inFlightOwners, which also pre-reserves every
// keepAcrossReplan queue entry and would make each one claim against its
// own unlaunched self here -- kept live for the rest of this pass -- see
// pruneClaimedOwners): a queue entry whose owner already has a live claim
// elsewhere has that owner dropped before it's ever considered for launch,
// and a successful launch immediately reserves its own (possibly-just-
// pruned) owners so a *later* entry in this same pass can't claim them
// either. This is the launch-time backstop for reconcileQueue/
// enqueuePermuterLane's own replan-time dedup -- see pruneClaimedOwners's
// own comment for the real incident (two independent runs launched onto
// the identical owner at once) this closes.
func (l *Loop) launchEligible(ctx context.Context) error {
	if len(l.State.Queue) == 0 {
		return nil
	}
	totalRunning, byAgent := l.State.RunningCount()
	byAgentModel := l.State.RunningCountByAgentModel()
	byFile := l.State.RunningCountByFile()
	now := l.now()
	max := l.maxConcurrent()
	claimed := l.runningOwners()

	remaining := l.State.Queue[:0:0]
	for _, id := range l.State.Queue {
		rec := l.State.Runs[id]
		if rec == nil {
			continue
		}
		if dropped := pruneClaimedOwners(rec, claimed); len(dropped) > 0 {
			l.logf("run %s: dropped %d owner(s) already claimed by another live run for %s: %s",
				id, len(dropped), rec.Spec.File, strings.Join(dropped, ", "))
			if len(rec.Spec.Owners) == 0 {
				l.logf("run %s: nothing left after dropping already-claimed owners; discarding", id)
				continue
			}
		}
		switch {
		// A vanish-triggered requeue (handleExit, sec 2) is held back at
		// least vanishBackoff regardless of capacity/cooldown -- checked
		// first so it is never masked by (and never counted against) the
		// concurrency/cooldown cases below.
		case !rec.NotBefore.IsZero() && now.Before(rec.NotBefore):
			rec.WaitReason = fmt.Sprintf("backoff until %s", rec.NotBefore.Format(time.RFC3339))
			remaining = append(remaining, id)
		case totalRunning >= max:
			rec.WaitReason = "concurrency"
			remaining = append(remaining, id)
		// A file already at MaxPerFile concurrent runs is left queued
		// regardless of agent -- checked before cooldown/reassignment
		// below, since reassigning this run to a different agent would
		// not relieve a cap that is keyed on the file, not the agent.
		case l.MaxPerFile > 0 && byFile[rec.Spec.File] >= l.MaxPerFile:
			rec.WaitReason = "file-concurrency"
			remaining = append(remaining, id)
		// permuterAgent is never subject to cooldown (sec 13), so this case
		// can never fire for it regardless of what State.Cooldowns holds.
		// Checks both the model-specific key a real exhaustion now writes
		// (cooldownKey) and the bare-agent key (kept for a coarse/manual
		// provider-wide cooldown, and for existing callers/tests that set
		// one directly) -- either blocks this run.
		case rec.Spec.Agent != permuterAgent &&
			(l.State.OnCooldown(rec.Spec.Agent, now) || l.State.OnCooldown(cooldownKey(rec.Spec.Agent, rec.Spec.Model), now)):
			// Quota-window-aware scheduling (sec 12): rather than leave the
			// slot idle, hand this partition to the next eligible agent
			// (round-robin over the plan's own roster, preferring one whose
			// window just reopened) instead of waiting out rec's own
			// agent's cooldown.
			if alt, ok := l.reassignAgent(rec.Spec.Agent, now, byAgent, byAgentModel); ok {
				l.logf("run %s: agent %s on cooldown; reassigning to %s:%s%s (sec 12)",
					id, rec.Spec.Agent, alt.Agent, alt.Model, effortSuffix(alt.Effort))
				rec.Note = appendReassignNote(rec.Note, rec.Spec.Agent, alt.Agent)
				rec.Spec.Agent, rec.Spec.Model, rec.Spec.Effort = alt.Agent, alt.Model, alt.Effort
				if err := l.launch(ctx, rec); err != nil {
					l.logf("run %s: launch failed: %v", id, err)
					remaining = append(remaining, id)
					continue
				}
				reserveOwners(claimed, rec.Spec.File, rec.Spec.Owners)
				totalRunning++
				byAgent[alt.Agent]++
				byAgentModel[fleetstate.AgentModelKey(alt.Agent, alt.Model)]++
				byFile[rec.Spec.File]++
				continue
			}
			rec.WaitReason = "cooldown"
			remaining = append(remaining, id)
		case l.agentConcurrencyExceeded(rec.Spec.Agent, rec.Spec.Model, byAgent, byAgentModel):
			rec.WaitReason = "concurrency"
			remaining = append(remaining, id)
		default:
			if err := l.launch(ctx, rec); err != nil {
				l.logf("run %s: launch failed: %v", id, err)
				remaining = append(remaining, id)
				continue
			}
			reserveOwners(claimed, rec.Spec.File, rec.Spec.Owners)
			totalRunning++
			byAgent[rec.Spec.Agent]++
			byAgentModel[fleetstate.AgentModelKey(rec.Spec.Agent, rec.Spec.Model)]++
			byFile[rec.Spec.File]++
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
		OwnerSeconds:    l.OwnerSeconds,
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
	rec.NotBefore = time.Time{}
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
