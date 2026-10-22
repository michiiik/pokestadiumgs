#include "global.h"


#ifdef VERSION_US
extern u32 D_80128C00;
extern u32 D_80128C30;
extern u32 D_80128C34;
extern u32 D_80128C38;
u32 ParticleGfx_GetFrameDivisor(s32 arg0) {
    u32 ret = D_80128C00;
    switch (arg0) {
        case 2: ret = D_80128C38; break;
        case 3: ret = D_80128C34; break;
        case 4: ret = D_80128C30; break;
    }
    return ret;
}

void func_810001D4(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u32 arg7) {
    u32 temp_v0 = arg7;
    s32 temp_v1 = arg1 + (arg3 * temp_v0);
    s32 temp_a0 = arg2 - (arg4 * temp_v0);
    gDPSetTileSize(gfx, G_TX_RENDERTILE, temp_v1, temp_a0, ((temp_v1 + arg5) - 1) << 2, ((temp_a0 + arg6) - 1) << 2);
}

void func_81000248(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u32 arg7) {
    u32 temp_v0 = arg7;
    s32 temp_v1 = arg1 + (arg3 * temp_v0);
    s32 temp_a0 = arg2 - (arg4 * temp_v0);
    gDPSetTileSize(gfx, 1, temp_v1, temp_a0, ((temp_v1 + arg5) - 1) << 2, ((temp_a0 + arg6) - 1) << 2);
}

Gfx *ParticleGfx_LoadTextureBlock4ToList(Gfx *gfx, u8 *texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt) {
    gDPLoadTextureBlock_4b(gfx++, texture, fmt, width, height, 0, cms, cmt, masks, maskt, shifts, shiftt);
    return gfx;
}

