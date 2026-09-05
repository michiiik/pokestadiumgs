#!/bin/bash
# container/overlay_src.sh <checkout-dir>
#
# Overlays <checkout-dir>'s disasm/src, disasm/include, and
# disasm/linker_scripts onto the build tree at /work/disasm. Meant to run
# INSIDE a gs-decomp-agent container -- it always writes to the hardcoded
# /work/disasm paths, never a path derived from $0 or cwd.
#
# Both callers run THIS FILE out of the checkout being overlaid
# (<checkout-dir>/container/overlay_src.sh), never a copy baked into the
# image at build time:
#   - container/gate_pr.sh: `docker run --entrypoint bash ... -v
#     <checkout-dir>:/src:ro ...  bash /src/container/overlay_src.sh /src`
#   - container/entrypoint.sh: same pattern, driven by SRC_OVERLAY/
#     container/run.sh's /src mount (see that script's own comment)
# The point (issue #39 stale-image follow-up) is that the image's own
# baked disasm/src/include -- and a baked copy of this very script --
# can be behind whatever has since landed on <checkout-dir>'s master. A
# GLOBAL_ASM owner merged after the image was built must stop being
# rediscovered as an owner once a checkout containing that merge is
# overlaid; reading this script live out of that checkout is what makes
# that guarantee hold regardless of when the image was last rebuilt.
#
# src/include: fully replaced (rm -rf + cp -a), not overwritten in place,
# so a file <checkout-dir> deletes doesn't silently keep linking the
# image's stale .o for it.
# linker_scripts: overlaid, never delete-synced -- a plain checkout never
# contains the gitignored linker_scripts/<version>/auto/ splat output, so
# there is nothing to accidentally delete there even without --delete;
# this only ever adds/updates the handful of tracked .ld/.txt files.
#
# See container/gate_pr.sh's own header and the "ROM gate note" comment in
# container/entrypoint.sh for why only these directories matter to a
# `make rom`(-COMPARE) build -- disasm/asm/, disasm/assets/, and
# linker_scripts/<version>/auto/ are splat/extract output and stay exactly
# as baked in the image.
#
# disasm/tools is overlaid for the same reason as the Makefile: the
# lui-coalescing mechanism (coalesce_cc.py/coalesce_lui.py/coalesce_splice.py/
# elf32.py) is invoked as the Makefile's own `CC`, so a PR that touches it
# -- or that is itself only gate-able because of it, i.e. any
# `#pragma COALESCE_AT_LUI(...)` owner -- must not silently build against the
# image's stale baked-in copy.
set -euo pipefail

if [ "$#" -ne 1 ]; then
    echo "usage: $(basename "$0") <checkout-dir>" >&2
    exit 1
fi

checkout_dir="$1"

if [ ! -d "$checkout_dir/disasm/src" ] || [ ! -f "$checkout_dir/disasm/Makefile" ]; then
    echo "overlay_src.sh: $checkout_dir does not look like a repo checkout (no disasm/src or disasm/Makefile)" >&2
    exit 1
fi

rm -rf /work/disasm/src /work/disasm/include /work/disasm/tools
cp -a "$checkout_dir/disasm/src" /work/disasm/src
cp -a "$checkout_dir/disasm/include" /work/disasm/include
cp -a "$checkout_dir/disasm/tools" /work/disasm/tools
cp -a "$checkout_dir/disasm/linker_scripts/." /work/disasm/linker_scripts/
# The Makefile too: without it the gate builds a PR's sources with the
# image's baked-in Makefile, so a PR that changes build rules is not
# actually gated -- and a target the PR adds is simply missing, which is
# how this PR first failed with "No rule to make target 'cc-check'".
cp -a "$checkout_dir/disasm/Makefile" /work/disasm/Makefile

echo "overlay_src.sh: overlaid $checkout_dir/disasm/{src,include,tools,linker_scripts,Makefile} onto /work/disasm" >&2
