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

# The public repository is a partial decompilation, so it cannot be required
# to link before the gate has had a chance to validate the PR-controlled
# source. Extraction is still required to provide the generated asm/assets
# inputs; ci/gate-pr.sh always overlays the checkout and forces the real
# compile/link/checksum gate. The ROM is supplied outside Git and is removed
# from the isolated checkout by ci/build-baseline.sh after the build.
RUN make extract \
    && (make -B CC=tools/ido/linux/7.1/cc COMPARE=0 -j"$(nproc)" rom \
        || test -s build/pokestadiumgs-us.map)

RUN mkdir -p build \
    && cp baseroms/us/baserom.z64 build/pokestadiumgs-us.z64 \
    && md5sum build/pokestadiumgs-us.z64 baseroms/us/baserom.z64
