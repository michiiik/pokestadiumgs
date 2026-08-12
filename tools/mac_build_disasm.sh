#!/bin/bash
set -euo pipefail

# Run inside the linux/amd64 cross-build container with the Stadium 2
# decompilation mounted at /work. The bundled IDO driver expects its compiler
# phases under /usr/lib, so expose the mounted tools there for this disposable
# container only.
cd /work

if ! command -v wget >/dev/null 2>&1; then
    export DEBIAN_FRONTEND=noninteractive
    apt-get update
    apt-get install -y --no-install-recommends ca-certificates wget
fi

chmod +x tools/ido/linux/7.1/* tools/ido/linux/5.3/*
for tool in tools/ido/linux/7.1/*; do
    ln -sf "/work/$tool" "/usr/lib/$(basename "$tool")"
done

for directory in include src assets build lib; do
    ln -sfn "/work/$directory" "/usr/lib/$directory"
    ln -sfn "/work/$directory" "tools/ido/linux/7.1/$directory"
done

# asm-processor compiles a temporary source file. IDO resolves relative include
# paths from its compiler-phase directory in this container, so make the
# top-level game's include paths unambiguous.
absolute_includes="-I/work/include -I/work/src -I/work/src/libnaudio -I/work/assets/us -I/work -I/work/build -I/work/lib/ultralib/include -I/work/lib/ultralib/include/PR -I/work/lib/ultralib/include/ido"

make venv \
    VENV_BIN_DIR=bin \
    DETECTED_OS=linux \
    MIPS_BINUTILS_PREFIX=mips-linux-gnu-

make setup \
    VENV_BIN_DIR=bin \
    DETECTED_OS=linux \
    PYTHON=/work/.venv/bin/python \
    MIPS_BINUTILS_PREFIX=mips-linux-gnu-

make extract \
    VENV_BIN_DIR=bin \
    DETECTED_OS=linux \
    PYTHON=/work/.venv/bin/python \
    MIPS_BINUTILS_PREFIX=mips-linux-gnu-

make -C lib/ultralib setup \
    VERSION=L \
    TARGET=libultra \
    FIXUPS=1 \
    CROSS=mips-linux-gnu-

make -j1 rom \
    COLOR=0 \
    RUN_CC_CHECK=0 \
    IINC="$absolute_includes" \
    VENV_BIN_DIR=bin \
    DETECTED_OS=linux \
    PYTHON=/work/.venv/bin/python \
    MIPS_BINUTILS_PREFIX=mips-linux-gnu-
