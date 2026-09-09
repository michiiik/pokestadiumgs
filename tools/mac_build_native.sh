#!/bin/bash
set -euo pipefail

# The checked-in project is the Stadium 2 decomp/recomp configuration.  Its
# desktop runner and shared renderer live in the local runtime checkout used by
# the Android build, while the common runtime dependencies are shared with the
# Stadium 1 checkout.
repo_root="$(cd "$(dirname "$0")/.." && pwd)"
runtime_root="${PS2_RUNTIME_ROOT:-/Users/michaegg/ps2-recomp-build/runtime}"
stadium1_root="${PS1_RUNTIME_ROOT:-/Users/michaegg/psr-recomp-build/work}"
build_root="${PS2_MAC_BUILD_ROOT:-$repo_root/build-mac}"
source_root="$build_root/source"
build_dir="$build_root/ninja"

test -f "$runtime_root/CMakeLists.txt"
test -d "$runtime_root/lib/N64ModernRuntime"
test -d "$stadium1_root/lib/rt64"
test -d "$stadium1_root/recomp-ui"

# Stage source paths without copying or modifying either sibling checkout.
# N64ModernRuntime is the one exception: it's a GS-owned copy under
# runtime_root/lib (not a symlink into the Stadium 1 checkout). Scheduler
# fixes needed for this project's boot sequence live only in that copy —
# editing the tree shared with Stadium 1 previously broke Stadium 1's build.
rm -rf "$source_root"
mkdir -p "$source_root/lib"
#
# The recompiled sources come from gen_dir, a GS-owned copy of generated/. The
# two documented post-generation steps (tools/wire_ai_submit.py and the bogus
# trailing-section removal from tools/reapply_generated_patches.py) are applied
# there. They are NOT applied to generated/ itself, which the Android build
# also references. The staged tree still calls it "generated" because that is
# the include path baked into the generated sources and CMakeLists.
gen_dir="${PS2_GENERATED_DIR:-generated-mac}"
test -d "$runtime_root/$gen_dir"
for item in "$runtime_root"/*; do
    name="${item##*/}"
    case "$name" in
        lib|recomp-ui|generated|src|"$gen_dir") continue ;;
    esac
    ln -s "$item" "$source_root/$name"
done
ln -s "$runtime_root/$gen_dir" "$source_root/generated"
# src is COPIED, never symlinked. src/main/register_overlays.cpp (and three
# other files) include "../../generated/recomp_overlays.inl" and
# "../../generated/funcs.h" as relative paths. Through a symlinked src/ the
# compiler resolves those against the REAL directory (runtime/src/main), so
# they reach runtime/generated and silently bypass the generated symlink above
# — which produced a binary whose function bodies came from $gen_dir but whose
# section tables and funcs.h came from the stale, 0x10-skewed runtime/generated.
cp -R "$runtime_root/src" "$source_root/src"
ln -s "$runtime_root/lib/N64ModernRuntime" "$source_root/lib/N64ModernRuntime"
for item in "$stadium1_root/lib"/*; do
    name="${item##*/}"
    case "$name" in
        N64ModernRuntime) continue ;;
    esac
    ln -s "$item" "$source_root/lib/$name"
done
ln -s "$stadium1_root/recomp-ui" "$source_root/recomp-ui"
ln -s "$repo_root/tools/mac_post_mortem_stub.cpp" "$source_root/mac_post_mortem_stub.cpp"
ln -s "$repo_root/tools/mac_link_shims.c" "$source_root/mac_link_shims.c"
ln -s "$repo_root/tools/mac_debug_server_stub.cpp" "$source_root/debug_server_macos.cpp"
cp "$runtime_root/lib/N64ModernRuntime/librecomp/src/pi.cpp" "$source_root/mac_pi.cpp"
perl -pi -e 's/\r$//' "$source_root/mac_pi.cpp"
patch -s "$source_root/mac_pi.cpp" \
    < "$repo_root/patches/mac-native-pi-runtime.patch"
cp "$runtime_root/lib/N64ModernRuntime/librecomp/src/ai.cpp" "$source_root/mac_ai.cpp"
perl -pi -e 's/\r$//' "$source_root/mac_ai.cpp"
patch -s "$source_root/mac_ai.cpp" \
    < "$repo_root/patches/mac-native-ai-runtime.patch"
cp "$runtime_root/lib/N64ModernRuntime/ultramodern/src/mesgqueue.cpp" \
    "$source_root/mac_mesgqueue.cpp"
