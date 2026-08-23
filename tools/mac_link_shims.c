#include "recomp.h"

/* __osSiRelAccess_recomp used to need a shim here (the shared pi.cpp didn't
 * implement it), but the current N64ModernRuntime copy's pi.cpp defines it
 * for real now — a duplicate-symbol link error is the signal this shim is
 * stale. Removed rather than kept as a second, weaker no-op definition. */

void static_5_80021834(uint8_t* rdram, recomp_context* ctx) {
    (void)rdram;
    (void)ctx;
}
