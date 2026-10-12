#include "global.h"


#ifdef VERSION_US
void func_83000020(s32 arg0) { struct State { u8 pad[0x4E038]; u8 f0; u8 f1; u8 pad2[2]; f32 f2; }; struct State *p0 = (struct State *)(u32)arg0; struct State *p1 = (struct State *)(u32)arg0; p0->f1 = 0; p1->f0 = p1->f1; p0->f2 = 0.0f; }
#endif

#ifdef VERSION_US
s32 func_83000058(void *arg0) { struct Record { u8 pad[0x1D]; u8 value; u8 tail[0x3A]; }; s32 best = 0; s32 count = 0; s32 i; s32 j; s32 k; struct Record *p = (struct Record *)arg0; while (count < 6) { if (p->pad[0] == 0) break; best += p->value; count++; p++; } for (i = 0; i < count; i++) for (j = i + 1; j < count; j++) for (k = j + 1; k < count; k++) { struct Record *q = (struct Record *)arg0; s32 sum = q[i].value + q[j].value + q[k].value; if (best >= sum) best = sum; } return best; }
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
extern void func_8300021C(s32 arg0);
void func_830009D8(s32 arg0, void *arg1, void *arg2) {
    typedef struct {
        void *ptr;
        u8 status;
        u8 pad5[3];
    } SubState;
    typedef struct {
        u8 pad_00[0x3FB60];
        u8 unk_3FB60[0x3B8];
        SubState unk_3FF18;
        SubState unk_3FF20;
        s32 unk_3FF28;
    } State;
    State *state = (State *)(u32)arg0;
    SubState *sp20;
    s32 pad[5];

    func_8300021C(arg0);
    sp20 = &state->unk_3FF18;
    func_83000274(sp20, arg1, state->unk_3FB60);
    if (arg2 != NULL) {
        func_83000274(&state->unk_3FF20, arg1, (u8 *)arg2 + 0x10);
    }
    func_8004C594(1, *(u16 *)((u8 *)arg1 + 0x38));
    if (sp20->status != 0) {
        state->unk_3FF28 = 2;
    }
    if (arg2 != NULL) {
        if (state->unk_3FF20.status != 0) {
            state->unk_3FF28 = 2;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83000AA4.s")
#endif

#ifdef VERSION_US
extern s32 func_83000AA4(u8);
s32 func_83000BC0(u8 arg0, u8 arg1) {
    s32 result = func_83000AA4(arg0);
    u8 value = result;
    if (result < 5) return value != 0;
    if (arg1 == 0x19 && arg0 == 0xA3) return 1;
    if (arg1 == 0x71 && arg0 == 0x1E) return 1;
    if (arg1 == 0x68 && arg0 == 0x76) return 1;
    if (arg1 == 0x69 && arg0 == 0x76) return 1;
    if (arg1 == 0x53 && arg0 == 0x69) return 1;
    if (arg1 == 0x84 && arg0 == 0x23) return 1;
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83000CB4.s")
#endif

void func_83000E38(void) {
}

#ifdef VERSION_US
extern void func_80051830();
void func_83000E40(s32 arg0, s32 arg1)
{
  struct Record { u8 data[0x3C]; };
  struct Group { u8 pad[0x28]; struct Record records[6]; u8 tail[0x4C]; };
  struct Slot { u8 data[0xC80]; };
  struct State { u8 pad[0x3FF38]; struct Slot slots[6]; };
  u8 buffer[0x64];
  struct Group *a;
  struct State *b;
 a = (struct Group *)(u32)arg0; b = (struct State *)(u32)arg1; arg0 = 0; do { arg1 = 0; do { func_80051830(buffer, &a->records[arg1]);
      func_8004D878(&b->slots[arg1], 0, buffer);
      arg1++;
    } while (arg1 < 6);
    arg0++;
    a++;
    b = (struct State *)((u8 *)b + 0x4B00);
  } while (arg0 != 2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83000F04.s")
#endif

#ifdef VERSION_US
extern void func_83000F04(s32, s32, s32);
extern void func_83000CB4(s32, s32);
void func_83000F98(s32 arg0, s32 arg1, s32 arg2) {
    func_83000F04(arg1, arg0, arg2);
    if (arg2 != 0) {
        func_83000CB4(arg0, arg1);
    } else {
        _bzero((u8 *)(u32)arg0 + 0x3FF20, 8);
    }
}
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
extern s32 func_8300AED8(void *);
extern void func_800226C0(s32);
void func_830016BC(void *arg0, s32 arg1) { u8 *p = (u8 *)arg0; volatile s32 *status; if (arg1 == -1) { p[0x1E] = 0x23; func_800226C0(3); } else if (arg1 > 0) { if (arg1 < (s32)p[0x39E49] + 1) { if (p[0x46] == 1) { status = (volatile s32 *)(p + 0x4E040); *status = func_8300AED8(p + 0x3A06C); status = (volatile s32 *)(p + 0x4E040); if (*status != 0) p[0x1E] = 0x28; else p[0x1E] = 0x29; func_800226C0(0x90); } } else { func_800226C0(5); } } }
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
extern s32 func_8300B31C(void *arg0);
extern void func_800226C0(s32);
void func_83001DAC(void *arg0, s32 arg1) { u8 *p = (u8 *)arg0; volatile s32 *status; if (arg1 == -1) { p[0x1E] = 0x14; func_800226C0(3); } else if (arg1 > 0) { if (arg1 < (s32)((u8 *)(u32)arg0)[0x3A291] + 1) { if (p[0x46] == 1) { status = (volatile s32 *)(p + 0x4E040); *status = func_8300B31C((u8 *)(u32)arg0 + 0x3BDF4); status = (volatile s32 *)((u8 *)(u32)arg0 + 0x4E040); if (*status != 0) p[0x1E] = 0x19; else p[0x1E] = 0x1A; func_800226C0(0x90); } } else { func_800226C0(5); } } }
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
extern void func_800498C4();
extern void func_800499EC();
extern void func_8180351C(void *);
extern char *func_81802168(void *);
extern void func_800495F8(s32, s32, s32, void *);
extern s32 D_8300F86C[];
extern s32 D_8300F874[];
extern s32 D_8300F87C[];
extern s32 D_8300F884[];
extern u8 D_8300F88C[];
void func_830020CC(void *arg0, f32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    s32 start = (s32)arg1;
    s32 i;
    u8 *record;
    func_800498C4();
    for (i = start; i < start + 4; i++) {
        if (i >= ((u8 *)arg0)[1]) break;
        record = (u8 *)arg0 + i * 0x490 + 4;
        func_8180351C(D_8300F86C);
        func_800495F8(arg2 + 0x7E, (s32)((f32)(arg3 + 0x32) + 71.0f * (i - arg1)), D_8300F86C[0], record + 0x468);
        func_8180351C(D_8300F874);
        func_800495F8(arg2 + 0x13, (s32)((f32)(arg3 + 0x48) + 71.0f * (i - arg1)), D_8300F874[0], record + 0xD);
        func_8180351C(D_8300F87C);
        func_800495F8(arg2 + 0xE9, (s32)((f32)(arg3 + 0x48) + 71.0f * (i - arg1)), D_8300F87C[0], record + 0x1E9);
        func_8180351C(D_8300F884);
        func_800495F8(arg2 + 0x7E, (s32)((f32)(arg3 + 0x50) + 71.0f * (i - arg1)), D_8300F884[0], func_81802168(D_8300F88C));
    }
    func_800499EC();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830022F0.s")
#endif

#ifdef VERSION_US
typedef struct Rect02424 { s16 x, y, w, h; } Rect02424;
extern Rect02424 D_8300C3EC;
extern u8 D_8300C29C[];
extern void func_818006FC(s32, s32, s32, f32);
extern void func_830020CC(void *, f32, s32, s32, f32);
extern void func_81801854(void *, void *, void *);
extern void func_8004B2CC(s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_8300FAB8;
extern f32 D_8300FABC;
extern f32 func_818055E0();
extern void func_8180567C(s32, void *, void *);
extern void func_818057D0(s32, void *, void *);
void func_83002424(s32 arg0, void *arg1, void *arg2) {
    void *state = arg1;
    s32 pad;
    Rect02424 rect;
    f32 alpha;
    alpha = func_818055E0();
    func_818057D0(arg0, state, arg2);
    func_818006FC(((s16 *)arg2)[0] + 0xD, ((s16 *)arg2)[1] + 0x25, 0xE2, alpha);
    if (alpha > D_8300FAB8) {
        func_830020CC((u8 *)state + 0x3A290, 0.0f, ((s16 *)arg2)[0], ((s16 *)arg2)[1], alpha);
    }
    rect = D_8300C3EC;
    if (((u8 *)state)[0x46] == 1 && (((u8 *)state)[0x1F] == 0x19 || ((u8 *)state)[0x1F] == 0x1A)) {
        rect = *(Rect02424 *)(D_8300C29C + ((u8 *)state)[0x4A] * 0x18 - 0x12);
    }
    if (alpha > D_8300FABC && rect.w > 0) {
        func_81801854(&rect, &rect, arg2);
        func_8004B2CC(rect.x, rect.y, rect.w, rect.h, 0x96, 0x96, 0x5A, 0);
    }
    func_8180567C(arg0, state, arg2);
}
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
extern s32 func_81804A20(void *);
extern void func_81805524(void *, void *);
extern void func_800226C0(s32);
void func_83003320(void *arg0, void *arg1) {
    struct Record { s32 words[17]; };
    struct State {
        u8 pad0[0x14];
        u16 flags;
        u8 pad16[0x51 - 0x16];
        u8 selection;
        u8 pad52[0x3A06D - 0x52];
        u8 count;
        u8 pad3A06E[2];
        struct Record records[1];
        u8 pad3A0B4[0x3FD74 - 0x3A0B4];
        struct Record fixed[4];
        struct Record selected;
        s32 state;
        u8 active;
    };
    struct State *p = arg1;
    s32 index = p->selection - 1;
    if (func_81804A20(p) != 0) {
        if (p->flags & 0x10) {
            if (index < 4) {
                p->selected = p->fixed[index];
                p->state = 0x700;
                p->active = 1;
                func_800226C0(0xD2);
                return;
            }
            index -= 4;
            if (index < p->count) {
                p->selected = p->records[index];
                p->state = 0x700;
                p->active = 1;
                func_800226C0(0xD2);
                return;
            }
            func_800226C0(5);
            return;
        }
        func_81805524(arg0, p);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830034C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_83003F40.s")
#endif

#ifdef VERSION_US
extern void func_81801CB8(u8 *, u8 *, u8 *, s32);
void func_83004218(s32 a,u8 *b,u8 *c){extern u8 *func_818054D0(void *,u8);extern void func_81801CB8(u8 *,u8 *,u8 *,s32);extern u8 D_8300CD00[];extern u8 D_8300F8C0[];struct L{s32 x;s32 y;};struct L l;u8 *p;u8 *q;l.x=0;p=func_818054D0((void *)a,b[0x1C])+0x10;q=func_818054D0((void *)a,b[0x1D])+0x10;if(((a-(s32)D_8300CD00)/0x34)+1==b[0x43]){switch(b[0x1C]){case 0x11:case 0x12:case 0x13:p=D_8300F8C0;break;}switch(b[0x1D]){case 0x11:case 0x12:case 0x13:q=D_8300F8C0;break;}}func_81801CB8(c,p,q,*(s32 *)(b+0x2C));}
#endif

#ifdef VERSION_US
extern u8 *func_818054D0(void *, u8);
extern void func_81801CB8(u8 *, u8 *, u8 *, s32);
extern u8 D_8300D164[];
extern u8 D_8300F8C8[];
extern u8 D_8300F8D0[];
void func_830042F0(s32 arg0, void *arg1, u8 *arg2) {
    s32 pad;
    u8 *sp24;
    u8 *var_a1;
    u8 *var_a2;
    sp24 = func_818054D0((void *)arg0, *(u8 *)((u8 *)arg1 + 0x1C)) + 0x10;
    var_a1 = sp24;
    var_a2 = func_818054D0((void *)arg0, *(u8 *)((u8 *)arg1 + 0x1D)) + 0x10;
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
typedef struct { s32 x; s32 y; } Pair;
extern Pair D_8300F918;
extern void func_81801CB8(u8 *, u8 *, u8 *, s32);
extern u8 * func_818054D0(void *,u8);
void func_83006F30(s32 arg0, void *arg1, u8 *arg2) {
    struct Arg { u8 pad[0x1C]; u8 a; u8 b; u8 pad2[0xE]; s32 c; u8 pad3[0xE]; u8 flag; };
    u8 *sp28;
    Pair sp2C;
    u8 *var_a1; u8 *var_a2;
    struct Arg *p = arg1;
    sp2C = D_8300F918;
    sp28 = func_818054D0((void *)arg0, p->a) + 0x10;
    var_a1 = sp28;
    var_a2 = func_818054D0((void *)arg0, p->b) + 0x10;
    if (p->flag == 1) { if (p->a == 10) var_a1 = (u8 *)&sp2C; if (p->b == 10) var_a2 = (u8 *)&sp2C; }
    func_81801CB8(arg2, var_a1, var_a2, p->c);
}
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

extern void func_800226C0(s32);
void func_83007044(void *arg0, s32 arg1) {
    switch (arg1) {
        case -1:
            *(u8 *)((u8 *)(u32)arg0 + 0x3FECD) = 1;
            *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 0;
            func_800226C0(3);
            return;
        case 0:
            return;
        case 1:
            *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 2;
            func_800226C0(0xA3);
            return;
        case 2:
            *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 3;
            func_800226C0(0xA3);
            return;
        case 3:
            *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 4;
            func_800226C0(0xA3);
            return;
        case 4:
            *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 5;
            func_800226C0(0xA3);
            return;
    }
}
#endif

#ifdef VERSION_US
extern u8 D_8300DBE4[];
extern void func_818036D8(s32, s32, s32, s32);
extern void func_81805644(s32, s32, s32);
void func_83007100(s32 arg0, void *arg1, void *arg2) {
    void *state = arg1;
    func_81805644(arg0, (s32)arg1, (s32)arg2);
    if (((u8 *)state)[0x3D] > 0 && ((u8 *)state)[0x3D] < 5) {
        func_818036D8((u8 *)D_8300DBE4 + ((((u8 *)state)[0x3D] << 5) - 0x20), (s32)arg2, *(s32 *)((u8 *)state + 0x28), 0);
    }
}
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
void func_83007160(void *arg0, s32 arg1) {
    u8 *p = arg0;
    s32 a = 10;
    s32 b = 6;
    switch (arg1) { case -1: p[0x1E] = 1; func_800226C0(3); return; case 1: case 2:
        if ((s32)((u8 *)arg0 + arg1 * 0x1B64)[0x3872D] > 0) { p[0x1E] = a; func_800226C0(0xA3); return; }
        p[0x1E] = b; func_800226C0(5); return; }
}
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
extern void func_83000CB4(s32, s32);
extern void func_83000F98(s32 arg0, s32 arg1, s32 arg2);
void func_83007218(void *arg0, s32 arg1) {
    u8 *q;
    switch (arg1) {
    case -1:
        ((u8 *)arg0)[0x1E] = 1;
        func_800226C0(3);
        break;
    case 1:
        if ((s32)((u8 *)arg0)[0x3D959] > 0) {
            ((u8 *)arg0)[0x1E] = 0x11;
            q = (u8 *)arg0 + 0x3D95C;
            func_83000CB4(arg0, q);
            ((u8 *)arg0)[0x43] = 1;
            func_83000F98((s32)arg0, q, 0);
            func_800226C0(0xA3);
        } else {
            ((u8 *)arg0)[0x1E] = 6;
            func_800226C0(5);
        }
        break;
    case 2:
        if ((s32)((u8 *)arg0)[0x3EA5D] > 0) {
            ((u8 *)arg0)[0x1E] = 0x10;
            func_800226C0(0xA3);
        } else {
            ((u8 *)arg0)[0x1E] = 6;
            func_800226C0(5);
        }
        break;
    }
}
#endif

#ifdef VERSION_US
extern s32 _bcmp(void *, void *, s32);
extern void func_800226C0(s32);
void func_83007318(void *arg0, s32 arg1) { switch (arg1) { case -1: if (_bcmp((u8 *)(u32)arg0 + 0x39E48, (u8 *)(u32)arg0 + 0x34130, 0x5D18) != 0) { *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 7; func_800226C0(3); return; } *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 1; func_800226C0(3); return; case 1: *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 0x14; func_800226C0(0xA3); return; case 2: *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 0x1C; func_800226C0(0xA3); return; case 3: *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 0x23; func_800226C0(0xA3); return; } }
#endif

#ifdef VERSION_US
extern void func_83001000(void *);
extern void func_800226C0(s32);
void func_830073F8(void *arg0, s32 arg1) {
    struct Buffer {
        s32 data[0x5D18 / 4];
    };
    struct State {
        u8 pad0[0x1E];
        u8 unk1E;
        u8 pad1F[0x34130 - 0x1F];
        struct Buffer buf[2];
    };
    struct State *state = (struct State *)arg0;

    switch (arg1) {
    case -1:
    case 3:
        state->unk1E = 4;
        func_800226C0(3);
        break;
    case 1:
        func_800226C0(0x11);
        func_83001000(state);
        state->unk1E = 8;
        break;
    case 2:
        func_800226C0(0x14);
        state->buf[1] = state->buf[0];
        state->unk1E = 1;
        break;
    }
}
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
extern void main_pool_pop_state(s32);
extern void func_83009BD0(void *, s32);
extern s16 D_8300F7BC[][2];
void func_830074C8(void *arg0, s32 arg1) {
    switch (arg1) {
        case -1:
            *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 1;
            func_800226C0(3);
            return;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            main_pool_pop_state(0x4D535243);
            func_83009BD0(arg0, D_8300F7BC[arg1][0]);
            *(u8 *)((u8 *)(u32)arg0 + 0x1E) = 9;
            func_800226C0(0xA3);
            return;
    }
}
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
extern f32 func_818006B4(void);
extern u16 D_8300F7BE[][2];
extern void func_800226C0(s32);
extern s32 func_81804A20(void *);
extern void func_81805524(void *, void *);
s32 func_83007ECC(s32 arg0, void *arg1) {
    struct State { u8 pad[0x4E038]; u8 current; u8 target; u8 pad2[2]; f32 progress; };
    s32 limit;
    func_81805524((void *)arg0, arg1);
    if (((struct State *)arg1)->current != ((struct State *)arg1)->target) {
        ((struct State *)arg1)->progress += func_818006B4() * 0.0625f;
        if (((struct State *)arg1)->progress > 1.0f) {
            ((struct State *)arg1)->current = ((struct State *)arg1)->target;
            ((struct State *)arg1)->progress = 0.0f;
        }
    } else if (func_81804A20(arg1) != 0) {
        arg0 = ((struct State *)arg1)->current;
        if ((arg0 > 0) && ((*(u16 *)((u8 *)arg1 + 0x18) & 0x800) != 0)) {
            ((struct State *)arg1)->target = ((struct State *)arg1)->target - 1;
            func_800226C0(1);
            goto done;
        }
        limit = D_8300F7BE[*(u8 *)((u8 *)arg1 + 0x4F)][0] - 1;
        if (arg0 < limit) {
            if (((*(u16 *)((u8 *)arg1 + 0x18) & 0x400) != 0) || ((*(u16 *)((u8 *)arg1 + 0x14) & 0x8000) != 0)) {
                ((struct State *)arg1)->target = ((struct State *)arg1)->target + 1;
                func_800226C0(1);
                goto done;
            }
        }
        if ((arg0 == limit) && ((*(u16 *)((u8 *)arg1 + 0x14) & 0x8000) != 0)) {
            *(u8 *)((u8 *)arg1 + 0x1E) = 5;
            func_800226C0(3);
        }
    }
done:
    return 1;
}
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
extern void func_830034C8(void *, void *, void *, f32);
extern f32 func_818055E0();
extern void func_818057D0(s32, void *, void *);
void func_830080AC(s32 arg0, void *arg1, void *arg2) { struct Locals { void *ptr; u32 pad; f32 value; }; struct Locals local; void *base = arg1; u8 index; local.value = func_818055E0(); index = *((u8 *)base + 0x48); if (index >= 2) local.ptr = (u8 *)base + index * 0x220 + 0x3E620; else local.ptr = (u8 *)base + 0x3D95C; func_818057D0(arg0, base, arg2); func_830034C8(base, local.ptr, arg2, local.value); }
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
s32 func_83008844(s32 arg0, u8 arg1) { s32 selector; s32 result = 0; selector = arg1; if (arg0 == 13) { switch (selector) { case 1: result = 1; break; case 2: result = 2; break; case 3: case 4: case 6: case 7: result = 3; break; case 5: result = 4; break; } } return result; }
#endif

#ifdef VERSION_US
typedef struct { u8 data[5][8]; } Table088A0;
extern Table088A0 D_8300F928;
extern void func_81801CB8(u8 *, u8 *, u8 *, s32);
extern s32 func_83008844(s32 arg0, u8 arg1);
void func_830088A0(s32 arg0, void *arg1, u8 *arg2) {
    Table088A0 table = D_8300F928;
    u8 *second;
    u8 *state = arg1;
    u8 *first;
    s32 unused;
    first = table.data[func_83008844(state[0x1C], state[0x3FF1C])];
    second = table.data[func_83008844(state[0x1D], state[0x3FF1C])];
    func_81801CB8(arg2, first, second, *(s32 *)(state + 0x2C));
}
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
extern void func_83000F98(s32 arg0, s32 arg1, s32 arg2);
void func_83008960(void *arg0, s32 arg1) {
    if (arg1 == -1) {
        *((u8 *)arg0 + 0x1E) = 0x1C;
        func_800226C0(3);
        return;
    }
    if (arg1 == 1) {
        if (*((u8 *)arg0 + 0x3D959) > 0) {
            *((u8 *)arg0 + 0x1E) = 0x1F;
            func_83000F98((s32)arg0, (s32)((u8 *)arg0 + 0x3D95C), 0);
            func_800226C0(0x90);
            return;
        }
        func_800226C0(5);
        return;
    }
    if (arg1 >= 2) {
        arg1 -= 2;
        if (arg1 < *((u8 *)arg0 + 0x3EA5D)) {
            *((u8 *)arg0 + 0x1E) = 0x1F;
            func_83000F98((s32)arg0, (s32)((u8 *)arg0 + arg1 * 0x220 + 0x3EA60), 0);
            func_800226C0(0x90);
            return;
        }
        func_800226C0(5);
    }
}
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
extern void func_800226C0(s32);
void func_83008F84(void *arg0, s32 arg1)
{
  u8 *p = arg0;

  switch (arg1)
  {
    case -1:
      p[0x1E] = 2;
      func_800226C0(3);
      return;
    case 1:
    case 2:
    case 3:
      if ((arg1 + p[0x59]) < (((u8 (*)[0x1B64])(p + 0x3872D))[p[0x3E]][0] + 1))
      {
        func_800226C0(0x90);
        p[0x1E] = 0xB;
        func_83000E40((((p + (((s32) p[0x3E]) * 0x1B64)) + (((s32) p[0x40]) * 0x490)) + (((u32) p[0x59]) * 0x490)) + ((0, 0x382A0)), arg0);
        return;
      }
      func_800226C0(5);
      return;
  }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_830090D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_BA250/func_8300928C.s")
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
extern void func_830009D8(s32 arg0, void *arg1, void *arg2);
void func_830094C8(void *arg0, s32 arg1) {
    u8 *p = arg0;
    u8 *q;
    switch (arg1) {
        case -1:
            p[0x1E] = 0xB;
            func_800226C0(3);
            return;
        case 1:
        case 2:
            q = (((p + ((s32)p[0x3E] * 0x1B64)) + ((s32)p[0x40] * 0x490)) + ((u32)p[0x59] * 0x490)) + (0, 0x382A0);
            func_830009D8((s32)arg0, q + 0x424, 0);
            p[0x1E] = 0xD;
            func_800226C0(2);
            return;
    }
}
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
extern void func_8300B1CC(void *);
extern void func_8300ADA4(void *);
extern void func_8300B818(void *);
extern void func_80051D64(s32, s32);
extern void func_80055028(void);
extern s32 func_81A00074(void *, s32);
extern s32 _bcmp(void *, void *, s32);
void func_83009EC4(void *arg0) {
    typedef struct { u32 words[0x1B64 / 4]; } Large;
    typedef struct { u32 words[0x224 / 4]; } Small;
    typedef struct { u32 words[0x1104 / 4]; } Medium;
    s32 i;
    s32 changed;
    s32 slot = *((u8 *)arg0 + 0x3C);
    for (i = 0; i < 2; i++) {
    Large *a = &((Large *)((u8 *)arg0 + 0x3A290))[i];
    Large *b = &((Large *)((u8 *)arg0 + 0x34578))[i];
    Small *c = &((Small *)((u8 *)arg0 + 0x39E48))[i];
    Small *d = &((Small *)((u8 *)arg0 + 0x34130))[i];
    Medium *e = &((Medium *)((u8 *)arg0 + 0x3D958))[i];
    Medium *f = &((Medium *)((u8 *)arg0 + 0x37C40))[i];

        changed = 0;
        if (_bcmp(a, b, 0x1B64) != 0) {
            func_8300B1CC(a);
            changed = 1;
            if (i == 1) func_80051D64(0x19, 0);
        }
        if (_bcmp(c, d, 0x224) != 0) {
            func_8300ADA4(c);
            changed = 1;
            if (i == 1) func_80051D64(0x18, 0);
        }
        if (_bcmp(e, f, 0x1104) != 0) {
            func_8300B818(e);
            changed = 1;
            if (i == 1) func_80051D64(0x1B, 0);
        }
        if (changed) {
            if (i == 1) {
                func_80055028();
                *d = *c;
                *f = *e;
                *b = *a;
            } else if ((slot >= 0) && (slot < 4)) {
                if (!func_81A00074((u8 *)arg0 + 0x4E044, slot)) break;
                *d = *c;
                *f = *e;
                *b = *a;
            }
        }
    }
    if (_bcmp((u8 *)arg0 + 0x39E48, (u8 *)arg0 + 0x34130, 0x5D18) == 0)
        *(s32 *)((u8 *)arg0 + 0x3FF2C) = 0;
}
#endif

#ifdef VERSION_US
extern u8 D_8303FD00[];
extern u8 D_8304FB84[];
extern u8 D_82C00000[];
extern u8 fragment83_ROM_START[];
extern u8 fragment84_ROM_START[];
extern void StageLoader_WaitForRetrace();
s32 Fragment_LoadAndCall(s32, void *, void *, s32, void *);
extern s32 Fragment_LoadAndCall(s32, void *, void *, s32, void *);
extern void StageLoader_WaitForRetrace();
extern void func_80008648();
extern void func_800088DC();
extern void func_818017A8();
extern void func_81805308(s32 *);
extern void func_83009BD0(void *, s32);
extern void main_pool_pop_state(s32);
extern u8 D_8300FD00;
extern u8 D_8304FBCC;
void func_8300A208(void) {
    extern void func_800088DC();
    extern void func_818017A8();
    extern void func_81805308(s32 *);
    extern void func_80008648();
    extern void func_8004C398(void);
    extern void main_pool_pop_state(s32);
    extern void func_83009BD0(void *, s32);
    extern void func_80008624(void);
    extern u8 D_8300FD00;
    extern u8 D_8304FBCC;
    struct State { u8 pad[0xFEC8]; s32 argument; u8 gap[0x64]; s32 clear; };
    struct State *p;
    func_800088DC();
    func_818017A8();
    func_81805308((s32 *)&D_8300FD00);
    func_80008648();
    StageLoader_WaitForRetrace();
    func_8004C398();
    main_pool_pop_state(0x4D535243);
    p = (struct State *)(u32)D_8303FD00;
    p->clear = 0;
    Fragment_LoadAndCall((((u32)D_82C00000 & 0x0FF00000) >> 20) - 0x10, fragment83_ROM_START, fragment84_ROM_START, p->argument, D_8304FB84);
    func_83009BD0(&D_8300FD00, 0xC7);
    func_80008624();
    D_8304FBCC = 0;
}
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
extern void main_pool_push_state(s32);
extern u8 D_1000000[];
extern u8 D_446E30[];
extern u8 D_447D00[];
extern u8 *Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern void func_80055948(s32);
extern void func_80047588(s32, s32);
extern void func_830098A0(void *, s32, s32, s32);
extern void func_80008624(void);
extern void func_81801794(void);
extern void func_83009BD0(void *, s32);
extern void main_pool_push_state(s32);
extern u8 D_8300FD00;
void func_8300A50C(arg0, arg1, arg2)
s32 arg0;
s32 arg1;
s32 arg2;
{
    main_pool_push_state(0x4D535F32);
    Asset_LoadToSegment(((u32)D_1000000 & 0x0F000000) >> 24, D_446E30, D_447D00, 0);
    func_80055948(3);
    func_80047588(0x1C, 0);
    func_830098A0(&D_8300FD00, 0, arg1, arg2);
    func_83009BD0(&D_8300FD00, 0xC7);
    func_80008624();
    func_81801794();
}
#endif

#ifdef VERSION_US
extern u8 D_8300FD3C[];
extern void func_8004C398(void);
extern void func_80047610(void);
extern void main_pool_pop_state(s32);
extern u8 D_8300FD00;
void func_8300A5B4(s32 arg0, s32 arg1) {
    struct Payload { u8 bytes[31]; };
    struct Object { u8 pad[0x10]; s32 active; u8 pad2[8]; struct Payload payload; };
    struct State { u8 pad[0x1D]; u8 value; u8 pad2[0x1A]; struct Object *object; };
    volatile struct State *state = (struct State *)&D_8300FD00;
    struct Object *object = state->object;
    if (object->active != 0) {
        object->payload = *(struct Payload *)D_8300FD3C;
        state->object->payload.bytes[0x1A] = (&D_8300FD00)[0x1D];
    }
    func_8004C398();
    main_pool_pop_state(0x4D535243);
    func_80047610();
    main_pool_pop_state(0x4D535F32);
}
#endif

#ifdef VERSION_US
extern void Gfx_InitDisplayListBuffers(s32, s32);
s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_80008514(s32);
extern void StageLoader_WaitForRetrace();
extern void main_pool_push_state(s32);
void func_8300A6B0(s32 arg0, s32 arg1) {
    main_pool_push_state(0x4D535F31);
    Gfx_InitDisplayListBuffers(0x10000, 0);
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
s32 Fragment_LoadAndCall(s32, void *, void *, s32, void *);
extern u8 fragment10_ROM_START[];
extern u8 fragment11_ROM_START[];
extern u8 D_82800000[];
s32 func_8300A754(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 ret;
    struct {
        s16 unk0;
        s16 unk2;
        s32 unk4;
    } sp24;
    s32 var_a3;

    sp24.unk0 = 0x11;
    if (arg2 != 0) {
        sp24.unk4 = 0x6C610404;
    } else {
        sp24.unk4 = 0x7C610404;
    }
    sp24.unk2 = 0;
    main_pool_push_state(0x4D534353);
    if ((arg3 >= 0) && (arg3 < 4)) {
        var_a3 = arg3;
    } else {
        var_a3 = 0;
    }
    ret = Fragment_LoadAndCall((((u32)D_82800000 & 0x0FF00000) >> 20) - 0x10, fragment10_ROM_START, fragment11_ROM_START, var_a3, &sp24);
    main_pool_pop_state(0x4D534353);
    return ret;
}
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
