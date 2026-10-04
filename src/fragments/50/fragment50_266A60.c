#include "global.h"


#ifdef VERSION_US
extern void *D_8620E198;
extern void *D_87F119DC;
extern u8 D_8620DF60[];
extern s32 D_8620DF90;
extern void StageContext_SetClearColor(s32);
extern void StageFade_StartFromTransparent(s32);
extern void func_862005B4(s32, s32, s32);
extern void func_8620218C(void *, void *);
void func_86200020(s32 arg0) {
    *(s32 *)((u8 *)D_8620E198 + 0x73CC0) = arg0;
    *(s32 *)((u8 *)D_8620E198 + 0xE8) = 7;
    *(s32 *)((u8 *)D_8620E198 + 0xEC) = 8;
    StageContext_SetClearColor(0xFFFF);
    StageFade_StartFromTransparent(0xA);
}
void func_86200020_padding(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86200080.s")
#endif

#ifdef VERSION_US
extern void func_86200080(s32, u8 *);
extern u8 D_8620DF60[];
extern s32 D_8620DF90;
extern void * D_8620E198;
void func_862002A4(void) {
    s32 i;
    u8 *p;

    p = D_8620DF60;
    i = 0;
    if (D_8620DF90 > 0) {
        do {
            func_86200080(*(s32 *)((u8 *)D_8620E198 + i * 4 + 0x72254), p);
            i += 1;
            p += 0xC;
        } while (i < D_8620DF90);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86200344.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_8620050C.s")
#endif

#ifdef VERSION_US
extern void Vec3f_CrossProductFromPoints(f32 *, f32 *, f32 *, f32 *);
extern void func_80035A10(f32 *);

void func_862005B4(s32 arg0, s32 arg1, s32 arg2) {
    struct Point { f32 x; f32 y; f32 z; };
    struct Record {
        f32 x; f32 y; f32 z; f32 w;
        u8 index0; u8 index1; u8 index2; u8 pad;
    };
    s32 pad[2];
    f32 cross[3];
    s32 i;
    i = 0;
    if (arg2 > 0) {
        do {
            Vec3f_CrossProductFromPoints(
                cross,
                (f32 *)(u32)(((u32)(((struct Record *)(u32)arg1)->index0) * 12) + (u32)arg0),
                (f32 *)(u32)(((u32)(((struct Record *)(u32)arg1)->index1) * 12) + (u32)arg0),
                (f32 *)(u32)(((u32)(((struct Record *)(u32)arg1)->index2) * 12) + (u32)arg0)
            );
            func_80035A10(cross);
            ((struct Record *)(u32)arg1)->x = cross[0];
            ((struct Record *)(u32)arg1)->y = cross[1];
            ((struct Record *)(u32)arg1)->z = cross[2];
            ((struct Record *)(u32)arg1)->w =
                -((((struct Record *)(u32)arg1)->x * ((struct Point *)(u32)arg0)[((struct Record *)(u32)arg1)->index0].x) +
                  (((struct Record *)(u32)arg1)->y * ((struct Point *)(u32)arg0)[((struct Record *)(u32)arg1)->index0].y) +
                  (((struct Record *)(u32)arg1)->z * ((struct Point *)(u32)arg0)[((struct Record *)(u32)arg1)->index0].z));
            arg1 += 0x14;
            i += 1;
        } while (i != arg2);
    }
}
#endif

#ifdef VERSION_US
void func_862006C8(void) {
    s32 *var_s0;
    s32 var_s1;

    var_s0 = (s32 *)D_8620DF60;
    var_s1 = 0;
    if (D_8620DF90 > 0) {
        do {
            func_862005B4(var_s0[0], var_s0[1], var_s0[2]);
            var_s1 += 1;
            var_s0 += 3;
        } while (var_s1 < D_8620DF90);
    }
}
#endif

#ifdef VERSION_US
extern void func_80038E14(s32, s32, s32, s32, f32, f32, f32, s32);
extern void *D_8620E198;
s32 func_86200738(s32 arg0, s32 arg1) {
    func_80038E14(arg1, (*(s32 *)((u8 *)(D_8620E198) + (0x70))), (*(s32 *)((u8 *)(D_8620E198) + (0x74))), (*(s32 *)((u8 *)(D_8620E198) + (0x78))), (*(f32 *)((u8 *)(D_8620E198) + (0x7C))), (*(f32 *)((u8 *)(D_8620E198) + (0x80))), (*(f32 *)((u8 *)(D_8620E198) + (0x84))), 0);
    return 1;
}
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_86200794(s32 a, void *p) {
    s16 pad;
    s32 x;
    s16 y;
    s16 z;

    if (a == 2) {
        func_80037120(
            D_80094908 + 0xB4,
            D_80094908 + 0xA8,
            &x,
            &y,
            &z
        );
        *(s16 *)((u8 *)p + 0x1C) = y + 0x2000;
        *(s16 *)((u8 *)p + 0x1E) = z - 0x2000;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 D_80094908;
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
s32 func_862007FC(s32 arg0, void *arg1) {
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
void func_862007FC_padding(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86200870.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_862009E4.s")
#endif

#ifdef VERSION_US
extern f32 D_8620E05C;
extern void func_800277F0(u32, void *);
typedef struct Candidate86200AD4Vec { f32 x, y, z; } Candidate86200AD4Vec;
typedef struct Candidate86200AD4Obj { u8 pad0[0x10]; Candidate86200AD4Vec v; u8 pad1[0x2C]; Candidate86200AD4Vec p; } Candidate86200AD4Obj;
typedef struct Candidate86200AD4Obj1 { u8 pad0[0x34]; f32 q34; u8 pad38[0x10]; f32 q48; } Candidate86200AD4Obj1;
extern void * D_8620E198;
void func_86200AD4(Candidate86200AD4Obj *arg0, Candidate86200AD4Obj1 *arg1, Candidate86200AD4Vec *arg2, Candidate86200AD4Vec *arg3, f32 arg4) {
    f32 temp_fv0;
    f32 temp_fv1;

    arg0->p.x = arg0->p.x + arg3->x * arg4;
    arg0->p.y = arg0->p.y + arg3->y * arg4;
    arg0->p.z = arg0->p.z + arg3->z * arg4;
    temp_fv0 = arg3->x;
    temp_fv1 = *(f32 *)((u8 *)D_8620E198 + 0xC) * -2.0f * (temp_fv0 * arg0->v.x + arg3->y * arg0->v.y + arg3->z * arg0->v.z);
    arg2->x = arg2->x + temp_fv0 * temp_fv1;
    arg2->y = arg2->y + arg3->y * temp_fv1;
    arg2->z = arg2->z + arg3->z * temp_fv1;
    if (*(f32 *)((u8 *)D_8620E198 + 0x64) * 0.75f * 100.0f * arg1->q34 * D_8620E05C < arg4 && arg1->q48 > 55.0f) {
        func_800277F0(0xBF03U, (u8 *)arg1 + 0x38);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86200C30.s")
#endif

void func_862012F8(void) {
}

#ifdef VERSION_US
extern void func_86200C30(s32, void *, void *, s32 *, f32 *);
void func_86201300(void *arg0, void *arg1) {
    s32 i;
    f32 v[3];
    s32 count;
    u8 *p;

    count = 0;
    v[2] = 0.0f;
    v[1] = 0.0f;
    v[0] = 0.0f;
    p = *(u8 **)((u8 *)arg1 + 4);
    i = 0;
    if (*(s32 *)((u8 *)arg1 + 8) > 0) {
        do {
            func_86200C30(*(s32 *)arg1, arg0, p, &count, v);
            i += 1;
            p += 0x14;
        } while (i < *(s32 *)((u8 *)arg1 + 8));
    }
    if (count > 0) {
        *(f32 *)((u8 *)arg0 + 0x10) += v[0] / (f32)count;
        *(f32 *)((u8 *)arg0 + 0x14) += v[1] / (f32)count;
        *(f32 *)((u8 *)arg0 + 0x18) += v[2] / (f32)count;
    }
}
#endif

#ifdef VERSION_US
extern f32 func_86207EB0();
void func_86201418(s32 arg0, s32 arg1, void *arg2) {
    struct Point { f32 x; f32 y; f32 z; };
    struct Point direction;
    u8 pad[0x80];
    f32 distance;

    direction.x = 0.0f;
    direction.z = 0.0f;
    direction.y = -1.0f;
    distance = func_86207EB0(arg0, arg2, &direction);
    *(f32 *)((u8 *)arg1 + 0x48) = ((struct Point *)arg2)->x;
    *(f32 *)((u8 *)arg1 + 0x4C) = ((struct Point *)arg2)->y + direction.y * distance;
    *(f32 *)((u8 *)arg1 + 0x50) = ((struct Point *)arg2)->z;
}
#endif

#ifdef VERSION_US
extern void *D_87F119D8;
extern void *D_87F119DC;
extern void func_87F026E8(void *, void *);
void func_8620148C(void) {
    func_87F026E8(D_87F119D8, D_87F119DC);
}
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
extern u8 D_86209350[];
void func_862014B8(s32 arg0, s32 arg1) {
    if (arg0 == 5) {
        gDPPipeSync(D_800D0510++);
        gSPSegment(D_800D0510++, 0xF,
                   func_8004CA60((u8 *)func_8004C990(0x133, 0)));
        gDPSetEnvColor(D_800D0510++, 0, 0, 0, 0x80);
        gSPDisplayList(D_800D0510++, D_86209350);
        func_8003CD84();
    }
}
#endif

#ifdef VERSION_US
extern void *func_87F025B8(void *, void *);
extern void func_8003F1DC(void *);
extern void func_8003F114(void *, s32, s32, s32);
extern void func_8620148C(void);
extern void * D_8620E198;
s32 func_8620157C(s32 arg0) {
    void *result; void *ptr; f32 scale;
    result = func_87F025B8((u8 *)D_8620E198 + 0xED88, (void *)func_8620148C);
    if (result != NULL) {
        ptr = (u8 *)result + 0x24;
        func_8003F1DC(ptr);
        func_8003F114(ptr, 0, -1, *(s32 *)((u8 *)D_8620E198 + 0x13C));
        scale = *(f32 *)((u8 *)arg0 + 0x34) * (*(f32 *)((u8 *)D_8620E198 + 0x64) * 0.75f);
        *(f32 *)((u8 *)result + 0x5C) = scale;
        *(f32 *)((u8 *)result + 0x58) = scale;
        *(f32 *)((u8 *)result + 0x54) = scale;
    }
    return (s32)result;
}
#endif

#ifdef VERSION_US
extern void *D_8620E198;
extern s32 func_86200870(void *);
extern s32 func_8620157C(s32);
extern void func_86201418(s32, s32, void *);
void func_86201620(void) {
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    void *var_s0;
    var_s0 = *(void **)((u8 *)D_8620E198 + 0x180);
    if (var_s0 != NULL) {
        do {
            temp_s1 = *(s32 *)((u8 *)var_s0 + 0x20);
            temp_v0 = func_86200870(var_s0);
            if (temp_v0 != 0) {
                temp_v0_2 = func_8620157C(temp_s1);
                if (temp_v0_2 != 0) {
                    func_86201418(temp_v0, temp_v0_2, (u8 *)var_s0 + 0x48);
                }
            }
            var_s0 = *(void **)((u8 *)var_s0 + 4);
        } while (var_s0 != NULL);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_8620169C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86201790.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_862017F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86201A58.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_86209270[];
extern void func_8003CD84(void);
void func_86201DE4(s32 arg0, s32 arg1) {
    if (arg0 == 5) {
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238);
        gSPDisplayList(D_800D0510++, D_86209270);
        func_8003CD84();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86201E70.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_8620218C.s")
#endif

#ifdef VERSION_US
extern void func_8620218C(void *, void *);
extern void * D_8620E198;
void func_86202574(void) {
    void *outer;
    void *inner;
    outer = *(void **)((u8 *)D_8620E198 + 0x180);
    while (outer != NULL) {
        inner = *(void **)((u8 *)outer + 4);
        while (inner != NULL) {
            if (outer != inner) {
                func_8620218C(outer, inner);
            }
            inner = *(void **)((u8 *)inner + 4);
        }
        outer = *(void **)((u8 *)outer + 4);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_862025E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_862026C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_862028F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86202AC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86202C14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86202E94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_8620392C.s")
#endif

#ifdef VERSION_US
extern void func_87D00354(void *, f32 *);
typedef struct F86203B08Node F86203B08Node;
struct F86203B08Node {
    u8 pad00[4];
    F86203B08Node *next;
    u8 pad08[0x18];
    f32 *origin;
    u8 pad24[0x24];
    f32 x;
    f32 y;
    f32 z;
    u8 pad54[0x30];
    u8 transform[0x30];
    f32 savedX;
    f32 savedY;
    f32 savedZ;
};
typedef union F86203B08AlignedDelta {
    f32 v[3];
    f64 alignment;
} F86203B08AlignedDelta;
extern void * D_8620E198;
void func_86203B08(void) {
    F86203B08Node *p;
    f32 delta[3];
    f32 *origin;

    p = *(F86203B08Node **)((u8 *)D_8620E198 + 0x180);
    if (p != NULL) {
        do {
            origin = p->origin;
            delta[0] = p->x - origin[0];
            delta[1] = p->y - origin[1];
            delta[2] = p->z - origin[2];
            func_87D00354(p->transform, delta);
            p->savedX = p->x;
            p->savedY = p->y;
            p->savedZ = p->z;
            p = p->next;
        } while (p != NULL);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86203BA8.s")
#endif

#ifdef VERSION_US
void func_86203BEC(void) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    void *temp_v1;
    void *var_v0;

    var_v0 = (*(void **)((u8 *)(D_8620E198) + (0x180)));
    if (var_v0 != NULL) {
        do {
            temp_v1 = (*(void **)((u8 *)(var_v0) + (0x20)));
            temp_fv1 = (*(f32 *)((u8 *)(var_v0) + (0x48))) - (*(f32 *)((u8 *)(temp_v1) + (0x3C)));
            temp_fa0 = (*(f32 *)((u8 *)(var_v0) + (0x4C))) - (*(f32 *)((u8 *)(temp_v1) + (0x40)));
            temp_fa1 = (*(f32 *)((u8 *)(var_v0) + (0x50))) - (*(f32 *)((u8 *)(temp_v1) + (0x44)));
            (*(f32 *)((u8 *)(temp_v1) + (0x48))) = sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1));
            var_v0 = (*(void **)((u8 *)(var_v0) + (4)));
        } while (var_v0 != NULL);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86203C58.s")
#endif

#ifdef VERSION_US
extern f32 D_80087E50[];
extern f32 D_80088E50[];
extern void func_87F0C000(f32 *);
extern void * D_8620E198;
void func_86203D50(void) { if (*(s32 *)((u8 *)D_8620E198 + 0x90) == 0) { *(s16 *)((u8 *)D_8620E198 + 0x8E) += 0x2E; *(f32 *)((u8 *)D_8620E198 + 0x7C) = D_80087E50[(*(u16 *)((u8 *)D_8620E198 + 0x8E)) >> 4] * -400.0f; *(f32 *)((u8 *)D_8620E198 + 0x84) = D_80088E50[(*(u16 *)((u8 *)D_8620E198 + 0x8E)) >> 4] * -400.0f; func_87F0C000((f32 *)((u8 *)D_8620E198 + 0x70)); } }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86203DE8.s")
#endif

#ifdef VERSION_US
extern void *D_8620E198;
extern void *func_87F0A3E8(void *);
extern void func_86203DE8(void);
extern void func_86203C58(void);
extern void func_86200020(s32 arg0);
void func_86203ED8(void) {
    if (func_87F0A3E8((u8 *)D_8620E198 + 0x73C54) != NULL) {
        if (*(u8 *)((u8 *)*(void **)((u8 *)D_8620E198 + 0xF4) + 0x2180) == 1) {
            func_86200020(2);
        } else {
            *(s32 *)((u8 *)D_8620E198 + 0xE8) = 6;
        }
    }
    func_86203DE8();
    func_86203C58();
}
#endif

#ifdef VERSION_US
extern f32 D_8620E0B8;
extern f32 D_8620E0BC;
extern f32 D_8620E0C0;
extern void func_87F06240(s32, s32, f32, f32, s32);
extern Gfx * D_800D0510;
void func_86203F50(s32 n, s32 x, s32 y, u8 r1, u8 g1, u8 b1, u8 r2, u8 g2, u8 b2) {
    gDPSetPrimColor(D_800D0510++, 0, 0, r1, g1, b1, 0xFF);
    gDPSetEnvColor(D_800D0510++, r2, g2, b2, 0xFF);
    if (n < 10) {
        func_87F06240(x + 0x24, y + 2, D_8620E0B8, D_8620E0B8, n % 10);
        return;
    }
    func_87F06240(x + 0x1C, y + 2, D_8620E0BC, D_8620E0BC, n / 10);
    func_87F06240(x + 0x29, y + 2, D_8620E0C0, D_8620E0C0, n % 10);
}
#endif

#ifdef VERSION_US
extern void func_8004D1FC(void *);
extern void func_80044270(s32, s32, s16, s16, s32, s32, s32, s32, s32);
extern void func_87F0D600(void *, s32, s32, s32, f32, f32);
extern void func_87F061F0(void);
extern s32 func_80001FF0(void);
extern f32 D_8620E0C4;
extern f32 D_8620E0C8;
extern f32 D_8620E0CC;
extern f32 D_8620E0D0;
extern Gfx D_80094E38[];
extern Gfx D_80094F50[];
extern s32 func_8004C990(s32, s32);
extern void func_86203F50(s32 n, s32 x, s32 y, u8 r1, u8 g1, u8 b1, u8 r2, u8 g2, u8 b2);
extern void func_87F06240(s32, s32, f32, f32, s32);
extern Gfx * D_800D0510;
extern void * D_8620E198;
void func_862040AC(void) {
    s32 amount;
    u16 *p;
    f32 scale;
    f32 xa, ya;
    f32 bx, by;
    s32 second, first;
    Gfx *g;
    if (*(u8 *)((u8 *)*(void **)((u8 *)D_8620E198 + 0xF4) + 0x2180) != 4) {
    gSPDisplayList(D_800D0510++, D_80094E38);
        p = (u16 *)func_8004C990(0x1B2, *((u8 *)D_8620E198 + 0x73CB8));
        func_8004D1FC(p);
        scale = D_8620E0C4;
        xa = (f32)p[0] * scale;
        if (xa > 0.0f) { bx = 0.5f; } else { bx = -0.5f; }
        ya = (f32)p[1] * scale;
        if (ya > 0.0f) { by = 0.5f; } else { by = -0.5f; }

        func_80044270(0x1C, 0x10, (s16)(s32)(bx + xa), (s16)(s32)(by + ya), 0, 0, 0x500, 0x500, 0);
        p = (u16 *)func_8004C990(0x1B2, *((u8 *)D_8620E198 + 0x73CB9));
        func_8004D1FC(p);

        xa = (f32)p[0] * scale;
        if (xa > 0.0f) { bx = 0.5f; } else { bx = -0.5f; }
        ya = (f32)p[1] * scale;
        if (ya > 0.0f) { by = 0.5f; } else { by = -0.5f; }

        func_80044270(0x61, 0x10, (s16)(s32)(bx + xa), (s16)(s32)(by + ya), 0, 0, 0x500, 0x500, 0);
        p = (u16 *)func_8004C990(0x1B2, *((u8 *)D_8620E198 + 0x73CBA));
        func_8004D1FC(p);

        xa = (f32)p[0] * scale;
        if (xa > 0.0f) { bx = 0.5f; } else { bx = -0.5f; }
        ya = (f32)p[1] * scale;
        if (ya > 0.0f) { by = 0.5f; } else { by = -0.5f; }

        func_80044270(0xA6, 0x10, (s16)(s32)(bx + xa), (s16)(s32)(by + ya), 0, 0, 0x500, 0x500, 0);
        p = (u16 *)func_8004C990(0x1B2, *((u8 *)D_8620E198 + 0x73CBB));
        func_8004D1FC(p);

        xa = (f32)p[0] * scale;
        if (xa > 0.0f) { bx = 0.5f; } else { bx = -0.5f; }
        ya = (f32)p[1] * scale;
        if (ya > 0.0f) { by = 0.5f; } else { by = -0.5f; }

        func_80044270(0xEB, 0x10, (s16)(s32)(bx + xa), (s16)(s32)(by + ya), 0, 0, 0x500, 0x500, 0);
    gSPDisplayList(D_800D0510++, D_80094F50);
    func_87F0D600((u8 *)D_8620E198 + 0xF8, 0, 0x1C, 0x10, scale, scale);
    func_87F0D600((u8 *)D_8620E198 + 0xF8, 1, 0x61, 0x10, scale, scale);
    func_87F0D600((u8 *)D_8620E198 + 0xF8, 2, 0xA6, 0x10, scale, scale);
    func_87F0D600((u8 *)D_8620E198 + 0xF8, 3, 0xEB, 0x10, scale, scale);
    func_87F061F0();
    func_86203F50(*(s32 *)((u8 *)D_8620E198 + 0x73BC0), 0x1C, 0x10, 0x0, 0x0, 0x9B, 0xAA, 0xF5, 0xFF);
    func_86203F50(*(s32 *)((u8 *)D_8620E198 + 0x73BD8), 0x61, 0x10, 0x0, 0x64, 0x0, 0xC8, 0xFF, 0x9B);
    func_86203F50(*(s32 *)((u8 *)D_8620E198 + 0x73BF0), 0xA6, 0x10, 0x78, 0x0, 0x0, 0xFF, 0xA0, 0xBE);
    func_86203F50(*(s32 *)((u8 *)D_8620E198 + 0x73C08), 0xEB, 0x10, 0xD2, 0x5A, 0x0, 0xFF, 0xFF, 0x8C);
    first = func_80001FF0();
    second = func_80001FF0();
    amount = (*(s32 *)((u8 *)D_8620E198 + 0x73BAC) + (first >> 1) - 1) / (second >> 1);
    gDPSetPrimColor(D_800D0510++, 0, 0, 0xC8, 0xFF, 0x73, 0xFF);
    gDPSetEnvColor(D_800D0510++, 0, 0x46, 0, 0xFF);
    if (amount < 10) {
        func_87F06240(0xF4, 0xC0, D_8620E0C8, D_8620E0C8, amount % 10);
        return;
    }
    func_87F06240(0xEB, 0xC0, D_8620E0CC, D_8620E0CC, amount / 10);
    func_87F06240(0xFD, 0xC0, D_8620E0D0, D_8620E0D0, amount % 10);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_862048B0.s")
#endif

#ifdef VERSION_US
extern void func_8620739C(void);
extern s32 func_87F08208(void *);
extern void func_800225C4(s32);
extern void func_800279C4(s32);
extern void func_800226C0(s32);
extern void StageContext_SetClearColor(s32);
extern void func_86200020(s32 arg0);
void func_86204A00(void) {
    s32 temp_v0;
    func_8620739C();
    temp_v0 = func_87F08208((u8 *)D_8620E198 + 0x73C1C);
    switch (temp_v0) {
    case 1:
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0x14);
        *(s32 *)((u8 *)D_8620E198 + 0xE8) = 2;
        func_800225C4(0x28);
        func_800279C4(0xCF0B);
        break;
    case 2:
        func_86200020(0);
        func_800226C0(3);
        break;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86204A9C.s")
#endif

#ifdef VERSION_US
extern void func_86206334();
void func_86204EB8(void) {
    if (StageContext_GetFadeMode() == 1) {
        func_8620736C();
        func_86206304();
        func_86206334();
        StageFade_StartFromOpaque(0x14);
        (*(s32 *)((u8 *)(D_8620E198) + (0xE8))) = 3;
        func_87F00688();
    }
    func_8620739C();
}
#endif

#ifdef VERSION_US
extern s32 func_87F01A40(void);
extern u32 func_87F006AC(void);
extern void func_800279C4(s32);
extern void func_80021ED8(s32);
extern void func_86200020(s32 arg0);
void func_86204F20(void) {
    s32 state;

    if (StageContext_GetFadeMode() == 0) {
        state = func_87F01A40();
    } else {
        state = 2;
    }
    switch (state) {
    case 0:
    case 2:
        if (func_87F006AC() == 1) {
            func_800279C4(0x2F00);
        }
        if (func_87F006AC() == 2) {
            *(s32 *)((u8 *)D_8620E198 + 0xE8) = 4;
            func_800279C4(0x2F01);
            func_80021ED8(0x2F);
            return;
        }
        return;
    case 3:
        func_86200020(0);
        return;
    case 4:
        func_86200020(1);
        break;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86204FEC.s")
#endif

#ifdef VERSION_US
extern void func_862048B0();
extern void func_86204FEC();
void func_862052A0(void) {
    func_800086A4(2);
    StageFade_StartFromOpaque(0xA);
    do {
        func_80064D28();
        func_86204FEC();
        func_862048B0();
    } while ((*(s32 *)((u8 *)(D_8620E198) + (0xE8))) != 8);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_266A60/func_86205308.s")
#endif
