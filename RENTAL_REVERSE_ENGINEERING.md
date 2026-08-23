# Rental Blob Reverse Engineering — Pokémon Stadium 2 / G&S (US)

Companion to the Stadium 1 analysis in
`D:/Projects/lg/PokemonStadiumRecomp-rental/RENTAL_REVERSE_ENGINEERING.md`.
Everything below is **byte-verified against `baserom.z64`** unless explicitly
labelled as inference.

Repro tool: `tools/gs_rental_dump.py` (`--list`, `--table N`, `--check-expansion`).

---

## TL;DR

The rental blob is **uncompressed in ROM at `0x1708000`**, 0xFE90 bytes, copied
verbatim to RAM `0x802492B0`. It is a directory of 72 tables; tables 0–4 are the
flat rental lists, 5+ are trainer rosters. Records are 24 bytes.

The expansion hook in `game.toml` now inserts missing records in sorted order and
updates directory metadata. The remaining record-authoring risk is the
statistical quality of the five special-rental records; see §5.

---

## 1. Location and container format

`0x1708000` is exactly the offset the Stadium 1 repo's
`disasm/oldnotes/utils/extractrostertbltbl.c` documents for Stadium G&S, and the
format matches that tool — with one field the tool ignores (see the directory `size`).

Located unambiguously: the ROM contains exactly one place where a 4-byte big-endian
`0xCB0` is followed 0x10 later by `0x23D0` (the two known table offsets), at
`0x1708020` — i.e. directory index 1, giving blob base `0x1708000`.

```
blob header
  +0x00 u32  0
  +0x04 u32  0
  +0x08 u32  total_size   = 0xFE90
  +0x0C u32  ntables      = 72 (0x48)

directory at +0x10, 72 entries of 0x10 bytes:
  +0x00 u32  offset       (relative to blob base)
  +0x04 u32  size         (padded to 16)
  +0x08 u32  0
  +0x0C u32  0

table at `offset`:
  u8 count, 3 pad bytes, then count * 0x18 records
```

Verified invariants (all 72 entries, `--check-expansion`):
- `offset + size == next table's offset` — **the blob is strictly contiguous**.
- last table's `offset + size == 0xFE90 == header total_size`.
- for every rental table, `size == align16(4 + count * 0x18)`.
- directory words 2 and 3 are zero in every entry.

> **`size` is a real field, not padding.** The Stadium 1 oldnotes tool skips those
> three words, so it is easy to miss. Any edit that grows a table must update the
> table's own `size`, every later table's `offset`, and the header `total_size`.

### Record layout (0x18 bytes, big-endian u16s)

| off | field | notes |
|---|---|---|
| 0x00 | level | |
| 0x01 | species | 1..251 |
| 0x02 | item | **0 in every rental record** |
| 0x03 | unk | |
| 0x04–0x07 | move 1..4 | |
| 0x08 | unk | |
| 0x09 | happiness | |
| 0x0A | stat-exp HP | u16 |
| 0x0C | stat-exp Attack | u16 |
| 0x0E | stat-exp Defense | u16 |
| 0x10 | stat-exp Speed | u16 |
| 0x12 | stat-exp Special | u16 |
| 0x14 | DVs | u16, packed nibbles |
| 0x16, 0x17 | unk | |

**Contrast with Stadium 1:** Stadium 1 stores rentals *pre-expanded* in the 0x54-byte
runtime battle-Pokémon struct with stats already computed. Stadium 2 stores a
*compact 0x18-byte serialized* record with no computed stats — the game derives them
at load. That means a Stadium-2 record cannot be numerically self-checked the way the
Stadium 1 table could; correctness of an added record depends on the runtime path.

---

## 2. The tables

| i | offset | ROM | count | level | species | reading |
|---|---|---|---|---|---|---|
| 0 | `0x490` | `0x1708490` | 86 | 5 | 86 unique, 1..246 | Little Cup |
| 1 | `0xCB0` | `0x1708CB0` | 246 | 100 | 246 unique, 1..248 | Prime Cup |
| 2 | `0x23D0` | `0x170A3D0` | 248 | 100 | 248 unique, 1..251 | Prime Cup (variant) |
| 3 | `0x3B20` | `0x170BB20` | 246 | 50 | 246 unique, 1..248 | Poké Cup |
| 4 | `0x3B20` | `0x170BB20` | 246 | 50 | same table | dedup — shares table 3 |
| 5–71 | — | — | 1–9 | — | — | trainer/roster tables |

Every rental table is **strictly sorted ascending by species with no duplicates**.

Missing species:

- **table 1** — Mewtwo, Mew, Lugia, Ho-Oh, Celebi (5)
- **table 2** — Mewtwo, Lugia, Ho-Oh (3) — **Mew and Celebi are already present**
- **table 3/4** — Mewtwo, Mew, Lugia, Ho-Oh, Celebi (5)

Balancing: unlike Stadium 1's mostly-uniform stat-exp, GS rental tables use many
distinct stat-exp tiers (11–13 distinct sets per table, e.g. 45000 down to 6400)
and 9–11 distinct DV words — i.e. per-species grading is the norm here.
Table 0 (Little Cup) has all stat-exp zero.

