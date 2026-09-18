#!/usr/bin/env python3
"""Tests for the guarded IDO scheduler-order repair."""
from __future__ import annotations

import struct
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))

import schedule_patch  # noqa: E402


class ParserTest(unittest.TestCase):
    def test_reads_hex_and_decimal_markers(self):
        source = (
            "#pragma SWAP_FUNCTION_WORDS(func_a, 0xD0, 0xAFB80024, 0x00063403)\n"
            "#pragma SWAP_FUNCTION_WORDS(func_b, 12, 1, 2)\n"
        )
        self.assertEqual(
            schedule_patch.find_schedule_patches(source),
            {
                "func_a": (0xD0, 0xAFB80024, 0x00063403),
                "func_b": (12, 1, 2),
            },
        )

    def test_conflicting_markers_fail_closed(self):
        with self.assertRaises(schedule_patch.SchedulePatchError):
            schedule_patch.find_schedule_patches(
                "#pragma SWAP_FUNCTION_WORDS(func_a, 0, 1, 2)\n"
                "#pragma SWAP_FUNCTION_WORDS(func_a, 4, 1, 2)\n"
            )


class ObjectTest(unittest.TestCase):
    def test_swaps_words_and_preserves_object_shape(self):
        # This tiny ELF fixture is intentionally assembled by the test rather
        # than hand-constructed, so the assertion covers the real writer.
        import shutil
        import subprocess
        import tempfile

        if shutil.which("mips-linux-gnu-as") is None:
            self.skipTest("mips-linux-gnu-as is unavailable")
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "fixture.s"
            object_path = Path(directory) / "fixture.o"
            source.write_text(
                ".text\n"
                ".globl func_a\n"
                "func_a:\n"
                ".word 0x11111111\n"
                ".word 0x22222222\n"
                ".word 0x33333333\n"
                ".size func_a, .-func_a\n"
            )
            subprocess.run(
                ["mips-linux-gnu-as", "-mips2", "-o", str(object_path), str(source)],
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )
            original = object_path.read_bytes()
            patched, count = schedule_patch.swap_function_words_in_object(
                original, "func_a", 4, 0x22222222, 0x33333333
            )
            self.assertEqual(count, 1)
            self.assertNotEqual(patched, original)

            import elf32

            obj = elf32.parse(patched)
            symbol = next(s for s in obj.symbols() if s.name == "func_a")
            words = struct.unpack(">3I", obj.section(".text").data[symbol.value : symbol.value + symbol.size])
            self.assertEqual(words, (0x11111111, 0x33333333, 0x22222222))
            self.assertEqual(symbol.size, 12)
            self.assertEqual(
                obj.relocations(".rel.text"),
                elf32.parse(original).relocations(".rel.text"),
            )

    def test_expected_word_guard_rejects_wrong_shape(self):
        import shutil
        import subprocess
        import tempfile

        if shutil.which("mips-linux-gnu-as") is None:
            self.skipTest("mips-linux-gnu-as is unavailable")
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "fixture.s"
            object_path = Path(directory) / "fixture.o"
            source.write_text(
                ".text\n.globl func_a\nfunc_a:\n"
                ".word 0x11111111\n.word 0x22222222\n"
                ".size func_a, .-func_a\n"
            )
            subprocess.run(
                ["mips-linux-gnu-as", "-mips2", "-o", str(object_path), str(source)],
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )
            with self.assertRaises(schedule_patch.SchedulePatchError):
                schedule_patch.swap_function_words_in_object(
                    object_path.read_bytes(), "func_a", 0, 0xAAAAAAAA, 0xBBBBBBBB
                )

