#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA00020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA00380.s")
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_8FA004CC(s32 arg0, void *arg1) {
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
s32 func_8FA00534(s32 arg0, void *arg1) {
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
extern f32 D_8FA01D04;
extern s32 D_8FA01D38;
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_800371B4(f32 *, s32 *, f32, s16, s32);
extern void func_80038E14(s32, s32, s32, s32, f32, f32, f32, s32);
extern void GeoCamera_SetPerspective(void *, f32, f32, f32);
void func_8FA005A0(f32 arg0, void *arg1) {
    f32 position[3];
    s32 output[3];

    Vec3f_SetComponentsDuplicate(position, 0.0f, 250.0f / arg0, 0.0f);
    func_800371B4(position, output, D_8FA01D04 / arg0, *(s16 *)((u8 *)arg1 + 0), *(s16 *)((u8 *)arg1 + 2));
    func_80038E14(*(s32 *)((u8 *)(u32)D_8FA01D38 + 0xC), output[0], output[1], output[2], position[0], position[1], position[2], 0);
    GeoCamera_SetPerspective((void *)(u32)*(s32 *)((u8 *)(u32)D_8FA01D38 + 0xC), 30.0f, 100.0f / arg0, 12800.0f / arg0);
}

void func_8FA00694_padding(void) {}
#endif

#ifdef VERSION_US
extern s32 main_pool_alloc(s32, s32);
extern u8* func_8004D878(u8*, s32, u8*);
extern u8* D_8FA020A0;
extern s32 D_8FA01950[], D_8FA01958[];
void func_8FA0069C(void) {
    s32* asset;
    s32 offset;
    D_8FA020A0 = (u8*)main_pool_alloc(0x1900, 0);
    /* Keep this loop and its initialization on one physical line: IDO's
     * source-line scheduling otherwise delays the end-table address load. */
    asset = D_8FA01950; offset = 0; do { func_8004D878(offset + D_8FA020A0, *asset, 0); asset++; offset += 0xC80; } while (asset != D_8FA01958); }
#endif

void func_8FA0071C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA00724.s")
#endif

void func_8FA00AC0(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA00AC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA00E2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA00F4C.s")
#endif

#ifdef VERSION_US
s32 func_800542B0(s16);
extern void func_800542E4(s16, s32);
void func_8FA010B0(s16 arg0, s16 arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a1;

    temp_v1 = (1 << arg0) & 0xFF;
    temp_a0 = func_800542B0(arg1) & ~temp_v1;
    var_a1 = temp_a0 & 0xFF;
    if (arg2 != 0) {
        var_a1 = (temp_a0 | temp_v1) & 0xFF;
    }
    func_800542E4(arg1, var_a1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA01110.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA0125C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA01718.s")
#endif

#ifdef VERSION_US
extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern void func_8FA00F4C(void);
extern void func_8FA00E2C(void);
extern s32 func_8FA01718(s32);
extern void func_8FA00724(void);
extern s32 func_80055948(s32);
extern s32 func_80054E48(s32);
extern void Gfx_InitDisplayListBuffers(s32,s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 StageContext_Allocate(s8,s8,s8,s8,s8,s32);
extern s32 func_8004C09C(s32);
extern s32 func_8004C8C0(u16);
extern s32 func_8004C990(s32,s32);
extern u8* func_80047588(s32,s32);
extern u8* Asset_LoadToSegment(s32,u8*,u8*,s32);
extern u8 D_1000000[],D_446E30[],D_447D00[];
extern s32 D_8FA02028;
extern void func_80008514(s32);
extern void func_80008574(void);
extern void func_80051D64(s32,s32);
extern void func_80047610(void);
void func_8FA017B8(void) {
    s32 state = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    do {
        func_80064D28();
        if (state == 1) {
            func_8FA00F4C();
        }
        func_8FA00E2C();
        state = func_8FA01718(state);
    } while (state != 3);
}
#endif

#ifdef VERSION_US
s32 fragment75_main(s32 arg0, s32 arg1) {
    s32 configuration;
    main_pool_push_state(0x4D444C56);
    func_80055948(3);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    configuration = StageContext_Allocate(0, 1, 3, 1, 3, 1);
    func_8004C09C(9);
    func_8004C8C0(0x99);
    D_8FA02028 = func_8004C990(0x99, 2);
    func_80047588(3, 0);
    Asset_LoadToSegment(((u32)D_1000000 & 0x0F000000) >> 24, D_446E30, D_447D00, 0);
    func_8FA00724();
    func_80008514(configuration);
    func_8FA017B8();
    func_80008574();
    func_80051D64(0x13, 0);
    func_80054E48(3);
    func_80047610();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x4D444C56);
    return 0;
}
#endif
