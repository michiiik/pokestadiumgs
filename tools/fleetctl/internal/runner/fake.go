package runner

import (
	"context"
	"fmt"
	"sync"
	"time"
)

// Call records one method invocation against a Fake, for assertions in
// control-loop tests ("launch command construction with seeds", "PR command
// construction", etc.) without needing a real subprocess.
type Call struct {
	Method string
	Launch LaunchSpec
	Merge  MergeSpec
	PR     PRSpec
	// Generic string args (container id, repo root, branch, ref, source, ...)
	Strings []string
}

// Fake is a scriptable, in-memory Runner for tests. Every field is safe to
// leave at its zero value; results default to "succeeded, did nothing".
type Fake struct {
	mu    sync.Mutex
	Calls []Call

	containerSeq int
	// LaunchIDFunc, when set, names the container id LaunchContainer
	// returns; otherwise ids are "fake-container-<n>".
	LaunchIDFunc func(spec LaunchSpec) string
	LaunchErr    error

	// InspectResults maps a container id to a queue of results popped in
	// call order; once exhausted, the last result (or a not-found result if
	// none was ever queued) repeats.
	InspectResults map[string][]InspectResult
	inspectCalls   map[string]int
	InspectErr     error

	StopErr error

	MergeResult ProcessResult
	MergeErr    error
	// MergeFunc, when set, overrides MergeResult/MergeErr for full control
	// (e.g. a merge that "accepts" specific owners by writing files a test
	// pre-seeded under spec.OutDir).
	MergeFunc func(spec MergeSpec) (ProcessResult, error)

	ImportStatsResult ProcessResult
	ImportStatsErr    error

	GitFetchErr              error
	GitCheckoutNewBranchErr  error
	GitCheckoutDetachErr     error
	GitStatusPorcelainResult string
	GitStatusPorcelainErr    error
	GitResetPathErr          error
	GitCheckoutPathErr       error
	GitPushErr               error
	GitRevParseResult        string
	GitRevParseErr           error

	GhPRURL string
	GhPRErr error

	GhPRViewResult string
	GhPRViewErr    error

	// GhPRChecksFunc, when set, overrides GhPRChecksResult/GhPRChecksErr for
	// full control keyed by PR number (e.g. a test driving one PR through
	// PENDING -> SUCCESS across polls).
	GhPRChecksFunc   func(prNumber int) (PRChecksResult, error)
	GhPRChecksResult PRChecksResult
	GhPRChecksErr    error

	GhPRMergeErr error

	// GhPRStateFunc, when set, overrides GhPRStateResult/GhPRStateErr for
	// full control keyed by PR number (e.g. distinguishing several open
	// PRs' conflict/idempotent-recovery states in one test).
	GhPRStateFunc   func(prNumber int) (PRStateResult, error)
	GhPRStateResult PRStateResult
	GhPRStateErr    error

	GhPRCloseErr error

	GitDeleteRemoteBranchErr error

	GhIssueCommentErr error

	DockerImageIDResult  string
	DockerImageIDCreated time.Time
	DockerImageIDErr     error

	OsascriptErr error

	RankFilesResult []FileRank
	RankFilesErr    error
	// TargetsResult maps a source path to the owners Targets should return
	// for it.
	TargetsResult map[string][]TargetOwner
	TargetsErr    error
}

func (f *Fake) record(c Call) {
	f.mu.Lock()
	defer f.mu.Unlock()
	f.Calls = append(f.Calls, c)
}

func (f *Fake) LaunchContainer(_ context.Context, spec LaunchSpec) (string, error) {
	f.record(Call{Method: "LaunchContainer", Launch: spec})
	if f.LaunchErr != nil {
		return "", f.LaunchErr
	}
	if f.LaunchIDFunc != nil {
		return f.LaunchIDFunc(spec), nil
	}
	f.mu.Lock()
	f.containerSeq++
	id := fmt.Sprintf("fake-container-%d", f.containerSeq)
	f.mu.Unlock()
	return id, nil
}

func (f *Fake) InspectContainer(_ context.Context, containerID string) (InspectResult, error) {
	f.record(Call{Method: "InspectContainer", Strings: []string{containerID}})
	if f.InspectErr != nil {
		return InspectResult{}, f.InspectErr
	}
	f.mu.Lock()
	defer f.mu.Unlock()
	queue := f.InspectResults[containerID]
	if len(queue) == 0 {
		return InspectResult{Found: false}, nil
	}
	if f.inspectCalls == nil {
		f.inspectCalls = map[string]int{}
	}
	idx := f.inspectCalls[containerID]
	if idx >= len(queue) {
		idx = len(queue) - 1
	} else {
		f.inspectCalls[containerID] = idx + 1
	}
	return queue[idx], nil
}

func (f *Fake) StopContainer(_ context.Context, containerID string) error {
	f.record(Call{Method: "StopContainer", Strings: []string{containerID}})
	return f.StopErr
}

func (f *Fake) Merge(_ context.Context, spec MergeSpec) (ProcessResult, error) {
	f.record(Call{Method: "Merge", Merge: spec})
	if f.MergeFunc != nil {
		return f.MergeFunc(spec)
	}
	return f.MergeResult, f.MergeErr
}

func (f *Fake) ImportStats(_ context.Context, outDir, repoRoot string) (ProcessResult, error) {
	f.record(Call{Method: "ImportStats", Strings: []string{outDir, repoRoot}})
	return f.ImportStatsResult, f.ImportStatsErr
}

