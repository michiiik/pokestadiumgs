#include "global.h"


#ifdef VERSION_US
typedef struct { u16 unk00; u8 unk02; u8 unk03; u8 unk04; } Frag41_Input;
typedef struct {
    u8 pad00[0x20];
    u16 unk20;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u16 unk26;
} Frag41_State;
extern void *D_80087200;
extern void Input_SetRepeatController(void *);
extern Frag41_State *D_88C01A60;
void func_88C00020(Frag41_Input *arg0) {
    D_88C01A60->unk20 = arg0->unk00;
    D_88C01A60->unk22 = arg0->unk02;
    D_88C01A60->unk23 = arg0->unk03;
    D_88C01A60->unk24 = arg0->unk04;
    D_88C01A60->unk26 = 0;
    Input_SetRepeatController(D_80087200);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/41/fragment41_code/func_88C00084.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/41/fragment41_code/func_88C006B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/41/fragment41_code/func_88C00AB0.s")

typedef float Frag41_MtxF_t[4][4];
typedef union {
    Frag41_MtxF_t mf;
    struct {
        f32 xx, yx, zx, wx;
        f32 xy, yy, zy, wy;
        f32 xz, yz, zz, wz;
        f32 xw, yw, zw, ww;
    };
} Frag41_MtxF;

void MathUtil_BuildTransformMtx_fragment41(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA) {
    Frag41_MtxF sp20;

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/41/fragment41_code/func_88C00CE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/41/fragment41_code/func_88C0107C.s")

extern s32 func_80001FF0(void);
extern void func_80007AEC(s32);
extern void func_80064D28(void);
extern void func_88C0107C(s32);
extern f32 D_88C01A50;
void func_88C01398(void) {
    u16 count;
    s32 i;
    count = (u16)((f32)func_80001FF0() * D_88C01A50 / 2);
    func_80007AEC(count);
    if (count != 0) {
        i = 0;
        do {
            func_80064D28();
            func_88C0107C(0);
            i++;
        } while (i != count);
    }
}

extern s32 func_88C00084(void);

void func_88C01494(void) {
    s32 done;

    do {
        func_80064D28();
        done = func_88C00084();
        func_88C0107C(1);
    } while (done == 0);
}

extern void func_800225C4(s32);
extern void StageFade_StartFromTransparent(s32);
extern f32 D_88C01A54;
void func_88C014D8(void) {
    u16 count;
    s32 i;
    count = (u16)((f32)func_80001FF0() * D_88C01A54 / 2);
    func_800225C4(count * 2);
    StageFade_StartFromTransparent(count);
    if (count != 0) {
        i = 0;
        do {
            func_80064D28();
            func_88C0107C(2);
            i++;
        } while (i != count);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/41/fragment41_code/func_88C015DC.s")

extern void func_80006CD0(s32, s32);
s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_80008514(s32);
extern void func_80008574();
extern void func_88C015DC();
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
s32 fragment41_main(s32 arg0, s32 arg1) {
    s32 sp24;

    main_pool_push_state(0x434C4544);
    func_80006CD0(0x10000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(3);
    func_80047588(0x18, 0);
    func_88C015DC();
    func_80008514(sp24);
    func_88C01398();
    func_88C01494();
    func_88C014D8();
    func_80008574();
    Util_Free((s32) D_88C01A60);
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    func_80057944(0U);
    main_pool_pop_state(0x434C4544);
    return 0;
}
#endif
