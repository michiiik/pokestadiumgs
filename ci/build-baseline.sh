#!/usr/bin/env bash
# Build the local public baseline image.
#
# Usage:
#   POKESTADIUMGS_BASEROM=/private/path/baserom.z64 ci/build-baseline.sh

set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
baserom="$repo_root/baseroms/us/baserom.z64"
temporary_baserom=0

cleanup() {
    if [ "$temporary_baserom" -eq 1 ]; then
        rm -f "$baserom"
    fi
}
trap cleanup EXIT

if [ ! -f "$baserom" ]; then
    source_baserom="${POKESTADIUMGS_BASEROM:-}"
    if [ -z "$source_baserom" ] || [ ! -f "$source_baserom" ]; then
        echo "build-baseline.sh: provide POKESTADIUMGS_BASEROM or place baseroms/us/baserom.z64 in the ignored checkout" >&2
        exit 1
    fi
    mkdir -p "$(dirname "$baserom")"
    cp "$source_baserom" "$baserom"
    temporary_baserom=1
fi

if [ ! -f "$repo_root/baseroms/us/checksum.md5" ]; then
    echo "build-baseline.sh: missing baseroms/us/checksum.md5" >&2
    exit 1
fi

image="${GS_DECOMP_AGENT_IMAGE:-gs-decomp-agent-pokestadiumgs:latest}"
docker build \
    --platform linux/amd64 \
    --tag "$image" \
    --file "$repo_root/ci/Dockerfile" \
    "$repo_root"

echo "build-baseline.sh: built $image from the public checkout"
