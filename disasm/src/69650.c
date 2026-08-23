#include "global.h"

extern void _bzero(void *dst, s32 size);
extern s32 func_8006A3B8(u16 value);
extern s32 func_8006A400(u16 value);
extern void *main_pool_alloc(u32 size, u32 tag);
extern void *Fragment_Load(u32 pool, u32 source, u32 end);
extern s32 Fragment_LoadAndCall(u32 pool, u32 source, u32 end, s32 arg3,
                                void *arg4);
extern void func_80068B78(void *record);
extern u8 fragment4_ROM_START[];
extern u8 fragment5_ROM_START[];
extern u8 fragment6_ROM_START[];
extern u8 fragment7_ROM_START[];
extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment18_ROM_START[];
extern u8 fragment19_ROM_START[];

#define D_81600000 ((u8 *)0x81600000)
#define D_81700000 ((u8 *)0x81700000)
#define D_81800000 ((u8 *)0x81800000)
#define D_83100000 ((u8 *)0x83100000)

#ifdef VERSION_US
/* Initialize the compact scene descriptor and copy its 9-byte source key. */
void func_80068A50(void *descriptor, const void *source) {
    u8 *dst = (u8 *)descriptor;
    const u8 *src = (const u8 *)source;
    s32 i;

    if (descriptor == NULL) {
        return;
    }
    _bzero(descriptor, 0x5C);
    dst[0] = 0;
    for (i = 0; i < 9; i++) {
        dst[4 + i] = src[i];
    }
}

/* Select the scene command and participant slot associated with a state. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/69650/func_80068AB0.s")

#if 0
s32 func_80068AB0(u32 state) {
    u16 command = 0xFFFF;
    u16 slot = 4;

    switch (state) {
        case 0:
            command = 0x200;
            break;
        case 1:
            command = 0x202;
            slot = 1;
            break;
        case 2:
            command = 0x202;
            slot = 2;
            break;
        case 3:
            command = 0x202;
            slot = 3;
            break;
        case 4:
            command = 0x202;
            break;
        case 5:
            command = 0x220;
            break;
        case 6:
            command = 0x201;
            slot = 1;
            break;
        case 7:
            command = 0x201;
            slot = 2;
            break;
        case 8:
            command = 0x201;
            slot = 3;
            break;
        case 9:
            command = 0x201;
            break;
        case 10:
            command = 0x203;
            break;
        case 11:
            command = 0x210;
            break;
        default:
            break;
    }

    func_8006A3B8(command);
    return func_8006A400(slot);
}
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/69650/func_80068B78.s")

s32 func_80068CBC(void *record) {
    u8 *temporary = main_pool_alloc(0x5C, 0);
    u8 *output = (u8 *)record;
    u32 pool816 = (((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10;
    u32 pool817 = (((u32)D_81700000 & 0x0FF00000) >> 20) - 0x10;
    u32 pool818 = (((u32)D_81800000 & 0x0FF00000) >> 20) - 0x10;
    u32 pool831 = (((u32)D_83100000 & 0x0FF00000) >> 20) - 0x10;
    s32 result = 1;
    s32 i;

    func_80068A50(temporary, record);
    Fragment_Load(pool816, (u32)fragment11_ROM_START,
                  (u32)fragment12_ROM_START);
    Fragment_Load(pool818, (u32)fragment4_ROM_START,
                  (u32)fragment5_ROM_START);
    Fragment_Load(pool817, (u32)fragment18_ROM_START,
                  (u32)fragment19_ROM_START);
    Fragment_LoadAndCall(pool831, (u32)fragment6_ROM_START,
                         (u32)fragment7_ROM_START, 0, temporary);

    for (i = 0; i < 8; i++) {
        output[i] = temporary[4 + i];
    }
    output[8] = temporary[0x0C];

    if ((temporary[0x58] & 1) != 0) {
        result = 0;
    } else {
        func_80068B78(temporary);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/69650/Game_State16_Run.s")
#endif