Tables 5+ were not decoded in detail; per the Stadium 1 oldnotes tool they are
`{group, trainer, unk, text, nmons, unk, unk, unk}` headers followed by six 0x18-byte
mon slots, with unused slots filled with level-1 Bulbasaur / happiness 0x7F / DVs
0x6777. **Not verified here** — flagged as inference.

---

## 2b. The blob's slot in ROM — and how much room there is

`0x1708000` is **entry 11 of an asset ROM-offset table at ROM `0x437620`**
(19 entries, `u32` big-endian ROM offsets, terminated by 0; preceded at
`0x437610` by what looks like an ASCII build stamp `"0117" "2339"`). This is the
only aligned occurrence of the value `0x01708000` as data anywhere in the ROM.

The blob's data ends at `0x1717E90`; the next asset begins at `0x1718000`, and
the gap is **368 bytes of `0xFF` padding — exactly 15 records of 0x18**.

That is the hard ROM-side budget. A correct expansion needs
**5 + 3 + 5 = 13 records = 312 bytes**, so **it fits with 56 bytes to spare** —
a static ROM patch is possible without relocating the blob or touching the asset
table. (The current implementation instead rewrites the blob in RAM at runtime.)

Note the address is **never referenced as an instruction immediate** — searching
the freshly extracted `asm/` tree for `0x1708000` and for the hi/lo pair of
`0x802492B0` returns nothing. It is looked up through this asset table, which is
why constant-grep for the loader fails.

## 3. How it gets to RAM

`0x1708000` → `0x802492B0`, uncompressed and byte-identical (the recomp patch reads
the live RAM copy at `0x802492B0 + 0xCB0` and finds count 246, matching ROM).

The DMA primitive is `func_80006ACC` (`disasm/src/7140.c:42-56`), a generic
non-blocking DMA-request enqueue, driven by the chunked copy helper `func_80003F74`
(`disasm/src/4420.c:29-41`, ≤0x1000-byte chunks). Neither is rental-specific, and
`0x802492B0` appears nowhere as a symbol — it is a runtime address, which is why the
existing patch hooks `func_80006ACC` rather than a named loader.

The function that actually parses the directory/count and builds the selection list
is **not identified yet** (see §6).

---

## 3b. Stat pipeline (needed to author sane new records)

Because GS records store no computed stats, an appended record's strength comes
entirely from its level / DVs / stat-exp fed through the game's formula. That
formula is now located and verified (full detail in `DECOMP_SETUP.md`):

| address | meaning |
|---|---|
| `0x8006183C` | `CalculateStatValue(statIndex, species, statExp, level, dvWord)`, capped at 999 |
| `0x8006179C` | `GetPokemonDV` — Atk bits12-15, Def 8-11, Spd 4-7, Spc 0-3; SpAtk and SpDef **share** the Special nibble |
| `0x8006175C` | integer sqrt of stat-exp |
| `0x80063838` | `GetBaseStat(species, statIndex)`, valid `0 < species < 252` |
| `0x80098320` | `gBaseStats` — 251 entries × 0x16, indexed `species - 1` |

Standard Gen 2: `stat = ((base+DV)*2 + floor(sqrt(statexp)/4)) * level/100 + 5`,
HP adds `level + 10` instead of 5. Base-stats table verified exactly against
known Gen 2 values for 12 species.

Practical consequence: the five records the current patch appends use DVs
`0x0000` and stat-exp `0`, which is the **weakest possible** Pokémon at that
level. Copy the DV/stat-exp fields from a comparable existing record in the same
table instead.

## 4. State of the decompilation

`disasm/` is scaffolding, not a usable decomp: 80 `.c` files but **12,810
`#pragma GLOBAL_ASM` stubs**. As of 2026-08-13 splat is installed and the
**`asm/us/` tree is extracted (10,720 `.s` files)** — see `DECOMP_SETUP.md` for
the procedure and two important gotchas (renaming a function symbol deletes its
assembly; splat on Windows corrupts the linker script).

The **readable** game code is the recompiler output under
`build-local-ps2/generated/` (`funcs_0.c` … `funcs_234.c`, plus `funcs.h`,
`recomp_overlays.inl`, `dispatch_aliases.c`) and the fuller snapshot
`build-local-ps2/generated-full-current/`. It is machine-generated from MIPS
(`func_8xxxxxxx` names, `MEM_W`/`MEM_B` accessors, split hi/lo immediates) but it is
complete and traceable — that is the right place to find the blob consumer, not `disasm/`.

---

## 5. Review of the expansion patch (`game.toml`, hook on `func_80006ACC`)

The hook inserts five records into table 1, three into table 2, and five into the
shared table 3/4 data. It shifts the tail in record-sized steps, removes the
obsolete eight-byte pad after each expanded table, and updates directory
offsets, sizes, and header `total_size`. A count check makes the operation
idempotent.

