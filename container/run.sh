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
#   AGENT             claude (default) | codex | qwen | kimi | kimi_api |
#                     openai_compat | claude_via | alibaba | zai
#   GENERATOR_MODEL   override the wrapper's default model (REQUIRED for
#                     claude_via/alibaba/zai -- no default)
#   GENERATOR_EFFORT  codex reasoning effort (low|medium|high|xhigh); also
#                     forwarded to kimi as KIMI_MODEL_THINKING_EFFORT
#                     (low|high|max for the default kimi-code/k3)
#   ANTHROPIC_API_KEY claude (or CLAUDE_CODE_OAUTH_TOKEN from `claude setup-token`)
#   OPENAI_API_KEY    codex, qwen (or DASHSCOPE_API_KEY), openai_compat
#   OPENAI_BASE_URL   openai_compat (required), qwen (optional)
#   DASHSCOPE_API_KEY qwen, alternate to OPENAI_API_KEY
#   MOONSHOT_API_KEY  kimi_api
#   MOONSHOT_BASE_URL kimi_api, optional (default: global Moonshot endpoint)
#   KIMI_MODEL_NAME   kimi, alternate to a subscription login: paired with
#   KIMI_MODEL_API_KEY   KIMI_MODEL_API_KEY, the official CLI's own
#                     stateless API-key model definition (both required
#                     together; see container/generators/kimi.sh)
#   KIMI_CODE_HOME    kimi, optional: relocate the CLI's data/config root
#                     (default ~/.kimi-code) on both host lookup and
#                     in-container env
#   CLAUDE_VIA        claude_via only: alibaba | zai | custom (AGENT=alibaba
#                     and AGENT=zai set this for you -- see
#                     container/generators/README.md)
#   ALIBABA_PLAN      alibaba/claude_via(alibaba): token (default) | coding
#                     -- selects which Bailian plan's key/endpoint is used
#   ALIBABA_API_KEY   alibaba/claude_via(alibaba), optional: use this key
#                     directly instead of the ~/.qwen/settings.json lookup
#                     below
#   ZAI_API_KEY       zai/claude_via(zai): Z.ai GLM Coding Plan key. No key
#                     for this provider exists on this machine yet.
#   CLAUDE_VIA_BASE_URL / CLAUDE_VIA_API_KEY
#                     claude_via(custom): any other Anthropic-compatible
#                     endpoint's base URL + token
#
# alibaba key resolution: when AGENT is alibaba (or claude_via with
# CLAUDE_VIA=alibaba) and the caller has not exported ALIBABA_API_KEY or
# ANTHROPIC_AUTH_TOKEN themselves, this script reads the matching Bailian
# plan's dedicated key out of ~/.qwen/settings.json's "env" block
# (BAILIAN_CODING_PLAN_API_KEY or BAILIAN_TOKEN_PLAN_API_KEY, selected by
# $ALIBABA_PLAN) and forwards it into the container as ANTHROPIC_AUTH_TOKEN.
# The key is never written to disk or logged -- it only ever lives in this
# shell's environment and docker's own -e passthrough.
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

# Kimi Code CLI with a subscription login instead of an API key: mount a
# throwaway copy of the host's ~/.kimi-code (or $KIMI_CODE_HOME) login state
# so token refreshes never touch the original -- same pattern as codex above.
# Copies the specific files the CLI reads for auth/config, not the whole
# directory (which also holds session history, logs, etc.).
kimi_home_src="${KIMI_CODE_HOME:-$HOME/.kimi-code}"
if [ "${AGENT:-claude}" = "kimi" ] && [ -z "${KIMI_MODEL_API_KEY:-}" ] && [ -f "$kimi_home_src/credentials/kimi-code.json" ]; then
    # Mount the REAL login directory read-write, not a copy. Kimi Code
    # rotates its refresh token on every refresh; a refresh inside a copied
    # directory invalidates the host's token and the host's next refresh
    # fails with "authorization grant is invalid" and clears the credential.
    # Consequence: do not use `kimi` on the host while a container run is
    # active, and never run two kimi containers at once.
    extra_args+=(-v "$kimi_home_src:/root/.kimi-code")
