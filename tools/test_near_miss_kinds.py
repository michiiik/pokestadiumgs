#!/usr/bin/env python3
"""Unit tests for tools/near_miss_kinds.py's pool selection and rewrite generators."""

from __future__ import annotations

import sys
import unittest
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import near_miss_kinds as nmk  # noqa: E402


class FakeOwner:
    def __init__(self, path: str) -> None:
        self.source_path = Path(path)


def _fake_require_owner(solved: set[str]):
    def require_owner(function: str) -> FakeOwner:
        if function in solved:
            raise KeyError(function)
        return FakeOwner(f"/fake/{function}.c")
    return require_owner


class SelectPoolTests(unittest.TestCase):
    ROWS = [
        {
            "source": "disasm/src/a.c",
            "attempts": [
                {
                    "function": "func_AAA",
                    "label": "m2c:u8-void",
                    "status": "probe_rejected",
                    "similarity_score": 0.93,
                    "mismatch_kind": "register_allocation_only",
                    "candidate": "s32 func_AAA(void) { return 0; }\n",
                    "declarations": None,
                },
                # A later, higher-scoring attempt for the same function must win.
                {
                    "function": "func_AAA",
                    "label": "m2c:s32-s32",
                    "status": "probe_rejected",
                    "similarity_score": 0.97,
                    "mismatch_kind": "immediate_drift",
                    "candidate": "s32 func_AAA(void) { return 1; }\n",
                    "declarations": None,
                },
                # Accepted: must not appear in the pool at all.
                {
                    "function": "func_BBB",
                    "label": "m2c:s32-s32",
                    "status": "accepted",
                    "similarity_score": 1.0,
                    "mismatch_kind": None,
                    "candidate": "void func_BBB(void) {}\n",
                    "declarations": None,
                },
                # Below the similarity floor.
                {
                    "function": "func_CCC",
                    "label": "m2c:u8-void",
                    "status": "probe_rejected",
                    "similarity_score": 0.5,
                    "mismatch_kind": "instruction_drift",
                    "candidate": "void func_CCC(void) {}\n",
                    "declarations": None,
                },
                # High score but the owner no longer holds a pragma (solved
                # by a different run since these stats were recorded).
                {
                    "function": "func_DDD",
                    "label": "m2c:u8-void",
                    "status": "probe_rejected",
                    "similarity_score": 0.99,
                    "mismatch_kind": "register_allocation_only",
                    "candidate": "void func_DDD(void) {}\n",
                    "declarations": None,
                },
            ],
        }
    ]

    def test_best_attempt_wins_and_solved_owners_are_dropped(self) -> None:
        with mock.patch.object(nmk.targets, "require_owner", side_effect=_fake_require_owner({"func_DDD"})):
            pool = nmk.select_pool(self.ROWS, min_similarity=0.9)
        self.assertEqual(sorted(pool.keys()), ["immediate_drift"])
        entries = pool["immediate_drift"]
        self.assertEqual(len(entries), 1)
        self.assertEqual(entries[0]["function"], "func_AAA")
        self.assertEqual(entries[0]["similarity_score"], 0.97)
        self.assertEqual(entries[0]["candidate"], "s32 func_AAA(void) { return 1; }\n")

    def test_kinds_filter_restricts_result(self) -> None:
        with mock.patch.object(nmk.targets, "require_owner", side_effect=_fake_require_owner(set())):
            pool = nmk.select_pool(self.ROWS, min_similarity=0.9, kinds=("register_allocation_only",))
        self.assertEqual(sorted(pool.keys()), ["register_allocation_only"])
        self.assertEqual([e["function"] for e in pool["register_allocation_only"]], ["func_DDD"])

    def test_similarity_floor_excludes_low_scores(self) -> None:
        with mock.patch.object(nmk.targets, "require_owner", side_effect=_fake_require_owner(set())):
            pool = nmk.select_pool(self.ROWS, min_similarity=0.9)
        functions = {e["function"] for entries in pool.values() for e in entries}
        self.assertNotIn("func_CCC", functions)

    def test_pool_report_buckets_by_band(self) -> None:
        with mock.patch.object(nmk.targets, "require_owner", side_effect=_fake_require_owner(set())):
            pool = nmk.select_pool(self.ROWS, min_similarity=0.9)
        report = nmk.pool_report(pool, min_similarity=0.9)
        self.assertEqual(report["total"], 2)
        self.assertEqual(report["kinds"]["immediate_drift"]["bands"], {"0.95-1.00": 1})
        self.assertEqual(report["kinds"]["register_allocation_only"]["bands"], {"0.95-1.00": 1})


