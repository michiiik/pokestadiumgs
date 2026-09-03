#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E027E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E028D8.s")

extern void func_8004C8C0(s32);
void func_87E02A28(void) { func_8004C8C0(0x1A8); func_8004C8C0(0x1B2); func_8004C8C0(0x1A3); func_8004C8C0(0x1A5); func_8004C8C0(0x1A6); func_8004C8C0(0x1A7); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E02A70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E02B60.s")

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern void func_8003CD84(void);
void func_87E02F40(s32 arg0, s32 arg1) {
    u8 *context;
    void *temp_v0;
    void *temp_a0;
    if (arg0 == 5) {
        context = (u8 *)D_8009491C;
        temp_v0 = *(void **)(context + 0x14);
        temp_a0 = *(void **)((u8 *)temp_v0 + 0x20);
        gDPPipeSync(D_800D0510++);
        gDPSetTextureFilter(D_800D0510++, G_TF_BILERP);
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238);
        gSPSegment(D_800D0510++, 0xF, *(void **)((u8 *)temp_a0 + 8));
        gSPDisplayList(D_800D0510++, *(void **)((u8 *)temp_a0 + 4));
        func_8003CD84();
    }
}

void D_87E03018(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E03020.s")

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern void func_87E03020(void *);
extern void func_8003CD84(void);
void func_87E030F0(s32 arg0, s32 arg1) {
    u8 *context;
    void *temp_v0;
    void *temp_s0;
    if (arg0 == 5) {
        context = (u8 *)D_8009491C;
        temp_v0 = *(void **)(context + 0x14);
        temp_s0 = *(void **)((u8 *)temp_v0 + 0x20);
        func_87E03020(temp_s0);
        if (*(s32 *)((u8 *)temp_s0 + 4) != 0) {
            gDPPipeSync(D_800D0510++);
            gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238);
            gSPSegment(D_800D0510++, 0xF, *(void **)((u8 *)temp_s0 + 4));
            gSPDisplayList(D_800D0510++, *(void **)((u8 *)temp_s0 + 0));
            func_8003CD84();
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E031C0.s")

extern void func_87E031C0(void);
extern void func_800088DC(void);
void func_87E03448(void) {
    func_87E031C0();
    func_800088DC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E03470.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E03518.s")

extern void func_87E028D8(void *);
extern void func_87E02A70(void *);
extern void func_87E03470(void *);
extern void func_87E03518(void *);
void func_87E03594(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)(arg0) + (0x204))) = arg1;
    (*(s32 *)((u8 *)(arg0) + (0))) = 0;
    func_87E02A28();
    func_87E02A70(arg0);
    func_87E03470(arg0);
    func_87E03518(arg0);
    func_87E028D8(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E035E4.s")

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern void func_8003CD84(void);
typedef struct {
    u8 pad_60[0x60];
    u8 red;
    u8 green;
    u8 blue;
} Func87E0375CColor;
void func_87E0375C(s32 arg0, s32 arg1) {
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E03850.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E03A08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E03B70.s")

extern void func_87E03850(void *);
extern void func_87E03A08(void *);
extern void func_87E03B70(void *);
void func_87E03CBC(void *arg0) { func_87E03850(arg0); func_87E03A08(arg0); func_87E03B70(arg0); }

extern void func_87E13480(s32);
extern void func_87E13490();
extern void func_87E134C0();
void func_87E03CEC(void *arg0) {
    (*(s32 *)((u8 *)(arg0) + (4))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0))) = 0;
    func_87E03CBC(arg0);
    func_87E134C0();
    func_87E13490();
    func_87E13480(0);
}

extern void func_87F02684(s32);
void func_87E03D28(s32 arg0) {
    func_87F02684(arg0 + 8);
}

s32 func_87E03D48(s32 arg0) {
    u8 *p;
    s32 result;
    s32 i;
    p = (u8 *)(u32)(arg0 + 0x1C);
    result = 1;
    arg0 = 2;
    i = 0;
    do {
        if (*(s32 *)(p + 0x94) != 0) {
            result = 0;
            break;
        }
        i++;
        p += 0x98;
    } while (i != arg0);
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E03D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E03E48.s")

extern s32 func_87E016D8(void *);
s32 func_87E03FF0(void *arg0) {
    s32 result;
    void *p;
    p = *(void **)((u8 *)arg0 + 0x204);
    result = ((*(u8 *)((u8 *)p + 0x2182) & 1) != 0);
    if (result) {
        ;
        return func_87E016D8(p) >= 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E04030.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E04048.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_306150/func_87E04114.s")
#endif
