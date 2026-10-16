# Region notes: fragment31_1A3540

## 2026-10-17: func_88230384 accepted; fragment 31_1A3540 complete

`func_88230384` is accepted: 73 instructions / 292 bytes, frame 0x50, matching retail byte-for-byte. ROM gate passes retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
With this function, `fragment31_1A3540.c` has 0 remaining `GLOBAL_ASM` pragmas.

Allocates 0x44 bytes via `Util_Malloc`, passes `D_88234990 + 4` and callback `func_882302C0` to `func_88700364`, snapshots 16-bit returns from `func_887002F4()` and `func_8870032C()`, and passes them to `func_88004804`.
Stores the result indexed into table `D_8800ED50` (0x4C stride, matching `func_8821EB00`), updates offsets 0x10 and 0x12 of `*D_88234990`, and updates flags `D_880068B4` and `D_882346F4`.
Declaring `s16 val2 = func_8870032C()` alongside `s16 sp4A` preserves the exact 0x4A stack offset for the first return value without requiring padding or dummy variables.
