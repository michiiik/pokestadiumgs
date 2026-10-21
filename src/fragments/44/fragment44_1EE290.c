#include "global.h"


#ifdef VERSION_US
s32 func_8003514C();
s32 func_8AF244D0();
extern u16 D_8AF2BE8A;

s32 func_8AF00020(void) {
    if (func_8003514C() == 0) {
        return 1;
    }
    if ((D_8AF2BE8A & 0x100) && (func_8AF244D0() != 0)) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF0007C.s")

extern void func_800226C0(s32);
void func_8AF00130(s32 code) {
    func_800226C0(code);
}

extern u8 D_8AF2BE98[]; extern s32 D_8AF2BF10; void func_8AF00150(void) { _bzero(D_8AF2BE98, 0x78); D_8AF2BF10 = 0; }

extern s16 D_8AF2BE9A;
u8 *func_8AF0017C(s16 arg0) {
    s32 i;
    u8 *entry;
    entry = D_8AF2BE98;
    if (arg0 == D_8AF2BE9A) {
        return entry;
    }
    entry += 0xC;
    if (arg0 == *(s16 *)(entry + 2)) {
        return entry;
    }
    entry += 0xC;
    i = 2;
    do {
        if (arg0 == *(s16 *)(entry + 2)) {
            return entry;
        }
        i++;
        entry += 0xC;
    } while (i != 0xA);
    return NULL;
}

/* mkdraft:func_8AF00240 begin */
extern u8 D_8AF2BEA4[];

u8 *func_8AF00240(s16 arg0) {
    s32 i;
    u8 *entry;
    entry = D_8AF2BE98;
    if (arg0 == *(s16 *)(D_8AF2BEA4 - 0xC)) {
        return entry;
    }
    entry += 0xC;
    if (arg0 == *(s16 *)entry) {
        return entry;
    }
    entry += 0xC;
    i = 2;
    do {
        if (arg0 == *(s16 *)entry) {
            return entry;
        }
        i++;
        entry += 0xC;
    } while (i != 0xA);
    return NULL;
}
/* mkdraft:func_8AF00240 end */

void func_8AF00304(s16 arg0, s32 arg1)
{
  void *temp_v0;
  if ((arg0 == 0x89) || (arg0 == 0x92))
  {
    temp_v0 = func_8AC06D8C(arg1 ^ 0, 0x70696330, arg1);
    if (temp_v0 != 0)
    {
      *((u16 *) (((u8 *) temp_v0) + 2)) = (u16) ((*((u16 *) (((u8 *) temp_v0) + 2))) & 0xFFFE);
    }
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00360.s")

typedef struct Lookup_8AF003A8 {
    s16 unused;
    s16 id;
    s32 state;
    s32 value;
} Lookup_8AF003A8;
s32 func_8AF003A8(s16 arg0) {
    struct { Lookup_8AF003A8 *entry; s32 unused; } local;
    s32 index;

    local.entry = (Lookup_8AF003A8 *)D_8AF2BE98;
    index = 0;
    do {
        if (arg0 == local.entry->id) {
            func_8AF00304(arg0, local.entry->value);
            return local.entry->value;
        }
        index++;
        local.entry++;
    } while (index != 10);
    return 0;
}

/* mkdraft:func_8AF00410 begin */
extern s32 D_8AF2BF10;
extern s32 func_8AF00360(s32);
extern void func_8AC00FFC(s32);
extern s32 func_8004DC6C(s32);
extern void func_8004DCFC(u8 *, s32 *);
extern s32 main_pool_get_available(void);
extern u8 *MainPool_AllocState(s32, s32);
extern s32 func_8004EB58(s32, s32);
extern void MainPool_FinalizeAllocation(void *);

u8 *func_8AF00410(s16 arg0) {
    u8 *found;
    u8 *entry;
    u8 *allocState;
    s32 dc6c;
    u8 *rec;

    found = func_8AF0017C(arg0);
    if (found != NULL) {
        return NULL;
    }
    entry = func_8AF0017C(0);
    if (entry == NULL) {
        return NULL;
    }
    D_8AF2BF10 = D_8AF2BF10 + 1;
    *(s16 *)(entry + 0) = D_8AF2BF10;
    *(s16 *)(entry + 2) = arg0;
    *(s16 *)(entry + 4) = 1;
    func_8AC00FFC(func_8AF00360((u8)D_8AF2BF10));
    dc6c = func_8004DC6C(arg0);
    func_8004DCFC((u8 *)dc6c, NULL);
    allocState = MainPool_AllocState(main_pool_get_available(), 0);
    rec = (u8 *)func_8004EB58((s32)allocState, dc6c);
    *(s32 *)(entry + 8) = (s32)rec;
    MainPool_FinalizeAllocation(allocState);
    *(u16 *)(rec + 2) |= 1;
    *(u16 *)(rec + 2) |= 2;
    return entry;
}
/* mkdraft:func_8AF00410 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00504.s")

extern void func_800503A4(s32);
extern void func_8AC00738();
void func_8AF00620(void) {
    s32 var_s1;
    u8 *var_s0;

    var_s0 = D_8AF2BE98;
    var_s1 = 0;
    do {
        if (((*(s16 *)((u8 *)(var_s0) + (2))) != 0) && ((*(s16 *)((u8 *)(var_s0) + (4))) == 0)) {
            func_8AC00738();
            func_800503A4((*(s32 *)((u8 *)(var_s0) + (8))));
        }
        var_s1 += 1;
        var_s0 += 0xC;
    } while (var_s1 != 0xA);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00690.s")

void func_8AF00760(void) {}
void func_8AF00760_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00770.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00B74.s")

s16 func_8AF00B74();
extern s16 D_8AF2BA6C;
extern s32 D_8AF2BDD0;
extern s16 D_8AF2BDD4;
extern s32 D_8AF2BE78;
extern s16 D_8AF2BE7C;
void func_8AF00D90(void) {
    s16 temp_v0;

    temp_v0 = func_8AF00B74();
    if (temp_v0 != D_8AF2BA6C) {
        D_8AF2BDD0 = 1;
        D_8AF2BDD4 = 4;
        D_8AF2BE78 = 1;
        D_8AF2BE7C = temp_v0;
        return;
    }
    if (D_8AF2BDD0 != 0) {
        D_8AF2BDD4 -= 1;
        if (D_8AF2BDD4 < 0) {
            D_8AF2BDD0 = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00E24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF0118C.s")

extern void func_800504BC(s16 *);
extern void func_8AF0118C(s16, s16, void *);
s32 func_8AF013D8(s32 mode, void *record) {
    s16 values[2];
    s16 first;
    s16 second;
    void *preserved;

    preserved = record;
    switch (mode) {
    case 0:
        *(u16 *)((u8 *)preserved + 2) = *(u16 *)((u8 *)preserved + 2) & 0xFFFD;
        break;
    case 1:
        func_800504BC(values);
        first = *(s16 *)((u8 *)preserved + 8) + values[0];
        second = *(s16 *)((u8 *)preserved + 0xA) + values[1];
        func_8AF0118C(first, second, preserved);
        break;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF0145C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01530.s")

extern s16 D_8AF263F0[];
s16 Trade_GetSelectedBox(s16 arg0) { return D_8AF263F0[arg0]; }

s32 func_8AF01618(u8 arg0, u8 arg1) {
    s32 nibble = arg1 & 0xF;
    if ((nibble == (arg0 & 0xF)) || (nibble == ((arg0 & 0xF0) >> 4))) return 1;
    return 0;
}

extern u8 func_80063A48(u8);
extern s32 func_80064474(u8, u16);
u8 func_8AF01654(u8 arg0) {
    u8 result = func_80063A48(arg0);

    if ((func_80064474(arg0, 0x80) == 0) &&
        (func_8AF01618(result, 0xD) == 0) &&
        (func_8AF01618(result, 0xF) == 0)) {
        result = 0;
    }
    return result;
}

extern u8 D_8AF28760[];
extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern void Ui_DrawGradientPanel(s32, s32, s32, s32, s32, s32);
void func_8AF016BC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    Ui_DrawGradientPanel(arg0, arg1, arg2, arg3, arg4, arg5);
}
void func_8AF016BC_padding(void) {}

s16 *func_8AF01718(s16 *arg0, s32 arg1) {
    s16 value;
    if (arg1 == 0) return arg0;
    do {
        do {
            value = *arg0++;
        } while (value != -1);
        arg1--;
    } while (arg1 != 0);
    return arg0;
}

extern void func_8AC00824(void);
extern void func_8AF00D90(void);
void func_8AF01750(void) {
    func_8AC00824();
    func_8AF00D90();
}

extern Gfx *D_800D0510;
extern u8 D_8AF26418[];
void Font_EndTexturedTextRendering_fragment44(void) { Gfx *temp_v1 = D_800D0510++; temp_v1->words.w0 = 0xDE000000; temp_v1->words.w1 = (u32)D_8AF26418; }

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

M2C_UNK func_8AF0282C(M2C_UNK *, M2C_UNK);          /* extern */
extern M2C_UNK D_8AF2BDE0;
extern M2C_UNK D_8AF2BDF8;
extern M2C_UNK D_8AF2BE10;
extern s32 D_8AF2BE24;
extern M2C_UNK D_8AF2BE28;
extern s32 D_8AF2BE3C;
extern M2C_UNK D_8AF2BE48;
extern s32 D_8AF2BE5C;
extern M2C_UNK D_8AF2BE60;
extern s32 D_8AF2BE74;

void func_8AF017A4(void) {
    s32 var_v0;

    if (M2C_FIELD(&D_8AF2BDE0, s32 *, 0x14) != 0) {
        func_8AF0282C(&D_8AF2BDE0, 1);
        func_8AF0282C(&D_8AF2BDE0, 2);
    }
    if (M2C_FIELD(&D_8AF2BDF8, s32 *, 0x14) != 0) {
        func_8AF0282C(&D_8AF2BDF8, 1);
        func_8AF0282C(&D_8AF2BDF8, 2);
    }
    if (D_8AF2BE24 != 0) {
        func_8AF0282C(&D_8AF2BE10, 1);
    }
    if (D_8AF2BE3C != 0) {
        func_8AF0282C(&D_8AF2BE28, 1);
    }
    if (D_8AF2BE5C != 0) {
        func_8AF0282C(&D_8AF2BE48, 1);
    }
    var_v0 = M2C_FIELD(&D_8AF2BE60, s32 *, 0x14);
    if (var_v0 != 0) {
        func_8AF0282C(&D_8AF2BE60, 1);
        var_v0 = D_8AF2BE74;
    }
    if (var_v0 != 0) {
        func_8AF0282C(&D_8AF2BE60, 2);
    }
    if (D_8AF2BE5C != 0) {
        func_8AF0282C(&D_8AF2BE48, 2);
    }
    if (D_8AF2BE3C != 0) {
        func_8AF0282C(&D_8AF2BE28, 2);
    }
    if (D_8AF2BE24 != 0) {
        func_8AF0282C(&D_8AF2BE10, 2);
    }
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01910.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01A0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01C84.s")

extern s32 D_8AF2BA68;
extern s16 D_8AF2BE40;

s32 func_8AF01D7C(s32 arg0)
{
  s32 sp1C;
  s16 *new_var;
  s16 *new_var3;
  int new_var2;
  new_var = &D_8AF2BE40;
  sp1C = arg0;
  switch (arg0)
  {
    case 0:
      if (!StageContext_GetFadeMode())
    {
      sp1C = 1;
    }
      break;

    case 1:
      new_var2 = 0xA;
      if (D_8AF2BA68 > 0)
    {
      if (D_8AF2BA68 == 2)
      {
        sp1C = 2;
        D_8AF2BE40 = new_var2;
      }
      else
      {
        sp1C = 3;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(5);
        if (D_8AF2BA68 != 3)
        {
          func_80035424(5);
        }
      }
    }
      break;

    case 2:
      if ((*(new_var3 = new_var)) > 0)
    {
      D_8AF2BE40 = (*new_var3) - 1;
    }
    else
    {
      sp1C = 3;
      StageContext_SetClearColor(1);
      StageFade_StartFromTransparent(5);
      func_80035424(5);
    }
      break;

    case 3:
      if (StageContext_GetFadeMode() == 1)
    {
      sp1C = 4;
    }
      break;

  }

  return sp1C;
}
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

M2C_UNK StageFade_StartFromOpaque(M2C_UNK);         /* extern */
M2C_UNK func_800086A4(M2C_UNK);                     /* extern */
s32 func_80043678(s32);                             /* extern */
M2C_UNK func_8AC0080C(M2C_UNK);                     /* extern */
M2C_UNK func_8AF0007C(s32);                         /* extern */
M2C_UNK func_8AF01910();                            /* extern */
s32 func_8AF01D7C(s32);                             /* extern */
M2C_UNK func_8AF0282C(M2C_UNK *, M2C_UNK);          /* extern */
extern s32 D_8AF2BA84;
extern s32 D_8AF2BA8C;
extern s16 D_8AF2BAC8;
extern M2C_UNK D_8AF2BDE0;
extern M2C_UNK D_8AF2BDF8;
extern M2C_UNK D_8AF2BE10;
extern M2C_UNK D_8AF2BE28;
extern M2C_UNK D_8AF2BE48;
extern M2C_UNK D_8AF2BE60;
extern s32 D_8AF2BE80;

void func_8AF01EAC(void) {
    s32 temp_v0;
    s32 var_s1;

    var_s1 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    D_8AF2BDD0 = 0;
    D_8AF2BDD4 = 0;
    D_8AF2BE78 = 0;
    D_8AF2BE80 = 0;
    func_8AF0282C(&D_8AF2BDE0, 0);
    func_8AF0282C(&D_8AF2BDF8, 0);
    func_8AF0282C(&D_8AF2BE10, 0);
    func_8AF0282C(&D_8AF2BE28, 0);
    func_8AF0282C(&D_8AF2BE48, 0);
    func_8AF0282C(&D_8AF2BE60, 0);
    func_8AC0080C(0xC);
    do {
        func_8AF0007C(var_s1);
        func_8AF01750();
        if (D_8AF2BAC8 == 1) {
            D_8AF2BA8C = func_80043678(D_8AF2BA84);
            D_8AF2BAC8 = 2;
        }
        func_8AF01910();
        temp_v0 = func_8AF01D7C(var_s1);
        var_s1 = temp_v0;
    } while (temp_v0 != 4);
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01FFC.s")

/* mkdraft:func_8AF02208 begin */
extern s16 D_8AF2BA6E;
extern s32 D_8AF2C65C;
extern s32 D_8AF2BDD8;
extern s32 D_8AF2BF20;
extern s16 *D_8AF2BA90[];
extern s32 D_8AF2BA68;
extern u8 D_8AF2BE88[];
extern void func_8AC00FEC(void);
extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern s32 func_8004C09C(s32);
extern s32 func_80055948(s32);
extern void func_8005487C();
extern s32 func_8004C8C0(u16);
extern s32 func_8004C990(s32, s32);
extern u8 *BinArchive_Open(u8 *, u8 *, s32, s32);
extern u8 D_47B920[];
extern u8 D_47D310[];
extern void *func_80004B4C(s32, s32);
extern u8 *func_80047588(s32, s32);
extern s32 func_8004C4B0(s32);
extern u8 *Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern u8 D_1000000[], D_446E30[], D_447D00[];
extern void func_8AF01FFC(void);
extern void func_80008514(s32);
extern void func_80008574(void);
extern s32 func_80051D64(s32, s32);
extern s32 func_80054E48(s32);
extern void func_80047610(void);
extern void func_8004C398(void);
extern void func_80006158(void);

s32 func_8AF02208(s32 arg0, s32 arg1) {
    UNUSED s32 pad;
    s32 configuration;
    s32 i;
    u8 *archive;

    D_8AF2BA6E = arg0;
    D_8AF2C65C = 1;
    D_8AF2BDD8 = arg1;
    func_8AC00FEC();
    main_pool_push_state(0x504D4C43);
    Gfx_InitDisplayListBuffers(0x14000, 0);
    configuration = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(0x15F);
    func_80055948(3);
    func_8005487C(D_8AF2BE88);
    func_8004C8C0(0x1B);
    func_8004C8C0(0xA6);
    D_8AF2BF20 = func_8004C990(0xA6, 0);
    func_8004C8C0(0x11E);
    func_8004C8C0(0xAE);
    archive = BinArchive_Open(D_47B920, D_47D310, 1, 1);
    for (i = 0; i != 14; i++) {
        D_8AF2BA90[i] = func_80004B4C((s32)archive, i);
    }
    func_80047588(0x1C, 0);
    func_8004C4B0(0x36);
    func_8004C4B0(0x3B);
    func_8004C4B0(0xC);
    Asset_LoadToSegment(((u32)D_1000000 & 0x0F000000) >> 24, D_446E30, D_447D00, 0);
    func_8AF01FFC();
    func_80008514(configuration);
    func_8AF01EAC();
    func_80008574();
    func_80051D64(0x13, 0);
    func_80054E48(3);
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    func_80006158();
    main_pool_pop_state(0x504D4C43);
    if (D_8AF2BA68 <= 0) {
        D_8AF2BA68 = 1;
    }
    return D_8AF2BA68 - 1;
}
/* mkdraft:func_8AF02208 end */
#endif