**Verified invariants:** each expanded table has 251 sorted, unique species;
table 3 and table 4 retain one shared offset; and every later directory offset
tracks the physical shift.

**Remaining risk:**

1. **Record quality is still provisional.** The five special records use DVs
   `0x0000` and zero stat-exp fields, whereas real table records use stronger
   values. This is mechanically valid but likely not game-design-correct.

2. **The previous hook duplicated Mew and Celebi.** Table 2 already contains species 151 and
   251; it is missing only Mewtwo, Lugia and Ho-Oh. Appending all five produces two
   duplicate entries and `count = 253`, which exceeds the 251 species in Gen 2.
   Table 2 should receive **3** records → count 251.
3. **The previous hook left the directory `size` field stale.** The fix-up loops rewrite only bytes
   `info+0..3` (offset). Table 1's `size` stays `0x1720` while its data now needs
   `0x1790`; same for table 2. This breaks the `offset + size == next offset`
   invariant that holds for all 72 entries in the original blob. Whether it is fatal
   depends on whether the consumer bounds on `size` or on the count byte — unresolved,
   see §6 — but the invariant should be maintained regardless.
4. **The previous hook left the header `total_size` stale.** It stayed `0xFE90` after
   the blob grows by `0xF0`.
5. **The previous hook broke sort order.** Every rental table is strictly species-sorted; appending
   150/151/249/250/251 *after* species 248 leaves the list unsorted. If the selection
   screen or any lookup assumes dex order (plausible given the data is sorted, but
   **not verified**), the new entries will be misplaced or unreachable. This is a
   strong candidate for the "appended entries still missing" symptom recorded in
   `CLAUDE_HANDOFF.md`.
6. **The appended records are statistically empty**: DVs `0x0000` and all five
   stat-exp fields `0`, whereas real table-1 records use DVs up to `0xFEEF` and
   stat-exp up to 45000. The five legendaries would be markedly weaker than every
   other rental. Probably not intended.
7. Minor: the previous hook wrote table 1's five records twice (once by the `i < shift` loop, then
   again by the nested `i<5 / j` loop). Harmless, but dead work.
8. The previous patch also shifted table 3 (lv50 Poké Cup) without adding records to it, so the
   Poké Cup roster keeps its 5 gaps. Consistent with "Prime Cup only", but worth
   confirming that is the intent.

`tools/gs_rental_dump.py --check-expansion` reports items 1–3 and the exact target
sizes:

```
table 1: absent 5 -> count 251, size 0x1720 -> 0x1790
table 2: absent 3, ALREADY PRESENT Mew + Celebi -> count 251, size 0x1750 -> 0x1790
table 3: absent 5 -> count 251, size 0x1720 -> 0x1790
```

Note all three converge on `size 0x1790` / `count 251` — a full 251-species roster.

---

## 6. Open questions

1. **Does the consumer bound on the count byte or on the directory `size`?**
   Still unresolved. A search of `build-local-ps2/generated/` found the *writer*
   (the `game.toml` hook, plus compiled-out copies in
   `generated-full-current/funcs_119.c` and its `.with-rental-expansion` /
   `.pre-gs-expansion` twins) but **not the reader**. Directory-style `+0x10`
   stride-16 access is too common a pattern in machine-generated C to attribute
   without a cross-reference.
   Note: "the existing patch only bumps the count byte, therefore the count byte
   is the bound" is **not** evidence — it only tells us what the patch author
   assumed. `CLAUDE_HANDOFF.md:111` records the same gap ("inspect the
   table-directory consumer and the selection-screen count/index path next").
   Resolve it by finding who calls `func_80003F74` with this destination, or by
   watching reads of `0x802492B0 + 0x10 + i*0x10` at runtime.
2. Does the selection screen assume species-sorted order (defect 4)?
3. What are record bytes `0x03`, `0x08`, `0x16`, `0x17`?
4. Exact layout of the trainer tables (5–71) — inferred from the Stadium 1 oldnotes
   tool, not verified here.
5. Where the blob's ROM→RAM copy is actually issued. Narrowed: the blob is
   asset-table entry 11 at ROM `0x437620` (§2b), so the loader indexes that
   table rather than using a literal. Find the code that reads `0x437620`.

## 7. Recommended next steps

1. Answer §6.1 from the generated C — cheapest high-value step.
2. **Consider a static ROM patch instead of the runtime hook.** §2b shows the
   13 needed records fit in the 368-byte pad after the blob, so the blob can be
   rebuilt in place at build time — simpler and cheaper than rewriting ~64 KB of
   RDRAM on every load, and it removes the ordering/idempotency hazards.
3. Otherwise, rewrite the `game.toml` hook to a table-driven form: for each of tables 1, 2, 3,
   insert **only the species that table is missing**, in **sorted position** rather
   than appended, and update `count`, the table's `size`, all later `offset`s, and the
   header `total_size`. Give the added records realistic DVs/stat-exp copied from a
   comparable existing record.
4. Re-verify the patched blob with the same invariants
   `gs_rental_dump.py --check-expansion` applies to ROM.
