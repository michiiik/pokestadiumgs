#include "global.h"


#ifdef VERSION_US
void func_80009200(s32 ms) {
    u64 cycles = OS_USEC_TO_CYCLES(ms * 1000LL); // why not just do OS_NSEC_TO_CYCLES and not multiply by 1000LL?

    osSetTime(0);
    while (osGetTime() < cycles) {}
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_800092C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009384.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_8000948C.s")

extern void *memcpy(void *, const void *, s32); void *func_80009750(void *dest, const void *src, s32 size) { return (u8 *)memcpy(dest, src, size) + size; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009774.s")

extern char D_800A1B14[];
extern char D_800A1B20[];
void func_80009830(s32 x, s32 y, s32 regNum, void* addr) {
    u32 bits;
    s32 exponent;

    bits = *(u32*)addr;
    exponent = ((bits & 0x7f800000U) >> 0x17) - 0x7f;
    if ((exponent >= -0x7e && exponent <= 0x7f) || bits == 0) {
        func_80009774(x, y, D_800A1B14, regNum, *(f32*)addr);
    } else {
        func_80009774(x, y, D_800A1B20, regNum);
    }
}

extern char D_800A1B30[];
extern char D_800A1B3C[];
extern s32 D_80087DE8[];
void func_800098B4(u32 fpcsr) {
    s32 i;
    u32 bit = 1 << 17;
    func_80009774(30, 155, D_800A1B30, fpcsr);
    for (i = 0; i < 6; i++) {
        if (fpcsr & bit) {
            func_80009774(132, 155, D_800A1B3C, D_80087DE8[i]);
            break;
        }
        bit >>= 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009940.s")

OSThread* func_80009D98(void) {
    OSThread* thread = __osGetActiveQueue();

    while (thread->priority != -1) {
        if (thread->priority > 0 && thread->priority < 0x7F && (thread->flags & 3)) {
            return thread;
        }

        thread = thread->tlnext;
    }

    return NULL;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009E04.s")

extern u8 D_800D05B0[];
void func_80009EB4(s32 arg0, s32 arg1, s32 arg2) {
    s32 *arg1p = &arg1;
    s32 *arg2p = &arg2;
    *(s32 *)(D_800D05B0 + 0x9CC) = arg0 | 0xA0000000;
    *(s16 *)(D_800D05B0 + 0x9D0) = *arg1p;
    *(s16 *)(D_800D05B0 + 0x9D2) = *arg2p;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/crash_screen_init.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009F80.s")
#endif
