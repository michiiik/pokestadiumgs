#!/usr/bin/env python3
"""Unit tests for tools/name_decompiled.py.

Run with:
    python3 -m unittest discover -s tools -p 'test_*.py'
"""
from __future__ import annotations

import json
import shutil
import tempfile
import unittest
from pathlib import Path

import name_decompiled as nd


SYMTAB = """\
func_80001000 = 0x80001000; // type:func
func_80001111 = 0x80001111; // type:func
func_80002222 = 0x80002222; // type:func
AlreadyNamed = 0x80003333; // type:func
func_80004000 = 0x80004000; // type:func Foo4000
func_80005555 = 0x80005555; // type:func
func_80006666 = 0x80006666; // type:func
func_80007777 = 0x80007777; // type:func
func_80008888 = 0x80008888; // type:func
"""

A_C = """\
#include "global.h"

#pragma GLOBAL_ASM("asm/us/nonmatchings/foo/func_80001111.s")

void func_80001000(void) {
    // decoy: func_800010001 must not be touched (9 hex digits, not 8)
}

void func_80002222(void) {
    return;
}

void func_80003333(void) {
    return;
}

void func_80004000(void) {
    return;
}

void func_80006666(void) {
    return;
}

void func_80007777(void) {
    return;
}

void func_80008888(void) {
    return;
}
"""

B_C = """\
#include "global.h"
extern void func_80002222(void);

void func_80005555(void) {
    func_80002222();
}
// decoy: func_800010001 should not be touched
"""

PROTO_H = """\
extern void func_80002222(void);
extern void HelperUtil(void);
"""

SOME_S = """\
.section .text
glabel func_80009999
jal func_80002222
nop
lui $t0, %hi(func_80004000)
addiu $t0, $t0, %lo(func_80004000)
.word func_80001000
# decoy: func_800010001 should stay untouched
"""

NAMES_JSON = {
    "_README": ["fake test mapping"],
    "functions": {
        "func_80001000": ["Short", "evidence A"],
        "func_80001111": ["PragmaOwner", "evidence B: still a GLOBAL_ASM owner"],
        "func_80002222": ["RealName", "evidence C"],
        "func_80003333": ["AlreadyNamed", "evidence D: symtab already renamed it"],
        "func_80004000": ["Foo4000", "evidence E: pre-tagged // type:func comment"],
        "func_80005555": ["Wrapper5555", "evidence F"],
        "func_80006666": ["AlreadyNamed", "evidence G: collides with an existing symbol"],
        "func_80008888": ["HelperUtil", "evidence H: collides with a C identifier"],
        # func_80007777 intentionally has no mapping entry (reverse debt).
    },
}


class FixtureTestCase(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp(prefix="name_decompiled_test_"))
        self.addCleanup(shutil.rmtree, self.tmp, ignore_errors=True)

        disasm = self.tmp / "disasm"
        src = disasm / "src"
        include = disasm / "include"
        linker_us = disasm / "linker_scripts" / "us"
        asm_root = disasm / "asm" / "us" / "nonmatchings" / "foo"
        for d in (src, include, linker_us, asm_root):
            d.mkdir(parents=True, exist_ok=True)

        (src / "a.c").write_text(A_C, encoding="utf-8")
        (src / "b.c").write_text(B_C, encoding="utf-8")
        (include / "proto.h").write_text(PROTO_H, encoding="utf-8")
        (linker_us / "symbol_addrs_code.txt").write_text(SYMTAB, encoding="utf-8")
        (asm_root / "some.s").write_text(SOME_S, encoding="utf-8")

        self.names_path = self.tmp / "names.json"
        self.names_path.write_text(json.dumps(NAMES_JSON), encoding="utf-8")

        self.src_dir = src
        self.include_dir = include
        self.symtab_path = linker_us / "symbol_addrs_code.txt"
        self.asm_root = disasm / "asm" / "us"
        self.renames_log = disasm / "probe-stats" / "renames.jsonl"

    def build_plan(self):
        return nd.build_plan(repo_root=self.tmp, names_files=[str(self.names_path)],
                              src_dir=self.src_dir, symtab_path=self.symtab_path)

    def apply(self, rows, dry_run=False):
        return nd.apply_plan(rows, repo_root=self.tmp, src_dir=self.src_dir,
                              include_dir=self.include_dir, symtab_path=self.symtab_path,
                              asm_root=self.asm_root, renames_log=self.renames_log,
                              dry_run=dry_run)


