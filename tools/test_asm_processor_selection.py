"""Exercise the real Makefile's source selection without a ROM or compiler."""
import os
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path


class AsmProcessorSelectionTests(unittest.TestCase):
    def test_padding_survives_removal_of_last_assembly_owner(self):
        make = shutil.which('gmake') or shutil.which('make')
        if make is None:
            self.skipTest('GNU make is not installed')
        makefile = (Path(__file__).resolve().parents[1] / 'Makefile').read_text()
        start = makefile.index('DECOMP_POKESTADIUMGS :=')
        end = makefile.index('\nrom:', start)
        selection = makefile[start:end]
        with tempfile.TemporaryDirectory(prefix='gs-asm-selection-') as directory:
            root = Path(directory)
            (root / 'src').mkdir()
            source = root / 'src' / 'fixture.c'
            rules = ('SRC_DIRS := src\nCC := compiler\nCC_OLD := old-compiler\nASM_PROC := processor\n'
                     'ASM_PROC_FLAGS :=\nAS := assembler\nASFLAGS :=\n'
                     + selection
                     + '\n.PHONY: build/src/fixture.o build/src/C890.o\n'
                     + 'build/src/fixture.o build/src/C890.o:\n\t@echo $(CC)\n')
            cases = [
                ('#pragma GLOBAL_ASM("fixture.s")\n', True),
                ('void f(void) {}\n#pragma C_FUNCTION_PADDING(28)\n', True),
                ('#pragma GLOBAL_ASM("fixture.s")\n'
                 '#pragma C_FUNCTION_PADDING(28)\n', True),
                ('void f(void) {}\n', False),
            ]
            for contents, processed in cases:
                with self.subTest(source=contents):
                    source.write_text(contents)
                    result = subprocess.run(
                        [make, '--no-print-directory', '-f', '-', 'build/src/fixture.o'],
                        input=rules, cwd=root, text=True, capture_output=True,
                        env={k: v for k, v in os.environ.items()
                             if not k.startswith(('GIT_', 'MAKE'))},
                        check=True,
                    )
                    expected = 'processor compiler -- assembler --' if processed else 'compiler'
                    self.assertEqual(result.stdout.strip(), expected)
            # The source-specific JPEG compiler rule must work for both mixed
            # ASM/C and completed all-C files, without changing other sources.
            jpeg_source = root / 'src' / 'C890.c'
            for contents in ['#pragma GLOBAL_ASM("fixture.s")\n', 'void f(void) {}\n']:
                with self.subTest(jpeg_source=contents):
                    jpeg_source.write_text(contents)
                    result = subprocess.run(
                        [make, '--no-print-directory', '-f', '-', 'build/src/C890.o'],
                        input=rules, cwd=root, text=True, capture_output=True,
                        env={k: v for k, v in os.environ.items()
                             if not k.startswith(('GIT_', 'MAKE'))},
                        check=True,
                    )
                    self.assertEqual(result.stdout.strip(), 'processor old-compiler -- assembler --')


if __name__ == '__main__':
    unittest.main()
