#include "global.h"


#ifdef VERSION_US
extern void func_8004A858(s32, s32, u16, u16, s32 *, s32 *);
extern u8 D_8AF26450;
extern u8 D_8AF26454;
s32 func_8AF0EFF0(void *arg0) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0x18)));
    func_8004A858(0, 0, (*(u16 *)((u8 *)(temp_v0) + (4))), (*(u16 *)((u8 *)(temp_v0) + (6))), &D_8AF26450, &D_8AF26454);
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF0F040.s")

extern void func_800504BC(s16 *);
extern s16 D_8AF2F9E0[][3];

void func_8AF0F1A0(s32 mode, void *record) {
    s16 index;
    s16 values[2];
    s16 *entry;

    index = *(s16 *)((u8 *)record + 0x22);
    if (mode != 0 && mode == 1) {
        func_800504BC(values);
        entry = D_8AF2F9E0[index];
        entry[0] = index + 1;
        entry[1] = *(s16 *)((u8 *)record + 8) + values[0];
        entry[2] = *(s16 *)((u8 *)record + 0xA) + values[1];
    }
}

extern s32 func_80063BB8(u8);
extern s16 D_8AF2F9DE;
extern s16 D_8AF2F9D0[];
extern u8 D_8AF2FA70[][3];
extern u8 D_8AF31D42;
extern u8 func_80062D98(u8);
extern s16 func_8AF01530(s16);
extern u8 *func_8AF12410(u8 *, s16);

void func_8AF0F220(u8 code) {
    struct EvolutionEntry {
        u8 method;
        u8 requirement;
        u8 species;
    };
    u8 *entry;
    u8 *copy;
    s16 index;

    entry = (u8 *)func_80063BB8(code);
    if (entry != NULL) {
        for (;;) {
            if (entry[0] == 0) {
                break;
            }
            D_8AF2F9DE++;
            index = D_8AF2F9DE;
            D_8AF2F9D0[index] = entry[2];
            copy = D_8AF2FA70[index];
            *(struct EvolutionEntry *)copy = *(struct EvolutionEntry *)entry;
            func_8AF0F220(entry[2]);
            entry += 3;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF0F2EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1000C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1025C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF102AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1043C.s")

extern void func_80043E70(s32, s32);
extern s32 D_8AF26A44;

void func_8AF10540(void) {
    if (D_8AF26A44 != 0) {
        func_80043E70(D_8AF26A44, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1060C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF106A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10784.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10840.s")

extern void *D_8AF3011C;
extern void *D_8AF30120;
extern void *D_8AF30124;
extern void *D_8AF30128;
extern void *D_8AF3012C;
extern void *D_8AF30130;
void func_8AF108BC(void) {
    (*(u16 *)((u8 *)(D_8AF3011C) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3011C) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30128) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30128) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30120) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30120) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF3012C) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3012C) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30124) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30124) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30130) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30130) + (2))) | 2);
}

void func_8AF10938(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x28) = arg1;
    *(s32 *)(arg0 + 0x2C) = arg2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10944.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10AB8.s")

extern s16 D_8AF300C4;
extern s16 D_8AF30FF8;
extern s16 D_8AF30FFA;
extern s16 D_8AF30FFC;
extern s16 D_8AF30FFE;
extern s16 D_8AF31000;

void func_8AF10CD4(void) {
    D_8AF31000 = 0;
    D_8AF30FF8 = 0;
    D_8AF30FFC = 0;
    D_8AF30FFA = 0;
    D_8AF30FFE = 0;
    D_8AF300C4 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10D08.s")

void func_8AF11358(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (arg1 < value) {
        value -= arg2;
        if (value < arg1) value = arg1;
        *arg0 = value;
    }
}

void func_8AF11398(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (value < arg1) {
        value += arg2;
        if (arg1 < value) value = arg1;
        *arg0 = value;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF113D8.s")

extern void func_800498C4(void);
extern void func_800499EC(void);
void func_8AF12398(void) {
    func_800498C4();
    func_800499EC();
}

extern s16 *D_8AF2BA94;
extern u8 D_8AF31C48[250];
void func_8AF123C0(void) {
    s16 *source;
    s16 index;
    s16 value;
    s16 sentinel;

    source = D_8AF2BA94;
    index = 0;
    sentinel = -1;
    for (;;) {
        value = *source;
        if (sentinel != value) {
            *((u8 *)&D_8AF31C48 + index) = value;
            index++;
            index = (s16) index;
            if (index >= 250) {
                break;
            }
        }
        source++;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF12410.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF124A8.s")

extern void *func_8004C874(s32, s32);
extern s32 func_8004C54C(s32, s32);
extern void _bzero(s32 *, s32);
extern s16 D_8AF31024;
extern char D_8AF315A0[];
extern char D_8AF296C8[];
extern s16 D_8AF263C4[];
extern u8 D_8AF316C8[];

u8 *func_8AF125D0(s16 category) {
    u8 *output;
    u8 *destination;
    s32 index;
    s16 count;
    s16 selected;
    s16 mapped;
    s16 id;
    u16 saved;

    count = 0;
    D_8AF31024 = 1;
    *(s16 *)&D_8AF31D42 = -1;
    selected = (s16)category;
    sprintf(D_8AF315A0, D_8AF296C8);
    func_8004C54C(0x2F, (s32)func_8004C874(0xC, D_8AF263C4[selected]));
    func_8AF123C0();
    output = D_8AF316C8;
    _bzero((s32 *)output, 1000);
    destination = output;
    for (index = 0; index != 250; index++) {
        id = D_8AF31C48[index];
        saved = id;
        mapped = func_8AF01530(func_80062D98(id));
        if (id == 0xA5) {
            continue;
        }
        if (mapped != selected) {
            continue;
        }
        destination[0] = saved;
        destination[1] = mapped;
        destination += 4;
        count++;
    }
    return func_8AF12410(destination, count);
}

/* Preserve this logical source line for IDO's instruction scheduling. */
u8 *func_8AF1271C(u8 *output, s16 *table, u16 mask) { \
    u8 *entry; \
    u8 *end; \
    u8 *destination; \
    s32 id; \
    s16 count; \
    destination = output;
    count = 0;
    entry = D_8AF31C48; end = &D_8AF31D42;
    do {
        id = *entry;
        if (table[id - 1] & mask) {
            destination[0] = id;
            destination[1] = func_8AF01530(func_80062D98(id));
            destination += 4;
            count++;
        }
        entry++;
    } while (entry != end);
    return func_8AF12410(destination, count);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF127E8.s")

extern u8 D_8AF26F34[];
s32 func_8AF129F8(u8 arg0) {
    u8 *ptr;
    s32 index;
    ptr = &D_8AF26F34;
    index = 0;
    for (;;) {
        if (*ptr != 0xFF) {
            if (arg0 == *ptr) return index;
            ptr++;
            index++;
            index = (s16)index;
        } else {
            return -1;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF12A4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF12E30.s")

extern s32 D_8AF26F30;
extern s16 D_8AF316A4;
extern s16 D_8AF316A6;
extern u8 D_8AF316B8;

void func_8AF12E7C(void) {
    D_8AF316A4 = 0;
    D_8AF316A6 = 0;
    _bzero(&D_8AF316B8, 0xE);
    D_8AF26F30 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF12EB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF133C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF13718.s")
#endif
