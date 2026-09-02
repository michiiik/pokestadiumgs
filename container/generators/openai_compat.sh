#!/usr/bin/env bash
# Generator wrapper: generic OpenAI-chat-completions-compatible fallback.
# No CLI/agent required -- talks straight HTTP via openai_compat.py
# (Python stdlib only, no pip deps). Use this for any provider that speaks
# the OpenAI /chat/completions wire format but has no dedicated wrapper here.
#
# Usage: openai_compat.sh <prompt-file> <batch-file>
# Requires: OPENAI_API_KEY, OPENAI_BASE_URL (e.g. https://api.openai.com/v1),
#           GENERATOR_MODEL
set -eu
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=./_common.sh
. "$SCRIPT_DIR/_common.sh"

PROMPT="$1"
BATCH="$2"

require_env OPENAI_API_KEY
require_env OPENAI_BASE_URL
require_env GENERATOR_MODEL

python3 "$SCRIPT_DIR/openai_compat.py" "$PROMPT" "$BATCH"

validate_batch "$BATCH"
