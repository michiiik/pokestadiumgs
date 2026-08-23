#include "global.h"


#ifdef VERSION_US
extern s32 func_800356CC(s32 index);
extern void *BinArchive_Open(u32 source, u32 destination, s32 mode,
                             s32 flags);
extern void *func_80004B4C(void *archive, s32 index);
extern void func_800049B8(void *archive);
#define D_80097120 (*(s32 *)0x80097120)
#define D_80097124 (*(void **)0x80097124)
#define D_80097128 (*(void **)0x80097128)

void func_8004C020(void) {
    void *archive = BinArchive_Open((u32)func_800356CC(2), 0, 2, 1);

    D_80097124 = func_80004B4C(archive, 0x41);
    D_80097128 = func_80004B4C(archive, 0);
    func_800049B8(archive);
}

void func_8004C088(void *arg0, void *arg1) {
    (void)arg0;
    (void)arg1;
    D_80097120 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C09C.s")

void func_8004C398(void) {
    D_80097120 = 0;
}

void func_8004C3A4(void *arg, s32 *value) {
    (void)arg;
    *value = 0;
}

void *func_8004C3B0(void *table, s32 index) {
    u32 count;
    void *entry;

    if (table == NULL || index < 0) {
        return NULL;
    }

    count = *(u32 *)((u8 *)table + 0xC);
    if ((u32)index >= count) {
        return NULL;
    }

    entry = (u8 *)table + ((u32)index << 4) + 0x10;
    if (entry == NULL) {
        return NULL;
    }

    return *(void **)((u8 *)entry + 0x8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C3EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C468.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C4A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C4B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C504.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C54C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C594.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C5E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C7A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C874.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C8A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C8C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C948.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C990.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CA10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CA24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CA38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CA4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CA60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CA74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CB28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CB7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D150.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D19C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D1C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D1FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D27C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D314.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D334.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D40C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D418.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D43C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D488.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D5B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D690.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D6D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D720.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/PokeIcon_AdjustImageColors.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D878.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D998.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DA18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DA8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DAF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DB5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DC6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DCB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DCFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DD1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DD64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DDAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DDF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DE3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DE84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DEF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/WidgetTree_RunMessagePanelSilent.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DF38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DFEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004E018.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004E0F0.s")
#endif
