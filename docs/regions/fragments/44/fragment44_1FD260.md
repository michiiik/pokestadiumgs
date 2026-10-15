# Fragment 44 record collection and menu callbacks

## 2026-10-16 — category-filtered collection accepted

Solo native macOS, without agents or containers. `func_8AF125D0` becomes
matching C: **83 words / 332 bytes**, with its original **0x38-byte frame**.
This file advances from **14 C / 24 function ASM to 15 C / 23 function ASM**,
out of 38 originals. No new callable helper or data allocation.

Acceptance batch: `523529ea9b704e62a730680d10f4312d`, candidate
`f44-menu-kind-filter-indexed:narrow-False:less-False:global-True`.
The normal runner accepted it after **one successful sequential full-ROM
gate**. The isolated probe was relocation-masked, not `link_verified`:
the compiler expresses the input endpoint as the input-array symbol plus
250 instead of the separately named marker. A separate strict canonical
link resolves every undefined name from the normal ELF and proves the
complete containing text, including **all 38 original functions**, identical
to the assembly-backed baseline. No unresolved-symbol suppression is used.

### Source mechanism

Use a real `s32` index into the global 250-byte input array, with
`index != 250`. IDO strength-reduces this into the original pointer walk;
keeping an explicit input/end pointer pair produced the same operations but
the wrong saved-register allocation and pointer-add order. Preserve the two
real early-continue guards after mapping the ID: first exclude ID 0xA5,
then reject nonmatching categories. Moving those tests before the mapping
calls would change the original call behavior.

The signed halfword ID and separate unsigned halfword snapshot retain the
original call-argument and stored-ID carriers. All locals have real uses;
there are no empty conditions, artificial arrays or forced registers.

The input's extern becomes `u8[250]`, supported by the accepted collector's
250-entry limit and the original endpoint-address difference of 0xFA.
The existing mask filter now takes its start pointer directly from that
array. These are declarations of existing storage, not additional data.
The candidate, array declaration and accepted-caller adjustment were probed
and installed in the same transaction.

After formatting and removing redundant externs, fresh and twenty-leading-
blank builds reproduce the frozen accepted object's complete sections,
layout and every relocation row. All 38 original spans and the 37 untouched
function bodies are preserved. Forced normal ROM comparison passes, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`; edited-TU host syntax passes with four
pre-existing pointer warnings; all 46 native tooling tests pass. The naming
tool finds no evidence-backed public mapping, so the address name stays.

The adjacent section builder remains a **requeue**: its 296-byte leader has
the original 74-operation sequence but swapped input/output saved registers.
A real scan/emission cursor split fixes its first 33 words but adds a move
and grows it to 300 bytes. Neither is accepted. The renderer and callback
residuals below also remain unresolved. Scratch generators, traces, compiler
binaries, objects and ROMs remain local and are not part of the PR.

## 2026-10-16 — three native matching routines accepted

Solo native macOS, without agents or containers. Three existing assembly
owners become C: **134 words / 536 bytes**. This file advances from
**11 C / 27 function ASM to 14 C / 24 function ASM**, out of 38 originals.
No new callable helper, data allocation, layout change or compiler patch.

| Owner | Behavior | Bytes | Frame | Full-ROM acceptance batch |
| --- | --- | ---: | ---: | --- |
| `func_8AF0F1A0` | Collect indexed record positions | 128 | 0x28 | `90ffb797fdef41b4aa13cbc6e3d83be6` |
| `func_8AF0F220` | Recursively collect three-byte evolution entries | 204 | 0x30 | `159a50c71150453d8b73c4949bc2fe42` |
| `func_8AF1271C` | Filter IDs into four-byte output records, then pad | 204 | 0x30 | `6885a4aac1c442129ddb323bbbc9db1f` |

All three are **link-verified** normal-runner accepts, each passing one
combined full-ROM gate. No provenance or host-syntax bypass is used. The
naming tool finds no existing evidence-backed mappings for these owners;
their address names remain rather than introducing speculative public names.

### Source mechanisms

The position callback must declare its signed index before its two-halfword
position array. The original offset/coordinate additions, not their
commuted spellings, give the expected temporary allocation. Preserve the
unconditional record-index snapshot and the mode-zero/mode-one guard.

The recursive collector follows three-byte entries until their first byte
is zero. Preserve the incremented signed global index snapshot, ID store,
three-byte aggregate copy and recursive call before advancing the input.
An explicit infinite loop with a top-of-loop exit matches the original
branch layout; an ordinary `while` rotates the load/exit and is one word
longer. The aggregate has three actual byte fields and no padding member.

The filter needs a real word-wide ID, not a byte local: narrowing only at
the verified byte-argument call preserves the original normalization. A
separate destination carrier fixes its saved-register allocation. Keep the
prologue on one logical source line and both endpoint assignments on the
same physical line; backslash splices make the prologue readable without
changing IDO's measured instruction schedule. Advance the destination
before incrementing the signed-halfword count. Every local has a real use.
The callee declarations retain the actual `u8(u8)` and `s16(s16)` contracts;
no return-type mismatch is used to manufacture instructions.

After formatting and removal of redundant/unused externs, fresh and
twenty-leading-blank builds reproduce the frozen accepted object's entire
text/rodata/data/bss, section layout and every relocation row. All **38
original function spans** and **35 untouched bodies** are preserved. The
forced native full-ROM comparison passes, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. The edited TU passes host syntax with
four pre-existing pointer-type warnings; all **46 tooling tests** pass.
Scratch generators, controls, objects, compiler binaries and ROMs stay local.

### Unresolved adjacent owners

- `func_8AF10570`, `func_8AF1060C`, `func_8AF10784`: **requeue**, 32 cells
  each. Ordinary signed-coordinate variants have exact opcode sequences,
  original sizes/frames, but place the position array at sp+0x2C rather
  than sp+0x24. Declaration order, real saved-record carriers, case-local
  arrays and an all-used coordinate aggregate do not close this. The
  word-coordinate aggregate reaches sp+0x24 but adds memory traffic;
  narrowing its members does not repair that. Next investigate the actual
  automatic-object lifetime/stack-home mechanism, not unused locals or
  artificial padding.
- `func_8AF106A8`: **requeue**, eight initial cells. Best has the correct
  220-byte size, normalized 1.0 / raw .9273, but the same position-array
  offset discrepancy. Preserve its real conditional drawing calls and
  signed y snapshot. It is not accepted.
- `func_8AF12410`: **requeue**, 24 cells. It fills only the first two bytes
  of each four-byte record with 0xFF, padding a positive signed remainder
  to a multiple of four. Natural loop bounds, parameter reuse and explicit
  signed normalization expose the original unrolled shape, but no cell
  matches. The 152-byte leader has normalized .9474 / raw .2632; matching
  size alone is weak evidence. Next resolve the signed remainder/bound
  carriers and real parameter home, not hand-written unrolling.

A stock-driver comparison preserves all eleven pre-existing C controls
under 7.1. Stock 5.3 changes two of them and worsens both the callback and
padding leaders; this does not justify changing this file's compiler.
Leading-blank controls are stable. This is a bounded negative, not proof
of an impossible source shape or a broken compiler.
