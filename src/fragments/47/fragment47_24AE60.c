#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86004840.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86004968.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_860049B8.s")

void func_86004BC4(void) {}
void func_86004BC4_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86004BD4.s")

typedef struct {
    u8 pad[0x7518];
    s32 value;
} Func86004E84State;
s32 func_86004E84(Func86004E84State *arg0) {
    s32 result;
    result = arg0->value == 2;
    if (result == 0) {
        result = arg0->value == 3;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86004EA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86004F2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86004FDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_8600520C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_860053F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86005434.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_860057D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86005A00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86005B3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86005CB4.s")

extern u16 D_800CE060[];
s32 func_860062E0(s32 arg0, u16 arg1) {
    if (D_800CE060[4] & arg1) {
        return 1;
    }
    return 0;
}
void func_860062E0_padding(void) {}

extern void func_86001AFC(s32);
void func_86006318(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s1 = arg0 + 0x75C8;
    do {
        func_86001AFC(var_s1);
        var_s0 += 0x2D8;
        var_s1 += 0x2D8;
    } while (var_s0 != 0xB60);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86006364.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86006448.s")

extern u8 D_8600DE30[];
extern void func_86006364(s32);
extern void func_860057D0(s32, f64);
extern s32 StageContext_GetFadeMode(void);
extern void func_86007648(s32, s32);
extern void func_86006318(s32 arg0);
void func_86006538(s32 arg0) {
    s32 count;
    s32 i;

    func_86006318(arg0);
    func_86006364(arg0);
    if (StageContext_GetFadeMode() == 1) {
        func_86007648(arg0, 2);
    }
    count = *(s32 *)D_8600DE30;
    i = 0;
    if (count > 0) {
        do {
            func_860057D0(arg0, *(f64 *)((u8 *)arg0 + 0x6890) / (f64)count);
            count = *(s32 *)D_8600DE30;
            i++;
        } while (i < count);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_860065E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_8600666C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86006774.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_8600688C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86006964.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86006C30.s")

extern void StageFade_StartFromOpaque(s32);
s32 StageContext_GetFadeMode();
extern void func_86007648(s32, s32);

void func_86006D24(s32 arg0) {
    if (StageContext_GetFadeMode() == 1) {
        StageFade_StartFromOpaque(0xA);
        func_86007648(arg0, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86006D64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86006F20.s")

extern void func_86001B1C(s32);
void func_86007300(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s1 = arg0 + 0x75C8;
    do {
        func_86001B1C(var_s1);
        var_s0 += 0x2D8;
        var_s1 += 0x2D8;
    } while (var_s0 != 0xB60);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_8600734C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86007428.s")

extern void func_80021ED8(s32);
extern void func_86004968();
void func_860075A8(void *arg0) {
    func_80021ED8(0x21);
    func_86004968(arg0);
    (*(u8 *)((u8 *)(arg0) + (0x75C0))) = (u8) ((*(u8 *)((u8 *)(arg0) + (0x75C0))) & 0xFFFB);
}

extern void func_87F02328();
void func_860075E4(void *arg0) {
    (*(u8 *)((u8 *)(arg0) + (0x75C0))) = (u8) ((*(u8 *)((u8 *)(arg0) + (0x75C0))) & 0xFFF7);
    func_86004968();
    func_87F02328();
}

extern void StageContext_SetClearColor(s32); extern void StageFade_StartFromTransparent(s32);
void func_86007614(void *arg0) { StageContext_SetClearColor(1); StageFade_StartFromTransparent(0xA); }

void func_86007640(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86007648.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_860076EC.s")
#endif
