#!/usr/bin/env python3
"""Dump / validate the Pokemon Stadium 2 (USA) rental+roster blob.

Verified layout (see RENTAL_REVERSE_ENGINEERING.md):

  ROM 0x1708000 -> runtime RAM 0x802492B0, uncompressed, 0xFE90 bytes.

  blob header
    +0x00 u32 0
    +0x04 u32 0
    +0x08 u32 total_size      (0xFE90)
    +0x0C u32 ntables         (72)
  directory at +0x10, ntables entries of 0x10 bytes:
    +0x00 u32 offset          (relative to blob base)
    +0x04 u32 size            (offset + size == next table's offset; contiguous)
    +0x08 u32 0
    +0x0C u32 0
  each table
    u8 count, 3 pad bytes, then count * 0x18-byte records

  record (0x18 bytes, big-endian u16s)
    +0x00 level      +0x01 species   +0x02 item     +0x03 unk
    +0x04..07 moves  +0x08 unk       +0x09 happiness
    +0x0A hp_exp  +0x0C atk_exp  +0x0E def_exp  +0x10 spd_exp  +0x12 spc_exp
    +0x14 dvs     +0x16 unk        +0x17 unk

  Tables 0-4 are the flat rental lists; 5+ are trainer/roster tables
  (trainer header then up to 6 mons), per the Stadium-1 repo's
  disasm/oldnotes/utils/extractrostertbltbl.c.

Usage:
    python tools/gs_rental_dump.py <baserom.z64> [--list] [--table N]
                                                 [--check-expansion]
"""
import argparse
import struct
import sys

BLOB = 0x1708000
RAM = 0x802492B0
REC = 0x18
RENTAL_TABLES = (0, 1, 2, 3, 4)
GEN2_SPECIES = 251

NAMED = {144: "Articuno", 145: "Zapdos", 146: "Moltres", 150: "Mewtwo",
         151: "Mew", 243: "Raikou", 244: "Entei", 245: "Suicune",
         249: "Lugia", 250: "Ho-Oh", 251: "Celebi"}


class Blob:
    def __init__(self, path):
        self.d = open(path, "rb").read()

    def u8(self, o):
        return self.d[o]

    def u16(self, o):
        return struct.unpack_from(">H", self.d, o)[0]

    def u32(self, o):
        return struct.unpack_from(">I", self.d, o)[0]

    @property
    def total_size(self):
        return self.u32(BLOB + 8)

    @property
    def ntables(self):
        return self.u32(BLOB + 0xC)

    def dirent(self, i):
        e = BLOB + 0x10 + i * 0x10
        return self.u32(e), self.u32(e + 4)

    def table(self, i):
        off, size = self.dirent(i)
        a = BLOB + off
        return off, size, self.u8(a), a + 4      # off, size, count, first record

    def record(self, a):
        return {
            "level": self.u8(a), "species": self.u8(a + 1),
            "item": self.u8(a + 2), "unk3": self.u8(a + 3),
            "moves": list(self.d[a + 4:a + 8]),
            "unk8": self.u8(a + 8), "happiness": self.u8(a + 9),
            "statexp": [self.u16(a + o) for o in (0x0A, 0x0C, 0x0E, 0x10, 0x12)],
            "dvs": self.u16(a + 0x14),
            "unk16": self.u8(a + 0x16), "unk17": self.u8(a + 0x17),
        }

    def species_of(self, i):
        _, _, count, first = self.table(i)
        return [self.u8(first + k * REC + 1) for k in range(count)]


def cmd_list(b):
    print(f"blob ROM 0x{BLOB:X} -> RAM 0x{RAM:08X}  "
          f"total_size=0x{b.total_size:X}  ntables={b.ntables}")
    print(f"\n{'i':>3} {'offset':>8} {'size':>7} {'cnt':>4} {'lv':>4}  contents")
    for i in range(b.ntables):
        off, size, count, first = b.table(i)
        kind = "rental" if i in RENTAL_TABLES else "trainer"
        if i in RENTAL_TABLES:
            sp = b.species_of(i)
            lv = b.u8(first)
            extra = (f"{len(set(sp))} species {min(sp)}..{max(sp)} "
                     f"sorted={sp == sorted(sp)}")
        else:
            lv, extra = 0, "(trainer/roster table)"
        print(f"{i:3d} 0x{off:06X} 0x{size:05X} {count:4d} {lv:4d}  {kind:<7} {extra}")


