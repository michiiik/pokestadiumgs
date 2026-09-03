#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F900020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F9000D0.s")

extern void func_8004972C(s32, s32, s32, s32);
extern void func_800495BC(s32, s32, s32 *);
void func_8F900200(u8 *arg0, s32 arg1) {
    s32 temp_v0;

    if (arg1 != 0) {
        func_8004972C(0xFF, 0xFF, 0, 0xFF);
    } else {
        func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
    }
    temp_v0 = *(u16 *)(arg0 + 0);
    if ((temp_v0 == 0) || (temp_v0 == 2) || (temp_v0 == 3)) {
        func_800495BC(*(u16 *)(arg0 + 2), *(u16 *)(arg0 + 4), (s32 *)(arg0 + 0x10));
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F900284.s")

extern u8 D_8F901630;
extern s32 D_8F91163C;
extern s32 D_8F911664;

void func_8F900574(void) {
    D_8F911664 = (s32) *(&D_8F901630 + D_8F91163C);
}


void func_8F900594(void) {
    *(&D_8F901630 + D_8F91163C) = (s8) D_8F911664;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F9005B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F900690.s")

extern s32 func_8F900690(void);
extern s32 func_8F9000D0(void);
extern void func_8F900594(void);
extern s32 D_8F911650[];
extern s32 D_8F911648;
s32 func_8F90083C(void) {
    s32 sp1C;
    s32 var_v0;

    sp1C = func_8F900690();
    func_8F9000D0();
    if (sp1C == 1) {
        var_v0 = D_8F911650[5];
        if (var_v0 < 0) {
            D_8F911650[5] = 0;
            var_v0 = 0;
        }
        if (var_v0 >= 0x100) {
            D_8F911650[5] = 0xFF;
        }
        func_8F900594();
        D_8F911648 = 1;
    } else if (sp1C == 2) {
        D_8F911648 = 1;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F9008D0.s")

extern u8 D_8F901630;
extern void func_8005B140(s32);
extern u8 func_8005D92C(s32);
extern s32 GbPak_WriteCommand(s32, u8 *, s32, s32);
extern void GbSave_RequirePakPresent(s32);
s32 func_8F900968(s32 arg0) {
    s32 result;

    func_8005B140(arg0);
    if (func_8005D92C(arg0) == 7) {
        result = GbPak_WriteCommand(arg0, &D_8F901630, 0, 0x10000);
    } else {
        result = GbPak_WriteCommand(arg0, &D_8F901630, 0, 0x8000);
    }
    GbSave_RequirePakPresent(arg0);
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F9009E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F900A6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F900F14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F901078.s")

extern void func_80064D28(void);
extern void func_8F900284(void);
extern s32 func_8F900F14(void);
extern s32 func_8F901078(void);
extern s32 func_8F90083C(void);
extern void func_80008648(void);
extern s32 D_8F911648;
void func_8F90132C(void) {
    s32 var_s0;
    s32 var_v0;

    var_s0 = 0;
    do {
        func_80064D28();
        func_8F900284();
        switch (D_8F911648) {
        case 0:
            var_v0 = func_8F900F14();
            goto block_8;
        case 1:
            var_v0 = func_8F901078();
            goto block_8;
        case 2:
            var_v0 = func_8F90083C();
            goto block_8;
        }
        goto block_9;
    block_8:
        var_s0 = var_v0;
    block_9:
        func_80008648();
    } while (var_s0 != 0);
}

extern void Input_SetRepeatController(s32);
extern void func_8F9008D0(s32);
extern s32 D_80087200;
extern s32 D_8F911630;
extern s32 D_8F911634;
extern s32 D_8F911638;
extern s32 D_8F911644;
extern s32 D_8F911648;
extern s32 D_8F911668;
void func_8F9013E4(s32 arg0) {
    D_8F911668 = arg0;
    D_8F911648 = 0;
    D_8F911644 = 1;
    D_8F911638 = 0;
    D_8F911630 = 0;
    D_8F911634 = 0;
    Input_SetRepeatController(D_80087200);
    func_8F9008D0(arg0);
}

extern s32 main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void func_80006CD0(s32, s32);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_80047588(s32, s32);
extern void Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern void func_8F9013E4(s32);
extern void func_80008514(s32);
extern void func_800086A4(s32);
extern void func_80007AEC(s32);
extern void func_8F90132C(void);
extern void func_80008574(void);
extern void func_80047610(void);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 D_1000000;
extern u8 D_446E30[];
extern u8 D_447D00[];
s32 func_8F901448(s32 arg0, s32 arg1) {
    s32 var_v0;

    main_pool_push_state(0x53524544);
    func_80006CD0(0x10000, 0);
    var_v0 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_80047588(0x1C, 0);
    Asset_LoadToSegment((((u32)&D_1000000) & 0x0F000000) >> 24, &D_446E30, &D_447D00, 0);
    func_8F9013E4(0);
    func_80008514(var_v0);
    func_800086A4(2);
    func_80007AEC(0x10);
    func_8F90132C();
    func_80008574();
    func_80047610();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x53524544);
    return 0;
}
#endif
