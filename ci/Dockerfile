# Public Pokemon Stadium GS ROM-gate baseline.
#
# This image is built locally on the isolated Mac runner from a clean public
# checkout. The US baserom is supplied outside Git and is never published.
# The image contains only the build toolchain and generated baseline build
# state; it is not the workflow's authority to merge code.

FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive \
    MIPS_BINUTILS_PREFIX=mips-linux-gnu- \
    DETECTED_OS=linux \
    PYTHON=/work/.venv/bin/python3

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        bash \
        build-essential \
        binutils-mips-linux-gnu \
        ca-certificates \
        gcc-multilib \
        git \
        make \
        python3 \
        python3-pip \
        python3-venv \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /work
COPY . /work

# Install the exact pinned Python dependencies and build the repository tools.
RUN make venv \
    && make setup

# Generate the ignored asm/assets trees from the local baserom, then bake a
# matching baseline. The baseline is intentionally seeded with the real IDO
# compiler: the PR gate later overlays the coalescing wrapper and uses this
# linked map to reproduce opt-in matching artifacts. libultra is built with
# FIXUPS, so archive comparison is disabled here.
RUN make extract \
    && make CC=tools/ido/linux/7.1/cc -j"$(nproc)" COMPARE=0 rom

# Keep the expensive baseline build layer cacheable. The authoritative checksum
# is enforced by ci/gate-pr.sh after the PR-controlled files are overlaid.
RUN md5sum build/pokestadiumgs-us.z64 baseroms/us/baserom.z64
