# Stadium 2 decompilation scaffolding

Set up 2026-08-13. This documents how to get a working `disasm/` extraction and
the conventions/gotchas found while doing it.

## Status

- splat is installed and **extraction works**: `disasm/asm/us/` contains
  **10,720 `.s` files**, matching the 12,810 `#pragma GLOBAL_ASM` stubs in
  `disasm/src/*.c` (the rest are ultralib/library code).
- Coverage reported by splat: **4 MB (6.59%) in defined segments, 62 MB (93.41%)
  still unknown bin**. The rental blob at ROM `0x1708000` is in that unknown
  region and is a good candidate for a labelled segment (see below).
- This is a *scaffolding* milestone, not a decompilation. Nothing new was
  decompiled to C; 12,810 functions remain as assembly.

## Setup (already done; repeat after `distclean`)

`make` is not available in this environment, so run splat directly:

```bash
cd disasm
python -m venv .venv
./.venv/Scripts/python.exe -m pip install -U pip
./.venv/Scripts/python.exe -m pip install -r requirements.txt
cat yamls/us/header.yaml yamls/us/rom.yaml > pokestadiumgs-us.yaml
./.venv/Scripts/python.exe -m splat split pokestadiumgs-us.yaml
```

`disasm/baseroms/us/baserom.z64` must be present (it is).
`asm/`, `.venv`, `build/` and `pokestadiumgs-*.yaml` are all gitignored.

To force a full re-extract: `rm -rf asm/us .splat` before splitting.

## Gotchas (both cost real time — read before touching this)

### 1. Renaming a function symbol deletes its assembly

If you rename `func_8006183C` to `CalculateStatValue` in
`linker_scripts/us/symbol_addrs_code.txt`, splat **stops emitting
`asm/us/nonmatchings/615D0/func_8006183C.s` entirely** — it assumes a
non-`func_`-named symbol is defined in C. Call sites correctly switch to the new
name, but the definition disappears and the `#pragma GLOBAL_ASM` in
`disasm/src/615D0.c` then points at a missing file, breaking the build.

**Convention: only rename a function at the moment you decompile it to C**
(and delete its pragma in the same change). Until then, record the intended
name as a trailing comment:

```
func_8006183C = 0x8006183C; // type:func CalculateStatValue
```

That is the convention used for the four functions named so far (below).

**Data symbols do not have this problem** — naming `gBaseStats` worked and
immediately improved the assembly, which now reads
`lbu %lo(gBaseStats + ...)($v0)` instead of a bare address.

### 2. Running splat on Windows corrupts the linker script

`splat split` rewrites `linker_scripts/us/pokestadiumgs.ld` using **backslash**
paths (`build\asm\us\boot.o` instead of `build/asm/us/boot.o`) — 2413 lines
changed, and it would break any real build.

**Always `git checkout -- linker_scripts/us/pokestadiumgs.ld` after splitting**,
or run splat under WSL. The `.ld` is tracked; the `asm/` tree is not.

## Symbols named so far

All verified against the ROM — see `RENTAL_REVERSE_ENGINEERING.md`.

| address | current symbol | verified meaning |
|---|---|---|
| `0x8006175C` | `func_8006175C` | `StatExpSqrt` — `for(i=1;i<255;i++) if(i*i>=x) break;` |
| `0x8006179C` | `func_8006179C` | `GetPokemonDV(statIndex, dvWord)`; Atk bits12-15, Def 8-11, Spd 4-7, Spc 0-3; index 4 and 5 share the Special nibble |
| `0x8006183C` | `func_8006183C` | `CalculateStatValue(statIndex, species, statExp, level, dvWord)`, capped at 999 |
| `0x80063838` | `func_80063838` | `GetBaseStat(species, statIndex)`; validates `0 < species < 252` |
| `0x80098320` | **`gBaseStats`** | base-stats table, 251 entries × 0x16, indexed `species - 1` |

`gBaseStats` is the only one actually applied as a symbol (rule 1 above).
Naming matches the Stadium 1 decomp (`CalculateStatValue`, `GetPokemonDV`) so
the two projects stay comparable.

### Base-stats table, verified

ROM `0x98F20`–`0x9A4B2`, VRAM `0x80098320`. Entry stride `0x16` (22):

| off | field |
|---|---|
| +0x00 | index byte (runs 226, 227, 228 … for species 1, 2, 3) |
| +0x01 | base HP |
| +0x02 | base Attack |
| +0x03 | base Defense |
| +0x04 | base Speed |
| +0x05 | base Sp.Atk |
| +0x06 | base Sp.Def |
| +0x07 | type 1 |
| +0x08 | type 2 |
| +0x09 | catch-rate-like |
| +0x0A | 100 in every sampled record |
| +0x0B..+0x15 | unidentified |

Verified exactly against known Gen 2 base stats for Bulbasaur, Charmander,
Squirtle, Pikachu, Snorlax, Dragonite, Mewtwo, Mew, Raikou, Lugia, Ho-Oh and
Celebi — 12/12 exact. The distinct type ids across all 251 species are
`{0,1,2,3,4,5,7,8,9,20,21,22,23,24,25,26,27}`, i.e. the Gen 2 set including
Steel (9) and Dark (27).

`GetBaseStat` computes `0x8009830A + species*22`, folding the `-0x16` into the
base — the table itself starts at species 1. The bytes immediately before it are
a separate `(index, type)` pair table terminated by `0xFF`.

RAM→ROM for the fixed `text` segment (ROM `0x1000`, VRAM `0x80000400`):
`rom = vram - 0x7FFFF400`. **This only holds inside `text`** — fragments are
separately DMA'd overlays with their own `vram:`/`start:` pairs in
`yamls/us/rom.yaml`.

## Suggested next steps

1. **Label the rental blob as a segment** in `yamls/us/rom.yaml`. It is
   currently anonymous "unknown bin". It is ROM `0x1708000`, length `0xFE90`
   — adding it as a named `bin` segment would give it `_ROM_START`/`_ROM_END`
   symbols instead of the hardcoded `0x1708000` literal.
2. **Find the rental blob's consumer** — the open question in
   `RENTAL_REVERSE_ENGINEERING.md` §6.1. Now that `asm/` exists, grep it for the
   hi/lo pair that forms `0x802492B0` or `0x1708000`:
   `grep -rn "0x8025\|%hi(0x802492B0)" asm/us/nonmatchings/ | ...`
   That was impossible before this extraction.
3. Decompile that consumer to C and rename its symbols in the same change.
