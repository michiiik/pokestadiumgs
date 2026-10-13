"""Regression tests for source-line-sensitive candidate deduplication."""
import unittest

from candidate_identity import candidate_identity as identity


class CandidateIdentityTests(unittest.TestCase):
    def test_call_line_split_is_distinct(self):
        a = 'void f(void) { int color; color = -1; use(&color); }'
        b = a.replace('use(', '\nuse(')
        self.assertNotEqual(identity(a), identity(b))

    def test_indentation_is_inert(self):
        self.assertEqual(identity('x = 1;\ny = 2;'), identity('  x=1;\n\t y =2;'))

    def test_blank_line_padding_is_inert(self):
        self.assertEqual(identity('x=1;\ny=2;'), identity('\n\nx=1;\n\n\ny=2;\n'))

    def test_single_line_comments_are_inert(self):
        self.assertEqual(identity('x=1;\ny=2;'), identity('x=1; // comment\ny=2;'))

    def test_block_comment_without_line_split_is_inert(self):
        self.assertEqual(identity('x=1; y=2;'), identity('x=1; /* comment */ y=2;'))

    def test_multiline_comment_can_split_a_token_group(self):
        self.assertNotEqual(identity('x=1; y=2;'), identity('x=1; /*\n*/ y=2;'))

    def test_comment_only_line_is_inert(self):
        self.assertEqual(identity('x=1;\ny=2;'), identity('x=1;\n/* comment */\ny=2;'))

    def test_literal_whitespace_is_significant(self):
        self.assertNotEqual(identity('use("a  b");'), identity('use("a b");'))

    def test_comment_markers_inside_literals_are_preserved(self):
        self.assertNotEqual(identity('use("/* one */");'), identity('use("/* two */");'))
        self.assertNotEqual(identity('use("// one");'), identity('use("// two");'))

    def test_operator_boundaries_are_significant(self):
        self.assertNotEqual(identity('x+++y;'), identity('x+ + +y;'))

    def test_logical_line_splicing(self):
        self.assertEqual(identity('x=1; y=2;'), identity('x=1; \\\ny=2;'))

    def test_token_changes_are_significant(self):
        self.assertNotEqual(identity('x=1;'), identity('x=2;'))


if __name__ == '__main__':
    unittest.main()
