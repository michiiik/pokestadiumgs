package runner

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"strconv"
	"strings"
	"time"
)

// ExecRunner is the real Runner: it shells out to docker, git, gh, and the
// repo's own python tools. With DryRun set, every command that would touch
// a container, git history, or GitHub is printed (via Log, or fmt.Println
// when Log is nil) instead of executed; read-only python-tool calls
// (RankFiles, Targets) always run for real -- plan needs their real output
// even under --dry-run, and they never touch docker/git/gh (see
// docs/FLEET_CONTROLLER.md).
type ExecRunner struct {
	// RepoRoot is the checkout container/run.sh and tools/*.py are invoked
	// from (their cwd). It is NOT necessarily the same as a MergeSpec's own
	// RepoRoot / a git call's repoRoot, which name the checkout being
	// re-gated, committed to, or branched -- ordinarily the same directory,
	// but kept separate so a caller can point them elsewhere in tests.
	RepoRoot string
	// PythonBin overrides "python3" (tests only).
	PythonBin string
	DryRun    bool
	// Log receives one line per command; defaults to fmt.Println.
	Log func(string)
}

func (r *ExecRunner) log(format string, args ...any) {
	line := fmt.Sprintf(format, args...)
	if r.Log != nil {
		r.Log(line)
		return
	}
	fmt.Println(line)
}

func (r *ExecRunner) pythonBin() string {
	if r.PythonBin != "" {
		return r.PythonBin
	}
	return "python3"
}

func quoteArgs(argv []string) string {
	quoted := make([]string, len(argv))
	for i, a := range argv {
		if a == "" || strings.ContainsAny(a, " \t\"'") {
			quoted[i] = fmt.Sprintf("%q", a)
		} else {
			quoted[i] = a
		}
	}
	return strings.Join(quoted, " ")
}

// run executes argv with the given cwd and extra env (appended to the
// current process environment), returning a ProcessResult. Never used for
// commands gated by DryRun -- see runOrDryRun.
func run(ctx context.Context, dir string, env []string, argv ...string) (ProcessResult, error) {
	cmd := exec.CommandContext(ctx, argv[0], argv[1:]...)
	cmd.Dir = dir
	if len(env) > 0 {
		cmd.Env = append(os.Environ(), env...)
	}
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	err := cmd.Run()
	result := ProcessResult{Stdout: stdout.String(), Stderr: stderr.String()}
	if exitErr, ok := err.(*exec.ExitError); ok {
		result.ExitCode = exitErr.ExitCode()
		return result, nil
	}
	if err != nil {
		return result, err
	}
	return result, nil
}

// runOrDryRun prints the command instead of running it when r.DryRun is
// set, returning a synthetic zero-exit ProcessResult so a --dry-run control
// loop pass can proceed exactly as it would after a real success.
func (r *ExecRunner) runOrDryRun(ctx context.Context, dir string, env []string, argv ...string) (ProcessResult, error) {
	if r.DryRun {
		prefix := ""
		if len(env) > 0 {
			prefix = strings.Join(env, " ") + " "
		}
		r.log("[dry-run] (cwd=%s) %s%s", dir, prefix, quoteArgs(argv))
		return ProcessResult{}, nil
	}
	return run(ctx, dir, env, argv...)
}

