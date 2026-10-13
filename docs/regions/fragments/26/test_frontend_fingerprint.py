import unittest
import frontend_fingerprint as probe


class FingerprintTests(unittest.TestCase):
    def test_calibration_and_mangled_name(self):
        dump = '''00000000 <calibrated__FiT1>:
   0: afa40000 sw a0,0(sp)
   4: 03e00008 jr ra
   8: afa50004 sw a1,4(sp)
0000000c <noop_if__FiT1>:
   c: 03e00008 jr ra
  10: afa50004 sw a1,4(sp)
'''
        rows = probe.functions(dump)
        self.assertEqual([word for word, _ in rows['calibrated']], probe.CALIBRATION)
        self.assertEqual(len(rows['noop_if']), 2)

    def test_relocation_rows_are_not_instructions(self):
        rows = probe.functions('''00000000 <dense_five>:
  0: 3c010000 lui at,0
       0: R_MIPS_HI16 .rodata
  4: 01c00008 jr t6
''')
        self.assertEqual(len(rows['dense_five']), 2)
        self.assertEqual(probe.dispatch_shape(rows['dense_five']), 'table')

    def test_return_is_not_a_table_jump(self):
        self.assertEqual(probe.dispatch_shape([('03e00008', 'jr ra')]), 'chain')

    def test_changed_control_is_not_exact(self):
        result = probe.measurement('''00000000 <calibrated>:
   0: afa40000 sw a0,0(sp)
   4: 03e00008 jr ra
   8: 00000000 nop
''')
        self.assertEqual(result['calibration'], 'FAIL')
        self.assertEqual(result['status'], 'invalid_control')
        self.assertNotIn('noops', result)
        self.assertNotIn('dispatch', result)


if __name__ == '__main__':
    unittest.main()
