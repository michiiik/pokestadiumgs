#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F001CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00460.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00580.s")

extern void func_800226C0(s32);
void func_82F005F8(void *arg0, s32 arg1) {
    if (arg1 == 1) {
        *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 0;
        func_800226C0(0x14);
        return;
    }
    if (arg1 != 0) {
        *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 1;
        func_800226C0(3);
    }
}

extern void func_800226C0(s32);

void func_82F00644(void *arg0, s32 arg1) {
    if (arg1 != 0) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 1;
        func_800226C0(3);
    }
}


void func_82F00670(void *arg0, s32 arg1) {
    if (arg1 != 0) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 1;
        func_800226C0(3);
    }
}


void func_82F0069C(void *arg0, s32 arg1) {
    if (arg1 != 0) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 1;
        func_800226C0(3);
    }
}


void func_82F006C8(void *arg0, s32 arg1) {
    if (arg1 != 0) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 6;
        func_800226C0(3);
    }
}

void func_82F006F4(void *arg0) {
    (*(s8 **)((u8 *)arg0 + 0xEF4))[0x244] =
        *(s8 *)((u8 *)arg0 - ((s32)0 - (s32)*(u8 *)((u8 *)arg0 + 0xECE)) + 0xEEB);
    (*(s8 **)((u8 *)arg0 + 0xEF4))[0x245] =
        *(u8 *)((u8 *)arg0 + 0xED0) - 1;
    (*(s8 **)((u8 *)arg0 + 0xEF4))[0x246] =
        *(u8 *)((u8 *)arg0 - ((s32)0 - (s32)*(u8 *)((u8 *)arg0 + 0xECF)) + 0xED0);
}

extern void func_82F006F4(void *);
void func_82F00730(void *arg0, s32 arg1) {
    if (arg1 == 1) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 0;
        func_800226C0(0x11);
        func_82F006F4(arg0);
        return;
    }
    if (arg1 != 0) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 6;
        func_800226C0(3);
    }
}

void func_82F00788(void *arg0) {
    (*(s8 **)((u8 *)arg0 + 0xEF4))[0x244] =
        *(s8 *)((u8 *)arg0 - ((s32)0 - (s32)*(u8 *)((u8 *)arg0 + 0xECE)) + 0xEEB);
    (*(s8 **)((u8 *)arg0 + 0xEF4))[0x245] = -1;
    (*(s8 **)((u8 *)arg0 + 0xEF4))[0x246] =
        *(u8 *)((u8 *)arg0 - ((s32)0 - (s32)*(u8 *)((u8 *)arg0 + 0xECF)) + 0xED0);
}

extern void func_82F00788(void *);
void func_82F007C0(void *arg0, s32 arg1) {
    if (arg1 == 1) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 0;
        func_800226C0(0x11);
        func_82F00788(arg0);
        return;
    }
    if (arg1 != 0) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 5;
        func_800226C0(3);
    }
}

