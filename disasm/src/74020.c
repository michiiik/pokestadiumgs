#include "global.h"


#ifdef VERSION_US
u8 func_80073420(u8 arg0) { extern u8 D_8009F87F[]; if (arg0 > 0 && arg0 < 0xFE) return D_8009F87F[arg0]; return 0; }

u8 func_80073450(u8 arg0) { extern u8 D_8009F97F[]; if (arg0 > 0 && arg0 < 0xFE) return D_8009F97F[arg0]; return 0; }

extern u8 D_8009F87F[]; extern u8 D_8009F880[];
u8 func_80073480(u8 arg0) {
    s32 index = arg0;
    if (arg0 > 0) {
        if (index < 0x32) return D_8009F87F[index];
        if (arg0 < 0xFC) return D_8009F880[arg0];
    }
    return 0;
}

extern u8 D_8009FF6B[];
extern u8 D_8009F97F[];
extern u8 D_8009F87F[];
extern u8 D_8009F880[];
u8 func_800734CC(u8 arg0) {
    s32 index = arg0;
    u8 result = 0;
    if ((arg0 > 0) && (arg0 < 0xFC)) {
        result = D_8009F97F[index];
        if (result >= 0x33) result--;
    }
    return result;
}

u8 func_80073510(u8 arg0) { extern u8 D_8009FA7F[]; if (arg0 > 0 && arg0 < 0xFC) return D_8009FA7F[arg0]; return 0; }

u8 func_80073540(u8 arg0) { extern u8 D_8009FB7B[]; if (arg0 > 0 && arg0 < 0xFC) return D_8009FB7B[arg0]; return 0; }

u8 func_80073570(u8 arg0) { extern u8 D_8009FC77[]; if (arg0 > 0 && arg0 < 0xFB) return D_8009FC77[arg0]; return 0; }

u8 func_800735A0(u8 arg0) { extern u8 D_8009FD73[]; if (arg0 > 0 && arg0 < 0xFB) return D_8009FD73[arg0]; return 0; }

u8 func_800735D0(u8 arg0) { extern u8 D_8009FE6F[]; if (arg0 > 0 && arg0 < 0xFB) return D_8009FE6F[arg0]; return 0; }

u8 func_80073600(u8 arg0) {
    if (arg0 > 0 && arg0 < 0xFB) return D_8009FF6B[arg0];
    return 0;
}
void func_80073600_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/74020/func_80073638.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/74020/func_80073828.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/74020/func_800739EC.s")
#endif
