"""Regression test: a venv interpreter must not be symlink-resolved.

`decomp-venv/bin/python3` is a symlink chain ending at the system Python.
Running that target directly leaves sys.prefix outside the venv, so none of
the venv's site-packages import -- which is why every permuter run in this
repo died on "ModuleNotFoundError: No module named 'toml'" while decomp-venv
had toml installed the whole time.
"""

import os
import tempfile
import unittest
import unittest.mock
from pathlib import Path

import pragma_targets as targets
import permute_candidate


class ReadonlyToolPathSymlinkTests(unittest.TestCase):
    def test_follow_symlinks_false_keeps_the_link_path(self) -> None:
        with tempfile.TemporaryDirectory() as raw:
            root = Path(raw)
            real = root / "real_python"
            real.write_text("#!/bin/sh\n")
            link = root / "venv_python"
            link.symlink_to(real)

            with unittest.mock.patch.dict(os.environ, {"T": str(link)}):
                kept = targets.readonly_tool_path(
                    Path("unused"), override_name="T", follow_symlinks=False
                )
                resolved = targets.readonly_tool_path(
                    Path("unused"), override_name="T", follow_symlinks=True
                )
        self.assertEqual(kept.name, "venv_python")
        self.assertEqual(resolved.name, "real_python")

    def test_permuter_asks_for_the_unresolved_venv_python(self) -> None:
        path = permute_candidate._permuter_venv_python()
        self.assertIn("decomp-venv", str(path))
        self.assertNotIn("Cellar", str(path))
        self.assertNotIn("Frameworks", str(path))


if __name__ == "__main__":
    import unittest.mock  # noqa: F401
    unittest.main()
