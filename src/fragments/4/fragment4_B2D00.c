#include "global.h"


#ifdef VERSION_US
typedef struct {
    u8 unk_00[24];
    s32 comparison_key;
    void *unk_1C;
    void *unk_20;
    u8 *unk_24;
    u8 *unk_28;
} Fragment4ResourceView;
typedef struct {
    void (*initialize)(void *, void *);
    Fragment4ResourceView resources;
    void *variants;
} Fragment4DefinitionView;
typedef struct {
    Fragment4DefinitionView **definitions;
    s32 unk_04;
    u8 *controller;
    u8 unk_0C[8];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 unk_1F;
    u8 count;
    u8 unk_21;
    f32 progress;
    f32 unk_28;
    f32 unk_2C;
    // Status words produced by func_81804BC8.
    s32 unk_30;
    s32 unk_34;
} Fragment4StateView;
extern u8 D_800CE060[];
extern void func_81802DC8(u8 *);
extern void func_81802E34(u8 *);
extern void func_81803B18(void *);
extern void func_81802D98(void *);
extern void func_81803C9C();
extern f32 func_818006B4(void);
extern u8 *func_818054D0(void *, u8);
void WidgetResources_Release(s32 arg0) {
    u8 *entry;

    if (((Fragment4ResourceView *)arg0)->unk_28 != NULL) {
        entry = ((Fragment4ResourceView *)arg0)->unk_28;
        while (*(s16 *)entry >= 0) {
            func_81802DC8(entry);
            entry += 32;
        }
    }
    if (((Fragment4ResourceView *)arg0)->unk_24 != NULL) {
        entry = ((Fragment4ResourceView *)arg0)->unk_24;
        while (*(s16 *)entry >= 0) {
            func_81802E34(entry);
            entry += 32;
        }
    }
    if (((Fragment4ResourceView *)arg0)->unk_20 != NULL) {
        func_81803B18(((Fragment4ResourceView *)arg0)->unk_20);
    }
    if (((Fragment4ResourceView *)arg0)->unk_1C != NULL) {
        func_81802D98(((Fragment4ResourceView *)arg0)->unk_1C);
    }
}

extern void func_8004C8C0(s32 arg0);
void func_818047E0(s32 arg0) {
    s32 var_s0;
    s32 var_a1;

    var_s0 = *(s32 *)((u8 *)(u32)arg0 + 0x30);
    var_a1 = arg0;
    WidgetResources_Release(arg0 + 4);
    if (*(s32 *)((u8 *)(u32)var_a1 + 0x30) != 0) {
        if (*(s16 *)(u8 *)(u32)var_s0 >= 0) {
            do {
                WidgetResources_Release(*(s32 *)((u8 *)(u32)var_s0 + 4));
                var_s0 += 8;
            } while (*(s16 *)((u8 *)(u32)var_s0) >= 0);
        }
        func_8004C8C0(0x1B);
        func_8004C8C0(0x79);
    }
}

extern void func_818047E0(s32 arg0);
void func_81804858(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = *(s32 *)(u32)arg0;
    var_s1 = arg0;
    if (var_s0 != 0) {
        do {
            func_818047E0(var_s0);
            var_s0 = *(s32 *)((u8 *)(u32)var_s1 + 4);
            var_s1 += 4;
        } while (var_s0 != 0);
    }
}

void WidgetDefinitions_Initialize(Fragment4DefinitionView **list, Fragment4StateView *state) {
    s32 i;
    u8 *resource;

    while (*list != NULL) {
        if ((*list)->initialize != NULL) {
            (*list)->initialize(*list, state);
        }
        for (i = 0; i < state->count; i++) {
            resource = func_818054D0(*list, (u8)i);
            if (*(void **)(resource + 32) != NULL) {
                func_81803C9C(*(void **)(resource + 32), state);
            }
        }
        list++;
    }
}

