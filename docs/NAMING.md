# Naming pass over the Stadium 2 (G&S) decomp

Turning `func_800015C0` into `DisplayTask_Initialize`.

- Hand-written mapping: **`tools/gs_names.json`** — every entry carries its evidence.
- Transferred mapping: **`tools/s1_transfer.json`** — machine-generated, never hand-edited.
- Generator: **`tools/xmatch_stadium1.py`** — matches this ROM against Stadium 1's.
- Applier: **`tools/apply_names.py`** — `--dry-run`, `--check`, `--qa`, or bare to apply.
- Scope: the `disasm/` submodule, US tables only, on branch `stadium2-names`.

## Why this is not the Stadium 1 pass

The Stadium 1 decomp is decompiled: 7,200-odd C bodies, 193 assembly stubs. You
read a function and name it. This one is the mirror image — **10,532 of its
10,243 functions are `#pragma GLOBAL_ASM` stubs and only 99 have C bodies.**

That moves where a name lives. In Stadium 1 a name is an identifier in a `.c`
file. Here it is an entry in `disasm/linker_scripts/us/symbol_addrs_code.txt`,
which splat reads, plus the `#pragma GLOBAL_ASM("asm/us/nonmatchings/<file>/<name>.s")`
path in `disasm/src`, which the C file includes. **Splat, not the compiler, is
what turns a symbol name into code**, and the two references have to move
together — rename one without the other and the build breaks silently, because
the pragma points at a path splat no longer emits.

`apply_names.py` keeps them in step. Whole-word replacement covers both sites,
because the symbol appears as a word inside the pragma's path string too.

Starting point: **269 of 10,243 functions named (2.6%)**, all of it upstream
libultra and thread setup.

## What was done

**676 evidence-backed function names transferred from Stadium 1**, taking the
tree to **945 of 10,243 (9.2%)**.

Nothing here was named by reading a body and forming an opinion. Every one of
the 676 is a machine-verified correspondence between the two ROMs' machine code.

## How the transfer works

The two games share a large part of their engine verbatim. `xmatch_stadium1.py`
slices both ROMs into functions using each project's splat symbol table,
normalises out the fields that legitimately differ between two links of the same
source — `j`/`jal` targets, `lui` high halves, immediates encoding absolute
addresses — and matches what is left.

Four match classes, in descending confidence:

| class | count | what it means |
|---|---|---|
| `identical` | 107 | same length, every raw instruction word equal |
| `normalised` | 427 | every instruction equal once relocation-bearing fields are masked |
| `callgraph` | 35 | the Nth `jal` of an already-matched pair, ≥80% body agreement |
| `aligned` | 107 | equal-length run between two in-order anchors, ≥50% body agreement |

The segments line up too, which is itself corroboration — 478 anchors between
the two `text` segments with only 19 order inversions, because both ROMs emit a
translation unit's functions in source order.

| GS segment | → Stadium 1 | anchors |
|---|---|---|
| `text` | `text` | 478 |
| `fragment79` | `fragment62` | 65 |
| `fragment26` | `fragment31` | 11 |
| `fragment27` | `fragment34` | 7 |
| `fragment34` | `fragment41` | 6 |
| `boot` | `boot` | 4 |

By subsystem the haul is the engine floor, not the game: `BattleAnim_` (98,
almost all of fragment79), the geo scene graph (`Geo_`/`GeoNode_`/`GeoRender_`/
`geo*`, 97), `ModelAnim_` (33), `Gfx_`/`DisplayList_` (35), `Sched_` (22),
`ParticleGfx_` (20), `MtxF_`/`Vec3f_` (24), `Memmap_` (13), `Display_` (11),
`Jpeg_` (10), `Save_` (9), `TextRenderer_`/`Ui_` (18). 100 prefixes, 23 of them
used once.

**~7% is the ceiling for this technique**, and it has been reached. Stadium 2
shares Stadium 1's core engine and rewrote nearly everything above it; the
remaining ~9,300 functions are original reverse engineering.

## Two traps, and what caught them

**A symbol is not a function.** Splat's symbol table lists more than function
starts. Inside a `c` subsegment `do_c_func_detection` merges a symbol into the
function containing it, so a table entry with no emitted function is a *label in
the middle of one*. Slicing from such a label yields a function tail, and a
function tail matches things. Two names (`Dma_WriteChunks`, `Storage_QueueRequest`)
got assigned to mid-function labels before this was caught — by the applier's
own QA, which reports any applied name that reaches the symbol table but never a
pragma.

The fix is a reality filter in the matcher: inside a `c` subsegment a symbol is a
function only if a pragma emits it. Checked against the full extracted tree,
**all 69 address-named symbols that fail this test have no emitted `.s` file** —
none of them was ever a function. 282 further skips are libultra in `lib`
subsegments, all already named, so nothing nameable is lost.

**A name can only be applied once.** Two GS functions claiming one Stadium 1
symbol has two causes needing opposite treatment. Stadium 2 links the same helper
into several fragments, so one Stadium 1 function legitimately corresponds to
several here — those keep the name, suffixed with their segment
(`ParticleGfx_SetPrimColor_fragment84`). But a short generic body — a
two-instruction `osSendMesg` wrapper — collides with something unrelated, and two
claimants inside *one* segment cannot be told apart. 15 suffixed, 33 dropped.

The dropped group included the one place Stadium 1 is demonstrably wrong:
`__osPiRelAccess` and `__osSiRelAccess`, both already correctly named upstream
here, both matched Stadium 1's `Cont_NoBlockEepromQueue`. Two distinct libultra
functions cannot both be that; Stadium 1's name is misapplied.

## The audit, and the one thing it caught

Every class was audited by hand against the extracted assembly and Stadium 1's C
bodies before any of it was applied.

