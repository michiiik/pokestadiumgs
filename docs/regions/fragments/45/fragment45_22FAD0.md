# Fragment 45 countdown transition

`func_8AB0B54C` has a matching C implementation (148 instruction bytes).
It receives the current state and returns it unless the signed-halfword
countdown at `D_8AB16F6C` has expired. At zero or below, it clamps the
countdown to zero, obtains the next state from `func_8AB0CA58(0)`, clears
`D_8AB16F60`, and clears configuration byte 15 through `D_8AB11D0C`.
The broader role of `D_8AB16F60` remains unresolved.

At positive countdown values below four, it plays sound 52992 only when
the value differs from `D_8AB16F7C`. Every path then refreshes that history
halfword from the current countdown. Direct global accesses preserve the
retail value reuse and reloads around calls, including the unchanged-state
return after the sound call. The sound declaration follows the
`void Audio_PlayDefaultSound(u16)` definition in `src/229E0.c`; the original
address-keyed callee name is an existing linker alias.

The caller `func_8AB0B5E0` decrements this countdown when its clock word is
divisible by `func_80001FF0() / 2`, clamps a negative result to zero, and
passes its state through this helper. `func_8AB0B7CC` initializes the
countdown to 100. These producers and consumers establish the timer and
history roles without assigning meanings to the remaining state words.

Verification targets master `fd71b9d02061b8b3583267ad0317e0b6d1bde375` plus
this change. The normal host syntax check and forced source compilation
via `make -W src/fragments/45/fragment45_22FAD0.c -j4 VERSION=us rom` pass.
The complete US ROM passes checksum verification and compares byte-for-byte
with the retail ROM; MD5 is `1561c75d11cedf356a8ddb1a4a5f9d5d`.
The implementation preserves the original 24-byte frame without dummy
storage, forced registers, or instruction rewrites. Behavior descriptions
come from source and disassembly inspection.

## Prompt text reveal

`func_8AB0BE4C` has a matching C implementation (292 instruction bytes).
It refreshes the 256-byte buffer at `D_8AB16D10` using the banner node's
archive and entry halfwords at offsets 48 and 50, then advances through
`D_8AB16F82` encoded characters. Newline and bytes below `0x80` advance
one byte; other leading bytes advance two. Reaching the string terminator
sets `D_8AB16F84` and returns zero. Otherwise it terminates the visible
prefix and returns one.

On even `D_8AB1268C` values, it compares the final visible character with
the string referenced by `D_8AB112BC`, emits event 65549 for equality or
65548 otherwise, and increments the reveal count. The original data pointer
targets `D_8AB11A80`, whose ROM bytes are `0A 00`: a newline string.
The caller `func_8AB0C414` initializes the count to one and the completion
flag to zero before its update path calls the reveal helper. A positive
count supplies the final-character pointer used after the loop.

The copy helper is `func_8004C8A0` in `src/4CC20.c`; `HAL_Strcmp` in
`src/C180.c` returns zero for equal terminated strings. The event wrapper
is in `src/fragments/45/fragment45_2251A0.c`. The existing
`TextMode8_RevealPromptText` in `src/fragments/45/fragment45_2324B0.c` uses
the same loop with its own buffer, counters, and newline pointer. These
claims follow from source, original assembly, and the decoded ROM data.

Verification targets master `4d161470b602233a867ec15fe90e93adcb8faa4a` plus
this change. The normal syntax-enabled forced compilation and complete
`VERSION=us` ROM build pass with `build/pokestadiumgs-us.z64: OK`.
`cmp` confirms byte-for-byte equality with retail, whose MD5 remains
`1561c75d11cedf356a8ddb1a4a5f9d5d`. The original 40-byte frame is preserved
without dummy storage, forced registers, or instruction rewrites.
