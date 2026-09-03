#include "global.h"


#ifdef VERSION_US
extern u8 D_82D06F80;
void func_82D00020(u8 arg0) {
    D_82D06F80 = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D00030.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D000A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D00108.s")

extern s32 func_82D00030(u8 *, u8);
s32 func_82D00158(u8 *arg0) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 1; i != 0xFC; i++) {
        if (func_82D00030(arg0, i) != 0) {
            count++;
        }
    }
    return count & 0xFFFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D001C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D002CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D0034C.s")

extern u8 D_82D23938;
extern u8 D_82D2393C[];
extern u8 *func_8006218C(s32, s32, s32, s32);
extern void func_8006249C(void *, s32, u8 *);
extern void func_80062304(u8 *);
void func_82D00444(void) {
    u8 *sp1C;

    sp1C = func_8006218C(0x18, 0, 0, 1);
    func_8006249C(D_82D2393C, D_82D23938, sp1C);
    func_80062304(sp1C);
}
void func_82D00444_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D0049C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D00590.s")

extern u8 D_82D07428[];
void func_82D00590(u8);
void func_82D06B34(s32, s32, s32);
void func_82D006B8(void) {
    D_82D07428[0x10E] = 0;
    D_82D07428[0xE] = 0;
    *(u16 *)(D_82D07428 + 4) = 0;
    func_82D00590(D_82D07428[0x10] = 1);
    func_82D06B34(9, 1, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D00704.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D00784.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D007CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D0087C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D00BB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D00C34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D010F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D0125C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D01590.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D0183C.s")

extern u8 D_82D07420[];
extern s8 D_82D07421;
extern u8 D_82D2382A;
extern u8 D_82D23830;
extern u8 D_82D23D84;
extern void func_800226C0(s32);
extern void func_82D06B34(s32, s32, s32);
void func_82D019D8(void) {
    s8 var_v0;

    D_82D23830 = 1;
    D_82D07420[0] = 1;
    D_82D23D84 = 7;
    var_v0 = D_82D07420[1];
    if (var_v0 != 0) {
        func_82D06B34(2, 2, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 1) {
        func_82D06B34(3, 2, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 2) {
        func_82D06B34(4, 2, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 3) {
        func_82D06B34(5, 2, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 4) {
        func_82D06B34(6, 2, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D01AAC.s")

extern void func_82D06B34(s32, s32, s32);
void func_82D01D68(void) {
    s8 var_v0;

    D_82D23830 = 0;
    D_82D2382A = 0x17;
    D_82D07420[0] = 0;
    D_82D23D84 = 1;
    var_v0 = D_82D07420[1];
    if (var_v0 != 0) {
        func_82D06B34(2, 1, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 1) {
        func_82D06B34(3, 1, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 2) {
        func_82D06B34(4, 1, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 3) {
        func_82D06B34(5, 1, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 4) {
        func_82D06B34(6, 1, 0);
    }
    func_800226C0(3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D01E4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D01EB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D0201C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D0213C.s")

extern s8 D_82D23833;
extern u16 D_82D23D88;
extern void func_82D001C0(s8 *, s32, s32, s32);
extern void func_82D0213C(void);
extern void func_800226C0(s32);
void func_82D022D0(void) {
    func_82D001C0(&D_82D23833, 0, ((((u8 *)&D_82D23830)[7] - 1) & 0xFF), ((u8 *)&D_82D23830)[1]);
    if (D_82D23D88 & 0xC000) {
        if (D_82D23D88 & 0x8000) {
            func_82D0213C();
            *(s8 *)((u8 *)&D_82D23830 + 1) = *(s8 *)((u8 *)&D_82D23830 + 3);
            func_800226C0(0x44);
        } else {
            func_800226C0(3);
        }
        D_82D23D84 = 7;
        ((u8 *)&D_82D23830)[0] = 1;
        D_82D2382A = 0x1D;
    }
}

extern u16 D_82D23D88; extern u8 D_82D2382A; extern u8 D_82D23D84; void func_82D02380(void) { if (D_82D23D88 != 0) { D_82D2382A = 0x17; D_82D23D84 = 1; } }

extern void func_82D06B34(s32, s32, s32);

void func_82D023AC(void) {
    if (D_82D23D88 != 0) {
        D_82D23D84 = 4;
        func_82D06B34(0xA, 7, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D023EC.s")

extern void func_82D001C0(s8 *, s32, s32, s32);
extern void func_82D023EC();
extern s8 D_82D07421;
void func_82D0265C(void) {
    func_82D001C0(&D_82D07421, 0, 4, 0xFF);
    if (D_82D23D88 & 0x8000) {
        func_82D023EC();
        return;
    }
    if (D_82D23D88 & 0x4000) {
        D_82D07421 = 4;
        func_82D023EC();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D026C4.s")

extern void *D_80087200;
extern u16 D_82D23D86;
extern u16 D_82D23D8A;
void func_80064D28(void);
void func_82D027D4(void) {
    func_80064D28();
    if (D_82D06F80 != 0) {
        D_82D23D86 = (*(u16 *)((u8 *)(D_80087200) + (6)));
        D_82D23D88 = (*(u16 *)((u8 *)(D_80087200) + (8)));
        D_82D23D8A = (*(u16 *)((u8 *)(D_80087200) + (0xC)));
        return;
    }
    D_82D23D86 = 0;
    D_82D23D88 = 0;
    D_82D23D8A = 0;
}

extern void func_80008648();
extern void func_800088DC();
extern void func_82D026C4();
extern void func_82D027D4();
extern void func_82D05C90();
extern void func_82D068A0();
void func_82D0284C(void) {
    do {
        func_82D027D4();
        func_82D026C4();
        func_82D068A0();
        func_800088DC();
        func_82D05C90();
        func_80008648();
    } while (D_82D23D84 != 0xD);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D028B8.s")

extern u8 D_82D23B60[];
extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void func_82D028B8(void);
extern void func_82D06D50(void);
extern void func_80008624(void);
extern void StageLoader_WaitForRetrace(void);
extern s32 _bcmp(const void *, const void *, s32);
extern void func_82D0284C(void);
s32 func_82D029EC(s32 arg0, s32 arg1) {
    main_pool_push_state(0x524C4544);
    func_82D028B8();
    func_82D06D50();
    func_80008624();
    func_82D0284C();
    StageLoader_WaitForRetrace();
    main_pool_pop_state(0x524C4544);
    return _bcmp(&D_82D23938, D_82D23B60, 0x224) != 0;
}
#pragma C_FUNCTION_PADDING(8)
#endif
