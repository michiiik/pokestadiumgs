# Porting status

Last updated: 2026-08-06

## Completed

- Verified the supplied 64 MiB US ROM after converting its V64 byte order to
  canonical Z64.
- Confirmed MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`, matching
  `pret/pokestadiumgs`.
- Added `pret/pokestadiumgs` as the game-specific decompilation source.
- Added a distinct Android ARM64 probe package,
  `com.pokemonstadium2recomp.probe`.
- Built `pokestadiumgs-us.elf` from a clean Unix-native decomp checkout on the
  Mac Mini. The rebuilt ROM is byte-identical to the verified input.
- Added an N64Recomp config for all 88 relocatable fragment sections.
- Generated 33,529 functions with pinned engine revision
  `2b949c5c3f1c41dd76023e7626a6302a4a262a8a`.
- Built, installed, and launched the ARM64 probe on the AYN Thor. Logcat
  confirmed the native JNI call returned success.
- Kept ROMs, generated recompilation output, APKs, and machine-local Android
  configuration out of version control.

## Current boundary

The Android probe is not the game. The decompilation and first recompilation
passes are complete, but a bootable port still requires game-specific engine
and runtime work:

1. Resolve the pinned engine diagnostics that currently emit runtime-abort
   paths: the jump table at `0x800A5318`, `scd`, `movz`, the static entry at
   `0x8416CA04`, and two failed analysis regions.
2. Reduce or restructure the aggressive static-entry generation. The current
   pass emits about 5.3 GiB across 1,451 generated files because interior
   static entries duplicate large function bodies; compiling that output is
   not a practical runtime baseline.
3. Validate the fragment relocation-pair warnings rather than assuming the
   generated addresses are safe.
4. Port only reusable runtime/RT64/SDL Android changes from Pokemon Stadium 1;
   do not copy its Stadium 1 symbol addresses, battle companion offsets, boot
   patches, or generated code.
5. Install and launch the resulting APK on a real device, then collect logcat
   and frame evidence. APK installation alone is not renderer validation.

## Verified build hosts

`pret/pokestadiumgs` rejects native Windows builds. The existing Mac Mini build
host successfully ran the containerized decompilation and pinned N64Recomp
passes. Windows successfully built the standalone Android ARM64 probe.
