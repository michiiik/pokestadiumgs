#!/usr/bin/env bash
# Generator wrapper: Moonshot Kimi, via the generic OpenAI-compatible path.
#
# Why not wrap the official `kimi` CLI (pip install kimi-cli) directly:
# it does confirm a non-interactive single-prompt mode (-p/--prompt with
# --print and --yolo for auto-approval --
# https://github.com/MoonshotAI/kimi-cli, reference:
# https://moonshotai.github.io/kimi-cli/en/reference/kimi-command.html), but
# its auth is wired through `kimi login` / a TOML provider config
# (https://moonshotai.github.io/kimi-cli/en/configuration/providers.html)
# with no single documented stateless env var, which does not fit a
# disposable, non-interactive container. Moonshot's own chat-completions API
# is a plain, well-documented OpenAI-compatible HTTP endpoint
# (https://platform.kimi.ai/docs/overview), so route through
# openai_compat.sh instead, same as any other OpenAI-compatible provider.
#
# Usage: kimi.sh <prompt-file> <batch-file>
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
