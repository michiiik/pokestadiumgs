#include "global.h"


#ifdef VERSION_US
extern void func_80038E14(s32, s32, s32, s32, f32, f32, f32, s32);
extern u8 D_87E1EC10;
s32 func_87E136F0(s32 arg0, s32 arg1) {
    func_80038E14(arg1, (*(s32 *)((u8 *)(&D_87E1EC10) + (0))), (*(s32 *)((u8 *)(&D_87E1EC10) + (4))), (*(s32 *)((u8 *)(&D_87E1EC10) + (8))), (*(f32 *)((u8 *)(&D_87E1EC10) + (0xC))), (*(f32 *)((u8 *)(&D_87E1EC10) + (0x10))), (*(f32 *)((u8 *)(&D_87E1EC10) + (0x14))), 0);
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E1374C.s")

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
void func_87E13848(s32 arg0, s32 arg1) {
    u8 *context;
    void *temp_v0;
    if (arg0 == 5) {
        context = (u8 *)D_8009491C;
        temp_v0 = *(void **)(context + 0x14);
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238);
        gSPSegment(D_800D0510++, 0xF,
                   func_8004CA60((u8 *)func_8004C990(0x166, 0)));
        gSPDisplayList(D_800D0510++, *(void **)((u8 *)temp_v0 + 4));
        func_8003CD84();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E13924.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E13C94.s")

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern void func_8003CD84(void);
typedef struct {
    u8 pad_1d[0x1D];
    u8 alpha;
    u8 pad_3c[0x1E];
    u8 red;
    u8 green;
    u8 blue;
} Func87E13D18Context;
void func_87E13D18(s32 arg0, s32 arg1) {
    Func87E13D18Context *context;
    void *temp_v0;
    if (arg0 == 5) {
        context = (Func87E13D18Context *)D_8009491C;
        temp_v0 = *(void **)((u8 *)context + 0x14);
        gDPPipeSync(D_800D0510++);
        gSPClearGeometryMode(D_800D0510++, 0x400);
        gDPSetCombine(D_800D0510++, 0x42FFFF, -0x5C8);
        gDPSetEnvColor(D_800D0510++, context->red, context->green,
                       context->blue, context->alpha);
        gSPDisplayList(D_800D0510++, *(void **)((u8 *)temp_v0 + 4));
        func_8003CD84();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E13E04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E13F84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E1425C.s")

extern void func_87E13924(void *, s32);
extern void *D_87F119DC;

void func_87E14458(void) {
    func_87E13924(D_87F119DC, (*(s32 *)((u8 *)(D_87F119DC) + (0x20))));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E14480.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E14578.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E146DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E14898.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E14984.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E14A60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E14BA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E14D24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E14E08.s")

extern void func_87E120F8(s32);
extern void func_87E1425C(s32);
extern void func_87E14E08();
extern void func_87F0277C(s32);
extern void func_87F0C3EC(s32 *);
void func_87E14F98(s32 arg0) {
    func_87E14E08();
    func_87F0277C(arg0 + 4);
    func_87F0277C(arg0 + 0x18);
    func_87F0277C(arg0 + 0x2C);
    func_87E1425C(arg0);
    func_87E120F8(arg0 + 0x64);
    func_87F0C3EC(&D_87E1EC10);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E14FF4.s")

void func_87E15324(u8 *arg0) {}

void func_87E1532C(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E15334.s")

extern void *func_87F025B8(void *, void *);
extern void func_87E146DC(void *, s32, s32);
extern void func_87E14A60(void);
void func_87E15430(void *arg0) {
    void *result;
    result = func_87F025B8((u8 *)arg0 + 0x18, (void *)func_87E14A60);
    if (result != NULL) {
        func_87E146DC(result, *(s32 *)((u8 *)result + 0x20), 1);
        *(u8 *)((u8 *)result + 0x41) = 0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E15478.s")

extern void func_87E13F84(s32, s32);
void func_87E154E4(s32 arg0) {
    func_87E13F84(arg0, 0x10000000);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E15504.s")

void func_87E155DC(u8 *arg0) {
    *(s32 *)(arg0 + 0x168) = 4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E155E8.s")

extern void func_8003C6B8(s32);
void WidgetTree_OpenMessagePanel_fragment63(u8 *arg0) {
    func_8003C6B8(*(s32 *)(arg0 + 0x170));
}

s32 func_87E15698(u8 *arg0) {
    return *(s32 *)(arg0 + 0x164);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E156A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E15874.s")

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
void func_87E15920(s32 arg0, s32 arg1) {
    u8 *context;
    void *temp_v0;
    if (arg0 == 5) {
        context = (u8 *)D_8009491C;
        temp_v0 = *(void **)(context + 0x14);
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCFC38);
        gSPSegment(D_800D0510++, 0xF,
                   func_8004CA60((u8 *)func_8004C990(
                       0x1B2, *(s32 *)(context + 0x3C) + 2)));
        gSPDisplayList(D_800D0510++, *(void **)((u8 *)temp_v0 + 0x108));
        func_8003CD84();
    }
}
void func_87E15920_padding(void) {}

s32 func_80040E80(s32, s32 *);
s32 func_8004C990(s32, s32);
s32 func_87F08E3C(s32, s32);
extern u8 D_87E1B310;
void func_87E15A08(void *arg0) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    sp1C = temp_v0;
    (*(s32 *)((u8 *)(arg0) + (0x104))) = func_80040E80(temp_v0, &D_87E1B310);
    MainPool_FinalizeAllocation(sp1C);
    (*(s32 *)((u8 *)(arg0) + (0x108))) = func_87F08E3C(func_8004C990(0x1B2, 6), 0x0F000000);
}

void func_87E15A78(void *arg0) {
    if (((*(f32 *)((u8 *)(arg0) + (0))) == 0.0f) && ((*(f32 *)((u8 *)(arg0) + (4))) == 0.0f) && ((*(f32 *)((u8 *)(arg0) + (8))) == 0.0f)) {
        (*(f32 *)((u8 *)(arg0) + (0))) = 1.0f;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E15AD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E15E18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E1614C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E16200.s")

void func_87E1643C(void *arg0, void *arg1, void *arg2, void *arg3) {
    (*(f32 *)((u8 *)(arg0) + (0))) = (f32) (*(f32 *)((u8 *)(arg1) + (0)));
    (*(f32 *)((u8 *)(arg0) + (4))) = (f32) (*(f32 *)((u8 *)(arg1) + (4)));
    (*(f32 *)((u8 *)(arg0) + (8))) = (f32) (*(f32 *)((u8 *)(arg1) + (8)));
    (*(f32 *)((u8 *)(arg0) + (0x10))) = (f32) (*(f32 *)((u8 *)(arg2) + (0)));
    (*(f32 *)((u8 *)(arg0) + (0x14))) = (f32) (*(f32 *)((u8 *)(arg2) + (4)));
    (*(f32 *)((u8 *)(arg0) + (0x18))) = (f32) (*(f32 *)((u8 *)(arg2) + (8)));
    (*(f32 *)((u8 *)(arg0) + (0x20))) = (f32) (*(f32 *)((u8 *)(arg3) + (0)));
    (*(f32 *)((u8 *)(arg0) + (0x24))) = (f32) (*(f32 *)((u8 *)(arg3) + (4)));
    (*(f32 *)((u8 *)(arg0) + (0x28))) = (f32) (*(f32 *)((u8 *)(arg3) + (8)));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E16488.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E16738.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E16894.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E16AA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E16B50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E16DC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E16FC4.s")

extern f32 D_87E1B930;
extern f32 D_87E1B934;
s32 func_87E172F0(f32 arg0, f32 arg1, s32 arg2) {
    s32 result;
    result = 0;
    if (D_87E1B930 < arg1) {
        result = 1;
    } else if (arg1 < D_87E1B934) {
        result = -1;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E1733C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E17484.s")

extern void *D_87E1EC88;
s32 func_87E176A0(s32 arg0, s32 arg1) {
    func_80038E14(arg1, (*(s32 *)((u8 *)(D_87E1EC88) + (0x1158))), (*(s32 *)((u8 *)(D_87E1EC88) + (0x115C))), (*(s32 *)((u8 *)(D_87E1EC88) + (0x1160))), (*(f32 *)((u8 *)(D_87E1EC88) + (0x1164))), (*(f32 *)((u8 *)(D_87E1EC88) + (0x1168))), (*(f32 *)((u8 *)(D_87E1EC88) + (0x116C))), 0);
    return 1;
}

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
void func_87E176FC(s32 arg0, s32 arg1) {
    u8 *context;
    void *temp_v0;
    if (arg0 == 5) {
        context = (u8 *)D_8009491C;
        temp_v0 = *(void **)(context + 0x14);
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCFC38);
        gSPSegment(D_800D0510++, 0xF,
                   func_8004CA60((u8 *)func_8004C990(0x1B2, 6)));
        gSPDisplayList(D_800D0510++, *(void **)((u8 *)temp_v0 + 0x18));
        func_8003CD84();
    }
}
void func_87E176FC_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E177E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E17928.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E179F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E17B34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E17D40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E17DAC.s")

s32 func_87E17EA8(u8 *arg0) {
    return *(s8 *)(arg0 + 1) == 5;
}

s32 func_87E17EB8(u8 *arg0) {
    return *(s8 *)(arg0 + 3) == 1;
}

s32 func_87E17EC8(u8 *arg0) {
    return *(s8 *)(arg0 + 1);
}

extern s32 main_pool_push_state(s32);
extern void func_87E03594(void *, s32);
extern void func_87E03CEC(void *);
void func_87E17ED0(void *arg0) {
    main_pool_push_state(0x4D51454A);
    func_87E03594((u8 *)arg0 + 0x30, *(s32 *)((u8 *)arg0 + 0x264));
    func_87E03CEC((u8 *)arg0 + 0x30);
}

extern void func_87E01628();
extern void func_87E03D28(s32);
extern void main_pool_pop_state(s32);

void func_87E17F14(s32 arg0) {
    func_87E03D28(arg0 + 0x30);
    func_87E01628();
    main_pool_pop_state(0x4D51454A);
}


void func_87E17F48(void) {
    func_87E01628();
    main_pool_pop_state(0x4D514D53);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E17F74.s")

void func_87E18034(u8 *arg0, s32 arg1) {
    *(s32 *)(*(u8 **)(arg0 + 0x264) + 0x2200) = arg1;
    *(s32 *)(*(u8 **)(arg0 + 0x264) + 0x2184) = 3;
    *(s32 *)arg0 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E18054.s")

extern s32 func_87E04114(u8 *);
extern void func_87E17F14(s32);
extern void func_87E18A14(void *, s32, s32);
s32 func_87E18120(s32 arg0) {
    s32 result;
    s32 state;
    result = 0;
    state = func_87E04114((u8 *)arg0 + 0x30);
    if (state != 2) {
        func_87E17F14(arg0);
        switch (state) {
        case 0:
            *(s32 *)arg0 = 4;
            func_87E18A14((u8 *)arg0 + 0x238,
                          *(s32 *)(*(u8 **)((u8 *)arg0 + 0x264) + 0x2204),
                          0x2D);
            break;
        case 1:
            result = 1;
            break;
        }
    }
    return result;
}

void func_87E181B4(u8 *arg0, s32 arg1) {
    *(s32 *)(*(u8 **)(arg0 + 0x264) + 0x2204) = arg1;
    *(s32 *)(*(u8 **)(arg0 + 0x264) + 0x2184) = 4;
    *(s32 *)arg0 = 4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E181D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_317060/func_87E182A8.s")

extern void func_87E1918C(s32);
extern void func_87E03448();
void func_87E183A0(void *arg0) {
    s32 value;
    value = *(s32 *)arg0;
    switch (value) {
    case 1:
        func_87E1918C((s32)((u8 *)arg0 + 4));
        break;
    case 3:
        func_87E03448((u8 *)arg0 + 0x30);
        break;
    case 4:
        func_87E1918C((s32)((u8 *)arg0 + 0x238));
        break;
    }
}
#endif
