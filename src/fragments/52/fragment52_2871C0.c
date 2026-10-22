#include "global.h"


#ifdef VERSION_US
extern void func_87F05FB0(s32, s32, s32, s32, s32);
extern s32 D_80094908;
void func_86408D00(s32 arg0, s32 arg1) {
    if (arg0 == 2) {
        func_87F05FB0(arg1 + 0x60, D_80094908 + 0x64, arg1 + 0x24, arg1 + 0x1E, arg1 + 0x30);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2871C0/func_86408D4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2871C0/func_86408F84.s")

extern s32 func_80037E3C(void *, void *, void *);
extern void func_8003F114(u8 *, s32, s32, s32);
extern void func_8003F1DC(u8 *);
extern u8 *func_87F025B8(void *, void *);
extern void func_86408D4C(void);
void func_8640912C(void *arg0, s32 arg1) {
    u8 *object;
    u8 *base;
    u8 *child;
    s32 i;

    for (i = 0; i != 3; i++) {
        object = func_87F025B8(arg0, (void *)func_86408D4C);
        if (object != NULL) {
            base = object + 0x24;
            func_80037E3C(base, (void *)func_86408D00, *(void **)(object + 0x38));
            func_8003F1DC(base);
            func_8003F114(base, 0, -1, *(s32 *)((u8 *)arg0 + 0x1364));
            child = *(u8 **)(object + 0x38);
            *(s32 *)(object + 0xC4) = -0x100;
            *(u8 *)(object + 0x26) |= 0x10;
            *(u8 *)(object + 0x41) = 0xFF;
            *(f32 *)(object + 0x5C) = 1.5f;
            *(f32 *)(object + 0x58) = 1.5f;
            *(f32 *)(object + 0x54) = 1.5f;
            *(s32 *)(child + 0x00) = i;
            *(s32 *)(child + 0x0C) = arg1;
            *(s32 *)(child + 0x04) = 0;
        }
    }
}
extern void func_87F02684(void);
void func_86409240(void) {
    func_87F02684();
}

extern void func_87F0277C(void);
void func_86409260(void) {
    func_87F0277C();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2871C0/func_86409280.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2871C0/func_86409378.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2871C0/func_864094BC.s")
#endif
