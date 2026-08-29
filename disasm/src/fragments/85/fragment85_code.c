#include "global.h"


#ifdef VERSION_US
extern f32 D_8FD02120;
s32 func_8FD00020(f32 arg0) {
    s32 temp_v1;

    temp_v1 = (s32) arg0 & 0x1F;
    return ((temp_v1 << 0xA) + (s32) (((arg0 - (f32) temp_v1) + D_8FD02120) * 1024.0f)) & 0xFFFF;
}
#endif

void func_8FD0006C(void) {
}

#ifdef VERSION_US
extern Gfx *D_800D0510;
void func_8FD00074(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    gDPPipeSync(D_800D0510++);
    gDPSetPrimColor(D_800D0510++, 0, 0, arg0, arg1, arg2, arg3);
}
#endif

#ifdef VERSION_US
extern void func_8FD00074(u8, u8, u8, u8);
void func_8FD000E4(u8 *arg0, u8 arg1) {
    func_8FD00074(arg0[0], arg0[1], arg0[2], arg1);
}
void func_8FD000E4_padding(void) {}
#endif

#ifdef VERSION_US
extern s32 func_8004C990(s32, s32);
extern void func_8004D19C(s32, s32, s32, s32, s32);
void func_8FD00124(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    s32 value = func_8004C990((s32)arg2, (s32)arg3);
    func_8004D19C((s32)arg0, (s32)arg1, value, 0, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD00170.s")
#endif

#ifdef VERSION_US
extern s32 func_8004CA10(u16 *);
extern s32 func_8004CA24(u16 *);
extern u8 *func_8004CA60(u8 *);
extern s32 func_8004CA38(u8 *);
extern s32 func_8004CA4C(u8 *);
extern void func_8FD00170(s16, s16, u16, u16, s32, s32, u8 *, s32, s32, s32);
void func_8FD00514(s16 arg0, s16 arg1, u16 arg2, u16 arg3, u16 *arg4) {
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp24 = 1;
    u8 *sp34;
    sp44 = func_8004CA10(arg4);
    sp40 = func_8004CA24(arg4);
    sp34 = func_8004CA60((u8 *)arg4);
    sp3C = func_8004CA38((u8 *)arg4);
    func_8FD00170(arg0, arg1, arg2, arg3, sp44, sp40, sp34, sp3C, func_8004CA4C((u8 *)arg4), sp24);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD005B4.s")
#endif

#ifdef VERSION_US
s32 func_8004C990(s32, s32);
extern void func_8004D1FC(s32);

void func_8FD00654(void) {
    func_8004D1FC(func_8004C990(0x21, 3));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD00680.s")
#endif

#ifdef VERSION_US
s32 func_8004C990(s32, s32);

void func_8FD008BC(void) {
    func_8004D1FC(func_8004C990(0x1F, 0));
}
#endif

#ifdef VERSION_US
extern void func_80044270(s16, s16, s16, s16, s32, s32, s32, s32, s32);
void func_8FD008E8(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
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
extern Gfx *D_800D0510;
extern u8 D_8FD01FB8[];
extern u8 D_8FD020A0;
extern s16 D_8FD020B0;
extern s16 D_8FD020B4;
extern u16 D_8FD020B8;
extern u16 D_8FD020BC;
extern void func_8FD00680(s16, s16, u16, u16);
extern void func_8FD000E4(u8 *arg0, u8 arg1);
extern void func_8FD00654(void);
extern void func_8FD008BC(void);
extern void func_8FD008E8(s16 arg0, s16 arg1, u16 arg2, u16 arg3);
void func_8FD009B4(void) {
    gSPDisplayList(D_800D0510++, D_8FD01FB8);
    func_8FD000E4(&D_8FD020A0, 0xFF);
    func_8FD008BC();
    func_8FD008E8(D_8FD020B0, D_8FD020B4, D_8FD020B8, D_8FD020BC);
    func_8FD00654();
    func_8FD00680(D_8FD020B0, D_8FD020B4, D_8FD020B8, D_8FD020BC);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD00A5C.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_8FD02060[];
extern u8 D_8FD02188;
extern s16 D_8FD020D6;
extern s16 D_8FD020D8;
extern u16 D_8FD020DC;
extern u16 D_8FD020E0;
extern void func_8FD005B4(s16, s16, u16, u16);
void func_8FD00B28(void) {
    gSPDisplayList(D_800D0510++, D_8FD02060);
    if ((D_8FD02188 == 2) || (D_8FD02188 == 4)) {
        func_8FD005B4(D_8FD020D6, D_8FD020D8, D_8FD020DC, D_8FD020E0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD00BA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD00CD0.s")
#endif

#ifdef VERSION_US
extern void GfxImage_FillCurrent(s32 *, s32);
extern void func_80008648();
extern void func_800088DC();
extern void func_8FD009B4();
extern void func_8FD00A5C();
extern void func_8FD00B28();
extern void func_8FD00BA4();
extern void func_8FD00CD0();
extern Gfx *D_800D0510;
void func_8FD01120(void) {
    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 1);
    func_8FD009B4();
    func_8FD00A5C();
    func_8FD00B28();
    func_8FD00BA4();
    func_8FD00CD0();
    func_80008648();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD01180.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD01310.s")
#endif

#ifdef VERSION_US
extern u8 D_8FD02188;

void func_8FD014A0(void) {
    if ((*(u8 *)((u8 *)(&D_8FD02188) + (0))) == 2) {
        (*(s16 *)((u8 *)(&D_8FD02188) + (2))) = (s16) ((*(s16 *)((u8 *)(&D_8FD02188) + (2))) + 1);
        (*(s16 *)((u8 *)(&D_8FD02188) + (2))) = (s16) ((*(s16 *)((u8 *)(&D_8FD02188) + (2))) & 1);
    }
}
#endif

#ifdef VERSION_US

void func_8FD014D8(void) {
    if ((*(u8 *)((u8 *)(&D_8FD02188) + (0))) == 2) {
        (*(s16 *)((u8 *)(&D_8FD02188) + (2))) = (s16) ((*(s16 *)((u8 *)(&D_8FD02188) + (2))) + 1);
        (*(s16 *)((u8 *)(&D_8FD02188) + (2))) = (s16) ((*(s16 *)((u8 *)(&D_8FD02188) + (2))) & 1);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD01510.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD01554.s")
#endif

#ifdef VERSION_US
extern void func_8FD01180();
extern void func_8FD01310();
extern void func_8FD01510();
extern void func_8FD01554();
extern u16 D_8FD02182;
extern u16 D_8FD02184;
void func_8FD016E4(void) {
    if (D_8FD02184 & 0x800) {
        func_8FD01180();
    } else if (D_8FD02184 & 0x400) {
        func_8FD01310();
    } else if (D_8FD02184 & 0x200) {
        func_8FD014A0();
    } else if (D_8FD02184 & 0x100) {
        func_8FD014D8();
    }
    if (D_8FD02182 & 0x8000) {
        func_8FD01554();
        return;
    }
    if (D_8FD02182 & 0x4000) {
        func_8FD01510();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD01794.s")
#endif

#ifdef VERSION_US
extern void *D_80087200;
extern u8 D_8FD020E4;
extern u16 D_8FD02180;
void func_8FD01964(void) {
    func_80064D28();
    if (D_8FD020E4 != 0) {
        D_8FD02180 = (*(u16 *)((u8 *)(D_80087200) + (6)));
        D_8FD02182 = (*(u16 *)((u8 *)(D_80087200) + (8)));
        D_8FD02184 = (*(u16 *)((u8 *)(D_80087200) + (0xC)));
        return;
    }
    D_8FD02180 = 0;
    D_8FD02182 = 0;
    D_8FD02184 = 0;
}
#endif

#ifdef VERSION_US
extern void func_8FD016E4();
extern void func_8FD01794();
extern void func_8FD01964();
void func_8FD019DC(void) {
    do {
        func_8FD01964();
        func_8FD016E4();
        func_8FD01794();
        func_8FD01120();
    } while (D_8FD02188 != 5);
}
#endif

#ifdef VERSION_US
extern void func_8004C8C0(s32);

void func_8FD01A38(void) {
    func_8004C8C0(0x20);
    func_8004C8C0(0x21);
    func_8004C8C0(0x1F);
    func_8004C8C0(0x164);
    func_8004C8C0(0x7A);
}
#endif

#ifdef VERSION_US
extern void func_8004C4B0(s32);

void func_8FD01A78(void) {
    func_8004C4B0(0x4A);
    func_8004C4B0(0x10);
    func_8004C4B0(6);
    func_8004C4B0(8);
    func_8004C4B0(0xC);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD01AB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD01B90.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/85/fragment85_code/func_8FD01DA8.s")
#endif

#ifdef VERSION_US
extern void _bzero(u8 *, s32);
extern void func_8FD01B90();
extern void func_8FD01DA8(u8 *);
void func_8FD01E58(s32 arg0) {
    func_8FD01A38();
    func_8FD01A78();
    func_8FD01B90();
    _bzero(&D_8FD02188, 0x2128);
    (*(s16 *)((u8 *)(&D_8FD02188) + (6))) = 0x10;
    (*(s16 *)((u8 *)(&D_8FD02188) + (8))) = 0x4C;
    (*(s16 *)((u8 *)(&D_8FD02188) + (0xA))) = 3;
    func_8FD01DA8(&D_8FD02188);
}
#endif

#ifdef VERSION_US
extern void func_80006CD0(s32, s32);
s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_80008514(s32);
extern void func_80008574();
extern void func_8FD01E58(s32);
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
s32 fragment85_main(s32 arg0, s32 arg1) {
    s32 sp24;

    main_pool_push_state(0x52434544);
    sp24 = func_800082E0(0, 1, 2, 0, 2, 1);
    func_80006CD0(0x10000, 0);
    func_80047588(6, 0);
    func_8004C09C(0x43);
    func_8FD01E58(0);
    func_80008514(sp24);
    func_800086A4(2);
    func_80007AEC(0xA);
    func_8FD019DC();
    func_80008574();
    func_80047610();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x52434544);
    return 0;
}
#endif
