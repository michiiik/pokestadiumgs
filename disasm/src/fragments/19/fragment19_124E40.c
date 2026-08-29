#include "global.h"


#ifdef VERSION_US
typedef struct { s16 x; s16 y; } Vec2s; void func_82303D60(Vec2s *arg0, Vec2s *arg1, Vec2s *arg2) { arg0->x = arg1->x + arg2->x; arg0->y = arg1->y + arg2->y; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82303D84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82303E14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82304260.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_823043D8.s")

extern s32 func_82301428(void);
extern void Vec3f_SetComponentsDuplicate(void *, f32, f32, f32);
extern f32 D_82305D6C;
extern Vec2s D_82306AF0;
extern Vec2s D_82306AF4;
extern u8 D_82306DD4[];
extern void func_82303D60(Vec2s *arg0, Vec2s *arg1, Vec2s *arg2);
s32 func_82304520(s32 arg0, s32 arg1) {
    u8 padding[0x14];
    Vec2s sp20;
    s32 temp_v0;

    temp_v0 = func_82301428();
    if ((arg0 != 0) && (arg0 == 2) && (*(s16 *)(D_82306DD4 + (temp_v0 * 0x2F0)) != 0)) {
        func_82303D60(&sp20, &D_82306AF0, &D_82306AF4);
        Vec3f_SetComponentsDuplicate((void *)(arg1 + 0x24),
                                      (f32)sp20.x - 320.0f,
                                      240.0f - (f32)sp20.y,
                                      -579.0f);
        Vec3f_SetComponentsDuplicate((void *)(arg1 + 0x30), D_82305D6C, D_82305D6C, D_82305D6C);
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82304608.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_823049A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82304C88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82304F5C.s")

extern void func_8003CD84(void);
extern s32 func_82303D84(u16);
extern void func_82304F5C(s32, s32, void *, void *, void *, s32);
extern u8 D_82305BD0[];
extern u8 D_82305C08[];
extern u8 *D_82306AE8;
extern u16 D_82306AEC;
extern s16 D_82306AFC;
s32 func_823052FC(s32 arg0, s32 arg1) {
    u8 *var_a3;
    s32 temp_v1;
    u16 *coords;

    if ((arg0 != 0) && (arg0 == 5)) {
        temp_v1 = func_82303D84(D_82306AEC);
        if (D_82306AFC == 1) {
            var_a3 = D_82305BD0;
        } else {
            var_a3 = D_82305C08;
        }
        coords = (u16 *)D_82306AE8;
        func_82304F5C(-((s32)coords[0] / 2), (s32)coords[1] / 2, coords, var_a3, var_a3 + 3, temp_v1);
        func_8003CD84();
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_823053A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_823055DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_8230570C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_8230583C.s")

extern void func_823055DC(u8 *);
extern void func_8230570C(u8 *);
extern void func_8230583C(u8 *);
extern u8 D_82306AF8[];
void func_82305914(void) {
    switch ((*(s16 *)((u8 *)(D_82306AF8) + (2)))) {      /* irregular */
    case 1:
        func_823055DC(D_82306AF8);
        return;
    case 3:
        func_8230570C(D_82306AF8);
        return;
    case 4:
        func_8230583C(D_82306AF8);
        /* fallthrough */
    case 0:
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82305988.s")

void func_823059D4(void) {
    *(s16 *)(D_82306AF8 + 2) = 1;
    *(s16 *)(D_82306AF8 + 6) = -1;
}

void func_823059F0(void) {
    *(s16 *)(D_82306AF8 + 2) = 3;
    *(s16 *)(D_82306AF8 + 6) = -1;
}

void func_82305A0C(void) {
    *(s16 *)(D_82306AF8 + 2) = 4;
    *(s16 *)(D_82306AF8 + 6) = -1;
}

extern s16 D_82306AFA;
s32 func_82305A28(void) {
    s32 result = 0;
    if (D_82306AFA == 2) result = 1;
    return result;
}

s32 func_82305A4C(void) {
    s32 result = 0;
    if (D_82306AFA == 0) result = 1;
    return result;
}
#endif
