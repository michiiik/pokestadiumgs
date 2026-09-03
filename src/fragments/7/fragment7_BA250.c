#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83000020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83000058.s")
#endif

#ifdef VERSION_US
extern void _bzero(void *, s32);
void func_8300021C(s32 arg0) {
    _bzero((u8 *)(u32)arg0 + 0x3FF18, 8);
    _bzero((u8 *)(u32)arg0 + 0x3FF20, 8);
    *(s32 *)((u8 *)(u32)arg0 + 0x3FF28) = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83000274.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830009D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83000AA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83000BC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83000CB4.s")
#endif

void func_83000E38(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83000E40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83000F04.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83000F98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83001000.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_8300112C.s")
#endif

#ifdef VERSION_US
extern void func_81801FE8(void *, s32, s32, s32);
extern u8 D_8300F84C[];
void func_8300136C(s32 arg0, s32 arg1, s32 arg2) {
    func_81801FE8(D_8300F84C, 0x6E, 0x8C, 0xD2);
  }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830013A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830016BC.s")
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
extern void func_8300AC8C(void *, s32, s32, void *);
extern void func_8300B728(void *, s32, s32, void *);
void func_83001788(void *arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;
    if (arg1 == -1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 0x23;
        *(u8 *)((u8 *)arg0 + 0x52) = 0;
        func_800226C0(3);
        return;
    }
    if (arg1 > 0) {
        if (arg1 < ((s32)*(u8 *)((u8 *)(u32)arg0 + 0x3A06D) + 1)) {
            temp_v0 = *(u8 *)((u8 *)arg0 + 0x46);
            switch (temp_v0) {
            case 1:
                *(u8 *)((u8 *)arg0 + 0x1E) = 0x29;
                func_800226C0(0x90);
                return;
            case 3:
                temp_v0_2 = *(u8 *)((u8 *)arg0 + 0x52);
                if (temp_v0_2 == 0) {
                    *(u8 *)((u8 *)arg0 + 0x52) = (u8)arg1;
                    func_800226C0(0x90);
                    return;
                }
                func_8300AC8C((u8 *)(u32)arg0 + 0x3A06C, temp_v0_2 - 1, arg1 - 1, arg0);
                *(u8 *)((u8 *)arg0 + 0x52) = 0;
                *(u8 *)((u8 *)arg0 + 0x1E) = 0x23;
                func_800226C0(0x44);
                return;
            case 4:
                *(u8 *)((u8 *)arg0 + 0x1E) = 0x29;
                func_800226C0(0x90);
                return;
            }
        } else {
            func_800226C0(5);
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830018B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83001A3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83001BA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83001DAC.s")
#endif

#ifdef VERSION_US
extern void func_8300B0DC(void *, s32, s32, void *);
extern void func_800226C0(s32);
void func_83001E78(void *arg0, s32 arg1) {
    u8 temp_v0;
    s32 temp_v0_2;
    if (arg1 == -1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 0x14;
        *(u8 *)((u8 *)arg0 + 0x52) = 0;
        func_800226C0(3);
        return;
    }
    if (arg1 > 0) {
        arg1 += *(u8 *)((u8 *)arg0 + 0x57);
        if (arg1 < ((s32)*(u8 *)((u8 *)(u32)arg0 + 0x3BDF5) + 1)) {
            temp_v0 = *(u8 *)((u8 *)arg0 + 0x46);
            switch (temp_v0) {
            case 1:
                func_800226C0(0x90);
                *(u8 *)((u8 *)arg0 + 0x1E) = 0x1A;
                return;
            case 3:
                temp_v0_2 = *(u8 *)((u8 *)arg0 + 0x52);
                if (temp_v0_2 == 0) {
                    *(u8 *)((u8 *)arg0 + 0x52) = (u8)arg1;
                    func_800226C0(0x90);
                    return;
                }
                func_8300B0DC((u8 *)(u32)arg0 + 0x3BDF4, arg1 - 1, temp_v0_2 - 1, arg0);
                *(u8 *)((u8 *)arg0 + 0x52) = 0;
                *(u8 *)((u8 *)arg0 + 0x1E) = 0x14;
                func_800226C0(0x44);
                return;
            case 4:
                *(u8 *)((u8 *)arg0 + 0x1E) = 0x1A;
                func_800226C0(0x90);
                return;
            }
        } else {
            func_800226C0(5);
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
extern void func_8300AC8C(void *, s32, s32, void *);
extern void func_8300B728(void *, s32, s32, void *);
void func_83001FA4(void *arg0, s32 arg1) {
    u8 temp_v0;
    if (arg1 == -1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 0x1C;
        func_800226C0(3);
        *(u8 *)((u8 *)arg0 + 0x52) = 0;
        return;
    }
    if (arg1 > 0) {
        if (arg1 < ((s32)*(u8 *)((u8 *)(u32)arg0 + 0x3EA5D) + 1)) {
            temp_v0 = *(u8 *)((u8 *)arg0 + 0x46);
            switch (temp_v0) {
            case 1:
                *(u8 *)((u8 *)arg0 + 0x1E) = 0x21;
                func_800226C0(0x90);
                return;
            case 3:
                if (*(u8 *)((u8 *)arg0 + 0x52) == 0) {
                    *(u8 *)((u8 *)arg0 + 0x52) = (u8)arg1;
                    func_800226C0(0x90);
                    return;
                }
                func_800226C0(0x44);
                func_8300B728((u8 *)(u32)arg0 + 0x3EA5C, arg1 - 1, (s32)*(u8 *)((u8 *)arg0 + 0x52) - 1, arg0);
                *(u8 *)((u8 *)arg0 + 0x52) = 0;
                *(u8 *)((u8 *)arg0 + 0x1E) = 0x1C;
                return;
            case 4:
                *(u8 *)((u8 *)arg0 + 0x1E) = 0x21;
                func_800226C0(0x90);
                return;
            }
        } else {
            func_800226C0(5);
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830020CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830022F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83002424.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830025AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83002988.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83002ADC.s")
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
void func_83002F50(void *arg0, s32 arg1) {
    void *temp_a2;
    u8 temp_v0;

    temp_a2 = arg0;
    if (arg1 == -1) {
        temp_v0 = *(u8 *)((u8 *)arg0 + 0x3F);
        switch (temp_v0) {
        case 1:
            *(u8 *)((u8 *)temp_a2 + 0x1E) = 3;
            func_800226C0(3);
            return;
        case 2:
            *(u8 *)((u8 *)temp_a2 + 0x1E) = 0x10;
            func_800226C0(3);
            return;
        }
    } else if (arg1 > 0) {
        if (*(s32 *)((u8 *)(u32)temp_a2 + (arg1 * 4) + 0x3FECC) != 0) {
            *(u8 *)((u8 *)temp_a2 + 0x1E) = 0x13;
            func_800226C0(0x8D);
            return;
        }
        func_800226C0(5);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83003000.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83003320.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830034C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83003F40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83004218.s")
#endif

#ifdef VERSION_US
extern u8 *func_818054D0(s32, u8);
extern void func_81801CB8(u8 *, u8 *, u8 *, s32);
extern u8 D_8300D164[];
extern u8 D_8300F8C8[];
extern u8 D_8300F8D0[];
void func_830042F0(s32 arg0, void *arg1, u8 *arg2) {
    s32 pad;
    u8 *sp24;
    u8 *var_a1;
    u8 *var_a2;
    sp24 = func_818054D0(arg0, *(u8 *)((u8 *)arg1 + 0x1C)) + 0x10;
    var_a1 = sp24;
    var_a2 = func_818054D0(arg0, *(u8 *)((u8 *)arg1 + 0x1D)) + 0x10;
    if ((((arg0 - (s32)D_8300D164) / 0x34) + 1) == *(u8 *)((u8 *)arg1 + 0x40)) {
        switch (*(u8 *)((u8 *)arg1 + 0x1C)) {
        case 0x0B:
        case 0x0C:
            var_a1 = D_8300F8C8;
            break;
        case 0x0D:
            var_a1 = D_8300F8D0;
            break;
        }
        switch (*(u8 *)((u8 *)arg1 + 0x1D)) {
        case 0x0B:
        case 0x0C:
            var_a2 = D_8300F8C8;
            break;
        case 0x0D:
            var_a2 = D_8300F8D0;
            break;
        }
    }
    func_81801CB8(arg2, var_a1, var_a2, *(s32 *)((u8 *)arg1 + 0x2C));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830043F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83004CBC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83004FC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83005740.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830061BC.s")
#endif

#ifdef VERSION_US
extern void func_81805428(s32);
extern void func_8300112C(s32);
void func_83006308(s32 arg0, s32 arg1) {
    func_81805428(arg0);
    func_8300112C(arg1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83006330.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83006798.s")
#endif

#ifdef VERSION_US
extern void func_818042E4(s32 *, s32, s32, f32, s32);
f32 func_818055E0();
extern void func_83006798(s32, s32, s32);
extern u8 D_8300D4B4;
void func_83006AF0(s32 arg0, s32 arg1, s32 arg2) {
    f32 sp24;

    sp24 = func_818055E0();
    func_83006798(arg0, arg1, arg2);
    func_818042E4(&D_8300D4B4, arg2, arg1, sp24, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83006B48.s")
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
void func_83006EB0(void *arg0, s32 arg1) {
    u8 temp_v0;

    if ((arg1 == -1) || (arg1 == 1)) {
        func_800226C0(3);
        temp_v0 = (*(u8 *)((u8 *)(arg0) + (0x45)));
        switch (temp_v0) {                          /* irregular */
        case 1:
            (*(s8 *)((u8 *)(arg0) + (0x1E))) = 0x14;
            return;
        case 2:
            (*(s8 *)((u8 *)(arg0) + (0x1E))) = 0x1C;
            return;
        case 3:
            (*(s8 *)((u8 *)(arg0) + (0x1E))) = 0x23;
            break;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83006F30.s")
#endif

#ifdef VERSION_US
extern f32 func_818055E0(void);
extern void func_81805644(s32, s32, s32);
extern void func_818036D8(s32, s32, s32, s32);
extern u8 D_8300D908[];
void func_83006FDC(s32 arg0, s32 arg1, s32 arg2) {
    s32 pad;
    f32 temp_fv0;

    temp_fv0 = func_818055E0();
    func_81805644(arg0, arg1, arg2);
    func_818036D8((s32)(D_8300D908 + ((*(u8 *)((u8 *)(u32)arg1 + 0x3D) << 5) - 0x20)), arg2, *(s32 *)&temp_fv0, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83007044.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83007100.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83007160.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83007218.s")
#endif

#ifdef VERSION_US
extern s32 _bcmp(void *, void *, s32);
extern void func_800226C0(s32);
void func_83007318(void *arg0, s32 arg1) { switch (arg1) { case -1: if (_bcmp((u8 *)(u32)arg0 + 0x39E48, (u8 *)(u32)arg0 + 0x34130, 0x5D18) != 0) { *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 7; func_800226C0(3); return; } *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 1; func_800226C0(3); return; case 1: *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 0x14; func_800226C0(0xA3); return; case 2: *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 0x1C; func_800226C0(0xA3); return; case 3: *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 0x23; func_800226C0(0xA3); return; } }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830073F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830074C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83007568.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83007788.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830078E4.s")
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
void func_83007BE4(void *arg0, s32 arg1) {
    void *temp_a2;

    temp_a2 = arg0;
    switch (arg1) {
    case -1:
        (*(u8 *)((u8 *)(temp_a2) + 0x1E)) = 0x10;
        func_800226C0(3);
        return;
    case 1:
    case 2:
    case 3:
        (*(u8 *)((u8 *)(u32)temp_a2 + 0x3FECD)) = 1;
        func_800226C0(2);
        return;
    }
}
#endif

#ifdef VERSION_US
extern void func_800498C4();
extern void func_800499EC();
f32 func_818055E0();
extern void func_818057D0(s32, void *, void *);
void func_83007C5C(s32 arg0, void *arg1, void *arg2) {
    f32 sp1C;

    sp1C = func_818055E0();
    func_818057D0(arg0, arg1, arg2);
    func_800498C4();
    func_800496A4(8, 1);
    func_8004972C(0xFF, 0xFF, 0xFF, (s32) (255.0f * sp1C));
    func_8004989C(0x1A);
    func_800495BC((*(s16 *)((u8 *)(arg2) + (0))) + 0x11, (*(s16 *)((u8 *)(arg2) + (2))) + 0xB, (*(s32 **)((u8 *)(arg1) + (0x3FD70))));
    func_800499EC();
}
#endif

#ifdef VERSION_US

void func_83007D10(void *arg0, s32 arg1) {
    if (arg1 == -1) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 5;
        func_800226C0(3);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83007D40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83007ECC.s")
#endif

#ifdef VERSION_US
void func_83008070(void *arg0, s32 arg1) {
    if ((arg1 == -1) || (arg1 == 1)) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 0x1E;
        func_800226C0(2);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830080AC.s")
#endif

#ifdef VERSION_US
void func_8300814C(void *arg0, s32 arg1) {
    if ((arg1 == -1) || (arg1 == 1)) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 0x16;
        func_800226C0(2);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83008188.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83008290.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83008494.s")
#endif

#ifdef VERSION_US
void func_83008700(void *arg0, s32 arg1) {
    if ((arg1 == -1) || (arg1 == 1)) {
        (*(u8 *)((u8 *)(arg0) + (0x1E))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x21)));
        func_800226C0(2);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83008740.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83008844.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830088A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83008960.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83008A68.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83008BB8.s")
#endif

#ifdef VERSION_US
extern f32 func_818055E0(void);
extern void func_818057D0(s32, void *, void *);
extern void func_8180567C(s32, void *, void *);
extern void func_81803964(void *, void *, f32, s32);
extern u8 D_8300F118[];
extern u8 D_8300F138[];
void func_83008D18(s32 arg0, void *arg1, void *arg2) {
    s32 pad;
    f32 temp_fv0;

    temp_fv0 = func_818055E0();
    func_818057D0(arg0, arg1, arg2);
    func_8180567C(arg0, arg1, arg2);
    if (*(u8 *)((u8 *)arg1 + 0x3E) == 2) {
        if ((s32)(*(u8 *)((u8 *)arg1 + 0x57)) > 0) {
            func_81803964(D_8300F118, arg2, temp_fv0, 0);
        }
        if ((s32)(*(u8 *)((u8 *)arg1 + 0x57)) < 2) {
            func_81803964(D_8300F138, arg2, temp_fv0, 0);
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83008DC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83008F84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830090D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_8300928C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830094C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830095B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830096B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830098A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83009BD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83009EC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_8300A208.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_8300A2CC.s")
#endif

#ifdef VERSION_US
extern void func_80008648();
extern void func_800088DC();
extern void func_818017A8();
extern void func_81805308(s32 *);
extern void func_8300A208();
extern u8 D_8300FD00;
extern u8 D_8304FBCC;
extern u8 D_8305DD44;
void func_8300A45C(s32 arg0) {
    func_800088DC();
    func_818017A8();
    func_81805308(&D_8300FD00);
    func_81A0022C(&D_8305DD44);
    func_80008648();
    if ((s32) D_8304FBCC > 0) {
        func_8300A208();
    }
}
#endif

#ifdef VERSION_US
s32 func_8300A2CC(s32);
extern void func_8300A45C(s32);
void func_8300A4BC(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    do {
        temp_v0 = func_8300A2CC(var_s0);
        var_s0 = temp_v0;
        func_8300A45C(temp_v0);
    } while (var_s0 != 1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_8300A50C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_8300A5B4.s")
#endif

#ifdef VERSION_US
extern void func_80006CD0(s32, s32);
s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_80008514(s32);
extern void StageLoader_WaitForRetrace();
extern void main_pool_push_state(s32);
void func_8300A6B0(s32 arg0, s32 arg1) {
    main_pool_push_state(0x4D535F31);
    func_80006CD0(0x10000, 0);
    func_80008514(func_800082E0(1, 0, 2, 0, 2, 1));
    StageLoader_WaitForRetrace();
}
#endif

#ifdef VERSION_US
extern void Gfx_FreeDisplayListBuffers();
extern void func_80008574();
extern void main_pool_pop_state(s32);

void func_8300A71C(s32 arg0, s32 arg1) {
    func_80008574();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x4D535F31);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_8300A754.s")
#endif

#ifdef VERSION_US
extern void func_8300A4BC(s32, s32);
extern void func_8300A50C();
extern void func_8300A5B4(s32, s32);

void func_8300A81C(s32 arg0, s32 arg1) {
    func_8300A50C();
    func_8300A4BC(arg0, arg1);
    func_8300A5B4(arg0, arg1);
}
#endif

#ifdef VERSION_US
extern void func_80057944(s32);

void func_8300A858(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_80057944(var_s0 & 0xFF);
        var_s0 += 1;
    } while (var_s0 != 4);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_8300A898.s")
#endif
