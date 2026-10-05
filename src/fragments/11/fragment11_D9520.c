#include "global.h"


#ifdef VERSION_US
s32 func_81601980(s32 *arg0, s32 arg1) {
    return arg0[arg1 / 32] & (1 << (arg1 % 32));
}

void func_816019C0(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 mask;
    s32 value;
    ;
    arg0[arg1 / 32] = (arg0[arg1 / 32] & (~mask)) | ((arg2) ? (mask = 1 << (arg1 % 32)) : ((mask = 1 << (arg1 % 32), 0)));
}

void func_81601A38(s32 *arg0, s32 arg1) {
    s32 value;
    s32 i;
    value = arg1 ? -1 : 0;
    for (i = 0; i < 8; i++) {
        arg0[i] = value;
    }
}

void func_81601A78(s32 arg0, s32 arg1) { func_816019C0(arg0, 0xAD, arg1); func_816019C0(arg0, 0x4F, arg1); func_816019C0(arg0, 0x4E, arg1); func_816019C0(arg0, 0x50, arg1); func_816019C0(arg0, 0x54, arg1); func_816019C0(arg0, 0x53, arg1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81601B00.s")

void func_81601D24(s32 arg0, s32 arg1) {
    if (arg1 != 0x19) func_816019C0(arg0, 0xA3, 1);
    if (arg1 != 0x71) func_816019C0(arg0, 0x1E, 1);
    if (arg1 != 0x53) func_816019C0(arg0, 0x69, 1);
    if (arg1 != 0x84) func_816019C0(arg0, 0x23, 1);
    if ((arg1 != 0x68) && (arg1 != 0x69)) func_816019C0(arg0, 0x76, 1);
}

s32 func_81601DE8(u8 arg0, u8 arg1) { if ((arg1 == 0x19) && (arg0 == 0xA3)) return 1; if ((arg1 == 0x71) && (arg0 == 0x1E)) return 1; if ((arg1 == 0x68) && (arg0 == 0x76)) return 1; if ((arg1 == 0x69) && (arg0 == 0x76)) return 1; if ((arg1 == 0x53) && (arg0 == 0x69)) return 1; if ((arg1 == 0x84) && (arg0 == 0x23)) return 1; return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81601EAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81601FA0.s")

extern s32 func_8004C874(s32, s32);
extern u8 D_8160C010[];
s32 *func_816020BC(u8 arg0) {
    s32 *result;
    s32 *temp_v0;

    result = (s32 *)&D_8160C010;
    if (arg0 > 0) {
        temp_v0 = (s32 *)func_8004C874(9, arg0 - 1);
        if (temp_v0 != NULL) {
            result = temp_v0;
        }
    }
    return result;
}

extern u8 D_8160BD30[];
void *func_81602108(s32 arg0) { s32 index = arg0 & 0xFF; s32 *p = &arg0; *p = arg0; if (index >= 6) index = 0; return &D_8160BD30[index * 3]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81602134.s")

s32 func_816021E8(u8 *arg0, u8 arg1) {
    s32 i;
    if (arg1 == 0) {
        return 0;
    }
    for (i = 0; i < *(u16 *)(arg0 + 0x40); i++) {
        if (arg0[i] == arg1) {
            return i;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81602240.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816028E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81602940.s")

extern f32 D_8160C208;
extern f32 func_816092FC(void);
s32 func_81602AEC(u8 *arg0, u8 *arg1) {
    s32 changed = (arg0 == 0) * 0;
    s32 step = (s32)(func_816092FC() * D_8160C208);
    if (step <= 0) step = 1;
    if (arg1[0] != arg0[0]) {
        changed = 1;
        if ((arg0[0] - arg1[0] > 0 ? arg0[0] - arg1[0] : -(arg0[0] - arg1[0])) <= step) {
            arg0[0] = arg1[0];
        } else if (arg0[0] < arg1[0]) {
            arg0[0] = arg0[0] + step;
        } else if (arg1[0] < arg0[0]) {
            arg0[0] = arg0[0] - step;
        }
    }
    if (arg1[1] != arg0[1]) {
        changed = 1;
        if ((arg0[1] - arg1[1] > 0 ? arg0[1] - arg1[1] : -(arg0[1] - arg1[1])) <= step) {
            arg0[1] = arg1[1];
        } else if (arg0[1] < arg1[1]) {
            arg0[1] = arg0[1] + step;
        } else if (arg1[1] < arg0[1]) {
            arg0[1] = arg0[1] - step;
        }
    }
    if (arg1[2] != arg0[2]) {
        changed = 1;
        if ((arg0[2] - arg1[2] > 0 ? arg0[2] - arg1[2] : -(arg0[2] - arg1[2])) <= step) {
            arg0[2] = arg1[2];
        } else if (arg0[2] < arg1[2]) {
            arg0[2] = arg0[2] + step;
        } else if (arg1[2] < arg0[2]) {
            arg0[2] = arg0[2] - step;
        }
    }
    return changed;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81602C68.s")

extern u8 D_8160BE40;
extern u8 D_8160BE4C;

s32 *func_81602D70(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 4)) {
        return (arg0 * 3) + &D_8160BE40;
    }
    return &D_8160BE4C;
}

extern void func_8004972C(u8, u8, u8, s32);
void *func_81602C68();

void func_81602DA4(void) {
    void *temp_v0;

    temp_v0 = func_81602C68();
    func_8004972C((*(u8 *)((u8 *)(temp_v0) + (0))), (*(u8 *)((u8 *)(temp_v0) + (1))), (*(u8 *)((u8 *)(temp_v0) + (2))), 0xFF);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81602DD8.s")

extern void func_8004C8C0();
extern void func_81602DD8();
void func_8160317C(void) { func_8004C8C0(66); func_8004C8C0(65); func_81602DD8(); }

extern void func_8004C4B0(s32); extern void func_8004C8C0(s32); extern void func_81602DD8(void);
void func_816031AC(void) {
    func_8004C4B0(0x19);
    func_8004C4B0(0x17);
    func_8004C8C0(0x39);
    func_8004C8C0(0x42);
    func_8004C8C0(0x41);
    func_81602DD8();
}

void func_816031F4(void) {
    func_8004C4B0(0xF);
    func_8004C4B0(7);
    func_8004C4B0(0x17);
    func_8004C8C0(0x30);
    func_8004C8C0(0x39);
    func_8004C8C0(0x11B);
    func_8004C8C0(0x9F);
    func_81602DD8();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_8160324C.s")

void func_8160335C(u8 *arg0, s32 arg1) {}

/* Tail (last 3 entries) of jtbl_8160C20C, a jump table used by an earlier,
 * still-GLOBAL_ASM switch in this file. Not referenced from C: it exists
 * only so this file's own .rodata subsegment starts at a 16-byte-aligned
 * ROM address (required by this fragment's SUBALIGN(16)) while still
 * landing func_81603368's own jump table (jtbl_8160C27C, right below) at
 * its real retail address. */
const u32 D_8160C270[3] = {0x81602D00, 0x81602C94, 0x81602CAC};

extern s32 GbSave_GetPortAvailability(s32);
extern u8 func_8005D92C(s32);
s32 func_81603368(s32 arg0) {
    if (GbSave_GetPortAvailability(arg0)) {
        return -1;
    }
    switch (func_8005D92C(arg0)) {
        case 0:
            return 7;
        case 1:
            return 0;
        case 2:
            return 1;
        case 3:
            return 2;
        case 4:
            return 3;
        case 5:
            return 4;
        case 6:
            return 5;
        case 7:
            return 6;
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        default:
            return 7;
    }
}

extern s32 func_8005D8CC(s32);
extern s32 func_80057A80(s32);
extern s32 func_8005F37C(u8, u16 *, u8 *, u8 *, u8 *);
extern s32 func_8005DE68(s32);
extern s32 func_8005DE8C(s32);
extern s32 func_8005DDF8(s32);
extern s32 func_8005DDD4(s32);
extern u8 func_8005D92C(s32);
s32 func_81603404(s32 arg0, s32 arg1)
{
    s32 status;
    s32 new_var;
    u16 out0;
    u8 out1;
    u8 out2;
    u8 out3;
    s32 pad1;

    status = func_8005D8CC(arg0);
    if ((status == 1) || (status == 4)) {
        return 2;
    }
    new_var = status;
    if ((arg1 & 2) && (func_8005D92C(arg0) != 7)) {
        return 5;
    }
    if ((arg1 & 1) && func_80057A80(arg0)) {
        return 4;
    }
    if ((arg1 & 4) && ((new_var == 3) || (new_var == 5))) {
        return 6;
    }
    if (new_var == 2) {
        return 3;
    }
    if ((arg1 & 0x80) && func_8005F37C((u8)arg0, &out0, &out1, &out2, &out3)) {
        return 1;
    }
    if ((arg1 & 8) && !func_8005DE68(arg0)) {
        return 7;
    }
    if ((arg1 & 0x10) && !func_8005DE8C(arg0)) {
        return 8;
    }
    if ((arg1 & 0x20) && !func_8005DDF8(arg0)) {
        if ((arg1 && arg1) && arg1) {
        }
        return 9;
    }
    if ((arg1 & 0x40) && !func_8005DDD4(arg0)) {
        return 10;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81603598.s")

extern void *D_8160BDB8;
extern void func_8004D19C(s32, s32, void *, s32, s32);
void func_81603984(s32 arg0, s32 arg1) {
    func_8004D19C(arg0, arg1, D_8160BDB8, 0, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816039B0.s")

extern s32 func_81602940(s32);
extern void func_8004D1FC(void *);
void func_81603C84(s32 arg0, s32 arg1, s32 arg2) {
    s32 value;
    value = func_81602940(arg2);
    func_8004D1FC((void *)value);
    func_8004D19C(arg0, arg1, (void *)value, 0, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81603CD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81604024.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816044AC.s")

extern void func_816039B0();
extern void func_81608044(s32, s32, s32, s32, f32, s32 *);
extern u8 D_8160BE50;
void func_816048E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_816039B0();
    func_81608044(arg0 + 8, arg1 + 8, arg2 - 0x13, arg3 - 0x13, 0.0f, &D_8160BE50);
}

extern void func_81603CD0(s32, s32, s32, s32, s32 *, s32 *);
extern void func_81604024(s32, s32, s32, s32, s32, s32 *, s32 *);
void func_81604944(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 *arg5) {
    func_81603CD0(arg0, arg1, arg2, arg3, arg4, arg5);
    func_81604024(0, arg0 + 5, arg1 + 5, arg2 - 0xD, arg3 - 0xD, arg4, arg5);
}

extern u8 D_8160BDC4;
extern u8 D_8160BDC8;
extern void func_81603CD0(s32, s32, s32, s32, s32 *, s32 *);
extern void func_81604024(s32, s32, s32, s32, s32, s32 *, s32 *);
void func_816049BC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_81603CD0(arg0, arg1, arg2, arg3, (s32 *)&D_8160BDC4, (s32 *)&D_8160BDC8);
    func_81604024(0, arg0 + 5, arg1 + 5, arg2 - 0xD, arg3 - 0xD, (s32 *)&D_8160BDC4, (s32 *)&D_8160BDC8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81604A44.s")

extern void func_81604A44(s32, s32, s32, s32, s32);
void func_816054D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_81604A44(arg0, arg1, arg2, arg3, 1);
}

void func_816054FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_81604A44(arg0, arg1, arg2, arg3, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_8160551C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81605598.s")

extern void func_8160551C(s32, s32, s32, s32);
extern void func_81605598(s32, s32, s32, s32, s32);
void func_81605908(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) { func_8160551C(arg0, arg1, arg2, arg3); func_81605598(arg0, arg1, arg2, arg3, arg4); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81605950.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816059CC.s")

extern void func_81605950(s32, s32, s32, s32);
extern void func_816059CC(s32, s32, s32, s32, s32);
void func_81605CDC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) { func_81605950(arg0, arg1, arg2, arg3); func_816059CC(arg0, arg1, arg2, arg3, arg4); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81605D24.s")

extern void *D_8160BD78[];
extern void func_81602240(f32, f32, f32, f32, s32, s32, f32, f32);
extern void func_8004D1FC(void *);
extern u8 D_80094E38[];
extern u8 D_80094F50[];
extern u32 D_800D0510;
void func_81605F94(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, f32 arg4) {
    Gfx *gfx;
    gSPDisplayList((*(Gfx **)&D_800D0510)++, D_80094E38);
    func_8004D1FC(D_8160BD78[arg2]);
    gDPSetCombine((*(Gfx **)&D_800D0510)++, 0x119623, 0xFF2FFFFF);
    gfx = (*(Gfx **)&D_800D0510)++;
    gfx->words.w0 = 0xFA00FFFF;
    gfx->words.w1 = _SHIFTL(arg3[1], 16, 8) | _SHIFTL(arg3[2], 8, 8) | _SHIFTL(arg3[0], 24, 8) | _SHIFTL((u32)(255.0f * arg4), 0, 8);
    func_81602240((f32)arg0, (f32)arg1, 48.0f, 24.0f, 0, 0, 1.0f, 1.0f);
    gSPDisplayList((*(Gfx **)&D_800D0510)++, D_80094F50);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_8160615C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606304.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606694.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606800.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816068C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606B5C.s")

extern s16 D_8160C0F0[];
f32 func_81606E14(f32 arg0, s32 arg1) {
    s32 index;
    if (arg1) {
        return 28.0f * arg0;
    }
    index = (s32)arg0;
    return ((f32)D_8160C0F0[index + 1] - (f32)D_8160C0F0[index]) * (arg0 - (f32)index) + (f32)D_8160C0F0[index];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606E84.s")

extern void func_81606E84(s16 *, s32, s32, f32, s32);
extern void func_816039B0();
void func_81606F88(s32 arg0, s32 arg1, f32 arg2, s32 arg3) {
    s16 sp20[4];

    func_81606E84(sp20, arg0, arg1, arg2, arg3);
    func_816039B0(sp20[0], sp20[1], sp20[2], sp20[3]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606FE0.s")

extern u32 D_800D0510;
#define GFX_DL (*(Gfx **)&D_800D0510)
extern u8 D_80094E38[];
extern u8 D_80094F50[];
extern void *D_8160BD94;
extern void *D_8160BD90;
extern void func_8004D19C(s32, s32, void *, s32, s32);
void func_8160710C(s32 arg0, s32 arg1) {
    gSPDisplayList(GFX_DL++, D_80094E38);
    gDPSetRenderMode(GFX_DL++, 0x0F0A7008, 0);
    func_8004D19C(arg0, arg1, D_8160BD94, 0, 0);
    gSPDisplayList(GFX_DL++, D_80094F50);
}

extern void func_8004D19C(s32, s32, void *, s32, s32);
void func_816071AC(s32 arg0, s32 arg1) {
    gSPDisplayList(GFX_DL++, D_80094E38);
    gDPSetRenderMode(GFX_DL++, 0x0F0A7008, 0);
    func_8004D19C(arg0, arg1, D_8160BD90, 0, 0);
    gSPDisplayList(GFX_DL++, D_80094F50);
}

void func_8160724C(s16 *arg0, s16 *arg1) { s16 value; value = arg1[0]; if (arg0[0] < value) arg0[0] = value; value = arg1[1]; if (arg0[1] < value) arg0[1] = value; if ((arg1[0] + arg1[2]) < (arg0[2] + arg0[0])) { arg0[2] = (arg1[0] + arg1[2]) - arg0[0]; if (arg0[2] < 0) arg0[2] = 0; } if ((arg1[1] + arg1[3]) < (arg0[3] + arg0[1])) { arg0[3] = (arg1[1] + arg1[3]) - arg0[1]; if (arg0[3] < 0) arg0[3] = 0; } }

void func_816072FC(void *arg0) {
    if ((*(s16 *)((u8 *)(arg0) + (4))) < 0x10) {
        (*(s16 *)((u8 *)(arg0) + (4))) = 0;
    }
    if ((*(s16 *)((u8 *)(arg0) + (6))) < 0x10) {
        (*(s16 *)((u8 *)(arg0) + (6))) = 0;
    }
}

void func_8160732C(void *arg0, void *arg1) {
    (*(s16 *)((u8 *)(arg0) + (0))) = (s16) ((*(s16 *)((u8 *)(arg1) + (0))) + 8);
    (*(s16 *)((u8 *)(arg0) + (2))) = (s16) ((*(s16 *)((u8 *)(arg1) + (2))) + 8);
    (*(s16 *)((u8 *)(arg0) + (4))) = (s16) ((*(s16 *)((u8 *)(arg1) + (4))) - 0x13);
    (*(s16 *)((u8 *)(arg0) + (6))) = (s16) ((*(s16 *)((u8 *)(arg1) + (6))) - 0x13);
}

extern void func_816028E4(void *, s32, s32, s32, s32);
extern u32 D_800D0510;
void func_81607360(s32 arg0) {
    func_816028E4(&D_800D0510, (s32) (*(s16 *)((u8 *)(arg0) + (0))), (s32) (*(s16 *)((u8 *)(arg0) + (2))), (s32) (*(s16 *)((u8 *)(arg0) + (4))), (s32) (*(s16 *)((u8 *)(arg0) + (6))));
}

void func_816073A0(void *arg0) {
    func_816028E4(&D_800D0510, (s32) (s16) ((*(s16 *)((u8 *)(arg0) + (0))) + 8), (s32) (s16) ((*(s16 *)((u8 *)(arg0) + (2))) + 8), (s32) (s16) ((*(s16 *)((u8 *)(arg0) + (4))) - 0x13), (*(s16 *)((u8 *)(arg0) + (6))) - 0x13);
}

void func_81607408(void) {
    func_816028E4(&D_800D0510, 0, 0, 640, 480);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81607440.s")

f32 func_8160762C(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    f32 result;
    s32 first;
    s32 next;
    if (arg1 < 2) {
        result = 0.0f;
        *arg3 = 0;
        *arg2 = 0;
    } else {
        result = (f32)arg0 / (f32)(arg1 - 1);
        first = arg0 != 0;
        next = arg0;
        next++;
        *arg2 = first;
        *arg3 = arg1 != next;
    }
    return result;
}

extern u32 D_8160BE60;
extern u32 D_8160BE64;
extern u32 D_8160BE68;
extern u32 D_8160BE6C;
void *func_81607680(u16 arg0, u16 arg1, u16 arg2) {
    if (arg0 <= 0) {
        return (arg1 & 1) ? &D_8160BE6C : &D_8160BE64;
    }
    if (arg0 >= arg2) {
        return (arg1 & 0x400) ? &D_8160BE68 : &D_8160BE64;
    }
    return (arg1 & (1 << arg0)) ? &D_8160BE60 : &D_8160BE64;
}

extern u32 D_8160BE70;
extern u32 D_8160BE74;
extern u32 D_8160BE78;
extern u32 D_8160BE7C;
void *func_8160771C(u16 arg0, u16 arg1, u16 arg2) {
    if (arg0 <= 0) {
        return (arg1 & 1) ? &D_8160BE7C : &D_8160BE74;
    }
    if (arg0 >= arg2) {
        return (arg1 & 0x400) ? &D_8160BE78 : &D_8160BE74;
    }
    return (arg1 & (1 << arg0)) ? &D_8160BE70 : &D_8160BE74;
}

extern void * func_81607680(u16 arg0, u16 arg1, u16 arg2);
extern u32 D_800D0510;
void func_816077B8(u16 arg0, u16 arg1, u16 arg2) {
    u8 *color;
    Gfx *gfx;
    color = func_81607680(arg0, arg1, arg2);
    gfx = (Gfx *)D_800D0510;
    D_800D0510 += sizeof(Gfx);
    gfx->words.w0 = 0xFA00FFFF;
    gfx->words.w1 = _SHIFTL(color[1], 16, 8) | _SHIFTL(color[2], 8, 8) | _SHIFTL(color[0], 24, 8) | 255;
}

extern void * func_81607680(u16 arg0, u16 arg1, u16 arg2);
extern u32 D_800D0510;
void func_81607834(u16 arg0, u16 arg1, u16 arg2) {
    struct Color07834RGB { u8 r; u8 g; u8 b; } *color;
    color = func_81607680(arg0, arg1, arg2);
    gDPPipeSync((*(Gfx **)&D_800D0510)++);
    gDPSetEnvColor((*(Gfx **)&D_800D0510)++, color->r, color->g, color->b, 255);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816078C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81607B1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81607DB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81608044.s")

extern s32 func_8000731C(void);
extern void *Gfx_AllocDisplayList(s32);
extern void Gfx_SetViewportDimensions(void *, s16, s16);
extern Mtx D_80094890;
extern u32 D_800D0510;
void func_816083A4(void) {
    s16 *dims;
    Mtx *matrix;
    Vp *viewport;
    dims = (s16 *)func_8000731C();
    matrix = Gfx_AllocDisplayList(0x40);
    viewport = Gfx_AllocDisplayList(0x10);
    Gfx_SetViewportDimensions(viewport, dims[2], dims[3]);
    gSPViewport((*(Gfx **)&D_800D0510)++, (u32)viewport & 0x1FFFFFFF);
    guOrtho(matrix, 0.5f, (f32)(u16)dims[2] - 0.5f, (f32)(u16)dims[3] - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);
    gSPPerspNormalize((*(Gfx **)&D_800D0510)++, 0xFFFF);
    gSPMatrix((*(Gfx **)&D_800D0510)++, (u32)matrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix((*(Gfx **)&D_800D0510)++, (u32)&D_80094890 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

extern void *D_8160BDB4;
void func_8160852C(void) {
    func_8004D1FC(D_8160BDB4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81608550.s")

extern void func_81608550(s32, s32, s32, s32, f32);
void func_8160877C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    if (arg2 != 0) {
        func_8160852C();
        func_81608550(arg0, arg1, arg2, arg3, arg4);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816087C8.s")

extern s32 func_80064474(u8, u16);
extern void func_800495BC(s32, s32, s32);
extern s32 func_8004C874(s32, s32);
void func_81608890(s32 arg0, s32 arg1, u8 *arg2) {
    s32 status;
    status = func_80064474(arg2[0], *(u16 *)(arg2 + 0x16));
    switch (status) {
    case 0:
        return;
    case 1:
        func_800495BC(arg0, arg1, func_8004C874(0xD, 0x1D));
        break;
    case 2:
        func_800495BC(arg0, arg1, func_8004C874(0xD, 0x1E));
        break;
    }
}

extern f32 func_8160BCB0(f32, f32);
extern void func_8004AF18(s32, s32);
extern f32 func_816092FC(void);
void func_81608918(s32 arg0, s32 arg1, f32 *arg2) {
    *arg2 = func_8160BCB0(*arg2 + func_816092FC(), 24.0f);
    if (*arg2 < 12.0f) {
        arg0 += *arg2 / 2;
    } else {
        arg0 += (24.0f - *arg2) / 2;
    }
    func_8004AF18(arg0, arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816089E0.s")

extern u8 D_80094D90[];
extern u8 D_80094DB8[];
extern f32 D_8160C2C8;
extern void Gfx_FillRectRgb(s16, s16, s16, s16, u32, u32, u32);
extern void Gfx_FillRectRgba(s16, s16, s16, s16, u32, u32, u32, u32);
extern u32 D_800D0510;
void func_81608A38(s32 arg0, s32 arg1, u8 arg2, f32 arg3) {
    Gfx *gfx;
    if (D_8160C2C8 < arg3) {
        gfx = (Gfx *)D_800D0510;
        D_800D0510 += 8;
        gSPDisplayList(gfx, D_80094D90);
        if (arg2 & 1) {
            Gfx_FillRectRgb((s16)(arg0 + 0x9E), (s16)(arg1 + 9), 1, 0x7A, 0, 0, 0);
        }
        if (arg2 & 2) {
            Gfx_FillRectRgb((s16)(arg0 + 0x138), (s16)(arg1 + 9), 1, 0x7A, 0, 0, 0);
        }
        if (arg2 & 4) {
            Gfx_FillRectRgb((s16)(arg0 + 0xD), (s16)(arg1 + 0x45), 0x1BC, 1, 0, 0, 0);
        }
        if (arg2 & 1) {
            Gfx_FillRectRgb((s16)(arg0 + 0x9F), (s16)(arg1 + 9), 1, 0x7A, 0xFF, 0xFF, 0xFF);
        }
        if (arg2 & 2) {
            Gfx_FillRectRgb((s16)(arg0 + 0x139), (s16)(arg1 + 9), 1, 0x7A, 0xFF, 0xFF, 0xFF);
        }
        if (arg2 & 4) {
            Gfx_FillRectRgb((s16)(arg0 + 0xD), (s16)(arg1 + 0x46), 0x1BC, 1, 0xFF, 0xFF, 0xFF);
        }
    } else {
        gfx = (Gfx *)D_800D0510;
        D_800D0510 += 8;
        gSPDisplayList(gfx, D_80094DB8);
        if (arg2 & 1) {
            Gfx_FillRectRgba((s16)(arg0 + 0x9E), (s16)(arg1 + 9), 1, 0x7A, 0, 0, 0, (u32)(255.0f * arg3));
        }
        if (arg2 & 2) {
            Gfx_FillRectRgba((s16)(arg0 + 0x138), (s16)(arg1 + 9), 1, 0x7A, 0, 0, 0, (u32)(255.0f * arg3));
        }
        if (arg2 & 4) {
            Gfx_FillRectRgba((s16)(arg0 + 0xD), (s16)(arg1 + 0x45), 0x1BC, 1, 0, 0, 0, (u32)(255.0f * arg3));
        }
        if (arg2 & 1) {
            Gfx_FillRectRgba((s16)(arg0 + 0x9F), (s16)(arg1 + 9), 1, 0x7A, 0xFF, 0xFF, 0xFF, (u32)(255.0f * arg3));
        }
        if (arg2 & 2) {
            Gfx_FillRectRgba((s16)(arg0 + 0x139), (s16)(arg1 + 9), 1, 0x7A, 0xFF, 0xFF, 0xFF, (u32)(255.0f * arg3));
        }
        if (arg2 & 4) {
            Gfx_FillRectRgba((s16)(arg0 + 0xD), (s16)(arg1 + 0x46), 0x1BC, 1, 0xFF, 0xFF, 0xFF, (u32)(255.0f * arg3));
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81609170.s")

s32 func_80001FF0();
s32 func_80008970();

f32 func_816092FC(void) {
    s32 sp1C;

    sp1C = func_80008970();
    return ((f32) sp1C * 60.0f) / (f32) func_80001FF0();
}

extern void func_816028E4(void *, s32, s32, s32, s32);
extern u32 D_800D0510;
void func_81609344(s32 arg0,s32 arg1,s32 arg2,s32 arg3,s32 arg4){s32 width=arg4?0x280:0x140; s32 height=arg4?0x1E0:0xF0; if(arg0<0){arg2+=arg0;arg0=0;} if(arg1<0){arg3+=arg1;arg1=0;} if(arg0+arg2>=width)arg2=width-arg0; if(arg1+arg3>=height)arg3=height-arg1; if(arg2<=0||arg3<=0||arg0>=width||arg1>=height||arg0+arg2<=0||arg1+arg3<=0)func_816028E4(&D_800D0510,0,0,0,0); func_816028E4(&D_800D0510,(s16)arg0,(s16)arg1,(s16)arg2,arg3);}

void func_8160945C(s16 *arg0, s16 *arg1, s16 *arg2, f32 arg3) { arg0[0] = arg1[0] + (arg2[0] - arg1[0]) * arg3; arg0[1] = arg1[1] + (arg2[1] - arg1[1]) * arg3; arg0[2] = arg1[2] + (arg2[2] - arg1[2]) * arg3; arg0[3] = arg1[3] + (arg2[3] - arg1[3]) * arg3; }

extern u8 D_8160C128;

void *func_81609530(s32 arg0) {
    if ((arg0 < 0) || (arg0 >= 0xB)) {
        return NULL;
    }
    return (arg0 * 8) + &D_8160C128;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_8160955C.s")

struct Color098 { u8 r, g, b; };
extern s32 func_8004CA10(void *);
extern s32 func_8004CA24(void *);
extern void func_8004D19C(s32, s32, void *, s32, s32);
extern u8 D_80094E38[];
extern u8 D_80094F50[];
void func_816098B0(void *arg0, struct Color098 *arg1) {
    s32 x;
    s32 y;
    gSPDisplayList(GFX_DL++, D_80094E38);
    gDPSetRenderMode(GFX_DL++, 0x0F0A4000, 0);
    gDPSetEnvColor(GFX_DL++, arg1->r, arg1->g, arg1->b, 0xFF);
    for (x = 0; x < 640; x += func_8004CA10(arg0)) {
        for (y = 0; y < 480; y += func_8004CA24(arg0)) {
            func_8004D19C(x, y, arg0, 0, 0);
        }
    }
    gSPDisplayList(GFX_DL++, D_80094F50);
}

extern f32 D_8160C2D4;
extern f32 D_8160C2D8;
extern u16 D_8160C188[];
extern s32 func_8004C990(s32, s32);
extern void func_8004D19C(s32, s32, void *, s32, s32);
extern void func_8004D1FC(void *);
void func_816099E0(s32 arg0, s32 arg1, s32 arg2, f32 arg3) {
    void *temp;

    if (arg3 > 1.0f) {
        arg3 = D_8160C2D4;
    }
    if (arg3 < 0.0f) {
        arg3 = 0.0f;
    }
    temp = (void *)func_8004C990(0x9F, D_8160C188[(s32)(arg3 * D_8160C2D8)]);
    func_8004D1FC(temp);
    func_8004D19C(arg0 - 0x10, arg1 - 0x10, temp, 0, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81609A90.s")

extern u32 D_8160BDF4;
extern void func_800226C0(s32);
extern void _bzero(void *, s32);
void func_81609CB8(void) { if ((D_8160BDF4 >> 31) != 0) func_800226C0(0xA5); if (((D_8160BDF4 << 1) >> 31) != 0) func_800226C0(0xA6); if (((D_8160BDF4 << 2) >> 31) != 0) func_800226C0(0xA9); if (((D_8160BDF4 << 3) >> 31) != 0) func_800226C0(0xA7); if (((D_8160BDF4 << 4) >> 31) != 0) func_800226C0(0xA8); if (((D_8160BDF4 << 5) >> 31) != 0) func_800226C0(0xAA); if (((D_8160BDF4 << 6) >> 31) != 0) func_800226C0(0xAC); if (*(u8 *)&D_8160BDF4 & 1) func_800226C0(0xAB); _bzero(&D_8160BDF4, 4); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81609DC0.s")
#endif
