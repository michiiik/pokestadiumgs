#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82604390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826043F8.s")

void func_82604628(s16 *arg0, s32 arg1, s32 arg2) {
    s16 result;
    s32 type;
    s32 value;

    result = -1;
    type = arg1 & 0xFF00;
    switch (type) {
    case 0:
        result = 0x57;
        break;
    case 0x100:
    case 0x200:
    case 0x700:
        value = arg1 & 0xFF;
        switch (value) {
        case 0x10: result = 0x5B; break;
        case 0x20: result = 0x64; break;
        default: result = 0x6E; break;
        }
        break;
    case 0x300:
        switch (arg2) {
        case 0xF: result = 0x72; break;
        case 0x18: result = 0x6A; break;
        default: result = 0x6F; break;
        }
        break;
    }
    if (arg0 != NULL) *arg0 = result;
}

extern void func_826043F8(s16 *, s16 *, s32, s32);
extern s32 func_8004C8C0(s32);
s32 func_826046D0(s32 arg0, s32 arg1) {
    s16 value;
    s32 result;

    result = 0;
    func_826043F8(&value, 0, arg0, arg1);
    if (value >= 0) {
        result = func_8004C8C0(value);
    }
    return result;
}

extern s32 func_8004C990(s32, s32);
extern void func_826043F8(s16 *, s16 *, s32, s32);
s32 func_82604720(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 result;
    s16 value2;
    s16 value1;

    result = 0;
    func_826043F8(&value2, &value1, arg1, arg2);
    if (value2 >= 0) {
        if (value1 >= 0) {
            if (arg3 != 0) {
                arg0[0] = func_8004C990(0x71, 0);
                result = 1;
            }
            arg0[result] = func_8004C990((s32)value2, (s32)value1);
            result += 1;
        }
    }
    return result;
}

