#include "global.h"

extern void func_800354B4(s32 event, s32 arg1, s32 arg2);
extern s32 func_8006A388(void);
extern void *Fragment_Load(u32 pool, u32 source, u32 end);
extern s32 Fragment_LoadAndCall(u32 pool, u32 source, u32 end, s32 arg3,
                                void *arg4);
extern u8 fragment58_ROM_START[];
extern u8 fragment59_ROM_START[];
extern u8 fragment64_ROM_START[];
extern u8 fragment65_ROM_START[];
extern u8 fragment66_ROM_START[];
extern u8 fragment67_ROM_START[];
extern u8 fragment68_ROM_START[];

#define D_82900000 ((u8 *)0x82900000)
#define D_82E00000 ((u8 *)0x82E00000)
#define D_83400000 ((u8 *)0x83400000)
#define D_87F00000 ((u8 *)0x87F00000)


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/69F70/Game_State14_Run.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/69F70/func_80069750.s")

 s32 func_800697B8(void) {
    u16 resultCode;
    u32 pool829 = (((u32)D_82900000 & 0x0FF00000) >> 20) - 0x10;
    u32 pool82E = (((u32)D_82E00000 & 0x0FF00000) >> 20) - 0x10;

    func_800354B4(0xD, 0, 0);
    Fragment_LoadAndCall(pool829, (u32)fragment67_ROM_START,
                         (u32)fragment68_ROM_START, 2, NULL);
    resultCode = (u16)func_8006A388();
    return Fragment_LoadAndCall(pool82E, (u32)fragment66_ROM_START,
                                (u32)fragment67_ROM_START, 0,
                                &resultCode) != 0;
}

s32 func_80069868(void) {
    u16 resultCode;
    u32 pool87F = (((u32)D_87F00000 & 0x0FF00000) >> 20) - 0x10;
    u32 pool834 = (((u32)D_83400000 & 0x0FF00000) >> 20) - 0x10;

    func_800354B4(0xC, 0, 0);
    resultCode = (u16)func_8006A388();
    Fragment_Load(pool87F, (u32)fragment64_ROM_START,
                  (u32)fragment65_ROM_START);
    return Fragment_LoadAndCall(pool834, (u32)fragment58_ROM_START,
                                (u32)fragment59_ROM_START, 0,
                                &resultCode);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/69F70/Game_State15_Run.s")
#endif
