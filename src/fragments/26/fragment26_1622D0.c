#include "global.h"


#ifdef VERSION_US
extern u8 *D_8009491C;
void DisplayList_BuildOptionalPlusSegment(Gfx *gfx, u32 *addresses) {
    if (((u8 *)D_8009491C)[0x1C] == 0) {
        gSPDisplayList(gfx++, addresses[0]);
    }
    gSPDisplayList(gfx++, addresses[1]);
    gSPEndDisplayList(gfx++);
}

typedef struct {
    unsigned char pad[0x14];
    u32 *addresses;
    Gfx *gfx;
} Func81003A74State;
extern Gfx *Gfx_AllocDisplayList();
void func_81003A74(s32 arg0, Func81003A74State *state) {
    Gfx *gfx;
    u32 *addresses;
    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = Gfx_AllocDisplayList(0x50);
        state->gfx = gfx;
        DisplayList_BuildOptionalPlusSegment(gfx, addresses);
    }
}
#endif
