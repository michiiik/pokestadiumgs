#!/usr/bin/env python3
"""Capture memory and section bases at the lookup-miss abort.

The battle abort is a call through a NULL function pointer loaded from
section 38 + 0xBD08. The ROM holds a real pointer table there
(81600020 816000D4 8160006C ...), so the slot is only zero if
section_addresses[38] does not point at the fragment's actual data.

The periodic 2 s RDRAM dump is useless for this - the snapshot pulled after the
last crash predated the fragment loads entirely (none of the bound bases even
contained a FRAGMENT header). Capture at the abort instead, and print the
section base table so the bad binding is visible without guesswork.
"""
import os
import shutil

P = "/Users/michaegg/psr-recomp-build/work/lib/N64ModernRuntime/librecomp/src/overlays.cpp"
t = open(P, encoding="utf-8", newline="").read()
nl = "\r\n" if "\r\n" in t else "\n"


def fit(s):
    return s.replace("\n", nl)


assert "psr_lookup_abort_dump" not in t, "already applied"

anchor = fit('    FILE* f = open_last_error_log("a");')
# That call appears several times; take the one at the lookup-miss abort.
marker = "lookup-miss trampoline reached"
mi = t.find(marker)
assert mi != -1, "abort site not found"
ai = t.find(anchor, mi)
assert ai != -1, "no open_last_error_log after the abort site"

dump = fit('''    // Diagnostic: capture RDRAM and the section base table at the abort. The
    // periodic dump runs on its own timer and has already proved too stale to
    // interpret (its snapshot predated the fragment loads under investigation).
    {
        extern "C" void psr_dump_rdram_snapshot(const char* name);
        extern "C" void psr_dump_trace_snapshot(const char* name);
        static bool psr_lookup_abort_dump = false;
        if (!psr_lookup_abort_dump) {
            psr_lookup_abort_dump = true;
            FILE* sf = open_last_error_log("a");
            if (sf != nullptr) {
                fprintf(sf, "\\n=== section bases at abort ===\\n");
                if (sections_info.code_sections != nullptr && section_addresses != nullptr) {
                    for (size_t si = 0; si < sections_info.num_code_sections; si++) {
                        const SectionTableEntry& se = sections_info.code_sections[si];
                        uint32_t base = (uint32_t)section_addresses[se.index];
                        // Only the relocatable fragments can be mis-bound.
                        if (se.relocs == nullptr || se.num_relocs == 0) continue;
                        if (base == (uint32_t)se.ram_addr) continue;  // not loaded
                        fprintf(sf, "  section %zu index=%u link=0x%08X size=0x%X base=0x%08X\\n",
                                si, (unsigned)se.index, (uint32_t)se.ram_addr,
                                (unsigned)se.size, base);
                    }
                }
                fclose(sf);
            }
            psr_dump_trace_snapshot("trace_abort.log");
            psr_dump_rdram_snapshot("rdram_abort.bin");
        }
    }

''')

t = t[:ai] + dump + t[ai:]
if not os.path.exists(P + ".abortdump.orig"):
    shutil.copy2(P, P + ".abortdump.orig")
open(P, "w", encoding="utf-8", newline="").write(t)
print("OK abort-time RDRAM + section-base capture installed")
