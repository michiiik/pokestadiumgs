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
extern s32 D_8650C498;
extern s32 D_8650C4B4;
extern f64 D_8650D678;
extern s32 D_8650C4AC;
extern f32 D_8650C4B8;
extern s32 D_8650C4CC;
extern s32 D_8650C4D4;
extern s32 D_8650D9D4;
void Fragment53_CountTrajectorySamplesInRange(void) {
    s32 i;
    f32 position;

    D_8650C4D4 = 0;
    D_8650C4B4 = D_8650C498 - D_8650C4CC - 10;
    for (i = 0; i < 100; i++) {
        position = (f32)((f64)D_8650C4AC - D_8650D678 * (f64)D_8650C4B8 * (f64)D_8650C4B8 * (f64)(D_8650D9D4 + i + 2) * (f64)(D_8650D9D4 + i + 2));
        if (!(position < (f32)D_8650C4B4) && !((f32)D_8650C498 < position)) {
            D_8650C4D4++;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_86501EA0.s")
#endif

void func_86501F98(void) {
}

#ifdef VERSION_US
extern s32 StageContext_GetFadeMode(void);
extern s32 StageFade_StartFromOpaque(s32);
extern void func_87F00688(void);
extern s32 D_8650C5EC;
extern f32 D_8650C4D8;
extern s32 D_8650C4DC;
extern s32 D_8650C620;
extern f64 D_8650D698;
extern void func_86501EA0(void);
void Fragment53_UpdateTrajectoryPosition(void) {
    if (D_8650C5EC == 10) {
        D_8650C4DC++;
        if (D_8650C4DC >= D_8650C4D4 - 2) {
            D_8650C4DC = 2;
        }
        if (D_8650C4DC < 2) {
            D_8650C4DC = 2;
        }
    } else {
        func_86501EA0();
    }
    D_8650C4D8 = (f32)(92.0 - ((f64)D_8650C4AC - D_8650D698 * (f64)D_8650C4B8 * (f64)D_8650C4B8 * (f64)(D_8650D9D4 + D_8650C4DC + 2) * (f64)(D_8650D9D4 + D_8650C4DC + 2)));
    D_8650C620 = (s32)(D_8650C4D8 / (f32)D_8650C4CC * 2000.0f + -1000.0f);
}
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
struct Fragment53ActorState {
    u8 prefix[0xC]; s32 animation; s32 pending;
    u8 middle[0x74]; s32 kind; u8 tail[0xC];
};
struct Fragment53Model { u8 opaque[0x168]; };
extern struct Fragment53ActorState D_86511698[];
extern struct Fragment53Model D_8650E120[];
extern void func_8003F210(void *, s32);
extern void ModelAnim_SetFrame(u8 *, s16);
void Fragment53_ApplyPendingPrimaryAnimation(s32 arg0) {
    if (D_86511698[arg0].pending == 1) {
        func_8003F210((u8 *)&D_8650E120[arg0], D_86511698[arg0].animation);
        ModelAnim_SetFrame((u8 *)&D_8650E120[arg0], 0);
        D_86511698[arg0].pending = 0;
    }
}
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
extern s32 D_8650C494;
extern s32 D_8650C5E8;
extern s32 D_8650C49C[];
extern f32 D_8650DBA8[];
extern f32 D_8650F7C8[];
extern void func_865040E4(s32);
void Fragment53_UpdateActorModelHeights(s32 arg0, void *arg1) {
    s32 index;
    s32 height;
    s32 offset;

    index = *(s32 *)((u8 *)arg1 + 0x14);
    if (arg0 == 0) { return; }
    if (arg0 == 2) {
        if (D_8650C5EC == 1) {
            if (D_8650C494 == 0) {
                *(s32 *)((u8 *)&D_86511698[index] + 0x58) += 1;
                if (*(s32 *)((u8 *)&D_86511698[index] + 0x58) >= 24) { *(s32 *)((u8 *)&D_86511698[index] + 0x58) = 0; }
                func_865040E4(index);
            }
            offset = index * 0x168;
            if (D_8650C5E8 == -2) {
                height = D_8650C49C[index];
                *(f32 *)((u8 *)D_8650DBA8 + offset) = (f32)(height - 5);
                *(f32 *)((u8 *)D_8650F7C8 + offset) = (f32)(height + 60);
            } else {
                *(f32 *)((u8 *)D_8650DBA8 + offset) = (f32)D_8650C49C[index];
                *(f32 *)((u8 *)D_8650F7C8 + offset) = (f32)D_8650C49C[index];
            }
        }
    }
}
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern Vtx D_8650C640[];
extern Gfx D_8650D430[];
extern void func_8003CD84();
s32 func_865046A8(s32 arg0, s32 arg1) {
    if (arg0 == 5) {
        gDPSetEnvColor(D_800D0510++, 255, 100, 100, 255);
        gSPVertex(D_800D0510++, D_8650C640, 4, 0);
        gSPDisplayList(D_800D0510++, D_8650D430);
        func_8003CD84();
    }
    return 0;
}
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
extern struct Fragment53Model D_8650E6C0[];
extern s32 D_8650DB28[];
extern u8 D_8650E6E4[];
extern u8 D_8650EC60[];
extern u8 D_8650DB80[];
extern u8 D_8650F7A0[];
extern u8 D_865118F8[];
extern void func_8003F114(void *, s32, s32, s32);
extern void ModelAnim_SetEventFrame(u8 *, s16);
extern void func_8003F3BC(void *, s32);
extern void func_87F06430(void *, s32);
extern void func_8003F1DC(void *);
extern s32 ModelAnim_SetSpeed(u8 *, s32);
extern void func_819006A0(void *);
extern void func_86502958(void);
void Fragment53_InitActorModels(void) {
    s32 index;

    for (index = 0; index < 4; index++) {
        func_8003F114((u8 *)&D_8650E6C0[index], 0, -1, D_8650DB28[index]);
        func_8003F210((u8 *)&D_8650E6C0[index], 0);
        ModelAnim_SetSpeed((u8 *)&D_8650E6C0[index], 0x20000);
        ModelAnim_SetFrame((u8 *)&D_8650E6C0[index], (s16)(guRandom() % 15 + 15));
        ModelAnim_SetEventFrame((u8 *)&D_8650E6C0[index], 0);
        func_8003F3BC((u8 *)&D_8650E6C0[index], 0);
        func_87F06430(D_8650E6E4 + index * 0x168, index);
        *(f32 *)((u8 *)&D_8650E6C0[index] + 0x38) = 0.095f;
        *(f32 *)((u8 *)&D_8650E6C0[index] + 0x34) = 0.095f;
        *(f32 *)((u8 *)&D_8650E6C0[index] + 0x30) = 0.095f;
        *(f32 *)((u8 *)&D_8650E6C0[index] + 0x28) = 55.0f;
        *(s16 *)((u8 *)&D_8650E6C0[index] + 0x1E) = 0;
        D_86511698[index].animation = 0;
        D_86511698[index].pending = 0;
        func_8003F1DC(D_8650EC60 + index * 0x168);
        func_8003F1DC((u8 *)&D_8650E120[index]);
        *(s16 *)((u8 *)&D_8650E6C0[index] + 0x20) = 0;
        func_8003F1DC(D_8650DB80 + index * 0x168);
        func_8003F1DC(D_8650F7A0 + index * 0x168);
    }
    func_819006A0(*(void **)D_865118F8);
    func_86502958();
}
#endif

#ifdef VERSION_US
extern s32 ModelAnim_IsFinished(void *);
extern void func_80027A28(u16, u8);
void Fragment53_UpdateTimedSecondaryAnimation(s32 arg0) {
    s32 index;
    u8 *model;

    index = arg0;
    switch (D_86511698[index].animation) {
    case 0:
        model = (u8 *)&D_8650E6C0[index];
        if ((*(s32 *)(model + 0x48) >> 16) >= 6) {
            func_8003F210(model, 2);
            ModelAnim_SetFrame(model, 0);
            ModelAnim_SetSpeed(model, 0x30000);
            D_86511698[index].animation = 2;
        }
        break;
    case 2:
        model = (u8 *)&D_8650E6C0[index];
        if (ModelAnim_IsFinished(model) == 1) {
            func_80027A28(0x1F04, (u8)index);
            func_8003F210(model, 1);
            ModelAnim_SetSpeed(model, 0x20000);
            D_86511698[index].animation = 1;
        }
        break;
    }
}
#endif

void func_86508778(void) {
}

#ifdef VERSION_US
void Fragment53_UpdateSecondaryAnimation(s32 arg0) {
    s32 index;

    index = arg0;
    switch (D_86511698[index].animation) {
    case 0:
        func_8003F210((u8 *)&D_8650E6C0[index], 2);
        ModelAnim_SetSpeed((u8 *)&D_8650E6C0[index], 0x30000);
        D_86511698[index].animation = 2;
        D_86511698[index].pending = 1;
        break;
    case 2:
        if (ModelAnim_IsFinished((u8 *)&D_8650E6C0[index]) == 1) {
            func_8003F210((u8 *)&D_8650E6C0[index], 1);
            D_86511698[index].pending = 0;
        }
        break;
    }
}
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
extern void func_800086A4(s32);
extern void func_80064D28(void);
extern void func_8650A074(void);
extern void func_865082C8(void);
extern s32 func_86509E54(s32);
void Fragment53_RunSceneTransition(void) {
    u8 *model;
    struct Fragment53ActorState *state;
    u8 *secondary;
    s32 *resource;
    s32 result;

    func_800086A4(2);
    if (*(u8 *)((u8 *)D_8650DB10 + 0x2180) == 4) {
        secondary = (u8 *)D_8650E6C0; model = (u8 *)D_8650E120;
        resource = D_8650DB28; state = D_86511698; do {
            func_8003F1DC(secondary);
            func_8003F114(model, 0, -1, *resource);
            ModelAnim_SetEventFrame(model, 0);
            func_8003F3BC(model, 0);
            func_8003F210(model, 0);
            ModelAnim_SetFrame(model, (s16)(guRandom() % 15 + 15));
            state++;
            secondary += 0x168;
            model += 0x168;
            resource++;
            state[-1].animation = 0;
        } while ((struct Fragment53ActorState *)D_865118F8 != state);
    }
    StageFade_StartFromOpaque(10);
    do {
        func_8650A074();
        func_80064D28();
        func_865082C8();
        result = func_86509E54(*(s32 *)((u8 *)&D_8650C5E0 + 0xC));
        *(s32 *)((u8 *)&D_8650C5E0 + 0xC) = result;
    } while (*(s32 *)((u8 *)&D_8650C5E0 + 0xC) != 3);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/53/fragment53_code/func_8650A3E4.s")
#endif