elif [ -n "${KIMI_CODE_HOME:-}" ]; then
    extra_args+=(-e KIMI_CODE_HOME="$KIMI_CODE_HOME")
fi

# Alibaba Cloud Model Studio (AGENT=alibaba, or AGENT=claude_via
# CLAUDE_VIA=alibaba): resolve the matching plan's dedicated API key out of
# ~/.qwen/settings.json's "env" block into ANTHROPIC_AUTH_TOKEN for the
# container, unless the caller already exported ALIBABA_API_KEY (used
# directly by container/generators/claude_via.sh instead) or
# ANTHROPIC_AUTH_TOKEN themselves. Never written to disk or logged -- held
# only in this shell's environment for the docker run -e below.
want_alibaba=0
case "${AGENT:-claude}" in
    alibaba) want_alibaba=1 ;;
    claude_via) [ "${CLAUDE_VIA:-}" = "alibaba" ] && want_alibaba=1 ;;
esac
if [ "$want_alibaba" -eq 1 ] && [ -z "${ALIBABA_API_KEY:-}" ] && [ -z "${ANTHROPIC_AUTH_TOKEN:-}" ] \
   && [ -f "$HOME/.qwen/settings.json" ]; then
    settings_key="BAILIAN_CODING_PLAN_API_KEY"
    [ "${ALIBABA_PLAN:-token}" = "token" ] && settings_key="BAILIAN_TOKEN_PLAN_API_KEY"
    resolved_token="$(python3 -c '
import json, sys
try:
    d = json.load(open(sys.argv[1]))
    print(d.get("env", {}).get(sys.argv[2], ""))
except Exception:
    pass
' "$HOME/.qwen/settings.json" "$settings_key")"
    if [ -n "$resolved_token" ]; then
        export ANTHROPIC_AUTH_TOKEN="$resolved_token"
    fi
fi

# --tmpfs bounds two IDO temp-file leak sinks in RAM instead of the
# container's writable layer: /tmp (the default) and /work/disasm/scratch
# (tools/try_pragma_compare.py, imported by the permuter driver, redirects
# TMPDIR there for runner-driven compiles). IDO's as0/as1/ugen create ctm*
# temp files honouring $TMPDIR and only clean up on a normal exit;
# decomp-permuter kills unpromising compiles constantly, stranding one each
# time (~7.5M files/hour measured). Bounding by size+inodes here fails
# loudly (ENOSPC/inode exhaustion) instead of silently growing the host
# image; entrypoint.sh also sweeps stray ctm* files periodically so a
# long run never gets close to the cap.
docker run \
    --platform linux/amd64 \
    --rm \
    --tmpfs /tmp:size=2g,nr_inodes=4m \
    --tmpfs /work/disasm/scratch:size=2g,nr_inodes=4m \
    -e SOURCE="$source_file" \
    -e AGENT \
    -e GENERATOR_MODEL \
    -e GENERATOR_EFFORT \
    -e ANTHROPIC_API_KEY \
    -e CLAUDE_CODE_OAUTH_TOKEN \
    -e OPENAI_API_KEY \
    -e OPENAI_BASE_URL \
    -e DASHSCOPE_API_KEY \
    -e MOONSHOT_API_KEY \
    -e MOONSHOT_BASE_URL \
    -e KIMI_MODEL_NAME \
    -e KIMI_MODEL_API_KEY \
    -e CLAUDE_VIA \
    -e ALIBABA_PLAN \
    -e ALIBABA_API_KEY \
    -e ZAI_API_KEY \
    -e CLAUDE_VIA_BASE_URL \
    -e CLAUDE_VIA_API_KEY \
    -e ANTHROPIC_AUTH_TOKEN \
    -v "$out_dir:/out" \
    ${extra_args[@]+"${extra_args[@]}"} \
    gs-decomp-agent:latest \
    "$@"
