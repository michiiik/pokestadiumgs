#include "global.h"


#ifdef VERSION_US
extern void func_80051D64(s32, s32);
extern void func_8005493C(u16 *);
extern void func_80054974(u16 *);
extern void func_80054E48(s32);
extern void func_80055948(s32);
void func_87E07BD0(void) {
    u16 sp18[4];

    func_80055948(3);
    func_8005493C(&sp18[0]);
    sp18[0] |= 4;
    func_80054974(&sp18[0]);
    func_80051D64(0x14, 0);
    func_80054E48(3);
}

extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void func_80055948(s32);
extern void func_8005493C(u16 *);
extern void func_80054974(u16 *);
extern void func_80051D64(s32, s32);
extern void func_80054E48(s32);
void func_87E07C20(s32 arg0) {
    u16 sp18[4];

    main_pool_push_state(0x4D475346);
    func_80055948(3);
    func_8005493C(&sp18[0]);
    sp18[0] |= arg0;
    func_80054974(&sp18[0]);
    func_80051D64(0x14, 0);
    func_80054E48(3);
    main_pool_pop_state(0x4D475346);
}

extern void func_87E07C20(s32);
void func_87E07C90(void) {
    func_87E07C20(2);
}

void func_87E07CB0(void) {
    func_87E07C20(1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E07CD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E07DD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E07E08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E07E38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E07ED8.s")

s32 func_87E07E38();
extern void func_87F0F1C0(s32, s32);

void func_87E07F18(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_87E07E38();
    if (temp_v0 != -1) {
        func_87F0F1C0(arg0, temp_v0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E07F4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E07F98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E0808C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E080F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E08168.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E081A0.s")

extern void func_87E080F8(s32);
extern void func_87E01628(void);
extern void main_pool_pop_state(s32);
void func_87E082E4(void *arg0, s32 arg1) {
    *(s32 *)((u8 *)arg0 + 0) = arg1;
    if (arg1 != 1) {
        if ((arg1 == 2) || (arg1 == 3)) {
            func_87E080F8(*(s32 *)((u8 *)arg0 + 0x20) + 0x2188);
            *(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x21F0) = 0;
            func_87E01628();
            main_pool_pop_state(0x4D47434D);
        }
    } else {
        *(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x21F0) = 1;
    }
}

extern s32 func_8005DED8(s32);
extern s32 func_80060368(s32);
extern void func_80060538(s32, s32);
s32 func_87E0835C(void *arg0, s32 arg1) {
    s32 sp1C = 0;
    s32 var_a1;
    if (func_8005DED8(arg1) != 0) {
        sp1C = 1;
        var_a1 = func_80060368(arg1);
        var_a1 += *(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x2188);
        var_a1 &= 0xFFFF;
        if (var_a1 >= 0x2710) {
            var_a1 = 0x270F;
        }
        func_80060538(arg1, var_a1);
    }
    return sp1C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E083CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E08564.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E085CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E087B0.s")

extern void func_87E01628();
extern void func_87E0AC6C(s32);
extern void main_pool_pop_state(s32);

void func_87E08810(s32 arg0) {
    func_87E0AC6C(arg0 + 0x24);
    func_87E01628();
    main_pool_pop_state(0x434D5456);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E08844.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E088E0.s")

extern void func_87E0C628(s32, s32);
extern void func_87E0DAE0(s32, s32);
extern void func_87E12674(s32, s32);
extern void func_87E14FF4(s32, s32);
extern void func_87E179F4(s32, s32);
extern void func_87F0D48C(s32, s32, s32);
void func_87E08B14(s32 arg0) {
    main_pool_push_state(0x434D4C42);
    func_87E0C628(arg0 + 0x60, *(s32 *)((u8 *)arg0 + 0x20));
    func_87E0DAE0(arg0 + 0x8C, *(s32 *)((u8 *)arg0 + 0x20));
    func_87E12674(arg0 + 0x628, *(s32 *)((u8 *)arg0 + 0x20));
    func_87E14FF4(arg0 + 0x644, *(s32 *)((u8 *)arg0 + 0x20));
    func_87E179F4(arg0 + 0x7BC, *(s32 *)((u8 *)arg0 + 0x20));
    func_87F0D48C(arg0 + 0x1970, *(s32 *)((u8 *)arg0 + 0x20), 0);
}

extern void func_87E0BE28(s32);
extern void func_87E0CD84(s32);
extern void func_87E12D28(s32);
extern void func_87E1532C(s32);
void func_87E08B90(s32 arg0) {
    func_87E0BE28(arg0 + 0x60);
    func_87E0CD84(arg0 + 0x8C);
    func_87E12D28(arg0 + 0x628);
    func_87E1532C(arg0 + 0x644);
    func_87E01628();
    main_pool_pop_state(0x434D4C42);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E08BEC.s")

extern s32 func_87E0B0EC(s32);
extern void func_87E08810(s32);
extern void func_87E08B14(s32);
extern void func_87E08844(s32, s32);
extern void func_87E015C0(s32);
extern void func_80021ED8(s32);
extern void func_87E082E4(void *, s32);
void func_87E08CD8(s32 arg0) {
    s32 sp24;
    s32 temp_v0;

    temp_v0 = func_87E0B0EC(arg0 + 0x24);
    sp24 = temp_v0;
    if (temp_v0 != 2) {
        func_87E08810(arg0);
        if (sp24 != 0) {
            if (sp24 == 1) {
                func_87E08B14(arg0);
                func_87E08844(arg0, 1);
                func_87E015C0(1);
                func_80021ED8(0x4D);
            }
        } else {
            func_87E082E4((void *)arg0, 2);
            func_87E015C0(0);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E08D70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E08E8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E08EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E094C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E09514.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E09654.s")

s32 func_87E07ED8(s32);
extern void func_87E08E8C(void *, s32, s32);

void func_87E09BDC(void *arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_a1;

    temp_v0 = func_87E07ED8((*(s32 *)((u8 *)(arg0) + (0x20))));
    var_a1 = temp_v0;
    if (temp_v0 == -1) {
        var_a1 = 0;
    }
    func_87E08E8C(arg0, var_a1, arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E09C20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E09F20.s")

extern s32 func_87E07ED8(s32);
extern void func_87E14F98(s32);
extern void func_87F0F3E4(s32);
extern void func_87E10EA8(s32);
extern void func_87E10F2C(s32);
extern s32 func_87E15698(s32);
extern s32 func_87F0F2B8(s32, s32);
extern void func_87E10F50(s32);
extern void func_87F0F390(s32);

void func_87E0A1B8(s32 arg0) {
    s32 sp2C;
    s32 sp28 = 1;
    s32 sp24;

    sp2C = func_87E07ED8(*(s32 *)((u8 *)(u32)arg0 + 0x20));
    sp24 = arg0 + 0x644;
    func_87E14F98(sp24);
    if (*(s32 *)((u8 *)(u32)arg0 + 0x7B8) == 0x1E) {
        func_87F0F3E4(*(s32 *)((u8 *)(u32)arg0 + 0x20));
        if (((*(u32 *)((u8 *)(u32)*(s32 *)((u8 *)(u32)arg0 + 0x20) +
                       (sp2C * 0x6C0) + 0x6B8)) >> 31) != 0) {
            func_87E10EA8(0x30);
            func_87E10F2C(0);
        }
    }
    if ((u32)*(s32 *)((u8 *)(u32)arg0 + 0x7B8) >= 0x1F) {
        *(s32 *)((u8 *)(u32)arg0 + 0x7B8) = 0x1E;
        if (func_87E15698(sp24) == 5) {
            if ((sp2C >= 0) && (sp2C < 4)) {
                sp28 = func_87F0F2B8(*(s32 *)((u8 *)(u32)arg0 + 0x20), sp2C);
            }
            if (sp28 != 0) {
                *(s32 *)((u8 *)(u32)arg0 + 0x7B8) = 0;
                *(s32 *)((u8 *)(u32)arg0 + 4) = 7;
                func_87E10F50(0);
                func_87E10EA8(0x29);
                func_87E10F2C(0);
                func_87F0F390(*(s32 *)((u8 *)(u32)arg0 + 0x20));
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E0A2D4.s")

extern void func_87E082E4(void *, s32);
u8 StageContext_GetFadeMode(void);
extern void StageFade_StartFromOpaque(s32);
void func_87E0A5BC(void *arg0) {
    if (StageContext_GetFadeMode() == 1) {
        if ((u32) (*(u32 *)((u8 *)(arg0) + (0x7B8))) >= 6U) {
            func_87E08B90((s32) arg0);
            func_87E082E4(arg0, 3);
            StageFade_StartFromOpaque(0xF);
        }
    } else {
        (*(u32 *)((u8 *)(arg0) + (0x7B8))) = 0U;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E0A620.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E0A724.s")

extern void func_87E079FC(s32);
extern void func_87E00590(void);
void func_87E0A7A0(s32 arg0) {
    func_87E079FC(arg0 + 0x498);
    func_87E00590();
}

extern void func_87E0C8DC(s32);
extern void func_87E0F124(s32);

void func_87E0A7C8(s32 arg0) {
    func_87E0C8DC(arg0 + 0x60);
    func_87E0F124(arg0 + 0x8C);
    func_87E00590();
}

extern void WidgetTree_OpenMessagePanel_fragment63(s32);

void func_87E0A800(s32 arg0) {
    func_87E0F124(arg0 + 0x8C);
    func_87E00590();
    WidgetTree_OpenMessagePanel_fragment63(arg0 + 0x644);
}


void func_87E0A838(s32 arg0) {
    func_87E0F124(arg0 + 0x8C);
    func_87E00590();
    WidgetTree_OpenMessagePanel_fragment63(arg0 + 0x644);
}


void func_87E0A870(s32 arg0) {
    func_87E0F124(arg0 + 0x8C);
    func_87E00590();
    WidgetTree_OpenMessagePanel_fragment63(arg0 + 0x644);
}


void func_87E0A8A8(s32 arg0) {
    func_87E0F124(arg0 + 0x8C);
    func_87E00590();
    WidgetTree_OpenMessagePanel_fragment63(arg0 + 0x644);
}


void func_87E0A8E0(s32 arg0) {
    func_87E0F124(arg0 + 0x8C);
    func_87E00590();
    WidgetTree_OpenMessagePanel_fragment63(arg0 + 0x644);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30B540/func_87E0A918.s")
#endif
