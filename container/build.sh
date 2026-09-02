#!/bin/bash
# Build the gs-decomp-agent image from the repo root.
#
# Always builds for linux/amd64: the checked-in IDO MIPS compiler binaries
# (disasm/tools/ido/linux/) are x86_64 Linux ELF, and the local Docker host
# may be linux/arm64 (e.g. OrbStack on Apple Silicon), which would otherwise
# select an incompatible base image / run nothing under emulation at all.
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$repo_root"

docker build \
    --platform linux/amd64 \
    -t gs-decomp-agent:latest \
    -f container/Dockerfile \
    .
