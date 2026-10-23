#include "global.h"

extern u8 *D_841911E0;
extern u8 *D_841911E4;
extern void func_841112C8(void);
extern s32 D_84191208;
extern s32 D_8419120C;
extern void func_84111248();
extern u8 *D_841911E8;
extern u8 *func_8410B330(u8 *);
extern s32 func_8411DC80(u16, s32 *, s32);
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_80037120(void *, void *, f32 *, s16 *, s16 *);
extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
extern void func_84120BB4(u8 *, s32);
extern void func_8410B884(u8 *, void *, u8 *, s16);
extern u8 *D_84193DD0;
extern void func_8411FEE8(s32);
extern s32 D_841911EC;
extern s32 D_84184148;
extern void func_8410AF1C(void);
extern void func_8410C934(u8 *arg0, s32 arg1, s16 arg2);
extern void func_8410E73C();
extern s32 D_841910D8;
extern void func_8410B420(u8 *, void *, s16);
extern void func_8410EA58(u8 *, void *, s16);
extern void func_8411EF20(u8 *);
extern void func_8411EF08(u8 *arg0);
extern void func_8411EFE4(s32);
extern void func_8410B08C(void);
extern void func_8410B104(void);
extern void func_8410B224(void);
extern void func_8410B27C(u8 *arg0, u8 *arg1);
extern void func_8410B2DC(u8 *arg0, u8 *arg1);
extern void func_8410B578(f32 arg0);
extern void func_8410C304(u8 *arg0, s32 arg1, s32 arg2);
extern void func_8410E878(u8 *arg0, s32 arg1);

#ifdef VERSION_US
extern void func_8410D088(u8 *, s32);
extern void func_8410E878(u8 *, s32);
void BattleAnim_ModelDispatch_016(u8 *arg0, s32 arg1) {
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    func_8410D088(arg0, arg1);
    func_8410E878(arg0, arg1);
}
#endif

#ifdef VERSION_US
extern void func_8410E73C(u8 *, void *);
void BattleAnim_ModelDispatch_044(u8 *arg0, void *arg1) {
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    func_8410E73C(arg0, arg1);
}
#endif

#ifdef VERSION_US
extern u8 *func_8410B330(u8 *);
extern void func_8410B420(u8 *, void *, s16);
extern void func_8410EA58(u8 *, void *, s16);
extern u8 *D_841911E8;
extern s32 D_841911EC;
extern s32 D_84184148;
void BattleAnim_ModelDispatch_071(u8 *arg0, void *arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_8410EA58(arg0, arg1, *(s16 *)(D_841911E8 + 0x98));
    *(s32 *)(D_841911E8 + (D_841911EC * 8) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
void func_8411123C(u8 *arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
extern u8 *D_841911E0;
extern u8 D_84184144;
void func_84111248(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        *(s32 *)(D_841911E0 + (i * 8) + 8) = *(s32 *)((u8 *)&D_84184144 + 4);
    }
}
#endif

#ifdef VERSION_US
extern u8 *D_841911E4;
extern u8 D_84184144;
void func_841112C8(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        *(s32 *)(D_841911E4 + (i * 8) + 8) = *(s32 *)((u8 *)&D_84184144 + 4);
    }
}
#endif

#ifdef VERSION_US
extern u8 D_8418414C;
void func_84111348(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = (arg1 * 0x1C) + &D_8418414C;
    (*(s32 *)((u8 *)(D_841911E0) + (8))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0)));
    (*(s32 *)((u8 *)(D_841911E0) + (0x10))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (4)));
    (*(s32 *)((u8 *)(D_841911E0) + (0x18))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (8)));
    (*(s32 *)((u8 *)(D_841911E0) + (0x20))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0xC)));
    (*(s32 *)((u8 *)(D_841911E0) + (0x28))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x10)));
    (*(s32 *)((u8 *)(D_841911E0) + (0x30))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x14)));
    (*(s32 *)((u8 *)(D_841911E0) + (0x38))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x18)));
    (*(s32 *)((u8 *)(D_841911E0) + (4))) = arg0;
    (*(s32 *)((u8 *)(D_841911E0) + (0xC))) = arg0;
    (*(s32 *)((u8 *)(D_841911E0) + (0x14))) = arg0;
    (*(s32 *)((u8 *)(D_841911E0) + (0x1C))) = arg0;
    (*(s32 *)((u8 *)(D_841911E0) + (0x24))) = arg0;
    (*(s32 *)((u8 *)(D_841911E0) + (0x2C))) = arg0;
    (*(s32 *)((u8 *)(D_841911E0) + (0x34))) = arg0;
}
#endif

#ifdef VERSION_US
void func_841113F8(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = (arg1 * 0x1C) + &D_8418414C;
    (*(s32 *)((u8 *)(D_841911E4) + (8))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0)));
    (*(s32 *)((u8 *)(D_841911E4) + (0x10))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (4)));
    (*(s32 *)((u8 *)(D_841911E4) + (0x18))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (8)));
    (*(s32 *)((u8 *)(D_841911E4) + (0x20))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0xC)));
    (*(s32 *)((u8 *)(D_841911E4) + (0x28))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x10)));
    (*(s32 *)((u8 *)(D_841911E4) + (0x30))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x14)));
    (*(s32 *)((u8 *)(D_841911E4) + (0x38))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x18)));
    (*(s32 *)((u8 *)(D_841911E4) + (4))) = arg0;
    (*(s32 *)((u8 *)(D_841911E4) + (0xC))) = arg0;
    (*(s32 *)((u8 *)(D_841911E4) + (0x14))) = arg0;
    (*(s32 *)((u8 *)(D_841911E4) + (0x1C))) = arg0;
    (*(s32 *)((u8 *)(D_841911E4) + (0x24))) = arg0;
    (*(s32 *)((u8 *)(D_841911E4) + (0x2C))) = arg0;
    (*(s32 *)((u8 *)(D_841911E4) + (0x34))) = arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_841114A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84111774.s")
#endif

#ifdef VERSION_US
extern void func_8410B2DC(u8 *arg0, u8 *arg1);
s32 func_84111868(s32 arg0, u8 *arg1, u8 *arg2) {
    extern void func_8410B27C(u8 *, u8 *);
    extern void func_84111774(u8 *, u8 *);

    switch (arg0) {
    case 0:
        func_8410B27C(arg1, arg2);
        break;
    case 1:
    case 2:
        func_84111774(arg1, arg2);
        break;
    case 3:
        func_8410B2DC(arg1, arg2);
        break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern u8 *D_84191200[];
extern s32 D_84191208;
extern s32 D_8419120C;
extern s32 D_84195208[];
extern s32 D_841951F8[];
extern s32 D_84195200[];
extern u8 *D_84193FA0;
extern void *main_pool_alloc(s32, s32);
extern void _bzero(void *, s32);
void BattleAnim_AllocateSideObjects(void) {
    D_84191200[0] = main_pool_alloc(2040, 0);
    D_84191200[1] = main_pool_alloc(2040, 0);
    _bzero(D_84191200[0], 2040);
    _bzero(D_84191200[1], 2040);
    D_84191208 = (s32)D_84191200[0];
    D_8419120C = (s32)D_84191200[1];
    *(s32 *)((u8 *)D_84191208 + 1644) = D_84195208[0];
    *(s32 *)((u8 *)D_8419120C + 1644) = D_84195208[1];
    *(s32 *)((u8 *)D_84191208 + 1648) = D_841951F8[0];
    *(s32 *)((u8 *)D_84191208 + 1652) = D_84195200[0];
    *(s32 *)((u8 *)D_8419120C + 1648) = D_841951F8[1];
    *(s32 *)((u8 *)D_8419120C + 1652) = D_84195200[1];
    D_84193FA0 = main_pool_alloc(148, 0);
}
#endif

#ifdef VERSION_US
extern u16 D_84183BDC[6];
extern u32 func_8003570C(void);
extern u16 D_84183BE8[];
extern u16 D_84183BF0[];
extern u16 D_84183BFC[];
extern u16 D_84183C04[];
extern u16 D_84183C0C[];
extern u16 D_84183C14[];
extern u16 D_84183C1C[];
extern u16 D_84183C24[];
extern u16 D_84183C2C[];
extern u16 D_84183C34[];
void BattleAnim_SelectCameraPreset(u8 *arg0, u16 arg1) {
    s32 selector = arg1;
    switch (selector) {
    case 40: *(u16 *)(arg0 + 152) = D_84183BDC[func_8003570C() % 6]; break;
    case 41: *(u16 *)(arg0 + 152) = D_84183BE8[func_8003570C() % 4]; break;
    case 42: *(u16 *)(arg0 + 152) = D_84183BF0[func_8003570C() % 6]; break;
    case 43: *(u16 *)(arg0 + 152) = D_84183BFC[func_8003570C() % 4]; break;
    case 44: *(u16 *)(arg0 + 152) = D_84183C04[func_8003570C() % 3]; break;
    case 45: *(u16 *)(arg0 + 152) = D_84183C0C[func_8003570C() % 3]; break;
    case 46: *(u16 *)(arg0 + 152) = D_84183C14[func_8003570C() % 3]; break;
    case 47: *(u16 *)(arg0 + 152) = D_84183C1C[func_8003570C() % 3]; break;
    case 48: *(u16 *)(arg0 + 152) = D_84183C24[func_8003570C() % 3]; break;
    case 49: *(u16 *)(arg0 + 152) = D_84183C2C[func_8003570C() % 4]; break;
    case 50: *(u16 *)(arg0 + 152) = D_84183C34[func_8003570C() % 3]; break;
    default: *(u16 *)(arg0 + 152) = selector; break;
    }
}
#endif

#ifdef VERSION_US
extern void func_841206D0(u8 *);
void func_84111BEC(u8 *arg0) {
    *(u16 *)(arg0 + 0x7E8) = 0;
    func_8411FEE8(0);
    func_841206D0(arg0);
}
#endif

#ifdef VERSION_US
extern void func_841089D8(s32);
void func_84111C1C(void) {
    func_841089D8(1);
}
void func_84111C1C_padding(void) {}
#endif

#ifdef VERSION_US
extern s32 func_800238C4(void);
void func_84111C44(void) {
    (void)func_841089D8(1);
    (void)func_800238C4();
}
#endif

#ifdef VERSION_US
void func_84111C6C(void) {
    func_841089D8(0);
}
#endif

#ifdef VERSION_US
extern s32 func_8411DC80(u16, s32 *, s32);
extern u8 D_84183A28[];

s32 func_84111C8C(u8 *arg0) {
    u8 *result;
    u8 *v0;

    v0 = *(u8 **)(arg0 + 0xC);
    result = ((u8 *(*)(s32, s32)) *(u8 **)(v0 + 0x2C))(0, 0);
    if ((*(u8 *)(result + 5) - 1 < 0) || (func_8411DC80(*(u16 *)(arg0 + 0x1A), (s32 *)D_84183A28, 0x12) != 0)) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 func_8411DC80(u16, s32 *, s32);
extern u8 D_84183A3C[];

s32 func_84111CF8(u8 *arg0) {
    u8 *result;
    u8 *v0;

    v0 = *(u8 **)(arg0 + 0xC);
    result = ((u8 *(*)(s32, s32)) *(u8 **)(v0 + 0x2C))(0, 0);
    if ((*(u8 *)(result + 5) - 1 < 0) || (func_8411DC80(*(u16 *)(arg0 + 0x1A), (s32 *)D_84183A3C, 0x12) != 0)) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
void func_84111D64(u8 *arg0, s32 arg1) {
    extern void ModelAnim_SetResourceAnimation(s32, s32, s32);
    extern s32 D_84190518;
    if (*(s16 *)(arg0 + 0x658) == 0xFC) {
        ModelAnim_SetResourceAnimation(D_84190518, (s32)arg0, arg1);
    } else {
        ModelAnim_SetResourceAnimation(*(s32 *)(arg0 + 0x5C0), (s32)arg0, arg1);
    }
}
#endif

#ifdef VERSION_US
extern void func_80024974(s32, s16, s16, s32, s32);
void func_84111DB4(u8 *arg0, s32 arg1) {
    if ((*(f32 *)((u8 *)(arg0) + (0x28))) == 0.0f) {
        func_80024974(func_8411E1F8((s32) arg0) & 0xFF, (*(s16 *)((u8 *)(arg0) + (0x1A))), (*(s16 *)((u8 *)(arg0) + (0x40))), 0, arg1);
    } else {
        func_80024974(func_8411E1F8((s32) arg0) & 0xFF, (*(s16 *)((u8 *)(arg0) + (0x1A))), (*(s16 *)((u8 *)(arg0) + (0x40))), 1, arg1);
    }
    ModelAnim_SetFrame(arg0, (s16) arg1);
}
#endif

#ifdef VERSION_US
extern void ModelAnim_SetEventTrack();
void func_84111E50(arg0)
u8 *arg0;
{
    if ((*(u16 *)(arg0 + 0x56) & 1) == 0) {
        ModelAnim_SetEventTrack();
    }
}
#endif

#ifdef VERSION_US
extern void ModelAnim_SetEventFrame(void *, s16);
s32 func_84111CF8();

void func_84111E80(void *arg0, s32 arg1) {
    if (!((*(u16 *)((u8 *)(arg0) + (0x56))) & 1) && (func_84111CF8(arg0) == 0)) {
        ModelAnim_SetEventFrame(arg0, arg1);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84111EC4.s")
#endif

#ifdef VERSION_US
s32 ModelAnim_IsEventTrackDone();
s32 func_84111FA4(void *arg0) {
    if ((*(s32 *)((u8 *)(arg0) + (0x58))) == 0) {
        return 1;
    }
    if (ModelAnim_IsEventTrackDone() != 0) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 func_8003EF60(void);
void func_84111FEC(void) {
    (void)func_8003EF60();
}
#endif

#ifdef VERSION_US
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
void func_8411200C(u8 *arg0) {
    s16 temp = *(s16 *)(arg0 + 0x1A);
    if (temp == 0x64) {
        func_84111D64(arg0, 7);
    } else if (temp == 0x6E) {
        func_84111D64(arg0, 7);
    } else if (temp == 0xA9) {
        func_84111D64(arg0, 7);
    } else {
        func_84111D64(arg0, *(u8 *)((u8 *)(u32)*(u32 *)(arg0 + 0x2D4) + 0x13D8));
    }
    func_84111DB4(arg0, 0);
}
#endif

#ifdef VERSION_US
void func_841120A4(u8 *arg0) {}
#endif

#ifdef VERSION_US
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
void func_841120AC(u8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    temp_v0 = arg1 * 0x14;
    func_84111D64(arg0, *(u8 *)(*(u8 **)(arg0 + 0x2D4) + temp_v0));
    func_84111E50(arg0, *(s8 *)(*(u8 **)(arg0 + 0x2D4) + temp_v0 + 1));
    func_84111DB4(arg0, (*(u16 *)(*(u8 **)(arg0 + 0x44) + 0xA) *
        ((arg2 / *(u16 *)(*(u8 **)(arg0 + 0x44) + 0xA)) + 1)) - arg2);
}
#endif

#ifdef VERSION_US
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s32 arg1);
void func_84112158(s32 arg0, s32 arg1) { func_84111D64((u8 *)arg0, *(u8 *)((u8 *)(u32)*(u32 *)(arg0 + 0x2D4) + arg1 * 0x14)); func_84111E50((u8 *)arg0, *(s8 *)((u8 *)(u32)*(u32 *)(arg0 + 0x2D4) + arg1 * 0x14 + 1)); func_84111DB4((u8 *)arg0, 0); func_84111E80((void *)arg0, 0); }
#endif

#ifdef VERSION_US
void BattleAnim_SetAnimationAndFrame(u8 *arg0, s32 animation, s32 event, s32 frame) {
    func_84111D64(arg0, animation);
    func_84111E50(arg0, event);
    func_84111DB4(arg0, frame);
    func_84111E80(arg0, frame);
}
#endif

#ifdef VERSION_US
/* mkdraft:func_84112218 begin */
void func_84112218(u8 *arg0, s32 arg1, s32 arg2) {
    func_84111D64(arg0, *(u8 *)((u8 *)(u32)*(u32 *)(arg0 + 0x2D4) + arg1 * 0x14));
    func_84111E50(arg0, *(u8 *)((u8 *)(u32)*(u32 *)(arg0 + 0x2D4) + arg1 * 0x14 + 1));
    func_84111DB4(arg0, arg2);
    func_84111E80(arg0, arg2);
}
/* mkdraft:func_84112218 end */
#endif

#ifdef VERSION_US
void func_84112290(u8 *arg0) {
    func_8003EF70(arg0);
    *(u8 *)(arg0 + 2) = *(u8 *)(arg0 + 2) | 0x20;
    ModelAnim_SetEventTrack(arg0, -1);
    ModelAnim_SetEventFrame(arg0, 0);
}
#endif

#ifdef VERSION_US
extern s32 func_84111C8C(u8 *);
extern void func_84112158(s32, s32);
void func_841122D4(u8 *arg0) { if (func_84111C8C(arg0) != 0) { func_84112158(arg0, 0x105); } else { *(u16 *)(arg0 + 0x7F4) |= 1; func_84111E50(arg0, *(u8 *)(*(u8 **)(arg0 + 0x2D4) + 0x1465)); } }
#endif

#ifdef VERSION_US
/* mkdraft:func_84112324 begin */
void func_84112324(u8 *arg0) {
    if (func_84111C8C(arg0) != 0) {
        func_84111D64(arg0, *(u8 *)(*(u8 **)(arg0 + 0x2D4) + 0x1464));
        if (*(s16 *)(arg0 + 0x1A) == 0x6E) {
            func_84111E50(arg0, *(s8 *)(*(u8 **)(arg0 + 0x2D4) + 0x1465));
            if (*(s8 *)(*(u8 **)(arg0 + 0x2D4) + 0x1465) >= 0) {
                func_84111E80(arg0, *(u16 *)(*(u8 **)(arg0 + 0x58) + 0xA) - 1);
            }
        }
        if (ModelAnim_IsFinished(arg0) != 0) {
            func_84111DB4(arg0, 0);
        }
    } else {
        *(u16 *)(arg0 + 0x7F4) |= 1;
        func_84111D64(arg0, *(u8 *)(*(u8 **)(arg0 + 0x2D4) + 0x1464));
        func_84111E50(arg0, *(s8 *)(*(u8 **)(arg0 + 0x2D4) + 0x1465));
        if (*(s8 *)(*(u8 **)(arg0 + 0x2D4) + 0x1465) >= 0) {
            func_84111E80(arg0, *(u16 *)(*(u8 **)(arg0 + 0x58) + 0xA) - 1);
        }
    }
}
/* mkdraft:func_84112324 end */
#endif

#ifdef VERSION_US
extern void func_84111DB4(u8 *arg0, s32 arg1);
s32 func_84112418(u8 *arg0) { if (func_84111C8C(arg0)) { if (ModelAnim_IsFinished(arg0) != 0) { func_84111DB4(arg0, 0); } return 0; } return 0; }
#endif

#ifdef VERSION_US
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s32 arg1);
extern void func_84111FEC(void);
extern s32 func_8411DC80(u16, s32 *, s32);
extern s32 D_84183A50[];
#ifdef CC_CHECK
#define CALL_84111FEC(x) ((void (*)(u8 *))func_84111FEC)(x)
#else
#define CALL_84111FEC(x) func_84111FEC(x)
#endif

void func_84112464(u8 *arg0) {
#ifndef CC_CHECK
    extern void func_84111FEC();
#endif
    u8 *self = arg0; if (*(s16 *)(self + 0x1A) == 0xFC) { func_84111D64(self, (*(u8 **)(self + 0x2D4))[0x139C]); func_84111DB4(self, 0); self[2] &= 0xFFDF; CALL_84111FEC((u8 *)arg0); *(u16 *)(self + 0x7F4) |= 2; return; } func_84111D64(self, (*(u8 **)(self + 0x2D4))[0x13D8]); func_84111E50(self, (*(u8 **)(self + 0x2D4))[0x13D9]); if (func_8411DC80(*(u16 *)(self + 0x1A), D_84183A50, 10) != 0) { func_84111DB4(self, 0); func_84111E80(self, 0); } else { func_84111DB4(self, 6); func_84111E80(self, 6); } self[2] &= 0xFFDF; CALL_84111FEC((u8 *)arg0); *(u16 *)(self + 0x7F4) |= 2; }

#undef CALL_84111FEC
#endif

#ifdef VERSION_US
void func_84112564(s32 arg0) {
    D_84193DD0[1] |= 1;
}
#endif

#ifdef VERSION_US
void func_84112580(s32 arg0) {
    D_84193DD0[1] |= 4;
}
#endif

void func_8411259C(void) {
}

#ifdef VERSION_US
extern s32 D_84183D50;
void func_841125A4(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        ((s32 *)(arg0 + 0x5C8))[i] = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern u8 D_84183D54;
void func_841125F4(void *arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = (arg1 * 0x1C) + &D_84183D54;
    (*(s32 *)((u8 *)(arg0) + (0x5C8))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0)));
    (*(s32 *)((u8 *)(arg0) + (0x5CC))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (4)));
    (*(s32 *)((u8 *)(arg0) + (0x5D0))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (8)));
    (*(s32 *)((u8 *)(arg0) + (0x5D4))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0xC)));
    (*(s32 *)((u8 *)(arg0) + (0x5D8))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x10)));
    (*(s32 *)((u8 *)(arg0) + (0x5DC))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x14)));
    (*(s32 *)((u8 *)(arg0) + (0x5E0))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x18)));
}
#endif

