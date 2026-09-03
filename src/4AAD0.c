#include "global.h"


void func_80049ED0(void) {
}

#ifdef VERSION_US
extern s32 D_801270A8; extern s32 D_801270AC; void Input_SetRepeatController(s32 value) { D_801270A8 = 10; D_801270AC = value; }
#endif

#ifdef VERSION_US
s32 Input_GetRepeatedDPad(void) {
    u8 *state=(u8 *)(u32)D_801270AC; u32 flags;
    flags=*(u16 *)(state+8);
    if(flags&0x800){D_801270A8=10;return 0x800;}if(flags&0x400){D_801270A8=10;return 0x400;}if(flags&0x200){D_801270A8=10;return 0x200;}if(flags&0x100){D_801270A8=10;return 0x100;}
    D_801270A8 -= 1;
    if (D_801270A8 <= 0) {
      D_801270A8=0; flags=*(u16 *)(state+6);
      if(flags&0x800){D_801270A8=2;return 0x800;}if(flags&0x400){D_801270A8=2;return 0x400;}if(flags&0x200){D_801270A8=2;return 0x200;}if(flags&0x100){D_801270A8=2;return 0x100;}
    }
    return 0;
}
#endif
