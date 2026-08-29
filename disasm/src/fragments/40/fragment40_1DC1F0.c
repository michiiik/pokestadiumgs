#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B00020.s")

extern void *D_88B05F60;
typedef struct {
    s16 x;
    s16 y;
    u16 w;
    u16 h;
} Func88B00288Rect;
void func_88B00288(Func88B00288Rect *arg0, Func88B00288Rect *arg1, s32 arg2) {
    f32 scale;
    f32 value;
    f32 value2;
    f32 offset;
    s32 temp;
    s32 temp2;
    scale = (f32)(3 - *(u8 *)D_88B05F60) / 3.0f;
    value = (f32)(arg1->w - 0x30) * scale;
    if (value > 0.0f) {
        offset = 0.5f;
    } else {
        offset = -0.5f;
    }
    temp = (s32)(offset + value);
    arg0->w = temp + 0x30;
    value2 = (f32)(arg1->h - 0x30) * scale;
    if (value2 > 0.0f) {
        offset = 0.5f;
    } else {
        offset = -0.5f;
    }
    temp2 = (s32)(offset + value2);
    arg0->h = temp2 + 0x30;
    arg0->x = arg1->x + (arg1->w >> 1) - (arg0->w >> 1);
    arg0->y = arg1->y + (arg1->h >> 1) - (arg0->h >> 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B003B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B00690.s")

s32 func_88B044D0(s32);
void func_88B00700(s16 *arg0) {
    u32 temp_v0;

    *arg0 = 0xA;
    if (func_88B046F0() != 0) {
        if (Credits_RandomRange(3U) == 0) {
            *arg0 = 0x34;
        }
    } else {
        temp_v0 = Credits_RandomRange(5U);
        switch (temp_v0) {                          /* irregular */
        case 0:
            if (func_88B044D0(1) != 0) {
                *arg0 = 0x32;
                return;
            }
            return;
        case 1:
            if (func_88B044D0(0) != 0) {
                *arg0 = 0x33;
            }
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B007A0.s")

typedef float S1_MtxF_t[4][4];
typedef union {
    S1_MtxF_t mf;
    struct {
        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
    };
} S1_MtxF;
void MathUtil_BuildTransformMtx_fragment40(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9,
                   f32 argA) {
    S1_MtxF sp20;

    guRotateF(sp20.mf, arg4, arg5, arg6, arg7);

    sp20.xx *= arg1;
    sp20.yx *= arg1;
    sp20.zx *= arg1;

    sp20.xy *= arg2;
    sp20.yy *= arg2;
    sp20.zy *= arg2;

    sp20.xz *= arg3;
    sp20.yz *= arg3;
    sp20.zz *= arg3;

    sp20.xw = arg8;
    sp20.yw = arg9;
    sp20.zw = argA;

    guMtxF2L(sp20.mf, arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B010A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B01438.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B01824.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B01A60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B01C54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B01FE0.s")

extern s32 func_80001FF0(void);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern void func_88B01FE0(s32);
extern f32 D_88B05E7C;
void func_88B038E8(void) {
    u16 count;
    s32 i;
    count = (u16)((f32)func_80001FF0() * D_88B05E7C / 3);
    StageFade_StartFromOpaque(count);
    if (count != 0) {
        i = 0;
        do {
            func_80064D28();
            func_88B01FE0(0);
            i++;
        } while (i != count);
    }
}

extern void func_800226C0(s32);
extern void func_80064D28(void);
extern void func_88B007A0(void);
extern void func_88B01FE0(s32);
extern void *D_88B05F60;
extern s8 D_8800EF40;
void func_88B039E4(void) {
    func_800226C0(4);
    while (*(s32 *)((u8 *)D_88B05F60 + 0x248) == 0) {
        if (D_8800EF40 == -1) {
            func_80064D28();
        }
        func_88B007A0();
        func_88B01FE0(1);
    }
}

extern s32 func_80001FF0(void);
extern void func_800225C4(s32);
extern void StageFade_StartFromTransparent(s32);
extern void func_80064D28(void);
extern void func_88B01FE0(s32);
extern f32 D_88B05E80;
void func_88B03A70(void) {
    u16 count;
    s32 i;
    count = (u16)((f32)func_80001FF0() * D_88B05E80 / 3);
    func_800225C4(count * 3);
    StageFade_StartFromTransparent(count);
    if (count != 0) {
        i = 0;
        do {
            func_80064D28();
            func_88B01FE0(2);
            i++;
        } while (i != count);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B03B78.s")

extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_8004C09C(s32);
extern s32 func_80047588(s32, s32);
extern void func_88B03B78(s32);
extern void func_80008514(s32);
extern void func_88B038E8(void);
extern void func_88B039E4(void);
extern void func_88B03A70(void);
extern void func_80008574(void);
extern void func_88B0552C(u16, s32, s32, s32);
extern void func_8005ADD8(s8, s32);
extern void Util_Free(void *);
extern void func_80047610(void);
extern void func_8004C398(void);
extern void Gfx_FreeDisplayListBuffers(void);
extern void func_80057944(u8);
extern void *D_88B05F60;
extern s32 D_88B05F68;
extern s8 D_88006868;
extern s32 D_8800687C;
s32 fragment40_main(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_a1;
    s32 temp_a2;
    void *var_s0;
    main_pool_push_state(0x47494654);
    Gfx_InitDisplayListBuffers(0x14000, 0);
    temp_s0 = func_800082E0(1, 0, 2, 0, 3, 1);
    func_8004C09C(7);
    D_8800687C = func_80047588(0x1C, 0);
    func_88B03B78(arg0);
    func_80008514(temp_s0);
    func_88B038E8();
    func_88B039E4();
    func_88B03A70();
    func_80008574();
    var_s0 = D_88B05F60;
    temp_a1 = *(s32 *)((u8 *)var_s0 + 0x460);
    if ((temp_a1 != 0) && (*(s32 *)((u8 *)var_s0 + 0x464) != 0)) {
        func_88B0552C(*(u16 *)((u8 *)var_s0 + 0x1C), temp_a1, *(s32 *)((u8 *)var_s0 + 0x464), *(s32 *)((u8 *)var_s0 + 0x468));
        var_s0 = D_88B05F60;
    } else if (D_88B05F68 != 0) {
        func_8005ADD8(D_88006868, temp_a1);
        var_s0 = D_88B05F60;
    }
    Util_Free(var_s0);
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    func_80057944((u8)arg0);
    main_pool_pop_state(0x47494654);
    return 0;
}

extern s32 strlen();
void func_88B04170(void *arg0, s8 *arg1, s32 arg2) {
    *(s32 *)((u8 *)arg0 + 0) = (s32)arg1;
    *(u8 *)((u8 *)arg0 + 4) = 0;
    *(u16 *)((u8 *)arg0 + 0x204) = 0;
    *(u16 *)((u8 *)arg0 + 0x206) = strlen(arg1);
    *(u8 *)((u8 *)arg0 + 0x208) = 3;
    *(s32 *)((u8 *)arg0 + 0x20C) = 0;
    *(s32 *)((u8 *)arg0 + 0x210) = arg2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B041C4.s")
#endif
