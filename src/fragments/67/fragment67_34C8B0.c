#include "global.h"


#ifdef VERSION_US
typedef struct F67DisplayRecord {
    /* 0x00 */ s16 x, y;
    /* 0x04 */ s16 unused04, flags;
    /* 0x08 */ u8 unused08[4];
    /* 0x0C */ s16 selection;
    /* 0x0E */ u8 unused0E[4];
    /* 0x12 */ u8 foreground[3];
    /* 0x15 */ u8 background[3];
} F67DisplayRecord;
extern F67DisplayRecord D_8291BE80, D_8291BE98;

typedef struct unk_func_8290FDB0 {
    u8 unk_00;
    u8 unk_01[3];
    s32 unk_04;
} unk_func_8290FDB0;

extern s32 func_80055948(s32 arg0);
extern void func_80054210(unk_func_8290FDB0* arg0);
extern void func_80054248(unk_func_8290FDB0* arg0);
extern void func_80051D64(s32 arg0, s32 arg1);
extern s32 func_80055028(void);

void func_8290FDB0(s16 arg0) {
    unk_func_8290FDB0 var_sp18;

    func_80055948(3);
    func_80054210(&var_sp18);
    var_sp18.unk_00 = arg0 + 1;
    func_80054248(&var_sp18);
    func_80051D64(20, 0);
    func_80055028();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_8290FE04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_8290FF14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910258.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910510.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910740.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910B30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910FC8.s")

typedef struct F67TextRow {
    s32 id;
    u8 padding[0x40];
} F67TextRow;
extern F67TextRow D_829172F8[], D_829172FC[], D_82917300[];
extern u8 D_8291BEB0[];
extern char D_829177C0[], D_829177C4[], D_829177C8[];
extern s32 func_800476FC(s32, s32);
extern s32 func_8004C990(s32, s32);
extern s32 func_80047738(s32, s32, s32, s32);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void* func_8004C874(s32, s32);
extern void func_800495F8(s32, s32, s32, const char*, ...);
extern void func_800499EC(void);

void func_82911418(void) {
    func_800476FC((s32)D_8291BEB0, 4);
    func_80047738(0, func_8004C990(0x38, 5), 0, 0);
    func_80047738(1, func_8004C990(0x38, 1), 0, 0);
    func_80047738(2, func_8004C990(0x38, 7), 0, 0);
    func_80047738(3, func_8004C990(0x33, 5), 0, 0);
    func_800498C4();
    func_800496A4(8, 0);
    func_8004972C(255, 255, 255, 255);
    func_800495F8(D_8291BE98.x + 0xCE, D_8291BE98.y + 0xC, 1, D_829177C0, func_8004C874(0x1C, D_829172F8[D_8291BE80.selection].id));
    func_800495F8(D_8291BE80.x + 0x116, D_8291BE80.y + 0x26, 1, D_829177C4, func_8004C874(0x1C, D_829172FC[D_8291BE80.selection].id));
    func_800495F8(D_8291BE80.x + 0x114, D_8291BE80.y + 0x4E, 1, D_829177C8, func_8004C874(0x1C, D_82917300[D_8291BE80.selection].id));
    func_800499EC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_829115E0.s")

extern void func_800088DC(void);
extern void func_829115E0(void);
extern void func_80008648(void);
void func_82911850(void) {
    func_800088DC();
    func_829115E0();
    func_80008648();
}

extern void StageFade_StartFromOpaque(s32);
extern s32 D_8291BE70;
void func_82911880(void) {
    s32 var_s0;

    StageFade_StartFromOpaque(0xC);
    var_s0 = 0;
    do {
        func_82911850();
        var_s0 += 1;
    } while (var_s0 != 0xC);
    D_8291BE70 = 1;
}

extern void func_80064D28();
extern void func_82910258();
void func_829118D4(void) {
    if (D_8291BE70 != 0) {
        do {
            func_80064D28();
            func_82910258();
            func_82911850();
        } while (D_8291BE70 != 0);
    }
}

extern void StageFade_StartFromTransparent(s32);
void func_8291192C(void) {
    s32 var_s0;

    StageFade_StartFromTransparent(0x10);
    var_s0 = 0;
    do {
        func_82911850();
        var_s0 += 1;
    } while (var_s0 != 0x10);
}

extern void func_8290FE04(s16);

void func_82911974(s16 arg0) {
    func_8290FE04(arg0);
}

extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern u8* func_80047588(s32, s32);
extern s32 func_8004C09C(s32);
extern s32 func_8004D690(s32);
extern s32 func_8004C8C0(u16);
extern s32 func_8004C4B0(s32);
extern u8* Asset_LoadToSegment(s32, u8*, u8*, s32);
extern void func_80008514(s32);
extern void func_80008574(void);
extern void func_80047610(void);
extern void func_8004C398(void);
extern s32 D_8291BE74;
extern u8 D_1000000[], D_446E30[], D_447D00[];

s32 func_8291199C(s32 arg0, s32 selection) {
    s32 configuration;

    main_pool_push_state(0x474244);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    configuration = func_800082E0(1, 0, 2, 0, 2, 1);
    func_80047588(12, 0);
    func_8004C09C(7);
    D_8291BE74 = func_8004D690(2);
    func_8004C8C0(0x52);
    func_8004C8C0(0x51);
    func_8004C8C0(0x12A);
    func_8004C8C0(0x12B);
    func_8004C8C0(0x38);
    func_8004C8C0(0x33);
    func_8004C8C0(0x126);
    func_8004C8C0(0x128);
    func_8004C8C0(0x127);
    func_8004C8C0(0x12F);
    func_8004C4B0(0x1C);
    Asset_LoadToSegment((((u32)D_1000000 & 0x0F000000) >> 24), D_446E30, D_447D00, 0);
    func_82911974((s16)selection);
    func_80008514(configuration);
    func_82911880();
    func_829118D4();
    func_8291192C();
    func_80008574();
    func_80047610();
    Gfx_FreeDisplayListBuffers();
    func_8004C398();
    main_pool_pop_state(0x474244);
    return 0;
}
#endif
