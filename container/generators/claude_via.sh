#!/usr/bin/env bash
# Generator wrapper: Claude Code CLI pointed at a third-party
# Anthropic-*compatible* endpoint instead of Anthropic's own API. Same
# invocation shape as claude.sh (agentic -- writes $BATCH itself via its
# Write tool); only the auth/base-URL env differs.
#
# Usage: claude_via.sh <prompt-file> <batch-file>
# Selected either directly (AGENT=claude_via, CLAUDE_VIA=<provider>) or via
# the AGENT=alibaba / AGENT=zai shorthands that container/generators/
# run_generator.sh maps onto this script with CLAUDE_VIA set accordingly.
#
# $CLAUDE_VIA selects the provider:
#
#   alibaba  Alibaba Cloud Model Studio (Bailian). Anthropic-compatible
#            endpoint documented at
#            https://www.alibabacloud.com/help/en/model-studio/claude-code
#            Two plans, chosen by $ALIBABA_PLAN (default "token"; the coding key on this host was rejected --
#            the one with the qwen3-coder-* models):
#              coding  https://coding-intl.dashscope.aliyuncs.com/apps/anthropic
#                      (the /apps/anthropic sibling of the Coding Plan's
#                      OpenAI-compatible https://coding-intl.dashscope.aliyuncs.com/v1)
#                      models e.g. qwen3-coder-plus, qwen3-coder-next,
#                      qwen3.7-plus, glm-5, kimi-k2.5
#              token   https://token-plan.ap-southeast-1.maas.aliyuncs.com/apps/anthropic
#                      (the /apps/anthropic sibling of the Token Plan's
#                      https://token-plan.ap-southeast-1.maas.aliyuncs.com/compatible-mode/v1)
#                      models e.g. qwen3.7-plus, qwen3.7-max,
#                      qwen3.8-max-preview, deepseek-v4-pro, kimi-k2.7-code,
#                      glm-5.2, MiniMax-M2.5
#            Auth: $ANTHROPIC_AUTH_TOKEN if already set (container/run.sh
#            resolves this on the host from ~/.qwen/settings.json's
#            BAILIAN_CODING_PLAN_API_KEY / BAILIAN_TOKEN_PLAN_API_KEY,
#            matching $ALIBABA_PLAN, and forwards it in -- see run.sh's
#            comment), else $ALIBABA_API_KEY if the caller exported that
#            directly instead. Never logged either way.
#
#   zai      Z.ai / Zhipu GLM Coding Plan. Anthropic-compatible endpoint
#            https://api.z.ai/api/anthropic
#            (https://docs.z.ai/devpack/tool/claude -- "the only provider
#            besides Anthropic itself with a true Anthropic-compatible
#            API"). Auth: $ZAI_API_KEY. No key for this provider exists on
#            this machine yet -- this wrapper fails clearly if it's unset.
#
#   custom   Any other Anthropic-compatible endpoint:
#            $CLAUDE_VIA_BASE_URL (base URL) + $CLAUDE_VIA_API_KEY (token).
#
# $GENERATOR_MODEL is REQUIRED for every provider here -- unlike claude.sh
# there is no "sonnet" alias a third-party endpoint understands, so this
# wrapper refuses to guess a default. It's used both as --model and (via
# ANTHROPIC_DEFAULT_SONNET_MODEL/_OPUS_MODEL/_HAIKU_MODEL) as the target for
# any internal Claude Code model routing, so a background/haiku-tier call
# the CLI makes on its own stays on the same provider instead of resolving
# an Anthropic-side alias that would fail auth against a provider token.
#
# $ANTHROPIC_API_KEY and $CLAUDE_CODE_OAUTH_TOKEN are unset before exec so a
# real Anthropic credential sitting in the environment is never picked up in
# preference to the provider token (Claude Code prefers a real API key over
# ANTHROPIC_AUTH_TOKEN when both are present).
set -eu
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=./_common.sh
. "$SCRIPT_DIR/_common.sh"

PROMPT="$1"
BATCH="$2"

require_env GENERATOR_MODEL

CLAUDE_VIA="${CLAUDE_VIA:-}"
case "$CLAUDE_VIA" in
  alibaba)
    plan="${ALIBABA_PLAN:-token}"
    case "$plan" in
      coding) base_url="https://coding-intl.dashscope.aliyuncs.com/apps/anthropic" ;;
      token)  base_url="https://token-plan.ap-southeast-1.maas.aliyuncs.com/apps/anthropic" ;;
      *)
        echo "container/generators: unknown ALIBABA_PLAN '$plan' (want: coding|token)" >&2
        exit 1
        ;;
    esac
    api_token="${ALIBABA_API_KEY:-${ANTHROPIC_AUTH_TOKEN:-}}"
    if [ -z "$api_token" ]; then
      echo "container/generators: CLAUDE_VIA=alibaba (ALIBABA_PLAN=$plan) needs \$ANTHROPIC_AUTH_TOKEN (container/run.sh sets this from ~/.qwen/settings.json's BAILIAN_${plan}_PLAN_API_KEY -- coding/token) or \$ALIBABA_API_KEY set directly." >&2
      exit 1
    fi
    ;;
  zai)
    base_url="https://api.z.ai/api/anthropic"
    api_token="${ZAI_API_KEY:-}"
    if [ -z "$api_token" ]; then
      echo "container/generators: CLAUDE_VIA=zai needs \$ZAI_API_KEY set (Z.ai GLM Coding Plan key -- https://docs.z.ai/devpack/tool/claude). No key for this provider exists on this machine yet." >&2
      exit 1
    fi
    ;;
  custom)
    require_env CLAUDE_VIA_BASE_URL
    require_env CLAUDE_VIA_API_KEY
    base_url="$CLAUDE_VIA_BASE_URL"
    api_token="$CLAUDE_VIA_API_KEY"
    ;;
  "")
    echo "container/generators: AGENT=claude_via needs \$CLAUDE_VIA set to alibaba|zai|custom (or use AGENT=alibaba / AGENT=zai directly)." >&2
    exit 1
    ;;
  *)
    echo "container/generators: unknown CLAUDE_VIA '$CLAUDE_VIA' (want: alibaba|zai|custom)" >&2
    exit 1
    ;;
esac

unset ANTHROPIC_API_KEY CLAUDE_CODE_OAUTH_TOKEN

ANTHROPIC_BASE_URL="$base_url" \
ANTHROPIC_AUTH_TOKEN="$api_token" \
ANTHROPIC_MODEL="$GENERATOR_MODEL" \
ANTHROPIC_DEFAULT_SONNET_MODEL="$GENERATOR_MODEL" \
ANTHROPIC_DEFAULT_OPUS_MODEL="$GENERATOR_MODEL" \
ANTHROPIC_DEFAULT_HAIKU_MODEL="$GENERATOR_MODEL" \
claude -p "$(cat "$PROMPT")" \
  --output-format text \
  --model "$GENERATOR_MODEL" \
  --allowedTools Read Write Bash

validate_batch "$BATCH"
