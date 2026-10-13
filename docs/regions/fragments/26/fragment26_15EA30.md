# Fragment 26 particle callbacks

## 2026-10-13: func_81003768 accepted

- On event 2, set the vector at node + 0x30 to the default scale in all three components, then apply the default RGBA bytes. Return zero for all events.
- Three eight-candidate hypothesis batches compared aggregate, array, and separate-field spellings. Aggregate/array forms materialized the base before the float load (best normalized 0.9000, raw 0.6333). Separate field symbols produced relocation-masked instruction matches.
- `D_80128C54` occupies 12 bytes at linked address 0x80128C54. The original accesses scale at +4 and RGBA at +8. Aliases `D_80128C58` and `D_80128C5C` preserve those fields without changing storage.
- Runner acceptance: `particle-callback:field-symbols:direct`, sequential full-ROM gate, retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. `link_verified=false` reflects changed relocation symbol spellings; it is not the acceptance evidence. No explicit padding was needed after linking. Naming tool found no known name.

## 2026-10-13: func_81003680 accepted

- Event 2 derives an animation index from an unsigned frame remainder, updates signed halfword coordinates from global offsets 0x1E/0x20, and copies three interpolated color bytes. The helper writes four bytes to the stack buffer and returns its address.
- Three eight-candidate batches varied buffer extent, scope/declaration order, and carrier/frame layout. A 12-byte buffer with an explicit index initially reached raw 0.9808, with only `addiu a0,sp,44` versus expected `addiu a0,sp,28` different.
- Winner: `particle-animation:event-carrier:pad12:function`. Reuse the event formal for the index; declare 12 bytes of verified frame padding before the global/settings/color pointers and four-byte buffer. This preserves the original 0x38 frame, buffer at sp+0x1C, settings spill at sp+0x24, and global spill at sp+0x28.
- `link_verified=true`; the probe-only invocation auto-gated and accepted the full ROM at retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. Two installation attempts failed before gating because a host-copied file retained host ownership in the capability-restricted container; recreating the private container copy resolved it. These were infrastructure failures, not source rejections.
- Naming tool found no known name. Next owner: `func_8100352C`, the neighboring event callback. Preserve the accepted settings/node overlays as ABI hints and inspect its assembly before drafting.
