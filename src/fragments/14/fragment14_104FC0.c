#include "global.h"


#ifdef VERSION_US
s32 func_8130CE30(u8 *arg0) {
    return *(s32 *)(arg0 + 0x5C) != 0;
}

extern s32 func_81601FA0(u8);
extern s32 func_81601980(s32 *, s32);
extern void func_81601D24(void *, u8, void *, void *);
extern f32 func_816092FC(void);
extern s32 func_8130CE30(u8 *);
s32 func_8130CE3C(u8 *arg0) {
    s32 result;
    u8 selector;
    if (arg0[0x35] == 1) {
        return 0;
    }
    selector = arg0[0x39];
    if (selector == 0) {
        return 0;
    }
    result = func_81601FA0(selector) == 0;
    if (result == 0) {
        result = func_81601980((s32 *)(arg0 + 0x3C), arg0[0x39]) != 0;
    }
    return result;
}

extern s32 func_81601FA0(u8);
extern s32 func_81601980(s32 *, s32);
extern void func_81601D24(void *, u8, void *, void *);
extern f32 func_816092FC(void);
extern s32 func_8130CE30(u8 *);
s32 func_8130CEAC(u8 *arg0) {
    s32 result;
    if ((arg0[0x35] == 1) || (func_8130CE30(arg0) == 0)) {
        result = 2;
    } else {
        result = 3;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130CEF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130D098.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130D1FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130D340.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130D45C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130D4E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130D6A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130DA04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130DEB8.s")

extern u8 D_813120B4[];
extern s32 func_80042D54(u8 *, u16);
void func_8130E99C(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3) {
    u16 color;
    arg0[0x34] = 0;
    arg0[0x37] = 0;
    *(s32 *)(arg0 + 0x60) = 0;
    *(s32 *)(arg0 + 0x5C) = arg1;
    *(s32 *)(arg0 + 0x24) = 0;
    *(s32 *)(arg0 + 0x64) = arg2;
    *(u8 **)(arg0 + 0x68) = arg3;
    *(s32 *)(arg0 + 0x6C) = 0;
    *(u16 *)(arg0 + 0x12) = 0;
    *(u16 *)(arg0 + 0x10) = 0;
    *(u16 *)(arg0 + 0x0C) = 0x2F;
    *(u16 *)(arg0 + 0x0E) = 0xFF;
    *(u16 *)(arg0 + 0x08) = 0x2F;
    *(u16 *)(arg0 + 0x0A) = 0xFF;
    *(s32 *)(arg0 + 0x00) = 0;
    *(s32 *)(arg0 + 0x70) = 0;
    *(f32 *)(arg0 + 0x28) = 0.0f;
    *(f32 *)(arg0 + 0x30) = 0.0f;
    *(f32 *)(arg0 + 0x2C) = 1.0f;
    *(u16 *)arg3 &= 0xFFFD;
    *(u16 *)(*(u8 **)(arg0 + 0x68)) &= 0xFFFB;
    *(u16 *)(*(u8 **)(arg0 + 0x68)) |= 0x100;
    color = (((D_813120B4[2] >> 2) & 0x3E) |
             (((D_813120B4[1] * 8) & 0x7C0) |
              ((D_813120B4[0] << 8) & 0xF800)) | 1) & 0xFFFF;
    func_80042D54(*(u8 **)(arg0 + 0x68), color);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130EA8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130EB04.s")

void func_8130EC94(u8 *arg0) {
    *(u32 *)(arg0 + 0x6C) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130EC9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130EF88.s")

extern f32 func_816092FC(void);
extern s32 func_8130CE30(u8 *arg0);
void func_8130F09C(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 0x2C) += step;
    if (*(f32 *)(arg0 + 0x2C) >= 1.0f) {
        *(f32 *)(arg0 + 0x2C) = 1.0f;
        arg0[0x34] = 1;
        *(s8 *)(arg0 + 0x38) = -1;
    }
}

extern s16 func_81306B0C(void *);
extern void func_800226C0(s32);
void func_8130F0FC(u8 *arg0) {
    s32 status;
    void *target;
    target = *(void **)(arg0 + 0x5C);
    if (target != NULL) {
        status = func_81306B0C(target);
        if (status != -1) {
            if (status == -2) {
                *(u8 *)(arg0 + 0x34) = 1;
            }
            if (status >= 0) {
                *(u8 *)(arg0 + 0x36) = 0;
                *(s8 *)(arg0 + 0x39) = status;
                *(u8 *)(arg0 + 0x34) = 3;
                *(f32 *)(arg0 + 0x2C) = 1.0f;
                func_800226C0(*(s32 *)(arg0 + 0x04));
            }
        }
    } else {
        *(u8 *)(arg0 + 0x34) = 3;
    }
}

extern f32 func_816092FC(void);
void func_8130F184(u8 *arg0) {
    s32 sp18;
    s32 speed;
    speed = ((arg0[0x34] == 3) && (*(s8 *)(arg0 + 0x36) == 0)) ? 0x32 : 1;
    sp18 = speed;
    *(f32 *)(arg0 + 0x2C) = *(f32 *)(arg0 + 0x2C) - (func_816092FC() * (f32)speed);
    if (*(f32 *)(arg0 + 0x2C) <= 0.0f) {
        arg0[0x34] = 0;
        *(f32 *)(arg0 + 0x2C) = 0.0f;
        *(s8 *)(arg0 + 0x38) = -1;
    }
}

void func_8130F218(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 0x30) += step;
    if (*(f32 *)(arg0 + 0x30) >= 12.0f) {
        *(f32 *)(arg0 + 0x30) = 12.0f;
        arg0[0x34] = 6;
    }
}

void func_8130F270(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 0x30) -= step;
    if (*(f32 *)(arg0 + 0x30) <= 0.0f) {
        arg0[0x34] = 1;
        *(f32 *)(arg0 + 0x30) = 0.0f;
    }
}

/* func_8130F2C4 is still GLOBAL_ASM, but its .s is hand-maintained (not the
 * splat-generated asm/us/nonmatchings/.../func_8130F2C4.s) so that it can
 * also carry jtbl_81312840's last 3 entries (12 bytes) in a .late_rodata
 * block ahead of its .text. Those words have to land immediately before
 * func_8130F5AC's own compiler-generated jump table (jtbl_8131285C) to
 * satisfy this fragment's SUBALIGN(16); a plain C global here would instead
 * be emitted by IDO before func_8130F2C4's own late-rodata (which isn't
 * used here) but, more importantly, can't be positioned relative to a
 * *later* function's late rodata at all. Placing it in a GLOBAL_ASM
 * .late_rodata block instead makes asm-processor position it correctly:
 * after all earlier rodata and immediately before func_8130F5AC's own
 * late-rodata jump table, matching retail. jtbl_81312840's first 4 entries
 * keep coming from the unmodified data blob at their real retail address. */
#pragma GLOBAL_ASM("hand_asm/fragments/14/func_8130F2C4_manual.s")

s16 func_8130F578(u8 *arg0, s32 *arg1) {
    s16 result = 0;
    if (arg1 != NULL) {
        *arg1 = arg0[0x39];
    }
    if (arg0[0x34] == 0) {
        result = *(s8 *)(arg0 + 0x36) + 1;
    }
    return result;
}

extern void func_81306E90(u8 *arg0);
void func_8130F5AC(u8 *arg0) {
    u8 *target;
    switch (arg0[0x34]) {
        case 4:
            target = *(u8 **)(arg0 + 0x5C);
            if (target != NULL) {
                func_81306E90(target);
            }
        case 5:
        case 6:
        case 7:
            *(f32 *)(arg0 + 0x30) = 0.0f;
        case 1:
            *(f32 *)(arg0 + 0x2C) = 1.0f;
        case 2:
        case 3:
            arg0[0x34] = 3;
        case 0:
        default:
            break;
    }
}
#endif
