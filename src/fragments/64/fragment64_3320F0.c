#include "global.h"


#ifdef VERSION_US
extern s32 func_8002806C(void);
extern void func_800225C4(s32);
typedef struct {
    u8 pad_0000[0x2184]; s32 unk_2184; u8 pad_2188[0x1E]; u16 unk_21A6;
    u8 pad_21A8[0x16]; u16 unk_21BE; u8 pad_21C0[0x16]; u16 unk_21D6;
    u8 pad_21D8[0x16]; u16 unk_21EE;
} State_87F0F480;
s32 func_87F0F480(State_87F0F480 *arg0) {
    s32 result; s32 count;
    result = func_8002806C();
    if (arg0->unk_2184 == 2) {
        count = ((((u32)arg0->unk_21EE >> 15) != 0)
              + (((u32)arg0->unk_21A6 >> 15) != 0)
              + (((u32)arg0->unk_21BE >> 15) != 0)
              + (((u32)arg0->unk_21D6 >> 15) != 0));
        if (count == 1) func_800225C4(0x28);
    } else if (result != 0x48) {
        func_800225C4(0x28);
    }
    return result;
}
#endif
