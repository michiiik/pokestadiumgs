#include "global.h"


#ifdef VERSION_US
s32 func_8AF1E2F0(u8 arg0, u8 arg1) {
    s32 nibble = arg1 & 0xF;
    if ((nibble == (arg0 & 0xF)) || (nibble == ((arg0 & 0xF0) >> 4))) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20C560/func_8AF1E32C.s")
#endif

#ifdef VERSION_US
typedef struct Snapshot_8AF1E45C {
    u32 words[0x52C / 4];
} Snapshot_8AF1E45C;
extern Snapshot_8AF1E45C D_8AF38208;
extern Snapshot_8AF1E45C *D_8AF27940;
extern s16 D_8AF38206;
extern s16 D_8AF3779C;
void func_8AF1E45C(void) {
    *D_8AF27940 = D_8AF38208;
    D_8AF3779C = D_8AF38206;
}
#endif

void func_8AF1E4B0(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20C560/func_8AF1E4B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20C560/func_8AF1E54C.s")
#endif

#ifdef VERSION_US
extern void *D_8AF263C0;
extern s16 D_8AF27954;
extern u16 D_8AF2BDC6;
extern s32 D_8AF38828;
extern s32 D_8AF38738;
extern s32 D_8AF387B0;
extern s32 func_8AF0326C(void *);
extern void func_8AF00130(s32);
extern void func_8AC0686C(void *, s16);
extern void func_8AC0619C(s32 *, u16);
extern void func_8AC06220(s32 *, u16);
s16 func_8AF1E840(void) {
    s16 result = 0x19;
    u8 *state = (u8 *)D_8AF27940;

    if (func_8AF0326C(state) == 0) {
        if (*(u16 *)((u8 *)D_8AF263C0 + 8) & 0x4000) {
            func_8AF00130(3);
            result = 0x17;
            D_8AF27954 = 0;
        }
    }
    func_8AC0686C(&D_8AF38828, *(s16 *)(state + 0x38));
    func_8AC0619C(&D_8AF38738, D_8AF2BDC6);
    func_8AC06220(&D_8AF387B0, D_8AF2BDC6);
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20C560/func_8AF1E8E4.s")
#endif
