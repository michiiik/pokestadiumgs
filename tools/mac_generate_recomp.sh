#!/bin/bash
set -euo pipefail

# Run inside the linux/amd64 build container with this repository at /work and
# the pinned N64Recomp build directory mounted at /n64recomp.
cd /work

test -f baserom.z64
test -f disasm/build/pokestadiumgs-us.elf
test -x /n64recomp/N64Recomp

export N64RECOMP_SKIP_AGGRESSIVE_STATIC_SEEDS=1
exec /n64recomp/N64Recomp /work/game.toml