void WidgetState_Initialize(Fragment4StateView *state, s32 controller, s32 count, void *definitions, s32 arg4) {
    state->unk_04 = arg4;
    state->unk_1C = state->unk_1F = 0;
    state->unk_1D = state->unk_1E = 0;
    state->unk_21 = 0;
    state->count = count;
    state->unk_28 = 1.0f;
    state->unk_2C = 1.0f;
    if (controller >= 0 && controller < 4) {
        state->controller = D_800CE060 + controller * 40;
    } else {
        state->controller = NULL;
    }
    state->unk_14 = 0;
    state->unk_16 = 0;
    state->unk_18 = 0;
    state->unk_1A = 0;
    state->definitions = definitions;
    state->progress = 0.0f;
    WidgetDefinitions_Initialize(definitions, state);
}

extern void func_81804858(s32);
void WidgetTree_OpenMessagePanel_fragment4(u8 *arg0) {
    func_81804858(*(s32 *)arg0);
}

s32 func_81804A20(u8 *arg0) {
    return *(u16 *)(arg0 + 0x1A) == 0;
}

s32 WidgetState_AdvanceTransition(Fragment4StateView *state, s32 duration) {
    s32 done = 0;

    state->progress += func_818006B4() / duration;
    switch (state->unk_1A) {
    case 1:
    case 4:
        done = !state->unk_34;
        break;
    case 2:
    case 3:
        done = !state->unk_30;
        break;
    }
    if (done || state->progress >= 1.0f) {
        state->progress = 1.0f;
        return 1;
    }
    return 0;
}

f32 __sinf(f32 arg0, f32 arg1);
extern f32 D_81805F98;
extern f32 D_81805F9C;
f32 func_81804AE8(f32 arg0) {
    if (arg0 <= 0.0f) {
        return 0.0f;
    }
    if (arg0 >= 1.0f) {
        return 1.0f;
    }
    return (__sinf((arg0 * D_81805F98) - D_81805F9C, arg0) * 0.5f) + 0.5f;
}
void func_81804AE8_padding(void) {}

