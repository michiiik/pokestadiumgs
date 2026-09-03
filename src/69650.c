#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/69650/func_80068A50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/69650/func_80068AB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/69650/func_80068B78.s")

extern u8 D_81600000[];
extern u8 D_81800000[];
extern u8 D_81700000[];
extern u8 D_83100000[];
extern u8 fragment4_ROM_START[];
extern u8 fragment5_ROM_START[];
extern u8 fragment6_ROM_START[];
extern u8 fragment7_ROM_START[];
extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment18_ROM_START[];
extern u8 fragment19_ROM_START[];
extern void *main_pool_alloc(s32, s32);
extern void func_80068A50(void *, void *);
extern void Fragment_Load(s32, void *, void *);
extern s32 Fragment_LoadAndCall(s32, void *, void *, s32, void *);
extern void func_80068B78(void *);
#pragma pack(1)
typedef struct { s32 a; s32 b; u8 c; } Copy9Layout;
#pragma pack(0)
s32 func_80068CBC(void *arg0) {
    s32 var_v1;
    s32 sp2C;
    void *temp_v0;
    temp_v0 = main_pool_alloc(0x5C, 0);
    func_80068A50(temp_v0, arg0);
    Fragment_Load((((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10, fragment11_ROM_START, fragment12_ROM_START);
    Fragment_Load((((u32)D_81800000 & 0x0FF00000) >> 20) - 0x10, fragment4_ROM_START, fragment5_ROM_START);
    Fragment_Load((((u32)D_81700000 & 0x0FF00000) >> 20) - 0x10, fragment18_ROM_START, fragment19_ROM_START);
    Fragment_LoadAndCall((((u32)D_83100000 & 0x0FF00000) >> 20) - 0x10, fragment6_ROM_START, fragment7_ROM_START, 0, temp_v0);
    var_v1 = 1;
    *(Copy9Layout *)arg0 = *(Copy9Layout *)((u8 *)temp_v0 + 4);
    if ((*(u8 *)((u8 *)temp_v0 + 0x58) & 1) != 0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    if (var_v1 != 0) {
        sp2C = var_v1;
        func_80068B78(temp_v0);
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/69650/func_80068E14.s")
#endif
