"""Tests for ``tools/permute_candidate.py``'s ``base.c`` composition.

Regression coverage for a real fleet failure: a candidate for
``func_86000020`` (fragment 47) probed fine via ``try_pragma_compare``'s
probe path (similarity 0.9524) but the permuter's flattened ``base.c``
failed to compile with

    redeclaration of 'func_87C00160'; previous declaration at line 2055
    Incompatible function return type for this function.

The candidate body calls ``func_87C00160``/``func_87C0068C`` without any
declaration in scope. The probe path's ``_augment_blocks_with_callee_
declarations`` scans the owner file for a real signature of every callee a
candidate references but does not itself declare, and injects it above the
body -- so IDO never falls back to an implicit ``int`` declaration at the
call site that later conflicts with the file's own (correctly typed)
prototype further down. ``permute_candidate.build_work_directory`` skipped
that step and simply concatenated ``declarations + code``, so an undeclared
callee got IDO's implicit declaration first and the real prototype,
encountered later while flattening the whole owner file into the permuter's
single ``base.c``, was rejected as an incompatible redeclaration.

``_compose_candidate`` closes that gap by routing through the exact same
``_augment_blocks_with_callee_declarations`` helper the probe path uses, so
these tests exercise that composition directly -- no filesystem, subprocess,
or compiler involved.
"""

from __future__ import annotations

import types
import unittest
from pathlib import Path

import permute_candidate
import try_pragma_compare as runner


def _owner(function: str, source_path: Path) -> types.SimpleNamespace:
    """A duck-typed stand-in for ``pragma_targets.Owner``.

    ``_compose_candidate`` only reads ``.function`` and ``.source_path``.
    """
    return types.SimpleNamespace(function=function, source_path=source_path)


