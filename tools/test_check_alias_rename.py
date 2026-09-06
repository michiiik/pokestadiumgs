#!/usr/bin/env python3
"""Tests for tools/check_alias_rename.py.

Run with:
    python3 -m unittest discover -s tools -p 'test_*.py'
"""
from __future__ import annotations

import os
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import check_alias_rename as car  # noqa: E402

# See test_update_coverage.py's _GitFixture docstring: git hook subprocess
# env vars (GIT_DIR/GIT_INDEX_FILE/...) point at the *enclosing* repo when
# this test file itself runs from a pre-commit hook's `tools/run_tests.sh`.
# Left inherited, they'd redirect the `git init`/`add`/`commit` calls below
# off the throwaway tempdir fixture and onto the enclosing repo instead.
_GIT_ENV_VARS_TO_STRIP = (
    "GIT_DIR", "GIT_WORK_TREE", "GIT_INDEX_FILE", "GIT_COMMON_DIR",
    "GIT_OBJECT_DIRECTORY", "GIT_ALTERNATE_OBJECT_DIRECTORIES",
)

SYMTAB_REL = car.SYMTAB_PATH
ALIASES_REL = car.ALIASES_LD_PATH

BASE_SYMTAB = """\
func_80001000 = 0x80001000; // type:func
func_80002000 = 0x80002000; // type:func
AlreadyNamed = 0x80003000; // type:func
"""

BASE_ALIASES = """\
SomeExisting = func_80099999;
"""


def _run_git(repo: Path, *args: str) -> str:
    env = dict(os.environ)
    for var in _GIT_ENV_VARS_TO_STRIP:
        env.pop(var, None)
    result = subprocess.run(
        ["git", "-C", str(repo), *args],
        check=True, capture_output=True, text=True, env=env,
    )
    return result.stdout


class _RepoFixture:
    """A tiny git repo with a committed symtab + aliases.ld baseline, ready
    for a test to stage a rename-shaped change on top."""

    def __init__(self, repo: Path) -> None:
        self.repo = repo
        linker_us = repo / "disasm" / "linker_scripts" / "us"
        linker_us.mkdir(parents=True)
        (linker_us / "symbol_addrs_code.txt").write_text(BASE_SYMTAB, encoding="utf-8")
        (linker_us / "aliases.ld").write_text(BASE_ALIASES, encoding="utf-8")

        _run_git(repo, "init", "-q", "-b", "main")
        _run_git(repo, "config", "user.email", "test@example.com")
        _run_git(repo, "config", "user.name", "Test")
        _run_git(repo, "add", "-A")
        _run_git(repo, "commit", "-q", "-m", "baseline")

        self.symtab_path = linker_us / "symbol_addrs_code.txt"
        self.aliases_path = linker_us / "aliases.ld"

    def write(self, symtab: str | None = None, aliases: str | None = None) -> None:
        if symtab is not None:
            self.symtab_path.write_text(symtab, encoding="utf-8")
        if aliases is not None:
            self.aliases_path.write_text(aliases, encoding="utf-8")

    def stage(self) -> None:
        _run_git(self.repo, "add", "-A")


class _GitEnvIsolatedTestCase(unittest.TestCase):
    def setUp(self) -> None:
        env_patch = mock.patch.dict(os.environ, {}, clear=False)
        env_patch.start()
        self.addCleanup(env_patch.stop)
        for var in _GIT_ENV_VARS_TO_STRIP:
            os.environ.pop(var, None)

        self._tmp = tempfile.TemporaryDirectory()
        self.repo = Path(self._tmp.name)
        self.fixture = _RepoFixture(self.repo)

    def tearDown(self) -> None:
        self._tmp.cleanup()


class RenamedSymtabEntriesTests(unittest.TestCase):
    """Pure diff-text parsing, no git involved."""

    def test_rename_at_same_address_detected(self) -> None:
        diff = (
            "-func_80001000 = 0x80001000; // type:func\n"
            "+Real_Name = 0x80001000; // type:func\n"
        )
        self.assertEqual(
            car.renamed_symtab_entries(diff), [("func_80001000", "Real_Name", "0x80001000")]
        )

    def test_newly_added_entry_is_not_a_rename(self) -> None:
        diff = "+func_80005000 = 0x80005000; // type:func\n"
        self.assertEqual(car.renamed_symtab_entries(diff), [])

    def test_address_value_change_for_same_name_is_not_a_rename(self) -> None:
        diff = (
            "-func_80001000 = 0x80001000; // type:func\n"
            "+func_80001000 = 0x80001004; // type:func\n"
        )
        self.assertEqual(car.renamed_symtab_entries(diff), [])

    def test_diff_metadata_lines_ignored(self) -> None:
        diff = (
            "diff --git a/x b/x\n"
            "index 111..222 100644\n"
            "--- a/x\n"
            "+++ b/x\n"
            "@@ -1 +1 @@\n"
            "-func_80001000 = 0x80001000; // type:func\n"
            "+Real_Name = 0x80001000; // type:func\n"
        )
        self.assertEqual(
            car.renamed_symtab_entries(diff), [("func_80001000", "Real_Name", "0x80001000")]
        )


class AddedAliasPairsTests(unittest.TestCase):
    def test_added_bare_alias_line_captured(self) -> None:
        diff = "+func_80001000 = Real_Name;\n"
        self.assertEqual(car.added_alias_pairs(diff), {("func_80001000", "Real_Name")})

    def test_removed_alias_line_not_captured(self) -> None:
        diff = "-func_80001000 = Real_Name;\n"
        self.assertEqual(car.added_alias_pairs(diff), set())

    def test_non_bare_expression_not_captured(self) -> None:
        diff = "+some_symbol = func_80001000 + 4;\n"
        self.assertEqual(car.added_alias_pairs(diff), set())


