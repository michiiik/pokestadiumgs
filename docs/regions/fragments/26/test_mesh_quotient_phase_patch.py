import unittest
from collections import namedtuple
import mesh_quotient_phase_patch as patch


Record = namedtuple('Record', 'name words')


def fixture():
    result = [Record('loc', (0x51000002, n)) for n in range(160)]
    for index, name, words in [
        (142, 'lod', (0x52600000, 0, 4, 3)),
        (150, 'div', (0x1d660000, 0)),
        (151, 'str', (0x7b660000, 0, 4, 2)),
        (153, 'lod', (0x52600000, 0, 4, 4)),
        (154, 'lod', (0x52680000, 0, 4, 2)),
    ]:
        result[index] = Record(name, words)
    return result


class QuotientPhasePatchTests(unittest.TestCase):
    def test_moves_destination_under_expression_and_removes_color_copy(self):
        original = fixture()
        result = patch.transform(original)
        self.assertEqual(result[:142], [record.words for record in original[:142]])
        self.assertEqual(result[142], original[153].words)
        self.assertEqual(result[143], original[142].words)
        self.assertNotIn(original[151].words, result)
        self.assertNotIn(original[154].words, result)
        self.assertEqual(len(result), len(original) - 2)

    def test_input_remains_intact(self):
        original = fixture()
        before = list(original)
        patch.transform(original)
        self.assertEqual(original, before)

    def test_wrong_register_anchor_refused(self):
        original = fixture()
        original[151] = Record('str', (0x7b660000, 0, 4, 3))
        with self.assertRaisesRegex(ValueError, 'record 151'):
            patch.transform(original)

    def test_short_stream_refused(self):
        with self.assertRaisesRegex(ValueError, 'too short'):
            patch.transform(fixture()[:151])


if __name__ == '__main__':
    unittest.main()
