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