#ifdef VERSION_US
extern s32 D_841911F4;
void BattleAnim_RunObjectCallbacks(u8 *arg0) {
    for (D_841911F4 = 0; D_841911F4 < 7; D_841911F4++) {
        ((void (**)(u8 *))(arg0 + 1480))[D_841911F4](arg0);
    }
    (*(s16 *)(arg0 + 2024))++;
}
#endif

#ifdef VERSION_US
extern s32 func_8411E164();
extern void func_841125A4(s32);
extern void func_84112158(s32, s32);
void func_841126C8(s32 arg0) {
    func_841125A4(func_8411E164(arg0));
    func_84112158(func_8411E164(arg0), 0xFB);
}
#endif

#ifdef VERSION_US
void func_84112704(void *arg0) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0x664)));
    (*(f32 *)((u8 *)(arg0) + (0x644))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0x20)));
    (*(f32 *)((u8 *)(arg0) + (0x640))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0x1C)));
    (*(f32 *)((u8 *)(arg0) + (0x654))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0xC)));
    (*(f32 *)((u8 *)(arg0) + (0x64C))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (4)));
    (*(f32 *)((u8 *)(arg0) + (0x650))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (8)));
    (*(f32 *)((u8 *)(arg0) + (0x654))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0xC)));
    (*(f32 *)((u8 *)(arg0) + (0x634))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0x10)));
    (*(f32 *)((u8 *)(arg0) + (0x638))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0x14)));
    (*(f32 *)((u8 *)(arg0) + (0x63C))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0x18)));
    (*(f32 *)((u8 *)(arg0) + (0x648))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0x14)));
}
#endif

#ifdef VERSION_US
extern u8 *D_841910DC;
extern u8 D_84191210[];
extern void func_80003F74(u8 *, u8 *, u8 *, s32);
void BattleAnim_LoadModelResource(u8 *arg0) {
    u8 *start;
    u8 *end;
    s32 *entry;
    entry = ((s32 (*)[4])D_841910DC)[*(s16 *)(arg0 + 1624)];
    start = (u8 *)(entry[0] + *(s32 *)(D_841910DC + 4));
    end = start + entry[1];
    func_80003F74(D_84191210 + func_8411E1F8((s32)arg0) * 5600, start, end, 0);
    *(u8 **)(arg0 + 724) = D_84191210 + func_8411E1F8((s32)arg0) * 5600;
}
#endif

#ifdef VERSION_US
extern void BattleAnim_LoadModelResource(u8 *);
void func_8411281C(u8 *arg0) {
    BattleAnim_LoadModelResource(arg0);
}
#endif

#ifdef VERSION_US
/* mkdraft:func_8411283C begin */
extern void func_8003F018(void *);
extern void func_8003F1DC(u8 *);
extern void func_8003F114(u8 *, s32, s16, s32);
extern void func_8003F9AC(u8 *, s16, u16);
extern void func_8003F2C4(s32, s32, s32);
extern u8 *D_84193DD0;

void func_8411283C(u8 *arg0) {
    s32 index;
    s32 i;
    u8 *elem;

    for (i = 0; i < 2; i++) {
        elem = arg0 + 0x2D8 + i * 0x170;
        func_8003F018(elem);
        func_8003F1DC(elem);
        func_8003F114(elem, 0, *(s16 *)(arg0 + 0x658), **(s32 **)(*(s32 *)(*(s32 *)(arg0 + 0x5C0) + 0x38) + 8));
        index = func_8411E1F8((s32)arg0);
        func_8003F9AC(arg0, *(s16 *)(arg0 + 0x1A), *(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x14));
        func_8003F2C4(*(s32 *)(arg0 + 0x5C0), (s32)elem, 0);
        *(u8 *)(elem + 2) &= ~0x40;
        *(u8 *)(elem + 1) &= ~1;
    }
}
/* mkdraft:func_8411283C end */
#endif

#ifdef VERSION_US
extern void func_8003F018(void *);
extern void func_8003F3BC(void *, u8);
extern void func_8003F114(u8 *, s32, s16, s32);
extern void func_8003F1DC(u8 *);
extern void ModelAnim_SetResourceAnimation(s32, s32, s32);
extern void SceneObject_SetModelVariant(u8 *, s16, u16);
extern u8 * D_84193DD0;
void func_8411293C(u8 *arg0, u8 *arg1, s16 arg2) {
    s32 index;
    func_8003F018(arg1);
    func_8003F1DC(arg1);
    func_8003F114(arg1, arg2, *(s16 *)(arg0 + 0x658), **(s32 **)(*(s32 *)(*(s32 *)(arg0 + 0x5C0) + 0x38) + 8));
    index = func_8411E1F8((s32)arg0);
    SceneObject_SetModelVariant(arg1, *(s16 *)(arg1 + 0x1A), *(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x14));
    ModelAnim_SetResourceAnimation(*(void **)(arg0 + 0x5C0), arg1, *(u8 *)(*(u8 **)(arg0 + 0x2D4) + 0x139C));
    func_8003F3BC(arg1, *(u8 *)(*(u8 **)(arg0 + 0x2D4) + 0x139D));
}
#endif

#ifdef VERSION_US
void func_841129E8(u8 *arg0, s16 arg1, s32 arg2) {
    extern void func_8003F114(u8 *, s32, s16, s32);
    extern void SceneObject_SetModelVariant(u8 *, s16, u16);
    s32 index;

    func_8003F114(arg0, 0, arg1, arg2);
    index = func_8411E1F8((s32)arg0);
    SceneObject_SetModelVariant(arg0, arg1,
        *(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0x14));
}
#endif

#ifdef VERSION_US
/* mkdraft:func_84112A40 begin */
extern void func_8003F1DC(u8 *);
extern void func_8003F114(u8 *, s32, s16, s32);
extern void func_8003F9AC(u8 *, s16, u16);
extern void func_8003F2C4(s32, s32, s32);
extern u8 *D_84193DD0;

void func_84112A40(u8 *arg0) {
    s32 index;
    s32 i;
    u8 *elem;

    for (i = 0; i < 2; i++) {
        elem = arg0 + 0x2D8 + i * 0x170;
        func_8003F1DC(elem);
        func_8003F114(elem, 0, *(s16 *)(arg0 + 0x658), **(s32 **)(*(s32 *)(*(s32 *)(arg0 + 0x5C0) + 0x38) + 8));
        index = func_8411E1F8((s32)arg0);
        func_8003F9AC(elem, *(s16 *)(arg0 + 0x1A), *(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x14));
        ModelAnim_SetFrame(elem, 0);
        func_8003F2C4(*(s32 *)(arg0 + 0x5C0), (s32)elem, 0);
        *(u8 *)(elem + 2) &= ~0x40;
        *(u8 *)(elem + 1) &= ~1;
    }
}
/* mkdraft:func_84112A40 end */
#endif

#ifdef VERSION_US
void func_84112B44(u8 *arg0) {
    BattleAnim_LoadModelResource(arg0);
}
#endif

#ifdef VERSION_US
extern void func_8003F1DC(u8 *);
extern void func_84108E00(u8 *, s32);
extern void func_84112158(s32 arg0, s32 arg1);
extern void func_84112704(void *arg0);
extern void func_841129E8(u8 *arg0, s16 arg1, s32 arg2);
extern void func_84112B44(u8 *arg0);
extern void func_84113014(u8 *);
extern void func_841242C0(void);
extern s32 D_84190518;
extern u8 * D_84193DD0;
void BattleAnim_LoadSpecialModel(u8 *arg0) {
    if ((((u16 (*)[8])(D_84193DD0 + 16))[func_8411E1F8((s32)arg0)][1] & 4) != 0) {
        if (*(s16 *)(arg0 + 1624) == 50 || *(s16 *)(arg0 + 1624) == 51) {
            return;
        }
    }
    if (*(s16 *)(arg0 + 1624) != 252) {
        *(s16 *)(arg0 + 1624) = 252;
        func_84112B44(arg0);
        func_84113014(arg0);
        func_8003F1DC(arg0);
        func_841129E8(arg0, 252, **(s32 **)(*(u8 **)((u8 *)D_84190518 + 56) + 8));
        func_84112158((s32)arg0, 251);
        func_84112704(arg0);
        func_841242C0();
        if (((u16 (*)[8])(D_84193DD0 + 16))[func_8411E1F8((s32)arg0)][0] == 0x20) {
            func_84108E00(arg0, 1);
        }
        if ((((u16 (*)[8])(D_84193DD0 + 16))[func_8411E1F8((s32)arg0)][0] & 7) != 0) {
            func_84108E00(arg0, 2);
        }
        *(s16 *)(arg0 + 2026) = 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84112C98.s")
#endif

#ifdef VERSION_US
extern void BattleAnim_LoadSpecialModel(u8 *);
extern s32 D_84191208;
extern s32 D_8419120C;
extern void func_84112C98();
void func_84112DB8(void) {
    if ((*(u16 *)((u8 *)(D_84193DD0) + (0x12))) & 1) {
        BattleAnim_LoadSpecialModel(D_84191208);
    } else {
        func_84112C98(D_84191208);
    }
    if ((*(u16 *)((u8 *)(D_84193DD0) + (0x22))) & 1) {
        BattleAnim_LoadSpecialModel(D_8419120C);
        return;
    }
    func_84112C98(D_8419120C);
}
#endif

#ifdef VERSION_US
extern void func_84112C98();
void func_84112E40(s32 arg0) {
    extern s32 func_8411F750(u8);
    s32 index;

    index = func_8411F750(*(u8 *)(u32)D_84193DD0);
    index = func_8411E1F8(index);
    if ((*(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0x12) & 1) != 0) {
        BattleAnim_LoadSpecialModel(arg0);
        return;
    }
    func_84112C98(arg0);
}
#endif

#ifdef VERSION_US

void func_84112EAC(void *arg0) {
    if ((*(s16 *)((u8 *)(arg0) + (0x1A))) == 0xFC) {
        func_84112C98();
    }
}
#endif

#ifdef VERSION_US
extern void func_84113014(u8 *);
extern void func_8003F1DC(u8 *);
extern void func_841242C0(void);
extern u8 *D_84193F88;
extern u8 *D_84193F8C;
extern void func_8411F558(u8 *, s32);
extern void func_84112A40(u8 *);
extern void func_84112158(s32 arg0, s32 arg1);
extern void func_8411EFE4(s32);
extern s32 D_84191208;
void func_84112EDC(u8 *arg0) {
    *(s16 *)(arg0 + 0x658) = *(s16 *)(arg0 + 0x65C);
    func_84112B44(arg0);
    func_84113014(arg0);
    func_8003F1DC(arg0);
    func_841129E8(arg0, *(s16 *)(arg0 + 0x658), *(s32 *)(*(s32 *)(*(s32 *)(*(s32 *)(arg0 + 0x5C0) + 0x38) + 8)));
    if (*(s16 *)(arg0 + 0x658) == 0x32 || *(s16 *)(arg0 + 0x658) == 0x33) {
        *(u8 *)(arg0 + 2) &= 0xFFBF;
    }
    func_84112158((s32)arg0, 0xFB);
    func_84112704(arg0);
    func_841242C0();
    func_8411EFE4((s32)arg0);
    if (D_84191208 == (s32)arg0) {
        func_8411F558(*(u8 **)(D_84193F88 + 0x168), (s32)arg0);
    } else {
        func_8411F558(*(u8 **)(D_84193F8C + 0x168), (s32)arg0);
    }
    func_84112A40(arg0);
    *(s16 *)(arg0 + 0x7EA) = 0;
    *(s16 *)(arg0 + 0x7F4) = 0;
}
#endif

#ifdef VERSION_US
typedef union {
    s32 word;
    s8 bytes[4];
} F12State;
extern s32 func_80041FD0(u8 *, u16, F12State, s32);
void func_84112FD0(u8 *arg0, u16 arg1, F12State arg2, s32 arg3) {
    func_80041FD0(arg0, arg1, arg2, arg3);
}
#endif

#ifdef VERSION_US
void func_84112FFC(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x678) = arg1;
}
#endif

#ifdef VERSION_US
void func_84113004(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x664) = arg1;
}
#endif

#ifdef VERSION_US
void func_8411300C(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x668) = arg1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84113014.s")
#endif

#ifdef VERSION_US
s32 func_841133EC(s32 arg0) {
    extern u8 D_84193DDC;
    return D_84193DDC & 0xD0;
}
#endif

#ifdef VERSION_US
extern u8 D_84193DD8[];
extern u8 D_84193DDC;
extern s32 func_8003F904(u8 *);
s32 func_84113400(s32 arg0) {
    func_8003F904(D_84193DD8);
    return D_84193DDC & 0xC0;
}
#endif

#ifdef VERSION_US
extern void func_8410373C(u8 *);

s32 func_84113430(s32 arg0) {
    if (func_84113400(arg0) == 0) {
        func_8410373C(D_84193DD8);
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern void func_84103640(u8 *, s32);
void func_8411346C(s32 arg0) {
    func_8411FEE8(0xFFFF);
    func_84103640(D_84193DD8, 0);
}
#endif

#ifdef VERSION_US
extern void func_84103694(s32, s16);
void func_841134A0(u8 *arg0) {
    func_8411FEE8(0xFFFF);
    func_84103694((s32)D_84193DD8, arg0[0x618]);
}
#endif

#ifdef VERSION_US
extern s32 func_80062D20(u8);
void func_841134D8(u8 *arg0) {
    func_8411FEE8(0xFFFF);
    if (arg0[0x618] != 0xF8) {
        if (func_80062D20(D_84193DD0[8]) != 0x4D &&
            func_80062D20(D_84193DD0[8]) != 0x1D) {
            return;
        }
    }
    func_84111C44();
    func_84103694((s32)D_84193DD8, arg0[0x618]);
}
#endif

#ifdef VERSION_US
void func_84113560(s32 arg0) {
    func_84103694((s32)D_84193DD8, (s16)arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84113590.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84113658.s")
#endif

#ifdef VERSION_US
extern void func_84108AF8(u8 *);
extern u8 * D_84193DD0;
void func_841136E8(u8 *arg0) {
    s32 index;
    if ((*(u16 *)(arg0 + 0x7F4) & 0x10) != 0) {
        index = func_8411E1F8((s32)arg0);
        if ((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12) & 4) == 0) { *(u16 *)(arg0 + 0x7F4) &= 0xFFEF; func_84108AF8(arg0); }
    }
    if ((*(u16 *)(arg0 + 0x7F4) & 0x20) != 0) {
        index = func_8411E1F8((s32)arg0);
        if (*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x10) != 0x20) { *(u16 *)(arg0 + 0x7F4) &= 0xFFDF; func_84108AF8(arg0); }
    }
    if ((*(u16 *)(arg0 + 0x7F4) & 0x40) != 0) {
        index = func_8411E1F8((s32)arg0);
        if ((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x10) & 7) == 0) { *(u16 *)(arg0 + 0x7F4) &= 0xFFBF; func_84108AF8(arg0); }
    }
}
#endif

#ifdef VERSION_US
void func_841137F0(u8 *arg0) {}
#endif

#ifdef VERSION_US
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s32 arg1);
void func_841137F8(u8 *arg0) { if ((*(s16 *)(arg0 + 0x7E8) % 0xC8) == 0) { func_84111E50(arg0, (*(u8 **)(arg0 + 0x2D4))[0x139D]); func_84111E80(arg0, 0); } if (ModelAnim_IsFinished(arg0) != 0) { if (*(s16 *)(arg0 + 0x40) != (*(u8 **)(arg0 + 0x2D4))[0x139C]) { func_84111D64(arg0, (*(u8 **)(arg0 + 0x2D4))[0x139C]); } else { func_84111DB4(arg0, 0); } } }
#endif

#ifdef VERSION_US
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s32 arg1);
void func_8411388C(u8 *arg0) { if ((*(s16 *)(arg0 + 0x7E8) % 0xC8) == 0) { func_84111E50(arg0, (*(u8 **)(arg0 + 0x2D4))[0x1479]); func_84111E80(arg0, 0); } if (ModelAnim_IsFinished(arg0) != 0 || *(s16 *)(arg0 + 0x40) != (*(u8 **)(arg0 + 0x2D4))[0x1478]) { func_84111D64(arg0, (*(u8 **)(arg0 + 0x2D4))[0x1478]); func_84111DB4(arg0, 0); } }
#endif

#ifdef VERSION_US
extern void func_84112218(u8 *, s32, s32);
void func_84113920(u8 *arg0) {
    s32 index;

    index = func_8411E1F8((s32)arg0);
    if (((*(u16 *)((u8 *)(D_84193DD0) + (index << 4) + 0x12)) & 4) != 0) {
        if (*(s16 *)(arg0 + 0x1A) == 0x32) {
            func_84112218(arg0, 0x102, 0x28);
            return;
        }
    }
    index = func_8411E1F8((s32)arg0);
    if (((*(u16 *)((u8 *)(D_84193DD0) + (index << 4) + 0x12)) & 4) != 0) {
        if (*(s16 *)(arg0 + 0x1A) == 0x33) {
            func_84112218(arg0, 0x102, 0x30);
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_84112218(u8 *, s32, s32);
extern void func_84112464(u8 *arg0);
extern void func_8411388C(u8 *arg0);
extern void func_8411EE74();
extern u8 * D_84193DD0;
s32 func_841139D0(u8 *arg0) {
    s32 result;
    s32 index;
    result = 0;
    index = func_8411E1F8((s32)arg0);
    if ((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12) & 2) != 0) { func_8411388C(arg0); result = 1; goto done; }
    index = func_8411E1F8((s32)arg0);
    if ((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12) & 4) != 0 && *(s16 *)(arg0 + 0x1A) != 0x32 && *(s16 *)(arg0 + 0x1A) != 0x33) { func_8411EE74(arg0); result = 1; goto done; }
    index = func_8411E1F8((s32)arg0);
    if ((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12) & 4) != 0 && *(s16 *)(arg0 + 0x1A) == 0x32) { func_84112218(arg0, 0x102, 0x28); result = 1; goto done; }
    index = func_8411E1F8((s32)arg0);
    if ((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12) & 4) != 0 && *(s16 *)(arg0 + 0x1A) == 0x33) { func_84112218(arg0, 0x102, 0x30); result = 1; goto done; }
    index = func_8411E1F8((s32)arg0);
    if (*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x10) == 0x20) { func_84112464(arg0); result = 1; goto done; }
    index = func_8411E1F8((s32)arg0);
    if ((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x10) & 7) != 0) { func_84112324(arg0); result = 1; goto done; }
    index = func_8411E1F8((s32)arg0);
    if (*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x0E) == 0) { func_8411EE74(arg0); result = 1; }
done: return result;
}
#endif

#ifdef VERSION_US
extern s32 func_841139D0(u8 *);
extern void func_841136E8(u8 *);
extern s32 D_841911F4;
extern s32 D_84183D50;
void BattleAnim_Dispatch_001(u8 *arg0) {
    if ((func_841139D0(arg0) == 0) && ((*(s16 *)((u8 *)(arg0) + (0x40))) != 0)) {
        func_84112158((s32) arg0, 0xFB);
    }
    func_841136E8(arg0);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84112158(s32, s32);
extern void func_841136E8(u8 *);
void BattleAnim_Dispatch_190(u8 *arg0) {
    s32 index;

    if ((func_841139D0(arg0) == 0) && (*(s16 *)(arg0 + 0x40) != 0)) {
        func_84112158((s32)arg0, 0xFB);
    }
    func_841136E8(arg0);
    index = func_8411E1F8((s32)arg0);
    if ((*(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0x12) & 8) != 0) {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0x30),
            0.8000000119f, 0.8000000119f, 0.8000000119f);
    }
    *(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + 0x5C8) = (s32)D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_841137F8(u8 *);
void BattleAnim_Dispatch_002(u8 *arg0) {
    if (func_841139D0(arg0) == 0) {
        func_841137F8(arg0);
    }
}
#endif

#ifdef VERSION_US
void func_84113D38(u8 *arg0) {
    if ((func_841139D0(arg0) == 0) && ((*(s16 *)((u8 *)(arg0) + (0x40))) != 0)) {
        func_84112158((s32) arg0, 0xFB);
    }
    func_841136E8(arg0);
}
#endif

#ifdef VERSION_US
extern void func_84111C1C(void);
extern void func_84113560(s32);
extern s32 D_84183D50;
extern s32 D_841911F4;
extern u8 D_841911FA;
extern u8 * D_84193DD0;
void BattleAnim_Dispatch_218(u8 *arg0) {
    s32 index;
    if (D_841911FA == 0) { func_84111C1C(); }
    if (D_841911FA == 0) {
        index = func_8411E1F8((s32)arg0);
        if (((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12)) & 0x10) != 0) { func_84113560(0x11C); }
        else { index = func_8411E1F8((s32)arg0); if (((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12)) & 0x20) != 0) { func_84113560(0x11E); } else { index = func_8411E1F8((s32)arg0); if (((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12)) & 0x40) != 0) func_84113560(0x11D); } }
    }
    *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84113E7C.s")
#endif

