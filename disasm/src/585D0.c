#include "global.h"


#ifdef VERSION_US
u16 func_800579D0(const u8 *arg0) { return (u16)((arg0[1] << 8) | arg0[0]); }
#endif

#ifdef VERSION_US
void func_800579E8(u8 *arg0, u16 arg1)
{
  u16 new_var;
  arg0[0] = arg1 & 0xFFFF;
  arg0[1] = (new_var = arg1 >> 8);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_800579FC.s")
#endif

#ifdef VERSION_US
extern u8 D_80128574[];
s32 func_80057A1C(s32 arg0) {
    u8 value = D_80128574[arg0 * 0x70];
    if ((value == 5) || (value == 6)) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern u8 D_80128574[]; s32 func_80057A5C(s32 index) { return D_80128574[index * 112] == 7; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057A80.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057ACC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057BCC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057C74.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057D74.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057E08.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057EB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057F58.s")
#endif

#ifdef VERSION_US
void func_80057FE8(u8 *start, u8 *end) {
    s32 sum = 0;

    while (start < end) {
        sum += *start++;
    }
    *end = 0xFF - (sum & 0xFF);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058018.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005805C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005818C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058288.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058614.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_800587BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058850.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058880.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005892C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_800589A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058C6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058D18.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058D98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058DE4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058E60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058F18.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058FD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059050.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_800590CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005910C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005914C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_800591BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059234.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059274.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_800592B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059320.s")
#endif

#ifdef VERSION_US
void func_80059468(s32 arg0) { func_80059320(arg0, 4); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059488.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059578.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059670.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_800596D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005989C.s")
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_80059AE0(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x10000) != 0; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059B08.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059D00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059DD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059EF8.s")
#endif

#ifdef VERSION_US
void func_8005A014(s32 arg0) { func_80059EF8(arg0, 1); }
#endif

#ifdef VERSION_US
void func_8005A034(s32 arg0) { func_80059EF8(arg0, 2); }
#endif

#ifdef VERSION_US
void func_8005A054(s32 arg0) { func_80059EF8(arg0, 5); }
#endif

#ifdef VERSION_US
void func_8005A074(s32 arg0) { func_80059EF8(arg0, 8); }
#endif

#ifdef VERSION_US
void func_8005A094(s32 arg0) { func_80059EF8(arg0, 16); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A0B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A0F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A134.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A174.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A228.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A364.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A468.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A5C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A60C.s")
#endif

void func_8005A8E4(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A8EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A92C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A98C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005ACE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005AD58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005ADD8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005AEA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005AFF4.s")
#endif

#ifdef VERSION_US
void func_8005B058(s32 arg0) { func_80059320(arg0, 1); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B078.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B0B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B0E8.s")
#endif

#ifdef VERSION_US
void func_8005B120(s32 arg0) { func_80059320(arg0, 0xFF); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B140.s")
#endif

#ifdef VERSION_US
void func_8005B190(s32 arg0) { if (func_80056A5C(arg0, 0) == 0) func_80064D58(arg0, 2); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B1C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B280.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B314.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B378.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B4B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B5D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B6F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B778.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B848.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B924.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BA00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BA88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BBD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BCF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BD4C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BE08.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BECC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BF28.s")
#endif

#ifdef VERSION_US
u8 *func_8005B280();

u8 func_8005BF78(void) {
    u8 *temp_v0;
    u8 var_v1;

    temp_v0 = func_8005B280();
    if (temp_v0 != NULL) {
        var_v1 = *temp_v0;
    } else {
        var_v1 = 0;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BFA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BFF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C028.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C060.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C0B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C12C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C1AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C22C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C2B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C2FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C348.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C394.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C41C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C52C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C584.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C5CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C614.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C694.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C6D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C714.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C750.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C7D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C880.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C8D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C988.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C9E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CAA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CB38.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CBA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CC14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CCD8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CDDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CF20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CFE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D0B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D194.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D2BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D348.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D418.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D4FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D610.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D698.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D778.s")
#endif

#ifdef VERSION_US
extern s32 D_80128748;

s32 func_8005D8C0(void) {
    return D_80128748;
}
#endif

#ifdef VERSION_US
extern u8 D_80128575[]; u8 func_8005D8CC(s32 index) { return D_80128575[index * 112]; }
#endif

#ifdef VERSION_US
extern u8 D_8012874C;
extern u8 D_8012874D;
s32 func_8005D8E8(s32 arg0) {
    s32 mask = 1 << arg0;
    if (!(D_8012874C & mask)) {
        return 1;
    }
    if (!(D_8012874D & mask)) {
        return 2;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern u8 D_80128574[]; u8 func_8005D92C(s32 index) { return D_80128574[index * 112]; }
#endif

#ifdef VERSION_US
extern u8 D_801285B8[]; u8 func_8005D948(s32 index) { return D_801285B8[index * 112]; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D964.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D9E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005DA1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005DAC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005DB84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005DC48.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005DD14.s")
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DDD4(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x100) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DDF8(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x200) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DE1C(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x200000) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DE44(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x400) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DE68(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x1000) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DE8C(s32 index) { return !((*(u32 *)(D_80128570 + index * 112) & 0x2000) != 0); }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DEB4(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x800) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DED8(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x4000) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DEFC(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x8000) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DF20(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x40000) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DF48(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x80000) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DF70(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x100000) != 0; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005DF98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005DFD4.s")
#endif

#ifdef VERSION_US
extern u8 D_80128570[];
u8 func_8005E03C(s32 arg0) {
    u8 *entry = D_80128570 + (arg0 * 0x70);
    if (*(u32 *)entry & 2) {
        return *(u8 *)(*(u8 **)(entry + 0x68) + 0x5E5);
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E07C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E0BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E12C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E1F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E278.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E2BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E304.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E350.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E420.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E524.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E5D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E648.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E6B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E728.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E8A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005EB3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005ECA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005ED78.s")
#endif

#ifdef VERSION_US
extern void func_8005EB3C(void *, s32);

void func_8005EE4C(s32 arg0) {
    func_8005EB3C((arg0 * 0x70) + 8 + D_80128570, 0xFB);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005EE88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005EF78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F04C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F0B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F110.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F190.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F37C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F3B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F3E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F5D4.s")
#endif

#ifdef VERSION_US
extern void func_8005F3E0(s32, s32, s32, s32, s32, s32);
void func_8005F620(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    func_8005F3E0(arg0 & 0xFF, arg1 & 0xFFFF, arg2 & 0xFF, arg3 & 0xFF, (s32) arg4, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F668.s")
#endif

#ifdef VERSION_US
extern void func_8005F668(s32, s32, s32);
extern void func_8005F808(s32, s32, s32);
void func_8005F790(s32 arg0, s32 arg1) {
    s32 *p = &arg1;
    func_8005F668(arg0, arg1 & 0xFF, 0);
}
#endif

#ifdef VERSION_US
void func_8005F7B8(s32 arg0, s32 arg1) {
    s32 *p = &arg1;
    func_8005F668(arg0, arg1 & 0xFF, 1);
}
#endif

#ifdef VERSION_US
void func_8005F7E0(s32 arg0, s32 arg1) {
    s32 *p = &arg1;
    func_8005F668(arg0, arg1 & 0xFF, 2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F808.s")
#endif

#ifdef VERSION_US
void func_8005F9A4(s32 arg0, s32 arg1) {
    s32 *p = &arg1;
    func_8005F808(arg0, arg1 & 0xFFFF, 0);
}
#endif

#ifdef VERSION_US
void func_8005F9CC(s32 arg0, s32 arg1) {
    s32 *p = &arg1;
    func_8005F808(arg0, arg1 & 0xFFFF, 1);
}
#endif

#ifdef VERSION_US
extern void func_8005F808(s32, s32, s32);

void func_8005F9F4(s32 arg0, s32 arg1) {
    s32 *p = &arg1;
    func_8005F808(arg0, arg1 & 0xFFFF, 2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FA1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FAB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FB40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FBCC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FC7C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FD24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FDB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FE58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FF0C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FFB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80060110.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_800601A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80060250.s")
#endif

#ifdef VERSION_US
s32 func_80060348(s32 arg0, s32 arg1) {
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_80060358(s32 arg0, s32 arg1) {
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80060368.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80060538.s")
#endif

#ifdef VERSION_US
extern u8 D_800A4A40[];

u8 *func_800606D8(u8 *arg0) {
    return D_800A4A40;
}
#endif

#ifdef VERSION_US
s32 func_800606E8(s32 arg0) {
    return 0;
}
#endif

#ifdef VERSION_US
u8 func_800606F4(s32 arg0) {
    u8 var_v1;
    void *temp_v0;

    temp_v0 = (arg0 * 0x70) + D_80128570;
    var_v1 = 0;
    if ((*(u8 *)((u8 *)(temp_v0) + (4))) == 7) {
        var_v1 = (*(u8 *)((u8 *)(temp_v0) + (0x49)));
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8006072C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8006092C.s")
#endif