- **`aligned`** — the weakest class, matched on position alone. ~60 of its 117
  entries sampled across the full address range. **Zero false positives.** It
  held up because the runs being aligned sit in dense, regularly-shaped tables
  (alloc+init pairs, Init/Update/Draw triples) between closely-spaced anchors,
  and because several entries call *each other* — two independently generated
  proposals corroborating one another.
- **`callgraph`** — all 35 audited. **Zero false positives.**
- **`normalised`** — 29 audited, chosen from the shortest bodies where collision
  risk is highest. **One false positive**, and it was instructive.

`func_800436CC` was matched to `SushiGame_SetGamePhase`. Both are "compare
against a literal, branch, store to a global" — seven instructions, identical
shape. But the GS function bounds-checks against 7 where Stadium 1 checks
against 3, and it lives in always-resident `.text` while Stadium 1's is inside a
mini-game overlay. Two unrelated functions of a very common shape.

The lesson is not "short functions are risky" — a 6-instruction match was
reliably correct and a 10-instruction one of nearly the same shape
(`Profiler_SetDisplayModes`) was exactly right, literals and all. The risk factor
is **shape genericity**: a body that compares against constants, branches and
stores, and calls nothing, has almost no content left once the normalised
signature discards its immediates.

So the matcher now screens for exactly that. A `normalised` or `aligned` match
whose body calls nothing else already matched must additionally agree on its
literal constants — for the opcodes where an immediate cannot be an address
(`slti`, `sltiu`, `andi`, `xori`, and `addiu`/`ori` from `$zero`). Bodies that do
call a matched function keep their match; the callee is independent evidence.

That screen dropped 21 matches, including both entries the audit had flagged:
`SushiGame_SetGamePhase`, and `Trade_SpeciesEvolvesOnTransfer`, whose four
compared species IDs differ between the games in a way we could not independently
confirm was just Gen 2 renumbering.

**Inherited error rate.** These names come from Stadium 1, and that project's own
naming pass documents names it got wrong and later fixed. A correct match to a
misnamed Stadium 1 function transfers the mistake intact --- `Cont_NoBlockEepromQueue`
above is a proven instance. The match evidence certifies *the correspondence*,
not the name.

## Verification

Unlike the Stadium 1 pass, this one is **extraction-verified**. Splat 0.25.0 was
run against the renamed symbol table on a scratch copy of the tree:

- **10,532 US `GLOBAL_ASM` pragmas, 0 unresolved** after extraction;
- **10,532 `.s` files emitted** — an exact 1:1 with the pragmas;
- **all 676 transferred names present as emitted `.s` filenames**.

`apply_names.py --qa` is clean on all six checks: every applied name resolves to
exactly one symbol table entry, none is defined twice, no pragma points at a
symbol that does not exist, none clashes with a C keyword, all are valid C
identifiers, and none is symbol-table-only.

**Still not assembly-verified.** There is no `mips-linux-gnu` toolchain on this
host, so the renamed tree has not been assembled or linked. Extraction passing
makes that very likely to be fine — the names are labels — but run
`tools/mac_build_disasm.sh` in the build container before trusting it.

## Deliberately not done

- **The JP tables.** `linker_scripts/jp/` is a separate address space with its
  own 6,573 symbols. The recomp targets US only, and a US-only rename cannot
  break JP, because every symbol renamed here is address-derived and therefore
  version-specific. Porting the names is a later mechanical pass: the same
  matcher, US against JP, where agreement should be near-total.
- **Data symbols and struct types.** `gs_names.json` has the sections; they are
  empty. A textual rename cannot be type-aware.
- **Three names Stadium 1 disagrees with us about.** `Thread3_CreateThread`
  (S1: `Sched_Init`), `Thread4_CreateThread` (S1: `Audio_StartThread`) and
  `Vi_SelectMode` (S1: `Video_SetMode`) are the same functions under different
  spellings. The upstream `pret/pokestadiumgs` name stands; the disagreement is
  recorded in `gs_names.json` under `_conflicts_with_stadium_1` rather than
  resolved by fiat. `Thread4_CreateThread` is the one worth re-deriving — if
  Stadium 1 is right that thread 4 is the audio thread, that is a real finding.

## How to get a name right

The four rules from the Stadium 1 pass (`docs/NAMING.md` there) all still apply,
and rule 1 applies harder. **A function's body tells you what it does, not what
it is for** — and here you do not even have a body, you have assembly. Where a
routine is reached through a table, a switch or a state id, the caller's index is
the primary evidence. When a table indexes into game data, audit the whole table
against the data at once rather than naming entries one at a time.

Rule 3 — **use the game's own text as an oracle** — survives the move to
assembly intact and is probably the strongest tool available from here. A
screen's visible label is strong evidence about the code beneath it, and a
disagreement between the two is a bug you can prove.

## Adding more names

Hand-written names go in `tools/gs_names.json` with their evidence. It takes
precedence over the generated file, so adding the same key there overrides a
transferred name.

```bash
python3 tools/apply_names.py --dry-run   # review; refuses on collisions
python3 tools/apply_names.py
python3 tools/apply_names.py --check     # no old name survives
python3 tools/apply_names.py --qa        # the applied names are sound
```

To regenerate the transfer after the Stadium 1 decomp gains names, **revert
`disasm/` first**. The matcher skips GS functions that already have a name, so
run against a renamed tree it produces almost nothing; it refuses to overwrite a
larger mapping with a much smaller one rather than let that happen silently.

```bash
git -C disasm checkout -- .
python3 tools/xmatch_stadium1.py --report          # summarise, write nothing
python3 tools/xmatch_stadium1.py --out tools/s1_transfer.json
python3 tools/apply_names.py
```
