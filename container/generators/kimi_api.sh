#!/usr/bin/env bash
# Generator wrapper: Moonshot Kimi, via the generic OpenAI-compatible path
# and a plain Moonshot Open Platform API key -- no CLI, no login state.
#
# This is the API-key sibling of kimi.sh (AGENT=kimi), which wraps the
# official Kimi Code CLI (`kimi`, https://moonshotai.github.io/kimi-code/)
# under the user's own subscription login (a mounted ~/.kimi-code, see
# container/run.sh and container/generators/README.md). That CLI *does* now
# document a stateless, config-file-free way to point it at a bare API key
# (the KIMI_MODEL_* env vars -- KIMI_MODEL_NAME, KIMI_MODEL_API_KEY,
# KIMI_MODEL_PROVIDER_TYPE=kimi -- see
# https://moonshotai.github.io/kimi-code/en/configuration/env-vars.html),
# but that still means installing and shelling out to the ~180MB `kimi`
# binary just to make one HTTP call. Moonshot's own chat-completions
# endpoint is a plain, well-documented OpenAI-compatible HTTP API
# (https://platform.kimi.ai/docs/overview), so this wrapper routes through
# openai_compat.sh instead, same as any other OpenAI-compatible provider --
# no extra binary, works from any environment with just python3 stdlib.
#
# Usage: kimi_api.sh <prompt-file> <batch-file>
# Requires: MOONSHOT_API_KEY (Moonshot Open Platform API key)
# Optional: MOONSHOT_BASE_URL (default https://api.moonshot.ai/v1; use
#           https://api.moonshot.cn/v1 for the China region)
# Default model: kimi-k2.7-code (Moonshot's coding-focused model as of
#   https://platform.kimi.ai/docs/models; override with GENERATOR_MODEL)
set -eu
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=./_common.sh
. "$SCRIPT_DIR/_common.sh"

require_env MOONSHOT_API_KEY

export OPENAI_API_KEY="$MOONSHOT_API_KEY"
export OPENAI_BASE_URL="${MOONSHOT_BASE_URL:-https://api.moonshot.ai/v1}"
export GENERATOR_MODEL="${GENERATOR_MODEL:-kimi-k2.7-code}"

exec "$SCRIPT_DIR/openai_compat.sh" "$@"
