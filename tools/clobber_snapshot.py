#!/usr/bin/env python3
"""Snapshot RDRAM at the instant the 0x800CDA10 tripwire fires.

The periodic dump is 2 s granular, which is long enough for the corrupting
write to be buried. Dumping from the tripwire itself captures the queue block
as soon as it stops looking like a queue, so the bytes can be matched against
the ROM the same way the audio-microcode corruption was identified.
"""
import os
import shutil

MAIN = "/Users/michaegg/ps2-recomp-build/runtime/src/main/main.cpp"
MESG = "/Users/michaegg/psr-recomp-build/work/lib/N64ModernRuntime/ultramodern/src/mesgqueue.cpp"


def nl_of(t):
    return "\r\n" if "\r\n" in t else "\n"


def fit(s, nl):
    return s.replace("\n", nl)


# ---- main.cpp: exported snapshot writer ---------------------------------
m = open(MAIN, encoding="utf-8", newline="").read()
mnl = nl_of(m)
assert "psr_dump_rdram_snapshot" not in m, "already applied"

anchor = fit("namespace psr_freeze_state {", mnl)
assert m.count(anchor) == 1

writer = fit('''// Called from the message-queue tripwire the moment the watched OSMesgQueue
// stops looking like a queue, so the corrupting write is captured before
// anything else runs. Diagnostic; remove with the other freeze instrumentation.
extern "C" void psr_dump_rdram_snapshot(const char* name) {
    static std::atomic<bool> done{false};
    bool expected = false;
    if (!done.compare_exchange_strong(expected, true)) {
        return;
    }
    uint8_t* snap = recomp_runtime_get_rdram();
    if (snap == nullptr) {
        return;
    }
    const auto path = pkmnstadium::exe_dir() / name;
    FILE* f = std::fopen(path.string().c_str(), "wb");
    if (f == nullptr) {
        return;
    }
    constexpr uint32_t kRdramSize = 0x800000u;
    constexpr uint32_t kChunk = 0x10000u;
    std::vector<uint8_t> buf(kChunk);
    for (uint32_t base = 0; base < kRdramSize; base += kChunk) {
        for (uint32_t i = 0; i < kChunk; i++) {
            buf[i] = snap[(base + i) ^ 3];
        }
        std::fwrite(buf.data(), 1, kChunk, f);
    }
    std::fclose(f);
    std::fprintf(stderr, "[clobber] RDRAM snapshot written to %s\\n", name);
    std::fflush(stderr);
}

''', mnl)

m = m.replace(anchor, writer + anchor, 1)
if not os.path.exists(MAIN + ".clobbersnap.orig"):
    shutil.copy2(MAIN, MAIN + ".clobbersnap.orig")
open(MAIN, "w", encoding="utf-8", newline="").write(m)
print("main.cpp: snapshot writer added")

# ---- mesgqueue.cpp: call it from the tripwire ---------------------------
q = open(MESG, encoding="utf-8", newline="").read()
qnl = nl_of(q)
assert "psr_dump_rdram_snapshot" not in q, "tripwire already calls it"

decl_anchor = fit('extern "C" void recomp_ultra_trace_record(const char* name, uint32_t pc, uint32_t a0,', qnl)
assert q.count(decl_anchor) == 1
q = q.replace(decl_anchor,
              fit('extern "C" void psr_dump_rdram_snapshot(const char* name);\n', qnl) + decl_anchor, 1)

call_anchor = fit('        recomp_ultra_trace_record("~ps2_mq_clobber", 0,', qnl)
assert q.count(call_anchor) == 1
q = q.replace(call_anchor,
              fit('        psr_dump_rdram_snapshot("rdram_clobber.bin");\n', qnl) + call_anchor, 1)

if not os.path.exists(MESG + ".clobbersnap.orig"):
    shutil.copy2(MESG, MESG + ".clobbersnap.orig")
open(MESG, "w", encoding="utf-8", newline="").write(q)
print("mesgqueue.cpp: tripwire now snapshots RDRAM")
