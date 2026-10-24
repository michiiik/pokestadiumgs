# Fragment 45 state four controller branches

`func_8AB06718` has a matching C implementation (292 instruction bytes).
Argument zero copies archive 57 entry 361 into the 256-byte banner buffer,
enables the banner, initializes the highlight records at `D_8AB168D8` and
`D_8AB16980` from their respective nodes, and enables `D_8AB168D0`.

Argument one animates the first highlight and reads the controller halfword
at offset eight through `D_80087200`. Mask `0x8000` takes priority: it hides
`D_8AB168D0`, enters `func_8AB0683C(0)`, and forwards command 194. Otherwise,
mask `0x4000` calls `func_8AB05A00`, enters `func_8AB066B4(0)`, and forwards
command three. Other paths return state four. The controller halfword's
pressed/held interpretation is not established by this handler.

The initializer `func_8AB05B88` binds the two nodes and highlight records.
`func_8AC06400` in `src/fragments/43/fragment43_1E5A10.c` initializes scales
and node centers; `func_8AC063AC` updates the scales from the sine table.
The update dispatcher `func_8AB062C4` passes one, the draw dispatcher
`func_8AB064C4` passes two, and `func_8AB06650` enters this handler with zero.
`func_8AB05A00` fills configuration selection bytes with all-ones values;
`func_8AB066B4(0)` starts the existing fade from transparent.

The command wrapper `func_8AB00B78` in
`src/fragments/45/fragment45_2251A0.c` accepts one signed word and returns
void. This module's existing declaration now follows that contract; its
callers ignore the result. These behavior claims follow from source and
original disassembly inspection, preserving unknown symbol names.

Verification targets master `6f05b8a0667cf854cded70e243464530106bd465` plus
this change. `make -W src/fragments/45/fragment45_22AB80.c -j4 VERSION=us rom`
forces the normal syntax check and source compilation before linking the
complete US ROM. It passes with `build/pokestadiumgs-us.z64: OK`, and `cmp`
confirms byte-for-byte equality with retail. MD5 is
`1561c75d11cedf356a8ddb1a4a5f9d5d`. The original 32-byte frame is preserved
without dummy storage, forced registers, or instruction rewrites.

## State 12 banner and panel delay

`func_8AB073F4` has a matching C implementation (324 instruction bytes).
Argument zero resets `D_8AB16A2C`, enables the banner at `D_8AB11D00`,
calls the existing panel-visibility helper, and copies archive 57 entry 389
into the banner buffer. It clears flag mask one on `D_8AB167AC` and the
four nodes referenced by `D_8AB12678`, then clears flag mask two on
`D_8AB16968`. It emits event 65550 with zero parameters and calls
`func_800225C4(40)`.

Argument one increments the signed-halfword counter and calls
`TextHighlight_AnimateScales`. At counter 61 or above it enters
`func_8AB07538(0)`; other paths return state 12. The update and draw
dispatchers `func_8AB062C4` and `func_8AB064C4` pass one and two respectively.
`func_8AB05B88` initializes the referenced nodes. The visibility, highlight,
and event helpers are defined in `src/fragments/45/fragment45_2251A0.c`;
`func_800225C4` is in `src/229E0.c`. These claims follow from source and
original assembly inspection without assigning a broader meaning to flag
mask two. IDO unrolls the ordinary four-node loop into the retail stores.

Verification targets master `81a6f93f05a34a99eedc2717bbede0491a5cc3b7` plus
this change. The normal syntax-enabled forced source compile and full
`make -W src/fragments/45/fragment45_22AB80.c -j4 VERSION=us rom` pass with
`build/pokestadiumgs-us.z64: OK`. `cmp` confirms byte-for-byte equality
with retail; MD5 is `1561c75d11cedf356a8ddb1a4a5f9d5d`. The original
32-byte frame is preserved without dummy storage or instruction rewrites.
