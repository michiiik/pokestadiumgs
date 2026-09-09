import tempfile
import unittest
from pathlib import Path

from tools.ensure_fragment_hooks import apply


BODY = """#include \"recomp.h\"\nRECOMP_FUNC void func_800024A0(uint8_t* rdram, recomp_context* ctx) {\nL_800024A0:\n    // body\nL_800024FC:\n    // 0x800024FC: jr $ra\n}\nRECOMP_FUNC void func_80042968(uint8_t* rdram, recomp_context* ctx) {\nL_80042968:\n    // body\n}\nRECOMP_FUNC void func_841120AC(uint8_t* rdram, recomp_context* ctx) {\nL_841120AC:\n    ctx->r8 = 0;\n    ctx->r2 = MEM_HU(ctx->r8, 0XA);\nL_84112148:\n    // epilogue\n}\n"""


class EnsureFragmentHooksTests(unittest.TestCase):
    def test_inserts_pair_and_is_idempotent(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            owner = root / "funcs_1.c"
            owner.write_text(BODY, encoding="utf-8")

            self.assertTrue(apply(root))
            patched = owner.read_text(encoding="utf-8")
            self.assertEqual(patched.count("librecomp_fragment_input_push"), 1)
            self.assertEqual(patched.count("librecomp_fragment_resolve_exit"), 1)
            self.assertEqual(patched.count("MEM_BU(ctx->r4, 0) == 1"), 1)
            self.assertEqual(patched.count("if (ctx->r2 == 0)"), 1)
            self.assertFalse(apply(root))
            self.assertEqual(owner.read_text(encoding="utf-8"), patched)


if __name__ == "__main__":
    unittest.main()
