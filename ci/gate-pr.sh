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
headers_changed=0
tools_changed=0
makefile_changed=0
# The baseline image contains generated lib/ultralib/build and extracted
# objects. They are not PR-controlled inputs and must not make the gate throw
# away the baked linker map before compiling the public checkout.
if ! diff -qr --exclude=build --exclude=extracted /src/lib /work/lib >/dev/null 2>&1; then
    library_changed=1
fi
if ! diff -qr /src/include /work/include >/dev/null 2>&1; then
    headers_changed=1
fi
if ! diff -qr /src/tools /work/tools >/dev/null 2>&1; then
    tools_changed=1
fi
if [ ! -f /work/Makefile ] || ! cmp -s /src/Makefile /work/Makefile; then
    makefile_changed=1
fi

# Keep the baked source/object timestamps for unchanged files. A plain
# recursive copy makes every checkout file newer than the baked objects,
# which defeats the image's build cache and turns every PR into a full build.
# Content comparison also handles Git checkout timestamp differences.
sync_tree() {
    local source_dir="$1"
    local target_dir="$2"
    mkdir -p "$target_dir"
    while IFS= read -r -d "" source_file; do
        local relative="${source_file#"$source_dir"/}"
        local target_file="$target_dir/$relative"
        if [ ! -f "$target_file" ] || ! cmp -s "$source_file" "$target_file"; then
            mkdir -p "$(dirname "$target_file")"
            cp -p "$source_file" "$target_file"
        fi
    done < <(find "$source_dir" -type f -print0)
    while IFS= read -r -d "" target_file; do
        local relative="${target_file#"$target_dir"/}"
        if [ ! -f "$source_dir/$relative" ]; then
            rm -f "$target_file"
        fi
    done < <(find "$target_dir" -type f -print0)
}

sync_tree /src/src /work/src
sync_tree /src/include /work/include
sync_tree /src/tools /work/tools
sync_tree /src/linker_scripts /work/linker_scripts
sync_tree /src/lib /work/lib
if [ "${makefile_changed}" -eq 1 ]; then
    cp -p /src/Makefile /work/Makefile
fi

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
    ""|*[!0-9]*|0)
        echo "gate-pr.sh: GS_DECOMP_JOBS must be a positive integer" >&2
        exit 2
        ;;
esac
echo "gate-pr.sh: building with ${build_jobs} parallel job(s); per-object host syntax checks enabled"
full_build=0
if [ "${split_changed}" -eq 1 ] || [ "${headers_changed}" -eq 1 ] || [ "${tools_changed}" -eq 1 ] || [ "${makefile_changed}" -eq 1 ]; then
    full_build=1
fi
if [ "${full_build}" -eq 1 ]; then
    echo "gate-pr.sh: forcing a full rebuild because split, header, tool, or Makefile inputs changed"
    make -B COMPARE=0 -j"${build_jobs}" rom
else
    echo "gate-pr.sh: reusing cached objects and rebuilding changed source inputs"
    make COMPARE=0 -j"${build_jobs}" rom
fi
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

# Make's colored output can leave an ANSI reset sequence immediately before
# md5sum's result. The md5sum exit status above is authoritative; this check
# is only a readable-log sanity check and therefore must not require the line
# to start at column zero.
if ! grep -q 'build/pokestadiumgs-us\.z64: OK' "$log_file"; then
    echo "gate-pr.sh: FAIL -- expected checksum acceptance line was absent" >&2
    exit 1
fi

echo "gate-pr.sh: PASS -- build/pokestadiumgs-us.z64: OK" >&2
