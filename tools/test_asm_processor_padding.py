"""Redistributable controls for declarative padding and rodata alignment."""
import importlib.util
import io
import os
import platform
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

import elf32

spec = importlib.util.spec_from_file_location(
    'padding_asm_processor', Path(__file__).parent / 'asm-processor' / 'asm_processor.py'
)
processor = importlib.util.module_from_spec(spec)
spec.loader.exec_module(processor)


def marker(name='_asmpp_func1', size=4):
    return processor.Function([], [], [], 0, [], 'padding fixture', {'.text': (name, size)}, size)


def fixture(count=1, prefix=0):
    names = ['', '.text', '.rodata', '.rel.text', '.rel.rodata', '.mdebug',
             '.symtab', '.strtab', '.shstrtab']
    index = {name: i for i, name in enumerate(names)}
    text = bytearray(struct.pack('>II', 0x0C000004, 0))
    symbols = [elf32.Symbol('', 0, 0, 0, 0, 0),
               elf32.Symbol('', 0, 0, 3, 0, 1),
               elf32.Symbol('before', 0, 8, 0x12, 0, 1)]
    text.extend(b'\0' * prefix)
    reserved = processor.SHORT_PADDING_RESERVE + 4
    markers = []
    for i in range(count):
        name = '_asmpp_func' + str(i + 1)
        symbols.append(elf32.Symbol(name, len(text), reserved, 0x12, 0, 1))
        markers.append(marker(name))
        text.extend(bytes.fromhex('ac000000') * (reserved // 4 - 2) + bytes.fromhex('03e00008ac000000'))
        symbols.append(elf32.Symbol('after' + str(i), len(text), 8, 0x12, 0, 1))
        text.extend(struct.pack('>II', 0x3C010000, 0x8C220000))
    tail = len(text)
    first_after = 8 + prefix + reserved
    struct.pack_into('>I', text, 0, 0x0C000000 | (first_after // 4))
    symbols.append(elf32.Symbol('tail', tail, 8, 0x12, 0, 1))
    text.extend(bytes.fromhex('03e0000800000000'))
    text.extend(b'\0' * (-len(text) % 16))
    external = len(symbols)
    symbols.append(elf32.Symbol('external', 0, 0, 0x10, 0, 0))
    strings = b'\0' + b''.join(s.name.encode() + b'\0' for s in symbols if s.name)
    shstrings = b'\0' + b''.join(name.encode() + b'\0' for name in names if name)
    reltext = [elf32.Relocation(first_after, external, 5), elf32.Relocation(first_after + 4, external, 6),
               elf32.Relocation(0, 1, 4)]  # Deliberately not sorted by offset.
    debug = bytearray(0x60)
    for st, sc, value in [(14, 1, tail), (6, 1, first_after), (2, 3, tail)]:
        debug.extend(struct.pack('>III', 0, value, (st << 26) | (sc << 21)))
    sections = [elf32.Section('', 0, 0, 0, 0, 0, 1, 0, b'')]
    sections += [
        elf32.Section('.text', 1, 6, 0, 0, 0, 16, 0, bytes(text)),
        elf32.Section('.rodata', 1, 2, 0, 0, 0, 4, 0, struct.pack('>II', first_after, tail)),
        elf32.Section('.rel.text', 9, 0, 0, index['.symtab'], 1, 4, 8,
                      b''.join(struct.pack('>II', r.offset, r.r_info()) for r in reltext)),
        elf32.Section('.rel.rodata', 9, 0, 0, index['.symtab'], 2, 4, 8,
                      struct.pack('>IIII', 0, (1 << 8) | 2, 4, (1 << 8) | 2)),
        elf32.Section('.mdebug', elf32.SHT_MIPS_DEBUG, 0, 0, 0, 0, 4, 0, bytes(debug)),
        elf32.Section('.symtab', 2, 0, 0, index['.strtab'], 2, 4, 16, b'\0' * (16 * len(symbols))),
        elf32.Section('.strtab', 3, 0, 0, 0, 0, 1, 0, strings),
        elf32.Section('.shstrtab', 3, 0, 0, 0, 0, 1, 0, shstrings),
    ]
    obj = elf32.Elf32Object(1, 8, 1, 0, 0x20001001, sections)
    obj.set_symbols(symbols)
    obj = elf32.parse(elf32.build(obj))
    debug = bytearray(obj.section('.mdebug').data)
    struct.pack_into('>II', debug, 8 * 4, 3, obj.section('.mdebug').file_offset + 0x60)
    obj.set_section_data('.mdebug', bytes(debug))
    return elf32.build(obj), markers


class LateRodataAlignmentTests(unittest.TestCase):
    def parse(self, annotation='', asm_hint='', late=True, second=False, words='1, 2', inline=False):
        opts = processor.Opts('O2', False, False, False, False, 'latin1', 'latin1', False)
        with tempfile.TemporaryDirectory(prefix='gs-rodata-alignment-') as directory:
            root = Path(directory)
            def owner(name):
                path = root / (name + '.s')
                data = ('.section .late_rodata\n' + asm_hint + 'dlabel table_' + name + '\n.word ' + words + '\n') if late else ''
                assembly = data + '.section .text\nglabel ' + name + '\n' + 'nop\n' * 10 + 'jr $ra\nnop\n'
                if inline:
                    return '#pragma GLOBAL_ASM(\n' + assembly + ')\n'
                path.write_text(assembly)
                return '#pragma GLOBAL_ASM("' + str(path) + '")\n'
            text = annotation + owner('fixture')
            if second:
                text += owner('other')
            source = io.StringIO(text)
            source.name = 'rodata-alignment-fixture.c'
            output = io.StringIO()
            functions = processor.parse_source(source, opts, [], output)
            return functions, output.getvalue()

    def test_named_alignment_matches_existing_assembly_directive(self):
        annotated, source = self.parse('#pragma asmproc late_rodata_alignment("fixture", 8)\n')
        explicit, explicit_source = self.parse('\n', asm_hint='.late_rodata_alignment 8\n')
        plain, plain_source = self.parse()
        self.assertIn('volatile double', source)
        self.assertNotIn('volatile double', plain_source)
        self.assertEqual(source, explicit_source)
        self.assertEqual(annotated[0].data, explicit[0].data)
        self.assertEqual(annotated[0].data['.text'][1], plain[0].data['.text'][1])
        self.assertEqual(annotated[0].late_rodata_dummy_bytes, explicit[0].late_rodata_dummy_bytes)

    def test_annotation_does_not_leak_to_another_owner(self):
        functions, source = self.parse('#pragma asmproc late_rodata_alignment("fixture", 8)\n', second=True)
        self.assertEqual(len(functions), 2)
        self.assertEqual(source.count('volatile double'), 1)

    def test_four_byte_offset_and_inline_annotations(self):
        annotation = '#pragma asmproc late_rodata_alignment("fixture", 4)\n'
        annotated, source = self.parse(annotation, words='1, 2, 3')
        explicit, explicit_source = self.parse('\n', asm_hint='.late_rodata_alignment 4\n', words='1, 2, 3')
        self.assertEqual(source, explicit_source)
        self.assertEqual(annotated[0].data, explicit[0].data)
        self.assertIn('volatile float', source)
        self.assertIn('volatile double', source)
        inline, _ = self.parse(annotation, words='1, 2, 3', inline=True)
        self.assertEqual(inline[0].data, annotated[0].data)

    def test_annotation_rejects_invalid_or_unconsumed_metadata(self):
        for annotation in (
            '#pragma asmproc late_rodata_alignment("fixture", 16)\n',
            '#pragma asmproc late_rodata_alignment("missing", 8)\n',
            '#pragma asmproc late_rodata_alignment("fixture", 8)\n' * 2,
        ):
            with self.subTest(annotation=annotation), self.assertRaises(processor.Failure):
                self.parse(annotation)

    def test_annotation_rejects_missing_data_and_conflicting_metadata(self):
        annotation = '#pragma asmproc late_rodata_alignment("fixture", 8)\n'
        with self.assertRaises(processor.Failure):
            self.parse(annotation, late=False)
        with self.assertRaises(processor.Failure):
            self.parse(annotation, asm_hint='.late_rodata_alignment 4\n')


class PaddingTests(unittest.TestCase):
    def test_parser_tags_only_explicit_padding(self):
        opts = processor.Opts('O2', False, False, False, False, 'latin1', 'latin1', False)
        source = io.StringIO('#pragma C_FUNCTION_PADDING(4)\n')
        source.name = 'padding-fixture.c'
        functions = processor.parse_source(source, opts, [])
        self.assertEqual(functions[0].padding_size, 4)
        self.assertEqual(functions[0].data['.text'][1], 4)
        self.assertIsNone(processor.Function([], [], [], 0, [], 'ordinary', {}).padding_size)

    def test_no_marker_and_ordinary_sizes_are_byte_inert(self):
        original, functions = fixture()
        self.assertIs(processor.normalize_padding_placeholders(original, []), original)
        self.assertIs(processor.normalize_padding_placeholders(b'not ELF', []), b'not ELF')
        self.assertEqual(processor.normalize_padding_placeholders(original, [marker(size=8)]), original)

    def test_exact_word_symbols_relocations_addends_and_mdebug(self):
        original, functions = fixture()
        before = elf32.parse(original)
        after = elf32.parse(processor.normalize_padding_placeholders(original, functions))
        syms = {s.name: s for s in after.symbols() if s.name}
        self.assertEqual((syms['_asmpp_func1'].value, syms['_asmpp_func1'].size), (8, 4))
        self.assertEqual((syms['after0'].value, syms['tail'].value), (12, 20))
        self.assertEqual(after.section('.text').data[8:12], b'\0' * 4)
        old_after = 8 + processor.SHORT_PADDING_RESERVE + 4
        self.assertEqual(after.section('.text').data[12:28], before.section('.text').data[old_after:old_after + 16])
        self.assertEqual(len(after.section('.text').data), 32)
        self.assertEqual(struct.unpack_from('>I', after.section('.text').data)[0], 0x0C000003)
        self.assertEqual([r.offset for r in after.relocations('.rel.text')], [12, 16, 0])
        self.assertEqual([r.sym_index for r in after.relocations('.rel.text')],
                         [r.sym_index for r in before.relocations('.rel.text')])
        self.assertEqual(struct.unpack('>II', after.section('.rodata').data), (12, 20))
        debug = after.section('.mdebug')
        self.assertEqual(debug.file_offset, before.section('.mdebug').file_offset)
        self.assertEqual([struct.unpack_from('>I', debug.data, 0x64 + i * 12)[0] for i in range(3)],
                         [20, 12, old_after + 8])  # Text statics/procs shift; a data static does not.

    def test_multiple_markers_use_updated_positions(self):
        original, functions = fixture(2)
        after = elf32.parse(processor.normalize_padding_placeholders(original, functions))
        syms = {s.name: s for s in after.symbols() if s.name}
        self.assertEqual((syms['_asmpp_func1'].value, syms['_asmpp_func2'].value), (8, 20))
        self.assertEqual((syms['after0'].value, syms['after1'].value, syms['tail'].value), (12, 24, 32))
        self.assertEqual(after.section('.text').data[20:24], b'\0' * 4)

    def test_section_relative_hi_lo_crosses_signed_low_carry(self):
        original, functions = fixture(prefix=0x7EF8)
        obj = elf32.parse(original)
        old_target = next(s.value for s in obj.symbols() if s.name == 'after0')
        self.assertEqual(old_target, 0x8004)
        text = bytearray(obj.section('.text').data)
        struct.pack_into('>II', text, old_target, 0x3C010001, 0x8C228004)
        obj.set_section_data('.text', bytes(text))
        relocations = obj.relocations('.rel.text')
        for relocation in relocations[:2]:
            relocation.sym_index = 1  # .text section-relative HI16/LO16.
        obj.set_relocations('.rel.text', relocations)
        after = elf32.parse(processor.normalize_padding_placeholders(elf32.build(obj), functions))
        target = old_target - processor.SHORT_PADDING_RESERVE
        self.assertEqual(target, 0x7F04)
        self.assertEqual(struct.unpack_from('>II', after.section('.text').data, target),
                         (0x3C010000, 0x8C227F04))
        self.assertEqual([r.offset for r in after.relocations('.rel.text')], [target, target + 4, 0])

    def test_ifdef_discarded_marker_is_byte_inert(self):
        original, _ = fixture()
        self.assertEqual(processor.normalize_padding_placeholders(original, [marker('_asmpp_absent')]), original)

    def test_nonempty_placeholder_fails_closed(self):
        original, functions = fixture()
        obj = elf32.parse(original)
        text = bytearray(obj.section('.text').data)
        struct.pack_into('>I', text, 8, 0x24020001)
        obj.set_section_data('.text', bytes(text))
        with self.assertRaisesRegex(processor.Failure, 'alignment-preserving'):
            processor.normalize_padding_placeholders(elf32.build(obj), functions)

    def test_wrong_extent_fails_closed(self):
        original, functions = fixture()
        obj = elf32.parse(original)
        symbols = obj.symbols()
        symbols[3].size = 12
        obj.set_symbols(symbols)
        with self.assertRaisesRegex(processor.Failure, 'alignment-preserving'):
            processor.normalize_padding_placeholders(elf32.build(obj), functions)

    def test_relocated_placeholder_fails_closed(self):
        original, functions = fixture()
        obj = elf32.parse(original)
        rels = obj.relocations('.rel.text')
        rels.append(elf32.Relocation(8, 1, 2))
        obj.set_relocations('.rel.text', rels)
        with self.assertRaisesRegex(processor.Failure, 'has relocations'):
            processor.normalize_padding_placeholders(elf32.build(obj), functions)

    def test_external_reference_into_placeholder_fails_closed(self):
        original, functions = fixture()
        obj = elf32.parse(original)
        obj.set_section_data('.rodata', struct.pack('>II', 8, 24))
        with self.assertRaisesRegex(processor.Failure, 'cannot normalize'):
            processor.normalize_padding_placeholders(elf32.build(obj), functions)

    def test_malformed_metadata_fails_closed(self):
        original, _ = fixture()
        with self.assertRaisesRegex(processor.Failure, 'metadata'):
            processor.normalize_padding_placeholders(original, [marker()._replace(data={'.text': ('before', 4)})])

    def test_malformed_debug_table_fails_closed(self):
        original, functions = fixture()
        obj = elf32.parse(original)
        debug = bytearray(obj.section('.mdebug').data)
        struct.pack_into('>I', debug, 8 * 4, 10000)
        obj.set_section_data('.mdebug', bytes(debug))
        with self.assertRaisesRegex(processor.Failure, '.mdebug symbol table'):
            processor.normalize_padding_placeholders(elf32.build(obj), functions)


class CompilerPaddingTests(unittest.TestCase):
    def test_short_marker_preserves_assembler_loop_alignment_phase(self):
        root = Path(__file__).resolve().parents[1]
        host = {'Darwin': 'macos', 'Linux': 'linux'}.get(platform.system(), 'unsupported')
        cc = root / 'tools' / 'ido' / host / '7.1' / 'cc'
        assembler = shutil.which('mips-linux-gnu-as')
        if not cc.is_file() or not assembler:
            self.skipTest('native IDO and MIPS assembler are unavailable')
        source = '''extern void tick(void);
void before_loop(void) { tick(); }
#pragma C_FUNCTION_PADDING(SIZE)
void run_loop(void) { for (;;) { tick(); } }
#pragma C_FUNCTION_PADDING(8)
'''
        env = {key: value for key, value in os.environ.items() if not key.startswith(('GIT_', 'MAKE'))}
        env['PYTHONDONTWRITEBYTECODE'] = '1'
        with tempfile.TemporaryDirectory(prefix='gs-padding-phase-') as directory:
            directory = Path(directory)
            controls = []
            for size in (processor.SHORT_PADDING_RESERVE + 4, 4):
                path, output = directory / ('input' + str(size) + '.c'), directory / ('output' + str(size) + '.o')
                path.write_text(source.replace('SIZE', str(size)))
                result = subprocess.run(
                    [sys.executable, str(root / 'tools/asm-processor/build.py'), str(cc),
                     '--', assembler, '-march=vr4300', '-mabi=32', '--',
                     '-c', '-O2', '-mips2', '-G', '0', '-non_shared', '-o', str(output), str(path)],
                    cwd=root, env=env, capture_output=True, text=True, timeout=60)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                obj = elf32.parse(output.read_bytes())
                loop = next(s for s in obj.symbols() if s.name == 'run_loop')
                controls.append((loop.value, loop.size, obj.section('.text').data[loop.value:loop.value + loop.size]))
            large, short = controls
            self.assertGreater(large[1], 0)
            self.assertEqual(large[0] - short[0], processor.SHORT_PADDING_RESERVE)
            self.assertEqual(large[1:], short[1:])

    def test_real_wrapper_static_conversion_and_linked_references(self):
        root = Path(__file__).resolve().parents[1]
        host = {'Darwin': 'macos', 'Linux': 'linux'}.get(platform.system(), 'unsupported')
        cc = root / 'tools' / 'ido' / host / '7.1' / 'cc'
        assembler, linker = shutil.which('mips-linux-gnu-as'), shutil.which('mips-linux-gnu-ld')
        if not cc.is_file() or not assembler or not linker:
            self.skipTest('native IDO and MIPS binutils are unavailable')
        source = '''extern int external_value;
static int private_data = 7;
int before_padding(int value) { return value + external_value; }
#pragma C_FUNCTION_PADDING(4)
static int after_padding(int value) { return value + external_value + private_data; }
int (*after_pointer)(int) = after_padding;
int padding_caller(int value) { return after_padding(value) + before_padding(value); }
#pragma C_FUNCTION_PADDING(4)
int after_second_padding(int value) { return value - 1; }
#pragma C_FUNCTION_PADDING(8)
'''
        env = {key: value for key, value in os.environ.items() if not key.startswith(('GIT_', 'MAKE'))}
        env['PYTHONDONTWRITEBYTECODE'] = '1'
        with tempfile.TemporaryDirectory(prefix='gs-short-padding-') as directory:
            directory = Path(directory)
            objects = []
            for label, code in [('baseline', source.replace('#pragma C_FUNCTION_PADDING(4)', '')),
                                ('padded', source)]:
                path, output = directory / (label + '.c'), directory / (label + '.o')
                path.write_text(code)
                command = [sys.executable, str(root / 'tools/asm-processor/build.py'), str(cc),
                           '--', assembler, '-march=vr4300', '-mabi=32', '--',
                           '-c', '-O2', '-mips2', '-G', '0', '-non_shared', '-o', str(output), str(path)]
                result = subprocess.run(command, cwd=root, env=env, capture_output=True, text=True, timeout=60)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                objects.append(elf32.parse(output.read_bytes()))
            before, after = objects
            original = {sym.name: sym for sym in before.symbols() if sym.name and sym.shndx != 0}
            current = {sym.name: sym for sym in after.symbols() if sym.name and sym.shndx != 0}
            for name, delta in [('before_padding', 0), ('after_padding', 4),
                                ('padding_caller', 4), ('after_second_padding', 8)]:
                self.assertEqual(current[name].value, original[name].value + delta, name)
                self.assertEqual(current[name].size, original[name].size, name)
                size = original[name].size or original['padding_caller'].value - original[name].value
                if name != 'padding_caller':
                    self.assertEqual(before.section('.text').data[original[name].value:original[name].value + size],
                                     after.section('.text').data[current[name].value:current[name].value + size], name)
            self.assertEqual(after.section('.text').data[current['after_padding'].value - 4:current['after_padding'].value], b'\0' * 4)
            self.assertEqual(after.section('.text').data[current['after_second_padding'].value - 4:current['after_second_padding'].value], b'\0' * 4)
            self.assertFalse(any(sym.name.startswith('_asmpp_') for sym in after.symbols()))
            script = directory / 'fixture.ld'
            script.write_text('external_value = 0x80100000;\nSECTIONS {\n'
                              '.text 0x80000000 : SUBALIGN(4) { *(.text) }\n'
                              '.data 0x80010000 : SUBALIGN(4) { *(.data) }\n'
                              '.rodata 0x80020000 : SUBALIGN(4) { *(.rodata) }\n'
                              '/DISCARD/ : { *(.mdebug*) *(.pdr*) *(.reginfo*) *(.MIPS*) *(.options*) *(.comment) }\n}\n')
            output = directory / 'linked.elf'
            result = subprocess.run([linker, '-EB', '-T', str(script), '--no-undefined', '-o', str(output), str(directory / 'padded.o')],
                                    cwd=root, env=env, capture_output=True, text=True, timeout=60)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            linked = elf32.parse(output.read_bytes())
            symbols = {sym.name: sym for sym in linked.symbols() if sym.name and sym.shndx != 0}
            pointer, target = symbols['after_pointer'], symbols['after_padding']
            section = linked.sections[pointer.shndx]
            self.assertEqual(struct.unpack_from('>I', section.data, pointer.value - section.addr)[0], target.value)
            caller = symbols['padding_caller']
            section = linked.sections[caller.shndx]
            words = struct.unpack('>' + 'I' * (caller.size // 4), section.data[caller.value - section.addr:caller.value - section.addr + caller.size])
            calls = {((word & 0x3FFFFFF) << 2) | ((caller.value + 4) & 0xF0000000) for word in words if word >> 26 == 3}
            self.assertEqual(calls, {target.value, symbols['before_padding'].value})


if __name__ == '__main__':
    unittest.main()
