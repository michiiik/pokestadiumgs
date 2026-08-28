#!/usr/bin/env python3
"""Tests for tools/file_claims.py and tools/check_file_claims.py."""

from __future__ import annotations

import json
import os
import shutil
import subprocess
import sys
import tempfile
import time
import unittest
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import file_claims  # noqa: E402
import check_file_claims  # noqa: E402
import try_pragma_compare as runner  # noqa: E402

# See test_update_coverage.py's _GitFixture: git hook subprocess env vars
# (GIT_DIR/GIT_INDEX_FILE/...) point at the *enclosing* repo when this test
# file itself runs from a pre-commit hook's `tools/run_tests.sh`. Left
# inherited, they'd redirect the `git init`/`add`/`commit` calls below off
# the throwaway tempdir fixture and onto the enclosing repo instead.
_GIT_ENV_VARS_TO_STRIP = (
    "GIT_DIR", "GIT_WORK_TREE", "GIT_INDEX_FILE", "GIT_COMMON_DIR",
    "GIT_OBJECT_DIRECTORY", "GIT_ALTERNATE_OBJECT_DIRECTORIES",
)


def _clean_git_env(extra: dict | None = None) -> dict:
    env = dict(os.environ)
    for var in _GIT_ENV_VARS_TO_STRIP:
        env.pop(var, None)
    if extra:
        env.update(extra)
    return env


def _run_git(repo: Path, *args: str, env: dict | None = None) -> str:
    result = subprocess.run(
        ["git", "-C", str(repo), *args],
        check=True,
        capture_output=True,
        text=True,
        env=_clean_git_env(env),
    )
    return result.stdout


