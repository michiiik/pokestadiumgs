#!/bin/bash
# Run gs-decomp-agent against exactly one decomp source file.
#
# Usage:
#   container/run.sh <disasm/src/file.c> <out-dir> [driver args...]
#
# <disasm/src/file.c>  repo-relative path to the source file the in-container
#                       agent (tools/container_agent.py) should work on.
# <out-dir>             host directory to mount at /out (created if missing).
#                       Passed through to the driver as --out /out.
# [driver args...]      forwarded verbatim to entrypoint.sh -> container_agent.py
#                       (e.g. --candidate-file batch.json for a one-shot test
#                       with no generator/model call at all).
#
# Candidate generator env (see container/generators/README.md), forwarded
# from this shell's environment when set -- entrypoint.sh requires whichever
# key AGENT's wrapper needs, unless --candidate-file is passed:
#   AGENT             claude (default) | codex | qwen | kimi | openai_compat
#   GENERATOR_MODEL   override the wrapper's default model
#   GENERATOR_EFFORT  codex reasoning effort (low|medium|high|xhigh)
#   ANTHROPIC_API_KEY claude
#   OPENAI_API_KEY    codex, qwen (or DASHSCOPE_API_KEY), openai_compat
#   OPENAI_BASE_URL   openai_compat (required), qwen (optional)
#   DASHSCOPE_API_KEY qwen, alternate to OPENAI_API_KEY
#   MOONSHOT_API_KEY  kimi
#   MOONSHOT_BASE_URL kimi, optional (default: global Moonshot endpoint)
set -euo pipefail

if [ "$#" -lt 2 ]; then
    echo "usage: $(basename "$0") <disasm/src/file.c> <out-dir> [driver args...]" >&2
    exit 1
fi

source_file="$1"
out_dir="$2"
shift 2

case "$out_dir" in
    /*) : ;;
    *)
        echo "run.sh: <out-dir> must be an absolute path (got: $out_dir)" >&2
        exit 1
        ;;
esac

mkdir -p "$out_dir"

# Codex with a ChatGPT login instead of an API key: mount a throwaway copy of
# the host's ~/.codex/auth.json so token refreshes never touch the original.
extra_args=()
if [ "${AGENT:-claude}" = "codex" ] && [ -z "${OPENAI_API_KEY:-}" ] && [ -f "$HOME/.codex/auth.json" ]; then
    codex_home="$(mktemp -d)"
    cp "$HOME/.codex/auth.json" "$codex_home/auth.json"
    extra_args+=(-v "$codex_home:/root/.codex")
fi

docker run \
    --platform linux/amd64 \
    --rm \
    -e SOURCE="$source_file" \
    -e AGENT \
    -e GENERATOR_MODEL \
    -e GENERATOR_EFFORT \
    -e ANTHROPIC_API_KEY \
    -e OPENAI_API_KEY \
    -e OPENAI_BASE_URL \
    -e DASHSCOPE_API_KEY \
    -e MOONSHOT_API_KEY \
    -e MOONSHOT_BASE_URL \
    -v "$out_dir:/out" \
    "${extra_args[@]}" \
    gs-decomp-agent:latest \
    "$@"
