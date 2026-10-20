# Six-slot trails and auxiliary particle pools

## Layout evidence

The GS six-slot records begin 2304 bytes into the allocation referenced by
`D_84187DC0`. `func_84168540` and `func_84168680` independently add that base
offset and advance by 884 bytes. Each record has twenty 36-byte nodes at
offset 164 and a vertex pointer at offset 136. The existing
`S1_unk_D_843C3508` view reproduces those GS offsets; its declarations are
moved before the lifecycle functions without changing any game-object
fingerprint. Known, prepared, twenty-leading-blank and target-layout controls
verify that declaration-only preparation.

The allocation referenced by `D_84187E40` holds two 484-byte auxiliary
records. Each begins with an active halfword and has twenty 24-byte nodes at
offset 4. A node holds active/age/lifetime halfwords, a scale float and a
three-float position. The remaining halfword at offset 2 is still unknown.
Target-compiler size and offset assertions validate both views.

## Accepted lifecycle batch (2026-10-20)

Five original assembly owners are replaced by genuine C:

| Original owner | Name | Body bytes |
| --- | --- | ---: |
| `func_84168540` | `BattleAnim_SixSlotTrail_ResetPool` | 320 |
| `func_84168680` | `BattleAnim_SixSlotTrail_Spawn` | 1152 |
| `func_84169BA8` | `AuxiliaryEffect_Alloc` | 204 |
| `func_84169C74` | `AuxiliaryEffect_Spawn` | 328 |
| `func_84169DBC` | `AuxiliaryEffect_Update` | 348 |

Reset clears both GS lifecycle halfwords and initializes six records and
their twenty nodes. It reads the existing packed five-byte default at
`D_84187DC4`; it does not emit a duplicate initializer into another section.
Spawn initializes the first free trail, both texture-scroll descriptions,
combine-mode descriptions and twenty position/velocity nodes. Its pool lookup
follows the two real vector initializations; that statement order reproduces
the retail load/store schedule without line directives or compiler patches.

Auxiliary allocation initializes the first free record and returns its signed
16-bit index, or -1. Index-based traversal derives the selected-record pointer
inside the loop and reproduces retail's distinct traversal/selected pointers;
cached base and explicit alias variants do not. Spawn activates the first
free node in an active record. Update increments active-node ages, expires
them after their stored lifetime, and subtracts 0.75 from their vertical
position, including the expiration frame. Corresponding Stadium 1 lifecycle
functions and the GS producer/consumer accesses justify the names. Original
address aliases are retained for all five functions.

All five have runner `accepted` provenance and link-verified object matches,
followed by normal full-ROM gates. The first gate accepted trail reset,
auxiliary spawn and auxiliary update together; two later gates accepted
trail spawn and auxiliary allocation.
Every first successful callback froze the complete changed translation unit
and four collateral units before returning. Receipts were reread and every
object externally SHA-256 checked before further compilation.

The final reviewed gate freezes fourteen complete translation units. All
thirteen collateral fingerprints equal the prior verified baseline. An
independent unmodified linker reproduces all 7200 retail text bytes and all
eighteen existing function starts/extents at original, prepared, each
acceptance, named and extern-cleanup stages. No allocated data or rodata
sections are added. Canonical/named, native/public-wrapper, twenty-leading-
blank and target-layout controls pass. Full-ROM MD5 remains
`1561c75d11cedf356a8ddb1a4a5f9d5d`.

All 427 source syntax checks and 76 native tool tests pass. The clean public
clone passes 77 tool tests with fourteen environment-dependent skips.
Provenance covers exactly five actual replacements; four pragmas relocated
past the moved type declarations remain unchanged, and their assembly words
are independently checked against retail. Claims and alias checks pass.

## Auxiliary drawing and constant-pool layout (2026-10-20)

