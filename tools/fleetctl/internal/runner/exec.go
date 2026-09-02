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
	argv := []string{"bash", "container/run.sh", spec.SourceFile, spec.OutDir,
		"--budget-seconds", strconv.Itoa(spec.BudgetSeconds)}
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

func (r *ExecRunner) GitCheckoutNewBranch(ctx context.Context, repoRoot, branch, from string) error {
	result, err := r.runOrDryRun(ctx, r.RepoRoot, nil, "git", "-C", repoRoot, "checkout", "-b", branch, from)
	return gitErr(result, err, "git checkout -b "+branch, r.DryRun)
}

func (r *ExecRunner) GitCheckout(ctx context.Context, repoRoot, ref string) error {
	result, err := r.runOrDryRun(ctx, r.RepoRoot, nil, "git", "-C", repoRoot, "checkout", ref)
	return gitErr(result, err, "git checkout "+ref, r.DryRun)
}

func (r *ExecRunner) GitPush(ctx context.Context, repoRoot, branch string) error {
	result, err := r.runOrDryRun(ctx, r.RepoRoot, nil, "git", "-C", repoRoot, "push", "-u", "origin", branch)
	return gitErr(result, err, "git push -u origin "+branch, r.DryRun)
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

func (r *ExecRunner) RankFiles(ctx context.Context, repoRoot string, maxInstructions int, excludeRecentHours float64, limit int) ([]FileRank, error) {
	argv := []string{r.pythonBin(), "tools/pragma_targets.py", "rank-files", "--json"}
	if maxInstructions > 0 {
		argv = append(argv, "--max-instructions", strconv.Itoa(maxInstructions))
	}
	if excludeRecentHours > 0 {
		argv = append(argv, "--exclude-recent", strconv.FormatFloat(excludeRecentHours, 'g', -1, 64))
	}
	if limit > 0 {
		argv = append(argv, "--limit", strconv.Itoa(limit))
	}
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
	result, err := run(ctx, repoRoot, nil,
		r.pythonBin(), "tools/pragma_targets.py", "targets", "--source", source, "--limit", "100000")
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
