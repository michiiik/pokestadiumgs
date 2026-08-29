#include "global.h"


#ifdef VERSION_US
s32 func_8006DC50(s32 arg0) {
    s32 sp4;
    return ((((u8 *)&sp4) + (arg0 * 0x50)) - ((u8 *)&sp4)) + 0x40;
}
#endif

#ifdef VERSION_US
s32 func_8006DC78(s32 arg0) { u8 local[1]; return (local + (arg0 << 4)) - local; }
#endif

#ifdef VERSION_US
f32 Math_FAbs(f32 arg0) { if (arg0 < 0.0f) { arg0 = -arg0; } return arg0; }
#endif

#ifdef VERSION_US
void func_8006DCB8(void) {}
void func_8006DCB8_padding(void) {}
void func_8006DCB8_padding2(void) {}
#endif

#ifdef VERSION_US
extern s16 D_8009E5CC[];
extern u16 D_8009E3C8[];
extern s16 D_8009E7D0[];
extern s16 D_8009E9D4[];
extern s16 D_8009EBD8[];
extern s16 D_8009EDDC[];
extern s16 D_8009EFE0[];
s16 Model_GetVertexClass(s16 *arg0, s32 arg1) {
    s16 index;
    s16 value;

    index = arg0[arg1];
    value = D_8009E5CC[index]; if (value > 0) return 0;
    value = ((s16 *)D_8009E3C8)[index]; if (value > 0) return 1;
    value = D_8009E7D0[index]; if (value > 0) return 2;
    value = D_8009E9D4[index]; if (value > 0) return 3;
    value = D_8009EBD8[index]; if (value > 0) return 4;
    value = D_8009EDDC[index]; if (value > 0) return 5;
    value = D_8009EFE0[index]; if (value > 0) return 6;
    return index;
}
#endif

#ifdef VERSION_US
extern u8 D_8009E1C4[]; s32 Model_GetVertexThreshold(s16 *arg0,s32 arg1){s16 v=arg0[arg1]; s16 r=*(s16*)(D_8009E1C4+(v<<1)); if(r>0)return r; return 0;}
#endif

#ifdef VERSION_US
extern s16 D_8009DFC0[];
s16 func_8006DDE8(s16 *arg0, s32 arg1) {
    s16 *table = D_8009DFC0;
    s16 value = arg0[arg1];
    s16 result = table[value];
    return result;
}
#endif

#ifdef VERSION_US
s16 func_8006DE08(s16 *arg0, s32 arg1) { s16 index = arg0[arg1]; u16 *table = D_8009E3C8 + index; s16 result = (s16)(*table - 1); return result; }
#endif

#ifdef VERSION_US
s16 func_8006DE34(s16 *arg0, s32 arg1) {
    s16 *table = D_8009E7D0;
    s16 value = arg0[arg1];
    s16 result = table[value];
    return result;
}
#endif

#ifdef VERSION_US
s16 func_8006DE54(s16 *arg0, s32 arg1)
{
  s16 value = arg0[arg1];
  s16 new_var;
  new_var = D_8009E9D4[value];
  return new_var;
}
#endif

#ifdef VERSION_US
s16 func_8006DE74(s16 *arg0, s32 arg1)
{
  s16 new_var;
  s16 value = arg0[arg1];
  new_var = D_8009EBD8[value];
  return new_var;
}
#endif

void func_8006DE94(void) {
}