def cmd_table(b, i):
    off, size, count, first = b.table(i)
    print(f"table {i}: blob+0x{off:X} (ROM 0x{BLOB + off:X}) size=0x{size:X} "
          f"count={count}")
    for k in range(count):
        r = b.record(first + k * REC)
        nm = NAMED.get(r["species"], "")
        print(f"  [{k:3d}] lv{r['level']:3d} sp{r['species']:3d} {nm:<9} "
              f"item={r['item']:3d} moves={r['moves']} happy={r['happiness']:3d} "
              f"statexp={r['statexp']} dv=0x{r['dvs']:04X}")


def cmd_check(b):
    """Structural invariants + a review of the planned 5-record expansion."""
    print("=== structural invariants ===")
    ok = True
    for i in range(b.ntables):
        off, size = b.dirent(i)
        if i + 1 < b.ntables:
            nxt, _ = b.dirent(i + 1)
            if nxt > off and off + size != nxt:
                print(f"  FAIL table {i}: offset+size 0x{off + size:X} != "
                      f"next offset 0x{nxt:X}")
                ok = False
    last = max(b.dirent(i)[0] for i in range(b.ntables))
    li = [i for i in range(b.ntables) if b.dirent(i)[0] == last][0]
    end = last + b.dirent(li)[1]
    print(f"  contiguity: {'OK' if ok else 'FAILED'}")
    print(f"  last table ends at 0x{end:X}, header total_size 0x{b.total_size:X}: "
          f"{'OK' if end == b.total_size else 'MISMATCH'}")
    for i in RENTAL_TABLES:
        off, size, count, _ = b.table(i)
        need = (4 + count * REC + 15) // 16 * 16
        print(f"  table {i}: size 0x{size:X} vs align16(4+{count}*0x18)=0x{need:X} "
              f"{'OK' if need == size else 'MISMATCH'}")

    print("\n=== expansion review (appending the 5 'special' rentals) ===")
    want = [150, 151, 249, 250, 251]
    for i in (1, 2, 3):
        off, size, count, _ = b.table(i)
        sp = set(b.species_of(i))
        missing = [s for s in want if s not in sp]
        dup = [s for s in want if s in sp]
        newcount = count + len(want)
        print(f"  table {i} (count {count}):")
        print(f"    absent  : {[(s, NAMED[s]) for s in missing]}")
        if dup:
            print(f"    ALREADY PRESENT (appending would DUPLICATE): "
                  f"{[(s, NAMED[s]) for s in dup]}")
        if newcount > GEN2_SPECIES:
            print(f"    appending all 5 gives count {newcount} > {GEN2_SPECIES} "
                  f"species in Gen 2")
        print(f"    correct append here is {len(missing)} record(s) -> "
              f"count {count + len(missing)}")
        grow = len(missing) * REC
        need = (4 + (count + len(missing)) * REC + 15) // 16 * 16
        print(f"    table size must go 0x{size:X} -> 0x{need:X} "
              f"(+0x{need - size:X}); data grows 0x{grow:X}")
    print(f"\n  header total_size 0x{b.total_size:X} must also grow, and every "
          f"directory\n  entry after a modified table needs BOTH its offset and "
          f"its size kept consistent.")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("rom")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--table", type=int)
    ap.add_argument("--check-expansion", action="store_true")
    a = ap.parse_args()

    b = Blob(a.rom)
    if b.u32(BLOB + 0xC) != 72:
        sys.exit(f"blob signature check failed at 0x{BLOB:X} "
                 f"(ntables={b.u32(BLOB + 0xC)}); wrong ROM?")
    if a.table is not None:
        cmd_table(b, a.table)
    if a.check_expansion:
        cmd_check(b)
    if a.list or not (a.table is not None or a.check_expansion):
        cmd_list(b)


if __name__ == "__main__":
    main()
