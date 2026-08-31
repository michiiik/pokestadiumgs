# Region notes -- disasm/src/fragments/79/fragment79_372DE0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 17 accepted func_8410413C (2026-08-31)

accepted; exact Stadium 1 transfer spelling for ParticleGfx_BuildBillboardRotatedMatrixYScaled matched after substituting the file-local S1_MtxF type for S1 MtxF. Keep f32 temp_fv0 = SINS(arg4) then temp_fv1 = COSS(arg4); preserve the matrix expression and store order. Probe was exact with link_verified=true; full make -C disasm COMPARE=1 gate passed checksum 1561c75d11cedf356a8ddb1a4a5f9d5d. One candidate variant, prior_attempts=0 at selection.

## Wave 17 accepted func_84103FF0 (2026-08-31)

accepted; exact Stadium 1 ParticleGfx_BuildBillboardRotatedMatrix spelling matched with file-local S1_MtxF and direct D_80087E50/D_80088E50 array expressions because SINS/COSS macros occur later in this GS source. Link-verified probe and full COMPARE=1 gate passed checksum 1561c75d11cedf356a8ddb1a4a5f9d5d. The first macro-name attempt compiled as implicit calls (0.7368 normalized / 0.0737 raw, expected 332 vs actual 380, first diff expected lhu v0,0x1A(sp), actual addiu sp,-0x20); do not repeat without hoisting macros. Bootstrap required VENV and PYTHON pointing at the repository-root .venv because disasm/.venv lacks splat.

## Wave 17 accepted func_841043AC (2026-08-31)

accepted; exact Stadium 1-near ParticleGfx_PushTransformMatrix shape using S1_MtxF sp28 and exact same-file prototypes for func_84103A3C and func_841037A0. First variant probe matched with link_verified=true; full COMPARE=1 gate passed checksum 1561c75d11cedf356a8ddb1a4a5f9d5d. name_decompiled plan had no mapped rename for this ambiguous exact twin, so func_ name was preserved.

## Wave 17 func_8410358C requeue (2026-08-31)

requeue; prior_attempts=0 at selection. Exact S1 BattleAnim_ResetAssetTable body adjusted to the GS 520-pointer table reached normalized 1.0000/raw 0.8500 at exact 80 bytes but immediate/relocation plus scheduling drift: first relocation diff expected addiu v1,v1,%lo(D_8418D240) (addend 0), actual addiu v1,v1,2080 from D_8418CA20+0x820; later expected stores -16,-12,-8 then bne with -4 delay, actual schedules -12,-8,-4 then bne with -16 delay. Direct four-store pointer/end forms were 0.4000/0.3333; simple pointer end 0.6000/0.4667; index/address end 0.8000/0.5500. Invalid conflicting D_8418D240 declaration attempts were preflight errors and do not count. Next action: retain the compiler-unrolled constant-count S1 loop while expressing the terminal relocation against D_8418D240 directly, then repair the four-store delay-slot schedule; likely requires a correct table/end declaration or linker-visible alias model rather than generic pointer loops.

## Wave 17 accepted func_84104428 and func_841044A4 (2026-08-31)

accepted together in one combined gate. Both use S1_MtxF sp28, pass S1_Vec3f/S1_Vec3s by value to the exact transform constructor, then call func_841037A0. func_84104428 calls func_84103BCC with one f32 and kept its ambiguous func_ name; func_841044A4 calls func_84103D2C with two f32 and was evidence-renamed ParticleGfx_PushTransformMatrixXYScaled. Both first variants were link-verified exact probe hits; combined full COMPARE=1 and post-name COMPARE=1 passed checksum 1561c75d11cedf356a8ddb1a4a5f9d5d.

## Wave 17 func_841035DC requeue (2026-08-31)

requeue; prior_attempts=0 at selection, 7 valid variants across raw indexed parser, pointer/postincrement, explicit loop-carried byte, declaration-order, and register-qualified lifetime models. Best normalized/raw 0.9231/0.6154, operand_or_scheduling_drift, expected 100 bytes vs actual 104; stable first diff offset 0x10/17: expected lui v1,%hi(D_84182A60), actual lui v0,%hi(D_84182A60). Expected keeps source in v1 and returned counter in v0, but all indexed models allocate source v0/counter v1 and add a final move v0,v1; explicit value lowers raw to 0.4615 without changing the fingerprint. Pointer/destination model was 0.6800/0.3200. Next action: materially different ABI/lifetime model that makes the counter the return-register live range from entry and source v1, likely reconstructing the original table record type or using a result expression tied directly to v0; do not repeat declaration order, explicit byte, or register qualifiers.