class ComposeCandidateTests(unittest.TestCase):
    def setUp(self) -> None:
        # ``_compose_candidate`` resolves a repo root from ``owner.source_path``
        # via ``runner._repo_root_for_path`` and feeds it to
        # ``_augment_blocks_with_callee_declarations`` for the cross-file
        # declaration index. A path under a directory with no ``.git`` and no
        # ``disasm/src`` keeps that index empty and this test isolated from
        # the real repository tree (which the fallback would otherwise scan).
        import tempfile

        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self.repo_root = Path(self._tmp.name)
        self.source_path = self.repo_root / "disasm" / "src" / "fragments" / "47" / "fake.c"
        self.source_path.parent.mkdir(parents=True)

    def test_injects_fallback_declarations_for_undeclared_callees(self) -> None:
        # Mirrors the real fragment47 file: func_87C00160/func_87C0068C are
        # declared correctly somewhere in the owner file (as they were, ahead
        # of a sibling function later in fragment47_246640.c) but not before
        # this candidate's own call sites, and not in the shared declarations
        # block the driver passed.
        baseline_source = (
            "extern f64 func_87C00208(void *, void *);\n"
            "f64 func_86000020(void *arg0, void *arg1) {\n"
            "    func_87C00160(arg0, arg1, arg0);\n"
            "    return func_87C0068C(arg0);\n"
            "}\n"
            "extern void *func_87C00160(void *, void *, void *);\n"
            "extern f64 func_87C0068C(void *);\n"
            "void func_860004C8(void) {}\n"
        )
        declarations = "extern f64 func_87C00208(void *, void *);"
        body = (
            "f64 func_86000020(void *arg0, void *arg1) {\n"
            "    func_87C00160(arg0, arg1, arg0);\n"
            "    return func_87C0068C(arg0);\n"
            "}"
        )
        owner = _owner("func_86000020", self.source_path)
        composed = permute_candidate._compose_candidate(
            owner, body, declarations, baseline_source
        )

        # Both fallback prototypes must land above the body's first use. The
        # scanner reuses the file's own spelling verbatim (including its
        # ``void *`` spacing), which is why this is a real bug reproduction
        # and not a hand-normalized expectation.
        first_use = composed.index("func_87C00160(arg0")
        decl_160 = composed.index("extern void * func_87C00160(void *, void *, void *);")
        decl_068c = composed.index("extern f64 func_87C0068C(void *);")
        self.assertLess(decl_160, first_use)
        self.assertLess(decl_068c, first_use)
        # The shared declarations block is preserved too.
        self.assertIn(declarations, composed)

    def test_no_fallback_needed_when_declarations_already_cover_the_callee(self) -> None:
        baseline_source = (
            "f64 func_86000020(void *arg0) { return func_87C0068C(arg0); }\n"
            "extern f64 func_87C0068C(void *);\n"
        )
        declarations = "extern f64 func_87C0068C(void *);"
        body = "f64 func_86000020(void *arg0) { return func_87C0068C(arg0); }"
        owner = _owner("func_86000020", self.source_path)
        composed = permute_candidate._compose_candidate(
            owner, body, declarations, baseline_source
        )
        # Exactly the shared declaration plus the body -- no second, possibly
        # duplicate declaration is layered on top of it.
        self.assertEqual(composed.count("func_87C0068C("), 2)  # decl + call
        self.assertEqual(composed, declarations + "\n" + body + "\n")

    def test_no_fallback_when_candidate_already_declares_the_callee_itself(self) -> None:
        baseline_source = "f64 func_86000020(void *arg0) { return func_87C0068C(arg0); }\n"
        body = (
            "extern f64 func_87C0068C(void *);\n"
            "f64 func_86000020(void *arg0) { return func_87C0068C(arg0); }"
        )
        owner = _owner("func_86000020", self.source_path)
        composed = permute_candidate._compose_candidate(owner, body, None, baseline_source)
        self.assertEqual(composed, body + "\n")

    def test_nothing_guessed_when_callee_is_undeclared_anywhere(self) -> None:
        # "synthesise only when nothing is found" (AGENTS.md Sec 5): a callee
        # the whole owner file says nothing about is left alone so a probe
        # against it fails (or implicitly declares) exactly as it always has.
        baseline_source = "f64 func_86000020(void *arg0) { return func_ABCDEF01(arg0); }\n"
        body = "f64 func_86000020(void *arg0) { return func_ABCDEF01(arg0); }"
        owner = _owner("func_86000020", self.source_path)
        composed = permute_candidate._compose_candidate(owner, body, None, baseline_source)
        self.assertEqual(composed, body + "\n")

    def test_does_not_declare_the_target_function_itself(self) -> None:
        baseline_source = "s32 func_86000020(s32 a) { return a; }\n"
        body = "s32 func_86000020(s32 a) { return func_86000020(a - 1) + 1; }"
        owner = _owner("func_86000020", self.source_path)
        composed = permute_candidate._compose_candidate(owner, body, None, baseline_source)
        self.assertEqual(composed, body + "\n")

    def test_matches_the_probe_paths_helper_directly(self) -> None:
        # ``_compose_candidate`` must be a thin wrapper: for a single-block
        # batch its result should be exactly what
        # ``_augment_blocks_with_callee_declarations`` returns, so the
        # permuter's composition can never silently drift from the probe
        # path that already validated the candidate.
        baseline_source = (
            "f64 func_86000020(void *arg0) { return func_87C0068C(arg0); }\n"
            "extern f64 func_87C0068C(void *);\n"
        )
        declarations = "extern f64 D_8600D4E8;"
        body = "f64 func_86000020(void *arg0) { return func_87C0068C(arg0); }"
        owner = _owner("func_86000020", self.source_path)
        composed = permute_candidate._compose_candidate(
            owner, body, declarations, baseline_source
        )
        expected = runner._augment_blocks_with_callee_declarations(
            [(owner.function, body.rstrip() + "\n")],
            runner._declaration_prefix(declarations),
            baseline_source,
            runner._repo_root_for_path(owner.source_path),
        )[0][1]
        self.assertEqual(composed, expected)


if __name__ == "__main__":
    unittest.main()
