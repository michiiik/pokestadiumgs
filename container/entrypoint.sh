#!/bin/bash
# Entrypoint for gs-decomp-agent: runs the in-container driver loop
# (tools/container_agent.py) against exactly one decomp source file.
#
# Required:
#   SOURCE                repo-relative path to the file to work on, e.g.
#                          disasm/src/foo.c
#
# Optional (stale-image fix, issue #39 follow-up):
#   SRC_OVERLAY            set by container/run.sh from `SRC_OVERLAY=<host
#                          checkout dir>` to the in-container mountpoint
#                          (/src, read-only). When set, this entrypoint
#                          overlays that checkout's disasm/src,
#                          disasm/include, and disasm/linker_scripts onto
#                          /work/disasm (container/overlay_src.sh) and runs
#                          one incremental `make -C disasm rom` before the
#                          driver starts, so a container launched from an
#                          image built before some GLOBAL_ASM owners landed
#                          on master doesn't still discover and treat them
#                          as owners. See container/overlay_src.sh's own
#                          header and the "ROM gate note" below for why
#                          `make rom` (no COMPARE) is what runs here, not
#                          `make COMPARE=1`.
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
#                          KIMI_MODEL_NAME+KIMI_MODEL_API_KEY for kimi,
#                          GENERATOR_MODEL plus a provider token for
#                          claude_via -- ANTHROPIC_AUTH_TOKEN/ALIBABA_API_KEY
#                          for CLAUDE_VIA=alibaba, ZAI_API_KEY for
#                          CLAUDE_VIA=zai, CLAUDE_VIA_BASE_URL+
#                          CLAUDE_VIA_API_KEY for CLAUDE_VIA=custom; the
#                          AGENT=alibaba/AGENT=zai shorthands expand to this
#                          with CLAUDE_VIA set for you, see
#                          container/generators/README.md) so a
#                          missing key fails fast here instead of partway
#                          through the driver's first iteration. It also
#                          exports PROBE_TOOL (off for AGENT=openai_compat/
#                          kimi_api, on otherwise; never overrides a value
#                          the caller already exported) -- see the driver's
#                          --probe-tool and docs/CONTAINER_AGENT.md's "Fast
#                          inner loop" section.
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

# --- SRC_OVERLAY: overlay a live checkout's sources over the baked image ---
# container/run.sh sets SRC_OVERLAY=<host checkout dir> and mounts it
# read-only at /src when the caller wants this run to see sources newer
# than what the image baked at build time -- see the header comment above.
# Read container/overlay_src.sh out of /src itself (never a possibly-stale
# baked copy at /work/container/overlay_src.sh) so this stays correct even
# for an image built before overlay_src.sh existed at all -- that script's
# own header explains why.
if [ -n "${SRC_OVERLAY:-}" ]; then
    if [ ! -d /src ]; then
        echo "entrypoint: SRC_OVERLAY is set but /src is not mounted -- container/run.sh should mount it read-only" >&2
        exit 1
    fi
    echo "entrypoint: SRC_OVERLAY set -- overlaying /src onto /work/disasm and rebuilding" >&2
    overlay_start=$(date +%s)
    # Re-split first when the overlaid checkout changed splat's inputs. The
    # image bakes a completed asm/ tree; overlaying sources built from a
    # different split links against jump tables that reference labels the new
    # sources no longer define, and `make rom` fails before the driver ever
    # starts -- the container exits with no summary.json and fleetctl records
    # it as vanished. That took the whole fleet down once: every run hit
    # "vanished 3 times in a row" after 585D0 gained its own .rodata
    # subsegment while the image still had the old blob. container/gate_pr.sh
    # does the same check for the PR gate.
    if ! diff -qr /src/disasm/yamls /work/disasm/yamls >/dev/null 2>&1; then
        echo "entrypoint: split inputs changed -- re-running extraction" >&2
        rm -rf /work/disasm/yamls
        cp -a /src/disasm/yamls /work/disasm/yamls
        make -C /work/disasm extract
    fi
    bash /src/container/overlay_src.sh /src
    # Incremental, no explicit COMPARE (see the "ROM gate note" above) --
    # brings the baked build tree in sync with the overlaid sources before
    # the driver starts, without tripping lib/ultralib's COMPARE=1
    # force-propagation.
    make -C /work/disasm rom
    overlay_elapsed=$(( $(date +%s) - overlay_start ))
    echo "entrypoint: SRC_OVERLAY overlay + make -C disasm rom done in ${overlay_elapsed}s" >&2
fi

