#!/usr/bin/env python3
"""End-to-end proof for the PR #58/#59 aliases.ld convention's two guard
layers -- real subprocesses and a real git repo, no mocking (the opposite of
test_container_merge.py and test_name_decompiled.py, which are pure-unit).

Two things this repo needs to actually be true, together:

  1. The normal path -- `tools/name_decompiled.py apply` invoked exactly the
     way `tools/container_merge.py`'s `name_after_commit` invokes it (a real
     subprocess) -- must land a rename that leaves
     `disasm/linker_scripts/us/symbol_addrs_code.txt`'s address-keyed entry
     untouched and adds a matching `aliases.ld` alias, AND that same commit
     must pass `tools/check_alias_rename.py`'s gate.

  2. A direct hard-rename with no alias (`name_decompiled.py apply
     --hard-rename`, bypassing container_merge.py entirely -- the real
     incident this session) must be CAUGHT by that same gate.
"""
from __future__ import annotations

import json
import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import check_alias_rename as car  # noqa: E402
import container_merge  # noqa: E402

_GIT_ENV_VARS_TO_STRIP = (
    "GIT_DIR", "GIT_WORK_TREE", "GIT_INDEX_FILE", "GIT_COMMON_DIR",
    "GIT_OBJECT_DIRECTORY", "GIT_ALTERNATE_OBJECT_DIRECTORIES",
)


def _clean_env() -> dict:
    env = dict(os.environ)
    for var in _GIT_ENV_VARS_TO_STRIP:
        env.pop(var, None)
    return env


def _run_git(repo: Path, *args: str) -> str:
    result = subprocess.run(
        ["git", "-C", str(repo), *args],
        check=True, capture_output=True, text=True, env=_clean_env(),
    )
    return result.stdout


SYMTAB = "func_80002222 = 0x80002222; // type:func\n"
A_C = "void func_80002222(void) {\n    return;\n}\n"
NAMES_JSON = {"functions": {"func_80002222": ["RealName", "evidence"]}}


class _RepoFixture:
    """A real git repo with a decompiled-but-unnamed function
    (func_80002222), a real copy of tools/name_decompiled.py (subprocess
    calls need it on disk under <repo>/tools/), and a baseline commit."""

    def __init__(self, repo: Path) -> None:
        self.repo = repo
        (repo / "disasm" / "src").mkdir(parents=True)
        (repo / "disasm" / "include").mkdir(parents=True)
        (repo / "disasm" / "linker_scripts" / "us").mkdir(parents=True)
        (repo / "tools").mkdir(parents=True)

        (repo / "disasm" / "src" / "a.c").write_text(A_C, encoding="utf-8")
        (repo / "disasm" / "linker_scripts" / "us" / "symbol_addrs_code.txt").write_text(
            SYMTAB, encoding="utf-8"
        )
        (repo / "disasm" / "linker_scripts" / "us" / "aliases.ld").write_text(
            "", encoding="utf-8"
        )
        (repo / "tools" / "gs_names.json").write_text(
            json.dumps(NAMES_JSON), encoding="utf-8"
        )
        shutil.copy(TOOLS / "name_decompiled.py", repo / "tools" / "name_decompiled.py")

        _run_git(repo, "init", "-q", "-b", "main")
        _run_git(repo, "config", "user.email", "test@example.com")
        _run_git(repo, "config", "user.name", "Test")
        _run_git(repo, "add", "-A")
        _run_git(repo, "commit", "-q", "-m", "baseline")

    @property
    def symtab_path(self) -> Path:
        return self.repo / "disasm" / "linker_scripts" / "us" / "symbol_addrs_code.txt"

    @property
    def aliases_path(self) -> Path:
        return self.repo / "disasm" / "linker_scripts" / "us" / "aliases.ld"

    @property
    def a_c_path(self) -> Path:
        return self.repo / "disasm" / "src" / "a.c"


class _TempRepoTestCase(unittest.TestCase):
    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.repo = Path(self._tmp.name)
        self.fixture = _RepoFixture(self.repo)

    def tearDown(self) -> None:
        self._tmp.cleanup()


