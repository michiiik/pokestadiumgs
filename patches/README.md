# patches/

Three groups. `tools/mac_build_native.sh` is the authority on what is actually
applied — if a patch is not named there, it is not in the macOS build.

## Active — applied by `tools/mac_build_native.sh`

| patch | target |
|---|---|
| `mac-native-recompiled-unity.patch` | `CMakeLists.txt` — unity-build the recompiled sources |
| `mac-native-apple-arch.patch` | `CMakeLists.txt` — arm64 / Apple bits |
| `mac-native-postmortem.patch` | `CMakeLists.txt` — post-mortem stub |
| `mac-native-debug-server.patch` | `CMakeLists.txt` — swap the Windows-only debug server for `tools/mac_debug_server_stub.cpp` |
| `mac-native-link-shims.patch` | `CMakeLists.txt` — `tools/mac_link_shims.c` |
| `mac-native-extras-source.patch` / `mac-native-extras.patch` | `extras.c` and its build entry |
| `mac-native-pi-runtime-source.patch` / `mac-native-pi-runtime.patch` | `pi.cpp` (`osPiReadIo_recomp`) and its build entry |
| `mac-native-mesgqueue-source.patch` / `mac-native-mesgqueue.patch` | `mesgqueue.cpp` and its build entry |
| `mac-native-ai-runtime.patch` | `ai.cpp` — Stadium 2 AI submit path |

## Retained for reference — deliberately NOT applied

`mac-native-funcs-21-guard.patch`, `mac-native-funcs-76-guard.patch`,
`mac-native-funcs-189-guard.patch` (and their `-source` build entries).

Each was compensating for a *symptom* of one root cause: the old
`runtime/generated` tree was recompiled from an ELF whose `.text` is 16 bytes
larger than the ROM's, so every address and data reference sat `+0x10` off. That
is why the ALHeap length underflowed, the audio config globals read as garbage,
and `osSendMesg`/`osRecvMesg` saw NULL queues. With `gen_dir` pointing at a tree
built from the matching ELF the underlying values are correct and these guards
would only mask real behavior. Kept so the analysis in each header isn't lost.

## `legacy/` — superseded, referenced by nothing

Older variants kept only for history: earlier `funcs-200` and `funcs-76`
attempts, and the `pi-helpers` / `pi-source` pair that
`mac-native-pi-runtime*.patch` replaced.

## Everything else

The `librecomp-*`, `n64recomp-*`, `stadium2-*` and `ultramodern-*` patches
predate the macOS work and belong to the Android/rental-roster effort. Two of
them are applied by `tools/reapply_generated_patches.py` after a regenerate
(`stadium2-exclude-rom-tail-section`, `stadium2-generated-callback-guard`) —
that script and `tools/wire_ai_submit.py` must BOTH be run after any regenerate.

**A post-generation anchor that does not match means the generated tree is
wrong.** Never adjust the anchor to force a patch to apply — both of those tools
encode the correct addresses, and their refusal to apply is exactly how the
wrong-ELF tree was eventually caught.
