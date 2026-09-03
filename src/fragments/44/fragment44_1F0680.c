#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02410.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02584.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02684.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02750.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF0282C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF0299C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02A34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02AE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02B88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02C28.s")

extern void func_8AF02C28(s32, s32, void *, s32);
extern s32 D_8AF2BE10;
void func_8AF02DA4(s32 arg0, s32 arg1) {
    func_8AF02C28(arg0, arg1, &D_8AF2BE10, 0x4943414C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02DD0.s")

extern Gfx *D_800D0510;
extern u8 D_80094E00[];
extern u8 D_80094F50[];
extern void func_8AF02DD0(void *);
void func_8AF02F18(void *arg0) {
    s32 i;
    u8 *ptr;
    u8 *count_base;

    gSPDisplayList(D_800D0510++, D_80094E00);
    count_base = (u8 *)arg0 + 0x44;
    if (*(s16 *)(count_base + 0x2C) > 0) {
        ptr = (u8 *)arg0 + 0x74;
        i = 0;
        do {
            func_8AF02DD0(ptr);
            i++;
            ptr += 0x10;
        } while (i < *(s16 *)(count_base + 0x2C));
    }
    gSPDisplayList(D_800D0510++, D_80094F50);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02FC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF0304C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF03104.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF03198.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF0326C.s")
#endif
