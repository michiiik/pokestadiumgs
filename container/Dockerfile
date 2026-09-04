# gs-decomp-agent: a slim image for an autonomous agent that works on ONE
# Pokemon Stadium 2 (GS) decomp source file at a time -- probing candidate C
# functions, running the ROM gate, and driving decomp-permuter.
#
# Build for linux/amd64 explicitly, via `docker build --platform linux/amd64`
# (see container/build.sh) rather than a constant here: the checked-in IDO
# MIPS compiler binaries under disasm/tools/ido/linux/ are x86_64 Linux ELF,
# and this is meant to run under QEMU on an arm64 Docker host too.
#
# Runtime user: root. IDO's bundled `cc` driver expects its sibling compiler
# phases (as0, as1, cfe, ...) symlinked under /usr/lib, which needs root at
# build time to create; keeping the runtime user root avoids a second,
# redundant non-root symlink dance at every container start for a disposable,
# single-purpose image that only ever touches /work (baked image content) and
# /out (a mounted volume).
FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive \
    MIPS_BINUTILS_PREFIX=mips-linux-gnu- \
    DETECTED_OS=linux \
    PYTHON=/work/disasm/.venv/bin/python3

# git, make, build-essential, python3(+venv/pip): core build deps.
# gcc-multilib: RUN_CC_CHECK's host syntax check runs `gcc -fsyntax-only
#   -std=gnu89 -m32` (disasm/Makefile CC_CHECK_COMP/CC_CHECK_FLAGS).
# binutils-mips-linux-gnu: MIPS as/ld/ar/objcopy/objdump/nm -- not vendored.
# ca-certificates, wget, curl, gnupg: NodeSource setup + any tool-side fetches.
#
# container/generators/README.md's install lines: the claude/codex/qwen
# wrappers each need their CLI on PATH; kimi_api.sh and openai_compat.sh need
# only python3 stdlib (already required above), no extra install. kimi.sh
# needs the official Kimi Code CLI (installed separately below, a native
# binary with no npm/pip dependency).
RUN apt-get update && apt-get install -y --no-install-recommends \
        git make build-essential gcc-multilib \
        python3 python3-venv python3-pip \
        binutils-mips-linux-gnu \
        ca-certificates wget curl gnupg \
    && curl -fsSL https://deb.nodesource.com/setup_20.x | bash - \
    && apt-get install -y --no-install-recommends nodejs \
    && npm install -g @anthropic-ai/claude-code @openai/codex @qwen-code/qwen-code \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Kimi Code CLI (container/generators/kimi.sh): a standalone native binary,
# not an npm/pip package -- installed via Moonshot's own installer script
# (https://moonshotai.github.io/kimi-code/), pinned to an exact version so
# the image doesn't silently pick up a new release on rebuild.
# KIMI_INSTALL_DIR=/usr/local puts the binary straight at /usr/local/bin/kimi
# (already on PATH), matching the installer's own
# `sudo env KIMI_INSTALL_DIR=/usr/local bash` example -- no PATH/rc-file
# juggling needed since this image's RUN steps aren't login shells anyway.
# Manifest + per-platform sha256 checksum verified by the script itself
# (linux-x64 target, matching --platform linux/amd64 above).
ENV KIMI_CODE_VERSION=0.39.1
RUN curl -fsSL https://code.kimi.com/kimi-code/install.sh \
        | KIMI_VERSION="$KIMI_CODE_VERSION" KIMI_INSTALL_DIR=/usr/local bash \
    && kimi --version

# Google Antigravity CLI (container/generators/gemini.sh): a standalone
# native binary, not an npm/pip package. The installer has no version-pin or
# install-dir override (checked its source: no VERSION/INSTALL_DIR env var
# handling), so this always picks up whatever is current at build time,
# unlike Kimi above -- rebuild the image to pick up a new release. It places
# the binary at ~/.local/bin/agy (root's HOME here, i.e. /root/.local/bin)
# and is not on PATH by default; symlink it onto PATH directly rather than
# rely on a login-shell rc file, matching Kimi's reasoning above.
RUN curl -fsSL https://antigravity.google/cli/install.sh | bash \
    && ln -s /root/.local/bin/agy /usr/local/bin/agy \
    && agy --version

WORKDIR /work
COPY . /work

# disasm/requirements.txt pins spimdisasm to an exact commit
# (spimdisasm@fe13384) after declaring splat64[mips]==0.25.0; installing the
# two together in one `pip install -r requirements.txt` (what `make venv`
# does) is required -- a bare `pip install splat64[mips]` alone would resolve
# spimdisasm 1.42, which corrupts asm-processor output on thousands of files
# (see gs-host-check-and-splat-pin in project memory). `make setup` just
# builds disasm/tools/vtxdis.
RUN make -C disasm venv && make -C disasm setup

