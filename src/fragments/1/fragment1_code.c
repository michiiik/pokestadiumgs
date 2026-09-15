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

extern s32 D_83503BB4;
extern s16 D_83503E82;
extern void func_835012C8(void);
extern void func_83500C14(void);
extern void func_83500708(void);
extern void func_8350182C(void);

void func_83501D3C(void) {
    switch (D_83503BB4) {
        case 2:
        case 3:
        case 4:
            func_835012C8();
        case 1:
            func_83500C14();
        case 0:
            func_83500708();
    }
    if (D_83503BB4 >= 2 && D_83503E82 == 1) {
        func_8350182C();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83501DC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83502BFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83502EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503048.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503324.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_835034A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503548.s")

extern s32 D_83503BB4;
extern void func_83503048(void);
extern void func_83503188(void);
extern void func_83503324(void);
extern void func_835034A8(void);
extern void func_83503548(void);
void func_835035F0(void) {
    switch (D_83503BB4) {
        case 0:
            func_83503048();
            break;
        case 1:
            func_83503188();
            break;
        case 2:
            func_83503324();
            break;
        case 3:
            func_835034A8();
            break;
        case 4:
            func_83503548();
            break;
    }
}

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

/* func_83503720 is still GLOBAL_ASM, but its .s is hand-maintained (not the
 * splat-generated asm/us/nonmatchings/.../func_83503720.s) so that it can
 * also carry jtbl_83503E64's first 3 entries (12 bytes) in a .late_rodata
 * block ahead of its .text. Those words have to land immediately after
 * func_835035F0's own compiler-generated jump table (jtbl_83503E50) to
 * satisfy this fragment's SUBALIGN(16); a plain C global here would instead
 * be emitted by IDO BEFORE func_835035F0's switch table (IDO always emits
 * named/array rodata ahead of switch-table "late" rodata within one
 * compilation), landing at the wrong address. Placing it in a GLOBAL_ASM
 * .late_rodata block instead makes asm-processor position it correctly:
 * after all first-pass rodata and after func_835035F0's own late-rodata
 * jump table, matching retail. jtbl_83503E64's remaining entries keep
 * coming from the unmodified data blob at their real retail addresses. */
#pragma GLOBAL_ASM("hand_asm/fragments/1/func_83503720_manual.s")

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
