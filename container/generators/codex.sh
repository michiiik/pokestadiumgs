#!/usr/bin/env bash
# Generator wrapper: OpenAI Codex CLI (agentic -- writes $BATCH itself; the
# prompt file already contains the batch JSON schema and output path per
# tools/container_agent.py's BATCH_CONTRACT).
#
# Usage: codex.sh <prompt-file> <batch-file>
# Install: npm install -g @openai/codex
# Requires: OPENAI_API_KEY
# Default model: gpt-5.1-codex (override with GENERATOR_MODEL; codex accounts
#   vary in which model ids they can access -- set GENERATOR_MODEL if this
#   default 404s)
#
# Flags verified locally against `codex exec --help` (codex-cli 0.152.0):
#   codex exec [OPTIONS] [PROMPT]   non-interactive ("exec"/"e" subcommand);
#                                   PROMPT omitted or "-" reads stdin
#   -m, --model <MODEL>             model the agent should use
#   --dangerously-bypass-approvals-and-sandbox
#                                    "Skip all confirmation prompts and
#                                    execute commands without sandboxing...
#                                    Intended solely for running in
#                                    environments that are externally
#                                    sandboxed" -- exactly this container.
#     (docs: https://developers.openai.com/codex/noninteractive,
#      https://developers.openai.com/cookbook/examples/codex/autofix-github-actions
#      confirm OPENAI_API_KEY as the CI/headless auth env var.)
set -eu
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=./_common.sh
. "$SCRIPT_DIR/_common.sh"

PROMPT="$1"
BATCH="$2"

require_env OPENAI_API_KEY

codex exec \
  --dangerously-bypass-approvals-and-sandbox \
  --skip-git-repo-check \
  -m "${GENERATOR_MODEL:-gpt-5.1-codex}" \
  - < "$PROMPT"

validate_batch "$BATCH"