class PlanTests(FixtureTestCase):
    def test_selects_decompiled_evidence_backed_still_func_named(self):
        plan = self.build_plan()
        by_old = {r.old: r for r in plan.rows}
        self.assertIn("func_80002222", by_old)
        self.assertEqual(by_old["func_80002222"].new, "RealName")
        self.assertEqual(by_old["func_80002222"].evidence, "evidence C")
        self.assertEqual(by_old["func_80002222"].origin, self.names_path.name)
        self.assertIn("a.c", by_old["func_80002222"].def_file)

    def test_skips_pragma_owner(self):
        plan = self.build_plan()
        self.assertNotIn("func_80001111", {r.old for r in plan.rows})

    def test_skips_already_renamed_in_symtab(self):
        # func_80003333 has a C body and an evidence entry, but the symtab
        # already spells it "AlreadyNamed" -- it is not still func_-named,
        # so plan() must leave it alone.
        plan = self.build_plan()
        self.assertNotIn("func_80003333", {r.old for r in plan.rows})

    def test_reverse_debt_unnamed_decompiled(self):
        plan = self.build_plan()
        self.assertIn("func_80007777", plan.unnamed_decompiled)

    def test_counts(self):
        plan = self.build_plan()
        # decompiled: everything in a.c/b.c minus the pragma owner
        # (func_80001111): 1000,2222,3333,4000,6666,7777,8888,5555 = 8
        self.assertEqual(plan.decompiled_count, 8)
        self.assertEqual(plan.pragma_owned_count, 1)


