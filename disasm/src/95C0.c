#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D05A0;
extern u8 D_80087320[];
void func_800089C0(void) { Gfx *a,*b,*c,*d,*e,*f,*g,*h,*i,*j,*k,*l,*m,*n; a=D_800D05A0++; a->words.w0=0xE7000000; a->words.w1=0; b=D_800D05A0++; b->words.w0=0xE3000A01; b->words.w1=0; c=D_800D05A0++; c->words.w0=0xE3000C00; c->words.w1=0; d=D_800D05A0++; d->words.w0=0xE3001201; d->words.w1=0; e=D_800D05A0++; e->words.w0=0xFA000000; e->words.w1=0xFFFFFFFF; f=D_800D05A0++; f->words.w0=0xE200001C; f->words.w1=0x0F0A7008; g=D_800D05A0++; g->words.w0=0xFC119623; g->words.w1=0xFF2FFFFF; h=D_800D05A0++; h->words.w0=0xFD700000; h->words.w1=((u32)&D_80087320&0x1FFFFFFF); i=D_800D05A0++; i->words.w0=0xF5700000; i->words.w1=0x07018070; j=D_800D05A0++; j->words.w0=0xE6000000; j->words.w1=0; k=D_800D05A0++; k->words.w0=0xF3000000; k->words.w1=0x0747F156; l=D_800D05A0++; l->words.w0=0xE7000000; l->words.w1=0; m=D_800D05A0++; m->words.w0=0xF5600C00; m->words.w1=0x00018070; n=D_800D05A0++; n->words.w0=0xF2000000; n->words.w1=0x0017C0BC; }

extern Gfx *D_800D05A0;
void func_80008B7C(void) {
    gDPPipeSync(D_800D05A0++);
    gDPSetTexturePersp(D_800D05A0++, G_TP_PERSP);
    gDPSetTextureFilter(D_800D05A0++, G_TF_BILERP);
    gDPSetAlphaCompare(D_800D05A0++, G_AC_NONE);
    gSPTexture(D_800D05A0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
}

void func_80008C18(s16 arg0, s16 arg1, s16 arg2) {
    gSPTextureRectangle(D_800D05A0++, arg0 * 4, arg1 * 4, (arg0 + 6) << 2, (arg1 + 8) << 2, G_TX_RENDERTILE,
                        ((arg2 % 16) * 6) << 5, (u16)(arg2 / 16) << 8, 0x0400, 0x0400);
}

void func_80008D24(s16 arg0, s16 arg1, s16 arg2) {
    gSPTextureRectangle(D_800D05A0++, arg0 * 8, arg1 * 8, (arg0 + 6) << 3, (arg1 + 8) << 3, G_TX_RENDERTILE,
                        ((arg2 % 16) * 6) << 5, (u16)(arg2 / 16) << 8, 0x0200, 0x0200);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/func_80008E30.s")

typedef struct {
    s32 next;
    s16 x;
    s16 y;
    s8 text[1];
} FlushTextQueueNode;
extern void *D_80087310;
extern s32 *D_80087314;
extern Gfx *D_800D05A0;
extern s32 D_80087318;
extern void Util_Free(s32);
extern void func_800089C0(void);
extern void func_80008E30(s16, s16, s8 *, s32);
extern void func_80008B7C(void);
extern void TextRenderer_ClearQueuedStrings(void);
void func_80008F04(Gfx **arg0, s32 arg1) {
    FlushTextQueueNode *var_s0;
    FlushTextQueueNode *var_s2;
    FlushTextQueueNode *temp_s1;
    var_s0 = (FlushTextQueueNode *)D_80087310;
    var_s2 = (FlushTextQueueNode *)D_80087314;
    D_800D05A0 = *arg0;
    if ((var_s0 != NULL) || (var_s2 != NULL)) {
        func_800089C0();
        if (var_s0 != NULL) {
            do {
                temp_s1 = (FlushTextQueueNode *)var_s0->next;
                func_80008E30(var_s0->x, var_s0->y, var_s0->text, arg1);
                Util_Free((s32)var_s0);
                var_s0 = temp_s1;
            } while (temp_s1 != NULL);
        }
        if (var_s2 != NULL) {
            do {
                func_80008E30(var_s2->x, var_s2->y, var_s2->text, arg1);
                var_s2 = (FlushTextQueueNode *)var_s2->next;
            } while (var_s2 != NULL);
        }
        func_80008B7C();
        D_80087310 = NULL;
    }
    *arg0 = D_800D05A0;
    D_80087318 = D_80087318 + 1;
    if (D_80087318 >= 0x384) {
        D_80087318 = 0;
        if (D_80087314 != NULL) {
            TextRenderer_ClearQueuedStrings();
        }
    }
}

extern s32 *D_80087314;
void TextRenderer_ClearQueuedStrings(void) {
    s32 *temp_s1;
    s32 *var_s0;

    var_s0 = D_80087314;
    if (var_s0 != NULL) {
        do {
            temp_s1 = *var_s0;
            Util_Free((s32) var_s0);
            var_s0 = temp_s1;
        } while (temp_s1 != NULL);
    }
    D_80087314 = NULL;
}

extern void *memcpy(void *, const void *, s32); void *TextRenderer_FormatCopy(void *dest, const void *src, s32 size) { return (u8 *)memcpy(dest, src, size) + size; }

#include <stdarg.h>
extern void *Util_Malloc(s32);
extern s32 _Printf();
extern void *D_80087310;
typedef struct {
    s32 next;
    s16 x;
    s16 y;
    u8 text[1];
} TextQueueNode;
s32 func_80009094(s16 arg0, s16 arg1, const char *fmt, ...) {
    s32 result;
    u8 buf[0x104];
    TextQueueNode *node;
    va_list args;

    va_start(args, fmt);
    result = _Printf(TextRenderer_FormatCopy, buf, fmt, args);
    va_end(args);
    if (result > 0) {
        node = Util_Malloc(result + 0xC);
        if (node != NULL) {
            node->x = arg0;
            node->y = arg1;
            memcpy(node->text, buf, result);
            node->text[result] = 0;
            node->next = (s32)D_80087310;
            D_80087310 = node;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/func_80009138.s")
#endif
