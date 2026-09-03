#include "global.h"


#ifdef VERSION_US
void func_87E0F170(void) {
    extern u32 D_87E1EBB8;
    u8 *base = (u8 *)(u32)D_87E1EBB8;
    *(s32 *)base = 0;
    *(u16 *)(base + 6) = 0;
    base[4] = 0;
}

extern u32 D_87E1EBB8;
void func_87E0F188(s32 arg0) { u8 *base = (u8 *)(u32)D_87E1EBB8; if ((*(s32 *)base != arg0) && ((*(s8 *)(base + 4) & 1) == 0)) { *(s32 *)base = arg0; *(s16 *)(base + 6) = 0; *(u8 *)(base + 4) = 1; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E0F1C4.s")

extern void func_800279C4(s32);
void func_87E0F288(void *arg0, s32 arg1) {
    void *state = arg0;
    s32 value = *(s32 *)((u8 *)state + 0xC);
    if (((value << 3) >= 0) && ((arg1 << 3) < 0)) {
        func_800279C4(0xCF01);
        value = *(s32 *)((u8 *)state + 0xC);
    }
    if (((value << 2) >= 0) && ((arg1 << 2) < 0)) {
        func_800279C4(0xCF02);
        value = *(s32 *)((u8 *)state + 0xC);
    }
    if (((value << 1) >= 0) && ((arg1 << 1) < 0)) {
        func_800279C4(0xCF01);
        value = *(s32 *)((u8 *)state + 0xC);
    }
    *(s32 *)((u8 *)state + 0xC) = value | arg1;
    *(s32 *)((u8 *)state + 0x1C) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E0F33C.s")

extern void *D_8009491C;
extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
void func_87E0F664(s32 arg0, s32 arg1) {
    void *temp_v0;
    u8 *context;

    if (arg0 == 5) {
        context = (u8 *)D_8009491C;
        temp_v0 = *(void **)(context + 0x14);
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0xFCFFFFFF, 0xFFFCF238);
        gSPSegment(D_800D0510++, 0xF,
                   func_8004CA60((u8 *)func_8004C990(0x170, 0)));
        gSPDisplayList(D_800D0510++, *(void **)((u8 *)temp_v0 + 0x648));
        func_8003CD84();
    }
}

void func_87E0F740(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 4) = arg1;
    *(s32 *)arg0 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E0F74C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E0FBB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E0FC90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E0FDB4.s")

extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_80094F50[];
extern void func_800504BC(s16 *);
extern s32 func_8004C990(s32, s32);
extern s32 func_8004D1FC(u8 *);
extern void func_80044270(s16, s16, s16, s16, s32, s32, s32, s32, s32);
void func_87E0FFA0(void *arg0, s32 arg1) {
    s32 temp_v0;
    s32 sp40;
    s16 coords[2];

    if (arg1 != -1) {
        func_800504BC(coords);
        gSPDisplayList(D_800D0510++, D_80094E38);
        temp_v0 = func_8004C990(*(u16 *)((u8 *)arg0 + 0x24), arg1);
        sp40 = temp_v0;
        func_8004D1FC((u8 *)(u32)temp_v0);
        func_80044270((s16)(*(s16 *)((u8 *)arg0 + 8) + coords[0]),
                      (s16)(*(s16 *)((u8 *)arg0 + 0xA) + coords[1]),
                      *(s16 *)((u8 *)(u32)sp40),
                      *(s16 *)((u8 *)(u32)sp40 + 2),
                      0, 0, 0x400, 0x400, 0);
        gSPDisplayList(D_800D0510++, D_80094F50);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E10094.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E10154.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E10214.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E102D4.s")

void func_87E10500(s32 arg0, u8 *arg1) { if ((arg0 != 0) && (arg0 == 1)) { *(s16 *)(arg1 + 0x26) = *(s8 *)((u8 *)(u32)D_87E1EBB8 + 0x938); } }

void func_87E10524(void *arg0, s32 (*arg1)(s32, void *), s32 arg2) {
    void *temp_s3;
    void *var_s0;

    temp_s3 = (*(void **)((u8 *)(arg0) + (0x18)));
    var_s0 = temp_s3;
    if (temp_s3 != NULL) {
        do {
            if (arg1 != NULL) {
                arg1(arg2, var_s0);
            }
            func_87E10524(var_s0, arg1, arg2);
            var_s0 = (*(void **)((u8 *)(var_s0) + (0x14)));
        } while (var_s0 != temp_s3);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E10598.s")

extern s32 func_87E10598(s32, void *);
extern s32 func_8004C990(s32, s32);
extern s32 D_87E1A5EC[];
extern s32 D_87E1A620[];
extern s32 D_87E1A684[];
extern s32 D_87E1A6E8[];
void func_87E105FC(void *arg0, u8 arg1) {
    func_87E10524(arg0, func_87E10598, arg1);
}

extern void func_8004C8C0(s32);
void func_87E10628(void) { func_8004C8C0(0x164); func_8004C8C0(0x165); func_8004C8C0(0x171); func_8004C8C0(0x170); func_8004C8C0(0x1B5); func_8004C8C0(0x1B8); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E10670.s")

extern void func_87F02684(s32);
void func_87E1078C(void) {
    func_87F02684(D_87E1EBB8 + 712);
}

extern s32 D_87E1AA4C;
extern u8 D_87E1EBA0;
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(s32);
extern s32 func_80040E80(s32, s32 *);
extern s32 func_8004C990(s32, s32);
extern s32 func_87F08DF8(void *, f32, f32, s32);
extern void func_87F0252C(void *, void *, void *, s32);
void func_87E107B4(void *arg0) {
    void *sp20;
    s32 sp28;

    sp28 = MainPool_AllocState(main_pool_get_available(), 0);
    *(s32 *)((u8 *)arg0 + 0x90c) = func_80040E80(sp28, &D_87E1AA4C);
    MainPool_FinalizeAllocation(sp28);
    *(s32 *)((u8 *)arg0 + 0x910) = func_87F08DF8((void *)func_8004C990(0x170, 0), 0.0f, 25.0f, 0x0f000000);
    sp20 = (u8 *)arg0 + 0x2c8;
    func_87F0252C(&D_87E1EBA0, sp20, (u8 *)arg0 + 0x2dc, 4);
    *(s32 *)((u8 *)arg0 + 0x930) = 0;
    *(s32 *)((u8 *)arg0 + 0x92c) = 0;
    *(s32 *)((u8 *)arg0 + 0x928) = 0;
    *(s32 *)((u8 *)arg0 + 0x924) = 0;
    *(s32 *)((u8 *)arg0 + 0x920) = 0;
    *(s32 *)((u8 *)arg0 + 0x91c) = 0;
    *(s32 *)((u8 *)arg0 + 0x914) = 0;
    *(s32 *)((u8 *)arg0 + 0x918) = 0;
    *(s32 *)((u8 *)arg0 + 0x4a0) = (s32)sp20;
    *(s32 *)((u8 *)arg0 + 0x62c) = (s32)sp20;
    *(s32 *)((u8 *)arg0 + 0x7b8) = (s32)sp20;
    *(s32 *)((u8 *)arg0 + 0x314) = (s32)sp20;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E1087C.s")

extern void func_87F0A6C8(s32, s32, s32 *, s32 *);
extern void func_87F0AA80(s32, s32, s32 *);
s32 func_87F0AB08(s32, s32, void (*)(s32, u8 *), s32);
extern u8 D_87E1A5D0;
extern u8 D_87E1A5D4;
extern u8 D_87E1A5E4;
void func_87E1097C(s32 *arg0, s32 arg1) {
    if (arg1 == 0xE3) {
        func_87F0A6C8(*arg0, 0x44425F43, &D_87E1A5D0, &D_87E1A5D4);
        func_87F0AA80(*arg0, 0x44425F4D, &D_87E1A5E4);
        func_87F0AB08(*arg0, 0x44425F50, func_87E10500, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E109FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E10B30.s")

void func_87E10E64(s32 arg0) {
    if ((arg0 >= -1) && (arg0 < 2) && (arg0 != (*(s32 *)((u8 *)(D_87E1EBB8) + (8))))) {
        (*(s32 *)((u8 *)(D_87E1EBB8) + (8))) = arg0;
        func_87E0F170();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E10EA8.s")

void func_87E10F2C(s32 arg0) {
    if ((arg0 >= -1) && (arg0 < 4)) {
        (*(s32 *)((u8 *)(D_87E1EBB8) + (0x10))) = arg0;
    }
}

void func_87E10F50(s32 arg0) {
    if ((arg0 >= -1) && (arg0 <= 0)) {
        (*(s32 *)((u8 *)(D_87E1EBB8) + (0x14))) = arg0;
    }
}

void func_87E10F74(void *arg0, s32 arg1) {
    u32 index = ((u32)*(s32 *)((u8 *)(u32)D_87E1EBB8 + 0x2C0) % 26U) >> 1;
    *(s32 *)((u8 *)arg0 + 4) = func_8004C990(0x164, D_87E1A5EC[index]);
}

void func_87E10FD0(void *arg0, s32 arg1) {
    u32 index = ((u32)*(s32 *)((u8 *)(u32)D_87E1EBB8 + 0x2C0) % 50U) >> 1;
    *(s32 *)((u8 *)arg0 + 4) = func_8004C990(0x164, D_87E1A620[index]);
}

void func_87E1102C(void *arg0, s32 arg1) {
    u32 index = ((u32)*(s32 *)((u8 *)(u32)D_87E1EBB8 + 0x2C0) % 50U) >> 1;
    *(s32 *)((u8 *)arg0 + 4) = func_8004C990(0x165, D_87E1A684[index]);
}

void func_87E11088(void *arg0, s32 arg1) {
    u32 index = ((u32)*(s32 *)((u8 *)(u32)D_87E1EBB8 + 0x2C0) % 50U) >> 1;
    *(s32 *)((u8 *)arg0 + 4) = func_8004C990(0x165, D_87E1A6E8[index]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E110E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E11148.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E11248.s")

s32 func_80040E80(s32, s32 *);
extern u8 D_87E1AA80;
extern u8 D_87E1EBA0;
void func_87E113C8(void) {
    s32 sp1C;
    s32 temp_v0;

    func_80037E9C(0, &D_87E1EBA0);
    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    sp1C = temp_v0;
    (*(s32 *)((u8 *)(D_87E1EBB8) + (0x934))) = func_80040E80(temp_v0, &D_87E1AA80);
    MainPool_FinalizeAllocation(sp1C);
}

extern void func_8004C4B0(s32);
void func_87E1142C(void) {
    func_8004C4B0(50);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E1144C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E11534.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E1162C.s")

extern void *func_8005049C(void *, s32);
extern s32 func_8004C874(s32, s32);
extern void func_87E0F188(s32);
extern void func_87E11534(s32, s32, s32, s32, s32);
void func_87E11850(s32 arg0) {
    volatile u32 *base;
    u8 *entry;
    s32 i;
    s32 marker;
    long count;
    s32 flag;
    void *value;

    base = &D_87E1EBB8;
    func_87E11534(0x32, arg0, *base + 0x2C, 0xFF, 0xFF);
    entry = (u8 *)*base + 0x2C;
    marker = 0x50414B55;
    flag = 0xFF;
    count = 0x32;
    for (i = 0; i != 0x32; i++) {
        if ((i == arg0) && (entry[4] == flag)) {
            value = func_8005049C(*(void **)entry, marker);
            if (value != NULL) {
                func_87E0F188(func_8004C874(*(u16 *)((u8 *)value + 0x30), *(u16 *)((u8 *)value + 0x32)));
            }
        }
        entry += 8;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E11924.s")

extern void func_87E1162C(s32 *, s32 *, s32 *);
extern void func_87E11534(s32, s32, s32, s32, s32);
extern void func_87E11850(s32);
extern void func_87E11924(s32);
extern void func_87F0277C();
void func_87E119DC(void) {
    s32 sp2C;
    s32 sp24;
    s32 sp28;
    (*(s32 *)((u8 *)(u32)D_87E1EBB8 + 0x2C0))++;
    func_87E1162C(&sp2C, &sp28, &sp24);
    func_87E11534(4, sp28, D_87E1EBB8 + 0x1BC, 0xFF, 0xFF);
    func_87E11850(sp2C);
    func_87E11924(sp24);
    func_87F0277C(D_87E1EBB8 + 0x2C8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E11A5C.s")

extern void func_8003C6B8(s32);
extern void func_87E11A5C(s32, s32);
void func_87E11AB8(void) {
    func_87E11A5C(2, D_87E1EBB8 + 0x1C);
    func_87E11A5C(4, D_87E1EBB8 + 0x1BC);
    func_87E11A5C(0x32, D_87E1EBB8 + 0x2C);
    func_87E11A5C(1, D_87E1EBB8 + 0x1DC);
    func_8003C6B8((*(s32 *)((u8 *)(D_87E1EBB8) + (0x934))));
}

extern u8 D_87E1A4B0[];
extern void func_8004C54C(s32, s32);
void func_87E11B30(s32 arg0) {
    u8 *var_a1;
    u8 *temp_v0;
    *(u8 *)((u8 *)(u32)D_87E1EBB8 + 0x938) = arg0;
    temp_v0 = *(u8 **)((u8 *)(u32)D_87E1EBB8 + 0x2C4);
    if (*(u8 *)(temp_v0 + 0x2182) & (1 << arg0)) {
        var_a1 = ((u8 *)(u32)temp_v0) + (arg0 * 0x6C0) + 0x6AA;
    } else {
        var_a1 = D_87E1A4B0;
    }
    func_8004C54C(0x15, (s32)var_a1);
}

extern s32 func_8004C874(s32, s32);
extern void func_8004C54C(s32, s32);
extern s32 func_80054668(s32);
void func_87E11BA4(s32 arg0) {
    s32 sp1C;
    s32 sp18;
    switch (arg0) {
    case 0:
        sp1C = 0x39;
        sp18 = 0;
        break;
    case 1:
        sp1C = 0x38;
        sp18 = 1;
        break;
    case 2:
        sp1C = 0x37;
        sp18 = 2;
        break;
    }
    func_8004C54C(0x53, func_8004C874(0x32, sp1C));
    *(s16 *)((u8 *)(u32)D_87E1EBB8 + 0x93A) = func_80054668(sp18);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E11C38.s")

extern void *D_87F119DC;

void func_87E11CC0(void) {
    s32 (*temp_v1)();
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(D_87F119DC) + (0x38)));
    temp_v1 = (*(s32 (**)())((u8 *)(temp_v0) + (0x94)));
    (*(s32 *)((u8 *)(temp_v0) + (0x8C))) = (s32) ((*(s32 *)((u8 *)(temp_v0) + (0x8C))) + 1);
    if (temp_v1 != NULL) {
        temp_v1();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E11D00.s")

extern void func_87E11E48(s32 *, s32, s32);
extern u8 D_80126420;

void func_87E11E18(s32 arg0, s32 arg1) {
    func_87E11E48(&D_80126420, arg0, arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E11E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_312AE0/func_87E12070.s")

extern void func_87F0277C(void);
void func_87E120F8(void) {
    func_87F0277C();
}
#pragma C_FUNCTION_PADDING(8)
#endif
