#include "global.h"


#ifdef VERSION_US
typedef struct { u8 pad0[4]; s16 mode; u8 pad6[2]; s32 status; u8 padC[4]; u16 x; u16 alt; s16 out; } Fragment29Node;
typedef struct { u8 pad0[8]; u16 flags; } Fragment29Input;

typedef struct {
    s32 enabled;
    u8 *flags;
} F29TextMask;

typedef struct {
    u8 reserved[8];
    s16 x, y;
    u16 width, height;
    s32 anchor;
} F29Rect;

typedef struct {
    s16 x, y;
    s32 align;
    u8 **strings;
    u16 count, width;
    s32 font;
    s16 spacingX, spacingY, left, right, top, bottom;
    s32 constrain;
} F29TextLayout;

extern s32 func_88002958(u8 **, u16, s32, s16);
extern void func_88003480(s32, u16, u16, s16 *, s16 *);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_80049064(s32, s32, s32, const char *);
extern s32 func_80049290(s32, s32, const char *);

extern u8 D_8800ED40; extern u8 D_8800ED41;
void func_880022F0(void) { D_8800ED40 = 10; D_8800ED41 = 1; }

extern Fragment29Input *D_80087200;
extern void func_800226C0(s32);
s16 func_8800230C(Fragment29Node *node) {
    s16 selected = 0;
    s16 enabled = *(s16 *)((u8 *)node + 0x18);

    if ((enabled & 0x200) && (D_80087200->flags & 0x200)) {
        selected = 0x200;
    } else if ((enabled & 0x100) && (D_80087200->flags & 0x100)) {
        selected = 0x100;
    } else if ((enabled & 0x20) && (D_80087200->flags & 0x20)) {
        selected = 0x20;
    } else if ((enabled & 0x10) && (D_80087200->flags & 0x10)) {
        selected = 0x10;
    }
    if (selected != 0) {
        func_880022F0();
        func_800226C0(*(s32 *)((u8 *)node + 0x1C));
    } else if (node->alt != 0) {
        (*(s8 *)&D_8800ED40)--;
        if (*(s8 *)&D_8800ED40 <= 0) {
            D_8800ED40 = 0;
            if ((enabled & 0x200) && (*(u16 *)((u8 *)D_80087200 + 6) & 0x200)) {
                selected = 0x200;
            } else if ((enabled & 0x100) && (*(u16 *)((u8 *)D_80087200 + 6) & 0x100)) {
                selected = 0x100;
            } else if ((enabled & 0x20) && (*(u16 *)((u8 *)D_80087200 + 6) & 0x20)) {
                selected = 0x20;
            } else if ((enabled & 0x10) && (*(u16 *)((u8 *)D_80087200 + 6) & 0x10)) {
                selected = 0x10;
            }
            if (selected != 0) {
                D_8800ED40 = 1;
                (*(s8 *)&D_8800ED41)--;
                if (*(s8 *)&D_8800ED41 <= 0) {
                    D_8800ED41 = *(s8 *)((u8 *)node + 0x1A);
                    func_800226C0(*(s32 *)((u8 *)node + 0x1C));
                }
            }
        }
    }
    return selected;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880024FC.s")

void func_8800254C(Fragment29Node *node) {
    s32 changed;

    if (node->mode != 0) {
        changed = 0;
        *(s16 *)((u8 *)node + 0x16) += node->out;
        if (*(s16 *)((u8 *)node + 0x16) < 0) {
            *(s16 *)((u8 *)node + 0x16) += *(u16 *)((u8 *)node + 0xE);
            if (node->status == 0 || *(s16 *)((u8 *)node + 0x16) == 0) {
                --**(s8 **)node;
                if (**(s8 **)node < 0) {
                    **(s8 **)node = *(u8 *)((u8 *)node + 0xC) - 1;
                }
            }
            changed = 1;
        } else if (*(s16 *)((u8 *)node + 0x16) >= *(u16 *)((u8 *)node + 0xE)) {
            *(s16 *)((u8 *)node + 0x16) -= *(u16 *)((u8 *)node + 0xE);
            ++**(s8 **)node;
            if (**(s8 **)node >= *(u8 *)((u8 *)node + 0xC)) {
                **(s8 **)node = 0;
            }
            changed = 1;
        }
        if (changed && node->status) {
            *(s16 *)((u8 *)node + 0x16) = 0;
            node->out = 0;
            node->status = 0;
            node->mode = 0;
        }
    }
}

void func_88002640(Fragment29Node *arg0) {
    s16 mode;
    s16 current;

    if (arg0->status != 0) goto done;
    mode = func_8800230C(arg0);
    current = arg0->mode;
    if (mode == current) goto done;
    if (current != 0) goto set_status;
    arg0->mode = mode;
    if (mode == 0x10) goto positive;
    if (mode == 0x20) goto negative;
    if (mode == 0x100) goto positive;
    if (mode != 0x200) goto done;
negative:
    if (D_80087200->flags & 0x220) arg0->out = -arg0->x;
    else arg0->out = -arg0->alt;
    goto done;
positive:
    if (D_80087200->flags & 0x110) arg0->out = arg0->x;
    else arg0->out = arg0->alt;
    goto done;
set_status:
    arg0->status = 1;
done:
    func_8800254C(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002720.s")

extern s32 func_800472B8(s32);
void func_88002820(s16 x, s16 y, s8 style, u8 **text, u16 count,
                   s16 spacing, F29TextMask *mask) {
    s32 row;
    u8 **cursor;
    s16 step = func_800472B8(0) + spacing;
    row = 0;
    if (count != 0) {
        cursor = text;
        do {
            if (mask->enabled && mask->flags[row]) {
                func_8004972C(255, 255, 255, 100);
            }
            func_80049064(x, y, style, *cursor);
            y += step;
            if (mask->enabled && mask->flags[row]) {
                func_8004972C(255, 255, 255, 255);
            }
            row++;
            cursor++;
        } while (row != count);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002958.s")

extern s32 func_800472E0(u8 *); extern s32 func_800472B8(s32);
s32 func_88002A08(u8 **arg0, u16 arg1, s32 arg2, s16 arg3) {
    s32 temp_s2;
    s32 temp_s3;
    s32 var_s0;
    s32 var_s2;
    u8 **var_s1;
    s32 result;

    temp_s3 = arg1;
    var_s2 = 0;
    var_s0 = 0;
    if (temp_s3 != 0) {
        var_s1 = arg0;
        do {
            temp_s2 = func_800472E0(*var_s1);
            var_s0 += 1;
            var_s2 += temp_s2;
            var_s1 += 1;
            var_s2 &= 0xFFFF;
        } while (var_s0 != temp_s3);
    }
    result = func_800472B8(arg2);
    return (result * var_s2 + (arg3 * (var_s2 - 1))) & 0xFFFF;
}

extern s32 func_8003514C(void);
u8 *func_88002AA8(u8 *node, s32 align, u8 **strings, u16 count,
                  s32 font, s16 spacingX, s16 spacingY, s16 left, s16 right,
                  s16 top, s16 bottom, s32 constrain, s16 selection, void *mask) {
    *(s32 *)(node + 4) = align;
    *(u8 ***)(node + 8) = strings;
    *(u16 *)(node + 12) = count;
    *(s32 *)(node + 16) = font;
    if (func_8003514C() == 0) {
        *(s16 *)(node + 20) = spacingX;
    } else {
        *(s16 *)(node + 20) = 0;
    }
    *(s16 *)(node + 22) = spacingY;
    *(s16 *)(node + 24) = left;
    *(s16 *)(node + 26) = right;
    *(s16 *)(node + 28) = top;
    *(s16 *)(node + 30) = bottom;
    *(s32 *)(node + 32) = constrain;
    *(s32 *)(node + 36) = 1;
    *(s16 *)(node + 40) = selection;
    *(F29TextMask *)(node + 44) = *(F29TextMask *)mask;
    if (*(s32 *)mask) {
again:
        if (*(*(s16 *)(node + 40) + *(u8 **)((u8 *)mask + 4))) {
            ++*(s16 *)(node + 40);
            if (*(s16 *)(node + 40) >= count) {
                *(s16 *)(node + 40) = 0;
            }
            goto again;
        }
    }
    return node;
}

extern Gfx *D_800D0510;
void func_88002BA0(u8 arg0, u8 arg1, u8 arg2) {
    gDPPipeSync(D_800D0510++);
    gDPSetEnvColor(D_800D0510++, arg0, arg1, arg2, 0xFF);
    gDPSetRenderMode(D_800D0510++, 0x0F0A7008, 0);
}

void func_88002C2C(u8 arg0, u8 arg1, u8 arg2) {
    gDPPipeSync(D_800D0510++);
    gDPSetEnvColor(D_800D0510++, arg0, arg1, arg2, 0xFF);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002CB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002EC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880032C4.s")

extern u8 D_8800ED50[];
u8 func_8800335C(void) {
    u8 count = 0;
    s32 i;
    u8 *node = (u8 *)D_8800ED50;

    for (i = 0; i < 6; i++, node += 0x4C) {
        if (*(s32 *)(node + 0x20) == 1 || *(s32 *)(node + 0x20) == 3) {
            count++;
        }
    }
    return count;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003430.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003480.s")

extern s32 func_88002A08(u8 **arg0, u16 arg1, s32 arg2, s16 arg3);
void func_88003534(F29Rect *rect, F29TextLayout *text) {
    s16 excessX, excessY;

    text->width = func_88002958(text->strings, text->count, text->font, text->spacingX);
    rect->width = text->width + text->left + text->right;
    rect->height = func_88002A08(text->strings, text->count, text->font, text->spacingY) + text->top + text->bottom;
    func_88003480(rect->anchor, rect->width, rect->height, &rect->x, &rect->y);
    switch (text->constrain) {
    case 1:
        excessX = rect->x + rect->width - 592;
        if (excessX > 0) {
            rect->x = rect->x - excessX;
        }
        break;
    case 2:
        excessY = rect->y + rect->height - 427;
        if (excessY > 0) {
            rect->y = rect->y - excessY;
        }
        break;
    }
    switch (text->align) {
    case 0:
        text->x = rect->x + text->left;
        break;
    case 1:
        text->x = rect->x + text->left + (text->width >> 1);
        break;
    case 2:
        text->x = rect->x + text->left + text->width - 1;
        break;
    }
    text->y = rect->y + text->top;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880036CC.s")

void func_88003858(F29Rect *rect, u8 *data) {
    u16 headingHeight;
    F29TextLayout *text;

    headingHeight = func_88002A08((u8 **)(data + 8), 1, *(s32 *)(data + 12), *(s16 *)(data + 18));
    text = (F29TextLayout *)(data + 0x1C);
    text->width = func_88002958(text->strings, text->count, text->font, text->spacingX);
    rect->width = (func_80049290(*(s32 *)(data + 12), *(s16 *)(data + 16), *(u8 **)(data + 8)) < text->width + 8
                       ? text->width + 8
                       : func_80049290(*(s32 *)(data + 12), *(s16 *)(data + 16), *(u8 **)(data + 8))) + 25;
    rect->height = func_88002A08(text->strings, text->count, text->font, text->spacingY) + headingHeight + 43;
    func_88003480(rect->anchor, rect->width, rect->height, &rect->x, &rect->y);
    *(s16 *)data = rect->x + 11;
    *(s16 *)(data + 2) = rect->y + 11;
    switch (text->align) {
    case 0:
        text->x = rect->x + 15;
        break;
    case 1:
        text->x = rect->x + (text->width >> 1) + 15;
        break;
    case 2:
        text->x = rect->x + text->width + 14;
        break;
    }
    text->y = rect->y + headingHeight + 27;
    *(s16 *)(data + 0x14) = *(s16 *)data;
    *(s16 *)(data + 0x16) = text->y - 10;
    *(s16 *)(data + 0x18) = rect->width - 25;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003A00.s")

extern void func_88003A00();
extern s8 D_8800EF18;
void func_88003FBC(void *arg0) {
    s8 var_v0;

    if ((*(s32 *)((u8 *)(arg0) + (0x1C))) == 3) {
        if ((*(s32 *)((u8 *)(arg0) + (0x14))) == 3) {
            var_v0 = 4;
        } else {
            var_v0 = D_8800EF18;
        }
        if (var_v0 == (*(s8 *)((u8 *)(arg0) + (0x20)))) {
            func_88003A00();
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88004014.s")

extern u8 D_8800ED50[]; extern void func_88003A00(u8 *);
void func_880040D4(void) {
    u8 *entry;
    u32 i;
    s32 state;
    u8 *child;
    void (*callback)(void);

    entry = D_8800ED50;
    i = 0;
    state = 2;
    do {
        child = entry + 4;
        if ((*(s32 *)(entry + 0x20) == state) && (*(s32 *)(child + 0x28) != 0)) {
            callback = (void (*)(void))(u32)*(u32 *)(child + 0x34);
            if (callback != 0) {
                callback();
            }
        }
        i += 1;
        entry += 0x4C;
    } while (i < 6);

    entry = D_8800ED50;
    i = 0;
    do {
        if (*(s32 *)(entry + 0x20) != 0) {
            func_88003A00(entry + 4);
        }
        i += 1;
        entry += 0x4C;
    } while (i != 6);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88004180.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880046EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88004804.s")

extern void func_880046EC(s32, s32, s16, s16, s32, s32, u8, u8, u8,
                          s32 *, s32 *, s32 *, s32 *, u8, u8, void *);

void func_880048D4(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5,
                   u8 arg6, u8 arg7, u8 arg8, s32 *arg9, s32 *arg10,
                   s32 *arg11, s32 *arg12, u8 arg13, u8 arg14, s32 arg15) {
    u8 *entry;

    entry = D_8800ED50 + ((u8)arg15 * 0x4C);
    if (*(s32 *)(entry + 0x20) == 0) {
        func_880046EC(arg0, arg1, arg2, arg3, arg4, arg5,
                       arg6, arg7, arg8, arg9, arg10, arg11, arg12,
                       arg13, arg14, entry);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88004990.s")
#endif
