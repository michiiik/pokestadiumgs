#include "global.h"


#ifdef VERSION_US
extern s32 D_884017E4;
s32 func_88400020(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        D_884017E4 = arg1;
    }
    return 0;
}

extern void *D_80087200;
s32 func_88400034(s32 arg0, u8 *arg1) {
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0;
    s32 result;

    result = 0;
    if (arg0 == 0) {
        var_v0 = 0x800;
        var_a0 = 0x400;
        var_a1 = 0x200;
        var_a2 = 0x100;
    } else {
        var_v0 = 8;
        var_a0 = 4;
        var_a1 = 2;
        var_a2 = 1;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 6) & var_v0) != 0) {
        result = 1;
        *(s16 *)(arg1 + 0) = *(s16 *)(arg1 + 0) + 0x400;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 6) & var_a0) != 0) {
        result = 1;
        *(s16 *)(arg1 + 0) = *(s16 *)(arg1 + 0) - 0x400;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 6) & var_a1) != 0) {
        result = 1;
        *(s16 *)(arg1 + 2) = *(s16 *)(arg1 + 2) + 0x400;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 6) & var_a2) != 0) {
        result = 1;
        *(s16 *)(arg1 + 2) = *(s16 *)(arg1 + 2) - 0x400;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/33/fragment33_code/func_8840011C.s")

extern void func_8840011C(void *);
extern void *D_884017E0;
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
void func_884001CC(u8 *arg0) {
    f32 scale;
    s16 countdown;
    s32 temp_result;
    s32 result;
    u16 flags;

    flags = *(u16 *)(arg0 + 0);
    result = 0;
    if (flags & 2) {
        temp_result = func_88400034((flags & 1) != 0, (u8 *)(u32)(*(s32 *)(arg0 + 0x1C) + 0x1E));
        result = temp_result;
        if (temp_result == 0) {
            result = 0;
        }
    }
    if (result != 0) {
        *(s16 *)(arg0 + 0xE) = 0;
        *(s16 *)(arg0 + 0xC) = *(s16 *)((u8 *)D_884017E0 + 0x48);
    } else if (*(u16 *)(arg0 + 0) & 4) {
        countdown = *(s16 *)(arg0 + 0xC);
        if (countdown > 0) {
            *(s16 *)(arg0 + 0xC) = countdown - 1;
        } else {
            func_8840011C(arg0);
        }
    }
    scale = *(f32 *)(arg0 + 0x10);
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)*(u32 *)(arg0 + 0x1C) + 0x30), scale, scale, scale);
}

extern void func_80044270(s16, s16, s16, s16, s32, s32, s32, s32, s32);
extern u8 *func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_800459AC(u8 *, u8, u8, u16, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_8800528C(s32);
void func_88400284(s32 arg0) {
    s16 var_s0;
    s16 var_s1;
    s32 var_s3;
    u8 *temp_v0;
    u8 *var_s2;

    temp_v0 = func_8004C990(0x3C, 0);
    var_s2 = func_8004CA60(temp_v0);
    var_s0 = 0;
    var_s1 = 0xD8;
    func_8800528C(arg0);
    var_s3 = 0;
    do {
        func_800459AC(var_s2, temp_v0[4], temp_v0[5], 0xA0, 0x18, 1, 0, 2, 2, 0, 0, 0, 0);
        func_80044270(0, var_s0, 0xA0, 0x18, -0x10, -0x10, 0x400, 0x400, 0);
        func_80044270(0xA0, var_s0, 0xA0, 0x18, 0x13F0, -0x10, -0x400, 0x400, 0);
        func_80044270(0, var_s1, 0xA0, 0x18, -0x10, 0x2F0, 0x400, -0x400, 0);
        func_80044270(0xA0, var_s1, 0xA0, 0x18, 0x13F0, 0x2F0, -0x400, -0x400, 0);
        var_s3 += 1;
        var_s2 += 0xF00;
        var_s0 += 0x18;
        var_s1 -= 0x18;
    } while (var_s3 != 5);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/33/fragment33_code/func_8840045C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/33/fragment33_code/func_88400610.s")

extern s32 func_80001FF0(void);
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern void func_88400610(void);
extern f32 D_884017D0;
void func_88400F48(void) {
    s32 count;
    s32 i;

    count = (u32) (((f32)func_80001FF0() * D_884017D0) / 2) & 0xFFFF;
    func_800086A4(2);
    StageFade_StartFromOpaque(count);
    i = 0;
    if (count != 0) {
        do {
            func_80064D28();
            func_88400610();
            i += 1;
        } while (i != count);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/33/fragment33_code/func_8840104C.s")

extern s32 func_80001FF0(void);
extern void func_80064D28(void);
extern void func_88400610(void);
extern void func_88600020(void *);
extern void StageFade_StartFromTransparent(s32);
extern void *D_884017E0;
extern f32 D_884017D4;
void func_88401200(void) {
    u16 count;
    s32 i;

    count = (u16)(((f32)func_80001FF0() * D_884017D4) / 2);
    *(u16 *)((u8 *)D_884017E0 + 0) = *(u16 *)((u8 *)D_884017E0 + 0) & 0xFFFB;
    *(u16 *)((u8 *)D_884017E0 + 0) = *(u16 *)((u8 *)D_884017E0 + 0) & 0xFFFD;
    *(s32 *)((u8 *)*(u32 *)((u8 *)D_884017E0 + 0x1C) + 0x4C) = 0;
    StageFade_StartFromTransparent(count);
    i = 0;
    if (count != 0) {
        do {
            func_80064D28();
            func_88400610();
            i += 1;
        } while (i != count);
    }
    if (*(s16 *)((u8 *)D_884017E0 + 0xC) < 0x78) {
        *(s16 *)((u8 *)D_884017E0 + 0xC) = *(s16 *)((u8 *)D_884017E0 + 0xC);
    } else {
        *(s16 *)((u8 *)D_884017E0 + 0xC) = 0x78;
    }
    func_88600020(D_884017E0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/33/fragment33_code/func_88401364.s")

extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_8004C09C(s32);
extern s32 func_80047588(s32, s32);
extern s32 D_8800687C;
extern void Font_EnableLineBreak(void);
extern void func_88401364(s32);
extern void func_80008514(s32);
extern void func_88400F48(void);
extern void func_8840104C(void);
extern void func_88401200(void);
extern void func_80008574(void);
extern void *D_884017E0;
extern void Util_Free(void *);
extern void func_80047610(void);
extern void func_8004C398(void);
extern void Gfx_FreeDisplayListBuffers(void);
s32 fragment33_main(s32 arg0, s32 arg1) {
    s32 sp24;

    main_pool_push_state(0x5A4F4F4D);
    Gfx_InitDisplayListBuffers(0x14000, 0);
    sp24 = func_800082E0(0, 1, 3, 1, 2, 1);
    func_8004C09C(3);
    D_8800687C = func_80047588(1, 0);
    Font_EnableLineBreak();
    func_88401364(arg1);
    func_80008514(sp24);
    func_88400F48();
    func_8840104C();
    func_88401200();
    func_80008574();
    Util_Free(D_884017E0);
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x5A4F4F4D);
    return 0;
}
#endif