class DeclOrderTests(unittest.TestCase):
    CODE = (
        "s32 func_80001000(s32 arg0) {\n"
        "    s32 temp1;\n"
        "    s32 temp2;\n"
        "    s32 temp3;\n"
        "    temp1 = arg0 + 1;\n"
        "    temp2 = temp1 & 0xFF;\n"
        "    temp3 = temp2 == 4;\n"
        "    return temp3;\n"
        "}\n"
    )

    def test_three_locals_gets_all_five_non_identity_permutations(self) -> None:
        results = nmk.decl_order_candidates(self.CODE)
        self.assertEqual(len(results), 5)
        labels = [label for label, _ in results]
        self.assertEqual(len(labels), len(set(labels)))
        for label, candidate in results:
            self.assertTrue(label.startswith("kind:register_allocation_only:decl-order:"))
            self.assertNotEqual(candidate, self.CODE)
            self.assertIn("temp1 = arg0 + 1;", candidate)

    def test_cap_is_honored(self) -> None:
        results = nmk.decl_order_candidates(self.CODE, limit=2)
        self.assertLessEqual(len(results), 2)

    def test_no_decl_block_returns_empty(self) -> None:
        code = "void func_80002000(void) {\n    return;\n}\n"
        self.assertEqual(nmk.decl_order_candidates(code), [])

    def test_stack_slot_ascending_and_descending(self) -> None:
        # Five locals (scrambled, neither ascending nor descending) so the
        # exhaustive-permutation path (<=4 locals) doesn't apply and the
        # adjacent-swap/reverse orders can't already coincide with a fully
        # sorted order -- this isolates the stack-slot helper reuse.
        code = (
            "void func_80003000(void) {\n"
            "    s32 sp24;\n"
            "    s32 sp30;\n"
            "    s32 sp20;\n"
            "    s32 sp2C;\n"
            "    s32 sp28;\n"
            "    sp24 = 0;\n"
            "    sp30 = 1;\n"
            "    sp20 = 2;\n"
            "    sp2C = 3;\n"
            "    sp28 = 4;\n"
            "}\n"
        )
        results = nmk.decl_order_candidates(code, limit=100)
        labels = [label for label, _ in results]
        self.assertIn("kind:register_allocation_only:decl-order:stack-ascending", labels)
        self.assertIn("kind:register_allocation_only:decl-order:stack-descending", labels)
        ascending = dict(results)["kind:register_allocation_only:decl-order:stack-ascending"]
        self.assertLess(ascending.index("sp20"), ascending.index("sp24"))
        self.assertLess(ascending.index("sp24"), ascending.index("sp28"))
        descending = dict(results)["kind:register_allocation_only:decl-order:stack-descending"]
        self.assertLess(descending.index("sp30"), descending.index("sp2C"))
        self.assertLess(descending.index("sp2C"), descending.index("sp20"))


