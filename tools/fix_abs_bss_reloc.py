#!/usr/bin/env python3
"""Relocate SHN_ABS symbols that actually live in a fragment's bss.

splat's yaml declares bss_size: 0x0 for the fragments, but the fragment ROM
headers say otherwise (sizeInRam - fileSize; fragment20's real bss is 0x5BC0).
Symbols in that undeclared bss therefore end up outside every section and the
linker emits them as SHN_ABS, so the recompiler drops their relocation and
bakes the link-time literal.

Pokemon Stadium 2 hits this in fragment 0x82600000's init:

    lui $s0, 0x8261   -> RELOC_HI16(65, 0x163E8)   start: relocated
    lui $s1, 0x8262   -> U32(0x8262) << 16         end:   raw literal
    ...
    bne $s0, $s1      -> never equal

The start walks from the fragment's runtime base while the end stays in link
space, so the loop never terminates. It writes s16 -1 every 0x814 bytes, and
because MEM_H masks with RECOMP_MEM_MASK the address wraps and sweeps all of
RDRAM repeatedly - destroying the OS thread/queue block as collateral.

Fix: when a reloc references an SHN_ABS symbol whose value falls inside a
relocatable section's 1 MB fragment slot, attribute it to that section. This is
safe because genuine absolutes (hardware registers at 0xA4xxxxxx, etc.) never
share a slot with a fragment's link address, and only relocatable sections are
considered. 21313 HI16/LO16 relocs across ~60 fragments are affected, so this
also removes the same latent trap everywhere else.
"""
import os
import shutil

P = "/Users/michaegg/ps2-recomp-build/n64recomp-2b/src/elf.cpp"
t = open(P, encoding="utf-8", newline="").read()

OLD = """        else if (rel_symbol_section_index == ELFIO::SHN_ABS) {
            reloc_out.reference_symbol = false;
            reloc_out.target_section = N64Recomp::SectionAbsolute;
            rel_section_vram = 0;
        }"""

NEW = """        else if (rel_symbol_section_index == ELFIO::SHN_ABS) {
            // A fragment's bss can be absent from the linker script (splat
            // yamls that declare bss_size: 0x0 while the fragment header's
            // sizeInRam - fileSize says otherwise). Symbols living there fall
            // outside every section and arrive as SHN_ABS, which would drop
            // the relocation and bake the link-time literal - fatal when the
            // symbol is a loop bound compared against a relocated pointer.
            // If the value sits in a relocatable section's 1 MB fragment slot,
            // relocate against that section instead. Genuine absolutes (RSP/DP
            // hardware registers and the like) never share a slot with a
            // fragment's link address, and non-relocatable sections are left
            // alone.
            size_t abs_owner_section = (size_t)-1;
            uint32_t abs_value = (uint32_t)rel_symbol_value;
            for (size_t abs_i = 0; abs_i < context.sections.size(); abs_i++) {
                const auto& abs_sec = context.sections[abs_i];
                if (!abs_sec.relocatable) {
                    continue;
                }
                uint32_t abs_sec_vram = (uint32_t)abs_sec.ram_addr;
                if (abs_sec_vram == 0) {
                    continue;
                }
                if ((abs_sec_vram & 0xFFF00000u) == (abs_value & 0xFFF00000u) &&
                    abs_value >= abs_sec_vram) {
                    abs_owner_section = abs_i;
                    break;
                }
            }

            reloc_out.reference_symbol = false;
            if (abs_owner_section != (size_t)-1) {
                reloc_out.target_section = (uint16_t)abs_owner_section;
                rel_section_vram = context.sections[abs_owner_section].ram_addr;
            }
            else {
                reloc_out.target_section = N64Recomp::SectionAbsolute;
                rel_section_vram = 0;
            }
        }"""

assert t.count(OLD) == 1, t.count(OLD)
if not os.path.exists(P + ".absbss.orig"):
    shutil.copy2(P, P + ".absbss.orig")
open(P, "w", encoding="utf-8", newline="").write(t.replace(OLD, NEW, 1))
print("OK SHN_ABS fragment-bss relocation added")
