#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100020.s")
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_8F10008C(s32 arg0, void *arg1) {
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
s32 func_8F1000F4(s32 arg0, void *arg1) {
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100160.s")
#endif

#ifdef VERSION_US
extern u8 D_8F1DF270[];
s32 func_8F10018C(s32 arg0)
{
  s16 *entry = (s16 *) (D_8F1DF270 + (arg0 * 6));
  s16 value;
  s32 result = 0;
  if (((*entry) == 0) || ((*entry) == 6))
  {
    *entry = 1;
    result = 1;
  }
  return result;
}
#endif

#ifdef VERSION_US
s32 func_8F1001D0(s32 arg0)
{
  s16 *temp_v0;
  s16 temp_a1;
  s32 var_v1;
  temp_v0 = (arg0 * 6) + D_8F1DF270;
  ;
  var_v1 = 0;
  if (((*temp_v0) == 3) || ((*temp_v0) == 4))
  {
    *temp_v0 = 5;
    var_v1 = 1;
  }
  return var_v1;
}
#endif

void func_8F100218(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100220.s")
#endif

#ifdef VERSION_US
extern u8 D_8F1DF274[];
void func_8F100274(s32 arg0) { struct Rec { s16 value[3]; }; ((struct Rec *)D_8F1DF274)[arg0].value[0] = 0; }
#endif

#ifdef VERSION_US
void func_8F100290(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (2))) = (s16) ((*(s16 *)((u8 *)(arg0) + (2))) + 1);
    if ((*(s16 *)((u8 *)(arg0) + (2))) >= 8) {
        (*(s16 *)((u8 *)(arg0) + (0))) = 2;
        (*(s16 *)((u8 *)(arg0) + (2))) = 8;
    }
}
#endif

#ifdef VERSION_US
void func_8F1002C4(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (2))) = (s16) ((*(s16 *)((u8 *)(arg0) + (2))) - 1);
    if ((*(s16 *)((u8 *)(arg0) + (2))) <= 0) {
        (*(s16 *)((u8 *)(arg0) + (0))) = 6;
        (*(s16 *)((u8 *)(arg0) + (2))) = 0;
    }
}
#endif

#ifdef VERSION_US
typedef struct {
    s16 state;
    s16 pad2;
    s16 index;
} Fragment69MenuRecord;
typedef struct {
    s16 values[5];
} Fragment69LimitRecord;
extern void *D_80087200;
extern u8 D_8F1DF270[];
extern Fragment69LimitRecord D_8F1039D0[];
void func_8F1002F0(void *arg0) {
    Fragment69MenuRecord *record = (Fragment69MenuRecord *)arg0;
    s32 rowIndex;
    Fragment69LimitRecord *row;

    if ((*(u16 *)((u8 *)D_80087200 + 0xC)) & 0x800) {
        record->index--;
        if (record->index < 0) {
            rowIndex = ((u8 *)record - D_8F1DF270) / 6;
            row = &D_8F1039D0[rowIndex];
            record->index = row->values[0] - 1;
        }
    }
    if ((*(u16 *)((u8 *)D_80087200 + 0xC)) & 0x400) {
        rowIndex = ((u8 *)record - D_8F1DF270) / 6;
        row = &D_8F1039D0[rowIndex];
        record->index++;
        if (record->index >= row->values[0]) record->index = 0;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 0xC)) & 0x8000) {
        record->state = 3;
        return;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 0xC)) & 0x4000) record->state = 4;
}
#endif

