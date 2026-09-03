#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/70/fragment70_code/func_8F200020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/70/fragment70_code/func_8F20015C.s")
#endif

#ifdef VERSION_US
extern s16 D_8F200870;
extern s32 D_8F200874;
extern s32 D_8F200904;
extern s32 D_8F200908;
extern s32 D_8F20090C;
extern s32 D_8F200910;

void func_8F200214(void) {
    D_8F200904 = 0;
    D_8F200908 = -1;
    D_8F20090C = 0;
    D_8F200910 = 1;
    D_8F200870 = 1;
    D_8F200874 = 1;
}
#endif

void func_8F200250(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/70/fragment70_code/func_8F200258.s")
#endif

#ifdef VERSION_US
extern void func_800088DC(void);
extern void GfxImage_FillCurrent(void *, u16);
extern void func_800503A4(u8 *);
extern void func_8F200258(void);
extern void func_80008648(void);
extern u8 D_800D0510[];
void func_8F200424(void) {
    u8 *value;
    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 0x5295);
    value = (u8 *)D_8F20090C;
    if (value != NULL) {
        func_800503A4(value);
    }
    func_8F200250();
    if (D_8F200874 != 0) {
        func_8F200258();
    }
    func_80008648();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/70/fragment70_code/func_8F200494.s")
#endif

#ifdef VERSION_US
extern s32 StageContext_GetFadeMode();
extern void StageFade_StartFromTransparent();
extern s32 func_8F200494();
s32 func_8F200588(s32 arg0) {
    s32 result = arg0;
    s32 temp_v0;

    switch (arg0) {
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            result = 1;
        }
        break;
    case 1:
        temp_v0 = func_8F200494();
        if (temp_v0 != 0) {
            if (temp_v0 == 1) {
                result = 2;
                StageFade_StartFromTransparent(5);
            } else if (temp_v0 == 2) {
                result = 3;
            }
        }
        break;
    case 2:
        if (StageContext_GetFadeMode() == 1) {
            result = 4;
        }
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/70/fragment70_code/func_8F20063C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/70/fragment70_code/func_8F2007B4.s")
#endif
