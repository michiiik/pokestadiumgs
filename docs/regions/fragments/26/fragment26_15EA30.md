# Fragment 26 particle callbacks

## 2026-10-13: func_81003768 accepted

- On event 2, set the vector at node + 0x30 to the default scale in all three components, then apply the default RGBA bytes. Return zero for all events.
- Three eight-candidate hypothesis batches compared aggregate, array, and separate-field spellings. Aggregate/array forms materialized the base before the float load (best normalized 0.9000, raw 0.6333). Separate field symbols produced relocation-masked instruction matches.
- `D_80128C54` occupies 12 bytes at linked address 0x80128C54. The original accesses scale at +4 and RGBA at +8. Aliases `D_80128C58` and `D_80128C5C` preserve those fields without changing storage.
- Runner acceptance: `particle-callback:field-symbols:direct`, sequential full-ROM gate, retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. `link_verified=false` reflects changed relocation symbol spellings; it is not the acceptance evidence. No explicit padding was needed after linking. Naming tool found no known name.
- Next owner: `func_81003680`. Its event-2 path derives an animation index from an unsigned frame remainder, updates two signed halfword coordinates using global offsets 0x1E/0x20, and copies the first three interpolated color bytes. Reconstruct the existing global overlay and helper return ABI before probing.
