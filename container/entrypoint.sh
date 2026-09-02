#!/bin/bash
# Entrypoint for gs-decomp-agent: runs the in-container driver loop
# (tools/container_agent.py) against exactly one decomp source file.
#
# Required:
#   SOURCE                repo-relative path to the file to work on, e.g.
#                          disasm/src/foo.c
#
# Candidate generator (see container/generators/README.md):
#   AGENT                 which coding agent generates candidates (default:
#                          claude). Selects container/generators/$AGENT.sh.
#   --generator-cmd ...    if the caller already passes this (or
#   --candidate-file ...   this, a one-shot test mode with no generator at
#                          all), it is forwarded to the driver as-is and
#                          this entrypoint does not touch it or gate on an
#                          API key. Otherwise this entrypoint defaults
#                          --generator-cmd to
#                          "/work/container/generators/run_generator.sh {prompt} {batch}"
#                          and requires the auth AGENT's wrapper needs
#                          (ANTHROPIC_API_KEY for claude, OPENAI_API_KEY for
#                          codex/openai_compat, OPENAI_API_KEY or
#                          DASHSCOPE_API_KEY for qwen, MOONSHOT_API_KEY for
#                          kimi_api, a mounted subscription login or
#                          KIMI_MODEL_NAME+KIMI_MODEL_API_KEY for kimi) so a
#                          missing key fails fast here instead of partway
#                          through the driver's first iteration.
#
# /out is expected to be a mounted volume (see container/run.sh) that the
# driver writes results/logs into.
#
# ROM gate note for tools/container_agent.py: invoke the gate as
# `make -C disasm COMPARE=1 -j2` (tools/try_pragma_compare.py's fixed
# invocation) freely -- the image now bakes a full `make -C disasm rom`
# (COMPARE left at its unpassed default) so lib/ultralib/build/L/libultra/libultra.a
# already exists on disk. That target has no listed prerequisites in
# disasm/Makefile, so once it is present a later COMPARE=1 invocation never
# re-enters the lib/ultralib sub-make (where COMPARE=1 would otherwise get
# force-propagated over FIXUPS=1's internal `COMPARE := 0` and demand a
# proprietary base/L/libultra.a this image does not ship) -- it just
# re-checks timestamps and relinks. Confirmed while smoke-testing this image
# (issue #39).
set -euo pipefail

# TMPDIR=/tmp: explicit rather than relying on the unset-var fallback, so
# anything that checks whether $TMPDIR is set (not just where it points)
# behaves the same as everything else here. container/run.sh mounts /tmp as
# a bounded tmpfs; a runner-driven compile independently redirects TMPDIR to
# /work/disasm/scratch (tools/try_pragma_compare.py, at import), which
# run.sh also tmpfs-bounds -- see the sweeper below and run.sh's --tmpfs
# comment for why both need bounding.
export TMPDIR=/tmp

