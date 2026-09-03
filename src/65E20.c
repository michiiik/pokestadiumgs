#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65E20/func_80065220.s")

extern void func_800354B4(s32, s32, s32);
extern void func_800355E4(s32);
extern s32 Fragment_LoadAndCall(s32, void *, void *, u32, u32);
extern u8 D_82000000;
extern u8 fragment16_ROM_START;
extern u8 fragment17_ROM_START;
void func_800657B0(void) {
    func_800354B4(1, 0, 0);
    func_800355E4(0x24);
    Fragment_LoadAndCall(((u32)((s32)&D_82000000 & 0x0FF00000) >> 20) - 0x10,
        &fragment16_ROM_START, &fragment17_ROM_START, 0, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/65E20/func_80065814.s")

extern void func_80065814(s32);
extern void Audio_ResetRequestId(void);
extern void func_800727D4(s32);
extern void func_80065B20(void);
void func_80065974(u32 arg0) {
    s32 temp_v0;
    temp_v0 = arg0 & 1;
    switch (temp_v0) {
    case 0:
        func_80065814(arg0 >> 1);
        Audio_ResetRequestId();
        return;
    case 1:
        func_800354B4(6, 0, 0);
        func_800727D4(1);
        Audio_ResetRequestId();
        if (((arg0 >> 1) % 3U) == 2) {
            func_800354B4(0, 0, 0);
            func_80065B20();
        }
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/65E20/func_80065A18.s")

extern void Game_SetState(s32);
extern u8 D_83F00000;
extern u8 D_82900000;
extern u8 fragment15_ROM_START;
extern u8 fragment67_ROM_START;
extern u8 fragment68_ROM_START;
void func_80065B20(void) {
    Fragment_LoadAndCall(((u32)((s32)&D_83F00000 & 0x0FF00000) >> 20) - 0x10,
        &fragment15_ROM_START, &fragment16_ROM_START, 0, 0);
    Fragment_LoadAndCall(((u32)((s32)&D_82900000 & 0x0FF00000) >> 20) - 0x10,
        &fragment67_ROM_START, &fragment68_ROM_START, 0, 0);
    Game_SetState(1);
}
#endif