void ParticleGfx_LoadTextureI4ToList(Gfx *gfx, u8 *texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureBlock4ToList(gfx, texture, G_IM_FMT_I, width, height,
        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

u8 func_81000550(u8 firstTime, u8 secondTime, u8 firstValue, u8 secondValue, u8 position) {
    f32 color;
    f32 first;
    f32 current;

    color = firstValue;
    first = firstTime;
    current = position;
    if (current == first) {
        return firstValue;
    }
    return (((f32)secondValue - color) / ((f32)secondTime - first)) * (current - first) + color;
}


typedef struct { u8 pad_00[4]; s16 count; u8 pad_06[2]; s16 *values; } Func810006C4Table;
s16 func_810006C4(Func810006C4Table *arg0, u32 arg1) {
    s32 i;
    for (i = 0; i < arg0->count - 1; i++) {
        if (arg1 >= arg0->values[i] && arg1 < arg0->values[i + 1]) {
            return (s16)i;
        }
    }
    return arg0->count - 2;
}

typedef struct {
    u8 pad[8];
    s16 *times;
    u8 *values;
} ParticleFiveChannelTrack26;

u8 *func_8100072C(u8 *dest, void *settings, u32 frame) {
    ParticleFiveChannelTrack26 *track = (ParticleFiveChannelTrack26 *)settings;
    s16 index;
    u8 position;

    index = func_810006C4((Func810006C4Table *)settings, frame);
    position = (u8)frame;
    dest[0] = func_81000550((u8)track->times[index], (u8)track->times[index + 1],
                           track->values[index * 5 + 0], track->values[index * 5 + 5], position);
    dest[1] = func_81000550((u8)track->times[index], (u8)track->times[index + 1],
                           track->values[index * 5 + 1], track->values[index * 5 + 6], position);
    dest[2] = func_81000550((u8)track->times[index], (u8)track->times[index + 1],
                           track->values[index * 5 + 2], track->values[index * 5 + 7], position);
    dest[3] = func_81000550((u8)track->times[index], (u8)track->times[index + 1],
                           track->values[index * 5 + 3], track->values[index * 5 + 8], position);
    dest[4] = func_81000550((u8)track->times[index], (u8)track->times[index + 1],
                           track->values[index * 5 + 4], track->values[index * 5 + 9], position);
    return dest;
}

typedef struct {
    u8 pad[8];
    s16 *times;
    u8 padC[4];
    u8 *colors;
} ParticleColorTrack26;

u8 *func_81000894(u8 *dest, void *settings, u32 frame) {
    ParticleColorTrack26 *track;
    s16 index;
    u8 position;

    track = (ParticleColorTrack26 *)settings;
    index = func_810006C4((Func810006C4Table *)settings, frame);
    position = (u8)frame;
    dest[0] = func_81000550((u8)track->times[index], (u8)track->times[index + 1],
                           track->colors[index * 4 + 0], track->colors[index * 4 + 4], position);
    dest[1] = func_81000550((u8)track->times[index], (u8)track->times[index + 1],
                           track->colors[index * 4 + 1], track->colors[index * 4 + 5], position);
    dest[2] = func_81000550((u8)track->times[index], (u8)track->times[index + 1],
                           track->colors[index * 4 + 2], track->colors[index * 4 + 6], position);
    dest[3] = func_81000550((u8)track->times[index], (u8)track->times[index + 1],
                           track->colors[index * 4 + 3], track->colors[index * 4 + 7], position);
    return dest;
}

u8 func_810009C0(s32 count, u8 *times, u8 *values, u8 frame) {
    f32 coefficients[50];
    s32 i;
    s32 j;
    f32 product;
    f32 total;
    f32 time;
    f32 value;

    for (i = 0; i < count; i++) {
        time = (f32)(u32)times[i];
        value = (f32)(u32)values[i];
        product = 1;
        for (j = 0; j < count; j++) {
            if (j != i) {
                product *= time - (f32)(u32)times[j];
            }
        }
        coefficients[i] = value / product;
    }
    total = 0;
    for (i = 0; i < count; i++) {
        product = 1;
        for (j = 0; j < count; j++) {
            if (j != i) {
                product *= (f32)(u32)frame - (f32)(u32)times[j];
            }
        }
        total += coefficients[i] * product;
    }
    if (total > 255.0f) {
        total = 255.0f;
    }
    if (total < 0.0f) {
        total = 0.0f;
    }
    return (u8)(u32)total;
}

typedef struct {
    u8 pad[4];
    s16 count;
    u8 pad6[2];
    s16 *times;
    u8 *values;
} ParticleSplineFive26;
extern void *Util_Malloc(s32);
extern void Util_Free(void *);

u8 *func_81000E54(u8 *dest, ParticleSplineFive26 *settings, u32 frame) {
    u8 *times;
    s32 i;
    u8 *timesCursor;
    u8 *channel0;
    u8 *channel1;
    u8 *channel2;
    u8 *channel3;
    u8 *channel4;
    u8 *channel0Cursor;
    u8 *channel1Cursor;
    u8 *channel2Cursor;
    u8 *channel3Cursor;
    u8 *channel4Cursor;

    times = Util_Malloc(settings->count * 4);
    timesCursor = times;
    channel0 = Util_Malloc(settings->count * 4);
    channel0Cursor = channel0;
    channel1 = Util_Malloc(settings->count * 4);
    channel1Cursor = channel1;
    channel2 = Util_Malloc(settings->count * 4);
    channel2Cursor = channel2;
    channel3 = Util_Malloc(settings->count * 4);
    channel3Cursor = channel3;
    channel4 = Util_Malloc(settings->count * 4);
    channel4Cursor = channel4;
    for (i = 0; i < settings->count; i++) {
        *timesCursor++ = settings->times[i];
        *channel0Cursor++ = settings->values[i * 5 + 0];
        *channel1Cursor++ = settings->values[i * 5 + 1];
        *channel2Cursor++ = settings->values[i * 5 + 2];
        *channel3Cursor++ = settings->values[i * 5 + 3];
        *channel4Cursor++ = settings->values[i * 5 + 4];
    }
    dest[0] = func_810009C0(settings->count, times, channel0, (u8)frame);
    dest[1] = func_810009C0(settings->count, times, channel1, (u8)frame);
    dest[2] = func_810009C0(settings->count, times, channel2, (u8)frame);
    dest[3] = func_810009C0(settings->count, times, channel3, (u8)frame);
    dest[4] = func_810009C0(settings->count, times, channel4, (u8)frame);
    Util_Free(times);
    Util_Free(channel0);
    Util_Free(channel1);
    Util_Free(channel2);
    Util_Free(channel3);
    Util_Free(channel4);
    return dest;
}

typedef struct {
    u8 pad[4];
    s16 count;
    u8 pad6[2];
    s16 *times;
    u8 padC[4];
    u8 *values;
} ParticleSplineColors26;

u8 *func_8100107C(u8 *dest, ParticleSplineColors26 *settings, u32 frame) {
    u8 *times;
    s32 i;
    u8 *timesCursor;
    u8 *red;
    u8 *green;
    u8 *blue;
    u8 *alpha;
    u8 *redCursor;
    u8 *greenCursor;
    u8 *blueCursor;
    u8 *alphaCursor;

    times = Util_Malloc(settings->count);
    timesCursor = times;
    red = Util_Malloc(settings->count);
    redCursor = red;
    green = Util_Malloc(settings->count);
    greenCursor = green;
    blue = Util_Malloc(settings->count);
    blueCursor = blue;
    alpha = Util_Malloc(settings->count);
    alphaCursor = alpha;
    for (i = 0; i < settings->count; i++) {
        *timesCursor++ = settings->times[i];
        *redCursor++ = settings->values[i * 4 + 0];
        *greenCursor++ = settings->values[i * 4 + 1];
        *blueCursor++ = settings->values[i * 4 + 2];
        *alphaCursor++ = settings->values[i * 4 + 3];
    }
    dest[0] = func_810009C0(settings->count, times, red, (u8)frame);
    dest[1] = func_810009C0(settings->count, times, green, (u8)frame);
    dest[2] = func_810009C0(settings->count, times, blue, (u8)frame);
    dest[3] = func_810009C0(settings->count, times, alpha, (u8)frame);
    Util_Free(times);
    Util_Free(red);
    Util_Free(green);
    Util_Free(blue);
    Util_Free(alpha);
    return dest;
}

typedef struct {
    u8 format;
    u8 size;
    u8 cms;
    u8 cmt;
    u8 masks;
    u8 maskt;
    u8 shifts;
    u8 shiftt;
    s16 width;
    s16 height;
} ParticleTextureTile26;

Gfx *func_8100124C(Gfx *gfx, void *texture, u32 metadata, s32 tmem, s32 tile) {
    ParticleTextureTile26 *settings = (ParticleTextureTile26 *)metadata;

    switch (settings->format) {
        case G_IM_FMT_RGBA:
            switch (settings->size) {
                case G_IM_SIZ_32b:
                    if (tmem == 0x100) {
                        tmem = 0x80;
                    }
                    gDPLoadMultiTile(gfx++, texture, tmem, tile, settings->format, G_IM_SIZ_32b,
                                     settings->width, settings->height, 0, 0,
                                     settings->width - 1, settings->height - 1, 0,
                                     settings->cms, settings->cmt, settings->masks, settings->maskt,
                                     settings->shifts, settings->shiftt);
                    break;
                case G_IM_SIZ_16b:
                    gDPLoadMultiTile(gfx++, texture, tmem, tile, settings->format, G_IM_SIZ_16b,
                                     settings->width, settings->height, 0, 0,
                                     settings->width - 1, settings->height - 1, 0,
                                     settings->cms, settings->cmt, settings->masks, settings->maskt,
                                     settings->shifts, settings->shiftt);
                    break;
            }
            break;
        case G_IM_FMT_IA:
            switch (settings->size) {
                case G_IM_SIZ_8b:
                    gDPLoadMultiTile(gfx++, texture, tmem, tile, G_IM_FMT_IA, G_IM_SIZ_8b,
                                     settings->width, settings->height, 0, 0,
                                     settings->width - 1, settings->height - 1, 0,
                                     settings->cms, settings->cmt, settings->masks, settings->maskt,
                                     settings->shifts, settings->shiftt);
                    break;
                case G_IM_SIZ_16b:
                    gDPLoadMultiTile(gfx++, texture, tmem, tile, G_IM_FMT_IA, G_IM_SIZ_16b,
                                     settings->width, settings->height, 0, 0,
                                     settings->width - 1, settings->height - 1, 0,
                                     settings->cms, settings->cmt, settings->masks, settings->maskt,
                                     settings->shifts, settings->shiftt);
                    break;
            }
            break;
        case G_IM_FMT_I:
            switch (settings->size) {
                case G_IM_SIZ_4b:
                    gDPLoadMultiTile_4b(gfx++, texture, tmem, tile, G_IM_FMT_I,
                                        settings->width, settings->height, 0, 0,
                                        settings->width - 1, settings->height - 1, 0,
                                        settings->cms, settings->cmt, settings->masks, settings->maskt,
                                        settings->shifts, settings->shiftt);
                    break;
                case G_IM_SIZ_8b:
                    gDPLoadMultiTile(gfx++, texture, tmem, tile, G_IM_FMT_I, G_IM_SIZ_8b,
                                     settings->width, settings->height, 0, 0,
                                     settings->width - 1, settings->height - 1, 0,
                                     settings->cms, settings->cmt, settings->masks, settings->maskt,
                                     settings->shifts, settings->shiftt);
                    break;
            }
            break;
    }
    return gfx;
}

typedef struct {
    u32 count;
    void **textures;
} ParticleTextureSequence26;
typedef struct {
    s16 values[6];
} ParticleTileSettings26;
typedef struct {
    s16 unused;
    s16 mode;
    ParticleTileSettings26 *tile;
    u32 unused8;
    ParticleTextureSequence26 *sequence;
} ParticleTextureAnimation26;
typedef struct {
    void *texture;
    u32 unused4;
    u32 format;
} ParticleTextureBase26;
typedef struct {
    ParticleTextureBase26 *base;
    ParticleTextureAnimation26 *animation;
} ParticleTextureSettings26;

Gfx *func_81001F14(Gfx *gfx, ParticleTextureSettings26 *settings, s32 format, s32 tile, u32 frame) {
    void *texture = 0;
    ParticleTextureAnimation26 *animation;
    u32 index;

    animation = settings->animation;
    if ((animation != 0) && (animation->sequence != 0)) {
        if (animation->mode == 1) {
            if (frame >= animation->sequence->count) {
                index = animation->sequence->count - 1;
            } else {
                index = frame % animation->sequence->count;
            }
        } else {
            index = frame % animation->sequence->count;
        }
        texture = animation->sequence->textures[index];
    } else if ((settings->base != 0) && (settings->base->texture != 0)) {
        texture = settings->base->texture;
    }
    if (texture != 0) {
        gfx = func_8100124C(gfx, texture, settings->base->format, format, tile);
        animation = settings->animation;
    }
    if ((animation != 0) && (animation->tile != 0)) {
        switch (tile) {
            case 0:
                func_810001D4(gfx++, animation->tile->values[0], animation->tile->values[1],
                              animation->tile->values[2], animation->tile->values[3],
                              animation->tile->values[4], animation->tile->values[5], frame);
                break;
            case 1:
                func_81000248(gfx++, animation->tile->values[0], animation->tile->values[1],
                              animation->tile->values[2], animation->tile->values[3],
                              animation->tile->values[4], animation->tile->values[5], frame);
                break;
        }
    }
    return gfx;
}

typedef struct {
    u8 pad[0x1A];
    s16 kind;
    u8 pad1C;
    u8 opacity;
} ParticleCombineContext26;
typedef struct { unsigned char pad_00[0x1C]; u8 unk_1C; } Func810033DCGlobalG2;
extern Func810033DCGlobalG2 *D_8009491C;
typedef struct {
    u8 colorA0;
    u8 colorB0;
    u8 colorC0;
    u8 colorD0;
    u8 alphaA0;
    u8 alphaB0;
    u8 alphaC0;
    u8 alphaD0;
    u8 colorA1;
    u8 colorB1;
    u8 colorC1;
    u8 colorD1;
    u8 alphaA1;
    u8 alphaB1;
    u8 alphaC1;
    u8 alphaD1;
} ParticleCombineFields26;

void func_810020E0(Gfx *gfx, ParticleCombineFields26 *values, s32 mode, u8 selector) {
    ParticleCombineContext26 *context;

    gfx->words.w0 = ((((values->colorA0 & 15) << 20) | ((values->colorC0 & 31) << 15) |
                      ((values->alphaA0 & 7) << 12) | ((values->alphaC0 & 7) << 9) |
                      ((values->colorA1 & 15) << 5) | (values->colorC1 & 31)) & 0xFFFFFF) | 0xFC000000;
    if (mode == 1) {
        context = (ParticleCombineContext26 *)D_8009491C;
        if (context->kind == 0xDB && selector == 4) {
            gfx->words.w1 = _SHIFTL(values->colorB0, 28, 4) | _SHIFTL(values->colorD0, 15, 3) |
                            _SHIFTL(values->alphaB0, 12, 3) | _SHIFTL(values->alphaD0, 9, 3) |
                            _SHIFTL(values->colorB1, 24, 4) | _SHIFTL(values->alphaA1, 21, 3) |
                            _SHIFTL(values->alphaC1, 18, 3) | _SHIFTL(values->colorD1, 6, 3) |
                            _SHIFTL(values->alphaB1, 3, 3) | _SHIFTL(values->alphaD1, 0, 3);
            return;
        }
        if (context->opacity == 0xFF) {
            gfx->words.w1 = _SHIFTL(values->colorB0, 28, 4) | _SHIFTL(values->colorD0, 15, 3) |
                            _SHIFTL(values->alphaB0, 12, 3) | _SHIFTL(values->alphaD0, 9, 3) |
                            _SHIFTL(values->colorB1, 24, 4) | _SHIFTL(7, 21, 3) | _SHIFTL(7, 18, 3) |
                            _SHIFTL(values->colorD1, 6, 3) | _SHIFTL(7, 3, 3) | _SHIFTL(0, 0, 3);
            return;
        }
        gfx->words.w1 = _SHIFTL(values->colorB0, 28, 4) | _SHIFTL(values->colorD0, 15, 3) |
                        _SHIFTL(values->alphaB0, 12, 3) | _SHIFTL(values->alphaD0, 9, 3) |
                        _SHIFTL(values->colorB1, 24, 4) | _SHIFTL(0, 21, 3) | _SHIFTL(6, 18, 3) |
                        _SHIFTL(values->colorD1, 6, 3) | _SHIFTL(7, 3, 3) | _SHIFTL(7, 0, 3);
        return;
    }
    gfx->words.w1 = _SHIFTL(values->colorB0, 28, 4) | _SHIFTL(values->colorD0, 15, 3) |
                    _SHIFTL(values->alphaB0, 12, 3) | _SHIFTL(values->alphaD0, 9, 3) |
                    _SHIFTL(values->colorB1, 24, 4) | _SHIFTL(values->alphaA1, 21, 3) |
                    _SHIFTL(values->alphaC1, 18, 3) | _SHIFTL(values->colorD1, 6, 3) |
                    _SHIFTL(values->alphaB1, 3, 3) | _SHIFTL(values->alphaD1, 0, 3);
}

typedef struct { s16 first; s16 second; } Func810023ACRangeA;
typedef struct { u8 pad[0x44]; void *flag; s32 value; } Func810023ACContextA;
typedef struct { u8 pad[0x7F]; u8 value; } Func810023ACInputA;
extern s32 func_84100054(u8 *, s32);
s32 func_810023AC(Func810023ACRangeA *arg0, u8 *arg1, Func810023ACContextA *arg2) {
    s32 result = 0;
    Func810023ACRangeA *range = *(Func810023ACRangeA **)((u8 *)arg0 + 4);
    if (range != NULL) {
        s16 denominator = range->second;
        s16 selector = range->first;
        if (denominator == 0) {
            if (arg1 != NULL && func_84100054(arg1, 0x100) != 0) {
                result = ((Func810023ACInputA *)arg1)->value / selector;
            } else {
                result = ParticleGfx_GetFrameDivisor(selector);
            }
        } else if (arg2 != NULL && arg2->flag != NULL) {
            result = (arg2->value >> 16) / selector;
        } else if (arg1 != NULL) {
            result = ((Func810023ACInputA *)arg1)->value / selector;
        }
    }
    return result;
}

typedef struct { u8 r; u8 g; u8 b; u8 a; } DispatchEnv26;

typedef struct { u8 r; u8 g; u8 b; u8 a; u8 lod; } DispatchPrim26;
typedef struct { ParticleCombineFields26 *combine; DispatchPrim26 *prim; DispatchEnv26 *env; } DispatchColor26;
typedef struct { s16 type; s16 count; s16 keys; s16 pad; s16 *times; DispatchPrim26 *prim; DispatchEnv26 *env; } DispatchTrack26;
typedef struct { s16 selector; s16 mode; void *tile; DispatchTrack26 *track; void *sequence; } DispatchAnimation26;
typedef struct { u32 geometry; u16 s; u16 t; } DispatchGeometry26;
typedef struct { ParticleTextureBase26 *base; DispatchAnimation26 *animation; DispatchColor26 *color; DispatchGeometry26 *geometry; } DispatchLayer26;
typedef struct { DispatchLayer26 *primary; DispatchLayer26 *secondary; } DispatchLayers26;
typedef struct { u8 pad[0x14]; u8 *object; u8 pad18[2]; s16 kind; u8 pad1C; u8 opacity; } DispatchContext26;

typedef struct { u8 pad[0x84]; u8 pr; u8 pg; u8 pb; u8 pa; u8 pad88[3]; u8 er; u8 eg; u8 eb; u8 ea; } DispatchObject26;


s32 func_810024E0(s32 address, void *layerData, s32 mode, u8 *explicitObject, u8 selector) {
    DispatchContext26 *context;
    Gfx *gfx;
    DispatchObject26 *object;
    DispatchLayer26 *secondary;
    u32 frame;
    DispatchLayer26 *primary;
    u8 alpha;

    context = NULL;
    primary = ((DispatchLayers26 *)layerData)->primary;
    secondary = ((DispatchLayers26 *)layerData)->secondary;
    gfx = (Gfx *)address;
    object = NULL;
    frame = 0;
    if (explicitObject == NULL) { context = (DispatchContext26 *)D_8009491C; }
    if (mode == 0) {
        if (explicitObject != NULL) { object = (DispatchObject26 *)explicitObject; }
        else { object = (DispatchObject26 *)context->object; }
    }
    if (primary != NULL) {
        if (primary->color != NULL) {
            address = (s32)primary->color->combine; /* Reuse the incoming carrier to preserve call scheduling. */
            func_810020E0(gfx++, (ParticleCombineFields26 *)address, mode, selector);
            if (primary->animation == NULL || primary->animation->track == NULL) {
                if (primary->color->prim != NULL) {
                    gDPPipeSync(gfx++);
                    if (mode == 2) {
                        gDPSetPrimColor(gfx++, 0, primary->color->prim->lod, primary->color->prim->r, primary->color->prim->g, primary->color->prim->b, primary->color->prim->a);
                    } else if (mode == 1) {
                        gDPSetPrimColor(gfx++, 0, context->opacity, primary->color->prim->r, primary->color->prim->g, primary->color->prim->b, primary->color->prim->a);
                    } else if (object == NULL) {
                        if (context->opacity < 255) {
                            gDPSetPrimColor(gfx++, 0, primary->color->prim->lod, primary->color->prim->r, primary->color->prim->g, primary->color->prim->b, context->opacity);
                        } else {
                            gDPSetPrimColor(gfx++, 0, primary->color->prim->lod, primary->color->prim->r, primary->color->prim->g, primary->color->prim->b, primary->color->prim->a);
                        }
                    } else if (func_84100054((u8 *)object, 4)) {
                        if (func_84100054((u8 *)object, 0x10)) {
                            gDPSetPrimColor(gfx++, 0, primary->color->prim->lod, object->pr, object->pg, object->pb, object->pa);
                        } else {
                            gDPSetPrimColor(gfx++, 0, primary->color->prim->lod, object->pr, object->pg, object->pb, primary->color->prim->a);
                        }
                    } else if (func_84100054((u8 *)object, 0x10)) {
                        gDPSetPrimColor(gfx++, 0, primary->color->prim->lod, primary->color->prim->r, primary->color->prim->g, primary->color->prim->b, object->pa);
                    } else {
                        gDPSetPrimColor(gfx++, 0, primary->color->prim->lod, primary->color->prim->r, primary->color->prim->g, primary->color->prim->b, primary->color->prim->a);
                    }
                }
                if (primary->color->env != NULL) {
                    if (object == NULL) {
                        gDPSetEnvColor(gfx++, primary->color->env->r, primary->color->env->g, primary->color->env->b, primary->color->env->a);
                    } else if (func_84100054((u8 *)object, 8)) {
                        if (func_84100054((u8 *)object, 0x20)) {
                            gDPSetEnvColor(gfx++, object->er, object->eg, object->eb, object->ea);
                        } else {
                            gDPSetEnvColor(gfx++, object->er, object->eg, object->eb, primary->color->env->a);
                        }
                    } else if (func_84100054((u8 *)object, 0x20)) {
                        gDPSetEnvColor(gfx++, primary->color->env->r, primary->color->env->g, primary->color->env->b, object->ea);
                    } else {
                        gDPSetEnvColor(gfx++, primary->color->env->r, primary->color->env->g, primary->color->env->b, primary->color->env->a);
                    }
                }
            }
        }
        if (primary->geometry != NULL) {
            gSPSetGeometryMode(gfx++, primary->geometry->geometry);
            gSPTexture(gfx++, primary->geometry->s, primary->geometry->t, 0, 0, G_ON);
        }
        if (primary->animation != NULL) {
            DispatchTrack26 *track;
            s32 type;
            u32 index;
            u8 primBuffer[5];
            DispatchPrim26 *prim;
            frame = func_810023AC((Func810023ACRangeA *)primary, (u8 *)object, (Func810023ACContextA *)context);
            if (primary->animation->track != NULL) {
                track = primary->animation->track;
                type = track->type;
                if (primary->animation->mode == 1) {
                    if (frame >= track->count) { index = track->count - 1; }
                    else { index = frame % track->count; }
                } else { index = frame % track->count; }
                if (track->prim != NULL) {
                    if (type == 0) { prim = &track->prim[index]; }
                    else if (track->type == 1) { prim = (DispatchPrim26 *)func_8100072C(primBuffer, track, index); }
                    else if (track->type == 2) { prim = (DispatchPrim26 *)func_81000E54(primBuffer, (ParticleSplineFive26 *)track, index); }
                    gDPPipeSync(gfx++);
                    if (mode == 2) {
                        gDPSetPrimColor(gfx++, 0, prim->lod, prim->r, prim->g, prim->b, prim->a);
                    } else if (mode == 1) {
                        if (context->kind == 0xDB) {
                            alpha = (context->opacity * prim->a) / 255;
                            gDPSetPrimColor(gfx++, 0, alpha, prim->r, prim->g, prim->b, alpha);
                        } else {
                            gDPSetPrimColor(gfx++, 0, context->opacity, prim->r, prim->g, prim->b, prim->a);
                        }
                    } else if (object == NULL) {
                        if (context->opacity < 255) {
                            gDPSetPrimColor(gfx++, 0, prim->lod, prim->r, prim->g, prim->b, context->opacity);
                        } else {
                            gDPSetPrimColor(gfx++, 0, prim->lod, prim->r, prim->g, prim->b, prim->a);
                        }
                    } else if (func_84100054((u8 *)object, 4)) {
                        if (func_84100054((u8 *)object, 0x10)) {
                            gDPSetPrimColor(gfx++, 0, prim->lod, object->pr, object->pg, object->pb, object->pa);
                        } else {
                            gDPSetPrimColor(gfx++, 0, prim->lod, object->pr, object->pg, object->pb, prim->a);
                        }
                    } else if (func_84100054((u8 *)object, 0x10)) {
                        if (func_84100054((u8 *)object, 0x40)) {
                            alpha = (object->pa * prim->a) / 255;
                            gDPSetPrimColor(gfx++, 0, prim->lod, prim->r, prim->g, prim->b, alpha);
                        } else {
                            gDPSetPrimColor(gfx++, 0, prim->lod, prim->r, prim->g, prim->b, object->pa);
                        }
                    } else {
                        gDPSetPrimColor(gfx++, 0, prim->lod, prim->r, prim->g, prim->b, prim->a);
                    }
                }
                if (track->env != NULL) {
                    u8 envBuffer[4];
                    DispatchEnv26 *env;
                    if (type == 0) { env = &track->env[index]; }
                    else if (track->type == 1) { env = (DispatchEnv26 *)func_81000894(envBuffer, track, index); }
                    else if (track->type == 2) { env = (DispatchEnv26 *)func_8100107C(envBuffer, (ParticleSplineColors26 *)track, index); }
                    if (object == NULL) {
                        gDPSetEnvColor(gfx++, env->r, env->g, env->b, env->a);
                    } else if (func_84100054((u8 *)object, 8)) {
                        if (func_84100054((u8 *)object, 0x20)) {
                            gDPSetEnvColor(gfx++, object->er, object->eg, object->eb, object->ea);
                        } else {
                            gDPSetEnvColor(gfx++, object->er, object->eg, object->eb, env->a);
                        }
                    } else if (func_84100054((u8 *)object, 0x20)) {
                        if (func_84100054((u8 *)object, 0x40)) {
                            alpha = (object->ea * env->a) / 255;
                            gDPSetEnvColor(gfx++, env->r, env->g, env->b, alpha);
                        } else {
                            gDPSetEnvColor(gfx++, env->r, env->g, env->b, object->ea);
                        }
                    } else {
                        gDPSetEnvColor(gfx++, env->r, env->g, env->b, env->a);
                    }
                }
            }
        }
        if (primary->base != NULL) {
            if (primary->base->texture != NULL && primary->geometry == NULL) {
                gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, 0, G_ON);
            }
            if (primary->base->unused4 == 0) { gDPSetTextureLUT(gfx++, G_TT_NONE); }
            else { gDPSetTextureLUT(gfx++, G_TT_RGBA16); }
        }
        gfx = func_81001F14(gfx, (ParticleTextureSettings26 *)((DispatchLayers26 *)layerData)->primary, 0, 0, frame);
    }
    if (secondary != NULL) {
        s32 tmem;
        tmem = 0;
        frame = func_810023AC((Func810023ACRangeA *)secondary, (u8 *)object, (Func810023ACContextA *)context);
        if (((DispatchLayer26 **)layerData)[0]->base->texture != ((DispatchLayer26 **)layerData)[1]->base->texture) { tmem = 0x100; }
        gfx = func_81001F14(gfx, (ParticleTextureSettings26 *)((DispatchLayers26 *)layerData)->secondary, tmem, 1, frame);
    }
    return (s32)gfx;
}

typedef struct {
    unsigned char pad_00[3];
    u8 unk_03;
    unsigned char pad_04[0x10];
    void *unk_14;
} Func8100338CStateK;
extern s32 D_800D0510;
void func_8100338C(s32 arg0, Func8100338CStateK *state) {
    if (arg0 == 5) {
        D_800D0510 = func_810024E0(D_800D0510, state->unk_14, 0, 0, state->unk_03);
    }
}

typedef struct { unsigned char pad_00[3]; u8 unk_03; unsigned char pad_04[0x10]; void *unk_14; } Func810033DCStateG2;
extern Func810033DCGlobalG2 *D_8009491C;
void func_810033DC(s32 arg0, Func810033DCStateG2 *state) {
    if (arg0 == 5) {
        Func810033DCGlobalG2 *global = D_8009491C;
        Func810033DCStateG2 *temp = state;
        void *value = temp->unk_14;
        if (global->unk_1C == 0) {
            D_800D0510 = func_810024E0(D_800D0510, value, 1, 0, temp->unk_03);
        }
    }
}

typedef struct {
    unsigned char pad_00[3];
    u8 unk_03;
    unsigned char pad_04[0x10];
    void *unk_14;
} Func8100343CState;
void func_8100343C(s32 arg0, Func8100343CState *state) {
    if (arg0 == 5) {
        D_800D0510 = func_810024E0(D_800D0510, state->unk_14, 2, 0, state->unk_03);
    }
}

void func_8100348C(s32 arg0, s32 arg1) {
    s32 value = 0;
    D_800D0510 = func_810024E0(D_800D0510, arg1, 0, arg0, value);
}

typedef struct {
    unsigned char pad_00[3];
    u8 unk_03;
    unsigned char pad_04[0x10];
    void *unk_14;
} Func810034C0StateD;
void func_810034C0(s32 arg0, Func810034C0StateD *state) {
    if (arg0 == 5) {
        D_800D0510 = func_810024E0(D_800D0510, state->unk_14, 4, 0, state->unk_03);
    }
}

void func_81003510(s32 arg0) {
    // FAKE: uopt deletes a lone `if (arg0 == 5) {}`; the mixed signed/unsigned
    // literal spellings split the compares into two CSE classes (s32 singleton +
    // u32 pair) so the surviving branch reaches as1 as a pseudo `bne a0, 5`,
    // which it expands to `li at, 5; bne a0, at`.
    if (arg0 == 5 && arg0 == 5U && arg0 == 5U) {

    }
}
void func_81003524(s32 arg0, s32 arg1) { if (arg0 == 5) { arg1 = arg1; } }

typedef union { s16 packed; struct { s8 red, green, blue; u8 alpha; } color; } ParticleVertexTail26;
typedef struct { s16 xyz[3]; u16 flag; s16 uv[2]; ParticleVertexTail26 tail; } ParticleVertex26;
typedef struct { u8 pad[0x20]; void *vertices; u8 pad24[2]; s16 count; } ParticleMeshCopy26;
typedef struct { u8 pad[0x87]; u8 opacity; } ParticleOpacityCopy26;
typedef struct { u8 pad[0x14]; ParticleOpacityCopy26 *object; } ParticleMeshContextCopy26;
typedef struct { s16 pad; s16 count; ParticleVertex26 *source; ParticleOpacityCopy26 *object; } ParticleCopyShort26;
extern ParticleMeshCopy26 *D_80094920;
extern void *Gfx_AllocDisplayList(s32);
void func_8100352C(s32 event, void *node)
{
  s32 i;
  ParticleVertex26 *src;
  ParticleVertex26 *dst;
  if (event == 5)
  {
    ParticleCopyShort26 locals;
    ParticleVertex26 *allocated;
    src = (ParticleVertex26 *)D_8009491C;
    locals.object = ((ParticleMeshContextCopy26 *)src)->object;
    locals.source = (ParticleVertex26 *)D_80094920->vertices;
    locals.count = D_80094920->count;
    allocated = (ParticleVertex26 *)Gfx_AllocDisplayList(locals.count * 16);
    i = 0;
    if (locals.count > 0)
    {
      src = locals.source;
      dst = allocated;
      copy_vertex:
      dst->xyz[0] = src->xyz[0];
      dst->xyz[1] = src->xyz[1];
      dst->xyz[2] = src->xyz[2];
      dst->flag = src->flag;
      dst->uv[0] = src->uv[0];
      dst->uv[1] = src->uv[1];
      dst->tail.packed = src->tail.packed;
      dst->tail.color.red = src->tail.color.red;
      dst->tail.color.green = src->tail.color.green;
      dst->tail.color.blue = src->tail.color.blue;
      dst->tail.color.alpha = (src->tail.color.alpha * locals.object->opacity) / 255;
      i++;
      src++;
      dst++;
      if (i < locals.count)
      {
        goto copy_vertex;
      }
    }
    /* Keep the allocation result live here for the original IDO register
     * reservation. This side-effect-free check emits no instructions. */
    if (allocated != NULL) { }
    gSPSegment((*((Gfx **)(&D_800D0510)))++, 15, osVirtualToPhysical(allocated));
  }
}

typedef struct { s16 mode; s16 period; } ParticleSettings26;
typedef struct { u8 pad[0x14]; ParticleSettings26 *settings; u8 color[3]; u8 pad1b; s16 x; s16 y; } ParticleNode26;
typedef struct { u8 pad[0x1e]; s16 x; s16 y; } ParticleCoords26;
void func_81003680(s32 event, ParticleNode26 *node) {
    u8 frame_padding[12]; /* Preserve the original 0x38-byte frame. */
    ParticleCoords26 *global;
    ParticleSettings26 *settings;
    u8 *color;
    u8 buffer[4];

    if (event == 2) {
        global = (ParticleCoords26 *)D_8009491C;
        settings = node->settings;
        event = ParticleGfx_GetFrameDivisor(1) % settings->period;
        if (settings->mode == 0) {
            node->x = global->x - 0x1800;
            node->y = global->y - 0x2000;
        } else {
            node->x = global->x - 0x1800;
            node->y = global->y + 0x2000;
        }
        color = func_81000894(buffer, settings, (u32)event);
        node->color[0] = color[0];
        node->color[1] = color[1];
        node->color[2] = color[2];
    }
}

void func_81003750(u8 *arg0, s32 arg1) {}

void func_8100375C(u8 *arg0, s32 arg1) {}

extern f32 D_80128C58;
extern u8 D_80128C5C[4];
extern void *Vec3f_SetComponentsDuplicate(void *, f32, f32, f32);
extern void func_8003F498(s32, s32, s32, s32, u8);
s32 func_81003768(s32 event, u8 *node) {
    if (event == 2) {
        Vec3f_SetComponentsDuplicate(node + 0x30, D_80128C58, D_80128C58, D_80128C58);
        func_8003F498((s32)node, D_80128C5C[0], D_80128C5C[1], D_80128C5C[2], D_80128C5C[3]);
    }
    return 0;
}
#endif