# --- run-time symlink setup that could not be baked into the image --------
# The image bakes /usr/lib symlinks for IDO's compiler phases and for
# include/src/assets/build/lib under /work/disasm at build time (see
# container/Dockerfile) since /work does not move between builds. Re-assert
# them defensively here in case a caller bind-mounts over /work (e.g. for
# local iteration on the repo without rebuilding the image) -- cheap and
# idempotent, a no-op when the image's own /work is used unmodified.
if [ -d /work/disasm/tools/ido/linux/7.1 ]; then
    for f in /work/disasm/tools/ido/linux/7.1/* /work/disasm/tools/ido/linux/5.3/*; do
        [ -f "$f" ] && ln -sf "$f" "/usr/lib/$(basename "$f")"
    done
    mkdir -p /work/disasm/build
    for d in include src assets build lib; do
        [ -d "/work/disasm/$d" ] && ln -sfn "/work/disasm/$d" "/usr/lib/$d"
        [ -d "/work/disasm/$d" ] && ln -sfn "/work/disasm/$d" "/work/disasm/tools/ido/linux/7.1/$d"
        [ -d "/work/disasm/$d" ] && ln -sfn "/work/disasm/$d" "/work/disasm/tools/ido/linux/5.3/$d"
    done
fi

# --- required inputs --------------------------------------------------------
if [ -z "${SOURCE:-}" ]; then
    echo "entrypoint: SOURCE is required -- pass a repo-relative decomp source path (e.g. disasm/src/foo.c)" >&2
    echo "entrypoint: usually set via container/run.sh <disasm/src/file.c> <out-dir> [driver args...]" >&2
    exit 1
fi

# --- detect whether the caller already handles candidate generation --------
have_generator_cmd=0
have_candidate_file=0
for arg in "$@"; do
    case "$arg" in
        --generator-cmd|--generator-cmd=*) have_generator_cmd=1 ;;
        --candidate-file|--candidate-file=*) have_candidate_file=1 ;;
    esac
done

# --- default --generator-cmd to the container/generators/ dispatcher -------
args=("$@")
if [ "$have_generator_cmd" -eq 0 ] && [ "$have_candidate_file" -eq 0 ]; then
    args=(--generator-cmd "/work/container/generators/run_generator.sh {prompt} {batch}" "${args[@]}")
fi

# --- require the API key AGENT's generator wrapper needs -------------------
# Skipped entirely for --candidate-file (no generator/model call happens)
# and for a caller-supplied --generator-cmd (their command, their auth).
if [ "$have_candidate_file" -eq 0 ] && [ "$have_generator_cmd" -eq 0 ]; then
    AGENT="${AGENT:-claude}"

    fail_missing_key() {
        echo "entrypoint: AGENT=$AGENT needs \$$1 set." >&2
        echo "entrypoint: pass -e $1=... to 'docker run' (container/run.sh forwards it), or pass --candidate-file to skip the generator entirely." >&2
        exit 1
    }

    case "$AGENT" in
        claude)
            [ -n "${ANTHROPIC_API_KEY:-}" ] || fail_missing_key ANTHROPIC_API_KEY
            ;;
        openai_compat)
            [ -n "${OPENAI_API_KEY:-}" ] || fail_missing_key OPENAI_API_KEY
            ;;
        codex)
            if [ -z "${OPENAI_API_KEY:-}" ] && [ ! -f "${CODEX_HOME:-$HOME/.codex}/auth.json" ]; then
                echo "entrypoint: AGENT=codex needs \$OPENAI_API_KEY or an auth.json under \${CODEX_HOME:-~/.codex} (container/run.sh mounts the host's copy)." >&2
                exit 1
            fi
            ;;
        qwen)
            if [ -z "${OPENAI_API_KEY:-}" ] && [ -z "${DASHSCOPE_API_KEY:-}" ]; then
                echo "entrypoint: AGENT=qwen needs \$OPENAI_API_KEY or \$DASHSCOPE_API_KEY set." >&2
                echo "entrypoint: pass -e OPENAI_API_KEY=... or -e DASHSCOPE_API_KEY=... to 'docker run', or pass --candidate-file to skip the generator entirely." >&2
                exit 1
            fi
            ;;
        kimi)
            kimi_home="${KIMI_CODE_HOME:-$HOME/.kimi-code}"
            if [ ! -f "$kimi_home/credentials/kimi-code.json" ] \
               && { [ -z "${KIMI_MODEL_API_KEY:-}" ] || [ -z "${KIMI_MODEL_NAME:-}" ]; }; then
                echo "entrypoint: AGENT=kimi needs a subscription login (a credentials file under \${KIMI_CODE_HOME:-~/.kimi-code}/credentials/, mounted by container/run.sh from the host's copy) or both \$KIMI_MODEL_NAME and \$KIMI_MODEL_API_KEY set (the CLI's own stateless API-key model definition)." >&2
                echo "entrypoint: for a plain Moonshot API key with no CLI login state, use AGENT=kimi_api (\$MOONSHOT_API_KEY) instead." >&2
                exit 1
            fi
            ;;
        kimi_api)
            [ -n "${MOONSHOT_API_KEY:-}" ] || fail_missing_key MOONSHOT_API_KEY
            ;;
        *)
            # Unknown AGENT: let container/generators/run_generator.sh's own
            # error (unknown AGENT, lists available agents) surface instead
            # of guessing a key requirement here.
            ;;
    esac
fi

mkdir -p /out

# --- background sweeper for stranded IDO ctm* temp files -------------------
# IDO's compiler passes (as0, as1, ugen) create ctm* temp files honouring
# $TMPDIR and only remove them on a normal exit. decomp-permuter kills
# unpromising candidate compiles by design, so a pass gets killed constantly
# and strands its file -- ~7.5M files/hour measured during an active run.
# container/run.sh's --tmpfs flags bound both sinks (/tmp and
# /work/disasm/scratch) by size/inodes so that's a hard, loud failure mode
# rather than silent disk growth, but this sweep keeps a long session from
# ever getting close: every 120s, delete ctm* files idle for 5+ minutes --
# far above a live compile's lifetime (seconds) -- in each directory. Silent
# unless a sweep itself errors.
#
# This entrypoint execs the driver below, replacing this shell's program
# image without changing its PID -- so the sweeper, backgrounded here as a
# child of that same PID, remains a child of the driver process afterward.
# Docker container PID 1 is also its PID-namespace init: when the driver
# (now PID 1) exits, the kernel tears down the namespace and kills every
# remaining process in it, including the sweeper, so it can't outlive the
# container or hold it open. It also can't be killed before the driver
# starts: it's backgrounded and running well before the exec below.
sweep_stray_tmpfiles() {
    while true; do
        sleep 120
        for dir in /tmp /work/disasm/scratch; do
            err="$(find "$dir" -maxdepth 1 -name 'ctm*' -mmin +5 -delete 2>&1 1>/dev/null)"
            [ -n "$err" ] && echo "entrypoint: ctm* sweep of $dir failed: $err" >&2
        done
    done
}
sweep_stray_tmpfiles &

exec python3 /work/tools/container_agent.py --source "$SOURCE" --out /out "${args[@]}"
