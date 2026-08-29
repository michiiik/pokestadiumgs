#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
extern s32 D_835040D8;
extern s32 D_835040DC;
void func_83500020(s32 arg0, s32 arg1) {
    s32 pad[2];
    if (arg0 == 0) {
        D_835040DC = func_8004C990(0x136, 0);
    }
    if (arg0 == 5) {
        gDPPipeSync(D_800D0510++);
        gDPSetPrimColor(D_800D0510++, 0, 0, 0, 0, 0, 0x80);
        gDPSetCombine(D_800D0510++, 0xFFB3FF, 0xFFFCFE38);
        gSPSegment(D_800D0510++, 0xF, func_8004CA60((u8 *)D_835040DC));
        gSPDisplayList(D_800D0510++, D_835040D8);
        func_8003CD84();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500124.s")

extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_83500198(s32 arg0, void *arg1) {
    s32 pad;
    s32 v28;
    s16 v26;
    s16 v24;
    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &v28, &v26, &v24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(v26 + 0x2000);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(v24 - 0x2000);
    }
    return 0;
}

extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_83500200(s32 arg0, void *arg1) {
    s32 pad;
    s32 v28;
    s16 v26;
    s16 v24;
    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &v28, &v26, &v24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(-0x2000 - v26);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(v24 + 0x6000);
    }
    return 0;
}

s32 func_80040E80(s32, s32 *);
extern void func_80041E2C();
extern u8 D_83503BEC;
extern u8 D_83503C24;
extern u8 D_83503F30;
extern s32 D_83503F54;
extern s32 D_83503F6C;
extern u8 D_83503F70;
extern s32 MainPool_AllocState(s32, s32);
s32 main_pool_get_available(void);
extern void MainPool_FinalizeAllocation(s32);
void ModelRenderer_InitDisplayRoots(void);
void func_87F02CB0(s32 arg0, s32 arg1);
void func_8003F018(s32 arg0);
void func_8350026C(void) {
    s32 sp1C[3];
    s32 temp_v0;
    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    sp1C[0] = temp_v0;
    D_83503F54 = func_80040E80(temp_v0, &D_83503C24);
    D_83503F6C = func_80040E80(sp1C[0], &D_83503BEC);
    MainPool_FinalizeAllocation(sp1C[0]);
    ModelRenderer_InitDisplayRoots();
    func_80041E2C();
    func_87F02CB0((s32) &D_83503F30, 0x64);
    func_8003F018((s32) &D_83503F70);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500300.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500708.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500C14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_835012C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_8350182C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83501D3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83501DC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83502BFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83502EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503048.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503324.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_835034A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503548.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_835035F0.s")

extern void *D_80087200;
extern s32 D_83503BA8;
extern void func_800226C0(s32, s32);
s32 func_83503678(s32 arg0) {
    s32 result = arg0;
    if (*(s32 *)((u8 *)&D_83503BA8 + 4) == 2) {
        result = arg0 + 1;
    }
    if (((*(u16 *)((u8 *)D_80087200 + 8) & 0x8000) != 0) &&
        (*(s32 *)((u8 *)&D_83503BA8 + 0x14) == 1) &&
        (*(s32 *)((u8 *)&D_83503BA8 + 0x30) == 0xFF)) {
        *(s32 *)((u8 *)&D_83503BA8 + 0x2C) = -1;
        arg0 = result;
        func_800226C0(2, result);
        result = arg0;
        if (*(s32 *)((u8 *)&D_83503BA8 + 4) >= 2) {
            *(s32 *)((u8 *)&D_83503BA8 + 4) = 2;
            return 0x1770;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503720.s")

extern void func_83502EF0();
s32 func_83503720(s32);
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
void func_80064D28(void);
void func_835038BC(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(0x1E);
    do {
        func_80064D28();
        func_83502EF0();
        temp_v0 = func_83503720(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 5);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503918.s")
#endif
