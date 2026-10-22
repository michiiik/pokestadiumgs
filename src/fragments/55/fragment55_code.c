#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void GeoRender_ApplyMaterialState(void);
extern u8 D_8670BA40[];
extern u8 D_8670B660[];
void func_86700020(s32 arg0, s32 arg1) {
    if (arg0 == 5) {
        gDPPipeSync(D_800D0510++);
        gSPSegment(D_800D0510++, 0xF, func_8004CA60((u8 *)func_8004C990(0x133, 1)));
        gSPDisplayList(D_800D0510++, D_8670BA40);
        GeoRender_ApplyMaterialState();
    }
}
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void GeoRender_ApplyMaterialState(void);
extern u8 D_8670BA40[];
extern u8 D_8670B660[];
void func_867000C8(s32 arg0, s32 arg1) {
    if (arg0 == 5) {
        gDPPipeSync(D_800D0510++);
        gSPSegment(D_800D0510++, 0xF, func_8004CA60((u8 *)func_8004C990(0x3E, 1)));
        gDPSetEnvColor(D_800D0510++, 0, 0, 0xFF, 0xFF);
        gSPDisplayList(D_800D0510++, D_8670B660);
        GeoRender_ApplyMaterialState();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670018C.s")
#endif

#ifdef VERSION_US
extern s32 D_8670C970;
extern s32 D_8670BB84;
extern s32 D_8670C96C;
extern void GeoRender_ApplyMaterialState(void);
extern s32 func_8004C990(s32, s32);
extern u8 * func_8004CA60(u8 *);
extern Gfx * D_800D0510;
void func_86700318(s32 arg0, s32 arg1) {
    s32 temp_v0;
    if (arg0 == 0) { D_8670C970 = func_8004C990(0xE3, 0); }
    if (arg0 == 5) {
        temp_v0 = func_8004C990(0xE3, D_8670BB84); D_8670C970 = temp_v0;
        gDPPipeSync(D_800D0510++); gDPSetCombine(D_800D0510++, 0xFCFFFFFF, 0xFFFCF238);
        gSPSegment(D_800D0510++, 0xF, func_8004CA60((u8 *)D_8670C970)); gSPDisplayList(D_800D0510++, D_8670C96C); GeoRender_ApplyMaterialState();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86700418.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86700588.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern void *D_8009491C;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void GeoRender_ApplyMaterialState(void);
extern s32 D_8670AB90[];
extern s32 D_8670C97C;
extern void *D_8670C978;
/* function: func_867006C4 */
void func_867006C4(s32 arg0, s32 arg1) {
    void *context;
    s32 index;

    if (arg0 == 5) {
        context = D_8009491C;
        index = *(s32 *)((u8 *)context + 0x14);
        D_8670C97C = func_8004C990(0x1B2, D_8670AB90[index]);
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238);
        gSPSegment(D_800D0510++, 0xF,
                   func_8004CA60((u8 *)D_8670C97C));
        gSPDisplayList(D_800D0510++, D_8670C978);
        GeoRender_ApplyMaterialState();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867007B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86700FD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670122C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867014C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86701874.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86701C6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670211C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86702434.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86702B28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86702E50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867035A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867036B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867037B8.s")
#endif

#ifdef VERSION_US
extern s16 MathUtil_Atan2s(f32, f32);
s16 func_86703D98(s8 arg0, s8 arg1) {
    if (arg1 > 0) {
        arg1 = 0;
    }
    return MathUtil_Atan2s(arg0, arg1) - 0xC000;
}
#endif

#ifdef VERSION_US
typedef struct State86703DF4 {
    u8 pad00[0x08];
    s32 unk08;
    u8 pad0C[0x20];
    s32 unk2C;
    u8 pad30[0x08];
    s32 unk38;
    u8 pad3C[0x0C];
    s32 unk48;
    u8 pad4C[0x60];
} State86703DF4;
extern State86703DF4 D_86728408[];
extern s16 D_86710C40[][0xB4];
void func_86703DF4(s32 arg0) {
    s32 count;
    s32 limit;

    limit = 0;
    if (D_86728408[arg0].unk38 != 0) {
        D_86728408[arg0].unk48 = 1;
        limit = 0x20;
    }
    count = ++D_86728408[arg0].unk08;
    if (limit < count) {
        D_86728408[arg0].unk08 = 0;
        D_86728408[arg0].unk2C = 0;
        D_86728408[arg0].unk38 = 0;
        D_86728408[arg0].unk48 = 0;
        return;
    }
    D_86710C40[arg0][0] = count << 12;
}

void func_86703DF4_padding(void) {
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86703E9C.s")
#endif

#ifdef VERSION_US
/* mkdraft:func_86703F9C begin */
extern s32 D_8670BB58;
extern s32 D_86727CD8[];
extern u32 func_8003570C(void);

void func_86703F9C(void) {
    s32 value;
    D_86727CD8[0] = D_8670BB58 / 1800;
    value = D_8670BB58 - D_86727CD8[0] * 1800;
    D_86727CD8[1] = value / 30;
    value -= D_86727CD8[1] * 30;
    D_86727CD8[2] = func_8003570C() % 3 + value * 100 / 30;
}
/* mkdraft:func_86703F9C end */
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670408C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670427C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867043AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670675C.s")
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 GeoCallback_OrientToCamera(s32 arg0, void *arg1) {
    s16 pad;
    s32 x;
    s16 y;
    s16 z;

    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &x, &y, &z);
        *(s16 *)((u8 *)arg1 + 0x1C) = y + 0x2000;
        *(s16 *)((u8 *)arg1 + 0x1E) = z - 0x2000;
    }
    return 0;
}

void func_867068DC(void) {
}

void D_867068E4(void) {
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867068EC.s")
#endif

#ifdef VERSION_US
typedef struct { u8 pad38[0x38]; s32 index; u8 pad3C[0x0C]; f32 out48; f32 out4C; f32 out50; f32 in54; f32 out58; } State86706A30;
typedef struct { u8 pad24[0x24]; f32 x; f32 y; f32 z; u8 tail[0x138]; } Row86706A30;
extern State86706A30 *D_87F119DC;
extern f32 D_8670C974;
extern Row86706A30 D_86710C20[];
void func_86706A30(void) { f32 temp_fv0; temp_fv0 = D_87F119DC->in54; D_87F119DC->out58 = temp_fv0; D_8670C974 = temp_fv0; D_87F119DC->out48 = D_86710C20[D_87F119DC->index].x; D_87F119DC->out4C = D_86710C20[D_87F119DC->index].y + 120.0f; D_87F119DC->out50 = D_86710C20[D_87F119DC->index].z - 50.0f; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86706AC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86706B88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86706D3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86706E34.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86707E2C.s")
#endif

void func_867086E4(void) {
}

#ifdef VERSION_US
s32 func_87F00930();
extern void func_87F01D44();

void func_867086EC(void) {
    if (func_87F00930() == 1) {
        func_87F01D44();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86708720.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86708944.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86708B18.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86708EDC.s")
#endif

#ifdef VERSION_US
extern s32 D_8670BB48;
extern void *D_8670FEB0;
void func_86709040(void) {
    if ((*(u8 *)((u8 *)(D_8670FEB0) + (0x2180))) == 4) {
        StageFade_StartFromOpaque(0x14);
        func_87F00688();
        D_8670BB48 = 0xD;
        return;
    }
    if (StageContext_GetFadeMode() == 0) {
        D_8670BB48 = 4;
    }
}
#endif

#ifdef VERSION_US
extern s32 func_87F006AC(void);
extern void Audio_PlayDefaultSound(s32);
extern void func_80021ED8(s32);
extern void func_87F0CA30(void);
extern s32 D_8670B394;
extern s32 D_8670BB48;
s32 func_867090A8(void) {
    if (D_8670B394 == 1) {
        return 0;
    }
    if (func_87F006AC() == 1) {
        Audio_PlayDefaultSound(0x5F07);
    }
    if (func_87F006AC() == 2) {
        D_8670BB48 = 1;
        Audio_PlayDefaultSound(0x5F08);
        func_80021ED8(0x2E);
        func_87F0CA30();
    }
}
#endif

void func_86709128(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86709130.s")
#endif

#ifdef VERSION_US
extern s32 StageFade_StartFromTransparent(s32);
s32 func_87F01A40();
extern s32 D_8670B394;
void func_8670972C(void) {
    s32 temp_v0;

    D_8670B394 = 1;
    temp_v0 = func_87F01A40();
    switch (temp_v0) {                              /* irregular */
    case 0:
    case 2:
        D_8670B394 = 0;
        return;
    case 3:
        (*(s32 *)((u8 *)(&D_8670BB48) + (0x48))) = 0;
        (*(s32 *)((u8 *)(&D_8670BB48) + (0))) = 2;
        (*(s32 *)((u8 *)(&D_8670BB48) + (0x30))) = 3;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        return;
    case 4:
        (*(s32 *)((u8 *)(&D_8670BB48) + (0x48))) = 1;
        (*(s32 *)((u8 *)(&D_8670BB48) + (0))) = 2;
        (*(s32 *)((u8 *)(&D_8670BB48) + (0x30))) = 3;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867097D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86709934.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86709AD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670A07C.s")
#endif

#ifdef VERSION_US
extern f32 D_8670C684;
extern f32 D_8670C688;
extern f32 D_8670BE7C;
extern s16 D_8670BE80;
extern s16 D_8670BE84;
extern u8 D_86726A48[];
extern u8 D_86726BB0[];
extern u8 D_86726D18[];
extern u8 D_86726E80[];
extern u8 D_86726FE8[];
extern u8 D_86727150[];
extern u8 D_867272B8[];
extern void func_8003F1DC(void *);

void func_8670A404(void) {
    f32 *var_v0 = (f32 *)&D_8670BB48;

    var_v0[5] = 0.0f;
    var_v0[6] = -140.0f;
    var_v0[7] = D_8670C684;
    var_v0[8] = 0.0f;
    var_v0[9] = 40.0f;
    var_v0[10] = 0.0f;
    D_8670BE7C = D_8670C688;
    D_8670BE80 = 16388;
    D_8670BE84 = 6400;
    func_8003F1DC(D_86726A48);
    func_8003F1DC(D_86726BB0);
    func_8003F1DC(D_86726D18);
    func_8003F1DC(D_86726E80);
    func_8003F1DC(D_86726FE8);
    func_8003F1DC(D_86727150);
    func_8003F1DC(D_867272B8);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670A4D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670A790.s")
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

M2C_UNK Asset_LoadToSegment(u32, M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK Gfx_FreeDisplayListBuffers();               /* extern */
M2C_UNK Gfx_InitDisplayListBuffers(M2C_UNK, M2C_UNK); /* extern */
s32 func_800082E0(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_80008514(s32);                         /* extern */
M2C_UNK func_80008574();                            /* extern */
M2C_UNK func_80027EE0(M2C_UNK);                     /* extern */
M2C_UNK func_80047588(s32, M2C_UNK);                /* extern */
M2C_UNK func_80047610();                            /* extern */
M2C_UNK func_8004C09C(M2C_UNK);                     /* extern */
M2C_UNK func_8004C398();                            /* extern */
M2C_UNK func_8004C8C0(M2C_UNK);                     /* extern */
M2C_UNK func_86706E34();                            /* extern */
M2C_UNK func_8670A790();                            /* extern */
M2C_UNK func_87F00030();                            /* extern */
M2C_UNK func_87F01F34(u8 *);                      /* extern */
M2C_UNK func_87F06EAC(M2C_UNK, M2C_UNK *, u8 *);  /* extern */
s32 func_87F08E3C(s32, M2C_UNK);                    /* extern */
M2C_UNK func_87F0C980();                            /* extern */
M2C_UNK func_87F0F480(u8 *);                      /* extern */
M2C_UNK main_pool_pop_state(M2C_UNK);               /* extern */
M2C_UNK main_pool_push_state(M2C_UNK);              /* extern */
extern M2C_UNK D_1000000;
extern M2C_UNK D_446E30;
extern M2C_UNK D_447D00;
extern s32 D_8670BB90;
extern s32 D_8670C958;
extern M2C_UNK D_8670D880;
extern s32 D_8670D888;
extern s32 D_8670D8D8;

s32 func_8670A96C(s32 arg0, u8 *arg1) {
    s32 sp24;

    D_8670FEB0 = arg1;
    if (M2C_FIELD(D_8670FEB0, u8 *, 0x2180) == 4) {
        func_80027EE0(0xFFF);
    }
    main_pool_push_state(0x4D523033);
    Gfx_InitDisplayListBuffers(0x20000, 0);
    sp24 = func_800082E0(0, 1, 3, 1, 2, 1);
    func_8004C09C(0x123);
    func_87F06EAC(0x6C, &D_8670D880, D_8670FEB0);
    func_8004C8C0(0xE2);
    func_8004C8C0(0xE3);
    func_8004C8C0(0x1B2);
    func_8004C8C0(0x133);
    func_8004C8C0(0xE0);
    func_8004C8C0(0x3E);
    func_8004C8C0(0x182);
    func_8004C8C0(0x183);
    func_8004C8C0(0xCD);
    D_8670C96C = func_87F08E3C(func_8004C990(0xE3, 0), 0x0F000000);
    D_8670C958 = func_87F08E3C(func_8004C990(0xCD, 0), 0x0F000000);
    func_80047588(D_8670D888 | 5 | D_8670D8D8, 0);
    Asset_LoadToSegment((u32) ((s32) &D_1000000 & 0x0F000000) >> 0x18, &D_446E30, &D_447D00, 0);
    func_87F00030();
    func_87F01F34(D_8670FEB0);
    func_87F0C980();
    func_86706E34();
    func_80008514(sp24);
    func_8670A790();
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x4D523033);
    func_87F0F480(D_8670FEB0);
    func_80027EE0(0xFFE);
    return D_8670BB90;
}
#endif
