#include "global.h"


#ifdef VERSION_US
u16 func_80003820(const u8 *arg0) {
    return (u16)((arg0[0] << 8) | arg0[1]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003838.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800039C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003A78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003AB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003AF0.s")

void func_80003CD0(void) { extern OSMesgQueue D_800CD000; extern OSMesg D_800CD018[]; osCreateMesgQueue(&D_800CD000, D_800CD018, 1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003D00.s")

extern OSMesgQueue D_800CD000;
extern void func_80006BB4(s32, u8 *, s32, s32, OSMesgQueue *, s32);
void func_80003DD4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_s0;
    for (; arg2 > 0; arg2 -= var_s0) {
        if (arg2 >= 0x1000) var_s0 = 0x1000; else var_s0 = arg2;
        func_80006BB4(arg3, arg0, arg1, var_s0, &D_800CD000, 0);
        osRecvMesg(&D_800CD000, NULL, 1);
        arg0 += var_s0;
        arg1 += var_s0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003E84.s")

s32 func_80003F54(s32 arg0) { return osFlashSectorErase(arg0 << 7); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003F74.s")

extern OSMesgQueue D_800CD000;
extern void func_80006B40(u8 *, u8 *, s32, OSMesgQueue *, s32);
void func_80004024(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 remaining = arg2 - arg1;
    s32 chunk;
    while (remaining > 0) {
        chunk = remaining >= 0x1000 ? 0x1000 : remaining;
        func_80006B40(arg0, arg1, chunk, &D_800CD000, 0);
        osRecvMesg(&D_800CD000, NULL, 1);
        remaining -= chunk;
        arg0 += chunk;
        arg1 += chunk;
    }
}

s32 func_800040C4(u8 *arg0) {
    return *(s32 *)(arg0 + 0xC) + 0x100;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800040D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800041E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004254.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800042C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004458.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800045E0.s")

extern u8 *func_800042C0(u8 *, u8 *, s32, s32);
extern s32 func_80002DE4(u8 *);
extern void func_800020A0(s32, u8 *, s32);
extern void func_80002DD4(u8 *, s32, void *);
extern void func_800045E0(void *, u32);
u8 *func_80004638(s32 id, u8 *rom_start, u8 *rom_end, s32 arg3) {
    u8 *vaddr = func_800042C0(rom_start, rom_end, arg3, 0);
    if (vaddr != NULL && id > 0) {
        func_800020A0(id, vaddr, func_80002DE4(vaddr));
        func_80002DD4(vaddr, id + 0x82000000, (void *)func_800045E0);
    }
    return vaddr;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800046C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004718.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800047B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800047F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_8000484C.s")

void func_800049B8(void) { func_800029E0(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800049D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004B4C.s")

void func_80004B78(void) { func_80004A40(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004B98.s")
#endif
