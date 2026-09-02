#!/usr/bin/env bash
# Generator wrapper: Claude Code CLI (agentic -- writes $BATCH itself via its
# Write tool; the prompt file already contains the batch JSON schema and the
# exact output path per tools/container_agent.py's BATCH_CONTRACT).
#
# Usage: claude.sh <prompt-file> <batch-file>
# Install: npm install -g @anthropic-ai/claude-code
# Requires: ANTHROPIC_API_KEY
# Default model: sonnet (override with GENERATOR_MODEL)
#
# Flags verified locally against `claude --help` (Claude Code 2.1.258):
#   -p, --print                 non-interactive, print response and exit
#       --output-format <fmt>   "text" | "json" | "stream-json"
#       --model <model>         alias ("sonnet") or full model name
#       --allowedTools <tools>  space-separated tool allowlist, auto-approved
#                                without prompting in --print mode
set -eu
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=./_common.sh
. "$SCRIPT_DIR/_common.sh"

PROMPT="$1"
BATCH="$2"

require_env ANTHROPIC_API_KEY

claude -p "$(cat "$PROMPT")" \
  --output-format text \
  --model "${GENERATOR_MODEL:-sonnet}" \
  --allowedTools Read Write Bash

validate_batch "$BATCH"