#ifdef VERSION_US
s16 func_8006DE9C(s16 *arg0, s32 arg1)
{
  s16 new_var;
  s16 value = arg0[arg1];
  new_var = D_8009EFE0[value];
  return new_var;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006DEBC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006E1C8.s")
#endif

#ifdef VERSION_US
extern void func_8006DEBC(void *); extern void func_8006F23C(void *); void func_8006E2D0(void *arg0) { func_8006DEBC(arg0); func_8006F23C(arg0); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006E2F8.s")
#endif

#ifdef VERSION_US
void func_8006E7DC(f32 (*arg0)[4], void *arg1) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    sp3C = (*(f32 *)((u8 *)(arg1) + (0)));
    sp38 = (*(f32 *)((u8 *)(arg1) + (4)));
    sp34 = (*(f32 *)((u8 *)(arg1) + (8)));
    guMtxXFMF(arg0, sp3C, sp38, sp34, &sp3C, &sp38, &sp34);
    (*(f32 *)((u8 *)(arg1) + (0xC))) = sp3C;
    (*(f32 *)((u8 *)(arg1) + (0x10))) = sp38;
    (*(f32 *)((u8 *)(arg1) + (0x14))) = sp34;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006E858.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006E944.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006EA18.s")
#endif

#ifdef VERSION_US
typedef struct Copy60 { s32 words[15]; } Copy60;
void Model_CopyPositionBuffer(void *arg0, void *arg1) {
    *(Copy60 *)arg1 = *(Copy60 *)arg0;
}
void func_8006EB14_padding(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006EB54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006ED10.s")
#endif

#ifdef VERSION_US
extern f32 D_800A5990;
extern f32 D_800A5994;
extern f32 D_800A5998;
f32 func_8006EF04(f32 *arg0, f32 *arg1) {
    f32 x = arg0[3] - arg1[3];
    f32 y = arg0[4] - arg1[4];
    f32 z = arg0[5] - arg1[5];

    if (Math_FAbs(x) < D_800A5990) x = 0.0f;
    if (Math_FAbs(y) < D_800A5994) y = 0.0f;
    if (Math_FAbs(z) < D_800A5998) z = 0.0f;
    return sqrtf((x * x) + (y * y) + (z * z));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006EFF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006F0A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006F23C.s")
#endif

#ifdef VERSION_US
extern void func_8006EFF0(f32 *, f32 *, f32, f32, f32);
extern f32 func_8006EF04(f32 *arg0, f32 *arg1);
void func_8006F438(void *arg0, u8 *arg1, f32 arg2, f32 arg3)
{
  u8 *record;
  u8 *item;
  u8 *objA;
  u8 *objB;
  f32 *posA;
  f32 *posB;
  s16 indexA;
  s16 indexB;
  s16 flagA;
  u16 *new_var;
  s16 flagB;
  f32 weight;
  f32 computed;
  record = arg1;
  for (;;)
  {
    item = record + 8;
    record += 0x50;
    indexA = *((s16 *) item);
    if (indexA == (-1))
    {
      break;
    }
    indexB = *((s16 *) (item + 2));
    flagA = *((s16 *) (item + 4));
    flagB = *((s16 *) (item + 6));
    weight = *((f32 *) (item + 8));
    objA = arg1 + (indexA * 0x50);
    if ((*((u16 *) (objA + 0x4A))) != 0)
    {
      flagA = 0;
    }
    objB = arg1 + (indexB * 0x50);
    new_var = (u16 *) (objB + 0x4A);
    if ((*new_var) != 0)
    {
      flagB = 0;
    }
    if ((flagB != 0) || (flagA != 0))
    {
      posA = (f32 *) (objA + 0x14);
      posB = (f32 *) (objB + 0x14);
      computed = func_8006EF04(posA, posB);
      func_8006EFF0(posA, posB, weight, computed, arg3);
    }
  }

}
#endif

#ifdef VERSION_US
extern void func_8006F0A8(f32 *, f32 *, f32, f32, f32);
extern f32 func_8006EF04(f32 *arg0, f32 *arg1);
void func_8006F548(void *arg0, u8 *arg1, f32 arg2, f32 arg3)
{
  u8 *record;
  u8 *item;
  u8 *objA;
  u8 *objB;
  f32 *posA;
  f32 *posB;
  s16 indexA;
  s16 indexB;
  s16 flagA;
  u16 *new_var;
  s16 flagB;
  f32 weight;
  f32 computed;
  record = arg1;
  for (;;)
  {
    item = record + 8;
    record += 0x50;
    indexA = *((s16 *) item);
    if (indexA == (-1))
    {
      break;
    }
    indexB = *((s16 *) (item + 2));
    flagA = *((s16 *) (item + 4));
    flagB = *((s16 *) (item + 6));
    weight = *((f32 *) (item + 8));
    objA = arg1 + (indexA * 0x50);
    if ((*((u16 *) (objA + 0x4A))) != 0)
    {
      flagA = 0;
    }
    objB = arg1 + (indexB * 0x50);
    new_var = (u16 *) (objB + 0x4A);
    if ((*new_var) != 0)
    {
      flagB = 0;
    }
    if ((flagB != 0) || (flagA != 0))
    {
      posA = (f32 *) (objA + 0x14);
      posB = (f32 *) (objB + 0x14);
      computed = func_8006EF04(posA, posB);
      func_8006F0A8(posA, posB, weight, computed, arg3);
    }
  }

}
#endif

#ifdef VERSION_US
extern u32 Memmap_GetSegmentVaddr(u32);
void func_8006F658(u8 *arg0, u8 *arg1, f32 arg2) {
    s16 *classes;
    s16 *indices;
    s32 cls;
    s32 i;
    u16 count;
    u8 *record;

    classes = (s16 *)Memmap_GetSegmentVaddr(*(u32 *)(arg0 + 0x10));
    indices = (s16 *)Memmap_GetSegmentVaddr(*(u32 *)(arg0 + 0x14));
    count = *(u16 *)(arg0 + 4);
    record = arg1;
    i = 0;
    while (i < count) {
        cls = Model_GetVertexClass(classes, i);
        if ((cls != 0) && (cls != 1) && (i == *indices)) {
            *(f32 *)(record + 0x24) += arg2;
        }
        i++;
        record += 0x50;
        indices++;
    }
}
#endif

#ifdef VERSION_US
extern u32 Memmap_GetSegmentVaddr(u32);
void Model_OffsetVertexHeightsByClass(u8 *arg0, u8 *arg1, f32 arg2) {
    s16 *classes;
    s16 *indices;
    s32 cls1;
    s32 cls2;
    s32 i;
    u16 count;
    u8 *record;
    u8 *target;
    int new_var;

    classes = (s16 *)Memmap_GetSegmentVaddr(*(u32 *)(arg0 + 0x10));
    new_var = 0x14;
    indices = (s16 *)Memmap_GetSegmentVaddr(*(u32 *)(arg0 + new_var));
    count = *(u16 *)(arg0 + 4);
    record = arg1;
    i = 0;
    while (i < count) {
        cls1 = Model_GetVertexClass(classes, i);
        if ((cls1 != 0) && (i == *indices)) {
            cls2 = func_8006DE9C(classes, i);
            switch (cls2) {
            case 1:
                target = record + new_var;
                *(f32 *)(target + 0x10) += arg2;
                break;
            case 2:
                target = record + new_var;
                *(f32 *)(target + 0x10) += arg2 * 0.25f;
                break;
            }
        }
        i++;
        record += 0x50;
        indices++;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006F83C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006F9B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006FBC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8006FF80.s")
#endif

#ifdef VERSION_US
extern u32 Memmap_GetSegmentVaddr(u32);
extern void func_8006FF80(void *, s32);
extern Mtx D_80129038;
Gfx *Model_Draw(Gfx *arg0, void *arg1, s32 arg2) {
    void *segment;
    segment = (void *)(u32)Memmap_GetSegmentVaddr(*(u32 *)((u8 *)arg1 + 4));
    if (*(u16 *)segment >= 0xF) {
        return arg0;
    }
    func_8006FF80(arg1, arg2);
    gMoveWd(arg0++, G_MW_SEGMENT, 0x38, arg2);
    gSPMatrix(arg0++, &D_80129038, G_MTX_PUSH);
    gSPDisplayList(arg0++, *(void **)((u8 *)segment + 0x1C));
    gSPPopMatrixN(arg0++, G_MTX_MODELVIEW, 1);
    return arg0;
}
#endif

#ifdef VERSION_US
extern s16 *func_80003240(s32);
extern s32 D_8009491C;
s16 ModelRenderer_GetObjectType(void) {
    s16 result;
    result = *func_80003240(D_8009491C + 0x1A);
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_8007074C.s")
#endif

#ifdef VERSION_US
extern u16 *func_8003F54C(void *);
extern u16 D_80094904[];
extern void func_81003F44(void);
void func_800707D0(void *arg0) {
    u16 *state = func_8003F54C(arg0);

    if ((state != NULL) && (*(s16 *)((u8 *)arg0 + 0x1A) != 0xDB)) {
        state[0] = 0;
        state[1]++;
        if (state[2] == D_80094904[0]) {
            state[3] = 0;
        } else {
            state[3] = 1;
        }
        state[2] = D_80094904[0];
        ((void (*)(void))func_80003240((s32)func_81003F44))();
    }
}
#endif

#ifdef VERSION_US
extern s16 D_80129078; void func_80070860(s32 arg0) { D_80129078++; }
#endif

#ifdef VERSION_US
extern void MtxF_Copy(u32 *, u32 *);
extern u32 *func_8003936C(s32);
extern void func_8006E1C8();
extern void func_8006FBC4();
void func_80070FDC(f32 arg0[4][4]);
void func_80071068(f32 arg0[4][4]);
extern f32 D_80129080[4][4];
extern f32 D_80129120[4][4];
extern f32 D_8009F3B0[4][4];
void func_8007087C(void) {
    u16 *state;
    u8 *entry;
    f32 scaleMtx[4][4];

    state = func_8003F54C((void *)D_8009491C);
    if (state != NULL) {
        entry = *(u8 **)(((u8 (*)[4])state)[(s16)*state] + 0xC);
        MtxF_Copy(D_80129120[0], func_8003936C(0));
        func_80070FDC(D_80129120);
        func_80071068(D_80129120);
        if ((*(s16 *)(entry + 2) == 0) || (*(s16 *)((u8 *)state + 6) == 0)) {
            guScaleF(scaleMtx, 1.0f, 1.0f, 1.0f);
            func_8006E1C8(entry, D_80129080, D_80129120, D_8009F3B0, scaleMtx);
            *(s16 *)(entry + 2) = 1;
        } else {
            func_8006FBC4(entry, D_80129120);
        }
    }
}
#endif

#ifdef VERSION_US
extern Gfx *Gfx_AllocDisplayList(s32);
extern Gfx *func_80070A4C(Gfx *);
extern Gfx *Model_Draw(Gfx *, void *, s32);
extern u8 D_8009F3D0[];
extern u8 D_8009F410[];
Gfx *func_80070974(Gfx *arg0) {
    s16 *state;
    void *entry;
    s32 matrix;
    Gfx *gfx;

    state = (s16 *)func_8003F54C((void *)D_8009491C);
    if (state == NULL) {
        return arg0;
    }
    entry = ((void **)state)[(s16)*state + 3];
    matrix = Gfx_AllocDisplayList(0xA0);
    gSPMatrix(arg0++, D_8009F3D0, G_MTX_LOAD | G_MTX_PUSH);
    gfx = func_80070A4C(arg0);
    gfx = Model_Draw(gfx, entry, matrix);
    gSPPopMatrixN(gfx++, G_MTX_MODELVIEW, 1);
    gSPDisplayList(gfx++, D_8009F410);
    (*state)++;
    return gfx;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_80070A4C.s")
#endif

#ifdef VERSION_US
f32 Math_AbsF32(f32 arg0) { if ((f64)arg0 < 0.0) { arg0 = -arg0; } return arg0; }
#endif

#ifdef VERSION_US
void Vec3f_CrossProductComponents(f32 a0, f32 a1, f32 a2, f32 a3, f32 a4, f32 a5,
                   f32 *o0, f32 *o1, f32 *o2) {
    *o0 = (a1 * a5) - (a2 * a4);
    *o1 = (a2 * a3) - (a0 * a5);
    *o2 = (a0 * a4) - (a1 * a3);
}
#endif

#ifdef VERSION_US
void func_80070C14(f32 *arg0, f32 *arg1, f32 *arg2) { f32 x = *arg0; f32 y = *arg1; f32 z = *arg2; f32 length = sqrtf(x * x + y * y + z * z); if (length > 0.0f) { x /= length; y /= length; z /= length; } *arg0 = x; *arg1 = y; *arg2 = z; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_80070C68.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6E850/func_80070DEC.s")
#endif

#ifdef VERSION_US
void func_80070F30(f32 *arg0, f32 *arg1) {
    f32 x0 = arg0[0];
    f32 y0 = arg0[1];
    f32 z0 = arg0[2];
    f32 x1 = arg0[4];
    f32 y1 = arg0[5];
    f32 z1 = arg0[6];
    f32 x2 = arg0[8];
    f32 y2 = arg0[9];
    f32 z2 = arg0[10];
    arg1[0] = sqrtf((x0 * x0) + (y0 * y0) + (z0 * z0));
    arg1[1] = sqrtf((x1 * x1) + (y1 * y1) + (z1 * z1));
    arg1[2] = sqrtf((x2 * x2) + (y2 * y2) + (z2 * z2));
}
#endif

#ifdef VERSION_US
void func_80070FDC(f32 arg0[4][4]) {
    u8 pad[12];
    f32 x;
    f32 y;
    f32 z;
    f32 translateMtx[4][4];
    f32 scaleMtx[4][4];
    f32 scale[3];

    func_80070F30((f32 *)arg0, scale);
    guScaleF(scaleMtx, scale[0], scale[1], scale[2]);
    guMtxXFMF(arg0, 0.0f, 0.0f, 0.0f, &x, &y, &z);
    guTranslateF(translateMtx, x, y, z);
    guMtxCatF(scaleMtx, translateMtx, arg0);
}
#endif

#ifdef VERSION_US
extern u8 *D_80094908;
extern void func_80070DEC(float [4][4], void *);
void func_80071068(float arg0[4][4]) {
    float temp[18];
    func_80070DEC((float (*)[4])(temp + 1), D_80094908 + 0x64);
    guMtxCatF((float (*)[4])(temp + 1), arg0, arg0);
}
#endif

#ifdef VERSION_US
typedef struct S1_SomeStruct {
    u32 padding[0x0C];
} S1_SomeStruct;
typedef struct S1_Vec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} S1_Vec3f;
typedef struct S1_PosBlend {
    /* 0x00 */ S1_Vec3f base;
    /* 0x0C */ S1_Vec3f offset;
} S1_PosBlend;
typedef struct S1_ModelSegment {
    /* 0x00 */ u16 type;
    /* 0x02 */ u16 nodeCount;
    /* 0x04 */ u16 vertexCount;
    /* 0x06 */ u16 triangleCount;
    /* 0x08 */ u32 indexSegment;
    /* 0x0C */ u32 childIndexSegment; // Model_BuildVertexRuntimeData: -1-terminated per-vertex child-index lists
    /* 0x10 */ u32 tableSegment;
    /* 0x14 */ u32 remapSegment;
    /* 0x18 */ u32 vertexSegment;
    /* 0x1C */ Gfx* displayList;
} S1_ModelSegment;
typedef float S1_MtxF_t[4][4];
typedef union {
    S1_MtxF_t mf;
    struct {
        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
    };
} S1_MtxF;
typedef struct S1_StadiumTransform {
    /* 0x00 */ s32  unk_00;
    /* 0x04 */ f32  maxDist;
    /* 0x08 */ f32  x0;
    /* 0x0C */ f32  y0;
    /* 0x10 */ f32  z0;
    /* 0x14 */ f32  x1;
    /* 0x18 */ f32  y1;
    /* 0x1C */ f32  z1;
    /* 0x20 */ f32  x2;
    /* 0x24 */ f32  y2;
    /* 0x28 */ f32  z2;
    /* 0x2C */ f32  x3;
    /* 0x30 */ f32  y3;
    /* 0x34 */ f32  z3;
    /* 0x38 */ S1_MtxF* mtx;
} S1_StadiumTransform;
typedef struct S1_ModelTransformCmd {
    /* 0x00 */ s16 targetIndex;
    /* 0x02 */ s16 sourceIndex;
    /* 0x04 */ s16 enableFrom;
    /* 0x06 */ s16 enableTo;
    /* 0x08 */ f32 blendWeight;
} S1_ModelTransformCmd;
typedef struct S1_ModelVertex {
    /* 0x00 */ s16 jointIndex;      // bone / transform index
    /* 0x02 */ s16 parentIndex;     // parent bone index
    /* 0x04 */ s16 childIndex;      // child / next transform
    /* 0x06 */ u16  pad06;
    /* 0x08 */ S1_ModelTransformCmd cmd;
    /* 0x14 */ u8   pad14[0xC];
    /* 0x20 */ f32 linkDistance; // Model_LinkNearestVertices: compared against a distance threshold to find nextIndex
    /* 0x24 */ u8  pad24[0x40];
    /* 0x64 */ S1_PosBlend position;   // base + animated offset
    /* 0x7C */ f32 colorR;          // vertex color (float)
    /* 0x80 */ f32 colorG;
    /* 0x84 */ f32 colorB;
    /* 0x88 */ s16 texS;            // texture coordinate S
    /* 0x8A */ s16 texT;            // texture coordinate T
    /* 0x8C */ u8  alpha;           // vertex alpha
    /* 0x8D */ u8  pad8D;
    /* 0x8E */ u16 disabled;      // enable / visibility / animation flags
    /* 0x90 */ s16 drawGroup;       // render group / material group
    /* 0x92 */ s16 nextIndex;       // linked-list / chain index
} S1_ModelVertex;
typedef struct S1_StadiumModel {
    /* 0x00 */  s16 unk_00;
    /* 0x02 */  s16 transformCount; // Model_ApplyVertexTransforms/LinkNearestVertices loop bound
    /* 0x04 */  S1_StadiumTransform transforms[5];
    /* 0x130 */ u32 modelSegment;
    /* 0x134 */ s8 pad134[0x24];
    /* 0x158 */ S1_Vec3f position;
    /* 0x164 */ s8 pad164[0xC];
    /* 0x170 */ S1_ModelVertex mvtx;
} S1_StadiumModel;
extern Mtx D_80129038;
void Gfx_SetCombineMode(Gfx* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16) {
    gDPSetCombine(arg0++, GCCc0w0(arg1, arg3, arg5, arg7) | GCCc1w0(arg9, arg11), GCCc0w1(arg2, arg4, arg6, arg8) | GCCc1w1(arg10, arg13, arg15, arg12, arg14, arg16));
}
#endif

void func_800711A8(void) {
}

#ifdef VERSION_US
s32 func_800711B0(void) { return 0; }
#endif

#ifdef VERSION_US
void func_800711B8(s32 arg0)
{
  s32 var_v0;
  s32 var_v1;
 do { var_v0 = 0; do { var_v1 = 8 * 0; loop_2: var_v1 += 1; if (var_v1 != 2) { goto loop_2; } var_v0 += 1; } while (var_v0 != 8); } while (0);
}
#endif

#ifdef VERSION_US
void func_800711EC(s32 arg0) {
    s32 var_v0;

    var_v0 = 0;
loop_1:
    var_v0 += 1;
    if (var_v0 != 4) {
        goto loop_1;
    }
    return;
}
#endif
