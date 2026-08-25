#include "global.h"


#ifdef VERSION_US
typedef struct {
    u32 segments[2];
    u32 textures[1];
} DisplayListAddresses26;

Gfx* func_810037E0(Gfx* gfx, DisplayListAddresses26* addresses, s32 index) {
    gSPDisplayList(gfx++, addresses->segments[0]);
    gDPSetTextureImage(gfx++, G_IM_FMT_I, G_IM_SIZ_16b, 1, addresses->textures[index]);
    gDPSetTile(gfx++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(gfx++);
    gDPLoadBlock(gfx++, 7, 0, 0, 0x3FF, 0x200);
    gDPPipeSync(gfx++);
    gDPSetTile(gfx++, G_IM_FMT_I, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPSetTileSize(gfx++, 0, 0, 0, 0x7C, 0xFC);
    gSPDisplayList(gfx++, addresses->segments[1]);
    gSPEndDisplayList(gfx++);
    return gfx;
}

typedef struct {
    unsigned char pad[0x14];
    u32* addresses;
    Gfx* gfx;
} Func810038BCState;
extern void* func_80006DEC();
extern Gfx* func_810037E0();
extern u16 D_80094904;

void func_810038BC(s32 arg0, Func810038BCState* state) {
    Gfx* gfx;
    u32* addresses;
    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = func_80006DEC(0x50);
        state->gfx = gfx;
        func_810037E0(gfx, addresses, D_80094904 & 7);
    }
}

void func_81003910(Gfx* gfx, u32* addresses) {
    gSPDisplayList(gfx++, *addresses);
    gSPDisplayList(gfx++, addresses[1]);
    gSPEndDisplayList(gfx++);
}

extern void func_81003910();

void func_81003948(s32 arg0, Func810038BCState* state) {
    Gfx* gfx;
    u32* addresses;
    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = func_80006DEC(0x18);
        state->gfx = gfx;
        func_81003910(gfx, addresses);
    }
}

extern u8* D_8009491C;

void func_81003990(Gfx* gfx, u32* addresses) {
    if (((u8*)D_8009491C)[0x1C] == 0) {
        gSPDisplayList(gfx++, addresses[0]);
    }
    gSPEndDisplayList(gfx++);
}

extern void func_81003990();

void func_810039CC(s32 arg0, Func810038BCState* state) {
    Gfx* gfx;
    u32* addresses;
    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = func_80006DEC(0x50);
        state->gfx = gfx;
        func_81003990(gfx, addresses);
    }
}
#endif