class NormalPathIsSafeAndPassesTheGateTests(_TempRepoTestCase):
    """The path a container match actually takes: container_merge.py's
    name_after_commit, a REAL subprocess call to `name_decompiled.py apply`
    (no --hard-rename -- container_merge.py never passes it)."""

    def test_name_after_commit_leaves_symtab_untouched_and_adds_alias(self) -> None:
        new_name, detail = container_merge.name_after_commit(
            "func_80002222", repo_root=self.repo
        )
        self.assertEqual(new_name, "RealName", detail)
        self.assertIn("func_80002222 = 0x80002222", self.fixture.symtab_path.read_text())
        self.assertIn("func_80002222 = RealName;", self.fixture.aliases_path.read_text())
        self.assertIn("RealName(void)", self.fixture.a_c_path.read_text())
        self.assertNotIn("func_80002222", self.fixture.a_c_path.read_text())

    def test_resulting_staged_commit_passes_check_alias_rename(self) -> None:
        # This is exactly what container_merge.py's merge() does after
        # name_after_commit succeeds: stage disasm/src, disasm/include, and
        # aliases.ld, then commit. The staged diff must pass the same gate
        # that would refuse a bare hard rename.
        new_name, _detail = container_merge.name_after_commit(
            "func_80002222", repo_root=self.repo
        )
        self.assertEqual(new_name, "RealName")
        _run_git(self.repo, "add", "-A")
        missing = car.check_diff(self.repo, staged=True)
        self.assertEqual(missing, [])
        rc = car.main(["--staged", "--repo-root", str(self.repo)])
        self.assertEqual(rc, 0)

    def test_container_merges_own_revert_dance_is_a_harmless_no_op(self) -> None:
        # container_merge.merge()'s own post-processing (revert every
        # disasm/linker_scripts change except aliases.ld, then
        # append_name_alias) runs on top of name_after_commit unconditionally.
        # With name_decompiled.py's new safe default, that dance now finds
        # nothing to revert and a line already present to (not) duplicate --
        # verifying it stays a no-op, not a source of drift or duplication.
        new_name, _detail = container_merge.name_after_commit(
            "func_80002222", repo_root=self.repo
        )
        self.assertEqual(new_name, "RealName")

        linker_changed = container_merge.git_status_paths(
            self.repo, prefixes=("disasm/linker_scripts",)
        )
        self.assertEqual(linker_changed, [container_merge._ALIASES_LD_PATH])

        to_revert = [p for p in linker_changed if p != container_merge._ALIASES_LD_PATH]
        self.assertEqual(to_revert, [])

        appended = container_merge.append_name_alias(
            "func_80002222", new_name, repo_root=self.repo
        )
        self.assertFalse(appended)  # already there -- exact-line dedup
        text = self.fixture.aliases_path.read_text()
        self.assertEqual(text.count("func_80002222 = RealName;"), 1)


class DirectHardRenameIsCaughtTests(_TempRepoTestCase):
    """The actual incident this session: bypass container_merge.py entirely
    and call `name_decompiled.py apply --hard-rename` directly."""

    def _run_hard_rename_apply(self) -> subprocess.CompletedProcess:
        return subprocess.run(
            [
                sys.executable, str(self.repo / "tools" / "name_decompiled.py"),
                "apply", "--only", "func_80002222", "--hard-rename",
                "--repo-root", str(self.repo),
            ],
            cwd=self.repo, capture_output=True, text=True, env=_clean_env(),
        )

    def test_hard_rename_actually_rewrites_symtab_with_no_alias(self) -> None:
        proc = self._run_hard_rename_apply()
        self.assertEqual(proc.returncode, 0, proc.stderr)
        self.assertIn("RealName = 0x80002222", self.fixture.symtab_path.read_text())
        self.assertNotIn("func_80002222", self.fixture.aliases_path.read_text())

    def test_staged_hard_rename_is_caught_by_check_alias_rename(self) -> None:
        proc = self._run_hard_rename_apply()
        self.assertEqual(proc.returncode, 0, proc.stderr)
        _run_git(self.repo, "add", "-A")

        missing = car.check_diff(self.repo, staged=True)
        self.assertEqual(missing, [("func_80002222", "RealName", "0x80002222")])

        rc = car.main(["--staged", "--repo-root", str(self.repo)])
        self.assertEqual(rc, 1)

    def test_gate_error_message_points_at_the_correct_tools(self) -> None:
        proc = self._run_hard_rename_apply()
        self.assertEqual(proc.returncode, 0, proc.stderr)
        _run_git(self.repo, "add", "-A")

        check_proc = subprocess.run(
            [sys.executable, str(TOOLS / "check_alias_rename.py"),
             "--staged", "--repo-root", str(self.repo)],
            cwd=self.repo, capture_output=True, text=True, env=_clean_env(),
        )
        self.assertEqual(check_proc.returncode, 1)
        self.assertIn("func_80002222", check_proc.stderr)
        self.assertIn("RealName", check_proc.stderr)
        self.assertIn("container_merge.py", check_proc.stderr)
        self.assertIn("aliases.ld", check_proc.stderr)

    def test_adding_the_alias_by_hand_satisfies_the_gate(self) -> None:
        # The escape hatch used responsibly: --hard-rename plus a
        # hand-added alias in the same commit is accepted.
        proc = self._run_hard_rename_apply()
        self.assertEqual(proc.returncode, 0, proc.stderr)
        with self.fixture.aliases_path.open("a", encoding="utf-8") as fh:
            fh.write("func_80002222 = RealName;\n")
        _run_git(self.repo, "add", "-A")
        rc = car.main(["--staged", "--repo-root", str(self.repo)])
        self.assertEqual(rc, 0)


if __name__ == "__main__":
    unittest.main()
