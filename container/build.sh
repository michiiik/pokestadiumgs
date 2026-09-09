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

# Stage a reference linker map for disasm/tools/coalesce_lui.py's
# COALESCE_AT_LUI fold (see disasm/tools/coalesce_cc.py), which needs one to
# resolve fixed data-segment addresses for functions like func_84136D84 that
# still only exist as still-GLOBAL_ASM callers -- disasm/tools/Makefile's
# tracked symbol_addrs*.txt/undefined_syms*.ld files don't carry those,
# by this project's own convention (dlabel-only addresses are intentionally
# kept out of them; see resolve_repo_addresses' docstring).
#
# .dockerignore excludes disasm/build/ from the build context entirely (line
# "Generated build output inside disasm/ -- (re)created at image build time"),
# same as .git is excluded a few lines above it in the Dockerfile for
# pokestadiumgs.ld -- so the image's own baked RUN make -C disasm rom (which
# runs before any build of its own has produced a map) has no map to read
# from inside the build context by default, only tracked symbol files. A
# linked worktree building natively doesn't hit this: coalesce_lui.py's
# _primary_worktree_root falls back to a linked primary checkout's
# already-built map when the local one doesn't exist yet (addresses are
# intrinsic to the ROM's segment layout, identical across every worktree of
# this repo) -- but Docker's build context has no .git at all, so that
# fallback can never trigger either.
#
# Stage a copy of whichever map is actually available on this host --
# preferring this worktree's own (if it has been built at least once), else
# walking to the primary checkout's the same way _primary_worktree_root does
# -- into container/.map-cache/, a path .dockerignore does NOT exclude, so
# COPY . /work picks it up; the Dockerfile then copies it into
# disasm/build/ right before the RUN step that needs it. Best-effort: if
# neither exists (a from-scratch checkout with no successful build anywhere
# yet), nothing is staged and that RUN step fails exactly as it would have
# without this -- loudly, per coalesce_cc.py's own "never something to paper
# over" design, not silently degraded.
map_cache_dir="$repo_root/container/.map-cache"
rm -rf "$map_cache_dir"
mkdir -p "$map_cache_dir"

map_src=""
if [ -f "$repo_root/disasm/build/pokestadiumgs-us.map" ]; then
    map_src="$repo_root/disasm/build/pokestadiumgs-us.map"
elif [ -f "$repo_root/.git" ]; then
    # Linked worktree: .git is a file containing "gitdir: <path>/.git/worktrees/<name>".
    gitdir_line="$(cat "$repo_root/.git")"
    gitdir_path="${gitdir_line#gitdir: }"
    if [ -d "$gitdir_path" ]; then
        worktrees_dir="$(cd "$gitdir_path" && pwd)"
        if [ "$(basename "$(dirname "$worktrees_dir")")" = "worktrees" ]; then
            primary_root="$(dirname "$(dirname "$(dirname "$worktrees_dir")")")"
            if [ -f "$primary_root/disasm/build/pokestadiumgs-us.map" ]; then
                map_src="$primary_root/disasm/build/pokestadiumgs-us.map"
            fi
        fi
    fi
fi

if [ -n "$map_src" ]; then
    cp "$map_src" "$map_cache_dir/pokestadiumgs-us.map"
    echo "container/build.sh: staged coalesce-lui reference map from $map_src"
else
    echo "container/build.sh: no built pokestadiumgs-us.map found (locally or via a primary checkout) to stage -- COALESCE_AT_LUI functions may fail to bake if their address isn't in a tracked symbol_addrs*.txt/undefined_syms*.ld"
fi

docker build \
    --platform linux/amd64 \
    -t gs-decomp-agent:latest \
    -f container/Dockerfile \
    .
