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

## Remaining owners and inherited work

Seven owners remain assembly: `func_84168B00`, `func_84168C18`,
`func_84168CA4`, `func_84169040`, `func_84169618`, `func_84169F18` and
`func_8416A050`. The shared rodata pool begins at ROM 0x3FC1B0; constant-using
owners need an independently verified per-file layout before C literal pools
can replace that assembly. Do not infer layout acceptance from the lifecycle
functions, which add no allocated non-text sections.

The existing texture loader's unused locals and the existing empty padding
function are inherited and unresolved. They are unchanged and are not counted
among the five new matches. No unused locals, padding, forced registers,
manual unrolling, instruction/HEX/relocation rewrites or tool changes are
introduced by this batch. Private campaigns and generated coverage are not
part of the change.