extern u8 D_800D0510[];
extern void func_80007444(void *, s32, s32, s32, s32, s32);
void func_82F00818(s32 arg0, s32 arg1, s32 arg2) {
    func_80007444(D_800D0510, 0, 0, 0x280, 0x1E0, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00860.s")

extern void func_800226C0(s32);
void func_82F00A3C(void *arg0, s32 arg1) {
    if (arg1 < 0) {
        *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 10;
        func_800226C0(3);
        return;
    }
    if (arg1 != 0) {
        if (*(u8 *)((u8 *)(u32)arg0 + arg1 * 0x58 - 0x20) > 0) {
            if (*(s8 *)((u8 *)(u32)arg0 + arg1 + 0xEEB) < 0) {
                *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 4;
                func_800226C0(5);
            } else if (*(s32 *)((u8 *)(u32)arg0 + 0xEE8) != 0) {
                *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 3;
                func_800226C0(5);
            } else if (*(u8 *)((u8 *)(u32)arg0 + 0xED1) != 0) {
                *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 5;
                func_800226C0(0x90);
            } else {
                *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 2;
                func_800226C0(5);
            }
        } else {
            func_800226C0(5);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00B28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00C2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F01220.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F012AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F01658.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F01958.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F019CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F01A5C.s")

extern void _bzero(void *, s32);
extern s32 func_82F01A5C(void *);
extern void func_81804954(void *, s32, s32, void *, s32);
extern u8 D_82F03100[];
s32 func_82F01BAC(void *arg0, s32 arg1, void *arg2) {
    _bzero(arg0, 0xEF8);
    *(s32 *)((u8 *)(u32)arg0 + 0xEF4) = (s32)arg2;
    *(s8 *)((u8 *)(u32)arg2 + 0x244) = -1;
    if (func_82F01A5C(arg0) == 0) {
        return 0;
    }
    func_81804954(
        arg0,
        *(u8 *)((u8 *)(u32)*(s32 *)((u8 *)(u32)arg0 + 0xEF4) + 0x240),
        0xB,
        D_82F03100,
        arg1);
    *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 1;
    return 1;
}

extern void func_8180132C(s32);
s32 func_81801388(s32, s32);
extern void func_81804FD0(u8 *);
s32 func_82F00460(u8 *);
extern void func_82F00580(u8 *);
extern u8 D_82F02B28;
extern u8 D_82F02F48;
extern u8 D_82F0305C;
extern u8 D_82F030CC;
void func_80064D28(void);
extern u8 D_82F032C0;
void func_81600AF0(s32 arg0, s32 arg1, s32 arg2);
extern void Gfx_InitDisplayListBuffers(s32, s32);
s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_80008514(s32);
extern void func_8004C8C0(s32);
extern u8 D_446E30;
extern u8 D_82F031C8;
u8 *Asset_LoadToSegment(s32 id, u8 *rom_start, u8 *rom_end, s32 arg3);
extern u8 D_1000000[];
extern u8 D_447D00[];
extern void func_8004C09C(s32 arg0);
s32 func_8004C4B0(s32 value);
void WidgetTree_OpenMessagePanel_fragment4(u8 *arg0);
void func_81801F60(u8 *arg0);
extern s32 func_80047588(s32 arg0, s32 arg1);
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
void func_81801794(void);
extern void func_80021ED8(s32);
s32 func_81801388(s32, s32);
s32 func_82F00460(u8 *);
void func_80064D28(void);
void func_81600AF0(s32 arg0, s32 arg1, s32 arg2);
s32 func_82F01C34(s32 arg0) {
    func_80064D28();
    func_81804FD0(&D_82F032C0);
    if (func_82F00460(&D_82F032C0) != 0) {
        func_81600AF0((*(s32 *)((u8 *)(&D_82F032C0) + (4))), (s32) &D_82F02B28, 1);
        func_81600AF0((*(s32 *)((u8 *)(&D_82F032C0) + (4))), (s32) &D_82F02F48, 1);
    }
    if ((*(u8 *)((u8 *)(&D_82F032C0) + (0xECF))) != (*(u8 *)((u8 *)(&D_82F032C0) + (0xEE0)))) {
        (*(u8 *)((u8 *)(&D_82F032C0) + (0xEE0))) = (u8) (*(u8 *)((u8 *)(&D_82F032C0) + (0xECF)));
        func_81600AF0((*(s32 *)((u8 *)(&D_82F032C0) + (4))), (s32) &D_82F0305C, 1);
    }
    if ((*(u8 *)((u8 *)(&D_82F032C0) + (0xED0))) != (*(u8 *)((u8 *)(&D_82F032C0) + (0xEE1)))) {
        (*(u8 *)((u8 *)(&D_82F032C0) + (0xEE1))) = (u8) (*(u8 *)((u8 *)(&D_82F032C0) + (0xED0)));
        func_81600AF0((*(s32 *)((u8 *)(&D_82F032C0) + (4))), (s32) &D_82F030CC, 1);
    }
    func_82F00580(&D_82F032C0);
    if (((*(u8 *)((u8 *)(&D_82F032C0) + (0x1D))) == 0) && ((*(u8 *)((u8 *)(&D_82F032C0) + (0x1C))) == 0) && ((*(u8 *)((u8 *)(&D_82F032C0) + (0x1E))) == 0)) {
        if (func_81801388(0x10, 1) != 0) {
            arg0 = 1;
        }
    } else {
        func_8180132C(0x10);
    }
    return arg0;
}

extern void func_80008648();
extern void func_800088DC();
extern void func_818017A8();
extern void func_81805308(s32 *);

void func_82F01D38(s32 arg0) {
    func_800088DC();
    func_818017A8();
    func_81805308(&D_82F032C0);
    func_80008648();
}

s32 func_82F01C34(s32);
void func_82F01D74(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    do {
        temp_v0 = func_82F01C34(var_s0);
        var_s0 = temp_v0;
        func_82F01D38(temp_v0);
    } while (var_s0 != 1);
}

s32 func_800082E0(s32, s32, s32, s32, s32, s32);
u8 *Asset_LoadToSegment(s32 id, u8 *rom_start, u8 *rom_end, s32 arg3);
s32 func_8004C4B0(s32 value);
void WidgetTree_OpenMessagePanel_fragment4(u8 *arg0);
void func_81801F60(u8 *arg0);
void func_81801794(void);
void func_82F01DC4(s32 arg0, s32 arg1) {
    s32 sp24;

    Asset_LoadToSegment((s32) ((u32) ((s32) D_1000000 & 0x0F000000) >> 0x18), &D_446E30, D_447D00, 0);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(0x10F);
    func_8004C8C0(0x14C);
    func_8004C4B0(0x49);
    func_8004C4B0(6);
    func_8004C4B0(7);
    func_8004C4B0(0xC);
    func_8004C4B0(0xD);
    WidgetTree_OpenMessagePanel_fragment4(&D_82F032C0);
    func_81801F60(&D_82F031C8);
    func_80047588(0xC, 0);
    func_80008514(sp24);
    func_800086A4(2);
    StageFade_StartFromOpaque(1);
    func_81801794();
    func_80021ED8(0x5E);
}

extern void Gfx_FreeDisplayListBuffers();
extern void func_80008574();
extern void func_80047610();
extern void func_8004C398();

void func_82F01EC8(s32 arg0, s32 arg1) {
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
}

extern void main_pool_push_state(s32);
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern void *func_81600E28(s32, s32, s32);
extern void MainPool_FinalizeAllocation(s32);
extern s32 func_82F01BAC(void *, s32, void *);
extern void func_82F01DC4(s32, s32);
extern void func_82F01D74(s32, s32);
extern void func_82F01EC8(s32, s32);
extern void main_pool_pop_state(s32);
extern u8 D_82F032C0;
s32 fragment8_main(s32 arg0, s32 arg1) {
    s32 state;
    s32 result;
    main_pool_push_state(0x544D434E);
    state = MainPool_AllocState(main_pool_get_available(), 0);
    result = func_81600E28(state, 1, 0xF);
    MainPool_FinalizeAllocation(state);
    if (func_82F01BAC(&D_82F032C0, result, arg1) != 0) {
        func_82F01DC4(arg0, arg1);
        func_82F01D74(arg0, arg1);
        func_82F01EC8(arg0, arg1);
    }
    main_pool_pop_state(0x544D434E);
    return 0;
}
#endif
