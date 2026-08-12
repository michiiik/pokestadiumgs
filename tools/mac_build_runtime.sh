#!/bin/bash
set -euo pipefail

runtime_root="${PS2_RUNTIME_ROOT:-/Users/michaegg/ps2-recomp-build/runtime}"
stadium1_root="${PS1_RUNTIME_ROOT:-/Users/michaegg/psr-recomp-build/work}"
android_deps="${PS2_ANDROID_DEPS:-/Users/michaegg/psr-recomp-build/deps/android3}"
container_image="${PS2_BUILD_IMAGE:-psr-recomp-cross:latest}"

export DOCKER_CONFIG="${DOCKER_CONFIG:-/tmp/psr-docker-config}"

exec docker run --rm --platform linux/amd64 \
    -v "$runtime_root:/work" \
    -v "$stadium1_root/lib:/work/lib:ro" \
    -v "$stadium1_root/cmake:/work/cmake:ro" \
    -v "$android_deps:/android:ro" \
    -w /work \
    "$container_image" \
    cmake --build /work/build-android \
        --target PokemonStadiumRecomp \
        --parallel 4
