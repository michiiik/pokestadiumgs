#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_80094DE0[];
void func_8F800020(s32 arg0, s32 arg1, s32 arg2) {
    gSPDisplayList(D_800D0510++, D_80094DE0);
    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, 0xFFC7FFC1);
    gDPFillRectangle(D_800D0510++, arg0, arg1, arg0 + arg2, arg1 + 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F8000D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F8006B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F800924.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F800E50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F800F7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F8010E4.s")

extern s32 D_8F809F98, D_8F809F9C, D_8F809FA0, D_8F809FA4;
extern u8 *D_8F809FA8, *D_8F809FB0;
extern u8 D_8F803BF0, D_8F803BF4, D_8F803E08;
extern u8 *func_8006218C(s32, s32, s32, s32);
extern s32 func_80062390(void*, s32, u8*);
extern s32 func_80062304(u8*);
void func_8F8012C0(u8 slot) {
    u8* data;

    if (slot == 0) {
        data = func_8006218C(0x20, D_8F809F98, 0, 0);
        D_8F803BF0 = func_80062390(&D_8F803BF4, 6, data);
        D_8F809FA0 = D_8F803BF0;
        D_8F809FA8 = &D_8F803BF4;
    } else {
        data = func_8006218C(0x21, D_8F809F98, slot - 1, 0);
        *((u8*)&D_8F803E08 + slot * 0x6F8 - 0x6F8) =
            func_80062390((u8*)&D_8F803E08 + slot * 0x6F8 - 0x6F4, 30, data);
        D_8F809FA0 = *((u8*)&D_8F803E08 + slot * 0x6F8 - 0x6F8);
        D_8F809FA8 = (u8*)&D_8F803E08 + slot * 0x6F8 - 0x6F4;
    }
    func_80062304(data);
    D_8F809F9C = slot;
    D_8F809FA4 = 0;
    D_8F809FB0 = D_8F809FA8 + D_8F809FA4 * 0x58;
}

extern s32 D_8F809F98;
extern u16 D_8F809FF0;
extern u8 D_8F803BF0;
extern u8 D_8F803BF4;
extern u8 D_8F803E08;
extern void func_8005DAC8(s32, u16);
extern void func_8006249C(void *, s32, u8 *);
extern void func_8005B058(s32);
extern void func_80059468(s32);
extern s32 func_80062304(u8 *);
void func_8F8013FC(u8 arg0) {
    u8 *sp1C;

    func_8005DAC8(D_8F809F98, D_8F809FF0);
    if (arg0 == 0) {
        sp1C = func_8006218C(0x20, D_8F809F98, 0, 1);
        func_8006249C(&D_8F803BF4, (s32)D_8F803BF0, sp1C);
        func_8005B058(D_8F809F98);
    } else {
        sp1C = func_8006218C(0x21, D_8F809F98, arg0 - 1, 1);
        func_8006249C((u8 *)&D_8F803E08 + (s32)arg0 * 0x6F8 - 0x6F4,
                      *(u8 *)((u8 *)&D_8F803E08 + (s32)arg0 * 0x6F8 - 0x6F8),
                      sp1C);
        func_80059468(D_8F809F98);
    }
    func_80062304(sp1C);
}

extern u16 D_8F8034CC[][17];
extern s32 D_8F809FB4, D_8F809FB8;
typedef union {
    u16 halfwords[18];
    s32 words[9];
    s8 bytes[36];
} F77EditorState;
extern F77EditorState D_8F809FC0;
extern u8 D_8F809FE4, D_8F809FE8, D_8F809FE9, D_8F809FEA;
extern u16 D_8F809FE6;
extern void func_8F8015A8(void);
extern s32 func_8F801FC4(void);
extern void func_8F800924(void);
extern void func_8F801988(void);
extern void func_800226C0(s32);
void func_8F8014E4(void) {
    D_8F809FE4++;
    if (D_8F809FE4 >= 30) {
        D_8F809FE4 -= 30;
        D_8F809FEA++;
        if (D_8F809FEA >= 60) {
            D_8F809FEA -= 60;
            D_8F809FE9++;
            if (D_8F809FE9 >= 60) {
                D_8F809FE9 -= 60;
                D_8F809FE8++;
                if (D_8F809FE8 >= 24) {
                    D_8F809FE8 -= 24;
                    D_8F809FE6++;
                    D_8F809FE6 &= 0xFF;
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F8015A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F801988.s")

extern s32 D_8F809FB4;
void func_8F801F44(void) {
    D_8F809FC0.halfwords[0] = D_8F8034CC[D_8F809FB4][1];
    D_8F809FC0.halfwords[1] = D_8F8034CC[D_8F809FB4][2];
    D_8F809FC0.halfwords[2] = D_8F8034CC[D_8F809FB4][5] * 20;
    func_8F8015A8();
    D_8F809FC0.halfwords[3] = D_8F809FC0.halfwords[6] * 20;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F801FC4.s")

s32 func_8F8021E8(void) {
    s32 event;

    event = func_8F801FC4();
    func_8F800924();
    if (event == 1) {
        func_800226C0(2);
        if (((s16*)D_8F809FC0.halfwords)[4] < D_8F8034CC[D_8F809FB4][3]) {
            ((s16*)D_8F809FC0.halfwords)[4] = D_8F8034CC[D_8F809FB4][3];
        }
        if (((s16*)D_8F809FC0.halfwords)[4] > D_8F8034CC[D_8F809FB4][4]) {
            ((s16*)D_8F809FC0.halfwords)[4] = D_8F8034CC[D_8F809FB4][4];
        }
        func_8F801988();
        D_8F809FB8 = 0;
    } else if (event == 2) {
        func_800226C0(3);
        D_8F809FB8 = 0;
    }
    return 1;
}

extern u16 D_8F8034D6[][17];
void func_8F8022B4(void) {
    D_8F809FC0.halfwords[0] = 230;
    D_8F809FC0.halfwords[1] = 150;
    D_8F809FC0.halfwords[2] = 180;
    D_8F809FC0.halfwords[3] = 170;
    D_8F809FC0.halfwords[16] = D_8F8034D6[D_8F809FB4][0];
    D_8F809FC0.halfwords[4] = 0;
    D_8F809FC0.halfwords[5] = 0;
    func_8F8015A8();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F802324.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F8023B8.s")

extern s32 func_8F8023B8(void);
extern s32 func_8F8006B0(void);
extern s32 D_8F809FB8;
s32 func_8F802670(void) {
    s32 sp1C;

    sp1C = func_8F8023B8();
    func_8F8006B0();
    if (sp1C == 1) {
        func_8F801988();
        D_8F809FB8 = 0;
    } else if (sp1C == 2) {
        func_800226C0(3);
        D_8F809FB8 = 0;
    }
    return 1;
}

void func_8F8026DC(void) {
    s32 value;
    s32 index;

    D_8F809FC0.halfwords[0] = D_8F8034CC[D_8F809FB4][1];
    D_8F809FC0.halfwords[1] = D_8F8034CC[D_8F809FB4][2];
    D_8F809FC0.halfwords[2] = D_8F8034CC[D_8F809FB4][5] * 20;
    D_8F809FC0.halfwords[3] = 20;
    D_8F809FC0.halfwords[4] = 0;
    D_8F809FC0.halfwords[5] = D_8F8034CC[D_8F809FB4][5] - 1;
    func_8F8015A8();
    value = ((s32*)D_8F809FC0.halfwords)[5];
    index = 0;
    if (index <= D_8F809FC0.halfwords[5]) {
        do {
            D_8F809FC0.bytes[index + 12] = value % 10;
            value /= 10;
            index++;
        } while (index <= D_8F809FC0.halfwords[5]);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F8027C4.s")

extern s32 func_8F8027C4(void);
extern s32 func_8F802B40(void);
extern void func_8F800E50(void);
extern void func_8F800F7C(void);
s32 func_8F80299C(void) {
    s32 event;

    event = func_8F8027C4();
    func_8F800E50();
    if (event == 1) {
        func_800226C0(2);
        if (((s32*)D_8F809FC0.halfwords)[5] < D_8F8034CC[D_8F809FB4][3]) {
            ((s32*)D_8F809FC0.halfwords)[5] = D_8F8034CC[D_8F809FB4][3];
        }
        if (((s32*)D_8F809FC0.halfwords)[5] > D_8F8034CC[D_8F809FB4][4]) {
            ((s32*)D_8F809FC0.halfwords)[5] = D_8F8034CC[D_8F809FB4][4];
        }
        func_8F801988();
        D_8F809FB8 = 0;
    } else if (event == 2) {
        func_800226C0(3);
        D_8F809FB8 = 0;
    }
    return 1;
}

void func_8F802A68(void) {
    s32 value;
    s32 index;

    D_8F809FC0.halfwords[0] = D_8F8034CC[D_8F809FB4][1];
    D_8F809FC0.halfwords[1] = D_8F8034CC[D_8F809FB4][2];
    D_8F809FC0.halfwords[2] = D_8F8034CC[D_8F809FB4][5] * 20;
    D_8F809FC0.halfwords[3] = 20;
    D_8F809FC0.halfwords[4] = 0;
    D_8F809FC0.halfwords[5] = D_8F8034CC[D_8F809FB4][5] - 1;
    func_8F8015A8();
    value = ((s32*)D_8F809FC0.halfwords)[5];
    index = 0;
    if (index <= D_8F809FC0.halfwords[5]) {
        do {
            D_8F809FC0.bytes[index + 12] = value % 16;
            value /= 16;
            index++;
        } while (index <= D_8F809FC0.halfwords[5]);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F802B40.s")

s32 func_8F802D0C(void) {
    s32 event;

    event = func_8F802B40();
    func_8F800F7C();
    if (event == 1) {
        func_800226C0(2);
        if (((s32*)D_8F809FC0.halfwords)[5] < D_8F8034CC[D_8F809FB4][3]) {
            ((s32*)D_8F809FC0.halfwords)[5] = D_8F8034CC[D_8F809FB4][3];
        }
        if (((s32*)D_8F809FC0.halfwords)[5] > D_8F8034CC[D_8F809FB4][4]) {
            ((s32*)D_8F809FC0.halfwords)[5] = D_8F8034CC[D_8F809FB4][4];
        }
        func_8F801988();
        D_8F809FB8 = 0;
    } else if (event == 2) {
        func_800226C0(3);
        D_8F809FB8 = 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F802DD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F802ECC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F803130.s")

extern u8 D_8F8044EC[];
extern s32 D_80087200;
extern u16 D_8F809FE6, D_8F809FF0;
extern void Input_SetRepeatController(s32);
extern s32 func_8005A134(s32);
extern void func_8005F37C(s32, s32, s32, s32, s32);
extern void func_8F8012C0(u8);
extern void *func_8005EE88(s32, s32, void*);
extern s32 func_8005DA1C(s32);
void func_8F8031F8(s32 id) {
    s32 index;

    D_8F809F98 = id;
    D_8F809FB4 = 1;
    D_8F809F9C = 0;
    D_8F809FA4 = 0;
    D_8F809FA0 = 0;
    D_8F809FA8 = &D_8F803BF4;
    D_8F809FB0 = D_8F809FA8 + D_8F809FA4 * 0x58;
    D_8F809FB8 = 0;
    Input_SetRepeatController(D_80087200);
    func_8005A134(D_8F809F98);
    func_8005F37C((u8)D_8F809F98, (s32)&D_8F809FE6, (s32)&D_8F809FE8, (s32)&D_8F809FE9, (s32)&D_8F809FEA);
    D_8F809FE4 = 0;
    func_8F8012C0((u8)D_8F809F9C);
    for (index = 0; index < 14; index++) {
        func_8005EE88(D_8F809F98, index, D_8F8044EC + index * 0x6F8);
    }
    D_8F809FF0 = func_8005DA1C(D_8F809F98);
}

extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern s32 func_8005D8C0(void);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern s32 func_80047588(s32, s32);
extern void func_8004C09C(s32);
extern void func_8004C4B0(s32);
extern void Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern void func_8F8031F8(s32);
extern void func_80057908(s32);
extern void func_80008514(s32);
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_8F803130(void);
extern void func_80008574(void);
extern void func_80047610(void);
extern void func_80057944(s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 D_8F809FEC;
extern s32 D_1000000;
extern u8 D_446E30[];
extern u8 D_447D00[];
s32 fragment77_main(s32 arg0, s32 arg1) {
    s32 sp24;

    main_pool_push_state(0x504D4544);
    if (!(func_8005D8C0() & 1)) {
        return 0;
    }
    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    D_8F809FEC = func_80047588(0x1E, 0);
    func_8004C09C(3);
    func_8004C4B0(6);
    func_8004C4B0(8);
    func_8004C4B0(0x41);
    Asset_LoadToSegment((((u32)&D_1000000) & 0x0F000000) >> 24,
                        &D_446E30, &D_447D00, 0);
    func_8F8031F8(0);
    func_80057908(0);
    func_80008514(sp24);
    func_800086A4(2);
    StageFade_StartFromOpaque(0x10);
    func_8F803130();
    func_80008574();
    func_80047610();
    func_80057944(0);
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x504D4544);
    return 0;
}
#endif
