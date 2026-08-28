#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413E410.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413E490.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413E514.s")
#endif

#ifdef VERSION_US
extern Gfx* D_800D0510;
void ParticleGfx_SetPrimColor_fragment79(u8 r, u8 g, u8 b, u8 a) {
    gDPSetPrimColor(D_800D0510++, 0, 0, r, g, b, a);
}
#endif

#ifdef VERSION_US
void func_8413E63C(u16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, (((((arg0 << 8) & 0xF800) | ((arg1 << 3) & 0x7C0) | ((arg2 >> 2) & 0x3E) | (arg3 & 1)) << 16) |
        (((arg0 << 8) & 0xF800) | ((arg1 << 3) & 0x7C0) | ((arg2 >> 2) & 0x3E) | (arg3 & 1))));
}
#endif

#ifdef VERSION_US
void func_8413E6B8(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    gDPPipeSync(D_800D0510++);
    gDPSetEnvColor(D_800D0510++, arg0, arg1, arg2, arg3);
}
#endif

#ifdef VERSION_US
extern void func_8004C8C0(s32);
void func_8413E728(u8 arg0) {
    func_8004C8C0(0x157);
    if (arg0 != 0) {
        func_8004C8C0(0x139);
    } else {
        func_8004C8C0(0x24);
        func_8004C8C0(0x1E);
        func_8004C8C0(0x23);
        func_8004C8C0(0x20);
        func_8004C8C0(0x21);
        func_8004C8C0(0x1F);
        func_8004C8C0(0x22);
        func_8004C8C0(0x7A);
    }
}
#endif