func (f *Fake) GitFetch(_ context.Context, repoRoot string) error {
	f.record(Call{Method: "GitFetch", Strings: []string{repoRoot}})
	return f.GitFetchErr
}

func (f *Fake) GitCheckoutNewBranch(_ context.Context, repoRoot, branch, from string) error {
	f.record(Call{Method: "GitCheckoutNewBranch", Strings: []string{repoRoot, branch, from}})
	return f.GitCheckoutNewBranchErr
}

func (f *Fake) GitCheckoutDetach(_ context.Context, repoRoot, ref string) error {
	f.record(Call{Method: "GitCheckoutDetach", Strings: []string{repoRoot, ref}})
	return f.GitCheckoutDetachErr
}

func (f *Fake) GitStatusPorcelain(_ context.Context, repoRoot string) (string, error) {
	f.record(Call{Method: "GitStatusPorcelain", Strings: []string{repoRoot}})
	return f.GitStatusPorcelainResult, f.GitStatusPorcelainErr
}

func (f *Fake) GitResetPath(_ context.Context, repoRoot, path string) error {
	f.record(Call{Method: "GitResetPath", Strings: []string{repoRoot, path}})
	return f.GitResetPathErr
}

func (f *Fake) GitCheckoutPath(_ context.Context, repoRoot, path string) error {
	f.record(Call{Method: "GitCheckoutPath", Strings: []string{repoRoot, path}})
	return f.GitCheckoutPathErr
}

func (f *Fake) GitPush(_ context.Context, repoRoot, branch string) error {
	f.record(Call{Method: "GitPush", Strings: []string{repoRoot, branch}})
	return f.GitPushErr
}

func (f *Fake) GitRevParse(_ context.Context, repoRoot, ref string) (string, error) {
	f.record(Call{Method: "GitRevParse", Strings: []string{repoRoot, ref}})
	return f.GitRevParseResult, f.GitRevParseErr
}

func (f *Fake) GhPRCreate(_ context.Context, spec PRSpec) (string, error) {
	f.record(Call{Method: "GhPRCreate", PR: spec})
	return f.GhPRURL, f.GhPRErr
}

func (f *Fake) GhPRChecks(_ context.Context, repoRoot string, prNumber int) (PRChecksResult, error) {
	f.record(Call{Method: "GhPRChecks", Strings: []string{repoRoot, fmt.Sprintf("%d", prNumber)}})
	if f.GhPRChecksFunc != nil {
		return f.GhPRChecksFunc(prNumber)
	}
	return f.GhPRChecksResult, f.GhPRChecksErr
}

func (f *Fake) GhPRMerge(_ context.Context, repoRoot string, prNumber int) error {
	f.record(Call{Method: "GhPRMerge", Strings: []string{repoRoot, fmt.Sprintf("%d", prNumber)}})
	return f.GhPRMergeErr
}

func (f *Fake) GhPRView(_ context.Context, repoRoot string, prNumber int) (string, error) {
	f.record(Call{Method: "GhPRView", Strings: []string{repoRoot, fmt.Sprintf("%d", prNumber)}})
	return f.GhPRViewResult, f.GhPRViewErr
}

func (f *Fake) GhPRState(_ context.Context, repoRoot string, prNumber int) (PRStateResult, error) {
	f.record(Call{Method: "GhPRState", Strings: []string{repoRoot, fmt.Sprintf("%d", prNumber)}})
	if f.GhPRStateFunc != nil {
		return f.GhPRStateFunc(prNumber)
	}
	return f.GhPRStateResult, f.GhPRStateErr
}

func (f *Fake) GhPRClose(_ context.Context, repoRoot string, prNumber int, comment string) error {
	f.record(Call{Method: "GhPRClose", Strings: []string{repoRoot, fmt.Sprintf("%d", prNumber), comment}})
	return f.GhPRCloseErr
}

func (f *Fake) GitDeleteRemoteBranch(_ context.Context, repoRoot, branch string) error {
	f.record(Call{Method: "GitDeleteRemoteBranch", Strings: []string{repoRoot, branch}})
	return f.GitDeleteRemoteBranchErr
}

func (f *Fake) GhIssueComment(_ context.Context, repoRoot string, issueNumber int, body string) error {
	f.record(Call{Method: "GhIssueComment", Strings: []string{repoRoot, fmt.Sprintf("%d", issueNumber), body}})
	return f.GhIssueCommentErr
}

func (f *Fake) DockerImageID(_ context.Context, image string) (string, time.Time, error) {
	f.record(Call{Method: "DockerImageID", Strings: []string{image}})
	return f.DockerImageIDResult, f.DockerImageIDCreated, f.DockerImageIDErr
}

func (f *Fake) OsascriptNotify(_ context.Context, title, body string) error {
	f.record(Call{Method: "OsascriptNotify", Strings: []string{title, body}})
	return f.OsascriptErr
}

func (f *Fake) RankFiles(_ context.Context, repoRoot string, maxInstructions int, excludeRecentHours float64, limit int) ([]FileRank, error) {
	f.record(Call{Method: "RankFiles", Strings: []string{repoRoot}})
	return f.RankFilesResult, f.RankFilesErr
}

func (f *Fake) Targets(_ context.Context, repoRoot string, source string) ([]TargetOwner, error) {
	f.record(Call{Method: "Targets", Strings: []string{repoRoot, source}})
	if f.TargetsErr != nil {
		return nil, f.TargetsErr
	}
	return f.TargetsResult[source], nil
}

var _ Runner = (*Fake)(nil)
var _ Runner = (*ExecRunner)(nil)