#ifdef VERSION_US
extern u8 D_8F1DF282[];
extern void func_8F100290(void *);
extern void func_8F1002F0(void *);
extern void func_8F1002C4(void *);
void func_8F1003EC(void)
{
  u8 *ptr;
 ptr = D_8F1DF270; do {
    switch (*((s16 *) ptr))
    {
      case 1:
        func_8F100290(ptr);
        break;

      case 2:
        func_8F1002F0(ptr);
        break;

      case 5:
        func_8F1002C4(ptr);
        break;

    }

    ptr += 6;
  }
  while (ptr != D_8F1DF282);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F10049C.s")
#endif

#ifdef VERSION_US
typedef struct {
    s16 state;
    s16 timer;
    s16 selected;
} Fragment69MenuState;
extern s16 D_8F1039C8[][5];
extern u8 D_8F1039E8[];
extern u8 D_8F103A04[];
extern void *D_8F103A20[];
extern void *D_8F103A28[];
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void Font_EnableTwoCycleTexturing(void);
extern void func_800497E4(s32, s32, s32, s32);
extern s32 func_8003514C(void);
extern void func_800495BC(s32, s32, void *);
extern void Font_DisableTwoCycleTexturing(void);
extern void func_800499EC(void);
void func_8F100594(Fragment69MenuState *arg0) {
    void *text;
    void *itemText;
    s32 item;
    s32 tableOffset;
    s32 yOffset;
    s16 *position;

    func_800498C4();
    func_800496A4(0x20, 0);
    func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
    Font_EnableTwoCycleTexturing();
    func_800497E4(0, 0xFF, 0, 0xFF);
    if (func_8003514C() == 0) {
        text = D_8F1039E8;
    } else {
        text = D_8F103A04;
    }
    position = D_8F1039C8[((u8 *)arg0 - D_8F1DF270) / 6];
    func_800495BC(position[0] + 0xA, position[1] + 4, text);
    Font_DisableTwoCycleTexturing();
    item = 0; tableOffset = 0; yOffset = 0; do {
        if (item == arg0->selected) {
            func_8004972C(0xFF, 0xFF, 0, 0xFF);
        } else {
            func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
        }
        if (func_8003514C() == 0) {
            itemText = *(void **)((u8 *)D_8F103A20 + tableOffset);
        } else {
            itemText = *(void **)((u8 *)D_8F103A28 + tableOffset);
        }
        func_800495BC(position[0] + 0xA, position[1] + yOffset + 0x28, itemText);
        item++;
        tableOffset += 4;
        yOffset += 0xE;
    } while (item != 2);
    func_800499EC();
}
#endif

#ifdef VERSION_US
extern u8 D_8F103A30[];
extern u8 D_8F103A48[];
void func_8F100740(Fragment69MenuState *arg0) {
    void *text;
    void *itemText;
    s32 item;
    s32 tableOffset;
    s32 yOffset;
    s16 *position;

    func_800498C4();
    func_800496A4(0x20, 0);
    func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
    Font_EnableTwoCycleTexturing();
    func_800497E4(0xFF, 0, 0, 0xFF);
    if (func_8003514C() == 0) {
        text = D_8F103A30;
    } else {
        text = D_8F103A48;
    }
    position = D_8F1039C8[((u8 *)arg0 - D_8F1DF270) / 6];
    func_800495BC(position[0] + 0xA, position[1] + 4, text);
    Font_DisableTwoCycleTexturing();
    item = 0; tableOffset = 0; yOffset = 0; do {
        if (item == arg0->selected) {
            func_8004972C(0xFF, 0xFF, 0, 0xFF);
        } else {
            func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
        }
        if (func_8003514C() == 0) {
            itemText = *(void **)((u8 *)D_8F103A20 + tableOffset);
        } else {
            itemText = *(void **)((u8 *)D_8F103A28 + tableOffset);
        }
        func_800495BC(position[0] + 0xA, position[1] + yOffset + 0x14, itemText);
        item++;
        tableOffset += 4;
        yOffset += 0xC;
    } while (item != 2);
    func_800499EC();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1008EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100B54.s")
#endif

#ifdef VERSION_US
extern f32 D_8F104010;
extern s32 D_8F1DECA4;
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_800371B4(f32 *, s32 *, f32, s16, s32);
extern void func_80038E14(s32, s32, s32, s32, f32, f32, f32, s32);
extern void GeoCamera_SetPerspective(void *, f32, f32, f32);
void func_8F100C64(f32 arg0, void *arg1) {
    f32 position[3];
    s32 output[3];

    Vec3f_SetComponentsDuplicate(position, 0.0f, 250.0f / arg0, 0.0f);
    func_800371B4(position, output, D_8F104010 / arg0, *(s16 *)((u8 *)arg1 + 0), *(s16 *)((u8 *)arg1 + 2));
    func_80038E14(*(s32 *)((u8 *)(u32)D_8F1DECA4 + 0xC), output[0], output[1], output[2], position[0], position[1], position[2], 0);
    GeoCamera_SetPerspective((void *)(u32)*(s32 *)((u8 *)(u32)D_8F1DECA4 + 0xC), 30.0f, 100.0f / arg0, 12800.0f / arg0);
}
#endif

#ifdef VERSION_US
extern s32 func_8004B7E0(s32, void *);
extern s32 func_8004B8E4(s32);
typedef struct { f32 x; f32 y; f32 z; } Func8F100D58Vec3f;

void func_8F100D58(s32 arg0, void *arg1) {
    Func8F100D58Vec3f sp1C;

    func_8004B7E0(arg0, &sp1C);
    if (sp1C.y > -150.0f) {
        *(f32 *)((u8 *)arg1 + 4) = (f32)(func_8004B8E4(arg0) * 4);
        return;
    }
    *(f32 *)((u8 *)arg1 + 4) = 0.0f;
}
#endif

#ifdef VERSION_US
extern void func_8004D1FC(u8 *);
extern void func_80044270(s16, s16, s16, s16, s32, s32, s32, s32, s32);
void func_8F100DCC(void *arg0, void *arg1) {
    u8 *sp3C;
    void *temp_s0;
    sp3C = *(u8 **)((u8 *)arg0 + 4);
    *(s16 *)((u8 *)arg1 + 2) = (s16)(*(s16 *)((u8 *)arg1 + 2) + 6);
    *(u16 *)((u8 *)arg1 + 4) = (u16)(*(u16 *)((u8 *)arg1 + 4) & 0xFFFD);
    temp_s0 = arg1;
    func_8004D1FC(sp3C);
    func_80044270(*(s16 *)((u8 *)temp_s0 + 0), *(s16 *)((u8 *)temp_s0 + 2),
        (s16)(*(u16 *)(u32)sp3C / 2), (s16)(*(u16 *)((u8 *)sp3C + 2) / 2), 0, 0, 0x800, 0x800, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100E78.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_8F1040A0[];
extern s32 D_8F1DEE24;
extern void Gfx_DrawTextureRgba16(s16, s16, s16, s16, u8 *, s16, s32);
void func_8F10128C(void) {
    u8 *texture;

    texture = D_8F1040A0 + D_8F1DEE24 * 0xC80;
    gSPDisplayList(D_800D0510++, D_80094E38);
    Gfx_DrawTextureRgba16(0xA0, 0x1E, 0x28, 0x28, texture, 0x28, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F101318.s")
#endif

#ifdef VERSION_US
extern void func_800088DC(void);
extern void GfxImage_FillCurrent(void *, u16);
extern void GeoRender_AdvanceFrameCounter(void);
extern void func_8003C6B8(s32);
extern void func_8F10128C(void);
extern void func_8F100B54(void);
extern void func_8F101318(void);
extern void func_80008648(void);
extern void *D_80087200;
extern s32 D_8F103988;
extern s32 D_8F1DECA4;
extern s32 D_8F103984;
void func_8F101CDC(void) {
    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 0x5295);
    if (D_8F103988 != 0) {
        if (D_8F103988 > 0) {
            D_8F103988--;
        }
        GeoRender_AdvanceFrameCounter();
    }
    func_8003C6B8(D_8F1DECA4);
    func_8F10128C();
    if ((*(u16 *)((u8 *)D_80087200 + 8)) & 0x10) {
        D_8F103984 ^= 1;
    }
    if (D_8F103984 != 0) {
        func_8F101318();
    }
    func_8F100B54();
    func_80008648();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F101DA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F101FF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1020A4.s")
#endif

#ifdef VERSION_US
extern void *D_8F1DECB4;
extern void *D_80087200;
extern u8 D_8F1DECA8;
extern s32 D_8F1DEE38;
extern s32 D_8F1DEE3C;
extern void func_8003F3BC(u8 *, s32);
void func_8F102394(void) {
    void *object;
    void *temp_v0;

    object = D_8F1DECB4;
    temp_v0 = (*(void *(**)(s32, s32))((u8 *)object + 0x2C))(0, 0);
    if (*(u8 *)((u8 *)temp_v0 + 5) > 0) {
        if ((*(u16 *)((u8 *)D_80087200 + 0xC)) & 0x200) { D_8F1DEE3C--; }
        if ((*(u16 *)((u8 *)D_80087200 + 0xC)) & 0x100) { D_8F1DEE3C++; }
        if (D_8F1DEE3C < 0) {
            D_8F1DEE3C = *(u8 *)((u8 *)temp_v0 + 5) - 1;
        } else if (D_8F1DEE3C >= (s32)*(u8 *)((u8 *)temp_v0 + 5)) {
            D_8F1DEE3C = 0;
        }
        if ((*(u16 *)((u8 *)D_80087200 + 8)) & 0x8000) {
            D_8F1DEE38 = D_8F1DEE3C;
            func_8003F3BC(&D_8F1DECA8, -1);
            func_8003F3BC(&D_8F1DECA8, D_8F1DEE38);
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102488.s")
#endif

#ifdef VERSION_US
typedef union {
    s32 word;
    s8 bytes[4];
} Fragment69PackedState;
extern s8 D_8F1DEE48[];
extern s32 D_8F1DECA0;
extern s32 D_8F1DECF0;
extern u16 D_8F1DEE26;
extern s32 D_8F1DEE30;
extern s32 D_8F1DEE44;
extern s32 D_8F1DEE5C;
extern s32 func_80041FD0(s32, u16, Fragment69PackedState, s32);
void func_8F102618(void) {
    if (*(u16 *)((u8 *)D_80087200 + 0xC) & 0x200) {
        D_8F1DEE48[3]--;
        if (D_8F1DEE48[3] < -8) {
            D_8F1DEE48[3] = 8;
        }
    }
    if (*(u16 *)((u8 *)D_80087200 + 0xC) & 0x100) {
        D_8F1DEE48[3]++;
        if (D_8F1DEE48[3] >= 9) {
            D_8F1DEE48[3] = -8;
        }
    }
    if (D_8F1DEE44 != ((Fragment69PackedState *)D_8F1DEE48)->word) {
        D_8F1DEE5C = 0;
        if (func_80041FD0(D_8F1DECA0, D_8F1DEE26, *(Fragment69PackedState *)D_8F1DEE48, 0) != 0) {
            D_8F1DEE44 = ((Fragment69PackedState *)D_8F1DEE48)->word;
            D_8F1DEE30 = D_8F1DECF0;
        }
    }
}
#endif

#ifdef VERSION_US
void func_8F102708(void) {
    if (*(u16 *)((u8 *)D_80087200 + 0xC) & 0x200) {
        D_8F1DEE48[2]--;
        if (D_8F1DEE48[2] < -8) {
            D_8F1DEE48[2] = 8;
        }
    }
    if (*(u16 *)((u8 *)D_80087200 + 0xC) & 0x100) {
        D_8F1DEE48[2]++;
        if (D_8F1DEE48[2] >= 9) {
            D_8F1DEE48[2] = -8;
        }
    }
    if (D_8F1DEE44 != ((Fragment69PackedState *)D_8F1DEE48)->word) {
        D_8F1DEE5C = 0;
        if (func_80041FD0(D_8F1DECA0, D_8F1DEE26, *(Fragment69PackedState *)D_8F1DEE48, 0) != 0) {
            D_8F1DEE44 = ((Fragment69PackedState *)D_8F1DEE48)->word;
            D_8F1DEE30 = D_8F1DECF0;
        }
    }
}
#endif

#ifdef VERSION_US
extern void Dma_CopyChunks(s32 *, s32, s32);
s32 func_800356CC(s32);
extern u8 D_8F1DEE68;

void func_8F1027F8(void) {
    s32 temp_v0;

    temp_v0 = func_800356CC(9);
    Dma_CopyChunks(&D_8F1DEE68, temp_v0, temp_v0 + 0x408);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F10282C.s")
#endif

#ifdef VERSION_US
extern u8 D_8F1DECA8;
void func_8F1029CC(void) {
    if ((*(u16 *)((u8 *)(D_80087200) + (0xC))) & 0x200) {
        (*(u8 *)((u8 *)(&D_8F1DECA8) + (0x1D))) = (u8) ((*(u8 *)((u8 *)(&D_8F1DECA8) + (0x1D))) - 1);
    }
    if ((*(u16 *)((u8 *)(D_80087200) + (0xC))) & 0x100) {
        (*(u8 *)((u8 *)(&D_8F1DECA8) + (0x1D))) = (u8) ((*(u8 *)((u8 *)(&D_8F1DECA8) + (0x1D))) + 1);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102A20.s")
#endif

#ifdef VERSION_US
extern s32 func_80041FD0(s32, u16, Fragment69PackedState, s32);
void func_8F102A98(void) {
    s32 previous;
    s32 var_a3;

    previous = D_8F1DEE5C;
    if ((*(u16 *)((u8 *)D_80087200 + 0xC)) & 0x200) {
        D_8F1DEE5C--;
        if (D_8F1DEE5C < 0) {
            D_8F1DEE5C = 0;
        }
    }
    if ((*(u16 *)((u8 *)D_80087200 + 0xC)) & 0x100) {
        D_8F1DEE5C++;
        if (D_8F1DEE5C >= 2) {
            D_8F1DEE5C = 1;
        }
    }
    if (previous != D_8F1DEE5C) {
        if (D_8F1DEE5C != 0) {
            var_a3 = 1;
        } else {
            var_a3 = 0;
        }
        func_80041FD0(D_8F1DECA0, D_8F1DEE26, *(Fragment69PackedState *)&D_8F1DEE44, var_a3);
    }
}
#endif

#ifdef VERSION_US
void func_8F102B48(void) {
    if ((*(u16 *)((u8 *)(D_80087200) + (0xC))) & 0x200) {
        (*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) = (s8) ((*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) - 1);
        if ((*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) < 0) {
            (*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) = 0;
        }
    }
    if ((*(u16 *)((u8 *)(D_80087200) + (0xC))) & 0x100) {
        (*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) = (s8) ((*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) + 1);
        if ((*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) >= 0x10) {
            (*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) = 0xF;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102BC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102D98.s")
#endif

#ifdef VERSION_US
extern s32 func_8F100220(s32);
extern void func_8004BE50(void);
s32 func_8F102F58(void) {
    s32 var_v1;

    var_v1 = func_8F100220(1);
    if (var_v1 == 1) {
        func_8004BE50();
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
extern s32 func_8F100220(s32 arg0);
void func_8F102F94(void) {
    func_8F100220(2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102FB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F103194.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F103478.s")
#endif

#ifdef VERSION_US
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern void func_8F102FB4(s32, s32);
extern void func_8F101DA0(void);
extern s32 func_8F103478(s32);
extern s32 D_8F1DEE58;
extern void func_8F1003EC(void);
extern void func_8F101CDC(void);
void func_8F1036F4(void) {
    s32 var_a1;
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    do {
        func_80064D28();
        if ((4 != D_8F1DEE58) && (5 != D_8F1DEE58) && (6 != D_8F1DEE58)) {
            var_a1 = 1;
        } else {
            var_a1 = 0;
        }
        func_8F102FB4(0, var_a1);
        func_8F1003EC();
        func_8F101DA0();
        func_8F101CDC();
        temp_v0 = func_8F103478(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 8);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1037C4.s")
#endif