#ifdef VERSION_US
extern s32 func_8004C4B0(s32);
extern s32 func_8004C504(s32);
extern void func_8413E514(void);
extern u8 *D_841951F8;
extern u8 *D_841951FC;
void func_8413E7A8(u8 arg0) {
    func_8004C4B0(7);
    func_8413E514();
    func_8004C504(7);
    func_8004C4B0(0xE);
    func_8004C4B0(0x10);
    func_8004C4B0(6);
    func_8004C4B0(8);
    func_8004C4B0(0xC);
    func_8004C4B0(D_841951F8[0x49B] + 0x4C);
    func_8004C4B0(D_841951FC[0x49B] + 0x4C);
    if (arg0 != 0) {
        func_8004C4B0(0x16);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413E840.s")
#endif

#ifdef VERSION_US
extern f32 D_8418B1CC;
s32 func_8413E890(f32 arg0) { s32 low = ((s32)arg0) & 0x1F; return ((low << 10) + (s32)((arg0 - (f32)low + D_8418B1CC) * 1024.0f)) & 0xFFFF; }
#endif

void func_8413E8DC(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413E8E4.s")
#endif

#ifdef VERSION_US
extern s32 func_8004CA10(u16 *);
extern s32 func_8004CA24(u16 *);
extern u8 *func_8004CA60(u8 *);
extern s32 func_8004CA38(u8 *);
extern s32 func_8004CA4C(u8 *);
extern void func_8413E8E4(s16, s16, u16, u16, s32, s32, u8 *, s32, s32, s32);
void func_8413EC88(s16 arg0, s16 arg1, u16 arg2, u16 arg3, void *arg4) {
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp24 = 1;
    u8 *sp34;

    sp44 = func_8004CA10((u16 *)arg4);
    sp40 = func_8004CA24((u16 *)arg4);
    sp34 = func_8004CA60((u8 *)arg4);
    sp3C = func_8004CA38((u8 *)arg4);
    func_8413E8E4(arg0, arg1, arg2, arg3, sp44, sp40, sp34, sp3C, func_8004CA4C((u8 *)arg4), sp24);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413ED28.s")
#endif

#ifdef VERSION_US
extern void *func_8004C990(s32, s32);
extern void func_8004D1FC(void *);
void func_8413EDCC(void) {
    void *value = func_8004C990(0x21, 3);
    func_8004D1FC(value);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413EDF8.s")
#endif

#ifdef VERSION_US
void func_8413F034(void) {
    void *value = func_8004C990(0x1F, 0);
    func_8004D1FC(value);
}
#endif

#ifdef VERSION_US
extern void func_80044270(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_8413F060(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    s32 temp_v0;
    s32 temp_a2;
    s32 temp_a3;
    temp_a2 = arg2;
    temp_a3 = arg3;
    if ((temp_a2 >= 7) && (temp_a3 >= 7)) {
        temp_v0 = temp_a2 - 6;
        func_80044270((s16)(arg0 + 2), (s16)(arg1 + 2), (s16)temp_v0, (s16)(temp_a3 - 6), 0, 0, (0x10000 / temp_v0) & 0xFFFF, 0, 0);
    }
}
#endif

#ifdef VERSION_US
extern void func_80044270(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_8413F12C(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    s32 temp_v0;
    s32 temp_a2;
    s32 temp_a3;
    temp_a2 = arg2;
    temp_a3 = arg3;
    if ((temp_a2 >= 7) && (temp_a3 >= 7)) {
        temp_v0 = temp_a2 - 6;
        func_80044270((s16)(arg0 + 2), (s16)(arg1 + 2), (s16)temp_v0, (s16)(temp_a3 - 6), 0, 0, (0x10000 / temp_v0) & 0xFFFF, 0, 0);
    }
}
#endif

#ifdef VERSION_US
void func_8413F1F8(void) {
    void *value = func_8004C990(0x21, 0);
    func_8004D1FC(value);
}
#endif

#ifdef VERSION_US
extern void func_80044270(s32,s32,s32,s32,s32,s32,s32,s32,s32);
void func_8413F224(s16 arg0, s16 arg1) {
    func_80044270(arg0, arg1, 0x40, 0xE, 0, 0, 0x400, 0x400, 0);
}
#endif

#ifdef VERSION_US
void func_8413F27C(void) {
    void *value = func_8004C990(0x21, 1);
    func_8004D1FC(value);
}
#endif

#ifdef VERSION_US
void func_8413F2A8(s16 arg0, s16 arg1) {
    func_80044270(arg0, arg1, 0x5E, 0x11, 0, 0, 0x400, 0x400, 0);
}
#endif

#ifdef VERSION_US
void func_8413F300(void) {
    void *value = func_8004C990(0x20, 7);
    func_8004D1FC(value);
}
#endif

#ifdef VERSION_US
void func_8413F32C(s16 arg0, s16 arg1, u8 arg2) {
    s32 temp_t7;
    temp_t7 = (arg2 & 0xFF) << 8;
    func_80044270((s32)arg0, (s32)arg1, 8, 9, temp_t7, 0, 0x400, 0x400, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413F390.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413F498.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413F5A8.s")
#endif

#ifdef VERSION_US
extern u8 D_84186FE0[];
extern void func_8413F5A8(s32,s32,s32,s32);
void func_8413F5F4(s16 arg0, s16 arg1, s32 arg2) {
    func_8413F5A8(arg0, arg1, 0x23, D_84186FE0[arg2]);
}
#endif

#ifdef VERSION_US
extern void func_8413F5A8(s32,s32,s32,s32);
extern s32 func_800630F0(s32);
extern u8 D_84186F98[];
extern u8 D_84186FE8[];
void func_8413F640(s16 arg0, s16 arg1, s32 arg2) {
    s32 temp_v0;
    s32 saved_index;
    u8 *temp_v0_2;
    temp_v0 = func_800630F0(arg2 & 0xFF);
    if (temp_v0 != 0x12) {
        saved_index = temp_v0;
        temp_v0_2 = D_84186F98 + saved_index * 3;
        ParticleGfx_SetPrimColor_fragment79(temp_v0_2[0], temp_v0_2[1], temp_v0_2[2], 0xFF);
        func_8413F5A8((s32)arg0, (s32)arg1, 0x24, D_84186FE8[saved_index]);
    }
}
#endif

#ifdef VERSION_US
extern void func_8413F5A8(s32, s32, s32, s32);
void func_8413F6C0(s16 arg0, s16 arg1, u16 arg3) {
    func_8413F5A8(arg0, arg1, 0x1E, arg3);
}
#endif

#ifdef VERSION_US
void func_8413F700(s16 arg0, s16 arg1) {
    func_8413F5A8(arg0, arg1, 0x20, 2);
}
#endif

#ifdef VERSION_US
void func_8413F73C(s16 arg0, s16 arg1) {
    func_8413F5A8(arg0, arg1, 0x20, 3);
}
#endif

#ifdef VERSION_US
void func_8413F778(s16 arg0, s16 arg1) {
    func_8413F5A8(arg0, arg1, 0x20, 4);
}
#endif

#ifdef VERSION_US
void func_8413F7B4(s16 arg0, s16 arg1) {
    func_8413F5A8(arg0, arg1, 0x20, 9);
}
#endif

#ifdef VERSION_US
void func_8413F7F0(s16 arg0, s16 arg1) {
    func_8413F5A8(arg0, arg1, 0x20, 1);
}
#endif

#ifdef VERSION_US
void func_8413F82C(void) {
    void *value = func_8004C990(0x20, 5);
    func_8004D1FC(value);
}
#endif

#ifdef VERSION_US
extern u8 D_84186F88[];
void func_8413F858(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    func_80044270((s32)arg0, (s32)arg1, (s32)(s16)(arg3 + 1), 6, 0, 0, 0x400, 0x400, 0);
    ParticleGfx_SetPrimColor_fragment79(D_84186F88[0], D_84186F88[1], D_84186F88[2], 0xFF);
    if (arg2 != arg3) {
        func_80044270((s32)(s16)(arg0 + arg3 + 1), (s32)arg1, (s32)(s16)(arg2 - arg3), 6, 0x20, 0, 0, 0x400, 0);
    }
    func_80044270((s32)(s16)(arg0 + arg2 + 1), (s32)arg1, 1, 6, 0, 0, 0, 0x400, 0);
    ParticleGfx_SetPrimColor_fragment79(0xFF, 0xFF, 0xFF, 0xFF);
}
#endif

#ifdef VERSION_US
extern u8 D_84186F7C[];
extern u8 D_84186F80[];
extern u8 D_84186F84[];
extern s32 func_80064590(u16, u16);
void func_8413F988(u16 arg0, u16 arg1) {
    s32 temp_v0;

    temp_v0 = func_80064590(arg0, arg1);
    switch (temp_v0) {
    case 0:
        ParticleGfx_SetPrimColor_fragment79(D_84186F7C[0], D_84186F7C[1], D_84186F7C[2], 0xFF);
        return;
    case 1:
        ParticleGfx_SetPrimColor_fragment79(D_84186F80[0], D_84186F80[1], D_84186F80[2], 0xFF);
        return;
    case 2:
        ParticleGfx_SetPrimColor_fragment79(D_84186F84[0], D_84186F84[1], D_84186F84[2], 0xFF);
        return;
    }
}
#endif

#ifdef VERSION_US
void func_8413FA34(void) {
    void *value = func_8004C990(0x20, 6);
    func_8004D1FC(value);
}
#endif

#ifdef VERSION_US
void func_8413FA60(s16 arg0, s16 arg1) {
    func_80044270(arg0, arg1, 0x10, 7, 0, 0, 0x400, 0x400, 0);
}
#endif

#ifdef VERSION_US
void func_8413FAB8(void) {
    void *value = func_8004C990(0x7A, 0);
    func_8004D1FC(value);
}
#endif

#ifdef VERSION_US
void func_8413FAE4(s16 arg0, s16 arg1) {
    func_80044270(arg0, arg1, 0x18, 0xE, 0, 0, 0x400, 0x400, 0);
}
#endif

#ifdef VERSION_US
extern void func_8004D19C(s32,s32,s32,s32,s32);
void func_8413FB3C(s16 arg0, s16 arg1) {
    void *value = func_8004C990(0x22, 0);
    func_8004D19C(arg0, arg1, (s32)value, 0, 0);
}
#endif

#ifdef VERSION_US
void func_8413FB80(s16 arg0, s16 arg1) {
    void *value = func_8004C990(0x22, 1);
    func_8004D19C(arg0, arg1, (s32)value, 0, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413FBC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413FC34.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413FD04.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8413FDB0.s")
#endif

#ifdef VERSION_US
extern u8 D_841869E0[];
extern void func_8413EC88(s16, s16, u16, u16, void *);
extern void func_8413FDB0(void *);
void func_84140270(void *arg0) {
    gSPDisplayList(D_800D0510++, D_841869E0);
    ParticleGfx_SetPrimColor_fragment79(
        *(u8 *)((u8 *)arg0 + 0x22),
        *(u8 *)((u8 *)arg0 + 0x23),
        *(u8 *)((u8 *)arg0 + 0x24),
        *(u8 *)((u8 *)arg0 + 0x25));
    func_8413EC88(
        *(s16 *)((u8 *)arg0 + 0xA),
        *(s16 *)((u8 *)arg0 + 0xC),
        *(u16 *)((u8 *)arg0 + 0xE),
        *(u16 *)((u8 *)arg0 + 0x10),
        func_8004C990(0x157, 0));
    func_8413FDB0(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841402FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84140474.s")
#endif

#ifdef VERSION_US
extern void func_84140270(void *);
extern void func_841402FC(void *);
extern void func_84140474(void *);
void func_84140690(void *arg0) {
    s32 temp_v0;

    if (!((*(u8 *)((u8 *)(arg0) + (8))) & 1) && ((*(u8 *)((u8 *)(arg0) + (0))) == 0x17)) {
        temp_v0 = (*(s32 *)((u8 *)(arg0) + (4)));
        switch (temp_v0) {                          /* irregular */
        case 0:
            func_84140270(arg0);
            return;
        case 1:
            func_841402FC(arg0);
            return;
        case 2:
            func_84140474(arg0);
            break;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84140718.s")
#endif

#ifdef VERSION_US
extern u8 D_84186B60[];
extern void func_8413F5A8(s32,s32,s32,s32);
void func_84140B64(void *arg0) {
    u8 sp27;
    s32 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 9);
    if (temp_v0 >= 31) {
        sp27 = 0x177 - temp_v0 * 4;
    } else if (temp_v0 >= 16) {
        sp27 = 0xFF;
    } else {
        sp27 = temp_v0 * 4 + 0xC3;
        if (temp_v0 == 1) {
            *(u8 *)((u8 *)arg0 + 9) = 0x2E;
        }
    }
    gSPDisplayList(D_800D0510++, D_841869E0);
    ParticleGfx_SetPrimColor_fragment79(0xFF, 0xEB, 0xC3, 0xFF);
    func_8413F5A8(*(s16 *)((u8 *)arg0 + 0xA), *(s16 *)((u8 *)arg0 + 0xC), 0x131, 0);
    gSPDisplayList(D_800D0510++, D_84186B60);
    ParticleGfx_SetPrimColor_fragment79(0xFF, 0xFF, 0xFF, sp27);
    func_8413E6B8(0xFF, 0xC8, 0, 0xFF);
    func_8413F5A8(*(s16 *)((u8 *)arg0 + 0xA), *(s16 *)((u8 *)arg0 + 0xC), 0x131, 1);
}
#endif

#ifdef VERSION_US
extern void func_84140718();
extern void func_84140B64(void *);
void func_84140C8C(void *arg0) {
    s32 temp_v0;

    if (!((*(u8 *)((u8 *)(arg0) + (8))) & 1) && ((*(u8 *)((u8 *)(arg0) + (0))) == 0x18)) {
        temp_v0 = (*(s32 *)((u8 *)(arg0) + (4)));
        switch (temp_v0) {                          /* irregular */
        case 1:
            func_84140718();
            return;
        case 2:
            func_84140B64(arg0);
            break;
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_8413FBC4(s16, s16, u8, void *);
void func_84140CFC(void *arg0) {
    u8 temp_v0;
    u8 temp_a2;

    temp_v0 = *(u8 *)((u8 *)arg0 + 8);
    temp_a2 = *(u8 *)((u8 *)arg0 + 1);
    if (!(temp_v0 & 1) && !(temp_v0 & 0x10) && (*(u8 *)((u8 *)arg0 + 0) == 2)) {
        func_8413FBC4(
            (s16)(*(s16 *)((u8 *)arg0 + 0xA) + 2),
            (s16)(*(s16 *)((u8 *)arg0 + 0xC) + 2),
            temp_a2,
            arg0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84140D68.s")
#endif

#ifdef VERSION_US
extern void func_8413F12C(s16, s16, u16, u16);
void func_84140F1C(void *arg0) {
    u8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = (*(u8 *)((u8 *)(arg0) + (8)));
    if (!(temp_v0 & 1) && (temp_v0 & 0x10) && ((temp_v0_2 = (*(u8 *)((u8 *)(arg0) + (0))), (temp_v0_2 == 1)) || (temp_v0_2 == 2))) {
        ParticleGfx_SetPrimColor_fragment79((*(u8 *)((u8 *)(arg0) + (0x22))), (*(u8 *)((u8 *)(arg0) + (0x23))), (*(u8 *)((u8 *)(arg0) + (0x24))), 0xA8U);
        func_8413F12C((*(s16 *)((u8 *)(arg0) + (0xA))), (*(s16 *)((u8 *)(arg0) + (0xC))), (*(u16 *)((u8 *)(arg0) + (0xE))), (*(u16 *)((u8 *)(arg0) + (0x10))));
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84140F98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84141020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841410A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8414111C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84141278.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84141538.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84141768.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84141BE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84141D1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84141F20.s")
#endif

#ifdef VERSION_US
extern s16 D_84186BCC;
extern s16 D_84186BD0;
extern s16 D_84186D54;
extern s16 D_84186D58;
void func_841420A4(void *arg0) {
    u8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = (*(u8 *)((u8 *)(arg0) + (8)));
    if (!(temp_v0 & 1) && !(temp_v0 & 2) && !(temp_v0 & 0x10)) {
        temp_v0_2 = (*(u8 *)((u8 *)(arg0) + (0)));
        switch (temp_v0_2) {                        /* irregular */
        case 1:
            func_8413FA60((s16) ((*(s16 *)((u8 *)(arg0) + (0xA))) + D_84186BCC), (s16) ((*(s16 *)((u8 *)(arg0) + (0xC))) + D_84186BD0));
            return;
        case 13:
            func_8413FA60((s16) ((*(s16 *)((u8 *)(arg0) + (0xA))) + D_84186D54), (s16) ((*(s16 *)((u8 *)(arg0) + (0xC))) + D_84186D58));
            break;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8414216C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841427DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84142B78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84142DCC.s")
#endif

#ifdef VERSION_US
void func_84142E44(void *arg0) {
    if (!((*(u8 *)((u8 *)(arg0) + (8))) & 1) && ((*(u8 *)((u8 *)(arg0) + (0))) == 0x19)) {
        ParticleGfx_SetPrimColor_fragment79((*(u8 *)((u8 *)(arg0) + (0x22))), (*(u8 *)((u8 *)(arg0) + (0x23))), (*(u8 *)((u8 *)(arg0) + (0x24))), (*(u8 *)((u8 *)(arg0) + (0x25))));
        func_8413F5A8((s32) (*(s16 *)((u8 *)(arg0) + (0xA))), (s32) (*(s16 *)((u8 *)(arg0) + (0xC))), 0x21, 2);
    }
}
#endif

#ifdef VERSION_US
void func_84142EB0(void *arg0) {
    if ((*(u8 *)((u8 *)(arg0) + (0))) == 0x1A) {
        ParticleGfx_SetPrimColor_fragment79((*(u8 *)((u8 *)(arg0) + (0x22))), (*(u8 *)((u8 *)(arg0) + (0x23))), (*(u8 *)((u8 *)(arg0) + (0x24))), (*(u8 *)((u8 *)(arg0) + (0x25))));
        func_8413F5A8((s32) (*(s16 *)((u8 *)(arg0) + (0xA))), (s32) (*(s16 *)((u8 *)(arg0) + (0xC))), 0x139, 0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84142F0C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841430D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8414327C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84143508.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841436EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841438EC.s")
#endif

#ifdef VERSION_US
extern s16 D_84186EC4;
extern s16 D_84186EC8;
extern s16 D_84186ECC;
extern void func_8413F390(s16, s16, s32, u16);
void func_84143BF4(void *arg0) {
    u16 sp26;

    sp26 = (u16)((u32)*(u32 *)((u8 *)arg0 + 4) / 100U);
    ParticleGfx_SetPrimColor_fragment79(0xFFU, 0xFFU, 0xFFU, *(u8 *)((u8 *)arg0 + 0x25));
    func_8413F390(
        (s16)(*(s16 *)((u8 *)arg0 + 0xA) + D_84186EC4),
        (s16)(*(s16 *)((u8 *)arg0 + 0xC) + D_84186ECC),
        2,
        (u16)((s32)sp26 / 60) & 0xFFFF);
    func_8413F390(
        (s16)(*(s16 *)((u8 *)arg0 + 0xA) + D_84186EC8),
        (s16)(*(s16 *)((u8 *)arg0 + 0xC) + D_84186ECC),
        2,
        (u16)((s32)sp26 % 60) & 0xFFFF);
    ParticleGfx_SetPrimColor_fragment79(0xFFU, 0xFFU, 0xFFU, 0xFFU);
}
#endif

#ifdef VERSION_US
extern void func_8413F390(s16, s16, s32, u16);
extern s16 D_84186E9C;
extern s16 D_84186EA0;
void func_84143CF0(void *arg0) {
    u16 sp1E;

    sp1E = (u16) ((u32) (*(u32 *)((u8 *)(arg0) + (4))) / 100U);
    ParticleGfx_SetPrimColor_fragment79(0xFFU, 0xFFU, 0xFFU, (*(u8 *)((u8 *)(arg0) + (0x25))));
    func_8413F390((s16) ((*(s16 *)((u8 *)(arg0) + (0xA))) + D_84186E9C), (s16) ((*(s16 *)((u8 *)(arg0) + (0xC))) + D_84186EA0), 2, sp1E);
    ParticleGfx_SetPrimColor_fragment79(0xFFU, 0xFFU, 0xFFU, 0xFFU);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84143D8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84143E64.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84143F18.s")
#endif

#ifdef VERSION_US
extern u8 D_84186F90[];
extern s16 D_84186BBC;
extern s16 D_84186BC0;
extern u8 *func_8413D29C(u8);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800495F8(s32, s32, s32, void *);
void func_84143FF4(void *arg0) {
    u8 sp1F[4];
    u8 temp_a0;
    u8 *temp_v0;

    temp_a0 = *(u8 *)((u8 *)arg0 + 1);
    sp1F[3] = temp_a0;
    temp_v0 = func_8413D29C(temp_a0);
    if (temp_v0[0x10] != 0) {
        func_8004972C(D_84186F90[0], D_84186F90[1], D_84186F90[2], 0xFF);
    } else {
        func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
    }
    func_800495F8(
        *(s16 *)((u8 *)arg0 + 0xA) + D_84186BBC,
        *(s16 *)((u8 *)arg0 + 0xC) + D_84186BC0,
        1,
        ((u8 **)&D_841951F8)[sp1F[3]] + 0x48C);
    func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
}
#endif

#ifdef VERSION_US
extern void func_84143E64(s32, s32, u8, u16, s32);
extern s16 D_84186BBC;
extern s16 D_84186BC0;
void func_841440B4(void *arg0) {
    u8 *temp_v0;

    temp_v0 = func_8413D29C((*(u8 *)((u8 *)(arg0) + (1))));
    func_84143E64(((*(s16 *)((u8 *)(arg0) + (0xA))) + D_84186BBC) & 0xFFFF, ((*(s16 *)((u8 *)(arg0) + (0xC))) + D_84186BC0) & 0xFFFF, (*(u8 *)((u8 *)(temp_v0) + (0xF))), (*(u16 *)((u8 *)(temp_v0) + (0xC))), (*(s32 *)((u8 *)(temp_v0) + (0))));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84144118.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841442BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84144410.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84144514.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84144634.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8414491C.s")
#endif

#ifdef VERSION_US
extern u8 *D_84195200[];
extern u8 D_84186FFC[];
extern s16 D_84186DF0;
extern s16 D_84186DFC;
extern void func_8004C54C(s32, s32);
extern s32 func_8004C8A0(void *, s32, s32, s32);
extern void func_800495F8(s32, s32, s32, void *);
void func_84144A00(void *arg0) {
    u8 index;
    u8 sp20[0x28];

    index = *(u8 *)((u8 *)arg0 + 1);
    func_8004C54C(0x1A, D_84195200[index] + 0x34);
    func_8004C8A0(
        sp20 + 4,
        0x28,
        0x10,
        D_84186FFC[*(u32 *)((u8 *)arg0 + 4)]);
    func_800495F8(
        *(s16 *)((u8 *)arg0 + 0xA) + D_84186DF0,
        *(s16 *)((u8 *)arg0 + 0xC) + D_84186DFC,
        1,
        sp20 + 4);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84144A90.s")
#endif

#ifdef VERSION_US
extern s16 D_84186E10, D_84186E14;
extern u16 D_84186E18;
extern u8 *func_8413D260(void);
extern void func_8004989C(s32);
extern void func_800495BC(s32, s32, s32 *);
void func_84144B98(void *arg0) {
    struct S { s32 *resource; s32 pad; } local;

    local.resource = func_8413D260();
    func_8004989C(D_84186E18);
    func_800495BC(*(s16 *)((u8 *)arg0 + 0xA) + D_84186E10,
                  *(s16 *)((u8 *)arg0 + 0xC) + D_84186E14,
                  local.resource);
}
#endif

#ifdef VERSION_US
extern s32 func_8004C874(s32, s32);
extern void func_800495BC(s32, s32, s32 *);
extern u16 D_8419D7A0;
void func_84144BF4(void *arg0) { s32 resource = func_8004C874(0x16, 0); *(s16 *)((u8 *)arg0 + 0xA) = *(s16 *)((u8 *)arg0 + 0xA) - 1; if (*(s16 *)((u8 *)arg0 + 0xA) < -(s32)D_8419D7A0) { *(s16 *)((u8 *)arg0 + 0xA) = 0; } func_800495BC(*(s16 *)((u8 *)arg0 + 0xA), *(s16 *)((u8 *)arg0 + 0xC), (s32 *)resource); func_800495BC(*(s16 *)((u8 *)arg0 + 0xA) + D_8419D7A0, *(s16 *)((u8 *)arg0 + 0xC), (s32 *)resource); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84144C88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84144EF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841450B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84145340.s")
#endif

#ifdef VERSION_US
extern void func_84144EF4();
extern void func_841450B4();
extern void func_84145340();
void func_84145744(void *arg0) {
    u8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = (*(u8 *)((u8 *)(arg0) + (8)));
    if (!(temp_v0 & 1) && !(temp_v0 & 2)) {
        temp_v0_2 = (*(u8 *)((u8 *)(arg0) + (0)));
        switch (temp_v0_2) {                        /* irregular */
        case 11:
            func_84144EF4();
            return;
        case 12:
            func_841450B4();
            return;
        case 13:
            func_84145340();
            break;
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_8413ED28(s16, s16, u16, u16);
void func_841457C4(void *arg0) {
    if (!((*(u8 *)((u8 *)(arg0) + (8))) & 1) && ((*(u8 *)((u8 *)(arg0) + (0))) == 0x12)) {
        ParticleGfx_SetPrimColor_fragment79((*(u8 *)((u8 *)(arg0) + (0x22))), (*(u8 *)((u8 *)(arg0) + (0x23))), (*(u8 *)((u8 *)(arg0) + (0x24))), (*(u8 *)((u8 *)(arg0) + (0x25))));
        func_8413ED28((*(s16 *)((u8 *)(arg0) + (0xA))), (*(s16 *)((u8 *)(arg0) + (0xC))), (*(u16 *)((u8 *)(arg0) + (0xE))), (*(u16 *)((u8 *)(arg0) + (0x10))));
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84145830.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841459E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84145AB4.s")
#endif

void func_84145B24(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84145B2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84145BA0.s")
#endif

#ifdef VERSION_US
extern u8 D_84186868[];
extern u8 D_841869E0[];
extern u8 D_841868B8[];
extern u8 D_84186890[];
extern void func_84140690(void *arg0);
extern void func_84140C8C(void *arg0);
void func_8414605C(void) {
    func_84140690(D_84186868);
    gSPDisplayList(D_800D0510++, D_841869E0);
    func_84142E44(D_841868B8);
    func_84140C8C(D_84186890);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841460C0.s")
#endif

#ifdef VERSION_US
extern u16 D_84186BAC[];
extern u16 D_84186BB0[];
extern u16 D_84186BB4;
extern u16 D_84186BB8;
void func_8414640C(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186BAC[index];
    *(u16 *)(arg0 + 0xC) = D_84186BB0[index];
    *(u16 *)(arg0 + 0xE) = D_84186BB4;
    *(u16 *)(arg0 + 0x10) = D_84186BB8;
}
#endif

#ifdef VERSION_US
extern u16 D_84186BC4[];
extern u16 D_84186BC8;
void func_84146450(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186BAC[index];
    *(u16 *)(arg0 + 0xC) = D_84186BC4[index];
    *(u16 *)(arg0 + 0xE) = D_84186BB4;
    *(u16 *)(arg0 + 0x10) = D_84186BC8;
}
#endif

#ifdef VERSION_US
extern u16 D_84186BA0[];
extern u16 D_84186BA4[];
extern u16 D_84186BA8;
void func_84146494(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186BA0[index];
    *(u16 *)(arg0 + 0xC) = D_84186BA4[index];
    *(u16 *)(arg0 + 0xE) = D_84186BA8;
    *(u16 *)(arg0 + 0x10) = D_84186BA8;
}
#endif

#ifdef VERSION_US
extern u16 D_84186BF4[];
extern u16 D_84186BF8[];
void func_841464D8(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186BF4[index];
    *(u16 *)(arg0 + 0xC) = D_84186BF8[index];
}
#endif

#ifdef VERSION_US
extern u16 D_84186C00[];
extern u16 D_84186C0C[];
void func_84146504(u8 *arg0, u8 arg1) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = *(u16 *)((u8 *)D_84186C00 + (arg1 << 2) + (index << 1));
    *(u16 *)(arg0 + 0xC) = *(u16 *)((u8 *)D_84186C0C + (index << 1));
}
#endif

#ifdef VERSION_US
extern u16 D_84186C2C[];
extern u16 D_84186C30[];
extern s16 D_84186C34;
extern s16 D_84186C36;
extern s16 D_84186C38;
extern s16 D_84186C3A;
extern s16 D_84186C3C;
extern s16 D_84186C3E;
extern s16 D_84186C40;
extern s16 D_84186C42;
void func_84146540(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186C2C[index];
    *(u16 *)(arg0 + 0xC) = D_84186C30[index];
    *(u16 *)(arg0 + 0x12) = D_84186C34;
    *(u16 *)(arg0 + 0x14) = D_84186C3C;
    *(u16 *)(arg0 + 0x16) = D_84186C36;
    *(u16 *)(arg0 + 0x18) = D_84186C3E;
    *(u16 *)(arg0 + 0x1A) = D_84186C38;
    *(u16 *)(arg0 + 0x1C) = D_84186C40;
    *(u16 *)(arg0 + 0x1E) = D_84186C3A;
    *(u16 *)(arg0 + 0x20) = D_84186C42;
}
#endif

#ifdef VERSION_US
extern u16 D_84186C8C[];
extern u16 D_84186C90[];
extern u16 D_84186C94;
extern u16 D_84186C98;
void func_841465CC(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186C8C[index];
    *(u16 *)(arg0 + 0xC) = D_84186C90[index];
    *(u16 *)(arg0 + 0xE) = D_84186C94;
    *(u16 *)(arg0 + 0x10) = D_84186C98;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84146610.s")
#endif

#ifdef VERSION_US
extern u16 D_84186CD4[];
extern u16 D_84186CE0[];
extern u16 D_84186CE4;
extern u16 D_84186CEC;
void func_841466B0(void *arg0) {
    s32 index;
    s32 offset;

    index = *(u8 *)((u8 *)arg0 + 1);
    offset = index << 1;
    *(u16 *)((u8 *)arg0 + 0xA) = *(u16 *)((u8 *)D_84186CD4 + offset);
    *(u16 *)((u8 *)arg0 + 0xC) = *(u16 *)((u8 *)D_84186CE0 + offset);
    *(u16 *)((u8 *)arg0 + 0xE) = D_84186CE4;
    *(u16 *)((u8 *)arg0 + 0x10) = D_84186CEC;
    *(s16 *)((u8 *)arg0 + 0x12) = *(s16 *)((u8 *)arg0 + 0xA);
    *(s16 *)((u8 *)arg0 + 0x14) = *(s16 *)((u8 *)arg0 + 0xC);
}
#endif

#ifdef VERSION_US
extern u16 D_84186D3C[];
extern u16 D_84186D40[];
extern u16 D_84186D44;
extern u16 D_84186D48;
void func_84146704(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186D3C[index];
    *(u16 *)(arg0 + 0xC) = D_84186D40[index];
    *(u16 *)(arg0 + 0xE) = D_84186D44;
    *(u16 *)(arg0 + 0x10) = D_84186D48;
}
#endif

#ifdef VERSION_US
extern u16 D_84186DD8[];
extern u16 D_84186DDC[];
extern u16 D_84186DE0;
extern u16 D_84186DE4;
extern u16 D_84186DEC;
extern s16 D_84186DF8;
extern s16 D_8419D7A4[];
void func_84146748(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186DD8[index];
    *(u16 *)(arg0 + 0xC) = D_84186DDC[index];
    *(u16 *)(arg0 + 0xE) = D_84186DE0;
    *(u16 *)(arg0 + 0x10) = D_84186DE4;
    *(u16 *)(arg0 + 0x12) = D_8419D7A4[0] - D_84186DEC;
    *(u16 *)(arg0 + 0x14) = D_84186DF8;
    *(u16 *)(arg0 + 0x16) = D_8419D7A4[1] - D_84186DEC;
    *(u16 *)(arg0 + 0x18) = D_84186DF8;
}
#endif

#ifdef VERSION_US
extern u16 D_84186E00;
extern u16 D_84186E04;
extern u16 D_84186E08;
extern u16 D_84186E0C;
void func_841467D4(u8 *arg0) {
    *(u16 *)(arg0 + 0xA) = D_84186E00;
    *(u16 *)(arg0 + 0xC) = D_84186E04;
    *(u16 *)(arg0 + 0xE) = D_84186E08;
    *(u16 *)(arg0 + 0x10) = D_84186E0C;
}
#endif

#ifdef VERSION_US
extern u16 D_84186E2C[];
extern u16 D_84186E30[];
extern u16 D_84186E34;
extern u16 D_84186E38;
extern s16 D_84186E3C;
extern s16 D_84186E40[];
extern s16 D_84186E44;
extern s16 D_84186E48[];
void func_84146808(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186E2C[index];
    *(u16 *)(arg0 + 0xC) = D_84186E30[index];
    *(u16 *)(arg0 + 0xE) = D_84186E34;
    *(u16 *)(arg0 + 0x10) = D_84186E38;
    *(u16 *)(arg0 + 0x12) = D_84186E3C;
    *(u16 *)(arg0 + 0x14) = D_84186E40[index];
    *(u16 *)(arg0 + 0x16) = D_84186E44;
    *(u16 *)(arg0 + 0x18) = D_84186E48[index];
}
#endif

#ifdef VERSION_US
extern u16 D_84186E4C[];
extern u16 D_84186E50[];
extern u16 D_84186E54[];
extern u16 D_84186E58[];
extern u16 D_84186E5C[];
extern u16 D_84186E60;
extern u16 D_84186E64;
extern u16 D_84186E68;
extern s16 D_84186E6C;
extern s16 D_84186E70[];
extern s16 D_84186E74;
extern s16 D_84186E78[];
extern s16 D_84186E7C;
extern s16 D_84186E80;
extern s16 D_84186E84;
extern s16 D_84186E88;
void func_84146884(u8 *arg0) {
    u8 temp_v0;
    u8 **temp_v1;
    s32 temp_a1;
    s32 temp_a1_2;

    temp_v0 = arg0[1];
    temp_v1 = &((u8 **)&D_841951F8)[temp_v0];
    temp_a1 = temp_v0 * 2;
    if ((*temp_v1)[2] == 1) {
        temp_a1_2 = temp_v0 * 2;
        *(u16 *)(arg0 + 0xA) = *(u16 *)((u8 *)D_84186E4C + temp_a1_2);
        if ((*temp_v1)[8] < 4) {
            *(u16 *)(arg0 + 0xC) = *(u16 *)((u8 *)D_84186E50 + temp_a1_2);
        } else {
            *(u16 *)(arg0 + 0xC) = *(u16 *)((u8 *)D_84186E54 + temp_a1_2);
        }
        *(u16 *)(arg0 + 0xE) = D_84186E60;
        *(u16 *)(arg0 + 0x10) = D_84186E38;
        *(s16 *)(arg0 + 0x12) = D_84186E6C;
        *(s16 *)(arg0 + 0x14) = *(s16 *)((u8 *)D_84186E70 + temp_a1_2);
        *(s16 *)(arg0 + 0x16) = D_84186E74;
        *(s16 *)(arg0 + 0x18) = *(s16 *)((u8 *)D_84186E78 + temp_a1_2);
        return;
    }
    *(u16 *)(arg0 + 0xA) = *(u16 *)((u8 *)D_84186E58 + temp_a1);
    *(u16 *)(arg0 + 0xC) = *(u16 *)((u8 *)D_84186E5C + temp_a1);
    *(u16 *)(arg0 + 0xE) = D_84186E64;
    *(u16 *)(arg0 + 0x10) = D_84186E68;
    *(s16 *)(arg0 + 0x12) = D_84186E7C;
    *(s16 *)(arg0 + 0x14) = D_84186E80;
    *(s16 *)(arg0 + 0x16) = D_84186E84;
    *(s16 *)(arg0 + 0x18) = D_84186E88;
}
#endif

#ifdef VERSION_US
extern u16 D_84186E8C[];
extern u16 D_84186E90[];
extern u16 D_84186E94;
extern u16 D_84186E98;
void func_841469BC(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186E8C[index];
    *(u16 *)(arg0 + 0xC) = D_84186E90[index];
    *(u16 *)(arg0 + 0xE) = D_84186E94;
    *(u16 *)(arg0 + 0x10) = D_84186E98;
}
#endif

#ifdef VERSION_US
extern u16 D_84186EA4;
extern u16 D_84186EA8;
extern u16 D_84186EAC;
extern u16 D_84186EB0;
void func_84146A00(u8 *arg0) {
    *(u16 *)(arg0 + 0xA) = D_84186EA4;
    *(u16 *)(arg0 + 0xC) = D_84186EA8;
    *(u16 *)(arg0 + 0xE) = D_84186EAC;
    *(u16 *)(arg0 + 0x10) = D_84186EB0;
}
#endif

#ifdef VERSION_US
extern u16 D_84186E1C[];
extern u16 D_84186E20;
extern u16 D_84186E24;
extern u16 D_84186E28;
void func_84146A34(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186E1C[index];
    *(u16 *)(arg0 + 0xC) = D_84186E20;
    *(u16 *)(arg0 + 0xE) = D_84186E24;
    *(u16 *)(arg0 + 0x10) = D_84186E28;
}
#endif

#ifdef VERSION_US
extern u16 D_84186EF0[];
extern u16 D_84186EF4[];
extern u16 D_84186EF8;
extern u16 D_84186EFC;
void func_84146A74(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186EF0[index];
    *(u16 *)(arg0 + 0xC) = D_84186EF4[index];
    *(u16 *)(arg0 + 0xE) = D_84186EF8;
    *(u16 *)(arg0 + 0x10) = D_84186EFC;
}
#endif

#ifdef VERSION_US
extern u16 D_84186ED8, D_84186EDC;

void func_84146AB8(u8 *arg0) {
    *(u16 *)(arg0 + 0xA) = D_84186ED8;
    *(u16 *)(arg0 + 0xC) = D_84186EDC;
}
#endif

#ifdef VERSION_US
extern u16 D_84186EE0, D_84186EE4;

void func_84146AD4(u8 *arg0) {
    *(u16 *)(arg0 + 0xA) = D_84186EE0;
    *(u16 *)(arg0 + 0xC) = D_84186EE4;
}
#endif

#ifdef VERSION_US
extern u16 D_84186EE8, D_84186EEC;

void func_84146AF0(u8 *arg0) {
    *(u16 *)(arg0 + 0xA) = D_84186EE8;
    *(u16 *)(arg0 + 0xC) = D_84186EEC;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84146B0C.s")
#endif

#ifdef VERSION_US
void func_84146CF8(u8 *arg0) {
    u8 index = arg0[1];
    *(u16 *)(arg0 + 0xA) = D_84186BAC[index];
    *(u16 *)(arg0 + 0xC) = D_84186BB0[0];
    *(u16 *)(arg0 + 0xE) = D_84186BB4;
    *(u16 *)(arg0 + 0x10) = D_84186BC8;
}
#endif

#ifdef VERSION_US
extern void func_84146CF8(u8 *);
extern void func_841467D4(u8 *);
void func_84146D38(u8 *arg0) {
    switch (arg0[0]) {
        case 1:
            func_84146CF8(arg0);
            break;
        case 0x10:
        case 0x11:
            func_841467D4(arg0);
            break;
        case 0x12:
            return;
        default:
            return;
    }
}
#endif

#ifdef VERSION_US
void func_84146D98(u8 *arg0, u8 *arg1) {
    arg0[0x22] = arg1[0];
    arg0[0x23] = arg1[1];
    arg0[0x24] = arg1[2];
    arg0[0x25] = 0xFF;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84146DBC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84146F24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84147008.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841470C4.s")
#endif

#ifdef VERSION_US
extern u8 *func_841460C0(u8, u8, u8);
extern void func_841470C4(u8 *, u8, s32);
void func_84147228(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4) { func_841470C4(func_841460C0(arg0, arg1, arg2), arg3, arg4); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84147270.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8414735C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841474B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8414760C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841476E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8414782C.s")
#endif

#ifdef VERSION_US
extern u8 D_84186F34;
void func_84147968(void *arg0, s16 arg1) {
    s32 var_v0;

    if (arg1 > 0) {
        var_v0 = D_84186F34 - *(u8 *)((u8 *)arg0 + 9);
    } else {
        var_v0 = *(u8 *)((u8 *)arg0 + 9) - 1;
    }
    *(s16 *)((u8 *)arg0 + 0xA) = (s16) ((var_v0 * 0xC5) / 6 - 0x25);
    *(s16 *)((u8 *)arg0 + 0xC) = 0;
    *(s16 *)((u8 *)arg0 + 0xE) = (s16) (0x140 - (*(s16 *)((u8 *)arg0 + 0xA) << 1));
    *(s16 *)((u8 *)arg0 + 0x10) = 0xF0;
    *(u8 *)((u8 *)arg0 + 0x22) = 0;
    *(u8 *)((u8 *)arg0 + 0x23) = 0;
    *(u8 *)((u8 *)arg0 + 0x24) = 0;
    *(u8 *)((u8 *)arg0 + 0x25) = 0xFF;
    *(u8 *)((u8 *)arg0 + 8) = *(u8 *)((u8 *)arg0 + 8) & 0xFFFC;
}
#endif

#ifdef VERSION_US
extern u8 D_84186F34;
void func_84147A04(void *arg0, s16 arg1) {
    s32 var_v0;

    if (arg1 > 0) {
        var_v0 = D_84186F34 - *(u8 *)((u8 *)arg0 + 9);
    } else {
        var_v0 = *(u8 *)((u8 *)arg0 + 9) - 1;
    }
    *(s16 *)((u8 *)arg0 + 0xC) = (s16) ((var_v0 * 0xB8) / 6 - 0x1E);
    *(s16 *)((u8 *)arg0 + 0xA) = 0;
    *(s16 *)((u8 *)arg0 + 0xE) = 0x140;
    *(s16 *)((u8 *)arg0 + 0x10) = (s16) (0xF0 - (*(s16 *)((u8 *)arg0 + 0xC) << 1));
    *(u8 *)((u8 *)arg0 + 0x22) = 0;
    *(u8 *)((u8 *)arg0 + 0x23) = 0;
    *(u8 *)((u8 *)arg0 + 0x24) = 0;
    *(u8 *)((u8 *)arg0 + 0x25) = 0xFF;
    *(u8 *)((u8 *)arg0 + 8) = *(u8 *)((u8 *)arg0 + 8) & 0xFFFC;
}
#endif

#ifdef VERSION_US
extern u8 D_84186F34;
extern void func_8414782C(void *, s32, s32);
extern void func_84147968(void *, s16);
extern void func_84147A04(void *, s16);
void func_84147A9C(void *arg0) {
    s32 temp_v0;

    if (D_84186F34 >= *(u8 *)((u8 *)arg0 + 9)) {
        temp_v0 = *(s32 *)((u8 *)arg0 + 4);
        switch (temp_v0) {
        case 0:
            func_8414782C(arg0, 1, 0x3FAA3D71);
            return;
        case 1:
            func_84147968(arg0, 1);
            return;
        case 2:
            func_84147A04(arg0, 1);
            break;
        }
    }
}
#endif

#ifdef VERSION_US
extern u8 D_84186F34;
extern void func_8414782C(void *, s32, s32);
extern void func_84147968(void *, s16);
extern void func_84147A04(void *, s16);
void func_84147B20(void *arg0) {
    s32 temp_v0;

    if (D_84186F34 >= *(u8 *)((u8 *)arg0 + 9)) {
        temp_v0 = *(s32 *)((u8 *)arg0 + 4);
        switch (temp_v0) {
        case 0:
            func_8414782C(arg0, -1, 0x3FAA3D71);
            return;
        case 1:
            func_84147968(arg0, -1);
            return;
        case 2:
            func_84147A04(arg0, -1);
            break;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84147BA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84147C9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84147E50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84147FF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_84148054.s")
#endif

#ifdef VERSION_US
extern void func_84146D38(u8 *arg0);
void func_841480C0(u8 *arg0) { u8 value = arg0[9]; if (arg0[0] == 1) { func_84146D38(arg0); if (value >= 2) { *(s16 *)(arg0 + 0xA) += value * (((value & 1) << 1) - 1); } } }
#endif

#ifdef VERSION_US
extern u8 D_84186F3C;
extern u8 D_84186F50;
void func_84148128(u8 *arg0) {
    s32 temp_v1;

    temp_v1 = func_8413D26C((*(u8 *)((u8 *)(arg0) + (1))), (*(u8 *)((u8 *)(arg0) + (2)))) & 0xFF;
    if ((*(u8 *)((u8 *)(arg0) + (0))) == 1) {
        if (((s32) (*(u8 *)((u8 *)(arg0) + (9))) / 4) & 1) {
            func_84146D98(arg0, &D_84186F3C);
            return;
        }
        func_84146D98(arg0, (temp_v1 * 3) + &D_84186F50);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841481BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_841482BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3ADCA0/func_8414831C.s")
#endif

#ifdef VERSION_US
extern void func_8004C948(s32);
void func_84148410(void) {
    func_8004C948(0x7A);
    func_8004C948(0x22);
    func_8004C948(0x1F);
    func_8004C948(0x21);
    func_8004C948(0x20);
    func_8004C948(0x23);
    func_8004C948(0x1E);
    func_8004C948(0x24);
    func_8004C8C0(0x131);
}
#endif

#ifdef VERSION_US
extern u8 D_841865EA[];
u8 func_84148470(u8 arg0) {
    return D_841865EA[arg0 * 40];
}
#endif

#ifdef VERSION_US
extern u8 *func_841460C0(u8, u8, u8);
s32 func_84148494(u8 arg0, u8 arg1, u8 arg2) {
    return *(s32 *)(func_841460C0(arg0, arg1, arg2) + 4);
}
#endif

#ifdef VERSION_US
s32 func_841484CC(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    u8 *value;
    value = func_841460C0(arg0, arg1, arg2);
    return (value[8] & arg3) != 0;
}
#endif

#ifdef VERSION_US
s32 func_84148510(u8 *arg0) {
    return 0;
}
#endif