# IDO's `cc` driver looks for its sibling phase binaries (as0, as1, cfe,
# ugen, ...) under /usr/lib, and those phases resolve relative -I flags
# against their own directory rather than the invoking process's cwd. Expose
# the checked-in tools/ido/linux/7.1 (and 5.3, used for libultra) phases
# there, plus the source directories they need to see -- reproduces the
# symlink setup from tools/mac_build_disasm.sh (the prior cross-build
# container recipe) inside this image instead of at container start, since
# /work is baked and does not move.
RUN chmod +x disasm/tools/ido/linux/7.1/* disasm/tools/ido/linux/5.3/* \
    && for f in disasm/tools/ido/linux/7.1/* disasm/tools/ido/linux/5.3/*; do \
         [ -f "$f" ] && ln -sf "/work/$f" "/usr/lib/$(basename "$f")"; \
       done; \
       mkdir -p disasm/build \
    && for d in include src assets build lib; do \
         ln -sfn "/work/disasm/$d" "/usr/lib/$d"; \
         ln -sfn "/work/disasm/$d" "/work/disasm/tools/ido/linux/7.1/$d"; \
         ln -sfn "/work/disasm/$d" "/work/disasm/tools/ido/linux/5.3/$d"; \
       done

# asm/ and assets/ are entirely gitignored -- only the GLOBAL_ASM
# nonmatchings/*.s stubs under disasm/asm/us are force-tracked. A fresh
# checkout has nothing else for `make rom` to link, so split the baserom now
# (disasm/baseroms/us/baserom.z64 is copied into this build context; it is
# gitignored upstream, not fetched here). splat rewrites
# linker_scripts/us/pokestadiumgs.ld's ~11 hand-written alias lines when it
# runs -- stash and restore the tracked copy around the split (see
# DECOMP_SETUP.md and the gs-host-check-and-splat-pin project note; normally
# fixed with `git checkout --`, but .git is excluded from this build context
# by .dockerignore, so a plain file copy stands in for it here).
RUN cp disasm/linker_scripts/us/pokestadiumgs.ld /tmp/pokestadiumgs.ld.orig \
    && make -C disasm extract \
    && cp /tmp/pokestadiumgs.ld.orig disasm/linker_scripts/us/pokestadiumgs.ld \
    && rm /tmp/pokestadiumgs.ld.orig

# Bake a full initial matching build into the image. This is required, not
# just an optimization: tools/try_pragma_compare.py (the host-side gate
# runner container_agent.py drives) invokes the ROM gate as exactly
# `make -C disasm COMPARE=1 -j2` and cannot be changed. Passing COMPARE=1 on
# that command line makes it a command-line-origin variable, which GNU Make
# force-propagates into the lib/ultralib sub-make invocation below (see
# `$(ULTRALIB_LIB):` in disasm/Makefile) and overrides FIXUPS=1's internal
# `COMPARE := 0` -- but `$(ULTRALIB_LIB):` has no listed prerequisites, so
# once the archive already exists on disk (baked here, via a plain
# `make -C disasm rom` with COMPARE left at its unpassed default) that rule
# is satisfied and make never re-enters lib/ultralib on a later
# `COMPARE=1` invocation, which is what actually avoids the "not been setup"
# failure. This also means an incremental `make -C disasm COMPARE=1 -j2`
# gate run against an unmodified image only has to re-check timestamps and
# relink, not rebuild ~1,700 objects from scratch, so container_agent.py's
# gate calls stay fast after this layer.
RUN make -C disasm -j"$(nproc)" rom

# .dockerignore excludes .git from this build context entirely, so /work has
# no repository -- tools/container_agent.py's `git diff -- <source>` (used
# to write <out>/accepted/<owner>.patch once a candidate is installed) fails
# and only logs a warning without one. Give /work a minimal repo of its own
# so that command has something to diff against. `git add` only
# disasm/src and disasm/include (the files container_agent.py ever edits)
# to keep the object store tiny -- not the ~11,500-file extracted asm/assets
# trees baked above. No global git config is touched: user.name/user.email
# are set inline on this one commit via `-c`, scoped to this command only.
# This is a plain `git init`, not `git worktree add`, so it does not trip
# tools/try_pragma_compare.py's linked-worktree machinery
# (_primary_worktree_root and everything gated on it): that helper only
# recognizes a linked worktree's `.git` *file* containing a `gitdir: ...`
# pointer under a `worktrees/` directory, which a plain `git init`'s `.git`
# *directory* never matches -- confirmed by reading try_pragma_compare.py
# before adding this (issue #39 follow-up).
RUN git init -q \
    && git add disasm/src disasm/include \
    && git -c user.name="gs-decomp-agent image" -c user.email="gs-decomp-agent@localhost" \
         commit -q -m "baseline: disasm/src and disasm/include as shipped in the image"

# decomp-permuter + m2c clones and their private venv (disasm/tools/m2c,
# disasm/tools/decomp-permuter, disasm/tools/decomp-venv -- all gitignored).
RUN sh tools/setup_decomp_tools.sh

RUN mkdir -p /out
VOLUME ["/out"]

COPY container/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
