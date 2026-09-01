"""Tests for the fleet janitor.

The classification is the only judgement here that can destroy work, so it is
pinned hard: proven-but-uncommitted work must never be reverted, and an
unproven body must never be mistaken for proven.
"""

import unittest
from unittest import mock

import fleet_janitor as janitor


_PRAGMA = '#pragma GLOBAL_ASM("asm/us/nonmatchings/x/{name}.s")'


def _drop_diff(*names: str) -> str:
    """A diff dropping pragmas from a real ``disasm/src`` path.

    The path matters: ``removed_pragma_functions`` deliberately ignores a
    pragma line removed anywhere else, so a fixture outside ``disasm/src``
    silently tests nothing.
    """
    lines = [
        "diff --git a/disasm/src/x.c b/disasm/src/x.c",
        "--- a/disasm/src/x.c",
        "+++ b/disasm/src/x.c",
    ]
    lines += ["-" + _PRAGMA.format(name=name) for name in names]
    return "\n".join(lines)


class ClassifySourceTests(unittest.TestCase):
    def test_all_pragmas_proven_is_recoverable(self) -> None:
        with mock.patch.object(janitor, "git", return_value=_drop_diff("func_1", "func_2")):
            verdict, functions = janitor.classify_source("x.c", {"func_1", "func_2"})
        self.assertEqual(verdict, "recoverable")
        self.assertEqual(functions, ["func_1", "func_2"])

    def test_any_unproven_pragma_is_orphaned(self) -> None:
        with mock.patch.object(janitor, "git", return_value=_drop_diff("func_1", "func_2")):
            verdict, functions = janitor.classify_source("x.c", {"func_1"})
        self.assertEqual(verdict, "orphaned")
        self.assertEqual(functions, ["func_2"])

    def test_no_pragma_dropped_is_harmless(self) -> None:
        diff = ("diff --git a/disasm/src/x.c b/disasm/src/x.c\n"
                "+++ b/disasm/src/x.c\n+// a comment\n")
        with mock.patch.object(janitor, "git", return_value=diff):
            verdict, functions = janitor.classify_source("x.c", set())
        self.assertEqual(verdict, "no-pragma-change")
        self.assertEqual(functions, [])

    def test_nothing_proven_is_orphaned(self) -> None:
        with mock.patch.object(janitor, "git", return_value=_drop_diff("func_1")):
            verdict, _ = janitor.classify_source("x.c", set())
        self.assertEqual(verdict, "orphaned")


class CleanTests(unittest.TestCase):
    def _state(self, sources):
        return {"sources": sources, "dead_claims": [],
                "prunable_worktrees": [], "stale_probe_dirs": []}

    def test_recoverable_is_never_reverted(self) -> None:
        state = self._state([
            {"path": "disasm/src/x.c", "verdict": "recoverable", "functions": ["func_1"]},
        ])
        with mock.patch.object(janitor, "git") as git, \
             mock.patch.object(janitor, "backup") as backup:
            janitor.clean(state, revert_orphaned=True)
        git.assert_not_called()
        backup.assert_not_called()

    def test_orphaned_is_kept_without_the_flag(self) -> None:
        state = self._state([
            {"path": "disasm/src/x.c", "verdict": "orphaned", "functions": ["func_1"]},
        ])
        with mock.patch.object(janitor, "git") as git, \
             mock.patch.object(janitor, "backup") as backup:
            acted = janitor.clean(state, revert_orphaned=False)
        self.assertEqual(acted, 0)
        git.assert_not_called()
        backup.assert_not_called()

    def test_orphaned_is_backed_up_before_revert(self) -> None:
        state = self._state([
            {"path": "disasm/src/x.c", "verdict": "orphaned", "functions": ["func_1"]},
        ])
        calls = []
        with mock.patch.object(janitor, "git", side_effect=lambda *a, **k: calls.append(a)), \
             mock.patch.object(janitor, "backup",
                               side_effect=lambda p: calls.append(("backup", p)) or janitor.BACKUP_DIR / "b"):
            janitor.clean(state, revert_orphaned=True)
        self.assertEqual(calls[0][0], "backup")
        self.assertIn("checkout", calls[1])


if __name__ == "__main__":
    unittest.main()
