#include "global.h"


#ifdef VERSION_US
extern void Input_SetRepeatController(void *);
extern void *D_80087200;
extern s32 D_880068B8;

void func_882243C0(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void Util_Free(s32);
extern s32 D_880068B4;
extern u32 D_88234860;
void func_882243E8(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B4 = 1;
    Util_Free(D_88234860);
}

extern void func_88004990(u8, s32);
extern u32 D_88234860;
void func_88224424(void) {
    func_88004990(*(*(u8 **)((u8 *)(D_88234860) + 0)), 0);
    D_880068B8 = 1;
}

extern u32 D_88234860;
s32 func_8822445C(void) {
    typedef struct {
        u8 pad[0x36];
        u8 slots[4];
    } LookupRecord;
    s32 result;
    u8 i;

    result = 0;
    for (i = 0; i < 4; i++) {
        if (((LookupRecord *)D_88234860)->slots[i] == 0) {
            break;
        }
    }
    if (i == 4) {
        result = 1;
    }
    return result;
}

extern u32 D_88234860;
s32 func_882244B0(u8 arg0) {
    s32 result = 0;
    u8 i;
    for (i = 0; i < 4; i++) {
        if (arg0 == *((u8 *)D_88234860 + i + 0x36)) {
            result = 1;
            break;
        }
    }
    return result;
}

extern void func_880022B4(s32, s32, s32);
void func_882244F8(s32 arg0) {
    (*(s32 *)((u8 *)(D_88234860) + (0x30))) = arg0;
    if (arg0 != 0) {
        func_880022B4(D_88234860 + 4, 0xF00, 0);
        return;
    }
    func_880022B4(D_88234860 + 4, 0xF00, 1);
}

typedef struct Func88224554StateV2 {
    u8 pad00[0xC];
    s16 cursor;
    u8 pad0E[0x26];
    s16 slot;
    u8 assigned[5];
    u8 choices[256];
} Func88224554StateV2;
extern void Input_SetRepeatController(void *);
extern void func_800226C0(s32);
extern s32 func_8822445C(void);
extern void func_882244F8(s32 arg0);
extern void * D_80087200;
extern u32 D_88234860;
void func_88224554(void) {
    u8 i;
    u8 value;
    u8 cleared;

    value = ((Func88224554StateV2 *)D_88234860)->choices[((Func88224554StateV2 *)D_88234860)->cursor];
    cleared = 0;
    Input_SetRepeatController(D_80087200);
    func_882244F8(1);
    if (value != ((Func88224554StateV2 *)D_88234860)->assigned[((Func88224554StateV2 *)D_88234860)->slot]) {
        func_800226C0(0x47);
        ((Func88224554StateV2 *)D_88234860)->assigned[((Func88224554StateV2 *)D_88234860)->slot] = value;
    } else {
        func_800226C0(0x48);
        ((Func88224554StateV2 *)D_88234860)->assigned[((Func88224554StateV2 *)D_88234860)->slot] = 0;
        cleared = 1;
    }
    for (i = 0; i < 4; i++) {
        if (value != ((Func88224554StateV2 *)D_88234860)->assigned[i]) {
            continue;
        }
        if (i == ((Func88224554StateV2 *)D_88234860)->slot) {
            continue;
        }
        ((Func88224554StateV2 *)D_88234860)->assigned[i] = 0;
    }
    if (func_8822445C()) {
        ((Func88224554StateV2 *)D_88234860)->slot = 4;
    } else if (cleared == 0) {
        ((Func88224554StateV2 *)D_88234860)->slot++;
    }
}

extern u8 D_88234758[];
extern u8 D_88234761[];

s32 func_88224688(void) {
    u8 *output;
    s32 result;
    s32 index;
    u8 value;

    result = 0;
    output = D_88234761;
    for (index = 0; index < 4; index = (index + 1) & 0xFF) {
        D_88234758[index + 9] = 0;
    }
    for (index = 0; index < 4; index = (index + 1) & 0xFF) {
        value = ((u8 *)(u32)D_88234860)[index + 0x36];
        if (value != 0) {
            result = 1;
            *output++ = value;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_882246FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_8822497C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_882254B8.s")

void func_88225B70(void) {
    D_880068B8 = 0;
}

extern u8 D_8823474C;
void func_88225B7C(void) { D_880068B8 = 1; D_8823474C = 2; }

extern void func_888002DC(void);
void func_88225B98(void) { D_880068B4 = 1; func_888002DC(); }

extern void func_88800020();
s32 func_88802DCC(s32, s32, void (*)(), void (*)(), void (*)(), s32 *, s32, s32);
extern u8 func_882313A4;

void func_88225BC0(s32 arg0) {
    func_88800020();
    func_88802DCC(0, arg0, func_88225B70, func_88225B98, func_88225B7C, &func_882313A4, 2, 0);
}

void func_88225C20(void) { Input_SetRepeatController(D_80087200); D_880068B8 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88225C48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88225D80.s")

extern u8 *D_88234870;
s32 func_88225EA0(void) {
    u32 index;
    s32 result;
    u8 *state;
    u32 count;
    u8 *entry;
    result = 0;
    index = 0;
    state = D_88234870;
    count = *(u16 *)(state + 0x18);
    if (count != 0) {
        entry = *(u8 **)(state + 0x98);
loop:
        if (*entry != 0) {
            result = 1;
            goto done;
        }
        index++;
        entry++;
        if (index < count) {
            goto loop;
        }
    }
done:
    return result;
}

s32 func_88225EEC(void) {
    u32 index;
    s32 result;
    u8 *state;
    u32 count;
    u8 *entry;
    result = 0;
    index = 0;
    state = D_88234870;
    count = *(u16 *)(state + 0x28);
    if (count != 0) {
        entry = *(u8 **)(state + 0x9C);
loop:
        if (*entry != 0) {
            result = 1;
            goto done;
        }
        index++;
        entry++;
        if (index < count) {
            goto loop;
        }
    }
done:
    return result;
}

extern s32 func_88225EA0(void);
extern s32 func_88225EEC(void);
extern u8 * D_88234870;
void func_88225F38(void)
{
  s32 first;
  s32 second;
  first = func_88225EA0();
  second = func_88225EEC();
  if (((second + (*(((u8 *) D_88234870) + 0x94))) + first) != ((0, 0)))
  {
    *((s32 *) (((u8 *) D_88234870) + 0x88)) = 0;
    *(((u8 *) D_88234870) + 0x93) = 0;
  }
  else
  {
    *((s32 *) (((u8 *) D_88234870) + 0x88)) = 1;
    *(((u8 *) D_88234870) + 0x93) = 1;
  }
}

extern u8 * D_88234870;
s32 func_88225FA8(void) {
    u32 i;
    s8 *p;

    i = 0;
    p = (s8 *)D_88234870 + 0xA0;
    for (; i < 3; i++, p += 2) {
        if (*p != 0) {
            return 1;
        }
    }
    i = 0;
    p = *(s8 **)((u8 *)D_88234870 + 0xA8);
    for (; i < *(u16 *)((u8 *)D_88234870 + 0x18); i++, p += 2) {
        if (*p != 0) {
            return 1;
        }
    }
    i = 0;
    p = *(s8 **)((u8 *)D_88234870 + 0xAC);
    for (; i < *(u16 *)((u8 *)D_88234870 + 0x28); i++, p += 2) {
        if (*p != 0) {
            return 1;
        }
    }
    return 0;
}

void func_88226058(u8 *arg0, u8 arg1) { arg0[1] = arg1 ? 1 : -1; }

void func_88226080(void *arg0) {
    s8 temp_v0;
    s8 temp_v0_2;
    s8 temp_v0_3;

    temp_v0 = (*(s8 *)((u8 *)(arg0) + (1)));
    if (temp_v0 > 0) {
        (*(s8 *)((u8 *)(arg0) + (0))) = (s8) ((*(s8 *)((u8 *)(arg0) + (0))) + 1);
        temp_v0_2 = (*(s8 *)((u8 *)(arg0) + (0)));
        if (temp_v0_2 == 0) {
            (*(s8 *)((u8 *)(arg0) + (1))) = 0;
            return;
        }
        if (temp_v0_2 == 2) {
            (*(s8 *)((u8 *)(arg0) + (1))) = -1;
        }
    } else if (temp_v0 < 0) {
        (*(s8 *)((u8 *)(arg0) + (0))) = (s8) ((*(s8 *)((u8 *)(arg0) + (0))) - 1);
        temp_v0_3 = (*(s8 *)((u8 *)(arg0) + (0)));
        if (temp_v0_3 == 0) {
            (*(s8 *)((u8 *)(arg0) + (1))) = 0;
            return;
        }
        if (temp_v0_3 == -2) {
            (*(s8 *)((u8 *)(arg0) + (1))) = 1;
        }
    }
}

extern void func_88226080(void *arg0);
extern u8 * D_88234870;
void func_88226100(void) {
    u32 i;
    u16 *p;

    i = 0;
    p = (u16 *)((u8 *)D_88234870 + 0xA0);
    for (; i < 3; i++, p++) {
        func_88226080(p);
    }
    i = 0;
    p = *(u16 **)((u8 *)D_88234870 + 0xA8);
    for (; i < *(u16 *)((u8 *)D_88234870 + 0x18); i++, p++) {
        func_88226080(p);
    }
    i = 0;
    p = *(u16 **)((u8 *)D_88234870 + 0xAC);
    for (; i < *(u16 *)((u8 *)D_88234870 + 0x28); i++, p++) {
        func_88226080(p);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_882261CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88226378.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88226918.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88227224.s")

void func_882277D0(void) { Input_SetRepeatController(D_80087200); D_880068B8 = 0; }

typedef struct Func882277F8Data {
    u8 pad00[0x10];
    u16 countA;
    u8 pad12[6];
    s32 blockA;
    u8 pad1C[4];
    u16 countB;
    u8 pad22[6];
    s32 blockB;
    u8 pad2C[12];
    s32 *arrayA;
    s32 *arrayB;
} Func882277F8Data;
extern void Util_Free(s32);
extern void * D_88234880;
void func_882277F8(void) {
    u32 i;

    for (i = 0; i < *(u16 *)((u8 *)D_88234880 + 0x10); i++) {
        Util_Free((*(s32 **)((u8 *)D_88234880 + 0x38))[i]);
    }
    for (i = 0; i < *(u16 *)((u8 *)D_88234880 + 0x20); i++) {
        Util_Free((*(s32 **)((u8 *)D_88234880 + 0x3C))[i]);
    }
    Util_Free(*(s32 *)((u8 *)D_88234880 + 0x18));
    Util_Free(*(s32 *)((u8 *)D_88234880 + 0x28));
    Util_Free(*(s32 *)((u8 *)D_88234880 + 0x38));
    Util_Free(*(s32 *)((u8 *)D_88234880 + 0x3C));
    Util_Free((s32)D_88234880);
}

extern void func_88001900();
extern void func_882277F8();
extern void *D_88234880;

void func_882278EC(void) {
    func_88001900();
    D_880068B4 = (*(s32 *)((u8 *)(D_88234880) + (0x64)));
    func_882277F8();
}

extern void func_88004990(u8, s32);
void func_88227924(void) {
    func_88004990(*(*(u8 **)((u8 *)(D_88234880) + (0))), 0);
    func_88004990(*(*(u8 **)((u8 *)(D_88234880) + (4))), 0);
    D_880068B8 = 1;
}

extern void *func_8004C874(s32, void *);
extern s32 func_88903C50();
extern void func_88903B00();
extern u8 D_88000E4C[];
extern void * D_88234880;
void func_88227974(void *arg0) {
    void *temp;

    temp = func_8004C874(0x1F, arg0);
    func_88903C50(temp, 0x17C, 0x11F, 4, 0xFF, 0xAA, 0x8C, 2, 1, *(u8 **)D_88234880 + 0x2C, 0, func_88903B00, D_88000E4C);
}

extern void func_800226C0(s32);
extern void func_882017F8(s32, void *, s8);
extern void func_88227924();
extern void func_882310A0();
extern s32 D_882345F4;
extern s8 D_88234746;
void func_88227A04(void *arg0) {
    func_800226C0(0x5D);
    func_800226C0(0x63);
    D_88234746 = 0;
    func_882310A0();
    func_882017F8(D_882345F4, arg0, (*(s8 *)((u8 *)(arg0) + (0x15))));
    (*(s32 *)((u8 *)(D_88234880) + (0x64))) = 0;
    func_88227924();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88227A60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88227EE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88228390.s")
#endif
