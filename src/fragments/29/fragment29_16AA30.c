#include "global.h"


#ifdef VERSION_US
void PointerList_SwapRange(void** arg0, void** arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < arg2; i++) {
        void* tmp = *arg0;
        *arg0++ = *arg1;
        *arg1++ = tmp;
    }
}

s32* Sort_SelectMedianPointer(s32* arg0, s32* arg1, s32* arg2, s32 (*arg3)(s32, s32)) {
    return (arg3(*arg0, *arg1) < 0)   ? (arg3(*arg1, *arg2) < 0)   ? arg1
                                        : (arg3(*arg0, *arg2) < 0) ? arg2
                                                                   : arg0
           : (arg3(*arg1, *arg2) > 0) ? arg1
           : (arg3(*arg0, *arg2) > 0) ? arg2
                                      : arg0;
}

// Quicksort of n pointers at base with comparator cmp, in the BSD qsort shape: insertion sort
// below 7 elements, median-of-3 pivot (ninther above 40) via Sort_SelectMedianPointer, a
// three-way partition, PointerList_SwapRange to move the equal runs to the middle, then
// recursion on both parts (the compiled code turns the second call into a jump back to the
// top). Same body as Pokemon Stadium 1 Sort_QuickSort (src/table_view.c there).
void func_88004B60(void** base, s32 n, s32 (*cmp)(s32, s32)) {
    void** sp8C;
    s32 temp_s2;
    void* temp_s4;
    s32 temp_s4_2;
    void* temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_6;
    s32 var_a2_2;
    s32 var_v0;
    void** var_a2;
    void** var_s0;
    void** var_s0_2;
    void** var_s1;
    void** var_s1_2;
    void** var_s2;
    void** var_s2_2;
    void** var_s3;
    void** var_s6;

    if (n < 7) {
        for (var_s1 = base; var_s1 < base + n; var_s1++) {
            var_s0 = var_s1;
            if ((base < var_s1) && (cmp(*(var_s1 - 1), *var_s1) > 0)) {
                while (1) {
                    temp_v0 = *var_s0;
                    *(var_s0) = *(var_s0 - 1);
                    *(var_s0 - 1) = temp_v0;
                    var_s0--;
                    if (base < var_s0) {
                        if (cmp(*(var_s0 - 1), *var_s0) > 0) {
                            continue;
                        }
                    }
                    break;
                }
            }
        }
        return;
    }

    sp8C = base + (n / 2);
    if (n >= 8) {
        var_s2 = base;
        var_a2 = (base + n) - 1;
        if (n > 40) {
            temp_v0_2 = n / 8;
            var_s2 = (void**)Sort_SelectMedianPointer((s32*)base, (s32*)(base + temp_v0_2), (s32*)(base + temp_v0_2 * 2), cmp);
            sp8C = (void**)Sort_SelectMedianPointer((s32*)(sp8C - temp_v0_2), (s32*)sp8C, (s32*)(sp8C + temp_v0_2), cmp);
            var_a2 = (void**)Sort_SelectMedianPointer((s32*)(var_a2 - temp_v0_2 * 2), (s32*)(var_a2 - temp_v0_2), (s32*)var_a2, cmp);
        }
        sp8C = (void**)Sort_SelectMedianPointer((s32*)var_s2, (s32*)sp8C, (s32*)var_a2, cmp);
    }

    temp_s4 = *sp8C;
    var_s0_2 = (base + n) - 1;
    var_s2_2 = base;
    var_s1_2 = base;
    var_s3 = (base + n) - 1;

    while (1) {
        if (var_s0_2 >= var_s1_2) {
            var_v0 = cmp(*var_s1_2, temp_s4);
            while (var_v0 <= 0) {
                if (var_v0 == 0) {
                    temp_v0 = *var_s2_2;
                    *var_s2_2 = *var_s1_2;
                    *var_s1_2 = temp_v0;
                    var_s2_2++;
                }
                var_s1_2++;
                if (var_s0_2 < var_s1_2) {
                    break;
                }
                var_v0 = cmp(*var_s1_2, temp_s4);
            }
        }
        if (var_s0_2 >= var_s1_2) {
            var_v0 = cmp(*var_s0_2, temp_s4);
            while (var_v0 >= 0) {
                if (var_v0 == 0) {
                    temp_v0 = *var_s0_2;
                    *var_s0_2 = *var_s3;
                    *var_s3 = temp_v0;
                    var_s3 -= 1;
                }
                var_s0_2 -= 1;
                if (var_s0_2 < var_s1_2) {
                    break;
                }
                var_v0 = cmp(*var_s0_2, temp_s4);
            }
        }
        if (var_s0_2 < var_s1_2) {
            break;
        }
        temp_v0 = *var_s1_2;
        *var_s1_2 = *var_s0_2;
        *var_s0_2 = temp_v0;
        var_s1_2++;
        var_s0_2--;
    }
    temp_s4_2 = (s32)(var_s1_2 - var_s2_2);
    temp_v0_6 = (s32)(var_s2_2 - base);
    if (temp_v0_6 < temp_s4_2) {
        var_a2_2 = temp_v0_6;
    } else {
        var_a2_2 = temp_s4_2;
    }
    var_s6 = base + n;
    PointerList_SwapRange(base, var_s1_2 - var_a2_2, var_a2_2);
    temp_s2 = (s32)(var_s3 - var_s0_2);
    temp_v0_6 = ((s32)(var_s6 - var_s3)) - 1;
    if (temp_s2 < temp_v0_6) {
        var_a2_2 = temp_s2;
    } else {
        var_a2_2 = temp_v0_6;
    }
    PointerList_SwapRange(var_s1_2, var_s6 - var_a2_2, var_a2_2);
    if (temp_s4_2 >= 2) {
        func_88004B60(base, temp_s4_2, cmp);
    }
    if (temp_s2 >= 2) {
        func_88004B60(var_s6 - temp_s2, temp_s2, cmp);
    }
}
#endif