class TypeWidthTests(unittest.TestCase):
    def test_swaps_one_local_at_a_time(self) -> None:
        code = "s32 func_80004000(void) {\n    s32 temp;\n    temp = 1;\n    return temp;\n}\n"
        results = nmk.type_width_candidates(code)
        alts = {label.rsplit(":", 1)[-1] for label, _ in results}
        self.assertEqual(alts, {"s32-to-u8", "s32-to-u16", "s32-to-s16"})
        for label, candidate in results:
            # Exactly one declaration changed; usage sites are untouched.
            self.assertEqual(candidate.count("s32 temp;") + candidate.count("u8 temp;") +
                              candidate.count("u16 temp;") + candidate.count("s16 temp;"), 1)

    def test_u32_only_swaps_to_s32(self) -> None:
        code = "void func_80005000(void) {\n    u32 count;\n    count = 0;\n}\n"
        results = nmk.type_width_candidates(code)
        self.assertEqual(len(results), 1)
        self.assertTrue(results[0][0].endswith("u32-to-s32"))


class HoistInlineTests(unittest.TestCase):
    def test_inlines_single_use_temp(self) -> None:
        code = "s32 func_80006000(s32 arg0) {\n    s32 temp = arg0 + 4;\n    return temp;\n}\n"
        results = nmk.inline_single_use_temp_candidates(code)
        self.assertEqual(len(results), 1)
        label, candidate = results[0]
        self.assertEqual(label, "kind:register_allocation_only:inline-temp:temp")
        self.assertNotIn("s32 temp", candidate)
        self.assertIn("return (arg0 + 4);", candidate)

    def test_skips_multi_use_temp(self) -> None:
        code = "s32 func_80007000(s32 arg0) {\n    s32 temp = arg0 + 4;\n    temp = temp + 1;\n    return temp;\n}\n"
        self.assertEqual(nmk.inline_single_use_temp_candidates(code), [])

    def test_hoists_repeated_field_access(self) -> None:
        code = (
            "void func_80008000(s32 *arg0) {\n"
            "    s32 result;\n"
            "    result = arg0[4] + arg0[4];\n"
            "}\n"
        )
        results = nmk.hoist_repeated_subexpr_candidates(code)
        self.assertEqual(len(results), 1)
        label, candidate = results[0]
        self.assertTrue(label.startswith("kind:register_allocation_only:hoist-temp:"))
        self.assertEqual(candidate.count("arg0[4]"), 1)
        self.assertIn("temp_hoist0 = arg0[4];", candidate)


class CommuteSwapTests(unittest.TestCase):
    def test_swaps_addition_operands(self) -> None:
        code = "s32 func_80009000(s32 a, s32 b) {\n    return a + b;\n}\n"
        results = nmk.commute_swap_candidates(code)
        self.assertEqual(len(results), 1)
        self.assertIn("return b + a;", results[0][1])

    def test_does_not_split_logical_and(self) -> None:
        code = "s32 func_8000A000(s32 a, s32 b) {\n    return a && b;\n}\n"
        for _, candidate in nmk.commute_swap_candidates(code):
            self.assertNotIn("b &a", candidate)
            self.assertNotIn("a& b", candidate)


class BooleanNormalizeTests(unittest.TestCase):
    SLT_ENTRY = {"expected_instruction_text": "slt $t0, $t1, $t2", "actual_instruction_text": "xor $t0, $t1, $t2"}
    OTHER_ENTRY = {"expected_instruction_text": "addu $t0, $t1, $t2", "actual_instruction_text": "addu $t0, $t2, $t1"}

    def test_if_assign_to_ne_zero(self) -> None:
        code = "void func_8000B000(s32 x, s32 *y) {\n    if (x > 0) { *y = 1; }\n}\n"
        results = nmk.boolean_normalize_candidates(code, self.SLT_ENTRY)
        self.assertEqual(len(results), 1)
        self.assertIn("*y = (x > 0) != 0;", results[0][1])

    def test_ne_zero_to_if_assign(self) -> None:
        code = "void func_8000C000(s32 x, s32 *y) {\n    *y = x != 0;\n}\n"
        results = nmk.boolean_normalize_candidates(code, self.SLT_ENTRY)
        self.assertEqual(len(results), 1)
        self.assertIn("if (x) { *y = 1; }", results[0][1])

    def test_gated_off_when_diff_is_not_slt_or_xor(self) -> None:
        code = "void func_8000D000(s32 x, s32 *y) {\n    if (x > 0) { *y = 1; }\n}\n"
        self.assertEqual(nmk.boolean_normalize_candidates(code, self.OTHER_ENTRY), [])


