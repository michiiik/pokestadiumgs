"""Synthetic contracts for the separately supplied candidate-runner backend.

No compiler, ROM or probe statistics are required. Without that backend these
tests explicitly skip, matching the existing install-prefix contract tests.
"""
import unittest
from pathlib import Path
from unittest import mock

try:
    import try_pragma_compare as runner
except ModuleNotFoundError as error:
    if error.name != 'try_pragma_compare':
        raise
    runner = None


@unittest.skipIf(runner is None, 'separate runner backend is not installed')
class MismatchDiagnosticsTests(unittest.TestCase):
    def compare(self, expected, actual, size=None):
        left = b''.join(word.to_bytes(4, 'big') for word in expected)
        right = b''.join(word.to_bytes(4, 'big') for word in actual)
        def decode(data, **kwargs):
            return [runner._mips_instruction_description(int.from_bytes(data[i:i+4], 'big'))
                    for i in range(0, len(data), 4)]
        with mock.patch.object(runner, '_instruction_texts', side_effect=decode):
            return runner._function_mismatch_details(
                Path('synthetic.o'), 'synthetic', left, right,
                actual_symbol_size=len(right) if size is None else size)

    def test_four_addu_operand_swaps(self):
        result = self.compare(
            [0x00485021, 0x004B6021, 0x004D7021, 0x004FC021, 0x03E00008, 0],
            [0x01025021, 0x01626021, 0x01A27021, 0x01E2C021, 0x03E00008, 0])
        self.assertEqual(result['mismatch_kind'], 'commutative_operand_order_only')
        self.assertEqual(result['operand_order_offsets'], [0, 4, 8, 12])
        self.assertLess(result['raw_similarity_score'], 1)

    def test_whitelist_in_both_directions(self):
        for operation in (0x21, 0x2D, 0x24, 0x25, 0x26, 0x27):
            left = 0x00485000 | operation
            right = 0x01025000 | operation
            for expected, actual in ((left, right), (right, left)):
                with self.subTest(operation=operation, expected=expected):
                    result = self.compare([expected], [actual])
                    self.assertEqual(result['mismatch_kind'], 'commutative_operand_order_only')

    def test_identical_body_is_not_an_operand_mismatch(self):
        self.assertNotEqual(self.compare([0x00485021], [0x00485021]).get('mismatch_kind'),
                            'commutative_operand_order_only')

    def test_changed_destination_is_not_commutation(self):
        self.assertNotIn('operand_order_offsets', self.compare([0x00485021], [0x01025821]))

    def test_changed_source_is_not_commutation(self):
        self.assertNotIn('operand_order_offsets', self.compare([0x00485021], [0x01225021]))

    def test_noncommutative_and_side_effecting_ops_are_excluded(self):
        for operation in (0x23, 0x2B, 0x04, 0x18, 0x1A):
            with self.subTest(operation=operation):
                self.assertNotIn('operand_order_offsets', self.compare(
                    [0x00485000 | operation], [0x01025000 | operation]))

    def test_changed_immediate_elsewhere_invalidates_whole_body_label(self):
        self.assertNotIn('operand_order_offsets', self.compare(
            [0x00485021, 0x24420001], [0x01025021, 0x24420002]))

    def test_changed_opcode_elsewhere_invalidates_whole_body_label(self):
        self.assertNotIn('operand_order_offsets', self.compare(
            [0x00485021, 0x00485025], [0x01025021, 0x00485026]))

    def test_extra_word_and_truncated_symbol_are_excluded(self):
        self.assertNotIn('operand_order_offsets', self.compare([0x00485021], [0x01025021, 0]))
        self.assertNotIn('operand_order_offsets', self.compare([0x00485021], [0x01025021], size=8))

    def test_current_operand_evidence_beats_historical_register_tie(self):
        prior = [{'mismatch_kind': 'register_allocation_only', 'similarity_score': 1.0}] * 6
        attempt = dict(function='synthetic', mismatch_kind='commutative_operand_order_only')
        result = dict(attempts=[attempt])
        with mock.patch.object(runner, '_load_prior_attempt_history', return_value={'synthetic': prior}):
            runner._annotate_prior_attempts(result)
        self.assertEqual(attempt['prior_attempts'], 6)
        self.assertTrue(attempt['futility'].startswith('operand-order:'))
        self.assertEqual(result['futility_summary']['synthetic'], attempt['futility'])

    def test_real_register_tie_advice_is_preserved(self):
        prior = [{'mismatch_kind': 'register_allocation_only', 'similarity_score': 1.0}] * 6
        attempt = dict(function='synthetic', mismatch_kind='register_allocation_only')
        with mock.patch.object(runner, '_load_prior_attempt_history', return_value={'synthetic': prior}):
            runner._annotate_prior_attempts(dict(attempts=[attempt]))
        self.assertTrue(attempt['futility'].startswith('register-tie:'))


if __name__ == '__main__':
    unittest.main()
