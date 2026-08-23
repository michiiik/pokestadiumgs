#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/Game_PollState.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064C88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064C94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064CB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064CC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064CD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064CDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/Fragment_LoadAndCall.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064D28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/Game_ShutdownAndLoadFragment.s")
#endif

void func_80064DF4(void) {
}

extern s32 D_8009DE94;
extern s32 D_80128BE4;

s32 Game_SetState(s32 state) {
    s32 previous = D_8009DE94;

    if (state != previous) {
        D_80128BE4 = previous;
        D_8009DE94 = state;
        return 1;
    }

    return 0;
}

s32 Game_GetState(void) {
    return D_8009DE94;
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064E38.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/Game_State11_Options.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/Game_ThreadInit.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064F54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/Game_Thread.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80065210.s")
#endif