# --- detect whether the caller already handles candidate generation --------
have_generator_cmd=0
have_candidate_file=0
have_permuter_only=0
prev=""
for arg in "$@"; do
    case "$arg" in
        --generator-cmd|--generator-cmd=*) have_generator_cmd=1 ;;
        --candidate-file|--candidate-file=*) have_candidate_file=1 ;;
        --mode=permuter-only) have_permuter_only=1 ;;
        permuter-only) [ "$prev" = "--mode" ] && have_permuter_only=1 ;;
    esac
    prev="$arg"
done
# A permuter-only run (AGENT=permuter) never calls a model: no generator
# command, no API key.
if [ "$have_permuter_only" -eq 1 ]; then
    have_generator_cmd=1
fi

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
            if [ -z "${ANTHROPIC_API_KEY:-}" ] && [ -z "${CLAUDE_CODE_OAUTH_TOKEN:-}" ]; then
                echo "entrypoint: AGENT=claude needs \$ANTHROPIC_API_KEY or \$CLAUDE_CODE_OAUTH_TOKEN (from 'claude setup-token')." >&2
                exit 1
            fi
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
        claude_via)
            [ -n "${GENERATOR_MODEL:-}" ] || fail_missing_key GENERATOR_MODEL
            case "${CLAUDE_VIA:-}" in
                alibaba)
                    if [ -z "${ANTHROPIC_AUTH_TOKEN:-}" ] && [ -z "${ALIBABA_API_KEY:-}" ]; then
                        echo "entrypoint: AGENT=claude_via CLAUDE_VIA=alibaba needs \$ANTHROPIC_AUTH_TOKEN (container/run.sh resolves this from ~/.qwen/settings.json, selected by \$ALIBABA_PLAN) or \$ALIBABA_API_KEY." >&2
                        exit 1
                    fi
                    ;;
                zai)
                    [ -n "${ZAI_API_KEY:-}" ] || fail_missing_key ZAI_API_KEY
                    ;;
                custom)
                    [ -n "${CLAUDE_VIA_BASE_URL:-}" ] || fail_missing_key CLAUDE_VIA_BASE_URL
                    [ -n "${CLAUDE_VIA_API_KEY:-}" ] || fail_missing_key CLAUDE_VIA_API_KEY
                    ;;
                "")
                    echo "entrypoint: AGENT=claude_via needs \$CLAUDE_VIA set to alibaba|zai|custom." >&2
                    exit 1
                    ;;
                *)
                    # Unknown CLAUDE_VIA: let container/generators/claude_via.sh's
                    # own error surface instead of guessing here.
                    ;;
            esac
            ;;
        alibaba)
            # Shorthand for AGENT=claude_via CLAUDE_VIA=alibaba, expanded by
            # container/generators/run_generator.sh -- same key requirement.
            [ -n "${GENERATOR_MODEL:-}" ] || fail_missing_key GENERATOR_MODEL
            if [ -z "${ANTHROPIC_AUTH_TOKEN:-}" ] && [ -z "${ALIBABA_API_KEY:-}" ]; then
                echo "entrypoint: AGENT=alibaba needs \$ANTHROPIC_AUTH_TOKEN (container/run.sh resolves this from ~/.qwen/settings.json's BAILIAN_CODING_PLAN_API_KEY/BAILIAN_TOKEN_PLAN_API_KEY, selected by \$ALIBABA_PLAN, default coding) or \$ALIBABA_API_KEY set directly." >&2
                exit 1
            fi
            ;;
        zai)
            # Shorthand for AGENT=claude_via CLAUDE_VIA=zai.
            [ -n "${GENERATOR_MODEL:-}" ] || fail_missing_key GENERATOR_MODEL
            [ -n "${ZAI_API_KEY:-}" ] || fail_missing_key ZAI_API_KEY
            ;;
        *)
            # Unknown AGENT: let container/generators/run_generator.sh's own
            # error (unknown AGENT, lists available agents) surface instead
            # of guessing a key requirement here.
            ;;
    esac

    # --- default PROBE_TOOL from AGENT -------------------------------------
    # tools/container_agent.py's --probe-tool (a paragraph in BATCH_CONTRACT
    # telling the generator it may call tools/probe_one.py to iterate before
    # writing the batch) falls back to $PROBE_TOOL when the flag itself is
    # not passed -- see docs/CONTAINER_AGENT.md's "Fast inner loop" section.
    # openai_compat and kimi_api are plain HTTP wrappers with no tool access
    # at all (see container/generators/README.md), so that paragraph would
    # just be noise for them; every other agent here is agentic (Read/Write/
    # Bash) and can act on it. Only set a default -- never override a value
    # the caller already exported.
    case "$AGENT" in
        openai_compat|kimi_api) PROBE_TOOL="${PROBE_TOOL:-off}" ;;
        *)                      PROBE_TOOL="${PROBE_TOOL:-on}" ;;
    esac
    export PROBE_TOOL
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