s32 WidgetResources_UseTransitionWeight(void *arg0, void *arg1) {
    if (((Fragment4ResourceView *)arg0)->comparison_key >= 0 &&
        ((Fragment4ResourceView *)arg1)->comparison_key >= 0 &&
        ((Fragment4ResourceView *)arg0)->comparison_key == ((Fragment4ResourceView *)arg1)->comparison_key) {
        return 0;
    }
    if (((Fragment4ResourceView *)arg0)->comparison_key == -2 ||
        ((Fragment4ResourceView *)arg1)->comparison_key == -2) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804BC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804FD0.s")

extern void func_81801420(void);
extern void func_81800A90(void);
extern void func_81600B30(s32);
extern s32 func_81600DA8(void *, void *);
extern s32 func_81801C90(u8 *);
extern void func_818017A8(void);
typedef struct {
    u8 unk_00[8];
    void (*draw)(void *, void *, s16 *);
    void (*bounds)(void *, void *, s16 *);
    u8 unk_10[12];
    void *content;
} Fragment4DrawResourceView;
void WidgetDefinitions_Draw(Fragment4StateView *state) {
    Fragment4DrawResourceView *resource;
    Fragment4DefinitionView **list;
    s32 context;
    s16 rect[4];

    list = state->definitions;
    context = state->unk_04;
    func_81801420();
    if (list != NULL) {
        if (context != 0) {
            func_81600B30(context);
        }
        func_81800A90();
        while (*list != NULL) {
            resource = (Fragment4DrawResourceView *)func_818054D0(*list, state->unk_1F);
            if (resource->draw != NULL) {
                resource->bounds(*list, state, rect);
                if (func_81801C90((u8 *)rect) != 0) {
                    if (resource->content == NULL || rect[3] * rect[2] > 0) {
                        if (context == 0 || func_81600DA8((void *)context, *list) != 0) {
                            func_818017A8();
                            resource->draw(*list, state, rect);
                        }
                    }
                }
            }
            list++;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81805428.s")

extern u8 *func_818054D0(void *arg0, u8 arg1);
extern void func_81801CB8(void *arg0, void *arg1, void *arg2, s32 arg3);
void func_81805474(void *arg0, u8 *arg1, void *arg2) {
    void *first_offset;
    void *first;
    void *second;

    first = func_818054D0(arg0, arg1[0x1C]);
    first_offset = (u8 *)first + 0x10;
    second = func_818054D0(arg0, arg1[0x1D]);
    func_81801CB8(arg2, first_offset, (u8 *)second + 0x10, *(s32 *)(arg1 + 0x2C));
}

u8 *func_818054D0(void *arg0, u8 arg1) {
    struct Entry {
        s16 id;
        s16 unused;
        void *value;
    } *entries = *(struct Entry **)((u8 *)arg0 + 0x30);

    if (entries != NULL) {
        struct Entry *entry = entries;
        s32 value = entry->id;
        s32 needle = arg1;
        while (value >= 0) {
            if (needle == value) {
                return entry->value;
            }
            value = entry[1].id;
            entry++;
        }
    }
    return (u8 *)arg0 + 4;
}

extern s32 func_81804088(void *, u8 *);
s32 func_81805524(void *arg0, u8 *arg1) {
    u8 *entry;
    s32 result;

    entry = func_818054D0(arg0, arg1[0x1F]);
    result = 0;
    if (*(void **)(entry + 0x20) != NULL && *(s32 *)(entry + 0x18) != -2) {
        func_81804088(*(void **)(entry + 0x20), arg1);
        result = 1;
    }
    if (func_81804A20(arg1) == 0) {
        result = 1;
    }
    return result;
}

s32 func_81805594(u8 *arg0, u8 *arg1) { return 1; }

s32 StageContext_GetFadeMode(s32);
s32 func_81805524(void *, u8 *);

s32 func_818055A4(void *arg0, u8 *arg1) {
    s32 var_a0;

    var_a0 = func_81805524(arg0, arg1) != 0;
    if (var_a0 == 0) {
        var_a0 = StageContext_GetFadeMode(var_a0) != 0;
    }
    return var_a0;
}

extern u8 *func_818054D0(void *arg0, u8 arg1);
f32 func_818055E0(void *arg0, u8 *arg1) {
    void *first;
    void *second;
    f32 result;

    first = func_818054D0(arg0, arg1[0x1C]);
    second = func_818054D0(arg0, arg1[0x1D]);
    if (WidgetResources_UseTransitionWeight(first, second) != 0) {
        result = *(f32 *)(arg1 + 0x28);
    } else {
        result = 1.0f;
    }
    return result;
}

extern void func_8180567C(s32, s32, s32);
extern void WidgetResources_DrawRecords(s32, s32, s32);

void func_81805644(s32 arg0, s32 arg1, s32 arg2) {
    WidgetResources_DrawRecords(arg0, arg1, arg2);
    func_8180567C(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_8180567C.s")

extern void func_81802EA0(void *, s32, s32, s32, s32);
extern void func_81801E3C(u8 *, u8 *);
extern void func_800498C4(void);
extern void func_800499EC(void);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_81803558(u8 *, u8 *, f32, s32);
extern void func_81803964(u8 *, u8 *, f32, s32);
void WidgetResources_DrawRecords(s32 arg0, s32 arg1, s32 arg2) {
    Fragment4ResourceView *resource;
    u8 *first;
    u8 *second;
    f32 weight;

    resource = (Fragment4ResourceView *)func_818054D0((void *)arg0, ((Fragment4StateView *)arg1)->unk_1F);
    first = resource->unk_24;
    second = resource->unk_28;
    weight = func_818055E0((void *)arg0, (u8 *)arg1);
    if (resource->unk_1C != NULL) {
        func_81802EA0(resource->unk_1C, ((s16 *)arg2)[0], ((s16 *)arg2)[1], ((s16 *)arg2)[2], ((s16 *)arg2)[3]);
        func_81801E3C((u8 *)arg2, (u8 *)resource->unk_1C + 72);
    }
    if (first != NULL) {
        func_800498C4();
        func_8004972C(255, 255, 255, (s32)(255.0f * weight));
        while (*(s16 *)first >= 0) {
            func_81803558(first, (u8 *)arg2, weight, 0);
            first += 32;
        }
        func_800499EC();
    }
    if (second != NULL) {
        while (*(s16 *)second >= 0) {
            func_81803964(second, (u8 *)arg2, weight, 0);
            second += 32;
        }
    }
}
#endif
