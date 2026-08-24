#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84168540.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84168680.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84168B00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84168C18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84168CA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169040.s")

typedef struct {
    u8 pad[0x88];
    Vtx *vertices;
} Func84169214State;
Gfx *func_84169214(Gfx *arg0, Func84169214State *arg1) {
    s32 i;
    Vtx *temp_v0 = arg1->vertices;
    for (i = 0; i < 19; i++) {
        gSPVertex(arg0++, temp_v0, 4, 0);
        gSP2Triangles(arg0++, 0, 2, 1, 0, 1, 2, 3, 0);
        temp_v0 += 2;
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169344.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169618.s")

extern u8 *D_84187E40;
void func_84169B80(void) {
    u8 *ptr = *(u8 **)&D_84187E40;
    s32 i = 0;
    while (i != 2) {
        i += 1;
        *(u16 *)ptr = 0;
        ptr += 0x1E4;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169BA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169C74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169DBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169F18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_8416A050.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_8416A140.s")

void *func_8416A150(void *arg0) { return arg0; }
#endif