def _dead_pid() -> int:
    """A pid guaranteed not to be running right now."""
    proc = subprocess.Popen(
        [sys.executable, "-c", "pass"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL
    )
    proc.wait()
    return proc.pid


class OwnerIdentityTests(unittest.TestCase):
    def test_default_owner_shape(self) -> None:
        with mock.patch.dict(os.environ, {}, clear=False):
            os.environ.pop("CLAIMS_OWNER", None)
            os.environ["CLAUDE_JOB_DIR"] = "/tmp/job-42"
            owner = file_claims.default_owner()
        self.assertRegex(owner, rf"^{os.getpid()}@.+:/tmp/job-42$")

    def test_session_tag_falls_back_to_ppid(self) -> None:
        with mock.patch.dict(os.environ, {}, clear=False):
            os.environ.pop("CLAUDE_JOB_DIR", None)
            tag = file_claims._session_tag()
        self.assertEqual(tag, str(os.getppid()))

    def test_current_owner_respects_claims_owner_override(self) -> None:
        with mock.patch.dict(os.environ, {"CLAIMS_OWNER": "coordinator-A"}):
            self.assertEqual(file_claims.current_owner(), "coordinator-A")

    def test_owner_session_extracts_host_and_session_for_structured_owner(self) -> None:
        self.assertEqual(file_claims.owner_session("123@myhost:/tmp/job-1"), "myhost:/tmp/job-1")

    def test_owner_session_returns_freeform_string_unchanged(self) -> None:
        self.assertEqual(file_claims.owner_session("coordinator-A"), "coordinator-A")

    def test_same_session_matches_structured_owners_with_different_pids(self) -> None:
        self.assertTrue(file_claims.same_session("111@host:/tmp/job-1", "222@host:/tmp/job-1"))

    def test_same_session_rejects_different_session_tags(self) -> None:
        self.assertFalse(file_claims.same_session("111@host:/tmp/job-1", "111@host:/tmp/job-2"))

    def test_registry_key_normalizes_absolute_path(self) -> None:
        absolute = file_claims.REPO_ROOT / "disasm" / "src" / "AAA.c"
        self.assertEqual(file_claims.registry_key(absolute), "disasm/src/AAA.c")

    def test_registry_key_leaves_relative_path_alone(self) -> None:
        self.assertEqual(file_claims.registry_key("disasm/src/AAA.c"), "disasm/src/AAA.c")


class IsLiveTests(unittest.TestCase):
    def test_expired_entry_is_not_live_even_with_running_pid(self) -> None:
        entry = {
            "owner": f"{os.getpid()}@somehost:sess",
            "expires_at": time.time() - 10,
        }
        self.assertFalse(file_claims.is_live(entry))

    def test_running_pid_same_host_is_live(self) -> None:
        import socket
        entry = {
            "owner": f"{os.getpid()}@{socket.gethostname()}:sess",
            "expires_at": time.time() + 3600,
        }
        self.assertTrue(file_claims.is_live(entry))

    def test_dead_pid_same_host_is_not_live(self) -> None:
        import socket
        entry = {
            "owner": f"{_dead_pid()}@{socket.gethostname()}:sess",
            "expires_at": time.time() + 3600,
        }
        self.assertFalse(file_claims.is_live(entry))

    def test_dead_pid_different_host_trusts_ttl(self) -> None:
        entry = {
            "owner": "99999999@some-other-host:sess",
            "expires_at": time.time() + 3600,
        }
        self.assertTrue(file_claims.is_live(entry))

    def test_freeform_owner_with_no_pid_trusts_ttl(self) -> None:
        entry = {"owner": "coordinator-A", "expires_at": time.time() + 3600}
        self.assertTrue(file_claims.is_live(entry))


class RegistryTests(unittest.TestCase):
    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.registry = Path(self._tmp.name) / "claims.json"

    def tearDown(self) -> None:
        self._tmp.cleanup()

    def test_claim_new_path_succeeds_and_is_visible(self) -> None:
        self.assertTrue(file_claims.claim("disasm/src/AAA.c", owner="A", registry=self.registry))
        entry = file_claims.holder("disasm/src/AAA.c", registry=self.registry)
        self.assertEqual(entry["owner"], "A")

    def test_missing_registry_file_reads_back_empty(self) -> None:
        self.assertIsNone(file_claims.holder("disasm/src/AAA.c", registry=self.registry))
        self.assertEqual(file_claims.list_claims(registry=self.registry), {})

    def test_claim_refuses_different_live_owner(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="A", registry=self.registry)
        self.assertFalse(file_claims.claim("disasm/src/AAA.c", owner="B", registry=self.registry))
        self.assertEqual(file_claims.holder("disasm/src/AAA.c", registry=self.registry)["owner"], "A")

    def test_claim_refreshes_same_owner_and_preserves_claimed_at(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="A", ttl=1000, registry=self.registry)
        first = file_claims.holder("disasm/src/AAA.c", registry=self.registry)
        self.assertTrue(file_claims.claim("disasm/src/AAA.c", owner="A", ttl=2000, registry=self.registry))
        second = file_claims.holder("disasm/src/AAA.c", registry=self.registry)
        self.assertEqual(first["claimed_at"], second["claimed_at"])
        self.assertGreater(second["expires_at"], first["expires_at"])

    def test_claim_succeeds_once_previous_owner_expired(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="A", ttl=-1, registry=self.registry)
        self.assertTrue(file_claims.claim("disasm/src/AAA.c", owner="B", registry=self.registry))
        self.assertEqual(file_claims.holder("disasm/src/AAA.c", registry=self.registry)["owner"], "B")

    def test_touch_requires_same_owner_and_extends_expiry(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="A", ttl=100, registry=self.registry)
        before = file_claims.holder("disasm/src/AAA.c", registry=self.registry)["expires_at"]
        self.assertFalse(file_claims.touch("disasm/src/AAA.c", owner="B", registry=self.registry))
        self.assertTrue(file_claims.touch("disasm/src/AAA.c", owner="A", ttl=5000, registry=self.registry))
        after = file_claims.holder("disasm/src/AAA.c", registry=self.registry)["expires_at"]
        self.assertGreater(after, before)

    def test_touch_missing_path_returns_false(self) -> None:
        self.assertFalse(file_claims.touch("disasm/src/AAA.c", owner="A", registry=self.registry))

    def test_release_requires_matching_owner_unless_forced(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="A", registry=self.registry)
        self.assertFalse(file_claims.release("disasm/src/AAA.c", owner="B", registry=self.registry))
        self.assertTrue(file_claims.release("disasm/src/AAA.c", owner="A", registry=self.registry))
        self.assertIsNone(file_claims.holder("disasm/src/AAA.c", registry=self.registry))

    def test_release_force_ignores_owner(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="A", registry=self.registry)
        self.assertTrue(file_claims.release("disasm/src/AAA.c", owner="B", force=True, registry=self.registry))

    def test_release_missing_path_returns_false(self) -> None:
        self.assertFalse(file_claims.release("disasm/src/AAA.c", owner="A", registry=self.registry))

    def test_list_claims_returns_every_entry(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="A", registry=self.registry)
        file_claims.claim("disasm/src/BBB.c", owner="B", registry=self.registry)
        data = file_claims.list_claims(registry=self.registry)
        self.assertEqual(set(data), {"disasm/src/AAA.c", "disasm/src/BBB.c"})

    def test_expire_removes_only_dead_entries(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="A", ttl=-1, registry=self.registry)
        file_claims.claim("disasm/src/BBB.c", owner="B", ttl=1000, registry=self.registry)
        removed = file_claims.expire(registry=self.registry)
        self.assertEqual(removed, ["disasm/src/AAA.c"])
        self.assertIsNone(file_claims.holder("disasm/src/AAA.c", registry=self.registry))
        self.assertIsNotNone(file_claims.holder("disasm/src/BBB.c", registry=self.registry))

    def test_corrupt_registry_file_reads_back_empty_instead_of_raising(self) -> None:
        self.registry.parent.mkdir(parents=True, exist_ok=True)
        self.registry.write_text("{not json")
        self.assertEqual(file_claims.list_claims(registry=self.registry), {})
        # A write still succeeds afterwards (corrupt file is simply replaced).
        self.assertTrue(file_claims.claim("disasm/src/AAA.c", owner="A", registry=self.registry))

    def test_writes_are_atomic_temp_file_replace(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="A", registry=self.registry)
        leftovers = [p for p in self.registry.parent.iterdir() if p.name.startswith(".claims-")]
        self.assertEqual(leftovers, [])
        data = json.loads(self.registry.read_text())
        self.assertIn("disasm/src/AAA.c", data)


class RegistryPathResolutionTests(unittest.TestCase):
    def test_default_registry_path_is_under_probe_stats(self) -> None:
        with mock.patch.dict(os.environ, {}, clear=False):
            os.environ.pop("PRAGMA_CLAIMS_REGISTRY", None)
            self.assertEqual(file_claims.registry_path(), file_claims.DEFAULT_REGISTRY_PATH)
        parts = file_claims.DEFAULT_REGISTRY_PATH.parts
        self.assertIn("probe-stats", parts)

    def test_env_override_wins(self) -> None:
        with mock.patch.dict(os.environ, {"PRAGMA_CLAIMS_REGISTRY": "/tmp/custom-claims.json"}):
            self.assertEqual(file_claims.registry_path(), Path("/tmp/custom-claims.json"))


class RunnerClaimIntegrationTests(unittest.TestCase):
    """_claim_or_refuse: the single guarded call at the install boundary."""

    def setUp(self) -> None:
        runner._CLAIMED_SOURCE_PATHS.clear()
        self.addCleanup(runner._CLAIMED_SOURCE_PATHS.clear)

    def test_first_call_claims_second_call_touches(self) -> None:
        with mock.patch.object(file_claims, "claim", return_value=True) as claim_mock, \
             mock.patch.object(file_claims, "touch", return_value=True) as touch_mock:
            self.assertIsNone(runner._claim_or_refuse(Path("disasm/src/AAA.c")))
            self.assertIsNone(runner._claim_or_refuse(Path("disasm/src/AAA.c")))
        claim_mock.assert_called_once()
        touch_mock.assert_called_once()

    def test_refusal_names_the_holder_without_writing_anything(self) -> None:
        with mock.patch.object(file_claims, "claim", return_value=False), \
             mock.patch.object(file_claims, "holder", return_value={"owner": "other@host:sess"}):
            diagnostic = runner._claim_or_refuse(Path("disasm/src/AAA.c"))
        self.assertIsNotNone(diagnostic)
        self.assertIn("other@host:sess", diagnostic)

    def test_gate_false_batch_never_claims(self) -> None:
        # A probe-only batch returns from _try_candidates_detailed_unlocked
        # before _claim_or_refuse is ever reached; simplest regression
        # guard is that the batch_status the caller sees is "probe_only",
        # never "file_claimed_by_other", when gate=False.
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_1.s")\n')
            with mock.patch.object(runner, "probe_candidates", return_value=[
                {"function": "func_1", "status": "probe_rejected"}
            ]), mock.patch.object(file_claims, "claim") as claim_mock:
                result = runner._try_candidates_detailed_unlocked(
                    source, [("func_1", "int func_1(void) { return 0; }")], gate=False,
                )
        self.assertEqual(result["batch_status"], "probe_only")
        claim_mock.assert_not_called()

    def test_batch_refused_by_a_foreign_claim_never_reaches_the_gate(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_1.s")\n')
            with mock.patch.object(runner, "probe_candidates", return_value=[
                {"function": "func_1", "status": "probe_match", "link_verified": False}
            ]), mock.patch.object(file_claims, "claim", return_value=False), \
                 mock.patch.object(file_claims, "holder", return_value={"owner": "other@host:sess"}), \
                 mock.patch.object(runner, "compare_current_tree") as gate_mock:
                result = runner._try_candidates_detailed_unlocked(
                    source, [("func_1", "int func_1(void) { return 0; }")], gate=True,
                )
        self.assertEqual(result["batch_status"], "file_claimed_by_other")
        self.assertIn("other@host:sess", result["claim_diagnostic"])
        gate_mock.assert_not_called()


class FreeFilesTests(unittest.TestCase):
    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.repo = Path(self._tmp.name)
        self.registry = self.repo / "claims.json"
        src = self.repo / "disasm" / "src"
        (src / "fragments" / "1").mkdir(parents=True)
        (src / "AAA.c").write_text(_pragma("func_1") + _pragma("func_2"))
        (src / "BBB.c").write_text(_pragma("func_3"))
        (src / "fragments" / "1" / "fragment1_code.c").write_text(_pragma("func_9"))

        _run_git(self.repo, "init", "-q", "-b", "main")
        _run_git(self.repo, "config", "user.email", "test@example.com")
        _run_git(self.repo, "config", "user.name", "Test")
        _run_git(self.repo, "add", "-A")
        _run_git(self.repo, "commit", "-q", "-m", "baseline")

    def tearDown(self) -> None:
        self._tmp.cleanup()

    def _free(self, *, patch_recent: bool = True, **kwargs):
        # git's --since has only second-level granularity, so "0 hours ago"
        # unreliably still matches a commit made microseconds earlier (see
        # test_recently_touched_file_excluded for the real git-log
        # integration, which uses an unambiguously large window instead).
        # Every other test here is about fragment/claim filtering, not
        # recency, so it stubs _recently_touched to an empty set.
        if patch_recent:
            with mock.patch.object(file_claims, "_recently_touched", return_value=set()):
                return file_claims.free_files(
                    registry=self.registry,
                    repo_root=self.repo,
                    source_root=self.repo / "disasm" / "src",
                    **kwargs,
                )
        return file_claims.free_files(
            registry=self.registry,
            repo_root=self.repo,
            source_root=self.repo / "disasm" / "src",
            **kwargs,
        )

    def test_lists_text_segment_files_with_remaining_owners_by_default(self) -> None:
        rows = self._free()
        sources = {row["source"] for row in rows}
        self.assertIn("disasm/src/AAA.c", sources)
        self.assertIn("disasm/src/BBB.c", sources)
        self.assertNotIn("disasm/src/fragments/1/fragment1_code.c", sources)

    def test_fragments_flag_lists_only_fragment_files(self) -> None:
        rows = self._free(fragments=True)
        sources = {row["source"] for row in rows}
        self.assertEqual(sources, {"disasm/src/fragments/1/fragment1_code.c"})

    def test_recently_touched_file_excluded(self) -> None:
        # The baseline commit just happened, so a large exclude-recent
        # window (hours) should exclude every file touched by it. This is
        # the one test that exercises the real `git log --since` call.
        rows = self._free(patch_recent=False, exclude_recent_hours=24)
        self.assertEqual(rows, [])

    def test_live_claim_excludes_a_file_even_when_not_recently_committed(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="A", registry=self.registry)
        rows = self._free()
        sources = {row["source"] for row in rows}
        self.assertNotIn("disasm/src/AAA.c", sources)
        self.assertIn("disasm/src/BBB.c", sources)

    def test_expired_claim_does_not_exclude_a_file(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="A", ttl=-1, registry=self.registry)
        rows = self._free()
        sources = {row["source"] for row in rows}
        self.assertIn("disasm/src/AAA.c", sources)

    def test_rows_are_sorted_by_remaining_owners_descending(self) -> None:
        rows = self._free()
        counts = [row["remaining_owners"] for row in rows]
        self.assertEqual(counts, sorted(counts, reverse=True))


def _pragma(owner: str) -> str:
    return f'#pragma GLOBAL_ASM("asm/us/nonmatchings/x/{owner}.s")\n'


class _ClaimsGitFixture:
    """A tiny git repo with a disasm/src file and a staged (index) edit to it."""

    def __init__(self, repo: Path) -> None:
        self.repo = repo
        src = repo / "disasm" / "src"
        src.mkdir(parents=True)
        (src / "AAA.c").write_text("int func_1(void) { return 0; }\n")
        (src / "BBB.c").write_text("int func_2(void) { return 0; }\n")

        _run_git(repo, "init", "-q", "-b", "main")
        _run_git(repo, "config", "user.email", "test@example.com")
        _run_git(repo, "config", "user.name", "Test")
        _run_git(repo, "add", "-A")
        _run_git(repo, "commit", "-q", "-m", "baseline")

        # Stage an edit to both files -- what an agent's runner-installed,
        # not-yet-committed change looks like.
        (src / "AAA.c").write_text("int func_1(void) { return 1; }\n")
        (src / "BBB.c").write_text("int func_2(void) { return 1; }\n")
        _run_git(repo, "add", "-A")


class CheckFileClaimsTests(unittest.TestCase):
    def setUp(self) -> None:
        env_patch = mock.patch.dict(os.environ, {}, clear=False)
        env_patch.start()
        self.addCleanup(env_patch.stop)
        for var in _GIT_ENV_VARS_TO_STRIP:
            os.environ.pop(var, None)

        self._tmp = tempfile.TemporaryDirectory()
        self.repo = Path(self._tmp.name)
        self.registry = self.repo / "claims.json"
        self.fixture = _ClaimsGitFixture(self.repo)

    def tearDown(self) -> None:
        self._tmp.cleanup()

    def test_no_claims_on_file_passes(self) -> None:
        foreign, multi_owner, live = check_file_claims.find_violations(
            ["disasm/src/AAA.c", "disasm/src/BBB.c"], committer="me", registry=self.registry,
        )
        self.assertEqual(foreign, {})
        self.assertFalse(multi_owner)

    def test_claim_by_committers_own_session_passes(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="42@host:/tmp/job-mine", registry=self.registry)
        foreign, multi_owner, live = check_file_claims.find_violations(
            ["disasm/src/AAA.c"], committer="99@host:/tmp/job-mine", registry=self.registry,
        )
        self.assertEqual(foreign, {})
        self.assertFalse(multi_owner)

    def test_claim_by_a_foreign_session_fails(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="42@host:/tmp/job-other", registry=self.registry)
        foreign, multi_owner, live = check_file_claims.find_violations(
            ["disasm/src/AAA.c"], committer="99@host:/tmp/job-mine", registry=self.registry,
        )
        self.assertIn("disasm/src/AAA.c", foreign)

    def test_expired_foreign_claim_does_not_fail(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="42@host:/tmp/job-other", ttl=-1, registry=self.registry)
        foreign, multi_owner, live = check_file_claims.find_violations(
            ["disasm/src/AAA.c"], committer="99@host:/tmp/job-mine", registry=self.registry,
        )
        self.assertEqual(foreign, {})
        self.assertFalse(multi_owner)

    def test_two_different_foreign_owners_staged_together_is_multi_owner(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="1@host:/tmp/job-x", registry=self.registry)
        file_claims.claim("disasm/src/BBB.c", owner="2@host:/tmp/job-y", registry=self.registry)
        foreign, multi_owner, live = check_file_claims.find_violations(
            ["disasm/src/AAA.c", "disasm/src/BBB.c"], committer="99@host:/tmp/job-mine", registry=self.registry,
        )
        self.assertTrue(multi_owner)
        self.assertEqual(set(live), {"disasm/src/AAA.c", "disasm/src/BBB.c"})

    def test_hook_script_fails_commit_on_foreign_claim(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="42@host:/tmp/job-other", registry=self.registry)
        env = _clean_git_env({
            "PRAGMA_CLAIMS_REGISTRY": str(self.registry),
            "CLAIMS_OWNER": "99@host:/tmp/job-mine",
        })
        result = subprocess.run(
            [sys.executable, str(TOOLS / "check_file_claims.py"), "--staged", "--repo-root", str(self.repo)],
            cwd=self.repo, env=env, capture_output=True, text=True,
        )
        self.assertEqual(result.returncode, 1)
        self.assertIn("disasm/src/AAA.c", result.stderr)
        self.assertIn("claimed by 42@host:/tmp/job-other", result.stderr)
        self.assertIn("commit by explicit path; this file is being edited by another session", result.stderr)

    def test_hook_script_passes_when_only_committers_own_claim_is_staged(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="99@host:/tmp/job-mine", registry=self.registry)
        env = _clean_git_env({
            "PRAGMA_CLAIMS_REGISTRY": str(self.registry),
            "CLAIMS_OWNER": "1@host:/tmp/job-mine",
        })
        result = subprocess.run(
            [sys.executable, str(TOOLS / "check_file_claims.py"), "--staged", "--repo-root", str(self.repo)],
            cwd=self.repo, env=env, capture_output=True, text=True,
        )
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_pragma_claims_skip_bypasses_with_warning(self) -> None:
        file_claims.claim("disasm/src/AAA.c", owner="42@host:/tmp/job-other", registry=self.registry)
        env = _clean_git_env({
            "PRAGMA_CLAIMS_REGISTRY": str(self.registry),
            "CLAIMS_OWNER": "99@host:/tmp/job-mine",
            "PRAGMA_CLAIMS_SKIP": "1",
        })
        result = subprocess.run(
            [sys.executable, str(TOOLS / "check_file_claims.py"), "--staged", "--repo-root", str(self.repo)],
            cwd=self.repo, env=env, capture_output=True, text=True,
        )
        self.assertEqual(result.returncode, 0)
        self.assertIn("PRAGMA_CLAIMS_SKIP=1", result.stderr)

    def test_missing_registry_file_passes(self) -> None:
        env = _clean_git_env({
            "PRAGMA_CLAIMS_REGISTRY": str(self.repo / "does-not-exist.json"),
            "CLAIMS_OWNER": "99@host:/tmp/job-mine",
        })
        result = subprocess.run(
            [sys.executable, str(TOOLS / "check_file_claims.py"), "--staged", "--repo-root", str(self.repo)],
            cwd=self.repo, env=env, capture_output=True, text=True,
        )
        self.assertEqual(result.returncode, 0, result.stderr)

    def _copy_hook_deps(self) -> Path:
        # .githooks/pre-commit.d/12-claims.sh resolves its own repo root via
        # `git rev-parse --show-toplevel` (this fixture repo, once it is the
        # cwd) and expects a sibling tools/ directory there -- copy just the
        # two files it actually needs rather than the whole real tools/ tree.
        tools_dir = self.repo / "tools"
        tools_dir.mkdir(exist_ok=True)
        for name in ("check_file_claims.py", "file_claims.py"):
            shutil.copy(TOOLS / name, tools_dir / name)
        return file_claims.REPO_ROOT / ".githooks" / "pre-commit.d" / "12-claims.sh"

    def test_hook_script_wrapper_blocks_on_a_foreign_claim(self) -> None:
        hook = self._copy_hook_deps()
        file_claims.claim("disasm/src/AAA.c", owner="42@host:/tmp/job-other", registry=self.registry)
        env = _clean_git_env({
            "PRAGMA_CLAIMS_REGISTRY": str(self.registry),
            "CLAIMS_OWNER": "99@host:/tmp/job-mine",
        })
        result = subprocess.run([str(hook)], cwd=self.repo, env=env, capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("commit by explicit path; this file is being edited by another session", result.stderr)

    def test_hook_script_wrapper_passes_with_no_foreign_claim(self) -> None:
        hook = self._copy_hook_deps()
        env = _clean_git_env({
            "PRAGMA_CLAIMS_REGISTRY": str(self.registry),
            "CLAIMS_OWNER": "99@host:/tmp/job-mine",
        })
        result = subprocess.run([str(hook)], cwd=self.repo, env=env, capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == "__main__":
    unittest.main()
