"""Reproduce the companion install path losing its shared declaration prefix."""
import importlib.util
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

module_path = Path(sys.argv.pop(1)).resolve()
sys.path.insert(0, str(module_path.parent))
spec = importlib.util.spec_from_file_location('prefix_runner', module_path)
runner = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = runner
spec.loader.exec_module(runner)

class SharedPrefixTest(unittest.TestCase):
    def run_case(self, count):
        prefix = 'typedef struct { int value; } Shared;\n'
        names = ['func_a', 'func_b'][:count]
        baseline = '\n'.join('#pragma GLOBAL_ASM("asm/us/nonmatchings/test/%s.s")' % n for n in names)
        baseline += '\nextern void paired(int);\n'
        winners = {n: prefix + 'void %s(Shared *p) { p->value = 1; }' % n for n in names}
        attempts = [{'status': 'probe_match'} for _ in names]
        indices = {n: i for i, n in enumerate(names)}
        companion = [{'function': 'paired', 'old': 'extern void paired(int);', 'new': 'extern void paired(void *);'}]
        with tempfile.TemporaryDirectory(prefix='prefix-regression-') as tmp:
            source = Path(tmp) / 'test.c'
            source.write_text(baseline)
            captured = []
            def compile_fixture(path):
                text = path.read_text()
                captured.append(text)
                return 0 if text.count(prefix) == 1 else 1
            with patch.object(runner, 'rebuild_source_object', side_effect=compile_fixture):
                kept, invalid = runner._install_incrementally(source, baseline, prefix, winners, attempts, indices, {'install_compiles': 0}, companion)
            self.assertFalse(invalid)
            self.assertEqual(list(kept), names)
            self.assertEqual(len(captured), 1)
            self.assertEqual(captured[0].count(prefix), 1)
            self.assertIn('extern void paired(void *);', captured[0])
            self.assertEqual(source.read_text(), captured[0])

    def test_single_companion_winner_preserves_prefix(self):
        self.run_case(1)

    def test_two_companion_winners_deduplicate_prefix(self):
        self.run_case(2)

if __name__ == '__main__':
    unittest.main()
