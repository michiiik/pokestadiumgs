# Naming pass over the Stadium 2 (G&S) decomp

Turning `func_800015C0` into `DisplayTask_Initialize`.

- Hand-written mapping: **`tools/gs_names.json`** — every entry carries its evidence.
- Transferred mapping: **`tools/s1_transfer.json`** — machine-generated, never hand-edited.
- Generator: **`tools/xmatch_stadium1.py`** — matches this ROM against Stadium 1's.
- Applier: **`tools/apply_names.py`** — `--dry-run`, `--check`, `--qa`, or bare to apply.
- Triage aid: **`tools/subsystem_map.py`** — for each unnamed function, the named functions it calls and is called by, bucketed by translation unit.
- Dispatch tables: **`tools/find_dispatch_tables.py`** — finds function-pointer tables whose per-index entries are naming evidence.
- Scope: `disasm/` (a vendored copy of the fork's `stadium2-names` branch), US tables only.

## Why this is not the Stadium 1 pass

The Stadium 1 decomp is decompiled: 7,200-odd C bodies, 193 assembly stubs. You
read a function and name it. This one is the mirror image. Of its **10,901 US
function symbols, 10,532 are `#pragma GLOBAL_ASM` stubs** and 64 have C bodies;
the rest are libultra, linked from `lib/` rather than stubbed.

That moves where a name lives. In Stadium 1 a name is an identifier in a `.c`
file. Here it is an entry in `disasm/linker_scripts/us/symbol_addrs_code.txt`,
which splat reads, plus the `#pragma GLOBAL_ASM("asm/us/nonmatchings/<file>/<name>.s")`
path in `disasm/src`, which the C file includes. **Splat, not the compiler, is
what turns a symbol name into code**, and the two references have to move
together — rename one without the other and the build breaks silently, because
the pragma points at a path splat no longer emits.

`apply_names.py` keeps them in step. Whole-word replacement covers both sites,
because the symbol appears as a word inside the pragma's path string too.

Starting point: **297 of 10,901 function symbols named (2.7%)**, all of it
upstream libultra and thread setup.

## What was done

**676 evidence-backed function names transferred from Stadium 1**, taking the
tree to **973 of 10,901 (8.9%)**.

Nothing here was named by reading a body and forming an opinion.

## Phase 3.1: boot and scene dispatch

The first original reverse-engineering batch adds **23 names**, taking the tree
to **1,093 of 10,901 functions (10.0%)**. It maps the always-resident game state
machine that `Game_Thread` enters on boot: the state reader and sole writer, the
thread initializer, and all 19 jump-table handlers.

`Game_ThreadInit` establishes state 17. `Game_State17_Boot` loads fragments 15
and 67 before selecting state 1; `Game_State01_Loop` drives fragment 16 under
the game's `loop` pool tag and normally advances to state 2;
`Game_State02_Run` loads fragment 17 under `gbch` and dispatches its result into
the rest of the scene states. The exact jump-table positions, fragment loads,
pool tags, and outgoing transitions are recorded with each name in
`tools/gs_names.json`.

Only roles established by dispatch position or strong in-game tags are in the
names. Broader readings such as title/attract, main menu, and battle-mode roles
remain hypotheses in the evidence text. Probable audio helpers, the `dbug`
scene selector, and menu-result accessors remain unnamed for their own subsystem
passes.

## Phase 2: structure around the anchors

Phase 1 hit the transfer technique's ceiling, so phase 2 extracts names from
the structure around the 676 anchors rather than from Stadium 1. **97 further
names, taking the tree to 1,070 of 10,901 (9.8%)**, plus two survey tools.

**Fragment entry points (87 names).** Every fragment begins with an 8-byte
header trampoline -- a `J` to the fragment's real entry plus its delay slot --
which `game.toml` already relies on. The header is a `textbin` subsegment so
splat emits no symbol for it, but the J target is a real function.
`tools/name_fragment_entries.py` decodes the J at each fragment's offset 0 and
names the target `fragmentN_main`. Two fragments needed more than the plain
decode: fragment26's header jumps into a table of further J trampolines whose
first entry lands on the already-named `DisplayList_InitIndexedTextureSegment`,
and fragment28 is linked at `0x80000000` but loaded at `0x8FE00000`, so its
target resolves through the linked base. fragment43's entry turned out to have
a C body, which is why QA flags `fragment43_main` as symbol-table-only -- that
flag means "no GLOBAL_ASM pragma", and is expected there.

**The geo layout command table (9 names).** `find_dispatch_tables.py` found
180 candidate function-pointer tables; the one at `0x80094BB4` is the geo
layout command dispatch table, 43 entries, 34 of them already named by the
phase 1 transfer and in exact command order against Stadium 1's
`GeoLayoutJumpTable`. The 9 gaps were audited against Stadium 1 individually
before naming, which mattered: `skip`, `create_ambient_light` and
`set_node_flag4` are instruction-identical to their Stadium 1 counterparts at
the same indices, index 0x12 is a two-instruction `jr $ra; nop` and Stadium
1's index 0x12 is `geo_layout_cmd_noop` -- but index 0x17's body agrees with
Stadium 1's `geo_layout_cmd_create_shadow_context` on only 14% of
instructions, so the Stadium 1 name was deliberately **not** transferred; it
and the four indices past the end of Stadium 1's 39-entry table are named by
position alone (`geo_layout_cmd_17`, `geo_layout_cmd_27` ... `geo_layout_cmd_2A`).
That is rule 1 working as intended: the table index is the primary evidence,
the body is corroboration, and here the body vetoed.

**The libultra remainder (1 name).** A direct pass over the `lib` subsegments
found all 282 of their symbols already named upstream, and the 112 libultra
names Stadium 1 has that we lack are functions this ROM does not link
(libaudio, LEO/64DD) or already carries under a different spelling (`_bzero`,
`guMtxIdentF`). Nothing was left to recover there. The one genuinely unnamed
asm helper with solid evidence is the ROM's first instruction:
`func_80000400` is now `entrypoint` (`game.toml` already pins it as the
entrypoint). The IPL3 `func_A400*` labels and the three handwritten
`func_80021xxx` helpers were left alone -- no independent evidence for their
roles.

**The survey tools.** `tools/subsystem_map.py` prints, per translation unit,
every unnamed function with its named callers and callees -- the partition that
makes a manual pass tractable (`229E0` alone has 208 anchors around 331
unnamed functions). `tools/find_dispatch_tables.py` found the 180 candidate
tables (1,560 entries); the historical Phase 2 batch resolved 102 + the 9 geo
entries, while later Phase 3 batches resolve the 253-, 225-, 83-, 53-, 50-,
and 9-entry tables positionally.

Phase 2 is assembly-verified: the renamed tree builds the byte-identical US
ROM (md5 `1561c75d11cedf356a8ddb1a4a5f9d5d`) in the linux/amd64 container.

## Phase 3.2: fragment and main-pool eviction hooks

The loader's callback edges provide stronger evidence than the generic function
shapes around them. `Asset_LoadToSegment` installs
`Memmap_SegmentCleanupCallback` for allocations in the `0x82000000` segment
range; the callback checks the owning segment base and clears the segment map
when the allocation is evicted. `Fragment_Register` installs the parallel
`Memmap_FragmentCleanupCallback` for the `0x81000000` fragment range. The
shared header helper is `MainPool_GetAllocationSize`: it reads the main-pool
block size stored at `user_pointer - 0xC`, and both registration paths use it
before deciding whether to reallocate.

The archive path's post-registration helper is now
`Fragment_RelocateAndReset`. Its body calls `Memmap_RelocateFragment`, computes
the fragment end from the loaded header, and calls
`MainPool_ResetStateToOffset`; that call relationship fixes the role without
assuming a particular archive format. The actual file/decompression worker at
`func_800042C0` remains address-named because it handles multiple `PERS`/`PRES`
and fallback payload forms and its format-specific consumers are not yet
settled. Fragment-to-state assignments remain hypotheses until each state's
loader call site is audited.

The fragment-role inventory now covers all 88 entries in
`fragments_relocatable.txt`. Direct state-dispatch evidence assigns fragment
16 to state 1, 17 to state 2, 25 to state 3, 11/4/10/26 to state 4, 29 to state
5, 43/44/64/12/27/79/80 to state 6, 3/13/87 to state 7, 22 to state 11,
15/67 to state 17, and 88/40 to state 19. State 10's minigame setup and
dispatch band covers 2/3/4/26/27/43-57/59-66; these are shared minigame
residents rather than individual title assignments. The remaining entries —
1, 5-9, 14, 18-21, 23-24, 28, 30-39, 41-42, 58, 68-78, and 81-86 — are
explicitly hypothesised as optional or mode-selected overlays whose direct
caller has not yet been recovered. This is an unresolved-role hypothesis, not
a semantic name, so no fragment is silently omitted from the loader audit.

## Phase 3.3: audio request-id edge

The small audio helpers at `0x800355D4` and `0x800355E4` are now named from
their shared global and call sites. `Audio_RequestEvent` suppresses duplicate
ids, forwards a changed id to the resident dispatcher at `0x80021ED8`, and
stores it as the current request. `Audio_ResetRequestId` writes the sentinel
`-1`; the game thread calls it when leaving the minigame state. This establishes
the request/reset edge without claiming that the larger `0x800354B4` orchestration
function is a music-only API; its mode and task transitions remain for the
audio-thread pass.

## Phase 3.4: minigame fragment inventory

`Game_State10_Minigame` now has a call-site inventory in the ledger: its
`Fragment_Load`/`Fragment_LoadAndCall` operands name the complete resident set
`{2, 3, 4, 26, 27, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
56, 57, 59, 60, 61, 62, 63, 64, 65, 66}`. The first five are loaded during
minigame setup; the remaining entries are selected by the minigame dispatch
branches and paired as loader/callback operations. This is direct evidence from
the ROM-start operands, not an inference from fragment names. Individual
fragment init/update/draw roles remain open until their callback targets and
per-minigame state tables are audited.

The first minigame state helpers are now named from direct body and caller
evidence. `Minigame_StateInit` initializes the `D_801291E0` state block,
`Minigame_SetModeDefaults` seeds `D_8012B3E8`, and
`Minigame_UpdateResultState` maps the loaded fragment result back into that
mode block. The controller-facing wrappers are `Minigame_ProcessInput`,
`Minigame_UpdateControllerState`, and `Minigame_ResetControllerPoll`; their
fragment callbacks respectively scan four controller records, normalize the
per-loop controller state, and clear those records while resetting the GB
Tower poll mask. `Minigame_ProcessPlayerEvents` covers the three-argument
fragment callback as well: its body scans four player records and their
18-slot event tables. The callback's individual event meanings remain open.

The supporting record helpers are covered as well: `Minigame_ResetPlayerRecord`
clears one embedded player record, `Minigame_ResetPlayerSubstate` initializes
its four-word substate, `Minigame_SetPlayerMask` writes the active-player bit,
and `Minigame_MapControllerButtons` translates the four controller bits into
the destination input flags. `Minigame_ProcessPlayerEvents` is the wrapper for
the fragment callback that scans the four player records and their 18 event
slots. These names remain structural and data-flow based; they do not assign
individual minigame titles to the records.
`Minigame_UpdatePlayerCounters` wraps the callback that increments the selected
18-slot counter for each player, while `Minigame_ResetRoundPlayers` restores
the GB Tower poll mask and resets all four player records before a new round.

## Phase 3.5: GB-save format and checksum helpers

The save/Controller Pak pass adds two names in the GB-save translation unit.
`GbSave_ComputeChecksumRange` is called by four save-block writers; its body
sums the requested byte range, truncates to 16 bits, and stores the result via
the existing little-endian helper. `GbSave_IdentifyFormat` is called by the
main GB-save flows and is more specific than a generic parser label: it checks
the `0x3031` header marker, requires a non-empty version field, compares the
embedded names against seven resident format strings, and returns the matching
format index. The lower-level Pak presence and port-availability functions
were already transferred and remain separately named.

The Controller Pak gate is `GbSave_RequirePakPresent`: it checks
`GbTower_CheckPakRemoved` and routes a missing Pak through
`Game_ShutdownAndLoadFragment`. The record path is explicit in the save
translation unit: `Save_WriteRecord` copies a 24-byte record and sets its
pending bit, `Save_CommitRecord` writes the footer and commits that bit, and
the paired `Save_InvalidateRecord`, `Save_RestoreRecord`, and
`Save_ClearRecord` helpers implement the invalidation/restore/clear states.
`Save_Checksum`, `Save_WriteFooter`, and `Save_ResetBank` complete the checksum,
footer, and bank transitions; `GbPak_VerifyPattern`, `GbPak_DetectRam`, and the
`GbTower_*Pak*` anchors cover Pak detection and removal handling. The remaining
address-named routines in these translation units lack a distinct read/write
or Pak edge and remain explicitly outside this naming claim.

## Phase 3.9: GB Tower and Transfer Pak paths

The transfer path is now named from the hardware calls themselves:
`GbPak_Initialize` performs `osGbpakInit`/id/connector setup,
`GbPak_ProbeAndDetectRam` repeats the id/connector probe and detects RAM,
`GbPak_ReadCommand` and `GbPak_WriteCommand` gate the shared
`GbPak_ReadWriteBytes` helper, and that helper performs chunked
`osGbpakReadWrite` transfers across 0x2000-byte bank boundaries. The Tower
wrappers `GbTower_PollPortState`, `GbTower_UpdatePortState`,
`GbTower_StartPortSession`, and `GbTower_InitializePorts` cover the four-port
state machine, insertion checks, save-format validation, and poll-mask setup.
These names establish the hardware access and emulation entry edges; trade/Lab
UI callers remain separate from the Pak transport layer.

## Phase 3.7: audio thread and command dispatcher

`Thread4_CreateThread` passes `func_80035174` directly to `osCreateThread`; its
body initializes a scheduler client, creates the completion queues, and loops
on `Sched_WaitClientQueue` before submitting audio tasks. It is therefore named
`Audio_ThreadEntry`. The resident `0x80021ED8` function is named
`Audio_DispatchCommand`: `Audio_RequestEvent` calls it for changed ids, while
its body maps those ids through the audio state tables and updates command
flags. The mixer/task internals below that dispatcher remain separate audit
targets.

The lifecycle edges are now named as well: `Audio_StopProcessing` is called by
both the scheduler pre-NMI path and `Game_ShutdownAndLoadFragment`, invokes the
audio stop primitive, and clears the Thread4 processing flag;
`Audio_WaitForPendingTasks` is called by the state-4 shutdown path and polls the
completion primitive until the pending audio work drains. These names describe
control-flow roles only; they do not claim ownership of the lower-level RSP
mixer implementation.

`Audio_SetProcessingEnabled` completes the control surface: state 4 calls it
with both boolean values, and `Audio_ThreadEntry` reads the same flag before
submitting work. The name is intentionally limited to the flag transition;
the event IDs and mixer command meanings remain separate.

The thread's task side is now named through its producer as well:
`Audio_InitializeTaskState` is the one-time RSP/task setup, and each scheduler
wake calls `Audio_BuildSchedulerTask`, which obtains the next task from
`Audio_MixerStep` and submits it through `Sched_SubmitTask`. The mixer-step
body advances the audio scheduler, services AI/GB audio buffers, drains task
completion messages, and constructs the resident 0x68-byte task record. This
establishes the mixer entry from the thread's direct call edge without naming
individual command IDs beyond the separately documented request dispatcher.

Two adjacent audio controls are now named from their direct global writes:
`Audio_ResetModeSelector` stores `-1` in `D_80094860`, while
`Audio_EnableModeFlag` stores `1` in `D_80094868`. Their names describe only
those state transitions; the mode values consumed by the larger command
routine remain unresolved.

## Phase 3.8: fragment-79 species dispatch handlers

The 253-entry table at `0x84183D50` is now resolved at the handler level. It
contains one repeated default target plus 99 non-default targets; those targets
are named `BattleAnim_Dispatch_NNN` from their table slots, with repeated slots
recorded in each entry's evidence. This is deliberately a positional naming
batch: the table cardinality and slot selection establish a per-species-style
dispatch surface, but do not by themselves prove the semantic animation for a
handler. The neighboring table is audited separately below.

The neighboring 225-entry table at `0x84184148` has now received the same
positional treatment: one dominant default target and 51 non-default targets
are named `BattleAnim_ModelDispatch_NNN`, with repeated slots retained in the
evidence. These names identify the dispatch surface only; they do not assert
that every slot is a distinct model or animation.

The fragment-67 table at `0x829130A4` is also resolved positionally. Its 53
entries consist of one repeated default handler and 13 non-default handlers at
slots `1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49`; those handlers are
named `BattleAnim_Fragment67Dispatch_NNN`. The regular stride is recorded as
structural evidence, while the exact effect semantics remain a body-level
follow-up.

Three auxiliary fragment-79 tables are now covered without semantic guesses:
the 50-entry table at `0x84185F10`, the 83-entry table at `0x84186004`, and the
9-entry table at `0x84185FDC`. Every entry in these tables points to a distinct
handler, so each target is named `BattleAnim_Table_<table>_<slot>` using the
table address and zero-padded slot. This records stable positional evidence;
the handlers still need body-level analysis before receiving effect-specific
names.

## Phase 3.6: remaining dispatch-table boundaries

The dispatch-table survey was rerun after the subsystem slices. The two largest
resolved tables are in fragment 79 at `0x84183D50` (253 entries) and
`0x84184148` (225 entries); the 83-, 50-, and 9-entry neighbors are now also
covered positionally above. No table-level caller evidence currently
distinguishes the remaining 23-entry and smaller tables from animation/effect
dispatch, so they remain audit targets rather than receiving guessed names.
This preserves the issue #3 rule that table structure is evidence, but not proof
of each callee's behavior.

## Phase 1: the Stadium 1 transfer
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
remaining ~9,900 functions are original reverse engineering.

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

**Assembly-verified.** The renamed tree assembles, links and produces the
byte-identical US ROM (md5 `1561c75d11cedf356a8ddb1a4a5f9d5d`) under
`tools/mac_build_disasm.sh` in the linux/amd64 build container -- verified
after the phase 1 rename (which also caught two pre-existing bugs in the
`a404a06` DMA-helper C translations, fixed in disasm commit `ccae2a1`) and
again after phase 2.

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
