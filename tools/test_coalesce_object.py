"""Synthetic safety controls for scheduled shared-page address pairs."""
import unittest

import coalesce_object as fold


HI = 0x3C010000
MOVE = 0x00803025  # or a2,a0,zero
STORE_A = 0xA0200000
STORE_B = 0xAC300000
A, B = "D_8AF2BF34", "D_8AF2BF30"
ADDRESSES = {A: 0x8AF2BF34, B: 0x8AF2BF30}


def fixture(gap=(MOVE,)):
    words = [HI, *gap, STORE_A, HI, 0x10A00002, STORE_B, 0x24020001, 0x03E00008, 0]
    n = len(gap)
    relocs = {0: [(A, 5)], (n + 1) * 4: [(A, 6)],
              (n + 2) * 4: [(B, 5)], (n + 4) * 4: [(B, 6)]}
    return words, relocs


class ScheduledPairs(unittest.TestCase):
    def test_copy_gap_and_final_branch_delay_store(self):
        words, relocs = fixture()
        actual, kept, count = fold.fold_function_words(words, relocs, ADDRESSES, None, "synthetic")
        expected = words[:3] + words[4:]
        expected[4] |= 0xBF30
        self.assertEqual((actual, count), (expected, 1))
        self.assertEqual(kept, [(0, A, 5), (8, A, 6)])

    def test_four_copies_are_bounded_but_supported(self):
        words, relocs = fixture((MOVE,) * 4)
        self.assertEqual(len(fold.plan_runs(words, relocs, ADDRESSES)), 1)

    def test_immediate_sign_extension_shift_is_a_safe_gap(self):
        for shift in [0x00052C00, 0x00052C03, 0x00052C02]:
            words, relocs = fixture((shift,))
            with self.subTest(shift=hex(shift)):
                self.assertEqual(len(fold.plan_runs(words, relocs, ADDRESSES)), 1)

    def test_shift_between_pairs_and_move_before_delay_slot(self):
        words = [HI, 0x00052C00, STORE_A, 0x00052C03, HI, MOVE,
                 0x10A00002, STORE_B, 0x24020001, 0x03E00008, 0]
        relocs = {0: [(A, 5)], 8: [(A, 6)], 16: [(B, 5)], 28: [(B, 6)]}
        actual, _, count = fold.fold_function_words(words, relocs, ADDRESSES, None, "synthetic")
        expected = words[:4] + words[5:]
        expected[6] |= 0xBF30
        self.assertEqual((actual, count), (expected, 1))

    def test_shift_must_not_read_or_write_at(self):
        for shift in [0x00010C00, 0x00050C03, 0x00252C00]:
            words, relocs = fixture((shift,))
            with self.subTest(shift=hex(shift)):
                self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])

    def test_relocated_branch_is_not_an_entry_proof(self):
        words, relocs = fixture()
        relocs[16] = [('outside', 10)]
        self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])

    def test_branch_must_not_enter_shift_between_pairs(self):
        words = [HI, MOVE, STORE_A, 0x00052C03, HI, STORE_B,
                 0x1000FFFC, 0]  # branch at 6 targets the gap at 3
        relocs = {0: [(A, 5)], 8: [(A, 6)], 16: [(B, 5)], 20: [(B, 6)]}
        self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])

    def test_too_many_instructions_between_pairs_are_not_skipped(self):
        words = [HI, STORE_A, *([MOVE] * 5), HI, STORE_B]
        relocs = {0: [(A, 5)], 4: [(A, 6)], 28: [(B, 5)], 32: [(B, 6)]}
        self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])

    def test_five_copies_are_not_supported(self):
        words, relocs = fixture((MOVE,) * 5)
        self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])

    def test_at_reads_writes_and_unknown_gap_operations_are_barriers(self):
        for word in [0x00203025, 0x00800825, 0x24080001, 0x8C880000, 0]:
            with self.subTest(word=hex(word)):
                words, relocs = fixture((word,))
                self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])

    def test_relocated_copy_is_not_an_unmodeled_gap(self):
        words, relocs = fixture()
        relocs[4] = [(A, 2)]
        self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])

    def test_branch_entry_into_any_part_of_new_run_is_refused(self):
        for target in range(1, 6):
            words, relocs = fixture()
            index = len(words)
            words += [0x10000000 | ((target - index - 1) & 0xFFFF), 0]
            with self.subTest(target=target):
                self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])

    def test_first_lui_in_delay_slot_is_not_extended(self):
        words, relocs = fixture()
        words.insert(0, 0x10000008)
        relocs = {offset + 4: entries for offset, entries in relocs.items()}
        self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])

    def test_unknown_control_flow_is_not_extended(self):
        for word in [0x08000000, 0x0C000000, 0x01000008, 0x0100F809]:
            words, relocs = fixture()
            words += [word, 0]
            with self.subTest(word=hex(word)):
                self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])

    def test_filter_and_address_proof_are_unchanged(self):
        words, relocs = fixture()
        self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES, {A}), [])
        self.assertEqual(fold.plan_runs(words, relocs, {A: ADDRESSES[A]}), [])
        with self.assertRaises(fold.FoldError):
            fold.plan_runs(words, relocs, {A: 0x8AF2BF38, B: ADDRESSES[B]})

    def test_branch_before_run_is_repaired(self):
        words, relocs = fixture()
        words = [0x10000008, 0] + words
        relocs = {offset + 8: entries for offset, entries in relocs.items()}
        actual, _, count = fold.fold_function_words(words, relocs, ADDRESSES, None, "synthetic")
        self.assertEqual(count, 1)
        self.assertEqual(actual[0], 0x10000007)

    def test_symbolic_external_call_before_run_is_allowed(self):
        words, relocs = fixture()
        words = [0x0C000000, 0] + words
        relocs = {offset + 8: entries for offset, entries in relocs.items()}
        relocs[0] = [('callee', 4)]
        self.assertEqual(len(fold.plan_runs(words, relocs, ADDRESSES)), 1)

    def test_symbolic_call_with_addend_is_not_extended(self):
        words, relocs = fixture()
        words += [0x0C000001, 0]
        relocs[(len(words) - 2) * 4] = [('callee', 4)]
        self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])

    def test_last_store_before_call_is_safe_but_run_cannot_cross_return(self):
        words, relocs = fixture()
        words[4] = 0x0C000000
        relocs[16] = [('callee', 4)]
        self.assertEqual(len(fold.plan_runs(words, relocs, ADDRESSES)), 1)
        words[6:6] = [HI, MOVE, STORE_A]
        relocs.update({24: [(A, 5)], 32: [(A, 6)]})
        self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])

    def test_legacy_adjacent_pair_still_folds(self):
        words, relocs = fixture(())
        self.assertEqual(fold.fold_function_words(words, relocs, ADDRESSES, None, "synthetic")[2], 1)

    def test_load_into_at_cannot_feed_later_new_pair(self):
        words, relocs = fixture()
        words[2] = 0x8C210000
        self.assertEqual(fold.plan_runs(words, relocs, ADDRESSES), [])


if __name__ == "__main__":
    unittest.main()