func (r *ExecRunner) LaunchContainer(ctx context.Context, spec LaunchSpec) (string, error) {
	argv := []string{"bash", "container/run.sh", spec.SourceFile, spec.OutDir}
	if spec.Mode != "" {
		// Permuter-only lane (docs/FLEET_CONTROLLER.md sec 13): no
		// --budget-seconds (the permuter-only driver stops on
		// --permuter-seconds/plateau, not a wall-clock budget).
		argv = append(argv, "--mode", spec.Mode)
		if spec.TiePoolFile != "" {
			argv = append(argv, "--tie-pool-file", spec.TiePoolFile)
		}
		if spec.PermuterSeconds > 0 {
			argv = append(argv, "--permuter-seconds", strconv.Itoa(spec.PermuterSeconds))
		}
	} else {
		argv = append(argv, "--budget-seconds", strconv.Itoa(spec.BudgetSeconds))
	}
	if len(spec.Owners) > 0 {
		argv = append(argv, "--owners", strings.Join(spec.Owners, ","))
	}
	if len(spec.SeedFrom) > 0 {
		argv = append(argv, "--seed-from", strings.Join(spec.SeedFrom, ","))
	}
	if spec.Resume {
		argv = append(argv, "--resume")
	}
	if spec.GeneratorTimeout > 0 {
		argv = append(argv, "--generator-timeout", strconv.Itoa(spec.GeneratorTimeout))
	}
	if spec.MaxInstructions > 0 {
		argv = append(argv, "--max-instructions", strconv.Itoa(spec.MaxInstructions))
	}
	env := []string{"RUN_DETACHED=1"}
	if spec.Agent != "" {
		env = append(env, "AGENT="+spec.Agent)
	}
	if spec.Model != "" {
		env = append(env, "GENERATOR_MODEL="+spec.Model)
	}
	if spec.Effort != "" {
		env = append(env, "GENERATOR_EFFORT="+spec.Effort)
	}
	if spec.SrcOverlay != "" {
		env = append(env, "SRC_OVERLAY="+spec.SrcOverlay)
	}

	if r.DryRun {
		r.log("[dry-run] (cwd=%s) %s %s", r.RepoRoot, strings.Join(env, " "), quoteArgs(argv))
		return "dryrun-" + filepath.Base(spec.OutDir), nil
	}
	result, err := run(ctx, r.RepoRoot, env, argv...)
	if err != nil {
		return "", fmt.Errorf("launch %s: %w", spec.SourceFile, err)
	}
	if result.ExitCode != 0 {
		return "", fmt.Errorf("launch %s: container/run.sh exited %d: %s",
			spec.SourceFile, result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	id := strings.TrimSpace(result.Stdout)
	// RUN_DETACHED=1 makes docker run -d the last thing run.sh execs, so its
	// stdout is exactly the printed container id followed by a newline; be
	// defensive and take the last non-empty line in case anything else was
	// echoed ahead of it.
	if lines := strings.Split(id, "\n"); len(lines) > 0 {
		id = strings.TrimSpace(lines[len(lines)-1])
	}
	if id == "" {
		return "", fmt.Errorf("launch %s: container/run.sh printed no container id", spec.SourceFile)
	}
	return id, nil
}

func (r *ExecRunner) InspectContainer(ctx context.Context, containerID string) (InspectResult, error) {
	if r.DryRun {
		r.log("[dry-run] docker inspect --format '{{.State.Running}}|{{.State.ExitCode}}' %s", containerID)
		return InspectResult{Found: true, Running: false, ExitCode: 0}, nil
	}
	result, err := run(ctx, r.RepoRoot, nil,
		"docker", "inspect", "--format", "{{.State.Running}}|{{.State.ExitCode}}", containerID)
	if err != nil {
		return InspectResult{}, err
	}
	if result.ExitCode != 0 {
		// "No such object" -- the container vanished (killed out of band,
		// or --rm already reaped it after exiting).
		return InspectResult{Found: false}, nil
	}
	parts := strings.SplitN(strings.TrimSpace(result.Stdout), "|", 2)
	if len(parts) != 2 {
		return InspectResult{}, fmt.Errorf("docker inspect %s: unexpected output %q", containerID, result.Stdout)
	}
	exitCode, _ := strconv.Atoi(parts[1])
	return InspectResult{Found: true, Running: parts[0] == "true", ExitCode: exitCode}, nil
}

func (r *ExecRunner) StopContainer(ctx context.Context, containerID string) error {
	result, err := r.runOrDryRun(ctx, r.RepoRoot, nil, "docker", "stop", containerID)
	if err != nil {
		return err
	}
	if !r.DryRun && result.ExitCode != 0 {
		return fmt.Errorf("docker stop %s: exit %d: %s", containerID, result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	return nil
}

func (r *ExecRunner) Merge(ctx context.Context, spec MergeSpec) (ProcessResult, error) {
	argv := []string{r.pythonBin(), "tools/container_merge.py", "merge", spec.OutDir,
		"--repo", spec.RepoRoot}
	if spec.FreshHistory {
		argv = append(argv, "--fresh-history")
	}
	if spec.Commit {
		argv = append(argv, "--commit")
	}
	if spec.NoCCCheck {
		argv = append(argv, "--no-cc-check")
	}
	return r.runOrDryRun(ctx, r.RepoRoot, nil, argv...)
}

func (r *ExecRunner) ImportStats(ctx context.Context, outDir, repoRoot string) (ProcessResult, error) {
	return r.runOrDryRun(ctx, r.RepoRoot, nil,
		r.pythonBin(), "tools/container_merge.py", "import-stats", outDir, "--repo", repoRoot)
}

func (r *ExecRunner) GitFetch(ctx context.Context, repoRoot string) error {
	result, err := r.runOrDryRun(ctx, r.RepoRoot, nil, "git", "-C", repoRoot, "fetch", "origin")
	return gitErr(result, err, "git fetch origin", r.DryRun)
}

func (r *ExecRunner) GitCheckoutNewBranch(ctx context.Context, repoRoot, branch, from string) error {
	result, err := r.runOrDryRun(ctx, r.RepoRoot, nil, "git", "-C", repoRoot, "checkout", "-B", branch, from)
	return gitErr(result, err, "git checkout -B "+branch, r.DryRun)
}

func (r *ExecRunner) GitCheckoutDetach(ctx context.Context, repoRoot, ref string) error {
	result, err := r.runOrDryRun(ctx, r.RepoRoot, nil, "git", "-C", repoRoot, "checkout", "--detach", ref)
	return gitErr(result, err, "git checkout --detach "+ref, r.DryRun)
}

// GitStatusPorcelain is a read-only query (never gated by DryRun, same
// reasoning as RankFiles/Targets/DockerImageID/GitRevParse) used to check
// the merge repo is clean before a run's merge step branches it.
func (r *ExecRunner) GitStatusPorcelain(ctx context.Context, repoRoot string) (string, error) {
	result, err := run(ctx, r.RepoRoot, nil, "git", "-C", repoRoot, "status", "--porcelain")
	if err != nil {
		return "", fmt.Errorf("git status --porcelain: %w", err)
	}
	if result.ExitCode != 0 {
		return "", fmt.Errorf("git status --porcelain: exit %d: %s", result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	return result.Stdout, nil
}

func (r *ExecRunner) GitResetPath(ctx context.Context, repoRoot, path string) error {
	result, err := r.runOrDryRun(ctx, r.RepoRoot, nil, "git", "-C", repoRoot, "reset", "-q", "--", path)
	return gitErr(result, err, "git reset -q -- "+path, r.DryRun)
}

func (r *ExecRunner) GitCheckoutPath(ctx context.Context, repoRoot, path string) error {
	result, err := r.runOrDryRun(ctx, r.RepoRoot, nil, "git", "-C", repoRoot, "checkout", "--", path)
	return gitErr(result, err, "git checkout -- "+path, r.DryRun)
}

func (r *ExecRunner) GitPush(ctx context.Context, repoRoot, branch string) error {
	result, err := r.runOrDryRun(ctx, r.RepoRoot, nil, "git", "-C", repoRoot, "push", "-u", "origin", branch)
	return gitErr(result, err, "git push -u origin "+branch, r.DryRun)
}

// GitRevParse is a read-only query (never gated by DryRun, matching
// RankFiles/Targets/DockerImageID) used to verify a remote-tracking ref
// (e.g. origin/master, --base-ref) has picked up a just-merged PR's merge
// commit.
func (r *ExecRunner) GitRevParse(ctx context.Context, repoRoot, ref string) (string, error) {
	result, err := run(ctx, r.RepoRoot, nil, "git", "-C", repoRoot, "rev-parse", ref)
	if err != nil {
		return "", fmt.Errorf("git rev-parse %s: %w", ref, err)
	}
	if result.ExitCode != 0 {
		return "", fmt.Errorf("git rev-parse %s: exit %d: %s", ref, result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	return strings.TrimSpace(result.Stdout), nil
}

func gitErr(result ProcessResult, err error, what string, dryRun bool) error {
	if err != nil {
		return fmt.Errorf("%s: %w", what, err)
	}
	if !dryRun && result.ExitCode != 0 {
		return fmt.Errorf("%s: exit %d: %s", what, result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	return nil
}

func (r *ExecRunner) GhPRCreate(ctx context.Context, spec PRSpec) (string, error) {
	argv := []string{"gh", "pr", "create", "--base", spec.Base, "--title", spec.Title, "--body", spec.Body}
	if r.DryRun {
		r.log("[dry-run] (cwd=%s) %s", spec.RepoRoot, quoteArgs(argv))
		return "", nil
	}
	result, err := run(ctx, spec.RepoRoot, nil, argv...)
	if err != nil {
		return "", fmt.Errorf("gh pr create: %w", err)
	}
	if result.ExitCode != 0 {
		return "", fmt.Errorf("gh pr create: exit %d: %s", result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	return strings.TrimSpace(result.Stdout), nil
}

// checkState classifies one entry of `gh pr checks --json name,state`'s
// output. gh's own "state" values include SUCCESS, FAILURE, ERROR,
// PENDING, QUEUED, IN_PROGRESS, CANCELLED, SKIPPED, NEUTRAL, STALE,
// ACTION_REQUIRED, TIMED_OUT -- treated here as three buckets: SUCCESS
// (SUCCESS, SKIPPED, NEUTRAL all count as "did not block"), FAILURE
// (FAILURE, ERROR, CANCELLED, TIMED_OUT, ACTION_REQUIRED, STALE all count
// as "the gate did not pass"), everything else PENDING.
func checkState(raw string) string {
	switch strings.ToUpper(raw) {
	case "SUCCESS", "SKIPPED", "NEUTRAL":
		return "SUCCESS"
	case "FAILURE", "ERROR", "CANCELLED", "TIMED_OUT", "ACTION_REQUIRED", "STALE":
		return "FAILURE"
	default:
		return "PENDING"
	}
}

// GhPRChecks is a read-only query (never gated by DryRun): it rolls every
// reported check up into one PRChecksResult -- SUCCESS only when every
// check reported SUCCESS, FAILURE if any one check failed, PENDING
// otherwise (including "no checks reported yet").
func (r *ExecRunner) GhPRChecks(ctx context.Context, repoRoot string, prNumber int) (PRChecksResult, error) {
	// gh pr checks exits non-zero when a check has failed or is still
	// pending, so --json output is parsed regardless of exit code.
	result, err := run(ctx, repoRoot, nil, "gh", "pr", "checks", strconv.Itoa(prNumber), "--json", "name,state")
	if err != nil {
		return PRChecksResult{}, fmt.Errorf("gh pr checks %d: %w", prNumber, err)
	}
	var rows []struct {
		Name  string `json:"name"`
		State string `json:"state"`
	}
	if err := json.Unmarshal([]byte(result.Stdout), &rows); err != nil {
		return PRChecksResult{}, fmt.Errorf("gh pr checks %d: parse output: %w", prNumber, err)
	}
	if len(rows) == 0 {
		return PRChecksResult{State: "PENDING"}, nil
	}
	agg := "SUCCESS"
	for _, row := range rows {
		switch checkState(row.State) {
		case "FAILURE":
			return PRChecksResult{State: "FAILURE"}, nil
		case "PENDING":
			agg = "PENDING"
		}
	}
	return PRChecksResult{State: agg}, nil
}

// GhPRMerge runs `gh pr merge <prNumber> --merge` -- see the Runner
// interface doc for why --delete-branch is deliberately never passed.
func (r *ExecRunner) GhPRMerge(ctx context.Context, repoRoot string, prNumber int) error {
	argv := []string{"gh", "pr", "merge", strconv.Itoa(prNumber), "--merge"}
	result, err := r.runOrDryRun(ctx, repoRoot, nil, argv...)
	if err != nil {
		return fmt.Errorf("gh pr merge %d: %w", prNumber, err)
	}
	if !r.DryRun && result.ExitCode != 0 {
		return fmt.Errorf("gh pr merge %d: exit %d: %s", prNumber, result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	return nil
}

// GhPRView is a read-only query (never gated by DryRun, same as
// GhPRChecks): it returns the merge commit sha `gh pr view --json
// mergeCommit` reports for a just-merged PR, so the merge repo never has
// to check out or rev-parse a local base branch to learn it.
func (r *ExecRunner) GhPRView(ctx context.Context, repoRoot string, prNumber int) (string, error) {
	result, err := run(ctx, repoRoot, nil, "gh", "pr", "view", strconv.Itoa(prNumber), "--json", "mergeCommit")
	if err != nil {
		return "", fmt.Errorf("gh pr view %d: %w", prNumber, err)
	}
	if result.ExitCode != 0 {
		return "", fmt.Errorf("gh pr view %d: exit %d: %s", prNumber, result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	var payload struct {
		MergeCommit *struct {
			Oid string `json:"oid"`
		} `json:"mergeCommit"`
	}
	if err := json.Unmarshal([]byte(result.Stdout), &payload); err != nil {
		return "", fmt.Errorf("gh pr view %d: parse output: %w", prNumber, err)
	}
	if payload.MergeCommit == nil || payload.MergeCommit.Oid == "" {
		return "", fmt.Errorf("gh pr view %d: mergeCommit not yet reported", prNumber)
	}
	return payload.MergeCommit.Oid, nil
}

// GhPRState is a read-only query (never gated by DryRun, same as
// GhPRChecks/GhPRView): `gh pr view <prNumber> --json
// state,mergeable,mergeStateStatus`.
func (r *ExecRunner) GhPRState(ctx context.Context, repoRoot string, prNumber int) (PRStateResult, error) {
	result, err := run(ctx, repoRoot, nil, "gh", "pr", "view", strconv.Itoa(prNumber),
		"--json", "state,mergeable,mergeStateStatus")
	if err != nil {
		return PRStateResult{}, fmt.Errorf("gh pr view %d --json state,mergeable,mergeStateStatus: %w", prNumber, err)
	}
	if result.ExitCode != 0 {
		return PRStateResult{}, fmt.Errorf("gh pr view %d --json state,mergeable,mergeStateStatus: exit %d: %s",
			prNumber, result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	var payload struct {
		State            string `json:"state"`
		Mergeable        string `json:"mergeable"`
		MergeStateStatus string `json:"mergeStateStatus"`
	}
	if err := json.Unmarshal([]byte(result.Stdout), &payload); err != nil {
		return PRStateResult{}, fmt.Errorf("gh pr view %d: parse output: %w", prNumber, err)
	}
	return PRStateResult{State: payload.State, Mergeable: payload.Mergeable, MergeStateStatus: payload.MergeStateStatus}, nil
}

// GhPRClose runs `gh pr close <prNumber> --comment <comment>`.
func (r *ExecRunner) GhPRClose(ctx context.Context, repoRoot string, prNumber int, comment string) error {
	argv := []string{"gh", "pr", "close", strconv.Itoa(prNumber), "--comment", comment}
	result, err := r.runOrDryRun(ctx, repoRoot, nil, argv...)
	if err != nil {
		return fmt.Errorf("gh pr close %d: %w", prNumber, err)
	}
	if !r.DryRun && result.ExitCode != 0 {
		return fmt.Errorf("gh pr close %d: exit %d: %s", prNumber, result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	return nil
}

// GitDeleteRemoteBranch runs `git -C repoRoot push origin --delete branch`
// -- see the Runner interface doc: callers only log its error.
func (r *ExecRunner) GitDeleteRemoteBranch(ctx context.Context, repoRoot, branch string) error {
	result, err := r.runOrDryRun(ctx, r.RepoRoot, nil, "git", "-C", repoRoot, "push", "origin", "--delete", branch)
	return gitErr(result, err, "git push origin --delete "+branch, r.DryRun)
}

func (r *ExecRunner) GhIssueComment(ctx context.Context, repoRoot string, issueNumber int, body string) error {
	argv := []string{"gh", "issue", "comment", strconv.Itoa(issueNumber), "--body", body}
	result, err := r.runOrDryRun(ctx, repoRoot, nil, argv...)
	if err != nil {
		return fmt.Errorf("gh issue comment %d: %w", issueNumber, err)
	}
	if !r.DryRun && result.ExitCode != 0 {
		return fmt.Errorf("gh issue comment %d: exit %d: %s", issueNumber, result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	return nil
}

// DockerImageID is a read-only query (never gated by DryRun, same
// reasoning as RankFiles/Targets: it touches neither a container, git
// history, nor GitHub) used for stale-image awareness
// (docs/FLEET_CONTROLLER.md sec 6).
func (r *ExecRunner) DockerImageID(ctx context.Context, image string) (string, time.Time, error) {
	result, err := run(ctx, r.RepoRoot, nil,
		"docker", "image", "inspect", image, "--format", "{{.Id}}|{{.Created}}")
	if err != nil {
		return "", time.Time{}, fmt.Errorf("docker image inspect %s: %w", image, err)
	}
	if result.ExitCode != 0 {
		return "", time.Time{}, fmt.Errorf("docker image inspect %s: exit %d: %s", image, result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	parts := strings.SplitN(strings.TrimSpace(result.Stdout), "|", 2)
	if len(parts) != 2 {
		return "", time.Time{}, fmt.Errorf("docker image inspect %s: unexpected output %q", image, result.Stdout)
	}
	created, err := time.Parse(time.RFC3339Nano, parts[1])
	if err != nil {
		return "", time.Time{}, fmt.Errorf("docker image inspect %s: parse created time %q: %w", image, parts[1], err)
	}
	return parts[0], created, nil
}

// OsascriptNotify runs `osascript -e 'display notification ...'` -- the
// --alert-macos notifier's one effect, gated by DryRun like every other
// real-world side effect this package can produce.
func (r *ExecRunner) OsascriptNotify(ctx context.Context, title, body string) error {
	script := fmt.Sprintf("display notification %s with title %s", osascriptQuote(body), osascriptQuote(title))
	result, err := r.runOrDryRun(ctx, r.RepoRoot, nil, "osascript", "-e", script)
	if err != nil {
		return fmt.Errorf("osascript notify: %w", err)
	}
	if !r.DryRun && result.ExitCode != 0 {
		return fmt.Errorf("osascript notify: exit %d: %s", result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	return nil
}

// osascriptQuote wraps s in AppleScript double quotes, escaping backslashes
// and embedded quotes -- osascript's -e argument is itself AppleScript
// source, not a shell string.
func osascriptQuote(s string) string {
	s = strings.ReplaceAll(s, `\`, `\\`)
	s = strings.ReplaceAll(s, `"`, `\"`)
	return `"` + s + `"`
}

func (r *ExecRunner) RankFiles(ctx context.Context, repoRoot string, maxInstructions int, excludeRecentHours float64, limit int) ([]FileRank, error) {
	argv := []string{r.pythonBin(), "tools/pragma_targets.py", "rank-files", "--json"}
	if maxInstructions > 0 {
		argv = append(argv, "--max-instructions", strconv.Itoa(maxInstructions))
	}
	// Negative means "omit the flag entirely" (rank-files' own --exclude-
	// recent default of None, no filtering at all); 0 or positive is passed
	// through explicitly -- 0 still applies rank-files' unconditional
	// dirty-working-tree exclusion, just with no commit-recency window,
	// which control.Loop.Replan (docs/FLEET_CONTROLLER.md sec 2) relies on.
	if excludeRecentHours >= 0 {
		argv = append(argv, "--exclude-recent", strconv.FormatFloat(excludeRecentHours, 'g', -1, 64))
	}
	if limit > 0 {
		argv = append(argv, "--limit", strconv.Itoa(limit))
	}
	// rank-files is read-only (never gated by DryRun -- see the type
	// doc), but its command is still logged so a `run --dry-run --replan`
	// pass shows exactly what it queried, matching every other command
	// this package logs.
	r.log("(cwd=%s) %s", repoRoot, quoteArgs(argv))
	result, err := run(ctx, repoRoot, nil, argv...)
	if err != nil {
		return nil, fmt.Errorf("rank-files: %w", err)
	}
	if result.ExitCode != 0 {
		return nil, fmt.Errorf("rank-files: exit %d: %s", result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	var payload struct {
		Files []FileRank `json:"files"`
	}
	if err := json.Unmarshal([]byte(result.Stdout), &payload); err != nil {
		return nil, fmt.Errorf("rank-files: parse output: %w", err)
	}
	return payload.Files, nil
}

func (r *ExecRunner) Targets(ctx context.Context, repoRoot string, source string) ([]TargetOwner, error) {
	// A high --limit so every owner in the file comes back in one call --
	// list_targets is already sorted smallest-instructions-first and this
	// is a per-file query, never the whole tree.
	argv := []string{r.pythonBin(), "tools/pragma_targets.py", "targets", "--source", source, "--limit", "100000"}
	r.log("(cwd=%s) %s", repoRoot, quoteArgs(argv))
	result, err := run(ctx, repoRoot, nil, argv...)
	if err != nil {
		return nil, fmt.Errorf("targets --source %s: %w", source, err)
	}
	if result.ExitCode != 0 {
		return nil, fmt.Errorf("targets --source %s: exit %d: %s", source, result.ExitCode, strings.TrimSpace(result.Stderr))
	}
	var payload struct {
		Targets []TargetOwner `json:"targets"`
	}
	if err := json.Unmarshal([]byte(result.Stdout), &payload); err != nil {
		return nil, fmt.Errorf("targets --source %s: parse output: %w", source, err)
	}
	return payload.Targets, nil
}