class ImmediateDriftTests(unittest.TestCase):
    def test_offset_shift_repairs_literal_and_scaled_index(self) -> None:
        code = "void func_8000E000(struct Foo *arg0) {\n    arg0->field = *(u8 *)((u8 *)arg0 + 0x10);\n}\n"
        entry = {
            "expected_instruction_text": "lbu $t0, 0x14($t1)",
            "actual_instruction_text": "lbu $t0, 0x10($t1)",
            "assembly_diff": [{"expected": "lbu $t0, 0x14($t1)", "actual": "lbu $t0, 0x10($t1)"}],
        }
        results = nmk.offset_shift_candidates(code, entry)
        self.assertTrue(any("0x14" in candidate for _, candidate in results))
        for label, _ in results:
            self.assertTrue(label.startswith("kind:immediate_drift:offset-shift:"))

    def test_offset_shift_scales_array_index(self) -> None:
        code = "void func_8000F000(s32 *arr) {\n    arr[2] = 1;\n}\n"
        entry = {"expected_instruction_text": "sw $t0, 0xC($t1)", "actual_instruction_text": "sw $t0, 0x8($t1)"}
        results = nmk.offset_shift_candidates(code, entry)
        self.assertTrue(any("arr[3]" in candidate for _, candidate in results))

    def test_frame_padding_grows_frame_by_expected_delta(self) -> None:
        code = "void func_80010000(s32 arg0) {\n    s32 temp;\n    temp = arg0;\n}\n"
        entry = {"expected_instruction_text": "addiu $sp, $sp, -0x28", "actual_instruction_text": "addiu $sp, $sp, -0x20"}
        results = nmk.frame_padding_candidates(code, entry)
        self.assertEqual(len(results), 1)
        self.assertIn("s32 pad_frame[2];", results[0][1])

    def test_frame_padding_empty_without_sp_instructions(self) -> None:
        self.assertEqual(nmk.frame_padding_candidates("void func_80011000(void) {}\n", {}), [])

    def test_literal_width_round_trips(self) -> None:
        code = "void func_80012000(void) {\n    s32 mask = 0xFF7F;\n}\n"
        results = nmk.literal_width_candidates(code)
        labels = [label for label, _ in results]
        self.assertIn("kind:immediate_drift:literal-width:0xFF7F-to-~0x80", labels)

    def test_negative_literal_gets_masked_form(self) -> None:
        code = "void func_80013000(void) {\n    s32 x = -5;\n}\n"
        results = nmk.literal_width_candidates(code)
        self.assertTrue(any("0xFFFFFFFB" in candidate for _, candidate in results))

    def test_stride_shift_to_mul_and_index_to_ptr(self) -> None:
        code = "void func_80014000(s32 *arr, s32 i) {\n    s32 v = arr[i];\n    s32 w = i << 2;\n}\n"
        results = nmk.stride_candidates(code)
        candidates = [c for _, c in results]
        self.assertTrue(any("i * (1 << 2)" in c for c in candidates))
        self.assertTrue(any("*(arr + i)" in c for c in candidates))

    def test_immediate_drift_aggregate_is_capped(self) -> None:
        code = "void func_80015000(s32 *arr, s32 i) {\n    s32 v = arr[i];\n    s32 w = i << 2;\n    s32 mask = 0xFF7F;\n}\n"
        entry = {"expected_instruction_text": "sw $t0, 0xC($t1)", "actual_instruction_text": "sw $t0, 0x8($t1)"}
        results = nmk.immediate_drift_candidates(code, entry, cap=3)
        self.assertLessEqual(len(results), 3)
        candidates_only = [c for _, c in results]
        self.assertEqual(len(candidates_only), len(set(candidates_only)))


