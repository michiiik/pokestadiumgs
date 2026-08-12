#!/usr/bin/env python3
"""Write-protect a never-used RDRAM page so the sweeping writer faults on it.

The corruption is a single global writer: 0xFFFF halfwords at 90 fixed phases
of a repeating 0x814-byte period, across the whole 8 MB. Every damaged word in
the OS block sits on that same phase set, and the pattern is absent from
boot-time snapshots. Because it also covers memory the game never touches,
0x80400000 is a safe tripwire: nothing legitimate writes there, so the first
fault is the writer, and the tombstone names the function.

Armed 12 s after start so boot is finished. PROT_READ only — the fault is a
clean SEGV_ACCERR whose backtrace is the answer.
"""
import os
import shutil

M = "/Users/michaegg/ps2-recomp-build/runtime/src/main/main.cpp"
t = open(M, encoding="utf-8", newline="").read()
nl = "\r\n" if "\r\n" in t else "\n"


def fit(s):
    return s.replace("\n", nl)


assert "psr_arm_rdram_watchpage" not in t, "already applied"

anchor = fit('extern "C" void psr_dump_trace_snapshot(const char* name) {')
assert t.count(anchor) == 1

watch = fit('''#include <sys/mman.h>

// Write-protect one never-used RDRAM page to catch the global 0xFFFF sweep.
// Guest code that legitimately writes here does not exist (the page is far
// above the heap and stays zero in boot snapshots), so any fault is the
// corrupting writer and the tombstone backtrace identifies it.
extern "C" void psr_arm_rdram_watchpage(void) {
    uint8_t* base = recomp_runtime_get_rdram();
    if (base == nullptr) {
        return;
    }
    // 0x80400000 -> rdram + 0x400000. Page-align defensively.
    uint8_t* page = base + 0x400000u;
    const uintptr_t aligned = (uintptr_t)page & ~(uintptr_t)0xFFF;
    if (mprotect((void*)aligned, 0x1000, PROT_READ) != 0) {
        std::fprintf(stderr, "[watchpage] mprotect failed: %s\\n", std::strerror(errno));
    } else {
        std::fprintf(stderr, "[watchpage] 0x80400000 is now read-only; "
                             "the next writer there will fault\\n");
    }
    std::fflush(stderr);
}

''')

t = t.replace(anchor, watch + anchor, 1)

# Arm it from the periodic dump thread on the first round.
arm_anchor = fit('      for (int dump_round = 0; dump_round < 14; dump_round++) {')
assert t.count(arm_anchor) == 1, t.count(arm_anchor)
t = t.replace(arm_anchor,
              arm_anchor + fit('\n        if (dump_round == 4) { psr_arm_rdram_watchpage(); }'), 1)

if not os.path.exists(M + ".watchpage.orig"):
    shutil.copy2(M, M + ".watchpage.orig")
open(M, "w", encoding="utf-8", newline="").write(t)
print("OK RDRAM watchpage armed (0x80400000, read-only, ~12s after start)")
