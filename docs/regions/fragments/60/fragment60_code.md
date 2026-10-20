# Fragment 60 camera callback

## Accepted: `func_86A00020`, 2026-10-20

The 188-byte callback sets the perspective, then positions the camera at
`(0, sin(angle) * radius + 400 + centerY, cos(angle) * radius + centerZ)`
looking toward `(0, centerY, centerZ)`. `D_86A0D4DC` supplies the angle,
`D_86A0D4D8` the radius, `D_86A0D4E0`/`D_86A0D4E4` the center and
`D_86A0D4E8` the field of view.

The shared helper's actual definition in `src/229E0.c`, `func_80038E14`,
takes six `f32` coordinates followed by a `u16` roll angle. It stores the
eye/target coordinates and uses the roll angle's high bits to index the
trigonometric tables for the up vector. The callback now declares that
actual contract and passes a real `u16 roll = 0` local as the final argument.
The first coordinate is the ordinary integer literal `0`, converted to
`f32` by the prototype. No fake declaration, unused padding local or
instruction rewrite is needed to obtain the original 56-byte frame and
zero-argument materialization.

The normal runner accepts this source with `link_verified: true`, followed
by the full-ROM gate. Stop candidate-probing this owner after acceptance.
Real scalar/vector experiments without the roll local did not match; unused
padding is not a substitute for the consumed roll-angle value. Runtime
aggregate initializers are rejected by this IDO frontend and establish no
code-generation result.

The paired fragment-61 callback uses the same mechanism. Four successful
stages (assembly baseline, each individual acceptance and declaration cleanup)
freeze seven complete modules inside the successful gate callback, reread
receipts and externally hash every object before returning and before later
compilation. Every allocated-object fingerprint equals its original baseline.
Independent retail-address links cover all 69 function extents and 54,448
text bytes in this module and all 63 extents/53,568 bytes in fragment 61.
Native/public compiler paths, twenty-leading-blank controls, accepted-attempt
provenance, all-source host syntax and all 76 native tests pass. The final
normal ROM gate retains MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.

Only this callback and its helper declaration change in the source file.
Unrelated assembly owners and existing C remain untouched. No private helper
or coverage changes are part of the public correction.
