#include "global.h"


#ifdef VERSION_US
extern void func_82902808(s32 arg0, s32 arg1);
extern s32 func_829056A4(void *arg0, void *arg1);
extern s32 func_82908A54(s32 arg0, s32 arg1);
extern void func_8290FB3C(s32 arg0, s32 arg1);
extern void func_8291199C(s32 arg0, s32 arg1);

void func_82900020(s32 arg0, s32 arg1) {
    switch (arg0) {
        case 0:
            func_82902808(arg0, arg1);
            break;
        case 1:
            func_829056A4((void *)arg0, (void *)arg1);
            break;
        case 2:
            func_82908A54(arg0, arg1);
            break;
        case 3:
            func_8290FB3C(arg0, arg1);
            break;
        case 4:
            func_8291199C(arg0, arg1);
            break;
    }
}
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_82911B00[];
extern u8 D_82911B40[];
void func_829000A0(void) { Gfx *temp_v1 = D_800D0510++; temp_v1->words.w0 = 0xDE000000; temp_v1->words.w1 = (u32)D_82911B00; }
#endif

#ifdef VERSION_US
void func_829000CC(void) { Gfx *temp_v1 = D_800D0510++; temp_v1->words.w0 = 0xDE000000; temp_v1->words.w1 = (u32)D_82911B40; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33CB20/func_829000F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33CB20/func_82900168.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33CB20/func_829001E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33CB20/func_82900254.s")
#endif

#ifdef VERSION_US
extern f32 D_829173D0;
s32 func_8290074C(f32 arg0) {
    s32 temp_v1;

    temp_v1 = (s32) arg0 & 0x1F;
    return ((temp_v1 << 0xA) + (s32) (((arg0 - (f32) temp_v1) + D_829173D0) * 1024.0f)) & 0xFFFF;
}
#endif

void func_82900798(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33CB20/func_829007A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33CB20/func_82900AFC.s")
#endif
