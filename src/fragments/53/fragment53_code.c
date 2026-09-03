#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86500020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86500354.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86500780.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86500D5C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86500EF8.s")
#endif

#ifdef VERSION_US
extern s32 D_8650C4DC;
extern s32 D_8650D9D4;
s32 func_8650123C(s32 arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = (D_8650D9D4 + D_8650C4DC) - arg0;
    if (D_8650D9D4 >= arg0) {
        var_v1 = -0xA;
    }
    if (arg0 >= (D_8650D9D4 + 0xA)) {
        var_v1 = -0xA;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86501280.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86501D6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86501EA0.s")
#endif

void func_86501F98(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86501FA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_865020D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86502524.s")
#endif

#ifdef VERSION_US
extern f32 D_8650C4B8;
extern f32 D_8650C508;
extern s32 D_8650C634;
extern s32 D_8650D0A4;
extern f64 D_8650D6B8;
extern f64 D_8650D6C0;
extern f64 D_8650D6C8;
extern f64 D_8650D6D0;
void func_86502620(void) {
    if (D_8650C634 == 0) {
        D_8650D0A4 = 2;
    } else {
        D_8650D0A4 = D_8650C634;
    }
    switch (D_8650D0A4) {                           /* irregular */
    case 1:
        D_8650C4B8 = (f32) ((f64) D_8650C508 * D_8650D6B8);
        return;
    case 2:
        D_8650C4B8 = (f32) ((f64) D_8650C508 * D_8650D6C0);
        return;
    case 3:
        D_8650C4B8 = (f32) ((f64) D_8650C508 * D_8650D6C8);
        return;
    case 4:
        D_8650C4B8 = (f32) ((f64) D_8650C508 * D_8650D6D0);
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86502720.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86502958.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86502B88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86502D80.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86503178.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_865038A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86503938.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86503B98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_865040E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_8650455C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_865046A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86504740.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86504EB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_8650515C.s")
#endif

#ifdef VERSION_US
extern void GeoCamera_SetPerspective(void *, f32, f32, f32);
extern void func_80038E14(s32, s32, f32, s32, f32, f32, f32, s32);
extern f32 D_8650C47C;
extern f32 D_8650D1E0;
s32 func_86505858(s32 arg0, s32 arg1) {
    extern s32 D_8650C5E0;
    GeoCamera_SetPerspective((void *)(u32)arg1, D_8650D1E0, 100.0f, 12800.0f);
    func_80038E14(arg1,
        *(s32 *)((u8 *)(&D_8650C5E0) + 0x24),
        D_8650C47C,
        *(s32 *)((u8 *)(&D_8650C5E0) + 0x2C),
        0.0f, D_8650C47C, 0.0f, 0);
    return 0;
}
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_865058CC(s32 arg0, void *arg1) {
    s16 pad;
    s32 sp28;
    s16 sp26;
    s16 sp24;
    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &sp28, &sp26, &sp24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(sp26 + 0x2000);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(sp24 - 0x2000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_86505934(s32 arg0, void *arg1) {
    s16 pad;
    s32 sp28;
    s16 sp26;
    s16 sp24;
    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &sp28, &sp26, &sp24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(-0x2000 - sp26);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(sp24 + 0x6000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_865059A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86505EA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_865064B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86506B2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86506E78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86507AFC.s")
#endif

#ifdef VERSION_US
s32 func_87F00930();
extern void func_87F01D44();

void func_86508294(void) {
    if (func_87F00930() == 1) {
        func_87F01D44();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_865082C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86508484.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_8650863C.s")
#endif

void func_86508778(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86508780.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86508890.s")
#endif

#ifdef VERSION_US
extern s32 StageFade_StartFromTransparent(s32);
extern s32 func_800226C0(s32);
extern s32 func_86501280();
s32 func_87F08208(s32 *);
extern s32 D_8650C5E0;
extern s32 D_8650DAD8;
void func_86508A14(void) {
    s32 temp_v0;

    temp_v0 = func_87F08208(&D_8650DAD8);
    switch (temp_v0) {                              /* irregular */
    case 1:
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0x14);
        func_86501280();
        (*(s32 *)((u8 *)(&D_8650C5E0) + (0xC))) = 5;
        func_800225C4(0x28);
        func_800279C4(0xCF0B);
        return;
    case 2:
        (*(s32 *)((u8 *)(&D_8650C5E0) + (0xC))) = 2;
        (*(s32 *)((u8 *)(&D_8650C5E0) + (0x4C))) = 1;
        (*(s32 *)((u8 *)(&D_8650C5E0) + (0x58))) = 0;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        func_800226C0(3);
        return;
    }
}
#endif

#ifdef VERSION_US
extern s32 D_8650C5EC;
extern void *D_8650DB10;
void func_86508ABC(void) {
    if (StageContext_GetFadeMode() == 0) {
        if ((*(u8 *)((u8 *)(D_8650DB10) + (0x2180))) == 4) {
            StageFade_StartFromOpaque(0x14);
            func_87F00688();
            D_8650C5EC = 6;
            return;
        }
        D_8650C5EC = 4;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86508B20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86508C2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86509318.s")
#endif

#ifdef VERSION_US
s32 func_87F01A40();
extern s32 D_8650C494;
void func_86509480(void) {
    s32 temp_v0;

    D_8650C494 = 1;
    temp_v0 = func_87F01A40();
    switch (temp_v0) {                              /* irregular */
    case 0:
    case 2:
        D_8650C494 = 0;
        return;
    case 3:
        (*(s32 *)((u8 *)(&D_8650C5E0) + (0x58))) = 0;
        (*(s32 *)((u8 *)(&D_8650C5E0) + (0xC))) = 2;
        (*(s32 *)((u8 *)(&D_8650C5E0) + (0x4C))) = 3;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        return;
    case 4:
        (*(s32 *)((u8 *)(&D_8650C5E0) + (0x58))) = 1;
        (*(s32 *)((u8 *)(&D_8650C5E0) + (0xC))) = 2;
        (*(s32 *)((u8 *)(&D_8650C5E0) + (0x4C))) = 3;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_8650952C.s")
#endif

#ifdef VERSION_US
extern s32 func_87F02104(void);
void func_86509D8C(void) {
    s32 temp_v0;

    temp_v0 = func_87F02104();
    switch (temp_v0) {
    case 1:
        StageContext_SetClearColor(1);
        *(s32 *)((u8 *)&D_8650C5E0 + 0xC) = 0xC;
        *(s32 *)((u8 *)&D_8650C5E0 + 0x4C) = 2;
        StageFade_StartFromTransparent(0xA);
        *(s32 *)((u8 *)&D_8650C5E0 + 0x8) = 0;
        return;
    case 2:
        *(s32 *)((u8 *)&D_8650C5E0 + 0x58) = 0;
        *(s32 *)((u8 *)&D_8650C5E0 + 0xC) = 2;
        *(s32 *)((u8 *)&D_8650C5E0 + 0x4C) = 2;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        return;
    case 3:
        *(s32 *)((u8 *)&D_8650C5E0 + 0x58) = 1;
        *(s32 *)((u8 *)&D_8650C5E0 + 0xC) = 2;
        *(s32 *)((u8 *)&D_8650C5E0 + 0x4C) = 2;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86509E54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_8650A074.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_8650A278.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_8650A3E4.s")
#endif
