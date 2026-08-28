#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004A010.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004A174.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004A2E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004A44C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004A5B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004A708.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004A858.s")

extern Gfx *D_800D0510;
extern s32 StageContext_IsHighResolution(void);
extern void func_8004A174(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8004A44C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8004A5B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4);
extern u8 D_80094E38[];
extern u8 D_80094F50[];
void func_8004AC24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    if (StageContext_IsHighResolution() != 0) {
        func_8004A174(arg0, arg1, arg2, arg3);
    } else {
        func_8004A44C(arg0, arg1, arg2, arg3);
    }
    if (arg2 >= 15 && arg3 >= 15) {
        func_8004A5B8(arg0, arg1, arg2, arg3, arg4);
    }
    gSPDisplayList(D_800D0510++, D_80094F50);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004AD00.s")

extern Gfx *D_800D0510;
extern s32 StageContext_IsHighResolution(void);
extern void func_8004A2E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8004A44C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8004A708(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4);
extern u8 D_80094E38[];
extern u8 D_80094F50[];
void func_8004AE3C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    if (StageContext_IsHighResolution() != 0) {
        func_8004A2E0(arg0, arg1, arg2, arg3);
    } else {
        func_8004A44C(arg0, arg1, arg2, arg3);
    }
    if (arg2 >= 15 && arg3 >= 15) {
        func_8004A708(arg0, arg1, arg2, arg3, arg4);
    }
    gSPDisplayList(D_800D0510++, D_80094F50);
}

extern Gfx *D_800D0510;
extern s32 StageContext_IsHighResolution(void);
extern s32 func_8004C990(s32 arg0, s32 arg1);
extern void func_8004D19C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern u8 D_80094E38[];
extern u8 D_80094F50[];
void func_8004AF18(s32 arg0, s32 arg1) {
    s32 result;
    if (StageContext_IsHighResolution() != 0) {
        result = func_8004C990(0x79, 0);
        if (result != 0) {
            gSPDisplayList(D_800D0510++, D_80094E38);
            func_8004D19C(arg0, arg1, result, 0, 0);
        }
    } else {
        result = func_8004C990(0x7A, 0);
        if (result != 0) {
            gSPDisplayList(D_800D0510++, D_80094E38);
            func_8004D19C(arg0, arg1, result, 0, 0);
        }
    }
    gSPDisplayList(D_800D0510++, D_80094F50);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004B010.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004B09C.s")

extern u8 D_80095110[];
extern void func_8004B09C(s32, s32, s32, s32, void *, s32, s32, s32, s32);
void func_8004B2CC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7) {
    func_8004B09C(arg0, arg1, arg2, arg3, D_80095110, arg4, arg5, arg6, arg7);
}

extern u8 D_80095114[];
void func_8004B314(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8004B09C(arg0, arg1, arg2, arg3, D_80095114, 0xF0, 0xD4, 0x68, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004B35C.s")
#endif
