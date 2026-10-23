#include "global.h"


#ifdef VERSION_US
typedef struct { f32 x, y, z; } GeometryVec3;
extern GeometryVec3 *func_80035A10(GeometryVec3 *);

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26E4C0/func_86207A80.s")

void Geometry_ComputeLineProjection(f32 *point, f32 *start, f32 *end, f32 *distance, f32 *parameter, GeometryVec3 *closest) {
    f32 px;
    f32 py;
    f32 pz;
    f32 qz;
    f32 qx;
    f32 qy;
    f32 dz;
    f32 dx;
    f32 dy;
    f32 point_distance;
    px = start[0] - point[0];
    py = start[1] - point[1];
    pz = start[2] - point[2];
    qx = end[0] - point[0];
    qy = end[1] - point[1];
    qz = end[2] - point[2];
    dz = qz - pz;
    dx = qx - px;
    dy = qy - py;
    if (qx == px && dy == 0 && dz == 0) {
        *distance = 0;
        *parameter = 0;
        closest->x = 0;
        closest->y = 0;
        closest->z = 0;
    } else {
        *parameter = -((px * dx + py * dy) + pz * dz) / ((dx * dx + dy * dy) + dz * dz);
        closest->x = *parameter * dx + px;
        closest->y = *parameter * dy + py;
        closest->z = *parameter * dz + pz;
        point_distance = sqrtf((closest->x * closest->x +
                                closest->y * closest->y) +
                               closest->z * closest->z);
        *distance = point_distance;
    }
}

s32 Geometry_TestSphereContact(f32 *first, f32 radius, f32 *second, GeometryVec3 *normal, f32 *depth) {
    s32 result;
    f32 distance;
    result = 0;
    normal->x = first[0] - second[0];
    normal->y = first[1] - second[1];
    normal->z = first[2] - second[2];
    if ((normal->x > 0.0f ? normal->x : -normal->x) <= radius && (normal->y > 0.0f ? normal->y : -normal->y) <= radius && (normal->z > 0.0f ? normal->z : -normal->z) <= radius) {
        distance = sqrtf((normal->x * normal->x + normal->y * normal->y) + normal->z * normal->z);
        if (distance <= radius) {
            if (normal->x == 0.0f && normal->y == 0.0f && normal->z == 0.0f) {
                normal->x = 1.0f;
            } else {
                func_80035A10(normal);
            }
            *depth = radius - distance;
            result = 1;
        }
    }
    return result;
}

f32 Geometry_ComputePlaneParameter(f32 *plane, f32 *point, f32 *direction) {
    f32 denominator;
    denominator = plane[2] * direction[2] +
                  (plane[1] * direction[1] + direction[0] * plane[0]);
    return denominator == 0 ? 0.0f :
           -(plane[3] + (plane[2] * point[2] +
                         (plane[1] * point[1] + point[0] * plane[0]))) / denominator;
}

s32 Geometry_TestSegmentContact(f32 *point, f32 radius, f32 *start, f32 *end, GeometryVec3 *normal, f32 *depth) {
    f32 distance;
    f32 parameter;
    s32 result;
    Geometry_ComputeLineProjection(point, start, end, &distance, &parameter, normal);
    if (distance < radius && parameter >= 0 && parameter <= 1) {
        result = 1;
        func_80035A10(normal);
        normal->x *= -1.0f;
        normal->y *= -1.0f;
        normal->z *= -1.0f;
        *depth = radius - distance;
    } else {
        result = 0;
    }
    return result;
}
#endif
