#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000C280.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000C614.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000C6D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000C800.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000C85C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000CCF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000CDB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000CFB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D024.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D0CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D174.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D1D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D374.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D56C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D710.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D7B8.s")
#endif

#ifdef VERSION_US
void func_8000D880(u8 *arg0, s32 arg1, s32 arg2) { *(u32 *)(arg0 + 0) = ((u32)arg1 & 0x00FFFFFF) | 0x02000000; *(u32 *)(arg0 + 4) = arg2; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D8A0.s")
#endif

#ifdef VERSION_US
void func_8000D8D8(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  *((s32 *) (((u8 *) arg0) + 0)) = (s32) ((((arg1 & 0xFF) << 0x10) | 0x08000000) | (arg2 & 0xFFFF));
  *((s32 *) (((u8 *) arg0) + 4)) = (s32) ((arg3 << 0x10) | (arg4 & 0xFFFF));
  *((s32 *) (((u8 *) arg0) + 4)) = (s32) (((arg3 << 3) << 13) | (arg4 & 0xFFFF));
}
#endif

#ifdef VERSION_US
void func_8000D90C(void) {}
void func_8000D90C_padding(void) {}
#endif

#ifdef VERSION_US
void func_8000D91C(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  *((s32 *) (((u8 *) arg0) + 0)) = (s32) ((arg1 & 0xFFFFFF) | 0x0A000000);
  *((s32 *) (((u8 *) arg0) + 4)) = (s32) (((arg2 << 4) << 12) | (arg3 & 0xFFFF));
}
#endif

#ifdef VERSION_US
void func_8000D948(void) {}
void func_8000D948_padding(void) {}
void func_8000D948_padding2(void) {}
void func_8000D948_padding3(void) {}
#endif

#ifdef VERSION_US
void func_8000D968(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  *((s32 *) (((u8 *) arg0) + 0)) = (arg3 & 0xFFFF) | 0x11000000;
  *((s32 *) (((u8 *) arg0) + 4)) = (s32) (((arg1 << 8) << 8) | (arg2 & 0xFFFF));
}
#endif

#ifdef VERSION_US
void func_8000D98C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  *((s32 *) (((u8 *) arg0) + 0)) = (s32) ((((arg1 & 0xFF) << 0x10) | 0x12000000) | (arg2 & 0xFFFF));
  *((s32 *) (((u8 *) arg0) + 4)) = (s32) (((arg3 << 4) << 12) | (arg4 & 0xFFFF));
}
#endif

void func_8000D9C0(void) {
}

#ifdef VERSION_US
void func_8000D9C8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    (*(s32 *)((u8 *)(arg0) + (0))) = (s32) ((((arg2 >> 4) & 0xFF) << 0x10) | 0x14000000 | (arg1 & 0xFFFF));
    (*(s32 *)((u8 *)(arg0) + (4))) = arg3;
}
#endif

void func_8000D9F0(void) {
}

#ifdef VERSION_US
void func_8000D9F8(void *arg0, s32 arg1, s32 arg2)
{
  u8 *new_var;
  new_var = (u8 *) arg0;
  *((s32 *) (new_var + 0)) = 0x16000000;
 do { *((s32 *) (((u8 *) arg0) + 4)) = (s32) (((arg1 << 7) << 9) | (arg2 & 0xFFFF)); } while (0);
}
#endif

#ifdef VERSION_US
void func_8000DA14(void) {}
void func_8000DA14_padding(void) {}
void func_8000DA14_padding2(void) {}
#endif

#ifdef VERSION_US
void func_8000DA2C(u8 *arg0, s32 arg1, s32 arg2) { *(u32 *)(arg0 + 0) = 0x17000000 | (((u32)arg1 & 0xFF) << 16); *(u32 *)(arg0 + 4) = arg2; }
#endif

#ifdef VERSION_US
void func_8000DA48(u32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0[0] = ((arg1 & 0xFF) << 16) | 0x0E000000 | (arg4 & 0xFFFF);
    arg0[1] = ((arg2 & 0xFFFF) << 16) | (arg3 & 0xFFFF);
}
#endif

#ifdef VERSION_US
void func_8000DA7C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  u8 *p = arg0;
  *((u32 *) (p + 0x00)) = ((arg4 & 0xFF) << 16) | (arg3 & 0xFFFF);
  *((u32 *) (p + 0x04)) = ((arg1 << 14) << 2) | (arg2 & 0xFFFF);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DAA8.s")
#endif

#ifdef VERSION_US
void func_8000DAE8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) { *(u32 *)(arg0 + 0) = 0x07000000 | (((u32)arg1 & 0xFF) << 16) | ((u32)arg2 & 0xFFFF); *(u32 *)(arg0 + 4) = arg3; }
#endif

#ifdef VERSION_US
void func_8000DB0C(u8 *arg0, s32 arg1, s32 arg2) { *(u32 *)(arg0 + 0) = 0x07020000 | ((u32)arg1 & 0xFFFF); *(u32 *)(arg0 + 4) = arg2; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DB24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DBD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DC7C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DDC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DE34.s")
#endif

void func_8000DEA0(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DEA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DEE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DF5C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000E13C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000E1E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000E750.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000F4E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000F794.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000F834.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000FCF0.s")
#endif
