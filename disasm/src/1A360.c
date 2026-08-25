#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_80019760.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_80019C08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_80019CC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_80019D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_80019DE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001A2CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001A308.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001A3DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001A4C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001A5B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001A6F8.s")

extern void func_8001A6F8(void *arg0, s32 arg1);
void func_8001A994(void *arg0) {
    func_8001A6F8(arg0, 6);
}

void func_8001A9B4(void *arg0) {
    func_8001A6F8(arg0, 7);
}

void func_8001A9D4(u32 *arg0) {
    arg0[0] = (u32)arg0;
    arg0[1] = (u32)arg0;
    arg0[2] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001A9E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001AA34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001AAD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001AC38.s")

void func_8001AD74(s32 *arg0, s32 *arg1) {
    if ((*(s32 **)((u8 *)(arg1) + (0))) == NULL) {
        (*(s32 **)((u8 *)(arg1) + (0))) = arg0;
        (*(s32 **)((u8 *)(arg1) + (4))) = (s32 *) (*(s32 **)((u8 *)(arg0) + (4)));
        *(*(s32 **)((u8 *)(arg0) + (4))) = arg1;
        (*(s32 **)((u8 *)(arg0) + (4))) = arg1;
        (*(s32 *)((u8 *)(arg0) + (8))) = (s32) ((*(s32 *)((u8 *)(arg0) + (8))) + 1);
        (*(s32 *)((u8 *)(arg1) + (0xC))) = (s32) (*(s32 *)((u8 *)(arg0) + (0xC)));
    }
}

void func_8001ADB4(void *arg0) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0)));
    if (temp_v0 != NULL) {
        (*(void ***)((u8 *)(temp_v0) + (4))) = (void **) (*(void ***)((u8 *)(arg0) + (4)));
        *(*(void ***)((u8 *)(arg0) + (4))) = (*(void **)((u8 *)(arg0) + (0)));
        (*(void **)((u8 *)(arg0) + (0))) = NULL;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001ADE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001AE60.s")

void func_8001AFAC(void *arg0, s32 arg1) {
    func_8001A9B4((*(void **)((u8 *)(arg0) + (0x44))));
    (*(s32 *)((u8 *)(arg0) + (0x48))) = arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001AFE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001B00C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001B058.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001B0B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001B1A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001B218.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001B59C.s")
#endif
