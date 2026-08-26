# Pokemon Stadium 2 Recomp for Android

## Decompilation coverage

The following block is refreshed by the repository post-commit hook.
Enable the tracked hook once per checkout with
`git config core.hooksPath .githooks`.

<!-- AUTO_COVERAGE:START -->
- US functions with C implementations: **2,972 / 10,532 (28.2%)**
- Remaining `GLOBAL_ASM` owners: **7,560**
- Baseline: `f477acf` (vendored US pragma snapshot)
<!-- AUTO_COVERAGE:END -->

Work-in-progress static recompilation of **Pokemon Stadium 2 (US)** for
Android, using [N64Recomp](https://github.com/N64Recomp/N64Recomp) and the
[pret/pokestadiumgs](https://github.com/pret/pokestadiumgs) decompilation.

This repository establishes the verified Stadium 2 ROM/decomp base, the N64Recomp
generation configuration, and the Android runtime path. Earlier builds booted
on the AYN Thor; the current rental-roster build still needs device validation.
See
[PORTING_STATUS.md](PORTING_STATUS.md) for the exact boundary.

## ROM

The project targets the US ROM in canonical big-endian Z64 form:

- Size: `67108864` bytes
- MD5: `1561c75d11cedf356a8ddb1a4a5f9d5d`
- Header: `80 37 12 40`

ROM files are ignored and must never be committed. A byte-swapped V64 dump
starts with `37 80 40 12`; convert it to Z64 before building the decompilation.

## Android probe

The probe verifies the local Android SDK, Java, NDK ARM64 compiler, JNI bridge,
APK packaging, and 16 KiB page-compatible native linking independently of the
unfinished game recompilation.

```powershell
.\tools\verify_rom.ps1
.\tools\build_android_probe.ps1
```

The APK is written to:

`android/app/build/outputs/apk/debug/app-debug.apk`

The latest rental-roster build handoff is in
[CLAUDE_HANDOFF.md](CLAUDE_HANDOFF.md).

## Decompilation

The `disasm` directory is a vendored copy of `pret/pokestadiumgs` (forked at
`michiiik/pokestadiumgs`, imported at `stadium2-names` commit `ccae2a1`). Its
build currently requires a
Linux/macOS environment with GNU Make, Python, and `mips-linux-gnu` binutils;
native Windows is explicitly unsupported upstream.

On the existing Mac Mini cross-build host, mount `disasm` at `/work` in the
linux/amd64 build container and run `tools/mac_build_disasm.sh` inside it. The
verified build produces `build/pokestadiumgs-us.elf` and a byte-identical US
ROM.

## Recompilation

`game.toml` targets the ELF above, and `fragments_relocatable.txt` is derived
from its 88 fragment sections:

```powershell
python tools\derive_recomp_metadata.py `
  --readelf <path-to-llvm-readelf-or-mips-linux-gnu-readelf>
```

The engine revision is recorded in `n64recomp.pin`. In the Mac Mini container,
mount this repository at `/work`, the pinned engine build at `/n64recomp`, and
run `tools/mac_generate_recomp.sh`. The first verified pass emitted 33,529
functions. Current Android runtime and rental-roster status is recorded in
`PORTING_STATUS.md` and `CLAUDE_HANDOFF.md`.

## Symbol naming

The decompilation ships almost entirely as `#pragma GLOBAL_ASM` stubs, so a
function's name lives in `disasm/linker_scripts/us/symbol_addrs_code.txt` and in
the pragma path that references it -- not in a C identifier. `tools/apply_names.py`
keeps the two in step; `tools/xmatch_stadium1.py` derives names by matching this
ROM's machine code against the Stadium 1 decomp, which shares much of the engine.

```sh
python3 tools/xmatch_stadium1.py --report   # what would transfer, and why
python3 tools/apply_names.py --dry-run
python3 tools/apply_names.py && python3 tools/apply_names.py --qa
```

Coverage, method and caveats are in [docs/NAMING.md](docs/NAMING.md). The renamed
tree (the `stadium2-names` branch of the disasm fork) is vendored in `disasm/`.

## Native macOS build

The desktop runner is supplied by the local runtime checkout used for the
Android build. With the Stadium 1 checkout available at its usual path, build
the macOS executable from this repository with:

```sh
tools/mac_build_native.sh
```

The script stages the shared RT64/N64ModernRuntime/recomp-ui dependencies
without modifying either sibling checkout. It also carries the AppleClang fmt
workaround used by Stadium 1 and uses unoptimized generated C for a practical
first boot. The executable is written to `build-mac/ninja/PokemonStadiumGSRecomp`.

To boot it directly after building, run it from the staged runtime directory so
the ROM and runtime assets are next to the executable:

```sh
cd build-mac/source
PSR_AUTOBOOT=1 ../ninja/PokemonStadiumGSRecomp
```
