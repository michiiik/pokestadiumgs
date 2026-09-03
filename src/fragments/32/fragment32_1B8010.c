#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88306D00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88306D6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88306DAC.s")

extern void func_88004B60(s32, u8, s32 *);
extern u8 D_88601896;
extern s32 D_88601898;
extern u8 func_88306D00;
extern u8 func_88306D6C;
extern u8 func_88306DAC;
void func_88306E18(s32 arg0) {
    s32 *sp1C;

    switch (arg0) {                                 /* irregular */
    case 0:
        sp1C = &func_88306D00;
        break;
    case 1:
        sp1C = &func_88306D6C;
        break;
    case 2:
        sp1C = &func_88306DAC;
        break;
    }
    func_88004B60(D_88601898, D_88601896, sp1C);
}

extern s32 D_88308EA0;
extern s16 D_88308EB8[];
extern u8 D_88308EB0;
extern s8 D_88308EB1;
extern s16 D_88308EB4;
extern s16 D_88308EC0;
void func_88306E90(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, s8 arg5) {
    D_88308EA0 = 0;
    D_88308EB8[0] = arg0;
    D_88308EB8[1] = arg1;
    D_88308EB8[2] = arg2;
    D_88308EB8[3] = arg3;
    D_88308EB0 = arg4;
    D_88308EB1 = arg5;
    D_88308EB4 = D_88308EB8[arg5];
    D_88308EC0 = 0;
}

extern void func_800226C0(s32);
extern s32 D_88308EA0;
extern s8 D_88308EB1;
extern s8 D_88308EB2;
extern s16 D_88308EB6;
extern s16 D_88308EB8[];
void func_88306F18(u8 arg0) {
    if (arg0 < D_88308EB1) {
        func_800226C0(0x46);
        D_88308EB2 = D_88308EB1 - 1;
        D_88308EB6 = D_88308EB8[D_88308EB2];
        D_88308EA0 = 1;
    }
}

extern void func_800226C0(s32);
extern s32 D_88308EA0;
extern u8 D_88308EB0;
extern s8 D_88308EB1;
extern s8 D_88308EB2;
extern s16 D_88308EB6;
extern s16 D_88308EB8[];
void func_88306F90(void) {
    if (D_88308EB1 < (D_88308EB0 - 1)) {
        func_800226C0(0x46);
        D_88308EB2 = D_88308EB1 + 1;
        D_88308EB6 = D_88308EB8[D_88308EB2];
        D_88308EA0 = 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_8830700C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88307294.s")

extern Gfx *D_800D0510;
extern u8 *D_88308EA8;
extern u8 *D_88308EAC;
extern s32 func_8004D1FC(u8 *);
extern s32 func_8004D27C(u8 *, s32, s32);
void func_88307468(void) {
    gDPPipeSync(D_800D0510++);
    gDPSetCombine(D_800D0510++, 0x309661, 0x552EFF7F);
    func_8004D1FC(D_88308EA8);
    func_8004D27C(D_88308EAC, 0x100, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_883074E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_8830765C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_8830780C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88307938.s")
#endif
