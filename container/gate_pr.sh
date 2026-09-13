#!/bin/bash
# container/gate_pr.sh <checkout-dir> [--rebuild-image]
#
# The container ROM gate for a PR checkout: rebuilds the ROM inside the
# prebuilt gs-decomp-agent:latest image using ONLY that checkout's
# disasm/src, disasm/include, and disasm/linker_scripts, and exits 0 only
# if the result byte-matches the retail ROM. This is the whole PR gate as
# one script -- .github/workflows/container-gate.yml just calls it, and a
# human can run the exact same command locally (see docs/PR_GATE.md).
#
# Why only those three directories: gs-decomp-agent:latest (built by
# container/build.sh, see docs/CONTAINER_AGENT.md) already has a full
# checkout at /work with a completed, byte-matching ROM build baked in.
# `make -C disasm COMPARE=1 -j2` is incremental against that image -- ~1s
# when sources are unchanged, ~70s for a full relink -- because splat's
# extracted disasm/asm/ and disasm/assets/ trees are baked in and never
# regenerated here. Per disasm/Makefile, everything a `make rom`
# (non-extract) build actually reads is: $(C_FILES)/$(S_FILES) under
# src/ (IINC's -Isrc, -Iinclude), disasm/include/ (-Iinclude), and the
# *tracked* files under disasm/linker_scripts/ (common_undef_syms.ld,
# <version>/{aliases,hardware_regs,undefined_syms,unused_syms,pokestadiumgs}.ld,
# <version>/symbol_addrs*.txt) -- disasm/yamls/ (rom.yaml/header.yaml) only
# feeds `make extract`, which this gate never runs. disasm/asm/,
# disasm/assets/, and linker_scripts/<version>/auto/ are splat/extract
# output: gitignored, absent from any git checkout, and never touched here
# -- they stay exactly as baked in the image.
#
# check_decomp_provenance.py is deliberately NOT run by this gate: it reads
# `git diff --staged` (a pre-commit-hook contract -- .githooks/pre-commit
# runs it on the developer's own staged index, see that script's own
# docstring), and this gate never stages or commits anything, so there is
# no staged diff for it to read. Its accepted-attempt history
# (disasm/probe-stats/, see tools/probe_stats.py) is also deliberately
# gitignored/untracked (.gitignore: "Durable probe-stats history ...
# deliberately ... untracked") -- it lives only on whichever host produced
# it and is not part of a PR checkout or reproducible from the image, so
# even a staged-diff-shaped invocation could not give a trustworthy answer
# here. Provenance stays a commit-time human/CI concern on the source repo,
# not part of the container rebuild-and-compare gate.
set -euo pipefail

usage() {
    echo "usage: $(basename "$0") <checkout-dir> [--rebuild-image]" >&2
    exit 1
}

[ "$#" -ge 1 ] || usage

checkout_dir=""
rebuild_image=0
for arg in "$@"; do
    case "$arg" in
        --rebuild-image)
            rebuild_image=1
            ;;
        -h|--help)
            usage
            ;;
        -*)
            echo "gate_pr.sh: unknown option: $arg" >&2
            usage
            ;;
        *)
            if [ -n "$checkout_dir" ]; then
                echo "gate_pr.sh: unexpected extra argument: $arg" >&2
                usage
            fi
            checkout_dir="$arg"
            ;;
    esac
done

[ -n "$checkout_dir" ] || usage

