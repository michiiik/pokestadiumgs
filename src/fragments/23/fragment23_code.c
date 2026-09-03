#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/23/fragment23_code/func_82A00020.s")

extern s32 func_800506A4(u8 *);
extern void func_80050578(u8 *, s32);
extern s32 D_82A01898[];
s32 func_82A00178(s32 arg0, u8 *arg1) {
    if ((arg0 != 0) && (arg0 == 1) && (func_800506A4(arg1) != 0)) {
        func_80050578(arg1, D_82A01898[guRandom() & 3]);
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/23/fragment23_code/func_82A001DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/23/fragment23_code/func_82A005D8.s")

s32 func_82A00784(s32 arg0, u8 *arg1) { if (arg0 == 0) { (*(u16 *)((u8 *)arg1 + 2)) &= 0xFFFD; } return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/23/fragment23_code/func_82A007A0.s")

extern u8 D_82A019C8[];
extern u8 D_82A01A0A[];
s32 func_82A0083C(s32 arg0, void *arg1) {
    s32 index;
    u8 *entry;
    index = *(s32 *)((u8 *)arg1 + 0x20);
    if ((arg0 != 0) && (arg0 == 1)) {
        if (D_82A01A0A[index * 4] != 0) {
            entry = D_82A019C8 + index * 0x10;
            *(s16 *)((u8 *)arg1 + 8) = *(s16 *)(entry + 8) + *(s16 *)(entry + 4);
        } else {
            *(u16 *)((u8 *)arg1 + 2) &= 0xFFFD;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/23/fragment23_code/func_82A0089C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/23/fragment23_code/func_82A009A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/23/fragment23_code/func_82A00A04.s")

s32 func_82A00A90(void *arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (((*(u8 *)((u8 *)(arg0) + (1))) == 0) && ((*(u8 *)((u8 *)(arg0) + (0))) != 2)) {
        var_v1 = 0;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/23/fragment23_code/func_82A00ABC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/23/fragment23_code/func_82A00BF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/23/fragment23_code/func_82A00C84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/23/fragment23_code/func_82A01098.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/23/fragment23_code/func_82A011E4.s")

extern void func_800088DC(void);
extern void func_82A01098(void);
extern void func_800503A4(u8 *);
extern s32 func_80008648(void);
extern void func_82A011E4(s16, s16, s32, Gfx **);
extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern s16 D_82A01998;
extern s16 D_82A0199A;
extern u8 *D_82A019B8;
extern u8 *D_82A019BC;
extern u8 *D_82A019C0;
void func_82A015C0(void) {
    func_800088DC();
    func_82A01098();
    func_800503A4(D_82A019C0);
    func_800503A4(D_82A019B8);
    func_800503A4(D_82A019BC);
    gSPDisplayList(D_800D0510++, D_80094E38);
    func_82A011E4(D_82A01998, D_82A0199A, 1, &D_800D0510);
    func_80008648();
}

extern s32 StageContext_GetFadeMode(void);
s32 func_82A01654(s32 arg0) {
    s32 var_v1;
    s32 sp1C;
    var_v1 = arg0;
    switch (arg0) {
    case 0:
        sp1C = var_v1;
        if (StageContext_GetFadeMode() == 0) {
            var_v1 = 1;
        }
        break;
    case 1:
        break;
    case 2:
        sp1C = var_v1;
        if (StageContext_GetFadeMode() == 1) {
            var_v1 = 3;
        }
        break;
    }
    return var_v1;
}

extern void StageFade_StartFromOpaque(s32);
extern void func_800086A4(s32);
extern void func_82A00020();
extern void func_82A015C0();
s32 func_82A01654(s32);

void func_82A016C4(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    do {
        func_82A00020();
        func_82A015C0();
        temp_v0 = func_82A01654(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 3);
}

extern void Gfx_InitDisplayListBuffers(s32, s32);
s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_80008514(s32);
extern void func_80008574();
extern void func_8004C8C0(s32);
extern void func_82A00C84(s32, s32);
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
extern u8 D_446E30;
extern void func_8004C09C(s32 arg0);
extern s32 func_80047588(s32 arg0, s32 arg1);
u8 *Asset_LoadToSegment(s32 id, u8 *rom_start, u8 *rom_end, s32 arg3);
extern u8 D_1000000[];
extern u8 D_447D00[];
void func_80047610(void);
void func_8004C398(void);
void Gfx_FreeDisplayListBuffers(void);
s32 fragment23_main(s32 arg0, s32 arg1) {
    s32 sp24;

    main_pool_push_state(0x4641544C);
    Gfx_InitDisplayListBuffers(0x18000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(0x103);
    func_8004C8C0(0x73);
    func_8004C8C0(0x74);
    func_8004C8C0(0xE);
    func_80047588(0x1C, 0);
    Asset_LoadToSegment((s32) ((u32) ((s32) D_1000000 & 0x0F000000) >> 0x18), &D_446E30, D_447D00, 0);
    func_82A00C84(arg0, arg1);
    func_80008514(sp24);
    func_82A016C4();
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x4641544C);
    return 0;
}
#endif
