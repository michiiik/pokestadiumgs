#include "global.h"


#ifdef VERSION_US
// Texture record read by func_81005E00: a scroll multiplier and eight RGBA16 64x32 frames.
typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ u32 unk_04[8];
} unk_func_81005E00;
extern u8 *D_8009491C;
extern u16 D_80094904;
// Loads frame (D_80094904 & 7) of arg1 as a 64x32 RGBA16 texture with an s-scroll of
// 0x4000 - unk_00 * D_80094904, unless byte 0x1C of D_8009491C is set; always ends the list.
// Same body as Pokemon Stadium 1 LoadTextureBlockWithTileSize
// (src/fragments/particle_data_library/particle_data_library_257AF0.c there), which reads
// its counter as s16; here the load is lhu, so D_80094904 is u16.
void func_81005E00(Gfx *gfx, u32 *arg1) {
    s32 var_a5;
    unk_func_81005E00 *ptr;
    s32 var_a4;
    s32 var_a3;
    s16 temp_v0;

    var_a4 = 1; // FAKE
    if (D_8009491C[0x1C] == 0) {
        ptr = (unk_func_81005E00 *)arg1;
        var_a3 = D_80094904;
        temp_v0 = 0x4000 - (ptr->unk_00 * var_a3);
        // FAKE: the var_a4/var_a3/var_a5 shuffles (and the dead var_a4 = 1 above) select the
        // target's register assignment; constants in place of them do not match.
        var_a4 = var_a3;
        var_a3 = 32;
        gDPLoadTextureBlock(gfx++, ptr->unk_04[var_a4 & 0x7], G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, var_a3, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
        var_a5 = 0;
        gDPSetTileSize(gfx++, var_a5, temp_v0, var_a5, ((temp_v0 + 63) << 2), 124);
    }
    gSPEndDisplayList(gfx++);
}

typedef struct Func81005F38State {
    unsigned char pad[0x14];
    u32 *addresses;
    Gfx *gfx;
} Func81005F38State;

extern Gfx *Gfx_AllocDisplayList(s32);
extern void func_81005E00(Gfx *, u32 *);

void func_81005F38(s32 arg0, Func81005F38State *state) {
    Gfx *gfx;
    u32 *addresses;

    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = Gfx_AllocDisplayList(0x50);
        state->gfx = gfx;
        func_81005E00(gfx, addresses);
    }
}

extern void *D_80094BB0;

s32 func_81005F80(s32 arg0, void *arg1) {
    if (arg0 == 0) {
        if (D_80094BB0 == NULL) {
            D_80094BB0 = arg1;
        }
    }
    return 0;
}
#endif