case "$checkout_dir" in
    /*) : ;;
    *) checkout_dir="$(cd "$checkout_dir" && pwd)" ;;
esac

if [ ! -d "$checkout_dir/disasm/src" ] || [ ! -f "$checkout_dir/disasm/Makefile" ]; then
    echo "gate_pr.sh: $checkout_dir does not look like a repo checkout (no disasm/src or disasm/Makefile)" >&2
    exit 1
fi

image="gs-decomp-agent:latest"

if [ "$rebuild_image" -eq 1 ]; then
    if [ ! -x "$checkout_dir/container/build.sh" ]; then
        echo "gate_pr.sh: --rebuild-image passed but $checkout_dir/container/build.sh is missing/not executable" >&2
        exit 1
    fi
    echo "gate_pr.sh: --rebuild-image passed -- rebuilding $image from $checkout_dir/container/build.sh" >&2
    "$checkout_dir/container/build.sh"
fi

log_file="$(mktemp -t gate_pr_compare.XXXXXX.log)"
cleanup() { rm -f "$log_file"; }
trap cleanup EXIT

start_ts=$(date +%s)

# In-container steps:
#  1. Overlay the checkout's disasm/src, disasm/include, and
#     disasm/linker_scripts onto /work/disasm (container/overlay_src.sh --
#     run out of the mounted checkout itself, /src/container/overlay_src.sh,
#     never a copy baked into the image; see that script's own header for
#     why, and container/entrypoint.sh's SRC_OVERLAY handling for the other
#     caller of the same script).
#  2. Run the exact gate command container_agent.py's own driver uses,
#     `make -C disasm COMPARE=1 -j2`.
in_container_script='
set -euo pipefail
# Re-split first when the PR changes splat'"'"'s inputs. The image bakes a
# completed asm/ tree, and the overlay only refreshes sources -- so a PR that
# moves a subsegment in yamls/ would otherwise be built against the OLD split
# and fail with a wrong ROM checksum that says nothing about the change (that
# is exactly how PR #64 first failed: its strings were emitted both from the
# new C literals and from the stale shared rodata blob). The image venv has
# the pinned spimdisasm, so `make extract` here is the same split the repo
# documents. Skipped entirely when yamls/ is unchanged, which is the common
# case, because extract wipes asm/ and forces a full rebuild.
if ! diff -qr /src/disasm/yamls /work/disasm/yamls >/dev/null 2>&1; then
    echo "gate_pr.sh: split inputs changed -- re-running extraction" >&2
    rm -rf /work/disasm/yamls
    cp -a /src/disasm/yamls /work/disasm/yamls
    make -C disasm extract
    # `extract` regenerates the asm/ *source* tree but does not clean
    # build/ -- a subsegment that changes type (e.g. data -> rodata) or
    # name renames the generated .s file, but the OLD compiled .o from
    # the image'"'"'s baked-in build/ stays on disk with nothing to ever
    # remove it, since make has no rule saying a file that no longer
    # exists should delete its old output. The stale object then links
    # in alongside the freshly-built one and fails as a duplicate
    # symbol definition -- a real bug found on PR #390 (fragment9,
    # `.data` -> `.rodata`), same root cause as the PR #64 case above,
    # just manifesting as "multiple definition" instead of a silent
    # wrong checksum. A full rebuild when the split changes is the only
    # way to guarantee no such orphan survives.
    rm -rf /work/disasm/build
fi
bash /src/container/overlay_src.sh /src
cd /work
# Whole-tree host syntax check first. The ROM build below is incremental
# against the image, so it only re-runs the per-object CC_CHECK for sources
# this PR actually changed -- a host-check break in an untouched file slips
# through here and then surfaces much later, failing an unrelated candidate
# at re-gate time (see PR #57 / func_82702954). ~18s for the full tree.
make -C disasm cc-check RUN_CC_CHECK=1
make -C disasm COMPARE=1 -j2
'

set +e
docker run --rm \
    --platform linux/amd64 \
    -v "$checkout_dir:/src:ro" \
    --entrypoint bash \
    "$image" \
    -c "$in_container_script" \
    > "$log_file" 2>&1
status=$?
set -e

end_ts=$(date +%s)
elapsed=$((end_ts - start_ts))

cat "$log_file"
echo "gate_pr.sh: container exit status $status, elapsed ${elapsed}s" >&2

if [ "$status" -ne 0 ]; then
    echo "gate_pr.sh: FAIL -- container/build exited nonzero" >&2
    exit "$status"
fi

if ! grep -q '^build/pokestadiumgs-us\.z64: OK$' "$log_file"; then
    echo "gate_pr.sh: FAIL -- 'build/pokestadiumgs-us.z64: OK' not found in gate output (checksum mismatch or gate did not run md5sum -c)" >&2
    exit 1
fi

echo "gate_pr.sh: PASS -- build/pokestadiumgs-us.z64: OK (${elapsed}s)" >&2
exit 0