extern void func_82604628(s16 *, s32, s32);
extern s32 func_8004C8C0(s32);
s32 func_826047C4(s32 arg0, s32 arg1) {
    s16 value;
    s32 result;

    func_82604628(&value, arg0, arg1);
    if (value >= 0) {
        result = func_8004C8C0(value);
    } else {
        result = 1;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82604814.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826049A0.s")

extern s16 D_82615542[];
extern s32 func_8004C990(s32, s32);
s32 func_82604A78(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 result;
    s32 next;

    result = 0;
    switch (arg1) {
    case 15:
        arg0[0] = func_8004C990(0x72, 1);
        result = 1;
        break;
    case 11:
        arg0[0] = func_8004C990(0x6B, 0);
        result = result + 1;
        arg0[result] = func_8004C990(0x65, D_82615542[arg2]);
        result = result + 1;
        break;
    case 14:
        arg0[0] = func_8004C990(0x6F, 1);
        result = result + 1;
        arg0[result] = func_8004C990(0x65, D_82615542[arg2]);
        result = result + 1;
        break;
    case 24:
        arg0[0] = func_8004C990(0x6A, 1);
        result = 1;
        break;
    default:
        next = arg2 + 1;
        if (arg3 != next) goto indexed_default;
        arg0[0] = func_8004C990(0x6F, 0);
        result = 1;
        break;
indexed_default:
        if (arg2 >= 6) goto done_default;
        arg0[0] = func_8004C990(0x6F, 2);
        result = result + 1;
        arg0[result] = func_8004C990(0x65, D_82615542[arg2]);
        result = result + 1;
done_default:
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82604C08.s")

void *func_82604C40(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 var_v0;
    u8 *var_a0;
    void *var_v1;

    var_v1 = NULL;
    var_v0 = 0;
    if (arg3 > 0) {
        var_a0 = arg2;
loop_2:
        var_v0 += 1;
        if ((arg0 == *(s16 *)var_a0) && (arg1 == *(s16 *)(var_a0 + 2))) {
            var_v1 = var_a0;
        } else {
            var_a0 += 0x298;
            if (var_v0 != arg3) {
                goto loop_2;
            }
        }
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82604C98.s")

extern s32 func_82604C98(s32, s32, s32, s32);
s32 func_82604CF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 result;
    s32 index;

    result = 0x29;
    index = func_82604C98(arg0, arg1, arg2, arg3);
    if (index >= 0) {
        result = *(s16 *)((index * 6) + arg0 + 4) + 0x29;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82604D40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82605110.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82605218.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826053A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826057A8.s")

s32 func_826058CC(s32 arg0) {
    s32 result;

    switch (arg0) {
    case 0:
    case 4:
        result = 0;
        break;
    case 1:
    case 3:
        result = 1;
        break;
    default:
        result = -1;
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82605908.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82605E04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82605EF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82605FE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826063AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82606548.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826065B0.s")

void func_8260675C(u8 *arg0) {
    if (arg0 != NULL && *(s16 *)(arg0 + 6) == 0) {
        *(s16 *)(arg0 + 6) = 1;
        *(s16 *)(arg0 + 8) = 0;
    }
}

extern void func_800226C0(s32);
void func_82606784(u8*a0,s32 a1,s32 a2,s32 a3){if(*(s16*)(a0+6)==0){*(s16*)(a0+6)=1;*(s16*)(a0+8)=0;*(s16*)(a0+0x1C)=a1;*(s16*)(a0+0x1E)=a3;*(s16*)(a0+0x20)=a2;*(s16*)(a0+0x22)=a3;func_800226C0(0x6D);}}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826067D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82606B28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82606CE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82606E90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82606EC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82607528.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82607734.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82607790.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826078B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82607AA0.s")

extern void func_826067D4();
extern void func_82607528();
extern void func_82607790();
extern void func_82607AA0();
void func_82607B74(void *arg0) {
    s16 temp_v0;

    temp_v0 = (*(s16 *)((u8 *)(arg0) + (6)));
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_826067D4();
        return;
    case 2:
        func_82607528();
        return;
    case 3:
        func_82607790();
        return;
    case 4:
        func_82607AA0();
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82607BF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82607E40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82608054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82608270.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826082C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260850C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260899C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82608C1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82608EC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826090F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260933C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82609584.s")

extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern void func_82609584(s32, s32, s32, s16);

void func_82609730(void *arg0, s32 arg1) {
    s16 temp_s5;
    s16 temp_s6;
    s32 temp_a2;
    s32 var_s0;
    u8 *temp_a3;
    u8 *var_s1;
    u8 *var_s2;
    temp_a3 = (u8 *)arg0 + 0x30;
    if (arg1 != 0) {
        gSPDisplayList(D_800D0510++, D_80094E38);
        gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
    }
    temp_s5 = *(s16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg0 + 0x10);
    temp_s6 = *(s16 *)((u8 *)arg0 + 0x16) + *(s16 *)((u8 *)arg0 + 0x12);
    var_s0 = 0;
    if (*(s16 *)(temp_a3 + 4) > 0) {
        var_s1 = temp_a3;
        var_s2 = temp_a3;
        do {
            temp_a2 = *(s32 *)(var_s2 + 0x24);
            if ((*(s16 *)(var_s1 + 0xA) < 0xFF) && (temp_a2 != 0)) {
                func_82609584(temp_s5 + (var_s0 * 0x86) + 0xB, temp_s6 + 9, temp_a2, *(s16 *)(var_s1 + 0x12));
            }
            var_s0 += 1;
            var_s1 += 2;
            var_s2 += 4;
        } while (var_s0 < *(s16 *)(temp_a3 + 4));
    }
}

extern s16 D_826156C0[];
extern s16 D_826156C4[];
void func_82609868(void *arg0, s32 arg1, s32 arg2) {
    s16 temp_s6;
    s16 temp_s5;
    s32 index;
    if (arg2 != 0) {
        if (arg1 != 0) {
            gSPDisplayList(D_800D0510++, D_80094E38);
            gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
        }
        index = *(s16 *)((u8 *)arg0 + 2) * 2;
        temp_s5 = *(s16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg0 + 0x10);
        temp_s6 = *(s16 *)((u8 *)arg0 + 0x16) + *(s16 *)((u8 *)arg0 + 0x12);
        func_82609584(*(s16 *)((u8 *)D_826156C0 + index) + temp_s5, *(s16 *)((u8 *)D_826156C4 + index) + temp_s6, arg2, 1);
    }
}

extern void func_80044270(s16, s16, s16, s16, s32, s32, s32, s32, s32);
extern void func_80046204(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_82609938(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    if (arg4 > 0) {
        do {
            temp_v0 = arg4 - var_s1;
            if (temp_v0 < arg5) var_s0 = temp_v0;
            else var_s0 = arg5;
            func_80046204((arg3 * var_s1 * 2) + arg2, 0, 2, arg3, var_s0, 0, 0, arg3, var_s0 - 1, 0, 2, 2, 0, 0, 0, 0);
            func_80044270((s16)arg0, (s16)(arg1 + var_s1), (s16)arg3, (s16)var_s0, 0, 0, 0x400, 0x400, 0);
            var_s1 += arg5;
        } while (var_s1 < arg4);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82609A88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82609D84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260A0B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260A6B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260AF30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260B424.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260B8CC.s")

extern s32 func_8004D1FC(u8 *);
extern void func_82607BF4(s16, u8 *, u8 *, s16, s32);
extern void func_8260B8CC(s32, s32, s32, s32);
extern u8 D_80094E78[];
extern s32 func_8004C990(s32, s32);
extern Gfx * D_800D0510;
void func_8260BBA8(void *arg0, s32 arg1) {
    s32 temp_v0;
    s16 sp4A;
    s16 sp48;
    struct Color { u8 r; u8 g; u8 b; u8 a; } sp44;
    struct Color2 { u8 r; u8 g; u8 b; u8 a; } sp40;

    temp_v0 = func_8004C990(0x51, 0);
    if (temp_v0 != 0) {
        sp48 = *(s16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg0 + 0x10);
        sp4A = *(s16 *)((u8 *)arg0 + 0x16) + *(s16 *)((u8 *)arg0 + 0x12);
        if (arg1 != 0) {
            gSPDisplayList(D_800D0510++, D_80094E78);
            gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
            func_8004D1FC((u8 *)temp_v0);
        }
        func_82607BF4(*(s16 *)arg0, (u8 *)&sp44, (u8 *)&sp40,
                      *(s16 *)((u8 *)arg0 + 0xC),
                      (*(u16 *)((u8 *)arg0 + 4) & 8) != 0);
        gDPPipeSync(D_800D0510++);
        gDPSetEnvColor(D_800D0510++, sp44.r, sp44.g, sp44.b, 0xFF);
        gDPSetPrimColor(D_800D0510++, 0, 0, sp40.r, sp40.g, sp40.b, 0xFF);
        func_8260B8CC(sp48 + 0x36, sp4A + 0x24, 0x12C, 0x61);
        func_8260B8CC(sp48 + 0x36, sp4A + 0xAC, 0x12C, 0x52);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260BD50.s")

extern Gfx *D_800D0510;
extern u8 D_80094D90[];
extern void Gfx_FillRectRgb(s16, s16, s16, s16, u8, u8, u8);

void func_8260BE24(u8 *arg0, s32 arg1) {
    s16 pad;
    s16 temp_t1;
    s16 temp_t0;
    temp_t1 = *(s16 *)(arg0 + 0x14) + *(s16 *)(arg0 + 0x10);
    temp_t0 = *(s16 *)(arg0 + 0x16) + *(s16 *)(arg0 + 0x12);
    if (arg1 != 0) {
        gSPDisplayList(D_800D0510++, D_80094D90);
    }
    Gfx_FillRectRgb(temp_t1 + 0x3A, temp_t0 + 0x28, 0x124, 0x59, 0, 0, 0);
    Gfx_FillRectRgb(temp_t1 + 0x3A, temp_t0 + 0xB0, 0x124, 0x4A, 0, 0, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260BEF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260C2B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260C7D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260C988.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260CC24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260CF84.s")

s32 func_8004C990(s32, s32);

s32 func_8260D3F4(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v0;

    if (arg0 != 0) {
        var_v0 = func_8004C990(0x6D, 1);
    } else {
        var_v0 = func_8004C990(0x6D, 0);
    }
    return var_v0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260D440.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260D820.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260DB98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260DD84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260E03C.s")

extern void Ui_DrawAnimatedTextureMarker(s16, s16);
extern s16 D_8261A4AE;
void func_8260E140(u8 *arg0, s32 arg1) {
    s16 x;
    s16 y;

    x = *(s16 *)(arg0 + 0x14) + *(s16 *)(arg0 + 0x10);
    y = *(s16 *)(arg0 + 0x16) + *(s16 *)(arg0 + 0x12);
    Ui_DrawAnimatedTextureMarker((s16)(x + 0x3C), (s16)(y + D_8261A4AE * 0x1F + 0xBC));
}

extern void func_800498C4(void);
extern void func_800499EC(void);
void func_8004972C(s32 a0, s32 a1, s32 a2, s32 a3);
void func_800496A4(s32 a0, s32 a1);
void func_8004989C(s32 arg0);
extern void func_800495BC(s32, s32, s32 *);
extern u8 D_82615738[];
extern u8 D_8261573C[];
extern u8 D_82615740[];
void func_8260E1B4(void *arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 arg4) {
    s16 sp26;
    s16 sp24;
    s32 idx;
    s32 idx2;

    sp24 = *(s16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg0 + 0x10);
    sp26 = *(s16 *)((u8 *)arg0 + 0x16) + *(s16 *)((u8 *)arg0 + 0x12);
    func_800498C4();
    func_8004972C(0xFF, 0xFF, 0xFF, arg4);
    func_800496A4(4, 0);
    func_8004989C(0x10);
    if (arg2 != NULL) {
        idx = *(s16 *)((u8 *)arg0 + 2) * 2;
        func_800495BC(*(s16 *)(D_82615738 + idx) + sp24, *(s16 *)(D_8261573C + idx) + sp26, arg2);
    }
    func_800496A4(8, 0);
    if (arg3 != NULL) {
        idx2 = *(s16 *)((u8 *)arg0 + 2) * 2;
        func_800495BC(*(s16 *)(D_82615738 + idx2) + sp24, *(s16 *)(D_82615740 + idx2) + sp26, arg3);
    }
    func_800499EC();
}

extern void func_800495BC(s32, s32, s32 *);
extern void func_800496A4(s32 a0, s32 a1);
extern void func_8004972C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8004989C(s32 arg0);
extern void func_800498C4(void);
extern void func_800499EC(void);
void func_8260E2C4(void *arg0, s32 arg1) {
    s16 pad2;
    s16 pad1;
    s16 sp22;
    s16 sp20;
    struct Entry { s16 x; s16 y; s16 count; s16 pad; } *base;

    sp20 = *(s16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg0 + 0x10);
    sp22 = *(s16 *)((u8 *)arg0 + 0x16) + *(s16 *)((u8 *)arg0 + 0x12);
    if (*(s16 *)((u8 *)arg0 + 0x2A) == *(s16 *)((u8 *)arg0 + 0x24)) {
        base = (struct Entry *)((u8 *)arg0 + 0x30);
        if (*(s16 *)((u8 *)arg0 + 0x2E) == *(s16 *)((u8 *)arg0 + 0x26) && base->count > 0) {
            func_800498C4();
            func_8004972C(0xFF, 0xFF, 0xFF, base->count);
            func_800496A4(8, 0);
            func_8004989C(0x14);
            if (*(s32 **)((u8 *)base + 8) != NULL) {
                func_800495BC(sp20 + base->x, sp22 + base->y, *(s32 **)((u8 *)base + 8));
            }
            func_800499EC();
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260E398.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260E4A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260E684.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260EA60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260ED40.s")

void func_8260F084(void *arg0, s32 arg1) {
    struct Vec2s {
        s16 x;
        s16 y;
    };
    struct State {
        s16 unk0;
        s16 unk2;
        s16 unk4;
        s16 unk6;
        s16 unk8;
        s16 padA;
        s32 unkC;
        s32 unk10;
        struct Vec2s unk14;
        struct Vec2s unk18;
        struct Vec2s unk1C;
    } *ptr = (struct State *)arg0;

    ptr->unk0 = 0;
    ptr->unk2 = 0;
    ptr->unk4 = 0;
    ptr->unk6 = arg1;
    ptr->unk8 = 0;
    ptr->unkC = 0;
    ptr->unk10 = 0x40000;
    ptr->unk14.x = 0x110;
    ptr->unk14.y = 0xC0;
    ptr->unk18 = ptr->unk14;
    ptr->unk1C = ptr->unk14;
}

void func_8260F0DC(u8 *arg0) {
    *(s16 *)(arg0 + 0) = 1;
    *(s16 *)(arg0 + 4) = 0;
    func_800226C0(0x78);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260F108.s")

extern s32 func_8004E0F0(s32, s32, s32);
s32 func_8260F49C(s32 arg0, s32 arg1) {
    s32 value;
    s32 result;
    void *record;

    record = (void *)((u8 *)(u32)arg0 + (arg1 * 4));
    value = *(s16 *)((u8 *)record + 0x58);
    result = 0;
    if (value != -1) {
        result = func_8004E0F0(0, value, *(s16 *)((u8 *)record + 0x5A));
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260F4E4.s")

extern s32 func_8006456C(s32);
extern s32 func_80064728(void *);
extern s32 func_8003F970(s32, u16);
s32 func_8260F6C8(void *arg0, void **arg1, s32 arg2) {
    struct ResultSlot {
        s32 value;
        s32 pad;
    } result;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_s7;
    s32 temp_v0;
    s32 i;
    void **ptr;
    void *entry;

    result.value = -1;
    temp_s5 = func_8006456C(*(u16 *)((u8 *)arg0 + 0x16));
    temp_s6 = func_80064728(arg0);
    temp_s7 = func_8003F970(*(u8 *)arg0, *(u16 *)((u8 *)arg0 + 0x16));
    i = 0;
    if (arg2 > 0) {
        ptr = arg1;
loop_2:
        entry = *ptr;
        temp_s2 = func_8006456C(*(u16 *)((u8 *)entry + 0x16));
        temp_s3 = func_80064728(entry);
        temp_v0 = func_8003F970(*(u8 *)entry, *(u16 *)((u8 *)entry + 0x16));
        if ((temp_s6 == temp_s3) && (temp_s5 == temp_s2) && (temp_s7 == temp_v0)) {
            result.value = i;
        } else {
            i += 1;
            ptr++;
            if (i != arg2) goto loop_2;
        }
    }
    return result.value;
}

s32 func_8260F7C4(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_v1;

    var_v1 = 0;
    if (arg0 == -1) {
        temp_v0 = (s32) (arg1 + 3) / 4;
        var_v1 = temp_v0;
        if (temp_v0 >= 3) {
            var_v1 = 2;
        }
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260F7FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_8260FFE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826101B4.s")

extern void _bzero(void *, s32);
extern s32 D_8261A5A0;
extern s32 func_8260F7FC(s32);
extern s32 func_826101B4(s32);
extern s16 D_8261A490;
s32 func_82610C84(s32 arg0, s32 arg1) {
    s32 result;
    s32 mode;

    result = 1;
    _bzero((void *)&D_8261A490, 0x35DC);
    D_8261A5A0 = arg0;
    mode = *(s16 *)((u8 *)&arg1 + 2);
    D_8261A490 = mode;
    switch (mode) {
    case 0:
        result = func_8260F7FC(arg0);
        break;
    case 1:
        result = func_826101B4(arg0);
        break;
    }
    return result;
}

extern s16 D_8261A490;
s32 func_82610D14(void) {
    u8 *base = (u8 *)&D_8261A490;
    s32 result = 1;
    s32 i;

    for (i = 0; i < *(s16 *)(base + 0x18); i++) {
        if (((s16 **)(base + 0x34F4))[i][3] != 0) {
            result = 0;
            break;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82610D6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82610E34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82610EE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82610FF8.s")

extern void func_82607734(void *, s32);
void func_82611184(u8 *arg0)
{
  s32 pad[2];
  u8 *sp34;
  s16 temp_v1;
  s32 var_a1;
  s32 var_s0;
  s32 var_s2;
  u8 *temp_s3;
  u8 *temp_v0;
  u8 *var_v0;
  temp_v1 = *((s16 *) (arg0 + 0x18));
  var_a1 = 1;
  var_s0 = 0;
  if ((temp_v1 - 1) >= 0)
  {
    var_v0 = arg0;
    loop_2:
    var_s0 += 1;

    if ((*((s16 *) ((*((u8 **) (var_v0 + 0x34F4))) + 6))) != 0)
    {
      var_a1 = 0;
    }
    else
    {
      var_v0 += 4;
      if (var_s0 < temp_v1)
      {
        goto loop_2;
      }
    }
  }
  if (var_a1 != (0 ^ 0))
  {
    temp_s3 = arg0 + 0x114;
    sp34 = func_82604C40(5, 0, temp_s3, 0x14);
    var_s0 = 0;
    *((s16 *) (arg0 + 2)) = 4;
    *((s16 *) (arg0 + 6)) = 0;
    if ((*((s16 *) (arg0 + 0x12))) > 0)
    {
      var_s2 = -1;
      do
      {
        temp_v0 = func_82604C40(1, var_s0, temp_s3, 0x14);
        if ((*((s16 *) (temp_v0 + 0x32))) != var_s2)
        {
          *((u8 **) ((arg0 + 0x34F4) + ((*((s16 *) (arg0 + 0x18))) * 4))) = func_82604C40(1, var_s0, temp_s3, 0x14);
          *((s16 *) (arg0 + 0x18)) = (*((s16 *) (arg0 + 0x18))) + 1;
          func_82607734(temp_v0, (*((s16 *) (sp34 + 0x26))) / 2);
          return;
        }
        var_s0 += 1;
      }
      while (var_s0 < (*((s16 *) (arg0 + 0x12))));
    }
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826112CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826114DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826119A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826119DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82611D44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826122A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826123B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826127A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826129AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82612BD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82612E1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826131A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826132D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826134DC.s")

s32 func_82610D14();

void func_82613764(void *arg0) {
    if (func_82610D14() != 0) {
        (*(s16 *)((u8 *)(arg0) + (6))) = (s16) ((*(s16 *)((u8 *)(arg0) + (6))) + 1);
        if ((*(s16 *)((u8 *)(arg0) + (6))) >= 8) {
            (*(s16 *)((u8 *)(arg0) + (2))) = 0x13;
            (*(s16 *)((u8 *)(arg0) + (6))) = 0;
            (*(s16 *)((u8 *)(arg0) + (0x18))) = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826137B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82613814.s")

extern void func_8260850C(u8 *, s32);
extern void func_8260899C(u8 *, s32);
extern void func_82608C1C(u8 *, s32);
extern void func_826090F4(u8 *, s32);
extern void func_8260933C(u8 *, s32);
extern void func_8260BEF4(u8 *, s32);
extern void func_8260C2B0(u8 *, s32);
extern void func_8260D820(u8 *, s32);
extern void func_8260DB98(u8 *, s32);
extern void func_8260DD84(u8 *, s32);
void func_826139D4(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s32 var_s1;
    u8 *temp_a0;
    u8 *var_s0;

    var_s2 = 1;
    var_s0 = arg0;
    var_s1 = 0;
    do {
        temp_a0 = var_s0 + 0x114;
        if (*(s16 *)(var_s0 + 0x114) != 0) {
            temp_a1 = var_s2;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s2 = 0;
                func_8260850C(temp_a0, temp_a1);
            }
        }
        var_s1 += 0x298;
        var_s0 += 0x298;
    } while (var_s1 != 0x33E0);
}

void func_82613A4C(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s32 var_s1;
    u8 *temp_a0;
    u8 *var_s0;

    var_s2 = 1;
    var_s0 = arg0;
    var_s1 = 0;
    do {
        temp_a0 = var_s0 + 0x114;
        if (*(s16 *)(var_s0 + 0x114) != 0) {
            temp_a1 = var_s2;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s2 = 0;
                func_8260899C(temp_a0, temp_a1);
            }
        }
        var_s1 += 0x298;
        var_s0 += 0x298;
    } while (var_s1 != 0x33E0);
}

void func_82613AC4(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s32 var_s1;
    u8 *temp_a0;
    u8 *var_s0;

    var_s2 = 1;
    var_s0 = arg0;
    var_s1 = 0;
    do {
        temp_a0 = var_s0 + 0x114;
        if (*(s16 *)(var_s0 + 0x114) == 7) {
            temp_a1 = var_s2;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s2 = 0;
                func_82608C1C(temp_a0, temp_a1);
            }
        }
        var_s1 += 0x298;
        var_s0 += 0x298;
    } while (var_s1 != 0x33E0);
}

extern void func_82608EC4(u8 *, s32);
void func_82613B48(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s16 temp_v0;
    s32 var_s1;
    u8 *temp_a0;
    u8 *var_s0;

    var_s2 = 1;
    var_s0 = arg0;
    var_s1 = 0;
    do {
        temp_v0 = *(s16 *)(var_s0 + 0x114);
        temp_a0 = var_s0 + 0x114;
        if ((temp_v0 == 2) || (temp_v0 == 3)) {
            temp_a1 = var_s2;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s2 = 0;
                func_82608EC4(temp_a0, temp_a1);
            }
        }
        var_s1 += 0x298;
        var_s0 += 0x298;
    } while (var_s1 != 0x33E0);
}

void func_82613BE0(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s32 var_s1;
    u8 *temp_a0;
    u8 *var_s0;

    var_s2 = 1;
    var_s0 = arg0;
    var_s1 = 0;
    do {
        temp_a0 = var_s0 + 0x114;
        if (*(s16 *)(var_s0 + 0x114) == 7) {
            temp_a1 = var_s2;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s2 = 0;
                func_826090F4(temp_a0, temp_a1);
            }
        }
        var_s1 += 0x298;
        var_s0 += 0x298;
    } while (var_s1 != 0x33E0);
}

extern void func_82609868(void *, s32, s32);
extern void func_82609730(void *arg0, s32 arg1);
void func_82613C64(void *arg0) {
    s32 temp_a1;
    s32 temp_a2;
    s32 var_s1;
    s32 var_s2;
    s16 temp_v0;
    u8 *temp_a0;
    u8 *var_s0;

    var_s1 = 1;
    var_s0 = arg0;
    var_s2 = 0;
    do {
        temp_v0 = *(s16 *)(var_s0 + 0x114);
        temp_a0 = var_s0 + 0x114;
        switch (temp_v0) {
        case 1:
            temp_a1 = var_s1;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s1 = 0;
                func_82609730(temp_a0, temp_a1);
            }
            break;
        case 4:
            temp_a1 = var_s1;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                temp_a2 = *(s32 *)(var_s0 + 0x144);
                var_s1 = 0;
                func_82609868(temp_a0, temp_a1, temp_a2);
            }
            break;
        case 6:
            temp_a1 = var_s1;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                temp_a2 = *(s32 *)(var_s0 + 0x144);
                var_s1 = 0;
                func_82609868(temp_a0, temp_a1, temp_a2);
            }
            break;
        }
        var_s2 += 0x298;
        var_s0 += 0x298;
    } while (var_s2 != 0x33E0);
}

extern void func_82609A88(void *, s32);
extern void func_82609D84(void *, s32);
void func_82613D60(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s32 var_s1;
    s16 temp_v0;
    u8 *temp_a0;
    u8 *var_s0;

    var_s1 = 1;
    var_s0 = arg0;
    var_s2 = 0;
    do {
        temp_v0 = *(s16 *)(var_s0 + 0x114);
        temp_a0 = var_s0 + 0x114;
        switch (temp_v0) {
        case 4:
            temp_a1 = var_s1;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s1 = 0;
                func_82609A88(temp_a0, temp_a1);
            }
            break;
        case 6:
            temp_a1 = var_s1;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s1 = 0;
                func_82609D84(temp_a0, temp_a1);
            }
            break;
        }
        var_s2 += 0x298;
        var_s0 += 0x298;
    } while (var_s2 != 0x33E0);
}

void func_82613E20(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s32 var_s1;
    u8 *temp_a0;
    u8 *var_s0;

    var_s2 = 1;
    var_s0 = arg0;
    var_s1 = 0;
    do {
        temp_a0 = var_s0 + 0x114;
        if (*(s16 *)(var_s0 + 0x114) == 7) {
            temp_a1 = var_s2;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s2 = 0;
                func_8260933C(temp_a0, temp_a1);
            }
        }
        var_s1 += 0x298;
        var_s0 += 0x298;
    } while (var_s1 != 0x33E0);
}

extern void func_8260BE24(u8 *arg0, s32 arg1);
void func_82613EA4(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s32 var_s1;
    s16 temp_v0;
    u8 *temp_a0;
    u8 *var_s0;

    var_s1 = 1;
    var_s0 = arg0;
    var_s2 = 0;
    do {
        temp_v0 = *(s16 *)(var_s0 + 0x114);
        temp_a0 = var_s0 + 0x114;
        switch (temp_v0) {
        case 8:
            temp_a1 = var_s1;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s1 = 0;
                func_8260BD50(temp_a0, temp_a1);
            }
            break;
        case 0xB:
            temp_a1 = var_s1;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s1 = 0;
                func_8260BE24(temp_a0, temp_a1);
            }
            break;
        }
        var_s2 += 0x298;
        var_s0 += 0x298;
    } while (var_s2 != 0x33E0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82613F64.s")

void func_82614088(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s32 var_s1;
    u8 *temp_a0;
    u8 *var_s0;

    var_s2 = 1;
    var_s0 = arg0;
    var_s1 = 0;
    do {
        temp_a0 = var_s0 + 0x114;
        if (*(s16 *)(var_s0 + 0x114) == 6) {
            temp_a1 = var_s2;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s2 = 0;
                func_8260BEF4(temp_a0, temp_a1);
            }
        }
        var_s1 += 0x298;
        var_s0 += 0x298;
    } while (var_s1 != 0x33E0);
}

void func_8261410C(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s32 var_s1;
    u8 *temp_a0;
    u8 *var_s0;

    var_s2 = 1;
    var_s0 = arg0;
    var_s1 = 0;
    do {
        temp_a0 = var_s0 + 0x114;
        if (*(s16 *)(var_s0 + 0x114) == 1) {
            temp_a1 = var_s2;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s2 = 0;
                func_8260C2B0(temp_a0, temp_a1);
            }
        }
        var_s1 += 0x298;
        var_s0 += 0x298;
    } while (var_s1 != 0x33E0);
}

void func_82614190(void *arg0) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 var_s1;
    s16 temp_v0;
    s32 var_s2;
    u8 *new_var;
    u8 *temp_a0;
    u8 *var_s0;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    var_s1 = 1;
    var_s0 = arg0;
    var_s2 = 0;
    var_s3 = 1;
    var_s4 = 6;
    ;
    do {
        temp_v0 = *((s16 *)(var_s0 + 0x114));
        temp_a0 = var_s0 + 0x114;
        switch (temp_v0) {
        case 1:
            temp_a1_2 = var_s1;
            if ((*((s16 *)(temp_a0 + 6))) != 0) {
                var_s1 = 0;
                func_8260C7D4(temp_a0, temp_a1_2);
            }
            break;
        case 6:
            temp_a1 = var_s1;
            if ((*((s16 *)((new_var = temp_a0 + 6)))) != 0) {
                var_s1 = 0;
                func_8260C988(temp_a0, temp_a1);
            }
            break;
        }
        var_s2 += 0x298;
        var_s0 += 0x298;
    } while (var_s2 != 0x33E0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82614250.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82614324.s")

void func_826143E4(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s32 var_s1;
    u8 *temp_a0;
    u8 *var_s0;

    var_s2 = 1;
    var_s0 = arg0;
    var_s1 = 0;
    do {
        temp_a0 = var_s0 + 0x114;
        if (*(s16 *)(var_s0 + 0x114) == 1) {
            temp_a1 = var_s2;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s2 = 0;
                func_8260D820(temp_a0, temp_a1);
            }
        }
        var_s1 += 0x298;
        var_s0 += 0x298;
    } while (var_s1 != 0x33E0);
}

void func_82614468(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s32 var_s1;
    u8 *temp_a0;
    u8 *var_s0;

    var_s2 = 1;
    var_s0 = arg0;
    var_s1 = 0;
    do {
        temp_a0 = var_s0 + 0x114;
        if (*(s16 *)(var_s0 + 0x114) == 6) {
            temp_a1 = var_s2;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s2 = 0;
                func_8260DB98(temp_a0, temp_a1);
            }
        }
        var_s1 += 0x298;
        var_s0 += 0x298;
    } while (var_s1 != 0x33E0);
}

void func_826144EC(void *arg0) {
    s32 temp_a1;
    s32 var_s2;
    s32 var_s1;
    u8 *temp_a0;
    u8 *var_s0;

    var_s2 = 1;
    var_s0 = arg0;
    var_s1 = 0;
    do {
        temp_a0 = var_s0 + 0x114;
        if (*(s16 *)(var_s0 + 0x114) == 6) {
            temp_a1 = var_s2;
            if (*(s16 *)(temp_a0 + 6) != 0) {
                var_s2 = 0;
                func_8260DD84(temp_a0, temp_a1);
            }
        }
        var_s1 += 0x298;
        var_s0 += 0x298;
    } while (var_s1 != 0x33E0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82614570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82614630.s")

extern s32 func_8004D19C(s32, s32, s32, s32, s32);
extern void func_82607E40(u8 *, u8 *, u8 *, u8 *, s32);
extern u8 D_80094E78[];
extern u8 D_8261551C[];
extern u8 D_82615520[];
void func_8261479C(void *arg0) {
    struct State { u8 pad[0xA]; s16 index; s16 alpha; };
    s32 result;
    struct Color { u8 r; u8 g; u8 b; } color1;
    struct Color color2;

    result = func_8004C990(0x53, 3);
    gSPDisplayList(D_800D0510++, D_80094E78);
    func_82607E40(&color1.r, &color2.r, D_8261551C, D_82615520, ((struct State *)arg0)->index);
    gDPPipeSync(D_800D0510++);
    gDPSetEnvColor(D_800D0510++, color1.r, color1.g, color1.b, ((struct State *)arg0)->alpha);
    gDPSetPrimColor(D_800D0510++, 0, 0, color2.r, color2.g, color2.b, 0xFF);
    func_8004D19C(0x141, 0xD0, result, 1, 0);
}

extern u8 D_82615524;
extern u8 D_82615528;
void func_826148D4(void *arg0) {
    struct State { u8 pad[0xE]; s16 index; s16 alpha; };
    struct Color { u8 r; u8 g; u8 b; };
    s32 result;
    struct Color color1;
    struct Color color2;

    result = func_8004C990(0x5F, 0);
    gSPDisplayList(D_800D0510++, D_80094E78);
    func_82607E40(&color1.r, &color2.r, &D_82615524, &D_82615528, ((struct State *)arg0)->index);
    gDPPipeSync(D_800D0510++);
    gDPSetEnvColor(D_800D0510++, color1.r, color1.g, color1.b, ((struct State *)arg0)->alpha);
    gDPSetPrimColor(D_800D0510++, 0, 0, color2.r, color2.g, color2.b, 0xFF);
    func_8004D19C(0x141, 0xD4, result, 1, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82614A0C.s")

extern s16 D_8261A490;
extern u16 D_8261A494;
extern s16 D_8261DA4C;
extern void func_82614A0C(void *arg0);
extern void func_82614630(void *arg0);
extern void func_8261479C(void *arg0);
extern void func_826148D4(void *arg0);
extern void func_826139D4(void *arg0);
extern void func_82613A4C(void *arg0);
extern void func_82613AC4(void *arg0);
extern void func_82613B48(void *arg0);
extern void func_82613BE0(void *arg0);
extern void func_82613E20(void *arg0);
extern void func_82614088(void *arg0);
extern void func_8261410C(void *arg0);
extern void func_826143E4(void *arg0);
extern void func_82614468(void *arg0);
extern void func_826144EC(void *arg0);
s32 func_82614BD0(void) {
    void *s0 = &D_8261A490;

    if (*(u16 *)((u8 *)s0 + 4) & 1) {
        func_82613A4C(s0);
        func_826139D4(s0);
        func_82613B48(s0);
        func_82613BE0(s0);
        func_82613C64(s0);
        func_82613D60(s0);
        func_82613E20(s0);
        func_82613EA4(s0);
        func_82613F64(s0);
        func_82613AC4(s0);
        func_82614088(s0);
        func_8261410C(s0);
        func_82614190(s0);
        func_82614250(s0);
        func_82614324(s0);
        func_826143E4(s0);
        func_82614468(s0);
        func_82614570(s0);
        func_82614A0C(s0);
        func_826144EC(s0);
        if (D_8261DA4C != 0) {
            func_82614630(&D_8261DA4C);
        }
        func_8261479C(s0);
        if (D_8261DA4C) {
        }
        func_826148D4(s0);
    }
    return (D_8261A494 & 1) != 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82614CE0.s")

extern s16 D_8261A492;
extern u16 D_8261A494;

s32 func_82614F0C(void) {
    s32 var_v1;

    var_v1 = 0;
    if ((D_8261A494 & 1) && (D_8261A492 == 0)) {
        var_v1 = 1;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_82614F40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12C460/func_826150A4.s")
#endif
