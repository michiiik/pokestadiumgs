"""Synthetic contract tests for the separately supplied private runner backend.

Run with the backend and its dependencies available on PYTHONPATH. A public
checkout without that backend explicitly skips these tests; it does not pass
the backend contract by omission. No compiler, ROM, stats, or real source is
touched.
"""
import tempfile
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
class CompanionInstallPrefixTests(unittest.TestCase):
    def exercise(self, count, compile_status=0):
        prefix = 'struct Shared { int value; };\n'
        functions = ['func_80000000', 'func_80000004'][:count]
        baseline = ''.join('#pragma GLOBAL_ASM("asm/us/nonmatchings/test/' + f + '.s")\n' for f in functions)
        baseline += 'extern void func_80000008(void);\n'
        winners = {f: prefix + 'int ' + f + '(void) { struct Shared s; s.value = 1; return s.value; }' for f in functions}
        attempts = [{'status': 'probe_match'} for f in functions]
        timing = {}
        with tempfile.TemporaryDirectory(prefix='gs-prefix-test-') as directory:
            source = Path(directory) / 'fixture.c'
            source.write_text(baseline)

            def rebuild(path):
                installed = path.read_text()
                self.assertEqual(installed.count(prefix), 1)
                self.assertNotIn('GLOBAL_ASM', installed)
                self.assertIn('extern int func_80000008(void);', installed)
                return compile_status

            with mock.patch.object(runner, 'rebuild_source_object', side_effect=rebuild):
                kept, invalid = runner._install_incrementally(
                    source, baseline, prefix, winners, attempts,
                    {f: i for i, f in enumerate(functions)}, timing,
                    [{'function': 'func_80000008', 'old': 'extern void func_80000008(void);',
                      'new': 'extern int func_80000008(void);'}])
            self.assertFalse(invalid)
            self.assertEqual(timing['install_compiles'], 1)
            self.assertEqual(kept, winners if compile_status == 0 else {})
            if compile_status:
                self.assertEqual(source.read_text(), baseline)
                self.assertTrue(all(a['status'] == 'combined_compile_failed' for a in attempts))

    def test_one_winner_retains_shared_types(self):
        self.exercise(1)

    def test_two_winners_keep_prefix_only_once(self):
        self.exercise(2)

    def test_failed_compile_restores_baseline(self):
        self.exercise(2, 1)


if __name__ == '__main__':
    unittest.main()
