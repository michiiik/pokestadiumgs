#include "global.h"


#ifdef VERSION_US
// 0x34-stride entry tables shared with the matched sibling func_8AF079FC
// (unk_04 is the entry payload read via table[-1] after the materialized
// decrement; the three tables are the switch's arg0 selections).
struct unk_D_8AF27E30 {
    u8 pad00[0x4];
    s32 unk_04;
    u8 pad08[0xC];
    s32 unk_14;
    u8 pad18[0x1C];
};
extern struct unk_D_8AF27E30 D_8AF27E30[];
extern struct unk_D_8AF27E30 D_8AF28274[];
extern struct unk_D_8AF27E30 D_8AF284E4[];
extern s32 D_8AF2656C;
extern s32 D_8AF26564;
extern s32 D_8AF26568;

/* mkdraft:func_8AF07960 begin */
void func_8AF07960(s16 arg0, s16 arg1) {
    struct unk_D_8AF27E30 *sp4;
    struct unk_D_8AF27E30 *table;

    switch (arg0) {
    default:
        table = sp4;
        break;
    case 0:
        table = D_8AF27E30;
        break;
    case 1:
        table = D_8AF28274;
        break;
    case 2:
        table = D_8AF284E4;
        break;
    }
    table += arg1;
    D_8AF26568 = table[-1].unk_04;
    table--;
    D_8AF2656C = table->unk_14;
    D_8AF26564 = 0;
}
/* mkdraft:func_8AF07960 end */

/* 0x44-byte entries; D_8AF27BCC and D_8AF27D20 continue the same array
 * (offsets 7*0x44 and 12*0x44 past D_8AF279F0). See func_8AF220E8, which
 * selects the same three tables and records their entry counts (7/5/4).
 * //@src/fragments/44/fragment44_20F140.c */
struct unk_D_8AF279F0 {
    u8 pad00[0x10];
    s32 unk_10;
    s32 unk_14;
    u8 pad1C[0x2C];
};
extern struct unk_D_8AF279F0 D_8AF279F0[];
extern struct unk_D_8AF279F0 D_8AF27BCC[];
extern struct unk_D_8AF279F0 D_8AF27D20[];
extern s32 D_8AF26564;
extern s32 D_8AF26568;
extern s32 D_8AF2656C;

void func_8AF079FC(s16 arg0, s16 arg1) {
    /* Never assigned on any path: when arg0 matches no case below, the switch
     * copies this uninitialized stack slot (the lw from 4(sp)). */
    struct unk_D_8AF279F0 *sp4;
    struct unk_D_8AF279F0 *table;

    switch (arg0) {
    default:
        table = sp4;
        break;
    case 0:
        table = D_8AF279F0;
        break;
    case 1:
        table = D_8AF27BCC;
        break;
    case 2:
        table = D_8AF27D20;
        break;
    }
    table += arg1;
    D_8AF26568 = table->unk_10;
    D_8AF2656C = table->unk_14;
    D_8AF26564 = 1;
}
extern s32 D_8AF26564;
extern s32 D_8AF26568;
extern s32 D_8AF2656C;
void func_8AF07A90(void) {
    D_8AF26568 = 0;
    D_8AF2656C = 0;
    D_8AF26564 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5BD0/func_8AF07AAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5BD0/func_8AF07BC0.s")

extern void *D_8AF26560;
extern void func_8AF06EA4(void *);
void func_8AF07C84(void) {
    func_8AF06EA4(D_8AF26560);
}
#endif
