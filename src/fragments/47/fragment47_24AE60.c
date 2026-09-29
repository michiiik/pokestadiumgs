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

extern s32 func_86009C08(void *);
extern s32 func_86009C58(void *, void *);
extern s32 func_87C007DC(void *, void *);
s32 func_86004EA8(void *arg0, void *arg1)
{
    if (func_86009C08(((u8 *) arg0) + 0x66B8) != 0)
    {
        return func_86009C58(((u8 *) arg0) + 0x66B8, arg1);
    }
    if (!arg1)
    {
    }
    if (func_86009C08(((u8 *) arg0) + 0x6668) != 0)
    {
        return func_86009C58(((u8 *) arg0) + 0x6668, arg1);
    }
    return func_87C007DC(((u8 *) arg0) + 0x6848, arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86004F2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_86004FDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_8600520C.s")

typedef struct Func860053F8Record {
    u8 pad_0000[0x1814];
    s32 value;
    u8 pad_1818[0x180];
} Func860053F8Record;
s32 func_860053F8(Func860053F8Record *arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (arg0[i].value != arg0[i + 1].value) {
            return 0;
        }
    }
    return 1;
}

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

extern s32 func_87F08208(void *);
extern void func_800226C0(s32);
extern s32 StageContext_GetFadeMode(void);
extern void func_860057D0(s32, f64);
extern void func_86006318(s32 arg0);
extern void func_86006364(s32);
extern void func_86007648(s32 arg0, s32 arg1);
extern u8 D_8600DE30[];
void func_86006448(s32 arg0) {
    typedef struct { unsigned int enabled : 1; unsigned int rest : 7; } Flags;
    s32 i;

    func_86006318(arg0);
    func_86006364(arg0);
    if (StageContext_GetFadeMode() == 0) {
        switch (func_87F08208((void *)(arg0 + 0x7584))) {
            case 1:
                func_86007648(arg0, 1);
                break;
            case 2:
                ((Flags *)(arg0 + 0x75C0))->enabled = 1;
                func_800226C0(3);
                break;
        }
    }
    for (i = 0; i < *(s32 *)D_8600DE30; i++) {
        func_860057D0(arg0, *(f64 *)(arg0 + 0x6890) / *(s32 *)D_8600DE30);
    }
}

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

extern void func_860076EC(s32);
extern s32 func_860065E8(s32);
extern s32 func_87F00930(void);
extern void func_87F006BC(void);
extern void func_86005434(s32);
extern void func_80028118(s32);
extern u8 D_8600DE30[];
void func_86006774(s32 arg0) {
    s32 count;
    s32 i;
    func_860076EC(arg0);
    if ((func_860065E8(arg0) == 0) && (func_87F00930() == 0)) {
        func_87F006BC();
        *(f64 *)(arg0 + 0x6888) += *(f64 *)(arg0 + 0x6890);
        for (i = 0; i < (count = *(s32 *)D_8600DE30); i++) {
            func_86005CB4(arg0, *(f64 *)(arg0 + 0x6890) / (f64)count, 1);
        }
        func_86005434(arg0);
        if ((f64)*(s32 *)(D_8600DE30 + 0x20C) - *(f64 *)(arg0 + 0x6888) < 30.0) {
            func_80028118(4);
            *(u8 *)(arg0 + 0x75C0) = (*(u8 *)(arg0 + 0x75C0) & 0xFF) | 4;
        }
    }
}

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

extern void func_86007300(s32);
extern void func_8600734C(s32);
extern void func_86007428(s32);

void func_86007648(s32 arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x7518) = arg1;
    switch (arg1) {
        case 0:
            func_86007300(arg0);
            break;
        case 1:
            func_8600734C(arg0);
            break;
        case 2:
            func_86007428(arg0);
            break;
        case 3:
            func_860075A8((void *)arg0);
            break;
        case 4:
            func_860075E4((void *)arg0);
            break;
        case 6:
            func_86007614((void *)arg0);
            break;
        case 5:
            func_86007640((u8 *)arg0);
            break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24AE60/func_860076EC.s")
#endif
