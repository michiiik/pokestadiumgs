# Lab PC move and evolution queries

## Native matching evidence (2026-10-19)

`func_88902E8C` (`LabPC_FindLevelUpEvolution`) walks three-byte evolution
records. It returns the target species for level, friendship, and relative
Attack/Defense conditions, with the held-item and cartridge-mode guards from
the original assembly. The optional clock path selects species 196 or 197.

The clock reader's first output is a `u16` day count, followed by byte-sized
hour, minute, and second outputs. `func_8005F190` loads/stores the first output
with `lhu`/`sh`, but advances seconds, minutes, and hours with `lbu`/`sb`.
Four byte locals give the wrong stack offsets; a real halfword day count
reproduces the original 56-byte frame and all clock-output addresses.

`func_88902E4C` initializes a level-up move cursor and returns the result of
`func_88902CF0`. The stat-animation completion callback tests that result.
Its former `void` declaration discarded an observable return contract; the
explicit return preserves the complete translation-unit game fingerprint.

## Requeue: colored move-name formatter (`func_88902C3C`)

The best source has the original 180-byte instruction sequence and 48-byte
frame. Its sole remaining residual is a caller-save home: the live move
value is saved/reloaded at stack offset 32, whereas retail uses offset 36.
The four affected instructions occur at function offsets 44, 48, 72, and 76.
The best raw similarity is 0.9111; normalized 1.0 is not acceptance.

`func_88000510` returns the actual three-byte RGB struct defined in
`src/fragments/29/fragment29_166060.c`; the hidden result address is passed
in the first argument register. The original format string is
`<COL1,PUSH,%d,%d,%d,255>%s<COL1,POP>`. Move 252 uses the special-name lookup;
other moves use the move-name and move-type APIs.

Forty source variants tested declaration order, narrow versus word move
types, direct type expressions, real selected-move caches, struct-result
initialization, and name scope. Caches either retain the same residual or
change the frame/argument loads; do not repeat those families unchanged.
Next action: inspect caller-save/home allocation for the three-byte struct
result and the retained byte parameter using a known-matching control before
new compiler diagnostics. Do not add dummy locals, widen the RGB object, or
introduce artificial padding to occupy the missing home. The owner remains
assembly; no candidate from this search is accepted.