#ifdef VERSION_US
void func_84114600(void *arg0) {
    extern void func_84108728(u8, void *, s32);
    extern void func_800231A0(short, s16, s32, ...);
    s32 result;

    result = func_8411E164(arg0);
    func_84108728(*(u8 *)((u8 *)arg0 + 0x618), arg0, result);
    if ((D_84193DD0[9] & 7) == 1) {
        func_800231A0(*(u8 *)((u8 *)arg0 + 0x618),
            *(s16 *)((u8 *)arg0 + 0x658), 2, arg0);
        return;
    }
    func_800231A0(*(u8 *)((u8 *)arg0 + 0x618),
        *(s16 *)((u8 *)arg0 + 0x658), 0, arg0);
}
#endif

#ifdef VERSION_US
extern void func_800231A0(short, s16, s32, ...);
void func_84114678(void *arg0) {
    if (((*(u8 *)((u8 *)(D_84193DD0) + (9))) & 7) == 1) {
        func_800231A0((*(u8 *)((u8 *)(arg0) + (0x618))), (*(s16 *)((u8 *)(arg0) + (0x658))), 2, arg0);
        return;
    }
    func_800231A0((*(u8 *)((u8 *)(arg0) + (0x618))), (*(s16 *)((u8 *)(arg0) + (0x658))), 0, arg0);
}
#endif

#ifdef VERSION_US
extern s32 func_8411E164(s32);
void BattleAnim_ApplyAnimationRecord(u8 *arg0, s32 index) {
    u8 *entry;

    entry = *(u8 **)(arg0 + 724) + index * 20;
    arg0[1558] = entry[0];
    arg0[1559] = entry[1];
    arg0[1561] = entry[11];
    arg0[1562] = entry[10];
    arg0[1563] = entry[6];
    arg0[1568] = entry[9];
    arg0[1564] = entry[2];
    arg0[1565] = entry[3];
    *(s16 *)(arg0 + 1576) = entry[12];
    *(s16 *)(arg0 + 1578) = entry[13];
    *(s16 *)(arg0 + 1580) = entry[14];
    arg0[1633] = entry[15];
    *(s16 *)((u8 *)func_8411E164((s32)arg0) + 1576) = (*(u8 **)((u8 *)func_8411E164((s32)arg0) + 724))[index * 20 + 16];
    *(s16 *)((u8 *)func_8411E164((s32)arg0) + 1578) = (*(u8 **)((u8 *)func_8411E164((s32)arg0) + 724))[index * 20 + 17];
    *(s16 *)((u8 *)func_8411E164((s32)arg0) + 1580) = (*(u8 **)((u8 *)func_8411E164((s32)arg0) + 724))[index * 20 + 18];
    *(u8 *)((u8 *)func_8411E164((s32)arg0) + 1633) = (*(u8 **)((u8 *)func_8411E164((s32)arg0) + 724))[index * 20 + 19];
}
#endif

#ifdef VERSION_US
extern s32 D_841839EC[];
extern void BattleAnim_SelectCameraPreset(u8 *, u16);
extern void BattleAnim_ApplyAnimationRecord(u8 *, s32);
extern s32 func_8411DC80(u16, s32 *, s32);
extern u8 D_841849B6[];
extern u8 * D_841911E0;
void func_84114804(u8 *arg0) {
    u8 id;
    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        BattleAnim_SelectCameraPreset(D_841911E0, *(u16 *)(D_841849B6 + (arg0[0x618] * 8)));
        id = arg0[0x618];
        if (id == 0x39) { arg0[0x61F] = 10; }
        else if (id == 0x42) { arg0[0x61F] = 4; }
        else if (id == 0x45) { arg0[0x61F] = 8; }
        else if (id == 0x60) { arg0[0x61F] = 13; }
        else if (id == 0x61) { arg0[0x61F] = 6; }
        else if (id == 0x68) { arg0[0x61F] = 7; }
        else if (id == 0x6E && func_8411DC80(*(u16 *)(arg0 + 0x1A), D_841839EC, 6) == 0) {
            arg0[0x61F] = 12;
        }
        else if (arg0[0x618] == 0x7F) { arg0[0x61F] = 14; }
        else if (arg0[0x618] == 0xB9) { arg0[0x61F] = 25; }
        else if (arg0[0x618] == 0xE5) { arg0[0x61F] = 19; }
        else if (arg0[0x618] == 0x6B) { arg0[0x61F] = 9; }
        else if (arg0[0x618] == 0xBB) { arg0[0x61F] = 26; }
        else if (arg0[0x618] == 0xC2) { arg0[0x61F] = 24; }
        else { arg0[0x61F] = 0xFF; }
        BattleAnim_ApplyAnimationRecord(arg0, arg0[0x618] - 1);
    }
}
#endif

