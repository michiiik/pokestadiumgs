# Fragment 29 D-pad repeat

`func_88004EC0`: accepted native batch
`df4b8a8e06054bfea676070de67b51a8`, label
`f29:input-return-expression:all-False:cast-False:sum-False`.
73 body instructions / 292 bytes, frameless; twelve natural trailing zero
bytes preserve the 304-byte original owner span. Normal probe,
`link_verified: true`, automatic combined full-ROM gate, one gate run.

Read pressed buttons at controller +8 and held buttons at +6. Preserve
priority 0x200, 0x100, 0x800, 0x400, ten-frame initial delay, signed-byte
decrement/test, saturation at zero and two-frame held repeat. The existing
initializer's unsigned extern hid the signed countdown reads. Retype that
extern in the same accepted companion transaction; the initializer's sixteen
bytes remain unchanged.

Keep word-sized cached buttons and the controller pointer. For the first
held-button arm, `return (D_8800EF20 = 2, 0x200);` reproduces the retail
ordering of return-value and repeat-delay constants. Splitting the store
and return into separate statements leaves those two immediate loads swapped.
Shared-return, preseeded-result, separate-mask, pointer-reload and narrow
mask variants do not resolve that schedule. The comma expression is a real
sequenced store followed by the returned flag, not a diagnostic fake.

Fresh and twenty-leading-blank builds after formatting and duplicate cleanup
preserve every accepted object section, both function offsets and the
existing initializer. Object text stays 320 bytes with twelve final zero
bytes; no padding pragma/helper is installed. Both linked C spans and the
whole ROM match retail, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
Exactly one removed pragma has accepted, link-verified gate provenance.
Naming has no established mapping. This source file has no assembly owners.