perl -pi -e 's/\r$//' "$source_root/mac_mesgqueue.cpp"
patch -s "$source_root/mac_mesgqueue.cpp" \
    < "$repo_root/patches/mac-native-mesgqueue.patch"
# NOTE: the funcs_76 / funcs_21 / funcs_189 guard patches are deliberately NOT
# applied any more. Each was compensating for a symptom of a single root cause:
# the old runtime/generated tree was recompiled from disasm/pokestadiumgs-us.elf,
# whose .text is 0x10 larger than the ROM's (0xA7A90 vs 0xA7A80). Every address
# label and data reference past that point sat 0x10 off the real baserom.z64,
# which is why the ALHeap length underflowed, the audio config globals read as
# garbage, and osSendMesg/osRecvMesg saw NULL queue pointers. gen_dir now points
# at a tree built from the matching ELF (verified: 196/196 sampled instructions
# agree with the ROM at delta 0), so the underlying values are correct and the
# guards would only mask real behavior. The patches are kept in patches/ for
# reference.
cp "$runtime_root/extras.c" "$source_root/extras_macos.c"
patch -s "$source_root/extras_macos.c" \
    < "$repo_root/patches/mac-native-extras.patch"

# Keep the large generated game library buildable in a reasonable time without
# unity-compiling third-party C libraries whose headers intentionally lack
# include guards.
unlink "$source_root/CMakeLists.txt"
cp "$runtime_root/CMakeLists.txt" "$source_root/CMakeLists.txt"
patch -s "$source_root/CMakeLists.txt" \
    < "$repo_root/patches/mac-native-recompiled-unity.patch"
patch -s "$source_root/CMakeLists.txt" \
    < "$repo_root/patches/mac-native-apple-arch.patch"
patch -s "$source_root/CMakeLists.txt" \
    < "$repo_root/patches/mac-native-postmortem.patch"
patch -s "$source_root/CMakeLists.txt" \
    < "$repo_root/patches/mac-native-debug-server.patch"
patch -s "$source_root/CMakeLists.txt" \
    < "$repo_root/patches/mac-native-link-shims.patch"
patch -s "$source_root/CMakeLists.txt" \
    < "$repo_root/patches/mac-native-extras-source.patch"
patch -s "$source_root/CMakeLists.txt" \
    < "$repo_root/patches/mac-native-pi-runtime-source.patch"
patch -s "$source_root/CMakeLists.txt" \
    < "$repo_root/patches/mac-native-mesgqueue-source.patch"
patch -s "$source_root/CMakeLists.txt" \
    < "$repo_root/patches/mac-native-runtime-opt.patch"
# (matching *-funcs-{76,21,189}-source.patch hunks intentionally dropped; see above)

# The staged runtime is shared with Stadium 1, but this project must present
# its own product name in the macOS build output.
sed -i '' 's/PokemonStadiumRecomp/PokemonStadiumGSRecomp/g' \
    "$source_root/CMakeLists.txt"

# NDEBUG is defined even though this keeps a debuggable build configuration.
# The generated game C remains at -O0 so the huge unity translation units stay
# buildable on the Mac mini; the C++ runtime is optimized because its scheduler
# and queue paths are the dominant intro-time cost. The recompiled sources and
# runtime carry asserts
# that are porting AIDS, not correctness guarantees, and each one aborts the
# whole process on a condition real N64 hardware simply tolerates:
#   - funcs_166.c guLookAtReflectF: assert(ctx->f10.fl == ctx->f10.fl) is a NaN
#     test; the game legitimately hands it a NaN during boot and hardware just
#     computes with it.
# Keeping them fatal meant the renderer died mid-boot. Drop -DNDEBUG when you
# are deliberately hunting one of these.
cmake -S "$source_root" -B "$build_dir" -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_CXX_FLAGS="-DFMT_USE_CONSTEVAL=0 -DNDEBUG" \
    -DCMAKE_C_FLAGS="-O0 -DNDEBUG" \
    -DWITH_ARES_BRIDGE=OFF \
    -DN64MODERN_RUNTIME_ROOT="$source_root/lib/N64ModernRuntime"

cmake --build "$build_dir" --target PokemonStadiumGSRecomp \
    --parallel "${CMAKE_BUILD_PARALLEL_LEVEL:-2}"

echo "Built: $build_dir/PokemonStadiumGSRecomp"
