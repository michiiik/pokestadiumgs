# Porting status

Last updated: 2026-08-13

## Current boundary

The Stadium 2 recompilation has booted on the AYN Thor in earlier builds with
working audio, Vulkan/Turnip rendering, input, and much better menu
performance. The current build contains a source-side expanded Prime Cup
rental roster, but it has not yet been installed and runtime-verified because
the device was disconnected from ADB.

## Completed

- Verified the 64 MiB US ROM and canonical Z64 byte order.
- Confirmed MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
- Added the `pret/pokestadiumgs` decompilation source and generated metadata.
- Generated the relocatable recompilation with the pinned engine revision in
  `n64recomp.pin`.
- Built and launched ARM64 Android versions on the AYN Thor.
- Enabled the Android runtime path with audio and Turnip/Vulkan rendering.
- Analyzed the supplied Mord rental BPS and confirmed it replaces records
  rather than expanding the roster.
- Added a source-side expansion that preserves all original records, appends
  five special rentals to both Prime Cup tables, and fixes the shifted table
  directory offsets.
- Rebuilt the native library and assembled a debug APK from that change.
- Kept ROMs, generated output, APKs, native libraries, logs, screenshots, and
  local Android configuration out of version control.

## Immediate next step

Reconnect the Thor, install the APK, and validate the rental selection screen.
Check original rentals, all five added Pokémon, icons, audio, flicker, and
frame-rate stability. The detailed command sequence and remote build paths are
in [CLAUDE_HANDOFF.md](CLAUDE_HANDOFF.md).

## Important implementation note

The source helper lives in the sibling checkout
`C:\Users\laptop\Documents\lg\PokemonStadiumRecomp\extras.c`; this repository
contains the `game.toml` hook that calls it. That sibling checkout is dirty and
must not be overwritten wholesale. The current remote source and generated
function have backups ending in `.pre-gs-expansion`.
