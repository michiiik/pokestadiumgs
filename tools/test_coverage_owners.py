"""Function coverage must not count preserved rodata as unfinished code."""
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "ci"))
import update_coverage as coverage


class CoverageOwnerTests(unittest.TestCase):
    def test_data_and_jump_tables_are_not_functions(self):
        lines = '\n'.join(
            f'HEAD:src/test.c:#pragma GLOBAL_ASM("asm/us/nonmatchings/test/{name}.s")'
            for name in ['func_80001234', 'D_80001234', 'jtbl_80001238',
                         'D_DrawFrame', 'func_80001234']
        )
        with patch.object(coverage, 'git_grep', return_value=lines):
            self.assertEqual(coverage.owners_by_file(Path('.'), 'HEAD', False),
                             {'src/test.c': {'func_80001234', 'D_DrawFrame'}})

    def test_data_only_file_does_not_create_remaining_owner(self):
        line = 'HEAD:src/constants.c:#pragma GLOBAL_ASM("asm/us/nonmatchings/constants/D_82408F00.s")'
        with patch.object(coverage, 'git_grep', return_value=line):
            self.assertEqual(coverage.owners_by_file(Path('.'), 'HEAD', False), {})

    def test_staged_input_keeps_named_functions_and_filters_lowercase_hex(self):
        lines = '\n'.join(
            f'src/test.c:#pragma GLOBAL_ASM("asm/us/nonmatchings/test/{name}.s")'
            for name in ['Gfx_DrawPanel', 'D_82408f0c', 'jtbl_82409058']
        )
        with patch.object(coverage, 'git_grep', return_value=lines):
            self.assertEqual(coverage.owners_by_file(Path('.'), 'HEAD', True),
                             {'src/test.c': {'Gfx_DrawPanel'}})


if __name__ == '__main__':
    unittest.main()
