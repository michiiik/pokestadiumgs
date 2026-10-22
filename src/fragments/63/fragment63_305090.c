#include "global.h"


#ifdef VERSION_US
extern s32 func_8004C990(s32, s32);
void func_87E01720(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    u32 index;

    index = ((u32)arg0 % ((u32)arg1 * (u32)arg2)) / (u32)arg1;
    func_8004C990(arg3, ((u8 *)arg4)[index]);
}

extern u8 D_87E19720[];
extern void func_87E01720(s32, s32, s32, s32, void *);
void func_87E01798(s32 arg0) {
    func_87E01720(arg0, 4, 4, 0x1A6, D_87E19720);
}

extern u8 D_87E19724[];
void func_87E017CC(s32 arg0) {
    func_87E01720(arg0, 3, 8, 0x1A7, D_87E19724);
}

extern u8 D_87E1972C[];
void func_87E01800(s32 arg0) {
    func_87E01720(arg0, 3, 6, 0x1A4, D_87E1972C);
}

extern u8 D_87E19734[];
void func_87E01834(s32 arg0) {
    func_87E01720(arg0, 3, 8, 0x1A5, D_87E19734);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E01868.s")

/* mkdraft:func_87E01A5C begin */
extern Gfx *D_800D0510;
extern void *D_8009491C;
extern void func_8003CD84(void);
typedef struct { u8 pad_60[0x60]; u8 red; u8 green; u8 blue; } Func87E0375CColor;

void func_87E01A5C(s32 arg0, s32 arg1) {
    u8 *context;
    Func87E0375CColor *temp_a0;
    void *temp_a1;
    if (arg0 == 5) {
        context = (u8 *)D_8009491C;
        temp_a0 = *(Func87E0375CColor **)(context + 0x14);
        temp_a1 = *(void **)((u8 *)temp_a0 + 0x20);
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0x50FFFF, -0xDC8);
        gDPSetEnvColor(D_800D0510++, temp_a0->red, temp_a0->green,
                       temp_a0->blue, 0xFF);
        gSPSegment(D_800D0510++, 0xF,
                   *(void **)((u8 *)(*(void **)((u8 *)temp_a1 + 0xC)) + 8));
        gSPDisplayList(D_800D0510++, *(void **)((u8 *)temp_a1 + 8));
        func_8003CD84();
    }}
/* mkdraft:func_87E01A5C end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E01B50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E01DB4.s")

typedef struct { u8 pad_00[0x2180]; u8 mode; } F1E24ObjB;
typedef struct { u8 pad_00[4]; s32 value; u8 pad_08[0x278]; F1E24ObjB *obj; s8 out_284; s8 out_285; } F1E24StateB;
void func_87E01E24(F1E24StateB *arg0) {
    s32 value;
    switch (arg0->obj->mode) {
        case 0: arg0->value = 0; break;
        case 1: arg0->value = 1; break;
        case 2: arg0->value = 2; break;
        case 3: arg0->value = 3; break;
    }
    value = arg0->value;
    arg0->out_284 = value % 2;
    arg0->out_285 = value / 2;
}

extern void func_87E01E24();
extern void func_87E01B50();
extern void func_87E134C0();
extern void func_87E13490();
extern void func_87E13480();
extern void func_87E0168C();
void func_87E01EB0(void *arg0) {
    *(s32 *)arg0 = 0;
    func_87E01E24(arg0);
    func_87E01B50(arg0);
    func_87E134C0();
    func_87E13490();
    func_87E13480(1);
    func_87E0168C(3, 0x8C, 0x2D);
}

void func_87E01F04(u8 *arg0) {}

s32 func_87E01F0C(u32 arg0) {
    u8 *entry = (u8 *)arg0 + 0x1C;
    s32 result = 1;
    s32 index;
    arg0 = 4;
    index = 0;
    do {
        index++;
        if (*(s32 *)(entry + 0x94) != 0) {
            result = 0;
            break;
        }
        entry += 0x98;
    } while (index != arg0);
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E01F44.s")

extern u8 D_87E1979C[];
extern void func_87E10E64(s32);
extern void func_87E10EA8(s32);
extern void func_87E10F2C(s32);
void func_87E02150(s32 *arg0) {
    s32 *entry = (s32 *)(D_87E1979C + arg0[1] * 0xC);

    if (arg0[0] == 2) {
        func_87E10EA8(-1);
        func_87E10F2C(-1);
    } else {
        func_87E10E64(entry[0]);
        func_87E10EA8(entry[1]);
        func_87E10F2C(entry[2]);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E021CC.s")

extern void func_8004C8C0(s32);
void func_87E02438(void) {
    func_8004C8C0(0x1A4);
    func_8004C8C0(0x1A5);
    func_8004C8C0(0x1A6);
    func_8004C8C0(0x1A7);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E02470.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E02538.s")

extern void func_87E02538(void);
extern void BgStage_DrawFrame(void);
void func_87E0276C(void) {
    func_87E02538();
    BgStage_DrawFrame();
}

extern void func_87E02438();
extern void func_87E02470();
extern void func_87E01DB4();
void func_87E02794(void *arg0, s32 arg1) {
    *(s32 *)((u8 *)arg0 + 0x280) = arg1;
    *(s32 *)arg0 = 0;
    func_87E01E24(arg0);
    func_87E02438();
    func_87E02470(arg0);
    func_87E01DB4(arg0);
}
#endif
