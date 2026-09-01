#!/bin/sh
# Create N isolated fleet checkouts that can each run the full ROM gate.
#
# Why clones and not `git worktree`: the previous attempt put worktrees under
# /private/tmp, which macOS sweeps. That left 62 prunable entries and the
# "permission failure" that killed it -- the admin dirs outlived the trees.
# Clones under a persistent path have no such shared administrative state, so
# one tree dying cannot affect the others.
#
# A bare `git clone` cannot build: the baserom and three decomp helper clones
# are gitignored, so they are copied from the source checkout rather than
# re-downloaded. `disasm/build` is copied too, because a warm build turns the
# first ROM gate from a full compile into a ~2s incremental one.
#
# Usage:
#   tools/setup_fleet_clones.sh [count] [parent-dir]
#   tools/setup_fleet_clones.sh 5 ~/projects
set -eu

COUNT=${1:-5}
PARENT=${2:-$(cd "$(dirname "$0")/../.." && pwd)}
SRC=$(cd "$(dirname "$0")/.." && pwd)
NAME=$(basename "$SRC")

# Gitignored, but required for a build to run at all.
UNTRACKED_DEPS="disasm/baseroms disasm/tools/m2c disasm/tools/decomp-permuter disasm/tools/decomp-venv disasm/tools/vtxdis"

echo "source:  $SRC"
echo "parent:  $PARENT"
echo "clones:  $COUNT"
echo

i=1
while [ "$i" -le "$COUNT" ]; do
    dest="$PARENT/gs-fleet-$i"
    if [ -e "$dest" ]; then
        echo "== gs-fleet-$i: already exists, skipping =="
        i=$((i + 1))
        continue
    fi
    echo "== gs-fleet-$i =="
    git clone --shared --no-hardlinks "$SRC" "$dest" >/dev/null 2>&1
    # --shared keeps objects in the source repo: a clone costs megabytes, not
    # the 83MB object store, and every clone sees the same history.

    for dep in $UNTRACKED_DEPS; do
        if [ -e "$SRC/$dep" ]; then
            # Copy the CONTENTS: `cp -R src/d dest/d` nests when dest/d already
            # exists, and disasm/baseroms does -- its checksum.md5 is tracked,
            # so a plain copy produced disasm/baseroms/baseroms/.
            mkdir -p "$dest/$dep"
            cp -R "$SRC/$dep/." "$dest/$dep/"
        fi
    done

    if [ -d "$SRC/disasm/build" ]; then
        cp -R "$SRC/disasm/build" "$dest/disasm/build"
    fi

    # Probe stats are the process memory (AGENTS.md 2, rule 10): prior_attempts,
    # best_prior, futility, the near-miss pools and every hardness ranking read
    # them. A clone is not a linked worktree, so the runner's primary-worktree
    # fallback does not fire and the clone would start amnesiac -- repeating
    # failures 4,500 functions already recorded.
    #
    # Symlink rather than copy, so the fleet shares one ledger: the append lock
    # keys on the RESOLVED path, so every clone takes the same flock and
    # concurrent writes serialize instead of interleaving.
    rm -rf "$dest/disasm/probe-stats"
    ln -s "$SRC/disasm/probe-stats" "$dest/disasm/probe-stats"

    # The hooks are the guard that matters (AGENTS.md 1.3); a clone that
    # skips this can commit an ungated pragma removal.
    (cd "$dest" && git config core.hooksPath .githooks)
    (cd "$dest" && git checkout -q -B "fleet/tree-$i")

    echo "   $dest  (branch fleet/tree-$i)"
    i=$((i + 1))
done

echo
echo "Verify one before assigning work:"
echo "  cd $PARENT/gs-fleet-1 && make -C disasm COMPARE=1"