#ifdef VERSION_US
f32 func_8410EB50();
void BattleAnim_Dispatch_015(u8 *arg0) {
    (*(u8 *)((u8 *)(arg0) + (0x618))) = (u8) (*(u8 *)((u8 *)(D_84193DD0) + (8)));
    func_84111C44();
    func_841134A0(arg0);
    (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 5;
    (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_841120AC(u8 *arg0, s32 arg1, s32 arg2);
extern void func_841126C8(s32 arg0);
extern void func_84112E40(s32 arg0);
extern void func_84112EAC(void *arg0);
extern s32 func_84113430(s32 arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern u8 * D_841911E0;
extern s32 D_841911F4;
extern u8 * D_84193DD0;
void func_84114A04(u8 *a){s32 i;if(!func_84113430((s32)a))return;if(a[0x618]==164)func_84112E40((s32)a);else func_84112EAC(a);func_84114804(a);func_841126C8((s32)a);if(*(s16*)(D_841911E0+152)!=33){if(a[0x618]==19){*(s16*)(D_841911E0+152)=14;func_84111348((s32)a,5);}else if(a[0x618]==57)func_84111348((s32)a,13);else if(a[0x618]==127)func_84111348((s32)a,3);else if(a[0x618]==229)func_84111348((s32)a,17);else func_84111348((s32)a,0);}if(a[0x618]==19)*(u16*)(a+2036)|=8;*(s16*)(a+2024)=0;if(*(s8*)(a+1561)<0){*(s16*)(a+2024)=*(s8*)(a+1561);func_841120AC(a,251,-*(s16*)(a+2024));}a[2038]=0;a[1562]=a[1562]-a[1563];a[1561]=*(s8*)(a+1561)-a[1563];func_8411FEE8(600);if(a[0x618]==156)func_841120AC(a,251,a[1561]);else if(a[0x618]==173){i=func_8411E1F8((s32)a);if((*(u16 *)((u8 *)D_84193DD0+(i<<4)+16)&7)!=0)func_84112324(a);}*(s32*)(a+D_841911F4*4+1480)=D_84183D50;}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84114BF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_841153DC.s")
#endif

#ifdef VERSION_US
extern void func_84114BF4(s32);
extern void func_841153DC(s32);
void BattleAnim_Dispatch_017(s32 arg0) {
    if ((func_841133EC(arg0) == 0) && ((*(s8 *)((u8 *)(arg0) + (0x7F6))) == 0)) {
        if ((*(u8 *)((u8 *)(arg0) + (0x618))) == 0x9C) {
            func_841153DC(arg0);
            return;
        }
        func_84114BF4(arg0);
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_043(u8 *arg0) {
    (*(s8 *)((u8 *)(arg0) + (0x618))) = 0x13;
    func_84111C44();
    func_841134A0(arg0);
    (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 5;
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern void BattleAnim_ApplyAnimationRecord(u8 *, s32);
void func_841155B0(u8 *arg0) {
    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        arg0[0x61F] = 3;
        BattleAnim_ApplyAnimationRecord(arg0, 0x100);
    }
}
#endif

#ifdef VERSION_US
extern void func_80030420(s32, u8, s16, s32);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s32 arg1);
extern void func_841126C8(s32 arg0);
extern s32 func_84113430(s32 arg0);
extern void func_841155B0(u8 *arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern u8 * D_841911E0;
extern s32 D_841911F4;
void BattleAnim_Dispatch_044(u8 *arg0) {
    if (func_84113430((s32)arg0) == 0) return;
    func_84112EAC((void *)arg0);
    func_841155B0(arg0);
    func_841126C8((s32)arg0);
    *(s16 *)(arg0 + 0x7E8) = 0;
    func_8411FEE8(0x258);
    if (*(s16 *)(D_841911E0 + 0x98) != 0x21) {
        *(s16 *)(D_841911E0 + 0x98) = 0;
        func_84111348((s32)arg0, 3);
    }
    func_84111E50(arg0, *(s8 *)(arg0 + 0x617));
    func_84111D64(arg0, *(s8 *)(arg0 + 0x616));
    func_84111E80((void *)arg0, 0);
    func_84111DB4(arg0, 0);
    func_80030420(func_8411E1F8((s32)arg0) & 0xFF, 0x13, *(s16 *)(arg0 + 0x1A), 4);
    *(u8 *)(arg0 + 0x7F6) = 0;
    *(s32 *)(arg0 + D_841911F4 * 4 + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_841156D0.s")
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84112158(s32, s32);
extern void func_8411FEE8(s32);
void func_841157D8(s32 arg0) {
    s16 var_v0;

    var_v0 = *(s16 *)((u8 *)(u32)arg0 + 0x7E8);
    if (var_v0 == 1) {
        *(s16 *)(D_841911E0 + 0x98) = 8;
        func_84111348(arg0, 0xF);
        var_v0 = *(s16 *)((u8 *)(u32)arg0 + 0x7E8);
    }
    if (var_v0 == 0x1E) {
        func_8411FEE8(0);
    }
    if (ModelAnim_IsFinished(arg0) != 0) {
        func_84112158(arg0, 0x106);
    }
}
#endif

#ifdef VERSION_US
extern void func_841156D0(s32);
extern void func_841157D8(s32);
void BattleAnim_Dispatch_045(s32 arg0) {
    s8 temp_v0;

    if (func_841133EC(arg0) == 0) {
        if ((*(u8 *)((u8 *)(arg0) + (0x618))) == 0x13) {
            func_841139D0(func_8411E164(arg0));
        }
        temp_v0 = (*(s8 *)((u8 *)(arg0) + (0x7F6)));
        switch (temp_v0) {                          /* irregular */
        case 0:
            func_841156D0(arg0);
            return;
        case 1:
            func_841157D8(arg0);
            break;
        }
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_050(u8 *arg0) {
    (*(s8 *)((u8 *)(arg0) + (0x618))) = 0x5B;
    func_84111C44();
    func_841134A0(arg0);
    func_8411FEE8(0x258);
    (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 5;
    (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
void func_84115940(u8 *arg0) {
    if (!((*(u16 *)((u8 *)(arg0) + (0x7EC))) & 1)) {
        (*(s16 *)((u8 *)(D_841911E0) + (0x98))) = 0x10;
        (*(s8 *)((u8 *)(arg0) + (0x61F))) = 5;
        BattleAnim_ApplyAnimationRecord(arg0, 0x102);
    }
}
#endif

#ifdef VERSION_US
extern f32 func_8411E1B4(u8 *);
extern void func_84111D64(u8 *arg0, s32 arg1);
extern void func_8411EE74();
void func_84115988(u8 *arg0) {
    if (ModelAnim_IsFinished(arg0)) {
        func_84111E50(arg0, *(s8 *)(*(u8 **)(arg0 + 0x2D4) + 0x139D));
        func_84111D64(arg0, *(u8 *)(*(u8 **)(arg0 + 0x2D4) + 0x139C));
    }
    if (*(f32 *)(arg0 + 0x28) <= -func_8411E1B4(arg0) * 3.0f) {
        arg0[2] &= ~2;
        func_8411EE74(arg0);
        arg0[0x7F6] = 3;
        *(s16 *)(arg0 + 0x7E8) = 0;
    }
}
#endif

#ifdef VERSION_US
void func_84115A24(void *arg0)
{
  if (ModelAnim_IsFinished() != 0)
  {
    *((u8 *) (((u8 *) arg0) + 2)) = (u8) ((*((u8 *) (((u8 *) arg0) + 2))) & 0xFFFD);
    *((s8 *) (((u8 *) arg0) + 0x7F6)) = 3;
    *((s16 *) (((u8 *) arg0) + 0x7E8)) = 0;
  }
  if (arg0)
  {
  }
}
#endif

#ifdef VERSION_US
extern void func_80030420(s32, u8, s16, s32);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_841126C8(s32 arg0);
extern s32 func_84113430(s32 arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern u8 * D_841911E0;
extern s32 D_841911F4;
void BattleAnim_Dispatch_051(u8 *arg0) {
    if (func_84113430((s32)arg0) == 0) return;
    func_84112EAC((void *)arg0);
    func_84115940(arg0);
    func_841126C8((s32)arg0);
    *(s16 *)(arg0 + 0x7E8) = 0;
    func_8411FEE8(0x258);
    *(u8 *)(arg0 + 0x7F6) = 0;
    if (*(s16 *)(D_841911E0 + 0x98) != 0x21) {
        *(s16 *)(D_841911E0 + 0x98) = 0;
        func_84111348((s32)arg0, 0);
    }
    func_84112218(arg0, 0xFB, *(u16 *)(*(s32 *)(arg0 + 0x44) + 0xA) - 0xF);
    func_80030420(func_8411E1F8((s32)arg0) & 0xFF, 0x5B, *(s16 *)(arg0 + 0x1A), 4);
    *(s32 *)(arg0 + D_841911F4 * 4 + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84115B34.s")
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_106(u8 *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 5;
    (*(s8 *)((u8 *)(arg0) + (0x618))) = 0x5B;
    func_84111C44();
    func_841134A0(arg0);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern u8 * D_841911E0;
void func_84115D4C(u8 *arg0) { if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) { s32 index = (s32)arg0[0x618] - 1; *(s16 *)(D_841911E0 + 0x98) = 14; *(u8 *)(arg0 + 0x61F) = 255; BattleAnim_ApplyAnimationRecord(arg0, index); } }
#endif

#ifdef VERSION_US
extern void func_84108A10(u8 *);
void func_84115D98(u8 *arg0) {
    s16 temp_v0;

    temp_v0 = (*(s16 *)((u8 *)(arg0) + (0x1A)));
    if ((temp_v0 == 0x32) || (temp_v0 == 0x33)) {
        if (ModelAnim_IsFinished(arg0) != 0) {
            func_84108A10(arg0);
            func_84111BEC(arg0);
            (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
        }
    } else if ((*(s16 *)((u8 *)(arg0) + (0x7E8))) == 0x19) {
        func_84108A10(arg0);
        func_84111BEC(arg0);
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
    }
}
#endif

#ifdef VERSION_US
extern void func_80030420(s32, u8, s16, s32);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s32 arg1);
extern void func_841126C8(s32 arg0);
extern s32 func_84113430(s32 arg0);
extern void func_84115D4C(u8 *arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern u8 * D_841911E0;
extern s32 D_841911F4;
void BattleAnim_Dispatch_107(u8 *arg0) {
    if (func_84113430((s32)arg0) == 0) {
        return;
    }
    func_84115D4C(arg0);
    func_841126C8((s32)arg0);
    *(s16 *)(arg0 + 0x7E8) = 0;
    func_8411FEE8(0x258);
    if (*(s16 *)(D_841911E0 + 0x98) != 0x21) {
        func_84111348((s32)arg0, 6);
    }
    func_84111E50(arg0, arg0[0x617]);
    func_84111D64(arg0, *(s8 *)(arg0 + 0x616));
    func_84111DB4(arg0, arg0[0x61B]);
    func_84111E80(arg0, 0);
    func_80030420(func_8411E1F8((s32)arg0) & 0xFF, 0x5B, *(s16 *)(arg0 + 0x1A), 0);
    arg0[0x7F6] = 0;
    *(s32 *)(arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_800231A0(short, s16, s32, ...);
extern void func_84108728(u8, void *, s32);
extern void func_84115D98(u8 *arg0);
void BattleAnim_Dispatch_108(u8 *arg0) {
    s32 result;
    if (func_841133EC((s32)arg0) != 0) return;
    if (*(s8 *)(arg0 + 0x7F6) != 0) return;
    if (*(s16 *)(arg0 + 0x7E8) == 2) {
        if ((*(s16 *)(arg0 + 0x1A) != 0x32) && (*(s16 *)(arg0 + 0x1A) != 0x33)) {
            result = func_8411E164((s32)arg0);
            func_84108728(*(u8 *)(arg0 + 0x618), arg0, result);
        }
        func_800231A0(*(u8 *)(arg0 + 0x618), *(s16 *)(arg0 + 0x658), 0);
        func_84112564((s32)arg0);
        *(u16 *)(arg0 + 0x7F4) &= 0xFFEF;
    }
    func_84115D98(arg0);
}
#endif

#ifdef VERSION_US
extern void func_84111C44(void);
extern void func_841134A0(u8 *arg0);
extern s32 D_84183D50;
extern s32 D_841911F4;
extern u8 * D_84193DD0;
void BattleAnim_Dispatch_057(u8 *arg0) {
    *((u8 *) (((u8 *) arg0) + 0x618)) = (u8) (*((u8 *) (((u8 *) D_84193DD0) + 8)));
    *((s16 *) (((u8 *) arg0) + 0x7E8)) = 0;
    *((s8 *) (((u8 *) arg0) + 0x7F6)) = 5;
    func_84111C44();
    func_841134A0(arg0);
    *((s32 *) (((u8 *) (arg0 + (D_841911F4 * 4))) + 0x5C8)) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern u16 D_84185196;
extern u16 D_8418519E;
extern u16 D_841851A6;
extern u16 D_841851AE;

/* mkdraft:func_84116010 begin */
extern u16 D_84185196;
extern u16 D_8418519E;
extern u16 D_841851A6;
extern u16 D_841851AE;



void func_84116010(u8 *arg0) {
    s32 index;

    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        if (*(u16 *)(D_84193DD0 + 4) == 0x16) {
            index = 0xFF;
        }
        if (*(u16 *)(D_84193DD0 + 4) == 0x17) {
            index = 0x101;
        }
        if (*(u16 *)(D_84193DD0 + 4) == 0x18) {
            index = 0x103;
        }
        if (*(u16 *)(D_84193DD0 + 4) == 0x19) {
            index = 0x104;
        }
        if (*(u16 *)(D_84193DD0 + 4) == 0x16) {
            BattleAnim_SelectCameraPreset(D_841911E0, D_84185196);
        }
        if (*(u16 *)(D_84193DD0 + 4) == 0x17) {
            BattleAnim_SelectCameraPreset(D_841911E0, D_8418519E);
        }
        if (*(u16 *)(D_84193DD0 + 4) == 0x18) {
            BattleAnim_SelectCameraPreset(D_841911E0, D_841851A6);
        }
        if (*(u16 *)(D_84193DD0 + 4) == 0x19) {
            BattleAnim_SelectCameraPreset(D_841911E0, D_841851AE);
        }
        *(u8 *)(arg0 + 0x61F) = 0xFF;
        BattleAnim_ApplyAnimationRecord(arg0, index);
    }
}
/* mkdraft:func_84116010 end */
#endif

#ifdef VERSION_US
extern void func_84116010(u8 *);
extern void func_80030420(s32, u8, s16, s32);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s32 arg1);
extern void func_841126C8(s32 arg0);
extern s32 func_84113430(s32 arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern u8 * D_841911E0;
extern s32 D_841911F4;
void BattleAnim_Dispatch_058(u8 *arg0) {
    if (func_84113430((s32)arg0) == 0) return;
    func_84112EAC((void *)arg0);
    func_841126C8((s32)arg0);
    func_84116010(arg0);
    if (*(s16 *)(D_841911E0 + 0x98) != 0x21) func_84111348((s32)arg0, 0);
    func_84111E50(arg0, *(s8 *)(arg0 + 0x617));
    func_84111D64(arg0, *(s8 *)(arg0 + 0x616));
    func_84111DB4(arg0, *(u8 *)(arg0 + 0x61B));
    func_84111E80((void *)arg0, 0);
    if (*(u8 *)(arg0 + 0x61A) == 0) {
        *(s16 *)(arg0 + 0x7E8) = *(u8 *)(arg0 + 0x61B) - 1;
        func_8411FEE8(0x258);
    } else {
        *(s16 *)(arg0 + 0x7E8) = *(u8 *)(arg0 + 0x61B);
        func_8411FEE8(0x258);
    }
    func_80030420(func_8411E1F8((s32)arg0) & 0xFF, *(u8 *)(arg0 + 0x618), *(s16 *)(arg0 + 0x1A), 4);
    *(u8 *)(arg0 + 0x7F6) = 0;
    *(s32 *)(arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_841088CC();
extern void func_8003F4E8();
extern void func_800231A0(short, s16, s32, ...);
extern void func_8410B578(f32 arg0);
extern void func_84112158(s32 arg0, s32 arg1);
extern void func_84112564(s32 arg0);
extern s32 func_8411E164();
extern void func_8411FEE8(s32);
extern void func_841206D0(u8 *);
extern u8 * D_841911E0;
extern u8 * D_84193DD0;
void func_84116248(s32 arg0) {
    u8 *a = (u8 *)arg0;
    if (a[0x619] == *(s16 *)(a + 0x7E8)) {
        func_84112564(arg0);
        func_841088CC(a[0x618], a, func_8411E164(arg0));
        if (*(s16 *)(D_841911E0 + 0x98) == 4) {
            *(f32 *)(D_841911E0 + 0x88) = 60.0f;
        }
        func_8410B578(0.0f);
        if (D_84193DD0[8] == 0x59) {
            func_8410B578(45.0f);
        }
        if (D_84193DD0[8] == 0x6A) {
            func_8003F4E8(a, 1);
        }
        func_800231A0(a[0x618], *(s16 *)(a + 0x658), 4);
    }
    if (a[0x61A] == 0) {
        if (ModelAnim_IsFinished(a)) {
            func_8411FEE8(0);
            func_841206D0(a);
            *(s16 *)(a + 0x7E8) = 0;
            a[0x7F6] = 1;
        }
    } else {
        if (ModelAnim_IsFinished(a)) {
            func_84112158(arg0, 0xFB);
        }
        if (a[0x61A] == *(s16 *)(a + 0x7E8)) {
            func_8411FEE8(0);
            func_841206D0(a);
            *(s16 *)(a + 0x7E8) = 0;
            a[0x7F6] = 1;
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_84112158(s32, s32);
void BattleAnim_Dispatch_059(s32 arg0) {
    extern void func_84116248(s32);

    if (func_841133EC(arg0) == 0) {
        s8 temp_v0 = *(s8 *)((u8 *)arg0 + 0x7F6);
        switch (temp_v0) {
        case 0:
            func_84116248(arg0);
            return;
        case 1:
            if (ModelAnim_IsFinished(arg0) != 0) {
                func_84112158(arg0, 0xFB);
            }
            break;
        }
    }
}
#endif

#ifdef VERSION_US
void func_84116410(u8 *arg0) {
    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        s32 index = arg0[0x618] - 1;
        arg0[0x616] = *(u8 *)(*(u8 **)(arg0 + 0x2D4) + (index * 0x14));
        BattleAnim_ApplyAnimationRecord(arg0, index);
    }
}
#endif

#ifdef VERSION_US
extern s32 func_8006456C(s32);
extern void func_84108A10(u8 *);
extern void func_841126C8(s32 arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern s32 D_841911F4;
extern u8 * D_84193DD0;
void func_84116460(u8 *arg0) {
    f64 reservation;
    u8 index;
    s32 value;

    arg0[0x618] = D_84193DD0[8];
    *(s16 *)(arg0 + 0x7E8) = 0;
    arg0[0x7F6] = 0;
    func_8411FEE8(0x258);
    *(u16 *)(arg0 + 0x65C) = *(u16 *)(((u8 (*)[0x10])D_84193DD0)[func_8411E1F8(arg0)] + 0xC);
    index = func_8411E1F8(arg0);
    value = func_8006456C(*(u16 *)(((u8 (*)[0x10])D_84193DD0)[func_8411E1F8(arg0)] + 0x14));
    func_84112FD0(*(u8 **)(arg0 + 0x5C0), *(u16 *)(arg0 + 0x65C), *(F12State *)(((u8 (*)[0x10])D_84193DD0)[index] + 0x18), value);
    func_84108A10(arg0);
    func_841126C8((s32)arg0);
    *(s32 *)(arg0 + D_841911F4 * 4 + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern u8 D_841849B6[];
extern void BattleAnim_SelectCameraPreset(u8 *, u16);
extern s32 func_800427B8(s32);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84111C44(void);
extern void func_841126C8(s32 arg0);
extern void func_84112EDC(u8 *);
void BattleAnim_Dispatch_156(u8 *arg0) {
    func_841139D0(func_8411E164((s32)arg0));
    if (func_800427B8(*(s32 *)(arg0 + 0x5C0)) != 0) {
        func_841126C8((s32)arg0);
        func_84111C44();
        func_84112EAC(arg0);
        func_84112EDC(arg0);
        func_84116410(arg0);
        *(u8 *)(arg0 + 0x7F6) = 1;
        *(s16 *)(arg0 + 0x7E8) = 0;
        BattleAnim_SelectCameraPreset(D_841911E0,
            *(u16 *)((u8 *)D_841849B6 + (*(u8 *)(arg0 + 0x618) << 3)));
        func_84111348((s32)arg0, 0);
        *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern void func_80030420(s32, u8, s16, s32);
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s32 arg1);
extern void func_84112564(s32);
extern s32 func_84113430(s32 arg0);
extern void func_8411FEE8(s32);
void func_84116604(u8 *arg0) {
    if (func_84113430((s32)arg0) != 0) {
        func_84111E50(arg0, *(s8 *)(arg0 + 0x617));
        func_84111D64(arg0, *(s8 *)(arg0 + 0x616));
        func_84111E80(arg0, *(u8 *)(arg0 + 0x61B));
        func_84111DB4(arg0, *(u8 *)(arg0 + 0x61B));
        if (*(u8 *)(arg0 + 0x61A) == 0) {
            *(s16 *)(arg0 + 0x7E8) = *(u8 *)(arg0 + 0x61B) - 1;
            func_8411FEE8(0x258);
        } else {
            *(s16 *)(arg0 + 0x7E8) = *(u8 *)(arg0 + 0x61B);
            func_8411FEE8(0x258);
        }
        func_84112564((s32)arg0);
        *(u8 *)(arg0 + 0x7F6) = 3;
        func_80030420(func_8411E1F8((s32)arg0) & 0xFF, *(u8 *)(arg0 + 0x618), *(s16 *)(arg0 + 0x1A), 0);
    }
}
#endif

#ifdef VERSION_US
extern void func_800231A0(short, s16, s32, ...);
extern void func_84108728(u8, void *, s32);
extern void func_8410B578(f32 arg0);
extern void func_84112158(s32 arg0, s32 arg1);
extern s32 func_8411E164();
extern void func_8411FEE8(s32);
extern void func_841206D0(u8 *);
extern u8 * D_841911E0;
extern u8 * D_84193DD0;
void func_841166C4(u8 *arg0) {
    if (*(u8 *)(arg0 + 0x619) == *(s16 *)(arg0 + 0x7E8)) {
        u8 *state = D_841911E0;
        if (*(s16 *)(state + 0x98) == 4) *(f32 *)(state + 0x88) = 60.0f;
        func_8410B578(0.0f);
        if ((D_84193DD0[9] & 7) == 1) func_800231A0(arg0[0x618], *(s16 *)(arg0 + 0x658), 2);
        else func_800231A0(arg0[0x618], *(s16 *)(arg0 + 0x658), 0);
        func_84108728(arg0[0x618], arg0, func_8411E164(arg0));
    }
    if (arg0[0x61A] == 0) {
        if (ModelAnim_IsFinished(arg0) != 0) {
            func_841206D0(arg0);
            *(s16 *)(arg0 + 0x7E8) = 0;
            arg0[0x7F6] = 4;
            func_8411FEE8(0);
        }
    } else {
        if (ModelAnim_IsFinished(arg0) != 0) func_84112158(arg0, 0xFB);
        if (arg0[0x61A] == *(s16 *)(arg0 + 0x7E8)) {
            func_841206D0(arg0);
            *(s16 *)(arg0 + 0x7E8) = 0;
            arg0[0x7F6] = 4;
            func_8411FEE8(0);
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_841166C4(u8 *);
extern void BattleAnim_SetAnimationAndFrame(u8 *, s32, s32, s32);
extern void func_84116604(u8 *arg0);
extern u8 * D_84193DD0;
void func_84116808(u8 *arg0) {
    switch (*(s8 *)(arg0 + 0x7F6)) {
        case 1:
            arg0[0x618] = D_84193DD0[8];
            *(s16 *)(arg0 + 0x7EA) = 0;
            arg0[0x7F6] = 2;
            break;
        case 2:
            func_84116604(arg0);
            break;
        case 3:
            func_841166C4(arg0);
            break;
        case 4:
            BattleAnim_SetAnimationAndFrame(arg0, *(s8 *)(arg0 + 0x616), *(s8 *)(arg0 + 0x617), arg0[0x61A]);
            break;
    }
}
#endif

#ifdef VERSION_US
extern u32 func_8003570C(void);
void func_841168A0(u8 *arg0) {
    extern u16 D_84183BDC[6];
    extern u32 func_8003570C(void);
    s32 sp1C;

    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        sp1C = *(u8 *)(arg0 + 0x618) - 1;
        *(u16 *)(D_841911E0 + 0x98) =
            *(u16 *)((u8 *)&D_84183BDC +
                ((func_8003570C() % 6) * 2));
        *(u8 *)(arg0 + 0x61F) = 0xFF;
        BattleAnim_ApplyAnimationRecord(arg0, sp1C);
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_113(u8 *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 5;
    (*(s8 *)((u8 *)(arg0) + (0x618))) = 1;
    func_841136E8(arg0);
    func_84111C44();
    func_841134A0(arg0);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s32 arg1);
extern void func_841126C8(s32 arg0);
extern s32 func_84113430(s32 arg0);
extern void func_841168A0(u8 *arg0);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_114(u8 *arg0) {
    if (func_84113430((s32)arg0) != 0) {
        func_84112EAC(arg0);
        *(u8 *)(arg0 + 0x7F6) = 0;
        func_841168A0(arg0);
        func_841126C8((s32)arg0);
        func_84111348((s32)arg0, 0);
        func_84111E50(arg0, *(s8 *)(arg0 + 0x617));
        func_84111D64(arg0, *(s8 *)(arg0 + 0x616));
        func_84111E80(arg0, 0);
        func_84111DB4(arg0, *(u8 *)(arg0 + 0x61B));
        *(s16 *)(arg0 + 0x7E8) = *(u8 *)(arg0 + 0x61B);
        func_8411FEE8(0x258);
        func_84112564((s32)arg0);
        *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern void func_8411FEE8(s32);
extern void func_841206D0(u8 *);
void func_84116A3C(u8 *arg0) {
    if (arg0[0x61A] == 0) {
        if (ModelAnim_IsFinished((void *)arg0)) {
            func_8411FEE8(0);
            func_841206D0(arg0);
            *(s16 *)(arg0 + 0x7E8) = 0;
            arg0[0x7F6] = 1;
        }
    } else if (arg0[0x61A] == *(s16 *)(arg0 + 0x7E8)) {
        func_841206D0(arg0);
        *(s16 *)(arg0 + 0x7E8) = 0;
        arg0[0x7F6] = 1;
        func_8411FEE8(0);
    }
}
#endif

#ifdef VERSION_US
s32 func_841133EC(s32 arg0);
void func_84116A3C(u8 *arg0);
s32 func_841133EC(s32);
void func_84116A3C(u8 *);

void func_84116AC4(void *arg0)
{
  if ((func_841133EC(arg0) == 0) && ((*((s8 *) (((u8 *) arg0) + 0x7F6))) == 0))
  {
    if ((*((u8 *) (((u8 *) arg0) + 0x619))) == (*((s16 *) (((u8 *) arg0) + 0x7E8))))
    {
      func_84108728(*((u8 *) (((u8 *) arg0) - -0x618)), arg0, func_8411E164(arg0));
      func_800231A0(0x12C, *((s16 *) (((u8 *) arg0) + 0x658)), 0);
    }
    func_84116A3C(arg0);
  }
}

extern s32 func_8411E164();
extern s32 func_8411E164();
extern s32 func_8411E164(s32 arg0);
extern s32 func_8411E164();
extern s32 func_8411E164(s32 arg0);
extern s32 func_8411E164(s32 arg0);
extern void func_800231A0(short, s16, s32, ...);
extern void func_84108728(u8, void *, s32);
extern s32 func_8411E164();
extern void func_84108728(u8, void *, s32);
extern s32 func_8411E164();
extern s32 func_8411E164(s32 arg0);
#endif

#ifdef VERSION_US
extern void func_8411FEE8(s32);
extern u8 D_841911F8;
extern u8 * D_84193DD0;
void func_84116B40(u8 *arg0, s16 arg1) {
    arg0[0x61A] = arg1;
    if (D_84193DD0[9] & 0x10) {
        if (arg0[0x61A] - arg0[0x620] < 40) {
            arg0[0x61A] += 40 - (arg0[0x61A] - arg0[0x620]);
        }
    }
    if (*(s8 *)(arg0 + 0x619) <= 0) {
        *(s16 *)(arg0 + 0x7E8) = *(s8 *)(arg0 + 0x619) - 1;
    }
    func_8411FEE8(0x258);
    D_841911F8 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84116BC0.s")
#endif

#ifdef VERSION_US
extern void func_84116B40(u8 *, s16);
extern void func_841120AC(u8 *arg0, s32 arg1, s32 arg2);
extern void func_84112158(s32 arg0, s32 arg1);
extern u8 * D_84193DD0;
void func_84116EB4(u8 *arg0) { s16 height; s32 timer; if (*(s8 *)(arg0 + 0x619) <= 0) timer = *(s8 *)(arg0 + 0x619) - 1; func_84112158(arg0, 0xFE); height = *(s16 *)(*(u8 **)(arg0 + 0x44) + 0xA); if (timer < 0) func_841120AC(arg0, 0xFB, -timer); else func_841120AC(arg0, 0xFB, *(s16 *)(arg0 + 0x7E8)); if (height < 0x50) height = 0x50; if ((D_84193DD0[9] & 7) == 2 || (D_84193DD0[9] & 7) == 5) height = (s16)0x3C; func_84116B40(arg0, height); }
#endif

#ifdef VERSION_US
extern void func_84111C6C(void);
extern void func_841134A0(u8 *arg0);
extern void func_841134D8(u8 *arg0);
extern s32 D_841839E0[];
void BattleAnim_BeginMoveAnimation(u8 *arg0) {
    func_8411FEE8(300);
    if (*(u16 *)(D_84193DD0 + 4) == 16 || *(u16 *)(D_84193DD0 + 4) == 20 || *(u16 *)(D_84193DD0 + 4) == 75) {
        arg0[1560] = 1;
    } else {
        arg0[1560] = D_84193DD0[8];
    }
    if (*(u16 *)(D_84193DD0 + 4) != 18 && *(u16 *)(D_84193DD0 + 4) != 19 && *(u16 *)(D_84193DD0 + 4) != 17) {
        if (D_84193DD0[8] == 18 || D_84193DD0[8] == 46) {
            func_84108A10(arg0);
        }
    }
    func_84111C6C();
    if (*(u16 *)(arg0 + 2028) & 1) {
        func_841134A0(arg0);
    } else {
        func_841134D8(arg0);
    }
    if (func_8411DC80(arg0[1560], D_841839E0, 10) != 0) {
        arg0[2] |= 2;
    }
    *(s32 *)(arg0 + D_841911F4 * 4 + 1480) = D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_841170A0.s")
#endif

#ifdef VERSION_US
void func_841175D4(s32 arg0) {
    extern f32 func_8413D358(s32);
    extern u8 D_841911F8;
    s32 temp_v0;

    if ((func_8413D358(func_8411E1F8(arg0) & 0xFF) == 0.0f) &&
        (D_841911F8 == 0)) {
        temp_v0 = *(s16 *)((u8 *)(u32)arg0 + 0x7E8) + 0x32;
        if (temp_v0 < (s32)*(u8 *)((u8 *)(u32)arg0 + 0x61A)) {
            *(u8 *)((u8 *)(u32)arg0 + 0x61A) = (u8)temp_v0;
        }
        D_841911F8 = 1;
    }
}
#endif

#ifdef VERSION_US
extern void func_84111BEC(u8 *arg0);
void func_84117648(u8 *arg0) {
    s32 state;
    func_841175D4((s32)arg0);
    state = *(u8 *)(arg0 + 0x61A);
    if (state == 0xF) {
        if (*(s16 *)(arg0 + 0x7E8) == state) {
            func_84111BEC(arg0);
            *(s16 *)(arg0 + 0x7E8) = 0x12C;
            arg0[0x7F6] = 1;
        }
    } else if (*(s16 *)(arg0 + 0x7E8) == state) {
        *(u16 *)(arg0 + 0x7F4) &= 0xFFFE;
        *(u16 *)(arg0 + 0x7F4) &= 0xFFFD;
        func_84111BEC(arg0);
        *(s16 *)(arg0 + 0x7E8) = 0x12C;
        arg0[0x7F6] = 1;
    }
}
#endif

#ifdef VERSION_US
extern void func_80023A3C(s32, s32, s32);
extern void func_8410890C(s32, s32);
void func_841176E0(void *arg0) {
    if (((*(s16 *)((u8 *)(arg0) + (0x7E8))) == (*(u8 *)((u8 *)(arg0) + (0x619)))) && ((*(u8 *)((u8 *)(D_84193DD0) + (9))) & 0x10)) {
        func_80023A3C(0x10, 0, 0);
        func_8410890C(0xFD, (s32) arg0);
    }
}
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern u8 * D_841911E0;
extern u16 D_84183C6C[];
void BattleAnim_UpdateMoveFramesAndCamera(u8 *arg0) {
    if (arg0[1560] == 199) arg0[1562] = 120;
    if (arg0[1560] == 205) arg0[1562] = 90;
    if (arg0[1560] == 18) arg0[1562] = 50;
    if (arg0[1560] == 46) arg0[1562] = 50;
    if (arg0[1560] == 180) arg0[1562] = 120;
    if (arg0[1560] == 193) {
        arg0[1562] = 80;
        arg0[1561] = 0;
        if (*(s16 *)(arg0 + 2024) % 12 == 0) {
            if (*(s16 *)(arg0 + 2024) < 37) {
                *(s16 *)(D_841911E0 + 152) = D_84183C6C[*(s16 *)(arg0 + 2024) / 12];
                func_84111348((s32)arg0, 1);
            }
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_8410B578(f32 arg0);
extern u8 * D_84193DD0;
void func_84117880(u8 *arg0) {
    if ((s8)arg0[0x619] + 1 != *(s16 *)(arg0 + 0x7E8)) return;
    if ((D_84193DD0[9] & 7) == 2) func_8410B578(10.0f);
    if ((D_84193DD0[9] & 7) == 0) func_8410B578(15.0f);
    if ((D_84193DD0[9] & 7) == 3) func_8410B578(20.0f);
    if ((D_84193DD0[9] & 7) == 4) func_8410B578(25.0f);
}
#endif

#ifdef VERSION_US
void func_84117948(s32 arg0) {
    s32 temp_v0;

    if ((*(u16 *)((u8 *)(D_84193DD0) + (4))) == 0xE) {
        func_84112158(arg0, 0xFE);
        return;
    }
    temp_v0 = (*(u8 *)((u8 *)(D_84193DD0) + (9))) & 7;
    if ((temp_v0 != 6) && ((*(u8 *)((u8 *)(arg0) + (0x618))) != 0xD4) && (temp_v0 != 2) && (temp_v0 != 5)) {
        func_84112158(arg0, 0xFE);
    }
}
#endif

#ifdef VERSION_US
extern void func_84111DB4(u8 *arg0, s32 arg1);
void func_841179C4(u8 *arg0) {
    extern void func_84111D64(u8 *, s32);
    s32 temp_v0;

    temp_v0 = D_84193DD0[9] & 7;
    if ((temp_v0 != 6) && (temp_v0 != 2) && (temp_v0 != 5)) {
        func_84111D64(arg0,
            *(u8 *)((u8 *)(u32)*(u32 *)(arg0 + 0x2D4) + 0x13D8));
        func_84111DB4(arg0, 0);
    }
}
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84120BB4(u8 *, s32);
void func_84117A24(u8 *arg0) {
    extern u8 *D_841911E0;

    if (((*(s8 *)(arg0 + 0x619) + 2) == *(s16 *)(arg0 + 0x7E8)) &&
        (*(u8 *)(arg0 + 0x618) == 0xC7)) {
        func_84120BB4(*(u8 **)D_841911E0, (s32)arg0);
        func_8410C934(*(u8 **)D_841911E0, (s32)arg0,
            *(s16 *)(D_841911E0 + 0x98));
        func_84111348((s32)arg0, 0x19);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84117AA0.s")
#endif

#ifdef VERSION_US
void func_84117C18(void *arg0)
{
  u8 temp_v0;
  ;
  if ((*((u8 *) (((u8 *) arg0) + 0x618))) == 0xD9)
  {
    if (((*((s8 *) (((u8 *) arg0) + 0x619))) + 0x39) == (*((s16 *) (((u8 *) arg0) + 0x7E8))))
    {
      func_84112564((s32) arg0);
    }
  }
  else
    if ((*((u8 *) (((u8 *) arg0) + 0x618))) == 0xCD)
  {
    if (((*((s8 *) (((u8 *) arg0) + 0x619))) + 0x13) == (*((s16 *) (((u8 *) arg0) + 0x7E8))))
    {
      func_84112564((s32) arg0);
    }
  }
  else
    if ((*((s8 *) (((u8 *) arg0) + 0x619))) == (*((s16 *) (((u8 *) arg0) + 0x7E8))))
  {
    func_84112564((s32) arg0);
  }
}
#endif

#ifdef VERSION_US
s32 func_84117CAC(void *arg0) {
    if (((*(s8 *)((u8 *)(arg0) + (0x619))) == (*(s16 *)((u8 *)(arg0) + (0x7E8)))) && (((*(u8 *)((u8 *)(D_84193DD0) + (9))) & 7) != 6)) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 D_84183A0C[];
extern void func_841087B8(s32 arg0, s32 arg1, s32 arg2);
extern void func_84112580(s32 arg0);
extern s32 func_841139D0(u8 *arg0);
extern void BattleAnim_UpdateMoveFramesAndCamera(u8 *);
extern void func_84117880(u8 *arg0);
extern void func_84117A24(u8 *arg0);
extern void func_84117AA0(u8 *);
extern void func_84117C18(void *arg0);
extern s32 func_84117CAC(void *arg0);
extern s32 func_8411DC80(u16, s32 *, s32);
extern s32 func_8411E164();
extern void func_8411FEE8(s32);
extern void func_841206D0(u8 *);
extern void func_84123F60(u8 *, s32);
void func_84117CEC(u8 *arg0) {
    u8 pad[8];
    BattleAnim_UpdateMoveFramesAndCamera(arg0);
    func_841139D0(arg0);
    if (func_84117CAC(arg0)) {
        if (func_8411DC80(arg0[0x618], D_84183A0C, 10) == 0) {
            func_841087B8(arg0[0x618], func_8411E164((s32)arg0), (s32)arg0);
        }
        func_84123F60(arg0, arg0[0x61F]);
        func_84117AA0(arg0);
    }
    func_84117880(arg0);
    func_84117C18(arg0);
    func_84117A24(arg0);
    if (*(s8 *)(arg0 + 0x619) + 10 == *(s16 *)(arg0 + 0x7E8)) {
        func_84112580((s32)arg0);
    }
    if (arg0[0x61A] == *(s16 *)(arg0 + 0x7E8)) {
        func_841206D0(arg0);
        func_8411FEE8(0);
    }
}
#endif

#ifdef VERSION_US
extern void func_841087B8(s32 arg0, s32 arg1, s32 arg2);
extern void func_84112158(s32 arg0, s32 arg1);
extern void func_84112580(s32 arg0);
extern void BattleAnim_UpdateMoveFramesAndCamera(u8 *);
extern void func_84117880(u8 *arg0);
extern void func_84117A24(u8 *arg0);
extern void func_84117AA0(u8 *);
extern void func_84117C18(void *arg0);
extern s32 func_84117CAC(void *arg0);
extern s32 func_8411E164();
extern void func_8411FEE8(s32);
extern void func_841206D0(u8 *);
void func_84117DC4(u8 *arg0) {
    u8 pad[8];
    BattleAnim_UpdateMoveFramesAndCamera(arg0);
    if (ModelAnim_IsFinished((void *)arg0)) {
        func_84112158((s32)arg0, 0x106);
    }
    if (func_84117CAC(arg0)) {
        func_841087B8(arg0[0x618], func_8411E164((s32)arg0), (s32)arg0);
        func_84123F60(arg0, arg0[0x61F]);
        func_84117AA0(arg0);
    }
    func_84117880(arg0);
    func_84117C18(arg0);
    func_84117A24(arg0);
    if (*(s8 *)(arg0 + 0x619) + 10 == *(s16 *)(arg0 + 0x7E8)) {
        func_84112580((s32)arg0);
    }
    if (arg0[0x61A] == *(s16 *)(arg0 + 0x7E8)) {
        func_841206D0(arg0);
        func_8411FEE8(0);
    }
}
#endif

#ifdef VERSION_US
extern void BattleAnim_UpdateMoveFramesAndCamera(u8 *arg0);
extern void func_80023A3C(s32, s32, s32);
extern void func_841087B8(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_84111C8C(u8 *);
extern void func_84111D64(u8 *arg0, s32 arg1);
extern void func_8411200C(u8 *arg0);
extern void func_84112218(u8 *, s32, s32);
extern void func_84112580(s32 arg0);
extern void func_84117648(u8 *arg0);
extern void func_841176E0(void *arg0);
extern void func_84117880(u8 *arg0);
extern void func_84117948(s32 arg0);
extern void func_841179C4(u8 *arg0);
extern void func_84117A24(u8 *arg0);
extern void func_84117AA0(u8 *);
extern void func_84117C18(void *arg0);
extern s32 func_84117CAC(void *arg0);
extern s32 func_8411E164();
extern void func_84124104(u8 *, s32);
extern u8 * D_84193DD0;
void BattleAnim_UpdateTimedMoveEvents(u8 *arg0) {
    BattleAnim_UpdateMoveFramesAndCamera(arg0);
    if (*(s16 *)(arg0 + 2024) == 0) {
        if (*(u16 *)(D_84193DD0 + 4) == 11) {
            if (func_84111C8C(arg0) != 0) {
                if (*(s16 *)(arg0 + 26) == 252) {
                    if ((D_84193DD0[9] & 7) != 2) func_841179C4(arg0);
                } else {
                    if ((D_84193DD0[9] & 7) != 2) func_8411200C(arg0);
                }
            } else {
                func_84112324(arg0);
                func_841179C4(arg0);
            }
        } else {
            func_84117948((s32)arg0);
        }
    }
    func_841176E0(arg0);
    if (func_84117CAC(arg0) != 0) {
        func_841087B8(arg0[1560], func_8411E164((s32)arg0), (s32)arg0);
        func_84123F60(arg0, arg0[1567]);
        switch (*(u16 *)(D_84193DD0 + 4)) {
        case 16: func_80023A3C(17, 0, 0); break;
        case 20: func_80023A3C(18, 0, 0); break;
        default: func_84117AA0(arg0); break;
        }
    }
    func_84117C18(arg0);
    func_84117A24(arg0);
    func_84117880(arg0);
    if (*(s16 *)(arg0 + 2024) >= *(s8 *)(arg0 + 1561) + 20 && arg0[1560] == 205) {
        if (*(s16 *)(arg0 + 1624) == 16 || *(s16 *)(arg0 + 1624) == 17 || *(s16 *)(arg0 + 1624) == 18) {
            func_84112218(arg0, 254, 1);
        } else if (*(s16 *)(arg0 + 26) == 101) {
            func_84111D64(arg0, 8);
        } else {
            func_84112218(arg0, 251, 1);
        }
    }
    if (*(s16 *)(arg0 + 2024) >= *(s8 *)(arg0 + 1561)) {
        func_84124104(arg0, arg0[1567]);
    }
    if (*(s8 *)(arg0 + 1561) + 10 == *(s16 *)(arg0 + 2024)) func_84112580((s32)arg0);
    if (ModelAnim_IsFinished(arg0) != 0) {
        func_84111D64(arg0, (*(u8 **)(arg0 + 724))[5020]);
        if (*(u16 *)(D_84193DD0 + 4) == 11) func_84112324(arg0);
    }
    func_84117648(arg0);
}
#endif

#ifdef VERSION_US
extern void BattleAnim_UpdateMoveFramesAndCamera(u8 *);
extern void func_841087B8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8410890C(s32, s32);
extern void func_84108E00(u8 *, s32);
extern void func_84112158(s32 arg0, s32 arg1);
extern void func_84117648(u8 *arg0);
extern void func_841176E0(void *arg0);
extern void func_84117880(u8 *arg0);
extern void func_84117AA0(u8 *);
extern s32 func_8411DC80(u16, s32 *, s32);
extern s32 func_8411E164(s32 arg0);
extern s32 D_84183A50[];
extern u8 * D_84193DD0;
void func_84118138(u8 *arg0) {
    BattleAnim_UpdateMoveFramesAndCamera(arg0);
    if (*(s16 *)(arg0 + 0x7E8) == 0) {
        func_84112158((s32)arg0, 0xFE);
    }
    if (func_84117CAC(arg0) != 0) {
        func_841087B8(arg0[0x618], func_8411E164((s32)arg0), (s32)arg0);
        func_84117AA0(arg0);
        func_80023A3C(9, 0, 0);
        *(u16 *)(arg0 + 0x7F4) |= 0x20;
    }
    func_84117880(arg0);
    func_84117C18(arg0);
    func_841176E0(arg0);
    if (*(s8 *)(arg0 + 0x619) + 10 == *(s16 *)(arg0 + 0x7E8)) {
        func_84112580((s32)arg0);
    }
    if (func_8411DC80(*(u16 *)(arg0 + 0x1A), D_84183A50, 10)) {
        if ((*(s32 *)(arg0 + 0x48) >> 16) == 0) func_84112464(arg0);
    } else if ((*(s32 *)(arg0 + 0x48) >> 16) == 6) func_84112464(arg0);
    if (*(s16 *)(arg0 + 0x7E8) == 8) func_8410890C(0xFE, (s32)arg0);
    if (*(s16 *)(arg0 + 0x7E8) == 9) {
        s32 i = func_8411E1F8((s32)arg0);
        if ((*(u16 *)((u8 *)D_84193DD0 + (i << 4) + 0x12) & 2) ||
            ((i = func_8411E1F8((s32)arg0)), (*(u16 *)((u8 *)D_84193DD0 + (i << 4) + 0x12) & 4))) func_84108E00(arg0, 1);
    }
    func_841139D0(arg0);
    func_84117648(arg0);
}
#endif

#ifdef VERSION_US
extern s32 D_84183A50[];
extern void func_8410890C(s32, s32);
extern void func_84108E00(u8 *, s32);
extern void func_84112158(s32 arg0, s32 arg1);
extern void func_84117648(u8 *arg0);
extern void func_84117AA0(u8 *);
extern s32 func_8411DC80(u16, s32 *, s32);
extern u8 * D_84193DD0;
void func_841182E0(u8 *a){s32 i;if(*(s16*)(a+0x7E8)==0)func_84112158((s32)a,0xFE);if(func_84117CAC(a)){func_84117AA0(a);func_80023A3C(9,0,0);*(u16*)(a+0x7F4)|=0x20;}func_84117C18(a);if(*(s8*)(a+0x619)+10==*(s16*)(a+0x7E8))func_84112580((s32)a);if(func_8411DC80(*(u16*)(a+0x1A),D_84183A50,10)){if((*(s32*)(a+0x48)>>16)==0)func_84112464(a);}else if((*(s32*)(a+0x48)>>16)==6)func_84112464(a);if(*(s16*)(a+0x7E8)==8)func_8410890C(0xFE,(s32)a);if(*(s16*)(a+0x7E8)==9){i=func_8411E1F8((s32)a);if((*(u16*)((u8*)D_84193DD0+(i<<4)+0x12)&2)||(i=func_8411E1F8((s32)a),(*(u16*)((u8*)D_84193DD0+(i<<4)+0x12)&4)))func_84108E00(a,1);}func_841139D0(a);func_84117648(a);}
#endif

#ifdef VERSION_US
extern void func_84124104(u8 *, s32);
extern void func_841087B8(s32 arg0, s32 arg1, s32 arg2);
extern void func_84112580(s32 arg0);
extern void func_84117648(u8 *arg0);
extern void func_841176E0(void *arg0);
extern void BattleAnim_UpdateMoveFramesAndCamera(u8 *);
extern void func_84117880(u8 *arg0);
extern void func_84117A24(u8 *arg0);
extern void func_84117AA0(u8 *);
extern void func_84117C18(void *arg0);
extern s32 func_84117CAC(void *arg0);
extern s32 func_8411E164();
void func_8411845C(u8 *arg0) {
    BattleAnim_UpdateMoveFramesAndCamera(arg0);
    if (func_84117CAC(arg0)) {
        func_84117880(arg0);
        func_841087B8(arg0[0x618], func_8411E164((s32)arg0), (s32)arg0);
        func_84117AA0(arg0);
        if (arg0[0x618] != 0xCD) {
            func_84123F60(arg0, arg0[0x61F]);
        }
    }
    func_84117880(arg0);
    func_84117A24(arg0);
    func_84117C18(arg0);
    if ((arg0[0x618] != 0xCD) && (*(s16 *)(arg0 + 0x7E8) >= *(s8 *)(arg0 + 0x619))) {
        func_84124104(arg0, arg0[0x61F]);
    }
    if (*(s8 *)(arg0 + 0x619) + 10 == *(s16 *)(arg0 + 0x7E8)) {
        func_84112580((s32)arg0);
    }
    func_841176E0(arg0);
    func_84117648(arg0);
}
#endif

#ifdef VERSION_US
extern void func_841087B8(s32, s32, s32);
extern void func_84117AA0(u8 *);
extern void func_84117880(u8 *);
extern void func_84108A10(u8 *);
extern void func_84111D64(u8 *, s32);
extern void func_84117648(u8 *);
extern void func_841176E0(void *arg0);
extern s32 func_8411E164(s32 arg0);
void func_8411854C(u8 *arg0) {
    if (func_84117CAC(arg0) != 0) {
        func_841087B8(arg0[0x618], func_8411E164((s32)arg0), (s32)arg0);
        func_84117AA0(arg0);
        *(u16 *)(arg0 + 0x7F4) &= 0xFFFD;
        func_8003EF70(arg0);
        arg0[2] |= 0x20;
        func_84108A10(arg0);
        *(u16 *)(arg0 + 0x7F4) &= 0xFFDF;
    }
    func_84117880(arg0);
    func_84117C18(arg0);
    func_841176E0(arg0);
    if (ModelAnim_IsFinished(arg0) != 0) {
        func_84111D64(arg0, (*(u8 **)(arg0 + 0x2D4))[0x139C]);
    }
    if (*(s8 *)(arg0 + 0x619) + 10 == *(s16 *)(arg0 + 0x7E8)) {
        func_84112580((s32)arg0);
    }
    func_84117648(arg0);
}
#endif

#ifdef VERSION_US
extern void BattleAnim_UpdateMoveFramesAndCamera(u8 *);
extern void func_841087B8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8410890C(s32, s32);
extern void func_84112158(s32 arg0, s32 arg1);
extern s32 func_84112418(u8 *arg0);
extern void func_84113920(u8 *arg0);
extern void func_84117648(u8 *arg0);
extern void func_841176E0(void *arg0);
extern void func_84117880(u8 *arg0);
extern void func_84117AA0(u8 *);
extern s32 func_8411E164(s32 arg0);
void func_8411862C(u8 *arg0) {
    BattleAnim_UpdateMoveFramesAndCamera(arg0);
    if (func_84117CAC(arg0) != 0) {
        func_841087B8(arg0[0x618], func_8411E164((s32)arg0), (s32)arg0);
        func_84112158((s32)arg0, 0x105);
        func_8410890C(0x100, (s32)arg0);
        func_80023A3C(0xC, *(s16 *)(arg0 + 0x1A), 0);
        func_84117AA0(arg0);
        *(u16 *)(arg0 + 0x7F4) |= 0x40;
    }
    func_84117880(arg0);
    func_84117C18(arg0);
    func_84112418(arg0);
    func_841176E0(arg0);
    if (*(s8 *)(arg0 + 0x619) + 10 == *(s16 *)(arg0 + 0x7E8)) {
        func_84112580((s32)arg0);
    }
    func_84113920(arg0);
    func_84117648(arg0);
}
#endif

#ifdef VERSION_US
void func_84118704(u8 *arg0) {
    extern void func_84117648(u8 *);

    if (*(s16 *)(arg0 + 0x7E8) == 0) {
        func_84112564((s32)arg0);
        func_841139D0(arg0);
    }
    func_841139D0(arg0);
    func_84117648(arg0);
}
#endif

#ifdef VERSION_US
extern void func_84117648(u8 *);

void func_84118754(u8 *arg0) {
    if ((*(s16 *)((u8 *)(arg0) + (0x7E8))) == 0) {
        func_84112564((s32) arg0);
        func_841139D0(arg0);
    }
    func_84117648(arg0);
}
#endif

#ifdef VERSION_US
extern s32 func_84112418(u8 *);
void func_84118794(u8 *arg0) {
    if ((*(s16 *)((u8 *)(arg0) + (0x7E8))) == 0) {
        func_84112564((s32) arg0);
        func_841139D0(arg0);
    }
    func_84112418(arg0);
    func_84117648(arg0);
}
#endif

#ifdef VERSION_US
extern s32 func_841133EC(s32 arg0);
extern void func_84117CEC(u8 *arg0);
extern void func_84117DC4(u8 *arg0);
extern void func_84118138(u8 *arg0);
extern void func_841182E0(u8 *a);
extern void func_8411845C(u8 *arg0);
extern void func_8411854C(u8 *arg0);
extern void func_8411862C(u8 *arg0);
extern void func_84118704(u8 *arg0);
extern void func_84118754(u8 *arg0);
extern void func_84118794(u8 *arg0);
extern u8 * D_84193DD0;
extern void BattleAnim_UpdateTimedMoveEvents(u8 *);
void BattleAnim_DispatchAnimationStart(u8 *arg0) {
    if (func_841133EC((s32)arg0) == 0 && *(s8 *)(arg0 + 2038) == 0) {
        switch (*(u16 *)(D_84193DD0 + 4)) {
        case 17: func_84118704(arg0); break;
        case 13: func_8411845C(arg0); break;
        case 14: func_84118138(arg0); break;
        case 18: func_84118754(arg0); break;
        case 12: func_8411862C(arg0); break;
        case 19: func_84118794(arg0); break;
        case 15:
        case 21: func_8411854C(arg0); break;
        case 59: func_841182E0(arg0); break;
        case 10:
            if (((u16 (*)[8])(D_84193DD0 + 16))[func_8411E1F8((s32)arg0)][1] & 4) {
                func_84117CEC(arg0);
            } else if (((u16 (*)[8])(D_84193DD0 + 16))[func_8411E1F8((s32)arg0)][1] & 2) {
                func_84117DC4(arg0);
            } else {
                BattleAnim_UpdateTimedMoveEvents(arg0);
            }
            break;
        case 75:
        default: BattleAnim_UpdateTimedMoveEvents(arg0); break;
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_84111C44(void);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_064(s32 arg0) {
    extern void func_8410B104(void);
    func_8410B104();
    func_84111C44();
    func_8411FEE8(0x50);
    *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    *(u8 *)((u8 *)arg0 + 0x7F6) = 1;
    *(s32 *)((u8 *)(arg0 + (D_841911F4 * 4)) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_841189EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84118C08.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_84118DD4.s")
#endif

#ifdef VERSION_US
extern void func_84111C44(void);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_197(s32 arg0) {
    func_84111C44();
    func_8411FEE8(0x50);
    *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    *(u8 *)((u8 *)arg0 + 0x7F6) = 1;
    *(s32 *)((u8 *)(arg0 + (D_841911F4 * 4)) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84103694(s32, s16);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84113560(s32 arg0);
extern void func_84113D38(u8 *arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern u8 * D_841911E0;
extern s32 D_841911F4;
extern s32 D_84191208;
extern s32 D_8419120C;
extern u8 * D_84193DD0;
extern u8 D_84193DD8[];
void BattleAnim_DispatchDelayedCategory(u8 *arg0) {
    if (*(s16 *)(arg0 + 2024) < 2) return;
    arg0[2038] = 2;
    func_8411FEE8(80);
    switch (*(u16 *)(D_84193DD0 + 4)) {
    case 49: func_84113560(262); break;
    case 52: func_84113560(289); break;
    case 50: func_84113560(263); break;
    case 53: func_84113560(287); break;
    case 54: func_84113560(268); break;
    case 48: func_84103694((s32)D_84193DD8, 275); break;
    case 51: func_84113560(288); break;
    }
    switch (*(u16 *)(D_84193DD0 + 4)) {
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
        func_84113D38((u8 *)D_84191208);
        func_84113D38((u8 *)D_8419120C);
        if (*(s16 *)(D_841911E0 + 152) != 33) {
            func_84111348((s32)arg0, 29);
        }
        break;
    }
    *(s32 *)(arg0 + D_841911F4 * 4 + 1480) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern s32 func_84113430(s32 arg0);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_199(u8 *arg0) {
    if (*(s8 *)(arg0 + 0x7F6) != 1) {
        if (func_84113430((s32)arg0) != 0) {
            *(s16 *)(arg0 + 0x7E8) = 0;
            func_8411FEE8(0x64);
            if (*(u16 *)(D_84193DD0 + 4) == 0x36) {
                func_84112EAC(arg0);
                func_84113D38(arg0);
                *(s16 *)(D_841911E0 + 0x98) = 0;
                func_84111348((s32)arg0, 0);
                func_84123F60(arg0, 0x17);
            }
            *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
        }
    }
}
#endif

#ifdef VERSION_US
/* mkdraft:func_84119630 begin */
extern u8 *D_84193DD0;
extern s32 D_84191208;
extern s32 D_8419120C;
extern s32 D_841911F4;
extern s32 D_84183D50;
extern s32 func_841133EC(s32);
extern void func_84112564(s32);
extern void func_84112580(s32);
extern void func_8410890C(s32, s32);
extern void func_80023A3C(s32, s32, s32);
extern void func_84124104(u8 *, s32);
extern void BattleAnim_Dispatch_002(u8 *);
extern void func_84111C1C(void);
extern void func_841206D0(u8 *);
extern void func_8411FEE8(s32);
extern void func_80024180(u32, s32);

void func_84119630(u8 *arg0) {
    if (*(s8 *)(arg0 + 0x7F6) == 1) {
        return;
    }
    if (func_841133EC((s32)arg0) != 0) {
        return;
    }
    if (*(s16 *)(arg0 + 0x7E8) == 2) {
        func_84112564((s32)arg0);
        func_84112580((s32)arg0);
        switch (*(u16 *)(D_84193DD0 + 4)) {
            case 0x31:
                func_8410890C(0x106, (s32)arg0);
                func_80023A3C(0x1A, 0, 0);
                break;
            case 0x34:
                func_8410890C(0x121, (s32)arg0);
                func_80023A3C(0x1A, 0, 0);
                break;
            case 0x32:
                func_8410890C(0x107, (s32)arg0);
                func_80023A3C(0x1B, 0, 0);
                break;
            case 0x35:
                func_8410890C(0x11F, (s32)arg0);
                func_80023A3C(0x29, 0, 0);
                break;
            case 0x30:
                func_8410890C(0x113, (s32)arg0);
                func_80023A3C(0x1C, 0, 0);
                break;
            case 0x33:
                func_8410890C(0x120, (s32)arg0);
                func_80023A3C(0x2A, 0, 0);
                break;
            case 0x36:
                func_80023A3C(0x17, 0, 0);
                func_8410890C(0x10C, (s32)arg0);
                break;
        }
    }
    if (*(u16 *)(D_84193DD0 + 4) == 0x36) {
        func_84124104(arg0, 0x17);
    }
    switch (*(u16 *)(D_84193DD0 + 4)) {
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
            BattleAnim_Dispatch_002((u8 *)D_84191208);
            BattleAnim_Dispatch_002((u8 *)D_8419120C);
            break;
        case 0x36:
            BattleAnim_Dispatch_002(arg0);
            break;
    }
    if (*(s16 *)(arg0 + 0x7E8) == 0x33) {
        if (*(u16 *)(D_84193DD0 + 4) == 0x36) {
            func_84111C1C();
        }
        *(u16 *)(arg0 + 0x7F4) &= ~1;
        *(u16 *)(arg0 + 0x7F4) &= ~2;
        func_841206D0(arg0);
        func_8411FEE8(0);
        switch (*(u16 *)(D_84193DD0 + 4)) {
            case 0x31:
            case 0x34:
                func_80024180(0x1A, 0);
                break;
            case 0x32:
            case 0x35:
                func_80024180(0x1B, 0);
                break;
            case 0x30:
            case 0x33:
                func_80024180(0x1C, 0);
                break;
        }
        *(s32 *)(arg0 + 0x5C8 + D_841911F4 * 4) = D_84183D50;
    }
}
/* mkdraft:func_84119630 end */
#endif

#ifdef VERSION_US
#ifdef CC_CHECK
#define CALL_FUNC_84111C8C(x) ((s32 (*)(u8 *))func_84111C8C)(x)
#else
#define CALL_FUNC_84111C8C(x) func_84111C8C(x)
#endif
void func_84119908(u8 *arg0) {
#ifndef CC_CHECK
    extern s32 func_84111C8C();
#endif
    struct {
        u8 *saved;
        s32 unused;
    } local;
    u8 *table;
    s32 index;

    table = *(u8 **)(arg0 + 0xC);
    local.saved = (*(u8 *(**)(s32, s32))(table + 0x2C))(0, 0);
    *(s16 *)(arg0 + 0x7E8) = 0;
    arg0[0x7F6] = 0;
    func_84111C44();
    func_841126C8((s32)arg0);
    func_8411FEE8(0x258);
    index = func_8411E1F8(arg0);

    if (*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12) & 4) {
        func_841139D0(arg0);
        *(s16 *)(D_841911E0 + 0x98) = 0;
        func_84111348((s32)arg0, 0);
        func_84108CE8(arg0);
        *(u16 *)(arg0 + 0x7F4) &= ~1;
        func_8003EF70(arg0);
        *(u16 *)(arg0 + 0x7F4) &= ~0x40;
        arg0[0x7F6] = 4;
        func_84112564((s32)arg0);
        func_84112580((s32)arg0);
    } else {
        func_84111348((s32)arg0, 7);
        func_84112158((s32)arg0, 0xFB);
        if (CALL_FUNC_84111C8C(arg0)) {
            func_841120AC(arg0, 0x105, 0x14);
        } else {
            func_84111E50(arg0, (*(u8 **)(arg0 + 0x2D4))[0x152D]);
            if (*(s8 *)(*(u8 **)(arg0 + 0x2D4) + 0x152D) < 0 || local.saved[5] <= 0) {
                func_841120AC(arg0, 0x105, 0x14);
            } else {
                func_841120AC(arg0, 0xFB, *(u16 *)(*(u8 **)(arg0 + 0x58) + 0xA) + 0x36);
            }
        }
        func_84112324(arg0);
    }
    *(s32 *)(arg0 + 0x5C8 + D_841911F4 * 4) = D_84183D50;
}
#undef CALL_FUNC_84111C8C
#endif

#ifdef VERSION_US
extern void func_84111BEC(u8 *arg0);
extern void func_84111D64(u8 *arg0, s32 arg1);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s32 arg1);
extern s32 func_84111FA4(void *arg0);
extern void func_84112564(s32 arg0);
extern void func_84112580(s32 arg0);
extern s32 func_841139D0(u8 *arg0);
extern s32 func_84111C8C(u8 *);
void BattleAnim_UpdateModelEventSequence(u8 *arg0) {
    switch (*(s8 *)(arg0 + 2038)) {
    case 0:
        if (*(s16 *)(arg0 + 2024) == 20) {
            *(u16 *)(arg0 + 2036) &= ~1;
            func_8003EF70(arg0);
            *(u16 *)(arg0 + 2036) &= ~0x40;
            func_84108CE8(arg0);
            if (func_84111C8C(arg0)) {
                func_84111D64(arg0, (*(u8 **)(arg0 + 724))[5420]);
                func_84111DB4(arg0, 0);
                arg0[2038] = 1;
            } else {
                func_84111E50(arg0, (*(u8 **)(arg0 + 724))[5421]);
                func_84111E80(arg0, 0);
                arg0[2038] = 1;
            }
        }
        break;
    case 1:
        if (func_84111C8C(arg0)) {
            if (ModelAnim_IsFinished(arg0)) {
                func_84111D64(arg0, (*(u8 **)(arg0 + 724))[5020]);
                func_84111DB4(arg0, 0);
                *(s16 *)(arg0 + 2024) = 0;
                arg0[2038] = 2;
                func_84112564((s32)arg0);
                func_84112580((s32)arg0);
            }
        } else {
            if (func_84111FA4(arg0)) {
                func_84111E50(arg0, (*(u8 **)(arg0 + 724))[5021]);
                func_84111E80(arg0, 0);
                *(s16 *)(arg0 + 2024) = 0;
                arg0[2038] = 2;
                func_84112564((s32)arg0);
                func_84112580((s32)arg0);
            }
        }
        break;
    case 2:
        if (*(s16 *)(arg0 + 2024) == 30) {
            func_84111BEC(arg0);
            arg0[2038] = 3;
        }
        break;
    case 4:
        func_841139D0(arg0);
        if (*(s16 *)(arg0 + 2024) == 60) {
            func_84111BEC(arg0);
            arg0[2038] = 5;
        }
        break;
    }
}
#endif

#ifdef VERSION_US
extern void func_8410B104();
void BattleAnim_Dispatch_120(s32 arg0) {
    func_8411FEE8(0x3E);
    func_84111C44();
    func_8410B104();
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84112158(s32 arg0, s32 arg1);
extern void func_84112464(u8 *arg0);
extern void func_84112564(s32 arg0);
extern void func_84112580(s32 arg0);
extern void func_841126C8(s32 arg0);
extern void func_84112E40(s32 arg0);
extern s32 func_84113430(s32 arg0);
extern s32 func_841139D0(u8 *arg0);
extern void func_84113D38(u8 *arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern u8 * D_841911E0;
extern s32 D_841911F4;
extern u8 * D_84193DD0;
void BattleAnim_InitializeCategorySequence(u8 *arg0) {
    if (func_84113430((s32)arg0) == 0) return;
    func_841126C8((s32)arg0);
    func_84112E40((s32)arg0);
    *(s16 *)(arg0 + 2024) = 0;
    func_8411FEE8(62);
    arg0[1562] = 60;
    *(s16 *)(D_841911E0 + 152) = 0;
    func_84111348((s32)arg0, 0);
    arg0[1567] = 255;
    switch (*(u16 *)(D_84193DD0 + 4)) {
    case 44:
        arg0[2038] = 0;
        if (((u16 (*)[8])(D_84193DD0 + 16))[func_8411E1F8((s32)arg0)][1] & 4) {
            func_841139D0(arg0);
        } else {
            func_84112464(arg0);
        }
        break;
    case 2:
        arg0[2038] = 0;
        func_84112464(arg0);
        break;
    case 3:
    case 5:
        func_84113D38(arg0);
        break;
    case 4:
        func_84112324(arg0);
        break;
    case 7:
        func_84112158((s32)arg0, 251);
        if (((u16 (*)[8])(D_84193DD0 + 16))[func_8411E1F8((s32)arg0)][1] & 2) {
            *(s16 *)(D_841911E0 + 152) = 37;
        } else {
            *(s16 *)(D_841911E0 + 152) = 36;
        }
        arg0[1562] = 35;
        func_8411FEE8(37);
        func_84113D38(arg0);
        break;
    case 8:
        arg0[1562] = 35;
        *(s16 *)(D_841911E0 + 152) = 36;
        func_84112324(arg0);
        func_8411FEE8(37);
        break;
    case 9:
        *(s16 *)(D_841911E0 + 152) = 38;
        arg0[1562] = 35;
        func_84112464(arg0);
        func_8411FEE8(37);
        break;
    }
    func_84112564((s32)arg0);
    func_84112580((s32)arg0);
    *(s32 *)(arg0 + D_841911F4 * 4 + 1480) = D_84183D50;
}
#endif

#ifdef VERSION_US
/* mkdraft:func_84119F24 begin */
void func_84119F24(u8 *arg0) {
    s16 val;
    s32 index;

    if (func_841133EC((s32)arg0) != 0) {
        return;
    }
    switch (*(u16 *)(D_84193DD0 + 4)) {
        case 0x2C:
            index = func_8411E1F8(arg0);
            if (*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12) & 4) {
                func_841139D0(arg0);
                *(u16 *)(arg0 + 0x7F4) &= ~2;
                func_84112290(arg0);
                func_84108CE8(arg0);
                *(u16 *)(arg0 + 0x7F4) &= ~0x20;
            } else {
                switch (*(s8 *)(arg0 + 0x7F6)) {
                    case 0:
                        if (*(s16 *)(arg0 + 0x7E8) == 0x23) {
                            arg0[0x7F6] = 1;
                            *(u16 *)(arg0 + 0x7F4) &= ~2;
                            func_8003EF70(arg0);
                            arg0[2] |= 0x20;
                            func_84108CE8(arg0);
                            *(u16 *)(arg0 + 0x7F4) &= ~0x20;
                        }
                        break;
                    case 1:
                        val = (*(s32 *)(arg0 + 0x48) >> 16) - 1;
                        if (val < 0) {
                            arg0[0x7F6] = 2;
                            func_84112158((s32)arg0, 0xFB);
                        }
                        func_84111E80(arg0, val);
                        func_84111DB4(arg0, val);
                        break;
                }
            }
            break;
        case 3:
        case 5:
            BattleAnim_Dispatch_002(arg0);
            break;
        case 7:
            if (*(s16 *)(arg0 + 0x7E8) >= 0x23) {
                func_8411EF08((u8 *)func_8411E164(arg0));
            }
            BattleAnim_Dispatch_002(arg0);
            break;
        case 4:
        case 8:
            func_84112418(arg0);
            break;
    }
    if (arg0[0x61A] == *(s16 *)(arg0 + 0x7E8)) {
        func_84111BEC(arg0);
        *(u16 *)(arg0 + 0x7F4) &= ~1;
        *(u16 *)(arg0 + 0x7F4) &= ~2;
        *(s32 *)(arg0 + 0x5C8 + D_841911F4 * 4) = D_84183D50;
    }
}
/* mkdraft:func_84119F24 end */
#endif

#ifdef VERSION_US
extern void func_84112E40(s32);
void BattleAnim_Dispatch_141(s32 arg0) {
    func_8411FEE8(0x1F);
    func_84112E40(arg0);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_841126C8(s32 arg0);
extern s32 func_84113430(s32 arg0);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_142(u8 *arg0) {
    s32 index;

    if (func_84113430((s32)arg0) != 0) {
        func_841126C8((s32)arg0);
        *(s16 *)(arg0 + 0x7E8) = 0;
        func_8411FEE8(0x1F);
        index = func_8411E1F8((s32)arg0);
        if (((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12)) & 2) != 0) {
            *(s16 *)(D_841911E0 + 0x98) = 0x24;
        } else {
            *(s16 *)(D_841911E0 + 0x98) = 0;
        }
        func_84111348((s32)arg0, 0);
        func_84113D38(arg0);
        *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern void func_8410890C(s32, s32);
void BattleAnim_Dispatch_143(s32 arg0) {
    if (func_841133EC(arg0) != 0) return;

    BattleAnim_Dispatch_002((u8 *)arg0);
    if (*(s16 *)((u8 *)(u8 *)arg0 + 0x7E8) == 2) {
        func_84112564(arg0);
        func_8410890C(0x104, arg0);
        func_80023A3C(8, 0, 0);
    }
    if (*(s16 *)((u8 *)(u8 *)arg0 + 0x7E8) == 0x1E) {
        *(u16 *)((u8 *)(u8 *)arg0 + 0x7F4) &= 0xFFFE;
        *(u16 *)((u8 *)(u8 *)arg0 + 0x7F4) &= 0xFFFD;
        func_841206D0((u8 *)arg0);
        *(s16 *)((u8 *)(u8 *)arg0 + 0x7E8) = 0;
        *(s32 *)((u8 *)(u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern void func_84111E80(void *arg0, s32 arg1);
void func_8411A310(u8 *arg0) {
    u8 *temp_v0;
    u8 *temp_v1;
    s32 temp_a3;
    temp_v0 = *(u8 **)(arg0 + 0xC);
    temp_v1 = ((u8 * (*)(s32, s32))*(void **)(temp_v0 + 0x2C))(0, 0);
    if (*(s16 *)(arg0 + 0x7E8) >= arg0[0x61A]) {
        func_84111E50(arg0, *(s8 *)(*(u8 **)(arg0 + 0x2D4) + 0x13C5));
        if (*(s8 *)(*(u8 **)(arg0 + 0x2D4) + 0x13C5) >= 0) {
            if (temp_v1[5] > 0) {
                temp_a3 = *(u16 *)(*(u8 **)(arg0 + 0x58) + 0xA) - 1;
                if (temp_a3 < arg0[0x61A]) {
                    func_84111E80(arg0, temp_a3);
                } else {
                    func_84111E80(arg0, arg0[0x61A]);
                }
            }
        }
    }
}
#endif

#ifdef VERSION_US
void func_8411A3D4(void *arg0) {
    extern u8 D_84183C74;
    extern u32 func_8003570C(void);
    void *temp_v1;

    if ((*(u16 *)((u8 *)arg0 + 0x7EC) & 1) == 0) {
        *(u16 *)(D_841911E0 + 0x98) =
            *(u16 *)((u8 *)&D_84183C74 +
                ((func_8003570C() % 3) * 2));
        temp_v1 = *(void **)((u8 *)arg0 + 0x2D4);
        *(u8 *)((u8 *)arg0 + 0x619) = *(u8 *)((u8 *)temp_v1 + 0x13CF);
        *(u8 *)((u8 *)arg0 + 0x61A) = *(u8 *)((u8 *)temp_v1 + 0x13CE);
        *(u8 *)((u8 *)arg0 + 0x620) = *(u8 *)((u8 *)temp_v1 + 0x13CD);
    }
}
#endif

#ifdef VERSION_US
extern void func_84111C44(void);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_036(u8 *arg0) {
    extern void func_84108A10(u8 *);

    func_8411FEE8(0x258);
    func_84111C44();
    func_84108A10(arg0);
    *(s16 *)(arg0 + 0x7E8) = 0;
    *(u8 *)(arg0 + 0x7F6) = 3;
    *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern s32 D_84183A5C;
extern void func_84113560(s32);
extern s32 func_8411DC80(u16, s32 *, s32);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern s32 D_841911F4;
void BattleAnim_Dispatch_037(u8 *arg0) {
    if (*(s16 *)(arg0 + 0x7E8) >= 2) {
        *(u8 *)(arg0 + 0x7F6) = 5;
        func_8411FEE8(0x258);
        if (func_8411DC80(*(u16 *)(arg0 + 0x1A), (s32 *)&D_84183A5C, 0x32)) {
            func_84113560(0x11A);
            *(s16 *)(arg0 + 0x7E8) = 0;
        } else {
            func_84113560(0x11A);
            *(s16 *)(arg0 + 0x7E8) = 0;
        }
        *(s32 *)(arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern void func_80024480(s16, s32);
extern void func_84108A10(u8 *);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84112158(s32 arg0, s32 arg1);
extern void func_84112290(u8 *arg0);
extern void func_84112564(s32 arg0);
extern void func_841126C8(s32 arg0);
extern s32 func_84113430(s32 arg0);
extern void func_8411A3D4(void *arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern u8 * D_841911E0;
extern s32 D_841911F4;
void func_8411A544(u8 *arg0) {
    if (*(s8 *)(arg0 + 0x7F6) == 3) return;
    if (func_84113430((s32)arg0) == 0) return;
    func_841126C8((s32)arg0);
    *(s16 *)(arg0 + 0x7F4) = 0;
    func_84112290(arg0);
    func_84108A10(arg0);
    func_80024480(*(s16 *)(arg0 + 0x658), 1);
    func_8411A3D4(arg0);
    *(s16 *)(arg0 + 0x7E8) = 0;
    func_8411FEE8(0x258);
    if (*(s16 *)(D_841911E0 + 0x98) != 0x21) func_84111348((s32)arg0, 0xB);
    *(s16 *)(arg0 + 0x7EA) = 0;
    func_84112158((s32)arg0, 0xFD);
    *(u8 *)(arg0 + 0x7F6) = 0;
    func_84112564((s32)arg0);
    *(s32 *)(arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

s32 func_8411E244(u8 *, M2C_UNK);                   /* extern */

void func_8411A620(u8 *arg0) {
    if ((M2C_FIELD(arg0, s8 *, 0x7F6) != 3) && (func_841133EC((s32) arg0) == 0)) {
        if (M2C_FIELD(arg0, s8 *, 0x7F6) == 0) {
            if (M2C_FIELD(arg0, u8 *, 0x619) == M2C_FIELD(arg0, s16 *, 0x7E8)) {
                if (func_8411E244(arg0, 0x119) != 0xFF) {
                    func_8410890C(0x119, (s32) arg0);
                    func_80023A3C(7, (s32) M2C_FIELD(arg0, s16 *, 0x1A), 0);
                }
                func_84112580((s32) arg0);
            }
            if (M2C_FIELD(arg0, u8 *, 0x61A) == M2C_FIELD(arg0, s16 *, 0x7E8)) {
                func_80023A3C(6, 0, 0);
                func_8410890C(0x11A, (s32) arg0);
                func_8411FEE8(0);
                M2C_FIELD(arg0, s8 *, 0x7F6) = 2;
            }
        }
        if ((M2C_FIELD(arg0, u16 *, 0x7EC) & 1) && ((M2C_FIELD(arg0, u8 *, 0x61A) + 0x19) == M2C_FIELD(arg0, s16 *, 0x7E8))) {
            func_8411EE74(arg0);
        }
        func_8411A310(arg0);
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_225(s32 arg0) {
    func_8411FEE8(0x50);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_8411A310(u8 *arg0);
extern void func_8411EE74();
void BattleAnim_Dispatch_226(u8 *arg0) {
    s32 temp_v0;

    temp_v0 = *(u16 *)((u8 *)D_84193DD0 + 6);
    if (temp_v0 == 0x4D) {
        func_84112580((s32) arg0);
        func_84112564((s32) arg0);
        temp_v0 = *(u16 *)((u8 *)D_84193DD0 + 6);
    }
    if (temp_v0 == 0x37) {
        func_8411EE74(arg0);
    }
    func_8411A310(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_8411A7D8.s")
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84112EDC(u8 *);
void BattleAnim_Dispatch_023(u8 *arg0) {
    extern s32 func_800427B8(s32);
    extern void func_84112EDC(u8 *);

    if (func_800427B8(*(s32 *)(arg0 + 0x5C0)) != 0) {
        func_84112EDC(arg0);
        *(s16 *)(arg0 + 0x7E8) = 0;
        *(u8 *)(arg0 + 0x7F6) = 1;
        *(s16 *)(D_841911E0 + 0x98) = 0;
        func_84111348((s32)arg0, 0);
        *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_024(u8 *arg0) {
    if (((*(s8 *)((u8 *)(arg0) + (0x7F6))) != 0) && ((*(s16 *)((u8 *)(arg0) + (0x7E8))) == 4)) {
        func_841206D0(arg0);
        func_8411FEE8(0);
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern s32 func_8006456C(s32);
extern void func_84108A10(u8 *);
extern void func_841126C8(s32 arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern s32 D_841911F4;
extern u8 * D_84193DD0;
void func_8411A964(u8 *arg0) {
    s32 first;
    s32 second;
    u8 saved;
    s32 result;

    *(s16 *)(arg0 + 0x7E8) = 0;
    *(u8 *)(arg0 + 0x7F6) = 0;
    func_8411FEE8(0x12C);
    first = func_8411E1F8((s32)arg0);
    *(u16 *)(arg0 + 0x65C) = *(u16 *)((u8 *)D_84193DD0 + (first << 4) + 0xC);
    func_84108A10(arg0);
    saved = (u8)func_8411E1F8((s32)arg0);
    second = func_8411E1F8((s32)arg0);
    result = func_8006456C(*(u16 *)((u8 *)D_84193DD0 + (second << 4) + 0x14));
    func_84112FD0(*(u8 **)(arg0 + 0x5C0), *(u16 *)(arg0 + 0x65C), *(F12State *)((u8 *)D_84193DD0 + (saved << 4) + 0x18), result);
    func_841126C8((s32)arg0);
    *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern s32 func_800427B8(s32);
extern void func_8410890C(s32, s32);
extern void func_84112EDC(u8 *);
void BattleAnim_Dispatch_163(u8 *arg0) {
    extern s32 func_800427B8(s32);
    extern void func_84112EDC(u8 *);
    extern void func_8410890C(s32, s32);
    s32 index;

    func_841139D0(func_8411E164(arg0));
    if (func_800427B8(*(s32 *)(arg0 + 0x5C0)) != 0) {
        func_84112EDC(arg0);
        *(s16 *)(arg0 + 0x7E8) = 0;
        *(u8 *)(arg0 + 0x7F6) = 1;
        index = func_8411E1F8((s32) arg0);
        if ((*(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0x10) & 7) != 0) {
            func_8410890C(0x100, (s32) arg0);
        }
        *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_164(u8 *arg0) {
    if (*(s8 *)(arg0 + 0x7F6) != 0) {
        func_841139D0(func_8411E164((s32)arg0));
        if (*(s16 *)(arg0 + 0x7E8) == 4) {
            func_841206D0(arg0);
            func_8411FEE8(0);
            *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_84111C44(void);
extern void func_84113560(s32);
void BattleAnim_Dispatch_127(s32 arg0) {
    *(u8 *)((u8 *)arg0 + 0x618) = 1;
    func_84111C44();
    func_84113560(0x126);
    *(s32 *)((u8 *)(arg0 + (D_841911F4 * 4)) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern u16 D_84183C7C[];
extern u32 func_8003570C(void);
extern void func_8410890C(s32, s32);
extern void func_84108A10(u8 *);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84111D64(u8 *, s32);
extern void func_84112564(s32);
extern void func_841126C8(s32 arg0);
extern s32 func_84113430(s32 arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern u8 * D_841911E0;
extern s32 D_841911F4;
extern u8 * D_84193DD0;
void func_8411ABAC(u8 *arg0) {
    if (func_84113430((s32)arg0) == 0) return;
    func_841126C8((s32)arg0); *(s16 *)(arg0 + 0x7E8) = 0; func_8411FEE8(0x258);
    *(s16 *)(D_841911E0 + 0x98) = *(u16 *)((u8 *)&D_84183C7C + ((func_8003570C() & 3) << 1)); func_84111348((s32)arg0, 0x1B); func_80023A3C(6, 0, 0);
    switch (*(u16 *)((u8 *)D_84193DD0 + 4)) { case 0x20: *(s16 *)(D_841911E0 + 0x98) = 0x11; func_84108A10(arg0); func_84112464(arg0); break; case 0x1E: func_84111D64(arg0, *(u8 *)(*(u8 **)(arg0 + 0x2D4) + 0x139C)); break; case 0x1F: func_84108A10(arg0); func_84111D64(arg0, *(u8 *)(*(u8 **)(arg0 + 0x2D4) + 0x139C)); func_84112324(arg0); break; default: break; }
    func_84112564((s32)arg0); func_8410890C(0x126, (s32)arg0); *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_129(s32 arg0) {
    if (func_841133EC(arg0) == 0) {
        if (*(s16 *)((u8 *)arg0 + 0x7E8) == 0x46) {
            *(u16 *)((u8 *)arg0 + 0x7F4) = *(u16 *)((u8 *)arg0 + 0x7F4) & 0xFFFE;
            *(u16 *)((u8 *)arg0 + 0x7F4) = *(u16 *)((u8 *)arg0 + 0x7F4) & 0xFFFD;
            func_841206D0((u8 *)arg0);
            *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
            func_8411FEE8(0);
            *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
        }
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_101(u8 *arg0) {
    s8 temp_v0;

    temp_v0 = (*(s8 *)((u8 *)(arg0) + (0x7F6)));
    switch (temp_v0) {                              /* irregular */
    case 1:
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 2;
        return;
    case 2:
        func_84112158((s32) arg0, 0xFC);
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 3;
        return;
    case 3:
        if (ModelAnim_IsFinished(arg0) != 0) {
            func_841206D0(arg0);
            func_84112158((s32) arg0, 0xFB);
            func_8411FEE8(0);
        }
        return;
    }
}
#endif

#ifdef VERSION_US
extern s32 func_8006456C(s32);
extern u8 * D_84193DD0;
void BattleAnim_Dispatch_099(u8 *arg0) { s32 first; s32 second; u8 saved; s32 result; first = func_8411E1F8((s32)arg0); *(u16 *)(arg0 + 0x65C) = *(u16 *)((u8 *)D_84193DD0 + (first << 4) + 0xC); saved = (u8)func_8411E1F8((s32)arg0); second = func_8411E1F8((s32)arg0); result = func_8006456C(*(u16 *)((u8 *)D_84193DD0 + (second << 4) + 0x14)); func_84112FD0(*(u8 **)(arg0 + 0x5C0), *(u16 *)(arg0 + 0x65C), *(F12State *)((u8 *)D_84193DD0 + (saved << 4) + 0x18), result); *(u8 *)(arg0 + 0x7F6) = 3; }
#endif

#ifdef VERSION_US
extern void func_800231A0(short, s16, s32, ...);
extern s32 func_800427B8(s32);
extern void func_84108728(u8, void *, s32);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_841126C8(s32 arg0);
extern void func_84112EDC(u8 *arg0);
extern s32 func_8411E164();
extern u8 * D_841911E0;
void func_8411AEA8(u8 *arg0) {
    u8 *entry;
    if (func_800427B8(*(s32 *)(arg0 + 0x5C0))) {
        func_800231A0(arg0[0x618], *(s16 *)(arg0 + 0x658), 0);
        func_84108728(arg0[0x618], arg0, func_8411E164((s32)arg0));
        func_841126C8((s32)arg0);
        func_84112EDC(arg0);
        entry = arg0[0x618] * 0x14 + *(u8 **)(arg0 + 0x2D4);
        *(s16 *)(arg0 + 0x628) = entry[-8];
        *(s16 *)(arg0 + 0x62A) = entry[-7];
        *(s16 *)(arg0 + 0x62C) = entry[-6];
        arg0[0x661] = entry[-5];
        *(s16 *)(arg0 + 0x7E8) = 0;
        *(s16 *)(D_841911E0 + 0x98) = 0;
        func_84111348((s32)arg0, 0);
        arg0[0x7F6] = 4;
    }
}
#endif

#ifdef VERSION_US
extern u8 *D_841911E0;
void func_8411AF6C(u8 *arg0) {
    u8 *entry;
    s32 index;
    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        *(s16 *)(D_841911E0 + 0x98) = 0;
        index = arg0[0x618] - 1;
        entry = *(u8 **)(arg0 + 0x2D4) + (index * 0x14);
        arg0[0x616] = entry[0];
        arg0[0x61F] = 0xFF;
        arg0[0x617] = entry[1];
        arg0[0x619] = entry[0xB];
        arg0[0x61A] = entry[0xA];
        arg0[0x61B] = entry[6];
        arg0[0x620] = entry[9];
        arg0[0x61C] = entry[2];
        arg0[0x61D] = entry[3];
        *(s16 *)(arg0 + 0x628) = entry[0xC];
        *(s16 *)(arg0 + 0x62A) = entry[0xD];
        *(s16 *)(arg0 + 0x62C) = entry[0xE];
        arg0[0x661] = entry[0xF];
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_092(u8 *arg0) {
    func_84111C44();
    (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 0;
    (*(u8 *)((u8 *)(arg0) + (0x618))) = (u8) (*(u8 *)((u8 *)(D_84193DD0) + (8)));
    func_841134A0(arg0);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void BattleAnim_SelectCameraPreset(u8 *, u16);
extern void func_84111D64(u8 *arg0, s32 arg1);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s32 arg1);
extern s32 func_84113430(s32 arg0);
extern void func_8411AF6C(u8 *arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern u8 D_841849B6[];
extern u8 * D_841911E0;
extern s32 D_841911F4;
void func_8411B070(u8 *arg0) {
    if (func_84113430((s32)arg0)) {
        *(s16 *)(arg0 + 0x7E8) = 0;
        func_8411AF6C(arg0);
        BattleAnim_SelectCameraPreset(D_841911E0, *(u16 *)(D_841849B6 + arg0[0x618] * 8));
        func_84111348((s32)arg0, 0);
        func_84111E50(arg0, *(s8 *)(arg0 + 0x617));
        func_84111D64(arg0, *(s8 *)(arg0 + 0x616));
        func_84111DB4(arg0, arg0[0x61B]);
        func_84111E80(arg0, arg0[0x61B]);
        if (arg0[0x61A] == 0) {
            *(s16 *)(arg0 + 0x7E8) = arg0[0x61B] - 1;
            func_8411FEE8(500);
        } else {
            *(s16 *)(arg0 + 0x7E8) = arg0[0x61B];
            func_8411FEE8(500);
        }
        arg0[0x7F6] = 1;
        *(s32 *)(arg0 + 0x5C8 + D_841911F4 * 4) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern void func_84111D64(u8 *, s32);
extern void func_84112564(s32);
extern u8 * D_841911E0;
void func_8411B160(u8 *arg0) { if (*(s8 *)(arg0 + 0x619) == *(s16 *)(arg0 + 0x7E8)) { arg0[0x7F6] = 2; if (*(s16 *)(D_841911E0 + 0x98) == 4) *(f32 *)(D_841911E0 + 0x88) = 60.0f; func_84112564(arg0); } if (ModelAnim_IsFinished(arg0) != 0) { func_84111E50(arg0, (*(u8 **)(arg0 + 0x2D4))[0x139D]); func_84111D64(arg0, (*(u8 **)(arg0 + 0x2D4))[0x139C]); } }
#endif

#ifdef VERSION_US
extern void func_8411AE08(u8 *);
extern void func_8411AEA8(u8 *);
extern void func_8411B160(u8 *arg0);
extern void func_8411FEE8(s32);
extern void func_841206D0(u8 *);
void func_8411B1F4(u8 *arg0) {
    s8 status;
    status = *(s8 *)(arg0 + 0x7F6);
    switch (status) {
    case 1:
        func_8411B160(arg0);
        break;
    case 2:
        func_8411AE08(arg0);
        break;
    case 3:
        func_8411AEA8(arg0);
        break;
    case 4:
        if (*(s16 *)(arg0 + 0x7E8) == 0x28) {
            func_841206D0(arg0);
            func_8411FEE8(0);
            *(u8 *)(arg0 + 0x7F6) = 5;
        }
        break;
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_078(u8 *arg0)
{
  int new_var;
  new_var = 0xA4;
  *((s16 *) (((u8 *) arg0) + 0x7E8)) = 0;
  *((s8 *) (((u8 *) arg0) + 0x7F6)) = 0;
  func_8411FEE8(0x64);
  *((s8 *) (((u8 *) arg0) + 0x618)) = new_var;
  func_84111C44();
  func_841134A0(arg0);
  *((s32 *) (((u8 *) (arg0 + (D_841911F4 * 4))) + 0x5C8)) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern u8 D_841849B6[];
extern void BattleAnim_SelectCameraPreset(u8 *, u16);
extern void func_80030420(s32, u8, s16, s32);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84112158(s32, s32);
extern void func_841126C8(s32 arg0);
extern s32 func_84113430(s32 arg0);
void BattleAnim_Dispatch_079(u8 *arg0) {
    if (func_84113430((s32)arg0) == 0) {
        return;
    }
    func_841126C8((s32)arg0);
    *(s16 *)(arg0 + 0x7E8) = 0;
    func_84112158((s32)arg0, 0xFB);
    BattleAnim_SelectCameraPreset(D_841911E0,
        *(u16 *)((u8 *)D_841849B6 + (*(u8 *)(arg0 + 0x618) << 3)));
    func_84111348((s32)arg0, 0);
    *(s8 *)(arg0 + 0x7F6) = 1;
    func_80030420(func_8411E1F8((s32)arg0) & 0xFF,
        *(u8 *)(arg0 + 0x618), *(s16 *)(arg0 + 0x1A), 0);
    *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84112564(s32);
extern void func_8411EFE4(s32);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern u8 * D_841911E0;
extern s32 D_841911F4;
void BattleAnim_Dispatch_080(u8 *arg0) {
    switch (*(s8 *)(arg0 + 0x7F6)) {
    case 1:
        if (*(s16 *)(arg0 + 0x7E8) != 30) break;
        *(s8 *)(arg0 + 0x7F6) = 2;
        func_84114600(arg0);
        break;
    case 2:
        *(s16 *)(arg0 + 0x7E8) = 0;
        BattleAnim_LoadSpecialModel((s32)arg0);
        func_8411EFE4((s32)arg0);
        *(s16 *)(D_841911E0 + 0x98) = 0;
        func_84111348((s32)arg0, 0);
        *(s16 *)(arg0 + 0x7EA) = 0;
        *(s8 *)(arg0 + 0x7F6) = 3;
        func_84112564((s32)arg0);
        break;
    case 3:
        if (*(s16 *)(arg0 + 0x7E8) == 40) {
            func_8411FEE8(0);
            ((s32 *)(arg0 + 0x5C8))[D_841911F4] = D_84183D50;
        }
        break;
    }
}
#endif

#ifdef VERSION_US
extern void func_84111C44(void);
extern void func_841134A0(u8 *arg0);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_148(u8 *arg0) {
    extern void func_84108AF8(u8 *);

    *(s16 *)(arg0 + 0x7E8) = 0;
    *(u8 *)(arg0 + 0x7F6) = 0;
    func_8411FEE8(0x3E8);
    BattleAnim_LoadSpecialModel((s32)arg0);
    *(u8 *)(arg0 + 0x618) = 0x90;
    func_84111C44();
    func_84108AF8(arg0);
    func_841134A0(arg0);
    *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84113920(u8 *);
void BattleAnim_Dispatch_149(u8 *arg0) {
    func_841139D0(arg0);
    func_84113920(arg0);
    if (func_84113430((s32) arg0) != 0) {
        func_841126C8((s32) arg0);
        func_84112158((s32) arg0, 0xFB);
        (*(s16 *)((u8 *)(D_841911E0) + (0x98))) = 0;
        func_84111348((s32) arg0, 0);
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern void func_80023A3C(s32, s32, s32);
extern void func_84108728(u8, void *, s32);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84112464(u8 *arg0);
extern void func_84112564(s32 arg0);
extern void func_84112580(s32 arg0);
extern void func_84112C98();
extern void func_84113920(u8 *arg0);
extern s32 func_8411E164();
extern void func_8411FEE8(s32);
extern u8 * D_841911E0;
extern u8 * D_84193DD0;
void func_8411B5A8(u8 *arg0) {
    switch (*(s8 *)(arg0 + 0x7F6)) {
    case 1:
        if (*(s16 *)(arg0 + 0x7E8) == 30) {
            arg0[0x7F6] = 2;
            func_84108728(0x90, arg0, func_8411E164((s32)arg0));
            func_80023A3C(0x2D, 0, 0);
        }
        break;
    case 2:
        *(s16 *)(arg0 + 0x7E8) = 0;
        func_84112C98(arg0);
        *(s16 *)(D_841911E0 + 0x98) = 0;
        func_84111348((s32)arg0, 0);
        *(s16 *)(arg0 + 0x7EA) = 0;
        arg0[0x7F6] = 3;
        func_84112564((s32)arg0);
        func_84112580((s32)arg0);
        if (((u16 (*)[8])(D_84193DD0 + 0x10))[func_8411E1F8(arg0)][0] == 0x20) {
            func_84112464(arg0);
        } else if (((u16 (*)[8])(D_84193DD0 + 0x10))[func_8411E1F8(arg0)][0] & 7) {
            func_84112324(arg0);
        }
        break;
    case 3:
        if (*(s16 *)(arg0 + 0x7E8) == 50) {
            func_8411FEE8(0);
            arg0[0x7F6] = 4;
        }
        break;
    }
    func_84113920(arg0);
}
#endif

#ifdef VERSION_US
void func_8411B710(u8 *arg0) {
    s32 index;
    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        index = func_8411E1F8((s32)arg0);
        *(u16 *)(arg0 + 0x65C) = *(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0xC);
    }
}
#endif

#ifdef VERSION_US
extern s32 func_8006456C(s32);
extern void func_8411B710(u8 *arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern s32 D_841911F4;
extern u8 * D_84193DD0;
void func_8411B75C(u8 *arg0) {
    s32 reservation;
    u8 padding;
    u8 index;
    s32 value;
    func_8411B710((arg0[0x7F6] = 0, arg0));
    func_8411FEE8(0x12C);
    *(s16 *)(arg0 + 0x7E8) = 0;
    index = func_8411E1F8((s32)arg0);
    value = func_8006456C(*(u16 *)(((u8 (*)[0x10])D_84193DD0)[func_8411E1F8((s32)arg0)] + 0x14));
    func_84112FD0(*(u8 **)(arg0 + 0x5C0), *(u16 *)(arg0 + 0x65C), *(F12State *)(((u8 (*)[0x10])D_84193DD0)[index] + 0x18), value);
    *(s32 *)(arg0 + D_841911F4 * 4 + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
s32 func_800427B8(s32);
extern void func_84112EDC(u8 *);
void BattleAnim_Dispatch_177(u8 *arg0) {
    if (func_800427B8((*(s32 *)((u8 *)(arg0) + (0x5C0)))) != 0) {
        func_841126C8((s32) arg0);
        func_841136E8(arg0);
        func_84112EDC(arg0);
        func_8411FEE8(0x384);
        (*(s16 *)((u8 *)(arg0) + (0x7EA))) = 0;
        (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
        (*(s8 *)((u8 *)(arg0) + (0x1D))) = 0;
        func_8410890C(0x12C, (s32) arg0);
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
    }
}
#endif

#ifdef VERSION_US
#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

void func_8411B898(u8 *arg0) {
    s8 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;

    temp_v0 = M2C_FIELD(arg0, s8 *, 0x7F6);
    switch (temp_v0) {                              /* switch 1; irregular */
    case 1:                                         /* switch 1 */
        M2C_FIELD(arg0, s16 *, 0x7E8) = 0;
        M2C_FIELD(arg0, s8 *, 0x7F6) = 2;
        if (M2C_FIELD(D_841911E0, s16 *, 0x98) != 0x21) {
            M2C_FIELD(arg0, s16 *, 0x7EA) = 0;
            M2C_FIELD(D_841911E0, s16 *, 0x98) = 0;
            func_84111348((s32) arg0, 0);
            return;
        }
        return;
    case 2:                                         /* switch 1 */
        if (M2C_FIELD(arg0, s16 *, 0x7E8) == 5) {
            temp_v0_2 = M2C_FIELD(D_84193DD0, u16 *, 4);
            switch (temp_v0_2) {                    /* switch 2; irregular */
            case 45:                                /* switch 2 */
                func_84112158((s32) arg0, 0xFB);
                break;
            case 46:                                /* switch 2 */
                func_84112464(arg0);
                break;
            case 47:                                /* switch 2 */
                func_84112324(arg0);
                break;
            }
            M2C_FIELD(arg0, s16 *, 0x7E8) = 0;
            M2C_FIELD(arg0, s8 *, 0x7F6) = 3;
            func_84112564((s32) arg0);
            return;
        }
        break;
    case 3:                                         /* switch 1 */
        temp_v0_3 = M2C_FIELD(D_84193DD0, u16 *, 4);
        switch (temp_v0_3) {                        /* switch 3; irregular */
        case 45:                                    /* switch 3 */
            if (M2C_FIELD(arg0, s16 *, 0x7E8) == 0x3C) {
                func_841206D0(arg0);
                func_8411FEE8(0);
                M2C_FIELD(arg0, s8 *, 0x7F6) = 6;
                return;
            }
            break;
        case 47:                                    /* switch 3 */
            if (M2C_FIELD(arg0, s16 *, 0x7E8) == 6) {
                func_8410890C(0x100, (s32) arg0);
            }
            func_84112418(arg0);
            if (M2C_FIELD(arg0, s16 *, 0x7E8) == 0x3C) {
                M2C_FIELD(arg0, u16 *, 0x7F4) = (u16) (M2C_FIELD(arg0, u16 *, 0x7F4) & 0xFFFE);
                func_841206D0(arg0);
                func_8411FEE8(0);
                M2C_FIELD(arg0, s8 *, 0x7F6) = 6;
                return;
            }
            break;
        case 46:                                    /* switch 3 */
            if (M2C_FIELD(arg0, s16 *, 0x7E8) == 6) {
                func_8410890C(0xFE, (s32) arg0);
            }
            if (M2C_FIELD(arg0, s16 *, 0x7E8) == 0x3C) {
                M2C_FIELD(arg0, u16 *, 0x7F4) = (u16) (M2C_FIELD(arg0, u16 *, 0x7F4) & 0xFFFD);
                func_841206D0(arg0);
                func_8411FEE8(0);
                M2C_FIELD(arg0, s8 *, 0x7F6) = 6;
            }
            break;
        }
        break;
    }
}
#endif

#ifdef VERSION_US
void func_8411BAB8(u8 *arg0) {
    s32 index;
    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        index = func_8411E1F8((s32)arg0);
        *(u16 *)(arg0 + 0x65C) = *(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0xC);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_8411BB04.s")
#endif

#ifdef VERSION_US
s32 func_800427B8(s32);
extern void func_84113560(s32);
void func_8411EE74(u8 *arg0);
void BattleAnim_Dispatch_086(u8 *arg0) {
    func_8411EE74(arg0);
    if (func_800427B8((*(s32 *)((u8 *)(arg0) + (0x5C0)))) != 0) {
        func_841126C8((s32) arg0);
        func_841136E8(arg0);
        func_84112EDC(arg0);
        func_8411FEE8(0x384);
        (*(s16 *)((u8 *)(arg0) + (0x7EA))) = 0;
        (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
        func_841126C8((s32) arg0);
        (*(s8 *)((u8 *)(arg0) + (0x1D))) = 0;
        func_84113560(0x122);
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
        func_8411EE74(arg0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_8411BCC8.s")
#endif

#ifdef VERSION_US
extern void func_8410C720(u8 *, u8 *, f32, f32, f32, s32);

/* mkdraft:func_8411C1D4 begin */
extern void func_8410C720(u8 *, u8 *, f32, f32, f32, s32);



void func_8411C1D4(u8 *arg0, u8 *arg1, s32 arg2) {
    *(s16 *)(arg1 + 0x98) = 0;
    if (*(s16 *)((u8 *)D_84191208 + 0x7E8) == 1) {
        func_8410B884(*(u8 **)arg1, arg0, arg1, *(s16 *)(arg0 + 0x20));
    }
    if (*(s16 *)((u8 *)D_84191208 + 0x7E8) == arg2 - 0x23) {
        *(f32 *)(arg1 + 0x44) = 0.0f;
    }
    if (*(s16 *)((u8 *)D_84191208 + 0x7E8) < arg2 - 0x23) {
        func_8410C720(*(u8 **)arg1, arg0, 50.0f, 70.0f, 0.0f, 0);
    } else {
        func_8410C720(*(u8 **)arg1, arg0, 75.0f, 30.0f, 0.5f, 0x1C71);
    }
}
/* mkdraft:func_8411C1D4 end */
#endif

#ifdef VERSION_US
extern void func_841125A4(s32);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_169(s32 arg0) {
    func_841125A4(D_8419120C);
    *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    *(u8 *)((u8 *)arg0 + 0x7F6) = 0;
    func_8411FEE8(0x320);
    *(s32 *)((u8 *)(arg0 + (D_841911F4 * 4)) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

M2C_UNK func_8410C544(s32, s32, s16);               /* extern */

void func_8411C310(s32 arg0) {
    func_84112158(D_84191208, 0xFC);
    func_80024480(M2C_FIELD(D_84191208, s16 *, 0x1A), 4);
    func_84112158(D_8419120C, 0xFB);
    M2C_FIELD(D_84191208, s16 *, 0x7EA) = 0;
    M2C_FIELD(D_8419120C, s16 *, 0x7EA) = 0;
    M2C_FIELD(D_84191208, s8 *, 0x7F6) = 1;
    M2C_FIELD(D_841911E0, s16 *, 0x98) = 0;
    func_84111348(arg0, 0x1A);
    M2C_FIELD(D_841911E4, s16 *, 0x98) = 0;
    func_8410C544(M2C_FIELD(D_841911E4, s32 *, 0), D_8419120C, M2C_FIELD(D_841911E4, s16 *, 0x98));
    func_8411EF08((u8 *) arg0);
    M2C_FIELD(arg0, s8 *, 0x1D) = 0;
    func_8411EF20((u8 *) D_8419120C);
    func_8411EE74((u8 *) D_8419120C);
    func_84112564(arg0);
    M2C_FIELD((arg0 + (D_841911F4 * 4)), s32 *, 0x5C8) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_8411C418.s")
#endif

#ifdef VERSION_US
extern void func_8410C400(u8 *, void *, f32, f32, f32, s32);
extern void func_8410B884(u8 *arg0, void *arg1, u8 *arg2, s16 arg3);
extern s32 D_84191208;
void func_8411C7B8(void *arg0, void *arg1, s32 arg2) {
    *(s16 *)((u8 *)arg1 + 0x98) = 0;
    if (*(s16 *)((u8 *)D_84191208 + 0x7E8) == 1) {
        func_8410B884(*(u8 **)arg1, arg0, arg1, *(s16 *)((u8 *)arg0 + 0x20));
        *(s16 *)((u8 *)arg1 + 0x3C) = 0;
    }
    if (arg2 == *(s16 *)((u8 *)D_84191208 + 0x7E8)) {
        *(f32 *)((u8 *)arg1 + 0x44) = 0.0f;
    }
    if (*(s16 *)((u8 *)D_84191208 + 0x7E8) < arg2) {
        func_8410C400(*(u8 **)arg1, arg0, 50.0f, 30.0f, 0.0f, 0);
    } else {
        func_8410C400(*(u8 **)arg1, arg0, 80.0f, 30.0f, 0.5f, 0x1C71);
    }
}
#endif

#ifdef VERSION_US
#define C8_PREFIX(A) func_841125A4(D_8419120C); *(s16 *)((u8 *)(A) + 0x7E8) = 0; *(u8 *)((u8 *)(A) + 0x7F6) = 0; func_8411FEE8(0x320); func_84113560(0x112); func_8410AF1C(); func_84111248(); func_8410C304(*(u8 **)D_841911E0, D_84191208, *(s16 *)(D_841911E0 + 0x98)); func_841112C8(); func_8410C304(*(u8 **)D_841911E4, D_8419120C, *(s16 *)(D_841911E4 + 0x98));
#define C8_STORE(A) *(s32 *)((u8 *)(A) + (D_841911F4 * 4) + 0x5C8) = D_84183D50
void func_8411C8A0(s32 arg0) {
    func_841125A4(D_8419120C);
    *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    *(u8 *)((u8 *)arg0 + 0x7F6) = 0;
    func_8411FEE8(0x320);
    func_84113560(0x112);
    func_8410AF1C();
    func_84111248();
    func_8410C304(*(u8 **)D_841911E0, D_84191208, *(s16 *)(D_841911E0 + 0x98));
    func_841112C8();
    func_8410C304(*(u8 **)D_841911E4, D_8419120C, *(s16 *)(D_841911E4 + 0x98));
    *(u8 *)((u8 *)(u32)D_84191208 + 1) &= 0xFFFE;
    *(u8 *)((u8 *)(u32)1 + D_8419120C) &= 0xFFFE;
    *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_184(s32 arg0) {
    if (func_84113430(arg0) != 0) {
        func_8410890C(0x112, arg0);
        (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern void func_8411C7B8(void *, void *, s32);
extern s32 Math_StepToS32(s32, s32, s32, s32);
extern void func_80023A3C(s32, s32, s32);
extern s32 func_8006456C(s32);
extern void func_8410B08C(void);
extern void func_8410B104(void);
extern void func_8410B224(void);
extern void func_8411FEE8(s32);
extern u8 * D_841911E0;
extern u8 * D_841911E4;
extern s32 D_84191208;
extern s32 D_8419120C;
extern u8 * D_84193DD0;
void func_8411C9DC(u8 *arg0) {
    switch (*(s8 *)(arg0 + 0x7F6)) {
    case 1:
        func_8411C7B8(D_84191208, D_841911E0, 0x78);
        func_8411C7B8(D_8419120C, D_841911E4, 0x78);
        if (*(s16 *)(arg0 + 0x7E8) >= 0x3C) {
            s32 value = Math_StepToS32(*(s16 *)(D_841911E0 + 0xA0), 0xF0, 4, 4);
            *(s16 *)(D_841911E0 + 0xA0) = value;
            *(s16 *)(D_841911E4 + 0x9C) = *(s16 *)(D_841911E0 + 0xA0);
            *(s16 *)(D_841911E4 + 0xA0) = 0xF0 - *(s16 *)(D_841911E0 + 0xA0);
            if (*(s16 *)(D_841911E0 + 0xA0) == 0xF0) { func_8410B224(); *(s8 *)(arg0 + 0x7F6) = 2; } else func_8410B08C();
        }
        if (*(s16 *)(arg0 + 0x7E8) == 0) { func_80023A3C(4, 0, 0); func_80023A3C(4, 1, 0); }
        break;
    case 2:
        if (*(s16 *)(arg0 + 0x7E8) == 0x6B) { s32 i = func_8411E1F8((s32)arg0); if (func_8006456C(*(u16 *)((u8 *)D_84193DD0 + (i << 4) + 0x14)) == 1) func_80023A3C(0x3D, 0, 0); else func_80023A3C(0x3C, 0, 0); }
        func_8411C7B8(D_84191208, D_841911E0, 0x78);
        func_8411C7B8(D_8419120C, D_841911E4, 0x78);
        if (*(s16 *)(arg0 + 0x7E8) == 0xA0) { func_8410B104(); func_8411FEE8(0); *(s8 *)(arg0 + 0x7F6) = 3; }
        break;
    }
}
#endif

#ifdef VERSION_US
extern void func_841125A4(s32);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_239(s32 arg0) {
    func_841125A4(D_8419120C);
    *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    *(u8 *)((u8 *)arg0 + 0x7F6) = 0;
    func_8411FEE8(0x320);
    *(s32 *)((u8 *)(arg0 + (D_841911F4 * 4)) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

M2C_UNK func_84113590(M2C_UNK);                     /* extern */

void func_8411CC2C(s32 arg0) {
    func_84112158(D_84191208, 0xFC);
    func_80024480(M2C_FIELD(D_84191208, s16 *, 0x1A), 4);
    func_84112158(D_8419120C, 0xFB);
    M2C_FIELD(D_84191208, s16 *, 0x7EA) = 0;
    M2C_FIELD(D_8419120C, s16 *, 0x7EA) = 0;
    M2C_FIELD(D_84191208, s8 *, 0x7F6) = 1;
    M2C_FIELD(D_841911E0, s16 *, 0x98) = 0;
    func_84111348(arg0, 0x1A);
    func_841112C8();
    func_84113590(4);
    func_8410C304(M2C_FIELD(D_841911E4, u8 **, 0), D_8419120C, (s32) M2C_FIELD(D_841911E4, s16 *, 0x98));
    func_8411EF08((u8 *) arg0);
    M2C_FIELD(arg0, s8 *, 0x1D) = 0;
    func_8411EF20((u8 *) D_8419120C);
    func_8411EE74((u8 *) D_8419120C);
    func_84112564(arg0);
    M2C_FIELD((arg0 + (D_841911F4 * 4)), s32 *, 0x5C8) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_8411CD38.s")
#endif

#ifdef VERSION_US
extern void func_8410C304(u8 *arg0, s32 arg1, s32 arg2);
extern void func_84111248();
extern void func_841125A4(s32);
extern void func_84113560(s32);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_232(s32 arg0) {
    func_841125A4(D_8419120C);
    func_841112C8();
    *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    *(u8 *)((u8 *)arg0 + 0x7F6) = 0;
    func_8411FEE8(0x320);
    func_84113560(0x12A);
    func_84111248();
    func_8410C304(*(u8 **)D_841911E0, D_84191208, *(s16 *)(D_841911E0 + 0x98));
    *(u8 *)((u8 *)(u32)D_84191208 + 1) &= 0xFFFE;
    *(u8 *)((u8 *)(u32)1 + D_8419120C) &= 0xFFFE;
    *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_233(s32 arg0) {
    if (func_84113430(arg0) != 0) {
        (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern void func_80023A3C(s32, s32, s32);
extern s32 func_8006456C(s32);
extern void func_8410890C(s32, s32);
extern void func_8411C7B8(void *arg0, void *arg1, s32 arg2);
extern void func_8411FEE8(s32);
extern u8 * D_841911E0;
extern s32 D_84191208;
extern u8 * D_84193DD0;
void BattleAnim_UpdateTimedEffectSequence(u8 *arg0) {
    switch (*(s8 *)(arg0 + 2038)) {
    case 1:
        func_8411C7B8((void *)D_84191208, D_841911E0, 220);
        if (*(s16 *)(arg0 + 2024) == 100) {
            func_8410890C(298, (s32)arg0);
            func_80023A3C(4, 0, 0);
            arg0[2038] = 2;
        }
        break;
    case 2:
        if (*(s16 *)(arg0 + 2024) == 207) {
            if (func_8006456C(((u16 (*)[8])(D_84193DD0 + 16))[func_8411E1F8((s32)arg0)][2]) == 1) {
                func_80023A3C(61, 0, 0);
            } else {
                func_80023A3C(60, 0, 0);
            }
        }
        func_8411C7B8((void *)D_84191208, D_841911E0, 220);
        if (*(s16 *)(arg0 + 2024) == 260) {
            func_8411FEE8(0);
            arg0[2038] = 3;
        }
        break;
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_204(u8 *arg0) {}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_205(u8 *arg0) {}
#endif

#ifdef VERSION_US
extern void func_84108A10(u8 *);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84111C44(void);
extern void func_841126C8(s32 arg0);
extern s32 func_8411E164(s32 arg0);
extern void func_8411FEE8(s32);
extern s32 D_84183D50;
extern s32 D_841911F4;
void BattleAnim_Dispatch_211(u8 *arg0) {
    u8 *result;
    *(s16 *)(arg0 + 0x7E8) = 0;
    arg0[0x7F6] = 0;
    func_8411FEE8(0x154);
    func_841126C8(arg0);
    arg0[1] |= 1;
    result = (u8 *)func_8411E164((s32)arg0);
    result[1] = (u8)(result[1] & 0xFFFE);
    func_84111C44();
    func_84112290(arg0);
    func_84108A10(arg0);
    *(s16 *)(arg0 + 0x7EA) = 0;
    func_84111348((s32)arg0, 0x18);
    func_8002B2FC();
    *(s32 *)(arg0 + D_841911F4 * 4 + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern u8 D_841904DC[];
extern u8 D_841904D0[];
extern void func_80037120(void *, void *, f32 *, s16 *, s16 *);
extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_8411FEE8(s32);
extern u8 * D_841911E0;
void func_8411D388(u8 *arg0) {
    f32 position[3];
    f32 distance;
    s16 angleY;
    s16 angleX;

    switch (*(s8 *)(arg0 + 0x7F6)) {
    case 0:
        Camera_ComputeEyeFromAngles(D_841904DC, (u8 *)position, *(f32 *)(D_841911E0 + 0x40), *(s16 *)(D_841911E0 + 0x3C), *(s16 *)(D_841911E0 + 0x3E));
        func_80037120((s32)D_841904D0, (s32)position, (s32 *)&distance, &angleY, &angleX);
        if ((distance <= 1.75f) && (*(s16 *)(arg0 + 0x7E8) >= 6)) {
            *(s16 *)(arg0 + 0x7E8) = 0;
            *(s8 *)(arg0 + 0x7F6) = 1;
            func_84111348((s32)arg0, 7);
        }
        break;
    case 1:
        if (*(s16 *)(arg0 + 0x7E8) == 50) {
            *(s8 *)(arg0 + 0x7F6) = 2;
            func_8411FEE8(0);
        }
        break;
    }
}
#endif

#ifdef VERSION_US
extern void func_80024480(s16, s32);
void BattleAnim_Dispatch_008(u8 *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
    if (func_841139D0(arg0) == 0) {
        func_84112158((s32) arg0, 0xFC);
        func_80024480((*(s16 *)((u8 *)(arg0) + (0x658))), 2);
    }
    func_8411FEE8(0x12C);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_009(u8 *arg0) {
    func_841139D0(arg0);
    if ((*(s16 *)((u8 *)(arg0) + (0x1A))) == 0xFC) {
        if ((*(s16 *)((u8 *)(arg0) + (0x7E8))) == 0x3C) {
            func_8411FEE8(0);
            (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
        }
    } else if ((ModelAnim_IsFinished(arg0) != 0) || ((*(s16 *)((u8 *)(arg0) + (0x7E8))) == 0x78)) {
        func_8411FEE8(0);
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern u8 *D_84193FA0;
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s32 arg1);
extern s32 D_84183D50;
extern s32 D_841911F4;
void BattleAnim_Dispatch_246(u8 *arg0) {
    *(s16 *)(arg0 + 0x7E8) = 0;
    func_84111E50(arg0, -1);
    func_84111D64(arg0, *(s8 *)(D_84193FA0 + 0x7C));
    func_84111E80(arg0, 0);
    func_84111DB4(arg0, 0);
    *(s32 *)(arg0 + D_841911F4 * 4 + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84112158(s32, s32);
extern void func_841125F4(void *arg0, s32 arg1);
void BattleAnim_Dispatch_247(s32 arg0) {
    if (ModelAnim_IsFinished(arg0) != 0) {
        func_84112158(arg0, 0xFB);
        func_841206D0((u8 *)arg0);
        func_841125F4((void *)arg0, 0);
        *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    }
}
#endif

#ifdef VERSION_US
#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

s32 func_8006A3E0();                                /* extern */
s32 func_8006AC70();                                /* extern */
M2C_UNK func_84113590(s32);                         /* extern */
extern s32 D_841910D8;

void func_8411D65C(void) {
    s32 temp_v1;

    temp_v1 = func_8006A3E0() & 0xFF00;
    switch (temp_v1) {                              /* irregular */
    case 0x300:
        if ((D_841910D8 >= 9) && (D_841910D8 < 0xD)) {
            func_84113590(5);
            return;
        }
        if (func_8006AC70() == 0) {
            func_84113590(5);
            return;
        }
        func_84113590((func_8003570C() % 5U) & 0xFF);
        return;
    case 0x0:
        func_84113590((func_8003570C() % 5U) & 0xFF);
        return;
    case 0x400:
        func_84113590((func_8003570C() % 5U) & 0xFF);
        return;
    case 0x200:
        if ((D_841910D8 >= 0x17) && (D_841910D8 < 0x1D)) {
            func_84113590((func_8003570C() % 5U) & 0xFF);
            return;
        }
        func_84113590(5);
        return;
    case 0x600:
        func_84113590(5);
        return;
    default:
        func_84113590((func_8003570C() % 5U) & 0xFF);
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_8411D7F8.s")
#endif

#ifdef VERSION_US
void func_8411D9B4(void) {
    extern s32 D_84191208;
    extern s32 D_8419120C;
    extern u8 D_84190410;
    extern u8 D_84190411;
    extern u8 D_841911FA;
    extern void func_8411D7F8(u8 *);
    extern void func_8411D65C(void);

    *(u16 *)((u8 *)(*(u8 **)&D_84191208) + 0x7EC) = 0;
    *(u16 *)((u8 *)(*(u8 **)&D_8419120C) + 0x7EC) = 0;
    *(u16 *)((u8 *)(*(u8 **)&D_84191208) + 0x7F4) = 0;
    *(u16 *)((u8 *)(*(u8 **)&D_8419120C) + 0x7F4) = 0;
    func_8411D7F8(*(u8 **)&D_84191208);
    func_8411D7F8(*(u8 **)&D_8419120C);
    D_84190410 = 0;
    D_84190411 = 0;
    D_841911FA = 0;
    func_8411D65C();
}
#endif

#ifdef VERSION_US
extern void BattleAnim_RunObjectCallbacks(u8 *);
void func_8411DA2C(u8 *arg0) {
    BattleAnim_RunObjectCallbacks(arg0);
}
#endif

#ifdef VERSION_US
/* mkdraft:func_8411DA4C begin */
extern void func_8411FF1C(void);
extern void func_8411DA2C();
extern void func_8411FEFC(void);
extern void func_84111EC4(u8 *);

void func_8411DA4C(void) {
    *(u16 *)((u8 *)D_84191208 + 0x7EC) &= ~1;
    *(u16 *)((u8 *)D_8419120C + 0x7EC) &= ~1;
    func_8411FF1C();
    func_8411DA2C((u8 *)D_84191208);
    func_8411DA2C((u8 *)D_8419120C);
    func_841120A4((u8 *)D_84191208);
    func_841120A4((u8 *)D_8419120C);
    func_8411FEFC();
    func_84111EC4((u8 *)D_84191208);
    func_84111EC4((u8 *)D_8419120C);
}
/* mkdraft:func_8411DA4C end */
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380A00/func_8411DAE0.s")
#endif

#ifdef VERSION_US
extern void BattleAnim_AllocateSideObjects(void);
extern void func_8411DA4C(void);
extern void func_8411DAE0(void);
extern s32 n_alResampleParam(void);
s32 func_8411DBF4(s32 arg0) {
    /* Case bodies are emitted in *source* order, not case-value order --
     * recovered from jtbl_841893D4's actual call targets: retail's switch
     * declares case 30 before case 3 and case 5. */
    switch (arg0) {
    case 0: BattleAnim_AllocateSideObjects(); break;
    case 1:
    case 2: func_8411DA4C(); break;
    case 30: func_8411DAE0(); break;
    case 3: func_8411D9B4(); break;
    case 5: n_alResampleParam(); break;
    }
    return 0;
}
#endif
