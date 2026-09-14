#!/usr/bin/env bash
# Run the public PR ROM gate against a checkout directory.
#
# The caller supplies a checkout that may contain PR-controlled files. The
# checkout is mounted read-only into a disposable container. The host-side
# script is deliberately small and the container has no Docker socket,
# secrets, or network access.

set -euo pipefail

usage() {
    echo "usage: $(basename "$0") <checkout-dir> [coverage-output-dir]" >&2
    exit 2
}

[ "$#" -ge 1 ] && [ "$#" -le 2 ] || usage

checkout_dir="$1"
coverage_output_dir="${2:-}"
if [ ! -d "$checkout_dir" ]; then
    echo "gate-pr.sh: checkout does not exist: $checkout_dir" >&2
    exit 1
fi
checkout_dir="$(cd "$checkout_dir" && pwd)"

for required in Makefile src include linker_scripts yamls tools lib; do
    if [ ! -e "$checkout_dir/$required" ]; then
        echo "gate-pr.sh: missing public checkout path: $required" >&2
        exit 1
    fi
done

image="${GS_DECOMP_AGENT_IMAGE:-gs-decomp-agent-pokestadiumgs:latest}"
log_file="$(mktemp "${TMPDIR:-/tmp}/pokestadiumgs-gate.XXXXXX.log")"
cleanup() { rm -f "$log_file"; }
trap cleanup EXIT

docker_args=(
    run --rm
    --platform linux/amd64
    --network none
    --cap-drop=ALL
    --security-opt=no-new-privileges
    --pids-limit=2048
    -v "$checkout_dir:/src:ro"
)
if [ -n "$coverage_output_dir" ]; then
    mkdir -p "$coverage_output_dir"
    docker_args+=( -v "$coverage_output_dir:/out:rw" )
fi

set +e
docker "${docker_args[@]}" \
    --entrypoint bash \
    "$image" \
    -c '
set -euo pipefail

# Overlay all tracked inputs that can affect the public root build. Never
# overlay baseroms: the baseline image owns the known retail reference.
library_changed=0
split_changed=0
# The baseline image contains generated lib/ultralib/build and extracted
# objects. They are not PR-controlled inputs and must not make the gate throw
# away the baked linker map before compiling the public checkout.
if ! diff -qr --exclude=build --exclude=extracted /src/lib /work/lib >/dev/null 2>&1; then
    library_changed=1
fi
rm -rf /work/src /work/include /work/tools /work/linker_scripts /work/lib
cp -a /src/src /work/src
cp -a /src/include /work/include
cp -a /src/tools /work/tools
mkdir -p /work/linker_scripts
cp -a /src/linker_scripts/. /work/linker_scripts/
cp -a /src/lib /work/lib
cp -a /src/Makefile /work/Makefile

# The baked venv must match the checked-in requirements. Rebuilding it would
# require network access, so force a baseline rebuild for dependency changes.
if ! cmp -s /src/requirements.txt /work/requirements.txt; then
    echo "gate-pr.sh: requirements.txt changed; rebuild the public baseline image" >&2
    exit 3
fi

# A YAML change changes the split. Re-extract before compiling against it.
if ! diff -qr /src/yamls /work/yamls >/dev/null 2>&1; then
    split_changed=1
    echo "gate-pr.sh: split inputs changed; re-running extraction" >&2
    rm -rf /work/yamls
    cp -a /src/yamls /work/yamls
    make extract
fi

# A library change invalidates the baked lib objects. This remains inside the
# disposable container and does not touch the host checkout.
if [ "${library_changed}" -eq 1 ]; then
    make libclean
fi

# Rebuild a direct-IDO seed when extraction or libclean removed the baked map.
# The coalescing wrapper needs that map to resolve dlabels before it can safely
# apply an opted-in fold. The final ROM build is always forced after the PR
# overlay: the image contains a retail seed ROM, and timestamp-based make
# decisions must never be allowed to accept that seed without compiling the
# checked-out sources.
if [ "${split_changed}" -eq 1 ]; then
    rm -rf /work/build
fi
if [ ! -f /work/build/pokestadiumgs-us.map ]; then
    echo "gate-pr.sh: linked map missing; rebuilding direct-IDO seed" >&2
    make CC=tools/ido/linux/7.1/cc COMPARE=0 -j2 rom
fi

# Produce the proposed coverage snapshot even when the ROM build later
# fails, so reviewers can inspect the exact PR delta in the artifact.
if [ -d /out ]; then
    python3 /src/ci/update_coverage.py \
        --repo-root /src \
        --baseline /src/COVERAGE.md \
        --output /out/COVERAGE.md
fi

# Force every root object through its recipe. Each C-object recipe performs the
# host syntax check before invoking IDO, so this forced build covers the whole
# C tree without running a second serial cc-check pass. libultra is rebuilt
# with FIXUPS by the root Makefile; disabling the nested archive comparison
# lets that source build run without a private libultra base archive. Use all
# available container CPUs by default; the override is useful for diagnosing
# runner contention without weakening the gate.
build_jobs="${GS_DECOMP_JOBS:-$(nproc)}"
case "${build_jobs}" in
    ''|*[!0-9]*|0)
        echo "gate-pr.sh: GS_DECOMP_JOBS must be a positive integer" >&2
        exit 2
        ;;
esac
echo "gate-pr.sh: building with ${build_jobs} parallel job(s); per-object host syntax checks enabled"
make -B COMPARE=0 -j"${build_jobs}" rom
md5sum -c baseroms/us/checksum.md5
' >"$log_file" 2>&1
status=$?
set -e

cat "$log_file"
if [ -n "$coverage_output_dir" ]; then
    cp "$log_file" "$coverage_output_dir/gate.log"
fi
echo "gate-pr.sh: container exit status $status" >&2

if [ "$status" -ne 0 ]; then
    echo "gate-pr.sh: FAIL -- public build/compare failed" >&2
    exit "$status"
fi

if ! grep -q '^build/pokestadiumgs-us\.z64: OK$' "$log_file"; then
    echo "gate-pr.sh: FAIL -- expected checksum acceptance line was absent" >&2
    exit 1
fi

echo "gate-pr.sh: PASS -- build/pokestadiumgs-us.z64: OK" >&2
