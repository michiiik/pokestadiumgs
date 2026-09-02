package runner

import (
	"context"
	"strings"
	"testing"
)

// TestLaunchContainerDryRunPrintsPermuterOnlyCommand exercises the exact
// permuter-lane launch command docs/FLEET_CONTROLLER.md sec 13 promises:
// no --budget-seconds, --mode/--tie-pool-file/--permuter-seconds ahead of
// --owners, no GENERATOR_MODEL (LaunchSpec.Model empty), AGENT=permuter.
func TestLaunchContainerDryRunPrintsPermuterOnlyCommand(t *testing.T) {
	var lines []string
	r := &ExecRunner{RepoRoot: "/repo", DryRun: true, Log: func(s string) { lines = append(lines, s) }}

	id, err := r.LaunchContainer(context.Background(), LaunchSpec{
		SourceFile:      "disasm/src/x.c",
		OutDir:          "/runs/x-permuter",
		Owners:          []string{"func_1", "func_2"},
		Agent:           "permuter",
		Mode:            "permuter-only",
		TiePoolFile:     "/out/tie-pool-input.json",
		PermuterSeconds: 1200,
	})
	if err != nil {
		t.Fatal(err)
	}
	if id == "" {
		t.Fatal("dry-run LaunchContainer should still return a synthetic container id")
	}
	if len(lines) != 1 {
		t.Fatalf("expected exactly one logged line, got %v", lines)
	}
	line := lines[0]

	if strings.Contains(line, "--budget-seconds") {
		t.Fatalf("permuter-only launch must not pass --budget-seconds: %s", line)
	}
	if strings.Contains(line, "GENERATOR_MODEL") {
		t.Fatalf("permuter-only launch (no model) must not set GENERATOR_MODEL: %s", line)
	}
	if !strings.Contains(line, "AGENT=permuter") {
		t.Fatalf("expected AGENT=permuter: %s", line)
	}

	wantCmd := `bash container/run.sh disasm/src/x.c /runs/x-permuter --mode permuter-only --tie-pool-file /out/tie-pool-input.json --permuter-seconds 1200 --owners func_1,func_2`
	if !strings.Contains(line, wantCmd) {
		t.Fatalf("logged command = %q, want it to contain %q", line, wantCmd)
	}

	// The flag order matters (docs sec 13's exact example): --mode before
	// --tie-pool-file before --permuter-seconds before --owners.
	modeIdx := strings.Index(line, "--mode")
	tieIdx := strings.Index(line, "--tie-pool-file")
	secIdx := strings.Index(line, "--permuter-seconds")
	ownersIdx := strings.Index(line, "--owners")
	if !(modeIdx < tieIdx && tieIdx < secIdx && secIdx < ownersIdx) {
		t.Fatalf("flag order wrong: mode=%d tie=%d sec=%d owners=%d in %q", modeIdx, tieIdx, secIdx, ownersIdx, line)
	}
}

// TestLaunchContainerDryRunOrdinaryRunStillPassesBudgetSeconds is the
// regression guard for the ordinary (non-permuter) path: Mode == "" must
// keep passing --budget-seconds exactly as before this change.
func TestLaunchContainerDryRunOrdinaryRunStillPassesBudgetSeconds(t *testing.T) {
	var lines []string
	r := &ExecRunner{RepoRoot: "/repo", DryRun: true, Log: func(s string) { lines = append(lines, s) }}

	if _, err := r.LaunchContainer(context.Background(), LaunchSpec{
		SourceFile: "disasm/src/x.c", OutDir: "/runs/x-p0", BudgetSeconds: 3600,
		Agent: "codex", Model: "gpt-5.6-luna",
	}); err != nil {
		t.Fatal(err)
	}
	if len(lines) != 1 || !strings.Contains(lines[0], "--budget-seconds 3600") {
		t.Fatalf("expected --budget-seconds 3600 in %v", lines)
	}
	if !strings.Contains(lines[0], "GENERATOR_MODEL=gpt-5.6-luna") {
		t.Fatalf("expected GENERATOR_MODEL=gpt-5.6-luna in %v", lines)
	}
}

// TestGhPRMergeNeverPassesDeleteBranch is the regression guard for bug 1
// (docs/FLEET_CONTROLLER.md sec 7): the merge repo is always detached HEAD,
// so `gh pr merge --delete-branch` there fails with "could not determine
// current branch" even though the merge itself already landed -- GhPRMerge
// must never pass --delete-branch; GitDeleteRemoteBranch is the caller's
// separate, best-effort cleanup instead.
func TestGhPRMergeNeverPassesDeleteBranch(t *testing.T) {
	var lines []string
	r := &ExecRunner{RepoRoot: "/repo", DryRun: true, Log: func(s string) { lines = append(lines, s) }}

	if err := r.GhPRMerge(context.Background(), "/merge-repo", 42); err != nil {
		t.Fatal(err)
	}
	if len(lines) != 1 {
		t.Fatalf("expected exactly one logged line, got %v", lines)
	}
	if strings.Contains(lines[0], "--delete-branch") {
		t.Fatalf("GhPRMerge must never pass --delete-branch: %s", lines[0])
	}
	wantCmd := "gh pr merge 42 --merge"
	if !strings.Contains(lines[0], wantCmd) {
		t.Fatalf("logged command = %q, want it to contain %q", lines[0], wantCmd)
	}
}

func TestGhPRCloseBuildsCommentArgv(t *testing.T) {
	var lines []string
	r := &ExecRunner{RepoRoot: "/repo", DryRun: true, Log: func(s string) { lines = append(lines, s) }}

	if err := r.GhPRClose(context.Background(), "/merge-repo", 54, "closing: conflicting"); err != nil {
		t.Fatal(err)
	}
	if len(lines) != 1 {
		t.Fatalf("expected exactly one logged line, got %v", lines)
	}
	wantCmd := `gh pr close 54 --comment "closing: conflicting"`
	if !strings.Contains(lines[0], wantCmd) {
		t.Fatalf("logged command = %q, want it to contain %q", lines[0], wantCmd)
	}
}

func TestGitDeleteRemoteBranchBuildsPushDeleteArgv(t *testing.T) {
	var lines []string
	r := &ExecRunner{RepoRoot: "/repo", DryRun: true, Log: func(s string) { lines = append(lines, s) }}

	if err := r.GitDeleteRemoteBranch(context.Background(), "/merge-repo", "container/x-p0"); err != nil {
		t.Fatal(err)
	}
	if len(lines) != 1 {
		t.Fatalf("expected exactly one logged line, got %v", lines)
	}
	wantCmd := "git -C /merge-repo push origin --delete container/x-p0"
	if !strings.Contains(lines[0], wantCmd) {
		t.Fatalf("logged command = %q, want it to contain %q", lines[0], wantCmd)
	}
}
