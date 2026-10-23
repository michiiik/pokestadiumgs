#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_326820/func_87F03BB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_326820/func_87F03D9C.s")

extern f32 D_87F11480;
extern f32 D_87F11484;
void func_87F03EDC(u8 *arg0, u8 *arg1) {
    switch (arg1[0xC]) {
    case 0:
        *(f32 *)(arg1 + 0x18) = D_87F11480;
        *(s16 *)(arg1 + 0x14) = 0xF;
        break;
    case 1:
        *(f32 *)(arg0 + 0x14) = *(f32 *)arg1;
        *(f32 *)(arg1 + 0x18) = D_87F11484;
        *(s16 *)(arg1 + 0x14) = 0xFF;
        break;
    }
}

extern void *func_87F025B8(void *, void *);
extern void func_80037E3C(void *, void *, void *);
extern void func_8003F1DC(void *);
extern void *func_8003F114(void *, s32, s32, s32);
extern void func_87F03D9C(void);

u8 *func_87F03F38(u8 *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    u8 *obj;
    u8 *sub;

    obj = func_87F025B8(arg0, NULL);
    if (obj != NULL) {
        func_80037E3C(obj + 0x24, func_87F03D9C, obj);
        func_8003F1DC(obj + 0x24);
        func_8003F114(obj + 0x24, 0, -1, *(s32 *)(arg0 + 0x1C));
        sub = *(u8 **)(obj + 0x20);
        *(u8 *)(obj + 0x26) |= 0x10;
        *(f32 *)(obj + 0x48) = arg2;
        *(f32 *)(obj + 0x4C) = arg3;
        *(f32 *)(obj + 0x50) = arg4;
        *(f32 *)(obj + 0x54) = arg5;
        *(f32 *)(obj + 0x58) = arg5;
        *(f32 *)(obj + 0x5C) = arg5;
        *(u8 *)(sub + 0xC) = arg1;
        *(s32 *)(sub + 0x4) = arg6;
        *(f32 *)(sub + 0x0) = arg5;
        *(s32 *)(sub + 0x10) = -1;
        *(s16 *)(sub + 0x1C) = 0;
        *(s16 *)(sub + 0x1E) = 0x80;
        func_87F03EDC(obj, sub);
    }
    return obj;
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_326820/func_87F04018.s")
#endif
