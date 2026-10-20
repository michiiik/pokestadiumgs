# Fragment 61 camera callback

## Accepted: `func_86B00020`, 2026-10-20

The 208-byte callback sets the perspective and places the camera at
`(0, sin(angle) * radius + 400 + centerY, cos(angle) * radius)`, looking
toward `(0, centerY, 0)`. `D_86B0D16C` supplies the angle, `D_86B0D168`
the radius, `D_86B0D170` the center height and `D_86B0D174` the field of
view. When `D_86B17EAC` is zero, the original `func_87C037C0` camera call
with `D_86B17E2C` is preserved.

The actual six-float/`u16` helper signature and the consumed `u16 roll = 0`
value reproduce the original instructions and 56-byte frame without the old
word rewrite or unused padding. The normal runner accepts the callback with
`link_verified: true` and a full-ROM gate; do not candidate-probe it again.

Shared evidence and source-shape limits are recorded in
`docs/regions/fragments/60/fragment60_code.md`. Independent retail links
cover every one of this module's 63 function extents and all 53,568 text
bytes. All frozen-stage, whole-module, collateral, public compiler path,
blank-line, provenance, syntax, regression and final normal-ROM checks pass.
Other owners in this file remain outside this correction.
