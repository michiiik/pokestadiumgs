#!/usr/bin/env bash
# Generator wrapper: Qwen Code CLI (agentic -- writes $BATCH itself; the
# prompt file already contains the batch JSON schema and output path per
# tools/container_agent.py's BATCH_CONTRACT).
#
# Usage: qwen.sh <prompt-file> <batch-file>
# Install: npm install -g @qwen-code/qwen-code
# Requires (pick one auth style -- https://qwenlm.github.io/qwen-code-docs/en/users/configuration/auth/):
#   OpenAI-compatible: OPENAI_API_KEY (+ optional OPENAI_BASE_URL, OPENAI_MODEL/QWEN_MODEL)
#   DashScope:         DASHSCOPE_API_KEY
# Default model: qwen3-coder-plus (override with GENERATOR_MODEL)
#
# Flags verified locally against `qwen --help` (qwen-code 0.22.3):
#   -p, --prompt          run one prompt non-interactively, then exit
#   -m, --model            model
#   -o, --output-format    "text" | "json" | "stream-json"
#   --approval-mode <mode>  "default" | "plan" | "auto-edit" | "yolo"
# (headless mode doc: https://qwenlm.github.io/qwen-code-docs/en/users/features/headless/
#  -- "Headless / CI runs combined with --yolo (or --approval-mode=yolo)
#  auto-approve every tool call, including shell, write, and edit." Without
#  it, -p mode does NOT auto-approve tool calls -- unlike kimi.sh/claude.sh,
#  qwen needs this flag or it would sit waiting for an approval prompt that
#  can never arrive non-interactively, unable to write $BATCH or run
#  tools/probe_one.py at all. --yolo does not itself sandbox anything, but
#  this always runs inside the already-sandboxed gs-decomp-agent container,
#  same reasoning as codex.sh's --dangerously-bypass-approvals-and-sandbox.)
set -eu
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=./_common.sh
. "$SCRIPT_DIR/_common.sh"

PROMPT="$1"
BATCH="$2"

require_any_env OPENAI_API_KEY DASHSCOPE_API_KEY

qwen -p "$(cat "$PROMPT")" \
  --output-format text \
  --model "${GENERATOR_MODEL:-qwen3-coder-plus}" \
  --approval-mode yolo

validate_batch "$BATCH"
