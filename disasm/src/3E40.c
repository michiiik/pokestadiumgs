#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/func_80003240.s")


void func_80003308(u32 *dst, const u32 *src, s32 wordCount) {
    while (wordCount-- > 0) {
        *dst++ = *src++;
    }
}

extern void func_80002680(void *, s32);
extern void func_80003CD0(void);
extern void *func_80002E00(s32, s32);
extern u32 D_800871F0;
extern u32 D_800871F4;
extern u8 D_80134470[];
extern void *D_800CCDF0;
void Util_InitMainPools(void) {
    s32 size = osGetMemSize();
    D_800871F0 = size - 0x400000;
    D_800871F4 = size;
    func_80002680(D_80134470, size | 0x80000000);
    func_80003CD0();
    D_800CCDF0 = func_80002E00(0x10000, 0);
}

extern u32 D_800871F4; u32 func_8000339C(void) { return D_800871F4; }

extern u32 D_800871F0; u32 func_800033A8(void) { return D_800871F0; }


extern void * D_800CCDF0;
extern void func_80002EB8(void *, s32);
void func_800033B4(s32 arg0) {
    func_80002EB8(D_800CCDF0, arg0);
}


extern void func_80002F90(void *, s32);
void func_800033DC(s32 arg0) {
    func_80002F90(D_800CCDF0, arg0);
}

void func_80003404(Gfx** dlist, s32 ulx, s32 lrx, u16 color) {
    s32 uly = 15;
    s32 lry = 17;
    Gfx* gfx = *dlist;

    if (func_80008990() != 0) {
        ulx <<= 1;
        lrx <<= 1;
        uly <<= 1;
        lry <<= 1;
    }

    gDPPipeSync(gfx++);
    gDPSetFillColor(gfx++, color << 16 | color);
    gDPFillRectangle(gfx++, ulx, uly, lrx, lry);
    *dlist = gfx;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/func_800034E4.s")

void func_8000377C(u64 *dest, u32 size) {
    while (size-- > 0) {
        *(dest++) = -1;
    }
}

s32 func_800037B8(u64 *ptr) {
    s32 ret = 0;
    while (*(ptr++) == 0x8040000080400000ULL) {
        ret++;
    }
    return ret * sizeof(*ptr);
}
#endif
