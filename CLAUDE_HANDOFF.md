# Pokemon Stadium 2 Android recomp handoff

Last updated: 2026-08-13

## Current state

The game has previously booted on the AYN Thor with audio, Vulkan/Turnip, and
substantially improved performance. The latest rental-roster build has been
rebuilt and packaged, but has not yet been installed or runtime-tested because
the Thor was disconnected from ADB. Do not treat the latest build as device
validated until the rental screen has been checked.

The working tree is intentionally limited to the source configuration change.
The generated native library and APK are ignored build artifacts.

## Rental-roster investigation

`Pokemon Stadium 2 (U) - Mord's Rental Hack.bps` is a replacement patch: it
replaces five existing 24-byte rental records in two tables. It is useful as a
source for the special-rental records, but it does not implement the desired
expanded roster and must not be applied as the final solution.

The source-side expansion preserves every original record and appends Mewtwo,
Mew, Lugia, Ho-Oh, and Celebi to both relevant Prime Cup tables:

- rental blob base: `0x802492B0`;
- table 1: offset `0xCB0`, original count `246`, new count `251`;
- table 2: offset `0x23D0`, original count `248`, new count `253`;
- record size: `0x18` bytes;
- each append shifts later data by `0x78` bytes;
- table-directory offsets for tables 2 onward are adjusted once, and tables 3
  onward are adjusted a second time.

The five records are derived from the supplied BPS. The implementation is in
the sibling source checkout at
`C:\Users\laptop\Documents\lg\PokemonStadiumRecomp\extras.c`, with the
configuration hook in this repository's `game.toml`:

```toml
[[patches.hook]]
func = "func_80006ACC"
before_vram = 0x80006B38
text = "pkmnstadium_expand_gs_rental_blob(rdram, ctx);"
```

The remote Mac source and generated function were updated without replacing
the rest of their dirty worktrees. Backups are present remotely as:

- `extras.c.pre-gs-expansion`;
- `generated/funcs_119.c.pre-gs-expansion`.

The generated call currently replaces the earlier experimental inline patch.
Regenerating all C output may overwrite that generated edit; the durable path
is to keep the helper in `extras.c` and regenerate from `game.toml` when the
full generation workflow is next run.

## Build and package evidence

The focused Android native build completed on the Mac Mini using the cached
objects. The correct remote paths are:

```bash
docker run --rm --platform linux/amd64 \
  -v /Users/michaegg/ps2-recomp-build/runtime:/work \
  -v /Users/michaegg/psr-recomp-build/work/lib:/work/lib \
  -v /Users/michaegg/ps2-recomp-build/runtime/.ccache:/root/.cache/ccache \
  -v /Users/michaegg/psr-recomp-build/deps/android3/android-ndk-r27c:/android/android-ndk-r27c \
  -w /work psr-recomp-cross:latest \
  cmake --build /work/build-android --target PokemonStadiumRecomp --parallel 2
```

The original `deps/android` path is empty; use `deps/android3`. The dependency
tree is under `psr-recomp-build/work/lib`, not `ps2-recomp-build/work/lib`.

The resulting library was copied to
`android/app/src/main/jniLibs/arm64-v8a/libmain.so` and the debug APK assembled
successfully at:
`android/app/build/outputs/apk/debug/app-debug.apk`.

The latest local native-library SHA-256 was:
`E3AF9B864251CCB1CBB33371A5D528EDF0AB8CDE764D01965112E5652E6B0D8C`.

## Next runtime steps

When the Thor is connected, run:

```powershell
$adb = 'C:\projects\ddd-dl\.android-sdk\platform-tools\adb.exe'
& $adb devices -l
& $adb -s 3c43878a install -r android\app\build\outputs\apk\debug\app-debug.apk
& $adb -s 3c43878a shell am force-stop com.pokemonstadium2recomp
& $adb -s 3c43878a shell am start -n com.pokemonstadium2recomp/com.pokemonstadiumrecomp.probe.MainActivity
```

Then capture a screenshot of the rental selection screen and verify all of the
following:

1. original rentals such as Caterpie, Metapod, Weedle, Kakuna, and Magikarp
   remain available;
2. the five appended Pokémon appear in the intended expanded slots;
3. their icons, names, stats, and selection behavior are valid;
4. audio still works and there is no black flicker;
5. frame rate remains stable in the menu and rental screen.

If icons or appended entries are still missing, inspect the table-directory
consumer and the selection-screen count/index path next. Do not revert to the
BPS replacement behavior as a workaround.

## Repository hygiene

ROMs, generated C output, Android/Gradle output, native libraries, APKs, logs,
and screenshots are ignored. Keep runtime screenshots under `screenshots/`.
Do not commit the 64 MiB ROM, generated recompilation output, APK, or `.so`.
Before handing off, run `git status --short --branch`, `git diff --check`, and
confirm only intentional source/config/documentation changes remain.
