# Fragment 29 callback state

## Accepted native callback batch

| Owner | Role | Body instructions / bytes | Frame | Accepted batch |
| --- | --- | ---: | ---: | --- |
| `func_88005B60` | install callback state and countdown | 71 / 284 | 0x18 | `f9710e6b010b44c19c19f84186066523` |
| `func_88005CC0` | mode-specific payload match | 146 / 584 | none | `da7f6cb1e01f4602aa9c3c31fad3c2f6` |
| `func_88005F08` | tick, complete and free callback data | 36 / 144 | 0x18 | `f8a82f1d6013419ca232db2d426c33eb` |

All are normal native accepts, `link_verified: true`, with an automatic
combined full-ROM gate. Host checks and persistent statistics are enabled.
The final eight zero bytes are preserved natural text alignment, not an
extra padding function or pragma. This source now has four C bodies and no
assembly owners, including its unchanged previous update callback.

The 24-byte record has mode +0, data +4, signed count +8, signed limit +0xA
and no-argument callbacks at +0xC/+0x10/+0x14. Use an actual typed global
declaration, not an externally byte-typed global hidden behind a local cast:
the latter makes the compiler issue a separate high-half address load in
each switch arm. The typed-global companion edit preserves all three already
accepted C bodies in the object. No global storage definition is introduced.

- Initializer label: `f29:callback-divisor:integer-literal`. Keep mode-zero
  reset and mode-21 fixed count 20, and copy count into limit by its real
  halfword read. The default uses `(u32)((f32)func_80001FF0() / 2)`.
  Both `/ 2` and `/ 2.0f` are floating expressions; this IDO frontend keeps
  retail's divide with the integer literal but folds the float literal into
  a reciprocal multiply. Preserve the unsigned conversion sequence, not a
  signed-short conversion or cached frame-rate helper.
- Dispatcher label:
  `f29:callback-global:integer-False:combined-False:assign-True`.
  Keep the count and active-mode guards, zero-initialized result, source case
  order 1..21, separate structurally identical arms, and exact shared groups
  10..13 and 15..19. Recover those groups from table destinations, not guessed
  mode semantics. Payloads deliberately mix signed byte/halfword records,
  word identities and pointer-valued inputs; preserve every access width.
- Completion label: `f29:callbacks-finish:raw-False:guard-False:combined-False`.
  Re-read count after the tick callback; decrement the signed halfword and
  call completion only on zero. Clear active mode after that callback, then
  free the record's current data pointer. Callbacks can mutate the global,
  so do not cache its fields across calls or invent callback-null guards.

## Jump-table prerequisite

The object-local `.rodata` window is exactly ROM 0x16C840..0x16C8A0:
21 entries at `jtbl_88006800` (84 bytes) plus twelve zero bytes. The following
`D_88006860` starts at the exclusive endpoint and remains in the separate
rodata tail. The prior alignment tables end at the start of this window and
are untouched. The YAML changes one boundary into the owner segment and
adds its tail; generated LD only replaces the old tail input with the new.

Extraction uses splat64 0.25.0 and pinned spimdisasm
`fe1338434c99240eb4adca0b7860edc12b847565` (1.35.0.dev0). Normalize native
absolute archive paths back to relative spelling. Retain generated reference
`asm/us/matchings` files in ignored scratch storage rather than letting the
flat Makefile discover them as standalone inputs. Aliases remain identical.

Force a normal rebuild of this object after splitting; an old extracted
object can otherwise lack the newly owned table. The successful still-ASM
full-ROM gate passes before any dispatcher C probe: exact 96-byte object
rodata, three previous C bodies and all four text offsets preserved. The
final C table bytes also equal that assembly-object baseline.

## Final checks

Fresh and twenty-leading-blank controls after formatting/extern cleanup
preserve every accepted section, all original offsets, the previous C update
function and all three C bodies accepted before table migration. All four
linked C spans, the 96-byte table window and entire ROM match retail, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Explicit whole-translation-unit host
syntax checks and forced ordinary object rebuilds pass. Exactly three removed
pragmas have accepted, link-verified gate provenance. Naming has no established
mapping. No scratch tools, compiler changes or verification bypasses land.
