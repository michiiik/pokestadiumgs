#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004EC00.s")
#endif

#ifdef VERSION_US
extern s32 D_80128120; void func_8004EC5C(void) { if (D_80128120 > 0) { D_80128120--; } }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004EC7C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004ECD4.s")
#endif

#ifdef VERSION_US
extern void func_8004ECD4(void *, s32, s32);
void func_8004EE04(u8 *arg0, s32 arg1, s32 arg2) {
    arg1 += *(s16 *)(arg0 + 8);
    arg2 += *(s16 *)(arg0 + 10);
    func_8004ECD4(arg0, arg1, arg2);
}
#endif

#ifdef VERSION_US
void func_8004EE30(u8 *arg0, const u8 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    arg0[2] = arg1[2];
}
#endif

#ifdef VERSION_US
void func_8004EE4C(u16 *arg0, u8 *arg1)
{
  u8 r = arg1[0];
  u8 g = arg1[1];
  u8 b = arg1[2];
  g = (g >> 3) & 0x1F;
  b = (b >> 3) & 0x1F;
  r = r >> 3;
  *arg0 = (((r << 11) | (g << 6)) | (b << 1)) | 1;
}
#endif

void func_8004EE94(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004EE9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004F2D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004F64C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004FA6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004FC58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004FE00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_800501A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_80050218.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_800503A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_80050428.s")
#endif

#ifdef VERSION_US
void func_8005049C(void) { func_80050428(); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_800504BC.s")
#endif

#ifdef VERSION_US
u8 func_80050518(u8 arg0) {
    return arg0 & 0xF;
}
#endif

#ifdef VERSION_US
void func_80050528(u8 *arg0) {
    *(s16 *)(arg0 + 0) = 0;
    *(s16 *)(arg0 + 4) = 1;
    *(s32 *)(arg0 + 8) = 0;
}
#endif

#ifdef VERSION_US
void func_8005053C(void *arg0, u8 *arg1) {
    if (arg0 != NULL) {
        func_80050528(arg1);
        (*(u8 **)((u8 *)(arg0) + (0x34))) = arg1;
    }
}
#endif

#ifdef VERSION_US
void func_80050578(u8 *arg0, s32 arg1) { if (arg0 != NULL) { u8 *value = *(u8 **)(arg0 + 0x34); if (value != NULL) { *(s16 *)(value + 0) = -1; *(s16 *)(value + 2) = 0; *(s32 *)(value + 8) = arg1; } } }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_800505A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_80050640.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_800506A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_80050700.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_800507B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_80050878.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_80050994.s")
#endif

#ifdef VERSION_US
extern s32 D_801281B0;

void *GbTower_RecvExitMesg(void) {
    void *sp1C;

    osRecvMesg(D_801281B0 + 0x21E4, &sp1C, 1);
    return sp1C;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_80050B40.s")
#endif
