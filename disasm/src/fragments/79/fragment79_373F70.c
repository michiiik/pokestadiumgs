#include "global.h"


#ifdef VERSION_US
extern void func_80038894(s32, u8 *, s32, u8 *, u8 *, u8 *);
extern void func_80038F8C(u8 *, u8 *);
extern u8 D_800948DC[];
extern u8 D_800948E4[];
extern u8 D_800948D0[];
extern u8 D_84190030[];
void func_841046E0(u8 *arg0) {
    func_80038894(0, arg0, -1, D_800948D0, D_800948DC, D_800948E4);
    func_80038F8C(D_84190030, arg0);
    arg0[1] &= 0xFFFE;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_8410474C.s")

s32 func_841047A4(u8 *arg0) {
    return *(s32 *)(arg0 + 0x14);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_841047AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_84104818.s")

extern void func_84104818(u8 *);
void func_8410488C(u8 *arg0) {
    u8 *ptr = *(u8 **)(arg0 + 0xC);
    if (ptr != NULL) func_84104818(ptr);
}

extern void func_8003EB84(u8 *, s16);
void func_841048B8(u8 *arg0, s16 arg1) {
    func_8003EB84(arg0, arg1);
}

extern s32 D_8418CA20[];
extern void func_8003F114(u8 *, s32, s32, s32);
void func_841048E0(u8 *arg0, s16 arg1) {
    func_8003F114(arg0, 0, -1, D_8418CA20[arg1]);
}

extern s32 D_8418CA20[];
extern void func_8003EAFC(u8 *, s32, s32, s32);
void func_8410491C(u8 *arg0, s16 arg1) {
    func_8003EAFC(arg0, 0, D_8418CA20[arg1], 0x10000);
}

extern s32 D_8418CA20[];
extern void func_8003EAFC(u8 *, s32, s32, s32);
extern void func_8003EB84(u8 *, s16);
void func_84104958(u8 *arg0, s16 arg1) {
    func_8003EAFC(arg0, 0, D_8418CA20[arg1], 0xFFFF0000);
    func_8003EB84(arg0, (s16)(*(u16 *)(*(u8 **)(arg0 + 0x44) + 0xA) - 1));
}

void func_841049B4(u8 *arg0) { func_8003EB84(arg0, (s16)(*(u16 *)(*(u8 **)(arg0 + 0x44) + 0xA) - 1)); }

s32 func_841049E4(u8 *arg0) { s32 result = 0; if (*(s32 *)(arg0 + 0x48) == 0) { result = 1; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_84104A00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_84104D28.s")

extern u8 *func_841047AC(void);
extern void func_84105930(u8 *, f32);
extern void func_841048E0(u8 *, s16);
u8 *func_84104F54(u8 *arg0) {
    u8 *value;
    value = func_841047AC();
    if (value != NULL) {
        *(u8 **)(value + 0x14) = arg0;
        *(u8 **)(arg0 + 0xC) = value;
        func_84105930(value + 0x24, 50.0f);
        func_841048E0(value, 0x130);
    }
    return value;
}
#endif
