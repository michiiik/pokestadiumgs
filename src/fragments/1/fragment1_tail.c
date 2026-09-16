#include "global.h"

#ifdef VERSION_US
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

/* Keep jtbl_83503E64's first three words in the late-rodata block so the
 * compiler-generated jtbl_83503E50 precedes them at the retail boundary. */
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_tail/func_83503918.s")
#endif