class ApplyTests(FixtureTestCase):
    def test_dry_run_changes_nothing(self):
        plan = self.build_plan()
        before = self.symtab_path.read_text()
        result = self.apply(plan.rows, dry_run=True)
        self.assertEqual(self.symtab_path.read_text(), before)
        self.assertFalse(self.renames_log.exists())
        self.assertTrue(result.applied)  # still reports what *would* apply

    def test_symtab_rewrite_and_redundant_comment_dropped(self):
        plan = self.build_plan()
        rows = [r for r in plan.rows if r.old == "func_80004000"]
        self.apply(rows)
        text = self.symtab_path.read_text()
        self.assertIn("Foo4000 = 0x80004000; // type:func\n", text)
        self.assertNotIn("Foo4000 = 0x80004000; // type:func Foo4000", text)
        self.assertNotIn("func_80004000", text)

    def test_symtab_rewrite_keeps_bare_type_func_tag(self):
        plan = self.build_plan()
        rows = [r for r in plan.rows if r.old == "func_80002222"]
        self.apply(rows)
        text = self.symtab_path.read_text()
        self.assertIn("RealName = 0x80002222; // type:func\n", text)

    def test_rewrites_definition_call_sites_and_headers(self):
        plan = self.build_plan()
        rows = [r for r in plan.rows if r.old == "func_80002222"]
        self.apply(rows)
        a_text = (self.src_dir / "a.c").read_text()
        b_text = (self.src_dir / "b.c").read_text()
        proto_text = (self.include_dir / "proto.h").read_text()
        self.assertIn("void RealName(void) {", a_text)
        self.assertIn("extern void RealName(void);", b_text)
        self.assertIn("RealName();", b_text)
        self.assertIn("extern void RealName(void);", proto_text)
        self.assertNotIn("func_80002222", a_text)
        self.assertNotIn("func_80002222", b_text)
        self.assertNotIn("func_80002222", proto_text)

    def test_asm_tree_rewritten_jal_hi_lo_word_glabel(self):
        plan = self.build_plan()
        rows = [r for r in plan.rows if r.old in ("func_80002222", "func_80004000", "func_80001000")]
        self.apply(rows)
        s_text = (self.asm_root / "nonmatchings" / "foo" / "some.s").read_text()
        self.assertIn("jal RealName", s_text)
        self.assertIn("%hi(Foo4000)", s_text)
        self.assertIn("%lo(Foo4000)", s_text)
        self.assertIn(".word Short", s_text)
        # glabel func_80009999 is an unrelated symbol and must survive.
        self.assertIn("glabel func_80009999", s_text)

    def test_word_boundary_does_not_touch_longer_lookalike(self):
        plan = self.build_plan()
        rows = [r for r in plan.rows if r.old in ("func_80001000",)]
        self.apply(rows)
        a_text = (self.src_dir / "a.c").read_text()
        b_text = (self.src_dir / "b.c").read_text()
        s_text = (self.asm_root / "nonmatchings" / "foo" / "some.s").read_text()
        # The 9-hex-digit decoy must never be rewritten by the 8-digit rename.
        self.assertIn("func_800010001", a_text)
        self.assertIn("func_800010001", b_text)
        self.assertIn("func_800010001", s_text)

    def test_collision_with_existing_symbol_is_refused(self):
        plan = self.build_plan()
        rows = [r for r in plan.rows if r.old in ("func_80002222", "func_80006666")]
        result = self.apply(rows)
        refused_old = {old for old, _new, _reason in result.refused}
        applied_old = {old for old, _new in result.applied}
        self.assertIn("func_80006666", refused_old)
        self.assertIn("func_80002222", applied_old)
        # The refused rename must not have touched the symtab or source.
        self.assertIn("func_80006666", self.symtab_path.read_text())
        self.assertIn("func_80006666", (self.src_dir / "a.c").read_text())

    def test_collision_with_existing_c_identifier_is_refused(self):
        plan = self.build_plan()
        rows = [r for r in plan.rows if r.old == "func_80008888"]
        result = self.apply(rows)
        self.assertEqual(result.applied, [])
        self.assertEqual(len(result.refused), 1)
        old, new, reason = result.refused[0]
        self.assertEqual((old, new), ("func_80008888", "HelperUtil"))

    def test_renames_log_written(self):
        plan = self.build_plan()
        rows = [r for r in plan.rows if r.old == "func_80002222"]
        self.apply(rows)
        self.assertTrue(self.renames_log.exists())
        lines = self.renames_log.read_text().splitlines()
        self.assertEqual(len(lines), 1)
        entry = json.loads(lines[0])
        self.assertEqual(entry["old"], "func_80002222")
        self.assertEqual(entry["new"], "RealName")
        self.assertEqual(entry["evidence"], "evidence C")
        self.assertIn("timestamp", entry)

    def test_renames_log_appends_across_calls(self):
        plan = self.build_plan()
        first = [r for r in plan.rows if r.old == "func_80002222"]
        self.apply(first)
        second_plan = self.build_plan()
        second = [r for r in second_plan.rows if r.old == "func_80004000"]
        self.apply(second)
        lines = self.renames_log.read_text().splitlines()
        self.assertEqual(len(lines), 2)


class HookTests(FixtureTestCase):
    def test_name_after_accept_renames_only_requested_functions(self):
        renamed = nd.name_after_accept(
            ["func_80002222", "func_80001111"],  # 1111 still pragma-owned: excluded
            repo_root=self.tmp,
            names_files=[str(self.names_path)],
        )
        # name_after_accept uses default paths under repo_root, matching the
        # fixture layout (disasm/src, disasm/include, disasm/linker_scripts/us).
        self.assertEqual(renamed, [("func_80002222", "RealName")])
        text = self.symtab_path.read_text() if False else (
            self.tmp / "disasm" / "linker_scripts" / "us" / "symbol_addrs_code.txt"
        ).read_text()
        self.assertIn("RealName = 0x80002222", text)

    def test_name_after_accept_no_match_returns_empty(self):
        renamed = nd.name_after_accept(
            ["func_80009999"],  # not in the mapping at all
            repo_root=self.tmp,
            names_files=[str(self.names_path)],
        )
        self.assertEqual(renamed, [])


if __name__ == "__main__":
    unittest.main()
