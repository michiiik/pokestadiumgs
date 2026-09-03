#include "global.h"


void func_8F700020(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700028.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700420.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700538.s")
#endif

#ifdef VERSION_US
extern u8 D_15833A0[];
extern u8 D_8F702368;
extern void Dma_CopyChunks(u8 *, u8 *, u8 *);
void func_8F70058C(u8 arg0) {
    u8 *temp_a2;
    u8 temp_a3 = arg0;
    if (temp_a3 != 0) {
        temp_a2 = (u8 *)((u32)&D_15833A0 + (temp_a3 * 0x44));
        Dma_CopyChunks(&D_8F702368, temp_a2 - 0x44, temp_a2);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F7005D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700624.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F7006F0.s")
#endif

#ifdef VERSION_US
extern u8 D_8F701358[];
extern s32 D_8F7023B4;
extern void func_800226C0(s32);
extern void func_8F7005D8(void *, s32 *);
extern void func_8F700624(void *, s32 *, u8);
extern void func_8F7006F0(void *, s32);

void func_8F7007B8(u8 arg0) {
    s32 sp1C;

    func_800226C0(1);
    func_8F7005D8((D_8F7023B4 * 0x30) + D_8F701358, &sp1C);
    func_8F700624((D_8F7023B4 * 0x30) + D_8F701358, &sp1C, arg0);
    func_8F7006F0((D_8F7023B4 * 0x30) + D_8F701358, sp1C);
}
#endif

#ifdef VERSION_US
extern s16 D_8F7023BC;
s32 func_8F700858(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 8) & 0x200) {
        D_8F7023BC = 0xB;
        return 0x200;
    }
    if (*(u16 *)((u8 *)arg0 + 8) & 0x100) {
        D_8F7023BC = 0xB;
        return 0x100;
    }
    if (*(u16 *)((u8 *)arg0 + 8) & 0x800) {
        D_8F7023BC = 0xB;
        return 0x800;
    }
    if (*(u16 *)((u8 *)arg0 + 8) & 0x400) {
        D_8F7023BC = 0xB;
        return 0x400;
    }
    if (*(u16 *)((u8 *)arg0 + 8) & 8) {
        D_8F7023BC = 0xB;
        return 8;
    }
    if (*(u16 *)((u8 *)arg0 + 8) & 4) {
        D_8F7023BC = 0xB;
        return 4;
    }
    if (*(u16 *)((u8 *)arg0 + 8) & 2) {
        D_8F7023BC = 0xB;
        return 2;
    }
    if (*(u16 *)((u8 *)arg0 + 8) & 1) {
        D_8F7023BC = 0xB;
        return 1;
    }
    D_8F7023BC -= 1;
    if (D_8F7023BC <= 0) {
        D_8F7023BC = 1;
        if (*(u16 *)((u8 *)arg0 + 6) & 0x200) {
            D_8F7023BC = 2;
            return 0x200;
        }
        if (*(u16 *)((u8 *)arg0 + 6) & 0x100) {
            D_8F7023BC = 2;
            return 0x100;
        }
        if (*(u16 *)((u8 *)arg0 + 6) & 0x800) {
            D_8F7023BC = 2;
            return 0x800;
        }
        if (*(u16 *)((u8 *)arg0 + 6) & 0x400) {
            D_8F7023BC = 2;
            return 0x400;
        }
        if (*(u16 *)((u8 *)arg0 + 6) & 8) {
            D_8F7023BC = 2;
            return 8;
        }
        if (*(u16 *)((u8 *)arg0 + 6) & 4) {
            D_8F7023BC = 2;
            return 4;
        }
        if (*(u16 *)((u8 *)arg0 + 6) & 2) {
            D_8F7023BC = 2;
            return 2;
        }
        if (*(u16 *)((u8 *)arg0 + 6) & 1) {
            D_8F7023BC = 2;
            return 1;
        }
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700A54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700B78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700CA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700DC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700EF4.s")
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
extern void func_8F700EF4(void);
extern s32 D_8F7023B0;
void func_8F700F48(void) {
    func_800226C0(1);
    D_8F7023B0 = D_8F7023B0 + 1;
    if (D_8F7023B0 >= 3) {
        D_8F7023B0 = 0;
    }
    func_8F700EF4();
}
#endif

#ifdef VERSION_US
void func_8F700F90(void) {
    func_800226C0(1);
    D_8F7023B0 = D_8F7023B0 - 1;
    if (D_8F7023B0 < 0) {
        D_8F7023B0 = 2;
    }
    func_8F700EF4();
}
#endif

#ifdef VERSION_US
extern u8 D_8F701358[];
extern u8 D_8F702361;
extern s32 D_8F7023B4;
extern s32 D_8F7023B8;
extern void func_800226C0(s32);
extern void func_8F70058C(u8);
void func_8F700FD8(void) {
    s32 temp_v0;
    temp_v0 = D_8F701358[D_8F7023B4 * 0x30];
    switch (temp_v0) {
    case 0:
        D_8F7023B8 = 0;
        break;
    case 2:
        func_800226C0(2);
        func_8F70058C(D_8F702361);
        break;
    }
}
#endif

#ifdef VERSION_US
extern s32 D_8F7023B4;

void func_8F70104C(void) {
    func_800226C0(3);
    D_8F7023B0 = 0;
    D_8F7023B4 = 2;
}
#endif

#ifdef VERSION_US
extern void *D_80087200;
extern s32 func_8F700858(void *);
extern void func_8F7007B8(u8);
extern void func_8F700A54(void);
extern void func_8F700B78(void);
extern void func_8F700CA4(void);
extern void func_8F700DC8(void);
extern void func_8F700FD8(void);
extern void func_8F70104C(void);
extern void func_8F700F90(void);
extern void func_8F700F48(void);
void func_8F70107C(void) {
    s32 temp_v0;

    temp_v0 = func_8F700858(D_80087200);
    if (temp_v0 == 0) {
        goto common_tail;
    }
    if (temp_v0 == 1) {
        goto result_1;
    }
    if (temp_v0 == 2) {
        goto result_2;
    }
    if (temp_v0 == 4) {
        goto result_4;
    }
    if (temp_v0 == 8) {
        goto result_8;
    }
    if (temp_v0 == 0x100) {
        goto result_100;
    }
    if (temp_v0 == 0x200) {
        goto result_200;
    }
    if (temp_v0 == 0x400) {
        goto result_400;
    }
    if (temp_v0 != 0x800) {
        goto common_tail;
    }
result_800:
    func_8F700A54();
    goto common_tail;
result_400:
    func_8F700B78();
    goto common_tail;
result_200:
    func_8F700CA4();
    goto common_tail;
result_100:
    func_8F700DC8();
    goto common_tail;
result_8:
    func_8F7007B8(4);
    goto common_tail;
result_4:
    func_8F7007B8(5);
    goto common_tail;
result_2:
    func_8F7007B8(7);
    goto common_tail;
result_1:
    func_8F7007B8(6);
common_tail:
    if (*(u16 *)((u8 *)D_80087200 + 8) & 0x8000) {
        func_8F700FD8();
    } else if (*(u16 *)((u8 *)D_80087200 + 8) & 0x4000) {
        func_8F70104C();
    } else if (*(u16 *)((u8 *)D_80087200 + 8) & 0x20) {
        func_8F700F90();
    } else if (*(u16 *)((u8 *)D_80087200 + 8) & 0x10) {
        func_8F700F48();
    }
}
#endif

#ifdef VERSION_US
extern void func_80008648();
extern void func_800088DC();
extern void func_80064D28();
extern void func_8F700420();
extern void func_8F70107C();
extern s32 D_8F7023B8;
void func_8F7011C8(void) {
    do {
        func_80064D28();
        func_800088DC();
        func_8F70107C();
        func_8F700420();
        func_80008648();
    } while (D_8F7023B8 != 0);
}
#endif

#ifdef VERSION_US
extern void func_8F700538(u8);
extern u8 D_8F702360;
extern u8 D_8F702361;
extern u8 D_8F7023AC;
extern s32 D_8F7023B0;
extern s32 D_8F7023B4;
extern s32 D_8F7023B8;
void func_8F701224(void) {
    u8 value;
    D_8F7023B0 = 0;
    D_8F7023B4 = 0;
    value = 1;
    D_8F702360 = value;
    D_8F7023AC = value;
    D_8F702361 = value;
    D_8F7023B8 = 1;
    func_8F700538(D_8F702360);
}
#endif

#ifdef VERSION_US
extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void func_80006CD0(s32, s32);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_80047588(s32, s32);
extern void func_8004C09C(s32);
extern void func_8F701224(void);
extern void func_80008514(s32);
extern void func_800086A4(s32);
extern void func_80007AEC(s32);
extern void func_8F7011C8(void);
extern void func_80008574(void);
extern void func_80047610(void);
extern void Gfx_FreeDisplayListBuffers(void);
s32 fragment76_main(s32 arg0, s32 arg1) {
    s32 sp24;
    main_pool_push_state(0x41494544);
    func_80006CD0(0x10000, 0);
    sp24 = func_800082E0(1, 1, 2, 0, 2, 1);
    func_80047588(0x1C, 0);
    func_8004C09C(3);
    func_8F701224();
    func_80008514(sp24);
    func_800086A4(2);
    func_80007AEC(0x10);
    func_8F7011C8();
    func_80008574();
    func_80047610();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x41494544);
    return 0;
}
#endif
