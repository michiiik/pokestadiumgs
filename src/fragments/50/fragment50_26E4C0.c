#include "global.h"


#ifdef VERSION_US
typedef struct { f32 x, y, z; } GeometryVec3;
extern GeometryVec3 *func_80035A10(GeometryVec3 *);
extern void func_86207BC0(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26E4C0/func_86207A80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26E4C0/func_86207BC0.s")

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
    func_86207BC0(point, start, end, &distance, &parameter, (f32 *)normal);
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