class CheckDiffTests(_GitEnvIsolatedTestCase):
    """End-to-end against a real git repo's staged diff."""

    def test_hard_rename_with_no_alias_is_caught(self) -> None:
        # Exactly the dangerous shape this guard exists for: the symtab
        # entry is renamed in place and nothing is added to aliases.ld.
        self.fixture.write(
            symtab=BASE_SYMTAB.replace(
                "func_80001000 = 0x80001000; // type:func",
                "Real_Name = 0x80001000; // type:func",
            )
        )
        self.fixture.stage()
        missing = car.check_diff(self.repo, staged=True)
        self.assertEqual(missing, [("func_80001000", "Real_Name", "0x80001000")])

    def test_rename_with_matching_alias_is_accepted(self) -> None:
        # The correct shape: container_merge.py's merge() / name_decompiled
        # apply's safe default -- symtab renamed AND a matching alias added
        # in the same commit.
        self.fixture.write(
            symtab=BASE_SYMTAB.replace(
                "func_80001000 = 0x80001000; // type:func",
                "Real_Name = 0x80001000; // type:func",
            ),
            aliases=BASE_ALIASES + "func_80001000 = Real_Name;\n",
        )
        self.fixture.stage()
        missing = car.check_diff(self.repo, staged=True)
        self.assertEqual(missing, [])

    def test_symtab_untouched_alias_only_is_accepted(self) -> None:
        # name_decompiled.py apply's actual safe-default shape: the symtab
        # is never touched at all, only the alias is appended.
        self.fixture.write(aliases=BASE_ALIASES + "func_80001000 = Real_Name;\n")
        self.fixture.stage()
        missing = car.check_diff(self.repo, staged=True)
        self.assertEqual(missing, [])

    def test_unrelated_new_symtab_entry_is_not_flagged(self) -> None:
        self.fixture.write(symtab=BASE_SYMTAB + "func_80006000 = 0x80006000; // type:func\n")
        self.fixture.stage()
        missing = car.check_diff(self.repo, staged=True)
        self.assertEqual(missing, [])

    def test_address_value_fix_without_alias_is_not_flagged(self) -> None:
        self.fixture.write(
            symtab=BASE_SYMTAB.replace(
                "func_80001000 = 0x80001000; // type:func",
                "func_80001000 = 0x80001004; // type:func",
            )
        )
        self.fixture.stage()
        missing = car.check_diff(self.repo, staged=True)
        self.assertEqual(missing, [])

    def test_multiple_renames_only_missing_ones_reported(self) -> None:
        symtab = BASE_SYMTAB.replace(
            "func_80001000 = 0x80001000; // type:func",
            "Real_Name = 0x80001000; // type:func",
        ).replace(
            "func_80002000 = 0x80002000; // type:func",
            "Other_Name = 0x80002000; // type:func",
        )
        self.fixture.write(symtab=symtab, aliases=BASE_ALIASES + "func_80001000 = Real_Name;\n")
        self.fixture.stage()
        missing = car.check_diff(self.repo, staged=True)
        self.assertEqual(missing, [("func_80002000", "Other_Name", "0x80002000")])


class MainCliTests(_GitEnvIsolatedTestCase):
    def test_exits_nonzero_and_prints_guidance_for_a_bare_rename(self) -> None:
        self.fixture.write(
            symtab=BASE_SYMTAB.replace(
                "func_80001000 = 0x80001000; // type:func",
                "Real_Name = 0x80001000; // type:func",
            )
        )
        self.fixture.stage()
        buf_err = []
        with mock.patch("sys.stderr") as mock_stderr:
            mock_stderr.write = lambda s: buf_err.append(s)
            rc = car.main(["--staged", "--repo-root", str(self.repo)])
        self.assertEqual(rc, 1)
        text = "".join(buf_err)
        self.assertIn("func_80001000", text)
        self.assertIn("Real_Name", text)
        self.assertIn("container_merge.py", text)
        self.assertIn("aliases.ld", text)

    def test_exits_zero_for_clean_alias_preserving_rename(self) -> None:
        self.fixture.write(
            symtab=BASE_SYMTAB.replace(
                "func_80001000 = 0x80001000; // type:func",
                "Real_Name = 0x80001000; // type:func",
            ),
            aliases=BASE_ALIASES + "func_80001000 = Real_Name;\n",
        )
        self.fixture.stage()
        rc = car.main(["--staged", "--repo-root", str(self.repo)])
        self.assertEqual(rc, 0)

    def test_exits_zero_when_nothing_touches_the_symtab(self) -> None:
        rc = car.main(["--staged", "--repo-root", str(self.repo)])
        self.assertEqual(rc, 0)

    def test_skip_env_var_bypasses(self) -> None:
        self.fixture.write(
            symtab=BASE_SYMTAB.replace(
                "func_80001000 = 0x80001000; // type:func",
                "Real_Name = 0x80001000; // type:func",
            )
        )
        self.fixture.stage()
        with mock.patch.dict(os.environ, {"ALIAS_RENAME_SKIP": "1"}):
            rc = car.main(["--staged", "--repo-root", str(self.repo)])
        self.assertEqual(rc, 0)

    def test_missing_staged_flag_errors(self) -> None:
        with self.assertRaises(SystemExit):
            car.main(["--repo-root", str(self.repo)])


if __name__ == "__main__":
    unittest.main()
