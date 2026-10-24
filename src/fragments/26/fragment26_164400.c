#include "global.h"


#ifdef VERSION_US
extern u8 *D_8009491C;
extern u16 D_80094904;
extern Gfx D_810061B0[];
// Configures two wrapping RGBA16 tiles with offsets derived from the frame counter.
// The source shape follows Stadium 1's func_81002530 (particle_data_library_2577F0.c).
// Tile 1 retains the retail horizontal start/end coordinates, which are equal.
void DisplayList_BuildScrollingDualTexture(Gfx *gfx, u32 *textures) {
    s32 phase;
    s16 u;
    s16 v;
    s16 second_v;
    if (D_8009491C[0x1C] == 0) {
        phase = (s16)(-D_80094904 * 16);
        u = phase >> 4;
        v = 0x4000 - (phase >> 4);
        second_v = 0x4000 - ((phase >> 3) & 0xFFFF);
        gSPDisplayList(gfx++, D_810061B0);
        gDPLoadTextureTile(gfx++, textures[0], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, 31, 31, 0,
            G_TX_WRAP, G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, 0, u, v, u + 31, v + 31);
        gDPLoadMultiTile(gfx++, textures[1], 256, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, 31, 31, 0,
            G_TX_WRAP, G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, 1, v, second_v, v, second_v + 31);
    }
    gSPEndDisplayList(gfx++);
}

typedef struct {
    unsigned char pad[0x14];
    u32 *addresses;
    Gfx *gfx;
} ScrollingDualTextureState26;
extern u32 Gfx_AllocDisplayList(s32);

void DisplayList_InitScrollingDualTexture(s32 phase, ScrollingDualTextureState26 *state) {
    Gfx *gfx;
    u32 *addresses;
    if (phase == 2) {
        addresses = state->addresses;
        gfx = (Gfx *)Gfx_AllocDisplayList(240);
        state->gfx = gfx;
        DisplayList_BuildScrollingDualTexture(gfx, addresses);
    }
}
#endif
