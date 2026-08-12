#!/usr/bin/env python3
"""Use a fragment's real in-RAM extent when testing overlap for eviction.

load_overlays evicts any loaded section whose runtime range overlaps a newly
loaded one, resetting its section_addresses to the link literal. It measured the
old section with the ELF section size, which includes the trailing relocation
table -- the game does not keep that in RAM.

Fragment 38 (link 0x81600000): ELF size 0xD770, header sizeInRam 0xC300. Its
real extent is 0x8014B7B0..0x80157AB0. Fragment 41 loads at 0x80157AC0, a
16-byte gap above it, so nothing overlaps. Measured with 0xD770 it appears to
overlap by 0x1460 and fragment 38 gets unregistered while still live. Code in
fragment 41 then reads a function pointer through RELOC_HI16(38, 0xBD08); with
section_addresses[38] back at the link literal that resolves to 0x8160BD08,
which the 1 GB address mask maps past the 8 MB of real RDRAM, so it reads 0 and
the game calls a NULL pointer.

The header's sizeInRam (+0x1C) is what the game itself uses for the RAM
footprint, and it is right in both directions: smaller than the ELF size when a
reloc table is present (fragment 38), larger when the fragment has bss
(fragment 41: 0x8D70 -> 0x20B30). Read it from the loaded image and fall back to
the section size when the FRAGMENT magic is absent.
"""
import os
import shutil

P = "/Users/michaegg/psr-recomp-build/work/lib/N64ModernRuntime/librecomp/src/overlays.cpp"
t = open(P, encoding="utf-8", newline="").read()
nl = "\r\n" if "\r\n" in t else "\n"


def fit(s):
    return s.replace("\n", nl)


assert "loaded_fragment_extent" not in t, "already applied"

# Helper, placed just before the lambda that uses it.
anchor = fit("        const SectionTableEntry& new_section = sections_info.code_sections[section_index];")
assert t.count(anchor) == 1, t.count(anchor)

helper_anchor = fit("static void unload_overlay_by_section_index(uint32_t section_table_index);")
assert t.count(helper_anchor) == 1, t.count(helper_anchor)

helper = fit('''
// A fragment's ROM image ends with its relocation table, which is not kept in
// RAM, so the ELF section size overstates the loaded footprint; conversely a
// fragment with bss occupies more than its image. The header's sizeInRam
// (+0x1C) is the figure the game itself uses, and overlap tests must use it or
// they evict live fragments (and, with bss, miss real collisions).
static uint32_t loaded_fragment_extent(int32_t loaded_ram_addr, uint32_t section_size) {
    uint8_t* rd = recomp_runtime_get_rdram();
    if (rd == nullptr) {
        return section_size;
    }
    const uint32_t paddr = (uint32_t)loaded_ram_addr & 0x1FFFFFFFu;
    if (paddr + 0x20u > 0x800000u) {
        return section_size;
    }
    auto rd_be32 = [&](uint32_t off) -> uint32_t {
        return ((uint32_t)rd[(paddr + off + 0) ^ 3] << 24) |
               ((uint32_t)rd[(paddr + off + 1) ^ 3] << 16) |
               ((uint32_t)rd[(paddr + off + 2) ^ 3] << 8)  |
                (uint32_t)rd[(paddr + off + 3) ^ 3];
    };
    if (rd_be32(0x08) != 0x46524147u || rd_be32(0x0C) != 0x4D454E54u) {
        return section_size;  // no FRAGMENT magic: trust the section table
    }
    const uint32_t size_in_ram = rd_be32(0x1C);
    if (size_in_ram == 0 || size_in_ram > 0x800000u) {
        return section_size;
    }
    return size_in_ram;
}

''')
t = t.replace(helper_anchor, helper + helper_anchor, 1)

old_cmp = fit("""                if (!runtime_ranges_overlap(implied_base, new_section.size,
                                            loaded.loaded_ram_addr, old_section.size)) {
                    continue;
                }""")
assert t.count(old_cmp) == 1, t.count(old_cmp)
new_cmp = fit("""                const uint32_t old_extent =
                    loaded_fragment_extent(loaded.loaded_ram_addr, old_section.size);
                if (!runtime_ranges_overlap(implied_base, new_section.size,
                                            loaded.loaded_ram_addr, old_extent)) {
                    continue;
                }""")
t = t.replace(old_cmp, new_cmp, 1)

if not os.path.exists(P + ".evictextent.orig"):
    shutil.copy2(P, P + ".evictextent.orig")
open(P, "w", encoding="utf-8", newline="").write(t)
print("OK eviction now uses the fragment's real in-RAM extent")