class OperandOrSchedulingDriftTests(unittest.TestCase):
    def test_gated_below_0_95_similarity(self) -> None:
        code = "s32 func_80016000(s32 x) {\n    s32 result = func_80017000(x);\n    return result;\n}\n"
        self.assertEqual(nmk.operand_or_scheduling_drift_candidates(code, {"similarity_score": 0.9}), [])

    def test_merge_return_at_high_similarity(self) -> None:
        code = "s32 func_80018000(s32 x) {\n    s32 result = func_80019000(x);\n    return result;\n}\n"
        results = nmk.operand_or_scheduling_drift_candidates(code, {"similarity_score": 0.97})
        labels = [label for label, _ in results]
        self.assertTrue(any(label.startswith("kind:operand_or_scheduling_drift:merge-return:") for label in labels))

    def test_split_return_introduces_temp(self) -> None:
        code = "s32 func_8001A000(s32 x) {\n    return func_8001B000(x);\n}\n"
        results = nmk.split_merge_candidates(code)
        self.assertTrue(any("temp_ret" in candidate for _, candidate in results))

    def test_reorder_independent_store_and_call(self) -> None:
        code = "void func_8001C000(s32 *out, s32 x) {\n    *out = x;\n    func_8001D000(x);\n}\n"
        results = nmk.reorder_store_call_candidates(code)
        self.assertEqual(len(results), 1)
        candidate = results[0][1]
        self.assertLess(candidate.index("func_8001D000(x);"), candidate.index("*out = x;"))

    def test_does_not_reorder_dependent_store_and_call(self) -> None:
        code = "void func_8001E000(s32 *out) {\n    *out = func_8001F000();\n    func_80020000(out);\n}\n"
        self.assertEqual(nmk.reorder_store_call_candidates(code), [])

    def test_while_to_for_and_back(self) -> None:
        code = "void func_80021000(s32 n) {\n    while (n > 0) {\n        n = n - 1;\n    }\n}\n"
        results = nmk.loop_form_candidates(code)
        self.assertTrue(any("for (;n > 0;) {" in candidate for _, candidate in results))

    def test_do_while_to_while(self) -> None:
        code = "void func_80022000(s32 n) {\n    do {\n        n = n - 1;\n    } while (n > 0);\n}\n"
        results = nmk.loop_form_candidates(code)
        labels = [label for label, _ in results]
        self.assertIn("kind:operand_or_scheduling_drift:loop-form:do-while-to-while", labels)
        candidate = dict(results)["kind:operand_or_scheduling_drift:loop-form:do-while-to-while"]
        self.assertIn("while (n > 0) {", candidate)
        self.assertNotIn("do {", candidate)

    def test_increment_style_post_to_pre(self) -> None:
        code = "void func_80023000(s32 i) {\n    i++;\n}\n"
        results = nmk.increment_style_candidates(code)
        self.assertEqual(len(results), 1)
        self.assertIn("++i;", results[0][1])

    def test_increment_style_pre_to_post(self) -> None:
        code = "void func_80023100(s32 i) {\n    ++i;\n}\n"
        results = nmk.increment_style_candidates(code)
        self.assertEqual(len(results), 1)
        self.assertIn("i++;", results[0][1])


class GenerateCandidatesTests(unittest.TestCase):
    def test_unknown_kind_returns_empty(self) -> None:
        self.assertEqual(nmk.generate_candidates("some_other_kind", "code", {}), [])

    def test_dispatches_to_register_allocation_only(self) -> None:
        code = "s32 func_80024000(void) {\n    s32 temp;\n    temp = 1;\n    return temp;\n}\n"
        results = nmk.generate_candidates("register_allocation_only", code, {"similarity_score": 0.9}, cap=5)
        self.assertLessEqual(len(results), 5)
        self.assertTrue(all(label.startswith("kind:register_allocation_only:") for label, _ in results))


