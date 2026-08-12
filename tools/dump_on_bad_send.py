#!/usr/bin/env python3
"""Dump the trace ring and RDRAM the first time do_send rejects a queue.

do_send already detects the damage ("[do_send] BAD mq_=..."). The periodic
2 s dump is too coarse — the last one landed ~18 s while the corruption
happened later — so capture at the detection point instead. The trace ring
holds the most recent 16384 libultra events, which covers the window in which
the corrupting guest code ran.
"""
import os
import shutil

MAIN = "/Users/michaegg/ps2-recomp-build/runtime/src/main/main.cpp"
MESG = "/Users/michaegg/psr-recomp-build/work/lib/N64ModernRuntime/ultramodern/src/mesgqueue.cpp"


def nl_of(t):
    return "\r\n" if "\r\n" in t else "\n"


def fit(s, nl):
    return s.replace("\n", nl)


# ---- main.cpp: trace dumper -------------------------------------------
m = open(MAIN, encoding="utf-8", newline="").read()
mnl = nl_of(m)
assert "psr_dump_trace_snapshot" not in m, "already applied"

anchor = fit('extern "C" void psr_dump_rdram_snapshot(const char* name) {', mnl)
assert m.count(anchor) == 1

dumper = fit('''extern "C" void psr_dump_trace_snapshot(const char* name) {
    static std::atomic<bool> done{false};
    bool expected = false;
    if (!done.compare_exchange_strong(expected, true)) {
        return;
    }
    const auto path = pkmnstadium::exe_dir() / name;
    FILE* f = std::fopen(path.string().c_str(), "w");
    if (f == nullptr) {
        return;
    }
    const uint64_t write_idx = recomp_ultra_trace_write_idx();
    const uint32_t capacity = recomp_ultra_trace_capacity();
    const uint64_t count = std::min<uint64_t>(write_idx, capacity);
    const uint64_t start = write_idx - count;
    std::fprintf(f, "write_idx=%llu capacity=%u start=%llu\\n",
            static_cast<unsigned long long>(write_idx), capacity,
            static_cast<unsigned long long>(start));
    for (uint64_t index = start; index < write_idx; ++index) {
        recomp_ultra_trace_event event{};
        if (!recomp_ultra_trace_get(index, &event)) continue;
        std::fprintf(f,
                "%llu %llu tid=%u thread=%08X %-39s pc=%08X "
                "a0=%08X a1=%08X a2=%08X a3=%08X\\n",
                static_cast<unsigned long long>(event.seq),
                static_cast<unsigned long long>(event.ms),
                event.thread_id, event.thread, event.name, event.pc,
                event.a0, event.a1, event.a2, event.a3);
    }
    std::fclose(f);
    std::fprintf(stderr, "[clobber] trace snapshot written to %s\\n", name);
    std::fflush(stderr);
}

''', mnl)

m = m.replace(anchor, dumper + anchor, 1)
if not os.path.exists(MAIN + ".tracesnap.orig"):
    shutil.copy2(MAIN, MAIN + ".tracesnap.orig")
open(MAIN, "w", encoding="utf-8", newline="").write(m)
print("main.cpp: trace snapshot writer added")

# ---- mesgqueue.cpp: call both from the do_send failure path ------------
q = open(MESG, encoding="utf-8", newline="").read()
qnl = nl_of(q)
assert "psr_dump_trace_snapshot" not in q, "already hooked"

decl = fit('extern "C" void psr_dump_rdram_snapshot(const char* name);', qnl)
assert q.count(decl) == 1
q = q.replace(decl, decl + fit('\nextern "C" void psr_dump_trace_snapshot(const char* name);', qnl), 1)

# The failure reporter: find the "[do_send] BAD mq_" fprintf and dump there.
marker = "[do_send] BAD mq_=0x%08X"
idx = q.find(marker)
assert idx != -1, "do_send failure message not found"
line_start = q.rfind("fprintf", 0, idx)
assert line_start != -1
q = (q[:line_start]
     + fit('psr_dump_trace_snapshot("trace_clobber.log");\n        ', qnl)
     + fit('psr_dump_rdram_snapshot("rdram_clobber.bin");\n        ', qnl)
     + q[line_start:])

if not os.path.exists(MESG + ".tracesnap.orig"):
    shutil.copy2(MESG, MESG + ".tracesnap.orig")
open(MESG, "w", encoding="utf-8", newline="").write(q)
print("mesgqueue.cpp: do_send failure now snapshots trace + RDRAM")