`func_84169F18` is now `AuxiliaryEffect_DrawOne` (312 bytes), and
`func_8416A050` is `AuxiliaryEffect_Draw` (240 bytes). DrawOne applies a
sine-scaled node size, translation and the supplied fixed billboard matrix,
then emits the matrix, primitive-color and static display-list commands.
Draw visits twenty active nodes in the selected auxiliary record. It derives
a float matrix from the shared render-state matrix at offset 100, converts
it to a real fixed `Mtx`, and passes that matrix to DrawOne.

The allocator retains its actual `u32(s32)` interface and explicitly converts
the returned address to `Mtx *`. The float matrix is a real `f32[4][4]` and
the conversion destination is a fixed `Mtx`. A consumed `billboard_matrix`
pointer fixes the float matrix's stack location while preserving retail's
temporary register sequence; a cached active flag and node-count variants do
not. Neither accepted body adds unused storage, fake matrix types, padding,
forced registers, manual unrolling or binary/relocation rewrites.

The module owns the 48-byte pool at ROM 0x3FC1B0..0x3FC1E0, VMA
0x8418C920..0x8418C950. The YAML now assigns that exact range as its per-file
`.rodata` subsegment and leaves the following shared pool at 0x3FC1E0. The
reviewed linker keeps all earlier contributions in place and advances only
that following pool input. Isolated baseline/migrated, known and leading-
blank controls reproduce all eighteen extents, all 7200 retail text bytes
and all 48 pool bytes before adoption. Scoped generated extraction preserves
all C sources and the reviewed linker; the superseded generated source is
archived privately. The normal layout-only ROM gate passes before probing.

Both draw owners have runner acceptance and link-verified matches, followed
by normal full-ROM gates. Each first-success callback freezes the complete
changed translation unit and four collateral objects, and every receipt and
external SHA-256 is rechecked before further compilation. A fresh final gate
freezes fourteen whole objects. All thirteen collateral game fingerprints
remain equal to the earlier lifecycle baseline despite the layout rebuild.

Independent unmodified-linker verification covers original, layout-only,
both accepted stages and named/cleanup objects, including all eighteen
function extents, all 7200 text bytes and the exact 48-byte pool. Canonical/
named, native/public-wrapper, twenty-leading-blank and target-layout controls
pass. Full-ROM MD5 remains `1561c75d11cedf356a8ddb1a4a5f9d5d`.

### Update requeues

`func_84168CA4`: **requeue**. The donor-shaped 924-byte candidate has an
isolated relocation-masked hit but calls the wrong GS anchor helper; the
full-ROM gate correctly rejects it. Retail calls `func_84109780`, whose
existing interface accepts an address as `s32`. Correct-interface candidates
use `(s32)&anchor` and currently produce 856-byte bodies with different
allocation and division-check scheduling. Do not install the wrong helper,
reinterpret a relocation mask as acceptance, or introduce an invented
pointer prototype. Next investigate a genuinely consumed address carrier
and its lifetime with the actual helper interface. Retail also reads a phase
local without initializing it; this is an original bug, not permission to
invent a phase initialization.

`func_84169040`: **requeue**. GS uses a completion-triggered fifty-tick
deadline and a twenty-tick fade, rather than the donor's per-record seventy-
tick threshold. Real pool-base and counter initialization variants produce
the correct 468-byte size, but allocation and prologue scheduling still
differ. Getter return type remains the actual `u32`; signed consumed flags,
named active-state constants and earlier base initialization do not close
the residual. Next inspect the retained allocation/lifetime diagnostics
before repeating that initialization family.

## Remaining owners and inherited work

Five owners remain assembly: `func_84168B00`, `func_84168C18`,
`func_84168CA4`, `func_84169040` and `func_84169618`. Their constant-pool
layout prerequisite is now verified; their function bodies still require
normal runner acceptance and full-ROM verification.

The existing texture loader's unused locals and the existing empty padding
function are inherited and unresolved. They are unchanged and are not counted
among the five new matches. No unused locals, padding, forced registers,
manual unrolling, instruction/HEX/relocation rewrites or tool changes are
introduced by this batch. Private campaigns and generated coverage are not
part of the change.