class RunDriverTests(unittest.TestCase):
    ENTRY = {
        "function": "func_80025000",
        "source": "disasm/src/z.c",
        "candidate": (
            "s32 func_80025000(s32 arg0) {\n"
            "    s32 temp1;\n"
            "    s32 temp2;\n"
            "    temp1 = arg0;\n"
            "    temp2 = temp1;\n"
            "    return temp2;\n"
            "}\n"
        ),
        "declarations": None,
        "label": "m2c:u8-void",
        "similarity_score": 0.93,
        "mismatch_kind": "register_allocation_only",
    }

    class _AcceptFirstMatchRunner:
        def __init__(self) -> None:
            self.calls: list[tuple[bool, list[str]]] = []

        def try_candidates_detailed(self, source_path, blocks, *, labels, gate, declarations=None, probe_workers=None):
            self.calls.append((gate, list(labels)))
            if not gate:
                attempts = [
                    {"index": i, "status": "probe_match" if i == 0 else "probe_rejected", "similarity_score": 0.9}
                    for i in range(len(labels))
                ]
                return {"attempts": attempts}
            return {"accepted": [blocks[0][0]]}

    class _NeverMatchRunner:
        def try_candidates_detailed(self, source_path, blocks, *, labels, gate, declarations=None, probe_workers=None):
            attempts = [{"index": i, "status": "probe_rejected", "similarity_score": 0.4} for i in range(len(labels))]
            return {"attempts": attempts}

    def test_accepts_first_probe_match_and_builds_rule_summary(self) -> None:
        runner = self._AcceptFirstMatchRunner()
        with mock.patch.object(nmk.targets, "require_owner", side_effect=_fake_require_owner(set())):
            result = nmk.run([dict(self.ENTRY)], runner=runner)
        self.assertEqual(result["owners"], 1)
        self.assertEqual(result["accepted"], ["func_80025000"])
        # One probe-only batch, then exactly one gate call for the hit.
        self.assertEqual(runner.calls[0][0], False)
        self.assertEqual(runner.calls[1][0], True)
        self.assertEqual(len(runner.calls[1][1]), 1)
        total_attempts = sum(counts.get("attempts", 0) for counts in result["rule_summary"].values())
        self.assertGreater(total_attempts, 0)

    def test_no_probe_match_without_permute_seconds_does_not_call_permuter(self) -> None:
        runner = self._NeverMatchRunner()
        with mock.patch.object(nmk.targets, "require_owner", side_effect=_fake_require_owner(set())), \
             mock.patch.object(nmk.sweep, "permute_and_gate") as permute_mock:
            result = nmk.run([dict(self.ENTRY)], runner=runner, permute_seconds=0.0)
        permute_mock.assert_not_called()
        self.assertEqual(result["accepted"], [])

    def test_falls_back_to_permuter_with_best_scoring_rewrite(self) -> None:
        runner = self._NeverMatchRunner()

        def fake_permute_and_gate(rows, **kwargs):
            return {"accepted": ["func_80025000"], "attempts": []}

        with mock.patch.object(nmk.targets, "require_owner", side_effect=_fake_require_owner(set())), \
             mock.patch.object(nmk.sweep, "permute_and_gate", side_effect=fake_permute_and_gate) as permute_mock:
            result = nmk.run([dict(self.ENTRY)], runner=runner, permute_seconds=30.0)
        permute_mock.assert_called_once()
        self.assertEqual(result["accepted"], ["func_80025000"])

    def test_solved_owner_is_skipped(self) -> None:
        runner = self._AcceptFirstMatchRunner()
        with mock.patch.object(nmk.targets, "require_owner", side_effect=_fake_require_owner({"func_80025000"})):
            result = nmk.run([dict(self.ENTRY)], runner=runner)
        self.assertEqual(result["owners"], 0)
        self.assertEqual(runner.calls, [])

    def test_accepts_dict_pool_input(self) -> None:
        runner = self._AcceptFirstMatchRunner()
        pool = {"register_allocation_only": [dict(self.ENTRY)]}
        with mock.patch.object(nmk.targets, "require_owner", side_effect=_fake_require_owner(set())):
            result = nmk.run(pool, runner=runner)
        self.assertEqual(result["owners"], 1)


if __name__ == "__main__":
    unittest.main()
