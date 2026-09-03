#include "global.h"


#ifdef VERSION_US
s32 func_81601980(s32 *arg0, s32 arg1) {
    return arg0[arg1 / 32] & (1 << (arg1 % 32));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816019C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81601A38.s")

void func_81601A78(s32 arg0, s32 arg1) { func_816019C0(arg0, 0xAD, arg1); func_816019C0(arg0, 0x4F, arg1); func_816019C0(arg0, 0x4E, arg1); func_816019C0(arg0, 0x50, arg1); func_816019C0(arg0, 0x54, arg1); func_816019C0(arg0, 0x53, arg1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81601B00.s")

void func_81601D24(s32 arg0, s32 arg1) {
    if (arg1 != 0x19) func_816019C0(arg0, 0xA3, 1);
    if (arg1 != 0x71) func_816019C0(arg0, 0x1E, 1);
    if (arg1 != 0x53) func_816019C0(arg0, 0x69, 1);
    if (arg1 != 0x84) func_816019C0(arg0, 0x23, 1);
    if ((arg1 != 0x68) && (arg1 != 0x69)) func_816019C0(arg0, 0x76, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81601DE8.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816021E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81602240.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816028E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81602940.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81602AEC.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81603368.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81603404.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816049BC.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81605F94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_8160615C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606304.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606694.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606800.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816068C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606B5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606E14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606E84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81606F88.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_8160762C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81607680.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_8160771C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816077B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81607834.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816078C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81607B1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81607DB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81608044.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816083A4.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81608890.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81608918.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816089E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81608A38.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816098B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_816099E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81609A90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81609CB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D9520/func_81609DC0.s")
#endif
